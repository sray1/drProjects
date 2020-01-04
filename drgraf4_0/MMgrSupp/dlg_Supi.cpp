// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "MSupDll.h"
#include "UserMsg.h"
//#include "Def_Lims.h"
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
/////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"

#include "Dlg_Stif.h"
//////////////////////
#include "Dlg_SupI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SupI dialog


CDlg_SupI::CDlg_SupI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_SupI)
	m_bRx		= FALSE;
	m_bRy		= FALSE;
	m_bRz		= FALSE;
	m_bTx		= FALSE;
	m_bTy		= FALSE;
	m_bTz		= FALSE;
	m_SupID		= _T("");
	m_bTxG		= FALSE;
	m_bTyG		= FALSE;
	m_bTzG		= FALSE;
	m_bRxG		= FALSE;
	m_bRyG		= FALSE;
	m_bRzG		= FALSE;
	//}}AFX_DATA_INIT
	m_pWnd 		= pWnd;
	m_SuppProc	= SUP_RIGID;
}


void CDlg_SupI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SupI)
	DDX_Check(pDX, IDC_RX, m_bRx);
	DDX_Check(pDX, IDC_RY, m_bRy);
	DDX_Check(pDX, IDC_RZ, m_bRz);
	DDX_Check(pDX, IDC_TX, m_bTx);
	DDX_Check(pDX, IDC_TY, m_bTy);
	DDX_Check(pDX, IDC_TZ, m_bTz);
	DDX_CBString(pDX, IDC_SUPID, m_SupID);
	DDX_Check(pDX, IDC_GX, m_bTxG);
	DDX_Check(pDX, IDC_GY, m_bTyG);
	DDX_Check(pDX, IDC_GZ, m_bTzG);
	DDX_Check(pDX, IDC_GRX, m_bRxG);
	DDX_Check(pDX, IDC_GRY, m_bRyG);
	DDX_Check(pDX, IDC_GRZ, m_bRzG);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SupI, CDialog)
	//{{AFX_MSG_MAP(CDlg_SupI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_SUPID, OnSelchangeSupid)
	ON_BN_CLICKED(IDC_STIFFNESS, OnStiffness)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_STIFFNESS, OnStiffness)
	ON_CBN_SELCHANGE(IDC_COMBO_JCTYPE, OnSelchangeJctype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSup_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_SupI message handlers

BOOL CDlg_SupI::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////////////////// Fill Up Sup
	if(m_SuppProc == SUP_RIGID)
	{

		m_bRx	= TRUE;
		m_bRy	= TRUE;
		m_bRz	= TRUE;
		m_bTx	= TRUE;
		m_bTy	= TRUE;
		m_bTz	= TRUE;
		////////////////////////////////////////
		GetDlgItem(IDC_TX)->EnableWindow(FALSE);	
		GetDlgItem(IDC_TY)->EnableWindow(FALSE);	
		GetDlgItem(IDC_TZ)->EnableWindow(FALSE);	
		GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
		GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
		GetDlgItem(IDC_RZ)->EnableWindow(FALSE);
		GetDlgItem(IDC_GX)->EnableWindow(FALSE);	
		GetDlgItem(IDC_GY)->EnableWindow(FALSE);	
		GetDlgItem(IDC_GZ)->EnableWindow(FALSE);	
		GetDlgItem(IDC_GRX)->EnableWindow(FALSE);	
		GetDlgItem(IDC_GRY)->EnableWindow(FALSE);	
		GetDlgItem(IDC_GRZ)->EnableWindow(FALSE);
	}
	//////////////////////////////////////////// Joint Type
	CWnd* pWndCtrl = GetDlgItem(IDC_COMBO_JCTYPE);
   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	m_jcType = JC_DEFAULT;
	///////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_SupI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMSup_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_SupI::IDD);
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

void CDlg_SupI::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SUPIN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_SupI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SUPIN,IDC_UPDATE);
}

void CDlg_SupI::OnSelchangeSupid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	// TODO: Add your control notification handler code here
	
}

void CDlg_SupI::OnStiffness() 
{
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Stif Dlg;
	////////////////////////
	for(int i=0;i<6;i++)
		Dlg.dValu[i]= m_dStif[i];
	/////////////////////////// Kode
	BOOL bKode[6];
	bKode[0] = m_bTx;
	bKode[1] = m_bTy;
	bKode[2] = m_bTz;
	bKode[3] = m_bRx;
	bKode[4] = m_bRy;
	bKode[5] = m_bRz;
	///////////////////////////
	Dlg.bKode		= bKode;
	Dlg.m_SuppProc	= m_SuppProc;
	////////////////////////
	int nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update
	if(nStatus == IDOK)
	{
		for(int i=0;i<6;i++)
			m_dStif[i] = Dlg.dValu[i];
	}
	//////////////////////////////////
}

void CDlg_SupI::OnSelchangeJctype() 
{
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(IDC_COMBO_JCTYPE);
   	int index = ((CComboBox*)pWndCtrl)->GetCurSel();
	if(index<0)
		return;
	//////////////
	switch(index)
	{
		case 1:
			m_jcType =	JC_X_FIXEDDIR;	//	JC_X_FIXEDDIR
			break;
		case 2:
			m_jcType =	JC_X_TAN_CURVE;	//	JC_X_TAN_CURVE
			break;
		case 3:
			m_jcType =	JC_I_TAN_PATCH;	//	JC_I_TAN_PATCH
			break;
		case 4:
			m_jcType =	JC_Z_NOR_PATCH;	//	JC_Z_NOR_PATCH
			break;
		case 0:
		default:
			m_jcType =	JC_DEFAULT;		//	JC_DEFAULT,
			break;
	}
	////////
}
/////////////////////////// end of module //////////////
