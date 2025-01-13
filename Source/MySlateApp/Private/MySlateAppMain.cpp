#include "Windows/WindowsHWrapper.h"
#include "MySlateApp.h"

int WINAPI WinMain( _In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR, _In_ int nCmdShow )
{
	RunMySlateApp(GetCommandLineW());

	return 0;
}
