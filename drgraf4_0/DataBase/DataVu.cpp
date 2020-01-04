// DataVu.cpp : implementation file
//

#include "stdafx.h"
#include <Limits.h>	// UINT_MAX   

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "DListMgr.h"
/////////////////////
#include "NodeSheet.h"
#include "CNodeSheet.h"
#include "MCNodeSheet.h"
#include "MNodeSheet.h"
#include "CurveSheet.h"
#include "Cur_PSheet.h"
#include "PatchSheet.h"
#include "SolidSheet.h"
#include "Obj3DSheet.h"
#include "Mesh1DSheet.h"
#include "Mesh2DSheet.h"
#include "Mesh3DSheet.h"
#include "Mbj3DSheet.h"
#include "SuppSheet.h"
#include "StalSheet.h"
/////////////////////
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_Supp.h"
#include "Def_Stal.h"
/////////////////////
#include "DbObjMgr.h"

#include "DataVu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataVu

IMPLEMENT_DYNCREATE(CDataVu, CView)

CDataVu::CDataVu()
{
	m_SheetList.InsertObject(new CNodeSheet("Node Properties"));
	m_SheetList.InsertObject(new CCNodeSheet("Control Node Properties"));
	m_SheetList.InsertObject(new CMCNodeSheet("Mesh Control Node Properties"));
	m_SheetList.InsertObject(new CMNodeSheet("Mesh Node Properties"));
	m_SheetList.InsertObject(new CCurveSheet("Curve Properties"));
	m_SheetList.InsertObject(new CCur_PSheet("Profile Curve Properties"));
	m_SheetList.InsertObject(new CPatchSheet("Patch Properties"));
	m_SheetList.InsertObject(new CSolidSheet("Solid Properties"));
	m_SheetList.InsertObject(new CObj3DSheet("Object SubAssembly Properties"));
	m_SheetList.InsertObject(new CMesh1DSheet("1D Mesh Properties"));
	m_SheetList.InsertObject(new CMesh2DSheet("2D Mesh Properties"));
	m_SheetList.InsertObject(new CMesh3DSheet("3D Mesh Properties"));
	m_SheetList.InsertObject(new CMbj3DSheet("Mesh SubAssembly Properties"));
	m_SheetList.InsertObject(new CSuppSheet("Linear Support Properties"));
	m_SheetList.InsertObject(new CStalSheet("Static Load Properties"));
	//////////////////////////////////
	m_CurrentSheetType	= ALL_SHEET;
	m_bSizedBefore		= FALSE;
	m_CurrentObjType	= UINT_MAX;
	m_CurrentstrItem	= "";
	m_bViewChanged		= FALSE;
}

CDataVu::~CDataVu()
{
	while(!(GetSheetList()->IsEmpty()))// delete:
		delete (CDrPropSheet*)(GetSheetList()->RemoveHead());	// 
}



BEGIN_MESSAGE_MAP(CDataVu, CView)
	//{{AFX_MSG_MAP(CDataVu)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataVu drawing

void CDataVu::OnDraw(CDC* pDC)
{
	if(m_bViewChanged)
	{
		ShowCurrentSheet(m_CurrentObjType);
		m_bViewChanged = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDataVu diagnostics

#ifdef _DEBUG
void CDataVu::AssertValid() const
{
	CView::AssertValid();
}

void CDataVu::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataVu message handlers

int CDataVu::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//////////////////////////////////////////
	if (m_CurrentSheetType == ALL_SHEET)
		return Create_AllSheet(lpCreateStruct);
		
	else
	if (m_CurrentSheetType == NO_SHEET)
		return 0;
	else
		return Create_SpecificSheet(m_CurrentSheetType,lpCreateStruct);

}
/*
int CDataVu::Create_NodeSheet(LPCREATESTRUCT lpCreateStruct) 
{

	if (!m_pNodeSheet->Create(this,
			DS_CONTEXTHELP | DS_SETFONT | WS_CHILD | WS_VISIBLE))
	{
		DestroyWindow();
		return FALSE;
	}

	m_pNodeSheet->SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

	// we use the style from the template - but make sure that
	// the WS_BORDER bit is correct.
	// the WS_BORDER bit will be whatever is in dwRequestedStyle

	m_pNodeSheet->ModifyStyle(WS_BORDER|WS_CAPTION,
		lpCreateStruct->style & (WS_BORDER|WS_CAPTION));

	// Force the size requested.
	// Fake a call to OnSize()--it would have been called automatically
	// if this were using the base class implementation of Create().

	CFrameWnd* pParentFrame = GetParentFrame();
	CRect rectSize;
	m_pNodeSheet->GetWindowRect(rectSize);
	pParentFrame->CalcWindowRect(rectSize);
//	OnSize(SIZE_RESTORED, rectSize.Width(), rectSize.Height());

	return 0;
}
*/
int CDataVu::Create_AllSheet(LPCREATESTRUCT lpCreateStruct) 
{
	int nResult = 0;
	////////////////
	POSITION 	pos;
	CDListMgr* pList = GetSheetList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPropSheet* pSheet = (CDrPropSheet*)pList->GetNextObject(pos);
		//////////////////////////
		nResult = Create_Sheet(pSheet, lpCreateStruct);
		if(nResult<0)
			return nResult;
	}
	////////////////
	return nResult;
}

int CDataVu::Create_SpecificSheet(FORM_SHEET& fsCurrentSheetType,LPCREATESTRUCT lpCreateStruct) 
{
	int nResult = 0;
	////////////////
	POSITION 	pos;
	CDListMgr* pList = GetSheetList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPropSheet* pSheet	= (CDrPropSheet*)pList->GetNextObject(pos);
		FORM_SHEET fsType		= pSheet->GetSheetType();
		if(fsType != fsCurrentSheetType)
			continue;
		//////////////////////////
		nResult = Create_Sheet(pSheet, lpCreateStruct);
		return nResult;
		///////////////
	}
	///////////
	return nResult;
}

