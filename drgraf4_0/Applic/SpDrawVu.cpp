// drgravw.cpp : implementation of the CSpDrawVu class
//

#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <Float.h>		// FLT_MAX


#include "Def_IGen.h"
#include "Def_View.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
//////////////////////
#include "drgradoc.h"
#include "cntritem.h" 
/////////////////////
#include "mousemgr.h"
//#include "elmouse.h"
/////////////////////
#include "DrObject.h"
/////////////////////////////////////////////// toolboxes
#include "drgrafrm.h"
//#include "dbebextn.h"         
/////////////////////
#include "SpDrawVu.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////
// CSpDrawVu

IMPLEMENT_DYNCREATE(CSpDrawVu, CAxDrawVu)

BEGIN_MESSAGE_MAP(CSpDrawVu, CAxDrawVu)
	//{{AFX_MSG_MAP(CSpDrawVu)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpDrawVu construction/destruction

CSpDrawVu::CSpDrawVu()
{
	m_nView		= VIEWSPECTRA_IN;  // VIEWSPECTRA_IN = 1 etc.
}

CSpDrawVu::~CSpDrawVu()
{ 
/*
	/////////////////////////// C3D needs todo put in class
	if( m_pL )
		DisposPtr( (Ptr)m_pL );
	if( m_hCLUT )
		DeleteObject( m_hCLUT );
	///////////////////////////	
*/	
}

void CSpDrawVu::OnInitialUpdate()
{
	///////////////////////////////////////////
	//Note: This is a good time to fill up the list with Special Objects
	//////////////////////////////
	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection
	///////////////////////////////////////////////////////////////////// 
	CScrollView::OnInitialUpdate();
	///////////////////////////////
	m_nView		= VIEWSPECTRA_IN;
	m_OpMode	= OP_SPECTRA_IN;
	////////////////////////////// set all others.
	CAxDrawVu::OnInitialUpdate();
	//////////////////////////////
}

void CSpDrawVu::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

//	AfxMessageBox("OnUpdate");

	CDrGrafDoc* pDoc = GetDocument();
	CAxObjMgr* pObjectMgr 	= GetDocument()->GetAxObjMgr();
	//////////////////////////////////////////////////////////// View Changed
	pObjectMgr->SetViewChanged(TRUE);
	/////////////////////////////////
	
	// The document has informed this view that some data has changed.

//	if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CDataRowHint))  )
	if (pHint != NULL)
	{
		// The hint is that an Object has been added (or changed).
		// So, invalidate its rectangle.
		int nObjectIndex  = LOWORD(lHint);
		int nObjectType   = HIWORD(lHint);
		//////////////////////////////////////////////
		UpdateObject(nObjectIndex,nObjectType,VIEWSPECTRA_IN);
		////////////////////////////////////////////// 
	}
    else
		// We can't interpret the hint, so assume that anything might
		// have been updated.
		//////////////////
		Invalidate(); 
		//////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CSpDrawVu drawing

int CSpDrawVu::GetActiveObjectIndex()
{
	CDrGrafDoc* pDoc = GetDocument();
	return (pDoc->GetAxObjMgr()->GetActiveRowIndex());		//june96
}

int CSpDrawVu::GetObjectCount()
{
	CDrGrafDoc* pDoc = GetDocument();
	return (pDoc->GetAxObjMgr()->GetRowCount());			//june96
} 

void CSpDrawVu::ChangeSelectionNextObjectIndex(BOOL bNext)
{
	CDrGrafDoc* pDoc = GetDocument();
	pDoc->GetAxObjMgr()->ChangeSelectionNextObjectIndex(bNext);
}

void CSpDrawVu::ChangeSelectionToObjectIndex(int nObjectIndex)
{
	CDrGrafDoc* pDoc = GetDocument();
	pDoc->GetAxObjMgr()->ChangeSelectionToObjectIndex(nObjectIndex);
} 

void CSpDrawVu::OnDrawObject(CDC* pDC, int nObjIndex,int nObjectType, BOOL bSelected)
{
	CDrGrafDoc* pDoc = GetDocument();
	/////////////////////////////////////////// Show Element View for the Element
	pDoc->GetAxObjMgr()->Do_Object_DrawView(pDC,bSelected,nObjIndex,VIEWSPECTRA_IN,nObjectType);
	/////////////////////////////////////////////////////////////////////////////		
}	

void CSpDrawVu::OnDraw(CDC* pDC)
{
	//////////////////////////////////////////////////////////////////// OLE
	CDrGrafDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CDrGrafCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CDrGrafCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
	//////////////////////////////////////////////////////////////////// Call BaseClass 
	CAxDrawVu::OnDraw(pDC);
    ///////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CSpDrawVu printing

BOOL CSpDrawVu::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSpDrawVu::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSpDrawVu::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CSpDrawVu::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrGrafCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CSpDrawVu::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CDrGrafCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CDrGrafCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CDrGrafDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CDrGrafCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CSpDrawVu::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CSpDrawVu::OnSetFocus(CWnd* pOldWnd)
{ 
	///////////////////////////////////////////////////////////////////////// OLE
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}
	///////////////////////////////////// if NodeDlg Open
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	if(pWnd->GetActiveViewNumber() != VIEWSPECTRA_IN)
	{
		pWnd->SetActiveViewNumber(VIEWSPECTRA_IN);
		pWnd->SwitchMenu(IDR_INPUTMENU); 
		//////////////////////////
		MouseActivateViewMatUpdate();
		//////////////////////////
	}
	/////////////////////////////////
	CScrollView::OnSetFocus(pOldWnd);
}

int CSpDrawVu::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	///////////////////////////////////// if NodeDlg Open
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	if(pWnd->GetActiveViewNumber() != VIEWSPECTRA_IN)
	{
		pWnd->SetActiveViewNumber(VIEWSPECTRA_IN);
 		//////////////////////////////////
		m_nView		= VIEWSPECTRA_IN;
		m_OpMode	= OP_SPECTRA_IN;
		//////////////////////////
		MouseActivateViewMatUpdate();
		//////////////////////////
	}
	////////////////////////////////////////////
	return MA_ACTIVATE;
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CSpDrawVu::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CSpDrawVu diagnostics

#ifdef _DEBUG
void CSpDrawVu::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSpDrawVu::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrGrafDoc* CSpDrawVu::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrGrafDoc)));
	return (CDrGrafDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpDrawVu message handlers

int CSpDrawVu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAxDrawVu::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

///////////////////////////////////////////////////// Mouse Manipulation
void CSpDrawVu::OnMouseMove(UINT nFlags, CPoint point)
{
	MouseMove(nFlags,point);
}

void CSpDrawVu::OnLButtonDown(UINT nFlags, CPoint point)
{
	LButtonDown(nFlags,point);
}

void CSpDrawVu::OnLButtonUp(UINT nFlags, CPoint point)
{
	LButtonUp(nFlags,point);
}

void CSpDrawVu::OnRButtonDown(UINT nFlags, CPoint point)
{ 
	RButtonDown(nFlags,point);
}
		
void CSpDrawVu::OnRButtonUp(UINT nFlags, CPoint point)
{
	RButtonUp(nFlags,point);
}
//////////////////////////////// end of module /////////////////////////  
