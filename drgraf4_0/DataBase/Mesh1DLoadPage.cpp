// CMesh1DLoadPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "Def_StaL.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DLoadPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DLoadPage property page

IMPLEMENT_DYNCREATE(CMesh1DLoadPage, CPropertyPage)

CMesh1DLoadPage::CMesh1DLoadPage() : CPropertyPage(CMesh1DLoadPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DLoadPage)
	m_LoadType = _T("");
	m_TX = 0.0;
	m_RX = 0.0;
	m_TY = 0.0;
	m_RY = 0.0;
	m_TZ = 0.0;
	m_RZ = 0.0;
	m_bSkewed = FALSE;
	m_CreateBase = _T("");
	//}}AFX_DATA_INIT
}

CMesh1DLoadPage::~CMesh1DLoadPage()
{
}

void CMesh1DLoadPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DLoadPage)
	DDX_Text(pDX, IDC_LOAD_TYPE, m_LoadType);
	DDX_Text(pDX, IDD_NODE_DX, m_TX);
	DDX_Text(pDX, IDD_NODE_DX2, m_RX);
	DDX_Text(pDX, IDD_NODE_DY, m_TY);
	DDX_Text(pDX, IDD_NODE_DY2, m_RY);
	DDX_Text(pDX, IDD_NODE_DZ, m_TZ);
	DDX_Text(pDX, IDD_NODE_DZ2, m_RZ);
	DDX_Check(pDX, IDC_SKEWED, m_bSkewed);
	DDX_Text(pDX, IDC_CREATEBASE, m_CreateBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DLoadPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DLoadPage)
	ON_CBN_SELCHANGE(IDC_STALCOMBO, OnSelchangeStalcombo)
	ON_CBN_SELCHANGE(IDC_SPELCOMBO, OnSelchangeSpelcombo)
	ON_CBN_SELCHANGE(IDC_DYNLCOMBO, OnSelchangeDynlcombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DLoadPage message handlers

int CMesh1DLoadPage::UpdateObjData(CString& strItemID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(MESH1D);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(MESH1D,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	m_pCurrentObject = (CDrMesh1D*)(pList->GetObject(index));
	///////////////////////
	if(m_pCurrentObject)
	{
		///
		UpdateCombo(m_pCurrentObject->GetStaLList(),IDC_STALCOMBO);
		UpdateCombo(m_pCurrentObject->GetSpeLList(),IDC_SPELCOMBO);
		UpdateCombo(m_pCurrentObject->GetDynLList(),IDC_DYNLCOMBO);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CMesh1DLoadPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

void CMesh1DLoadPage::OnSelchangeStalcombo() 
{
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(IDC_STALCOMBO);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
	if(index<0)
		return;
	//////////////
	CString strID;  
    ((CComboBox*)pWndCtrl)->GetLBText(index,strID); 
    /////////////////////////////////////////////
   	index = m_pCurrentObject->GetStaLList()->GetObjectIndex(STATICLOAD,strID);
	//////////////
   	if(index<0)
   	{
    	MessageBeep(MB_ICONEXCLAMATION); 
    	return;
	}
	else
	{
		CDrStatic* pStatic = (CDrStatic*)(m_pCurrentObject->GetStaLList()->GetObject(index)); 
		FillLinearStaticLoadInfo(pStatic);
	}
	////////
}

void CMesh1DLoadPage::OnSelchangeSpelcombo() 
{
	// TODO: Add your control notification handler code here
	
}

void CMesh1DLoadPage::OnSelchangeDynlcombo() 
{
	// TODO: Add your control notification handler code here
	
}

void CMesh1DLoadPage::FillLinearStaticLoadInfo(CDrStatic* pStatic) 
{
	STALCARD* pStaLCard = pStatic->GetStaLCard();
	STALPROC  stalproc	= pStaLCard->StaLProc;
	//////////////////////////////////////////
	FillLoadType(stalproc);
	//////////////////////////////////////////
	((CButton*)GetDlgItem(IDC_DOFX))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFXR))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFY))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFYR))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFZ))->SetCheck(FALSE);	// 
	((CButton*)GetDlgItem(IDC_DOFZR))->SetCheck(FALSE);	// 
	///
	if(pStaLCard->kode[0])
	{
		((CButton*)GetDlgItem(IDC_DOFX))->SetCheck(TRUE);	// 
		m_TX = pStaLCard->value[0];
	}
	if(pStaLCard->kode[3])
	{
		((CButton*)GetDlgItem(IDC_DOFXR))->SetCheck(TRUE);	// 
		m_RX= pStaLCard->value[1];
	}
	if(pStaLCard->kode[1])
	{
		((CButton*)GetDlgItem(IDC_DOFY))->SetCheck(TRUE);	// 
		m_TY = pStaLCard->value[2];
	}
	if(pStaLCard->kode[4])
	{
		((CButton*)GetDlgItem(IDC_DOFYR))->SetCheck(TRUE);	// 
		m_RY = pStaLCard->value[3];
	}
	if(pStaLCard->kode[2])
	{
		((CButton*)GetDlgItem(IDC_DOFZ))->SetCheck(TRUE);	// 
		m_TZ = pStaLCard->value[4];
	}
	if(pStaLCard->kode[5])
	{
		((CButton*)GetDlgItem(IDC_DOFZR))->SetCheck(TRUE);	// 
		m_RZ = pStaLCard->value[5];
	}
	//////////////
	m_bSkewed		= pStatic->IsSkewed();
	////////////////////////////////////////////
	GetCreateBase(m_CreateBase,pStatic);
}

void CMesh1DLoadPage::GetCreateBase(CString& strCreateBase,CDrStatic* pStatic) 
{
	UINT uCreateBase = pStatic->GetCreateBase();
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

void CMesh1DLoadPage::FillLoadType(STALPROC  stalproc) 
{
	m_LoadType = "Dont Know!";
	//////////////////////////////////////////
	switch(stalproc)
	{
		case STL_DISPLACE:
			m_LoadType = "Displacement/Rotation";
			break;
		case STL_FORCE:
			m_LoadType = "Force/Moment";
			break;
		case STL_PRESSURE:
			m_LoadType = "Pressure";
			break;
		case STL_THERMAL:
			m_LoadType = "Thermal";
			break;
		case STL_LUMPWT:
			m_LoadType = "Lump Weight";
			break;
		default:
			break;
	}
}

BOOL CMesh1DLoadPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CMesh1DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}