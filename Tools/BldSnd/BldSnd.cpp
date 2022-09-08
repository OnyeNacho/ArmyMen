//=======================================================================
//	FILE:		BldSnd.cpp
//
//	CREATED:	04/29/96
//
//	PROJECT:	ArmyMen
//
//	AUTHOR:		Andrew J Burgess
//
//=======================================================================
//				Copyright (c) 1996, The 3DO Company
//=======================================================================
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	TRACE	printf

//=======================================================================
//	
//=======================================================================

#define	FALSE			0
#define	TRUE			1

typedef	char			BOOL;

#define	SND_MAX_SOUNDS		256
#define	SND_MAX_BUF_SIZE	1024
#define	SND_NAME_MAX		64
#define	SND_MAX_TEXT_LEN	128

#define	SND_ID_OFFSET	1000

#define	IDX_NUM1_STATE	0
#define	IDX_NUM2_STATE	1
#define	IDX_SEP_STATE	2

#define	SND_NULL_ID			~0L
#define	SND_NULL_OFFSET		~0L

//      VTXT =         T X T V		Voice Stream Text chunk block
#define VTXT_ID		0x54585456
//      CPYR =         R Y P C		CopyRight Chunk block
#define CPYR_ID		0x52595043
//      EODF =         F D O E		End Of Data File chunk block
#define EODF_ID		0x46444F45

typedef struct
{
			 char	soundName[SND_NAME_MAX+1];		// Sound ID name
			 char	soundText[ SND_MAX_TEXT_LEN ]; // text eqivalent of voice stream
	unsigned long	soundID;			// Sound ID number
	unsigned long	offset;				// offset from base of file to sound
} SND_H_ENTRY;

typedef struct
{
	unsigned long	soundID;			// Sound ID number
	unsigned long	offset;				// offset from base of file to sound
} SND_ENTRY;

typedef struct
{
			 char	version[4];					// APP version identifier
	unsigned long	numberOfSounds;				// number of sound IDs in this file
	SND_ENTRY		sounds[ SND_MAX_SOUNDS ];	// actual sound information
	SND_ENTRY		endOfTable;					// End of Table Marker
} SND_HEADER;

typedef struct
{
			 char	riffID[4];
	unsigned long	riffSize;
			 char	formatID[4];
} RIFF_HEADER;

typedef struct
{
			 char	chunkID[4];
	unsigned long	chunkSize;
} CHUNK_HEADER;

//=======================================================================
//	
//=======================================================================
FILE*			OPTfile;
FILE*			SNDfile;
FILE*			WAVfile;
FILE*			TMPfile;
FILE*			Hfile;
FILE*			Sfile;
FILE*			Tfile;
FILE*			LOGfile;

char			OPTfileName[SND_NAME_MAX];
char			SNDfileName[SND_NAME_MAX];
char			TEXTfileName[SND_NAME_MAX];
char			HfileName[SND_NAME_MAX];
char			SfileName[SND_NAME_MAX];
char			TfileName[SND_NAME_MAX];

char			SNDcommandLine[132];
char			TEXTstring[132];
unsigned		SNDnumber;
unsigned long	SNDoffset;
unsigned long	SNDidNumber;

BOOL			SNDactive;
BOOL			SNDuseID;
char			SNDactiveSndFile[SND_NAME_MAX];
char			SNDactiveSndName[SND_NAME_MAX];
unsigned		SNDactiveSndCnt;
unsigned		SNDactiveSubIdx;

SND_HEADER		SNDheader;
SND_H_ENTRY		SNDhHeader[ SND_MAX_SOUNDS ];

char			SNDlogMessage[256];

//=======================================================================
//	
//=======================================================================

void	main( int argc, char** argv );
void	Init( void );
void	Terminate( void );
BOOL	ProcessArgs( int argc, char** argv );
BOOL	CommandProcessing( void );
BOOL	CommandSndOutput( char* commandPtr, unsigned lineCount );
BOOL	CommandSndNum( char* commandPtr, unsigned lineCount );
BOOL	CommandSndFile( char* commandPtr, unsigned lineCount );
BOOL	CommandSndName( char* commandPtr, unsigned lineCount );
BOOL	CommandSndCnt( char* commandPtr, unsigned lineCount );
BOOL	CommandSndIdx( char* commandPtr, unsigned lineCount );
BOOL	CommandSndTextOutput( char* commandPtr, unsigned lineCount );
BOOL	CommandSndText( char* commandPtr, unsigned lineCount );
BOOL	LoadSound( void );
BOOL	SaveSounds( void );
BOOL	CreateHFile( void );
void	OutputHeader( void );
void	OutputFooter( void );
char*	StripWhiteSpace( char* string );
char*	SkipToWhiteSpace( char* string );
void	MakeLegalChar( char* pLetters, unsigned nIdx );
BOOL	sndFindWaveformatex( FILE* pSndFile );
BOOL	sndFindSample( FILE* pSndFile, unsigned nSize );

int	AcquireString( char* commandPtr );
void LogMsg( char* pLogMessage, BOOL bToScreen );
void ErrorMsg( char* pLogMessage, BOOL bToLog );

//=======================================================================
//	
//=======================================================================
void	main( int argc, char** argv )
{
	// Initialize the application
	Init();

	// Process the command line arguments
	if ( ProcessArgs( argc, argv ) )
		goto abortApp;

	// Process the build file <filename>.opt
	if ( CommandProcessing( ) )
		goto abortApp;

	// complete
	LogMsg( "Sound build completed!\n", TRUE );
	goto exit;

	// build aborted
abortApp:
	LogMsg( "Sound build failed!\n", TRUE );
exit:
	Terminate();
	return;
}

