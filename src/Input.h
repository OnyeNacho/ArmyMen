/****************************************************************************************/
/* Input.h                                                                              */
/*                                                                                      */
/* Direct Input routines for reading the mouse and keyboard devices.                    */
/****************************************************************************************/


#ifndef _INPUT_H
#define _INPUT_H

/****************************************************************************************/
/* Defines                                                                              */
/****************************************************************************************/
#define DINPUT_BUFFERSIZE  16 /* Size/depth of mouse buffer. */
#define JOYSTICK_BUTTONS   8  /* we only care about 8 joystick buttons for now*/

#define ETO_Down		0x01
#define ETO_Pressed		0x02
#define ETO_Released	0x03
#define ETO_Always		0x04
#define ETO_PressedRepeat	0x05

#define Flag_KeyDown	0x01
#define Flag_KeyDelta	0x02
#define Flag_KeyRepeat  0x04

extern BOOL MouseDown0;
extern BOOL MouseDown1;

/****************************************************************************************/
/* Typedefs																				 */
/****************************************************************************************/
typedef struct
{
	int x,y;
	int oldx,oldy;
	char buttonpressed[JOYSTICK_BUTTONS];
	char buttondown[JOYSTICK_BUTTONS];
} JOYSTICK_FRAME_DATA;

struct TKeyBindingEntry
{
	BYTE	key;
	void	(*dispatcher)(BYTE nChar, UINT nFlags);
	int		triggerOn;
	BYTE	modifier_key;
	BYTE	exclude_key;
	char	*desc;
	short   repeat_rate;
	short   repeat_time;
};

typedef enum
{
    RIGHT_KEY = JOYSTICK_BUTTONS+1,
    LEFT_KEY,
	UP_KEY,
	DOWN_KEY,

	ESC_KEY,

	JOY_BUTTONS
} JOY_VALUES;

/****************************************************************************************/
/* External Global Variables                                                            */
/****************************************************************************************/

extern HCURSOR	CursorHandle;     /* Crosshairs. */
extern int		CursorWidth;      /* Width of crosshairs cursor. */
extern int		CursorHeight;     /* Height of crosshairs cursor. */
extern int		CursorVisible;    /* Should the cursor be shown? */
extern POINT	CursorHotspot;    /* Hotspot location of crosshairs. */
extern POINT	CursorPos;        /* Virtual x, y coordinates. */

extern char CursorAtLeft, CursorAtRight, CursorAtTop, CursorAtBottom; //boolean values

extern TKeyBindingEntry **pKeyTable;
extern TKeyBindingEntry **pPrePauseKeyTable;

/****************************************************************************************/
/* External Prototypes                                                                  */
/****************************************************************************************/

BOOL InitDirectInput (HWND hWnd);
void DirectInputExit (void);
void ReadMouse(BOOL winMouse = FALSE);
void DisableDDMouse();
void UpdateCursorPos(int dx, int dy);
void ReadCapturedKeyboard( void );
void ReadKeyboard( void );
void ReadJoystick( void );
void ReadCapturedJoystick( void );
void NormalizeJoystickInput(JOYSTICK_FRAME_DATA *data);
void SetNormalizeJoystickInput();
BOOL JoystickActive();
BOOL JoystickPresent();
void UseSargeKeyTable();
char *GetJoystickButtonStr(int button);
void ShowWindowsCursor( BOOL showit );
void ShowTheCursor( BOOL showit );
void CursorOff(RECT *pRect);
void CursorOn();
void RestoreCursorArea();
void LoadCursor();
void FreeCursor();

#endif // _INPUT_H

