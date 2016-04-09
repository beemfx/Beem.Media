
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CornerBin.h"

#include "MainFrm.h"

extern LPCTSTR g_strAPP_GUID;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame(CCBSettings* pSettings)
	: m_pSettings(NULL)
{
	m_pSettings = pSettings;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	WNDCLASS cls;
	memset(&cls, 0, sizeof(cls));
	cls.lpfnWndProc = AfxWndProc;
	cls.hInstance = cs.hInstance;
	cls.lpszClassName = g_strAPP_GUID;
	AfxRegisterClass(&cls);

	cs.style = 0;
	cs.dwExStyle =0;
	cs.lpszClass = g_strAPP_GUID;//AfxRegisterWndClass(0);
	cs.lpszName = _T("CornerBin");


	

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
		//Now process our custom messages
	if(WM_SYSTRAYNOTIFY == message)
	{
		switch(lParam)
		{
		case WM_RBUTTONDOWN:
		{
			DWORD nMenu = m_pSettings->GetSimpleMenu()?1:0;

			//Setting this to the foreground window insures that the menu will dissapear when clicked outside.
			this->SetForegroundWindow();

			POINT pnt;
			GetCursorPos(&pnt);
			this->GetMenu()->GetSubMenu(nMenu)->TrackPopupMenu(
				TPM_BOTTOMALIGN|TPM_RIGHTALIGN, 
				pnt.x, 
				pnt.y, 
				this);

			//The null message insures that the popup doesn't dissapear right away.
			this->PostMessage(WM_NULL);
		}
		break;

		case WM_RBUTTONDBLCLK:
			//Should open up the settings box.
			((CCornerBinApp*)::AfxGetApp())->OpenSettingsDlg();
			break;
		case WM_LBUTTONDBLCLK:
			((CCornerBinApp*)::AfxGetApp())->OnDblClkTrayIcon();

		break;
		
		}
		return TRUE;
	}
	else if (WM_EXTSETTINGSUP == message)
	{
		((CCornerBinApp*)::AfxGetApp())->OpenSettingsDlg();
		return TRUE;
	}

	return CFrameWnd::OnWndMsg(message, wParam, lParam, pResult);
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if(UPDATE_TIMER_ID == nIDEvent)
	{
		((CCornerBinApp*)::AfxGetApp())->OnTimerUpdate();
	}

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::SetTimerUpdate(DWORD nFreq)
{
	if(0 == nFreq)
		this->KillTimer(UPDATE_TIMER_ID);
	else
		this->SetTimer(UPDATE_TIMER_ID, nFreq, 0);
}