//=======================================================================
//=======================================================================
void	Init( void )
{
	char		timeBuffer[32];
	time_t		currentTime;
	struct tm*	localTime;
	int			count;
	unsigned	snd;
	unsigned	letter;

	// initialize application globals
	OPTfile              = NULL;
	SNDfile              = NULL;
	WAVfile              = NULL;
	TMPfile              = NULL;

	OPTfileName[0]       = '\0';
	SNDfileName[0]       = '\0';
	HfileName[0]         = '\0';
	SfileName[0]         = '\0';

	SNDcommandLine[0]    = '\0';
	SNDnumber            = 0;
	SNDoffset            = sizeof(SND_HEADER);
	SNDidNumber          = 0;

	SNDactive            = FALSE;
	SNDuseID             = FALSE;
	SNDactiveSndFile[0]  = '\0';
	for( snd=0; snd<SND_NAME_MAX; ++ snd )
		SNDactiveSndName[snd]  = '\0';
	SNDactiveSndCnt      = 1;
	SNDactiveSubIdx      = 0;

	// initialize the header
	SNDheader.version[0]     = 'V';
	SNDheader.version[1]     = '0';
	SNDheader.version[2]     = '.';
	SNDheader.version[3]     = '0';
	SNDheader.numberOfSounds = (unsigned long)0;
	for( snd=0; snd<SND_MAX_SOUNDS; ++snd )
	{
		SNDheader.sounds[ snd ].soundID = (unsigned long)SND_NULL_ID;
		SNDheader.sounds[ snd ].offset  = (unsigned long)SND_NULL_OFFSET;
	}

	// insert the end of table marker
	SNDheader.endOfTable.soundID = 0x20454854;		// "The "
	SNDheader.endOfTable.offset  = 0x444e4520L;		// " end"

	// initialize the .H file header
	for( snd=0; snd<SND_MAX_SOUNDS; ++snd )
	{
		// initialize the .H file header
		for( letter=0; letter<=SND_NAME_MAX; ++letter )
			SNDhHeader[ snd ].soundName[letter] = '\0';

		SNDhHeader[ snd ].soundName[0] = 'N';
		SNDhHeader[ snd ].soundName[1] = 'U';
		SNDhHeader[ snd ].soundName[2] = 'L';
		SNDhHeader[ snd ].soundName[3] = 'L';
		SNDhHeader[ snd ].soundID      = (unsigned long)SND_NULL_ID;
		SNDhHeader[ snd ].offset       = (unsigned long)SND_NULL_OFFSET;
	}

	// open the .log file for debugging
	if ( (LOGfile = fopen( "sounds.log", "w" )) == NULL )
	{
		// report an error
		fprintf( stderr, "ERROR: failed to open log file: \"sounds.log\"\n\n" );
		fflush( stderr );
	}
	else
	{

		// Get the current time
		currentTime = time( NULL );
		localTime   = localtime( &currentTime );
		count       = strftime( timeBuffer, 32, "%#c", localTime );
		sprintf( SNDlogMessage, "BLDSND %s %s\n\n", SNDheader.version,timeBuffer );
		LogMsg( SNDlogMessage, TRUE );
	}

}

//=======================================================================
//=======================================================================
void	Terminate( void )
{
	// close the LOG file
	if ( LOGfile )
	{
		fclose( LOGfile );
	}
}

//=======================================================================
//=======================================================================

BOOL	ProcessArgs( int argc, char** argv )
{
	BOOL		error = FALSE;
	char*		namePtr;

	// make sure we've gotten enough arguments
	if ( argc <= 1 )
	{
		// no .opt file provided
		error = TRUE;
		ErrorMsg( "useage:	BldSnd <filename>.opt\n\n", TRUE );
		goto exit;
	}

	// open the .opt file for processing
	namePtr = argv[1];
	strcpy( OPTfileName, namePtr );
	if ( (OPTfile = fopen( OPTfileName, "rb" )) == NULL )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: failed to open file: \"%s\"\n\n",
				OPTfileName );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
		goto exit;
	}
	else
	{
		sprintf( SNDlogMessage, "Opened %s...\n", OPTfileName );
		LogMsg( SNDlogMessage, FALSE );
	}

	// open the .tmp file for processing
	if ( (TMPfile = (FILE*)fopen( "ASD00000.000", "wb" )) == NULL )
	{
		// report an error
		ErrorMsg( "ERROR: failed to open file: \"ASD00000.000\"\n\n", TRUE );
		error = TRUE;
		goto exit;
	}
	else
	{
		LogMsg( "Opened ASD00000.000...\n", FALSE );
	}

