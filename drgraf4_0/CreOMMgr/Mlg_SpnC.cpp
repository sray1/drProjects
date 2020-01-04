// Dlg_SpnC.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrMesh1D.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "Dlg_LTyp.h"
#include "Mlg_LALL.h"
//#include "dlg_LDir.h"
#include "Mlg_LSYT.h"
#include "Mlg_LSYM.h"
#include "Mlg_LSY3.h"
/////////////////////
#include "CommRsrc.h"
#include "Mlg_SpnC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnC dialog


CMlg_SpnC::CMlg_SpnC(CWnd* pParent /*=NULL*/)
	: CDialog(CMlg_SpnC::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CMlg_SpnC)
	m_SpawnID	= _T("");
	m_CID = _T("");
	//}}AFX_DATA_INIT
	m_pMatObj	= NULL;
}


void CMlg_SpnC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMlg_SpnC)
	DDX_Text(pDX, IDC_SPNID, m_SpawnID);
	DDX_Text(pDX, IDC_CID, m_CID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMlg_SpnC, CDialog)
	//{{AFX_MSG_MAP(CMlg_SpnC)
	ON_BN_CLICKED(IDC_SYMM, OnSymm)
	ON_BN_DOUBLECLICKED(IDC_SYMM, OnSymm)
	ON_BN_CLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnC message handlers

BOOL CMlg_SpnC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//structural
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	///////////////////////////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(MESH1D);
	if(nMaxNodes)
	{
		FillListAllString_Pool();   // only with Curves
//		FillListAllCurveIDs();
	}
	///////////////////////////////////////////////////////////
	m_nType = 2; // 0=Symm(Pt+Normal)/2=XForms Based/1=Direct/3=Symm(3Pts)
	((CButton*)GetDlgItem(IDC_XFORM))->SetCheck(TRUE);
	//////////////////////////////////////
	GetDlgItem(IDC_SPNID)->SetFocus();
	///////////////////////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMlg_SpnC::OnSymm() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_nType = 0;
	//////////////
	CMlg_LSyT Dlg;
	if(Dlg.DoModal() == IDCANCEL)
		return;
	///////////////////
	if(Dlg.m_bType_1)
		m_nType = 0;
	else
		m_nType = 3;
}

void CMlg_SpnC::OnXform() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////
/*	Later todo
	CMlg_LTyp Dlg;
	if(Dlg.DoModal() == IDCANCEL)
		return;
*/
	///////////////////////////////
	m_nType = 2;
	////////////
//	if(Dlg.m_nType == 2)
		return;
}

void CMlg_SpnC::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMlg_SpnC::OnOK() 
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
   	/////////////////////////////////////////////// Profile ID
   	if("" == m_SpawnID)
   	{
   		AfxMessageBox("Please Select a Spawn ID");
   		return;
   	}
	/////////////////////////////////////////////////////////// Get Info
	if(m_pMatObj)
		m_pMatObj = NULL;
	/////////////////////
	m_bInstanced = FALSE;
	/////////////////////
	if(m_nType == 0)			// Symmetry
	{
		///////////////////////////////
		CMlg_LSym Dlg;
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	if(m_nType == 1)			// Direct
	{
/*
		CMlg_LDir Dlg;			// Direct Matrix
		/////////////////////////
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
		/////////////
*/
	}
	else
	if(m_nType == 2)			// XForms
	{
		CMlg_LALL Dlg;			// TransformationBased
		/////////////////////////
		Dlg.m_IGenType	 = MESH1D;
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	if(m_nType == 3)			// Symmetry: 3 Pts
	{
		///////////////////////////////
		CMlg_LSy3 Dlg;
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	{
		AfxMessageBox("ERROR:\nCMlg_SpnC::OnOK\nInternal Problem!");
   		return;
	}
	/////////////////////////////////////////////////////////////////  SetInfo
    SetInfoForDataBase(m_pDrCurve);
	///////////////
	CDialog::OnOK();
}
///////////////////////////////////////////////////////
void CMlg_SpnC::FillListAllString_Pool()
{
	// with CURVES
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	////////////////////////////////////////////////////////
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(MESH1D);
    if(nMaxNodes<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Nid;
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == MESH1D)
		{ 
			CDrMesh1D* pNode = (CDrMesh1D*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}

void CMlg_SpnC::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(MESH1D);//
	if (nMaxCurves<=0)
		return;
	//////////////////
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == MESH1D)
		{ 
			CDrMesh1D* pCurve = (CDrMesh1D*)pObject;
   			CString CID		 = pCurve->GetObjectID();
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CID);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
		}	   		     
   	}
}    

void CMlg_SpnC::SetInfoForDataBase(CDrMesh1D* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pDListMgr;
	CDrMesh1D* pDrCurve;
    int index;  
	////////////////////////////////////
    pDrObject->SetObjectType((int)MESH1D);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    ////////////////////////////////////////// Get Old Curve Info
	pDListMgr	= pObjectMgr->GetObjectList(MESH1D);
	index = pObjectMgr->GetObjectIndexfromKey(MESH1D,m_CID,1);
		if(index>=0)
			pDrCurve = (CDrMesh1D*)(pDListMgr->GetObject(index));
	////////////////
	int nObjNo = pDrObject->GetObjectNo();
	if(pDrCurve)
		pDrCurve->GetObjectInfo(pDrObject);
	/////////////////////////////////////// DisConnect
	if(!(pDrObject->GetLabelList()->IsEmpty()) )
		pDrObject->GetLabelList()->RemoveAll(); 
//	if(!(pDrObject->GetFE0DList()->IsEmpty()) )	// should not delete, needed to Clone
//		pDrObject->GetFE0DList()->RemoveAll();
	if(!(pDrObject->GetFE1DList()->IsEmpty()) )
		pDrObject->GetFE1DList()->RemoveAll();
	if(!(pDrObject->GetFE2DList()->IsEmpty()) )
		pDrObject->GetFE2DList()->RemoveAll();
	if(!(pDrObject->GetFE3DList()->IsEmpty()) )
		pDrObject->GetFE3DList()->RemoveAll();
	if(!(pDrObject->GetMbj3DList()->IsEmpty()) )
		pDrObject->GetMbj3DList()->RemoveAll();
	//////////////////////////////////////////// Override
//	pDrObject->SetCurveType_S(CP_SPAWN);	
	pDrObject->SetObjectNo(nObjNo);	
	pDrObject->SetObjectID(m_SpawnID);
	pDrObject->SetInstanced(m_bInstanced);
	pDrObject->SetMatObj(m_pMatObj);	
	pDrObject->SetParentID(m_CID);	
	/////////////////////////////////
	switch(m_nType)
	{
		case 0:
			pDrObject->SetSpawnType(SPN_SYMM_N);
		case 1:
			pDrObject->SetSpawnType(SPN_DIRECT);
		case 2:
			pDrObject->SetSpawnType(SPN_XFORMS);
		case 3:
			pDrObject->SetSpawnType(SPN_SYMM_3);
		default:
			pDrObject->SetSpawnType(SPN_NONE);
	}
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
    
