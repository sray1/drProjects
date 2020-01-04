// dataview.cpp : implementation file
//

#include "stdafx.h"  
#include "stdlib.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "drgraDoc.h"
#include "MsObjMgr.h"
/////////////////////

#include "MsDataVu.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	DATAVIEW	100
/////////////////////////////////////////////////////////////////////////////
// CMsDataVu

IMPLEMENT_DYNCREATE(CMsDataVu, CRowView)

CMsDataVu::CMsDataVu()
{
}

CMsDataVu::~CMsDataVu()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CMsDataVu, CRowView)
	//{{AFX_MSG_MAP(CMsDataVu)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMsDataVu drawing

/////////////////////////////////////////////////////////////////////////////
// CMsDataVu message handlers
/////////////////////////////////////////////////////////////////////////////
// Overrides of CView and CRowView

void CMsDataVu::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
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

void CMsDataVu::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
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

int CMsDataVu::GetActiveRow()
{
	CDrGrafDoc* pDoc = GetDocument();
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	return (pObjectMgr->GetActiveObjectIndex());
}

int CMsDataVu::GetRowCount()
{
	CDrGrafDoc* pDoc = GetDocument();
	CMsObjMgr* pObjectMgr = pDoc->GetMsObjMgr();
	return (pObjectMgr->GetRowCount());
}

void CMsDataVu::ChangeSelectionNextRow(BOOL bNext)
{
	CDrGrafDoc* pDoc = GetDocument();
	CMsObjMgr* pObjectMgr = pDoc->GetMsObjMgr();
	pObjectMgr->ChangeSelectionNextObjectIndex(bNext);
}

void CMsDataVu::ChangeSelectionToRow(int nRow)
{
	CDrGrafDoc* pDoc = GetDocument();
	CMsObjMgr* pObjectMgr = pDoc->GetMsObjMgr();
	pObjectMgr->ChangeSelectionToObjectIndex(nRow);
}

void CMsDataVu::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
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
	CMsObjMgr* pObjectMgr = pDoc->GetMsObjMgr();
	pObjectMgr->Do_Object_DataView(pDC,y,nRow);
	///////////////////////////////////////
	// Restore the DC.
	if (!pDC->IsPrinting() && bSelected)
	{
		pDC->SetBkColor(crOldBackground);
		pDC->SetTextColor(crOldText);
	}
}


void CMsDataVu::OnLButtonDown(UINT, CPoint point)
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

void CMsDataVu::OnLButtonDblClk(UINT nFlags, CPoint point)
{

//	CRowView::OnLButtonDown(nFlags, point);  //sets active Index
	OnLButtonDown(nFlags, point);  //sets active Index
	///////////////////////////////////////////////////////////// Set ViewNumber
	CDrGrafFrame* pWnd= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetActiveViewNumber(DATAVIEW);
	///////////////////
	CDrGrafDoc* pDoc = GetDocument();
	CMsObjMgr* pObjectMgr = pDoc->GetMsObjMgr();
//	pObjectMgr->Do_Object_Dialog();						todo later
	/////////////////////////////
} 

void CMsDataVu::OnSetFocus(CWnd* pOldWnd)
{ 
	///////////////////////////////////// if NodeDlg Open
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	if(pWnd->GetActiveViewNumber() != VIEWMESH)
	{
		pWnd->SetActiveViewNumber(VIEWMESH);
		//////////////////////////
	}
	/////////////////////////////////
	CRowView::OnSetFocus(pOldWnd);
}
////////////////////////////////// end of module //////////////

