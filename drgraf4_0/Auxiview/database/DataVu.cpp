// DataVu.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "databaseDoc.h"
#include "ObjMap.h"

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
	m_pNodeSheet	= new CNodeSheet;
	m_pCurveSheet	= new CCurSheet;

	m_CurrentSheetType = NODE_SHEET;
	m_bSizedBefore = FALSE;

}

CDataVu::~CDataVu()
{
	if (m_pCurveSheet)
	{
		delete m_pCurveSheet;
		m_pCurveSheet = NULL;
	}
	if (m_pNodeSheet)
	{
		delete m_pNodeSheet;
		m_pNodeSheet = NULL;
	}
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
	CDatabaseDoc* pDoc = (CDatabaseDoc*)GetDocument();
	// TODO: add draw code here
	CString strItem;
	///////////////////////////////////////////////
	UINT type = pDoc->GetObjectType_N_Item(strItem);
// type	
	switch (type)
	{
		case NODE:
			pDoc->SetTitle("Node Database");
			m_pNodeSheet->ShowWindow(TRUE);
			break;
		default:
			m_pNodeSheet->ShowWindow(FALSE);
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

	if (m_CurrentSheetType == NODE_SHEET)
		return Create_NodeSheet(lpCreateStruct);
	else
		return Create_CurveSheet(lpCreateStruct);

}

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

int CDataVu::Create_CurveSheet(LPCREATESTRUCT lpCreateStruct) 
{
	// TODO: Add your specialized creation code here
	// create a modeless property page

	if (!m_pCurveSheet->Create(this,
			DS_CONTEXTHELP | DS_SETFONT | WS_CHILD | WS_VISIBLE))
	{
		DestroyWindow();
		return FALSE;
	}

	m_pCurveSheet->SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

	// we use the style from the template - but make sure that
	// the WS_BORDER bit is correct.
	// the WS_BORDER bit will be whatever is in dwRequestedStyle

	m_pCurveSheet->ModifyStyle(WS_BORDER|WS_CAPTION,
		lpCreateStruct->style & (WS_BORDER|WS_CAPTION));

	// Force the size requested.
	// Fake a call to OnSize()--it would have been called automatically
	// if this were using the base class implementation of Create().

	CFrameWnd* pParentFrame = GetParentFrame();
	CRect rectSize;
	m_pCurveSheet->GetWindowRect(rectSize);
	pParentFrame->CalcWindowRect(rectSize);
//	OnSize(SIZE_RESTORED, rectSize.Width(), rectSize.Height());

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


void CDataVu::OnSize_CurveSheet(UINT nType, int cx, int cy) 
{
//	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if (nType != SIZE_MINIMIZED && cx != 0 && cy != 0 && m_pCurveSheet != NULL)
	{
		if (m_bSizedBefore == FALSE)
		{
			m_bSizedBefore = TRUE;

			// get the size of the property sheet
			CRect rectSized;
			m_pCurveSheet->GetWindowRect(rectSized);

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
	// TODO: Add your specialized code here and/or call the base class
	if (pHint == NULL)
	{
		InvalidateRect(NULL);
		UpdateWindow();
	}
	
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
