// dlg_ppos.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_View.h"
/////////////////////
#include "3DMath.h"
#include "XForm.h"
////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Ext_Elem.h"
#include "DrNode.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
/////////////////////
#include "dlg_LTyp.h"
#include "dlg_LALL.h"
//#include "dlg_LDir.h"
#include "dlg_LSYT.h"
#include "dlg_LSYM.h"
#include "dlg_LSY3.h"
/////////////////////
#include "dlg_Rend.h"
#include "dlg_ppos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PPost dialog


CDlg_PPost::CDlg_PPost(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PPost::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_PPost)
	m_Dirty 		= "";
	m_Elem 			= "";
	m_Orient 		= "AntiClock";
	m_SubDiv 		= "None";
	m_bRend 		= TRUE;
	m_PID_Post		= "";
	m_bIdentity		= TRUE;
	//}}AFX_DATA_INIT
	m_OrientKind	= OT_ANTICLOCK;
	m_SubDivKind	= SU_NOSUB;
	
}

void CDlg_PPost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PPost)
	DDX_CBString(pDX, IDC_DIRTYPATCH, m_Dirty);
	DDX_CBString(pDX, IDC_FEMS, m_Elem);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_CBString(pDX, IDC_SUBDIV, m_SubDiv);
	DDX_Check(pDX, IDC_DEFAULT_REND, m_bRend);
	DDX_Text(pDX, IDC_PID_POST, m_PID_Post);
	DDX_Check(pDX, IDC_DEFAULT_LMAT, m_bIdentity);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_PPost, CDialog)
	//{{AFX_MSG_MAP(CDlg_PPost)
	ON_BN_CLICKED(IDC_SYMM, OnSymm)
	ON_BN_CLICKED(IDC_XFORM, OnXform)
	ON_BN_CLICKED(IDC_RENDINFO, OnRendinfo)
	ON_CBN_SELCHANGE(IDC_ORIENT, OnSelchangeOrient)
	ON_CBN_SELCHANGE(IDC_SUBDIV, OnSelchangeSubdiv)
	ON_CBN_SELCHANGE(IDC_FEMS, OnSelchangeFems)
	ON_BN_DOUBLECLICKED(IDC_SYMM, OnSymm)
	ON_BN_DOUBLECLICKED(IDC_XFORM, OnXform)
	ON_BN_DOUBLECLICKED(IDC_RENDINFO, OnRendinfo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_DEFAULT_LMAT, OnDefaultLmat)
	ON_BN_DOUBLECLICKED(IDC_DEFAULT_LMAT, OnDefaultLmat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_PPost message handlers

BOOL CDlg_PPost::OnInitDialog()
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
	pDListMgr	 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatch 	 = pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMaxPatch)
		FillPatchListAllString();   // only with DirtyPatch
	FillElemListAllString();		// only with 1D or 2D
	FillListAllString_Pool();	
	///////////////////////////////////////////////////////////
	m_bIdentity		= TRUE;
	m_nType			= -1;	// -1=None
							//  0=Symm(Pt+Normal)/2=XForms Based/1=Direct/3=Symm(3Pts)
	((CButton*)GetDlgItem(IDC_DEFAULT_LMAT))->SetCheck(m_bIdentity);
	((CButton*)GetDlgItem(IDC_DEFAULT_REND))->SetCheck(m_bRend);
	GetDlgItem(IDC_XFORM)->EnableWindow(!m_bIdentity);
	GetDlgItem(IDC_SYMM)->EnableWindow(!m_bIdentity);
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_PID_POST);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
	
}

void CDlg_PPost::OnRendinfo()
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

void CDlg_PPost::OnSelchangeOrient()
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


void CDlg_PPost::OnSelchangeSubdiv()
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

void CDlg_PPost::OnSelchangeFems()
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

void CDlg_PPost::OnDefaultLmat() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////////////////////////
	if(m_bIdentity == TRUE)
	{
		m_nType			= -1;	// -1=None
								//  0=Symm(Pt+Normal)/2=XForms Based/1=Direct/3=Symm(3Pts)
		GetDlgItem(IDC_XFORM)->EnableWindow(!m_bIdentity);
		GetDlgItem(IDC_SYMM)->EnableWindow(!m_bIdentity);
	}
	else
	{
		GetDlgItem(IDC_XFORM)->EnableWindow(!m_bIdentity);
		GetDlgItem(IDC_SYMM)->EnableWindow(!m_bIdentity);
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	
}

void CDlg_PPost::OnSymm() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_nType		= 0;
	m_bIdentity = FALSE;
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

void CDlg_PPost::OnXform() 
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
	m_bIdentity = FALSE;
	////////////
//	if(Dlg.m_nType == 2)
		return;
}

void CDlg_PPost::OnCancel()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CDialog::OnCancel();
}

