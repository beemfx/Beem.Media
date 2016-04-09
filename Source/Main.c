/*
	Quick and Dirty Application installer 
	
	Copyright (c) 2003 Blaine Myers
*/

#include "directoryex.h"
#include <tchar.h>
#include <windows.h>
#include "resource.h"

TCHAR szProgramName[MAX_PATH];
TCHAR szDefaultInstall[MAX_PATH];
TCHAR szInstallFrom[MAX_PATH];
TCHAR szAppToRun[MAX_PATH];
BOOL bRunApp=FALSE;

typedef enum tagLINECOMMAND{
	LC_NOCOMMAND=0,
	LC_NAME,
	LC_INSTALLTO,
	LC_INSTALLFROM,
	LC_APPTORUN
}LINECOMMAND;


#define WM_CONTINUEINSTALL (WM_USER+0x0001)

#define PRODUCT_VERSION TEXT("version 0.50")

BOOL InstallApp(LPTSTR szSource, LPTSTR szDest, HWND hwnd){	
	/*
		First we make see if the dest directory already
		exists.  If it does we prompt if the user wants to
		copy over it.  Then we go ahead and copy the directory.
	*/

	if(SetCurrentDirectory(szDest)){
		int nMBResult=0;
		nMBResult=MessageBox(
			hwnd, 
			TEXT("The specified directory already exists!  Overwrite?"), 
			TEXT("Notice"), 
			MB_YESNO|MB_ICONEXCLAMATION);

		if(nMBResult == IDNO)return FALSE;
	}

	SetDlgItemText(hwnd, IDC_COPYINGWORD, TEXT("Copying: Please wait!"));
	if(SUCCEEDED(CopyDirectory(szSource, szDest, FILE_ATTRIBUTE_NORMAL))){
		SetDlgItemText(hwnd, IDC_COPYINGWORD, TEXT(""));
		return TRUE;
	}else{
		MessageBox(
			hwnd,
			TEXT("An error occured while attempting to copy the directory!"),
			TEXT("Notice"),
			MB_OK|MB_ICONERROR);

		return FALSE;
	}
}

BOOL ReadLine(LPTSTR szLine, HANDLE hFile){
	/*Read until encounter ';', or there is no more file to read. */
	int i=0;
	TCHAR cChar=0;
	DWORD dwBytesRead=0;
	BOOL bInQuotes=FALSE;
	DWORD dwCurrentPosition=0;
	do{
		/*
			Here we make sure there is enough of the file left to read.
			If there isn't we return FALSE indicating the reading of the lines is done.
		*/
		dwCurrentPosition=SetFilePointer(hFile, 0, 0, FILE_CURRENT);
		if( dwCurrentPosition > (SetFilePointer(hFile, 0, 0, FILE_END)-sizeof(TCHAR)) ) return FALSE;
		SetFilePointer(hFile, dwCurrentPosition, 0, FILE_BEGIN);

		if(!ReadFile(hFile, &cChar, sizeof(TCHAR), &dwBytesRead, NULL)){
			/*If can't read line we're probably at the end of the file */
			_tcscpy(szLine, TEXT(""));
			return FALSE;
		}
		if((cChar == '"')){
			if(bInQuotes)bInQuotes=FALSE;
			else bInQuotes=TRUE;
		}
		if( (cChar != '\n') && (cChar != '\r') && (cChar != '\t')){
			if( !((!bInQuotes) && (cChar==' '))){
				szLine[i]=cChar;
				i++;
			}
		}
	}while(cChar != L';');
	szLine[i-1]=0;

	return TRUE;
}


/*
	GetString retrieves all data inside quotes in a string.
*/
BOOL GetString(TCHAR szLineOut[MAX_PATH], TCHAR szLineIn[MAX_PATH]){
	TCHAR szFinalLine[MAX_PATH];
	DWORD i=0, j=0;
	BOOL bInQuotes=FALSE;

	for(i=0, j=0; i<MAX_PATH; i++){
		if(szLineIn[i]==0)break;
		if(szLineIn[i]=='"'){
			if(bInQuotes)
				bInQuotes=FALSE;
			else bInQuotes=TRUE;

			continue;
		}
		if(bInQuotes){
			szFinalLine[j]=szLineIn[i];
			j++;
		}
	}

	szFinalLine[j]=0;
	_tcscpy(szLineOut, szFinalLine);
	return TRUE;
}

