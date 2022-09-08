/****************************************************************************************/
/* Input.ccp                                                                            */
/*                                                                                      */
/* Direct Input routines for reading the mouse and keyboard devices.                    */
/****************************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Input.cpp $
//  
//  71    4/17/98 1:54p Phu
//  fixed a trace message
//  
//  69    4/02/98 3:06p Phu
//  
//  68    4/01/98 12:03p Nrobinso
//  clear buffers before using
//  
//  67    3/24/98 2:48p Phu
//  fix to pause stuff to remember previous key table
//  
//  66    3/16/98 1:02p Nrobinso
//  turn off traces
//  
//  65    3/15/98 5:03p Nrobinso
//  fix inability to take cursor off screen in windowed mode
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include "stdafx.h"
#include "Army.h"
#include "DrawObject.h"
#include "GameFlow.h"
#include "MainFrm.h"
#include "Vehicle.h"
#include "Input.h"
#include "ui.h"
#include "Screen.h"
#include "Commands.h"
#include "miscfile.h"


#define TOP_CURSOR_POS 5

void GetJoystickInput(JOYSTICK_FRAME_DATA *data);

static  DIPROPDWORD dipdw ={
    {
        sizeof(DIPROPDWORD),    /* diph.dwSize */
        sizeof(DIPROPHEADER),   /* diph.dwHeaderSize */
        0,                      /* diph.dwObj */
        DIPH_DEVICE,            /* diph.dwHow */
    },
    DINPUT_BUFFERSIZE,         /* dwData */
};

/****************************************************************************************/
/* External Global Variables                                                            */
/****************************************************************************************/

HCURSOR CursorHandle;           /* Crosshairs. */
int     CursorWidth;            /* Width of crosshairs cursor. */
int     CursorHeight;           /* Height of crosshairs cursor. */
int     CursorVisible = 1;      /* Should the cursor be shown? */
POINT   CursorHotspot;          /* Hotspot location of crosshairs. */
POINT   CursorPos;              /* Virtual x, y coordinates. */
BOOL	screen_cursor = FALSE;

char CursorAtLeft=0, CursorAtRight=0, CursorAtTop=0, CursorAtBottom=0;

int  MouseDx = 0, 
	 MouseDy = 0;
BOOL MouseDown0 = 0,
	MouseDown1 = 0;


TKeyBindingEntry **pKeyTable = NULL;
TKeyBindingEntry **pPrePauseKeyTable = NULL;
extern TKeyBindingEntry JoystickButtons[];
JOYSTICK_FRAME_DATA joybasedata;


/****************************************************************************************/
/* Global Variables                                                                     */
/****************************************************************************************/

LPDIRECTINPUT           lpDI = NULL;        // Direct Input structure
LPDIRECTINPUTDEVICE     lpDIMouse = NULL;   // Direct Inpute mouse device
LPDIRECTINPUTDEVICE		lpDIKeyboard = NULL;
LPDIRECTINPUTDEVICE2    lpDIJoystick=NULL;	// Joystick device
char joyButtons = 0;

//HANDLE                hMouseEvent; /* Windows handle for mouse events. */

char    JoystickAcquired = FALSE;    /* Is joystick acquired? */
char    MouseAcquired = FALSE;       /* Is mouse acquired? */
int     MouseFuzzX = 0;              /* Leftover x-fuzz from scaling. */
int     MouseFuzzY = 0;              /* Leftover y-fuzz from scaling. */

HWND localwindow;

char buffer0[256];
char buffer1[256];
char *curBuffer = buffer0;
char *oldBuffer = buffer1;


/****************************************************************************************/
/* DIFail()                                                                             */
/*                                                                                      */
/* If failure occurs, translate the error code and (if _DEBUG) print to a message box.  */
/****************************************************************************************/

BOOL DIFail (const char* err_str, HRESULT dirval)
{
    TRACE (err_str);
    TRACE (": %s\n", DIErrorToString(dirval));

#ifdef _DEBUG
	Error(DDErrorToString(dirval));
#endif

	return FALSE;
}

void DisableDDMouse ()
{
    HRESULT hr = DI_OK;
    if (lpDIMouse && MouseAcquired){
        lpDIMouse->Unacquire();
        MouseAcquired = FALSE;
		ClientToScreen (pMainFrame->GetHwnd(), &CursorPos);
		SetCursorPos(CursorPos.x,CursorPos.y); // set windows cursor to screen coords
    }
}


/****************************************************************************************/
/* UpdateCursorPos()                                                                    */
/*                                                                                      */
/* Update mouse position based on delta x, y movement.                                  */
/****************************************************************************************/
#define CURSOR_LEFT 4
#define CURSOR_TOP 4
#define CURSOR_RIGHT pMainFrame->nMaxSize.cx - 5
#define CURSOR_BOTTOM 475


