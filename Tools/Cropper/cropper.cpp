/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: cropper.cpp $
//
//	DESCRIPTION:	crop a .bmp and add a hotspot if specified in data
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		1/12/1988
//
//	REVISION:		$Header: /ArmyMen/Tools/Cropper/cropper.cpp 19    1/21/98 4:23p Nrobinso $
//
//	Original Copyright (c) 1988-89, Nicky Robinson.
//	Modified Copyright (c) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/Tools/Cropper/cropper.cpp $
//  
//  19    1/21/98 4:23p Nrobinso
//  improve info printout; fix link bug if hotspot is negative
//  
//  18    11/19/97 11:51a Nrobinso
//  version 2.13; adds link spots
//  
//  17    11/19/97 10:55a Nrobinso
//  version 1.12; output a default mask (-mm)
//  
//  16    6/20/97 1:43p Nrobinso
//  When looking for reg point by RGB color, ANY use of that color is
//  looked for, not just the first one in the color list
//  
//  15    6/05/97 11:30a Nrobinso
//  version 1.9 fix mask rect, so that no rectangle is 0,0,0,0'
//  version 1.10 adds the internal hotspot options which replaces the
//  hotspot with the same color pixel as the one to the immediate left
//  instead of transparent
//  
//  14    3/28/97 10:36a Nrobinso
//  version 1.8; properly exports 1 bit masks
//  
//  13    2/05/97 12:54p Nrobinso
//  added RGB color based hotspot, transparent color and rectangle
//  detection
//  
//  12    2/04/97 11:25a Nrobinso
//  use more standard file interface; add a pause flag
//  
//  11    11/18/96 8:37p Nrobinso
//  if no hotspot, automatically leaves space for future hotspot; new
//  option to save off rectangle collision info
//  
//  10    10/24/96 3:44p Nrobinso
//  update version to 1.4
//  
//  8     10/08/96 6:52p Nrobinso
//  Added the -f flag, which reserves a transparent strip along the bottom
//  & right for future placement of a hotspot.
//  
//  Added version info (1.3)
//  
//  7     8/23/96 1:47p Nrobins
//  If bitmap size in header is listed as 0, calculate it instead
//  
//  6     8/13/96 8:53p Nrobins
//  Can force upper left to transparent; displays transparent color #
//  
//  5     7/30/96 12:09p Nrobins
//  Fixed bug with figuring hotspot with no reg mark
//  
//  4     7/22/96 7:14p Nrobins
//  added history info
//  
//  3     7/22/96 6:24p Nrobins
//  fixed up help message
// 
//  2     7/22/96 6:12p Nrobins
//  add ability to set hotspot to a particular point (relative to the uncropped bitmap)
// 
//  1     7/18/96 1:13p Nrobins
//  Created Cropper tool
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/* --------------------------------INCLUDES--------------------------------- */
#include <conio.h>
#include <io.h>
#include <malloc.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

/* ---------------------------------DEFINES--------------------------------- */
#define FNAMELENGTH 255
#define	MASKING	1

#define	REGCOLOR	0xFF
#define	RECTCOLOR	0xFE

#define MAX_COLORS 256

#define	pprintf1(a) {if (print) printf(a);}
#define	pprintf2(a,b) {if (print) printf(a,b);}

#define READ_BUFFER(pBuffer, howmany) Read((char *)pBuffer, howmany, 1, pFile)

/* ---------------------------------TYPEDEFS-------------------------------- */
typedef enum {
	LEFT,CENTER,RIGHT,NOHORZ
} HorzHotspot;
typedef enum {
	TOP,MIDDLE,BOTTOM,NOVERT
} VertHotspot;

typedef struct {
	BITMAPFILEHEADER bmfile;
	BITMAPINFOHEADER bminfo;
	RGBQUAD *pColor;
	int num_colors;
	BYTE *pBits;
	POINT hotspot;
	POINT linkspot;
} BITMAPFILE;

typedef struct {
	int major;
	int minor;
} Version;

