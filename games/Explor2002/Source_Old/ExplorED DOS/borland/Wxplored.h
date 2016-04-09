/*
	wxplored.h - Header for WinExplorED
*/
BOOL RegisterWindowClass(void);
LRESULT MainWindowProc(HWND hWnd, unsigned msg, WORD wParam, LONG lParam);
void MainWindowPaint(HWND hWnd, HDC hDc);
BOOL MainCommandProc(HWND hMainWnd, WORD wCommand, WORD wNotify, HWND hControl);
int GetOpenFileName(HWND hWnd, char *filename);
int GetSaveFileName(HWND hWnd, char *filename);