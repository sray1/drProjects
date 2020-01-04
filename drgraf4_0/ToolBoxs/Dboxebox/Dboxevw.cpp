// dboxevw.cpp : implementation of the CDBoxEBoxView class
//

#include "stdafx.h"
#include "dboxebox.h"
#include "mainfrm.h"
/////////////////////////////////////////////// toolboxes
#include "dbebextn.h"         
///////////////////////////////////////////////
#include "dboxedoc.h"
#include "dboxevw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
BOOL CElemBox::Create(CWnd* pParentWnd,CRect rect)
{

	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWnd_EB,
						NULL,
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_ElemBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CDrawBox::Create(CWnd* pParentWnd,CRect rect)
{

	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_DB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWnd_DB,
						NULL,
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_ElemBOX*/,
						NULL
					);
	return bOk;				
}

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxView

IMPLEMENT_DYNCREATE(CDBoxEBoxView, CView)

BEGIN_MESSAGE_MAP(CDBoxEBoxView, CView)
	//{{AFX_MSG_MAP(CDBoxEBoxView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxView construction/destruction

CDBoxEBoxView::CDBoxEBoxView()
{
	// TODO: add construction code here
}

CDBoxEBoxView::~CDBoxEBoxView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxView drawing

void CDBoxEBoxView::OnDraw(CDC* pDC)
{
	CDBoxEBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxView diagnostics

#ifdef _DEBUG
void CDBoxEBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CDBoxEBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBoxEBoxDoc* CDBoxEBoxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBoxEBoxDoc)));
	return (CDBoxEBoxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxView message handlers

int CDBoxEBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	////////////////////////////////////////////////////////// DrawBox
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	//////////////////////////// 
	if(!(GetElemBox()->Create((CWnd*)this,rect)))
	{
		AfxMessageBox("View:Could Not Create ElemBox");
		return -1;
	}	
//	GetElemBox()->ShowWindow(SW_HIDE);
	//////////////////////////// 
	if(!GetDrawBox()->Create((CWnd*)this,rect)) 
	{
		AfxMessageBox("View:Could Not Create DrawBox");
		return -1;
	}	
//	GetElemBox()->ShowWindow(SW_HIDE);
	////////////////////////////
    /////////////////////////////////////////////////////////
//	CMainFrame* pWnd = (CMainFrame*)(AfxGetApp()->m_pMainWnd );
	///////////////////////////////////////////// DrawBox 
//	int DBoxwidth  		= (int)pWnd->GetDrawBox()->GetWidth();
//	int DBoxheight 		= (int)pWnd->GetDrawBox()->GetHeight();
	int DBoxwidth  		= (int)GetDrawBox()->GetWidth();
	int DBoxheight 		= (int)GetDrawBox()->GetHeight();
	
	CRect Rect;
	
   	Rect.left   = 1;
   	Rect.top    = 41;        // 
   	Rect.right  = Rect.left + DBoxwidth;
   	Rect.bottom = Rect.top 	+ DBoxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&Rect,WS_BORDER|WS_CAPTION,FALSE); 
	////////////////////////////////////// shift to adjust caption+border
//	pWnd->GetDrawBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
	GetDrawBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
                        Rect.bottom-Rect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
                        
	///////////////////////////////////////////// ElemBox 
//	int EBoxwidth  = (int)pWnd->GetElemBox()->GetWidth();
//	int EBoxheight = (int)pWnd->GetElemBox()->GetHeight(); 
	int EBoxwidth  = (int)GetElemBox()->GetWidth();
	int EBoxheight = (int)GetElemBox()->GetHeight(); 
	
   	Rect.left   = Rect.left + DBoxwidth + 1;
//   	Rect.left   = 1;
   	Rect.top    = 41;        // 
   	Rect.right  = Rect.left + EBoxwidth;
   	Rect.bottom = Rect.top  + EBoxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&Rect,WS_BORDER|WS_CAPTION,FALSE); 
	////////////////////////////////////// shift to adjust caption+border
//	pWnd->GetElemBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
	GetElemBox()->SetWindowPos(NULL,Rect.left,Rect.top,Rect.right-Rect.left,
                        Rect.bottom-Rect.top,SWP_NOZORDER|SWP_SHOWWINDOW);								
	////////////////////////////////////////////////////////////////////////////////// 
	
	return 0;
}
//////////////////////////////////////////


void CDBoxEBoxView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    /////////////////////////////////////////////////////////
//	CMainFrame* pWnd = (CMainFrame*)(AfxGetApp()->m_pMainWnd );
	///////////////////
	static CString str;
	str = "EBoxDBox:LButDown\n";
	/////////////////////////////////////////////////////////
	// following logic won't work if both boxes have button down
	// in actual situation, one of the boxes will be disabled
	///////////////////////////////////////////////////////// ElemBox	
//	int nID = pWnd->GetElemBox()->GetActiveElemObject();
	int nID = GetElemBox()->GetActiveElemObject();
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
//	nID = pWnd->GetDrawBox()->GetActiveDrawObject();// 
	nID = GetDrawBox()->GetActiveDrawObject();// 
	if(nID<0) return;
	////////////////////////////////////////// get index
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if(nID == DbTypes[i].num)
		{
			str += DbTypes[i].ObjName;
			/////////////////////////
//			if((nID = pWnd->GetDrawBox()->GetActiveTool())>=0)
			if((nID = GetDrawBox()->GetActiveTool())>=0)
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
	
	
}