/*
	This changes a parsed string, into it's signal string.
*/
DWORD ConvertParsedString(TCHAR szLineOut[MAX_PATH], TCHAR szLineIn[MAX_PATH]){
	/* Here we convert a parse command into a new string! */
	TCHAR szFinal[MAX_PATH];
	TCHAR szTemp[MAX_PATH];

	if(_tcsicmp(szLineIn, TEXT("defaultdrive"))==0){
		GetWindowsDirectory(szTemp, MAX_PATH);
		szFinal[0]=szTemp[0];
		szFinal[1]=':';
		szFinal[2]=0;
	}else if(_tcsicmp(szLineIn, TEXT("currentdir"))==0){
		GetCurrentDirectory(MAX_PATH, szFinal);
	}else{
		_tcscpy(szFinal, TEXT(""));
	}
	if(szFinal[_tcslen(szFinal)-1]==TEXT('\\')){
		szFinal[_tcslen(szFinal)-1]=0;
	}
	_tcscpy(szLineOut, szFinal);
	return _tcslen(szLineOut);
}
/*
	This changes all parsed strings into their final strings.
*/
BOOL ParseCommandString(TCHAR szLineOut[MAX_PATH], TCHAR szLineIn[MAX_PATH]){
	/* _tcscpy(szLineOut, TEXT("This string was parsed!")); */
	/*
	To parse a string we change everything inside a %xxx% into
	it's equivilant string.
	*/
	DWORD i=0, j=0, k=0;
	TCHAR szParsedLine[MAX_PATH];
	TCHAR szParseCommand[MAX_PATH];
	DWORD dwParsedLen=0;

	for(i=0, j=0, k=0; i<MAX_PATH; i++, j++){
		if(szLineIn[i]=='%'){
			/* We need to parse */
			do{
				i++;
				szParseCommand[k]=szLineIn[i];
				k++;
			}while (szLineIn[i]!='%');
			szParseCommand[k-1]=0;
			/* Here we should parse the line */
			dwParsedLen=ConvertParsedString(szParseCommand, szParseCommand);
			for(k=0; k<dwParsedLen; k++, j++){
				szParsedLine[j]=szParseCommand[k];
			}
			i++;
		}

		szParsedLine[j]=szLineIn[i];
		if(szLineIn[i]==0)break;
	}
	szParsedLine[j]=0;
	_tcscpy(szLineOut, szParsedLine);
	return TRUE;
}

LINECOMMAND ProccessLine(TCHAR szLine[MAX_PATH]){
	/*
	To find out what the command is, we
	read the line until we encounter a '=' or
	a 0 (zero).
	*/
	TCHAR szCommand[MAX_PATH];
	DWORD i=0;
	DWORD nStringOffset;
	BOOL bString=FALSE;
	LINECOMMAND nCommand=0;

	for(i=0; i<MAX_PATH; i++){
		if( (szLine[i]=='=') || (szLine[i]==0) ){
			if(szLine[i]=='='){
				bString=TRUE;
				nStringOffset=i+1;
			}
			szCommand[i]=0;
			break;
		}
		szCommand[i]=szLine[i];
	}
	/* We now have the command, lets procces it */
	if(_tcsicmp(szCommand, TEXT("name"))==0)nCommand =LC_NAME;
	else if(_tcsicmp(szCommand, TEXT("installto"))==0)nCommand = LC_INSTALLTO;
	else if(_tcsicmp(szCommand, TEXT("installfrom"))==0)nCommand = LC_INSTALLFROM;
	else if(_tcsicmp(szCommand, TEXT("runonexit"))==0)nCommand = LC_APPTORUN;
	else return LC_NOCOMMAND;

	GetString(szLine, szLine);

	/*
	We now have the command string.  This string
	may need to be altered if it has a %condition%.
	*/

	/* Application name does not need to be parsed */
	if(nCommand==LC_NAME)return nCommand;

	/* Application to run after installation does not need to be parsed */
	if(nCommand==LC_APPTORUN)return nCommand;

	/* Install from needs to be parsed */
	if(nCommand==LC_INSTALLFROM){
		ParseCommandString(szLine, szLine);
		return nCommand;
	}

	/* Install to needs to be parsed */
	if(nCommand==LC_INSTALLTO){
		ParseCommandString(szLine, szLine);
		return nCommand;
	}

	return nCommand;
}

/*
	GetInfo opens install.ini and get's
	all install info from it.
*/
HRESULT GetInfo(){

	HANDLE hFile=0;
	TCHAR szTemp[MAX_PATH];

	hFile=CreateFile(
		TEXT("qinstall.ini"), 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE)NULL);

	if(hFile == INVALID_HANDLE_VALUE)return E_FAIL;

	while(ReadLine(szTemp, hFile)){
		switch(ProccessLine(szTemp))
		{
		case LC_NAME:
			_tcscpy(szProgramName, szTemp);
			break;
		case LC_INSTALLTO:
			_tcscpy(szDefaultInstall, szTemp);
			break;
		case LC_INSTALLFROM:
			_tcscpy(szInstallFrom, szTemp);
			break;
		case LC_APPTORUN:
			_tcscpy(szAppToRun, szTemp);
			break;
		default:
			break;
		}
	}

	CloseHandle(hFile);


	return S_OK;
}

