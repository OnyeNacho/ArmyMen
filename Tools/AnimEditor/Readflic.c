#include "stdafx.h"

/* readflic.c -- Routines to read and decompress a flic. Assumes Intel byte
 * ordering, but otherwise should be fairly portable. Calls machine-specific
 * stuff in pcclone.c. This file starts with the low-level decompression
 * routines: first for colors, then for pixels. It then goes to higher-level
 * exported flic_xxxx routines as prototyped in readflic.h.
 * Copyright (c) 1992 Jim Kent. This file may be freely used, modified,
 * copied and distributed. This file was first published as part of
 * an article for Dr. Dobb's Journal March 1993 issue. */

#include <errno.h>
#include <string.h>
#include <io.h>
#include "types.h"
#include "pcclone.h"
#include "flic.h"
#include "readflic.h"

typedef void ColorOut(Screen *s, int start, Color far *colors, int count);
    /* This is the type of output parameter to our decode_color below.
     * Not coincidently screen_put_color is of this type. */
static void decode_color(Uchar huge *data
, Flic *flic, Screen *s, ColorOut *output)
    /* Decode color map. Put results into output. Two color compressions
         * are identical except that RGB values are 0-63 or 0-255. Passing in
         * an output that does appropriate shifting on way to real pallete lets
         * us use the same code for both COLOR_64 and COLOR_256 compression. */
{
int start = 0;
Uchar far *cbuf = (Uchar far *)data;
Short far *wp = (Short far *)cbuf;
Short ops;
int count;

ops = *wp;
cbuf += sizeof(*wp);
while (--ops >= 0)
    {
    start += *cbuf++;
    if ((count = *cbuf++) == 0)
        count = 256;
    (*output)(s, start, (Color far *)cbuf, count);
    cbuf += 3*count;
    start += count;
    }
}
static void decode_color_256(Uchar huge *data, Flic *flic, Screen *s)
    /* Decode COLOR_256 chunk. */
{
decode_color(data, flic, s, screen_put_colors);
}
static void decode_color_64(Uchar huge *data, Flic *flic, Screen *s)
    /* Decode COLOR_64 chunk. */
{
decode_color(data, flic, s, screen_put_colors_64);
}
static void decode_byte_run(Uchar huge *data, Flic *flic, Screen *s)
    /* Byte-run-length decompression. */
{
int x,y;
int width = flic->head.width;
int height = flic->head.height;
Char psize;
Char huge *cpt = data;
int end;

y = flic->yoff;
end = flic->xoff + width;
while (--height >= 0)
    {
    x = flic->xoff;
    cpt += 1;   /* skip over obsolete opcount byte */
    psize = 0;
    while ((x+=psize) < end)
        {
        psize = *cpt++;
        if (psize >= 0)
            {
            screen_repeat_one(s, x, y, *cpt++, psize);
            }
        else
            {
            psize = -psize;
            screen_copy_seg(s, x, y, (Pixel far *)cpt, psize);
            cpt += psize;
            }
        }
    y++;
    }
}
static void decode_delta_fli(Uchar huge *data, Flic *flic, Screen *s)
    /* Fli style delta decompression. */
{
int xorg = flic->xoff;
int yorg = flic->yoff;
Short huge *wpt = (Short huge *)data;
Uchar huge *cpt = (Uchar huge *)(wpt + 2);
int x,y;
Short lines;
Uchar opcount;
Char psize;

y = yorg + *wpt++;
lines = *wpt;
while (--lines >= 0)
    {
    x = xorg;
    opcount = *cpt++;
    while (opcount > 0)
        {
        x += *cpt++;
        psize = *cpt++;
        if (psize < 0)
            {
            psize = -psize;
            screen_repeat_one(s, x, y, *cpt++, psize);
            x += psize;
            opcount-=1;
            }
        else
            {
            screen_copy_seg(s, x, y, (Pixel far *)cpt, psize);
            cpt += psize;
            x += psize;
            opcount -= 1;
            }
        }
    y++;
    }
}
static void decode_delta_flc(Uchar huge *data, Flic *flic, Screen *s)
    /* Flc-style delta decompression. Data is word-oriented. Much control info
     * (how far to skip, how many words to copy) are still byte-oriented. */
{
int xorg = flic->xoff;
int yorg = flic->yoff;
int width = flic->head.width;
int x,y;
Short lp_count;
Short opcount;
int psize;
union {Short huge *w; Uchar huge *ub; Char huge *b; Pixels2 huge *p2;} wpt;
int lastx;
    lastx = xorg + width - 1;
    wpt.ub = data;
    lp_count = *wpt.w++;
    y = yorg;
    goto LPACK;
SKIPLINES:  /* Advance over some lines. */
    y -= opcount;
LPACK:      /* do next line */
    if ((opcount = *wpt.w++) >= 0)
        goto DO_SS2OPS;
    if( ((Ushort)opcount) & 0x4000) /* skip lines */
        goto SKIPLINES;
    screen_put_dot(s,(Uchar)opcount,lastx,y); /* eol dot with low byte */
    if((opcount = *wpt.w++) == 0)
    {
        ++y;
        if (--lp_count > 0)
            goto LPACK;
        goto OUT;
    }
DO_SS2OPS:
    x = xorg;
PPACK:              /* do next packet */
    x += *wpt.ub++;
    psize = *wpt.b++;
    if ((psize += psize) >= 0)
    {
        screen_copy_seg(s, x, y, (Pixel far *)wpt.ub, psize);
        x += psize;
        wpt.ub += psize;
        if (--opcount != 0)
            goto PPACK;
        ++y;
        if (--lp_count > 0)
            goto LPACK;
    }
    else
    {
        psize = -psize;
        screen_repeat_two(s, x, y, *wpt.p2++, psize>>1);
        x += psize;
        if (--opcount != 0)
            goto PPACK;
        ++y;
        if (--lp_count > 0)
            goto LPACK;
    }
OUT:
    return;
}
static void decode_black(Uchar huge *data, Flic *flic, Screen *s)
     /* Decode a BLACK chunk. Set frame to solid color 0 one line at a time. */
{
Pixels2 black;
int i;
int height = flic->head.height;
int width = flic->head.width;
int x = flic->xoff;
int y = flic->yoff;

black.pixels[0] = black.pixels[1] = 0;
for (i=0; i<height; ++i)
    {
    screen_repeat_two(s, x, y+i, black, width/2);
    if (width & 1)  /* if odd set last pixel */
        screen_put_dot(s, x+width-1, y+i, 0);
    }
}
static void decode_literal(Uchar huge *data, Flic *flic, Screen *s)
    /* Decode a LITERAL chunk. Copy data to screen one line at a time. */
{
int i;
int height = flic->head.height;
int width = flic->head.width;
int x = flic->xoff;
int y = flic->yoff;

for (i=0; i<height; ++i)
    {
    screen_copy_seg(s, x, y+i, (Pixel far *)data, width);
    data += width;
    }
}
ErrCode flic_open(Flic *flic, char *name)
    /* Open flic file. Read header, verify it's a flic. Seek to first frame. */
{
ErrCode err;
ClearStruct(flic);      /* Start at a known state. */
if ((err = file_open_to_read(&flic->handle, name)) >= Success)
     {
     if ((err = file_read_block(flic->handle, &flic->head, sizeof(flic->head)))
     >= Success)
        {
        flic->name = name;      /* Save name for future use. */
        if (flic->head.type == FLC_TYPE)
            {
            /* Seek frame 1. */
            lseek(flic->handle,flic->head.oframe1,SEEK_SET);
            return Success;
            }
        if (flic->head.type == FLI_TYPE)
            {
            /* Do some conversion work here. */
            flic->head.oframe1 = sizeof(flic->head);
            flic->head.speed = flic->head.speed * 1000L / 70L;
            return Success;
            }
        else
            {
            err = ErrBadFlic;
            }
        }
    flic_close(flic);     /* Close down and scrub partially opened flic. */
    }
return err;
}
void flic_close(Flic *flic)
    /* Close flic file and scrub flic. */
{
close(flic->handle);
ClearStruct(flic);      /* Discourage use after close. */
}
static ErrCode decode_frame(Flic *flic
, FrameHead *frame, Uchar huge *data, Screen *s)
    /* Decode a frame that is in memory already into screen. Here we
     * loop through each chunk calling appropriate chunk decoder. */
{
int i;
ChunkHead huge *chunk;
for (i=0; i<frame->chunks; ++i)
    {
    chunk = (ChunkHead huge *)data;
    data += chunk->size;
    switch (chunk->type)
        {
        case COLOR_256:
            decode_color_256((Uchar huge *)(chunk+1), flic, s);
            break;
        case DELTA_FLC:
            decode_delta_flc((Uchar huge *)(chunk+1), flic, s);
            break;
        case COLOR_64:
            decode_color_64((Uchar huge *)(chunk+1), flic, s);
            break;
        case DELTA_FLI:
            decode_delta_fli((Uchar huge *)(chunk+1), flic, s);
            break;
        case BLACK:
            decode_black((Uchar huge *)(chunk+1), flic, s);
            break;
        case BYTE_RUN:
            decode_byte_run((Uchar huge *)(chunk+1), flic, s);
            break;
        case LITERAL:
            decode_literal((Uchar huge *)(chunk+1), flic, s);
            break;
        default:
            break;
        }
    }
return Success;
}
ErrCode flic_next_frame(Flic *flic, Screen *screen)
    /* Advance to next frame of flic. */
{
FrameHead head;
ErrCode err;
BigBlock bb;
long size;
if ((err = file_read_block(flic->handle, &head, sizeof(head))) >= Success)
    {
    if (head.type == FRAME_TYPE)
        {
        size = head.size - sizeof(head);    /* Don't include head. */
        if (size > 0)
              {
              if ((err = big_alloc(&bb, size)) >= Success)
               {
               if ((err = file_read_big_block(flic->handle, &bb, size))
            >= Success)
            {
                  err = decode_frame(flic, &head, bb.hpt, screen);
                    }
                big_free(&bb);
                }
            }
        }
    else
        {
        err = ErrBadFrame;
        }
    }
return err;
}
static Ulong calc_end_time(Ulong millis, Clock *clock)
    /* Little helper subroutine to find out when to start on next frame. */
{
return clock_ticks(clock) + millis * clock->speed / 1000l;
}
static ErrCode wait_til(Ulong end_time, Machine *machine)
    /* This waits until key is hit or end_time arrives. Return Success if timed
    * out, ErrCancel if key hit. Insures keyboard poll at least once. */
{
    do
        {
        if (key_ready(&machine->key))
            {
            key_read(&machine->key);
            return ErrCancel;
            }
        }
    while (clock_ticks(&machine->clock) < end_time);
    return Success;
}
ErrCode flic_play_once(Flic *flic, Machine *machine)
    /* Play a flic through once. */
{
ErrCode err;
int i;
Ulong end_time;
for (i=0; i<flic->head.frames; ++i)
    {
    end_time = calc_end_time(flic->head.speed, &machine->clock);
    if ((err = flic_next_frame(flic, &machine->screen)) < Success)
        break;
    if ((err = wait_til(end_time, machine)) < Success)
        break;
    }
return err;
}
static ErrCode fill_in_frame2(Flic *flic)
      /* This determines where second frame of flic is (useful for a loop). */
{
FrameHead head;
ErrCode err;
lseek(flic->handle, flic->head.oframe1, SEEK_SET);
if ((err = file_read_block(flic->handle, &head, sizeof(head))) < Success)
    return err;
flic->head.oframe2 = flic->head.oframe1 + head.size;
return Success;
}
ErrCode flic_play_loop(Flic *flic, Machine *machine)
    /* Play a flic until key is pressed. */
{
int i;
Ulong end_time;
ErrCode err;

if (flic->head.oframe2 == 0)
    {
    fill_in_frame2(flic);
    }
    /* Seek to first frame. */
lseek(flic->handle, flic->head.oframe1, SEEK_SET);
    /* Save time to move on. */
end_time = calc_end_time(flic->head.speed, &machine->clock);
    /* Display first frame. */
if ((err = flic_next_frame(flic, &machine->screen)) < Success)
    return err;
for (;;)
    {
        /* Seek to second frame */
    lseek(flic->handle, flic->head.oframe2, SEEK_SET);
        /* Loop from 2nd frame thru ring frame*/
    for (i=0; i<flic->head.frames; ++i)
        {
        if (wait_til(end_time, machine) < Success)
            return Success;     /* Time out is a success here. */
        if ((err = flic_next_frame(flic, &machine->screen)) < Success)
            return err;
        end_time = calc_end_time(flic->head.speed, &machine->clock);
        }
    }
}
static char *err_strings[] =
    {
    "Unspecified error",
    "Not enough memory",
    "Not a flic file",
    "Bad frame in flic",
    NULL,
    NULL,
    "Couldn't open display",
    "Couldn't open keyboard",
    "User canceled action",
    };
char *flic_err_string(ErrCode err)
    /* Return a string that describes an error. */
{
    if (err >= Success)
        return "Success";         /* Shouldn't happen really... */
    if (err == ErrOpen || err == ErrRead)
        return strerror(errno); /* Get Disk IO error from DOS. */
    err = -err;
    err -= 1;
    if (err > ArrayEls(err_strings))
        return "Unknown error";
    return err_strings[err];
}

