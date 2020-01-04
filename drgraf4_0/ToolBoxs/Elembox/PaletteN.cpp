// palette.cpp : implementation of the Floating tool palette class
//

#include "stdafx.h"
//////////////////////////////////////////////////
#include "Oldglob.h"  
#include "paletteN.h"  


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define CYCAPTION 9     /* height of the caption */

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CPaletteBarN, CToolBar)

BEGIN_MESSAGE_MAP(CPaletteBarN, CToolBar)
	//{{AFX_MSG_MAP(CPaletteBarN)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaletteBarN construction/destruction

CPaletteBarN::CPaletteBarN()
{ 

//	m_bTrackMove     = FALSE;
	
	m_nColumns       = 3;
	
//	m_cyCaption   	 = CYCAPTION;
	m_cyTopBorder    = CYCAPTION + 2;
	m_cxLeftBorder   = 0;
	m_cxRightBorder  = 0;
	m_cyBottomBorder = 0; 
	
}

CPaletteBarN::~CPaletteBarN()
{
}
/////////////////////////////////////////////////////////////////////////////
// CPaletteBarN diagnostics

#ifdef _DEBUG
void CPaletteBarN::AssertValid() const
{
	CToolBar::AssertValid();
}

void CPaletteBarN::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaletteBarN message handlers

void CPaletteBarN::SetColumns(UINT nColumns)
{
	m_nColumns = nColumns;
	int nCount = GetToolBarCtrl().GetButtonCount();

	for (int i = 0; i < nCount; i++)
	{
		UINT nStyle = GetButtonStyle(i);
		BOOL bWrap = (((i + 1) % nColumns) == 0);
		if (bWrap)
			nStyle |= TBBS_WRAPPED;
		else
			nStyle &= ~TBBS_WRAPPED;
		SetButtonStyle(i, nStyle);
	}
	
//	Invalidate();
//	GetParentFrame()->RecalcLayout();
	RecalcLayout(nCount);
}

int CPaletteBarN::HitTest(CPoint point)  // in window relative coords
{
	if (point.x < m_cxLeftBorder ||
			point.x >= (int)(m_cxLeftBorder + m_sizeButton.cx * m_nColumns))
		return -1;      // no X hit

	UINT nRows = (m_nCount + m_nColumns - 1) / m_nColumns;
	
	if (point.y < m_cyTopBorder ||
			point.y >= (int)(m_cyTopBorder + m_sizeButton.cy * nRows))
		return -1;      // no Y hit

	int iButton = ((point.y - m_cyTopBorder) / (m_sizeButton.cy-1) * m_nColumns +
			(point.x - m_cxLeftBorder) / (m_sizeButton.cx-1));
	return ( iButton < m_nCount ) ? iButton : -1;
}

