// AnimThread.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "AnimThread.h"
#include "ObjectLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimThread

#if USE_AFX_ANIMTHREAD
IMPLEMENT_DYNAMIC(CAnimThread, CWinThread)

CAnimThread::CAnimThread(CWnd *pWnd, CObjectLayer *pObjectLayer)
{
	m_bAutoDelete = FALSE;

	// kill event starts out in the signaled state
	m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEventDead = CreateEvent(NULL, TRUE, FALSE, NULL);

	ASSERT(pWnd != NULL);
	m_pMainWnd = pWnd;         // terminate when this window closes
	m_hWnd = pWnd->m_hWnd;     // post messages to this window
	m_pObjectLayer = pObjectLayer;
}

#else

IMPLEMENT_DYNCREATE(CAnimThread, CWinThread)

CAnimThread::CAnimThread()
{
	m_bAutoDelete = FALSE;

	// kill event starts out in the signaled state
	m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEventDead = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void CAnimThread::InitLocalData(CWnd *pWnd, CObjectLayer *pObjectLayer)
{
	ASSERT(pWnd != NULL);
	m_pMainWnd = pWnd;         // terminate when this window closes
	m_hWnd = pWnd->m_hWnd;     // post messages to this window
	m_pObjectLayer = pObjectLayer;
}
#endif


CAnimThread::~CAnimThread()
{
	CloseHandle(m_hEventKill);
	CloseHandle(m_hEventDead);
}

BOOL CAnimThread::InitInstance()
{
	// loop but check for kill notification
	while (WaitForSingleObject(m_hEventKill, 0) == WAIT_TIMEOUT)
	{
		m_pObjectLayer->SingleStep();
	}

	// avoid entering standard message loop by returning FALSE
	return FALSE;
}



BEGIN_MESSAGE_MAP(CAnimThread, CWinThread)
	//{{AFX_MSG_MAP(CAnimThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimThread message handlers

void CAnimThread::KillThread()
{
	// Note: this function is called in the context of other threads,
	//	not the thread itself.

	// reset the m_hEventKill which signals the thread to shutdown
	VERIFY(SetEvent(m_hEventKill));

	// allow thread to run at higher priority during kill process
	SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	WaitForSingleObject(m_hEventDead, INFINITE);
	WaitForSingleObject(m_hThread, INFINITE);

	// now delete CWinThread object since no longer necessary
	delete this;
}

void CAnimThread::Delete()
{
	// calling the base here won't do anything but it is a good habit
	CWinThread::Delete();

	// acknowledge receipt of kill notification
	VERIFY(SetEvent(m_hEventDead));
}

