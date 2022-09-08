#include "stdafx.h"
#include "IFFFile.h"

/*
** Implements an IFF-type file format where each chunk consists of:
**     char typeID[4];
**     long dataSize;
**     char data[dataSize];
**
** With two changes:
**     1> uses 8086 byte order, not 68000
**     2> datasize includes any padding byte.
*/

CIFFFile::CIFFFile() 
{
	m_pStack = NULL;
	m_checksum = 0;
}

CIFFFile::CIFFFile(int hFile) 
: CFile(hFile)
{
	m_pStack = NULL;
	m_checksum = 0;
}

CIFFFile::CIFFFile(LPCTSTR lpszFileName, UINT nOpenFlags) 
: CFile(lpszFileName, nOpenFlags)
{
	m_pStack = NULL;
	m_checksum = 0;
}


CIFFFile::~CIFFFile()
{
	CIFFChunk *pChunk = m_pStack;
	while (pChunk)
	{
		CIFFChunk *pDoomed = pChunk;
		pChunk = pChunk->m_pNext;
        delete pDoomed;
	}
}

void CIFFFile::WriteLong(long value)
{
	// TBD: if this were really IFF we would need to byte swap here.
	CFile::Write(&value,4);
	m_checksum += value;
}

void CIFFFile::WriteShort(short value)
{
	// TBD: if this were really IFF we would need to byte swap here
	CFile::Write(&value,2);

	m_checksum += (ULONG) value;
}

ULONG CIFFFile::PushChunk(ULONG nID, ULONG lSize)
{
   CIFFChunk *pChunk = new CIFFChunk();
   ASSERT_NEW(pChunk);

   if ((lSize != eSizeUnknown) && (lSize & 1))
	   lSize += 1;

   pChunk->m_nID = nID;
   pChunk->m_lSize = lSize;
   pChunk->m_lOffset = GetPosition(); 

   WriteLong(nID);
   WriteLong(lSize);

   pChunk->m_pNext = m_pStack;
   m_pStack = pChunk;

   return nID;
}

void CIFFFile::PopChunk()
{
	CIFFChunk *pChunk = m_pStack;
	ASSERT(pChunk != NULL);

	ULONG pos = GetPosition();
	ULONG size = pos - (pChunk->m_lOffset + 8);

	if (size & 1) 
	{
		char zero = '\0';
		CFile::Write(&zero,1);
		size += 1;
	}

	if (pChunk->m_lSize == eSizeUnknown)
	{
		Seek(pChunk->m_lOffset + 4,CFile::begin);
		WriteLong(size);
		Seek(pos,CFile::begin);
	}
	else 
		ASSERT(size == pChunk->m_lSize);

	m_pStack = pChunk->m_pNext;
	delete pChunk;
}

void CIFFFile::PopChunk(ULONG nID)
{
	ASSERT(m_pStack != NULL);
	ASSERT(m_pStack->m_nID == nID);
	PopChunk();
}

void CIFFFile::PopChunkBuffer(char *buffer)
{
	CIFFChunk *pChunk = m_pStack;
	ASSERT(pChunk != NULL);

	ULONG pos = GetPosition();
//	ULONG size = pos - (pChunk->m_lOffset + 8);

	ASSERT(pChunk->m_lSize != eSizeUnknown);

	Seek(pChunk->m_lOffset + 8,CFile::begin);
	CFile::Write(buffer,pChunk->m_lSize);
	Seek(pos,CFile::begin);

	m_pStack = pChunk->m_pNext;
	delete pChunk;
}

void CIFFFile::PopChunkBuffer(ULONG nID, char *buffer)
{
	ASSERT(m_pStack != NULL);
	ASSERT(m_pStack->m_nID == nID);
	PopChunkBuffer(buffer);
}


void CIFFFile::WriteChunk(ULONG nID, const CString& str, BOOL bTerminate/*=TRUE*/)
{

	ULONG lLength = str.GetLength() + (bTerminate ? 1 : 0); 
	ULONG id = PushChunk(nID, lLength + (lLength & 1)); // pad to make even
	WriteHuge((LPCTSTR)str, lLength);
	CheckSumHuge((LPCTSTR)str, lLength);
	PopChunk(id);
}

void CIFFFile::CheckSumHuge(const char* lpBuf, DWORD dwCount )
{
	int	i;

	for (i=0; i<dwCount; i++)	{
		m_checksum += lpBuf[i];
	}
}
