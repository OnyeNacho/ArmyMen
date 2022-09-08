// Vegas Games Launcher

#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <string.h>

#define ARMYMEN_KEY (TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\ArmyMen.exe"))
#define ARMYMEN ("\\Armymen.exe")

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow )
{
	HINSTANCE err = 0;
	char buffer[128];
	char *pExecute;
	HKEY hRegKey;						// application registry key handle
	DWORD	dwSize;
    DWORD	dwType;

	// look for armymen key
	if (RegOpenKeyEx( HKEY_LOCAL_MACHINE, ARMYMEN_KEY, REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS, &hRegKey ) == ERROR_SUCCESS)
	{
		dwSize = sizeof(buffer);
		if (RegQueryValueEx(hRegKey, "Path", NULL, &dwType, buffer, &dwSize) == ERROR_SUCCESS)
		{
			strcat(buffer, ARMYMEN);
			pExecute = buffer;
			err = ShellExecute (NULL, "open", pExecute, lpszCmdParam, NULL, SW_SHOWNORMAL);
		}
	}

	if ((int)err < SE_ERR_DLLNOTFOUND)
		MessageBox(NULL, "Army Men not installed.", "Error", MB_OK);

	return(1);
}
