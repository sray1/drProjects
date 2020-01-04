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
#include "SpeLButt.h"
#include "IGenRsrc.h"	// DLL specific
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "SpeLRsrc.h"	// DynticLoad ResourceIDs
//////////////////////
#include "Def_SpeL.h"   // DynticLoad
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "SpeLbox.h" 

#ifdef _DEBUG
#undef TSPL_FILE
static char BASED_CODE TSPL_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSpeLBox, CBoxWnd)
	//{{AFX_MSG_MAP(CSpeLBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()
IMPLEMENT_DYNAMIC(CSpeLBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Operbar

static UINT BASED_CODE SpeLBox[] =
{
	// same order as in the bitmap 'SpeLort.bmp'
	IDB_SPL_FORCE,
	IDB_SPL_DISPLACE,
	IDB_SPL_VELOCITY,
	IDB_SPL_ACCEL,
	IDB_SPL_PRESSURE,
	IDB_SPL_THERMAL,
	IDB_SPL_LUMPMASS
};
/////////////////////////////////////////////////////////////////////////////
// CSpeLBox
CSpeLBox::CSpeLBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // PatchBar Column 
}                    
	
CSpeLBox::~CSpeLBox()
{
}

void CSpeLBox::OnDestroy()
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}
/////////////////////////////////////////////////////////////////////////////
// CSpeLBox message handlers
int CSpeLBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("ERROR:CSpeLBox::OnCreate\nCannot Create OperBar");
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
BOOL CSpeLBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(SpeLBox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CSpeLBox::CreateElemBar()\nButton Count Discrepancy");
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
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_SPECTRALOADBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_SPELBOX) ||
		!m_wndElemBar.SetButtons(SpeLBox,sizeof(SpeLBox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("Failed to create SpeLBar\n");
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
int CSpeLBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CSpeLBox::GoRespondtoMouse()
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
	pWnd->SetMouseBoxType(SPECTRALOADBOX);
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentCntlID(GetActiveElemObject());
	////////////////////////////////////////// Hide SpeLBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle     
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Initiate StaticLoad Modeless Dlg
	ReSetDataDialogs();
	////////////////////	
	switch(pWnd->GetCurrentCntlID())
	{
		//////////////////////////////////////////// Create
		case SPL_FORCE:
			///////////////////////////// String
			str = "FORCE@SPECTRUM";
			pWnd->SetstrCntlID(str);
			strCur += "FORCE Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_DISPLACE:
			///////////////////////////// String
			str = "DISPLACE@SPECTRUM";
			pWnd->SetstrCntlID(str);
			strCur += "DISPLACE/ROTATION Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_VELOCITY:
			///////////////////////////// String
			str = "VELOCITY@SPECTRUM";
			pWnd->SetstrCntlID(str);
			strCur += "VELOCITY Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_ACCEL:
			///////////////////////////// String
			str = "ACCELERATION@SPECTRA";
			pWnd->SetstrCntlID(str);
			strCur += "ACCELERATION Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_PRESSURE:
			///////////////////////////// String
			str = "PRESSURE@SPECTRUM";
			pWnd->SetstrCntlID(str);
			strCur += "PRESSURE Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_THERMAL:
			///////////////////////////// String
			str = "THERMAL@SPECTRUM";
			pWnd->SetstrCntlID(str);
			strCur += "THERMAL Spectrum"; 
			break;
		//////////////////////////////////////////// Create
		case SPL_LUMPMASS:
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

void CSpeLBox::ReSetDataDialogs()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetApp()->m_pMainWnd; 
	/////////////////////////////////////////////////////////////////////////
	pWnd->SendMessage(IDM_VIEW_GENBOX);	// Open Generation Box (Node,Curve etc.)
	////////////////////
}
/////////////////////////////// end of module ///////////