/* --------------------------------PROTOTYPES------------------------------- */
void 	cdecl	main(int argc, char *argv[]);
BOOL	DoFile(char *fname);
BOOL	ReadFile(char *fname, BITMAPFILE *pFile);
BOOL	WriteFile(char *fname, BITMAPFILE *pbmfile);
BOOL	ModifyData(BITMAPFILE *pinfile, BITMAPFILE *poutfile);
BOOL	Read( void *buffer, size_t size, size_t count, FILE *stream );
void	SetColors(BITMAPFILE *pbmfile);
BOOL	MatchColors(RGBQUAD colors[MAX_COLORS], int num_colors, RGBQUAD *match);
inline BOOL	MatchColor(LONG colors[MAX_COLORS], BYTE which_color, LONG *match);

/* -------------------------------GLOBAL DATA------------------------------- */
Version version = {1,15};

BOOL	smallest = TRUE,
		pause = FALSE,
		internal = FALSE,
		future = TRUE,
		force_transparent = TRUE,
		set_upper_left = FALSE,
		print = TRUE,
		set_regcolor = TRUE,
		set_xpc = TRUE,
		set_rectcolor = TRUE,
		xpc_from_ul = FALSE,
		reg_override = FALSE,
		cropped_hotspot = TRUE,
		save_rect = FALSE,	// save rectangle file instead of cropped BMP
		save_mask = FALSE,	// save mask file instead of cropped BMP
		save_x_mask = FALSE,
		check_reg = TRUE,	// calculate hotspot from reg pixels and consider them transparent
		use_reg = TRUE,		// actually use reg hotspot
		add_link = FALSE;	// add link hotspot

// globals, but reset for every file
BOOL	this_xpc_from_ul,
		this_set_regcolor,
		this_check_reg;

BYTE	regcolor = REGCOLOR,
		rectcolor = RECTCOLOR,
		xpc = 0;
POINT	reg,
		new_reg,
		zero = {0,0};
RECT	out_rect;
LONG	vert_hot = NOHORZ,
		horz_hot = NOVERT;
POINT	hotoff;
char	name[FNAMELENGTH];
RGBQUAD	colors[MAX_COLORS];
RGBQUAD	regRGB = {255,0,255,0},
		rectRGB = {0,255,255,0},
		xpRGB = {255,255,0,0};

/* -------------------------------STATIC DATA------------------------------- */

/* -----------------------------------CODE---------------------------------- */

/******************************************************************************
FUNC:	void cdecl	main(int argc, char *argv[])
DESC:	
		
NOTES:	

HISTORY:	Created By Nicky
		
******************************************************************************/

