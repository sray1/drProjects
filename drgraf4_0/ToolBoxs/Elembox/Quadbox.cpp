// Quadbox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
//#include "drgradoc.h" 
//#include "ObjMgr.h"
/////////////////////
#include "palette.h"
#include "QuadButt.h"
#include "EoxWndID.h"
#include "EoxBMPID.h"
#include "EBoxrsrc.h"	// DLL specific
/////////////////////
#include "Def_Elem.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "Quadbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEBox_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CQuadBox, CEoxWnd)
	//{{AFX_MSG_MAP(CQuadBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE() 

IMPLEMENT_DYNAMIC(CQuadBox,CEoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE Quadbox[] =
{
	// same order as in the bitmap 'Quadbox.bmp'
	IDB_QU_4,//						1111		// Quad 4 Nodes
	IDB_QU_8,//						1112		// Quad 8 Nodes
	IDB_QU_9,//						1113		// Quad 9 Nodes
	IDB_QU_12,//					1114		// Quad 12 Nodes
	IDB_QU_16//						1115		// Quad 16 Nodes
	
}; 
/////////////////////////////////////////////////////////////////////////////
// CQuadBox
CQuadBox::CQuadBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // CurveBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    
	
CQuadBox::~CQuadBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CQuadBox message handlers
int CQuadBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CQuadBox::OnCreate\nCannot Create ElemBar");
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
	/////////////////    
	return 0;
}

void CQuadBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// 
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}
//////////////////////////////////////////////////////////////////////
BOOL CQuadBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(Quadbox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CQuadBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("QUADTA resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_QUADBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_QUADBOX) ||
		!m_wndElemBar.SetButtons(Quadbox,sizeof(Quadbox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CQuadBox:Failed to create toolbar\n");
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

void CQuadBox::OnPaint()
{

	//////////
//	return;	// do nothing
	//////////

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
/*
int CQuadBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CQuadBox::GoRespondtoMouse()
{
	
	///////////////////////////////////////
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetIGenBoxStatus(FALSE);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////////////// Check If SecondaryBoxes
	CClientDC dc(this);
//	int ScreenWidth = dc.GetDeviceCaps(HORZRES);
	int ScreenHeight = dc.GetDeviceCaps(VERTRES);
	////////////////////////////////////////////
	int nID 	= GetActiveElemObject(); 
	if(nID<0) return;
	//////////////////////////////
//	pWnd->SetMouseBoxType(QUADBOX);
	////////////////////////////////////////// Hide PenBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentPostID(GetActiveElemObject());
	///////////////////////
	m_WPARAM = IDW_QUADBOX;
//	ReSetDataDialogs();
	/////////////////////////////////////////////////////
}
///////////////////////////// end of module ////////////////
