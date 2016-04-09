
// CornerBin.h : main header file for the CornerBin application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "cbsettings.h"
#include "cbtrayicon.h"


// CCornerBinApp:
// See CornerBin.cpp for the implementation of this class
//

class CCornerBinApp : public CWinApp
{
public:
	CCornerBinApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOpenSettings();
	afx_msg void OnOpenRB();
	afx_msg void OnEmptyRB();
private:
	CCBSettings m_Settings;
	CCBTrayIcon m_CBTrayIcon;
public:
	void OnDblClkTrayIcon(void);
	void OnTimerUpdate(void);
	void OpenSettingsDlg(void);
private:
	// This mutex keeps track if the application is running, so that two copies are not run simoltaneously.
	HANDLE m_hMutex;
};

extern CCornerBinApp theApp;
