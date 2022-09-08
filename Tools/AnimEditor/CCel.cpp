//	CCel.cpp

#include "stdafx.h"
#include "CCel.h"
#include "DIBitmap.h"
#include "AnimEditorDoc.h"
#include "AnimEditor.h"

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CCel, CObject, 1)

CCel::CCel()
{
	// Used by Serialize only.
	bSelected		= FALSE;
	bDragSelected	= FALSE;
	bDIBHotspotSaved = TRUE;
}

CCel::CCel( const CString& csFileBMP, CAnimEditorDoc* pDoc ) 
{
	//	Throws a CFileException if image can't be loaded.

	this->csFileBMP = csFileBMP;
//	TRY
//	{
		LoadMyImage( ( (CAnimEditorApp*)AfxGetApp() )->bAutoCrop, pDoc->csFolder, TRUE );
//	}
//	CATCH( CFileException, e )
//	{
//		THROW_LAST();
//	}
//	END_CATCH
	bSelected		= FALSE;
	bDragSelected	= FALSE;
	bDIBHotspotSaved = TRUE;
}

CCel::~CCel()
{
}

//-----------------------------------------------------------------------------------------------------------------
void CCel::Serialize( CArchive& ar )
{
	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)ar.m_pDocument;		//	Set in CAnimEditorDoc::Serialize().
	
	if (ar.IsStoring())
	{
		ar << theApp.docVersion.major;

		/*
		// FIX HERE: remove the pathname
		CString newname;

		CString folder = pDoc->csFolder;
		folder.MakeLower();

		CString name = csFileBMP;
		name.MakeLower();

		int length = name.GetLength();
		LPCTSTR pfolder = (LPCTSTR) folder;
		LPCTSTR pname = (LPCTSTR) name;

		for (int i=0; i<length; i++)	{
			if (pfolder[i] != pname[i])	{
				LPCTSTR pfile = (LPCTSTR) csFileBMP;
				newname = &pfile[i];
				break;
			}
		}

		csFileBMP = newname;
		*/

		ar << csFileBMP;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		ar >> csFileBMP;

//		TRY
//		{
			LoadMyImage( ( (CAnimEditorApp*)AfxGetApp() )->bAutoCrop, pDoc->csFolder, FALSE );
//		}
//		CATCH( CFileException, e )
//		{
//			THROW_LAST();
//		}
//		END_CATCH
	}

}

//-----------------------------------------------------------------------------------------------------------------
void CCel::Reload(CString &folder)
{
	LoadMyImage( ( (CAnimEditorApp*)AfxGetApp() )->bAutoCrop, folder, FALSE );
}

//-----------------------------------------------------------------------------------------------------------------
CString CCel::csFileNamePortion( const CString& csFullFileName )
{
	//	Returns the file name (no extension) from a full path.

	CString csReturn = csFullFileName;

	//	Find last slash.
	int	iSlashPos = csFullFileName.ReverseFind( '\\' );
	if( iSlashPos != -1 )
	{
		int iDotPos = csFullFileName.ReverseFind( '.' );
		if( iDotPos == -1 )
			iDotPos = csFullFileName.GetLength() - 1;
		int iNameLen = iDotPos - iSlashPos - 1;
		ASSERT( iNameLen > 0 );
		csReturn = csFullFileName.Mid( iSlashPos + 1, iNameLen );
	}
	return csReturn;
}

