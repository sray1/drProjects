// Elembox.cpp : implementation file
//
#include "stdafx.h"

/////////////////////
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
/////////////////////
#include "drgrafrm.h"
#include "UserMsg.h"

#include "EoxWnd.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CEoxWnd, CWnd)
	//{{AFX_MSG_MAP(CEoxWnd)
	ON_WM_PAINT()  
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE() 

IMPLEMENT_DYNAMIC(CEoxWnd,CWnd)
/////////////////////////////////////////////////////////////////////////////
// CEoxWnd
CEoxWnd::CEoxWnd()
{ 
//	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // NodeBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    
	
CEoxWnd::~CEoxWnd()
{
}

//BOOL CEoxWnd::Create(CMDIFrameWnd* pParentWnd,CRect rect)
BOOL CEoxWnd::Create(CWnd* pParentWnd,CRect rect)
{
	m_pParentWnd	= pParentWnd;
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWnd,
						NULL,
						WS_POPUP,
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

BOOL CEoxWnd::Create(CWnd* pParentWnd,CRect rect,UINT uParentID)
{
	m_ParentID		= uParentID;
	m_pParentWnd	= pParentWnd;
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWnd,
						NULL,
						WS_POPUP,
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

UINT CEoxWnd::GetHeight()
{
	return m_nHeight;
}

UINT CEoxWnd::GetWidth()
{
	return m_nWidth;
}

int CEoxWnd::GetActiveTool()
{
	return m_nActiveTool;
}

int CEoxWnd::GetActiveElemObject()
{
	return m_nActiveElemObject;
} 

void CEoxWnd::FillToolNumArray()
{ 
	for (int i = 0; i<nMax_MousTypes; i++)
		m_nToolNumArray[i] =  MoTypes[i].num;
}

int CEoxWnd::GetToolNum(int index)
{

	if (index>(int)m_nElemBarButtCount)
	{
		AfxMessageBox("CEoxWnd::GetToolNum index Overflow");
    	return -2;
    }
    else	
		return m_nToolNumArray[index];
		
}		 	

BOOL CEoxWnd::IsEditMoveTool(UINT nID)
{
  
//	type;  		// -2  	= edit/move/post tool(for button management)
	for (int i = 0; i<nMax_MousTypes; i++)
	{
		if((int)nID == MoTypes[i].num)
		{
			if(MoTypes[i].type == MO_TOOL) 
				return TRUE;
		}
	}	
	return FALSE;
}	  
/////////////////////////////////////////////////////////////////////////////
void CEoxWnd::OnPaint()
{

	//////////
//	return;	// do nothing
	//////////

   CPaintDC dc(this); // device context for painting
	
   RECT    Rect;
   CPen    Pen;
   CBrush  Brush;
   CBrush* PtrOldBrush;
	
// color background LightGray

   GetClientRect(&Rect);
   dc.FillRect(&Rect,Brush.FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)) );

/*
// Create inner border rectangle

   	Rect.left   += 2;
   	Rect.top    += 2;
   	Rect.right  -= 2;
   	Rect.bottom -= 2;		

   	PtrOldBrush= (CBrush*)dc.SelectStockObject(NULL_BRUSH); 
  	dc.Rectangle(&Rect);
   	dc.SelectObject(PtrOldBrush);
*/   	
   	Brush.DeleteObject();
	/////////////////////////////
			
}

/////////////////////////////////////////////////////////////////////////////
// CElemBar message handlers
/*
int CEoxWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CEoxWnd::CalcBoxRect(CRect& BoxRect, CRect& ItemRect,int BoxWidth,int BoxHeight,
						 int ScreenHeight, int ScreenWidth,BOOL bColumn)
{
	if(bColumn)														// Vertical
	{
	   // attach to Top or Bottom of the Item
	   if((ItemRect.bottom + BoxHeight) < ScreenHeight) 
	   { // to the bottom
	      	BoxRect.left  	= ItemRect.left; //
			BoxRect.top  	= ItemRect.top;
	//   				BoxRect.top    += EB_BUTT_COUNT;//overlap
			BoxRect.right 	= BoxRect.left + BoxWidth;
			BoxRect.bottom 	= BoxRect.top  + BoxHeight;
		}
		else
	   { // to the top 
			BoxRect.right 	= ItemRect.right;
	     	BoxRect.left  	= ItemRect.left; //
			BoxRect.bottom 	= ItemRect.bottom;
	//   				BoxRect.top    += EB_BUTT_COUNT;//overlap
			BoxRect.top 	= BoxRect.bottom  - BoxHeight;
		}
	}
	else															// Horizontal
	{
		// attach to left or right of the Item
		if((ItemRect.right + BoxWidth) < ScreenWidth) 
	    { // to the right
	      	BoxRect.left  	= ItemRect.right; //
   			BoxRect.top  	= ItemRect.top;
	// 			BoxRect.top    += EB_BUTT_COUNT;//overlap
   			BoxRect.right 	= BoxRect.left + BoxWidth;
   			BoxRect.bottom 	= BoxRect.top  + BoxHeight;
   		}
   		else
	    { // to the left 
   			BoxRect.right 	= ItemRect.left;
	       	BoxRect.left  	= BoxRect.right - BoxWidth; //
   			BoxRect.top  	= ItemRect.top;
	//			BoxRect.top    += EB_BUTT_COUNT;//overlap
   			BoxRect.bottom 	= BoxRect.top  + BoxHeight;
   		}
	}
}

void CEoxWnd::ReSetDataDialogs()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetApp()->m_pMainWnd; 
	/////////////////////////////////////////////////////////////////////////
//092498	pWnd->SendMessage(ID_RESET_MODELESS,m_WPARAM);
	AfxMessageBox("CEoxWnd::ReSetDataDialogs() Should NOT be Called");
	////////////////////
}
///////////////////////////// end of module ////////////////
