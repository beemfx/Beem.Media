// GamepadToKey.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <vector>
#include <string>
#include <stdio.h>

static HINSTANCE g_Inst = nullptr;
std::vector<std::wstring> g_InputHistory;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK GamepadToKeyReceiver_WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GamepadToKeyReceiver_About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain( _In_ HINSTANCE hInstance , _In_opt_ HINSTANCE hPrevInstance ,_In_ LPWSTR lpCmdLine , _In_ int nCmdShow )
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	static const WCHAR szTitle[] = L"Test Receiver";                  // The title bar text
	static const WCHAR szWindowClass[] = L"Test Receiver Class";            // the main window class name

	auto DoRegisterClass = [](HINSTANCE hInstance) -> ATOM
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style          = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc    = GamepadToKeyReceiver_WndProc;
		wcex.cbClsExtra     = 0;
		wcex.cbWndExtra     = 0;
		wcex.hInstance      = hInstance;
		wcex.hIcon          = nullptr;
		wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName   = nullptr;
		wcex.lpszClassName  = szWindowClass;
		wcex.hIconSm        = nullptr;

		return RegisterClassExW(&wcex);
	};

	auto InitInstance =[](HINSTANCE hInstance, int nCmdShow) -> BOOL
	{
		g_Inst = hInstance;

		HWND hWnd = CreateWindowExW( WS_EX_TOPMOST , szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400 , 600, nullptr, nullptr, hInstance, nullptr);

		if (!hWnd)
		{
			return FALSE;
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		return TRUE;
	};

	// Initialize global strings
	DoRegisterClass( hInstance );

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK GamepadToKeyReceiver_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		RECT DisplayRect;
		GetClientRect( hWnd , &DisplayRect );

		TEXTMETRICW TextMetrics;
		GetTextMetricsW( hdc , &TextMetrics );

		INT Offset = 0;
		for( const std::wstring& Line : g_InputHistory )
		{
			RECT DrawRect = DisplayRect;
			DrawRect.top += Offset;
			DrawTextW( hdc , Line.c_str() , -1 , &DrawRect , 0 );
			Offset += TextMetrics.tmHeight;
		}

		EndPaint(hWnd, &ps);
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
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

		gptkKeyLParam Info;
		union gptkKeyLParamConverter
		{
			LPARAM lParam;
			gptkKeyLParam AsStruct;
		};

		gptkKeyLParamConverter lParam2;
		lParam2.lParam = lParam;

		WCHAR KeyName[256];
		GetKeyNameTextW( lParam , KeyName , sizeof(KeyName)/sizeof(KeyName[0]) );

		WCHAR Desc[256];
		_swprintf( Desc , L"%s (%u,0x%X,%u) %s" , KeyName , wParam , wParam , lParam2.AsStruct.ScanCode, (WM_KEYDOWN == message ? L"DOWN" : L"UP") );

		std::wstring CmdText = Desc;

		g_InputHistory.push_back( CmdText );

		if( g_InputHistory.size() > 30 )
		{
			g_InputHistory.erase( g_InputHistory.begin() );
		}
		
		InvalidateRect( hWnd , nullptr , true );
		UpdateWindow( hWnd );
		//RedrawWindow( hWnd , nullptr , nullptr , RDW_ERASE|RDW_UPDATENOW );

	} break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}
