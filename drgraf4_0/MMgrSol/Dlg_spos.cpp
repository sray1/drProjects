// dlg_ppos.cpp : implementation file
//

#include "stdafx.h"


#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_View.h"
////////////////////
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
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
#include "DrPatch.h"
#include "DrSolid.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
/////////////////////
#include "dlg_LMat.h"
#include "dlg_Rend.h"

#include "MCurRsrc.h"

#include "dlg_Spos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SPost dialog


CDlg_SPost::CDlg_SPost(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SPost::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_SPost)
	m_Dirty 		= "";
	m_Elem 			= "";
	m_Orient 		= "AntiClock";
	m_SubDiv 		= "NONE";
	m_bLMat 		= TRUE;
	m_bRend 		= TRUE;
	m_PID_Post = "";
	//}}AFX_DATA_INIT
	m_OrientKind	= OT_ANTICLOCK;
	m_SubDivKind	= SU_NOSUB;
	
}

void CDlg_SPost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SPost)
	DDX_CBString(pDX, IDC_DIRTYPATCH, m_Dirty);
	DDX_CBString(pDX, IDC_FEMS, m_Elem);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_CBString(pDX, IDC_SUBDIV, m_SubDiv);
	DDX_Check(pDX, IDC_DEFAULT_LMAT, m_bLMat);
	DDX_Check(pDX, IDC_DEFAULT_REND, m_bRend);
	DDX_Text(pDX, IDC_PID_POST, m_PID_Post);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SPost, CDialog)
	//{{AFX_MSG_MAP(CDlg_SPost)
	ON_BN_CLICKED(IDC_LOCALM, OnLocalm)
	ON_BN_CLICKED(IDC_RENDINFO, OnRendinfo)
	ON_BN_DOUBLECLICKED(IDC_LOCALM, OnLocalm)
	ON_BN_DOUBLECLICKED(IDC_RENDINFO, OnRendinfo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_CBN_SELCHANGE(IDC_ORIENT, OnSelchangeOrient)
	ON_CBN_SELCHANGE(IDC_SUBDIV, OnSelchangeSubdiv)
	ON_CBN_SELCHANGE(IDC_FEMS, OnSelchangeFems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_SPost message handlers

BOOL CDlg_SPost::OnInitDialog()
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
	/////////////////////////////////////////////
	pDListMgr		= pObjectMgr->GetObjectList(SOLID);
	int nMaxPatch 	 = pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMaxPatch)
		FillPatchListAllString();   // only with DirtySOLID
	FillElemListAllString();		// only with 1D or 2D or 3D
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
	
}

