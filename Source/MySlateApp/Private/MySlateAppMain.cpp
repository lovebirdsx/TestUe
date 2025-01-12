#include "Windows/WindowsHWrapper.h"
#include "MySlateApp.h"

/**
 * WinMain, called when the application is started
 */
int WINAPI WinMain( _In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR, _In_ int nCmdShow )
{
	// do the UE Hub thing
	RunMySlateApp(GetCommandLineW());

	return 0;
}