void cdecl
main(int argc, char *argv[])
{
	int		i;
	BOOL	ok = FALSE;
	BYTE	color;

	if (argc < 2)	{
		printf(	"USAGE: cropper [-options] filename(s)\n");
		printf(	"Version %d.%d\n", version.major, version.minor);
		printf(	"Crops .BMP file(s) to smallest possible image file(s)\n"
				"Sets hotspot into biXPelsPerMeter & biYPelsPerMeter from reg mark, defaults\n"
				"to 0,0 (ul). If none, an extra row & column for future hotspot is reserved.\n"
				"Press key for options\n"
				);

		getch();

		printf(	"Options:\n"
					"\t-c        turn off crop\n"
					"\t-i        internal hotspot; hotspot replaced with pixel one to the left\n"
					"\t-f        do not crop for future hotspot\n"
					"\t-n        no hotspot (leave as is)\n"
					"\t-h        zero hotspot to upper left of cropped image\n"
					"\t-hb,hm,ht set hotspot to bottom, middle, or top of cropped image\n"
					"\t-hl,hc,hr set hotspot to left, center, or right of cropped image\n"
					"\t-H        zero hotspot to upper left of original image\n"
					"\t-Hb,Hm,Ht set hotspot to bottom, middle, or top of original image\n"
					"\t-Hl,Hc,Hr set hotspot to left, center, or right of original image\n"
					"\t-o        turn off output to screen\n"

					"\t-s        no Spot reg mark color\n"
					"\t-s#       set color index of Spot reg mark to #\n"
					"\t-SR# -SG# -SB#   set RGB color of Spot reg mark (defauts to 255 0 255 - magenta)\n"

					"\t-t        set transparent color to ul corner\n"
					"\t-t#       set transparent color index\n"
					"\t-TR# -TG# -TB#   set transparent RGB color (defaults to 0 255 255 - cyan)\n"

					"\t-r        output Rectangle file (254 is color index of rect)\n"
					"\t-r#       output rectangle file (# is color index of rect)\n"

					"\t-R        output Rectangle file (255 255 0 - yellow - is RGB color of rect)\n"
					"\t-RR# -RG# -RB#   output Rectangle file (#'s are RGB color of rect)\n"

					"\t-l        add link information from upper left corner\n"

					"\t-mm       output Mask file (mask is any non-transparent)\n"

					"\t-m        output Mask file (254 is color index of mask)\n"
					"\t-m#       output Mask file (# is color index of mask)\n"

					"\t-M        output Mask file (255 255 0 - yellow - is RGB color of mask)\n"
					"\t-MR# -MG# -MB#   output Mask file (#'s are RGB color of mask)\n"

					"\t-u        turn off upper left forced to transparent\n"
					"\t-x#,-y#   set hotspot.x or hotspot.y to point in original image\n"
					"\t-dx#,-dy# move hotspot.x or hotspot.y\n"
//					"\t-Dx#,-Dy# move hotspot.x or hotspot.y relative to width or height\n"
				);
		}
	else {
		printf(	"Cropper %d.%d\n", version.major, version.minor);

		for (i=1;i<argc;i++) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
					case 'P':
						pause = TRUE;
						break;

					case 'o':
						print = FALSE;
						break;

					case 'c':
						smallest = FALSE;
						break;

					case 'f':
						future = FALSE;
						break;

					case 'i':
						internal = TRUE;
						break;

					case 'u':
						force_transparent = FALSE;
						break;

					case 'n':
						use_reg = FALSE;
						break;

					case 'l':
						add_link = TRUE;
						break;

					case 'r':
						save_rect = TRUE;

						if (argv[i][2])
							rectcolor = (BYTE) atoi(&argv[i][2]);
						else
							set_rectcolor = FALSE;
						break;

					case 'R':
						save_rect = TRUE;

						if (argv[i][2])	{
							if (argv[i][3])	{
								color = (BYTE) atoi(&argv[i][3]);
								switch(argv[i][2])	{
									case 'R':
										rectRGB.rgbRed = color;
										break;
									case 'G':
										rectRGB.rgbGreen = color;
										break;
									case 'B':
										rectRGB.rgbBlue = color;
										break;
								}
							}
						}
						break;

					case 'm':
						save_mask = TRUE;

						if (argv[i][2])	{
							if (argv[i][2] == 'm')	{
								save_x_mask = TRUE;
								smallest = FALSE;
							}
							else
								rectcolor = (BYTE) atoi(&argv[i][2]);
						}
						else
							set_rectcolor = FALSE;
						break;

					case 'M':
						save_mask = TRUE;

						if (argv[i][2])	{
							if (argv[i][3])	{
								color = (BYTE) atoi(&argv[i][3]);
								switch(argv[i][2])	{
									case 'R':
										rectRGB.rgbRed = color;
										break;
									case 'G':
										rectRGB.rgbGreen = color;
										break;
									case 'B':
										rectRGB.rgbBlue = color;
										break;
								}
							}
						}
						break;

					case 's':
						if (argv[i][2] == '\0')
							check_reg = FALSE;
						else	{
							set_regcolor = FALSE;
							if (argv[i][2])
								regcolor = (BYTE) atoi(&argv[i][2]);
						}
						break;

					case 'S':
						if (argv[i][2])	{
							if (argv[i][3])	{
								color = (BYTE) atoi(&argv[i][3]);
								switch(argv[i][2])	{
									case 'R':
										regRGB.rgbRed = color;
										break;
									case 'G':
										regRGB.rgbGreen = color;
										break;
									case 'B':
										regRGB.rgbBlue = color;
										break;
								}
							}
						}
						break;

					case 't':	/* transparent color */
						if (argv[i][2] == '\0')
							xpc_from_ul = TRUE;
						else	{
							set_xpc = FALSE;
							if (argv[i][2])
								xpc = (BYTE) atoi(&argv[i][2]);
						}
						break;

					case 'T':
						if (argv[i][2])	{
							if (argv[i][3])	{
								color = (BYTE) atoi(&argv[i][3]);
								switch(argv[i][2])	{
									case 'R':
										xpRGB.rgbRed = color;
										break;
									case 'G':
										xpRGB.rgbGreen = color;
										break;
									case 'B':
										xpRGB.rgbBlue = color;
										break;
								}
							}
						}
						break;

					case 'H':	/* hotspot setting relative to original image */
						cropped_hotspot = FALSE;

					case 'h':	/* hotspot setting relative to cropped image */
						switch (argv[i][2]) {
							case '\0':
								horz_hot = LEFT;
								vert_hot = TOP; 
								break;

							case 'b':
								vert_hot = BOTTOM;
								break;

							case 'c':
								horz_hot = CENTER;
								break;

							case 'l':
								horz_hot = LEFT;
								break;

							case 'm':
								vert_hot = MIDDLE;
								break;

							case 'r':
								horz_hot = RIGHT;
								break;
									
							case 't':
								vert_hot = TOP; 
								break;

						}
						break;

					case 'x':
						new_reg.x = atoi(&argv[i][2]);
						reg_override = TRUE;
						break;

					case 'y':
						new_reg.y = atoi(&argv[i][2]);
						reg_override = TRUE;
						break;

					case 'd':
						switch (argv[i][2]) {
							case 'x':
								hotoff.x = atoi(&argv[i][3]);
								break;
							case 'y':
								hotoff.y = atoi(&argv[i][3]);
								break;
						}
						break;
				}
			}
			else {
				HANDLE handle;
				WIN32_FIND_DATA FindFileData;

				handle = FindFirstFile(argv[i], &FindFileData);
				if (handle != INVALID_HANDLE_VALUE)	{
					ok = DoFile(FindFileData.cFileName);
					while (FindNextFile(handle, &FindFileData))	{
						if (pause)
							getch();
						ok &= DoFile(FindFileData.cFileName);
					}
				}
				else	{
					pprintf2("unable to find file |%s|",argv[i]);
				}
			}
		}
	}

