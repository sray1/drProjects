// dlg_pobj.cpp : implementation file
//

#include "stdafx.h"

#include "glb_Objs.h"
#include "glb_CuPS.h"
#include "glb_View.h"
/////////////////////
#include "3DMath.h"
#include "XForm.h"

#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Ext_Elem.h"
#include "Ext_Cur.h"
#include "Ext_Pat.h"
#include "Ext_Sol.h"
#include "DrNode.h"
#include "DrSolid.h"
#include "DrPatch.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
/////////////////////
#include "dlg_LMat.h"
#include "dlg_pobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PObj dialog


CDlg_PObj::CDlg_PObj(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PObj::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_PObj)
	m_OID_Post = "";
	m_bLMat = TRUE;
	//}}AFX_DATA_INIT
}

void CDlg_PObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PObj)
	DDX_Text(pDX, IDC_OID_POST, m_OID_Post);
	DDX_Check(pDX, IDC_DEFAULT_LMAT, m_bLMat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_PObj, CDialog)
	//{{AFX_MSG_MAP(CDlg_PObj)
	ON_BN_CLICKED(IDC_LOCALM, OnLocalm)
	ON_BN_DOUBLECLICKED(IDC_LOCALM, OnLocalm)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_PObj message handlers

BOOL CDlg_PObj::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////
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
	/////////////////////////////////////////////
	int nMax;
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	nMax 	  = pDListMgr->GetSpecificObjectCount(SOLID);
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	nMax 	 += pDListMgr->GetSpecificObjectCount(PATCH);
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	nMax 	 += pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllString();   // only with Posted Objects
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_OID_POST);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_PObj::OnDel()
{
	//delete current selection from SelectList	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
		((CListBox*)(pWndCtrl))->DeleteString(index); 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_PObj::OnAdd()
{
	// Add Current selction of POOLLIST to SELECTLIST	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
   	{
		CString CNid;
		((CListBox*)(pWndCtrl))->GetText(index,CNid);
		////////////////////////////////////// 
		pWndCtrl = GetDlgItem(IDD_SELECTLIST);
//		if( (((CListBox*)(pWndCtrl))->FindString(-1,CNid) ) >=0)     //already selected
//			return;
		((CListBox*)(pWndCtrl))->AddString(CNid);
	}	 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_PObj::OnCancel()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CDialog::OnCancel();
}

void CDlg_PObj::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrObj3D* pAdd 	= (CDrObj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,OBJ3D));
    SetInfoForDataBase(pAdd);
	///////////////
	CDialog::OnOK();
}


void CDlg_PObj::OnLocalm()
{
    ////////////////////
	UpdateData(TRUE);			//Update Data    
	///////////////////////////////////////
/*
	if(m_Dirty == "")
	{
		AfxMessageBox(
			"Please Select a Patch from the Pool");
		return;
	}
*/	
	////////////////							
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////	
	CDlg_LMat DlgLMat;
	//////////////////
//	DlgLMat.m_PatchID = m_Dirty;
	///////
	if(DlgLMat.DoModal() == IDCANCEL)
		return;
	////////////////////////////////////////////////////////////	
	m_bLMat 		= FALSE;
    ////////////////////
	UpdateData(FALSE);			//Update SCreen    
	///////////////////////
	m_RotX		= DlgLMat.m_RotX;
	m_RotY		= DlgLMat.m_RotY;
	m_RotZ		= DlgLMat.m_RotZ;
	m_ScaleX	= DlgLMat.m_ScaleX;
	m_ScaleY	= DlgLMat.m_ScaleY;
	m_ScaleZ	= DlgLMat.m_ScaleZ;
	///////////////////////////////
	m_RotPtID	= DlgLMat.m_RotPtID;
	/////////////////////////////////// strip Scale Factor (World Coord)
	m_TranX		= DlgLMat.m_TranX;
	pObjectMgr->SCtoDS(&m_TranX);
	m_TranX *= (dWorldBase/dMapFactor);
	///////	
	m_TranY		= DlgLMat.m_TranY;
	pObjectMgr->SCtoDS(&m_TranY);
	m_TranY *= (dWorldBase/dMapFactor);
	///////	
	m_TranZ		= DlgLMat.m_TranZ;
	pObjectMgr->SCtoDS(&m_TranZ);
	m_TranZ *= (dWorldBase/dMapFactor);
	////////////////////////////////////////RotPt Coordinates 
/*	
	int index	= pObjectMgr->GetObjectIndexfromKey(PATCH,m_Dirty,1);
	if(index<0)
	{
		AfxMessageBox("Internal Problem:Dlg_PPos/LMat");
		return;
	}
	////////////
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
	{
		AfxMessageBox("Internal Problem:Dlg_PObj/LMat");
		return;
	}
	/////////////////	
	CDListMgr*	pList = pDrPatch->GetCNodeList();
*/
	/////////////	
	WORLD LocR;
	/////////////////////////////////////////////
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int index = pDListMgr->GetObjectIndex(NODE,m_RotPtID);
	if(index<0)
	{
		AfxMessageBox("Internal Problem:Dlg_PPos/LMat");
		return;
	}
	////////////	
	CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
	//////////
	LocR = *(pNode->GetLocalPos());			    
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	C3DMath	Math3D;
	CXForm	XForm;
	//////////
	MATRIX TM;			// to translate by RotPT
	pMATRIX pTM = &TM;
	Math3D.GetIdentityMATRIX(pTM);
	XForm.Translate(pTM,-LocR.x,-LocR.y,-LocR.z,XF_REPLACE);
	//////////////////////////////////////////////////
	pMATRIX pM = &m_LM;
	Math3D.GetIdentityMATRIX(pM);
	/////////////////////////////
	XForm.Rotate_X(pM,m_RotX,XF_REPLACE);
	XForm.Rotate_Y(pM,m_RotY,XF_REPLACE);
	XForm.Rotate_Z(pM,m_RotZ,XF_REPLACE);
	XForm.Scale(pM,m_ScaleX,m_ScaleY,m_ScaleZ,XF_REPLACE);
	XForm.Translate(pM,m_TranX,m_TranY,m_TranZ,XF_REPLACE);
	////////////////////////////////////////////////////
	Math3D.F_MultMATRIX(pM,pTM,pM);
	//////////////////////////////

}

