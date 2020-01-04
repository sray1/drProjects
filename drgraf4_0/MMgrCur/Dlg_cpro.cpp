// dlg_cpro.cpp : implementation file
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
#include "DrNode.h"
#include "DrCurve.h"
#include "DrProf_C.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "dlg_LMTR.h"
#include "dlg_LMR.h"
#include "dlg_pLMC.h"

#include "CommRsrc.h"
#include "dlg_cpro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CPro dialog


CDlg_CPro::CDlg_CPro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CPro::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CPro)
	m_CPro_ID 	= "";
	m_Orient = _T("");
	//}}AFX_DATA_INIT
	m_End_NID	= "";
	m_FromID	= "";
	m_ToID 		= "";
	m_bLMat		= FALSE;
	m_bCur_Ist	= TRUE;
	/////////////////////////////
	C3DMath	Math3D;
	Math3D.GetIdentityMATRIX(&m_LocalM);	// Cumulative Matrix
	////////////////////////////////////
}

void CDlg_CPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CPro)
	DDX_Text(pDX, IDC_CID_PROF, m_CPro_ID);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CPro, CDialog)
	//{{AFX_MSG_MAP(CDlg_CPro)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	ON_BN_CLICKED(IDC_DEFAULT_LMAT, OnDefaultLmat)
	ON_BN_DOUBLECLICKED(IDC_DEFAULT_LMAT, OnDefaultLmat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CPro message handlers

BOOL CDlg_CPro::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
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
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxNodes)
		FillListAllString_Pool();   // only with Curves
	pDListMgr	= pObjectMgr->GetObjectList(C_PROFILE);
	int nMaxCProfs 	 = pDListMgr->GetSpecificObjectCount(C_PROFILE);
	if(nMaxCProfs)
		FillListAllString_Profile();   // only with C_Profiles
   	///////////////////////////////////
	GetDlgItem(IDD_LATCHLIST)->EnableWindow(FALSE);		// Always Disabled
   	////////
	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(1);		// 1 = FORWARD /0 = BACKWARD
	///////////////////////////////////////////////////////////
	GetDlgItem(IDC_CID_PROF)->SetFocus();
	///////////////////////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CPro::OnDefaultLmat() 
{
	m_bLMat		= !m_bLMat;
}

