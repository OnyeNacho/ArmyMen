// BoldComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "BoldComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoldComboBox

CBoldComboBox::CBoldComboBox() 
{
	m_hBoldFont = NULL;

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	ASSERT(hFont != NULL);

	CFont *pFont = CFont::FromHandle(hFont);
	ASSERT(pFont != NULL);

	LOGFONT logfont;
	VERIFY(pFont->GetLogFont(&logfont));
	logfont.lfWeight = FW_EXTRABOLD; 

	m_hBoldFont = ::CreateFontIndirect(&logfont);
    if (m_hBoldFont == NULL)
		TRACE0("Couldn't create bold font\n"); // TBD: throw an error?

	DeleteObject(hFont);
}

CBoldComboBox::~CBoldComboBox()
{
	if (m_hBoldFont) 
		DeleteObject(m_hBoldFont);
}


BEGIN_MESSAGE_MAP(CBoldComboBox, CComboBox)
	//{{AFX_MSG_MAP(CBoldComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoldComboBox message handlers
void CBoldComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT( lpDIS->CtlType == ODT_COMBOBOX );

	// The LBS_OWNERDRAWFIXED and LBS_HASSTRINGS style flags must be set
	// ASSERT((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)) ==
	//	(LBS_OWNERDRAWFIXED | LBS_HASSTRINGS));

	// make sure this is a *real* item
	if (lpDIS->itemID == -1)
		return;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	BOOL bBold = (BOOL)lpDIS->itemData;    
	COLORREF crBk, crText;
	TEXTMETRIC tm;
	int x, y;

	// Calculate the colors to use
	crBk = pDC->SetBkColor(
		GetSysColor(lpDIS->itemState & ODS_SELECTED ? COLOR_HIGHLIGHT : COLOR_WINDOW) );
	crText = pDC->SetTextColor(
		GetSysColor(lpDIS->itemState & ODS_SELECTED ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT) );

	// Calculate the position of the text
	pDC->GetTextMetrics( &tm );
	x = LOWORD(GetDialogBaseUnits()) / 2;
	y = (lpDIS->rcItem.bottom + lpDIS->rcItem.top - tm.tmHeight) / 2;

	// Draw the text

	CString string;
	GetLBText(lpDIS->itemID, string);

	HFONT hOldFont;
	if (bBold && m_hBoldFont) 
		hOldFont = (HFONT)pDC->SelectObject(m_hBoldFont);

	pDC->ExtTextOut(lpDIS->rcItem.left + x, y, ETO_CLIPPED | ETO_OPAQUE,
			&lpDIS->rcItem,(LPCTSTR) string, string.GetLength(), NULL);

	if (bBold && m_hBoldFont)
		pDC->SelectObject(hOldFont);

	// Put the colors back as they were
	pDC->SetTextColor( crText );
	pDC->SetBkColor( crBk );

	// Draw the focus rect if needed
	if (lpDIS->itemState & ODS_FOCUS)
		pDC->DrawFocusRect( &lpDIS->rcItem );
}

