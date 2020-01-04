// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"

#include "MNodDll.h"
#include "UserMsg.h"
/////////////////////
#include "CommRsrc.h"
#include "Dlg_Node.h"
#include "Dlg_NodI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_NodI dialog


CDlg_NodI::CDlg_NodI(CWnd* pWnd,BOOL bAdv)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_NodI)
	m_ObjID			= _T("");
	m_X				= 0.0;
	m_Y				= 0.0;
	m_Z				= 0.0;
	m_NID			= _T("");
	m_bDirect		= FALSE;
	m_bDirection	= FALSE;
	m_bDominant		= FALSE;
	m_bIncrement	= TRUE;
	m_bMultiple		= FALSE;
	//}}AFX_DATA_INIT
	m_pWnd 			= pWnd;
	m_bAdvanced		= bAdv;
}


void CDlg_NodI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_NodI)
	DDX_Text(pDX, IDC_OBJID, m_ObjID);
	DDX_Text(pDX, IDC_ROT_X, m_X);
	DDX_Text(pDX, IDC_ROT_Y, m_Y);
	DDX_Text(pDX, IDC_ROT_Z, m_Z);
	DDX_Text(pDX, IDC_TRANPT, m_NID);
	DDX_Check(pDX, IDC_DIRECT, m_bDirect);
	DDX_Check(pDX, IDC_DIRECTION, m_bDirection);
	DDX_Check(pDX, IDC_DOMINANT, m_bDominant);
	DDX_Check(pDX, IDC_INCREMENT, m_bIncrement);
	DDX_Check(pDX, IDC_MULTIPLE, m_bMultiple);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_NodI, CDialog)
	//{{AFX_MSG_MAP(CDlg_NodI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_WM_HELPINFO()
	ON_EN_CHANGE(IDC_OBJID, OnChangeObjID)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_CLICKED(IDC_DIRECTION, OnDirection)
	ON_BN_CLICKED(IDC_DIRECT, OnDirect)
	ON_BN_CLICKED(IDC_DOMINANT, OnDominant)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_DOUBLECLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_DOUBLECLICKED(IDC_DIRECT, OnDirect)
	ON_BN_DOUBLECLICKED(IDC_DIRECTION, OnDirection)
	ON_BN_DOUBLECLICKED(IDC_DOMINANT, OnDominant)
	ON_BN_CLICKED(IDC_MULTIPLE, OnMultiple)
	ON_BN_DOUBLECLICKED(IDC_MULTIPLE, OnMultiple)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMNod_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_NodI message handlers

BOOL CDlg_NodI::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_NodI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMNod_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	///////////////////////////////////////////////////////////// 
	bOk = CDialog::Create(CDlg_NodI::IDD);
	///////////////////////////////////////
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
	//////////////////
	return bOk;
}

void CDlg_NodI::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_NODIN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_NodI::OnUpdate() 
{
	UpdateData(TRUE);
	/////////////////
	m_dCoord = m_Z;
	///////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_UPDATE);
}


BOOL CDlg_NodI::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
/*
	BOOL WinHelp(
  

    HWND  hWndMain,	// handle of window requesting Help 
    LPCTSTR  lpszHelp,	// address of directory-path string 
    UINT  uCommand,	// type of Help 
    DWORD  dwData 	// additional data 
   );
*/ 

	AfxGetApp()->WinHelp(pHelpInfo->dwContextId,HELP_CONTEXTPOPUP);
	return TRUE;

//	return CDialog::OnHelpInfo(pHelpInfo);
}

void CDlg_NodI::OnIncrement()
{
	UpdateData(TRUE);
	/////////////////
	if(m_bIncrement)
		m_bDirection	= FALSE;
	else
		m_bDirection	= TRUE;
	///////////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_INCREMENT);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}


void CDlg_NodI::OnDirect() 
{
	UpdateData(TRUE);
	/////////////////
	if(!m_bDirect)
	{
		m_bDominant = FALSE;
		GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOMINANT)->SetWindowText("");
		((CButton*)GetDlgItem(IDC_DOMINANT))->SetCheck(FALSE);
	}
	else
	{
//		m_bDominant = FALSE;
		GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
		GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
//		((CButton*)GetDlgItem(IDC_DOMINANT))->SetCheck(FALSE);
	}
	///////////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_DIRECT);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_NodI::OnDirection() 
{
	UpdateData(TRUE);
	/////////////////
	if(m_bDirection)
		m_bIncrement = FALSE;
	else
		m_bIncrement = TRUE;
	///////////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_DIRECTION);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_NodI::OnDominant() 
{
	UpdateData(TRUE);
	/////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_DOMINANT);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_NodI::OnMultiple() 
{
	UpdateData(TRUE);
	/////////////////
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////
	CDlg_Node	Nodedlg;
	////////////////////
	Nodedlg.m_id				= m_NID;
	Nodedlg.m_nActiveViewNumber	= m_nViewNum;
	Nodedlg.m_bnid_c			= m_bnid_C;
	////////////////////////////////////////
	// m_nHowMany == -9999 -> Dialog-Induced
	////////////////////////////////////////
	Nodedlg.m_nHowMany			= -9999;		
	/////////////////////////////////////// Now Open Dialog/draw
	UINT nStatus = Nodedlg.DoModal(); 
	if(nStatus == IDOK)
	{
		/////////////////////////////////////// update
		m_MouseWIC.x	= Nodedlg.m_MouseWIC.x;
		m_MouseWIC.y	= Nodedlg.m_MouseWIC.y;
		m_MouseWIC.z	= Nodedlg.m_MouseWIC.z;
		//////////////////////////////////
		m_NID			= Nodedlg.m_CurrentNodeID;
		/////////////////
//		if(m_pWnd !=NULL)
//			m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_ADVANCED);
		/////////////////
	}
	///
	char	buf[50];
	int		nLastNum;
	///
	if(m_bnid_C)
	{
		pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	    nLastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_ObjID	= "CN_";
		m_ObjID	+= buf;
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    nLastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_ObjID	= "";
		m_ObjID	+= buf;
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_NodI::OnAdvanced() 
{
	UpdateData(TRUE);
	/////////////////
	m_bAdvanced = !m_bAdvanced;
	///
	if(m_bAdvanced)
	{
		GetDlgItem(IDC_DIRECT)->SetWindowText("Direct");
		GetDlgItem(IDC_DIRECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
		GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
		GetDlgItem(IDC_INCREMENT)->SetWindowText("Coords");
		GetDlgItem(IDC_INCREMENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_DIRECTION)->SetWindowText("Direction");
		GetDlgItem(IDC_DIRECTION)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DIRECT)->SetWindowText("");
		GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOMINANT)->SetWindowText("");
		GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_INCREMENT)->SetWindowText("");
		GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DIRECTION)->SetWindowText("");
		GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
	}
	///////////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_ADVANCED);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_NodI::OnChangeObjID() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_NODIN,IDC_OBJID);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}
/////////////////////////// end of module //////////////
