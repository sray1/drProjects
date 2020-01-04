// CCurveSuppPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "Def_Supp.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveSuppPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveSuppPage property page

IMPLEMENT_DYNCREATE(CCurveSuppPage, CPropertyPage)

CCurveSuppPage::CCurveSuppPage() : CPropertyPage(CCurveSuppPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveSuppPage)
	m_bSkewed = FALSE;
	m_SuppType = _T("");
	m_TX = 0.0;
	m_RX = 0.0;
	m_TY = 0.0;
	m_RY = 0.0;
	m_TZ = 0.0;
	m_RZ = 0.0;
	m_CreateBase = _T("");
	//}}AFX_DATA_INIT
}

CCurveSuppPage::~CCurveSuppPage()
{
}

void CCurveSuppPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveSuppPage)
	DDX_Check(pDX, IDC_SKEWED, m_bSkewed);
	DDX_Text(pDX, IDC_SUPPORT_TYPE, m_SuppType);
	DDX_Text(pDX, IDD_NODE_DX, m_TX);
	DDX_Text(pDX, IDD_NODE_DX2, m_RX);
	DDX_Text(pDX, IDD_NODE_DY, m_TY);
	DDX_Text(pDX, IDD_NODE_DY2, m_RY);
	DDX_Text(pDX, IDD_NODE_DZ, m_TZ);
	DDX_Text(pDX, IDD_NODE_DZ2, m_RZ);
	DDX_Text(pDX, IDC_CREATEBASE, m_CreateBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveSuppPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveSuppPage)
	ON_CBN_SELCHANGE(IDC_SUPPCOMBO, OnSelchangeSuppcombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveSuppPage message handlers

BOOL CCurveSuppPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CCurveSuppPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(CURVE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(CURVE,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	m_pCurrentObject = (CDrCurve*)(pList->GetObject(index));
	///////////////////////
	if(m_pCurrentObject)
	{
		///
		UpdateCombo(m_pCurrentObject->GetSuppList(),IDC_SUPPCOMBO);
   		OnSelchangeSuppcombo();
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CCurveSuppPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
{
	if(pList->IsEmpty())
		return 0;
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	CDrObject* pObject;			       
	POSITION pos;
	///	
	pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pList->GetNextObject( pos);
    	((CComboBox*)pWndCtrl)->AddString(pObject->GetObjectID());	// Show ALL  
   	}
	///
   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

void CCurveSuppPage::OnSelchangeSuppcombo() 
{
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(IDC_SUPPCOMBO);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
	if(index<0)
		return;
	//////////////
	CString strID;  
    ((CComboBox*)pWndCtrl)->GetLBText(index,strID); 
    /////////////////////////////////////////////
   	index = m_pCurrentObject->GetSuppList()->GetObjectIndex(LIN_SUPPORT,strID);
	//////////////
   	if(index<0)
   	{
    	MessageBeep(MB_ICONEXCLAMATION); 
    	return;
	}
	else
	{
		CDrLinSup* pLinSup = (CDrLinSup*)(m_pCurrentObject->GetSuppList()->GetObject(index)); 
		FillLinearSupportInfo(pLinSup);
	}
	////////
}

void CCurveSuppPage::FillLinearSupportInfo(CDrLinSup* pLinSup) 
{
	SUPPCARD* pSupCard = pLinSup->GetSuppCard();
	////////////////////////////////////////////
	SUPPPROC suppproc = pSupCard->SuppProc;
	FillSuppType(suppproc);
	//////////////////////////////////////////
	((CButton*)GetDlgItem(IDC_DOFX))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFXR))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFY))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFYR))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFZ))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFZR))->SetCheck(FALSE);	// 
	///
	if(pSupCard->kode[0])
	{
		((CButton*)GetDlgItem(IDC_DOFX))->SetCheck(TRUE);	// 
		m_TX = pSupCard->stiffness[0];
	}
	if(pSupCard->kode[3])
	{
		((CButton*)GetDlgItem(IDC_DOFXR))->SetCheck(TRUE);	// 
		m_RX = pSupCard->stiffness[1];
	}
	if(pSupCard->kode[1])
	{
		((CButton*)GetDlgItem(IDC_DOFY))->SetCheck(TRUE);	// 
		m_TY = pSupCard->stiffness[2];
	}
	if(pSupCard->kode[4])
	{
		((CButton*)GetDlgItem(IDC_DOFYR))->SetCheck(TRUE);	// 
		m_RY = pSupCard->stiffness[3];
	}
	if(pSupCard->kode[2])
	{
		((CButton*)GetDlgItem(IDC_DOFZ))->SetCheck(TRUE);	// 
		m_TZ = pSupCard->stiffness[4];
	}
	if(pSupCard->kode[5])
	{
		((CButton*)GetDlgItem(IDC_DOFZR))->SetCheck(TRUE);	// 
		m_RZ = pSupCard->stiffness[5];
	}
	//////////////
	m_bSkewed		= pLinSup->IsSkewed();
	////////////////////////////////////////////
	GetCreateBase(m_CreateBase,pLinSup);
}

void CCurveSuppPage::GetCreateBase(CString& strCreateBase,CDrLinSup* pSupp) 
{
	UINT uCreateBase = pSupp->GetCreateBase();
	////////////////////////////////////////////
	switch(uCreateBase)
	{
		case NODE:
			strCreateBase	= "Node";
			break;
		case CURVE:
			strCreateBase	= "Curve";
			break;
		case PATCH:
			strCreateBase	= "Patch";
			break;
		case SOLID:
			strCreateBase	= "Solid";
			break;
		case OBJ3D:
			strCreateBase	= "Object Assembly";
			break;
		case FE0D:
			strCreateBase	= "Mesh Node";
			break;
		case FE1D:
			strCreateBase	= "1D Element";
			break;
		case FE2D:
			strCreateBase	= "2D Element";
			break;
		case FE3D:
			strCreateBase	= "3D Element";
			break;
		case MESH1D:
			strCreateBase	= "1D Mesh";
			break;
		case MESH2D:
			strCreateBase	= "2D Mesh";
			break;
		case MESH3D:
			strCreateBase	= "3D Mesh";
			break;
		case MBJ3D:
			strCreateBase	= "Mesh Assembly";
			break;
		default:
			break;
	}
}

void CCurveSuppPage::FillSuppType(SUPPPROC  suppproc) 
{
	m_SuppType = "Dont Know!";
	//////////////////////////////////////////
	switch(suppproc)
	{
		case SUP_RIGID:
			m_SuppType = "Rigid Anchor";
			break;
		case SUP_LINSPR:
			m_SuppType = "Linear Spring";
			break;
		case SUP_LINSNU:
			m_SuppType = "Linear Snubber";
			break;
		case SUP_NONSPR:
			m_SuppType = "Non-Linear Spring";
			break;
		case SUP_NONSNU:
			m_SuppType = "Non-Linear Snubber";
			break;
		default:
			break;
	}
}

BOOL CCurveSuppPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}