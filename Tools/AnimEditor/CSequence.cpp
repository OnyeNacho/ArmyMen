//	CSequence.cpp

#include "stdafx.h"
#include "CSequence.h"
#include "CCel.h"
#include "AnimEditorDoc.h"
#include "CMultipleSequencesView.h"
#include "AnimEditor.h"
#include <strstrea.h>
#include "CCelView.h"
#include "CNewHotSpotDialog.h"


IMPLEMENT_SERIAL(CHSpot, CObject, 1)


//-----------------------------------------------------------------------------------------------------------------
//	CHSpot implementation.
//-----------------------------------------------------------------------------------------------------------------
CHSpot::CHSpot()
{
	// Used by Serialize only.
}

CHSpot::CHSpot( BOOL bPrimary, const CString& csName )
{
	this->bPrimary	= bPrimary;
	this->csName	= csName;
}

CHSpot::~CHSpot()
{
}

void CHSpot::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{
		ar << theApp.docVersion.major;
		ar << bPrimary << csName;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		ar >> bPrimary >> csName;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSequence, CObject, 1)

CSequence::CSequence()
{
	// Used by Serialize only.
	pSeqView		= NULL;
}

CSequence::CSequence( CAnimEditorDoc* pDoc ) 
{
	pSeqView	= NULL;
	pOwnerDoc	= pDoc;
	csName		= "Unnamed sequence";
	iSpeed		= 15;	//	SEQUENCE_SPEEDMIN;
	iMoveSpeed	= 15;
	iDirection	= 0;
	CHSpot* pHSpot = new CHSpot( TRUE, CString( "Primary" ) );
	lstHSpots.AddTail( pHSpot );

	CreateLinkedSequenceView();

	//	Set lAction to first action in actions list. (There had better be one...)
	POSITION posFirst = theApp.lstActions.GetHeadPosition();
	ASSERT( posFirst );
	CActionRecord* parAction = theApp.lstActions.GetAt( posFirst );
	lAction = parAction->lKey;

	csBackgroundBMP	= NO_BACKGROUND;
	pdibBackground	= NULL;
}

