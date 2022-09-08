#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
/*
** An Attribute can be anything from 1 bit to 15 bits long; we reserve
** the top/sign bit to denote attribute selection.  
**
*/
typedef SHORT ATTRIBUTE_BASE_TYPE;  
#define MAX_ATTRIBUTE_BITS     15      // Note: spin controls do not allow values > 0x7fff

class CAttribute 
{
protected:
	int m_nBitCount;
	ATTRIBUTE_BASE_TYPE m_maxValue;
	ATTRIBUTE_BASE_TYPE m_defaultValue;

public:
	CAttribute();
	int GetDefaultValue() const { return (int)m_defaultValue; }
	int GetMaxValue() const { return (int)m_maxValue; }
	int GetBitCount() const { return m_nBitCount; }
	virtual void SetBitCount(int nBitCount);
	virtual BOOL SetDefaultValue(int iValue);
	void SetMaxValue(int iMax) { m_maxValue = iMax; }
	virtual void Serialize(CArchive& ar);

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
};



// CAttributeInfo: 
//    convenience class used by CAttributesDlg for manipulating attribute lists.
class CAttributeInfo : public CAttribute
{
public:
	LPCTSTR m_pszName;
	ATTRIBUTE_BASE_TYPE m_currentValue;
    BOOL m_bRemoved;
	void SetValue(int iValue)
	{
		ASSERT(iValue >= 0 && iValue <= m_maxValue);
		m_currentValue = iValue;
		m_bRemoved = FALSE;
	}
    void RemoveValue()
	{
		m_currentValue = m_defaultValue;
		m_bRemoved = TRUE;
	}
};

typedef CArray<CAttributeInfo,CAttributeInfo *> CAttributeResult;

class CAttributeTarget 
{
public:
	virtual int GetAttributeCount() = 0;
	virtual POSITION GetFirstAttribute() = 0;
	virtual void GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo) = 0;
};

#endif