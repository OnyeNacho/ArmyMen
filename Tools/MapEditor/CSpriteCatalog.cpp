//	CSpriteCatalog.cpp

#include "stdafx.h"
#include "CSpriteCatalog.h"

IMPLEMENT_SERIAL(CSpriteCatalog, CObject, 1)

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////
CSpriteCatalog::CSpriteCatalog() // for serialization only
{
	pRLEPixels			= NULL;
	iRLEPixelCount		= 0;

}

CSpriteCatalog::~CSpriteCatalog()
{
	for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
		delete arSeqs[ i ];

	if( pRLEPixels )
		delete [] pRLEPixels;
}

//-----------------------------------------------------------------------------------------------------------------
void CSpriteCatalog::Serialize( CArchive& ar )
{
	int iAXRVersion;
	if( ar.IsStoring() )
	{
		iAXRVersion = 1;
		ar << iAXRVersion;
		ar << csName << iSeqs << iRLEPixelCount;
	}
	else
	{
		ar >> iAXRVersion;
		ar >> csName >> iSeqs >> iRLEPixelCount;
		arSeqs.SetSize( iSeqs );
	}

	arSeqs.Serialize( ar );

	if( ar.IsStoring() )
	{

		char szHeader[] = "AXR:";
		ar.Write( szHeader, 4 );
		int iVersion = 1;
		ar.Write( &iVersion, sizeof( iVersion ) );
		ar.Write( pRLEPixels, iRLEPixelCount );
	
	}
	else
	{
		//	Read in RLE data from the rest of the file.
		char szHeader[4];
		ar.Read( szHeader, 4 );
		int iVersion;
		ar.Read( &iVersion, sizeof( iVersion ) );
		pRLEPixels = new BYTE[iRLEPixelCount];
		ar.Read( pRLEPixels, iRLEPixelCount );
		//	Set RLE data origin values in each sequence.
		for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
			arSeqs[i]->Set_arRLEOrigins( pRLEPixels );
	}
}

//-----------------------------------------------------------------------------------------------------------------
/*
 * METHOD
 *    CSpriteCatalog::DrawSprite
 *
 * PARAMETERS
 *    void *pDestStart       -- pointer to location 0,0 of the destination buffer
 *    long lPitchDest        -- pitch of the destination buffer (may be positive or negative)
 *    long iDestX,iDestY     -- x,y location of the first destination pixel
 *    DWORD dwDestWidth      -- width in pixels of the destination buffer
 *    DWORD dwDestHeight     -- height in pixels of the destination buffer
 *    CSpriteSequence *pSeq  -- which sequence to use
 *    int iFrame             -- which frame in the sequence to render
 *    BOOL bHorizFlip        -- non-zero to reverse the image horizontally.
 *
 * DESCRIPTION
 *    Draws the iFrame of the given sequence from this catalog to
 *    the destination buffer.  If bHorizFlip is non-zero, the image
 *    is flipped horizontally.
 *    
 *    Clips the sprite as needed.  
 *
 * Note:
 *    for now, this method does not render the sprite if it is clipped
 *    and horizontally flipped.
 */
