// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
#include "MSupDll.h"
#include "UserMsg.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
///////////////////// 
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"

#include "Dlg_SupE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlg_SupE dialog

CDlg_SupE::CDlg_SupE(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SupE::IDD, pParent)
{
}

CDlg_SupE::CDlg_SupE(CDrLinSup* pDrLinSup,CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SupE::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_SupE)
	m_SupID = _T("");
	m_strProc = _T("");
	//}}AFX_DATA_INIT
	////////////////////////
	m_pDrLinSup	= pDrLinSup;
}

void CDlg_SupE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SupE)
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_Text(pDX, IDC_FY, m_dFy);
	DDX_Text(pDX, IDC_FZ, m_dFz);
	DDX_Text(pDX, IDC_MX, m_dMx);
	DDX_Text(pDX, IDC_MY, m_dMy);
	DDX_Text(pDX, IDC_MZ, m_dMz);
	DDX_Check(pDX, IDC_RX, m_bRx);
	DDX_Check(pDX, IDC_RY, m_bRy);
	DDX_Check(pDX, IDC_RZ, m_bRz);
	DDX_Check(pDX, IDC_TX, m_bTx);
	DDX_Check(pDX, IDC_TY, m_bTy);
	DDX_Check(pDX, IDC_TZ, m_bTz);
	DDX_Check(pDX, IDC_RX2, m_bRxG);
	DDX_Check(pDX, IDC_RY2, m_bRyG);
	DDX_Check(pDX, IDC_RZ2, m_bRzG);
	DDX_Check(pDX, IDC_TX2, m_bTxG);
	DDX_Check(pDX, IDC_TY2, m_bTyG);
	DDX_Check(pDX, IDC_TZ2, m_bTzG);
	DDX_CBString(pDX, IDC_NID, m_aNid);
	DDX_CBString(pDX, IDC_NIDB2, m_bNid);
	DDX_Check(pDX, IDC_TANGENT, m_bTan);
	DDX_Text(pDX, IDC_SUPID, m_SupID);
	DDX_Text(pDX, IDC_SUPPROC, m_strProc);
	DDX_Check(pDX, IDC_CN_A, m_bCN_a);
	DDX_Check(pDX, IDC_CN_B, m_bCN_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SupE, CDialog)
	//{{AFX_MSG_MAP(CDlg_SupE)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_TANGENT, OnTangent)
	ON_BN_CLICKED(IDC_CN_B, OnCnB)
	ON_BN_CLICKED(IDC_CN_A, OnCnA)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_TANGENT, OnTangent)
	ON_BN_DOUBLECLICKED(IDC_CN_B, OnCnB)
	ON_BN_DOUBLECLICKED(IDC_CN_A, OnCnA)
	ON_CBN_SELCHANGE(IDC_NIDB2, OnSelchangeNidb2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSup_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_SupE message handlers

BOOL CDlg_SupE::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////// Init Data
	Init();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	FillListAllNodeIDs_A();   //  with Nodes
	FillListAllNodeIDs_B();   //  with Nodes
	///////////////////////////////////////////// cannot be changed
	GetDlgItem(IDC_SUPPROC)->EnableWindow(FALSE);
	/////////////////////////////////////////////
	if(!m_bSkewed)
		GetDlgItem(IDC_NID)->EnableWindow(FALSE);
	///
	if(m_bTanHide)
	{
		m_bTan = FALSE;
		GetDlgItem(IDC_TANGENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TANGENT)->SetWindowText("");
	}
	if(m_bIdBHide)
	{
		m_bNid = "";
		GetDlgItem(IDC_NIDB2)->EnableWindow(FALSE);
		GetDlgItem(IDC_NIDHEADB)->SetWindowText("");
		GetDlgItem(IDC_CN_B)->EnableWindow(FALSE);
		GetDlgItem(IDC_CN_B)->SetWindowText("");
	}
	/////////////////////////////////////////// Tangent or Normal
	GetDlgItem(IDC_TANGENT)->SetWindowText("Tangential");
	GetDlgItem(IDC_SKEWHEAD)->SetWindowText("Skew Joint X");
	if(m_bPat)	// Patch
	{
		GetDlgItem(IDC_TANGENT)->SetWindowText("Normal");
		GetDlgItem(IDC_SKEWHEAD)->SetWindowText("Skew Joint Z");
	}
	////////////////////////////////////// Fill Up Sup that are active
	if(m_bRx)
		GetDlgItem(IDC_RX2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_RX2)->EnableWindow(FALSE);
	if(m_bRy)
		GetDlgItem(IDC_RY2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_RY2)->EnableWindow(FALSE);
	if(m_bRz)
		GetDlgItem(IDC_RZ2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_RZ2)->EnableWindow(FALSE);
	////
	if(m_bTx)
		GetDlgItem(IDC_TX2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_TX2)->EnableWindow(FALSE);
	if(m_bTy)
		GetDlgItem(IDC_TY2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_TY2)->EnableWindow(FALSE);
	if(m_bTz)
		GetDlgItem(IDC_TZ2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_TZ2)->EnableWindow(FALSE);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_SupE::Init()
{
	//////////////////////////////////////////////////////////////////////////////////////////
	//				DO NOT CHANGE FOLLOWING ORDER without Changing enum SUPPPROC in Def_Supp.h
	static CString Proc[] 	= {	"Rigid","Lin. Spring","Lin. Snubber","NonLinear Spring",
								"NonLinear Snubber"};
	/////////////////////////////////////////////////////////////////////////////
	m_SupBased	= m_pDrLinSup->GetCreateBase();
	///////////////////////////////////////////
	m_bPat		= FALSE;
	if(m_SupBased == PATCH)
		m_bPat = TRUE;
	/////////////////////////
	m_bTanHide		= FALSE;
	m_bIdBHide		= FALSE;
	if(m_SupBased == NODE)
	{
		m_bTanHide		= TRUE;
		m_bIdBHide		= TRUE;
	}
	////////////////////////////////////////////////////
	SUPPCARD	supCard = *(m_pDrLinSup->GetSuppCard());
	///////////////////
	m_bTx		= supCard.kode[0];
	m_bTy		= supCard.kode[1];
	m_bTz		= supCard.kode[2];
	m_bRx		= supCard.kode[3];
	m_bRy		= supCard.kode[4];
	m_bRz		= supCard.kode[5];
	//
	m_bTxG		= supCard.pgap[0];
	m_bTyG		= supCard.pgap[1];
	m_bTzG		= supCard.pgap[2];
	m_bRxG		= supCard.pgap[3];
	m_bRyG		= supCard.pgap[4];
	m_bRzG		= supCard.pgap[5];
	///
	m_aNid		= supCard.nid_a;
	m_bNid		= supCard.nid_b;
	m_bCN_a		= supCard.bCN_a;
	m_bCN_b		= supCard.bCN_b;
	m_bTanCur	= supCard.bTanCur;
	m_bTanPat	= supCard.bTanPat;
	m_bNorPat	= supCard.bNorPat;
	///////////////////////////// 
	m_dFx		= supCard.stiffness[0];
	m_dFy		= supCard.stiffness[1];
	m_dFz		= supCard.stiffness[2];
	m_dMx		= supCard.stiffness[3];
	m_dMy		= supCard.stiffness[4];
	m_dMz		= supCard.stiffness[5];
	///////////////////////////////////
	m_SupID		= supCard.sup_id;
	m_SuppProc	= supCard.SuppProc;
	////////////////////////////////
	m_strProc	= Proc[m_SuppProc];
}


void CDlg_SupE::UpdateSupInfo()
{
	// SuppProc Remains Same
	////////////////////////////////////////////////////
	SUPPCARD*	pSupCard = m_pDrLinSup->GetSuppCard();
	///////////////////
	pSupCard->kode[0]	= (BYTE)m_bTx;
	pSupCard->kode[1]	= (BYTE)m_bTy; 
	pSupCard->kode[2]	= (BYTE)m_bTz;
	pSupCard->kode[3]	= (BYTE)m_bRx;
	pSupCard->kode[4]	= (BYTE)m_bRy; 
	pSupCard->kode[5]	= (BYTE)m_bRz;
	//
	pSupCard->pgap[0]	= (BYTE)m_bTxG;
	pSupCard->pgap[1]	= (BYTE)m_bTyG;
	pSupCard->pgap[2]	= (BYTE)m_bTzG;
	pSupCard->pgap[3]	= (BYTE)m_bRxG;
	pSupCard->pgap[4]	= (BYTE)m_bRyG;
	pSupCard->pgap[5]	= (BYTE)m_bRzG;
	///
	pSupCard->nid_a		= m_aNid;
	pSupCard->nid_b		= m_bNid;
	pSupCard->nid_a		= m_aNid;
	pSupCard->nid_b		= m_bNid;
	pSupCard->bCN_a		= m_bCN_a;
	pSupCard->bCN_b		= m_bCN_b;
	pSupCard->bTanCur	= m_bTanCur;
	pSupCard->bTanPat	= m_bTanPat;
	pSupCard->bNorPat	= m_bNorPat;
	///////////////////////////////////
	pSupCard->stiffness[0]	= m_dFx;
	pSupCard->stiffness[1]	= m_dFy;
	pSupCard->stiffness[2]	= m_dFz;
	pSupCard->stiffness[3]	= m_dMx;
	pSupCard->stiffness[4]	= m_dMy;
	pSupCard->stiffness[5]	= m_dMz;
	///////////////////////////////////
	pSupCard->sup_id	= m_SupID;
	////////////////////////////////
	m_bSkewed	= FALSE;
	if(m_bTan || (m_aNid !=""))
		m_bSkewed	= TRUE;
	/////////////////////////////////
	m_pDrLinSup->SetSkewed(m_bSkewed);
	///////////
}

void CDlg_SupE::OnSelchangeNid() 
{
	CComboBox* pCtrl = (CComboBox*)(GetDlgItem(IDC_NID));
	/////////////////
	int index = pCtrl->GetCurSel();
	if(index<0)
	{
		m_aNid = "";
		return;
	}
	///////////
	pCtrl->GetLBText(index,m_aNid);
	//
}

void CDlg_SupE::OnSelchangeNidb2() 
{
	CComboBox* pCtrl = (CComboBox*)(GetDlgItem(IDC_NIDB2));
	/////////////////
	int index = pCtrl->GetCurSel();
	if(index<0)
	{
		m_bNid = "";
		return;
	}
	///////////
	pCtrl->GetLBText(index,m_bNid);
	//
}

void CDlg_SupE::OnCnA() 
{
	m_bCN_a = !m_bCN_a;
	///////////////////
	FillListAllNodeIDs_A();
}

void CDlg_SupE::OnCnB() 
{
	m_bCN_b = !m_bCN_b;
	///////////////////
	FillListAllNodeIDs_B();
}

void CDlg_SupE::OnTangent() 
{
	UpdateData(TRUE);
	///////////////
	if(m_SupBased == NODE)
		return;
	/////////////////////////
	m_bTan = !m_bTan;
	/////////////////////////
	if(m_bTan)
	{
		GetDlgItem(IDC_NID)->EnableWindow(FALSE);
		GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
		GetDlgItem(IDC_NIDB)->EnableWindow(FALSE);
		GetDlgItem(IDC_NIDHEADB)->SetWindowText("");
	}
	else
	{
		GetDlgItem(IDC_NID)->EnableWindow(TRUE);
		GetDlgItem(IDC_NIDHEAD)->SetWindowText("CNID_A");
		GetDlgItem(IDC_NIDB)->EnableWindow(TRUE);
		GetDlgItem(IDC_NIDHEADB)->SetWindowText("CNID_B");
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_SupE::OnOK()
{
	UpdateData(TRUE);
	///////////////
	UpdateSupInfo();
	////////////////
	CDialog::OnOK();
}

void CDlg_SupE::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_SupE::FillListAllNodeIDs_A()
{
   	((CComboBox*)(GetDlgItem(IDC_NID)))->ResetContent();	// Remove ALL  
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList 		= pObjectMgr->GetObjectList((m_bCN_a)?CNODE:NODE);
	//////////////////////////////////////////////////////
	if(pList->IsEmpty())
		return;
	//////////////////////////////////
	CString Nid;
	
	POSITION pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject( pos);
		Nid   = pNode->GetObjectID();
    	((CComboBox*)(GetDlgItem(IDC_NID)))->AddString(Nid);		// Show   
   	}
}    

void CDlg_SupE::FillListAllNodeIDs_B()
{
   	((CComboBox*)(GetDlgItem(IDC_NIDB2)))->ResetContent();	// Remove ALL  
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList 		= pObjectMgr->GetObjectList((m_bCN_b)?CNODE:NODE);
	//////////////////////////////////////////////////////
	if(pList->IsEmpty())
		return;
	//////////////////////////////////
	CString Nid;
	
	POSITION pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject( pos);
		Nid   = pNode->GetObjectID();
    	((CComboBox*)(GetDlgItem(IDC_NIDB)))->AddString(Nid);		// Show   
   	}
}    
/////////////////////////// end of module /////////////
