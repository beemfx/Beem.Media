// TexView3Doc.h : interface of the CTexView3Doc class
//


#pragma once
#include "afxwin.h"

class CTexView3Doc : public CDocument
{
protected: // create from serialization only
	CTexView3Doc();
	DECLARE_DYNCREATE(CTexView3Doc)

// Attributes
public:
	static const DWORD BC_IMAGE=0x00000010;
	static const DWORD BC_ACHANNEL=0x00000020;
	static const DWORD BC_USEAPPBG=0x00000040;
	
	static const COLORREF BG_COLOR=RGB(128, 128, 128);
	
private:
	typedef struct _ARGBVALUE{
		BYTE b, g, r, a;
	}ARGBVALUE;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTexView3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	HIMG m_pImg;
private:
	//CBitmap m_bmImg;
public:
	BOOL CreateCBitmap(CBitmap* pBM, DWORD* cx, DWORD* cy, IMGFILTER filter, DWORD Flags);
private:
	//DWORD m_nWidth;
private:
	//DWORD m_nHeight;
public:
	//BOOL DrawBitmap(int x, int y, CDC* pdc);
public:
	//void GetImageSize(int* px, int* py);
private:
	//int m_nAlphaMode;
public:
	//DWORD GetAlphaMode(void);
};


