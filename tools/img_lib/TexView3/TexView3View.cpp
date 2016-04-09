// TexView3View.cpp : implementation of the CTexView3View class
//

#include "stdafx.h"
#include "TexView3.h"

#include "TexView3Doc.h"
#include "TexView3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTexView3View

IMPLEMENT_DYNCREATE(CTexView3View, CScrollView)

BEGIN_MESSAGE_MAP(CTexView3View, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_TEXTURE_IMAGE, ID_TEXTURE_ALPHAONLY, &CTexView3View::OnTextureAlphaMode)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_IMAGE, &CTexView3View::OnUpdateTextureImage)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_IMAGEWITHALPHA, &CTexView3View::OnUpdateTextureImagewithalpha)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_ALPHAONLY, &CTexView3View::OnUpdateTextureAlphaonly)
	ON_COMMAND(ID_TEXTURE_REPEATING, &CTexView3View::OnTextureRepeating)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_REPEATING, &CTexView3View::OnUpdateTextureRepeating)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_LINEARFILTER, &CTexView3View::OnUpdateTextureLinearfilter)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_POINTFILTER, &CTexView3View::OnUpdateTexturePointfilter)
	ON_COMMAND_RANGE(ID_TEXTURE_LINEARFILTER, ID_TEXTURE_POINTFILTER, &CTexView3View::OnTextureFilter)
END_MESSAGE_MAP()

// CTexView3View construction/destruction

CTexView3View::CTexView3View()
: m_bTextureRepeat(FALSE)
, m_nWidth(0)
, m_nHeight(0)
, m_nAlphaMode(CTexView3Doc::BC_IMAGE)
, m_nFilter(IMGFILTER_LINEAR)
{
	// TODO: add construction code here
}

CTexView3View::~CTexView3View()
{
}

BOOL CTexView3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

// CTexView3View drawing

void CTexView3View::OnDraw(CDC* pDC)
{
	CTexView3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//int cx, cy;
	//pDoc->GetImageSize(&cx, &cy);
	CRect rcw;
	GetClientRect(&rcw);
	if(m_bTextureRepeat)
	{
		for(int i=0; i<rcw.Width()/m_nWidth+1; i++)
		{
			for(int j=0; j<rcw.Height()/m_nHeight+1; j++)
				DrawBitmap(i*m_nWidth, j*m_nHeight, pDC);
		}
		
		return;
	}
	int cx, cy;
	cx=rcw.Width()>m_nWidth?(rcw.right-m_nWidth)/2:0;
	cy=rcw.Height()>m_nHeight?(rcw.bottom-m_nHeight)/2:0;
	DrawBitmap(cx, cy, pDC);
}


// CTexView3View printing

BOOL CTexView3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTexView3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTexView3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTexView3View diagnostics

#ifdef _DEBUG
void CTexView3View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTexView3View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTexView3Doc* CTexView3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTexView3Doc)));
	return (CTexView3Doc*)m_pDocument;
}
#endif //_DEBUG


// CTexView3View message handlers

void CTexView3View::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{	
	SetScrollSizes(MM_TEXT, CSize(m_nWidth, m_nHeight));
	RedrawWindow();
}

void CTexView3View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	//Initially we create a default bitmap,
	//m_nWidth and m_nHeight and m_nAlphaMode were set to initial values
	//in the constructor.
	RebuildBitmap();
	SetScrollSizes(MM_TEXT, CSize(m_nWidth, m_nHeight));
	ResizeParentToFit(TRUE);
}

BOOL CTexView3View::OnEraseBkgnd(CDC* pDC)
{
	// Set brush to desired background color
	CBrush backBrush(CTexView3Doc::BG_COLOR);
	//backBrush.m_hObject=GetStockObject(LTGRAY_BRUSH);
	// Save old brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);

	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed

	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	//return CScrollView::OnEraseBkgnd(pDC);
}

