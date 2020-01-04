// StalDefnPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "Def_StaL.h"
#include "StalSheet.h"
//////////////////////
#include "StalDefnPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStalDefnPage property page

IMPLEMENT_DYNCREATE(CStalDefnPage, CPropertyPage)

CStalDefnPage::CStalDefnPage() : CPropertyPage(CStalDefnPage::IDD)
{
	//{{AFX_DATA_INIT(CStalDefnPage)
	m_StaLID = _T("");
	m_bSkewed = FALSE;
	m_LoadType = _T("");
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
	//}}AFX_DATA_INIT
}

CStalDefnPage::~CStalDefnPage()
{
}

void CStalDefnPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStalDefnPage)
	DDX_Text(pDX, IDD_STAL_ID, m_StaLID);
	DDX_Check(pDX, IDC_SKEWED, m_bSkewed);
	DDX_Text(pDX, IDC_STAL_TYPE, m_LoadType);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStalDefnPage, CPropertyPage)
	//{{AFX_MSG_MAP(CStalDefnPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStalDefnPage message handlers

BOOL CStalDefnPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CStalDefnPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(STATICLOAD);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(STATICLOAD,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	m_pCurrentObject = (CDrStatic*)(pList->GetObject(index));
	FillLinearStaticLoadInfo(m_pCurrentObject);
	/////////////////
	UpdateData(FALSE);
	/////////////////
	return 0;
}
int CStalDefnPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

void CStalDefnPage::FillLinearStaticLoadInfo(CDrStatic* pStatic) 
{
	m_StaLID = pStatic->GetObjectID();
	///
	STALCARD* pStaLCard = pStatic->GetStaLCard();
	STALPROC  stalproc	= pStaLCard->StaLProc;
	///
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
		m_RX = pStaLCard->value[1];
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
	if(m_bSkewed)
	{
		m_SKDirX = pStaLCard->SkewDir.x;
		m_SKDirY = pStaLCard->SkewDir.y;
		m_SKDirZ = pStaLCard->SkewDir.z;
	}
	m_bTanORNor = pStaLCard->bTanCur;
	////////////////////////////////////////////
	GetCreateBase(m_CreateBase,pStatic);
}

void CStalDefnPage::GetCreateBase(CString& strCreateBase,CDrStatic* pStatic) 
{
	UINT uCreateBase = pStatic->GetCreateBase();
	STALCARD* pStaLCard = pStatic->GetStaLCard();
	/////////////////////////////////////////////////////////
	m_bTanORNor = pStaLCard->bTanCur;
	GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Tangential");
	((CButton*)GetDlgItem(IDC_TANORNORMAL))->SetCheck(TRUE);
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
			GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Normal");
			break;
		case SOLID:
			GetDlgItem(IDC_TANORNORMAL)->SetWindowText("Normal");
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

void CStalDefnPage::FillLoadType(STALPROC  stalproc) 
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

BOOL CStalDefnPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CStalSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
