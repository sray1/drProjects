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
#include "SBoxButt.h"
#include "IGenRsrc.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "SolidBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSolidBox, CBoxWnd)
	//{{AFX_MSG_MAP(CSolidBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()

IMPLEMENT_DYNAMIC(CSolidBox, CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE solidbox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_COONS_S,
	IDB_GORDON_S,
	IDB_ROTATE_S,
	IDB_LOFT_S,
	IDB_EXTRUDE_S,
	IDB_DUCT_S,
	IDB_SWEEP_S
	
}; 

/////////////////////////////////////////////////////////////////////////////
// CSolidBox
CSolidBox::CSolidBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // SolidBar Column 
}                    
	
CSolidBox::~CSolidBox()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSolidBox message handlers
int CSolidBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CSolidBox::OnCreate\nCannot Create ElemBar");
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
	/////////////////    
	return 0;
}

void CSolidBox::OnDestroy()
{
	CWnd::OnDestroy();
	///////////////////////////////////////////
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}
//////////////////////////////////////////////////////////////////////
BOOL CSolidBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(solidbox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CSolidBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("Solid resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_SOLIDBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_SBOX)|
		!m_wndElemBar.SetButtons(solidbox,sizeof(solidbox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CSolidBox::CreateElemBar\nFailed to create toolbar\n");
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

/////////////////////////////////////////////////////////////////////////////
// CElemBar message handlers
/*
int CSolidBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CSolidBox::GoRespondtoMouse()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	CString str;
	/////
	pWnd->SetIGenBoxStatus(TRUE);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////////////// Check If SecondaryBoxes
	CClientDC dc(this);
//	int ScreenWidth = dc.GetDeviceCaps(HORZRES);
	int ScreenHeight = dc.GetDeviceCaps(VERTRES);
	CRect BoxRect,ItemRect;;
//	int BoxWidth,BoxHeight,index;
	////////////////////////////////////////////
	int nID 	= GetActiveElemObject(); 
	if(nID<0) return;
	/////////////////
	pWnd->SetMouseBoxType(SOLIDBOX);
	////////////////////////////////////////// Hide SolidBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentIGenID(GetActiveElemObject());
	///////////////////////
	m_WPARAM = IDW_SOLIDBOX;
//	ReSetDataDialogs();
	/////////////
	switch(GetActiveElemObject())
	{
		case S_COONS:
			str = "COONS@Solid";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_GORDON:
			str = "GORDON@Solid";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_ROTATE:
			str = "Solid by@ROTATION";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_LOFT:
			str = "Solid by@LOFTING";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_EXTRUDE:
			str = "Solid by@EXTRUSION";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_DUCT:
			str = "Solid by@DUCTING";
			pWnd->SetstrIGenID(str);
			////
			break;
		case S_SWEEP:
			str = "Solid by@SWEEPING";
			pWnd->SetstrIGenID(str);
			////
			break;
		default:
			str = "UNKNOWN";
			pWnd->SetstrIGenID(str);
			////
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
	///////
	return; 
}
/////////////////////////////// end of module ///////////