/*
void CPaletteBarN::OnDestroy()
{
	CToolBar::OnDestroy();
	
}

void CPaletteBarN::SetSizes(SIZE sizeButton, SIZE sizeImage,BOOL bCaption)
{

	////////////////////////
	if(!bCaption)
	{
		m_cyCaption   = 0;
		m_cyTopBorder = 0;
	} 
	else
	{
		m_cyCaption      = CYCAPTION;
		m_cyTopBorder    = m_cyCaption+2;
	}
	
	// default image sizes
	m_sizeImage.cx = sizeImage.cx;
	m_sizeImage.cy = sizeImage.cy;

	// default button sizes
	m_sizeButton.cx = sizeButton.cx;
	m_sizeButton.cy = sizeButton.cy;
//////////////////////////////////////////
//	CToolBar::SetSizes(sizeButton, sizeImage);
	//////////////////////////////////////////
//	RecalcLayout(m_nCount);

}

BOOL CPaletteBarN::SetButtons(const UINT *lpIDArray,int nIDCount,UINT nColumns)
{

	//////////////////////
    m_nColumns  = nColumns;
	m_nCount 	= nIDCount;             // CControlBar member
	/////////////////////////////////////////////////
	if(!CToolBar::SetButtons(lpIDArray, nIDCount)   )
		return FALSE;
	/////////////////////////////////////////////////
	RecalcLayout(nIDCount);
	///////////////////////
	return TRUE;

}
BOOL CPaletteBarN::Create(CWnd* pOwnerWnd, int x, int y,UINT nChildID)
{
	ASSERT(pOwnerWnd != NULL);
	m_pOwnerWnd = pOwnerWnd; 
	/////////////////////////
	return CreateEx(0, "AfxControlBar", NULL, WS_CHILD,     // CHILD
		x, y, 0, 0, pOwnerWnd->GetSafeHwnd(), (HMENU)nChildID, NULL);
}
 
BOOL CPaletteBarN::Create(CWnd* pOwnerWnd, int x, int y,
								UINT nChildID,UINT nIDCursor)
{
	ASSERT(pOwnerWnd != NULL);
	m_pOwnerWnd = pOwnerWnd;
    ////////////////////////////////////////////////////////////////
//	return CreateEx(0, "SuperControlBar", NULL, WS_CHILD,     // CHILD
//		x, y, 0, 0, pOwnerWnd->GetSafeHwnd(), (HMENU)nChildID, NULL);
	if (
		!(CToolBar::Create(pOwnerWnd, WS_CHILD | WS_VISIBLE | CBRS_SIZE_FIXED |
			CBRS_TOP | CBRS_TOOLTIPS, nChildID) ) 
		)
		return FALSE;
	else
		return TRUE;

}

*/
void CPaletteBarN::RecalcLayout(UINT nButtonCount)
{
	SetWindowPos(NULL, 0, 0,
//		m_cxLeftBorder + (m_sizeButton.cx-1) * m_nColumns + m_cxRightBorder+1,
		m_cxLeftBorder + (m_sizeButton.cx) * m_nColumns + m_cxRightBorder,
//		m_cyTopBorder  + m_cyBottomBorder + (m_sizeButton.cy-1) *
		m_cyTopBorder  + m_cyBottomBorder + (m_sizeButton.cy) *
		((nButtonCount + m_nColumns - 1) / m_nColumns) + 1,
		  SWP_NOZORDER|SWP_NOMOVE);

		  
	Invalidate();
	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CPaletteBarN message handlers

#define new DEBUG_NEW

// globals for fast drawing (shared globals)
static HDC hDCGlyphs = NULL;
static HDC hDCMono = NULL;
static HBRUSH hbrDither = NULL;
// Init / Term

static HBITMAP AFXAPI CreateDitherBitmap();

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif



// a special struct that will cleanup automatically
struct _AFX_TOOLBAR_TERM
{
	~_AFX_TOOLBAR_TERM()
	{
		AfxDeleteObject((HGDIOBJ*)&hDCMono);
		AfxDeleteObject((HGDIOBJ*)&hDCGlyphs);
	}
};

static const _AFX_TOOLBAR_TERM toolbarTerm;

/////////////////////////////////////////////////////////////////////////////

#ifdef AFX_CORE3_SEG
#pragma code_seg(AFX_CORE3_SEG)
#endif

static HBITMAP AFXAPI CreateDitherBitmap()
{
	struct  // BITMAPINFO with 16 colors
	{
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD      bmiColors[16];
	} bmi;
	memset(&bmi, 0, sizeof(bmi));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 8;
	bmi.bmiHeader.biHeight = 8;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 1;
	bmi.bmiHeader.biCompression = BI_RGB;

	COLORREF clr = ::GetSysColor(COLOR_BTNFACE);
	bmi.bmiColors[0].rgbBlue = GetBValue(clr);
	bmi.bmiColors[0].rgbGreen = GetGValue(clr);
	bmi.bmiColors[0].rgbRed = GetRValue(clr);

	clr = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	bmi.bmiColors[1].rgbBlue = GetBValue(clr);
	bmi.bmiColors[1].rgbGreen = GetGValue(clr);
	bmi.bmiColors[1].rgbRed = GetRValue(clr);

	// initialize the brushes
	long patGray[8];
	for (int i = 0; i < 8; i++)
	   patGray[i] = (i & 1) ? 0xAAAA5555L : 0x5555AAAAL;

	HDC hDC = GetDC(NULL);
	HBITMAP hbm = CreateDIBitmap(hDC, &bmi.bmiHeader, CBM_INIT,
		(LPBYTE)patGray, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS);
	ReleaseDC(NULL, hDC);

	return hbm;
}

// create a mono bitmap mask:
void CPaletteBarN::CreateMask(int iImage, CPoint ptOffset,
	 BOOL bHilite, BOOL bHiliteShadow)
{
	// initalize whole area with 0's
	PatBlt(hDCMono, 0, 0, m_sizeButton.cx-2, m_sizeButton.cy-2, WHITENESS);

	// create mask based on color bitmap
	// convert this to 1's
	SetBkColor(hDCGlyphs, globalData.clrBtnFace);
	BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
		hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);

	if (bHilite)
	{
		// convert this to 1's
		SetBkColor(hDCGlyphs, globalData.clrBtnHilite);

		// OR in the new 1's
		BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCPAINT);

		if (bHiliteShadow)
			BitBlt(hDCMono, 1, 1, m_sizeButton.cx-3, m_sizeButton.cy-3,
				hDCMono, 0, 0, SRCAND);
	}
}
////////////////////////////////////////////////////////////////////////////
void CPaletteBarN::DoPaint(CDC* pDC)
{
	CControlBar::DoPaint(pDC);      // draws any borders
    ////////////////////////////////////////////////////////  NO FRAME/CAPTION
	CRect rect;
	GetClientRect(&rect);

	if(m_cyCaption !=0)                                    
	{
		// Draw the frame border
		CBrush brBlack;
		brBlack.CreateSolidBrush(::GetSysColor(COLOR_WINDOWFRAME));
		pDC->FrameRect(rect,&brBlack);
		rect.bottom = CYCAPTION;
		pDC->FrameRect(rect,&brBlack);

		// Fill in the caption color
		CBrush brCaption;
		brCaption.CreateSolidBrush(::GetSysColor(COLOR_ACTIVECAPTION));
		rect.InflateRect(-1, -1);
		pDC->FillRect(rect, &brCaption);
	}
	// We need to initialize the bitmap selection process.
	DrawState ds;
	if (!PrepareDrawButton(ds))
		return;     // something went wrong

	GetClientRect(&rect);
	rect.top = m_cyTopBorder;
	rect.bottom = rect.top + m_sizeButton.cy;

	// Now draw each visible button
	for (int iButton = 0; iButton < m_nCount; )
	{
		rect.left = m_cxLeftBorder;
		for (UINT nCol = 0; nCol < m_nColumns && iButton<m_nCount; nCol++, iButton++)
		{
			rect.right = rect.left + m_sizeButton.cx;
			if (pDC->RectVisible(&rect))
			{
				UINT nID, nStyle;
				int iImage;
				GetButtonInfo(iButton, nID, nStyle, iImage);
//16				DrawButton(pDC->m_hDC, rect.left, rect.top,
				DrawButton(pDC, rect.left, rect.top,
					iImage, nStyle);
			}
//			rect.left = rect.right - 1; // prepare for overlap
			rect.left = rect.right ;
		}
//		rect.top = rect.bottom-1;
		rect.top = rect.bottom;
		rect.bottom = rect.top + m_sizeButton.cy;
	}

	EndDrawButton(ds);
}

