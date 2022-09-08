// CycleButton.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "CycleButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCycleButton

CCycleButton::CCycleButton()
{
   m_nCycleState = CCYCLE_INVALID;
}

CCycleButton::~CCycleButton()
{
	if (m_hWnd)
	{
		SetBitmap(NULL);
	}

	while (!m_hBitmapList.IsEmpty())
	{
		HBITMAP hBitmap = m_hBitmapList.RemoveHead();
		DeleteObject(hBitmap);
	}
}

void CCycleButton::LoadBitmaps(UINT nCycleStates,...) 
{
	va_list args;
	UINT nBitmapID;

	HINSTANCE hInstance = AfxGetInstanceHandle();
	va_start(args, nCycleStates);

	while (nCycleStates--)
	{
		nBitmapID = va_arg(args, UINT);
		HBITMAP hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(nBitmapID));
		m_hBitmapList.AddTail(hBitmap);
	}

	va_end(args);
	
}

void CCycleButton::SetCycleState(UINT nCycleState)
{
	ASSERT(m_hWnd != NULL);
	if (nCycleState != m_nCycleState)
	{
		if (nCycleState < GetCycleCount())
		{
			POSITION pos = m_hBitmapList.FindIndex(nCycleState);
			SetBitmap(m_hBitmapList.GetAt(pos));
		}
		else
			SetBitmap(NULL);
		m_nCycleState = nCycleState;
	}
}

BEGIN_MESSAGE_MAP(CCycleButton, CButton)
	//{{AFX_MSG_MAP(CCycleButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCycleButton message handlers

void CCycleButton::OnClicked() 
{
	if (m_nCycleState == CCYCLE_INVALID || m_nCycleState == (GetCycleCount()-1))
		SetCycleState(0);
	else 
		SetCycleState(m_nCycleState + 1);
}
