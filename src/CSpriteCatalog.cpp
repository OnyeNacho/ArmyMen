//	CSpriteCatalog.cpp

#include "stdafx.h"

#include "CSpriteCatalog.h"


extern BYTE fixed_trans_table[];

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////


IMPLEMENT_SERIAL(CSpriteCatalog, CObject, 1)

CSpriteCatalog::CSpriteCatalog()
{
	m_pSprites = NULL;
	iSeqs = 0;
	m_iNumBitmaps = 0;
	m_pCommandList = NULL;
	load_flags = 0;
	bSerializeRLE = FALSE;
}


CSpriteCatalog::~CSpriteCatalog()
{
	//	Delete created SpriteSequences.
	int j = arSeqs.GetUpperBound();
	for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
		delete arSeqs[ i ];

	if (m_pSprites)	{
		FreeSprites();
		delete [] m_pSprites;
	}

	if (m_pCommandList)	{
		FreeCommands();
		m_pCommandList = NULL;
	}
}

// relase all but bitmaps
void CSpriteCatalog::ReleaseSeqs()
{
	//	Delete created SpriteSequences.
	for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
		delete arSeqs[ i ];

	arSeqs.RemoveAll();
}

void CSpriteCatalog::SetFlags( long flags )
{
	load_flags = flags;
}

//-----------------------------------------------------------------------------------------------------------------
void CSpriteCatalog::Serialize( CArchive& ar )
{
	int iAXRVersion;
	int read;

	ASSERT(ar.IsLoading());

	ar >> iAXRVersion;
	ar >> csName >> iSeqs;
	arSeqs.SetSize( iSeqs );

	arSeqs.Serialize( ar );

	char szHeader[4];
	read = ar.Read( szHeader, 4 );
	if( strncmp(szHeader,"AXR:",4) == 0 )
	{
		load_flags |= BM_RLE_ONLOAD;
		if( load_flags & BM_NOTRANSLATE )
		{
			load_flags |= BM_TRLE;
		}
		else
		{
			load_flags &= ~BM_NOTRANSLATE;
  			load_flags |= BM_WRLE;
		}
	}

	int iVersion;
	read = ar.Read( &iVersion, sizeof( iVersion ) );
	ASSERT(iVersion == 1);

	//	Read in BMP information from the rest of the file.
	VERIFY( ReadBMPs( ar ) );
}


//-----------------------------------------------------------------
// One-to-One BITMAPINFO Struct ( Used below, in ReadBMP() )
//-----------------------------------------------------------------
struct BITMAPINFO_1TO1_DUPED
{
  BITMAPINFOHEADER  bmiHeader;
  WORD              bmiColors[256];

                    BITMAPINFO_1TO1_DUPED(const BITMAPINFOHEADER &bmih);
                    operator BITMAPINFO*()
                      { return (BITMAPINFO*)this; }
};

BITMAPINFO_1TO1_DUPED::BITMAPINFO_1TO1_DUPED(const BITMAPINFOHEADER
  &bmihToCopy)
{
  ::CopyMemory(&bmiHeader, &bmihToCopy, sizeof(BITMAPINFOHEADER));
  for (int i = 0; i < 256; i++)
    bmiColors[i] = i;
}

int data_size = 0;
int bitmap_size = 0;

