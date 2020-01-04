// SuppDefnPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "Def_Supp.h"
#include "SuppSheet.h"
/////////////////////
#include "SuppDefnPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuppDefnPage property page

IMPLEMENT_DYNCREATE(CSuppDefnPage, CPropertyPage)

CSuppDefnPage::CSuppDefnPage() : CPropertyPage(CSuppDefnPage::IDD)
{
	//{{AFX_DATA_INIT(CSuppDefnPage)
	m_bSkewed = FALSE;
	m_TX = 0.0;
	m_RX = 0.0;
	m_TY = 0.0;
	m_RY = 0.0;
	m_TZ = 0.0;
	m_RZ = 0.0;
	m_CreateBase = _T("");
	m_SKDirX = 0.0;
	m_SKDirY = 0.0;
	m_SKDirZ = 0.0;
	m_bTanORNor = FALSE;
	m_SuppType = _T("");
	m_SuppID = _T("");
	//}}AFX_DATA_INIT
}

CSuppDefnPage::~CSuppDefnPage()
{
}

void CSuppDefnPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuppDefnPage)
	DDX_Check(pDX, IDC_SKEWED, m_bSkewed);
	DDX_Text(pDX, IDC_SUPPORT_TYPE, m_SuppType);
	DDX_Text(pDX, IDD_NODE_DX, m_TX);
	DDX_Text(pDX, IDD_NODE_DX2, m_RX);
	DDX_Text(pDX, IDD_NODE_DY, m_TY);
	DDX_Text(pDX, IDD_NODE_DY2, m_RY);
	DDX_Text(pDX, IDD_NODE_DZ, m_TZ);
	DDX_Text(pDX, IDD_NODE_DZ2, m_RZ);
	DDX_Text(pDX, IDC_CREATEBASE, m_CreateBase);
	DDX_Text(pDX, IDC_SKEWDIRX, m_SKDirX);
	DDX_Text(pDX, IDC_SKEWDIRY, m_SKDirY);
	DDX_Text(pDX, IDC_SKEWDIRZ, m_SKDirZ);
	DDX_Check(pDX, IDC_TANORNORMAL, m_bTanORNor);
	DDX_Text(pDX, IDD_SUPPORT_ID, m_SuppID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuppDefnPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSuppDefnPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuppDefnPage message handlers

BOOL CSuppDefnPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CSuppDefnPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(LIN_SUPPORT);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(LIN_SUPPORT,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	m_pCurrentObject = (CDrLinSup*)(pList->GetObject(index));
	FillLinearSupportInfo(m_pCurrentObject);
	/////////////////
	UpdateData(FALSE);
	/////////////////
	return 0;
}

int CSuppDefnPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

void CSuppDefnPage::FillLinearSupportInfo(CDrLinSup* pLinSup) 
{
	m_SuppID = pLinSup->GetObjectID();
	///
	SUPPCARD* pSupCard = pLinSup->GetSuppCard();
	SUPPPROC suppproc = pSupCard->SuppProc;
	///
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
	if(pSupCard->kode[1])
	{
		((CButton*)GetDlgItem(IDC_DOFY))->SetCheck(TRUE);	// 
		m_TY = pSupCard->stiffness[1];
	}
	if(pSupCard->kode[2])
	{
		((CButton*)GetDlgItem(IDC_DOFZ))->SetCheck(TRUE);	// 
		m_TZ = pSupCard->stiffness[2];
	}
	if(pSupCard->kode[3])
	{
		((CButton*)GetDlgItem(IDC_DOFXR))->SetCheck(TRUE);	// 
		m_RX = pSupCard->stiffness[3];
	}
	if(pSupCard->kode[4])
	{
		((CButton*)GetDlgItem(IDC_DOFYR))->SetCheck(TRUE);	// 
		m_RY = pSupCard->stiffness[4];
	}
	if(pSupCard->kode[5])
	{
		((CButton*)GetDlgItem(IDC_DOFZR))->SetCheck(TRUE);	// 
		m_RZ = pSupCard->stiffness[5];
	}
	//////////////
	m_bSkewed		= pLinSup->IsSkewed();
	if(m_bSkewed)
	{
		m_SKDirX = pSupCard->SkewDir.x;
		m_SKDirY = pSupCard->SkewDir.y;
		m_SKDirZ = pSupCard->SkewDir.z;
	}
	m_bTanORNor = pSupCard->bTanCur;
	////////////////////////////////////////////
	GetCreateBase(m_CreateBase,pLinSup);
}

void CSuppDefnPage::GetCreateBase(CString& strCreateBase,CDrLinSup* pSupp) 
{
	UINT uCreateBase = pSupp->GetCreateBase();
	SUPPCARD* pSuppCard = pSupp->GetSuppCard();
	/////////////////////////////////////////////////////////
	m_bTanORNor = pSuppCard->bTanCur;
	GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Tangential");
	((CButton*)GetDlgItem(IDC_TANORNORMAL))->SetCheck(TRUE);
	/////////////////////////////////////////////////////////
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
			GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Normal");
			break;
		case SOLID:
			strCreateBase	= "Solid";
			GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Normal");
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

void CSuppDefnPage::FillSuppType(SUPPPROC  suppproc) 
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

BOOL CSuppDefnPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CSuppSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
