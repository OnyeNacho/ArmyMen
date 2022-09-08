// TileSetOp.h : header file
//
#ifndef _TILESETOP_H_
#define _TILESETOP_H_
#include "TileSet.h"

typedef enum
{
	TSOP_NONE,  // must be first operation code
	TSOP_COPY,
	TSOP_CUT,
	TSOP_PASTE, // must be last operation code
} CTileOp;


class CTileSetOp : CObject
{
protected:
	CString m_clipID;                    // clipboard id for the tileset
    CTileOp m_opType;                    // the type of operation.
	CTileSet *m_pSrc;                    // source tile set

public:
	// attributes
	int m_iTileView;					 // TSV_xxx, view from which data was obtained
	CArray<int,int> m_tileIndex;   		 // original tile indices, one for each tile
	CArray<int,int> m_groupIndex;        // original group indices for each group
    CTileSet m_tileSet;                  // all the tileset data
	
	void SetType(CTileOp opType);
	CTileOp GetType() { return m_opType; }
	BOOL IsSameTileSet(CTileSet* pTileSet);
	CString GetClipID() { return m_clipID; }

	int GetTileCount() const { return m_tileSet.GetTileCount(); }
	int GetGroupCount() { return m_tileSet.GetGroupCount(); }
    CTileGroup *GetGroupAt(int iGroup) { return m_tileSet.GetGroupAt(iGroup); }

	// construction/destruction
	CTileSetOp();
	CTileSetOp(CTileOp opType, int iTileView, int nIndices, CTileSet *pSrcTileSet);
	BOOL Create(CTileOp opType, int iTileView, int nIndices, CTileSet *pSrcTileSet);
	DECLARE_SERIAL(CTileSetOp)

	virtual ~CTileSetOp();
	void DeleteContents();

	// operations
	virtual void Serialize(CArchive& ar);
	int FindTile(int nIndex);
	int AddTile(int nIndex);

	void AddGroup(int iGroup);
	void AddGroup(CTileGroup* group, int iGroupIndex = -1);
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
};

#endif