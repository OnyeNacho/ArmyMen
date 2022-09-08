/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: shadow.cpp $
//
//	DESCRIPTION:	crop a .bmp and add a hotspot if specified in data
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		1/12/1988
//
//	REVISION:		$Header: /ArmyMen/Tools/ResizeShadow/shadow.cpp 1     12/03/97 4:02p Nrobinso $
//
//	Original Copyright (c) 1988-89, Nicky Robinson.
//	Modified Copyright (c) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/Tools/ResizeShadow/shadow.cpp $
//  
//  1     12/03/97 4:02p Nrobinso
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/* --------------------------------INCLUDES--------------------------------- */
#include <conio.h>
#include <io.h>
#include <malloc.h>
#include <direct.h>
#include <memory.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

/* ---------------------------------DEFINES--------------------------------- */
#define FNAMELENGTH 255
#define	MASKING	1

#define MAX_COLORS 256

#define	pprintf1(a) {if (print) printf(a);}
#define	pprintf2(a,b) {if (print) printf(a,b);}

#define READ_BUFFER(pBuffer, howmany) Read((char *)pBuffer, howmany, 1, pFile)

/* ---------------------------------TYPEDEFS-------------------------------- */
typedef struct {
	BITMAPFILEHEADER bmfile;
	BITMAPINFOHEADER bminfo;
	RGBQUAD	colors[MAX_COLORS];
	int num_colors;
	BYTE *pBits;
	RECT expand_rect;
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
BOOL	ReadRect(char *fname, RECT *pRect);
BOOL	WriteRect(char *fname, RECT *pRect);
BOOL	ResizeBitmap(BITMAPFILE *pinfile, BITMAPFILE *poverlayfile, BITMAPFILE *poutfile);
BOOL	ResizeRect(RECT *pinrect, RECT *pnewrect);
BOOL	Read( void *buffer, size_t size, size_t count, FILE *stream );
BOOL	ConvertTo8Bit(BITMAPFILE *pbmfile);
BOOL	ConvertTo1Bit(BITMAPFILE *pbmfile);
void	CopyHotspot(BITMAPFILE *destfile, BITMAPFILE *srcfile);
void	CheckRect(BITMAPFILE *file1, BITMAPFILE *file2);

/* -------------------------------GLOBAL DATA------------------------------- */
Version version = {1,0};

BOOL	pause = FALSE,
		print = TRUE;
char	out_folder[] = "Shadow.out";
char	rects_folder[] = "Shadow.out/Rects";
char	masks_folder[] = "Shadow.out/Masks";

RGBQUAD color_black = {0,0,0,0};
RGBQUAD color_white = {255,255,255,0};
RGBQUAD color_blue = {255,0,0,0};

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

	if (argc < 2)	{
		printf(	"USAGE: ResizeShadow [-options] filename(s)\n");
		printf(	"Version %d.%d\n", version.major, version.minor);
		printf(	"Resizes shadow and associated .BMP, .REC and .MSK file(s) to minimum possible\n" );
		printf(	"Resized files in folder %s\n", out_folder );
		}
	else {
		printf(	"ResizeShadow %d.%d\n", version.major, version.minor);

		for (i=1;i<argc;i++) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
					case 'P':
						pause = TRUE;
						break;

					case 'o':
						print = FALSE;
						break;
				}
			}
			else {
				HANDLE handle;
				WIN32_FIND_DATA FindFileData;
				char *dot;
				char filename[MAX_PATH];

				// make output folders
				_mkdir(out_folder);
				_mkdir(rects_folder);
				_mkdir(masks_folder);

				// look for shadows and process them
				strcpy(filename, argv[i]);
				dot = strchr( filename, '.' );
				if (dot)
					*dot = '\0';
				strcat(filename, ".sha");

				handle = FindFirstFile(filename, &FindFileData);
				if (handle != INVALID_HANDLE_VALUE)	{
					ok = DoFile(FindFileData.cFileName);
					while (FindNextFile(handle, &FindFileData))	{
						if (pause)
							getch();
						ok &= DoFile(FindFileData.cFileName);
					}
				}
				else	{
					pprintf2("unable to find file |%s|",filename);
				}
			}
		}
	}

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
DoFile(char *sha_name)
{
	BOOL retval = FALSE;
	BITMAPFILE	shafile,
				basefile,
				maskfile,
				outfile;
	char *dot;
	char basename[MAX_PATH];
	char rectname[MAX_PATH];
	char maskname[MAX_PATH];
	RECT rect;

	strcpy(basename, sha_name);
	dot = strchr( basename, '.' );
	if (dot)
		*dot = '\0';

	strcpy(rectname, "Rects/");
	strcat(rectname, basename);
	strcat(rectname, ".REC");

	strcpy(maskname, "Masks/");
	strcat(maskname, basename);
	strcat(maskname, ".MSK");

	strcat(basename, ".BMP");
	

	if (ReadFile(sha_name, &shafile))	{		// read in shadow file
		if (ReadFile(basename, &basefile))	{	// read in base .BMP file

			// resize .BMP
			if (ResizeBitmap(&basefile, &shafile, &outfile))	{
				WriteFile(basename, &outfile);
				free(outfile.pBits);
			}

			// resize .SHA
			if (ResizeBitmap(&shafile, &basefile, &outfile))	{
				ConvertTo1Bit(&outfile);
				WriteFile(sha_name, &outfile);
				free(outfile.pBits);
			}

			// resize mask, if exists
			if (ReadFile(maskname, &maskfile))	{		// read in mask file
				CopyHotspot(&maskfile, &basefile);

				if (ResizeBitmap(&maskfile, &shafile, &outfile))	{
					CheckRect(&maskfile, &basefile);
					ConvertTo1Bit(&outfile);
					WriteFile(maskname, &outfile);
					free(outfile.pBits);
				}
				free(maskfile.pBits);
			}

			// resize rect, if exists
			if (ReadRect(rectname, &rect))	{			// read in rect file
				ResizeRect(&rect, &basefile.expand_rect);
				WriteRect(rectname, &rect);
			}

			free(basefile.pBits);
		}
		free(shafile.pBits);
	}


	return retval;
}