//-----------------------------------------------------------------------------------------------------------------
BOOL CSpriteCatalog::ReadBMPs( CArchive& ar )
{
	int size;

	ASSERT(ar.IsLoading());

	// read the number of bitmaps
	ar >> m_iNumBitmaps;

	//	Read the file header.
	BITMAPFILEHEADER bmpFileHeader;
	DWORD dwBytesRead = ar.Read( &bmpFileHeader, sizeof( BITMAPFILEHEADER ) );
	ASSERT(dwBytesRead == sizeof( BITMAPFILEHEADER ));
	ASSERT(bmpFileHeader.bfType == 0x4142);

	//	Read the bitmapinfo header.
	BITMAPINFO_256 *pbmpInfo = new BITMAPINFO_256;
	dwBytesRead = ar.Read( &pbmpInfo->bmiHeader, sizeof( BITMAPINFOHEADER ) );
	ASSERT(dwBytesRead == sizeof( BITMAPINFOHEADER ));
	
	//	Verify 8 bpp (256 color).
	ASSERT( pbmpInfo->bmiHeader.biBitCount == 8 );
	//	Verify no compression.
	ASSERT( pbmpInfo->bmiHeader.biCompression == BI_RGB );

	int nColors = pbmpInfo->bmiHeader.biClrUsed;
	if( nColors == 0 )
		nColors = pbmpInfo->bmiHeader.biClrUsed = 256;

	::ZeroMemory( pbmpInfo->bmiColors, 256 * sizeof( RGBQUAD ) );

	VERIFY( pbmpInfo->bmiHeader.biSize == sizeof( BITMAPINFOHEADER ) );

	//	Read the color info.
	dwBytesRead = ar.Read( pbmpInfo->bmiColors, nColors * sizeof( RGBQUAD ) );
	ASSERT(dwBytesRead == (nColors * sizeof( RGBQUAD )));

	data_size += m_iNumBitmaps*sizeof(SPRITE);
	m_pSprites = new SPRITE[m_iNumBitmaps];

	for (int bm=0; bm<m_iNumBitmaps; bm++)	{
		LOADBITMAP lbitmap;

		lbitmap.flags = load_flags;

		dwBytesRead = ar.Read( &pbmpInfo->bmiHeader, sizeof( BITMAPINFOHEADER ) );
		ASSERT(dwBytesRead == sizeof( BITMAPINFOHEADER ));
		int iHeight = pbmpInfo->bmiHeader.biHeight;
		int iWidth = pbmpInfo->bmiHeader.biWidth;
		int bmsize = pbmpInfo->bmiHeader.biSizeImage;

		ASSERT(iHeight <= 480);
		ASSERT(iWidth <= 640);

		BYTE *pBits = new BYTE[bmsize];

		DWORD dwBMBytesRead = ar.Read(pBits, bmsize );
		ASSERT((DWORD)dwBMBytesRead == (DWORD)bmsize);
		ASSERT(bmsize);

		if ( !(size = MakeSprite(&m_pSprites[bm], pbmpInfo, pBits, &lbitmap, fixed_trans_table)) )
			TRACE("ERROR: MakeSprite failed: [%s:%d]\n", __FILE__, __LINE__ );

		// set the use self rect flag for this sprite
		m_pSprites[bm].sprite_flags |= SP_USESELFRECT;
		if( load_flags & BM_USEBMPASMASK )
			m_pSprites[bm].sprite_flags |= SP_USEBMPASMASK;

		if( load_flags & BM_ANIM_SHADOW )
		{
			dwBytesRead = ar.Read( &bmsize, sizeof(LONG) );
			ASSERT(dwBytesRead == sizeof(LONG));

			if( bmsize > 0 )
			{
				ASSERT(!m_pSprites[bm].pShadow);
				m_pSprites[bm].pShadow = (BYTE *)malloc(bmsize);
				if( !(m_pSprites[bm].pShadow) )
				{
					TRACE( "ERROR: malloc failed in animation shadow load \n" );
				}
				else
				{
					dwBytesRead = ar.Read( m_pSprites[bm].pShadow, bmsize );
					bitmap_size += bmsize;
				}
			}
		}

		bitmap_size += size;

		delete [] pBits;
	}

	delete (BITMAPINFO_256*)pbmpInfo;

	return TRUE;
}


void CSpriteCatalog::FreeSprites( )
{
	for (int bm=0; bm<m_iNumBitmaps; bm++)	{
		FreeSprite(&m_pSprites[bm]);
	}
}

int seq_size = 0;
int frame_size =0;