void CSpriteCatalog::DrawSprite( BYTE *pDestStart, long lPitchDest, 
     int iDestX, int iDestY, DWORD dwDestWidth, DWORD dwDestHeight,
	 CSpriteSequence* pSeq, int iFrame, BOOL bHorizFlip )
{
	CPoint* pptOffset	= pSeq->arOffsets[iFrame];
	CPoint* pptSize		= pSeq->arSizes[iFrame];
	CRect rcTarget;

	if( bHorizFlip )
		rcTarget.SetRect( iDestX + pptOffset->x - pptSize->x + 1, iDestY - pptOffset->y, 
							iDestX + pptOffset->x + 1, iDestY - pptOffset->y + pptSize->y);
	else
		rcTarget.SetRect( iDestX - pptOffset->x, iDestY - pptOffset->y,
							iDestX - pptOffset->x + pptSize->x, iDestY - pptOffset->y + pptSize->y);
	
	CRect rcSource( 0, 0, pptSize->x, pptSize->y );
	BOOL bClipped = FALSE;

	if( rcTarget.left < 0L )
	{
		rcSource.left += -rcTarget.left;
		rcTarget.left = 0;
		bClipped = TRUE;
	}
	if( rcTarget.right > (LONG)dwDestWidth )
	{
		rcSource.right -= rcTarget.right - dwDestWidth;
		rcTarget.right = dwDestWidth;
		bClipped = TRUE;
	}
	if( rcTarget.top < 0L )
	{
		rcSource.top += -rcTarget.top;
		rcTarget.top = 0;
		bClipped = TRUE;
	}
	if( rcTarget.bottom > (LONG)dwDestHeight )
	{
		rcSource.bottom -= rcTarget.bottom - dwDestHeight;
		rcTarget.bottom = dwDestHeight;
		bClipped = TRUE;
	}

	if( rcTarget.left < rcTarget.right && rcTarget.top < rcTarget.bottom )		//	( Else nothing is visible. )
	{
		pDestStart += rcTarget.top * lPitchDest + rcTarget.left;
		BYTE *pSourceStart = pSeq->arRLEOrigins[iFrame];
		if( !bClipped )
		{

			if( !bHorizFlip )
				VERIFY( RLEFastBlt( pDestStart, lPitchDest, pSourceStart, pptSize->y ));
			else
				VERIFY( RLEFastBltHFlipped( pDestStart, lPitchDest, 
											pSourceStart, pptSize->y, pptSize->x ));
		}
		else
		{
			if (bHorizFlip)
				VERIFY( RLEFastBltHFlipClipped( pDestStart, lPitchDest, 
											pSourceStart, pptSize->x, &rcSource ));
			else

				VERIFY( RLEFastBltClipped( pDestStart, lPitchDest, 
										   pSourceStart, &rcSource ));
		}
	}
}


//-----------------------------------------------------------------------------------------------------------------
BOOL CSpriteCatalog::RLEFastBlt(void* pDestStart,			//	First byte in locked DD surface.
								long lPitchDest,			//	Surface's line pitch.
								const BYTE* pSrcStart,		//	First byte in RLE data.
								int	iLines )				//	Number of lines in source image.
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.

	//	Copy DWORDs at a time when possible, WORDs and BYTEs when necessary.

#if 0
	const BYTE*	pSrc = pSrcStart;
	void*		pDest = pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	int			y = 0;
	const BYTE*	pSrcQuadEnd;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= (BYTE*)pDest + qSkip;

		//	Copy color pixels...

		//	Complete sets of four pixels.
		pSrcQuadEnd = pSrc + ( qRun & ~3 );
		while( pSrc != pSrcQuadEnd )
		{
			//	*((DWORD*)pDest)++ = *((DWORD*)pSrc)++;
			*(DWORD*)pDest = *(DWORD*)pSrc;
			pDest = ((DWORD*)pDest) + 1;
			pSrc += 4;
		}
		//	Catch remainders if not divisible by four...
		if( qRun & 2 )
		{
			//	*((WORD*)pDest)++ = *((WORD*)pSrc)++;
			*(WORD*)pDest = *(WORD*)pSrc;
			pDest = ((WORD*)pDest) + 1;
			pSrc += 2;
		}
		if( qRun & 1 )
		{
			//	*((BYTE*)pDest)++ = *pSrc++;
			*(BYTE*)pDest = *pSrc;
			pDest = ((BYTE*)pDest) + 1;
			pSrc++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = (void*)( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}

#else

	BYTE* pDestTerminator = (BYTE*)pDestStart + iLines * lPitchDest;	//	Used to determine when we are done.

	__asm
	{
		mov		edx, pDestStart					//	Put destination start address in edx. This register will always point to the 
												//	beginning of the current "line".
		mov		ebx, lPitchDest					//	Save destination pitch in ebx (ebx won't change).
		mov		esi, pSrcStart					//	Put source address in esi.

		image_loop:

			mov		edi, edx						//	Set edi to beginning of destination line.

			line_loop:

				xor		ecx, ecx						//	Clear ecx.
				mov		cl, [esi]						//	Put skip count in ecx.
				inc		esi								//	Move source pointer forward.
				add		edi, ecx						//	Skip over transparent pixels in destination.

				mov		cl, [esi]						//	Put run count in ecx.
				mov		eax, ecx						//	Save run count value in eax.
				inc		esi								//	Move source pointer forward.
				shr		ecx, 2							//	Set ecx to the number of complete quads in run count.
				rep		movsd							//	Copy dwords from esi to edi (incrementing the ptrs), ecx times.

				and		eax, 0x00000003					//	Get remainder of division of run count by 4.
				mov		ecx, eax						//	Set ecx to number of remaining pixels to copy.
				rep		movsb							//	Copy bytes from esi to edi (incrementing the ptrs), ecx times.

				cmp		byte ptr [esi], 0xff			//	Is the next byte the end-of-line marker?

			jne		line_loop

			inc		esi								//	Move source pointer forward.
			add		edx, ebx						//	Advance beginning-of-line pointer to start of next line.
			cmp		edx, pDestTerminator			//	Have we reached the end of the image?

		jne		image_loop
	}

#endif

	return TRUE;
}

