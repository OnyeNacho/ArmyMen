// AnimEditorDoc.cpp : implementation of the CAnimEditorDoc class
//

#include "stdafx.h"

#include "AnimEditor.h"
#include "AnimEditorDoc.h"

#include <strstrea.h>
#include <shlobj.h>

#include "CCel.h"
#include "CMultipleSequencesView.h"
#include "CSpriteCatalog.h"

#include "CSequenceView.h"
#include "AnimEditorView.h"
#include "CCelView.h"

#include "cderr.h"	//	for CommDlgExtendedError()

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorDoc

IMPLEMENT_DYNCREATE(CAnimEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CAnimEditorDoc)
	ON_COMMAND(ID_CATALOG_ADDBMP, OnCatalogAddbmp)
	ON_UPDATE_COMMAND_UI(ID_CATALOG_ADDBMP, OnUpdateCatalogAddbmp)
	ON_COMMAND(ID_SEQUENCE_NEW, OnSequenceNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_FILE_EXPORT_RLE, OnFileExportRle)
	ON_COMMAND(ID_CATALOG_BROWSE, OnCatalogBrowse)
	ON_COMMAND(ID_CATALOG_BROWSE_ALL, OnCatalogBrowseAll)
	ON_COMMAND(ID_SEQUENCE_DELETE, OnSequenceDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorDoc construction/destruction

//-----------------------------------------------------------------------------------------------------------------
CAnimEditorDoc::CAnimEditorDoc()
{
	csFileExport	= "";
	csFileExportRLE	= "";
	csFolder		= "";
    if (SHGetMalloc(&m_pMalloc) != NOERROR)
	{
		;	// should disable the menu item?
	}
}

//-----------------------------------------------------------------------------------------------------------------
CAnimEditorDoc::~CAnimEditorDoc()
{
	POSITION		posInList;
	//	Delete constructed cel sequences.
	CSequence*	pSeq;
	while( posInList = lstSeqs.GetHeadPosition() )
	{
		pSeq = lstSeqs.GetAt( posInList );
		delete pSeq;
		lstSeqs.RemoveAt( posInList );
	}		
	//	Delete constructed cels.
	CCel*		pCel;
	while( posInList = lstCels.GetHeadPosition() )
	{
		pCel = lstCels.GetAt( posInList );
		delete pCel;
		lstCels.RemoveAt( posInList );
	}		
	CDIBitmap::CleanupPalette();	//	Delete palette, static in CDIBitmap.

}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::OnNewDocument()
{
	//	BrowseForFolder(csFolder);	ajw replaced with following...
	//	Get last image folder from registry.
	csFolder = theApp.GetProfileString( "User Prefs", "Image Folder", "" );
	if( csFolder == "" )
		if( BrowseForFolder( csFolder ) )
			SetModifiedFlag( TRUE );

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	// use the csFolder to look for a palette
	SetupPalette();

	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

//	SetupPalette();		// called from serialize instead

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorDoc serialization

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::Serialize(CArchive& ar)
{
	ar.m_pDocument = this;		//	Used when member objects are created during serialize INs.

	if( ar.IsStoring() )
	{
		ar << theApp.docVersion.major;
		ar << csName << csFileExport << csFileExportRLE;
		ar << csFolder;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		ar >> csName >> csFileExport >> csFileExportRLE;
		ar >> csFolder;
		csFolder.MakeUpper();
	}

	SetupPalette();

	lstCels.Serialize( ar );

	lstSeqs.Serialize( ar );

	CheckForLoad();
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::Reload(CString &folder)
{
	POSITION posInList = lstCels.GetHeadPosition();
	while( posInList )
	{
		CCel* pCel = lstCels.GetNext( posInList );
		pCel->Reload(folder);
	}

	ResizeViews();

	CheckForLoad();
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::CheckForLoad()
{
	POSITION posInList = lstCels.GetHeadPosition();
	while( posInList )
	{
		CCel* pCel = lstCels.GetNext( posInList );
		if (pCel->GetImageSize() == 0)	{
			CString csMess;
			csMess.Format( "%s%s could not be read!", csFolder, pCel->csFileBMP );
			AfxMessageBox( csMess );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorDoc diagnostics

#ifdef _DEBUG
void CAnimEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnimEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorDoc commands

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnCatalogAddbmp() 
{
	CString csFileExt		= "BMP";
	CString csFileFilter	= "Bitmap Files (*.bmp)|*.bmp||";
	CFileDialog	dlg( TRUE, csFileExt, NULL, OFN_EXPLORER | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, csFileFilter );
	//	Create buffer for CFileDialog multiple file name storage.
	char chBuf[ 30000 ];
	dlg.m_ofn.lpstrFile	= chBuf;
	dlg.m_ofn.nMaxFile	= 30000;
	::ZeroMemory( chBuf, 30000 );		//	xxx There is still a 256 character cutoff bug here - may be within Windows.
	dlg.m_ofn.lpstrInitialDir = (LPCSTR) csFolder;

	int iRetVal = dlg.DoModal();
	if( iRetVal == 0 )
	{
		switch( ::CommDlgExtendedError() )
		{
		case FNERR_BUFFERTOOSMALL:
			AfxMessageBox( "Dialog error: FNERR_BUFFERTOOSMALL" );
		case FNERR_INVALIDFILENAME:
			AfxMessageBox( "Dialog error: FNERR_INVALIDFILENAME" );
		case FNERR_SUBCLASSFAILURE:
			AfxMessageBox( "Dialog error: FNERR_SUBCLASSFAILURE" );
		}
	}
	else if( iRetVal == IDOK )
	{
		BeginWaitCursor();
		BOOL bDocChanged = FALSE;

		POSITION posInFileList = dlg.GetStartPosition();
		while( posInFileList )
		{
			CString csFilePathName	= dlg.GetNextPathName( posInFileList );
			csFilePathName.MakeUpper();

			CString csFileBMP;

			// get just the non-base path part of the name
			int index = csFilePathName.Find(csFolder);
			if (index != 0)	{
				TRACE("Didn't find path in name\n");
			}
			else	{
				int length = csFolder.GetLength();
				csFileBMP = csFilePathName.Mid( length );
			}

			//	Verify that BMP is not already present in catalog.
			POSITION	posInList;
			CCel*		pCel;
			BOOL		bFound = FALSE;
			posInList = lstCels.GetHeadPosition();
			while( posInList )
			{
				pCel = lstCels.GetNext( posInList );
				if( csFileBMP.CompareNoCase( pCel->csFileBMP ) == 0 )
				{
					bFound = TRUE;
					break;
				}
			}
			if( bFound )
				continue;
			else
			{
				//	Read in BMP and add to catalog.
				TRY
				{
					pCel = new CCel( csFileBMP, this );
				}
				CATCH( CFileException, e )
				{
					continue;
				}
				END_CATCH
				lstCels_Insert( pCel );
				bDocChanged = TRUE;
			}
		}
		if( bDocChanged )
		{
			DocModified();
		}
		EndWaitCursor();
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnUpdateCatalogAddbmp(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable( TRUE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable( TRUE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnFileExport() 
{
	Export( FALSE, FALSE );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnFileExportRle() 
{
	Export( TRUE, FALSE );	
}

//-----------------------------------------------------------------------------------------------------------------
//void CAnimEditorDoc::CreateCelView()
//{
//	//	Private. Creates CelView frame using template set up in app InitInstance().
//
//	CDocTemplate*	pDocTemplate	= ( (CAnimEditorApp*)AfxGetApp() )->pCelViewTemplate;
//	CFrameWnd*		pFrame			= pDocTemplate->CreateNewFrame( this, NULL );
//	ASSERT(	pFrame );
//	CWnd*			pWndActive		= pFrame->GetWindow( GW_CHILD );
//	ASSERT( pWndActive );
//	CCelView*		pViewNew		= static_cast<CCelView*>( pWndActive );
//	pDocTemplate->InitialUpdateFrame( pFrame, this ); 
//}

//-----------------------------------------------------------------------------------------------------------------
CCel* CAnimEditorDoc::GetCelPtrByFileName( const CString& csFile )
{
	//	Return a pointer to the cel in the catalog with file name csFile, or NULL.
	POSITION	posInList;
	CCel*		pCel;
	posInList = lstCels.GetHeadPosition();
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( pCel->csFileBMP.CompareNoCase( csFile ) == 0 )
			return pCel;
	}
	return NULL;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::lstCels_Insert( CCel* pCelToInsert )
{
	//	Inserts pCel into lstCels at the appropriate location, alphabetically by filename.
	POSITION	posNext = lstCels.GetHeadPosition();
	POSITION	posNow;
	POSITION	posPrev = NULL;
	CCel*		pCel;
	while( posNow = posNext )
	{
		pCel = lstCels.GetNext( posNext );
		if( pCel->csFileBMP > pCelToInsert->csFileBMP )
			break;
		posPrev = posNow;
	}
	if( posPrev == NULL )
		lstCels.InsertBefore( lstCels.GetHeadPosition(), pCelToInsert );
	else
		lstCels.InsertAfter( posPrev, pCelToInsert );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::DocModified()
{
	//	Called when doc has been modified, and CAnimEditorView needs to be redrawn.
	//	(Otherwise, a call to SetModifiedFlag() is sufficient.)
	SetModifiedFlag();
	//	Post a resize window message to the AnimEditorView, so that it will figure out its scroll bars anew.
	POSITION posView = GetFirstViewPosition();
	CView* pView;
	while( posView != NULL )
	{
		pView = GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CAnimEditorView" ) == 0 )
		{
			pView->PostMessage( WM_SIZE );
			pView->InvalidateRect( NULL );
			break;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::CelSelect( POSITION posCel, UINT nFlags )
{
	//	The view has told us that the cel at posCel in our list has been selected.
	//	nFlags holds the mouse state when button was pressed.
	
	//xxx just do regular and ctrl-clicks for now

	CCel* pCelSubject = lstCels.GetAt( posCel );

	if( nFlags & MK_CONTROL )
	{
		//	Ctrl-click. If cel is already selected, unselect. Otherwise select.
		pCelSubject->bSelected = !pCelSubject->bSelected;
	}
	else	//	No ctrl- or shift-click.
	{
		//	Clear all selected cels. Select pCelSubject.
		POSITION posInList = lstCels.GetHeadPosition();
		CCel* pCel;
		while( posInList )
		{
			pCel = lstCels.GetNext( posInList );
			pCel->bSelected = ( pCelSubject == pCel );
		}
//		lstCelSelect.RemoveAll();					xxx could be used perhaps
//		lstCelSelect.AddTail( pCelSubject );
	}
}

//-----------------------------------------------------------------------------------------------------------------
int CAnimEditorDoc::iCountSelected()
{
	//	Returns number of cels selected.
	POSITION posInList = lstCels.GetHeadPosition();
	int iCount = 0;
	CCel* pCel;
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( pCel->bSelected )
			iCount++;
	}
	return iCount;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::PutDataOnClipboard( COleDataSource* pData )
{
	//	Called for CAnimEditorView Copy and Cut, and begin drag.
	ASSERT( iCountSelected() > 0 );

	//	Get handle to a piece of memory.
	HGLOBAL hData = ::GlobalAlloc( GMEM_MOVEABLE, theApp.iSizeClipFormatCelBlock );
	//	Lock and get a pointer to the bytes.
	LPVOID pMem = ::GlobalLock( hData );
	//	Set up an ostrstream object that will let me conveniently write to memory.
	ostrstream* pStream = new ostrstream( (char*)pMem, theApp.iSizeClipFormatCelBlock );
	//	Write data out...
	//	1. Number of items.
	*pStream << iCountSelected() << ' ';			//	xxx ' ' due to writing of numbers as strings.... xxx
	//	2. Each item. ( Write out backwards, as order is reversed on insertion. )
	POSITION posInList = lstCels.GetTailPosition();
	CCel* pCel;
	while( posInList )
	{
		pCel = lstCels.GetPrev( posInList );
		if( pCel->bSelected )
		{
			//	Length of string.
			int iLen = pCel->csFileBMP.GetLength();
			*pStream << iLen << ' ';
			//	Contents of string.
			pStream->write( pCel->csFileBMP, iLen );
		}
	}
	//	Finished writing to memory.
	delete pStream;
	::GlobalUnlock( hData );

	pData->CacheGlobalData( theApp.clipFormatCel, hData );
//	pData->DelayRenderData( theApp.clipFormatCel );

	pData->SetClipboard();

	//	xxx to do: limit number of selections placed on clipboard based on memory space
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::GetDataFromClipboard()
{
	//	Called upon paste and drop (see CAnimEditorView::OnEditPaste() and OnDrop() ).
	//	Can create new cels and adds them to lstCels.
	//	Returns FALSE if user is attempting to paste into the same view from which they dragged.
	//	(Evident because bDragSelected will be true for the existing cels.)

	COleDataObject	dataObj;
	CCel*			pCel;
	CCel*			pCelAlready;
	BOOL			bDifferentView = TRUE;
	BOOL			bCelAdded = FALSE;

	BOOL			bUsingFormatSequenceCel = FALSE;

	dataObj.AttachClipboard();

	if( dataObj.IsDataAvailable( theApp.clipFormatCel ) || dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) )
	{
		HGLOBAL		hData;
		LPVOID		pMem;
		istrstream* pStream;
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
			//	Length of string.
			*pStream >> iLen >> ws;
			char* pChar = new char[ iLen ];
			//	Contents of string.
			pStream->read( pChar, iLen );
			CString csFileBMP( pChar, iLen );
			delete pChar;
			if( bUsingFormatSequenceCel )
			{
				//	Throw away the primary hotspot data.
				int i;
				*pStream >> i >> ws;
				*pStream >> i >> ws;
			}
			//	Check for occurrence of a cel for this file.
			pCelAlready = GetCelPtrByFileName( csFileBMP );
			if( pCelAlready )
			{
				if( pCelAlready->bDragSelected )
					bDifferentView = FALSE;
			}
			else
			{
				bCelAdded = TRUE;
				pCel = new CCel( csFileBMP, this );
				lstCels_Insert( pCel );
			}
		}
		//	Finished reading from memory.
		delete pStream;
		::GlobalUnlock( hData );
		if( bCelAdded )
			DocModified();
	}
	else
		ASSERT( FALSE );	//	Menu choice should have been disabled if neither of these formats.

	return bDifferentView;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::VerifyDeleteSelected()
{
	//	If selected cels are used in any sequences, ask user to confirm their deletion.
	//	Returns number of cels selected.
	BOOL	bFound	= FALSE;
	CString	csAsk;
	if( iCountSelected() > 1 )
		csAsk = "This cel is used in the following sequences:\n\n";
	else
		csAsk = "These cels are used in the following sequences:\n\n";
	POSITION posInList = lstCels.GetHeadPosition();
	CCel* pCel;
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( pCel->bSelected && !pCel->lstSeqs.IsEmpty() )
		{
			bFound = TRUE;
			csAsk += csUsedInWhatSequences( pCel );
		}
	}
	if( bFound )
	{
		csAsk += "\nGo ahead and delete all occurrences of this cel?";
		CString csTitle = "Confirm Cel Deletion";
		POSITION posFirstView = GetFirstViewPosition();
		int iReturn = AfxGetMainWnd()->MessageBox( csAsk, csTitle, MB_OKCANCEL | MB_ICONQUESTION );  //	| MB_APPLMODAL );
		if( iReturn == IDOK )
			return TRUE;
	}
	else
		return TRUE;

	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
CString CAnimEditorDoc::csUsedInWhatSequences( CCel* pCel )
{
	//	Returns a CString suitable for a popup dialog listing the sequences in which pCel is used.
	CString csReturn = "";
	POSITION posInSeqList = pCel->lstSeqs.GetHeadPosition();	//	Note: same sequence can appear multiple times.
	CSequence* pSeq;
	while( posInSeqList )
	{
		pSeq = pCel->lstSeqs.GetNext( posInSeqList );
		csReturn += "\t";
		csReturn += pSeq->csName;
		csReturn += "\n";
	}
	return csReturn;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::DeleteSelected( BOOL bDragSelected, BOOL bDeleteLinkedCels )
{
	//	Deletes selected cels and any occurrences of them in sequences.
	//	If bDragSelected, bDragSelected cels are used instead of bSelected ones.
	//	If not bDeleteLinkedCels, any cels with links are skipped.
	//	(In this case, returns TRUE if no cels were skipped.)
	//	Called by CUT and delete.
	BOOL bNoSkips = TRUE;
	BOOL bFound = FALSE;
	POSITION posInList = lstCels.GetHeadPosition();
	POSITION posNow;
	CCel* pCel;
	while( posNow = posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( ( bDragSelected && pCel->bDragSelected ) || ( !bDragSelected && pCel->bSelected ) )
		{
			if( bDeleteLinkedCels )
			{
				if( !pCel->lstSeqs.IsEmpty() )
				{
					//	This cel appears in a sequence. Delete associated sequence cels.
					POSITION posInSeqList = pCel->lstSeqs.GetHeadPosition();	//	Note: same sequence can appear multiple times.
					CSequence* pSeq;
					while( posInSeqList )
					{
						pSeq = pCel->lstSeqs.GetNext( posInSeqList );
						pSeq->DeleteSequenceCelMatchingCel( pCel );			
						//	[ Note: lstSeqs link is not removed upon CSequenceCel delete (which would possibly make good 
						//	  sense otherwise ), so iteration through the list here is unaffected. ]
					}
				}
				bFound = TRUE;
				delete pCel;
				lstCels.RemoveAt( posNow );
			}
			else
			{
				if( !pCel->lstSeqs.IsEmpty() )
				{
					bNoSkips = FALSE;
				}
				else
				{
					bFound = TRUE;
					delete pCel;
					lstCels.RemoveAt( posNow );
				}
			}
		}
	}
	if( bFound )
	{
		DocModified();
	}
	return bNoSkips;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::ConvertSelectedToDragSelected()
{
	//	Sets all selected cels to dragselected.
	POSITION posInList = lstCels.GetHeadPosition();
	CCel* pCel;
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( pCel->bSelected )
		{
			pCel->bDragSelected = TRUE;
			pCel->bSelected = FALSE;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::ClearDragSelected()
{
	//	Clears all dragselected cel states.
	POSITION posInList = lstCels.GetHeadPosition();
	CCel* pCel;
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		pCel->bDragSelected = FALSE;
	}
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::Export( BOOL bRLE, BOOL bAuto )
{
	//	If bAuto is true, a filename is not asked for.
	//	If a filename hasn't been set, xxxxxx

	BOOL bDoExport = FALSE;
	CString* pcsFile;

	if( !bRLE )
		pcsFile	= &csFileExport;
	else
		pcsFile	= &csFileExportRLE;

	if( !bAuto )
	{
		if( bActionsReport( "About to export the following:" ) )
		{			
			CString csFileExt;
			CString csFileFilter;
			if( !bRLE )
			{
				csFileExt		= "AXC";
				csFileFilter	= "Animation eXport Catalog Files (*.axc)|*.axc||";
			}
			else
			{
				csFileExt		= "AXR";
				csFileFilter	= "Animation eXport RLE Catalog Files (*.axr)|*.axr||";
			}

			CFileDialog	dlg( FALSE, csFileExt, *pcsFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, csFileFilter );
			if( dlg.DoModal() == IDOK )
			{
				bDoExport = TRUE;
				if( *pcsFile != dlg.GetPathName() )
				{
					SetModifiedFlag();
					*pcsFile = dlg.GetPathName();
				}
			}
		}
	}
	else
	{
		if( *pcsFile == "" )
			TRACE( "No export file has been assigned to the AnimEditor AFC file: %s\n", GetPathName() );
		else
			bDoExport = TRUE;
	}

	if( bDoExport )
	{
		//	Set up export file.
		CFile fileExport;
		VERIFY( fileExport.Open( *pcsFile, CFile::modeWrite | CFile::modeCreate ) );
		CArchive arExport( &fileExport, CArchive::store );

		//	Create a CSpriteCatalog that mirrors this doc, for serializing out.
		CSpriteCatalog* pCat = new CSpriteCatalog( this, bRLE );
		
		pCat->Initialize( this );

		//	Export SpriteCatalog.
		pCat->bSerializeRLE = bRLE;		//	Flag used by CSpriteCatalog serialize.
		pCat->Serialize( arExport );

		delete pCat;		//	[ We only needed it for serialization. ]

		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::ExportRLEOutOfDate()
{
	//	Returns true if the datetime of the AXR file is older than the latest datetime of the source BMP files.
	if( csFileExportRLE == "" )			//	No AXR file name has been assigned.
		return TRUE;

	FILETIME ftimeExport;
	FILETIME ftimeTest;

	//	Get datetime of AXR file.
	try
	{
		CFile fileExport( csFileExportRLE, CFile::modeRead );
		::GetFileTime( (HANDLE)fileExport.m_hFile, NULL, NULL, &ftimeExport );
		fileExport.Close();
	}
	catch( CFileException* e )
	{
		TRACE( "File exception thrown trying to open export file: %s\n", csFileExportRLE );
		e->Delete();
		return TRUE;
	}

	//	Check that AFC file itself wasn't changed after last export.
	try
	{
		CFile fileDoc( GetPathName(), CFile::modeRead );
		::GetFileTime( (HANDLE)fileDoc.m_hFile, NULL, NULL, &ftimeTest );
		fileDoc.Close();
		if( ::CompareFileTime( &ftimeExport, &ftimeTest ) == -1 )
			return TRUE;
	}
	catch( CFileException* e )
	{
		TRACE( "File exception thrown trying to open AFC file: %s\n", GetPathName() );
		e->Delete();
		return FALSE;
	}

	//	Check all BMPs used in sequences.
	POSITION	posInList = lstCels.GetHeadPosition();
	CCel*		pCel;
	while( posInList )
	{
		pCel = lstCels.GetNext( posInList );
		if( !pCel->lstSeqs.IsEmpty() )			//	( Is it used in a sequence? )
		{
			try
			{
				CString filename = csFolder;
				filename += pCel->csFileBMP;

				CFile fileBMP( filename, CFile::modeRead );
				::GetFileTime( (HANDLE)fileBMP.m_hFile, NULL, NULL, &ftimeTest );
				fileBMP.Close();
				if( ::CompareFileTime( &ftimeExport, &ftimeTest ) == -1 )
					return TRUE;
			}
			catch( CFileException* e )
			{
				TRACE( "File exception thrown trying to open BMP file: %s\n", pCel->csFileBMP );
				e->Delete();
				return FALSE;
			}
		}
	}
	TRACE( "Export file %s is up-to-date.\n", csFileExportRLE );
	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnCatalogBrowse() 
{
	if (BrowseForFolder(csFolder))
	{
		SetModifiedFlag( TRUE );
		Reload(csFolder);
		//	Save latest chosen folder in registry.
		theApp.WriteProfileString( "User Prefs", "Image Folder", csFolder );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnCatalogBrowseAll()
{
	CString oldFolder = csFolder;

	if (BrowseForFolder(csFolder))	{
		SetModifiedFlag( TRUE );
		UpdateNames(oldFolder, csFolder);
		Reload(csFolder);
		//	Save latest chosen folder in registry.
		theApp.WriteProfileString( "User Prefs", "Image Folder", csFolder );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::UpdateNames(CString &oldfolder, CString &newfolder)
{
	POSITION posInList = lstCels.GetHeadPosition();
	while( posInList )
	{
		CCel* pCel = lstCels.GetNext( posInList );

		CString name = oldfolder + pCel->csFileBMP;		// full path name of cel
		name.MakeLower();

		CString folder = newfolder;
		folder.MakeLower();

		int ipos = name.Find(folder);
		if (ipos == 0)	{
			pCel->csFileBMP = name.Right(name.GetLength() - folder.GetLength());
		}
		else	{
			CString csMess;

			csMess = "New folder " + newfolder + " is not part of image name " + name;
			AfxMessageBox( csMess );
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::BrowseForFolder(CString &csPath) 
{
	BOOL gotnew = FALSE;

	if (!m_pMalloc)
		return gotnew;			// make sure alloctor is set up

	CString title = "Select Image Folder";

	BROWSEINFO bi; 
    LPSTR lpBuffer; 
    LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
    
    // Allocate a buffer to receive browse information. 
    if ((lpBuffer = (LPSTR)m_pMalloc->Alloc(MAX_PATH)) == NULL) 
        return gotnew; 
 
    // Fill in the BROWSEINFO structure. 
	memset(&bi,0,sizeof(BROWSEINFO));
//	bi.hwndOwner = m_hWnd;		// try just not setting this value
    bi.pszDisplayName = lpBuffer; 
    bi.lpszTitle = title;  
 
    // Browse for a folder and return its PIDL. 
    pidlBrowse = SHBrowseForFolder(&bi); 
    if (pidlBrowse != NULL) 
	{ 
        if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) 
		{
			// save a copy of the path in the document
			csPath = lpBuffer;
			csPath += "\\";
			csPath.MakeUpper();
			gotnew = TRUE;
		}
 
        // Free the PIDL returned by SHBrowseForFolder. 
        m_pMalloc->Free(pidlBrowse); 
    } 
 
    // Clean up. 
    m_pMalloc->Free(lpBuffer);

	return gotnew;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::SetupPalette()	{
	//	Set up dib holding game palette and transparent color to use.

	CDC* pDC = new CDC;
	pDC->CreateCompatibleDC( NULL );

	CString csPalette = "palette.bmp";
	if (!LoadPalette(csPalette, csFolder, pDC))	{
		LoadPalette(csPalette, theApp.csAppPath, pDC);
	}

	delete pDC;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::LoadPalette(CString &csPalette, CString &path, CDC *pDC)	{
	//	Set up dib holding game palette and transparent color to use.
	if (docPalette.Create( pDC, csPalette, path, FALSE, FALSE ) )	{
		docPalette.SetOriginalPalette();		// set this up for later export NAR

		theApp.indexTransparent = docPalette.GetTransColorIndex();

		PALETTEENTRY pePalette[ 256 ];
		VERIFY( docPalette.GetPaletteEntries( pePalette ) );
		PALETTEENTRY peTrans = pePalette[ theApp.indexTransparent ];
		theApp.colorTransparent = RGB( peTrans.peRed, peTrans.peGreen, peTrans.peBlue );
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::ResizeViews()
{
	CView* pView;
	POSITION posView;

	posView = GetFirstViewPosition();
	while( posView != NULL )
	{
		pView = GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CSequenceView" ) == 0 )
		{
			((CSequenceView*)pView)->PostMessage( WM_SIZE );
		}
	}

	posView = GetFirstViewPosition();
	while( posView != NULL )
	{
		pView = GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CMultipleSequencesView" ) == 0 )
		{
			((CMultipleSequencesView*)pView)->PostMessage( WM_SIZE );
		}
	}
	
	posView = GetFirstViewPosition();
	while( posView != NULL )
	{
		pView = GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CAnimEditorView" ) == 0 )
		{
			((CAnimEditorView*)pView)->PostMessage( WM_SIZE );
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorDoc::bActionsReport( const CString& csHeading )
{
	//	Put up a dialog showing the number of sequences in which each action appears.
	BOOL bAdditionMade = FALSE;
	CString csText = csHeading + "\n\n";
	
	POSITION posAction = theApp.lstActions.GetHeadPosition();
	CActionRecord* pAction;
	while( posAction )
	{
		pAction = theApp.lstActions.GetNext( posAction );
		CString csAdd;
		//	Inefficient but that's ok here. Spin through sequences and count, for every action.
		int iCount = 0;
		POSITION posSeq = lstSeqs.GetHeadPosition();
		CSequence* pSeq;
		while( posSeq )
		{
			pSeq = lstSeqs.GetNext( posSeq );
			if( pSeq->lAction == pAction->lKey )
				iCount++;
		}
		if( iCount )
		{
			csAdd.Format( "\"%s\" is the action for %i sequences.\n", pAction->csAction, iCount );
			csText += csAdd;
			bAdditionMade = TRUE;
		}
	}
	if( !bAdditionMade )
		csText += "No actions assigned to any sequences.";

	return ( AfxMessageBox( csText, MB_OKCANCEL ) == IDOK );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnSequenceNew() 
{
	//	Create a new sequence...
	CSequence* pSequenceNew = new CSequence( this );
	lstSeqs.AddTail( pSequenceNew );
	
	//	ajw Added 5/8/97
	//	Try to duplicate info from the active SequenceView, if there is one active.
	//	As usual, when it comes to finding a view I'm just making this up as I go...
	//	Get ptr to active view, by asking frame.
	POSITION posView		= GetFirstViewPosition();
	CView* pViewAny			= GetNextView( posView );
	CFrameWnd* pMainFrame	= pViewAny->GetParentFrame();
	CView* pViewActive		= pMainFrame->GetActiveView();
	POSITION posSeq = lstSeqs.GetHeadPosition();
	CSequence* pSeq;
	while( posSeq )
	{
		pSeq = lstSeqs.GetNext( posSeq );
		if( pSeq->pSeqView == pViewActive )
		{
			//	Found a SequenceView that matches active view.
			//	Copy its Sequence's info to the new sequence.
			pSequenceNew->csName		= pSeq->csName;
			pSequenceNew->iMoveSpeed	= pSeq->iMoveSpeed;
			pSequenceNew->iSpeed		= pSeq->iSpeed;
			pSequenceNew->lAction		= pSeq->lAction;
			//	Attempt to make direction the one _following_ what is set for selected sequence.
			POSITION posDirection = theApp.lstDirections.GetHeadPosition();
			POSITION posNow;
			CDirectionRecord* pdrCheck;
			while( posNow = posDirection )
			{
				pdrCheck = theApp.lstDirections.GetNext( posDirection );
				if( pdrCheck->lKey == pSeq->iDirection )
				{
					posDirection = posNow;
					break;
				}
			}
			if( !posDirection )		//	Direction not found in directions list (possible?).
				pSequenceNew->iDirection	= pSeq->iDirection;
			else
			{
				theApp.lstDirections.GetNext( posDirection );
				if( !posDirection )
				{
					//	No next - Wraparound to beginning of list.
					posDirection = theApp.lstDirections.GetHeadPosition();
				}
				CDirectionRecord* pdrRec = theApp.lstDirections.GetAt( posDirection );
				pSequenceNew->iDirection = pdrRec->lKey;
			}
		}
	}

	SetModifiedFlag();
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorDoc::OnSequenceDelete() 
{
	//	Similar process to OnSequenceNew() in terms of finding view with focus (there must be one).
	POSITION posView		= GetFirstViewPosition();
	CView* pViewAny			= GetNextView( posView );
	CFrameWnd* pMainFrame	= pViewAny->GetParentFrame();
	CView* pViewActive		= pMainFrame->GetActiveView();
	POSITION posSeq = lstSeqs.GetHeadPosition();
	POSITION posNow;
	CSequence* pSeq;
	while( posNow = posSeq )
	{
		pSeq = lstSeqs.GetNext( posSeq );
		if( pSeq->pSeqView == pViewActive )
		{
			//	Found a SequenceView that matches active view.
			//	Set focus to AnimEditorView, to avoid problems with deleting an active view.
			POSITION posView = GetFirstViewPosition();
			CView* pView;
			while( posView != NULL )
			{
				pView = GetNextView( posView );
				if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CAnimEditorView" ) == 0 )
				{
					pMainFrame->SetActiveView( pView, TRUE );
					break;
				}
			}

			//	Delete sequenceview, mimicking the way it was created, through the MultipleSequencesView.
			//	Get the MultipleSequencesView......
			posView = GetFirstViewPosition();
			while( posView != NULL )
			{
				pView = GetNextView( posView );
				if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CMultipleSequencesView" ) == 0 )
				{
					( (CMultipleSequencesView*)pView )->DeleteSequenceView( pSeq->pSeqView );
					break;
				}
			}
			//	Delete sequence.
			delete pSeq;
			lstSeqs.RemoveAt( posNow );
			//	Tell CelView not to point to deleted sequence.
			posView = GetFirstViewPosition();
			while( posView != NULL )
			{
				pView = GetNextView( posView );
				if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
				{
					((CCelView*)pView)->LinkToSequence( NULL );
					((CCelView*)pView)->pSequencePrev = NULL;		//	Just in case.
					break;
				}
			}
			break;
		}
	}
	SetModifiedFlag();
}
