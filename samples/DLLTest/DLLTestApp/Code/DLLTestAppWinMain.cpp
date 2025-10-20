// DLL Test

#include "DLLTestPluginClass.h"

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow)
{
	DLLTestPluginClass Plugin;
	Plugin.BaseFunction();
	Plugin.VirtualFunction();

	return MessageBox(NULL, L"Test App completed.", L"DLL Test", MB_OK);
}