BOOL CSpriteCatalog::RLEFastBltHFlipped(void* pDestStart,			//	First byte in locked DD surface.
										long lPitchDest,			//	Surface's line pitch.
										const BYTE* pSrcStart,		//	First byte in RLE data.
										int	iLines,					//	Number of lines in source image.
										int iWidth )				//	Width of image.
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.
	//	Flips image horizontally.

	//	Copy BYTEs individually, for simplicity.
#if 1
    //  The assembly version seems to have an off by one bug; I think. --LKO
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart + iWidth - 1;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest - qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
			*pDest-- = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest + iWidth - 1 );
		}	
	}

#else

	//	xxx needs to be examined for efficiency...

	int	iWidthMinusOne = iWidth - 1;

	BYTE* pDestTerminator = (BYTE*)pDestStart + iLines * lPitchDest + iWidthMinusOne;	//	Used to determine when we are done.

	__asm
	{
		mov		edx, pDestStart					//	Put destination start address in edx. This register will always point to the 
												//	beginning of the current "line".
		add		edx, iWidthMinusOne				//	Correction - the *end* of the current line.
		mov		esi, pSrcStart					//	Put source address in esi.

		image_loop:

			mov		edi, edx						//	Set edi to end of destination line.

			line_loop:

				xor		ecx, ecx						//	Clear ecx.
				mov		cl, [esi]						//	Put skip count in ecx.
				inc		esi								//	Move source pointer forward.
				sub		edi, ecx						//	Skip over transparent pixels in destination.

				mov		cl, [esi]						//	Put run count in ecx.
				mov		eax, ecx						//	Save run count value in eax.
				inc		esi								//	Move source pointer forward.

				shr		ecx, 2							//	Set ecx to the number of complete quads in run count.

				dword_loop:								//	No way to use rep for destination going backwards, it seems...
					jecxz	end_dword_loop					//	Break out of loop when ecx is zero.
					mov		ebx, [esi]						//	Put next 4 bytes of source into ebx.
					add		esi, 4							//	Advance forwards in source.
					bswap	ebx								//	Reverse order of the bytes.
					sub		edi, 4							//	Advance backwards in destination to start of quad.
					mov		[edi], ebx						//	Write the quad into the destination.
					dec		ecx								//	Decrement quad counter.
				jmp dword_loop
				end_dword_loop:

				and		eax, 0x00000003					//	Get remainder of division of run count by 4.
				mov		ecx, eax						//	Set ecx to number of remaining pixels to copy.
				
				byte_loop:
					jecxz	end_byte_loop					//	Break out of loop when ecx is zero.
					movsb									//	Copy a byte from source to destination.
					dec		edi								//	The movsb moved destination forward,	
					dec		edi								//	and we want it to move backward.   xxx better way?
					dec		ecx								//	Decrement counter.
				jmp		byte_loop
				end_byte_loop:

				cmp		byte ptr [esi], 0xff			//	Is the next byte the end-of-line marker?

			jne		line_loop

			inc		esi								//	Move source pointer forward.
			add		edx, lPitchDest					//	Advance end-of-line pointer to end of next line.
			cmp		edx, pDestTerminator			//	Have we reached the end of the image?

		jne		image_loop
	}

