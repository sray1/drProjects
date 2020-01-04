// Elembox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "palette.h"
#include "IGenRsrc.h"	// DLL specific
#include "EDimButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
////////////////////////////////////////
#include "EBoxRsrc.h"	// DLL specific
#include "EoxWndID.h"
#include "EoxBMPID.h"
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Elem.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"

#include "EDimBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CEDimBox, CBoxWnd)
	//{{AFX_MSG_MAP(CEDimBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()
IMPLEMENT_DYNAMIC(CEDimBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Operbar

static UINT BASED_CODE EDimBox[] =
{
	// same order as in the bitmap 'Patch.bmp'
	IDB_EDIM_0,
	IDB_EDIM_1,
	IDB_EDIM_2,
	IDB_EDIM_3,
};
/////////////////////////////////////////////////////////////////////////////
// CEDimBox
CEDimBox::CEDimBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // PatchBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    
	
CEDimBox::~CEDimBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CEDimBox message handlers
int CEDimBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("ERROR:CEDimBox::OnCreate\nCannot Create EDimBar");
		return -1;
    }
	
	m_wndElemBar.ShowWindow((m_wndElemBar.GetStyle() & WS_VISIBLE) == 0);
    /////////////////////////////////////////////////// set Height/Width
   	UINT width  = m_nElemBarColMax*EB_BNSIZE_CX;
   	////////////////
   	SetWidth(width);
   	/////////////////
   	UINT height = m_nElemBarRowMax*EB_BNSIZE_CY;//
	///////////////////
	SetHeight(height);
	////////////////////////////////////////////////// Secondary Boxes
	CRect BoxRect;
	BoxRect.left = BoxRect.top = BoxRect.right = BoxRect.bottom = 0;
	/////////////////////////////////////////// MeshBox
	GetMeshBox0()->Create((CWnd*)this,BoxRect,IDW_MESHBOX0);
	/////////////////////////////////////////// MeshBox
	GetMeshBox1()->Create((CWnd*)this,BoxRect,IDW_MESHBOX1);
	/////////////////////////////////////////// MeshBox
	GetMeshBox2()->Create((CWnd*)this,BoxRect,IDW_MESHBOX2);
	/////////////////////////////////////////// MeshBox
	GetMeshBox3()->Create((CWnd*)this,BoxRect,IDW_MESHBOX3);
	/////////////////    
	return 0;
}

void CEDimBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// MeshBox
	if(GetMeshBox0()->m_hWnd != NULL)
		GetMeshBox0()->DestroyWindow();
	/////////////////////////////////////////// MeshBox
	if(GetMeshBox1()->m_hWnd != NULL)
		GetMeshBox1()->DestroyWindow();
	/////////////////////////////////////////// MeshBox
	if(GetMeshBox2()->m_hWnd != NULL)
		GetMeshBox2()->DestroyWindow();
	/////////////////////////////////////////// MeshBox
	if(GetMeshBox3()->m_hWnd != NULL)
		GetMeshBox3()->DestroyWindow();
	/////////////////////////////////////////// Bar
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CEDimBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(EDimBox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CEDimBox::CreateElemBar()\nButton Count Discrepancy");
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
	AfxSetResourceHandle(extensionIGen_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("EDimBox resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_ELEMDIMBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_EDIMBOX) ||
		!m_wndElemBar.SetButtons(EDimBox,sizeof(EDimBox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CEDimBox:Failed to create EDimBar\n");
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

void CEDimBox::OnPaint()
{

	///////////////
//?	return;      // do nothing
	///////////////

   CPaintDC dc(this); // device context for painting
	
   RECT    Rect;
   CPen    Pen;
   CBrush  Brush;
//   CBrush* PtrOldBrush;
	
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

int CEDimBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CEDimBox::GoRespondtoMouse()
{
	
//	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
//	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	BOOL bMeshMode = FALSE;	//  FALSE = GENERATOR Mode (FOR NOW: 12/09/97)
	////////////////////////////////////////////
	if(bMeshMode)
	{
		pWnd->SetCntlBoxStatus(FALSE);
		pWnd->SetIGenBoxStatus(TRUE);
	}
	else
	{
		pWnd->SetCntlBoxStatus(TRUE);
		pWnd->SetIGenBoxStatus(FALSE);
	}
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////////////// Check If SecondaryBoxes
	CClientDC dc(this);
	int ScreenWidth = dc.GetDeviceCaps(HORZRES);
	int ScreenHeight = dc.GetDeviceCaps(VERTRES);
	CRect BoxRect,ItemRect;;
	int BoxWidth,BoxHeight,index;
	////////////////////////////////////////////
	int nID 	= GetActiveElemObject(); 
	if(nID<0) return;
	//////////////////////////////
	UINT mID	= (UINT)nID;
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	////////////////////////////
	pWnd->SetCurrentCntlID(mID);
	///////////
//#define EDIM_0				1163
//#define EDIM_1				1164
//#define EDIM_2				1165
//#define EDIM_3				1166
	switch(mID)
	{
		case EDIM_0:

//			pWnd->SetMouseBoxType(ELEMDIMBOX);
			//////////////////////////////////////////////////////////////
			if((GetMeshBox1()->GetStyle()) & WS_VISIBLE)
				GetMeshBox1()->ShowWindow(SW_HIDE);
			if((GetMeshBox2()->GetStyle()) & WS_VISIBLE)
				GetMeshBox2()->ShowWindow(SW_HIDE);
			if((GetMeshBox3()->GetStyle()) & WS_VISIBLE)
				GetMeshBox3()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetMeshBox0()->GetWidth();
			BoxHeight 	= (int)GetMeshBox0()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(EDIM_0);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsEDimOpen(0))
			{	
				GetMeshBox0()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
						BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				////////////////////////////////////////// Hide EDimBox by toggle
//				ShowWindow((GetStyle() & WS_VISIBLE) == 0);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
				break;
			

		case EDIM_1:

//			pWnd->SetMouseBoxType(ELEMDIMBOX);
			//////////////////////////////////////////////////////////////
			if((GetMeshBox0()->GetStyle()) & WS_VISIBLE)
				GetMeshBox0()->ShowWindow(SW_HIDE);
			if((GetMeshBox2()->GetStyle()) & WS_VISIBLE)
				GetMeshBox2()->ShowWindow(SW_HIDE);
			if((GetMeshBox3()->GetStyle()) & WS_VISIBLE)
				GetMeshBox3()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetMeshBox1()->GetWidth();
			BoxHeight 	= (int)GetMeshBox1()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(EDIM_1);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsEDimOpen(1))
			{	
				GetMeshBox1()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
						BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				////////////////////////////////////////// Hide EDimBox by toggle
//				ShowWindow((GetStyle() & WS_VISIBLE) == 0);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
				break;
			

		case EDIM_2:

//			pWnd->SetMouseBoxType(ELEMDIMBOX);
			//////////////////////////////////////////////////////////////
			if((GetMeshBox0()->GetStyle()) & WS_VISIBLE)
				GetMeshBox0()->ShowWindow(SW_HIDE);
			if((GetMeshBox1()->GetStyle()) & WS_VISIBLE)
				GetMeshBox1()->ShowWindow(SW_HIDE);
			if((GetMeshBox3()->GetStyle()) & WS_VISIBLE)
				GetMeshBox3()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetMeshBox2()->GetWidth();
			BoxHeight 	= (int)GetMeshBox2()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(EDIM_2);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsEDimOpen(2))
			{	
				GetMeshBox2()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
						BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				////////////////////////////////////////// Hide EDimBox by toggle
//				ShowWindow((GetStyle() & WS_VISIBLE) == 0);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
				break;
			

		case EDIM_3:

//			pWnd->SetMouseBoxType(ELEMDIMBOX);
			//////////////////////////////////////////////////////////////
			if((GetMeshBox0()->GetStyle()) & WS_VISIBLE)
				GetMeshBox0()->ShowWindow(SW_HIDE);
			if((GetMeshBox2()->GetStyle()) & WS_VISIBLE)
				GetMeshBox2()->ShowWindow(SW_HIDE);
			if((GetMeshBox1()->GetStyle()) & WS_VISIBLE)
				GetMeshBox1()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetMeshBox3()->GetWidth();
			BoxHeight 	= (int)GetMeshBox3()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(EDIM_1);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsEDimOpen(3))
			{	
				GetMeshBox3()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
						BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				////////////////////////////////////////// Hide EDimBox by toggle
//				ShowWindow((GetStyle() & WS_VISIBLE) == 0);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
				break;
			

	
			
		default:

//			pWnd->SetMouseBoxType(ELEMDIMBOX);
			//////////////////////////////////
			if((GetMeshBox0()->GetStyle()) & WS_VISIBLE)
				GetMeshBox0()->ShowWindow(SW_HIDE);
			if((GetMeshBox1()->GetStyle()) & WS_VISIBLE)
				GetMeshBox1()->ShowWindow(SW_HIDE);
			if((GetMeshBox2()->GetStyle()) & WS_VISIBLE)
				GetMeshBox2()->ShowWindow(SW_HIDE);
			if((GetMeshBox3()->GetStyle()) & WS_VISIBLE)
				GetMeshBox3()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			break;
			///////		
			
	}
	////////////////////////////////////////// Hide EDimBox by toggle
//	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	///////////////////////////////////// Reset TaskID
	if(bMeshMode)
		pWnd->SetCurrentIGenID_Mesh(GetActiveElemObject());
	else
		pWnd->SetCurrentCntlID_Alternate(GetActiveElemObject());
//	pWnd->SetCurrentPostID(GetActiveElemObject());
	///////////////////////
	m_WPARAM = IDW_ELEMDIMBOX;
//	ReSetDataDialogs();
	/////////////////////////////////////////////////////
	return; 
		
}
/////////////////////////////// end of module ///////////