void UpdateCursorPos (int dx, int dy)
{
	if (!screen_cursor && UI_CurMode == UIMODE_LOOKINGATSARGE)
		return;

    /* Pick up leftover fuzz from previouse mouse reads. */
    dx += MouseFuzzX;
    MouseFuzzX = 0;
    dy += MouseFuzzY;
    MouseFuzzY = 0;

    /* High sensitivity: Magnify. */        /* Low sensitivity: Scale down. */
    dx *= 2;                                // MouseFuzzX = dx % 2;
    dy *= 2;                                // MouseFuzzY = dy % 2;
                                            // dx /= 2;
    CursorPos.x += dx;                      // dy /= 2;
    CursorPos.y += dy;

    // return to windows cursor off top of frame
	if( !gpDO->bFullscreen )
	{
		if ( CursorPos.y < TOP_CURSOR_POS )
		{
			ShowTheCursor( FALSE );
			ShowWindowsCursor( TRUE );
			return;
		}
	}
    
	/* Clip the cursor to the client area. */
	if( CursorPos.x < CURSOR_LEFT )
        CursorPos.x = CURSOR_LEFT;
    else if( CursorPos.x > CURSOR_RIGHT )
        CursorPos.x = CURSOR_RIGHT;

	if( CursorPos.y < CURSOR_TOP )
		CursorPos.y = CURSOR_TOP;
    else if( CursorPos.y > ( CURSOR_BOTTOM ) )
        CursorPos.y = CURSOR_BOTTOM;

	if (CursorPos.x==CURSOR_LEFT)
		CursorAtLeft=1;
	else
		CursorAtLeft=0;

	if (CursorPos.x==CURSOR_RIGHT)
		CursorAtRight=1;
	else
		CursorAtRight=0;

	if (CursorPos.y==CURSOR_TOP)
		CursorAtTop=1;
	else
		CursorAtTop=0;

	if (CursorPos.y==CURSOR_BOTTOM)
		CursorAtBottom=1;
	else
		CursorAtBottom=0;
}

/****************************************************************************************/
/* ReadMouse()                                                                          */
/*                                                                                      */
/* Read the current mouse position and check button states, call once a frame max.      */
/****************************************************************************************/

void AcquireMouse()
{
    if (lpDIMouse != NULL)	{             
		GetCursorPos(&CursorPos);
		ScreenToClient(pMainFrame->m_hWnd, &CursorPos);
		if( !gpDO->bFullscreen )
			if ( CursorPos.y < TOP_CURSOR_POS )
				return;

		HRESULT hr = lpDIMouse->Acquire();
        if ( hr == DI_OK )
            MouseAcquired = TRUE;
    }
}

/****************************************************************************************/
/* ReadMouse()                                                                          */
/*                                                                                      */
/* Read the current mouse position and check button states, call once a frame max.      */
/****************************************************************************************/

