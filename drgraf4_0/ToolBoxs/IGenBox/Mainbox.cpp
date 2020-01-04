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
#include "MainButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"	// DLL specific
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "Mainbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainBox, CWnd)
	//{{AFX_MSG_MAP(CMainBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CMainBox,CWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_CREATEOPS,
	IDB_GENOPS,
	IDB_BULLOPS,
	IDB_FEMOPS
	
}; 

/////////////////////////////////////////////////////////////////////////////
// CMainBox
CMainBox::CMainBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CMainBox::~CMainBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CMainBox message handlers
int CMainBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CMainBox::OnCreate\nCannot Create ElemBar");
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
	/////////////////////////////////////////// COpBox
	GetCOpBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// GOpBox
	GetGOpBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// BOpBox
	/////////////////////////////////////////// FOpBox
	/////////////////    
	return 0;
}

void CMainBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// COpBox
	if(GetCOpBox()->m_hWnd != NULL)
		GetCOpBox()->DestroyWindow();
	/////////////////////////////////////////// GOpBox
	if(GetGOpBox()->m_hWnd != NULL)
		GetGOpBox()->DestroyWindow();
	/////////////////////////////////////////// BOpBox
	/////////////////////////////////////////// FOpBox
	////////////////////////////
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CMainBox::CreateElemBar()
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
		AfxMessageBox("ERROR:CMainBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_MAINBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_MAINBOX) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CMainBox::CreateElemBar()\nFailed to create toolbar\n");
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

void CMainBox::OnPaint()
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

int CMainBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CMainBox::GoRespondtoMouse()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////
	CString strCur;
	CString str;
	/////
	str = "UNKNOWN";
	pWnd->SetstrCntlID(str);
	pWnd->SetstrIGenID(str);
	pWnd->SetCurrentIGenID(UNONE);
	pWnd->SetCurrentCntlID(UNONE);
	pWnd->SetActiveToolType((int)UNONE);
	///////////////////////////////////////
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
//052997	pWnd->SetCurrentOperID(mID);
	//////////////////////////
	switch(mID)
	{
		case CREATEOPS:

			///////////////////////////////////////////
			if((GetGOpBox()->GetStyle()) & WS_VISIBLE)
				GetGOpBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			pWnd->SetMouseBoxType(OPERBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetCOpBox()->GetWidth();
			BoxHeight 	= (int)GetCOpBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
			GetCOpBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
			//////////////////////////////////////////////////////////////            
			return;
		
		case GENOPS:

			///////////////////////////////////////////
			if((GetCOpBox()->GetStyle()) & WS_VISIBLE)
				GetCOpBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			pWnd->SetMouseBoxType(OPERBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetGOpBox()->GetWidth();
			BoxHeight 	= (int)GetGOpBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,TRUE);
			////////////
			GetGOpBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
			//////////////////////////////////////////////////////////////            
			return;

			
		case BULLOPS:
		case FEMOPS:
			
			
		default:

			pWnd->SetMouseBoxType(MAINBOX);
			//////////////////////////////////
			if((GetGOpBox()->GetStyle()) & WS_VISIBLE)
				GetGOpBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////
			if((GetCOpBox()->GetStyle()) & WS_VISIBLE)
				GetCOpBox()->ShowWindow(SW_HIDE);
			break;
		///////		
			
	}
	///////////////////////////////////// Reset OperID
	if(bMeshMode)
		pWnd->SetCurrentOperID_Mesh(GetActiveElemObject());
	else
		pWnd->SetCurrentOperID(GetActiveElemObject());
	///////////////////////////////////// Close MainBox
	if(GetStyle() & WS_VISIBLE)
		ShowWindow(SW_HIDE);
	///////////////////////
	m_WPARAM = IDW_MAINBOX;
//	ReSetDataDialogs();
	/////////////////////////////////////////////////////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
