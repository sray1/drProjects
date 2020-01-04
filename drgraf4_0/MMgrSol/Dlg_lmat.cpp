// dlg_lmat.cpp : implementation file
//

#include "stdafx.h"

/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "dlg_lmat.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LMat dialog


CDlg_LMat::CDlg_LMat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LMat::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LMat)
	m_RotX 		= 0;
	m_RotY 		= 0;
	m_RotZ 		= 0;
	m_ScaleX 	= 1;
	m_ScaleY 	= 1;
	m_ScaleZ 	= 1;
	m_TranX 	= 0;
	m_TranY 	= 0;
	m_TranZ 	= 0;
	m_RotPtID 	= "";
	m_TranPtID 	= "";
	//}}AFX_DATA_INIT
}

void CDlg_LMat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LMat)
	DDX_Text(pDX, IDC_ROT_X, m_RotX);
	DDV_MinMaxDouble(pDX, m_RotX, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Y, m_RotY);
	DDV_MinMaxDouble(pDX, m_RotY, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Z, m_RotZ);
	DDV_MinMaxDouble(pDX, m_RotZ, -360., 360.);
	DDX_Text(pDX, IDC_SCALE_X, m_ScaleX);
	DDX_Text(pDX, IDC_SCALE_Y, m_ScaleY);
	DDX_Text(pDX, IDC_SCALE_Z, m_ScaleZ);
	DDX_Text(pDX, IDC_TRAN_X, m_TranX);
	DDX_Text(pDX, IDC_TRAN_Y, m_TranY);
	DDX_Text(pDX, IDC_TRAN_Z, m_TranZ);
	DDX_CBString(pDX, IDC_ROTPT, m_RotPtID);
	DDX_CBString(pDX, IDC_TRANPT, m_TranPtID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_LMat, CDialog)
	//{{AFX_MSG_MAP(CDlg_LMat)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_CBN_SELCHANGE(IDC_TRANPT, OnSelchangeTranPt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_LMat message handlers

BOOL CDlg_LMat::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////////
	CString IstID;
	FillListAllString(IDC_ROTPT,IstID);   // 
	CWnd* pWndCtrl;
	pWndCtrl 	= GetDlgItem(IDC_ROTPT);
	m_RotPtID 	= IstID;
	//////////////////////////////
	FillListAllString(IDC_TRANPT,IstID);   //
	((CComboBox*)pWndCtrl)->SetCurSel(0);
	pWndCtrl 	= GetDlgItem(IDC_TRANPT);
	m_TranPtID 	= IstID;
	((CComboBox*)pWndCtrl)->SetCurSel(0);
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}


int CDlg_LMat::FillListAllString(UINT DlgItemID,CString& IstID)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(DlgItemID);
	CString Nid;
	BOOL bGotStr = FALSE;
	///////////////////////// 
/*	
	int index	= pObjectMgr->GetObjectIndexfromKey(PATCH,m_PatchID,1);
	if(index>=0)
	{						
		CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
		if(!pDrPatch)
			return -1;
		/////////////////	
		CDListMgr*	pList = pDrPatch->GetCNodeList();
		/////////////////////////////////////////////
		if(pList)
		{
*/			
	if(pDListMgr)			// Allow All Nodes
	{
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			int nObjType = pObject->GetObjectType();
			if(nObjType != NODE)
				continue;
			////////////////	
			CDrNode* pNode = (CDrNode*)pObject;
   			Nid = pNode->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Nid);
	    	if(!bGotStr)
	    	{
	    		IstID = Nid;
	    		bGotStr !=bGotStr;
	    	}	
	    	/////////////////////////////////////////
		}	 
	}			    
	//////////
	return 0; 
    
}

void CDlg_LMat::OnSelchangeTranPt()
{
			 
	/////////////////
	UpdateData(TRUE);
	/////////////////
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
	WORLD LocR;
	int index;
	CString Nid;
	//////////////
	if(pDListMgr)
	{	

		CWnd* pWndCtrl = GetDlgItem(IDC_TRANPT);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocR 	= *(pNode->GetLocalPos());			    
		LocR.x /= (dWorldBase/dMapFactor);
		LocR.y /= (dWorldBase/dMapFactor);
		LocR.z /= (dWorldBase/dMapFactor);
		pObjectMgr->DStoSC(&LocR.x);
		pObjectMgr->DStoSC(&LocR.y);
		pObjectMgr->DStoSC(&LocR.z);
	}
	////////////////////////////////////// Fill Edits
	m_TranX 	= LocR.x;
	m_TranY 	= LocR.y;
	m_TranZ 	= LocR.z;
	m_TranPtID 	= Nid;
	//////////////////
	UpdateData(FALSE);	// update screen
	/////////////////////////////////////////////////////////
	
}

void CDlg_LMat::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_LMat::OnOK()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	CDialog::OnOK();
}
//////////////////////////////// end of module //////////////
