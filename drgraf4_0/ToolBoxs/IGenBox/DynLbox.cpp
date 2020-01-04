// StaticLoadbox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
/////////////////////
#include "palette.h"
#include "DynLButt.h"
#include "IGenRsrc.h"	// DLL specific
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "DynLRsrc.h"	// DynticLoad ResourceIDs
//////////////////////
#include "Def_DynL.h"   // DynticLoad
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "DynLbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDynLBox, CBoxWnd)
	//{{AFX_MSG_MAP(CDynLBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()
IMPLEMENT_DYNAMIC(CDynLBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Operbar

static UINT BASED_CODE DynLBox[] =
{
	// same order as in the bitmap 'DynLort.bmp'
	IDB_HIS_FORCE,
	IDB_HIS_DISPLACE,
	IDB_HIS_VELOCITY,
	IDB_HIS_ACCEL,
	IDB_HIS_PRESSURE,
	IDB_HIS_THERMAL,
	IDB_HIS_LUMPMASS
};
/////////////////////////////////////////////////////////////////////////////
// CDynLBox
CDynLBox::CDynLBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // PatchBar Column 
}                    
	
CDynLBox::~CDynLBox()
{
}

void CDynLBox::OnDestroy()
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}
/////////////////////////////////////////////////////////////////////////////
// CDynLBox message handlers
int CDynLBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("ERROR:CDynLBox::OnCreate\nCannot Create OperBar");
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
//////////////////////////////////////////////////////////////////////
BOOL CDynLBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(DynLBox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CDynLBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("Patch resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_DYNAMICLOADBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_DYNLBOX) ||
		!m_wndElemBar.SetButtons(DynLBox,sizeof(DynLBox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("Failed to create DynLBar\n");
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
int CDynLBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CDynLBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////
	CString strCur;
	CString str;
	strCur = "Assigning ";
	///////////////////////////////////////
	pWnd->SetCntlBoxStatus(TRUE);
	pWnd->SetIGenBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	/////////////////////////////////////////////////////////
	pWnd->SetMouseBoxType(DYNAMICLOADBOX);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentCntlID(GetActiveElemObject());
	////////////////////////////////////////// Hide DynLBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle    
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Initiate StaticLoad Modeless Dlg
	ReSetDataDialogs();
	////////////////////	
	switch(pWnd->GetCurrentCntlID())
	{
		//////////////////////////////////////////// Create
		case HIS_FORCE:
			///////////////////////////// String
			str = "FORCE@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "FORCE History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_DISPLACE:
			///////////////////////////// String
			str = "DISPLACE@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "DISPLACE/ROTATION History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_VELOCITY:
			///////////////////////////// String
			str = "VELOCITY@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "VELOCITY History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_ACCEL:
			///////////////////////////// String
			str = "ACCELERATION@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "ACCELERATION History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_PRESSURE:
			///////////////////////////// String
			str = "PRESSURE@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "PRESSURE History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_THERMAL:
			///////////////////////////// String
			str = "THERMAL@HISTORY";
			pWnd->SetstrCntlID(str);
			strCur += "THERMAL History"; 
			break;
		//////////////////////////////////////////// Create
		case HIS_LUMPMASS:
			///////////////////////////// String
			str = "LUMP@MASS";
			pWnd->SetstrCntlID(str);
			strCur += "LUMP MASS"; 
			break;
		//////////////////////////////////////////// Create
		default:
			///////////////////////////// String
			str = "DON'T KNOW";
			pWnd->SetstrCntlID(str);
			///////////////////////////////////// 
			strCur = "UNKNOWN Control Option";
			pWnd->SetstrCurrID(strCur);
			return;
	}
	////////////////
	if(pWnd->GetCurrentOperID() != GOP_POST)
	{
		if(bMeshMode)
		{
			strCur += "@Left CLICK: Select from MESH Box";
			pWnd->GetMGenBox()->ShowWindow(TRUE);	// Open MGenBox
			pWnd->GetMGenBox()->SetFocus();
		}
		else
		{
			strCur += "@Left CLICK: Select from GENERATOR Box";
			pWnd->GetIGenBox()->ShowWindow(TRUE);	// Open IGenBox
			pWnd->GetIGenBox()->SetFocus();
		}
		///
	}
	pWnd->SetstrCurrID(strCur);
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
}

void CDynLBox::ReSetDataDialogs()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetApp()->m_pMainWnd; 
	/////////////////////////////////////////////////////////////////////////
	pWnd->SendMessage(IDM_VIEW_GENBOX);	// Open Generation Box (Node,Curve etc.)
	////////////////////
}
/////////////////////////////// end of module ///////////
