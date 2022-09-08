// RulerWnd.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "tileset.h"
#include "RulerWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerWnd

IMPLEMENT_DYNCREATE(CRulerWnd, CWnd)

CRulerWnd::CRulerWnd()
{
	m_iMode = 0;
	m_iType = 0;
	m_pSet = NULL;
}

CRulerWnd::~CRulerWnd()
{
}


BEGIN_MESSAGE_MAP(CRulerWnd, CWnd)
	//{{AFX_MSG_MAP(CRulerWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRulerWnd message handlers

void CRulerWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CBrush back;
	CPen sLinePen;
	CPen *pOld=NULL;
	CRect sClipRect;
	CRect sWndRect;
	int iCur=0;
	int iWidth=0;
	int iHeight=0;
	int iTotal=0;
	int iMark=1;

	back.CreateSolidBrush(RGB(255, 255, 255));
	sLinePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.GetClipBox(&sClipRect);
	dc.FillRect(&sClipRect, &back);
	GetClientRect(&sWndRect);

	iWidth = sWndRect.Width();
	iHeight = sWndRect.Height();

	if (2 == m_iType)
	{
		return;
	}

	if (0 == m_iMode)
	{
		if (NULL == m_pSet)
			return;
		if (0 == m_iType)
			iCur = m_pSet->m_iTileHeight;
		else
			iCur = m_pSet->m_iTileWidth;
		iCur--;
	}
	else
		iCur = 5;

	pOld = dc.SelectObject(&sLinePen);
	if (NULL == pOld)
		return;

	if (0 == m_iType)
		iTotal = iHeight;
	else
		iTotal = iWidth;

	while (iCur < iTotal)
	{
		if (0 == m_iType)
		{
			if (0 == m_iMode)
			{
				if (10 == iMark)
				{
					dc.MoveTo(0, iCur);
					iMark = 1;
				}
				else if (5 == iMark)
				{
					dc.MoveTo(iWidth/2, iCur);
					iMark++;
				}
				else
				{
					dc.MoveTo((iWidth/4)*3, iCur);
					iMark++;
				}
			}
			else
			{
				if (30 == iMark)
				{
					dc.MoveTo(0, iCur);
					iMark = 1;
				}
				else if (15 == iMark)
				{
					dc.MoveTo(iWidth/2, iCur);
					iMark++;
				}
				else
				{
					dc.MoveTo((iWidth/4)*3, iCur);
					iMark++;
				}
			}
			dc.LineTo(iWidth, iCur);
		}
		else
		{
			if (0 == m_iMode)
			{
				if (10 == iMark)
				{
					dc.MoveTo(iCur, 0);
					iMark = 1;
				}
				else if (5 == iMark)
				{
					dc.MoveTo(iCur, iHeight/2);
					iMark++;
				}
				else
				{
					dc.MoveTo(iCur, (iHeight/4)*3);
					iMark++;
				}
			}
			else
			{
				if (30 == iMark)
				{
					dc.MoveTo(iCur, 0);
					iMark = 1;
				}
				else if (15 == iMark)
				{
					dc.MoveTo(iCur, iHeight/2);
					iMark++;
				}
				else
				{
					dc.MoveTo(iCur, (iHeight/4)*3);
					iMark++;
				}
			}
			dc.LineTo(iCur, iHeight);
		}
		if (0 == m_iMode)
		{
			if (0 == m_iType)
				iCur += m_pSet->m_iTileHeight;
			else
				iCur += m_pSet->m_iTileWidth;
		}
		else
			iCur += 5;
	}
	dc.SelectObject(pOld);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CRulerWnd::SetMode(int iMode)
{
	m_iMode = iMode;
	RedrawWindow();
}

void CRulerWnd::ChangeMode()
{
	if (0 == m_iMode)
		m_iMode = 1;
	else
		m_iMode = 0;
	RedrawWindow();
}
