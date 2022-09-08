#ifndef _MYMULTIDOCTEMPLATE_H_
#define _MYMULTIDOCTEMPLATE_H_

class CMyMultiDocTemplate : public CMultiDocTemplate
{
public:
	// same as OpenDocumentFile but does not create a frame/view for the document.
	virtual CDocument* OpenDocument( LPCTSTR lpszPathName, BOOL allowRetry = FALSE); 
    CMyMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
                        CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
};
#endif