// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
	m_color = RGB(0,0,0);
}

CColorButton::~CColorButton()
{
}

void CColorButton::SetColor(COLORREF color)
{
	m_color = color;
	SetButtonStyle(GetButtonStyle(),TRUE);
}

BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpdi) 
{
	CBrush brush(m_color);
	FillRect(lpdi->hDC, &lpdi->rcItem, (HBRUSH)brush);
}

