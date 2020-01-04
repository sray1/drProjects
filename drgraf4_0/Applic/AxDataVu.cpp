// dataview.cpp : implementation file
//

#include "stdafx.h"  
#include "stdlib.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "drgraDoc.h"
#include "AxObjMgr.h"
/////////////////////

#include "AxDataVu.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	DATAVIEW	100
/////////////////////////////////////////////////////////////////////////////
// CAxDataVu

IMPLEMENT_DYNCREATE(CAxDataVu, CRowView)

CAxDataVu::CAxDataVu()
{
}

CAxDataVu::~CAxDataVu()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CAxDataVu, CRowView)
	//{{AFX_MSG_MAP(CAxDataVu)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAxDataVu drawing

/////////////////////////////////////////////////////////////////////////////
// CAxDataVu message handlers
/////////////////////////////////////////////////////////////////////////////
// Overrides of CView and CRowView

void CAxDataVu::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{


	if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CDataRowHint) )  )
	{
/*
		// The hint is that an Object has been added (or changed).
		// So, invalidate its rectangle.
		int nObjectIndex  = LOWORD(lHint);
		int nObjectType   = HIWORD(lHint);
		//////////////////////////////////////////////
		UpdateObject(nObjectIndex,nObjectType,VIEW12);
		////////////////////////////////////////////// 
*/


		int nRowIndex = LOWORD(lHint);
		UpdateRow(nRowIndex);
	}
	else
	{
		Invalidate();
	}
	
}

void CAxDataVu::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{
	/////////////////////////////////////////////////////////////////// Deck Not Empty
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
	///////////////////////////////////////////////////////// Color / lOGfONT
	COLORREF Color 	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
 	///////////////////////////////////////////////////////// set font.
    CFont		Font;
    CFont*		pOldFont;
	Font.DeleteObject();
	////////////////
	Font.CreateFontIndirect(&lf);
	pOldFont = (CFont*)(pDC->SelectObject(&Font));
	/////////////////////////////////////////////////////////
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	nRowWidth = tm.tmAveCharWidth * ROW_WIDTH;
	nRowHeight = tm.tmHeight * 1; // 1 line of text
}

int CAxDataVu::GetActiveRow()
{
	CDrGrafDoc* pDoc = GetDocument();
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	return (pObjectMgr->GetActiveObjectIndex());
}

int CAxDataVu::GetRowCount()
{
	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr = pDoc->GetAxObjMgr();
	return (pObjectMgr->GetRowCount());
}

void CAxDataVu::ChangeSelectionNextRow(BOOL bNext)
{
	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr = pDoc->GetAxObjMgr();
	pObjectMgr->ChangeSelectionNextObjectIndex(bNext);
}

void CAxDataVu::ChangeSelectionToRow(int nRow)
{
	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr = pDoc->GetAxObjMgr();
	pObjectMgr->ChangeSelectionToObjectIndex(nRow);
}

void CAxDataVu::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
{
	// Prepare for highlighting or un-highlighting the check, depending
	// on whether it is the currently selected check or not.  And
	// paint the background (behind the text) accordingly.
	CBrush brushBackground;

	// save colors for drawing selected item on the screen
	COLORREF crOldText = 0;
	COLORREF crOldBackground = 0;

	if (!pDC->IsPrinting())
	{
		if (bSelected)
		{
			brushBackground.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			crOldBackground = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			crOldText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			brushBackground.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
		}

		CRect rectSelection;
		pDC->GetClipBox(&rectSelection);
		rectSelection.top = y;
		rectSelection.bottom = y + m_nRowHeight;
		pDC->FillRect(&rectSelection, &brushBackground);
	}
	/////////////////////////////// Show Element Data for the row
	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr = pDoc->GetAxObjMgr();
	pObjectMgr->Do_Object_DataView(pDC,y,nRow);
	///////////////////////////////////////
	// Restore the DC.
	if (!pDC->IsPrinting() && bSelected)
	{
		pDC->SetBkColor(crOldBackground);
		pDC->SetTextColor(crOldText);
	}
}


void CAxDataVu::OnLButtonDown(UINT, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	CRect rect(point, CSize(1,1));
	int nFirstRow, nLastRow;
	RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
	if (nFirstRow <= (GetRowCount() - 1))
		ChangeSelectionToRow(nFirstRow);
}
////////////////////////////////// end of module //////////////

