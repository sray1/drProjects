// aboutbox.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <limits.h> 	// INT_MAX etc

#include "resource.h"
#include "mdib.h"
#include "Banner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CBanner,CWnd,0);
/////////////////////////////////////////////////////////////////////////////
// CBanner

BEGIN_MESSAGE_MAP(CBanner, CWnd)
	//{{AFX_MSG_MAP(CBanner)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBanner diagnostics

#ifdef _DEBUG
void CBanner::AssertValid() const
{
	CWnd::AssertValid();
}

void CBanner::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif
/////////////////////////////////////////////////////////////////
CBanner::CBanner()
{
	m_bDestroy = FALSE;
	m_hDIB = NULL;
	m_palDIB = NULL;
}

CBanner::~CBanner()
{

	if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
	}
	if (m_pDIBImage != NULL)
	{
		delete m_pDIBImage;
	}	
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
	}
}

// Load Image DIB.

void CBanner::LoadImageDIB(CDC *pDC,int nPicture)
{

	// Copy background DIB from disk.
	BOOL bRetVal;
	if(nPicture == 1)
		bRetVal = LoadImageDIBfromFile(m_pDIBImage, "D:\\drgraf4_0\\applic\\res\\Jasmin.bmp");
	else	
	if(nPicture == 2)
		bRetVal = LoadImageDIBfromFile(m_pDIBImage, "D:\\drgraf4_0\\applic\\res\\seashore.bmp");
	else
		bRetVal = FALSE;	
	ASSERT(bRetVal);
	ASSERT_VALID(m_pDIBImage);

	// Set background DIB's attributes.
	m_pDIBImage->SetDIBInfo();

	// Get summa those attributes.
	m_imageScanLines 	= m_pDIBImage->GetNrScanLines();
	m_lpImageBits 		= m_pDIBImage->GetPVBits();
	m_lpImageBitsInfo	= m_pDIBImage->GetBitsInfo();
	m_imageDIBWidth 	= m_pDIBImage->GetDIBWidth();
	m_imageDIBHeight 	= m_pDIBImage->GetDIBHeight();

	m_bmWidth 			= (int)m_imageDIBWidth;
	m_bmHeight 			= (int)m_imageDIBHeight;
}

BOOL CBanner::LoadImageDIBfromFile(CMDIB *pDIB, char* pszPathName)
{
	HDIB hDIB;
	
	ASSERT_VALID(pDIB);
	if (pDIB == NULL)
		return FALSE;

	CFile file;
	CFileException fileException;
	if (!file.Open(pszPathName, CFile::modeRead 
		| CFile::shareDenyWrite, &fileException))
	{
//		ReportSaveLoadException(pszPathName, &fileException,
//			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	// DeleteContents();
	BeginWaitCursor();

	// replace calls to Serialize with ReadDIBFile function
	TRY
	{
		hDIB = pDIB->ReadDIBFile(file);
	}
	CATCH (CFileException, eLoad)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
//		ReportSaveLoadException(pszPathName, eLoad,
//			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		hDIB = NULL;
		return FALSE;
	}
	END_CATCH


	if (hDIB == NULL)
	{
		// If file is not in DIB format ...
		AfxMessageBox( "Couldn't load Image DIB", MB_ICONINFORMATION | MB_OK);
		return FALSE;
	} 
	//////////////////// Success!
	ReplaceHDIB(hDIB);
	InitDIBData();
	EndWaitCursor();
	pDIB->m_hDIB = hDIB;
	
	return TRUE;
}

// InitDIBData function.
void CBanner::InitDIBData()
{
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_hDIB == NULL)
	{
		return;
	} 
	
	// Set up document size
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	if (m_pDIBImage->DIBWidth(lpDIB) > INT_MAX || 
		m_pDIBImage->DIBHeight(lpDIB) > INT_MAX)
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		AfxMessageBox("DIB is too large", MB_ICONINFORMATION | MB_OK);
		return;
	}