void CDlg_PPost::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
   	/////////////////////////////////////////////// Profile ID
   	if("" == m_PID_Post)
   	{
   		AfxMessageBox("Please Select a Patch ID for Posting");
   		return;
   	}
	/////////////////////////////////////////////////////////// Get Info
	if(m_pMatObj)
		m_pMatObj = NULL;
	/////////////////////
	m_bIdentity = FALSE;
	/////////////////////
	if(m_nType == -1)			// No Transformation
	{
		///////////////////////////////
		m_pMatObj		= (CMatObj*)NULL;
		m_bIdentity		= TRUE;
	}
	else
	if(m_nType == 0)			// Symmetry: A Pt and the Normal
	{
		///////////////////////////////
		CDlg_LSym Dlg;
		Dlg.m_bInstanced = !m_bIdentity;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bIdentity		= !(Dlg.m_bInstanced);
	}
	else
	if(m_nType == 1)			// Direct
	{
/*
		CDlg_LDir Dlg;			// Direct Matrix
		/////////////////////////
		Dlg.m_bInstanced = !m_bIdentity;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bIdentity		= !(Dlg.m_bInstanced);
		/////////////
*/
	}
	else
	if(m_nType == 2)			// XForms
	{
		CDlg_LALL Dlg;			// TransformationBased
		/////////////////////////
		Dlg.m_bInstanced = !m_bIdentity;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bIdentity		= !(Dlg.m_bInstanced);
	}
	else
	if(m_nType == 3)			// Symmetry: 3 Pts
	{
		///////////////////////////////
		CDlg_LSy3 Dlg;
		Dlg.m_bInstanced = !m_bIdentity;
		Dlg.DoModal();
		m_pMatObj		= Dlg.m_pMatObj;
		m_bIdentity		= !(Dlg.m_bInstanced);
	}
	else
	{
		AfxMessageBox("ERROR:\nCDlg_PPost::OnOK\nInternal Problem!");
   		return;
	}
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrPatch* pAdd 	= (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
    SetInfoForDataBase(pAdd);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrPatch Nodes which IS NOT  YET INTERPOLATED
	///////////////////////////////////////////////////////// 
	pAdd->SetShow(FALSE);
	///////////////
	CDialog::OnOK();
}

void CDlg_PPost::FillListAllString_Pool()
{
	// with PATCHES
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	////////////////////////////////////////////////////////
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(PATCH);
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
		if( pObject->GetObjectType() == PATCH)
		{ 
			CDrPatch* pNode = (CDrPatch*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}


void CDlg_PPost::FillPatchListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
	CString Pid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatch = pDListMgr->GetSpecificObjectCount(PATCH);
    if(nMaxPatch>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == PATCH)
			{ 
				CDrPatch* pPatch = (CDrPatch*)pObject;
				if(pPatch->IsDirty())			// Only with DirtyPatch
				{
	   				Pid   = pPatch->GetObjectID();
			    	((CComboBox*)(pWndCtrl))->AddString(Pid);
			    }	 
			}			    
    	}
	} 
    
}

void CDlg_PPost::FillElemListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
    		if(nObjDim <1 || nObjDim >2) // only with 1D or 2D 
    			continue;  
			/////////////
			strElem = ElTypes[i].ObjName;
			((CComboBox*)(pWndCtrl))->AddString(strElem);
  		}
	} 
    
}
    
void CDlg_PPost::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
 
void CDlg_PPost::SetInfoForDataBase(CDrPatch* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pCNodeList	= pDrObject->GetCNodeList();
	CString DirtyPid;
	CDrPatch* pDirtyP;
	///////////////////////////////////////////////////// GetDirtyPatch
	CWnd* pWndCtrl = GetDlgItem(IDC_DIRTYPATCH);
    int index;  
    /////////////////
	index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	((CComboBox*)(pWndCtrl))->GetLBText(index,DirtyPid);
	//////////////////////////////////
	index = pObjectMgr->GetObjectIndexfromKey(PATCH,DirtyPid,1);
	if(index>=0)
	{
		CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
		pDirtyP = (CDrPatch*)(pDListMgr->GetObject(index));
	}
	////////////////////////////////////////////////////// Put in THE list
//	pObjectList->InsertObject(pDrObject);// done in OK	
	////////////////////////////////////////////////////// clone
	pDrObject->SetObjectInfo(pDirtyP);
	////////////////////////////////////////////////////// Reciprocate
	CDListMgr* pList;
	POSITION pos;
	pList = pDrObject->GetCNodeList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
		///////////////////////////
		pNode->GetPatchList()->InsertObject(pDrObject);
		///////////////////////////
	}
	////////////////////////////////////////////////////// Add AddlInfo
	int nObjNo = pDrObject->GetObjectNo();;
	///////////////////////////////////////
	pDrObject->SetPatchProc(PP_POST);	
	pDrObject->SetObjectNo(nObjNo);	
	pDrObject->SetObjectID(m_PID_Post);
	pDrObject->SetInstanced(!m_bIdentity);
	pDrObject->SetMatObj(m_pMatObj);	
	pDrObject->SetParentID(DirtyPid);	
	pDrObject->SetSubDiv(m_SubDivKind);
	pDrObject->SetOrient(m_OrientKind);
	pDrObject->SetDirty(FALSE);
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals 
    pDrObject->SetLevelType((int)LEVEL_DADDY);         // globals
    //////////////////////////////
//	BOOL		m_bRend;
	pDrObject->SetRInfo(&m_RI);
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