#endif

	return TRUE;
}


/*
** METHOD
**   CSpriteCatalog::RLEFastBltClipped
**
** PARAMETERS
**   void* pDestStart       -- pointer to first destination pixel
**   long lPitchDest        -- pitch of the destination buffer (may be negative)
**   const BYTE *pSrcStart  -- pointer to first byte of RLE data
**   const CRect* rcSrc     -- pointer to source rectangle to copy
**
** DESCRIPTION
**   Copies the rectangle rcSrc from a source bitmap whose upper left hand
**   corner is given by pSrcStart to a position in a destination bitmap 
**   (pDestStart).
** 
**   This method assumes that rcSrc is fully contained in source bitmap and
**   the width and height of rcSrc can be copied to the destination.
**
**   Assumes rcSrc has been normalized.
*/
BOOL CSpriteCatalog::RLEFastBltClipped(	void* pDestStart, long lPitchDest,			
					const BYTE* pSrcStart, const CRect* rcSrc )		
{
	int sh = rcSrc->Height();
	int sy = rcSrc->top;
	int sx = rcSrc->left;
	int xlast = sx + rcSrc->Width() -1;
    int x = 0;

	ASSERT(rcSrc->left <= rcSrc->right);
	ASSERT(rcSrc->top <= rcSrc->bottom);

	BYTE* pDestTerminator = (BYTE*)pDestStart + sh * lPitchDest;	//	Used to determine when we are done.
	const BYTE* pSrc = pSrcStart;
	BYTE* pDest = (BYTE *)pDestStart;
	BYTE* pDestLine = (BYTE *) pDestStart;

	BYTE qSkip;
	BYTE qRun;

	// skip all lines up to sy
	while (sy > 0)
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;
		pSrc	+= qRun;
		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			sy--;
		}
	}

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		while (qSkip-- > 0)
		{
			if (x >= sx && x <= xlast)
				pDest++;
			x++;
		}
        
		//	Copy color pixels...
		while (qRun-- > 0)
		{
			if (x >= sx && x <= xlast)
				*pDest++ = *pSrc; 
			pSrc++;
			x++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			pDestLine += lPitchDest;
			if (pDestLine == pDestTerminator)
				break;
			pDest = pDestLine;
			x = 0;
		}	
	}

	return TRUE;
}

BOOL CSpriteCatalog::RLEFastBltHFlipClipped( void* pDestStart, long lPitchDest, 
											 const BYTE* pSrcStart, long lSrcWidth,
											 const CRect* rcSrc )
{
	int sy = rcSrc->top;
	int sx = rcSrc->left;
	int iWidth = rcSrc->Width();
	int xlast = sx + iWidth-1;
	int lSourceLast = lSrcWidth-1;
    int x = lSourceLast;

	ASSERT(rcSrc->left <= rcSrc->right);
	ASSERT(rcSrc->top <= rcSrc->bottom);

	BYTE*		pDest = (BYTE *)pDestStart + iWidth - 1; // start at the end of the line
	BYTE*		pDestLine = (BYTE *) pDest;
	BYTE* pDestTerminator = (BYTE*)pDest + rcSrc->Height() * lPitchDest;	
	const BYTE*	pSrc = pSrcStart;

	BYTE		qSkip;
	BYTE		qRun;

	// skip all lines up to sy
	while (sy > 0)
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;
		pSrc	+= qRun;
		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			sy--;
		}
	}

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		while (qSkip-- > 0)
		{
			if (x >= sx && x <= xlast)
				pDest--;
			x--;
		}
        
		//	Copy color pixels...
		while (qRun-- > 0)
		{
			if (x >= sx && x <= xlast)
				*pDest-- = *pSrc; 
			pSrc++;
			x--;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			pDestLine += lPitchDest;
			if (pDestLine == pDestTerminator)
				break;
			pDest = pDestLine;
			x = lSourceLast;
		}	
	}

	return TRUE;
}