void CSpriteCatalog::ProcessAnim(COMMAND_LIST *pCommandList)	{
	SHORT commands = pCommandList->commands;
	COMMAND *pCommand = pCommandList->command_array;
	SHORT	action;
	SHORT	direction;
	int	frames;			// frames in this sequence

	m_pCommandList = pCommandList;

	int num = arSeqs.GetSize();
	for( int seq = 0; seq < num; seq++ )	{
		action = (SHORT) arSeqs[seq]->lAction;
		direction = (SHORT) arSeqs[seq]->iDirection;
		frames = arSeqs[seq]->iFrames;

		for (int i=0; i<commands; i++)	{
			if (pCommand[i].command_now == action)	{
#ifdef SPRITE_DEBUG
				TRACE("Found action %d from sequence %d in command array\n", action, seq);
#endif
				if (pCommand[i].seq == NULL)	{
#ifdef SPRITE_DEBUG
					TRACE("Allocating new sequence\n");
#endif
					seq_size += sizeof(SEQUENCE);
					pCommand[i].seq = new SEQUENCE;
					pCommand[i].copy_seq = FALSE;						// this is not a copy of another sequence
					ZeroMemory(pCommand[i].seq, sizeof(SEQUENCE));
					pCommand[i].seq->frames = frames;
					pCommand[i].seq->base_velocity = -1;
				}

				if (frames != pCommand[i].seq->frames)
					TRACE("ERROR in number of frames for action %d (%d found, should be %d)\n", action, frames, pCommand[i].seq->frames);

				pCommand[i].seq->directions++;
			}
		}

	}


	int	speed;			// frames per second
	int	hotspots;		// number of hotspots
	int	duration;		// milliseconds
	int	my_durations[LAST_COMMAND];
	int	velocity;		// pixels/seconds
	SHORT dirs;
	FRAME	*pFrameList,
			*pFrame;

	for( seq = 0; seq < LAST_COMMAND; seq++ )
		my_durations[seq] = -1;

	num = arSeqs.GetSize();
	for( seq = 0; seq < num; seq++ )	{
		action = (SHORT) arSeqs[seq]->lAction;
		direction = (SHORT) arSeqs[seq]->iDirection;
		speed = arSeqs[seq]->iSpeed;
		frames = arSeqs[seq]->iFrames;
		hotspots = arSeqs[seq]->iHotspots;
		velocity = arSeqs[seq]->iMoveSpeed;
		duration = 1000/speed;		// duration in milliseconds
		if (action == STAND_COMMAND)
		{
			velocity = 0;
			duration = 0;
		}

		for (int i=0; i<commands; i++)	{
			if (pCommand[i].command_now == action)	{
				if (pCommand[i].seq != NULL)	{
					dirs = pCommand[i].seq->directions;
					direction = direction / (32/dirs);

					if (direction == 0 )	{
						pCommand[i].seq->base_velocity = velocity;
						pCommand[i].seq->action_frame = arSeqs[seq]->iActionFrame;
						if (my_durations[action] != -1)
							if (my_durations[action] != duration)
								TRACE("Duration mismatch: action %d, direction %d\n",action,direction);
						my_durations[action] = duration;
					}
					else	{
						if (pCommand[i].seq->base_velocity != -1)	{
							if (pCommand[i].seq->base_velocity != velocity)
								;
//							TRACE("Velocity error: action %d, direction %d\n",action,direction);
						}

						if (my_durations[action] == -1)	{
//							TRACE("Duration error: action %d, direction %d\n",action,direction);
							if (action == STAND_COMMAND)
								TRACE("Duration error: action %d, direction %d\n",action,direction);
							my_durations[action] = duration;
						}
					}

					if (pCommand[i].seq->frame_list == NULL)	{
						switch(dirs)	{
							case 32:
							case 16:
							case 8:
							case 4:
							case 2:
							case 1:
								break;
							default:
								TRACE("Illegal number of directions (%d) for action %d\n", dirs, action);
								break;
						}

						pCommand[i].seq->divisor = 256 / dirs;
						pCommand[i].seq->frame_list = new FRAME[frames*dirs];
						frame_size += sizeof(FRAME)*frames*dirs;
						ZeroMemory(pCommand[i].seq->frame_list, sizeof(FRAME)*frames*dirs);
#ifdef SPRITE_DEBUG
						TRACE("Allocating new frame_list\n");
#endif

						pCommand[i].seq->spriteArray = m_pSprites;
						pCommand[i].seq->max_index = m_iNumBitmaps-1;
					}

					pFrameList = pCommand[i].seq->frame_list;
					pFrame = &pFrameList[direction*frames];					
					
					for (int j=0; j<frames; j++)	{
						if (pFrame[j].time != 0)	{
							TRACE("Duplicate action/direction: %d/%d\n",action,direction);
						}

						pFrame[j].time = my_durations[action];

						CPoint* pptOffset = arSeqs[seq]->arOffsets[j];

						// get from primary hotspot
						pFrame[j].primary_hotspot.x = (short)pptOffset->x;
						pFrame[j].primary_hotspot.y = (short)pptOffset->y;

						if (pFrame[j].primary_hotspot.x > 192 || pFrame[j].primary_hotspot.x < -192)	{
							TRACE("Bad x primary hotspot in sequence: %d\n",pFrame[j].primary_hotspot.x);
							pFrame[j].primary_hotspot.x = 0;
						}
						if (pFrame[j].primary_hotspot.y > 192 || pFrame[j].primary_hotspot.y < -192)	{
							TRACE("Bad y primary hotspot in sequence: %d\n",pFrame[j].primary_hotspot.y);
							pFrame[j].primary_hotspot.y = 0;
						}

						if (hotspots > 0)	{
							CPoint* pptHotspot = arSeqs[seq]->arHotspots[j*hotspots];
							pFrame[j].secondary_hotspot.x = (short)(pptHotspot->x - pptOffset->x);
							pFrame[j].secondary_hotspot.y = (short)(pptHotspot->y - pptOffset->y);
						}
						else	{
							pFrame[j].secondary_hotspot.x = 0;
							pFrame[j].secondary_hotspot.y = 0;
						}

						pFrame[j].sprite_index = arSeqs[seq]->arIndexes[j];
					}
				}
				else	{
					TRACE("ERROR: no sequence allocated");
				}
			}
		}
	}
	ReleaseSeqs();
}


void CSpriteCatalog::FreeCommands( )
{
	SHORT commands = m_pCommandList->commands;
	COMMAND *pCommand = m_pCommandList->command_array;

	for (int i=0; i<commands; i++)	{
		if (pCommand[i].seq != NULL && !pCommand[i].copy_seq)	{
			if (pCommand[i].seq->frame_list != NULL)
				delete [] pCommand[i].seq->frame_list;
			delete pCommand[i].seq;
		}
		pCommand[i].seq = NULL;
		pCommand[i].copy_seq = FALSE;
	}
}

void ClearTotals( )
{
	data_size = 0;
	bitmap_size = 0;
	seq_size = 0;
	frame_size = 0;
}

