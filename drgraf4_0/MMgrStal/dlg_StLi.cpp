// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "MStLDll.h"
#include "UserMsg.h"
//#include "Def_Lims.h"
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
/////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MSupRsrc.h"

#include "dlg_Uniform.h"
#include "dlg_StLC.h"
#include "Dlg_StLI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_StLI dialog


CDlg_StLI::CDlg_StLI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_StLI)
	m_LoadID	= _T("");
	m_bTx		= FALSE;
	m_bTy		= FALSE;
	m_bTz		= FALSE;
	m_bRx		= FALSE;
	m_bRy		= FALSE;
	m_bRz		= FALSE;
	m_bUniform	= FALSE;
	//}}AFX_DATA_INIT
	m_pWnd 		= pWnd;
	m_StaLProc	= STL_FORCE;
	m_bConOrDis	= TRUE;
	m_bIso		= FALSE;
	m_bNonIso	= FALSE;
}


void CDlg_StLI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_StLI)
	DDX_CBString(pDX, IDC_LOADID, m_LoadID);
	DDX_Check(pDX, IDC_TX, m_bTx);
	DDX_Check(pDX, IDC_TY, m_bTy);
	DDX_Check(pDX, IDC_TZ, m_bTz);
	DDX_Check(pDX, IDC_RX, m_bRx);
	DDX_Check(pDX, IDC_RY, m_bRy);
	DDX_Check(pDX, IDC_RZ, m_bRz);
	DDX_Check(pDX, IDC_UNIFORM, m_bUniform);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_StLI, CDialog)
	//{{AFX_MSG_MAP(CDlg_StLI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_LOADID, OnSelchangeLoadid)
	ON_BN_CLICKED(IDC_NONISO, OnNonIso)
	ON_BN_CLICKED(IDC_ISOPAR_CONC, OnIsoparConc)
	ON_BN_CLICKED(IDC_ISOPAR_DISTRIB, OnIsoparDistrib)
	ON_CBN_SELCHANGE(IDC_COMBO_JCTYPE, OnSelchangeComboJctype)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_NONISO, OnNonIso)
	ON_BN_DOUBLECLICKED(IDC_ISOPAR_CONC, OnIsoparConc)
	ON_BN_DOUBLECLICKED(IDC_ISOPAR_DISTRIB, OnIsoparDistrib)
	ON_BN_CLICKED(IDC_UNIFORM, OnUniform)
	ON_BN_DOUBLECLICKED(IDC_UNIFORM, OnUniform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_StLI message handlers

BOOL CDlg_StLI::OnInitDialog()
{
	CDialog::OnInitDialog();
	//////////////////////////////////////////// 
	m_bNonIso		= FALSE;
	((CButton*)GetDlgItem(IDC_NONISO))->SetCheck(FALSE);	// for Now	todo
	GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
	/////////////////
	if(m_bUniform)
	{
		/////////////////////////////
		GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
	}
	else
	{
		/////////////////////////////
		GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(TRUE);
		GetDlgItem(IDC_NONISO)->EnableWindow(TRUE);
	}
	//////////////////////////////////////////// Joint Type
	m_jcType = JC_DEFAULT;
	CWnd* pWndCtrl = GetDlgItem(IDC_COMBO_JCTYPE);
   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	///////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_StLI::Create ()
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
	bOk = CDialog::Create(CDlg_StLI::IDD);
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

void CDlg_StLI::OnCancel() 
{
	/////////////////
	if(m_pWnd ==NULL)
		return;
	/////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:
			m_pWnd->SendMessage(ID_CANCEL_FANDMIN,IDD_CANCEL);
			break;
		case STL_DISPLACE:
			m_pWnd->SendMessage(ID_CANCEL_DANDRIN,IDD_CANCEL);
			break;
		case STL_THERMAL:
			m_pWnd->SendMessage(ID_CANCEL_THERMIN,IDD_CANCEL);
			break;
		case STL_PRESSURE:
			m_pWnd->SendMessage(ID_CANCEL_PRESSIN,IDD_CANCEL);
			break;
		case STL_LUMPWT:
			m_pWnd->SendMessage(ID_CANCEL_LUMPWTIN,IDD_CANCEL);
			break;
		default:
			break;
	}
}

void CDlg_StLI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd ==NULL)
		return;
	/////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:
			m_pWnd->SendMessage(ID_UPDATE_FANDMIN,IDC_UPDATE);
			break;
		case STL_DISPLACE:
			m_pWnd->SendMessage(ID_UPDATE_DANDRIN,IDC_UPDATE);
			break;
		case STL_THERMAL:
			m_pWnd->SendMessage(ID_UPDATE_THERMIN,IDC_UPDATE);
			break;
		case STL_PRESSURE:
			m_pWnd->SendMessage(ID_UPDATE_PRESSIN,IDC_UPDATE);
			break;
		case STL_LUMPWT:
			m_pWnd->SendMessage(ID_UPDATE_LUMPWTIN,IDC_UPDATE);
			break;
		default:
			break;
	}
}

