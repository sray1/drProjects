// Elembox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
/////////////////////
#include "palette.h"
#include "IsoGButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IBoxrsrc.h"	// DLL specific
/////////////////////
#include "Def_Elem.h"   // Operations
#include "Def_Supp.h"   // Operations
#include "Def_StaL.h"   // Operations
#include "Def_SpeL.h"   // Operations
#include "Def_DynL.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "elembox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEBox_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CIsoGBox, CWnd)
	//{{AFX_MSG_MAP(CIsoGBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CIsoGBox,CWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_NODE,
	IDB_CURVE,
	IDB_PATCH,
	IDB_SOLID

	
}; 

/////////////////////////////////////////////////////////////////////////////
// CIsoGBox
CIsoGBox::CIsoGBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CIsoGBox::~CIsoGBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CIsoGBox message handlers
int CIsoGBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CIsoGBox::OnCreate\nCannot Create ElemBar");
		return -1;
    }
	
	m_wndElemBar.ShowWindow((m_wndElemBar.GetStyle() & WS_VISIBLE) == 0);
    /////////////////////////////////////////////////// set Height/Width
//   	UINT width  = 5 + 1 + m_nElemBarColMax*EB_BNSIZE_CX + 3 + 1;
   	UINT width  = m_nElemBarColMax*EB_BNSIZE_CX;
   	////////////////
   	SetWidth(width);
   	/////////////////
//+   	UINT height = 2*EB_CAP_ETC_SIZE + 10;                  // caption etc.
//   	UINT height = 10;                  // border etc.
//   	height +=    m_nElemBarRowMax*EB_BNSIZE_CY;//
   	UINT height = m_nElemBarRowMax*EB_BNSIZE_CY;//
	///////////////////
	SetHeight(height);
	//////////////////////////////////////////////////////////////////    
	////////////////////////////////////////////////// Secondary Boxes
	CRect BoxRect;
	BoxRect.left = BoxRect.top = BoxRect.right = BoxRect.bottom = 0;
	/////////////////////////////////////////// INodeBox
	GetNodeBox()->Create((CWnd*)this,BoxRect,IDW_ISOGBAR);
	/////////////////////////////////////////// ICurveBox
	GetCurveBox()->Create((CWnd*)this,BoxRect,IDW_ISOGBAR);
	/////////////////////////////////////////// IPatchBox
	GetPatchBox()->Create((CWnd*)this,BoxRect,IDW_ISOGBAR);
	/////////////////////////////////////////// ISolidBox
	GetSolidBox()->Create((CWnd*)this,BoxRect,IDW_ISOGBAR);
	/////////////////    
	return 0;
}

void CIsoGBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// CurveBox
	if(GetNodeBox()->m_hWnd != NULL)
		GetNodeBox()->DestroyWindow();
	/////////////////////////////////////////// CurveBox
	if(GetCurveBox()->m_hWnd != NULL)
		GetCurveBox()->DestroyWindow();
	/////////////////////////////////////////// PatchBox
	if(GetPatchBox()->m_hWnd != NULL)
		GetPatchBox()->DestroyWindow();
	/////////////////////////////////////////// SolidBox
	if(GetSolidBox()->m_hWnd != NULL)
		GetSolidBox()->DestroyWindow();
	////////////////////////////
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CIsoGBox::CreateElemBar()
{

	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;       // ElemBar Left,Top
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(elembox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CIsoGBox::CreateElemBar()\nButton Count Discrepancy");
		return FALSE;
	}
	////////////////////////////////////////////////////////////////////// 
	CString strRes;
//////////////////////////////////////////////////////////////////////////
/*
#ifdef _AFXDLL

	TRACE("In Elembox.Create\n");

	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	//////////////////////
	HINSTANCE hInstApp = AfxGetInstanceHandle(); // uses client's instance handle
	HINSTANCE hOldInst = AfxGetResourceHandle(); 
	///////////////
	AfxSetResourceHandle(hInstApp); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	//////////////
	AfxSetResourceHandle(hOldInst); // resource handle back 
    //////////////
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEBox_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#endif	
*/
#ifdef _AFXDLL
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEBox_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	if(m_ParentID == IDW_STALBAR)
	{
		if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_ISOGBAR,IDC_BUTTON) ||
			!m_wndElemBar.LoadBitmap(IDB_ISOGBOX) ||
			!m_wndElemBar.SetButtons(StaL_IBox,sizeof(StaL_IBox)/sizeof(UINT),m_nElemBarColMax) )
		{
			TRACE("CIsoGBox::CreateElemBar()\nFailed to create StaL_IsoGBar\n");
			return FALSE;       // fail to create
		} 
	}
	else
	if(m_ParentID == IDW_SPELBAR)
	{
		if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_ISOGBAR,IDC_BUTTON) ||
			!m_wndElemBar.LoadBitmap(IDB_ISOGBOX) ||
			!m_wndElemBar.SetButtons(SpeL_IBox,sizeof(SpeL_IBox)/sizeof(UINT),m_nElemBarColMax) )
		{
			TRACE("CIsoGBox::CreateElemBar()\nFailed to create SpeL_IsoGBar\n");
			return FALSE;       // fail to create
		} 
	}
	else
	if(m_ParentID == IDW_DYNLBAR)
	{
		if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_ISOGBAR,IDC_BUTTON) ||
			!m_wndElemBar.LoadBitmap(IDB_ISOGBOX) ||
			!m_wndElemBar.SetButtons(DynL_IBox,sizeof(DynL_IBox)/sizeof(UINT),m_nElemBarColMax) )
		{
			TRACE("CIsoGBox::CreateElemBar()\nFailed to create DynL_IsoGBar\n");
			return FALSE;       // fail to create
		} 
	}
	else
	{
			TRACE("CIsoGBox::CreateElemBar()\nFailed to create IsoGBar\n");
			return FALSE;       // fail to create
	}
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#endif

	//////////////////////////////////////////////// set Row Count
	m_nElemBarRowMax = m_nElemBarButtCount/m_nElemBarColMax;
	if(m_nElemBarButtCount%m_nElemBarColMax) m_nElemBarRowMax++;
	///////////////////////////////////////// set sizes / NO CAPTION
	CSize szButton,szImage;
	///////////////////////
	szButton.cx  = EB_BNSIZE_CX;
	szButton.cy  = EB_BNSIZE_CY; 
		
	szImage.cx   = EB_IMAGE_CX;
	szImage.cy   = EB_IMAGE_CY;
	///////////////////////
	m_wndElemBar.SetSizes(szButton,szImage,FALSE);
	///////////////////////////////////////////
	return TRUE;
}

void CIsoGBox::OnPaint()
{

	///////////////
//?	return;      // do nothing
	///////////////

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

int CIsoGBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CIsoGBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetElemBoxStatus(TRUE);
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////////////// Check If SecondaryBoxes
	////////////////////////////////////////////////// Check If SecondaryBoxes
	CClientDC dc(this);
//	int ScreenWidth = dc.GetDeviceCaps(HORZRES);
	int ScreenHeight = dc.GetDeviceCaps(VERTRES);
	CRect BoxRect,ItemRect;;
	int BoxWidth,BoxHeight,index;
	////////////////////////////////////////////
	int nID 	= GetActiveElemObject(); 
	if(nID<0) return;
	//////////////////////////////
	UINT mID	= (UINT)GetActiveTool();
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	///////////
	switch(mID)
	{
		case NODE:

			pWnd->SetMouseBoxType(INODBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetNodeBox()->GetWidth();
			BoxHeight 	= (int)GetNodeBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight);
			//////////////////////////////////////////////////////////////
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			GetNodeBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			break;
			
		case CURVE:

			pWnd->SetMouseBoxType(ICURBOX);
			//////////////////////////////////
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetCurveBox()->GetWidth();
			BoxHeight 	= (int)GetCurveBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			GetCurveBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			break;
			
		case PATCH:

			pWnd->SetMouseBoxType(IPATBOX);
			//////////////////////////////////
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetPatchBox()->GetWidth();
			BoxHeight 	= (int)GetPatchBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			GetPatchBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			break;
			
		case SOLID:

			pWnd->SetMouseBoxType(ISOLBOX);
			//////////////////////////////////
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetSolidBox()->GetWidth();
			BoxHeight 	= (int)GetSolidBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			////////////
			GetSolidBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			break;
			


	
			
		default:

			pWnd->SetMouseBoxType(CONTROLBOX);
			//////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);

			break;
		///////		
			
	}
	/////////////////////////////////////////////////////////////////// Notify
	pWnd->SetActiveObjectType(GetActiveElemObject());
	pWnd->SetActiveToolType(GetActiveTool());
	m_WPARAM = IDW_ISOGBAR;
	ReSetDataDialogs();
	/////////////////////////////////////////////////////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