//-----------------------------------------------------------------------------------------------------------------
void CCel::Draw( CDC* pDC, int iX, int iY, BOOL bShowSelected, BOOL bShowDragSelected, BOOL bShowAsActionFrame /*= FALSE*/ )
{
	//	iX, iY is the top corner of the area where text and image are drawn.
	CRect rcBounds( iX, iY + GAPTEXT, iX + GetWidth(), iY + GAPIMAGE + GetHeight() );
	rcBounds.InflateRect( 3, 3 );

	if( bShowAsActionFrame )
	{
		CRect rcBoundsAction = rcBounds;
		rcBoundsAction.InflateRect( 2, 2 );
		CBrush brush;
		brush.CreateSolidBrush( RGB( 255, 0, 0 ) );
		pDC->FillRect( &rcBoundsAction, &brush );
	}

	if( bShowSelected )
	{
		CBrush brush;
		brush.CreateSolidBrush( RGB( 0, 255, 255 ) );
		pDC->FillRect( &rcBounds, &brush );
	}

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextAlign( TA_RIGHT );
	CRect rcTextBounds( iX, iY + GAPTEXT, iX + GetWidth(), iY + GAPIMAGE );
	pDC->ExtTextOut( iX + GetWidth(), iY + GAPTEXT, ETO_CLIPPED, rcTextBounds, csFileNamePortion( csFileBMP ), NULL );
	dibImage.Draw( pDC, CPoint( iX, iY + GAPIMAGE ) );
	
	if( bShowSelected )
	{
		pDC->DrawEdge( &rcBounds, EDGE_SUNKEN, BF_RECT );
	}
	if( bShowDragSelected )
	{
		rcBounds.InflateRect( 1, 1 );
		pDC->DrawEdge( &rcBounds, EDGE_BUMP, BF_RECT );
	}
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CCel::bPointInMe( const CPoint& ptOrigin, const CPoint& ptHit )
{
	//	Returns TRUE if the ptHit point specified is in my Draw() area, given that I draw at ptOrigin.
	CRect rcBounds( ptOrigin.x, ptOrigin.y + GAPTEXT, ptOrigin.x + GetWidth(), ptOrigin.y + GAPIMAGE + GetHeight() );
	return rcBounds.PtInRect( ptHit );
	//	xxx Warning: not exact because of CRect definition of rectangles.
}

//-----------------------------------------------------------------------------------------------------------------
void CCel::LoadMyImage( BOOL bCrop, const CString& path, BOOL showerr )
{
	//	Cel loads the BMP file already assigned to it.
	//	It then crops itself, if bCrop.
	//	Get a DC to use when creating dibs.
	POSITION posFirstDocTemplate	= AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate* pFirstDocTemplate = AfxGetApp()->GetNextDocTemplate( posFirstDocTemplate );
	POSITION posFirstDoc			= pFirstDocTemplate->GetFirstDocPosition();
	CDocument* pFirstDoc			= pFirstDocTemplate->GetNextDoc( posFirstDoc );
	POSITION posFirstView			= pFirstDoc->GetFirstViewPosition();
	CView* pFirstView				= pFirstDoc->GetNextView( posFirstView );

	CClientDC* pDC = new CClientDC( pFirstView );

	if( !dibImage.Create( pDC, csFileBMP, path, TRUE ) )
	{
		if (showerr)	{
			CString csMess;
			csMess.Format( "%s%s could not be read!", path, csFileBMP );
			AfxMessageBox( csMess );
//			AfxThrowFileException( CFileException::generic );
		}
	}
	else	{
		xCrop = 0;
		yCrop = 0;
		if( bCrop )
		{
			CPoint ptCrop = dibImage.Crop( pDC );
			if( ptCrop.x != -1 || ptCrop.y != -1 )
			{
				//	Crop took place.
				xCrop = ptCrop.x;
				yCrop = ptCrop.y;
			}
		}
		bDIBHotspotSaved = TRUE;
	}

	delete pDC;
}

//-----------------------------------------------------------------------------------------------------------------
void CCel::LinkToSequence( BOOL bLink, CSequence* pSeq )
{
	//	Links or unlinks cel to a CSequence. Maintained by the sequences.
	//	[ A sequence may be linked several times (each sequence cel creates a link). ]
	if( bLink )
		lstSeqs.AddTail( pSeq );
	else
	{
		POSITION posInList;
		VERIFY( posInList = lstSeqs.Find( pSeq ) );	//	(Actually gets the first occurrence, which is okay.)
		lstSeqs.RemoveAt( posInList );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCel::CopyCatalogHotspotToSequences()
{
	//	Copies the hotspot in my dibImage to all sequencecel instances of me.
	POSITION posSeq = lstSeqs.GetHeadPosition();
	CSequence* pSeq;
	while( posSeq )
	{
		pSeq = lstSeqs.GetNext( posSeq );
		pSeq->SetHotspotForCelInstances( this, dibImage.GetHotspotX(), dibImage.GetHotspotY() );
	}
}
