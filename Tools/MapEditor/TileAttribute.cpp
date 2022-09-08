#include "stdafx.h" 
#include "MapEditor.h"
#include "TileAttribute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTileAttribute::CTileAttribute(LPCTSTR name, int nBitCount, int nSize, int iDefaultValue)
{
	m_pszName = name;
	ASSERT(!m_pszName.IsEmpty());
	SetBitCount(nBitCount);
	VERIFY(SetDefaultValue(iDefaultValue));

	m_values.SetSize(nSize);
	for (int i=0; i < nSize; i++)
		m_values[i] = iDefaultValue;  // TBD: NO_TILE_ATTRIBUTE;
}

CTileAttribute::~CTileAttribute()
{
	TRACE("Deleting tile attribute %s\n", m_pszName);
	m_values.RemoveAll();
}

IMPLEMENT_SERIAL(CTileAttribute, CObject, VERSIONABLE_SCHEMA | 1);

void CTileAttribute::Serialize(CArchive& ar)
{
	CAttribute::Serialize(ar);
	// Since tile attributes are always allocated/used dynamically
	// we can skip the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA
	if (ar.IsStoring())
		ar << m_pszName;
	else
		ar >> m_pszName;
	m_values.Serialize(ar);
}

int CTileAttribute::GetValue(int nIndex) const
{
	int iVal = (int)m_values[nIndex];
	if (iVal == NO_TILE_ATTRIBUTE)
		return m_defaultValue;
	return iVal;
}

#ifdef _DEBUG
void CTileAttribute::AssertValid() const
{
	CAttribute::AssertValid();

	int iCount = m_values.GetSize();
	for (int i=0; i < iCount; i++)
	{
		int iVal = GetValue(i);
		ASSERT(iVal >= 0 && iVal <= m_maxValue);
	}
}
#endif

void CTileAttribute::SetBitCount(int nBitCount)
{
	CAttribute::SetBitCount(nBitCount);
	int iCount = m_values.GetSize();
	for (int i=0; i < iCount; i++)
	{
		m_values[i] = min(m_values[i], m_maxValue);
	}
}
