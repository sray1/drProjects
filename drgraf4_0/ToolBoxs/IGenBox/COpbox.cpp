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
#include "COpButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"	// DLL specific
////////////////////
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
////////////////////
#include "Dlg_RotT.h"
#include "Dlg_LSyT.h"
////////////////////
#include "COpBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCOpBox, CBoxWnd)
	//{{AFX_MSG_MAP(CCOpBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE()
IMPLEMENT_DYNAMIC(CCOpBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Operbar

static UINT BASED_CODE OperBox[] =
{
	// same order as in the bitmap 'Patch.bmp'
	IDB_COP_CREATE,
	IDB_COP_TRANSLATE,
	IDB_COP_ROTATE,
	IDB_COP_SCALE,
	IDB_COP_REFLECT,
	IDB_COP_SHEAR,
	IDB_COP_STITCH,
	IDB_COP_SPAWN,
	IDB_COP_BLEND,
	IDB_COP_EXTRACT
};
/////////////////////////////////////////////////////////////////////////////
// CCOpBox
CCOpBox::CCOpBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // PatchBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    
	
CCOpBox::~CCOpBox()
{
}

void CCOpBox::OnDestroy()
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
}

/////////////////////////////////////////////////////////////////////////////
// CCOpBox message handlers
int CCOpBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("ERROR:CCOpBox::OnCreate\nCannot Create OperBar");
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
BOOL CCOpBox::CreateElemBar()
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
		AfxMessageBox("ERROR:CCOpBox::CreateElemBar()\nButton Count Discrepancy");
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
if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_CREATEOPBOX,IDC_BUTTON) ||
	!m_wndElemBar.LoadBitmap(IDB_COPBOX) ||
	!m_wndElemBar.SetButtons(OperBox,sizeof(OperBox)/sizeof(UINT),m_nElemBarColMax) )
{
	TRACE("Failed to create COperBar\n");
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
int CCOpBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}
*/
void CCOpBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	CString str;
	strCur = "Ready to ";
	///////////////////////////////////////
	pWnd->SetIGenBoxStatus(TRUE);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	///////////////////////////////////// Reset OperID
	pWnd->SetCurrentOperID(GetActiveElemObject());
	////////////////////////////////////////// Hide OperBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// Hide ParentBox by toggle
	m_pParentWnd->ShowWindow((m_pParentWnd->GetStyle() & WS_VISIBLE) == 0);
//	ShowWindow(SW_HIDE);
	////////////////////
	CDlg_ROTT DlgRot;
	CDlg_LSyT DlgSym;
	////////////////
	switch(pWnd->GetCurrentOperID())
	{
		//////////////////////////////////////////// Create
		case COP_CREATE:
			///////////////////////////// String
			str = "CREATE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_TRANSLATE:
			///////////////////////////// String
			str = "TRANSLATE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_ROTATE:
			///////////////////////////// Find Type
			if(DlgRot.DoModal() == IDCANCEL)
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
				if(DlgRot.m_nType == 1)
				{
					pWnd->GetCreOpMgr()->GetSolCreOp()->SetSpnType(SPN_ROT_ABT_LINE);
					///////////////////////////// String
					str = "ROTATE_L";
				}
				else
				if(DlgRot.m_nType == 2)
				{
					pWnd->GetCreOpMgr()->GetSolCreOp()->SetSpnType(SPN_ROT_REF_2_TAR);
					///////////////////////////// String
					str = "ROTATE_T";
				}
				pWnd->SetstrOperID(str);
				strCur += str; 
				break;
			}
		//////////////////////////////////////////// Create
		case COP_SCALE:
			///////////////////////////// String
			str = "SCALE";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_REFLECT:
			///////////////////////////// Find Type
			if(DlgSym.DoModal() == IDCANCEL)
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
				if(DlgSym.m_nType == 1)
				{
					pWnd->GetCreOpMgr()->GetSolCreOp()->SetSpnType(SPN_SYMM_N);
					///////////////////////////// String
					str = "REFLECT_N";
				}
				else
				if(DlgSym.m_nType == 2)
				{
					pWnd->GetCreOpMgr()->GetSolCreOp()->SetSpnType(SPN_SYMM_3);
					///////////////////////////// String
					str = "REFLECT_3";
				}
				pWnd->SetstrOperID(str);
				strCur += str; 
				break;
			}
		//////////////////////////////////////////// Create
		case COP_SHEAR:
			///////////////////////////// String
			str = "SHEAR";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_SPAWN:
			///////////////////////////// String
			str = "SPAWN";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_STITCH:
			///////////////////////////// String
			str = "STITCH";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_BLEND:
			///////////////////////////// String
			str = "BLEND";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		case COP_EXTRACT:
			///////////////////////////// String
			str = "EXTRACT";
			pWnd->SetstrOperID(str);
			strCur += str; 
			break;
		//////////////////////////////////////////// Create
		default:
			///////////////////////////// String
			str = "DON'T KNOW";
			pWnd->SetstrOperID(str);
			///////////////////////////////////// 
			strCur = "UNKNOWN Create Option";
			pWnd->SetstrCurrID(strCur);
			return;
	}
	////////////////
	strCur += "@Left CLICK: Select from CONTROL Box";
	///////////////////////////// Replace EDimBox by ControlBox
	pWnd->GetCntlBox()->ShowWindow(TRUE);	// Open ControlBox
//	pWnd->GetEDimBox()->ShowWindow(FALSE);	// Close EDimBox
	///////////////////////////////////////////////// Set Focus on ControlBox
	pWnd->GetCntlBox()->SetFocus();
	pWnd->SetstrCurrID(strCur);
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
}
/////////////////////////////// end of module ///////////
