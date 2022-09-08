#ifndef _CIFFFILE_H_
#define _CIFFFILE_H_

/*
** Interface to an IFF-type file format where each chunk consists of:
**     char typeID[4];
**     long dataSize;
**     char data[dataSize];
**
** With two changes:
**     1> uses 8086 byte order, not 68000
**     2> datasize includes any padding byte.
*/


class CIFFFile;

class CIFFChunk
{
   friend class CIFFFile;
   CIFFChunk *m_pNext;
   ULONG m_nID;        
   ULONG m_lSize;    // size in bytes of the data for this chunk (not including header)
   ULONG m_lOffset;  // file offset for the start of this chunk

   CIFFChunk() {m_pNext = NULL; m_nID = 0; m_lSize = 0; m_lOffset = 0;}
   virtual ~CIFFChunk() {}
};

class CIFFFile : public CFile
{
protected:
    CIFFChunk *m_pStack;

public:
	ULONG	m_checksum;
	enum { eSizeUnknown  = (ULONG)-1 };

	CIFFFile();
	CIFFFile(int hFile);
	CIFFFile(LPCTSTR lpszFileName, UINT nOpenFlags);
    virtual ~CIFFFile();

	// TBD: add read functions...
	ULONG MakeID(char a, char b, char c, char d)
	{
		return ((ULONG)d << 24) | ((ULONG)c << 16) | ((ULONG)b << 8) | ((ULONG)a);
	};
    virtual void WriteLong(long value);
	virtual void WriteLong(int a, int b, int c, int d) 
	{
		WriteLong(MakeID(a,b,c,d));
	}
	virtual void WriteShort(short value);
	virtual ULONG PushChunk(ULONG nID, ULONG lSize = eSizeUnknown);
	virtual ULONG PushChunk(char a, char b, char c, char d, ULONG lSize = eSizeUnknown) 
	{
		return PushChunk(MakeID(a,b,c,d),lSize);
	}
	void CheckSumHuge(const char* lpBuf, DWORD dwCount );

	virtual void PopChunkBuffer(ULONG nID, char *buffer);
	virtual void PopChunkBuffer(char *buffer);

	virtual void PopChunk(ULONG nID);
	virtual void PopChunk();
	virtual void WriteChunk(ULONG nID, const CString& str, BOOL bTerminate=TRUE);
	virtual void WriteChunk(int a, int b, int c, int d, const CString& str,BOOL bTerminate=TRUE) 
	{
		WriteChunk(MakeID(a,b,c,d), str, bTerminate);
	}

};

#endif