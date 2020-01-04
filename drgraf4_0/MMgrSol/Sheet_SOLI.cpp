// dlg_PatI.cpp : implementation file
//

#include "stdafx.h"

#include "Def_MouseAct.h"
//////////////////////////
/*
#include "Dlg_SI_EndCond.h"
#include "Dlg_SI_Xtrude.h"
#include "Dlg_SI_Revolv.h"
#include "Dlg_SI_Loft.h"
#include "Dlg_SI_Duct.h"
#include "Dlg_SI_Sweep.h"
#include "Dlg_SI_Coons.h"
#include "Dlg_SI_Tensor.h"
#include "Dlg_SI_Gordon.h"
//#include "Dlg_PatI.h"
*/
///////////////////////
#include "CommRsrc.h"
////////////////////
#include "Sheet_SOLI.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSheet_SOLI,CPropertySheet)
/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CSheet_SOLI dialog


CSheet_SOLI::CSheet_SOLI(UINT nIDCaption,CWnd* pParentWnd,SOLIDPROC SolProc,UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	/////////////////
	ConstructPages(pParentWnd);
	////////////////////////////
	m_pWnd 		= pParentWnd;
	m_SolProc	= SolProc;
}

CSheet_SOLI::CSheet_SOLI(LPCTSTR pszCaption, CWnd* pParentWnd,SOLIDPROC SolProc ,UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	/////////////////
	ConstructPages(pParentWnd);
	////////////////////////////
	m_pWnd 		= pParentWnd;
	m_SolProc	= SolProc;
}

void CSheet_SOLI::ConstructPages(CWnd* pParentWnd)
{
	m_pXtrudePage	= new CDlg_SI_Xtrude(pParentWnd/*Actually MainWnd*/,SP_EXTRUDE);
	m_pRevolvPage	= new CDlg_SI_Revolv(pParentWnd/*Actually MainWnd*/,SP_ROTATE);
	m_pLoftPage		= new CDlg_SI_Loft(pParentWnd/*Actually MainWnd*/,SP_LOFT);
	m_pDuctPage		= new CDlg_SI_Duct(pParentWnd/*Actually MainWnd*/,SP_DUCT);
	m_pSweepPage	= new CDlg_SI_Sweep(pParentWnd/*Actually MainWnd*/,SP_SWEEP);
	m_pCoonsPage	= new CDlg_SI_Coons(pParentWnd/*Actually MainWnd*/,SP_COONS);
	m_pTensorPage	= new CDlg_SI_Tensor(pParentWnd/*Actually MainWnd*/,SP_TENSOR);
	m_pGordonPage	= new CDlg_SI_Gordon(pParentWnd/*Actually MainWnd*/,SP_GORDON);
	m_pEndCondPage	= new CDlg_SI_EndCond(pParentWnd/*Actually MainWnd*/,SP_TENSOR);
}

CSheet_SOLI::CSheet_SOLI()
{
}

BEGIN_MESSAGE_MAP(CSheet_SOLI, CPropertySheet)
	//{{AFX_MSG_MAP(CSheet_SOLI)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;

HINSTANCE CSheet_SOLI::SetResource()
{
	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMSol_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

BOOL CSheet_SOLI::Create ()
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Create
	BOOL bOk;	
	/////////////////////////////////////////////// Sheet Header
	m_psh.hInstance		= extensionMSol_DLL.hModule; // Current Resource Instance 
	m_psh.hwndParent	= m_pWnd->GetSafeHwnd(); 
	/////////////////////////////////////////////// Page Header
	int nPages = GetPageCount();
	///
	for(int i=0;i<nPages;i++)
	{
		GetPage(i)->m_psp.hInstance	= extensionMSol_DLL.hModule; // Current Resource Instance 
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

void CSheet_SOLI::RestoreResource(HINSTANCE hInstResourceClient)
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

CSheet_SOLI::~CSheet_SOLI()
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
// CSheet_SOLI message handlers

int CSheet_SOLI::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/////////
	return 0;
}

int CSheet_SOLI::SetProcPage() 
{
	///////////////////////////////////////////////////////
	int nCount = GetPageCount();
	//////////////////////////// Remove All First
	for(int i=nCount-1;i>=0;i--)
		RemovePage(i);
	//////////////////////////// Add
	switch(m_SolProc)
	{
		case SP_EXTRUDE:

			AddPage(m_pXtrudePage);
			m_pXtrudePage->m_psp.pszTitle = (LPCTSTR)("Extrusion Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pXtrudePage);
			SetTitle("Extrusion Solid Data");
			m_pXtrudePage->ResetDlg();
			//////
			break;

		case SP_ROTATE:

			AddPage(m_pRevolvPage);
			m_pRevolvPage->m_psp.pszTitle = (LPCTSTR)("Revolution Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pRevolvPage);
			SetTitle("Revolution Solid Data");
			m_pRevolvPage->ResetDlg();
			//////
			break;

		case SP_LOFT:
		case SP_LOFTX:

			AddPage(m_pLoftPage);
			m_pLoftPage->m_psp.pszTitle = (LPCTSTR)("Loft Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pLoftPage);
			SetTitle("Lofted Solid Data");
			m_pLoftPage->ResetDlg();
			//////
			break;

		case SP_DUCT:

			AddPage(m_pDuctPage);
			m_pDuctPage->m_psp.pszTitle = (LPCTSTR)("Duct Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pDuctPage);
			SetTitle("Ducted Solid Data");
			m_pDuctPage->ResetDlg();
			//////
			break;

		case SP_SWEEP:

			AddPage(m_pSweepPage);
			m_pSweepPage->m_psp.pszTitle = (LPCTSTR)("Sweep Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pSweepPage);
			SetTitle("Sweeping Solid Data");
			m_pSweepPage->ResetDlg();
			//////
			break;

		case SP_COONS:

			AddPage(m_pCoonsPage);
			m_pCoonsPage->m_psp.pszTitle = (LPCTSTR)("Coons Data");
			////////////////////////
			Create();
			ShowWindow(FALSE);
			/////////
			SetActivePage(m_pCoonsPage);
			SetTitle("Coons Solid Data");
			m_pCoonsPage->ResetDlg();
			//////
			break;

		case SP_TENSOR:

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
				SetTitle("Bndry Conditions: Tensor Product Solid");
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
				SetTitle("Tensor Product Solid Data");
				m_pTensorPage->ResetDlg();
			}
			//////
			break;

		case SP_GORDON:

			if(m_pEndCondPage->m_bCornerMode)
			{
				AddPage(m_pEndCondPage);
				m_pEndCondPage->m_psp.pszTitle = (LPCTSTR)("Twist");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pEndCondPage);
				SetTitle("Bndry Conditions: Gordon Solid");
			}
			else
			{

				AddPage(m_pGordonPage);
				m_pGordonPage->m_psp.pszTitle = (LPCTSTR)("Patch Data");
				////////////////////////
				Create();
				ShowWindow(FALSE);
				/////////
				SetActivePage(m_pGordonPage);
				SetTitle("Gordon Solid Data");
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
	
void CSheet_SOLI::SizeRectDlgIn(CRect& BoxRect)
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
