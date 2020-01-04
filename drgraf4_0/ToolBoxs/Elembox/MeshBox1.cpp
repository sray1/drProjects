// Meshbox.cpp : implementation file
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
#include "MeshBut1.h"
#include "EoxWndID.h"
#include "EoxBMPID.h"
#include "EBoxrsrc.h"	// DLL specific
/////////////////////
#include "Def_Elem.h"   // Elements
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "MeshBox1.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEBox_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMeshBox1, CEoxWnd)
	//{{AFX_MSG_MAP(CMeshBox1)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CMeshBox1,CEoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Meshbox.bmp'
	IDB_PIPE,
	IDB_BEAM,
	IDB_TRUSS
	
}; 

/////////////////////////////////////////////////////////////////////////////
// CMeshBox1
CMeshBox1::CMeshBox1()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CMeshBox1::~CMeshBox1()
{
}
/////////////////////////////////////////////////////////////////////////////
// CMeshBox1 message handlers
int CMeshBox1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CMeshBox1::OnCreate\nCannot Create ElemBar");
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
	/////////////////////////////////////////// PipeBox
	GetPipeBox()->Create((CWnd*)this,BoxRect);
/*
	/////////////////////////////////////////// HexBox
	GetBeamBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// PenBox
	GetTrussBox()->Create((CWnd*)this,BoxRect);
*/
	return 0;
}

void CMeshBox1::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// PipeBox
	if(GetPipeBox()->m_hWnd != NULL)
		GetPipeBox()->DestroyWindow();
/*
	/////////////////////////////////////////// BeamBox
	if(GetBeamBox()->m_hWnd != NULL)
		GetBeamBox()->DestroyWindow();
	/////////////////////////////////////////// TrussBox
	if(GetTrussBox()->m_hWnd != NULL)
		GetTrussBox()->DestroyWindow();
	////////////////////////////
*/
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CMeshBox1::CreateElemBar()
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
		AfxMessageBox("ERROR:CMeshBox1::CreateElemBar()\nButton Count Discrepancy");
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
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_MESHBOX1,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_MESHBOX1) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CMeshBox1::CreateElemBar\nFailed to create toolbar\n");
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

void CMeshBox1::OnPaint()
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

int CMeshBox1::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CMeshBox1::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetIGenBoxStatus(FALSE);
	pWnd->SetCntlBoxStatus(FALSE);
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
	UINT mID		= (UINT)nID;
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	////////////////////////////
	pWnd->SetCurrentPostID(mID);
	//////////////////////////
	switch(mID)
	{
		case PIPE:

//			pWnd->SetMouseBoxType(PIPEBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetPipeBox()->GetWidth();
			BoxHeight 	= (int)GetPipeBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
/*
			if((GetBeamBox()->GetStyle()) & WS_VISIBLE)
				GetBeamBox()->ShowWindow(SW_HIDE);
			////////////
			if((GetTrussBox()->GetStyle()) & WS_VISIBLE)
				GetTrussBox()->ShowWindow(SW_HIDE);
*/
			///////////
			GetPipeBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
/*

		case BEAM:

//			pWnd->SetMouseBoxType(BEAMBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetTriBox()->GetWidth();
			BoxHeight 	= (int)GetTriBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
			if((GetPipeBox()->GetStyle()) & WS_VISIBLE)
				GetPipeBox()->ShowWindow(SW_HIDE);
			////////////
			if((GetTrussBox()->GetStyle()) & WS_VISIBLE)
				GetTrussBox()->ShowWindow(SW_HIDE);
			///////////
			GetBeamBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;


		case TRUSS:

//			pWnd->SetMouseBoxType(BEAMBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetTriBox()->GetWidth();
			BoxHeight 	= (int)GetTriBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
			if((GetPipeBox()->GetStyle()) & WS_VISIBLE)
				GetPipeBox()->ShowWindow(SW_HIDE);
			////////////
			if((GetBeamBox()->GetStyle()) & WS_VISIBLE)
				GetBeamBox()->ShowWindow(SW_HIDE);
			///////////
			GetTrussBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
*/			
			
		default:
//			pWnd->SetMouseBoxType(MESHBOX1);
			//////////////////////////////////
			if((GetPipeBox()->GetStyle()) & WS_VISIBLE)
				GetPipeBox()->ShowWindow(SW_HIDE);
/*
			if((GetBeamBox()->GetStyle()) & WS_VISIBLE)
				GetBeamBox()->ShowWindow(SW_HIDE);
			if((GetTrussBox()->GetStyle()) & WS_VISIBLE)
				GetTrussBox()->ShowWindow(SW_HIDE);
*/
			break;
		///////		
			
	}
	////////////////////////////////////////// Hide MeshBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentPostID(GetActiveElemObject());
	m_WPARAM = IDW_MESHBOX1;
//	ReSetDataDialogs();
	/////////////////////////////////////////////////////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
