#pragma once


// CDlgSettings dialog

class CDlgSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSettings)

public:
	CDlgSettings(CWnd* pParent, CCBSettings* pSettings);   // standard constructor
	virtual ~CDlgSettings();

// Dialog Data
	enum { IDD = IDD_DLG_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CCBSettings* m_pSettings;
public:
	afx_msg void OnBnClickedBtnbrowsee();
	void BrowseForIcon(int nCtrlID);
	afx_msg void OnBnClickedBtnbrowsef();
	afx_msg void OnBnClickedBtnsysempty();
	afx_msg void OnBnClickedBtnsysfull();
private:
	void SetStartWithWindows(BOOL bStartWith);
private:
	static BOOL IsStartWithWindowsSet(void);
public:
	afx_msg void OnBnClickedBtndefs();
};