//  Load a Rect from a file
BOOL ReadRect( char *szName, RECT *pRect )
{
	FILE *pFile;

	if ( ( pFile = fopen( szName, "rb" ) ) != NULL )	
	{
		READ_BUFFER( pRect, sizeof(RECT) );
		fclose( pFile );
		return TRUE;
	}
	else
		return FALSE;
}	// RectLoad


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

	memset(pbmfile, 0, sizeof(BITMAPFILE));

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

		if (pbminfohdr->biClrUsed == 0)
			pbminfohdr->biClrUsed = 1 << pbminfohdr->biBitCount;

		pbmfile->num_colors = pbminfohdr->biClrUsed;
		int iColorTableSize = pbminfohdr->biClrUsed * sizeof(RGBQUAD);

		// Now read the color table in
		READ_BUFFER( pbmfile->colors, iColorTableSize );

		if (pbminfohdr->biSizeImage == 0)	{
			long pitch = (pbminfohdr->biWidth + sizeof(LONG) - 1) & ~3;
			pbminfohdr->biSizeImage = (pitch * pbminfohdr->biHeight * pbminfohdr->biBitCount) / 8;
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

		pprintf2("%dow,",pbminfohdr->biWidth);
		pprintf2("%doh  ",pbminfohdr->biHeight);

		if (pbminfohdr->biBitCount != 8)
			ConvertTo8Bit(pbmfile);

		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
FUNC:	BOOL ConvertTo8Bit(BITMAPFILE *pbmfile)
DESC:	convert bitmap to 8 bit
		
NOTES:	

HISTORY:	Created By Nicky
		
******************************************************************************/
BOOL
ConvertTo8Bit(BITMAPFILE *pbmfile)	{
	BYTE	*pBits = NULL;
	LONG	new_pitch,
			base_pitch,
			pitch,
			width,
			height,
			new_size;
	int		x,y;
	BYTE	*src,
			*dest;

	width = pbmfile->bminfo.biWidth;
	height = pbmfile->bminfo.biHeight;
	base_pitch = (width + 7) / 8;
	pitch = (base_pitch + 3) & ~3;

	new_pitch = (width + 3) & ~3;
	new_size = new_pitch * height;

	// Allocate new memory for the mask data.
	pBits = (BYTE *) malloc(new_size);
	if (!pBits) {
		pprintf1("ERROR: Out of memory for new 8-bit data\n");
		return FALSE;
	}
	memset(pBits,0,new_size);

	src = &pbmfile->pBits[0];
	dest = pBits;

	for (y=0; y<height; y++) {
		for (x=0; x<base_pitch; x++)	{
			int bytes = 8;
			if ((x*8+8) > width)
				bytes = width - x*8;
			for (int a=0; a<bytes; a++)	{
				if (src[x] & (1 << (7-a)))
					dest[x*8+a] = 255;
			}
		}

		src += pitch;
		dest += new_pitch;
	}

	free(pbmfile->pBits);
	pbmfile->pBits = pBits;

	pbmfile->bminfo.biSizeImage = new_size;
	pbmfile->bminfo.biBitCount = 8;
	pbmfile->bminfo.biClrUsed = 256;

	pbmfile->colors[0] = color_black;
	pbmfile->colors[255] = color_white;

	for (int i=1; i<255; i++)
		pbmfile->colors[i] = color_blue;

//	WriteFile("test8.bmp", pbmfile);

	return TRUE;
}

/******************************************************************************
FUNC:	BOOL ConvertTo1Bit(BITMAPFILE *pbmfile)
DESC:	convert bitmap to 1 bit
		
NOTES:	

HISTORY:	Created By Nicky
		
******************************************************************************/
BOOL
ConvertTo1Bit(BITMAPFILE *pbmfile)	{
	BYTE	*pBits = NULL;
	LONG	new_pitch,
			pitch,
			width,
			height;
	int		x,y;
	BYTE	xpc;
	BYTE	value;
	BYTE	*src,
			*dest;

	width = pbmfile->bminfo.biWidth;
	height = pbmfile->bminfo.biHeight;
	pitch = (width + sizeof(LONG) - 1) & ~3;

	xpc = pbmfile->pBits[pitch*(height-1)];

	// Allocate new memory for the mask data.
	pBits = (BYTE *) malloc(pbmfile->bminfo.biSizeImage);
	if (!pBits) {
		pprintf1("ERROR: Out of memory for new 1-bit data\n");
		return FALSE;
	}
	memset(pBits,xpc,pbmfile->bminfo.biSizeImage);


	new_pitch = (width + 7) / 8;
	new_pitch = (new_pitch + 3) & ~3;

	src = &pbmfile->pBits[0];
	dest = pBits;

	for (y=0; y<height; y++) {
		for (x=0; x<width; x+=8)	{
			int bytes = 8;
			if ((x+8) > width)
				bytes = width - x;
			value = 0;
			for (int a=0; a<bytes; a++)	{
				if (xpc != src[x+a])	{
					value |= (1 << (7-a));
				}
			}
			dest[x/8] = value;
		}

		src += pitch;
		dest += new_pitch;
	}

	free(pbmfile->pBits);
	pbmfile->pBits = pBits;

	pbmfile->bminfo.biSizeImage = new_pitch*height;
	pbmfile->bminfo.biBitCount = 1;

	return TRUE;
}



/*****************************************************************************
FUNC:	BOOL ResizeBitmap(BITMAPFILE *pinfile, BITMAPFILE *poverlayfile, BITMAPFILE *poutfile)

DESC:	resize bitmap to new rectangle

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/
BOOL
ResizeBitmap(BITMAPFILE *pinfile, BITMAPFILE *poverlayfile, BITMAPFILE *poutfile)
{
	LONG	width,
			height,
			pitch,
			diff,
			new_width,
			new_height,
			new_size,
			new_pitch,
			left,
			top;
	BYTE	*pBits = NULL;
	int		y;
	POINT	hotspot,
			linkspot;
	RECT	rect;
	BYTE	xpc;

	ASSERT(pinfile->bminfo.biBitCount == 8);
	ASSERT(poverlayfile->bminfo.biBitCount == 8);

	// infile data
	width = pinfile->bminfo.biWidth;
	height = pinfile->bminfo.biHeight;
	pitch = (width + sizeof(LONG) - 1) & ~3;
	xpc = pinfile->pBits[pitch*(height-1)];

	ASSERT(pitch == (pinfile->bminfo.biSizeImage / height));

	hotspot.x = pinfile->bminfo.biXPelsPerMeter & 0xFFFF;
	hotspot.y = pinfile->bminfo.biYPelsPerMeter & 0xFFFF;
	linkspot.x = pinfile->bminfo.biXPelsPerMeter >> 16;
	linkspot.y = pinfile->bminfo.biYPelsPerMeter >> 16;

	// calculate new, expanded rectangle for bitmap by overlaying the bitmaps and getting the union of rectangles
	diff = hotspot.x - poverlayfile->bminfo.biXPelsPerMeter;
	rect.left = min(diff, 0);
	diff += poverlayfile->bminfo.biWidth;
	rect.right = max(diff,width);

	diff = hotspot.y - poverlayfile->bminfo.biYPelsPerMeter;
	rect.top = min(diff, 0);
	diff += poverlayfile->bminfo.biHeight;
	rect.bottom = max(diff,height);

	pinfile->expand_rect = rect;

	// calculate new size
	new_width = rect.right - rect.left;
	new_height = rect.bottom - rect.top;
	new_pitch = (new_width + sizeof(LONG) - 1) & ~3;
	new_size = new_pitch * new_height;

	// Allocate the memory for the expanded bitmap data.
	pBits = (BYTE *) malloc(new_size);
	if (!pBits) {
		pprintf1("ERROR: Out of memory for new bitmap data\n");
		return FALSE;
	}
	memset(pBits, xpc, new_size);		// fill bitmap with transparent

	poutfile->pBits = pBits;
	poutfile->bmfile = pinfile->bmfile;
	poutfile->bminfo = pinfile->bminfo;
	poutfile->bminfo.biHeight = new_height;
	poutfile->bminfo.biWidth = new_width;
	poutfile->bminfo.biSizeImage = new_size;
	poutfile->bminfo.biXPelsPerMeter = hotspot.x - rect.left;
	poutfile->bminfo.biYPelsPerMeter = hotspot.y - rect.top;
	memcpy(poutfile->colors, pinfile->colors, sizeof(poutfile->colors));

	// copy old bitmap into proper place in new bitmap
	BYTE	*src,
			*dest;

	left = -rect.left;
	top = rect.bottom - height;	// bitmap is stored bottom up, so we start with the bottom row of pixels
	src = pinfile->pBits;
	dest = &poutfile->pBits[(top * new_pitch) + left];
	for (y=0; y<height; y++) {
		memcpy(dest,src,width);
		src += pitch;
		dest += new_pitch;
	}

	return TRUE;
}


/*****************************************************************************
FUNC:	BOOL ResizeRect(RECT *pinrect, RECT *pnewrect)

DESC:	resize rectangle

INPUTS:
		
NOTES:	

ASSUMES:	

HISTORY:	Created By Nicky
		
*****************************************************************************/
BOOL
ResizeRect(RECT *pinrect, RECT *pnewrect)
{
	pinrect->left -= pnewrect->left;
	pinrect->right -= pnewrect->left;

	pinrect->top -= pnewrect->top;
	pinrect->bottom -= pnewrect->top;

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
	BOOL	ok = FALSE;

	_chdir(out_folder);

	pbmfilehdr = &pbmfile->bmfile;
	pbminfohdr = &pbmfile->bminfo;

	color_size = pbminfohdr->biClrUsed * sizeof(RGBQUAD);

	pbmfilehdr->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + color_size;
	if (pbmfilehdr->bfSize != pbmfilehdr->bfOffBits)	{
		pbmfilehdr->bfOffBits = pbmfilehdr->bfSize;
	}
	pbmfilehdr->bfSize += pbminfohdr->biSizeImage;
	
	if ((pFile = fopen(fname,"wb")) != NULL) {	// open output file
		pprintf2("%dnw,",pbminfohdr->biWidth);
		pprintf2("%dnh  ",pbminfohdr->biHeight);

		pprintf2("%dhsx,",pbminfohdr->biXPelsPerMeter);
		pprintf2("%dhsy  ",pbminfohdr->biYPelsPerMeter);

		pprintf1("\n");

		fwrite(pbmfilehdr,sizeof(BITMAPFILEHEADER),1,pFile);
		fwrite(pbminfohdr,sizeof(BITMAPINFOHEADER),1,pFile);

		fwrite(pbmfile->colors,1,color_size,pFile);
		fwrite(pbmfile->pBits,1,pbminfohdr->biSizeImage,pFile);

		fclose(pFile);
		ok = TRUE;
	}
	else	{
		pprintf1("Cannot Open Output File\n");
	}

	_chdir("..");
	return ok;
}


BOOL	WriteRect(char *fname, RECT *pRect)	{
	FILE *pFile;

	_chdir(out_folder);
	if ((pFile = fopen(fname,"wb")) != NULL) {	// open output file
		fwrite(pRect,sizeof(RECT),1,pFile);
		fclose(pFile);
	}
	else	{
		pprintf1("Cannot Open Output File\n");
	}
	_chdir("..");
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


void CopyHotspot(BITMAPFILE *destfile, BITMAPFILE *srcfile)	{
	destfile->bminfo.biXPelsPerMeter = srcfile->bminfo.biXPelsPerMeter;
	destfile->bminfo.biYPelsPerMeter = srcfile->bminfo.biYPelsPerMeter;
}

void CheckRect(BITMAPFILE *file1, BITMAPFILE *file2)	{
	ASSERT(file1->expand_rect.left == file2->expand_rect.left);
	ASSERT(file1->expand_rect.right == file2->expand_rect.right);
	ASSERT(file1->expand_rect.top == file2->expand_rect.top);
	ASSERT(file1->expand_rect.bottom == file2->expand_rect.bottom);
}
