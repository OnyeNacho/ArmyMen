//-----------------------------------------------------------------
// Bitmap Info Helpers
// C++ Header - BMInfo.h
//-----------------------------------------------------------------

#ifndef __BMINFO_H
#define __BMINFO_H

#define DECLAREBITMAPINFO(n) typedef struct tagBITMAPINFO##n \
{ \
  BITMAPINFOHEADER  bmiHeader; \
  RGBQUAD           bmiColors[n]; \
} BITMAPINFO##n;

#ifdef __cplusplus
template<int n>
struct BITMAPINFO_N
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[n];
};
#endif

#endif
