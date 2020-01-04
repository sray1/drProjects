// drgravw.cpp : implementation of the C31View class
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
#include "31View.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////
// C31View

IMPLEMENT_DYNCREATE(C31View, CDrawView)

BEGIN_MESSAGE_MAP(C31View, CDrawView)
	//{{AFX_MSG_MAP(C31View)
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
// C31View construction/destruction

C31View::C31View()
{
	m_nView		= VIEW31;  // View31 = 1 etc.
}

C31View::~C31View()
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

void C31View::OnInitialUpdate()
{
	///////////////////////////////////////////
	//Note: This is a good time to fill up the list with Special Objects
	//////////////////////////////
	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection
    ////////////////////////////////////////////////////////////////////
	CScrollView::OnInitialUpdate();
	///////////////////////////////
	m_nView		= VIEW31;
	m_OpMode	= OP_INPUT;
	////////////////////////////// set all others.
	CDrawView::OnInitialUpdate();
	////////////////////////////// if any Dlg Open
	MouseActivateViewMatUpdate();
}

void C31View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

//	AfxMessageBox("OnUpdate");GetDocString

	CDrGrafDoc* pDoc = GetDocument();
	CObjectMgr* pObjectMgr 	= GetDocument()->GetObjectMgr();
	////////////////////////////// Title
//	SetWindowText("Z = Horizontal Axis   X = Vertical Axis");
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
		UpdateObject(nObjectIndex,nObjectType,VIEW31);
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
// C31View drawing

int C31View::GetActiveObjectIndex()
{
	CDrGrafDoc* pDoc = GetDocument();
	return (pDoc->GetObjectMgr()->GetActiveRowIndex());		//june96
}

int C31View::GetObjectCount()
{
	CDrGrafDoc* pDoc = GetDocument();
	return (pDoc->GetObjectMgr()->GetRowCount());			//june96
} 

void C31View::ChangeSelectionNextObjectIndex(BOOL bNext)
{
	CDrGrafDoc* pDoc = GetDocument();
	pDoc->GetObjectMgr()->ChangeSelectionNextObjectIndex(bNext);
}

void C31View::ChangeSelectionToObjectIndex(int nObjectIndex)
{
	CDrGrafDoc* pDoc = GetDocument();
	pDoc->GetObjectMgr()->ChangeSelectionToObjectIndex(nObjectIndex);
} 

void C31View::OnDrawObject(CDC* pDC, int nObjIndex,int nObjectType, BOOL bSelected)
{
	CDrGrafDoc* pDoc = GetDocument();
	/////////////////////////////////////////// Show Element View for the Element
	pDoc->GetObjectMgr()->Do_Object_DrawView(pDC,bSelected,nObjIndex,VIEW31,nObjectType);
	/////////////////////////////////////////////////////////////////////////////		
}	

void C31View::OnDraw(CDC* pDC)
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
	CDrawView::OnDraw(pDC);
    ///////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// C31View printing

BOOL C31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void C31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void C31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL C31View::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrGrafCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void C31View::OnInsertObject()
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
void C31View::OnCancelEditCntr()
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
void C31View::OnSetFocus(CWnd* pOldWnd)
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
	if(pWnd->GetActiveViewNumber() != VIEW31)
	{
		pWnd->SetActiveViewNumber(VIEW31);
		pWnd->OnModeInput(); 
		//////////////////////////////////
		m_nView		= VIEW31;
		//////////////////////////
		MouseActivateViewMatUpdate();
		//////////////////////////
	}
	/////////////////////////////////
	CScrollView::OnSetFocus(pOldWnd);
}

int C31View::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	///////////////////////////////////// if NodeDlg Open
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	if(pWnd->GetActiveViewNumber() != VIEW31)
	{
		pWnd->SetActiveViewNumber(VIEW31);
		pWnd->OnModeInput(); 
		//////////////////////////////////
		m_nView		= VIEW31;
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
void C31View::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// C31View diagnostics

#ifdef _DEBUG
void C31View::AssertValid() const
{
	CScrollView::AssertValid();
}

void C31View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrGrafDoc* C31View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrGrafDoc)));
	return (CDrGrafDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C31View message handlers

int C31View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDrawView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

///////////////////////////////////////////////////// Mouse Manipulation
void C31View::OnMouseMove(UINT nFlags, CPoint point)
{
	MouseMove(nFlags,point);
}

void C31View::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	LButtonDown(nFlags,point);
}

void C31View::OnLButtonUp(UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	LButtonUp(nFlags,point);
}

void C31View::OnRButtonDown(UINT nFlags, CPoint point)
{ 
	SetCapture();
	RButtonDown(nFlags,point);
}
		
void C31View::OnRButtonUp(UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	RButtonUp(nFlags,point);
}
//////////////////////////////// end of module /////////////////////////  
