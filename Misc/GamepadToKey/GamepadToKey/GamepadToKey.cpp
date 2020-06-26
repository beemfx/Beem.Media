// GamepadToKey.cpp : Defines the entry point for the application.
//

#include "GPTKXInputHandler.h"
#include <windows.h>
#include "resource.h"


#define MAX_LOADSTRING 100

static HINSTANCE g_Inst = nullptr;
static bool g_bKeeyLooping = true;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK GamepadToKey_WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GamepadToKey_About(HWND, UINT, WPARAM, LPARAM);

static void GampeadToKey_Handler( DWORD Key , UINT Msg , void* Extra )
{
	if( false ) //Key == 'Z' )
	{
		g_bKeeyLooping = false;
	}

	UINT ScanCode = MapVirtualKeyExW( Key , MAPVK_VK_TO_VSC_EX , 0 );

	struct gptkKeyLParam
	{
		int Repeat:16;
		int ScanCode:8;
		int IsExtended:1;
		int Reserved:4;
		int ContextCode:1;
		int PreviousState:1;
		int TransitionState:1;
	};

	union gptkKeyLParamConverter
	{
		LPARAM lParam;
		gptkKeyLParam AsStruct;
	};

	gptkKeyLParamConverter lParam;
	lParam.lParam = 0;
	lParam.AsStruct.Repeat = 1;
	lParam.AsStruct.IsExtended = 0;
	lParam.AsStruct.PreviousState = ( Msg == WM_KEYUP ) ? 1 : 0;
	lParam.AsStruct.TransitionState = (Msg == WM_KEYUP ) ? 1 : 0;
	lParam.AsStruct.ScanCode = ScanCode;


	HWND hFocusedWindow = GetForegroundWindow();
	WCHAR FocusedWindowName[256];
	GetWindowTextW( hFocusedWindow , FocusedWindowName , 256 );
	SendMessageW( hFocusedWindow , Msg , Key , lParam.lParam );
}

int APIENTRY wWinMain( _In_ HINSTANCE hInstance , _In_opt_ HINSTANCE hPrevInstance ,_In_ LPWSTR lpCmdLine , _In_ int nCmdShow )
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	 WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	 WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	 GPTKXInputHandler_Init();

	 while( g_bKeeyLooping )
	 {
		 GPTKXInputHandler_Update( 0.f , GampeadToKey_Handler , nullptr );
	 }

	 GPTKXInputHandler_Deinit();

	 auto DoRegisterClass = [&szTitle,&szWindowClass](HINSTANCE hInstance) -> ATOM
	 {
		 WNDCLASSEXW wcex;

		 wcex.cbSize = sizeof(WNDCLASSEX);

		 wcex.style          = CS_HREDRAW | CS_VREDRAW;
		 wcex.lpfnWndProc    = GamepadToKey_WndProc;
		 wcex.cbClsExtra     = 0;
		 wcex.cbWndExtra     = 0;
		 wcex.hInstance      = hInstance;
		 wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEPADTOKEY));
		 wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
		 wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
		 wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMEPADTOKEY);
		 wcex.lpszClassName  = szWindowClass;
		 wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		 return RegisterClassExW(&wcex);
	 };

	 auto InitInstance =[&szWindowClass,&szTitle](HINSTANCE hInstance, int nCmdShow) -> BOOL
	 {
		 g_Inst = hInstance;

		 HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

		 if (!hWnd)
		 {
			 return FALSE;
		 }

		 ShowWindow(hWnd, nCmdShow);
		 UpdateWindow(hWnd);

		 return TRUE;
	 };

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEPADTOKEY, szWindowClass, MAX_LOADSTRING);
    DoRegisterClass( hInstance );

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEPADTOKEY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK GamepadToKey_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_Inst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, GamepadToKey_About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProcW(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK GamepadToKey_About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
