// TexView3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TexView3.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "TexView3Doc.h"
#include "TexView3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTexView3App

BEGIN_MESSAGE_MAP(CTexView3App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTexView3App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CTexView3App::OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CTexView3App::OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CTexView3App::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CTexView3App::OnUpdateFileSaveAs)
END_MESSAGE_MAP()


// CTexView3App construction

CTexView3App::CTexView3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTexView3App object

CTexView3App theApp;


// CTexView3App initialization

BOOL CTexView3App::InitInstance()
{
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
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Beem Software"));
	LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_TexView3TYPE,
		RUNTIME_CLASS(CTexView3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTexView3View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	
	BOOL bUnreg=FALSE;
	RegisterFileType(_T(".tga"), bUnreg);
	RegisterFileType(_T(".bmp"), bUnreg);
	RegisterFileType(_T(".jpg"), bUnreg);
	RegisterFileType(_T(".gif"), bUnreg);
	RegisterFileType(_T(".png"), bUnreg);
	//SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//Insure that a blank document is not created if we are not loading
	//something right away.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CTexView3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTexView3App message handlers


void CTexView3App::OnFileOpen()
{
	LPCTSTR pszFilter = 
		_T("TexView3 Files (*.tga;*.bmp;*.dib;*.gif;*.jpg; *.png)|*.tga;*.bmp;*.dib;*.gif;*.jpg;*.png|")
		_T("All files (*.*)|*.*||");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_EXPLORER|OFN_ALLOWMULTISELECT, pszFilter, AfxGetMainWnd());

	if(IDOK == dlgFile.DoModal())
	{
		POSITION ps(dlgFile.GetStartPosition());
		while(ps)
		{
			OpenDocumentFile(dlgFile.GetNextPathName(ps));
		}
	}
}

void CTexView3App::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CTexView3App::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CTexView3App::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

BOOL CAboutDlg::OnInitDialog()
{
	#define TEXVIEW3_VERSION _T("1.01")
	CDialog::OnInitDialog();

	this->SetDlgItemText(
		IDC_VERSIONTEXT, 
		_T("Version ")TEXVIEW3_VERSION _T(" ")
		#ifdef UNICODE 
		_T("(UNICODE)"));
		#else UNICODE
		_T("(ANSI)"));
		#endif UNICODE


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTexView3App::RegisterFileType(LPTSTR szExt, BOOL bUnReg)
{
	HKEY hKey=NULL;
	TCHAR szModPath[MAX_PATH];
	GetModuleFileName(NULL, szModPath, MAX_PATH);
	
	if(szExt[0]!='.')
		return;
		
	RegOpenKeyEx(HKEY_CLASSES_ROOT, szExt, 0, KEY_ALL_ACCESS, &hKey);

	if(hKey)
	{
		//If the file type is already registered we will 
		//add the command to open with texture viewer.
		CString szKey;
		//CString szBaseKey;
		CString szKeyValue;
		HKEY    hBaseKey=NULL;
		#define MAX_KEY_LENGTH 1024
		DWORD dwSize=MAX_KEY_LENGTH*sizeof(TCHAR);
		DWORD dwType=0;
		RegQueryValueEx(hKey, NULL, NULL, &dwType, (LPBYTE)szKey.GetBuffer(MAX_KEY_LENGTH), &dwSize);
		RegCloseKey(hKey);
		
		//If the image is registered as a TexView3.Document we
		//don't need to do anything.
		if(szKey.Compare(_T("TexView3.Document"))==0)
			return;
			
		CString szCommand;
		szCommand.Format(_T("TexView3"));//_T("Open with %s"), AfxGetAppName());
		szKey.Format(_T("%s\\shell\\%s"), szKey, szCommand);
		RegCreateKeyEx(HKEY_CLASSES_ROOT, szKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hBaseKey, NULL);
		if(!hBaseKey)
			return;
			
		if(bUnReg)
		{
			RegDeleteKey(hBaseKey, _T("command"));
			RegDeleteKey(hBaseKey, _T("ddeexec\\application"));
			RegDeleteKey(hBaseKey, _T("ddeexec"));
			RegCloseKey(hBaseKey);
			RegDeleteKey(HKEY_CLASSES_ROOT, szKey);
			return;
		}	
		//Register the command.
		RegCreateKeyEx(hBaseKey, _T("command"), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		szKeyValue.Format(_T("\"%s\" \"%%1\""), szModPath);
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szKeyValue.GetBuffer(), (DWORD)(szKeyValue.GetLength()+1)*sizeof(TCHAR));
		RegCloseKey(hKey);
		//Register the dde open command.
		RegCreateKeyEx(hBaseKey, _T("ddeexec"), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		szKeyValue.Format(_T("[open(\"%%1\")]"), szModPath);
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szKeyValue.GetBuffer(), (DWORD)(szKeyValue.GetLength()+1)*sizeof(TCHAR));
		RegCloseKey(hKey);
		/*
		//Register the dde app name (optional).
		RegCreateKeyEx(hBaseKey, _T("ddeexec\\application"), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		szKeyValue.Format(_T("TexView3"), szModPath);
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szKeyValue.GetBuffer(), (DWORD)(szKeyValue.GetLength()+1)*sizeof(TCHAR));
		RegCloseKey(hKey);
		*/
		
		RegCloseKey(hBaseKey);
	}
	else
	{
		if(bUnReg)
			return;
			
		//If the file type hasn't been register we attach it
		//to the TexView3.Document type.
		RegCreateKeyEx(HKEY_CLASSES_ROOT, szExt, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		CString szKeyValue=_T("TexView3.Document");
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szKeyValue.GetBuffer(), (szKeyValue.GetLength()+1)*sizeof(TCHAR));
		RegCloseKey(hKey);
	}
}
