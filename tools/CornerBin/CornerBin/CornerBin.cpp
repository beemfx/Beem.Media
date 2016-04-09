
// CornerBin.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CornerBin.h"
#include "MainFrm.h"
#include "DlgSettings.h"

LPCTSTR g_strAPP_GUID = _T("{7368B213-598B-4240-8C94-65420F2F9B3D}");


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCornerBinApp

BEGIN_MESSAGE_MAP(CCornerBinApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCornerBinApp::OnAppAbout)
	ON_COMMAND(ID_OPEN_SETTINGS, &CCornerBinApp::OnOpenSettings)
	ON_COMMAND(ID_OPEN_R_B, &CCornerBinApp::OnOpenRB)
	ON_COMMAND(ID_EMPTY_R_B, &CCornerBinApp::OnEmptyRB)
END_MESSAGE_MAP()


// CCornerBinApp construction

CCornerBinApp::CCornerBinApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("Beem Software.CornerBin.1.0.0"));
}

// The one and only CCornerBinApp object

CCornerBinApp theApp;


// CCornerBinApp initialization

BOOL CCornerBinApp::InitInstance()
{
	//Load up the settings file:
	m_Settings.LoadSettings();

	CString strCmdLine(m_lpCmdLine);
	
	if(-1 != strCmdLine.Find(_T("-settings")))
	{
		//See if an application is already running, if it
		//is, just have the currently running app open it's
		//settings dailaog box:
		HWND hwnd = ::FindWindow(g_strAPP_GUID, NULL);
		if(hwnd)
		{
			PostMessage(hwnd, WM_EXTSETTINGSUP, 0, 0);
			return FALSE;
		}
		else
		{
			CDlgSettings dlg(NULL, &m_Settings);
			dlg.DoModal();
		}
	}

	//Single instance at a time code:
	{

		//We'll create a mutex to make sure only one copy of the app runs at a time.
		CString strMutexName(g_strAPP_GUID);
		//The mutex name will append the user name, that way the program can still
		//be run by more than one user simoltaneously.
		TCHAR strTemp[UNLEN + 1];
		DWORD nLen = UNLEN;
		::GetUserName(strTemp, &nLen);
		strMutexName.Append(strTemp);
		m_hMutex = ::CreateMutex(NULL, FALSE, strMutexName);
		if(ERROR_ALREADY_EXISTS == GetLastError())
		{
			::AfxMessageBox(_T("CornerBin is already running."));
			return FALSE;
		}
	}

	
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame(&m_Settings);
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MENU_CORNERBIN,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	//Load up the tray icon:
	m_CBTrayIcon.Init(m_hInstance, m_pMainWnd->m_hWnd, &m_Settings);

	//With the settings loaded we can start the main window timer to query
	//the status of the recycle bin.
	pFrame->SetTimerUpdate(m_Settings.GetUpdateFreq());



	//We insure that the main window is never visible.
	pFrame->ShowWindow(SW_HIDE);
	//pFrame->ShowWindow(SW_SHOW);
	//pFrame->UpdateWindow();
	
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

int CCornerBinApp::ExitInstance()
{
	//TODO: handle additional resources you may have added

	//Go ahead and save the current settings, just in case they were never saved.
	m_Settings.SaveSettings();
	//Destroy the icon as well...
	m_CBTrayIcon.UnInit();

	AfxOleTerm(FALSE);

	//Destroy our mutex so the app may run again.
	CloseHandle(m_hMutex);

	return CWinApp::ExitInstance();
}

// CCornerBinApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CCornerBinApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCornerBinApp message handlers





void CCornerBinApp::OnOpenSettings()
{
	OpenSettingsDlg();
}


void CCornerBinApp::OnOpenRB()
{
	/*
	LPITEMIDLIST pidRecycle;
	//SHGetSpecialFolderLocation(NULL, CSIDL_BITBUCKET, &pidRecycle) ;
	SHELLEXECUTEINFO EI;
	memset(&EI, 0, sizeof(EI));
	EI.cbSize = sizeof(EI);
	EI.fMask = SEE_MASK_IDLIST;
	EI.nShow = SW_SHOWNORMAL;
	EI.lpIDList = &pidRecycle;
	ShellExecuteEx(&EI);
	*/
	
	//I don't necessarily like this code, because future versions of windows may not use the same identifier for the trash bin.
	ShellExecute(NULL, NULL, TEXT("::{645FF040-5081-101B-9F08-00AA002F954E}"), NULL, NULL, SW_SHOWNORMAL);
}


void CCornerBinApp::OnEmptyRB()
{
	//Note the prompt is determined by the settings:
	if(this->m_CBTrayIcon.IsRBFull())
		::SHEmptyRecycleBin(NULL, NULL, (m_Settings.GetEmptyPrompt()?0:SHERB_NOCONFIRMATION));

	//Also, we'll always update the icon to insure an immediate change.
	this->OnTimerUpdate();
}


void CCornerBinApp::OnDblClkTrayIcon(void)
{
	//Depending on the settings we decide what to do...
	if(m_Settings.GetOpenOnDblClk())
	{
		//Open the recycle bin
		this->OnOpenRB();
	}
	else
	{
		//Open the settings dialog
		OpenSettingsDlg();
		
	}
}


void CCornerBinApp::OnTimerUpdate(void)
{
	m_CBTrayIcon.Update();
}


void CCornerBinApp::OpenSettingsDlg(void)
{
	CDlgSettings dlgSettings(m_pMainWnd, &m_Settings);
	if(IDOK == dlgSettings.DoModal())
	{
		//At this point we should update any changes that may have occured.
		//Might actually want to have a function that simple updates since this
		//current code makes the icon dissapear then reapear.
		m_CBTrayIcon.UnInit();
		m_CBTrayIcon.Init(this->m_hInstance, this->m_pMainWnd->m_hWnd, &m_Settings);
	}
}