//	m_sizeDoc = CSize((int) m_pDIB->DIBWidth(lpDIB), 
//		(int) m_pDIB->DIBHeight(lpDIB));
	::GlobalUnlock((HGLOBAL) m_hDIB);
	
	// Create copy of palette
	m_palDIB = new CPalette;
	if (m_palDIB == NULL)
	{
		// we must be really low on memory
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return;
	}
	if (m_pDIBImage->CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		// DIB may not have a palette
		delete m_palDIB;
		m_palDIB = NULL;
		return;
	}
}

void CBanner::ReplaceHDIB(HDIB hDIB)
{
	if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
	}
	m_hDIB = hDIB;
}

void CBanner::Init(int nPic)
{
	CDC* pDC 	= GetDC();
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_pDIBImage != NULL)
	{
		delete m_pDIBImage;
		m_pDIBImage = NULL;
	}
	////////////////////////// Create DIBs.
	m_pDIBImage = new CMDIB;
	ASSERT_VALID(m_pDIBImage);
	//////////////////////////	
	LoadImageDIB(pDC,nPic);
	///////////////////////
	m_pColorPal = m_palDIB;
	
}	
	
BOOL CBanner::Create()
{                     
	CRect rect(0,0,0,0);
   	CString BanClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_BYTEALIGNWINDOW,
   						0,(HBRUSH)(COLOR_WINDOW+1),NULL);        //NULL CURSOR 
	if(!CreateEx 	(
						WS_EX_TOPMOST,
						BanClassName,
   						NULL,
   						WS_POPUP,
   						0,0,0,0,
   						NULL,
   						NULL,
   						NULL
   					) )
   		return FALSE;
   	else
   		return TRUE;	 
   				
}

void CBanner::DissolveDot(CDC*pDC,CRect &clRect)
{

	///////////////////////
	unsigned long index;
	int W,H;
	W = clRect.Width();
	H = clRect.Height();
    //////////////////////////////////////////////////////////////////////
	for (index=0; index<=300000; index++,pDC->
			SetPixel(clRect.left+rand()%W, clRect.top+rand()%H,
			 ::GetSysColor(COLOR_WINDOW)) 
		);
    //////////////////////////////////////////////////////////////////////
    
} // end Disolve 

void CBanner::DissolveRect(CDC*pDC,CRect &clRect)
{

	///////////////////////
	unsigned long index;
	int W,H;
	W = clRect.Width()+5;
	H = clRect.Height()+5;
    //////////////////////////////////////////////////////////////////////
//	COLORREF BkColor = ::GetSysColor(COLOR_APPWORKSPACE);
	int l,t,w,h;
 	////////////////////////////// 
 	CBrush 	Br;
 	CBrush* pBrOld;
 	//////////////
 	Br.CreateSolidBrush(::GetSysColor(COLOR_BACKGROUND));
 	pBrOld = pDC->SelectObject(&Br);
 	///////
	//SetPixel(rand()%W, rand()%H, BkColor)
    ///////////////////////////////////////// Loop
	for (index=0; index<=1000; index++)
	{
		l = rand()%W;
		t = rand()%H;
		w = rand()%10;
		h = rand()%10;
	 	////////////////////////////
		pDC->Rectangle(clRect.left+20+l,clRect.top+10+t,l+w,t+h); 
    	////////////////////////////
    }
    /////////////////////////////////////////	
 	pDC->SelectObject(pBrOld);
 	Br.DeleteObject();
    //////////////////////////////////////////////////////////////////////

}