void CDlg_StLI::OnSelchangeLoadid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
}

void CDlg_StLI::Get_Values_Uniform() 
{
	m_bUniform		= TRUE;
	////////////
	OnUniform();
}

void CDlg_StLI::OnUniform() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bUniform)
	{
		m_bIso = FALSE;
		m_bNonIso = FALSE;
		/////////////////////////////
		GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
	}
	else
	{
		/////////////////////////////
		GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(TRUE);
		GetDlgItem(IDC_NONISO)->EnableWindow(TRUE);
		//////////////////////////////////
		return;
	}
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Uniform Dlg;
	////////////////////////
	for(int i=0;i<6;i++)
		Dlg.m_dValu[i]= m_dUnif[i];
	/////////////////////////// Kode
	BOOL bKode[6];
	bKode[0] = m_bTx;
	bKode[1] = m_bTy;
	bKode[2] = m_bTz;
	bKode[3] = m_bRx;
	bKode[4] = m_bRy;
	bKode[5] = m_bRz;
	///////////////////////////
	Dlg.m_bKode		= bKode;
	Dlg.m_StaLProc	= m_StaLProc;
	Dlg.m_GenKind	= m_GenKind;
	////////////////////////
	int nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update
	if(nStatus == IDOK)
	{
		for(int i=0;i<6;i++)
			m_dUnif[i] = Dlg.m_dValu[i];
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_StLI::OnSelchangeComboJctype() 
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
			m_jcType =	JC_Z_NOR_PATCH;	//	JC_Z_NOR_PATCH
			break;
		case 0:
		default:
			m_jcType =	JC_DEFAULT;		//	JC_DEFAULT,
			break;
	}
	////////
}

void CDlg_StLI::OnIsoparConc() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	m_bConOrDis		= TRUE;
	m_bIso			= TRUE;
	//
	m_bNonIso		= FALSE;
	//////////////////
}

void CDlg_StLI::OnIsoparDistrib() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	m_bConOrDis		= FALSE;
	m_bIso			= TRUE;
	//
	m_bNonIso		= FALSE;
	//////////////////
}

void CDlg_StLI::OnNonIso() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	m_bNonIso		= TRUE;
	m_bIso			= FALSE;
	//
	m_bUniform		= FALSE;
	GetDlgItem(IDC_UNIFORM)->EnableWindow(TRUE);
	//////////////////
	m_bConOrDis		= FALSE;
	////////////////////
	if(m_GenKind == CURVE)
	{
		CDlg_StLC	dlg;
		////////////////////
		dlg.m_CID			= m_CID;
		dlg.m_bIncrement	= m_bIncrement;
		dlg.m_Orient		= m_Orient;
		dlg.m_dScale		= m_dScale;
		dlg.m_dStep			= m_dStep;
		dlg.m_dStart		= m_dStart;
		dlg.m_pDrCurve		= m_pDrCurve;	// Base Curve for which StaticLoad is needed
		dlg.m_Category		= m_Category;	// Force/Moment/Disp/Rot/Pres/Therm/LupWt etc
		/////////////////////////////////////// Now Open Dialog/draw
		UINT nStatus = dlg.DoModal(); 
		if(nStatus == IDOK)
		{
			/////////////////////////////////////// update
			m_CID			= dlg.m_CID;
			m_bIncrement	= dlg.m_bIncrement;
			m_Orient		= dlg.m_Orient;
			m_dScale		= dlg.m_dScale;
			m_dStep			= dlg.m_dStep;
			m_dStart		= dlg.m_dStart;
		}
	}
	else
	if(m_GenKind == PATCH)
	{
//		dlg.m_pDrPatch		= m_pDrPatch;	// Base Patch for which StaticLoad is needed
		;
	}
}
/////////////////////////// end of module //////////////