void CPaletteBarN::OnLButtonDown(UINT nFlags, CPoint point)
{
	///////////////////////////////////////////////// 
	if (point.y <= m_cyTopBorder)
	{
		m_bTrackMove = TRUE;
		m_ptMouse = point;
		SetCapture();
		ClientToScreen(&point);
		InvertTracker(point);
		m_ptLast = point;
	}
	else 
		CToolBar::OnLButtonDown(nFlags, point);
}

void CPaletteBarN::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bTrackMove)
	{
		m_bTrackMove=FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
		ShowWindow(SW_SHOW);
	}
	else
		CToolBar::OnLButtonUp(nFlags, point);
} 

void CPaletteBarN::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bTrackMove)
	{
		ClientToScreen(&point);
		InvertTracker(m_ptLast);
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else
		CToolBar::OnMouseMove(nFlags, point);
}

void CPaletteBarN::InvertTracker(CPoint point)
{
	CRect rectFrame;
	GetWindowRect(&rectFrame);
	CDC dc;
	dc.Attach(::GetDC(NULL));
	
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y, rectFrame.Width(),
			2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x+rectFrame.Width(), point.y-m_ptMouse.y,
			2, rectFrame.Height(), PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+rectFrame.Height(),
			rectFrame.Width()+2, 2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+2, 2,
			rectFrame.Height()-2, PATINVERT);
	::ReleaseDC(NULL,dc.Detach());
}

