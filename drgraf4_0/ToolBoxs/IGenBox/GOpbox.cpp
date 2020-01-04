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
#include "GOpButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"	// DLL specific
////////////////////
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
////////////////////
//#include "Dlg_MovT.h"
#include "Dlg_ROTT.h"
////////////////////
#include "GOpBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGOpBox, CBoxWnd)
	//{{AFX_MSG_MAP(CGOpBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()
IMPLEMENT_DYNAMIC(CGOpBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Operbar

static UINT BASED_CODE OperBox[] =
{
	// same order as in the bitmap 'Patch.bmp'
	IDB_GOP_EDIT,
	IDB_GOP_MOVE,
	IDB_GOP_UNPOST,
	IDB_GOP_POST,
	IDB_GOP_DELETE,
	IDB_GOP_MERGE
};
/////////////////////////////////////////////////////////////////////////////
// CGOpBox
CGOpBox::CGOpBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // PatchBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    
	
CGOpBox::~CGOpBox()
{
}

void CGOpBox::OnDestroy()
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}

/////////////////////////////////////////////////////////////////////////////
// CGOpBox message handlers
int CGOpBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("ERROR:CGOpBox::OnCreate\nCannot Create OperBar");
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
BOOL CGOpBox::CreateElemBar()
{
	// Create the Bar in Box
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(OperBox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CGOpBox::CreateElemBar()\nButton Count Discrepancy");
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
if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_GENOPBOX,IDC_BUTTON) ||
	!m_wndElemBar.LoadBitmap(IDB_GOPBOX) ||
	!m_wndElemBar.SetButtons(OperBox,sizeof(OperBox)/sizeof(UINT),m_nElemBarColMax) )
{
	TRACE("Failed to create GOperBar\n");
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
int CGOpBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CGOpBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	CString str;
	strCur = "Ready to ";
	///////////////////////////////////////
	pWnd->SetIGenBoxStatus(TRUE);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////// Hide OperBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
//	ShowWindow(SW_HIDE);
	///////////////////////////// Replace EDimBox by ControlBox
	pWnd->GetCntlBox()->ShowWindow(TRUE);	// Open ControlBox
	pWnd->GetEDimBox()->ShowWindow(FALSE);	// Close EDimBox
	////////////////////
	CDlg_ROTT DlgMov;
	////////////////
	switch(GetActiveElemObject())
	{
		//////////////////////////////////////////// Create
		case GOP_EDIT:
			///////////////////////////// String
			str = "EDIT";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case GOP_MOVE:
			///////////////////////////// Find Type
			DlgMov.m_Caller = GOP_MOVE;
			if(DlgMov.DoModal() == IDCANCEL)
			{
				///////////////////////////// String
				str = "DON'T KNOW";
				pWnd->SetstrOperID(str);
				///////////////////////////////////// 
				strCur = "UNKNOWN General Option";
				pWnd->SetstrCurrID(strCur);
				return;
			}
			else
			{
				///////////////////////////// SetDlg Info
				if(DlgMov.m_nType == 1)
				{
					pWnd->GetMditMgr()->GetDLDMouse()->SetMoveType(MT_TRANSLATE);
					///////////////////////////// String
					str = "Tran.MOVE";
				}
				else
				if(DlgMov.m_nType == 2)
				{
					pWnd->GetMditMgr()->GetDLDMouse()->SetMoveType(MT_ROTATE);
					///////////////////////////// String
					str = "Rot.MOVE";
				}
				pWnd->SetstrOperID(str);
				strCur += str; 
				break;
			}
		//////////////////////////////////////////// Create
		case GOP_DELETE:
			///////////////////////////// String
			str = "DELETE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
/*
		case GOP_UNDELETE:
			///////////////////////////// String
			str = "UNDELETE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
*/
		//////////////////////////////////////////// Create
		case GOP_POST:
			///////////////////////////// String
			str = "POST";
			pWnd->SetstrOperID(str);
			strCur += str; 
			///////////////////////////// Replace ControlBox by EdimBox
			pWnd->GetCntlBox()->ShowWindow(FALSE);	// close ControlBox
			pWnd->GetEDimBox()->ShowWindow(TRUE);	// Open EDimBox
			////
			break;

		//////////////////////////////////////////// Create
		case GOP_UNPOST:
			///
			pWnd->SetCurrentOperID_Alternate(GetActiveElemObject());
			///////////////////////////// String
			str = "UNPOST";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case GOP_MERGE:
			///////////////////////////// String
			str = "MERGE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		default:
			///////////////////////////// String
			str = "DON'T KNOW";
			pWnd->SetstrOperID(str);
			///////////////////////////////////// 
			strCur = "UNKNOWN General Option";
			pWnd->SetstrCurrID(strCur);
			return;
	}
	////////////////
	if(GetActiveElemObject() == GOP_POST)
	{
		strCur += "@Left CLICK on Object in GENERATOR Box";
		pWnd->SetstrCurrID(strCur);
		pWnd->SendMessage(ID_UPDATE_STATCNTLS);
		///
		pWnd->SetCurrentOperID_Alternate(GetActiveElemObject());
	}
	else
	{
		strCur += "@Left CLICK on Object in CONTROL Box";
		pWnd->SetstrCurrID(strCur);
		pWnd->SendMessage(ID_UPDATE_STATCNTLS);
		///
		pWnd->SetCurrentOperID(GetActiveElemObject());
	}
	/////////
}
/////////////////////////////// end of module ///////////
