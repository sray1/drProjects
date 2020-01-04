// dataview.cpp : implementation file
//

#include "stdafx.h"  
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "drgraDoc.h"
#include "AxObjMgr.h"
/////////////////////
#include "SpDataVu.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	DATAVIEW	100
/////////////////////////////////////////////////////////////////////////////
// CSpDataVu

IMPLEMENT_DYNCREATE(CSpDataVu, CAxDataVu)

CSpDataVu::CSpDataVu()
{
}

CSpDataVu::~CSpDataVu()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CSpDataVu, CRowView)
	//{{AFX_MSG_MAP(CSpDataVu)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CSpDataVu drawing

/////////////////////////////////////////////////////////////////////////////
// CSpDataVu message handlers
/////////////////////////////////////////////////////////////////////////////

void CSpDataVu::OnLButtonDblClk(UINT nFlags, CPoint point)
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

void CSpDataVu::OnSetFocus(CWnd* pOldWnd)
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

