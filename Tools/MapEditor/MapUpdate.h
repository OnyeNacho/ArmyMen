#ifndef _MAPUPDATE_H_
#define _MAPUPDATE_H_

// Note: this should go away...use CRgn instead!

class CMapUpdate : public CObject
{
public:
	CRect m_rect; // rectangular region of map to update
	CMapUpdate(CRect rect) { m_rect = rect; }
    DECLARE_DYNAMIC(CMapUpdate)
};

#endif