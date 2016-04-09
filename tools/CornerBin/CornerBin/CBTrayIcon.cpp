#include "StdAfx.h"
#include "Resource.h"
#include "CBTrayIcon.h"
const DWORD CCBTrayIcon::s_nUEID = 0xACE48A8F;

#ifdef _DEBUG
const GUID CCBTrayIcon::s_GUID = { 0xbc1e76d3, 0x6229, 0x4f4c, { 0xb9, 0x7f, 0xd3, 0x78, 0xb8, 0xb9, 0x68, 0xbe } };
#else
const GUID CCBTrayIcon::s_GUID = { 0x3479e298, 0x417e, 0x4938, { 0x95, 0x1b, 0x13, 0xf, 0xa1, 0xf7, 0x21, 0x7 } };
#endif

#define NIF_USING_GUID 0//NIF_GUID



CCBTrayIcon::CCBTrayIcon(void)
	: m_pSettings(NULL)
	, m_bIsFull(FALSE)
	, m_IcoEmpty(NULL)
	, m_IcoFull(NULL)
{

}


CCBTrayIcon::~CCBTrayIcon(void)
{


}


BOOL CCBTrayIcon::Init(HINSTANCE hInst, HWND hwndParent, CCBSettings* pSettings)
{
	m_pSettings = pSettings;
	m_hwndParent = hwndParent;

	LoadIcons();

	NOTIFYICONDATA NoteData;
	memset(&NoteData, 0, sizeof(NoteData));

	NoteData.cbSize = NOTIFYICONDATA_V3_SIZE;
	NoteData.uVersion = s_nVERSION;
	NoteData.hWnd = hwndParent;
	NoteData.uID  = s_nUEID;
	NoteData.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_USING_GUID;
	NoteData.hIcon = IsRBFull()?m_IcoFull:m_IcoEmpty;
	NoteData.guidItem = s_GUID;
	NoteData.uCallbackMessage = WM_SYSTRAYNOTIFY;
	_tcscpy_s(NoteData.szTip, 63, m_pSettings->GetTooTip());

	BOOL bRes = Shell_NotifyIcon(NIM_ADD, &NoteData);

	if(!bRes)
		AfxMessageBox(TEXT("Could not init tray icon."));

	Update();
	return bRes;
}

void CCBTrayIcon::UnInit(void)
{
	NOTIFYICONDATA NoteData;
	memset(&NoteData, 0, sizeof(NoteData));

	NoteData.cbSize = NOTIFYICONDATA_V3_SIZE;
	NoteData.uVersion = s_nVERSION;
	NoteData.hWnd = m_hwndParent;
	NoteData.uFlags = NIF_USING_GUID;
	NoteData.uID  = s_nUEID;
	NoteData.guidItem = s_GUID;

	Shell_NotifyIcon(NIM_DELETE, &NoteData);

	//Make sure any currently loaded icons are destroyed:
	::DestroyIcon(m_IcoFull);
	::DestroyIcon(m_IcoEmpty);
	m_IcoFull = NULL;
	m_IcoEmpty = NULL;
}



void CCBTrayIcon::Update(void)
{
	//Update is called as often as the application wishes.
	//It checks the status of the RB and changes the icon if necessary.
	BOOL bIsFull = IsRBFull();
	if(m_bIsFull != bIsFull)
	{
		//The status is changed, so we should change the state and icon.
		m_bIsFull = bIsFull;
		//And set the chosen icon:
		NOTIFYICONDATA NoteData;
		memset(&NoteData, 0, sizeof(NoteData));

		NoteData.cbSize = NOTIFYICONDATA_V3_SIZE;
		NoteData.uVersion = s_nVERSION;
		NoteData.hWnd = m_hwndParent;
		NoteData.uFlags = NIF_ICON|NIF_USING_GUID;
		NoteData.uID  = s_nUEID;
		NoteData.guidItem = s_GUID;
		NoteData.hIcon  = m_bIsFull?m_IcoFull:m_IcoEmpty;
		Shell_NotifyIcon(NIM_MODIFY, &NoteData);
	}
}


BOOL CCBTrayIcon::IsRBFull(void)
{
	::SHQUERYRBINFO RBInfo;
	memset(&RBInfo, 0, sizeof(RBInfo));
	RBInfo.cbSize = sizeof(RBInfo);
	::SHQueryRecycleBin(NULL, &RBInfo);

	return (RBInfo.i64NumItems != 0);
}


HICON CCBTrayIcon::LoadIcon2(LPCTSTR strIcon)
{
	//This function loads an icon based upon the string specification, or returns NULL if it couldn't.
	//The string specification is as follows
	//("(iconpath)"(:(resourcenumber))?)
	//That is, a path is always specified, and a resource number is specified if the path was a dll or other library.
	CString strIconC = strIcon;

	DWORD nResID = 0;

	int nToken=0;
	CString strPath = strIconC.Tokenize(_T("|"), nToken);
	if(-1 == nToken)
		return NULL;

	CString strResID = strIconC.Tokenize(_T("|"), nToken);
	
	nResID = (nToken != -1)?_ttoi(strResID):0xFFFFFFFF;

	
	///CString strMsg;
	///strMsg.Format(_T("The path is \"%s\" the res id is %d"), strPath, nResID);
	///::AfxMessageBox(strMsg);
	

	//If no resource id was specified, the icon should just be a file:
	HICON hIcon[1] = {NULL};
	if(0xFFFFFFFF == nResID)
	{
		hIcon[0] = ::LoadIcon(NULL, strPath);
	}
	else
	{
		::ExtractIconEx(strPath, nResID, NULL, hIcon, 1);
	}

	return hIcon[0];
}


void CCBTrayIcon::LoadIcons(void)
{
	//Make sure any currently loaded icons are destroyed:
	::DestroyIcon(m_IcoFull);
	::DestroyIcon(m_IcoEmpty);
	m_IcoFull = NULL;
	m_IcoEmpty = NULL;
	
	m_IcoFull = this->LoadIcon2(m_pSettings->GetFullIcon());
	m_IcoEmpty = this->LoadIcon2(m_pSettings->GetEmptyIcon());

	//If no icon was loaded, we load the default icons.
	if(NULL == m_IcoFull)
		m_IcoFull = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEFF), IMAGE_ICON, 16, 16, 0);


	if(NULL == m_IcoEmpty)
		m_IcoEmpty = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEFE), IMAGE_ICON, 16, 16, 0);
}