/*
	Dialog procedure for the Finish dialog.
*/
BOOL CALLBACK FinishQueryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	TCHAR szTemp[MAX_PATH];

	switch(msg){
	case WM_INITDIALOG:
	{
		SetDlgItemText(hwnd, IDC_PNAME2, szProgramName);
		_tcscpy(szTemp, TEXT("Run: "));
		_tcscat(szTemp, szAppToRun);
		_tcscat(szTemp, TEXT("?"));
		SetDlgItemText(hwnd, IDC_RUNPROGRAM, szTemp);
		CheckDlgButton(hwnd, IDC_RUNPROGRAM, BST_CHECKED);

		return FALSE;
	}
	case WM_CLOSE:
		if(IsDlgButtonChecked(hwnd, IDC_RUNPROGRAM))
			bRunApp=TRUE;
		
		SendMessage(GetParent(hwnd), WM_CLOSE, 0, 0);
		break;
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case IDC_CONTINUE:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	}
	case WM_DESTROY:		
		if(IsDlgButtonChecked(hwnd, IDC_RUNPROGRAM))
			bRunApp=TRUE;
		
		break;
	default:return FALSE;
	}
	return TRUE;
}

/*
	DialogProcedure for the installation dialog.
*/
BOOL CALLBACK InstallProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_INITDIALOG:	
		SetDlgItemText(hwnd, IDC_PNAME, szProgramName);
		SetDlgItemText(hwnd, IDC_INSTALLPATH, szDefaultInstall);
		SetDlgItemText(hwnd, IDC_INSTALLFROM, szInstallFrom);

		return FALSE;
	case WM_CLOSE:
		SendMessage(GetParent(hwnd), WM_CLOSE, 0, 0);
		break;
	case WM_DESTROY:
	{	
		break;
	}
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case IDC_QUIT:
			SendMessage(GetParent(hwnd), WM_CLOSE, 0, 0);
			break;
		case IDC_BROWSE:break;
		case IDC_INSTALL:
		{
			/*
			we first attempt to create the install to directory 
			if we can't we go back to dialog loop 
			*/
			TCHAR szInstallTo[MAX_PATH];
			GetDlgItemText(hwnd, IDC_INSTALLPATH, szInstallTo, MAX_PATH);
			/*we successfully created directroy, now we need to copy the files */
			if(!InstallApp(szInstallFrom, szInstallTo, hwnd)){
				/*If we couldn't copy directory... */
				break;
			}
			SetCurrentDirectory(szInstallTo);
			_tcscpy(szDefaultInstall, szInstallTo);
			/*We successfully copied the directoy so continue install.*/
			SendMessage(GetParent(hwnd), WM_CONTINUEINSTALL, 0, 0);
			break;
		}
		}
	}
	default:return FALSE;
	}
	return TRUE;
}

/*
	Paints the background window all blue, and addes text to it.
*/
HRESULT PaintWindow(HWND hwnd){
	HDC hDc=0;
	RECT rClient;
	PAINTSTRUCT ps;
	HPEN hp=0, hpt;
	HBRUSH hb=0, hbt;
	DWORD dwColor=RGB(0,0,125);
	LOGBRUSH logbrush;
	HFONT hfont, hfontt;
	TCHAR temp[]=TEXT("Quick Dirty Application Installer Copyright (c) 2002, 2003, Blaine Myers");
	TEXTMETRIC tm;

	GetClientRect(hwnd, &rClient);
	logbrush.lbColor=dwColor;
	logbrush.lbHatch=0;
	logbrush.lbStyle=BS_SOLID;

	hp=CreatePen(PS_SOLID, 1, dwColor);
	hb=CreateBrushIndirect(&logbrush);


	hDc=BeginPaint(hwnd, &ps);

	hpt=(HPEN)SelectObject(hDc, hp);
	hbt=(HBRUSH)SelectObject(hDc, hb);

	Rectangle(hDc, rClient.left, rClient.top, rClient.right, rClient.bottom);

	DeleteObject(SelectObject(hDc, hpt));
	DeleteObject(SelectObject(hDc, hbt));

	SetBkColor(hDc, dwColor);
	SetTextColor(hDc, RGB(255,255,255));
	hfont=CreateFont(35,0,0,0,FW_NORMAL, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, NULL);
	hfontt=(HFONT)SelectObject(hDc, hfont);

	TextOut(hDc, 4, 4, szProgramName, _tcslen(szProgramName));

	DeleteObject(SelectObject(hDc, hfontt));

	GetTextMetrics(hDc, &tm);

	TextOut(hDc, 0, rClient.bottom-tm.tmHeight*2, temp, _tcslen(temp));
	TextOut(hDc, 0, rClient.bottom-tm.tmHeight, PRODUCT_VERSION, _tcslen(PRODUCT_VERSION));

	EndPaint(hwnd, &ps);

	return S_OK;
}

