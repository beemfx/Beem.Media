/*
	wxplored.h - Header for WinExplorED
*/
#ifndef __WXPLORED_H__
#define __WXPLORED_H__

enum LASTMOVETYPE{SAVE, EDIT, OPEN};
void EditWindowPaint(HWND hWnd, int minX, int minY);
BOOL RegisterEditWindowClass(void);
BOOL RegisterWindowClass(void);
//BOOL RegisterStatusWindowClass(void);
LRESULT MainWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT EditWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL MainCommandProc(HWND hMainWnd, WORD wCommand, WORD wNotify, HWND hControl);
int GetOpenFileName(HWND hWnd, char *filename);
int GetSaveFileName(HWND hWnd, char *filename);
BOOL HorzScrollManager(HWND hWnd, WORD nScrollCode);
BOOL TranslatePoints(HWND hWnd, POINTS &points);
BOOL VertScrollManager(HWND hWnd, WORD nScrollCode);
BOOL UpdateScrollBar(HWND hWnd);
#endif