exit:
	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandProcessing( void )
{
	BOOL		error = FALSE;
	BOOL		done  = FALSE;
	unsigned	lineCount = 0;
	char*		cmdPtr;
	char		command[132];
	char		commandLine[132];

	// loop until file is completely read
	while( !done && !error )
	{
		// try a line
		++lineCount;

		// read in a line of data from the file
		if ( fgets( commandLine, 132, OPTfile ) == NULL )
		{
			// check to see what kind of error, if at all
			if ( feof( OPTfile ) )
			{
				// see if we still have a sound active
				if ( SNDactive )
					LoadSound();

				// combine the header and the sound data
				SaveSounds();

				// report that we've finished
				LogMsg( "EOF reached\n\n", TRUE );
				done = TRUE;
			}
			else
			{
				// report an error of some sort
				sprintf( SNDlogMessage, "ERROR: line #d: failed to retrieve command line\n\n",
						 lineCount );
				ErrorMsg( SNDlogMessage, TRUE );
				error = TRUE;
			}
		}
		else
		{
			// Parse the line to see what type of command it is
			// strip all leading white space
			cmdPtr = StripWhiteSpace( commandLine );
			if ( *cmdPtr != '\n' )
			{
				// now request the command name
				if ( sscanf( cmdPtr, "%s", command ) != EOF )
				{
					unsigned	len;

					// advance pointer past command name
					len     = strlen( command );
					cmdPtr += len;

					// determine which command it was
					if ( command[0] == '#' )						// comment
						error = FALSE;
					else
					if ( strcmp( "SND_OUTPUT", command ) == 0 )		// Specify the output filename
						error = CommandSndOutput( cmdPtr, lineCount );
					else
					if ( strcmp( "SND_INUM", command ) == 0 )		// Specify the ID number
						error = CommandSndNum( cmdPtr, lineCount );
					else
					if ( strcmp( "SND_FILE", command ) == 0 )		// open a sound file
						error = CommandSndFile( cmdPtr, lineCount );
					else
					if ( strcmp( "SND_NAME", command ) == 0 )		// sound id name
						error = CommandSndName( cmdPtr, lineCount );
					else
					if ( strcmp( "SND_CNT", command ) == 0 )		// number of sounds linked
						error = CommandSndCnt( cmdPtr, lineCount );	// to the sound name
					else
					if ( strcmp( "SND_IDX", command ) == 0 )		// index of first linked
						error = CommandSndIdx( cmdPtr, lineCount );	// sound
					else
					if ( strcmp( "SND_TEXT_OUTPUT", command ) == 0 )	// output file for SND Text
						error = CommandSndTextOutput( cmdPtr, lineCount );
					else
					if ( strcmp( "SND_TEXT", command ) == 0 )		// SND text string
						error = CommandSndText( cmdPtr, lineCount );
					else
					{
						// ERROR: unknown command
						sprintf( SNDlogMessage, "ERROR: line #d: unknown command \"%s\"\n\n",
								 lineCount, command );
						ErrorMsg( SNDlogMessage, TRUE );
						error = TRUE;
					}
				}
			}
		}
	}

	// check to see if there are any active sounds
	if ( SNDactive )
		LoadSound();

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndOutput( char* commandPtr, unsigned lineCount )
{
	char*	cmdPtr;
	char*	namePtr;
	long	number;
	char	fileName[32];
	BOOL	error  = FALSE;

	// DEBUG
	LogMsg( "SND_OUTPUT: ", TRUE );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get the name of the new wave file
	if ( sscanf( cmdPtr, "%s", fileName ) != EOF )
	{
		// load the filename

		namePtr = fileName;
		number  = 0;
		while( (*namePtr != '.') && (*namePtr ) && (number<8) )
		{
			SNDfileName[ number++ ] = *namePtr;
			++namePtr;
		}
		strcat( SNDfileName, ".asd" );

		// see if there ID number at end of the filename
		--namePtr;
		number = *namePtr - '0';
		if ( number > 9 )
			number = 0;
		SNDidNumber = (number * SND_ID_OFFSET);

		// DEBUG
		sprintf( SNDlogMessage, "\"%s\"\n", SNDfileName );
		LogMsg( SNDlogMessage, TRUE );
		sprintf( SNDlogMessage, "\"%s\"	ID start: %d\n", SNDfileName, SNDidNumber );
		LogMsg( SNDlogMessage, FALSE );
	}
	else
	{
		// ERROR: failed to retrieve input file name
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_OUTPUT name\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndNum( char* commandPtr, unsigned lineCount )
{
	char*		cmdPtr;
	BOOL		error = FALSE;

	// DEBUG
	LogMsg( "SND_INUM: ", TRUE );
	fflush( stdout );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get starting index number
	if ( sscanf( cmdPtr, "%d", &SNDidNumber ) == EOF )
	{
		// ERROR: failed to retrieve sound sub count
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_INUM\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}
	else
	{
		// DEBUG
		sprintf( SNDlogMessage, "%d\n", SNDidNumber );
		LogMsg( SNDlogMessage, TRUE );
	}

	if ( !error )
		SNDactive = TRUE;

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndFile( char* commandPtr, unsigned lineCount )
{
	char*	cmdPtr;
	char*	tmpPtr;
	char*	tmp2Ptr;
	int		len;
	BOOL	error  = FALSE;

	// check to see if there is already a sound active
	if ( SNDactive )
		LoadSound();

	// DEBUG
	LogMsg( "SND_FILE: ", TRUE );

	// close the currently open file
	if ( WAVfile )
		fclose( WAVfile );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get the name of the new wave file
	if ( sscanf( cmdPtr, "%s", SNDactiveSndFile ) != EOF )
	{
		// now open the new wav file
		if ( (WAVfile = (FILE*)fopen( SNDactiveSndFile, "rb" )) == NULL )
		{
			// report an error
			sprintf( SNDlogMessage, "ERROR: failed to open file: \"%s\"\n\n",
					SNDactiveSndFile );
			ErrorMsg( SNDlogMessage, TRUE );
			error = TRUE;
			goto exit;
		}

		// See if we already have an ID name, if not, use this file
		// name to derive the ID name. Look for a '.' or null.
		if ( SNDactiveSndName[0] == '\0' )
		{
			// get the length of the file nam
			len = strlen(SNDactiveSndFile);
			
			// start from the end and locate the either a '.' or a '\'
			tmpPtr = SNDactiveSndFile + len - 1;
			while( (*tmpPtr != '.') && (*tmpPtr != '\\') && (tmpPtr >= SNDactiveSndFile) )
				--tmpPtr;

			// why did we stop
			if ( *tmpPtr == '.' )	// find head of string
			{
				tmp2Ptr = tmpPtr;
				--tmpPtr;
				while( (*tmpPtr != '.') && (*tmpPtr != '\\') && (tmpPtr >= SNDactiveSndFile) )
					--tmpPtr;
				++tmpPtr;

				// now copy in the filename	
				strncpy( SNDactiveSndName, tmpPtr, (tmp2Ptr - tmpPtr) );
			}
			else
			if( *tmpPtr == '\\' )		// no suffix just use tmp ptr
			{
				strncpy( SNDactiveSndName, tmpPtr,
						 (len - ((tmpPtr - SNDactiveSndFile)-1)) );
			}
			else					// use the whole string
			{
				strncpy( SNDactiveSndName, SNDactiveSndFile, len );
			}
		}

		// DEBUG
		sprintf( SNDlogMessage, "\"%s\"\n", SNDactiveSndFile );
		LogMsg( SNDlogMessage, TRUE );
	}
	else
	{
		// ERROR: failed to retrieve input file name
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_FILE name\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}

	if ( !error )
		SNDactive = TRUE;
exit:
	return( error );
}


//=======================================================================
//=======================================================================
BOOL	CommandSndName( char* commandPtr, unsigned lineCount )
{
	char*		cmdPtr;
	BOOL		error = FALSE;
	unsigned	snd   = SNDheader.numberOfSounds;

	// DEBUG
	LogMsg( "SND_NAME: ", TRUE );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get the name of the new wave file
	if ( sscanf( cmdPtr, "%s", SNDactiveSndName ) == EOF )
	{
		// ERROR: failed to retrieve sound ID name
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_NAME\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}
	else
	{
		// DEBUG
		sprintf( SNDlogMessage, "\"%s\"\n", SNDactiveSndName );
		LogMsg( SNDlogMessage, TRUE );
	}

	if ( !error )
		SNDactive = TRUE;
	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndCnt( char* commandPtr, unsigned lineCount )
{
	char*		cmdPtr;
	BOOL		error = FALSE;
	unsigned	snd   = SNDheader.numberOfSounds;

	// DEBUG
	LogMsg( "SND_CNT: ", TRUE );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get the name of the new wave file
	if ( sscanf( cmdPtr, "%d", &SNDactiveSndCnt ) == EOF )
	{
		// ERROR: failed to retrieve sound sub count
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_CNT\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}
	else
	{
		// DEBUG
		sprintf( SNDlogMessage, "%d\n", SNDactiveSndCnt );
		LogMsg( SNDlogMessage, TRUE );
	}

	if ( !error )
		SNDactive = TRUE;	// mark this sound as active

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndIdx( char* commandPtr, unsigned lineCount )
{
	unsigned	startIdx    = 0;
	unsigned	endIdx      = 0;
	BOOL		done        = FALSE;
	BOOL		error       = FALSE;
	BOOL		readyToLoad = FALSE;
	BOOL		isARange    = FALSE;
	unsigned	snd         = SNDheader.numberOfSounds;
	char*		tokenPtr    = commandPtr;
	unsigned	idxState    = IDX_NUM1_STATE;


	// DEBUG
	LogMsg( "SND_IDX: ", TRUE );

	// mark this sound as active
	SNDactive = TRUE;

	// strip all leading white space
	tokenPtr = StripWhiteSpace( commandPtr );
	if ( *tokenPtr == '\n' )
	{
		// ERROR: no index values present
		ErrorMsg( "ERROR: SND_IDX invalid index list\n\n", TRUE );
		error = TRUE;
	}

	// get the snd index values
	while( (*tokenPtr != '\n') && !error )
	{
		// strip all leading white space
		tokenPtr = StripWhiteSpace( tokenPtr );

		switch( idxState )
		{
		case IDX_NUM1_STATE:
			if ( *tokenPtr != '\n' )
			{
				// read in a numerical value
				if ( sscanf( tokenPtr, "%d", &startIdx ) == EOF )
				{
					// ERROR: failed to retrieve sound sub count
					sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_IDX\n\n",
							 lineCount );
					ErrorMsg( SNDlogMessage, TRUE );
					error = TRUE;
				}
				else
				{
					// DEBUG
					sprintf( SNDlogMessage, "%d ", startIdx );
					LogMsg( SNDlogMessage, TRUE );

					// advance the token ptr
					tokenPtr    = SkipToWhiteSpace( tokenPtr );
					endIdx      = startIdx;
					readyToLoad = TRUE;

					// see if we have a range or a single idx
					idxState = IDX_SEP_STATE;
				}
			}
			else
			{
				// ERROR: no index values present
				ErrorMsg( "ERROR: SND_IDX invalid index list\n\n", TRUE);
				error = TRUE;
			}
			break;

		case IDX_SEP_STATE:
			switch ( *tokenPtr )
			{
			case ':':	// a range
				// look for the end of the range
				idxState = IDX_NUM2_STATE;
				break;
			case ',':	// a list
			default:
				// see if there's a sound load waiting
				if ( readyToLoad )
				{
					// read in the data for this idx
					SNDactiveSubIdx = startIdx;
					error           = LoadSound();
					readyToLoad     = FALSE;
				}
				 
				// look for new indicies
				idxState = IDX_NUM1_STATE;
				break;
			}
			break;
		case IDX_NUM2_STATE:
			if ( *tokenPtr != '\n' )
			{
				// read in a numerical value
				if ( sscanf( tokenPtr, "%d", &endIdx ) == EOF )
				{
					// ERROR: failed to retrieve sound sub count
					sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_IDX\n\n",
							 lineCount );
					ErrorMsg( SNDlogMessage, TRUE );
					error = TRUE;
				}
				else
				{
					// DEBUG
					sprintf( SNDlogMessage, ": %d ", endIdx );
					LogMsg( SNDlogMessage, TRUE );

					// read in the data for each idx
					SNDactiveSubIdx = startIdx;
					while ( (SNDactiveSubIdx<=endIdx) && !error )
					{
						error = LoadSound();
						++SNDactiveSubIdx;
					}

					// see if we have more indecies
					idxState    = IDX_NUM1_STATE;
					readyToLoad = FALSE;
				}
			}
			else
			{
				// ERROR: no index values present
				ErrorMsg( "ERROR: SND_IDX invalid index list\n\n", TRUE );
				error = TRUE;
			}
			break;
		default:
			// ERROR: failed to retrieve sound sub count
			ErrorMsg( "ERROR: SND_IDX invalid index list\n\n", TRUE );
			error = TRUE;
			break;
		}

		// advance the token ptr
		tokenPtr = SkipToWhiteSpace( tokenPtr );

	}

	// see if there's a sound load waiting
	if ( readyToLoad )
	{
		// read in the data for this idx
		SNDactiveSubIdx = startIdx;
		error           = LoadSound();
		readyToLoad     = FALSE;
	}
	
	// DEBUG
	LogMsg( "\n", TRUE );

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndTextOutput( char* commandPtr, unsigned lineCount )
{
	char*	cmdPtr;
	char*	namePtr;
	long	number;
	char	fileName[32];
	BOOL	error  = FALSE;

	// DEBUG
	LogMsg( "SND_TEXT_OUTPUT: ", TRUE );

	// strip all leading white space
	cmdPtr = StripWhiteSpace( commandPtr );

	// get the name of the new wave file
	if ( sscanf( cmdPtr, "%s", fileName ) != EOF )
	{
		// load the filename

		namePtr = fileName;
		number  = 0;
		while( (*namePtr != '.') && (*namePtr ) && (number<8) )
		{
			TEXTfileName[ number++ ] = *namePtr;
			++namePtr;
		}
		strcat( TEXTfileName, ".ast" );

		// DEBUG
		sprintf( SNDlogMessage, "\"%s\"\n", TEXTfileName );
		LogMsg( SNDlogMessage, TRUE );
	}
	else
	{
		// ERROR: failed to retrieve input file name
		sprintf( SNDlogMessage, "ERROR: line %d: failed to retrieve SND_TEXT_OUTPUT name\n\n",
				 lineCount );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
	}

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CommandSndText( char* commandPtr, unsigned lineCount )
{
	int		len;
	BOOL	error = FALSE;

	// DEBUG
	LogMsg( "SND_TEXT: ", TRUE );

	// acquire the text string
	len = AcquireString( commandPtr );

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	LoadSound( void )
{
	BOOL			error = FALSE;
	BOOL			found;
	RIFF_HEADER		riffHeader;
	CHUNK_HEADER	chunkHeader;
	unsigned		snd;
	unsigned		count;
	unsigned		size;
	unsigned		amount;
	unsigned		amountRetrieved;
	char			dataBuffer[SND_MAX_BUF_SIZE+1];

	// make sure there's a sound active
	if ( !SNDactive )
	{
		// ERROR: attempted to load a sound when none active
		ErrorMsg( "ERROR: sound not active for load\n\n", TRUE );
		goto exit;
	}
	if ( *SNDactiveSndFile == '\0' )
		goto exit;

	// open the wave file
	if ( (WAVfile = (FILE*)fopen( SNDactiveSndFile, "rb" )) == NULL )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: failed to open .WAV file: \"%s\"\n\n",
				SNDactiveSndFile );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
		goto exit;
	}

	// get the RIFF header file
	if ( fread( (void*)&riffHeader, sizeof(RIFF_HEADER), 1, WAVfile) != 1)
	{
		// report an error
		ErrorMsg( "ERROR: failed to read .WAV header\n\n", TRUE );
		error = TRUE;
		goto exit;
	}

	// make sure this is a WAVE file
	if (strncmp( "RIFF", riffHeader.riffID, 4 ) != 0 )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: file \"%s\" is not a RIFF type file\n\n",
				 SNDactiveSndFile );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
		goto exit;
	}
	if (strncmp( "WAVE", riffHeader.formatID, 4 ) != 0 )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: file \"%s\" does not contain WAVE data\n\n",
				 SNDactiveSndFile );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
		goto exit;
	}

	// walk through the file until you reach the desired WAVE chunk
	count = 0;
	while( (count != SNDactiveSubIdx) && !feof( WAVfile ) )
	{
		if ( sndFindWaveformatex( WAVfile ) )
		{
			// report an error
			ErrorMsg( "ERROR: failed to find \"fmt \" chunk data\n\n", TRUE );
			error = TRUE;
			goto exit;
		}

		++count;
	}

	// now read in the sound(s)
	count = 0;
	for ( count = 0; count<SNDactiveSndCnt && !feof( WAVfile ); ++count )
	{
		// add this entry to the SND table
		snd = SNDheader.numberOfSounds;
		if ( snd >= SND_MAX_SOUNDS )
		{
			// report an error
			sprintf( SNDlogMessage, "ERROR: too many to process (>%d)\n\n",
					 SND_MAX_SOUNDS );
			ErrorMsg( SNDlogMessage, TRUE );
			error = TRUE;
			goto exit;
		}

		// update the header record
		strcpy( SNDhHeader[ snd ].soundName, SNDactiveSndName );
		SNDhHeader[ snd ].soundID = SNDidNumber;
		SNDheader.sounds[ snd ].soundID = SNDidNumber;
		SNDheader.sounds[ snd ].offset = SNDoffset;
		if ( *TEXTstring )
			strcpy( SNDhHeader[ snd ].soundText, TEXTstring );
		++SNDidNumber;

		found = FALSE;
		while ( !found && !feof( WAVfile ) )
		{
			// get the "fmt " chunk
			if ( fread( (void*)&chunkHeader, sizeof(CHUNK_HEADER), 1, WAVfile) != 1)
			{
				// report an error
				ErrorMsg( "ERROR: failed to read \"fmt \" chunk header\n\n", TRUE );
				error = TRUE;
				goto exit;
			}

			// make sure this is a "fmt " chunk
			if (strncmp( "fmt ", chunkHeader.chunkID, 4 ) == 0 )
				found = TRUE;
			else
			// now seek pass the data in this chunk
			if ( fseek( WAVfile, chunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				sprintf( SNDlogMessage,"ERROR: fseek failure (%ld). [%s:%d]\n\n", 
					  chunkHeader.chunkSize, __FILE__, __LINE__ );\
				ErrorMsg( SNDlogMessage, TRUE );
				goto exit;
			}
		}

		if ( !found )
		{
			// report an error
			sprintf( SNDlogMessage, "ERROR: in file \"%s\" failed to find \"fmt \" chunk\n\n",
					 SNDactiveSndFile );
			ErrorMsg( SNDlogMessage, TRUE );
			error = TRUE;
			goto exit;
		}

		// write out the header
		if ( fwrite( (void*)&chunkHeader, sizeof(CHUNK_HEADER), 1, TMPfile) != 1)
		{
			// report an error
			ErrorMsg( "ERROR: failed to read \"fmt \" chunk header\n\n", TRUE );
			error = TRUE;
			goto exit;
		}

		// update the SND offset
		SNDoffset += sizeof(CHUNK_HEADER);

		// transfer the "fmt " data
		size = chunkHeader.chunkSize;
		while( size )
		{
			if ( size < SND_MAX_BUF_SIZE )
				amount = size;
			else
				amount = SND_MAX_BUF_SIZE;

			if ( fread( (void*)dataBuffer, 1, amount, WAVfile) != amount)
			{
				// report an error
				ErrorMsg( "ERROR: failed to read \"fmt \" chunk data\n\n", TRUE );
				error = TRUE;
				goto exit;
			}
			if ( fwrite( (void*)dataBuffer, 1, amount, TMPfile) != amount)
			{
				// report an error
				ErrorMsg( "ERROR: failed to write \"fmt \" chunk data\n\n", TRUE );
				error = TRUE;
				goto exit;
			}
			size -= amount;
		}

		// update the SND offset
		SNDoffset += chunkHeader.chunkSize;

		found = 0;
		while ( !found && !feof(WAVfile) )
		{
			// get the "data" chunk
			if ( fread( (void*)&chunkHeader, sizeof(CHUNK_HEADER), 1, WAVfile) != 1)
			{
				// report an error
				ErrorMsg( "ERROR: failed to read \"data\" chunk header\n\n", TRUE );
				error = TRUE;
				goto exit;
			}

			// make sure this is a "data" chunk
			if (strncmp( "data", chunkHeader.chunkID, 4 ) == 0 )
				found = 1;
			else
			// now seek pass the data in this chunk
			if ( fseek( WAVfile, chunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				sprintf( SNDlogMessage,"ERROR: fseek failure (%ld). [%s:%d]\n\n", 
					  chunkHeader.chunkSize, __FILE__, __LINE__ );
				ErrorMsg( SNDlogMessage, TRUE );
				goto exit;
			}
		}

		if ( !found )
		{
			// report an error
			ErrorMsg( "ERROR: failed to locate \"data\" chunk header\n\n", TRUE );
			error = TRUE;
			goto exit;
		}

		// write out the header
		if ( fwrite( (void*)&chunkHeader, sizeof(CHUNK_HEADER), 1, TMPfile) != 1)
		{
			// report an error
			ErrorMsg( "ERROR: failed to read \"data\" chunk header\n\n", TRUE );
			error = TRUE;
			goto exit;
		}

		// update the SND offset
		SNDoffset += sizeof(CHUNK_HEADER);

		// transfer the "data" data
		size = chunkHeader.chunkSize;
		while( size )
		{
			if ( size < SND_MAX_BUF_SIZE )
				amount = size;
			else
				amount = SND_MAX_BUF_SIZE;

			amountRetrieved = fread( (void*)dataBuffer, 1, amount, WAVfile);
			if ( amountRetrieved != amount)
			{
				// report an error
				ErrorMsg( "ERROR: failed to read \"data\" chunk data\n\n", TRUE );
				error = TRUE;
				goto exit;
			}
			amountRetrieved = fwrite( (void*)dataBuffer, 1, amount, TMPfile);
			if ( amountRetrieved != amount)
			{
				// report an error
				ErrorMsg( "ERROR: failed to write \"data\" chunk data\n\n", TRUE );
				error = TRUE;
				goto exit;
			}
			size -= amount;
		}

		// update the SND offset
		SNDoffset += chunkHeader.chunkSize;

		// update the sound count
		++(SNDheader.numberOfSounds);
	}

	// clear the voice text string
	*TEXTstring = '\0';

exit:
	// close the wave file
	if ( WAVfile )
		fclose( WAVfile );

	// clear the cound cnt to default of 1
	SNDactiveSndCnt = 1;

	// clear active flag
	SNDactive = FALSE; 

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	SaveSounds( void )
{
	BOOL			error = FALSE;
	char*			namePtr;
	unsigned		count;
	unsigned char	dataBuffer[SND_MAX_BUF_SIZE+1];

	// create the .H file for these sounds
	if ( CreateHFile() )
		goto exit;

	// initialize the potential output and include filenames
	if ( SNDfileName[0] == '\0' )
	{
		count   = 0;
		namePtr = OPTfileName;
		while ( (*namePtr != '.') && (count<8) && *namePtr )
			SNDfileName[ count++ ] = *namePtr++;
		SNDfileName[ count ] = '\0';
		strcat( SNDfileName, ".asd" );
	}

	// open the .asd file
	if ( (SNDfile = (FILE*)fopen( SNDfileName, "wb" )) == NULL )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: failed to open .ASD file: \"%s\"\n\n",
				SNDfileName );
		ErrorMsg( SNDlogMessage, TRUE );
		error = TRUE;
		goto exit;
	}

	// copy in the header information
	if ( fwrite( &SNDheader, sizeof( SND_HEADER ), 1, SNDfile ) != 1 )
	{
		// ERROR: failed writing header
		ErrorMsg( "ERROR: failed to write .ASD header\n\n", TRUE );
	}

	// now copy in the TMP data, first close the file to cause final write,
	// then open and copy data
	if ( TMPfile )
		fclose( TMPfile );
	if ( (TMPfile = (FILE*)fopen( "ASD00000.000", "rb" )) == NULL )
	{
		// report an error
		ErrorMsg( "ERROR: failed to open file: \"ASD00000.000\"\n\n", TRUE );
		error = TRUE;
		goto exit;
	}

	while( !feof( TMPfile ) )
	{
		// read in a chunk of data
		count = fread( (void*)dataBuffer, 1, SND_MAX_BUF_SIZE, TMPfile);

		// now write out this data to the SND file
		if ( fwrite( (void*)dataBuffer, count, 1, SNDfile ) != 1 )
		{
			// report an error
			ErrorMsg( "ERROR: failed to write .ASD data\n\n", TRUE );
			error = TRUE;
			goto exit;
		}
	}

exit:
	// close the temporary file
	if ( TMPfile )
		fclose( TMPfile );

	// close the Sound file
	if ( SNDfile )
		fclose( SNDfile );

	// now zero out the tmp file
	if ( (TMPfile = (FILE*)fopen( "ASD00000.000", "wb" )) == NULL )
	{
		// report an error
		ErrorMsg( "ERROR: failed to open file: \"ASD00000.000\"\n\n", TRUE );
		error = TRUE;
		goto exit;
	}
	if ( TMPfile )
		fclose( TMPfile );

	return( error );
}

//=======================================================================
//=======================================================================
BOOL	CreateHFile( void )
{
	BOOL			error = FALSE;
	char*			namePtr;
	unsigned		count;
	unsigned		idNameNumber;
	char			idName[SND_NAME_MAX+8];
	char			lastName[SND_NAME_MAX+8];
	char			tmpName[SND_NAME_MAX+8];
	unsigned long	len;
	unsigned long	chunkID;
	unsigned long	nSize;

	// initialize the ID numbers
	idNameNumber = 0;
	lastName[0]  = '\0';

	// initialize the potential include filenames
	if ( HfileName[0] == '\0' )
	{
		count   = 0;
		namePtr = SNDfileName;
		while ( (*namePtr != '.') && (count<8) && *namePtr )
			HfileName[ count++ ] = *namePtr++;
		HfileName[ count ] = '\0';
		strcat( HfileName, ".h" );
	}

	// open the .h file
	if ( (Hfile = (FILE*)fopen( HfileName, "w" )) == NULL )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: failed to open file: \"%s\"\n\n",
				HfileName );
		ErrorMsg( SNDlogMessage, TRUE );
		goto exit;
	}

	// initialize the potential include filenames
	if ( SfileName[0] == '\0' )
	{
		count   = 0;
		namePtr = SNDfileName;
		while ( (*namePtr != '.') && (count<8) && *namePtr )
			SfileName[ count++ ] = *namePtr++;
		SfileName[ count ] = '\0';
		strcat( SfileName, ".dat" );
	}

	// open the .dat file
	if ( (Sfile = (FILE*)fopen( SfileName, "w" )) == NULL )
	{
		// report an error
		sprintf( SNDlogMessage, "ERROR: failed to open file: \"%s\"\n\n",
				SfileName );
		ErrorMsg( SNDlogMessage, TRUE );
		goto exit;
	}

	// initialize the potential TEXT filename
	if ( TfileName[0] == '\0' )
	{
		count   = 0;
		namePtr = TEXTfileName;
		if ( *namePtr )
		{
			while ( (*namePtr != '.') && (count<8) && *namePtr )
				TfileName[ count++ ] = *namePtr++;
			TfileName[ count ] = '\0';
			strcat( TfileName, ".ast" );
		}
	}

	// open the .ast file
	if ( TfileName[0] != '\0' )
	{
		if ( (Tfile = (FILE*)fopen( TfileName, "wb" )) == NULL )
		{
			// report an error
			sprintf( SNDlogMessage, "ERROR: failed to open file: \"%s\"\n\n",
					TfileName );
			ErrorMsg( SNDlogMessage, TRUE );
			goto exit;
		}
	}
	else
		Tfile = NULL;

	// copy in the header information
	OutputHeader();
	for( count=0; count<SNDheader.numberOfSounds; ++count )
	{
		// extract the ID NAME
		strcpy( idName, SNDhHeader[ count ].soundName );
		
		if ( strcmp( idName, lastName ) != 0 )
			idNameNumber = 0;
		strcpy( lastName, idName );

		// combine the name and number as the label
		if( SNDuseID )
		{
			strcpy( tmpName, idName );
			sprintf( idName, "%s%03d", tmpName, idNameNumber++ );
		}
		fprintf( Hfile, "#define %-25s           %d\n", idName, SNDhHeader[ count ].soundID );
		fflush( Hfile );

		fprintf( Sfile, "\t{\t%s,\t\"%s\"\t},\t// %d\n", idName, idName, SNDhHeader[ count ].soundID );
		fflush( Sfile );

		// now output any associated text strings
		if ( Tfile )
		{
			// start by getting the length of the text string, if zero, ignore it
			chunkID = VTXT_ID;
			len = strlen( SNDhHeader[ count ].soundText );
			if ( len )
			{
				// write out the voice chunk header
				fwrite( (void*)(&chunkID), 1, sizeof(long), Tfile );
				nSize = sizeof( long ) + sizeof(long) + len;
				fwrite( (void*)(&nSize), 1, sizeof(long), Tfile );

				// write out the sound ID
				fwrite( (void*)(&SNDhHeader[ count ].soundID), 1, sizeof(long), Tfile );

				// write out the text length
				fwrite( (void*)&len, 1, sizeof(long), Tfile );

				// write out the sound ID
				fwrite( (void*)SNDhHeader[ count ].soundText, 1, len, Tfile );
				fflush( Tfile );
			}
		}
	}
	OutputFooter();

exit:
	// close the include file
	if ( Hfile )
		fclose( Hfile );
	if ( Sfile )
		fclose( Sfile );
	if ( Tfile )
		fclose( Tfile );

	return( error );
}