void CBanner::Dog_N_PonyShow(CDC*pDC,CRect &clRect)
{

	/////////////////////////////////////////////////////////////////////
	int nW = (int)m_imageDIBWidth;
	int nH = (int)m_imageDIBHeight;
	///////////////////////// 
	int nClWidth = clRect.Width(); 
	int nClHeight= clRect.Height();
	//////////////////////////////////////////////////
	int nsW = nClWidth;
	int nsH = nClHeight; 
	/////////////////////////
	HDIB hDIB = GetHDIB();
	if (hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
		int cxDIB = (int) m_pDIBImage->GetDIBWidth();         // Size of DIB - x
		int cyDIB = (int) m_pDIBImage->GetDIBHeight();        // Size of DIB - y
		::GlobalUnlock((HGLOBAL) hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest;
		int cx = (int)::GetSystemMetrics(SM_CXSCREEN);
		int cy = (int)::GetSystemMetrics(SM_CYSCREEN);
		int nleft,ntop;
		nleft = (cx - cxDIB)/2;
		ntop  = (cy - cyDIB)/2;
		//////////////////////////////////////////////
		if (pDC->IsPrinting())   // printer DC
		{
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

			//
			// Best Fit case -- create a rectangle which preserves
			// the DIB's aspect ratio, and fills the page horizontally.
			//
			// The formula in the "->bottom" field below calculates the Y
			// position of the printed bitmap, based on the size of the
			// bitmap, the width of the page, and the relative size of
			// a printed pixel (cyInch / cxInch).
			//
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;
		}
		else   // not printer DC
		{
			rcDest.left 	= nleft;
			rcDest.top 		= ntop;
			rcDest.right 	= nleft + rcDIB.Width();
			rcDest.bottom 	= ntop  + rcDIB.Height(); 
			///////////////////////////////////////////////////////// Shadow
			CRect shRect;
			shRect.left		= rcDest.left +30;
			shRect.top  	= rcDest.top +30;
			shRect.right	= rcDest.right+30;
			shRect.bottom	= rcDest.bottom+30;
			 
			pDC->SelectStockObject(BLACK_BRUSH);			
			pDC->SelectStockObject(BLACK_PEN);
			pDC->Rectangle(&shRect);
			/////////////////////////////////////////////////////////			
		}
//		m_pDIBImage->PaintDIB(pDC->m_hDC, &rcDest, GetHDIB(),
		m_pDIBImage->PaintDIB(pDC->m_hDC, &rcDest, GetHDIB(),
								&rcDIB, GetDocPalette(),SRCCOPY);
	}
	
	/////////////////////////
}
/////////////////////////////////////////////////////////////////////////////

BOOL CBanner::OnEraseBkgnd(CDC*)
{
	return TRUE;    // we don't do any erasing...
}

/////////////////////////////////////////////////////////////////////////////

void CBanner::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush	Br;
	CBrush* pBrOld;
	CPalette* pOldPal;
	CPen Pen;
	CPen* pPenOld;
	COLORREF crColor;
	
	crColor = RGB(255,0,255);  
	
	Br.CreateSolidBrush(crColor);
	pBrOld = dc.SelectObject(&Br);      
	Pen.CreatePen(PS_SOLID,1,crColor);
	pPenOld = dc.SelectObject(&Pen);
	pOldPal = dc.SelectPalette(m_pColorPal,FALSE);
	dc.RealizePalette(); 
	//////////////////////////////
	CRect BanRect,clRect;
	GetClientRect(&clRect);
	////////////////////////
	BanRect = clRect;
	BanRect.left	+= 100;
	BanRect.top  	+= 50;
	BanRect.right	-= 100;
	BanRect.bottom	-= 50;    					
	/////////////////////////
    if(!m_bDestroy)
    {
		dc.Rectangle(&clRect);
	   	Dog_N_PonyShow((CDC*)&dc,BanRect);
	}	
    else
	   	DissolveRect((CDC*)&dc,BanRect);
    /////////////////////////
	dc.SelectObject(pBrOld);
	Br.DeleteObject();
	dc.SelectObject(pPenOld);
	Pen.DeleteObject();
	dc.SelectPalette(pOldPal,FALSE);
//	dc.RealizePalette();
    
}

///////////////////////////////// end of Module ///////////////////////