void CDlg_SPost::OnLocalm()
{
    ////////////////////
	UpdateData(TRUE);			//Update Data    
	///////////////////////////////////////
	if(m_Dirty == "")
	{
		AfxMessageBox(
			"Please Select a Solid from the Pool");
		return;
	}
	////////////////							
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
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
	DlgLMat.m_PatchID = m_Dirty;
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
	int index	= pObjectMgr->GetObjectIndexfromKey(PATCH,m_Dirty,1);
	if(index<0)
	{
		AfxMessageBox("Internal Problem:Dlg_SPos/LMat");
		return;
	}
	////////////	
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
	{
		AfxMessageBox("Internal Problem:Dlg_SPos/LMat");
		return;
	}
	/////////////////	
//	CDListMgr*	pList = pDrPatch->GetCNodeList();
	WORLD LocR;
	/////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	index = pDListMgr->GetObjectIndex(NODE,m_RotPtID);
	if(index<0)
	{
		AfxMessageBox("Internal Problem:Dlg_SPos/LMat");
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

void CDlg_SPost::OnRendinfo()
{
	CDlg_Rend DlgRend;
	//////////////////
	m_bRend 		= FALSE;
    ////////////////////
	UpdateData(FALSE);			//Update SCreen    
	////////////////////////////////////////////////////////////	
	if(DlgRend.DoModal() == IDOK)
	{
		/////////////////////////
		RGBCOLOR rgb;
		CS2RGBCOLOR(DlgRend.m_crColor_Refl,rgb);
		m_RI.R				= rgb.red;
		m_RI.G				= rgb.green;
		m_RI.B				= rgb.blue;
		if(m_RI.R >1.) m_RI.R = 1.;
		if(m_RI.G >1.) m_RI.G = 1.;
		if(m_RI.B >1.) m_RI.B = 1.;
		if(m_RI.R <0.) m_RI.R = 0.;
		if(m_RI.G <0.) m_RI.G = 0.;
		if(m_RI.B <0.) m_RI.B = 0.;
		///////////////////////////
		m_RI.diffusion		= DlgRend.m_Diff_Coef;
		m_RI.specIndex		= DlgRend.m_SpecIndex;
		///////////
		CS2RGBCOLOR(DlgRend.m_crColor_Fram,rgb);
		m_RI.frameColor 	= rgb;
		///////////
		CS2RGBCOLOR(DlgRend.m_crColor_Ambi,rgb);
		m_RI.ambientColor 	= rgb;
		//////////////////////
		m_RI.turbulence		= DlgRend.m_bTurbul;
		m_RI.wireframed		= DlgRend.m_bWireF;
		m_RI.ambientEffect	= DlgRend.m_bAmb;
		m_RI.culling		= DlgRend.m_bCull;
		m_RI.distanceEffect	= DlgRend.m_bDist;
		m_RI.framed			= DlgRend.m_bFrame;
		m_RI.hazing			= DlgRend.m_bHazing;
		m_RI.lightSource	= DlgRend.m_bLight;
		m_RI.shadow			= DlgRend.m_bShadow;
		///////////
		m_RI.specularity	= DlgRend.m_Spec_Coef;
		m_RI.refraction		= DlgRend.m_Refr_Coef;
		m_RI.absorption		= DlgRend.m_Absorp;
		m_RI.transmission	= DlgRend.m_Transm_Coef;
//		m_RI.texture;			// texture type code						
//		m_RI.tx[TXLIMIT];
	}	
	////////////////////
}

void CDlg_SPost::OnSelchangeOrient()
{
	////////////////////////////////////////////////  Set Unit
	CString Names[] = {"AntiClock","ClockWise","DualSided"};
//	UINT	nOrientCount  = sizeof(Names)/sizeof(Names[0]);
	///////////////////////////////////
	UpdateData(TRUE);
	/////////////////	
	if(m_Orient == Names[0])
       	m_OrientKind = OT_ANTICLOCK;
	else		 
	if(m_Orient == Names[1])
       	m_OrientKind = OT_CLOCKWISE;	 
	else		 
	if(m_Orient == Names[2])
       	m_OrientKind = OT_DUALSIDED;
	/////////////////////////////       		 
}


void CDlg_SPost::OnSelchangeSubdiv()
{
	////////////////////////////////////////////////  Set Unit
	CString Names[] = {"None","Once","Twice","Auto"};
	///////////////////////////////////
	UpdateData(TRUE);
	/////////////////	
	if(m_SubDiv == Names[0])
       	m_SubDivKind = SU_NOSUB;
	else		 
	if(m_SubDiv == Names[1])
       	m_SubDivKind = SU_ONCE;	 
	else		 
	if(m_SubDiv == Names[2])
       	m_SubDivKind = SU_TWICE;
	else		 
	if(m_SubDiv == Names[3])
       	m_SubDivKind = SU_AUTO;
	/////////////////////////////       		 
	
}

void CDlg_SPost::OnSelchangeFems()
{
/*
    CString strElem;
	CWnd* pWndCtrl = GetDlgItem(IDC_FEMS);
    int index;  
    /////////////////
	index = ((CListBox*)(pWndCtrl))->GetCurSel();
	((CListBox*)(pWndCtrl))->GetText(index,strElem);
	////////////////
    if(nMax_ElemTypes<=0)		// elglobal.h
    	return;
    ///////////	
   	for(int i =0; i<nMax_ElemTypes; i++)
   	{
		if(strElem == ElTypes[i].ObjName)
		{
			if(ElTypes[i].num == PIPE)
			{
//				UINT	DoModal_Pipe(1); 		// todo
			}
			else
			if(ElTypes[i].num == PLATE)
			{
//				UINT 	DoModal_Plat(int nPlatTypeIndex,int nHowMany);
			}
   		}		 
		/////////////
	}
*/	
}

void CDlg_SPost::OnCancel()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CDialog::OnCancel();
}

void CDlg_SPost::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrSolid* pAdd 	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
    SetInfoForDataBase(pAdd);
	///////////////
	CDialog::OnOK();
}

