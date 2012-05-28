#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"
#include "MConvert.h"

BOOL CALLBACK MainDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int UpdateFields(HWND hWnd, WORD wCommand);

ExData exdata;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hdlg=NULL;
	MSG msg;
	if(exdata.GetConversionInfo()!=0){
		MessageBox(NULL, TEXT("Error Opening Conversion Table"), TEXT("Notice"), MB_OK|MB_ICONERROR);
		return 0;
	}
	hdlg=CreateDialog(
		hInstance, 
		"MConvertDlg", 
		NULL, 
		(DLGPROC)MainDialogProc);

	if(hdlg==NULL)
		return 0;

	ShowWindow(hdlg, nShowCmd);

	while(TRUE){
		if(!GetMessage(&msg, NULL, 0, 0)){
			return msg.wParam;
		}
		if(!IsDialogMessage(hdlg, &msg)){
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}	
	}
	return msg.wParam;
}

BOOL CALLBACK MainDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i=0;

	switch (uMsg){
	case WM_COMMAND:
	{
		//If the edit box has changed we update the value.
		if(LOWORD(wParam)==IDC_EDIT1)
			UpdateFields(hWnd, LOWORD(wParam));

		switch (LOWORD(wParam))
		{
		case IDOK:
			UpdateFields(hWnd, LOWORD(wParam));
			break;	
		}
		break;
	}
	case WM_CLOSE:DestroyWindow(hWnd);break;
	case WM_DESTROY:PostQuitMessage(0);break;
	case WM_INITDIALOG:
		for(i=0; i<=exdata.numentries;i++){
			SendDlgItemMessage(
				hWnd, 
				IDC_COMBO1, 
				CB_ADDSTRING, 
				0, 
				(LPARAM) exdata.countryName[i]);
				
			SendDlgItemMessage(
				hWnd, 
				IDC_COMBO2, 
				CB_ADDSTRING, 
				0,
				(LPARAM)exdata.countryName[i]);
			}	
		break;
	default:return FALSE;
	}	
	return TRUE;
}
BOOL UpdateFields(HWND hWnd, WORD wCommand)
{
	char srcCountryName[255];
	char destCountryName[255];
	char srcAmnt[20];
	char destAmnt[20];
	double dSrcAmnt;
	double dDestAmount;
	int DataEntry;
	int DestEntry;

	GetDlgItemText(hWnd, IDC_COMBO1, srcCountryName, sizeof(srcCountryName)/sizeof(char));
	GetDlgItemText(hWnd, IDC_COMBO2, destCountryName, sizeof(destCountryName)/sizeof(char));
	GetDlgItemText(hWnd, IDC_EDIT1, srcAmnt, sizeof(srcAmnt)/sizeof(char));
	for(int i=0;i<exdata.numentries;i++){
		if(strcmp(srcCountryName, exdata.countryName[i])==0)DataEntry=i;
		if(strcmp(destCountryName, exdata.countryName[i])==0)DestEntry=i;
	}
	if(DataEntry>exdata.numentries||DataEntry<0)return FALSE;
	if(DestEntry>exdata.numentries||DestEntry<0)return FALSE;
	dSrcAmnt=atof(srcAmnt);

	//I beleive this is the correct way to convert
	dDestAmount=dSrcAmnt*exdata.exchangeRate[DestEntry]/exdata.exchangeRate[DataEntry];

	sprintf(destAmnt, "%.2f", dDestAmount);
	SetDlgItemText(hWnd, IDC_STATIC1, destAmnt);
	return TRUE;
}
