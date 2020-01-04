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
#include "MeshButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "EBoxrsrc.h"	// DLL specific
/////////////////////
#include "Def_Elem.h"   // Elements
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "MeshBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEBox_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMeshBox, CWnd)
	//{{AFX_MSG_MAP(CMeshBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CMeshBox,CWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Meshbox.bmp'
	IDB_PIPE,
	IDB_BEAM,
	IDB_TRUSS,
	IDB_TRIANGLE,
	IDB_QUAD,
	IDB_SHELL,
	IDB_HEXA,
	IDB_PENTA,
	IDB_TETRA
	
}; 

/////////////////////////////////////////////////////////////////////////////
// CMeshBox
CMeshBox::CMeshBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CMeshBox::~CMeshBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CMeshBox message handlers
int CMeshBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CMeshBox::OnCreate\nCannot Create ElemBar");
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
	/////////////////////////////////////////// TriBox
	GetTriBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// QuadBox
	GetQuadBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// HexBox
	GetHexBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// PenBox
	GetPenBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// TetBox
	GetTetBox()->Create((CWnd*)this,BoxRect);
	////////////////////////////
	return 0;
}

void CMeshBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// TriBox
	if(GetTriBox()->m_hWnd != NULL)
		GetTriBox()->DestroyWindow();
	/////////////////////////////////////////// QuadBox
	if(GetQuadBox()->m_hWnd != NULL)
		GetQuadBox()->DestroyWindow();
	/////////////////////////////////////////// HexBox
	if(GetHexBox()->m_hWnd != NULL)
		GetHexBox()->DestroyWindow();
	/////////////////////////////////////////// PenBox
	if(GetPenBox()->m_hWnd != NULL)
		GetPenBox()->DestroyWindow();
	/////////////////////////////////////////// HexBox
	if(GetTetBox()->m_hWnd != NULL)
		GetTetBox()->DestroyWindow();
	////////////////////////////
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CMeshBox::CreateElemBar()
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
		AfxMessageBox("ERROR:CMeshBox::CreateElemBar()\nButton Count Discrepancy");
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
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_MESHBAR,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_MESHBOX) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CMeshBox::CreateElemBar\nFailed to create toolbar\n");
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

void CMeshBox::OnPaint()
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

int CMeshBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CMeshBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetIGenBoxStatus(TRUE);
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
	int index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	////////////////////////////
	pWnd->SetCurrentOperID(mID);
	//////////////////////////
	switch(mID)
	{
		case TRIANGLE:

			pWnd->SetMouseBoxType(TRIBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetTriBox()->GetWidth();
			BoxHeight 	= (int)GetTriBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
			if((GetQuadBox()->GetStyle()) & WS_VISIBLE)
				GetQuadBox()->ShowWindow(SW_HIDE);
			if((GetHexBox()->GetStyle()) & WS_VISIBLE)
				GetHexBox()->ShowWindow(SW_HIDE);
			if((GetPenBox()->GetStyle()) & WS_VISIBLE)
				GetPenBox()->ShowWindow(SW_HIDE);
			if((GetTetBox()->GetStyle()) & WS_VISIBLE)
				GetTetBox()->ShowWindow(SW_HIDE);
			///////////
			GetTriBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
			
		case QUAD:

			pWnd->SetMouseBoxType(QUADBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetQuadBox()->GetWidth();
			BoxHeight 	= (int)GetQuadBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetTriBox()->GetStyle()) & WS_VISIBLE)
				GetTriBox()->ShowWindow(SW_HIDE);
			if((GetHexBox()->GetStyle()) & WS_VISIBLE)
				GetHexBox()->ShowWindow(SW_HIDE);
			if((GetPenBox()->GetStyle()) & WS_VISIBLE)
				GetPenBox()->ShowWindow(SW_HIDE);
			if((GetTetBox()->GetStyle()) & WS_VISIBLE)
				GetTetBox()->ShowWindow(SW_HIDE);
			///////////
			GetQuadBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
			
		case HEXAHED:

			pWnd->SetMouseBoxType(HEXBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetHexBox()->GetWidth();
			BoxHeight 	= (int)GetHexBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetQuadBox()->GetStyle()) & WS_VISIBLE)
				GetQuadBox()->ShowWindow(SW_HIDE);
			if((GetTriBox()->GetStyle()) & WS_VISIBLE)
				GetTriBox()->ShowWindow(SW_HIDE);
			if((GetPenBox()->GetStyle()) & WS_VISIBLE)
				GetPenBox()->ShowWindow(SW_HIDE);
			if((GetTetBox()->GetStyle()) & WS_VISIBLE)
				GetTetBox()->ShowWindow(SW_HIDE);
			///////////
			GetHexBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
			
		case PENTAHED:

			pWnd->SetMouseBoxType(PENBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetPenBox()->GetWidth();
			BoxHeight 	= (int)GetPenBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetQuadBox()->GetStyle()) & WS_VISIBLE)
				GetQuadBox()->ShowWindow(SW_HIDE);
			if((GetTriBox()->GetStyle()) & WS_VISIBLE)
				GetTriBox()->ShowWindow(SW_HIDE);
			if((GetHexBox()->GetStyle()) & WS_VISIBLE)
				GetHexBox()->ShowWindow(SW_HIDE);
			if((GetTetBox()->GetStyle()) & WS_VISIBLE)
				GetTetBox()->ShowWindow(SW_HIDE);
			///////////
			GetPenBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
			
		case TETRAHED:

			pWnd->SetMouseBoxType(SOLIDBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetTetBox()->GetWidth();
			BoxHeight 	= (int)GetTetBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetQuadBox()->GetStyle()) & WS_VISIBLE)
				GetQuadBox()->ShowWindow(SW_HIDE);
			if((GetTriBox()->GetStyle()) & WS_VISIBLE)
				GetTriBox()->ShowWindow(SW_HIDE);
			if((GetPenBox()->GetStyle()) & WS_VISIBLE)
				GetPenBox()->ShowWindow(SW_HIDE);
			if((GetHexBox()->GetStyle()) & WS_VISIBLE)
				GetHexBox()->ShowWindow(SW_HIDE);
			///////////
			GetTetBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
            //////////////////////////////////////////////////////////////            
			return;
			
		default:
			pWnd->SetMouseBoxType(IGENBOX);
			//////////////////////////////////
			if((GetQuadBox()->GetStyle()) & WS_VISIBLE)
				GetQuadBox()->ShowWindow(SW_HIDE);
			if((GetTriBox()->GetStyle()) & WS_VISIBLE)
				GetTriBox()->ShowWindow(SW_HIDE);
			if((GetPenBox()->GetStyle()) & WS_VISIBLE)
				GetPenBox()->ShowWindow(SW_HIDE);
			if((GetHexBox()->GetStyle()) & WS_VISIBLE)
				GetHexBox()->ShowWindow(SW_HIDE);
			break;
		///////		
			
	}
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentPostID(GetActiveElemObject());
	m_WPARAM = IDW_MESHBOX;
	ReSetDataDialogs();
	/////////////////////////////////////////////////////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
