//	CSpriteSequence.h

//	CSpriteCatalog - simpler version of AnimEditor's CSequence, for use in games.

#ifndef CSpriteSequence_H
#define CSpriteSequence_H

class CSpriteSequence : public CObject
{
public:
	CSpriteSequence();

	DECLARE_SERIAL(CSpriteSequence)

	virtual ~CSpriteSequence();

// Attributes
public:
	CString		csName;
	long		lAction;
	int			iDirection;
	int			iSpeed;
	int			iMoveSpeed;
	int			iFrames;
	int			iHotspots;
	int			iActionFrame;

	//	Used always, replaces both arOrigins & arRLEOffsets
	CArray< int, int >							arIndexes;		//	index of bitmap in bitmap array

	//	Used when image is not RLE:
//	CTypedPtrArray< CPtrArray, CPoint* >		arOrigins;		//	Top left corner of sequence cels, in strip bitmap.
	//	Used when image is RLE:
//	CArray< int, int >							arRLEOffsets;	//	Offset of first bytes of sequence cels in catalog's RLE data.
	//	Used after RLE image has been imported:
//	CTypedPtrArray< CPtrArray, BYTE* >			arRLEOrigins;	//	Location in memory of first byte of sequence RLE data.

	CTypedPtrArray< CPtrArray, CPoint* >		arSizes;		//	Width and height of images.
	CTypedPtrArray< CPtrArray, CPoint* >		arOffsets;		//	Primary hotspots of all sequence cels.
	CTypedPtrArray< CPtrArray, CPoint* >		arHotspots;		//	Secondary hotspots, stored as pseudo two-dimensional array.

	BOOL										bSerializeRLE;	//	Flag used by serialize, set by caller.


// Operations
public:
	virtual void	Serialize( CArchive& ar );
	int				GetFrameCount();
//	void			Set_arRLEOrigins( BYTE* pCatalogOrigin );
};

inline int CSpriteSequence::GetFrameCount()
{	return iFrames;		}

#endif