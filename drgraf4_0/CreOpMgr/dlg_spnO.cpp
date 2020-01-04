// Dlg_SpnC.cpp : implementation file
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
#include "Def_IGen.h"
#include "DrObj3D.h"
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
/////////////////////
#include "CommRsrc.h"
#include "Dlg_SpnO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnO dialog


CDlg_SpnO::CDlg_SpnO(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SpnO::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_SpnO)
	m_SpawnID	= _T("");
	m_CID		= _T("");
	//}}AFX_DATA_INIT
	m_pMatObj	= NULL;
}


void CDlg_SpnO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SpnO)
	DDX_Text(pDX, IDC_SPNID, m_SpawnID);
	DDX_Text(pDX, IDC_CID, m_CID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SpnO, CDialog)
	//{{AFX_MSG_MAP(CDlg_SpnO)
	ON_BN_CLICKED(IDC_SYMM, OnSymm)
	ON_BN_DOUBLECLICKED(IDC_SYMM, OnSymm)
	ON_BN_CLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnO message handlers

BOOL CDlg_SpnO::OnInitDialog() 
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
	pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	int nMaxObj3Ds 	 = pDListMgr->GetSpecificObjectCount(OBJ3D);
	if(nMaxObj3Ds)
	{
		FillListAllString_Pool();   // only with Obj3Ds
//		FillListAllObj3DIDs();
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

void CDlg_SpnO::OnSymm() 
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

void CDlg_SpnO::OnXform() 
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

void CDlg_SpnO::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_SpnO::OnOK() 
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
		Dlg.m_IGenType	 = OBJ3D;
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
		AfxMessageBox("ERROR:\nCDlg_SpnO::OnOK\nInternal Problem!");
   		return;
	}
	/////////////////////////////////////////////////////////////////  SetInfo
    SetInfoForDataBase(m_pDrObj3D);
	///////////////
	CDialog::OnOK();
}
///////////////////////////////////////////////////////
void CDlg_SpnO::FillListAllString_Pool()
{
	// with Obj3DS
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	////////////////////////////////////////////////////////
	int nMaxObj3Ds = pDListMgr->GetSpecificObjectCount(OBJ3D);
    if(nMaxObj3Ds<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Nid;
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == OBJ3D)
		{ 
			CDrObj3D* pObj3D = (CDrObj3D*)pObject;
			Nid = pObj3D->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}

void CDlg_SpnO::FillListAllObj3DIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxObj3Ds = pDListMgr->GetSpecificObjectCount(OBJ3D);//
	if (nMaxObj3Ds<=0)
		return;
	//////////////////
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == OBJ3D)
		{ 
			CDrObj3D* pObj3D = (CDrObj3D*)pObject;
   			CString CID		 = pObj3D->GetObjectID();
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CID);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
		}	   		     
   	}
}    

void CDlg_SpnO::SetInfoForDataBase(CDrObj3D* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pDListMgr;
	CDrObj3D* pDrObj3D;
    int index;  
	////////////////////////////////////
    pDrObject->SetObjectType((int)OBJ3D);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
    ////////////////////////////////////////// Get Old Obj3D Info
	pDListMgr	= pObjectMgr->GetObjectList(OBJ3D);
	index = pObjectMgr->GetObjectIndexfromKey(OBJ3D,m_CID,1);
	if(index>=0)
		pDrObj3D = (CDrObj3D*)(pDListMgr->GetObject(index));
	////////////////
	int nObjNo = pDrObject->GetObjectNo();
	if(pDrObj3D)
		pDrObject->SetObjectInfo(pDrObj3D);
	//////////////////////////////////////////// DisConnect
	if(!(pDrObject->GetLabelList()->IsEmpty()) )
		pDrObject->GetLabelList()->RemoveAll();
/*	
	if(!(pDrObject->GetCurveList()->IsEmpty()) )
		pDrObject->GetCurveList()->RemoveAll(); 
	if(!(pDrObject->GetSolidList()->IsEmpty()) )
		pDrObject->GetSolidList()->RemoveAll(); 
	if(!(pDrObject->GetElemList()->IsEmpty()) )
		pDrObject->GetElemList()->RemoveAll();
	if(!(pDrObject->GetPatchList()->IsEmpty()) )
		pDrObject->GetPatchList()->RemoveAll(); 
	if(!(pDrObject->GetObj3DList()->IsEmpty()) )
		pDrObject->GetObj3DList()->RemoveAll(); 
	if(!(pDrObject->GetCProfList()->IsEmpty()) )
		pDrObject->GetCProfList()->RemoveAll(); 
*/
	//////////////////////////////////////////// Override
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
    