void CDlg_PObj::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Oid;
	//////////////////////////////////////////////////////// 
	CDrObject* pObject;
	CString	TextID,TypeID;
	//////////////////////////////////////////////////////// Over All Lists
	for(int j = 0;j<MAX_LIST_ARRAY;j++)
	{
		CDListMgr* pDListMgr 	= pObjectMgr->GetObjectListFromIndex(j);
		////////////////////
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			////////////////////////////////////////
			if(!(pObject->IsPosted()) )             // Only with POSTED
				continue;
			////////////////////////////////////
			int nType = pObject->GetObjectType();
			////////////////////////////////////////// get index 
			int i;
			//////
			for (i = 0; i<nMax_ElemTypes; i++)
			{
				if(nType == ElTypes[i].num)
				{
					TypeID = ElTypes[i].ObjName; 
					break;
				}
			} 
			for (i = 0; i<nMax_CurveTypes; i++)
			{
				if(nType == CuTypes[i].num)
				{
					TypeID = CuTypes[i].ObjName; 
					break;
				}
			} 
			for (i = 0; i<nMax_PatchTypes; i++)
			{
				if(nType == PaTypes[i].num)
				{
					TypeID = PaTypes[i].ObjName; 
					break;
				}
			} 
			for (i = 0; i<nMax_SolidTypes; i++)
			{
				if(nType == SoTypes[i].num)
				{
					TypeID = SoTypes[i].ObjName; 
					break;
				}
			} 
			 //////////////////////////////////
			TextID   = pObject->GetObjectID() + '/' + TypeID;
			/////////////////////////////////////////////////        	
			((CListBox*)(pWndCtrl))->AddString(TextID);
		}
   	}
    
}
    
void CDlg_PObj::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
 
void CDlg_PObj::SetInfoForDataBase(CDrObj3D* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pSolidList	= pDrObject->GetSolidList();
	CDListMgr* pPatchList	= pDrObject->GetPatchList();
	CDListMgr* pCurveList	= pDrObject->GetCurveList();
	////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems,index,nLen,nType;  
	CString TextID,ElemID,TypeID;
    /////////////////
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems )
	{ 
		for (i=0;i<nMaxListItems;i++)
		{
			((CListBox*)(pWndCtrl))->GetText(i,TextID);
			/////////////////////////////////////////// decipher
			nLen  	= TextID.GetLength();
			index 	= TextID.Find( '/' );
			ElemID 	= TextID.Left(index);
			TypeID	= TextID.Right(nLen - (index+1) );
			////////////////////////////////////////// get index 
			for (int i = 0; i<nMax_ElemTypes; i++)
			{
				if(TypeID == ElTypes[i].ObjName)
				{
					nType = ElTypes[i].num; 
					break;
				}
			} 
			//////////////////////////////////////////////////
			pDListMgr	= pObjectMgr->GetObjectList(nType);
			////////////////////
			index = pDListMgr->GetObjectIndex(nType,ElemID);
			if(index>=0)
			{
				CDrObject* pObject = (CDrObject*)(pDListMgr->GetObject(index));
				/////////////////////////////////////////////
				if(nType == SOLID)
					pSolidList->InsertObject(pObject);
				else	
				if(nType == PATCH)
					pPatchList->InsertObject(pObject);
				else	
				if(nType == CURVE)
					pCurveList->InsertObject(pObject);
				/////////////////////////////////////////////// reciprocate	
				pObject->GetObj3DList()->InsertObject(pDrObject); 
			}
		}
	}
	////////////////////////////////////////////////////////////////////////// save
	pDListMgr->InsertObject(pDrObject); 
	////////////////////////////////////
    pDrObject->SetObjectType((int)OBJ3D);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_OID_Post);	
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
 


