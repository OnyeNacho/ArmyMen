// AnimThread.h : header file
//

// external classes
class CObjectLayer;
class CMapEditorDoc;

#define USE_AFX_ANIMTHREAD 0  // non-zero to implement thread for use with AfxBeginThread
/////////////////////////////////////////////////////////////////////////////
// CAnimThread thread : assumes instance of this class is created with
// AfxBeginThread() so we can access our MFC classes

class CAnimThread : public CWinThread
{
#if USE_AFX_ANIMTHREAD
	DECLARE_DYNAMIC(CAnimThread)
	CAnimThread(CWnd *pWnd, CObjectLayer *pObjectLayer);
#else
	DECLARE_DYNCREATE(CAnimThread)
	CAnimThread();
	void InitLocalData(CWnd *pWnd, CObjectLayer *pObjectLayer);
#endif

// Attributes
public:
	HANDLE m_hEventKill;
	HANDLE m_hEventDead;
    HWND m_hWnd;

	void Delete();
	void KillThread();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimThread)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CObjectLayer *m_pObjectLayer;
	virtual ~CAnimThread();

	// Generated message map functions
	//{{AFX_MSG(CAnimThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
