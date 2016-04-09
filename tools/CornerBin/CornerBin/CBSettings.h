#pragma once
class CCBSettings
{
public:
	CCBSettings(void);
	~CCBSettings(void);

public:
	struct SSettings
	{
		CString m_strFullIcon;
		CString m_strEmptyIcon;
		CString m_strToolTip;
		DWORD    m_bEmptyPrompt;
		DWORD    m_bOpenRBOnDblClk;
		DWORD    m_nUpdateFreq;
		DWORD    m_bSimpleMenu;
	};

private:
	SSettings m_Settings;
public:
	BOOL LoadSettings(void);
	BOOL SaveSettings(void);
	LPCTSTR GetFullIcon(void);
	LPCTSTR GetEmptyIcon(void);
	BOOL GetEmptyPrompt(void);
	BOOL GetOpenOnDblClk(void);
	void SetSettings(const SSettings* pSettings);
	LPCTSTR GetTooTip(void);
	DWORD GetUpdateFreq(void);
	BOOL GetSimpleMenu(void);
private:
	static void LoadARegString(CString& strOut, CRegKey* pKey, LPCTSTR strName, LPCTSTR strDefault);
	static void LoadARegDword(DWORD& nOut, CRegKey* pKey, LPCTSTR strName, DWORD nDefault);
public:
	void GetSettings(SSettings* pSettingsOut);
};

