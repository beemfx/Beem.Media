// TexView3.h : main header file for the TexView3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTexView3App:
// See TexView3.cpp for the implementation of this class
//

class CTexView3App : public CWinApp
{
public:
	CTexView3App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
public:
	void RegisterFileType(LPTSTR szExt, BOOL bUnReg=FALSE);//, LPTSTR szDesc, LPTSTR szText, DWORD nIcon);
};

extern CTexView3App theApp;