//	_getch();
	if (ok)
		exit(0);
	else
		exit(-1);
}



/*****************************************************************************
FUNC:	BOOL DoFile(pChar fname)
DESC:	
INPUTS:
NOTES:	
ASSUMES:	
HISTORY:	Created By Evan
*****************************************************************************/

BOOL
DoFile(char *fname)
{
	BOOL retval = FALSE;
	BITMAPFILE	infile,
				outfile;

	this_set_regcolor = set_regcolor;
	this_xpc_from_ul = xpc_from_ul;
	this_check_reg = check_reg;

	infile.pBits = NULL;
	outfile.pBits = NULL;

	infile.pColor = colors;
	outfile.pColor = colors;

	if (ReadFile(fname, &infile))	{
		SetColors(&infile);
		if (ModifyData(&infile, &outfile))
			retval = WriteFile(fname, &outfile);
	}

	if (infile.pBits)
		free(infile.pBits);
	if (outfile.pBits)
		free(outfile.pBits);

	return retval;
}


/******************************************************************************
FUNC:	BOOL ReadFile(char *fname, BITMAPFILE *pbmfile)
DESC:	gets the bitmap data,
		
NOTES:	

HISTORY:	Created By Nicky
		
******************************************************************************/
BOOL
ReadFile(char *fname, BITMAPFILE *pbmfile)	{
	FILE *pFile;
	BYTE *pBits;
	BITMAPFILEHEADER *pbmfilehdr;
	BITMAPINFOHEADER *pbminfohdr;

	pbmfilehdr = &pbmfile->bmfile;
	pbminfohdr = &pbmfile->bminfo;

	pprintf2("\n%s: ",fname);
	if ((pFile = fopen(fname,"rb")) != NULL) {	/* open input file */
		READ_BUFFER(pbmfilehdr, sizeof(BITMAPFILEHEADER));

		if (pbmfilehdr->bfType != 0x4D42)	{
			pprintf2("ERROR: Not a bitmap (BM) file: %s\n", fname);
			fclose(pFile);
			return FALSE;
		}

		READ_BUFFER(pbminfohdr, sizeof(BITMAPINFOHEADER));

		if (pbminfohdr->biBitCount != 8)	{
			pprintf2("ERROR: Not an 8 bit file: %s\n", fname);
			fclose(pFile);
			return FALSE;
		}

		if (pbminfohdr->biClrUsed == 0)
			pbminfohdr->biClrUsed = 1 << pbminfohdr->biBitCount;

		pbmfile->num_colors = pbminfohdr->biClrUsed;
		int iColorTableSize = pbminfohdr->biClrUsed * sizeof(RGBQUAD);

		// Now read the color table in
		READ_BUFFER( pbmfile->pColor, iColorTableSize );

		if (pbminfohdr->biSizeImage == 0)	{
			long pitch = (pbminfohdr->biWidth + 3) & 0xFFFFFFFC;
			pbminfohdr->biSizeImage = pitch * pbminfohdr->biHeight;
		}

		// Allocate the memory for the bitmap data.
		pBits = (BYTE *) malloc(pbminfohdr->biSizeImage);
		if (!pBits) {
			pprintf2("ERROR: Out of memory for bitmap data: %s\n", fname);
			fclose(pFile);
			return FALSE;
		}

		// Seek to the bits
		fseek(pFile, pbmfilehdr->bfOffBits, SEEK_SET);

		// Read the bits.
		READ_BUFFER(pBits, pbminfohdr->biSizeImage);

		pbmfile->pBits = pBits;

		fclose(pFile);

		pprintf1("size=");
		pprintf2("%dx",pbminfohdr->biWidth);
		pprintf2("%d  ",pbminfohdr->biHeight);

		return TRUE;
	}
	else	{
		pprintf1("Cannot Open Input File\n");
	}

	return FALSE;
}