int CDataVu::Create_Sheet(CPropertySheet* pSheet, LPCREATESTRUCT lpCreateStruct) 
{
	// TODO: Add your specialized creation code here
	// create a modeless property page

	if (!pSheet->Create(this,
			DS_CONTEXTHELP | DS_SETFONT | WS_CHILD | WS_VISIBLE))
	{
		DestroyWindow();
		return FALSE;
	}

	pSheet->SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

	// we use the style from the template - but make sure that
	// the WS_BORDER bit is correct.
	// the WS_BORDER bit will be whatever is in dwRequestedStyle

	pSheet->ModifyStyle(WS_BORDER|WS_CAPTION,
		lpCreateStruct->style & (WS_BORDER|WS_CAPTION));

	// Force the size requested.
	// Fake a call to OnSize()--it would have been called automatically
	// if this were using the base class implementation of Create().

	CFrameWnd* pParentFrame = GetParentFrame();
	CRect rectSize;
	pSheet->GetWindowRect(rectSize);
	pParentFrame->CalcWindowRect(rectSize);
//	OnSize(SIZE_RESTORED, rectSize.Width(), rectSize.Height());

	return 0;
}

int CDataVu::UpdateCurrentSheet(CString& strCurrentItem,UINT uCurrentObjType)
{ 
	if(strCurrentItem == "")
		return 0;
	/////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	POSITION 	pos;
	CDListMgr* pList = GetSheetList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPropSheet* pSheet	= (CDrPropSheet*)pList->GetNextObject(pos);
		UINT uObjType			= pSheet->GetObjType();
		if(uObjType != uCurrentObjType)
			continue;
		//////////////////////////
		nResult = pSheet->UpdateSheet(strCurrentItem);
		return nResult;
		///////////////
	}
	/////////////////////////////////////////////////////
	return 0;
}

int CDataVu::ShowCurrentSheet(UINT uCurrentObjType)
{ 
//	CDrGrafDoc* pDoc		= (CDrGrafDoc*)GetDocument();
	HideAllSheet();
	/////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	POSITION 	pos;
	CDListMgr* pList = GetSheetList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPropSheet* pSheet	= (CDrPropSheet*)pList->GetNextObject(pos);
		UINT uObjType		= pSheet->GetObjType();
		if(uObjType != uCurrentObjType)
			continue;
		//////////////////////////
		if(pSheet->GetSafeHwnd() !=0)	// created already
			pSheet->ShowWindow(TRUE);
		///////////////
	}
	/////////////////////////////////////////////////////
	return 0;
}

int CDataVu::HideAllSheet()
{ 
	/////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	POSITION 	pos;
	CDListMgr* pList = GetSheetList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPropSheet* pSheet	= (CDrPropSheet*)pList->GetNextObject(pos);
		//////////////////////////
		if(pSheet->GetSafeHwnd() !=0)	// created already
			pSheet->ShowWindow(FALSE);
		///////////////
	}
	/////////
	return 0;
}

/**
void CDataVu::OnSize(UINT nType, int cx, int cy) 
{

	if (m_CurrentSheetType == NODE_SHEET)
		OnSize_NodeSheet(nType,cx,cy);
	else
		OnSize_CurveSheet(nType,cx,cy);

}


void CDataVu::OnSize_NodeSheet(UINT nType, int cx, int cy) 
{
//	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if (nType != SIZE_MINIMIZED && cx != 0 && cy != 0 && m_pNodeSheet != NULL)
	{
		if (m_bSizedBefore == FALSE)
		{
			m_bSizedBefore = TRUE;

			// get the size of the property sheet
			CRect rectSized;
			m_pNodeSheet->GetWindowRect(rectSized);

			// calculate the size of the frame
			CFrameWnd* pFrame = GetParentFrame();
			if (pFrame != NULL)
			{
				pFrame->CalcWindowRect(rectSized);
				CWnd* pParent = pFrame->GetParent();

				if (pParent != NULL)
					pParent->ScreenToClient(rectSized);

				// resize and reposition the frame
				pFrame->MoveWindow(rectSized);
			}
		}  
	}

}

**/


void CDataVu::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDrGrafDoc* pDoc		= (CDrGrafDoc*)GetDocument();
	CDbObjMgr* pDbObjMgr	= pDoc->GetDbObjMgr();
	///////////////////////////////////////////////
	CString strItem; 
	UINT uObjType = pDbObjMgr->GetObjectName_N_ID(strItem);
	///////////////////////////////////////////////////////
	if(uObjType == UINT_MAX || strItem == "")	// nothing in tree
	{
		m_bViewChanged	= FALSE;
		return;
	}
	///////////////////////////////////////////////////
	if(strItem != "")
	{
		UpdateCurrentSheet(strItem,uObjType);
		/////////////////////////////////////
		m_CurrentObjType	= uObjType;
		m_CurrentstrItem	= strItem;
		m_bViewChanged		= TRUE;
		///
		InvalidateRect(NULL);
		UpdateWindow();
	}
	else
		m_bViewChanged	= FALSE;
}

BOOL CDataVu::OnEraseBkgnd(CDC* pDC) 
{
	// Use the same background color as that of the dialog
	//  (property sheet).

	HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG,
		(WPARAM)pDC->m_hDC, (LPARAM)this->m_hWnd);
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(&rect, CBrush::FromHandle(hBrush));
	return TRUE;
}
