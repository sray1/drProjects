// Dlg_SpnS.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
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
#include "Def_Card.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "dlg_LTyp.h"
#include "dlg_LALL.h"
//#include "dlg_LDir.h"
#include "dlg_LSYT.h"
#include "dlg_LSYM.h"
#include "dlg_LSY3.h"

#include "Dlg_SpnS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnS dialog


CDlg_SpnS::CDlg_SpnS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SpnS::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_SpnS)
	m_CID		= _T("");
	m_SpawnID	= _T("");
	//}}AFX_DATA_INIT
	m_pMatObj	= NULL;
}


void CDlg_SpnS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SpnS)
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_Text(pDX, IDC_SPNID, m_SpawnID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SpnS, CDialog)
	//{{AFX_MSG_MAP(CDlg_SpnS)
	ON_BN_CLICKED(IDC_SYMM, OnSymm)
	ON_BN_DOUBLECLICKED(IDC_SYMM, OnSymm)
	ON_BN_CLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnS message handlers

BOOL CDlg_SpnS::OnInitDialog() 
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
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr		= pObjectMgr->GetObjectList(SOLID);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMaxNodes)
	{
		FillListAllString_Pool();   // only with Solides
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

void CDlg_SpnS::OnSymm() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_nType = 0;
	//////////////
	CDlg_LSyT Dlg;
	if(Dlg.DoModal() == IDCANCEL)
		return;
	///////////////////
	if(Dlg.m_bType_1)
		m_nType = 0;
	else
		m_nType = 3;
}

void CDlg_SpnS::OnXform() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////
/*	Later todo
	CDlg_LTyp Dlg;
	if(Dlg.DoModal() == IDCANCEL)
		return;
*/
	///////////////////////////////
	m_nType = 2;
	////////////
//	if(Dlg.m_nType == 2)
		return;
}

void CDlg_SpnS::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_SpnS::OnOK() 
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
		CDlg_LSym Dlg;
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	if(m_nType == 1)			// Direct
	{
/*
		CDlg_LDir Dlg;			// Direct Matrix
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
		CDlg_LALL Dlg;			// TransformationBased
		/////////////////////////
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	if(m_nType == 3)			// Symmetry: 3 Pts
	{
		///////////////////////////////
		CDlg_LSy3 Dlg;
		Dlg.m_bInstanced = m_bInstanced;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bInstanced	= Dlg.m_bInstanced;
	}
	else
	{
		AfxMessageBox("ERROR:\nCDlg_SpnS::OnOK\nInternal Problem!");
   		return;
	}
	/////////////////////////////////////////////////////////////////  SetInfo
    SetInfoForDataBase(m_pDrSolid);
	///////////////
	CDialog::OnOK();
}
///////////////////////////////////////////////////////
void CDlg_SpnS::FillListAllString_Pool()
{
	// with SOLIDES
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(CURVE);
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
		if( pObject->GetObjectType() == SOLID)
		{ 
			CDrSolid* pNode = (CDrSolid*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}

void CDlg_SpnS::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(SOLID);//
	if (nMaxCurves<=0)
		return;
	//////////////////
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == SOLID)
		{ 
			CDrSolid* pCurve = (CDrSolid*)pObject;
   			CString CID		 = pCurve->GetObjectID();
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CID);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
		}	   		     
   	}
}    

void CDlg_SpnS::SetInfoForDataBase(CDrSolid* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDrSolid* pDrCurve;
    int index;  
	/////////////////////////////////////////////////////////////	
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_DADDY);          // globals
    ////////////////////////////////////////// Get Old Solid Info
	index = pObjectMgr->GetObjectIndexfromKey(SOLID,m_CID,1);
	pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	if(index>=0)
		pDrCurve = (CDrSolid*)(pDListMgr->GetObject(index));
	////////////////
	int nObjNo = pDrObject->GetObjectNo();;
	if(pDrCurve)
		pDrCurve->GetObjectInfo(pDrObject);
	/////////////////////////////////////// DisConnect
	if(!(pDrObject->GetLabelList()->IsEmpty()) )
		pDrObject->GetLabelList()->RemoveAll(); 
//	if(!(pDrObject->GetPentaList()->IsEmpty()) )
//		pDrObject->GetPentaList()->RemoveHead();
//	if(!(pDrObject->GetTriangleList()->IsEmpty()) )
//		pDrObject->GetTriangleList()->RemoveHead();
	if(!(pDrObject->GetElemList()->IsEmpty()) )
		pDrObject->GetElemList()->RemoveHead();
	if(!(pDrObject->GetObj3DList()->IsEmpty()) )
		pDrObject->GetObj3DList()->RemoveHead(); 
//	if(!(pDrObject->GetCurveList()->IsEmpty()) )
//		pDrObject->GetCurveList()->RemoveHead(); 
//	if(!(pDrObject->GetPatchList()->IsEmpty()) )
//		pDrObject->GetPatchList()->RemoveHead(); 
	//////////////////////////////////////////// Override
//	pDrObject->SetSolidProc(SP_SPAWN);	
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
    
