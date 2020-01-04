// DrTreeVu.cpp : implementation file
//

#include "stdafx.h"
#include <afxcmn.h>

#include "drgraf.h"
#include "drgradoc.h"
#include "DbObjMgr.h"

#include "TreeHandler.h"
#include "DBRsrc.h"

#include "DrTreeVu.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrTreeVu

IMPLEMENT_DYNCREATE(CDrTreeVu, CTreeView)

CDrTreeVu::CDrTreeVu()
{
	m_pImageList	= new CImageList();
	m_bViewChanged	= FALSE;

}

CDrTreeVu::~CDrTreeVu()
{
//	CImageList	*pimagelist;
//	CTreeCtrl& TCtrl = GetTreeCtrl();

	if(m_pImageList)
	{
//	pimagelist = TCtrl.GetImageList(TVSIL_NORMAL);
		m_pImageList->DeleteImageList();
		delete m_pImageList;
	}
}



BEGIN_MESSAGE_MAP(CDrTreeVu, CTreeView)
	//{{AFX_MSG_MAP(CDrTreeVu)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrTreeVu drawing

void CDrTreeVu::OnDraw(CDC* pDC)
{
	CTreeCtrl& TCtrl = GetTreeCtrl();
	CTreeHandler TH;
	TH.PopulateTreeCtrl(TCtrl);
}

/////////////////////////////////////////////////////////////////////////////
// CDrTreeVu diagnostics

#ifdef _DEBUG
void CDrTreeVu::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDrTreeVu::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrTreeVu message handlers

void CDrTreeVu::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CTreeView::OnLButtonDown(nFlags, point);
}

void CDrTreeVu::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeView::OnLButtonUp(nFlags, point);

}

void CDrTreeVu::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeView::OnMouseMove(nFlags, point);
}

void CDrTreeVu::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeView::OnRButtonDown(nFlags, point);
}

void CDrTreeVu::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CTreeView::OnRButtonUp(nFlags, point);
}

int CDrTreeVu::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CTreeCtrl& TCtrl = GetTreeCtrl();
	TCtrl.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	//////////////////////////////////////
	ASSERT(m_pImageList->Create(8, 8, TRUE/*bMask*/, 2, 0));
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_OPEN);
	ASSERT(m_pImageList->Add(&bitmap, (COLORREF)0xFFFFFF) != -1);
	bitmap.DeleteObject();
	bitmap.LoadBitmap(IDB_CLOSED);
	ASSERT(m_pImageList->Add(&bitmap, (COLORREF)0xFFFFFF) != -1);
	bitmap.DeleteObject();
	ASSERT(m_pImageList->GetImageCount() == 2);
	///
	TCtrl.SetImageList(m_pImageList, TVSIL_NORMAL);
	/////////////////////////////////////////////// Init
	Init();
	/////////
	return 0;
}

int CDrTreeVu::Init()
{
	CTreeCtrl& TCtrl = GetTreeCtrl();
	CTreeHandler TH;
	TH.PopulateTreeCtrl(TCtrl);
	///
	InvalidateRect(NULL);
	UpdateWindow();
	///		
	return 0;
}

void CDrTreeVu::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CDrGrafDoc* pDoc		= (CDrGrafDoc*)GetDocument();
	CDbObjMgr* pDBObjMgr	= pDoc->GetDbObjMgr();
	///////////////////////////////////////////////
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// find out what item is getting Selected
	if (pNMTreeView->hdr.code ==  TVN_SELCHANGED)
	{
		HTREEITEM hSel = pNMTreeView->itemNew.hItem;
		CTreeCtrl& TCtrl = GetTreeCtrl();
//		HTREEITEM hSel = TCtrl.GetSelectedItem();
		ASSERT(hSel != NULL);
		CString strSel = TCtrl.GetItemText(hSel);
		CString strPar;
		HTREEITEM hPar = TCtrl.GetParentItem(hSel);
		if(hPar)	// child
			strPar = TCtrl.GetItemText(hPar);
		else		// top Level already
			strPar = "";
		///////////////////////////////////////////
		pDBObjMgr->SetCurrentParent(strPar);
		pDBObjMgr->SetCurrentItem(strSel);
		/////////////////////////////////////////// Update Views
		pDBObjMgr->ShowActiveObject_On_Off(strSel,strPar,TRUE);
		///////////////////////////
	}
/*
	HTREEITEM hRoot = TCtrl.GetRootItem();
	CString strRoot = TCtrl.GetItemText(hRoot);

	HTREEITEM hParent = TCtrl.GetParentItem(hSel);
	CString strParent = TCtrl.GetItemText(hParent);
*/
	


/***
	TV_ITEM tv_Item;
	tv_Item.mask = TVIF_HANDLE;
	tv_Item.hItem = hSel;
	ASSERT(TCtrl.GetItem(&tv_Item));
	CString strSub = tv_Item.pszText;
	
	HTREEITEM hRoot = TCtrl.GetRootItem();
	tv_Item.mask = TVIF_HANDLE;
	tv_Item.hItem = hRoot;
	ASSERT(TCtrl.GetItem(&tv_Item));
	CString strMain = tv_Item.pszText;
***/
	

	*pResult = 0;
}

void CDrTreeVu::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
/*
	CTreeCtrl& TCtrl = GetTreeCtrl();
	CTreeHandler TH;
	TH.PopulateTreeCtrl(TCtrl);
	///	
	if(TCtrl.GetCount() >0)
	{
		m_bViewChanged = TRUE;
		///
		InvalidateRect(NULL);
		UpdateWindow();
	}
	else
		m_bViewChanged	= FALSE;
*/
}