void CDlg_CPro::OnDel()
{
	//delete current selection from SelectList	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
   	{
		((CListBox*)(pWndCtrl))->DeleteString(index);
		////////
		pWndCtrl = GetDlgItem(IDD_LATCHLIST);
		((CListBox*)(pWndCtrl))->DeleteString(index);
		///////////////////////////////////////////// delete matrix from the List
		m_LMList.DeleteObject(index);
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CPro::OnAdd()
{
	// Add Current selection of POOLLIST to SELECTLIST
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE) 
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	BOOL	bInstanced = m_bLMat;
	///////////////
	CListBox* pWndPul = (CListBox*)GetDlgItem(IDD_POOLLIST);
	CListBox* pWndSel = (CListBox*)GetDlgItem(IDD_SELECTLIST);
	CListBox* pWndLat = (CListBox*)GetDlgItem(IDD_LATCHLIST);
	/////////////////////////////////////////////////// Curve Latch Orientation
	m_CuLat = CL_FORWARD;
	if(m_Orient == "BACKWARD")
		m_CuLat = CL_BACKWARD;
	/////////////////////////////////////////////////// Make sure of Connectivity
    int nMaxSel;  
    nMaxSel = pWndSel->GetCount();
    if(nMaxSel<=0)
		m_bCur_Ist= TRUE;
	else	
		m_bCur_Ist= FALSE;
	///////////////////////////////////////////////////////////// set Selection	
	int index = pWndPul->GetCurSel();
	CString CNid;
	if(index>=0)
	{
		pWndPul->GetText(index,CNid);
		////////////////////////////////////// Duplication Warning
		if( (pWndSel->FindString(-1,CNid) ) >=0)	// already selected:
		{
			int nAnswer = 
			AfxMessageBox("Do You Want to Select this Curve Again?",MB_YESNO|MB_ICONQUESTION);
			if(nAnswer == IDNO)
				return; //
			else	// force Transformation
			{
				/////////////////// 
				bInstanced 	= TRUE;
				pWndSel->AddString(CNid);
				pWndLat->AddString(m_Orient);
			}
		}
		else		
		{
			///////////////////////// 
			pWndSel->AddString(CNid);
			pWndLat->AddString(m_Orient);
		}
	}
	////////////////////////////////////////////////////////////
	// Find Begin or End Node of Current Curve Based on CuLatch
	////////////////////////////////////////////////////////////
	if((index= pObjectMgr->GetObjectIndexfromKey(CURVE,CNid,1)) <0)
	{
		AfxMessageBox("Internal Problem:CDlg_CPro::OnAdd");
		return;
	}
	////////////
	CDrNode* pNode;
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDrCurve* pCurve = (CDrCurve*)pDListMgr->GetObject(index);
	CDListMgr* pList = pCurve->GetCNodeList();
	if(!pList->IsEmpty())
	{
		if(m_CuLat == CL_FORWARD)
			pNode = (CDrNode*)pList->GetHead();
		else
			pNode = (CDrNode*)pList->GetTail();
	}
	else
	{
		AfxMessageBox("Internal Problem:CDlg_CPro::OnAdd\nEmptyList");
		return;
	}
	///////////////////////////////// Set Begin Pt. as RotPt
	m_RotPtID = pNode->GetObjectID();
	//////////////////////////////////////////////////// NO Transform
	if(!bInstanced)
	{
		if(m_bCur_Ist)
		{
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			///////////////////////////////
			pMatObj->SetInstanced_Prof(bInstanced);
			//////////////////////////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			pMatObj->SetMatrix(pM);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
		}
		else		// Force atleast Translation to EndPt
		{
			bInstanced = TRUE;
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			///////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			/////////////////////////////
			GetTranslations();
			SetUpLocalm(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			////////////////////////////////// Save
			pMatObj->SetInstanced_Prof(bInstanced);
			pMatObj->SetMatrix(pM);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
		}
	}
	//////////////////////////////////////////////////// YES Transform
	else
	{
		if(m_bCur_Ist)
		{
			/////////////
			FirstCurve();	// Ist Curve: Allow Both Tran & Rot	
			/////////////
		}
		else
		{
			////////////////
			NonFirstCurve();// NonIst Curve: Allow only Rot	
			////////////////
		}
	}
	//////////////////////////////////////////////////// Find End Node of Curve
	if((index= pObjectMgr->GetObjectIndexfromKey(CURVE,CNid,1)) <0)
	{
		AfxMessageBox("Internal Problem:CDlg_CPro::OnAdd");
		return;
	}
	////////////
	pCurve = (CDrCurve*)pDListMgr->GetObject(index);
	pList = pCurve->GetCNodeList();
	if(!pList->IsEmpty())
	{
		if(m_CuLat == CL_FORWARD)
			pNode = (CDrNode*)pList->GetTail();
		else
			pNode = (CDrNode*)pList->GetHead();
	}
	else
	{
		AfxMessageBox("Internal Problem:CDlg_CPro::OnAdd\nEmptyList");
		return;
	}
	///////////////////////////////// Update EndNode
	m_End_NID = pNode->GetObjectID();
	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
	///////////////////	
	return;
}

void CDlg_CPro::FirstCurve()
{
	C3DMath Math3D;
	BOOL	bInstanced;	
	////////////////////////////// Ist Curve: Allow Both Tran & Rot	
	if(m_bCur_Ist)
	{
		CDlg_LMTR DlgLMTR;
		DlgLMTR.m_RotPtID = m_RotPtID;
		////////////////////////////////
		if(DlgLMTR.DoModal() == IDCANCEL)
		{
			bInstanced = FALSE;
			//////////////////////////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			///////////////////////////////
			pMatObj->SetInstanced_Prof(bInstanced);
			pMatObj->SetMatrix(pM);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
			UpdateData(FALSE);		    //TO Screen(FALSE)    
			///////////////////	
			return;
		}
		else
		{
			//////////////////////////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			///////////////////////////////
			bInstanced 	= TRUE; 				// default is FALSE
			///////////////////////
			m_TranPtID	= DlgLMTR.m_TranPtID;
//			m_RotPtID	= DlgLMTR.m_RotPtID;
			m_FromID	= DlgLMTR.m_FromID;
			m_ToID		= DlgLMTR.m_ToID;
	
			m_RotX		= DlgLMTR.m_RotX;
			m_RotY		= DlgLMTR.m_RotY;
			m_RotZ		= DlgLMTR.m_RotZ;
			m_TranX		= DlgLMTR.m_TranX;
			m_TranY		= DlgLMTR.m_TranY;
			m_TranZ		= DlgLMTR.m_TranZ;
			//////////////////////////////////////////////////////// save in MatObj
			m_savRot.x 	= m_RotX; 
			m_savRot.y 	= m_RotY; 
			m_savRot.z 	= m_RotZ; 
			////////////////////// Set Up Local Matrix
			SetUpLocalm(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			////////////////////// Save	
			pMatObj->SetInstanced_Prof(bInstanced);
			pMatObj->SetMatrix(pM);
			pMatObj->SetFromID(m_FromID);
			pMatObj->SetToID(m_ToID);
			pMatObj->SetTranPtID(m_TranPtID);
			pMatObj->SetRotPtID(m_RotPtID);
			pMatObj->SetRotation(m_savRot);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
			UpdateData(FALSE);		    //TO Screen(FALSE)    
			///////////////////	
			return;
		}
	}
    ///////////////////	
}

void CDlg_CPro::NonFirstCurve()
{
	C3DMath Math3D;
	BOOL	bInstanced = TRUE;	// ALWAYS for NonFirstCurves
	////////////////////////////// NonIst Curve: Allow Only Rot	
	if(!m_bCur_Ist)
	{
		CDlg_LMR DlgLMR;
		////////////////
		DlgLMR.m_RotPtID = m_RotPtID;
		////////////////////////////////
		if(DlgLMR.DoModal() == IDCANCEL)
		{
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			pMatObj->SetInstanced_Prof(bInstanced);
			//////////////////////////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			pMatObj->SetMatrix(pM);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
			UpdateData(FALSE);		    //TO Screen(FALSE)    
			///////////////////	
			return;
		}
		else
		{
			//////////////////////////////////////////////////// save in the List
			CMatObj* pMatObj = new CMatObj;
			//////////////////////////////////////////////////
			MATRIX LM;
			pMATRIX pM 	= &LM;
			Math3D.GetIdentityMATRIX(pM);
			///////////////////////////////
//			m_RotPtID	= DlgLMR.m_RotPtID;
			m_FromID	= DlgLMR.m_FromID;
			m_ToID		= DlgLMR.m_ToID;
	
			m_RotX		= DlgLMR.m_RotX;
			m_RotY		= DlgLMR.m_RotY;
			m_RotZ		= DlgLMR.m_RotZ;
			/////////////////////////////////////// save in MatObj
			m_savRot.x 	= m_RotX; 
			m_savRot.y 	= m_RotY; 
			m_savRot.z 	= m_RotZ;
			/////////////////////////////////////// ALWAYS Translate
												 // to Previous End
			GetTranslations();
			////////////////////// Set Up Local Matrix
			SetUpLocalm(pM);
			/////////////////////////////// Update Cumul Matrix
//			Math3D.F_MultMATRIX(&m_LocalM,pM,&m_LocalM);
			m_LocalM = *pM;
			////////////////////// Save	
			pMatObj->SetInstanced_Prof(bInstanced);
			pMatObj->SetMatrix(pM);
			pMatObj->SetFromID(m_FromID);
			pMatObj->SetToID(m_ToID);
			pMatObj->SetTranPtID(m_TranPtID);
			pMatObj->SetRotPtID(m_RotPtID);
			pMatObj->SetRotation(m_savRot);
			pMatObj->SetCurveLatch(m_CuLat);
			/////////////////////////////// save in the list
			m_LMList.InsertObject(pMatObj);
			////////////////////
			UpdateData(FALSE);		    //TO Screen(FALSE)    
			///////////////////	
			return;
		}
	}
    ///////////////////	
}

void CDlg_CPro::SetUpLocalm(pMATRIX pM)
{
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
			/////////////////////////////////// strip Scale Factor (World Coord)
	pObjectMgr->SCtoDS(&m_TranX);
	m_TranX *= (dWorldBase/dMapFactor);
	pObjectMgr->SCtoDS(&m_TranY);
	m_TranY *= (dWorldBase/dMapFactor);
	pObjectMgr->SCtoDS(&m_TranZ);
	m_TranZ *= (dWorldBase/dMapFactor);
	////////////////////////////////////////RotPt Coordinates
	WORLD LocR;
	int index;
	/////////////////////////////////////////////
	index = pDListMgr->GetObjectIndex(NODE,m_RotPtID);
	if(index<0)			// No Rotation
	{
		LocR.x = 0.0;
		LocR.y = 0.0;
		LocR.z = 0.0;
	}
	else
	{	
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////
		LocR = *(pNode->GetLocalPos());
	}				    
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM;			// to translate by RotPT
	pMATRIX pTM = &TM;
	Math3D.GetIdentityMATRIX(pTM);
	///////////////////////////////////////////////////////// Rotation
	XForm.Translate(pTM,-LocR.x,-LocR.y,-LocR.z,XF_REPLACE);
	/////////////////////////////////////
	XForm.Rotate_X(pM,m_RotY,XF_PREMULT);
	XForm.Rotate_Y(pM,m_RotX,XF_PREMULT);
	XForm.Rotate_Z(pM,m_RotZ,XF_PREMULT);
	XForm.Translate(pM,m_TranX,m_TranY,m_TranZ,XF_PREMULT); // translate back
	////////////////////////////////////////////////////
	Math3D.F_MultMATRIX(pM,pTM,pM);
	///////////////////////////////
	return;
}

void CDlg_CPro::GetTranslations() 
{
	CXForm	XForm(TRUE);
	////////////////////
	CString Nid;
	Nid = m_End_NID;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
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
	WORLD LocT;
	int index;
	//////////////
	if(pDListMgr)
	{	
		/////////////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// 
		LocT 	= *(pNode->GetLocalPos());
		//////////////////////////////// Update By CumulMatrix
		XForm.Transform(&LocT,&LocT,&m_LocalM);
		//////////////////////////////// scale etc
		LocT.x /= (dWorldBase/dMapFactor);
		LocT.y /= (dWorldBase/dMapFactor);
		LocT.z /= (dWorldBase/dMapFactor);
		pObjectMgr->DStoSC(&LocT.x);
		pObjectMgr->DStoSC(&LocT.y);
		pObjectMgr->DStoSC(&LocT.z);
	}
	////////////////////////////////////// Fill Edits
	m_TranX 	= LocT.x;
	m_TranY 	= LocT.y;
	m_TranZ 	= LocT.z;
	m_TranPtID 	= Nid;
	//////////////////
	return;	
}

void CDlg_CPro::EmptyListAllString(UINT DlgID)
{
			 
	CWnd* pWndCtrl = GetDlgItem(DlgID);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_CPro::OnOK()
{
	// DONE
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	//	 Check first If Adequate Number of Curves: AtLeast 1
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int nCount = ((CListBox*)pWndCtrl)->GetCount();
   	/////////////////////////////////////////////// Minimum Required
   	int nMinCNode = 1; // m_nHowMany = 1
   	////////////////////////	
   	if(nCount < nMinCNode)
   	{
   		CString str;
   		char buf[100];
   		sprintf(buf,"Atleast  1 Curve Required\nNone Selected!"	);
   		AfxMessageBox(str = buf);
   		return;
   	}
   	/////////////////////////////////////////////// Profile ID
   	if("" == m_CPro_ID)
   	{
   		AfxMessageBox("Please Select a Profile ID");
   		return;
   	}
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrProf_C* pAdd 	= (CDrProf_C*)(pObjectMgr->AddToDataBase(nActiveIndex,C_PROFILE));
    SetInfoForDataBase(pAdd);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrProf_C which IS NOT  YET INTERPOLATED
	///////////////////////////////////////////////////////// 
	pAdd->SetShow(FALSE);
	////////////////////////////////////////////////////////// Put in ProfileList
//	pWndCtrl = GetDlgItem(IDD_LIST);
//	pWndCtrl->EnableWindow(TRUE);
// 	((CListBox*)(pWndCtrl))->AddString(m_CPro_ID);
//	pWndCtrl->EnableWindow(FALSE);
	///////////////
	CDialog::OnOK();
}

void CDlg_CPro::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_CPro::FillListAllString_Pool()
{
	// with CURVES
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	////////////////////////////////////////////////////////
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(CURVE);
    if(nMaxNodes<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pNode = (CDrCurve*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}
    
void CDlg_CPro::FillListAllString_Profile()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(C_PROFILE);
	//////////////////////////////////////////////////////
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(C_PROFILE);
    if(nMaxCurves<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Cid;
    //////////////////////////////////////////////////////////	
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == C_PROFILE)
		{ 
			CDrProf_C* pCurve = (CDrProf_C*)pObject;
			Cid   = pCurve->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}

void CDlg_CPro::SetInfoForDataBase(CDrProf_C* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pDListMgr;
	CDListMgr* pCurveList	= pDrObject->GetCurveList();
	CDListMgr* pLMList		= pDrObject->GetLMList();
	//////////////////
	CWnd* pWndCtrl 			= GetDlgItem(IDD_SELECTLIST);
    int i,nData,index;  
	CString Nid;
	CDrCurve* pDrCurve;
	////////////////////////////////////
    pDrObject->SetObjectType((int)C_PROFILE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CPro_ID);	
    ////////////////////////////////////////////////////////////////////	
    nData = ((CListBox*)(pWndCtrl))->GetCount();
    /////////////////
	for (i=0;i<nData;i++)
	{
		((CListBox*)(pWndCtrl))->GetText(i,Nid);
		//////////////////////////////////
		index = pObjectMgr->GetObjectIndexfromKey(CURVE,Nid,1);
		pDListMgr	= pObjectMgr->GetObjectList(CURVE);
		if(index>=0)
		{
			pDrCurve = (CDrCurve*)(pDListMgr->GetObject(index));
			pCurveList->InsertObject(pDrCurve);
			////////////////////////////////// save curve
			pDrCurve->GetCProfList()->InsertObject(pDrObject);
		}
	}
	////////////////////////////////////////////////////////// Matrix Info
	pLMList->AddTail(&m_LMList);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