void ReadMouse(BOOL winMouse)
{
    DIDEVICEOBJECTDATA od;
	DWORD dwElements = 1;
    HRESULT hr;
	HWND hWnd = pMainFrame->m_hWnd;
	BOOL done = FALSE;

    // if the game is live and you don't have a mouse acquired yet
//  if (!MouseAcquired && lpDIMouse != NULL && !gpGame->IsPaused() && !gpGame->nPauseDelay){ 
    if (!MouseAcquired)
		AcquireMouse();

    // Attempt to read one data element. Continue as long as device data is available.
    while (!done)
    {
        hr = lpDIMouse->GetDeviceData (sizeof (DIDEVICEOBJECTDATA), &od, &dwElements, 0);

        if (hr == DIERR_INPUTLOST)
        {
            MouseAcquired = FALSE;
			AcquireMouse();
			hr = lpDIMouse->GetDeviceData (sizeof (DIDEVICEOBJECTDATA), &od, &dwElements, 0);
			if (hr == DIERR_INPUTLOST)
			{
				MouseAcquired = FALSE;
				done = TRUE;
				continue;
			}
        }

        /* Unable to read data or no data available */
        if( FAILED(hr) || dwElements == 0 )
		{
			done = TRUE;
			continue;
		}

        /* Look at the element to see what happened */
	    switch (od.dwOfs)
		{
			/* DIMOFS_X: Mouse horizontal motion */
			case DIMOFS_X:
				MouseDx += od.dwData;
				UpdateCursorPos (od.dwData, 0);
				if (winMouse)
					PostMessage(hWnd, WM_MOUSEMOVE, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
				break;

			/* DIMOFS_Y: Mouse vertical motion */
			case DIMOFS_Y:
				MouseDy += od.dwData;
				UpdateCursorPos (0, od.dwData);
				if (winMouse)
					PostMessage(hWnd, WM_MOUSEMOVE, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
				break;

			/* DIMOFS_BUTTON0: Button 0 pressed or released */
			case DIMOFS_BUTTON0:
				if (od.dwData & 0x80) /* Button pressed */
				{
					PostMessage(hWnd, WM_LBUTTONDOWN, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
					MouseDown0 = TRUE;
				}
				else 
				{
					PostMessage(hWnd, WM_LBUTTONUP, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
					MouseDown0 = FALSE;
				}
				break;

			/* DIMOFS_BUTTON1: Button 1 pressed or released */
			case DIMOFS_BUTTON1:
				if (od.dwData & 0x80) /* Button pressed */
				{
					PostMessage(hWnd, WM_RBUTTONDOWN, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
					MouseDown1 = TRUE;
				}
				else	
				{
					PostMessage(hWnd, WM_RBUTTONUP, 0, (((long)CursorPos.y) << 16) | (CursorPos.x));
					MouseDown1 = FALSE;
				}
				break;
		}
    }
}

/*--------------------------------------------------------------------------
|
| SetDIDwordProperty
|
| Set a DWORD property on a DirectInputDevice.
|
*-------------------------------------------------------------------------*/

HRESULT
SetDIDwordProperty(LPDIRECTINPUTDEVICE pdev, REFGUID guidProperty,
                   DWORD dwObject, DWORD dwHow, DWORD dwValue)
{
   DIPROPDWORD dipdw;

   dipdw.diph.dwSize       = sizeof(dipdw);
   dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
   dipdw.diph.dwObj        = dwObject;
   dipdw.diph.dwHow        = dwHow;
   dipdw.dwData            = dwValue;

   return pdev->SetProperty(guidProperty, &dipdw.diph);

}

//test function for enumerating joysticks
BOOL CALLBACK DIEnumDeviceObjectsProc( 
                      LPCDIDEVICEOBJECTINSTANCE lpddoi,
                      LPVOID pvRef) 
{ 
//	TRACE("Found device object %s", lpddoi->tszName);
	
	if (lpddoi->guidType == GUID_Button)	{
//		TRACE(": a button");
		joyButtons++;
	}

//	TRACE("\n");
	return DIENUM_CONTINUE; 
} 


BOOL FAR PASCAL InitJoystickInput(LPCDIDEVICEINSTANCE pdinst, 
                                  LPVOID pvRef) 
{ 
   LPDIRECTINPUT lpdi = (LPDIRECTINPUT) pvRef; 
   LPDIRECTINPUTDEVICE pdev; 
   HRESULT hRes; 
 
//   TRACE("Found a joystick!!!!!!!!!!!!!!!!!!!!\n");

   if (lpDIJoystick)	{
	   TRACE("Already found a joystick");
	   return DIENUM_CONTINUE;
   }

   if (lpdi->CreateDevice(pdinst->guidInstance, &pdev, NULL) != DI_OK) 
   { 
      TRACE("IDirectInput::CreateDevice FAILED\n"); 
      return DIENUM_CONTINUE; 
   }
   
   if (pdev->SetDataFormat(&c_dfDIJoystick) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetDataFormat FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 

	joyButtons = 0;

//   pdev->EnumObjects(DIEnumDeviceObjectsProc, 
//                       NULL, DIDFT_ALL); 
   pdev->EnumObjects(DIEnumDeviceObjectsProc, 
                       NULL, DIDFT_BUTTON);		// count up the buttons

   if(pdev->SetCooperativeLevel(localwindow, DISCL_EXCLUSIVE | DISCL_FOREGROUND) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetCooperativeLevel FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 

	DIPROPDWORD  dipdw; 
	dipdw.diph.dwSize = sizeof(DIPROPDWORD); 
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	dipdw.diph.dwObj = 0; 
	dipdw.diph.dwHow = DIPH_DEVICE; 
	dipdw.dwData = DINPUT_BUFFERSIZE; 
	hRes = pdev->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph); 
	if (!SUCCEEDED(hRes)) 
	{
		TRACE("ERROR when setting joystick buffer size\n");
		pdev->Release();
		return DIENUM_CONTINUE;
	}
 

   DIPROPRANGE diprg; 
 
   diprg.diph.dwSize       = sizeof(diprg); 
   diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
   diprg.diph.dwObj        = DIJOFS_X; 
   diprg.diph.dwHow        = DIPH_BYOFFSET; 
   diprg.lMin              = -1000; 
   diprg.lMax              = +1000; 
 
   if(pdev->SetProperty(DIPROP_RANGE, &diprg.diph) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetProperty(DIPH_RANGE) FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 

   diprg.diph.dwObj	= DIJOFS_Y;

   if(pdev->SetProperty(DIPROP_RANGE, &diprg.diph) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetProperty(DIPH_RANGE) FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 

    // set X axis dead zone to 5% (to avoid accidental turning) 
   if (SetDIDwordProperty(pdev, DIPROP_DEADZONE, DIJOFS_X, 
                          DIPH_BYOFFSET, 500) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetProperty(DIPH_DEADZONE) FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 

       // set Y axis dead zone to 5% (to avoid accidental turning) 
   if (SetDIDwordProperty(pdev, DIPROP_DEADZONE, DIJOFS_Y, 
                          DIPH_BYOFFSET, 500) != DI_OK) 
   { 
      TRACE("IDirectInputDevice::SetProperty(DIPH_DEADZONE) FAILED\n"); 
      pdev->Release(); 
      return DIENUM_CONTINUE; 
   } 
  

   hRes = pdev->QueryInterface(IID_IDirectInputDevice2,
                    (LPVOID *)&lpDIJoystick);

   return DIENUM_STOP;
}

BOOL acquirejoystick(void) 
{ 
    HRESULT hRes; 
 
    // if we have a current device 
    if (lpDIJoystick) 
    { 
       // acquire the device 
       hRes = lpDIJoystick->Acquire();
 
       if (hRes == DI_OK) 
       { 
         JoystickAcquired = TRUE;
         return TRUE; 
       } 
       else 
       { 
          // acquisition failed 
          TRACE(DIErrorToString(hRes));

          return FALSE; 
       } 
    } 
    else 
    { 
       // we don't have a current device 
       return FALSE;
    } 
} 

void SetNormalizeJoystickInput() 
{
	GetJoystickInput( &joybasedata );
//	TRACE("Normalizing joystick to %d,%d\n",joybasedata.x, joybasedata.y);
 }


BOOL JoystickActive()	{
   	if (lpDIJoystick)
		return TRUE;
	return FALSE;
}

BOOL JoystickPresent()	{
   	if (lpDIJoystick)
		return TRUE;
	return FALSE;
}

void NormalizeJoystickInput(JOYSTICK_FRAME_DATA *data) 
{
	data->x -= joybasedata.x;
	data->y -= joybasedata.y;
}


char *GetJoystickButtonStr(int button)
{
	static char bstr[] = "Button 1";
	static char *dirs[] = {"Right","Left","Up","Down"};
	static char unused_str[] = "undefined";

	button--;
	if (button >= 0)
	{
		if (button < JOYSTICK_BUTTONS)
		{
			bstr[7] = button + '1';
			return bstr;
		}
		else if (button < JOY_BUTTONS)
		{
			button -= JOYSTICK_BUTTONS;
			return dirs[button];
		}
	}

	return  unused_str;
}


void GetJoystickInput(JOYSTICK_FRAME_DATA *data) 
{ 
    HRESULT                 hRes; 
    DIJOYSTATE              js; 
	DIDEVICEOBJECTDATA		joystickdata[DINPUT_BUFFERSIZE];
	DWORD					datacount=DINPUT_BUFFERSIZE;
	int						i;

	ZeroMemory(data, sizeof(JOYSTICK_FRAME_DATA));

   	if (!lpDIJoystick)
		return;

	if (!JoystickAcquired)
	{
		if (!acquirejoystick())	{
			TRACE("ERROR: Unable to acquire joystick. you bastard\n");
			return;
		}
	}

	hRes = IDirectInputDevice2_Poll(lpDIJoystick);
 
    // get data from the joystick 
    hRes = IDirectInputDevice_GetDeviceState(lpDIJoystick, 
                                            sizeof(DIJOYSTATE), &js); 
 
    if (hRes != DI_OK) 
    { 
      // did the read fail because we lost input for some reason? 

      // if so, then attempt to reacquire. If the second acquire 
      // fails, then the error from GetDeviceData will be 
      // DIERR_NOTACQUIRED, so we won't get stuck an infinite loop. 
      if(hRes == DIERR_INPUTLOST) 
         acquirejoystick(); 
 
      // return the fact that we did not read any data 
  	  return;
    } 

	data->oldx = data->x;
	data->oldy = data->y;

	data->x=js.lX;
	data->y=js.lY;

	for (i=0;i<JOYSTICK_BUTTONS;i++)
		data->buttondown[i]=js.rgbButtons[i]>>7;
	
	hRes=lpDIJoystick->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),joystickdata,&datacount,0);
	if (hRes != DI_OK)
	{
		TRACE("ERROR while trying to get buffered joystick data\n");
		return;
	}

	for (i=0;i<(int)datacount;i++)
	{
		DIDEVICEOBJECTDATA *curdata = &joystickdata[i];

		switch((int) curdata->dwOfs)
		{
		case DIJOFS_BUTTON0:
			data->buttonpressed[0]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[0]=1;
			break;
		case DIJOFS_BUTTON1:
			data->buttonpressed[1]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[1]=1;
			break;
		case DIJOFS_BUTTON2:
			data->buttonpressed[2]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[2]=1;
			break;
		case DIJOFS_BUTTON3:
			data->buttonpressed[3]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[3]=1;
			break;
		case DIJOFS_BUTTON4:
			data->buttonpressed[4]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[4]=1;
			break;
		case DIJOFS_BUTTON5:
			data->buttonpressed[5]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[5]=1;
			break;
		case DIJOFS_BUTTON6:
			data->buttonpressed[6]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[6]=1;
			break;
		case DIJOFS_BUTTON7:
			data->buttonpressed[7]=0;
			if (curdata->dwData & 0x80)
				data->buttonpressed[7]=1;
			break;
		}
	}
} 


void ReadCapturedKeyboard( void )
{
    #define KEYDOWN(name,key) (name[key] & 0x80) 
 
    HRESULT hr;
	int		status;
	int		delta;

    hr = lpDIKeyboard->GetDeviceState( sizeof(buffer0), (LPVOID)curBuffer ); 
    if (hr != DI_OK ) 
    { 
		hr = lpDIKeyboard->Acquire();
		if( hr == DI_OK )
			hr = lpDIKeyboard->GetDeviceState( sizeof(buffer0), (LPVOID)curBuffer ); 
		if( hr != DI_OK )
		{
			TRACE("Unable to acquire keyboard.\n");
			return;
		}
		ZeroMemory(oldBuffer, 256);
 		ZeroMemory(curBuffer, 256);
   } 
 	
	for( BYTE k = 1; k < 255; k++ )
	{
		status = KEYDOWN( curBuffer, k );
		delta = (status != KEYDOWN( oldBuffer, k ) );
		if( status )	{
			if (delta)	{
				if ( gpGame->nPauseDelay == 0 ) {
					SBtnKeycodeProcess( k );
				}
			}
		}
	}

	char *temp = oldBuffer;
	oldBuffer = curBuffer;
	curBuffer = temp;
}

extern long user_action;

void ReadKeyboard( void )
{
    #define KEYDOWN(name,key) (name[key] & 0x80) 
 
    HRESULT hr;
	int		status;
	int		delta;
	int		repeat;
	TKeyBindingEntry **pTempKeyTable;


    hr = lpDIKeyboard->GetDeviceState( sizeof(buffer0), (LPVOID)curBuffer ); 
    if (hr != DI_OK ) 
    { 
		hr = lpDIKeyboard->Acquire();
		if( hr == DI_OK )
		    hr = lpDIKeyboard->GetDeviceState( sizeof(buffer0), (LPVOID)curBuffer ); 
		if( hr != DI_OK )
		{
			TRACE("Unable to acquire keyboard.\n");
			return;
		}
   		ZeroMemory(oldBuffer, 256);
 		ZeroMemory(curBuffer, 256);
 } 
 	
	user_action = 0;
	pTempKeyTable = pKeyTable;
	int deltatime = gpGame->dwDeltaTime;

	for( int table = 0; pTempKeyTable[table] != NULL; table++ )
	{
		for( BYTE i = 0; (pTempKeyTable[table][i]).dispatcher != NULL; i++ )
		{
			UINT	flags;
			BYTE	modifier;
			BYTE	key;

			key = pTempKeyTable[table][i].key;
			if( key == 0 )
			{
				/*
				for( BYTE k = 1; k < 255; k++ )
				{
					flags = 0;
					status = KEYDOWN( curBuffer, k );
					delta = (status != KEYDOWN( oldBuffer, k ) );
					if( status )
						flags += Flag_KeyDown;
					if( delta )
						flags += Flag_KeyDelta;
					if( delta )
					{
						if ( gpGame->nPauseDelay == 0 )
							(pTempKeyTable[table][i].dispatcher)( k, flags );
					}
				}
				*/
				continue;
			}
			status = KEYDOWN( curBuffer, key );
			delta = (status != KEYDOWN( oldBuffer, key ) );
			if( pTempKeyTable[table][i].repeat_rate > 0 )
			{
				repeat = 0;
				if( status )
				{
					pTempKeyTable[table][i].repeat_time += deltatime;
					if( pTempKeyTable[table][i].repeat_time > pTempKeyTable[table][i].repeat_rate )
					{
						if( !delta )
							repeat = 1;
						pTempKeyTable[table][i].repeat_time = 0;
					}
				}
				else
					pTempKeyTable[table][i].repeat_time = 0;
			}
			if( (modifier = pTempKeyTable[table][i].modifier_key) > 0 )
			{
				if( !(KEYDOWN(curBuffer, modifier)) )
					continue;
			}
			if( (modifier = pTempKeyTable[table][i].exclude_key) > 0 )
			{
				if( KEYDOWN(curBuffer, modifier) )
					continue;
			}
			flags = 0;
			if( status )
				flags += Flag_KeyDown;
			if( delta )
				flags += Flag_KeyDelta;
			if( repeat )
				flags += Flag_KeyRepeat;
			if ( gpGame->nPauseDelay == 0 )
			{
				switch( pTempKeyTable[table][i].triggerOn )
				{
				case ETO_Always:
					(pTempKeyTable[table][i].dispatcher)( key, flags );
					break;
				case ETO_Down:
					if( status )
						(pTempKeyTable[table][i].dispatcher)( key, flags );
					break;
				case ETO_Pressed:
					if( status && delta )
						(pTempKeyTable[table][i].dispatcher)( key, flags );
					break;
				case ETO_PressedRepeat:
					if( status && (delta || repeat))
						(pTempKeyTable[table][i].dispatcher)( key, flags );
					break;
				case ETO_Released:
					if( (!status) && delta )
						(pTempKeyTable[table][i].dispatcher)( key, flags );
					break;
				}
			}
		}
	}

	char *temp = oldBuffer;
	oldBuffer = curBuffer;
	curBuffer = temp;
}


void ReadJoystick( void )
{
	static JOYSTICK_FRAME_DATA joydata;
	char on[JOY_BUTTONS];
	char pressed[JOY_BUTTONS];
	int		j;
	UINT	flags;
	char	delta;
	BYTE	key;
	BOOL	status;

	if ( gpGame->nPauseDelay == 0 ) {
		if (JoystickActive())	{
			GetJoystickInput( &joydata );
			NormalizeJoystickInput( &joydata );
			memset((void *) on, 0, JOY_BUTTONS);
			memset((void *) pressed, 0, JOY_BUTTONS);
		
			if (joydata.y > 100)	{
				on[DOWN_KEY] = TRUE;
				pressed[DOWN_KEY] = (joydata.oldy <= 100);
			}
			else if (joydata.y < -100)	{
				on[UP_KEY] = TRUE;
				pressed[UP_KEY] = (joydata.oldy >= -100);
			}

			if (joydata.x > 100)	{
				on[RIGHT_KEY] = TRUE;
				pressed[RIGHT_KEY] = (joydata.oldx <= 100);
			}
			else if (joydata.x < -100)	{
				on[LEFT_KEY] = TRUE;
				pressed[LEFT_KEY] = (joydata.oldx >= -100);
			}

			for (j=0; j<JOYSTICK_BUTTONS; j++)	{
				on[j+1] = joydata.buttondown[j];
				pressed[j+1] = joydata.buttonpressed[j];
			}
			
			for( BYTE i = 0; (JoystickButtons[i]).dispatcher != NULL; i++ )
			{
				key = JoystickButtons[i].key;

				status = on[key];
				delta = pressed[key];
				flags = 0;

				if( status )
					flags += Flag_KeyDown;
				if( delta )
					flags += Flag_KeyDelta;

				switch( JoystickButtons[i].triggerOn )
				{
				case ETO_Always:
					(JoystickButtons[i].dispatcher)( key, flags );
					break;
				case ETO_Down:
					if( status )
						(JoystickButtons[i].dispatcher)( key, flags );
					break;
				case ETO_Pressed:
					if( status && delta)
						(JoystickButtons[i].dispatcher)( key, flags );
					break;
				case ETO_Released:
					ASSERT(0);
					if( (!status) && delta )
						(JoystickButtons[i].dispatcher)( key, flags );
					break;
				}
			}
		}
	}
}


void ReadCapturedJoystick( void )
{
	static JOYSTICK_FRAME_DATA joydata;
	char on[JOY_BUTTONS];
	char pressed[JOY_BUTTONS];
	int		j;
	UINT	flags;
	char	delta;
	BYTE	key;
	BOOL	status;

	if ( gpGame->nPauseDelay == 0 ) {
		if (JoystickPresent())	{
			GetJoystickInput( &joydata );
			NormalizeJoystickInput( &joydata );
			memset((void *) on, 0, JOY_BUTTONS);
			memset((void *) pressed, 0, JOY_BUTTONS);
		
			if (joydata.y > 100)	{
				on[DOWN_KEY] = TRUE;
				pressed[DOWN_KEY] = (joydata.oldy <= 100);
			}
			else if (joydata.y < -100)	{
				on[UP_KEY] = TRUE;
				pressed[UP_KEY] = (joydata.oldy >= -100);
			}

			if (joydata.x > 100)	{
				on[RIGHT_KEY] = TRUE;
				pressed[RIGHT_KEY] = (joydata.oldx <= 100);
			}
			else if (joydata.x < -100)	{
				on[LEFT_KEY] = TRUE;
				pressed[LEFT_KEY] = (joydata.oldx >= -100);
			}

			for (j=0; j<JOYSTICK_BUTTONS; j++)	{
				on[j+1] = joydata.buttondown[j];
				pressed[j+1] = joydata.buttonpressed[j];
			}
			
			for( BYTE i = 0; (JoystickButtons[i]).dispatcher != NULL; i++ )
			{
				key = JoystickButtons[i].key;

				status = on[key];
				delta = pressed[key];
				flags = 0;

				if( status && delta)
					SBtnJoystickProcess( key );
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************************/
/* InitDirectInput()                                                                    */
/*                                                                                      */
/* Initialize Direct Input objects and devices.                                         */
/****************************************************************************************/

BOOL InitDirectInput (HWND hWnd)
{
   HRESULT     hr;

   /* Register with DirectInput and get an IDirectInput to play with. */
   hr = DirectInputCreate (AfxGetInstanceHandle(), DIRECTINPUT_VERSION, &lpDI, NULL);
   if (hr != DI_OK)
      return (DIFail ("DirectInputCreate()", hr));

   /* Obtain an interface to the system mouse device. */
   hr = lpDI->CreateDevice (GUID_SysMouse, &lpDIMouse, NULL);
   if (hr != DI_OK)
      return (DIFail ("CreateDevice (SysMouse)", hr));

   /* Set the data format to "mouse format". */
   hr = lpDIMouse->SetDataFormat (&c_dfDIMouse);
   if (hr != DI_OK)
      return (DIFail ("SetDataFormat (SysMouse, dfDIMouse)", hr));

   /* Set the cooperativity level. */
   hr = lpDIMouse->SetCooperativeLevel (hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
   if (hr != DI_OK)
      return (DIFail ("SetCooperativeLevel (SysMouse)", hr));

//   /* Create the handle that tells us new data is available. */
//   hMouseEvent = CreateEvent (0, 0, 0, 0);

//   if (hMouseEvent == NULL)
//      return (DIFail ("CreateEvent()", GetLastError()));

//   /* Associate the event with the device. */
//   hr = lpDIMouse->SetEventNotification (hMouseEvent);
//   if (hr != DI_OK)
//      return (DIFail ("SetEventNotification (SysMouse)", hr));

// Set the buffer size to DINPUT_BUFFERSIZE elements.
// The buffer size is a DWORD property associated with the device. 

    hr = lpDIMouse->SetProperty (DIPROP_BUFFERSIZE, &dipdw.diph);
    if (hr != DI_OK)
        return (DIFail ("Set buffer size (SysMouse)", hr));

	//  Create DI Keyboard
	hr = lpDI->CreateDevice( GUID_SysKeyboard, &lpDIKeyboard, NULL ); 
	if( hr != DI_OK ) 
		return( DIFail( "CreateDevice (SysKeyboard)", hr ) );
	hr = lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard); 
	if( hr != DI_OK )
		return( DIFail( "SetDataFormat (SysKeyboard)", hr ) );
	hr = lpDIKeyboard->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	if( hr != DI_OK )
		return( DIFail( "SetCooperativeLevel (SysKeyboard)", hr ) );
	localwindow=hWnd;


    lpDI->EnumDevices(DIDEVTYPE_JOYSTICK, 
                         InitJoystickInput, lpDI, DIEDFL_ATTACHEDONLY); 

	ZeroMemory( buffer0, 256 );
	ZeroMemory( buffer1, 256 );

	return TRUE;
}


/****************************************************************************************/
/* DirectInputExit()                                                                    */
/*                                                                                      */
/* Release Direct Input objects and devices.                                            */
/****************************************************************************************/

void DirectInputExit (void)
{
	if (lpDI)
	{
		if (lpDIMouse)
		{
			lpDIMouse->Unacquire();
			lpDIMouse->Release();
			lpDIMouse = NULL;
		}	
		if (lpDIJoystick)
		{
			lpDIJoystick->Unacquire();
			lpDIJoystick->Release();
			lpDIJoystick = NULL;
		}
		if( lpDIKeyboard )
		{
			lpDIKeyboard->Unacquire();
			lpDIKeyboard->Release();
			lpDIKeyboard = NULL;
		}
		lpDI->Release();
		lpDI= NULL;
	}
//   if (hMouseEvent)
//   {
//      CloseHandle (hMouseEvent);
//      hMouseEvent = NULL;
//   }
}

void	UseSargeKeyTable()
{
	pKeyTable = SargeKeyTable;
}



BOOL cursor_saved = FALSE;
SPRITE CursorSprite;
LPDIRECTDRAWSURFACE pCursorSurface = NULL;
static RECT rcSaveRect;
static RECT rcCursor = {0,0,16,16};

void LoadCursor()
{
	if (!CursorSprite.pGraphic)	{
		SetPath(NULL);
		LoadSprite( &CursorSprite, "cursor.bmp", BM_TRANSPARENT | BM_SYSTEMMEMORY );
	}

	if (!pCursorSurface)
		pCursorSurface = CreateSurfaceOfSize( 16, 16, BM_SYSTEMMEMORY, 0 );
}

void FreeCursor()
{
	if (CursorSprite.pGraphic)
		FreeSprite( &CursorSprite );

	if (pCursorSurface)
		pCursorSurface->Release();

	pCursorSurface = NULL;
}

void RestoreCursorArea()
{
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	RECT rcFront;
	int v;
	RECT rcIntersect;

	if( cursor_saved )	{
		rcFront = rcSaveRect;
		rcFront.left += rcWindowScreen.left;
		rcFront.right += rcWindowScreen.left;
		rcFront.top += rcWindowScreen.top;
		rcFront.bottom += rcWindowScreen.top;
		if( RectIntersect( &rcFront, &rcWindowScreen, &rcIntersect ) )
		{
			v = pFrontBuffer->Blt(&rcIntersect, pCursorSurface, &rcCursor, DDBLT_WAIT, &ddbltfx);
			if( v != DD_OK )
				TRACE( "BAD! in RestoreCursorArea (%x)\n", v );
		}
	}
}

void SaveCursorArea()
{
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	RECT rcFront;
	RECT rcIntersect;
	int v;

	rcSaveRect.left = CursorPos.x;
	rcSaveRect.right = rcSaveRect.left+16;
	rcSaveRect.top = CursorPos.y;
	rcSaveRect.bottom = rcSaveRect.top+16;
	rcFront = rcSaveRect;
	rcFront.left += rcWindowScreen.left;
	rcFront.right += rcWindowScreen.left;
	rcFront.top += rcWindowScreen.top;
	rcFront.bottom += rcWindowScreen.top;
	if( RectIntersect( &rcFront, &rcWindowScreen, &rcIntersect ) )
	{
		v = pCursorSurface->Blt(&rcCursor, pFrontBuffer, &rcIntersect, DDBLT_WAIT, &ddbltfx);
		if( v != DD_OK )
			TRACE( "BAD! in SaveCursorArea()  ERROR: %x\n", v );
		cursor_saved = TRUE;
	}
}

void CursorOff(RECT *pRect)
{
	if (screen_cursor)	{
		if (RectIntersect(pRect, &rcSaveRect, NULL))	
		{
			RestoreCursorArea();
			screen_cursor = FALSE;
		}
	}
}

void CursorOn()
{
	if (!screen_cursor)
		SaveCursorArea();
	screen_cursor = TRUE;
}

void ShowTheCursor( BOOL showit )
{
	switch( showit )
	{
		case TRUE:
			if (!screen_cursor)	{
				ShowWindowsCursor( FALSE );
				cursor_saved = FALSE;
			}
			screen_cursor = TRUE;
			break;

		case FALSE:
			if (screen_cursor)				
				RestoreCursorArea();
			screen_cursor = FALSE;
			break;
	}
}


void ShowWindowsCursor( BOOL showit )
{
	int show;

	switch( showit )
	{
		case TRUE:
			DisableDDMouse();
			while( (show = ShowCursor(TRUE)) < 0 )
				;
			break;

		case FALSE:
			while( (show = ShowCursor(FALSE)) >= 0 )
				;
			break;
	}
}


void DrawCursor(void)
{
	if (!screen_cursor)
		return;

	if (rcSaveRect.left != CursorPos.x || rcSaveRect.top != CursorPos.y)	{
		RestoreCursorArea();	// restore saved area under cursor

		// save area where cursor is going
		SaveCursorArea();
	}
	else if( !cursor_saved )
		SaveCursorArea();

	DisplaySpriteClippedFront( &CursorSprite, CursorPos.x, CursorPos.y );
}
