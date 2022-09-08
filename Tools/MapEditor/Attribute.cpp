#include "stdafx.h"
#include "MapEditor.h"
#include "Attribute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CAttribute::CAttribute()
{
	m_nBitCount = 0;
	m_maxValue = 0;
	m_defaultValue = 0;
}

void CAttribute::SetBitCount(int nBitCount) 
{
	ASSERT(nBitCount >= 0 && nBitCount <= MAX_ATTRIBUTE_BITS);
	m_nBitCount = nBitCount;
	m_maxValue = (1 << nBitCount) - 1;
	if (m_defaultValue > m_maxValue)
		m_defaultValue = m_maxValue;
}

BOOL CAttribute::SetDefaultValue(int iValue)
{
	if (iValue >= (0-m_maxValue) && iValue <= m_maxValue)
	{
		m_defaultValue = iValue;
		return TRUE;
	}
	return FALSE;
}

void CAttribute::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_nBitCount;
		ar << m_defaultValue;
	}
	else
	{
		UINT nBitCount;
		ar >> nBitCount;
		ar >> m_defaultValue;
		SetBitCount(nBitCount);
	}
}

#ifdef _DEBUG
void CAttribute::AssertValid() const
{
	ASSERT(m_nBitCount >= 0 && m_nBitCount <= MAX_ATTRIBUTE_BITS);
	ASSERT(m_maxValue == ((1 << m_nBitCount) - 1));
	ASSERT(m_defaultValue >= (0-m_maxValue) && m_defaultValue <= m_maxValue);
}
#endif