//=======================================================================
//=======================================================================
char	CopyRight[]="ArmyMen-3DO COMPANY (C)1997\0";
char	Trailer[]="DEADBABE\0";
void	OutputHeader( void )
{
	char		timeBuffer[SND_NAME_MAX+1];
	char		nameBuffer[SND_NAME_MAX+1];
	char*		pNameChar;
	time_t		currentTime;
	struct tm*	localTime;
	int			count;
	long		len;
	unsigned long	nSize;
	unsigned long	chunkID;

	// output the copyright
	if ( Tfile )
	{
		len = strlen( CopyRight );

		// write out the voice chunk header
		chunkID = CPYR_ID;
		fwrite( (void*)(&chunkID), 1, sizeof(long), Tfile );
		nSize = len;
		fwrite( (void*)(&nSize), 1, sizeof(long), Tfile );

		// write out the copyright
		fwrite( CopyRight, 1, len, Tfile );
		fflush( Tfile );
	}

	// Get the current time
	currentTime = time( NULL );
	localTime   = localtime( &currentTime );
	count       = strftime( timeBuffer, SND_NAME_MAX, "%#c", localTime );

	fprintf( Hfile, "//=======================================================================\n" );
	fprintf( Hfile, "//     FILE:     %s\n", HfileName );
	fprintf( Hfile, "//\n" );
	fprintf( Hfile, "//     CREATED:  %s\n", timeBuffer );
	fprintf( Hfile, "//\n" );
	fprintf( Hfile, "//=======================================================================\n\n" );

	pNameChar = SfileName;
	count     = 0;
	while( (*pNameChar != '.') && (count<SND_NAME_MAX) )
	{
		nameBuffer[ count ] = *pNameChar;
		++pNameChar;
		++count;
	}
	nameBuffer[ count ] = '\0';
	fprintf( Sfile, "//=======================================================================\n" );
	fprintf( Sfile, "//     FILE:     %s\n", SfileName );
	fprintf( Sfile, "//\n" );
	fprintf( Sfile, "//     CREATED:  %s\n", timeBuffer );
	fprintf( Sfile, "//\n" );
	fprintf( Sfile, "//=======================================================================\n\n" );
	fprintf( Sfile, "SND_NAMES\tSND_%s_Names[] =\n", nameBuffer );
	fprintf( Sfile, "{\n" );

}

