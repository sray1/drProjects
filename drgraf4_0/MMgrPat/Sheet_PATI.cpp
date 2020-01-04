// dlg_PatI.cpp : implementation file
//

#include "stdafx.h"

#include "Def_MouseAct.h"
//////////////////////////
/*
#include "Dlg_PI_EndCond.h"
#include "Dlg_PI_Xtrude.h"
#include "Dlg_PI_Revolv.h"
#include "Dlg_PI_Loft.h"
#include "Dlg_PI_Duct.h"
#include "Dlg_PI_Sweep.h"
#include "Dlg_PI_Coons.h"
#include "Dlg_PI_Tensor.h"
#include "Dlg_PI_Gordon.h"
//#include "Dlg_PatI.h"
*/
///////////////////////
#include "CommRsrc.h"
////////////////////
#include "Sheet_PATI.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSheet_PATI,CPropertySheet)
/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CSheet_PATI dialog


CSheet_PATI::CSheet_PATI(UINT nIDCaption,CWnd* pParentWnd,PATCHPROC PatProc,UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	/////////////////
	ConstructPages(pParentWnd);
	////////////////////////////
	m_pWnd 		= pParentWnd;
	m_PatProc	= PatProc;
}

CSheet_PATI::CSheet_PATI(LPCTSTR pszCaption, CWnd* pParentWnd,PATCHPROC PatProc ,UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	/////////////////
	ConstructPages(pParentWnd);
	////////////////////////////
	m_pWnd 		= pParentWnd;
	m_PatProc	= PatProc;
}

void CSheet_PATI::ConstructPages(CWnd* pParentWnd)
{
	m_pXtrudePage	= new CDlg_PI_Xtrude(pParentWnd/*Actually MainWnd*/,PP_EXTRUDE);
	m_pRevolvPage	= new CDlg_PI_Revolv(pParentWnd/*Actually MainWnd*/,PP_ROTATE);
	m_pLoftPage		= new CDlg_PI_Loft(pParentWnd/*Actually MainWnd*/,PP_LOFT);
	m_pDuctPage		= new CDlg_PI_Duct(pParentWnd/*Actually MainWnd*/,PP_DUCT);
	m_pSweepPage	= new CDlg_PI_Sweep(pParentWnd/*Actually MainWnd*/,PP_SWEEP);
	m_pCoonsPage	= new CDlg_PI_Coons(pParentWnd/*Actually MainWnd*/,PP_COONS);
	m_pTensorPage	= new CDlg_PI_Tensor(pParentWnd/*Actually MainWnd*/,PP_TENSOR);
	m_pGordonPage	= new CDlg_PI_Gordon(pParentWnd/*Actually MainWnd*/,PP_GORDON);
	m_pEndCondPage	= new CDlg_PI_EndCond(pParentWnd/*Actually MainWnd*/,PP_TENSOR);
}

CSheet_PATI::CSheet_PATI()
{
}

BEGIN_MESSAGE_MAP(CSheet_PATI, CPropertySheet)
	//{{AFX_MSG_MAP(CSheet_PATI)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;

HINSTANCE CSheet_PATI::SetResource()
{
	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMPat_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

BOOL CSheet_PATI::Create ()
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Create
	BOOL bOk;	
	/////////////////////////////////////////////// Sheet Header
	m_psh.hInstance		= extensionMPat_DLL.hModule; // Current Resource Instance 
	m_psh.hwndParent	= m_pWnd->GetSafeHwnd(); 
	/////////////////////////////////////////////// Page Header
	int nPages = GetPageCount();
	///
	for(int i=0;i<nPages;i++)
	{
		GetPage(i)->m_psp.hInstance	= extensionMPat_DLL.hModule; // Current Resource Instance 
		GetPage(i)->m_psp.dwFlags |= PSP_USETITLE; 
	}	
	/////////////////////////////////////////////// Create
	bOk = CPropertySheet::Create(m_pWnd,
					WS_POPUP | WS_CAPTION | DS_MODALFRAME/* | DS_CONTEXT_HELP*/,WS_EX_CONTEXTHELP);
	///////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////
	return bOk;
}

void CSheet_PATI::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
 
}

CSheet_PATI::~CSheet_PATI()
{
	delete m_pXtrudePage;
	delete m_pRevolvPage;
	delete m_pLoftPage;
	delete m_pDuctPage;
	delete m_pSweepPage;
	delete m_pCoonsPage;
	delete m_pTensorPage;
	delete m_pGordonPage;
	delete m_pEndCondPage;
}
/////////////////////////////////////////////////////////////////////////////
// CSheet_PATI message handlers

int CSheet_PATI::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/////////
	return 0;
}

