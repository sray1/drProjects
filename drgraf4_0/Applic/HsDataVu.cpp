// dataview.cpp : implementation file
//

#include "stdafx.h"  
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "drgraDoc.h"
#include "AxObjMgr.h"
/////////////////////
#include "HsDataVu.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	DATAVIEW	100
/////////////////////////////////////////////////////////////////////////////
// CHsDataVu

IMPLEMENT_DYNCREATE(CHsDataVu, CAxDataVu)

CHsDataVu::CHsDataVu()
{
}

CHsDataVu::~CHsDataVu()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CHsDataVu, CRowView)
	//{{AFX_MSG_MAP(CHsDataVu)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CHsDataVu drawing

/////////////////////////////////////////////////////////////////////////////
// CHsDataVu message handlers
/////////////////////////////////////////////////////////////////////////////

void CHsDataVu::OnLButtonDblClk(UINT nFlags, CPoint point)
{

//	CRowView::OnLButtonDown(nFlags, point);  //sets active Index
	OnLButtonDown(nFlags, point);  //sets active Index
	///////////////////////////////////////////////////////////// Set ViewNumber
	CDrGrafFrame* pWnd= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetActiveViewNumber(DATAVIEW);
	///////////////////
	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr = pDoc->GetAxObjMgr();
//	pObjectMgr->Do_Object_Dialog();						todo later
	/////////////////////////////
} 

void CHsDataVu::OnSetFocus(CWnd* pOldWnd)
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

