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
#include "CBoxButt.h"
#include "IGenRsrc.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "CurveBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCurveBox, CBoxWnd)
	//{{AFX_MSG_MAP(CCurveBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE() 

IMPLEMENT_DYNAMIC(CCurveBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE Curvebox[] =
{
	// same order as in the bitmap 'Curvebox.bmp'
	IDB_C_CIRCLE,
	IDB_C_ELLIPSE,
	IDB_C_PARABOLA,
	IDB_C_LINEAR,
	IDB_C_QUADRATIC,
	IDB_C_HERMITE,
	IDB_C_BEZIER,
	IDB_C_BSPLINE,
	IDB_C_NURB
	
}; 
/////////////////////////////////////////////////////////////////////////////
// CCurveBox
CCurveBox::CCurveBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // CurveBar Column 
}                    
	
CCurveBox::~CCurveBox()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCurveBox message handlers
int CCurveBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CCurveBox::OnCreate\nCannot Create ElemBar");
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

void CCurveBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// 
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}
//////////////////////////////////////////////////////////////////////
BOOL CCurveBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(Curvebox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CCurveBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("Curve resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_CURVEBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_CBOX)|
		!m_wndElemBar.SetButtons(Curvebox,sizeof(Curvebox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CCurveBox::CreateElemBar\nFailed to create toolbar\n");
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
int CCurveBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CCurveBox::GoRespondtoMouse()
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
	//////////////////////////////
	pWnd->SetMouseBoxType(CURVEBOX);
	////////////////////////////////////////// Hide CurveBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentIGenID(GetActiveElemObject());
	///////////////////////
	m_WPARAM = IDW_CURVEBOX;
//	ReSetDataDialogs();
	/////////////
	switch(GetActiveElemObject())
	{
		case C_CIRCLE:
			str = "CIRCULAR@Curve";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_ELLIPSE:
			str = "ELLIPTIC@Curve";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_PARABOLA:
			str = "PARABOLIC@Curve";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_LINEAR:
			str = "LINEAR@BSPLINE";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_QUADRATIC:
			str = "QUADRATIC@BSPLINE";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_HERMITE:
			str = "NOT@INCLUDED";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_BEZIER:
			str = "1_Segment@BEZIER";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_BSPLINE:
			str = "CUBIC@BSPLINE";
			pWnd->SetstrIGenID(str);
			////
			break;
		case C_NURB:
			str = "CUBIC@NURB";
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
///////////////////////////// end of module ////////////////