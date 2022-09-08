#include "stdafx.h" 
#include "MyMultiDocTemplate.h"

CMyMultiDocTemplate::CMyMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
     CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
	 : CMultiDocTemplate(nIDResource,pDocClass, pFrameClass, pViewClass)
{}


CDocument *CMyMultiDocTemplate::OpenDocument(LPCTSTR lpszPathName, BOOL allowRetry)
{
	CDocument *pDocument;
	if (lpszPathName != NULL && (MatchDocType(lpszPathName,pDocument) == CDocTemplate::yesAlreadyOpen))
	{
		ASSERT(pDocument != NULL);
		return pDocument;
	}
	pDocument = CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE0("MyMultiDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT_VALID(pDocument);

	if (lpszPathName == NULL || strlen(lpszPathName)==0)
	{
		// create a new document - with default document name
		SetDefaultTitle(pDocument);

		// avoid creating temporary compound file when starting up invisible
		pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			// user has be alerted to what failed in OnNewDocument
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			return NULL;
		}

		// it worked, now bump untitled count
		m_nUntitledCount++;
	}
	else
	{
		// open an existing document
		CWaitCursor wait;
		CString path = lpszPathName;
		BOOL bRetried = FALSE;

		while (!pDocument->OnOpenDocument(path))
		{
			// user has be alerted to what failed in OnOpenDocument
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			if (allowRetry) 
				allowRetry = AfxGetApp()->DoPromptFileName(path, AFX_IDS_OPENFILE,
								OFN_FILEMUSTEXIST, TRUE, this);
			if (!allowRetry)
				return NULL;
			else
				bRetried = TRUE;
		}

#ifdef _MAC
		// if the document is dirty, we must have opened a stationery pad
		//  - don't change the pathname because we want to treat the document
		//  as untitled
		if (!pDocument->IsModified())
#endif
			pDocument->SetPathName(path, !allowRetry);

		if (bRetried)
			pDocument->SetModifiedFlag();
	}
	return pDocument;
}