int CSheet_PATI::SetProcPage() 
{
	///////////////////////////////////////////////////////
	int nCount = GetPageCount();
	//////////////////////////// Remove All First
	for(int i=nCount-1;i>=0;i--)
		RemovePage(i);
	//////////////////////////// Add
	switch(m_PatProc)
	{
		case PP_EXTRUDE:

			AddPage(m_pXtrudePage);
			m_pXtrudePage->m_psp.pszTitle = (LPCTSTR)("Extrusion Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pXtrudePage);
			SetTitle("Extrusion Patch Data");
			m_pXtrudePage->ResetDlg();
			//////
			break;

		case PP_ROTATE:

			AddPage(m_pRevolvPage);
			m_pRevolvPage->m_psp.pszTitle = (LPCTSTR)("Revolution Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pRevolvPage);
			SetTitle("Revolution Patch Data");
			m_pRevolvPage->ResetDlg();
			//////
			break;

		case PP_LOFT:
		case PP_LOFTX:

			AddPage(m_pLoftPage);
			m_pLoftPage->m_psp.pszTitle = (LPCTSTR)("Loft Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pLoftPage);
			SetTitle("Lofted Patch Data");
			m_pLoftPage->ResetDlg();
			//////
			break;

		case PP_DUCT:

			AddPage(m_pDuctPage);
			m_pDuctPage->m_psp.pszTitle = (LPCTSTR)("Duct Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pDuctPage);
			SetTitle("Ducted Patch Data");
			m_pDuctPage->ResetDlg();
			//////
			break;

		case PP_SWEEP:

			AddPage(m_pSweepPage);
			m_pSweepPage->m_psp.pszTitle = (LPCTSTR)("Sweep Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pSweepPage);
			SetTitle("Sweeping Patch Data");
			m_pSweepPage->ResetDlg();
			//////
			break;

		case PP_COONS:

			AddPage(m_pCoonsPage);
			m_pCoonsPage->m_psp.pszTitle = (LPCTSTR)("Coons Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pCoonsPage);
			SetTitle("Coons Patch Data");
			m_pCoonsPage->ResetDlg();
			//////
			break;

		case PP_TENSOR:

			if(IsEndCondMode() || m_pEndCondPage->m_bCornerMode)
			{
				AddPage(m_pEndCondPage);
				if(m_pEndCondPage->m_bCornerMode)
					m_pEndCondPage->m_psp.pszTitle = (LPCTSTR)("Twist");
				else
				if(m_pEndCondPage->m_bU)
					m_pEndCondPage->m_psp.pszTitle = (LPCTSTR)("End Conditions_U");
				else
					m_pEndCondPage->m_psp.pszTitle = (LPCTSTR)("End Conditions_V");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pEndCondPage);
				SetTitle("Bndry Conditions: Tensor Product Patch");
// Not Yet				m_pEndCondPage->ResetDlg();
			}
			else
			{
				AddPage(m_pTensorPage);
				m_pTensorPage->m_psp.pszTitle = (LPCTSTR)("Nodal Data");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pTensorPage);
				SetTitle("Tensor Product Patch Data");
				m_pTensorPage->ResetDlg();
			}
			//////
			break;

		case PP_GORDON:

			if(m_pEndCondPage->m_bCornerMode)
			{
				AddPage(m_pEndCondPage);
				m_pEndCondPage->m_psp.pszTitle = (LPCTSTR)("Twist");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pEndCondPage);
				SetTitle("Bndry Conditions: Gordon Patch");
			}
			else
			{

				AddPage(m_pGordonPage);
				m_pGordonPage->m_psp.pszTitle = (LPCTSTR)("Curve Data");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pGordonPage);
				SetTitle("Gordon Patch Data");
				m_pGordonPage->ResetDlg();
			}
			//////
			break;
				

		default:

			return MA_ERROR;
	}
	////////////////////////
	CRect BoxRect;
	CWnd  wndTopMost;
	GetWindowRect(&BoxRect);
	SizeRectDlgIn(BoxRect);
	//////////////////////////////////////////////////////////////
	SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
					BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
	//////////////////////////////////////////////////////////////
	SetActiveWindow();
	/////////
	return MA_OK;
}
	
void CSheet_PATI::SizeRectDlgIn(CRect& BoxRect)
{
	
//	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cyHScroll	= ::GetSystemMetrics(SM_CYHSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cxEdge		= ::GetSystemMetrics(SM_CXEDGE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	///////////////////////////////
	CRect clientRect;
	m_pWnd->GetClientRect(&clientRect);
	m_pWnd->ClientToScreen(&clientRect);
	////////////////
	CRect FrameRect;
	m_pWnd->GetWindowRect(&FrameRect);
	/////////////////////////////////////////////////////////////// ...InBox 
	int Boxwidth  		= BoxRect.Width();
	int Boxheight 		= BoxRect.Height();
	/////////////////////////////////////// 
	BoxRect.bottom	= FrameRect.bottom	- cyHScroll- cyEdge; //
	BoxRect.top		= BoxRect.bottom - Boxheight; //
	BoxRect.left	= clientRect.left + (clientRect.Width() - Boxwidth)/2;  
	BoxRect.right	= BoxRect.left + Boxwidth;
	////////////////////////////////
	return;
}
////////////////////////////////// end of module //////////////////////