void CDlg_SPost::FillPatchListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
	CString Pid;
	
	int nMaxPatch = pDListMgr->GetSpecificObjectCount(SOLID);
    if(nMaxPatch>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == SOLID)
			{ 
				CDrSolid* pPatch = (CDrSolid*)pObject;
				if(pPatch->IsDirty())			// Only with DirtyPatch
				{
	   				Pid   = pPatch->GetObjectID();
			    	((CComboBox*)(pWndCtrl))->AddString(Pid);
			    }	 
			}			    
    	}
	} 
    
}

void CDlg_SPost::FillElemListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FE3D);
	//////////////////////////////////////////////////////
	CWnd* 	pWndCtrl = GetDlgItem(IDC_FEMS);
	int		nObjDim;
	CString	strElem;
	////////////////
    if(nMax_ElemTypes>0)		// elglobal.h
    {
    	for(int i =0; i<nMax_ElemTypes; i++)
    	{
    		nObjDim	= ElTypes[i].ObjDim;
    		if(nObjDim <1 || nObjDim >3) // only with 1D or 2D or 3D 
    			continue;  
			/////////////
			strElem = ElTypes[i].ObjName;
			((CComboBox*)(pWndCtrl))->AddString(strElem);
  		}
	} 
    
}
    
void CDlg_SPost::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
 
void CDlg_SPost::SetInfoForDataBase(CDrSolid* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pDListMgr;
	CDListMgr* pCNodeList	= pDrObject->GetCNodeList();
	CString DirtyPid;
	CDrPatch* pDirtyP;
	///////////////////////////////////////////////////// GetDirtySolid
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
    int index;  
    /////////////////
	index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	((CComboBox*)(pWndCtrl))->GetLBText(index,DirtyPid);
	//////////////////////////////////
	index = pObjectMgr->GetObjectIndexfromKey(SOLID,DirtyPid,1);
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	if(index>=0)
	{
		pDirtyP = (CDrPatch*)(pDListMgr->GetObject(index));
	}
	////////////////////////////////////////////////////// Put in THE list         Already IN 6/21/96
//	pDListMgr->InsertObject(pDrObject);	
	////////////////////////////////////////////////////// clone
	pDrObject->SetObjectInfo(pDirtyP);
	////////////////////////////////////////////////////// Add AddlInfo
	pDrObject->SetObjectID(m_PID_Post);
	pDrObject->SetSubDiv(m_SubDivKind);
	pDrObject->SetOrient(m_OrientKind);
	pDrObject->SetDirty(FALSE);
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals 
    pDrObject->SetLevelType((int)LEVEL_DADDY);         // globals
    //////////////////////////////
//	BOOL		m_bRend;
	pDrObject->SetRInfo(&m_RI);
	/////////
	pDrObject->SetInstanced(!m_bLMat);		
	if(!m_bLMat)		
		pDrObject->SetLocalTransform(&m_LM);		
    ///////////////////////////////////////////////////// Component Info
    CString strElem;
	pWndCtrl = GetDlgItem(IDC_FEMS);
    /////////////////
	index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	((CComboBox*)(pWndCtrl))->GetLBText(index,strElem);
	////////////////
    if(nMax_ElemTypes>0)		// elglobal.h
    {
    	for(int i =0; i<nMax_ElemTypes; i++)
    	{
			if(strElem == ElTypes[i].ObjName)
			{
    			int nObjDim	= ElTypes[i].ObjDim;
    			///////////
   				pDrObject->SetMeshElemDim(nObjDim);
    			pDrObject->SetCompoType(ElTypes[i].num);
    				
    		}		 
			/////////////
  		}
	} 
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
/////////////////////////////// end of Module ///////////////