//=======================================================================
//=======================================================================
void	OutputFooter( void )
{
	int				len;
	unsigned long	nSize;
	unsigned long	chunkID;

	fprintf( Hfile, "\n//=======================================================================\n" );
	fprintf( Hfile, "//                                  EOF\n" );
	fprintf( Hfile, "//=======================================================================\n\n" );

	fprintf( Sfile, "\n\t// do not add anything beyond this point\n\n" );
	fprintf( Sfile, "\t{\tSND_NULL_SND_ID,\t\"\\0\"\t}\t// -1\n" );
	fflush( Sfile );
	fprintf( Sfile, "\n};\n" );
	fprintf( Sfile, "\n//=======================================================================\n" );
	fprintf( Sfile, "//                                  EOF\n" );
	fprintf( Sfile, "//=======================================================================\n\n" );

	// output the voice text trailer
	if ( Tfile )
	{
		len = strlen( Trailer );

		// write out the voice chunk header
		chunkID = EODF_ID;
		fwrite( (void*)(&chunkID), 1, sizeof(long), Tfile );
		nSize = len;
		fwrite( (void*)(&nSize), 1, sizeof(long), Tfile );

		// write out the trailer
		fwrite( (void*)Trailer, 1, len, Tfile );
		fflush( Tfile );
	}
}

