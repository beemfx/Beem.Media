// TexView3View.h : interface of the CTexView3View class
//


#pragma once
#include "afxwin.h"


class CTexView3View : public CScrollView
{
protected: // create from serialization only
	CTexView3View();
	DECLARE_DYNCREATE(CTexView3View)

// Attributes
public:
	CTexView3Doc* GetDocument() const;
	
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTexView3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnTextureAlphaMode(UINT nID);
	//DWORD m_nAlphaMode;
public:
	afx_msg void OnUpdateTextureImage(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateTextureImagewithalpha(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateTextureAlphaonly(CCmdUI *pCmdUI);
private:
	BOOL m_bTextureRepeat;
public:
	afx_msg void OnTextureRepeating();
public:
	afx_msg void OnUpdateTextureRepeating(CCmdUI *pCmdUI);
private:
	DWORD m_nWidth;
	DWORD m_nHeight;
	CBitmap m_bmImg;
	DWORD m_nAlphaMode;
	BOOL DrawBitmap(int x, int y, CDC* pDC);
	IMGFILTER m_nFilter;
public:
	afx_msg void OnUpdateTextureLinearfilter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTexturePointfilter(CCmdUI *pCmdUI);
	afx_msg void OnTextureFilter(UINT nID);
	void RebuildBitmap(void);
};

#ifndef _DEBUG  // debug version in TexView3View.cpp
inline CTexView3Doc* CTexView3View::GetDocument() const
   { return reinterpret_cast<CTexView3Doc*>(m_pDocument); }
#endif

