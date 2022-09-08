//	CCel.h - Includes definitions for CCel

#ifndef CCEL_H
#define CCEL_H

#include "stdafx.h"

#include "DIBitmap.h"
#include "CSequence.h"

#define GAPFIRSTCOLUMN	5		//	Space between left edge and first column.
#define GAPCOLUMN		5		//	Space between columns.
#define GAPTEXT			3		//	Space between top of row and top of text.
#define	GAPIMAGE		15		//	Space between top of row and top of image.

class CCel : public CObject
{
public:
	CCel();
	CCel( const CString& csFileBMP, CAnimEditorDoc* pDoc );
	virtual ~CCel();	
	DECLARE_SERIAL(CCel)

protected:
	//hotspots?

public:
	CString			csFileBMP;
	CDIBitmap		dibImage;
	BOOL			bSelected;
	BOOL			bDragSelected;
	CTypedPtrList< CObList, CSequence* >	lstSeqs;	//	List of sequences that use this cel.
														//	(Maintained by the sequences themselves, so not serialized).
														//	(Note: not maintained by the sequence cels, but by the CSequence.)
	int				xCrop;								//	Crop position. Not serialized, as it is calc'ed during bmp load.
	int				yCrop;								//	  "

	BOOL			bDIBHotspotSaved;

private:
	void			LoadMyImage( BOOL bCrop, const CString& path, BOOL showerr );
	CString			csFileNamePortion( const CString& csFullFileName );

public:
	virtual void	Serialize( CArchive& ar );
	int				GetWidth()		{ return dibImage.GetWidth(); }
	int				GetHeight()		{ return dibImage.GetHeight(); }
	int				GetImageSize()	{ return dibImage.GetImageSize(); }
	void			Draw( CDC* pDC, int iX, int iY, BOOL bShowSelected, BOOL bShowDragSelected, BOOL bShowAsActionFrame = FALSE );
	BOOL			bPointInMe( const CPoint& ptOrigin, const CPoint& ptHit );
	void			LinkToSequence( BOOL bLink, CSequence* pSeq );
	void			Reload(CString &folder);

	void			CopyCatalogHotspotToSequences();
};

#endif