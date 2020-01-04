// drgravw.cpp : implementation of the CDrGrafView class
//

#include "stdafx.h"
#include "drgraf.h"

#include "drgradoc.h"
#include "cntritem.h"
#include "drgravw.h"
/////////////////////////////////////////////// toolboxes
#include "drgrafrm.h"
#include "dbebextn.h"         
///////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////
// CDrGrafView

IMPLEMENT_DYNCREATE(CDrGrafView, CScrollView)

BEGIN_MESSAGE_MAP(CDrGrafView, CScrollView)
	//{{AFX_MSG_MAP(CDrGrafView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT, OnCancelEdit)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrGrafView construction/destruction

CDrGrafView::CDrGrafView()
{
	// TODO: add construction code here
}

CDrGrafView::~CDrGrafView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafView drawing

void CDrGrafView::OnDraw(CDC* pDC)
{
	CDrGrafDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CDrgrafCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CDrgrafCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
}

void CDrGrafView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafView printing

BOOL CDrGrafView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrGrafView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrGrafView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CDrGrafView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrgrafCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CDrGrafView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CDrgrafCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CDrgrafCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CDrGrafDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CDrgrafCntrItem(pDoc);
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
//  user interface to cancel an in-place editing session.
void CDrGrafView::OnCancelEdit()
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
void CDrGrafView::OnSetFocus(CWnd* pOldWnd)
{
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

	CScrollView::OnSetFocus(pOldWnd);
}

void CDrGrafView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafView diagnostics

#ifdef _DEBUG
void CDrGrafView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrGrafView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrGrafDoc* CDrGrafView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrGrafDoc)));
	return (CDrGrafDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrGrafView message handlers

int CDrGrafView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	///////////////////////////////////////////////////////// ToolBoxes Creation
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd );
	CRect FrameRect;
	pWnd->GetClientRect(&FrameRect);
	ClientToScreen(&FrameRect);
	///////////////////////////////////////////// DrawBox 
	int DBoxwidth  		= (int)pWnd->GetDrawBox()->GetWidth();
	int DBoxheight 		= (int)pWnd->GetDrawBox()->GetHeight();
	
	CRect Rect;
	
   	Rect.left   = FrameRect.left; //1;
   	Rect.top    = FrameRect.top;  //81;hard coded; todo change based on toolbar
   	Rect.right  = Rect.left + DBoxwidth;
   	Rect.bottom = Rect.top 	+ DBoxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&Rect,WS_BORDER|WS_CAPTION,FALSE); 
	////////////////////////////////////// shift to adjust caption+border
	pWnd->GetDrawBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
                        Rect.bottom-Rect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
                        
	///////////////////////////////////////////// ElemBox 
	int EBoxwidth  = (int)pWnd->GetElemBox()->GetWidth();
	int EBoxheight = (int)pWnd->GetElemBox()->GetHeight(); 
	
   	Rect.left   = FrameRect.left + DBoxwidth + 1; //1;
   	Rect.top    = FrameRect.top;  //81;hard coded; todo change based on toolbar
   	Rect.right  = Rect.left + EBoxwidth;
   	Rect.bottom = Rect.top  + EBoxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&Rect,WS_BORDER|WS_CAPTION,FALSE); 
	////////////////////////////////////// shift to adjust caption+border
	pWnd->GetElemBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
                        Rect.bottom-Rect.top,SWP_NOZORDER|SWP_SHOWWINDOW);								
	//////////////////////////////////////////////////////////////////////	
	return 0;
}

void CDrGrafView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    /////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd );
	///////////////////
	static CString str;
	str = "DrGraf:LButDown\n";
	/////////////////////////////////////////////////////////
	// following logic won't work if both boxes have button down
	// in actual situation, one of the boxes will be disabled
	///////////////////////////////////////////////////////// ElemBox	
	int nID = pWnd->GetElemBox()->GetActiveElemObject();
	if(nID>=0) 
	{
		////////////////////////////////////////// get index 
		for (int i = 0; i<nMax_ElemTypes; i++)
		{
			if(nID == ElTypes[i].num)
			{
				str += ElTypes[i].ObjName; 
				AfxMessageBox(str);
				return;
			}
		} 
	}	
	///////////////////////////////////////////////////////// DrawBox	
	nID = pWnd->GetDrawBox()->GetActiveDrawObject();// 
	if(nID<0) return;
	////////////////////////////////////////// get index
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if(nID == DbTypes[i].num)
		{
			str += DbTypes[i].ObjName;
			/////////////////////////
			if((nID = pWnd->GetDrawBox()->GetActiveTool())>=0)
			{
				for (int j = 0; j<nMax_DBoxTypes; j++)
				{
					if(nID == DbTypes[j].num)
					str += DbTypes[j].ObjName;
				}	 
            }
			AfxMessageBox(str);
			return;
		}
	}	
	
	//////////////////////////////////////////	
	CScrollView::OnLButtonDown(nFlags, point);
}
