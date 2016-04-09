#pragma once
#include "CBSettings.h"
class CCBTrayIcon
{
public:
	CCBTrayIcon(void);
	~CCBTrayIcon(void);
	BOOL Init(HINSTANCE hInst, HWND hwndParent, CCBSettings* pSettings);
private:
	enum ICON_TYPE
	{
		ICON_FILE,
		ICON_INDLL
	};
	static const DWORD s_nUEID;
	static const GUID s_GUID;
	static const DWORD s_nVERSION = NOTIFYICON_VERSION;

	HICON m_IcoFull;
	HICON m_IcoEmpty;
	CCBSettings* m_pSettings;
public:
	void Update(void);
private:
	// Tracks if there are currently items in the RB
	BOOL m_bIsFull;
public:
	static BOOL IsRBFull(void);
public:
	HICON LoadIcon2(LPCTSTR strIcon);
	void LoadIcons(void);
	void UnInit(void);
private:
	HWND m_hwndParent;
};

