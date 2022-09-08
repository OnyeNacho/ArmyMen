/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: lobby.cpp $
//
//	DESCRIPTION:	lobby routines
//
//	AUTHOR:			MicroSoft
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/lobby.cpp 3     12/09/97 12:12p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/lobby.cpp $
//  
//  3     12/09/97 12:12p Phu
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  1     6/19/97 11:59a Awerner
//  
//  3     5/02/97 6:39p Dmaynard
//  Fixed unresolved reference.. This file will go away soon.
//  
//  2     4/27/97 3:43p Dmaynard
//  Change to pre-compiled headers
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "comm.h"
#include "lobby.h"

/*
 * Externals
 */
// extern LPDIRECTPLAY2                glpDP;                  // directplay object pointer

/*
 * Globals
 */
LPDPLCONNECTION                     glpdplConnection;       // connection settings

/*
 * Statics
 */
static LPDIRECTPLAYLOBBY            glpDPL;                 // lobby object pointer



/*
 * DPLobbyCreate
 *
 * Wrapper for DirectPlayLobby DirectPlayLobbyCreate API.
 */
HRESULT DPLobbyCreate(void)
{
    HRESULT hr=E_FAIL;

    hr = DirectPlayLobbyCreate(NULL, &glpDPL, NULL, NULL, 0);   

    return hr;
}

/*
 * DPLobbyConnect
 *
 * Wrapper for DirectPlayLobby Connect API.
 */
HRESULT DPLobbyConnect(void)
{
    HRESULT hr=E_FAIL;

    hr = IDirectPlayLobby_Connect(glpDPL, 0, &gpComm->m_pDPlay, NULL) ;    

    return hr;
}

/*
 * DPLobbyGetConnectionSettings
 *
 * Wrapper for DirectPlayLobby GetConnectionSettings API
 */
HRESULT DPLobbyGetConnectionSettings(void)
{
    HRESULT hr=E_FAIL;
    DWORD dwSize;

    if (glpDPL)
    {
        // get size for the connection settings structure
        hr = IDirectPlayLobby_GetConnectionSettings(glpDPL, 0, NULL, &dwSize);
        if (DPERR_BUFFERTOOSMALL == hr)
        { 
            // if we already have one, free it
            if (glpdplConnection)
            {
                free(glpdplConnection);
                glpdplConnection = NULL;
            }

            // allocate memory for the new one
            glpdplConnection = (LPDPLCONNECTION) malloc(dwSize);

            // get the connection settings
            if (glpdplConnection)
                hr = IDirectPlayLobby_GetConnectionSettings(glpDPL, 0, glpdplConnection, &dwSize);
        }
    }

    return hr;
}

/*
 * DPLobbyRelease
 *
 * Wrapper for DirectPlayLobby Release API
 */
HRESULT DPLobbyRelease(void)
{
    HRESULT hr=E_FAIL;

    // free our connection settings
    if (glpdplConnection)
    {
        free(glpdplConnection);
        glpdplConnection = NULL;
    }

    // release the lobby object
    if (glpDPL)
    {
        hr = IDirectPlayLobby_Release(glpDPL);
        glpDPL = NULL;
    }
    return hr;
}

/*
 * DPLobbySetConnectionSettings
 *
 * Wrapper for DirectPlayLobby SetConnectionSettings API
 */
HRESULT DPLobbySetConnectionSettings(void)
{
    HRESULT hr=E_FAIL;

    hr = IDirectPlayLobby_SetConnectionSettings(glpDPL, 0, 0, glpdplConnection);

    return hr;
}

