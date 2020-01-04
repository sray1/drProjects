// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
#include "MStLDll.h"
#include "Def_Objs.h"
#include "UserMsg.h"
#include "CommRsrc.h"

#include "dlg_F_Mi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_F_MI dialog


CDlg_F_MI::CDlg_F_MI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_F_MI)
	m_dMx		= 0.0;
	m_dMy		= 0.0;
	m_dMz		= 0.0;
	m_dFx		= 0.0;
	m_dFy		= 0.0;
	m_dFz		= 0.0;
	m_LoadID	= _T("");
	m_bIsoPar	= FALSE;
	m_bAdvanced = FALSE;
	//}}AFX_DATA_INIT
	m_pWnd 		= pWnd;


}


void CDlg_F_MI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_F_MI)
	DDX_Text(pDX, IDC_MX, m_dMx);
	DDX_Text(pDX, IDC_MY, m_dMy);
	DDX_Text(pDX, IDC_MZ, m_dMz);
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_Text(pDX, IDC_FY, m_dFy);
	DDX_Text(pDX, IDC_FZ, m_dFz);
	DDX_CBString(pDX, IDC_LOADID, m_LoadID);
	DDX_Check(pDX, IDC_ISOPAR, m_bIsoPar);
	DDX_Check(pDX, IDC_ADVANCED, m_bAdvanced);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_F_MI, CDialog)
	//{{AFX_MSG_MAP(CDlg_F_MI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_LOADID, OnSelchangeLoadid)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_DOUBLECLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_F_MI message handlers

BOOL CDlg_F_MI::OnInitDialog()
{
	CDialog::OnInitDialog();
	///////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_F_MI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMStL_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_F_MI::IDD);
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


void CDlg_F_MI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd ==NULL)
		return;
	/////////////////
	switch(m_Category)
	{
		case CA_FORCE:
			m_pWnd->SendMessage(ID_UPDATE_FANDMIN,IDC_UPDATE);
			break;
		case CA_DISPLACE:
			m_pWnd->SendMessage(ID_UPDATE_DANDRIN,IDC_UPDATE);
			break;
		case CA_THERMAL:
			m_pWnd->SendMessage(ID_UPDATE_THERMIN,IDC_UPDATE);
			break;
		case CA_PRESSURE:
			m_pWnd->SendMessage(ID_UPDATE_PRESSIN,IDC_UPDATE);
			break;
		case CA_LUMPWT:
			m_pWnd->SendMessage(ID_UPDATE_LUMPWTIN,IDC_UPDATE);
			break;
		default:
			break;
	}
}	

void CDlg_F_MI::OnSelchangeLoadid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	// TODO: Add your control notification handler code here
	
}

void CDlg_F_MI::OnCancel() 
{
	/////////////////
	if(m_pWnd ==NULL)
		return;
	/////////////////
	switch(m_Category)
	{
		case CA_FORCE:
			m_pWnd->SendMessage(ID_CANCEL_FANDMIN,IDD_CANCEL);
			break;
		case CA_DISPLACE:
			m_pWnd->SendMessage(ID_CANCEL_DANDRIN,IDD_CANCEL);
			break;
		case CA_THERMAL:
			m_pWnd->SendMessage(ID_CANCEL_THERMIN,IDD_CANCEL);
			break;
		case CA_PRESSURE:
			m_pWnd->SendMessage(ID_CANCEL_PRESSIN,IDD_CANCEL);
			break;
		case CA_LUMPWT:
			m_pWnd->SendMessage(ID_CANCEL_LUMPWTIN,IDD_CANCEL);
			break;
		default:
			break;
	}
}
/////////////////////////// end of module //////////////