/*****************************************************************************
FUNC:	BOOL SetColors(BITMAPFILE *pinfile)
DESC:	set registration mark, rectangle color and transparent color indexes from RGB colors

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/

void
SetColors(BITMAPFILE *pbmfile)
{
//	int color;

	if (set_regcolor && this_check_reg)	{
		if (!MatchColors(pbmfile->pColor, pbmfile->num_colors, &regRGB))	{
			pprintf1("no color match of reg color; using index 255\n");
			this_set_regcolor = FALSE;
		}
	}
	if (set_xpc)	{
		if (!MatchColors(pbmfile->pColor, pbmfile->num_colors, &xpRGB))	{
			pprintf1("no color match of transparent color; using ul corner\n");
			this_xpc_from_ul = TRUE;
		}
	}
	if (set_rectcolor && save_rect)	{
		if (!MatchColors(pbmfile->pColor, pbmfile->num_colors, &rectRGB))	{
			pprintf1("no color match of rect color; rect will be 0\n");
		}
	}
}

/*****************************************************************************
FUNC:	BOOL MatchColors(RGBQUAD colors[MAX_COLORS], int num_colors, RGBQUAD *match)
DESC:	check to see if any color in color array matches target color

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/

BOOL
MatchColors(RGBQUAD colors[MAX_COLORS], int num_colors, RGBQUAD *match)	{
	for (int i=0; i<num_colors; i++)	{
		if (colors[i].rgbBlue == match->rgbBlue)	{
			if (colors[i].rgbGreen == match->rgbGreen)	{
				if (colors[i].rgbRed == match->rgbRed)	{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

/*****************************************************************************
FUNC:	BOOL MatchColor(LONG colors[MAX_COLORS], BYTE which_color, LONG *match)
DESC:	check to see target RGB color matches the indexed color in the color list

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/

inline BOOL
MatchColor(LONG colors[MAX_COLORS], BYTE which_color, LONG *match)	{
	if (colors[which_color] == *match)	{
		return TRUE;
	}

	return FALSE;
}


/*****************************************************************************
FUNC:	BOOL ModifyData(BITMAPFILE *pinfile, BITMAPFILE *poutfile)
DESC:	crop image and find hotspot
		does background transform, if necessary

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/

BOOL
ModifyData(BITMAPFILE *pinfile, BITMAPFILE *poutfile)
{
	LONG	width,
			height,
			pitch,
			out_width,
			out_height,
			out_pitch;
	BYTE	*pBits = NULL,
			*buffer;
	BOOL	gotreg = FALSE,
			gotrect = FALSE,
			xpcline,
			firstline;
	int		x,y;
	POINT	ul,
			lr,
			hotspot,
			linkspot;

	memset(&out_rect,0,sizeof(out_rect));

	// Allocate the memory for the bitmap data.
	pBits = (BYTE *) malloc(pinfile->bminfo.biSizeImage);
	if (!pBits) {
		pprintf1("ERROR: Out of memory for new bitmap data\n");
		return FALSE;
	}
	memset(pBits,0,pinfile->bminfo.biSizeImage);

	poutfile->pBits = pBits;
	poutfile->bmfile = pinfile->bmfile;
	poutfile->bminfo = pinfile->bminfo;

	width = pinfile->bminfo.biWidth;
	height = pinfile->bminfo.biHeight;
	pitch = pinfile->bminfo.biSizeImage / height;
	if (this_xpc_from_ul)
		xpc = pinfile->pBits[0];


	// scan bitmap to find area to crop and any reg points
	ul.x = ul.y = 64000;
	lr.x = lr.y = 0;
	firstline = TRUE;

	for (y=0;y<(int) height;y++) {
		xpcline = TRUE;
		buffer = &pinfile->pBits[y*pitch];		// pointer to beginning of line

		for (x=0;x<width;x++) {
			if (xpc != buffer[x]) {
				if ( MatchColor((LONG *) pinfile->pColor, buffer[x], (LONG *) &regRGB) && (this_check_reg) && (this_set_regcolor)) {	// look for reg point by RGB color
					reg.y = y;
					if (!gotreg)
						reg.x = x;
					gotreg = TRUE;
					buffer[x] = xpc;
					if (internal && x!=0)	{
						buffer[x] = buffer[x-1];
					}
				}
				else if ((regcolor == buffer[x]) && (this_check_reg)) {	// look for reg point by index
					reg.y = y;
					if (!gotreg)
						reg.x = x;
					gotreg = TRUE;
					buffer[x] = xpc;
					if (internal && x!=0)	{
						buffer[x] = buffer[x-1];
					}
				}
				else if ((rectcolor == buffer[x]) && (save_rect))	{ // look for rect
					if (!gotrect)	{
						out_rect.left = out_rect.right = x;
						out_rect.top = out_rect.bottom = y;
					}
					else	{
						out_rect.right = x;
						out_rect.bottom = y;
					}
					gotrect = TRUE;
				}
				else	{
					if (firstline) {
						firstline = FALSE;
						ul.y = y;
					}

					if (x > lr.x)
						lr.x = x;

					if (xpcline) {
						xpcline = FALSE;
						if (x < ul.x)
							ul.x = x;
					}

					lr.y = y;
				}
			}
		}
	}

	if (!smallest || (ul.x > lr.x) || (ul.y > lr.y))	{
		ul = zero;
		lr.x = width-1;
		lr.y = height-1;
	}

	if (save_rect && !gotrect)	{	// set outrect to extent of bitmap
		out_rect.left = 0;
		out_rect.top = 0;
		out_rect.bottom = 0;
		out_rect.right = 0;
	}

	if (!gotreg)	{
		reg.x = ul.x;
		reg.y = lr.y;

		BOOL warning = FALSE;
		if (future)	{
			if (lr.x < width - 1)	{
				lr.x++;
			}
			else	{
				warning = TRUE;
			}

			if (ul.y > 0)	{
				ul.y--;
			}
			else	{
				warning = TRUE;
			}
		}

		if (warning)	{
			pprintf1("Unable to crop for future hotspot\n");
		}
		else	{
			if (this_check_reg)	{
				pprintf1("no hotspot found\n");
			}
		}
	}

	poutfile->bminfo.biHeight = out_height = 1 + lr.y - ul.y;
	poutfile->bminfo.biWidth = out_width = 1 + lr.x - ul.x;
	out_pitch = (out_width + 3) & 0xFFFFFFFC;

	// copy cropped area
	BYTE	*src,
			*dest;

	src = &pinfile->pBits[ul.y * pitch + ul.x];
	dest = &poutfile->pBits[0];
	for (y=0; y<out_height; y++) {
		memcpy(dest,src,out_width);
		src += pitch;
		dest += out_pitch;
	}

	poutfile->bminfo.biSizeImage = out_pitch * out_height;

	// force upper left pixel to be transparent
	set_upper_left = FALSE;
	if (force_transparent)	{
		src = &poutfile->pBits[(out_height-1) * out_pitch];
		if (src[0] != xpc)	{
			src[0] = xpc;
			set_upper_left = TRUE;
		}
	}

	// calculate hotspot

	// bitmap is bottom up, so flip y for ul, lr and reg
	// ul & lr must also be swapped
	long temp = ul.y;
	ul.y = height - lr.y - 1;
	lr.y = height - temp - 1;
	reg.y = height - reg.y - 1;

	if (reg_override)	{
		reg = new_reg;
	}

	// also swap the rectangle
	if (gotrect)	{
		temp = out_rect.top;
		out_rect.top = height - out_rect.bottom - 1 - ul.y;
		out_rect.bottom = height - temp - 1 - ul.y;

		out_rect.left -= ul.x;
		out_rect.right -= ul.x;
	}

	switch (horz_hot) {
		case NOHORZ:
			hotspot.x = reg.x - ul.x;
			break;

		case LEFT:
			if (cropped_hotspot)
				hotspot.x = 0;
			else
				hotspot.x = -ul.x;
			break;

		case CENTER:
			if (cropped_hotspot)
				hotspot.x = out_width/2;
			else
				hotspot.x = ul.x + out_width/2;
			break;

		case RIGHT:
			if (cropped_hotspot)
				hotspot.x = out_width - 1;
			else
				hotspot.x = ul.x + out_width - 1;
			break;
	}

	switch (vert_hot) {
		case NOVERT:
			hotspot.y = reg.y - ul.y;
			break;

		case TOP:
			if (cropped_hotspot)
				hotspot.y = 0;
			else
				hotspot.y = -ul.y;
			break;

		case MIDDLE:
			if (cropped_hotspot)
				hotspot.y = out_height/2;
			else
				hotspot.y = ul.y + out_height/2;
			break;

		case BOTTOM:
			if (cropped_hotspot)
				hotspot.y = out_height - 1;
			else
				hotspot.y = ul.y + out_height - 1;
			break;
	}

	// add any offset
	hotspot.x += hotoff.x;
	hotspot.y += hotoff.y;

	if (use_reg)	{
		poutfile->bminfo.biXPelsPerMeter = hotspot.x;
		poutfile->bminfo.biYPelsPerMeter = hotspot.y;

		poutfile->bminfo.biXPelsPerMeter &= 0xFFFF;
		poutfile->bminfo.biYPelsPerMeter &= 0xFFFF;

		poutfile->hotspot.x = hotspot.x;
		poutfile->hotspot.y = hotspot.y;

		if (add_link)	{
			linkspot.x = -ul.x;
			linkspot.y = -ul.y;

			poutfile->bminfo.biXPelsPerMeter |= (linkspot.x << 16);
			poutfile->bminfo.biYPelsPerMeter |= (linkspot.y << 16);

			poutfile->linkspot.x = linkspot.x;
			poutfile->linkspot.y = linkspot.y;
		}
	}


	// translate mask into 1 bit values
	if (save_mask)	{
		BYTE	*pMaskBits = NULL;
		LONG	mask_pitch;

		// Allocate new memory for the mask data.
		pMaskBits = (BYTE *) malloc(pinfile->bminfo.biSizeImage);
		if (!pMaskBits) {
			pprintf1("ERROR: Out of memory for new mask data\n");
			return FALSE;
		}
		memset(pMaskBits,0,pinfile->bminfo.biSizeImage);

		mask_pitch = (out_width + 7) / 8;
		mask_pitch = (mask_pitch + 3) & 0xFFFFFFFC;

		src = &poutfile->pBits[0];
		dest = pMaskBits;
		if (save_x_mask)	{
			for (y=0; y<out_height; y++) {
				for (x=0; x<out_width; x+=8)	{
					int bytes = 8;
					if ((x+8) > out_width)
						bytes = out_width - x;
					BYTE value = 0;
					for (int a=0; a<bytes; a++)	{
						if (xpc != src[x+a])	{
							value |= (1 << (7-a));
						}
					}
					dest[x/8] = value;
				}

				src += out_pitch;
				dest += mask_pitch;
			}
		}
		else	{
			for (y=0; y<out_height; y++) {
				for (x=0; x<out_width; x+=8)	{
					int bytes = 8;
					if ((x+8) > out_width)
						bytes = out_width - x;
					BYTE value = 0;
					for (int a=0; a<bytes; a++)	{
						if (rectcolor == src[x+a])	{
							value |= (1 << (7-a));
						}
					}
					dest[x/8] = value;
				}

				src += out_pitch;
				dest += mask_pitch;
			}
		}

		poutfile->bminfo.biSizeImage = mask_pitch * out_height;
		poutfile->bminfo.biBitCount = 1;
		poutfile->bminfo.biClrUsed = poutfile->bminfo.biClrImportant = 2;

		static RGBQUAD black = {0,0,0,0};
		static RGBQUAD white = {0xFF,0xFF,0xFF,0};
		poutfile->pColor[0] = black;
		poutfile->pColor[1] = white;

	// free the old data, and point to the new mask data
		free(poutfile->pBits);
		poutfile->pBits = pMaskBits;
	}

	return TRUE;
}


/******************************************************************************
FUNC:	BOOL WriteFile(char *fname, BITMAPFILE *pbmfile)
DESC:	write new bitmap data,
		
NOTES:	

HISTORY:	Created By Nicky
		
******************************************************************************/
BOOL
WriteFile(char *fname, BITMAPFILE *pbmfile)	{
	FILE *pFile;
	BITMAPFILEHEADER *pbmfilehdr;
	BITMAPINFOHEADER *pbminfohdr;
	long color_size;
	char new_fname[256];
	char *dot;


	if (save_rect)	{
		strcpy(new_fname, fname);
		dot = strchr( new_fname, '.' );
		if (dot)
			*dot = '\0';
		strcat(new_fname, ".REC");
  
		if ((pFile = fopen(new_fname,"wb")) != NULL) {	/* open output file */
			pprintf1("out_rect = {");
			pprintf2("%d,",out_rect.left);
			pprintf2("%d,",out_rect.top);
			pprintf2("%d,",out_rect.right);
			pprintf2("%d",out_rect.bottom);

			pprintf1("};\n");

			fwrite(&out_rect,sizeof(RECT),1,pFile);

			fclose(pFile);
			return TRUE;
		}
		else	{
			pprintf1("Cannot Open Output File\n");
		}

		return FALSE;
	}

	if (save_mask)	{
		strcpy(new_fname, fname);
		dot = strchr( new_fname, '.' );
		if (dot)
			*dot = '\0';
		strcat(new_fname, ".MSK");
		fname = new_fname;
	}

	pbmfilehdr = &pbmfile->bmfile;
	pbminfohdr = &pbmfile->bminfo;

	color_size = pbminfohdr->biClrUsed * sizeof(RGBQUAD);

	pbmfilehdr->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + color_size;
	if (pbmfilehdr->bfSize != pbmfilehdr->bfOffBits)	{
		pbmfilehdr->bfOffBits = pbmfilehdr->bfSize;
	}
	pbmfilehdr->bfSize += pbminfohdr->biSizeImage;
	
	if ((pFile = fopen(fname,"wb")) != NULL) {	/* open output file */
		pprintf1("new size=");
		pprintf2("%dx",pbminfohdr->biWidth);
		pprintf2("%d  ",pbminfohdr->biHeight);

		pprintf1("hotspot=");
		pprintf2("%d,",pbmfile->hotspot.x);
		pprintf2("%d  ",pbmfile->hotspot.y);

		pprintf1("linkspot=");
		pprintf2("%d,",pbmfile->linkspot.x);
		pprintf2("%d  ",pbmfile->linkspot.y);

		pprintf1("combo=");
		pprintf2("%X,",pbmfile->bminfo.biXPelsPerMeter);
		pprintf2("%X  ",pbmfile->bminfo.biYPelsPerMeter);

		pprintf2("xpc=%d  ",xpc);

		if (set_upper_left)
			pprintf1("WARNING: set upper left");

		pprintf1("\n");

		fwrite(pbmfilehdr,sizeof(BITMAPFILEHEADER),1,pFile);
		fwrite(pbminfohdr,sizeof(BITMAPINFOHEADER),1,pFile);

		fwrite(pbmfile->pColor,1,color_size,pFile);
		fwrite(pbmfile->pBits,1,pbminfohdr->biSizeImage,pFile);

		fclose(pFile);
		return TRUE;
	}
	else	{
		pprintf1("Cannot Open Output File\n");
	}

	return FALSE;
}


BOOL
Read( void *buffer, size_t size, size_t count, FILE *stream )	{
	if ( fread( buffer, size, count, stream ) != 1 )	{
		// report an error: failed reading header
		pprintf1("ERROR: failed to read.\n");
		return FALSE;
	}
	return TRUE;
}