//=======================================================================
//=======================================================================
char*	StripWhiteSpace( char* string )
{
	char*	scanPtr = string;
	int		len     = strlen( string );

	while( (*scanPtr == ' ') || (*scanPtr == '\t') && (scanPtr != (string+len-1)) )
		++scanPtr;

	return( scanPtr );
}

//=======================================================================
//=======================================================================
char*	SkipToWhiteSpace( char* string )
{
	char*	scanPtr = string;
	int		len     = strlen( string );

	while( (*scanPtr != ' ')  && (*scanPtr != '\t') &&
		   (*scanPtr != '\n') && (*scanPtr != '\0') &&
		   ( scanPtr != (string+len-1))
		 )
		++scanPtr;

	return( scanPtr );
}

//=======================================================================
//=======================================================================
void	MakeLegalChar( char* pLetters, unsigned nIdx )
{
	char	ch;

	// get the character to be made legal, where legal is '0'-'9',
	// 'a'-'z', 'A'-'Z', and '_'. All illegal characeters will be
	// converted to '_'

	ch = *(pLetters + nIdx);

	// check the various ranges
	if ( (ch >= '0') && (ch <= '9') )
		goto exit;

	if ( (ch >= 'a') && (ch <= 'z') )
		goto exit;

	if ( (ch >= 'A') && (ch <= 'Z') )
		goto exit;

	// no need to check for '_' as that's what the letter will become
	// once it reaches here.
	*(pLetters + nIdx) = '_';

exit:
	return;
}

