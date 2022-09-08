#ifndef _MYMACROS_H_
#define _MYMACROS_H_

#ifdef _DEBUG
inline HBITMAP SelectHBitmap(HDC hDC, HBITMAP hBitmap)
{
	HBITMAP hOld = (HBITMAP)SelectObject(hDC, hBitmap);
	if (hOld == NULL)
		TRACE0("SelectObject returned a NULL bitmap\n");
	return hOld;
}
#else
inline HBITMAP SelectHBitmap(HDC hDC, HBITMAP hBitmap)
{
	return (HBITMAP)SelectObject(hDC, hBitmap);
}
#endif



#endif