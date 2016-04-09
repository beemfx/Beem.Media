// TexView3Doc.cpp : implementation of the CTexView3Doc class
//

#include "stdafx.h"
#include "TexView3.h"

#include "TexView3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTexView3Doc

IMPLEMENT_DYNCREATE(CTexView3Doc, CDocument)

BEGIN_MESSAGE_MAP(CTexView3Doc, CDocument)
END_MESSAGE_MAP()


// CTexView3Doc construction/destruction

CTexView3Doc::CTexView3Doc()
: m_pImg(NULL)
{

}

CTexView3Doc::~CTexView3Doc()
{
	if(m_pImg)
	{
		IMG_Delete(m_pImg);
		m_pImg=NULL;
	}
}

BOOL CTexView3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	IMG_Delete(m_pImg);
	m_pImg = NULL;

	return TRUE;
}




// CTexView3Doc serialization

void CTexView3Doc::Serialize(CArchive& ar)
{
	CFile* pFile=ar.GetFile();
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		img_byte* pData=NULL;
		try
		{
			if(pFile->GetLength()>0x0A400000)
				throw CString(CString(AfxGetAppName())+_T(" will not load textures greater than 64MB!"));
			pData=(img_byte*)malloc((size_t)pFile->GetLength());
			if(!pData)
				throw CString(_T("Could not allocate enough memory to load image!"));
			
			if(!pData)
				throw CString(_T("Could not allocate memory to open file!"));
				
			if(pFile->Read(pData, (UINT)pFile->GetLength())<pFile->GetLength())
				throw CString("Could not read ")+pFile->GetFileName();
				
			if(m_pImg)
			{
				IMG_Delete(m_pImg);
				m_pImg = NULL;
			}
			m_pImg = IMG_OpenMemory(reinterpret_cast<img_void*>(pData), (img_dword)pFile->GetLength());
			if(!m_pImg)
				throw CString(_T("Could not open image, no valid image data found!"));
		}
		catch(CString szError)
		{
			AfxMessageBox(CString(_T("CTexView3Doc::Serialize Error: "))+szError);
			//Should close document.
			POSITION p=GetFirstViewPosition();
			this->GetNextView(p)->GetParent()->PostMessage(WM_CLOSE);
		}
		
		//Free data.
		if(pData)free(pData);
		
	}
}


// CTexView3Doc diagnostics

#ifdef _DEBUG
void CTexView3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTexView3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTexView3Doc commands

BOOL CTexView3Doc::CreateCBitmap(CBitmap* pBM, DWORD* cx, DWORD* cy, IMGFILTER filter, DWORD Flags)
{
	this->BeginWaitCursor();
	/* The idea behind converting an imaged to a DDB that can be used
	with windows is the get necessary data and use CreateDIBitmap
	with specified info. */
	if(!m_pImg)
		return FALSE;
	HBITMAP hFinal=NULL;
	LPVOID lpImageData=NULL;

	BITMAPINFOHEADER bmih;
	BITMAPINFO bmi;

	IMG_DESC descript;

	unsigned char nExtra=255;
	BOOL bOpen=FALSE;
	//unsigned short finalwidth=0, finalheight=0;

	memset(&bmih, 0, sizeof(BITMAPINFOHEADER));
	memset(&bmi, 0, sizeof(BITMAPINFO));

	if(!m_pImg)
	{
		EndWaitCursor();
		return FALSE;
	}

	IMG_GetDesc(m_pImg, &descript);

	*cx=*cx?*cx:descript.Width;
	*cy=*cy?*cy:descript.Height;

	lpImageData=malloc((*cx)*(*cy)*4);
	if(!lpImageData)
	{
		EndWaitCursor();
		return FALSE;
	}

	//Set up the destination rect.
	IMG_DEST_RECT rcd={0};
	rcd.nWidth=*cx;
	rcd.nHeight=*cy;
	rcd.nPitch=(*cx)*4;
	rcd.nFormat=IMGFMT_A8R8G8B8;
	rcd.nOrient=IMGORIENT_BOTTOMLEFT;
	rcd.rcCopy.top=0;
	rcd.rcCopy.left=0;
	rcd.rcCopy.right=*cx;
	rcd.rcCopy.bottom=*cy;
	rcd.pImage=(img_void*)lpImageData;

	IMG_CopyBits(m_pImg, &rcd, filter, NULL, 0xFF);		

	int i=0;
	//If we want the alpha channel we simply copy the alpha
	//value into all other values.  This will give us the gray
	//scale image we need.
	//DWORD nAlphaMode=CHECK_FLAG(Flags, BC_ACHANNEL)|CHECK_FLAG(Flags, BC_IMAGE);
	if(CHECK_FLAG(Flags, BC_ACHANNEL))
	{
		ARGBVALUE colrBG={0, 0, 0, 0xFF};
		DWORD   bgclr=CHECK_FLAG(Flags, BC_USEAPPBG)?/*pdc->GetBkColor()*/BG_COLOR:0xFF000000;
		memcpy(&colrBG, &bgclr, 4);
		ARGBVALUE* pColVals=(ARGBVALUE*)lpImageData;
		for(i=0; i<((*cx)*(*cy)); i++)
		{
			//If we want to render both the image and the alpah channel
			//we do an alpha blend.
			if(CHECK_FLAG(Flags, BC_IMAGE))
			{
				//newColor = backColor + (overlayColor – backColor) * (alphaByte div 255)
				pColVals[i].r=pColVals[i].r+(colrBG.r-pColVals[i].r)*(255-pColVals[i].a)/255;
				pColVals[i].g=pColVals[i].g+(colrBG.g-pColVals[i].g)*(255-pColVals[i].a)/255;
				pColVals[i].b=pColVals[i].b+(colrBG.b-pColVals[i].b)*(255-pColVals[i].a)/255;
			}
			else
			{
				//If not we use white as the image color and do the same alpha blend op.

				pColVals[i].r=255+(colrBG.r-255)*(255-pColVals[i].a)/255;
				pColVals[i].g=255+(colrBG.g-255)*(255-pColVals[i].a)/255;
				pColVals[i].b=255+(colrBG.b-255)*(255-pColVals[i].a)/255;
			}
		}
		
	}


	bmih.biSize=sizeof(BITMAPINFOHEADER);
	bmih.biWidth=*cx;
	bmih.biHeight=*cy;
	bmih.biPlanes=1;
	bmih.biBitCount=32;
	bmih.biCompression=BI_RGB;
	bmih.biSizeImage=(*cx)*(*cy)*4;//BI_RGB;
	bmih.biXPelsPerMeter=0;
	bmih.biYPelsPerMeter=0;
	bmih.biClrUsed=0;
	bmih.biClrImportant=0;

	bmi.bmiHeader=bmih;

	
	POSITION p=GetFirstViewPosition();
	hFinal=CreateDIBitmap(
		GetNextView(p)->GetDC()->m_hDC,
		&bmih,
		CBM_INIT,
		lpImageData,
		&bmi,
		DIB_RGB_COLORS);

	free(lpImageData);

	pBM->DeleteObject();
	pBM->m_hObject=hFinal;
	//UpdateAllViews(NULL);
	EndWaitCursor();
	return TRUE;
}