CSequence::~CSequence()
{
	//	Delete constructed sequence cels.
	POSITION posInList;
	CSequenceCel*	pSeqCel;
	while( posInList = lstSeqCels.GetHeadPosition() )
	{
		pSeqCel = lstSeqCels.GetAt( posInList );
		//	Remove the associated cel's link to myself.
		pSeqCel->pCel->LinkToSequence( FALSE, this );
		delete pSeqCel;		//	Note: does not inherently remove links pCel has to this sequence.
		lstSeqCels.RemoveAt( posInList );
	}
	//	Delete constructed hotspots.
	CHSpot*	pHSpot;
	while( posInList = lstHSpots.GetHeadPosition() )
	{
		pHSpot = lstHSpots.GetAt( posInList );
		delete pHSpot;
		lstHSpots.RemoveAt( posInList );
	}
	if( pdibBackground )
		delete pdibBackground;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::CreateLinkedSequenceView()
{
	//	[ pOwnerDoc has been set. ]
	//	Tell the CMultipleSequencesView to create a new CSequenceView for the new sequence.
	POSITION posView = pOwnerDoc->GetFirstViewPosition();
	CView* pView;
	while( posView != NULL )
	{
		pView = pOwnerDoc->GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CMultipleSequencesView" ) == 0 )
		{
			pSeqView = ( (CMultipleSequencesView*)pView )->AddNewSequence( this );
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{
		ar << theApp.docVersion.major;
		ar << csName << iSpeed << iMoveSpeed << lAction << iDirection << csBackgroundBMP;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		pOwnerDoc = (CAnimEditorDoc*)ar.m_pDocument;		//	Set in CAnimEditorDoc::Serialize().
		ar >> csName >> iSpeed >> iMoveSpeed >> lAction >> iDirection >> csBackgroundBMP;

		if( csBackgroundBMP == "" )
			csBackgroundBMP = NO_BACKGROUND;
		pdibBackground = NULL;
		if( !LoadBackgroundBMP( csBackgroundBMP ) )
		{
			csBackgroundBMP = NO_BACKGROUND;
			pOwnerDoc->DocModified();
		}
	}
	
	lstSeqCels.Serialize( ar );
	lstHSpots.Serialize( ar );

	//	Link the cels used by my sequence cels to myself.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		pSeqCel->pCel->LinkToSequence( TRUE, this );
	}

	if( !ar.IsStoring() )
		CreateLinkedSequenceView();

}

//-----------------------------------------------------------------------------------------------------------------
int CSequence::iCountSelected()
{
	//	Returns number of cels selected.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	int iCount = 0;
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( pSeqCel->bSelected )
			iCount++;
	}
	return iCount;
}

//-----------------------------------------------------------------------------------------------------------------
POSITION CSequence::PosFirstSelectedSeqCel()
{
	//	Returns POSITION of first sequence cel selected in lstSeqCels, or NULL.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	POSITION posNow;
	CSequenceCel* pSeqCel;
	while( posNow = posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( pSeqCel->bSelected )
			return posNow;
	}
	return NULL;
}

//-----------------------------------------------------------------------------------------------------------------
int CSequence::iFirstSelectedSeqCel()
{
	//	Returns order number of first sequence cel selected in lstSeqCels, or -1 for none selected.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	int	iCount = -1;
	while( posInList )
	{
		iCount++;
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( pSeqCel->bSelected )
			return iCount;
	}
	return -1;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::SequenceCelSelect( POSITION posCel, UINT nFlags )
{
	//	[ Much duplicated from CAnimEditorDoc::CelSelect ]
	//	The view has told us that the sequence cel at posCel in our list has been selected.
	//	nFlags holds the mouse state when button was pressed.
	
	//xxx just do regular and ctrl-clicks for now

	CSequenceCel* pSeqCelSubject = lstSeqCels.GetAt( posCel );

	if( nFlags & MK_CONTROL )
	{
		//	Ctrl-click. If cel is already selected, unselect. Otherwise select.
		pSeqCelSubject->bSelected = !pSeqCelSubject->bSelected;
	}
	else	//	No ctrl- or shift-click.
	{
		//	Clear all selected sequence cels. Select pSeqCelSubject.
		SequenceCelSelectOnly( pSeqCelSubject );
	}

	if( pSeqView->GetCelView()->pSequence == this && pSeqCelSubject->bSelected )
		pSeqView->GetCelView()->LinkImage( pSeqCelSubject );

}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::SequenceCelSelectOnly( CSequenceCel* pSeqCelSelect )
{
	//	Clears selectedness for all sequence cels except pSeqCelSelect (can be NULL).
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		pSeqCel->bSelected = ( pSeqCelSelect == pSeqCel );
	}
//		lstCelSelect.RemoveAll();					xxx could be used perhaps
//		lstCelSelect.AddTail( pCelSubject );
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequence::DeleteSelected( BOOL bDragSelected )
{
	BOOL bDeleteOccurred = FALSE;
	//	If bDragSelected, deletes all bDragSelected sequence cels, else all bSelected sequence cels.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	POSITION posNow;
	CSequenceCel* pSeqCel;
	BOOL bFound = FALSE;
	while( posNow = posInList )
	{
		bDeleteOccurred = TRUE;
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( ( bDragSelected && pSeqCel->bDragSelected ) || ( !bDragSelected && pSeqCel->bSelected ) )
		{
			//	Remove the associated cel's link to myself.
			pSeqCel->pCel->LinkToSequence( FALSE, this );
			delete pSeqCel;			//	Note: does not inherently remove links pCel has to this sequence.
			lstSeqCels.RemoveAt( posNow );
			bFound = TRUE;
		}
	}
	if( bFound )
	{
		pSeqView->CalcSizeChanges();
		ForceMultipleSequencesViewArrange();
		if( pSeqView->GetCelView()->pSequence = this )
		{
			//	Update size vars in CelView.
			pSeqView->GetCelView()->CalcSizeChanges();
			//	Clear image in CelView.
			pSeqView->GetCelView()->LinkImage( NULL );
		}
	}
	return bDeleteOccurred;
}
								
//-----------------------------------------------------------------------------------------------------------------
void CSequence::ForceMultipleSequencesViewArrange()
{
	//	Tell the CMultipleSequencesView to rearrange itself.
	POSITION posView = pOwnerDoc->GetFirstViewPosition();
	CView* pView;
	while( posView != NULL )
	{
		pView = pOwnerDoc->GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CMultipleSequencesView" ) == 0 )
		{
			( (CMultipleSequencesView*)pView )->Arrange();
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::PutDataOnClipboard( COleDataSource* pData )
{
	//	Called for CSequence Copy, Cut, and begin drag.
	ASSERT( iCountSelected() > 0 );

	//	Get handle to a piece of memory.
	HGLOBAL hData = ::GlobalAlloc( GMEM_MOVEABLE, theApp.iSizeClipFormatSequenceCelBlock );
	//	Lock and get a pointer to the bytes.
	LPVOID pMem = ::GlobalLock( hData );
	//	Set up an ostrstream object that will let me conveniently write to memory.
	ostrstream* pStream = new ostrstream( (char*)pMem, theApp.iSizeClipFormatSequenceCelBlock );
	//	Write data out...
	//	1. Number of items.
	*pStream << iCountSelected() << ' ';			//	xxx ' ' due to writing of numbers as strings.... xxx
	//	2. Each item. ( Write out backwards, as order is reversed on insertion. )
	POSITION posInList = lstSeqCels.GetTailPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetPrev( posInList );
		if( pSeqCel->bSelected )
		{
			//	Length of string.
			int iLen = pSeqCel->pCel->csFileBMP.GetLength();
			*pStream << iLen << ' ';
			//	Contents of string.
			pStream->write( pSeqCel->pCel->csFileBMP, iLen );
			//old
			////	Primary hot spot location.
			//CPoint ptPrimary = pSeqCel->ptPrimaryHotSpot();
			//*pStream << ptPrimary.x << ' ';
			//*pStream << ptPrimary.y << ' ';
			//	Write number of hotspots.
			iLen = lstHSpots.GetCount();
			*pStream << iLen << ' ';
			//	Write each hotspot.
			POSITION posSpot = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pSpotLoc;
			while( posSpot )
			{
				pSpotLoc = pSeqCel->lstHSpotLocs.GetNext( posSpot );
				*pStream << pSpotLoc->x << ' ';
				*pStream << pSpotLoc->y << ' ';
			}
		}
	}
	//	Finished writing to memory.
	delete pStream;
	::GlobalUnlock( hData );

	pData->CacheGlobalData( theApp.clipFormatSequenceCel, hData );

	pData->SetClipboard();

	//	xxx to do: limit number of selections placed on clipboard based on memory space
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::GetDataFromClipboard()
{
	//	Called upon paste (see CSequenceView::OnEditPaste() ).
	//	Creates new sequence cels (and possibly cels) and adds them to lstSeqCels.

	COleDataObject	dataObj;
	CSequenceCel*	pSeqCel;
	POSITION		posInsert = PosFirstSelectedSeqCel();	//	May be null because: 1) empty, or 2) none selected.

	BOOL			bUsingFormatSequenceCel = FALSE;

	dataObj.AttachClipboard();

	if( dataObj.IsDataAvailable( theApp.clipFormatCel ) || dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) )
	{
		HGLOBAL		hData;
		LPVOID		pMem;
		istrstream*	pStream;
		if( dataObj.IsDataAvailable( theApp.clipFormatCel ) )
		{
			hData = dataObj.GetGlobalData( theApp.clipFormatCel );
			//	Lock and get a pointer to the bytes.
			pMem = ::GlobalLock( hData );
			//	Set up an istrstream object that will let me conveniently read from memory.
			pStream = new istrstream( (char*)pMem, theApp.iSizeClipFormatCelBlock );
		}
		else
		{
			hData = dataObj.GetGlobalData( theApp.clipFormatSequenceCel );
			//	Lock and get a pointer to the bytes.
			pMem = ::GlobalLock( hData );
			//	Set up an istrstream object that will let me conveniently read from memory.
			pStream = new istrstream( (char*)pMem, theApp.iSizeClipFormatSequenceCelBlock );
			bUsingFormatSequenceCel = TRUE;
		}
		//	Read data in...
		//	1. Number of items.
		int iCount;
		int	iLen;
		*pStream >> iCount >> ws;		//	ws "eats white space" xxx  a way must exist that doesn't use stringstreams like these
		//	2. Each item.
		CString csFile;
		for( int i = 0; i < iCount; i++ )
		{
			//	Create sequence cel.
			pSeqCel = new CSequenceCel;
			//	Length of string.
			*pStream >> iLen >> ws;
			char* pChar = new char[ iLen ];
			//	Contents of string.
			pStream->read( pChar, iLen );
			CString csFileBMP( pChar, iLen );
			delete pChar;
			pSeqCel->LinkToCelByFileName( pOwnerDoc, csFileBMP );
			if( !pSeqCel->pCel )
			{
				//	Cel with this file name not in catalog. Create one there.
				CCel* pCelNew = new CCel( csFileBMP, pOwnerDoc );
				pOwnerDoc->lstCels_Insert( pCelNew );
				pOwnerDoc->DocModified();
				//	Link sequence cel to new cel.
				pSeqCel->pCel = pCelNew;
			}
			pSeqCel->pCel->LinkToSequence( TRUE, this );
			pSeqCel->CreateHSpotLocs( this );
			if( bUsingFormatSequenceCel )
			{
				//old
				////	Set the primary hotspot data.
				//int iX, iY;
				//*pStream >> iX >> ws;
				//*pStream >> iY >> ws;
				//pSeqCel->SetPrimaryHotSpot( CPoint( iX, iY ) );

				//	Get number of hotspots.
				int iNumSpots;
				*pStream >> iNumSpots >> ws;
				//	Loop through, reading in spots.
				//	If we go past the number of hotspots in the current sequence, ignore copied values.
				//	We will warn the user if this happens, below.
				int iX, iY;
				for( int iSpot = 0; iSpot < iNumSpots; iSpot++ )
				{
					*pStream >> iX >> ws;
					*pStream >> iY >> ws;
					if( iSpot < lstHSpots.GetCount() )
					{
						//	Set the iSpot'th CHSpotLoc for the new CSequenceCel.
						POSITION posFound = pSeqCel->lstHSpotLocs.FindIndex( iSpot );
						ASSERT( posFound );
						CHSpotLoc* pSpot = pSeqCel->lstHSpotLocs.GetAt( posFound );
						pSpot->x = iX;
						pSpot->y = iY;
					}
				}
				if( iNumSpots > lstHSpots.GetCount() )
					AfxMessageBox( "Warning! Not all hotspots in cel were copied, as the original cel's sequence has more hotspots than this sequence." );
			}
			else	
			{		
				// NAR
				int iX, iY;

				iX = pSeqCel->pCel->dibImage.GetHotspotX();
				iY = pSeqCel->pCel->dibImage.GetHotspotY();

				pSeqCel->SetPrimaryHotSpot( CPoint( iX, iY ) );
			}

			if( posInsert == NULL )
				posInsert = lstSeqCels.AddTail( pSeqCel );
			else
				posInsert = lstSeqCels.InsertBefore( posInsert, pSeqCel );
		}

		//	Finished reading from memory.
		delete pStream;
		::GlobalUnlock( hData );
		
		pOwnerDoc->SetModifiedFlag();
		
		if( pSeqView->GetCelView()->pSequence = this )
		{
			//	Update size vars in CelView.
			pSeqView->GetCelView()->CalcSizeChanges();
			//	Clear image in CelView.
			pSeqView->GetCelView()->LinkImage( NULL );
		}
	}
	else
		ASSERT( FALSE );	//	Menu choice should have been disabled if neither of these formats.

	SequenceCelSelectOnly( NULL );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::DeleteSequenceCelMatchingCel( CCel* pCel )
{
	//	Deletes the *first* sequence cel associated with pCel.
	
	if( pSeqView->GetCelView()->pSequence = this )
	{
		//	Clear image in CelView.
		pSeqView->GetCelView()->LinkImage( NULL );
	}

	POSITION posInList = lstSeqCels.GetHeadPosition();
	POSITION posNow;
	CSequenceCel* pSeqCel;
	while( posNow = posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( pSeqCel->pCel == pCel )
		{
			delete pSeqCel;		//	Note: does not inherently remove links pCel has to this sequence.
			lstSeqCels.RemoveAt( posNow );
			pSeqView->CalcSizeChanges();
			ForceMultipleSequencesViewArrange();
			return;
		}
	}
	ASSERT( FALSE );	//	should have found one or why was this called
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::ConvertSelectedToDragSelected()
{
	//	Sets all selected cels to dragselected and unselects them.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		if( pSeqCel->bSelected )
		{
			pSeqCel->bDragSelected	= TRUE;
			pSeqCel->bSelected		= FALSE;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::ClearDragSelected()
{
	//	Clears all dragselected cel states.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		pSeqCel->bDragSelected = FALSE;
	}
}

//-----------------------------------------------------------------------------------------------------------------
CSize CSequence::ImageBoundsMax()
{
	//	For CCelView. Returns largest width and height of sequence cel bitmaps (and uses half-size of background BMP, if set).
	int iWidthMax	= 0;
	int iHeightMax	= 0;
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		iWidthMax	= max( iWidthMax, pSeqCel->pCel->dibImage.GetWidth() );
		iHeightMax	= max( iHeightMax, pSeqCel->pCel->dibImage.GetHeight() );
	}
	if( pdibBackground )
	{
		iWidthMax	= max( iWidthMax, pdibBackground->GetWidth() / 2 );
		iHeightMax	= max( iHeightMax, pdibBackground->GetHeight() / 2 );
	}
	return CSize( iWidthMax, iHeightMax );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::AddHSpot()
{
	CNewHotSpotDialog* pDialog = new CNewHotSpotDialog( pSeqView );

	pDialog->csSequenceName = "Sequence: " + csName;

	if( pDialog->DoModal() == IDOK )
	{
		CNewHotSpotDialog::csNameLast = pDialog->csHSpotName;	//	Save last used name.
		CHSpot* pHSpot = new CHSpot( FALSE, pDialog->csHSpotName );
		lstHSpots.AddTail( pHSpot );
		//	Create associated CHSpotLocs.
		POSITION posInList = lstSeqCels.GetHeadPosition();
		CSequenceCel* pSeqCel;
		while( posInList )
		{
			pSeqCel = lstSeqCels.GetNext( posInList );
			CHSpotLoc* pHSpotLoc = new CHSpotLoc( pSeqCel->pCel );
			pSeqCel->lstHSpotLocs.AddTail( pHSpotLoc );
		}
		if( pSeqView->GetCelView()->pSequence == this )
			pSeqView->GetCelView()->UpdateData( FALSE );
		pOwnerDoc->SetModifiedFlag();
	}

	delete pDialog;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::DeleteHSpot( int iDel )
{
	//	Delete hspot at #iDel in list and all hspotlocs associated with it...

	//	Delete associated CHSpotLocs.
	POSITION posInList = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posInList )
	{
		pSeqCel = lstSeqCels.GetNext( posInList );
		pSeqCel->DeleteHSpotLoc( iDel );
	}

	posInList = lstHSpots.FindIndex( iDel );
	ASSERT( posInList );
	CHSpot* pHSpot = lstHSpots.GetAt( posInList );
	ASSERT( pHSpot );
	lstHSpots.RemoveAt( posInList );
	delete pHSpot;
		
	if( pSeqView->GetCelView()->pSequence == this )
		pSeqView->GetCelView()->UpdateData( FALSE );
	pOwnerDoc->SetModifiedFlag();
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::SetBackgroundBMP( const CString& csFileBMP )
{
	if( LoadBackgroundBMP( csFileBMP ) )
		csBackgroundBMP = csFileBMP;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequence::LoadBackgroundBMP( const CString& csFileBMP )
{
	//	Doesn't set csBackgroundBMP. Sets pdibBackground.
	if( csFileBMP == NO_BACKGROUND )
	{
		if( pdibBackground )
		{
			delete pdibBackground;
			pdibBackground = NULL;
		}
		if( pSeqView )
		{
			POSITION posView = pOwnerDoc->GetFirstViewPosition();
			while( posView )
			{
				CView* pView = pOwnerDoc->GetNextView( posView );
				if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
					((CCelView*)pView)->CalcSizeChanges();
			}
		}
		return TRUE;
	}

	CDIBitmap* pdibNew = new CDIBitmap;

	POSITION posFirstDocTemplate	= AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate* pFirstDocTemplate = AfxGetApp()->GetNextDocTemplate( posFirstDocTemplate );
	POSITION posFirstDoc			= pFirstDocTemplate->GetFirstDocPosition();
	CDocument* pFirstDoc			= pFirstDocTemplate->GetNextDoc( posFirstDoc );
	POSITION posFirstView			= pFirstDoc->GetFirstViewPosition();
	CView* pFirstView				= pFirstDoc->GetNextView( posFirstView );
	CClientDC dc( pFirstView );

	if( !pdibNew->Create( &dc, csFileBMP, "", TRUE ) )
	{
		CString csError;
		csError.Format( "Unable to load background BMP: %s.", csFileBMP );
		AfxMessageBox( csError );
		delete pdibNew;
		//	( pdibBackground is left unchanged. )
		return FALSE;
	}

	pdibBackground = pdibNew;

	if( pSeqView )
	{
		POSITION posView = pOwnerDoc->GetFirstViewPosition();
		while( posView )
		{
			CView* pView = pOwnerDoc->GetNextView( posView );
			if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
				((CCelView*)pView)->CalcSizeChanges();
		}
	}

	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequence::SetHotspotForCelInstances( CCel* pCelToMatch, int iX, int iY )
{
	//	Set primary hotspot for all SeqCels within me that point to pCel.
	POSITION posSeqCel = lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posSeqCel )
	{
		pSeqCel = lstSeqCels.GetNext( posSeqCel );
		if( pSeqCel->pCel == pCelToMatch )
			pSeqCel->SetPrimaryHotSpot( CPoint( iX, iY ) );
	}
}