void CPaletteBarN::GetItemRect(int nIndex, LPRECT lpRect) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nCount);
	ASSERT(AfxIsValidAddress(lpRect, sizeof(RECT)));

	lpRect->left = m_cxLeftBorder +
//			(nIndex - (nIndex / m_nColumns) * m_nColumns) * (m_sizeButton.cx-1);
			(nIndex - (nIndex / m_nColumns) * m_nColumns) * (m_sizeButton.cx);
	lpRect->right = lpRect->left + m_sizeButton.cx;

//	lpRect->top = m_cyTopBorder + (nIndex / m_nColumns) * (m_sizeButton.cy-1);
	lpRect->top = m_cyTopBorder + (nIndex / m_nColumns) * (m_sizeButton.cy);
	lpRect->bottom = lpRect->top + m_sizeButton.cy;
}

void CPaletteBarN::InvalidateButton(int nIndex)
{
	ASSERT_VALID(this);

	CRect rect;
	GetItemRect(nIndex, &rect);
	InvalidateRect(rect, FALSE);    // don't erase background
}

int CPaletteBarN::OnMouseActivate(CWnd*, UINT, UINT)
{
	return MA_ACTIVATE;
}

///////////////////////////////////
// Raster Ops
#define ROP_DSPDxax  0x00E20746L
#define ROP_PSDPxax  0x00B8074AL
///////////////////////////////////
BOOL CPaletteBarN::DrawButton(CDC* pDC, int x, int y, int iImage, UINT nStyle)
{
	ASSERT_VALID(pDC);

	int dx = m_sizeButton.cx;
	int dy = m_sizeButton.cy;
	if (!globalData.bWin4)
	{
		// make the coordinates the interior of the button
		x += 1;
		y += 1;
		dx -= 2;
		dy -= 2;

		// border around button
		pDC->FillSolidRect(x,    y-1,    dx, 1,  globalData.clrWindowFrame);
		pDC->FillSolidRect(x,    y+dy,   dx, 1,  globalData.clrWindowFrame);
		pDC->FillSolidRect(x-1,  y,  1,  dy, globalData.clrWindowFrame);
		pDC->FillSolidRect(x+dx, y,  1,  dy, globalData.clrWindowFrame);
	}

	// interior grey
	pDC->FillSolidRect(x, y, dx, dy, globalData.clrBtnFace);

	// determine offset of bitmap (centered within button)
	CPoint ptOffset;
	ptOffset.x = (dx - m_sizeImage.cx - 1) / 2;
	ptOffset.y = (dy - m_sizeImage.cy) / 2;

	if (nStyle & (TBBS_PRESSED | TBBS_CHECKED))
	{
		// pressed in or checked
		pDC->Draw3dRect(x, y, dx, dy,
			globalData.bWin4 ? globalData.clrWindowFrame : globalData.clrBtnShadow,
			globalData.bWin4 ? globalData.clrBtnHilite : globalData.clrBtnFace);

		if (globalData.bWin4)
		{
			pDC->Draw3dRect(x + 1, y + 1, dx - 2, dy - 2,
				globalData.clrBtnShadow, globalData.clrBtnFace);
		}

		// for any depressed button, add one to the offsets.
		ptOffset.x += 1;
		ptOffset.y += 1;
	}
	else
	{
		// regular button look
		pDC->Draw3dRect(x, y, dx, dy, globalData.clrBtnHilite,
			globalData.bWin4 ? globalData.clrWindowFrame : globalData.clrBtnShadow);
		pDC->Draw3dRect(x + 1, y + 1, dx - 2, dy - 2,
			globalData.clrBtnFace, globalData.clrBtnShadow);
	}

	if ((nStyle & TBBS_PRESSED) || !(nStyle & TBBS_DISABLED))
	{
		// normal image version
		BitBlt(pDC->m_hDC, x + ptOffset.x, y + ptOffset.y,
			m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);

		if (nStyle & TBBS_PRESSED)
			return TRUE;        // nothing more to do (rest of style is ignored)
	}

	if (nStyle & (TBBS_DISABLED | TBBS_INDETERMINATE))
	{
		// disabled or indeterminate version
		CreateMask(iImage, ptOffset, TRUE, FALSE);

		pDC->SetTextColor(0L);                  // 0's in mono -> 0 (for ROP)
		pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1's in mono -> 1

		if (nStyle & TBBS_DISABLED)
		{
			// disabled - draw the hilighted shadow
			HGDIOBJ hbrOld = pDC->SelectObject(globalData.hbrBtnHilite);
			if (hbrOld != NULL)
			{
				// draw hilight color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x + 1, y + 1,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}

		//BLOCK: always draw the shadow
		{
			HGDIOBJ hbrOld = pDC->SelectObject(globalData.hbrBtnShadow);
			if (hbrOld != NULL)
			{
				// draw the shadow color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x, y,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}
	}

	// if it is checked do the dither brush avoiding the glyph
	if (nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE))
	{
		HGDIOBJ hbrOld = pDC->SelectObject(hbrDither);
		if (hbrOld != NULL)
		{
			ptOffset.x -= globalData.cxBorder2;
			ptOffset.y -= globalData.cyBorder2;
			CreateMask(iImage, ptOffset, ~(nStyle & TBBS_INDETERMINATE),
					nStyle & TBBS_DISABLED);

			pDC->SetTextColor(0L);              // 0 -> 0
			pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1 -> 1

			ASSERT(globalData.cxBorder2 == globalData.cyBorder2);
			int delta = (nStyle & TBBS_INDETERMINATE) ?
				globalData.bWin4 ? globalData.cxBorder2*2 : 3 : globalData.cxBorder2*2;

			// only draw the dither brush where the mask is 1's
			BitBlt(pDC->m_hDC,
				x + globalData.cxBorder2, y + globalData.cyBorder2, dx-delta, dy-delta,
				hDCMono, 0, 0, ROP_DSPDxax);
			pDC->SelectObject(hbrOld);
		}
	}

	return TRUE;
}

BOOL CPaletteBarN::PrepareDrawButton(DrawState& ds)
{
	ASSERT(m_hbmImageWell != NULL);
	ASSERT(m_sizeButton.cx > 2 && m_sizeButton.cy > 2);

	// We need to kick-start the bitmap selection process.
	ds.hbmOldGlyphs = (HBITMAP)SelectObject(hDCGlyphs, m_hbmImageWell);
	ds.hbmMono = CreateBitmap(m_sizeButton.cx-2, m_sizeButton.cy-2,
					1, 1, NULL);
	ds.hbmMonoOld = (HBITMAP)SelectObject(hDCMono, ds.hbmMono);
	if (ds.hbmOldGlyphs == NULL || ds.hbmMono == NULL || ds.hbmMonoOld == NULL)
	{
		TRACE0("Error: can't draw toolbar.\n");
		AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
		return FALSE;
	}
	return TRUE;
}

void CPaletteBarN::EndDrawButton(DrawState& ds)
{
	SelectObject(hDCMono, ds.hbmMonoOld);
	AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
	SelectObject(hDCGlyphs, ds.hbmOldGlyphs);
}
///////////////////////////// end of module ///////////////
