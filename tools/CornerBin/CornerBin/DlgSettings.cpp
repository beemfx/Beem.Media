// DlgSettings.cpp : implementation file
//

#include "stdafx.h"
#include "CornerBin.h"
#include "DlgSettings.h"
#include "afxdialogex.h"
#include "IconDlg/IconDlg.h"


// CDlgSettings dialog

IMPLEMENT_DYNAMIC(CDlgSettings, CDialogEx)

CDlgSettings::CDlgSettings(CWnd* pParent, CCBSettings* pSettings)
	: CDialogEx(CDlgSettings::IDD, pParent)
	, m_pSettings(NULL)
{
	m_pSettings = pSettings;
}

CDlgSettings::~CDlgSettings()
{
}

void CDlgSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CCBSettings::SSettings Settings;
	m_pSettings->GetSettings(&Settings);
	::DDX_Text(pDX, IDC_TXTEICON, Settings.m_strEmptyIcon);
	::DDX_Text(pDX, IDC_TXTFICON, Settings.m_strFullIcon);
	::DDX_Text(pDX, IDC_TXTTOOLTIP, Settings.m_strToolTip);
	::DDX_Check(pDX, IDC_CHKEMPTYPROMPT, (int&)Settings.m_bEmptyPrompt);
	::DDX_Check(pDX, IDC_CHKDBLCLKRB, (int&)Settings.m_bOpenRBOnDblClk);
	//::DDX_Check(pDX, IDC_CHKSTARTWITHWINDOWS, (int&)bStartWithWindows);
	::DDX_Check(pDX, IDC_CHKSIMPLEMENU, (int&)Settings.m_bSimpleMenu);
	m_pSettings->SetSettings(&Settings);

	//Decide what to do with the start with windows button.
	if(pDX->m_bSaveAndValidate)
	{
		SetStartWithWindows(IsDlgButtonChecked(IDC_CHKSTARTWITHWINDOWS));
	}
	else
	{
		this->CheckDlgButton(IDC_CHKSTARTWITHWINDOWS, this->IsStartWithWindowsSet());
	}
}

BEGIN_MESSAGE_MAP(CDlgSettings, CDialogEx)
	ON_BN_CLICKED(IDC_BTNBROWSEE, &CDlgSettings::OnBnClickedBtnbrowsee)
	ON_BN_CLICKED(IDC_BTNBROWSEF, &CDlgSettings::OnBnClickedBtnbrowsef)
	ON_BN_CLICKED(IDC_BTNSYSEMPTY, &CDlgSettings::OnBnClickedBtnsysempty)
	ON_BN_CLICKED(IDC_BTNSYSFULL, &CDlgSettings::OnBnClickedBtnsysfull)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTNDEFS, &CDlgSettings::OnBnClickedBtndefs)
END_MESSAGE_MAP()


// CDlgSettings message handlers



void CDlgSettings::OnBnClickedBtnbrowsee()
{
	BrowseForIcon(IDC_TXTEICON);
}


void CDlgSettings::BrowseForIcon(int nCtrlID)
{
	CIconDialog dlg(this);
	CString strFile, strResID;
	CString strText;
	this->GetDlgItemText(nCtrlID, strText);
	int n = 0;
	strFile = strText.Tokenize(_T("|"), n);
	if(-1 == n)
	{
		strResID = _T("");
	}
	else
	{
		strResID = strText.Tokenize(_T("|"), n);
	}
	dlg.SetIcon(strFile, _ttol(strResID));

	if (dlg.DoModal() == IDOK)
	{
		dlg.GetIcon(strFile, n);
		//Form the new string.
		strText.Format(_T("%s|%d"), strFile, n);
		this->SetDlgItemText(nCtrlID, strText);
	}
}


void CDlgSettings::OnBnClickedBtnbrowsef()
{
	BrowseForIcon(IDC_TXTFICON);
}


void CDlgSettings::OnBnClickedBtnsysempty()
{
	// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\CLSID\{645FF040-5081-101B-9F08-00AA002F954E}\DefaultIcon
	CRegKey Key;
	Key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon"));
	ULONG nChars = 1023;
	TCHAR strTemp[1024] = { 0 };
	Key.QueryStringValue(_T("empty"), strTemp, &nChars);
	CString strIcon(strTemp);
	
	int n = strIcon.Find(_T(","));
	if(-1 != n)
	{
		strIcon.SetAt(n, '|');
		//strIcon.Delete(n+1);
		
	}
	this->SetDlgItemText(IDC_TXTEICON, strIcon);
	Key.Close();

}


void CDlgSettings::OnBnClickedBtnsysfull()
{
	// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\CLSID\{645FF040-5081-101B-9F08-00AA002F954E}\DefaultIcon
	CRegKey Key;
	Key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon"));
	ULONG nChars = 1023;
	TCHAR strTemp[1024] = { 0 };
	Key.QueryStringValue(_T("full"), strTemp, &nChars);
	CString strIcon(strTemp);
	
	int n = strIcon.Find(_T(","));
	if(-1 != n)
	{
		strIcon.SetAt(n, '|');
		//strIcon.Delete(n+1);
		
	}
	this->SetDlgItemText(IDC_TXTFICON, strIcon);
	Key.Close();
}


void CDlgSettings::SetStartWithWindows(BOOL bStartWith)
{
	//MessageBox(_T("Here!"));
	//We add the startup registry entry, or remove it, as soon as this button is clicked.
	CRegKey Key;
	Key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));

	if(bStartWith)
	{
		//Add the startup key.
		//We need to get the path:
		CString strExec;
		::AfxGetModuleFileName(NULL, strExec);
		strExec.Insert(0, '"');
		strExec.Append(_T("\""));

		Key.SetStringValue(_T("CornerBin"), strExec);
	}
	else
	{
		Key.DeleteValue(_T("CornerBin"));
	}

	Key.Close();
}


BOOL CDlgSettings::IsStartWithWindowsSet(void)
{
	//Just need to check to see if the key exists.
	CRegKey Key;
	Key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	BOOL bRes = ERROR_SUCCESS == Key.QueryValue(_T("CornerBin"), NULL, NULL, NULL);
	Key.Close();
	return bRes;
}




void CDlgSettings::OnBnClickedBtndefs()
{
	this->CheckDlgButton(IDC_CHKEMPTYPROMPT, 1);
	this->CheckDlgButton(IDC_CHKDBLCLKRB, 1);
	this->CheckDlgButton(IDC_CHKSTARTWITHWINDOWS, 0);
	this->CheckDlgButton(IDC_CHKSIMPLEMENU, 0);

	this->SetDlgItemText(IDC_TXTEICON, _T(""));
	this->SetDlgItemText(IDC_TXTFICON, _T(""));
	this->SetDlgItemText(IDC_TXTTOOLTIP, _T("Recycle Bin"));
}
