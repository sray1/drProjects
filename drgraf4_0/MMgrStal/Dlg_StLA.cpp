// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
#include "MStLDll.h"
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
#include "MSupRsrc.h"

#include "Dlg_StLA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_StLA dialog

CDlg_StLA::CDlg_StLA(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_StLA::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_StLA)
	m_NID	= _T("");
	m_bTan	= FALSE;
	m_NID_B = _T("");
	//}}AFX_DATA_INIT
	m_bPat	= FALSE;
}

void CDlg_StLA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_StLA)
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Check(pDX, IDC_TANGENT, m_bTan);
	DDX_CBString(pDX, IDC_NIDB, m_NID_B);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_StLA, CDialog)
	//{{AFX_MSG_MAP(CDlg_StLA)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_TANGENT, OnTangent)
	ON_BN_DOUBLECLICKED(IDC_TANGENT, OnTangent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_StLA message handlers

BOOL CDlg_StLA::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int nMax	= pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
	///////////////////////////////////////////
	if(m_bTanHide)
	{
		m_bTan = FALSE;
		GetDlgItem(IDC_TANGENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TANGENT)->SetWindowText("");
	}
	if(m_bIdBHide)
	{
		m_NID_B = "";
		GetDlgItem(IDC_NIDB)->EnableWindow(FALSE);
		GetDlgItem(IDC_NIDHEADB)->SetWindowText("");
	}
	/////////////////////////////////////////// Tangent or Normal
	GetDlgItem(IDC_TANGENT)->SetWindowText("Tangential");
	GetDlgItem(IDC_SKEWHEAD)->SetWindowText("Skew Joint X");
	if(m_bPat)	// Patch
	{
		GetDlgItem(IDC_TANGENT)->SetWindowText("Normal");
		GetDlgItem(IDC_SKEWHEAD)->SetWindowText("Skew Joint Z");
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_StLA::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_StLA::OnTangent() 
{
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
}

void CDlg_StLA::OnOK()
{
	UpdateData(TRUE);
	///////////////
	CDialog::OnOK();
}

void CDlg_StLA::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_StLA::FillListAllNodeIDs()
{

   	((CComboBox*)(GetDlgItem(IDC_NID)))->ResetContent();	// Remove ALL  
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CString Nid;
	
	int nMax = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMax<0)
		return;
	//////////////////////////////////
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
   			Nid   = (pNode->GetNodeCard())->id;
			///////////////////////////////////
			if(pNode->GetCategory() != CA_ELEMENT)
				continue;
			//////////////////////////////////////
   			if(pNode->GetCategory() == CA_ELEMENT)		// node for node/cnode for cnode
			{
		    	((CComboBox*)(GetDlgItem(IDC_NID )))->AddString(Nid);		// Show   
		    	((CComboBox*)(GetDlgItem(IDC_NIDB)))->AddString(Nid);		// Show   

			}
		}			    
   	}
   
}    
/////////////////////////// end of module //////////////