///========================================================================
//	Function:		sndFindWaveformatex()
//
//	Description:
//		Retrieve the WAVEFORMATEX information
//
//	Input:			pSndFile		File to scan through
//					nSndStart		Starting offset into file for sound
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndFindWaveformatex( FILE* pSndFile )
{
	CHUNK_HEADER	sndChunkHeader;
	BOOL			found;
	BOOL			error = TRUE;		// assume a failure

	// get the "fmt " chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			sprintf( SNDlogMessage,"ERROR: failed to read \"fmt \" chunk header. [%s:%d]\n\n", 
				  __FILE__, __LINE__ );
			ErrorMsg( SNDlogMessage, TRUE );
			goto exit;
		}

		// make sure this is a "fmt " chunk
		if (strncmp( "fmt ", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;
		else
		{
			// now seek pass the data in this chunk
			if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				sprintf( SNDlogMessage,"ERROR: fseek failure (%ld). [%s:%d]\n\n", 
					  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
				ErrorMsg( SNDlogMessage, TRUE );
				goto exit;
			}
		}
	}

	// did we find the WAVEFORMATEX chunk
	if (!found )
	{
		// report an error
		sprintf( SNDlogMessage,"ERROR: failed to locate WAVEFORMATEX. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		ErrorMsg( SNDlogMessage, TRUE );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndFindSample()
//
//	Description:
//		Locate the raw smaple data information. The file pointer will be
//		advanced to the beginning of the "WAVE" raw data. If an offset is
//		specified, the file pointer will advance that far into the data.
//
//	Input:			pSndFile		File to scan through
//					nSndStart	Starting offset into file for sound
//					nOffset		offset into the raw to advance the file pointer
//					nSize		size of the sample data retrieved.
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//					pSndFile	pointing to the specified raw data
//
///========================================================================

BOOL		sndFindSample( FILE* pSndFile, unsigned* nSize )
{
	// now seek to this offset
	CHUNK_HEADER	sndChunkHeader;
	BOOL			found;
	BOOL			error = TRUE;		// assume a failure

	// get the "data" chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			sprintf( SNDlogMessage,"ERROR: failed to read \"data\" chunk header. [%s:%d]\n\n", 
				  __FILE__, __LINE__ );
			ErrorMsg( SNDlogMessage, TRUE );
			goto exit;
		}

		// make sure this is a "data" chunk
		if (strncmp( "data", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;
		else
		{
			// now seek pass the data in this chunk
			if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				sprintf( SNDlogMessage,"ERROR: fseek failure (%ld). [%s:%d]\n\n", 
					  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
				ErrorMsg( SNDlogMessage, TRUE );
				goto exit;
			}
		}
	}

	// did we find the raw sample data chunk
	if (!found )
	{
		// report an error
		sprintf( SNDlogMessage,"ERROR: failed to locate raw sampled data. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		ErrorMsg( SNDlogMessage, TRUE );
		goto exit;
	}

	// report back to the caller the data size
	*nSize = sndChunkHeader.chunkSize;

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		AcquireString()
//
//	Description:
//		acquire a quoted string, striping the quotes and NULL terminate.
//
//	Input:			none
//
//	Ouput:			len			size of the string acquired.
//
///========================================================================

int	AcquireString( char* commandPtr )
{
	char*	cmdPtr;
	char*	pNextChar;
	int		len   = 0;

	// strip all leading white space
	cmdPtr    = StripWhiteSpace( commandPtr );

	// now look for a double quote
	if ( *cmdPtr == '\"' )
	{
		// advance past the double quote
		++cmdPtr;

		// now read in the characters that make up the string token
		len = 0;
		pNextChar = cmdPtr;
		while( *pNextChar != '\"' && *pNextChar != '\n' && *pNextChar != '\0' )
		{
			TEXTstring[ len ] = *pNextChar;
			++len;
			++pNextChar;
		}
		TEXTstring[ len ] ='\0';

		LogMsg( TEXTstring, TRUE );
		LogMsg( "\n", TRUE );
	}

	return( len );
}

//=======================================================================
//=======================================================================
void LogMsg( char* pLogMessage, BOOL bToScreen )
{
	if ( bToScreen && LOGfile  )
	{
		fprintf( LOGfile, "%s", pLogMessage );
		fflush( LOGfile );
	}

	if ( bToScreen )
	{
		fprintf( stdout, "%s", pLogMessage );
		fflush( stdout );
	}
}

//=======================================================================
//=======================================================================
void ErrorMsg( char* pLogMessage, BOOL bToLog )
{
	fprintf( stderr, "%s", pLogMessage );
	fflush( stderr );

	if ( bToLog && LOGfile )
	{
		fprintf( LOGfile, "%s", pLogMessage );
		fflush( LOGfile );
	}
}

//=======================================================================
//								EOF
//=======================================================================
