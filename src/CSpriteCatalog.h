//	CSpriteCatalog.h

//	CSpriteCatalog - simpler version of AnimEditor's CAnimEditorDoc, for use in games.

#ifndef CSpriteCatalog_H
#define CSpriteCatalog_H

#include "CSpriteSequence.h"
#include "anim.h"

//struct BITMAPINFO_256
//{
//  BITMAPINFOHEADER  bmiHeader;
//  RGBQUAD           bmiColors[256];
//};

class CSpriteCatalog : public CObject
{
public:
	CSpriteCatalog();

	DECLARE_SERIAL(CSpriteCatalog)
	
	virtual ~CSpriteCatalog();

// Attributes
protected:
	int				m_iNumBitmaps;
	SPRITE*			m_pSprites;
	COMMAND_LIST	*m_pCommandList;

	long		load_flags;

public:
	CString		csName;			//	User-assigned name of catalog.
	int			iSeqs;			//	Number of sprite sequences.
	CTypedPtrArray< CObArray, CSpriteSequence* >	arSeqs;			//	Array of sprite sequences.

	BOOL		bSerializeRLE;	//	Flag used by serialize, set by caller.

// Operations
protected:
	void			FreeSprites();
	void			FreeCommands();

public:
	virtual void	Serialize( CArchive& ar );
	BOOL			ReadBMPs( CArchive& ar );
	void			ProcessAnim(COMMAND_LIST *pCommandList);
	void			SetFlags( long flags );
	void			ReleaseSeqs();
};

extern void ClearTotals();

#endif