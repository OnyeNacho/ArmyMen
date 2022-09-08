#ifndef _TILE_ATTRIBUTE_H_
#define _TILE_ATTRIBUTE_H_

#include "Attribute.h"

#define NO_TILE_ATTRIBUTE -1

class CTileAttribute : public CObject, public CAttribute
{
protected:
	CString m_pszName;
	CArray<ATTRIBUTE_BASE_TYPE,ATTRIBUTE_BASE_TYPE> m_values;

	CTileAttribute() {} // for serialization only
    DECLARE_SERIAL(CTileAttribute);

public:
	void SetBitCount(int nBitCount);
	CTileAttribute(LPCTSTR name, int nBitCount, int nSize, int iDefaultValue);
	virtual ~CTileAttribute();

	LPCTSTR GetName() { return m_pszName; }
	int GetAt(int nIndex) { return m_values[nIndex]; } // may return NO_TILE_ATTRIBUTE
	int GetValue(int nIndex) const; // will not return NO_TILE_ATTRIBUTE
    int GetSize() { return m_values.GetSize(); }

	void RemoveAt(int nIndex) { m_values.RemoveAt(nIndex); }
	void SetName(LPCTSTR lpszName) { m_pszName = lpszName; }
	void SetSize(int nSize) { m_values.SetSize(nSize); }
	void SetValue(int nIndex, int iValue)
	{
		ASSERT(iValue >= 0 && iValue <= m_maxValue);
		m_values.SetAtGrow(nIndex, iValue);
	}
	void Serialize(CArchive& ar);

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

};

#endif