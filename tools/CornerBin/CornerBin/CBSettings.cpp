#include "StdAfx.h"
#include "CBSettings.h"


CCBSettings::CCBSettings(void)
{
}


CCBSettings::~CCBSettings(void)
{
}


BOOL CCBSettings::LoadSettings(void)
{
	CRegKey rSoftware, rBeem, rCB;
	rSoftware.Open(HKEY_CURRENT_USER, _T("Software"));
	rBeem.Create(rSoftware, _T("Beem Software"));
	rCB.Create(rBeem, _T("CornerBin"));

	//Attempt to load settings, and create defaults if they aren't already set.

	 

	LoadARegString(m_Settings.m_strEmptyIcon, &rCB, _T("EmptyIcon"), _T(""));
	LoadARegString(m_Settings.m_strFullIcon, &rCB, _T("FullIcon"), _T(""));
	LoadARegString(m_Settings.m_strToolTip, &rCB, _T("ToolTip"), _T("Recycle Bin"));

	LoadARegDword(m_Settings.m_bEmptyPrompt, &rCB, _T("PromptBeforeEmpty"), 1);
	LoadARegDword(m_Settings.m_bOpenRBOnDblClk, &rCB, _T("OpenRBOnDblClk"), 1);
	LoadARegDword(m_Settings.m_nUpdateFreq, &rCB, _T("UpdateFrequency"), 1000);
	LoadARegDword(m_Settings.m_bSimpleMenu, &rCB, _T("SimpleMenu"), 0);

	rCB.Close();
	rBeem.Close();
	rSoftware.Close();
	return TRUE;
}


BOOL CCBSettings::SaveSettings(void)
{
	CRegKey rSoftware, rBeem, rCB;
	rSoftware.Open(HKEY_CURRENT_USER, _T("Software"));
	rBeem.Create(rSoftware, _T("Beem Software"));
	rCB.Create(rBeem, _T("CornerBin"));


	rCB.SetStringValue(_T("EmptyIcon"), m_Settings.m_strEmptyIcon);
	rCB.SetStringValue(_T("FullIcon"), m_Settings.m_strFullIcon);
	rCB.SetStringValue(_T("ToolTip"), m_Settings.m_strToolTip);
	rCB.SetDWORDValue(_T("PromptBeforeEmpty"), m_Settings.m_bEmptyPrompt);
	rCB.SetDWORDValue(_T("OpenRBOnDblClk"), m_Settings.m_bOpenRBOnDblClk);
	rCB.SetDWORDValue(_T("UpdateFrequency"), m_Settings.m_nUpdateFreq);
	rCB.SetDWORDValue(_T("SimpleMenu"), m_Settings.m_bSimpleMenu);


	rCB.Close();
	rBeem.Close();
	rSoftware.Close();
	return 0;
}


LPCTSTR CCBSettings::GetFullIcon(void)
{
	return m_Settings.m_strFullIcon;
}


LPCTSTR CCBSettings::GetEmptyIcon(void)
{
	return m_Settings.m_strEmptyIcon;
}


BOOL CCBSettings::GetEmptyPrompt(void)
{
	return m_Settings.m_bEmptyPrompt != 0;
}


BOOL CCBSettings::GetOpenOnDblClk(void)
{
	return m_Settings.m_bOpenRBOnDblClk != 0;
}


void CCBSettings::SetSettings(const SSettings* pSettings)
{
	m_Settings = *pSettings;
	SaveSettings();
}


LPCTSTR CCBSettings::GetTooTip(void)
{
	return m_Settings.m_strToolTip;
}


DWORD CCBSettings::GetUpdateFreq(void)
{
	return m_Settings.m_nUpdateFreq;
}


BOOL CCBSettings::GetSimpleMenu(void)
{
	return m_Settings.m_bSimpleMenu != 0;
}

void CCBSettings::LoadARegString(CString& strOut, CRegKey* pKey, LPCTSTR strName, LPCTSTR strDefault)
{
		TCHAR strTemp[1024];
		DWORD nChars = 1023;
		strOut = strDefault;
		if(ERROR_SUCCESS == pKey->QueryStringValue(strName, strTemp, &nChars))
		{
			strOut = strTemp;
		}
		else
		{
			pKey->SetStringValue(strName, strOut);
		}
}

void CCBSettings::LoadARegDword(DWORD& nOut, CRegKey* pKey, LPCTSTR strName, DWORD nDefault)
{
		nOut = nDefault;
		pKey->QueryDWORDValue(strName, nOut);
}


void CCBSettings::GetSettings(SSettings* pSettingsOut)
{
	*pSettingsOut = m_Settings;
}