void CTexView3View::OnTextureAlphaMode(UINT nID)
{
	CTexView3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
		
	DWORD nNewMode=0;
	switch(nID)
	{
	case ID_TEXTURE_IMAGE:
		nNewMode=CTexView3Doc::BC_IMAGE;
		break;
	case ID_TEXTURE_IMAGEWITHALPHA:
		nNewMode=CTexView3Doc::BC_ACHANNEL|CTexView3Doc::BC_IMAGE;
		break;
	case ID_TEXTURE_ALPHAONLY:
		nNewMode=CTexView3Doc::BC_ACHANNEL;
		break;
	}
	
	//If the mode hasn't changed we
	//don't need to do anything.
	if(nNewMode==m_nAlphaMode)
		return;
		
	m_nAlphaMode=nNewMode;
	
	RebuildBitmap();
}
void CTexView3View::OnUpdateTextureImage(CCmdUI *pCmdUI)
{
	if(CHECK_FLAG(CTexView3Doc::BC_IMAGE, m_nAlphaMode) &&
		!(CHECK_FLAG(CTexView3Doc::BC_ACHANNEL, m_nAlphaMode)))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTexView3View::OnUpdateTextureImagewithalpha(CCmdUI *pCmdUI)
{
	if(CHECK_FLAG(CTexView3Doc::BC_IMAGE, m_nAlphaMode) &&
		(CHECK_FLAG(CTexView3Doc::BC_ACHANNEL, m_nAlphaMode)))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTexView3View::OnUpdateTextureAlphaonly(CCmdUI *pCmdUI)
{
	if(!CHECK_FLAG(CTexView3Doc::BC_IMAGE, m_nAlphaMode) &&
		(CHECK_FLAG(CTexView3Doc::BC_ACHANNEL, m_nAlphaMode)))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTexView3View::OnTextureRepeating()
{
	m_bTextureRepeat=!m_bTextureRepeat;
	if(m_bTextureRepeat)
		SetScrollSizes(MM_TEXT, CSize(0, 0));
	else
		SetScrollSizes(MM_TEXT, CSize(m_nWidth, m_nHeight));
	RedrawWindow();
}

void CTexView3View::OnUpdateTextureRepeating(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bTextureRepeat);
}

BOOL CTexView3View::DrawBitmap(int x, int y, CDC* pDC)
{
	if(!m_bmImg.m_hObject)
		return FALSE;
		
	CDC cImageDC;
	cImageDC.CreateCompatibleDC(NULL);
	CBitmap* bmOld=(CBitmap*)cImageDC.SelectObject(&m_bmImg);
	
	if(!pDC->IsPrinting())
	{
		pDC->BitBlt(
			x,
			y,
			m_nWidth,
			m_nHeight,
			&cImageDC,
			0,
			0,
			SRCCOPY);
	}
	else
	{
		BOOL bResult=0;
		CDC dcImg;
		dcImg.CreateCompatibleDC(&cImageDC);
		CBitmap bmImg, *bmOld;
		bmImg.CreateCompatibleBitmap(&cImageDC, pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
		bmOld=dcImg.SelectObject(&bmImg);
		
		//Adjust the width and height to fit the whole image on a page:
		DWORD nWidth=0, nHeight=0;
		if(m_nWidth<m_nHeight)
		{
			nHeight=pDC->GetDeviceCaps(VERTRES); 
			nWidth=m_nWidth*pDC->GetDeviceCaps(VERTRES)/m_nHeight;
		}
		else
		{
			nWidth=pDC->GetDeviceCaps(HORZRES); 
			nHeight=m_nHeight*pDC->GetDeviceCaps(HORZRES)/m_nWidth;
		}
		
		x=0;
		y=0;
		//Center the image horizontally on the page.
		if(nWidth<pDC->GetDeviceCaps(HORZRES))
			x=(pDC->GetDeviceCaps(HORZRES)-nWidth)/2;
			
		//We could also center the image vertically,
		//but i think it looks better if it is at the top of the page.
		//if(nHeight<pDC->GetDeviceCaps(VERTRES))
		//	y=(pDC->GetDeviceCaps(VERTRES)-nHeight)/2;
		
		bResult=dcImg.StretchBlt(
			0,
			0,
			nWidth,
			nHeight,
			&cImageDC,
			0,
			0,
			m_nWidth,
			m_nHeight,
			SRCCOPY);
		
		bResult=pDC->BitBlt(
			x,
			y,
			nWidth,
			nHeight,
			&dcImg,
			0,
			0,
			SRCCOPY);
			
		dcImg.SelectObject(bmOld);
		dcImg.DeleteDC();
		bmImg.DeleteObject();
	}	
	cImageDC.SelectObject(bmOld);
	cImageDC.DeleteDC();
	
	return TRUE;
}

void CTexView3View::OnUpdateTextureLinearfilter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nFilter==IMGFILTER_LINEAR);
}

void CTexView3View::OnUpdateTexturePointfilter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nFilter==IMGFILTER_POINT);
}

void CTexView3View::OnTextureFilter(UINT nID)
{
	switch(nID)
	{
	case ID_TEXTURE_LINEARFILTER:
		if(m_nFilter==IMGFILTER_LINEAR)
			return;
		m_nFilter=IMGFILTER_LINEAR;
		break;
	case ID_TEXTURE_POINTFILTER:
		if(m_nFilter==IMGFILTER_POINT)
			return;
		m_nFilter=IMGFILTER_POINT;
		break;
	}
	RebuildBitmap();
}

void CTexView3View::RebuildBitmap(void)
{
	CTexView3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
		
	m_bmImg.DeleteObject();
	pDoc->CreateCBitmap(&m_bmImg, &m_nWidth, &m_nHeight, m_nFilter, CTexView3Doc::BC_USEAPPBG|m_nAlphaMode);
	RedrawWindow();
}