/*
	Main Window procedure, manages all other app dialogs and procedures.
*/
LRESULT CALLBACK MainWnd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	static HWND hwndInstall=NULL;
	static HWND hwndFinishQuery=NULL;

	static BOOL bAppInstalled=FALSE;
	
	switch (msg){
	case WM_CREATE:
	{
		RECT wrc, mwrc;
		int nWndWidth;
		int nWndHeight;
		int nWndX,nWndY;

		hwndInstall=CreateDialog(
			((LPCREATESTRUCT)lParam)->hInstance, 
			MAKEINTRESOURCE(IDD_MAINDLG), 
			hwnd, 
			InstallProc);

		hwndFinishQuery=CreateDialog(
			((LPCREATESTRUCT)lParam)->hInstance, 
			MAKEINTRESOURCE(IDD_RUNDIALOG), 
			hwnd, 
			FinishQueryProc);

		GetWindowRect(hwndInstall, &wrc);
		GetWindowRect(hwnd, &mwrc);

	
		nWndWidth=wrc.right-wrc.left; 
		nWndHeight=wrc.bottom-wrc.top;


		nWndX=(mwrc.right/2) - (nWndWidth/2)-20;
		nWndY=(mwrc.bottom/2) - (nWndHeight/2)-20;

		MoveWindow(
			hwndInstall, 
			nWndX, 
			nWndY, 
			nWndWidth, 
			nWndHeight, 
			FALSE);

		ShowWindow(hwndInstall, SW_SHOWNORMAL);
		UpdateWindow(hwndInstall);

		break;
	}
	case WM_DESTROY:
	{	

		DestroyWindow(hwndInstall);
		DestroyWindow(hwndFinishQuery);

		if(bRunApp && bAppInstalled)
			PostQuitMessage(1); //1 indicates run app
		else
			PostQuitMessage(0); //0 indicates do not run app
		break;
	}
	case WM_CLOSE:
	{
		
		if(bAppInstalled){
			SendMessage(hwndInstall, WM_COMMAND, MAKEWORD(IDC_CONTINUE, NULL), 0);
		}
		
		DestroyWindow(hwnd);

		break;
	}
	case WM_CONTINUEINSTALL:
	{
		RECT rcWnd;

		GetWindowRect(hwndInstall, &rcWnd);


		MoveWindow(
			hwndFinishQuery, 
			rcWnd.left, 
			rcWnd.top, 
			rcWnd.right-rcWnd.left, 
			rcWnd.bottom-rcWnd.top, 
			FALSE);

		ShowWindow(hwndInstall, SW_HIDE);
		ShowWindow(hwndFinishQuery, SW_SHOWNORMAL);
		UpdateWindow(hwndFinishQuery);

		/*If we made it here the app is installed */
		bAppInstalled=TRUE;
		break;
	}
	case WM_PAINT:
	{
		PaintWindow(hwnd);
		break;
	}
	default:return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0l;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	WNDCLASS wc;
	TCHAR szAppName[]=TEXT("Quick and Dirty Application Installer");
	MSG msg;

	HWND hwnd=NULL;


	/*
		First thing we do is read the initializer info.
	*/
	if(FAILED(GetInfo())){
		MessageBox(NULL, 
			TEXT("Failed to load installation file!"), 
			TEXT("Quick Install"), 
			MB_OK|MB_ICONERROR);
		return 2;
	}
	
	
	ZeroMemory(&wc, sizeof(wc));
	wc.cbClsExtra =0;
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor=LoadCursor(NULL, IDC_ARROW);
	wc.hIcon=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance=hInstance;
	wc.lpfnWndProc=MainWnd;
	wc.lpszClassName=szAppName;
	wc.lpszMenuName=NULL;
	wc.style=0;

	if(!RegisterClass(&wc)){
		MessageBox(
			NULL, 
			TEXT("This program requires Windows NT!"), 
			szAppName, 
			MB_OK|MB_ICONERROR);
		return 2;
	}

	hwnd = CreateWindow(
		szAppName, 
		szAppName,
		WS_SYSMENU|WS_MINIMIZEBOX|WS_CAPTION,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL, 
		hInstance, 
		0);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);


	while(GetMessage(&msg, NULL, 0, 0)){
		/*if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){ */
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		/*}*/
	}
	if(msg.wParam==1)
	{
		/*Should run selected program here.  If run app is selected. */
		SetCurrentDirectory(szDefaultInstall);
		WinExec(szAppToRun, SW_SHOWNORMAL);
	}
	return msg.wParam;
}