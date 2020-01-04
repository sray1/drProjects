// dlg_tang.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <float.h>		// DBL_MIN

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
//#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "MNodRsrc.h"
#include "dlg_tang.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Tang dialog


CDlg_Tang::CDlg_Tang(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Tang::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Tang)
	m_dTanX = 1.;
	m_dTanY = 0.;
	m_dTanZ = 0.;
	m_bCoordIn	= TRUE;
	m_FromID	= "";
	m_ToID		= "";
	//}}AFX_DATA_INIT
}

void CDlg_Tang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Tang)
	DDX_Text(pDX, IDC_TAN_X, m_dTanX);
	DDX_Text(pDX, IDC_TAN_Y, m_dTanY);
	DDX_Text(pDX, IDC_TAN_Z, m_dTanZ);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_Check(pDX, IDC_COORD_INPUT, m_bCoordIn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Tang, CDialog)
	//{{AFX_MSG_MAP(CDlg_Tang)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM, OnSelchangeCnodeFrom)
	ON_CBN_SELCHANGE(IDC_CNODE_TO, OnSelchangeCnodeTo)
	ON_BN_CLICKED(IDC_COORD_INPUT, OnCoordInput)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_COORD_INPUT, OnCoordInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Tang message handlers

BOOL CDlg_Tang::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////////
	CString IstID;
//	CWnd* pWndCtrl;
	///////////////////////////////////////// 
	FillListAllString(IDC_CNODE_FROM,IstID);   // 
	m_FromID 	= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_TO,IstID);   // 
	m_ToID 		= IstID;
	////////////////////////////////////////
	if(m_FromID == m_ToID)
		m_bCoordIn	= TRUE;
	else
		m_bCoordIn	= FALSE;
	////////////////////////
	if(m_bCoordIn)				// Coord Input
	{
		///////////////////
		m_dTanX		= 1;
		m_dTanY 	= 0;
		m_dTanZ 	= 0;
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);
		///////////////////////////
	}
	else
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);
		///////////////////////////
		ShowTangent();
	}
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Tang::OnCoordInput() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bCoordIn)				// Coord Input
	{
		///////////////////
		m_dTanX		= 1;
		m_dTanY 	= 0;
		m_dTanZ 	= 0;
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);
		///////////////////////////
	}
	else
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);
		///////////////////////////
 		CWnd* pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
  		((CComboBox*)pWndCtrl)->SetCurSel(0);
		///////////////////
		ShowTangent();
	}
	//////////////////
	UpdateData(FALSE);
	//////////////////
}

void CDlg_Tang::OnSelchangeCnodeFrom() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetLBText(index,m_FromID);
	//////////////////
	ShowTangent();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CDlg_Tang::OnSelchangeCnodeTo() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetLBText(index,m_ToID);
	//////////////////
	ShowTangent();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

int CDlg_Tang::FillListAllString(UINT DlgItemID,CString& IstID)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(DlgItemID);
	CString Nid;
	BOOL bGotStr = FALSE;
	///////////////////////// 
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
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

void CDlg_Tang::ShowTangent() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_FromID == m_ToID)
	{
		///////////////////
		m_dTanX		= 1;
		m_dTanY 	= 0;
		m_dTanZ 	= 0;
		//////////////////
		UpdateData(FALSE);
		//////////////////
		return;
	}
	C3DMath	Math3D;
	///////////////////////////////////////
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
	WORLD LocFrom,LocTo;
	int index;
	CString Nid;
	//////////////
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(pDListMgr)
	{	

		CWnd* pWndCtrl;
		CDrNode* pNode;
		///////////////////////////////////////////// From
		pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocFrom 	= *(pNode->GetLocalPos());			    
		//////////////////////////////// scale etc
		LocFrom 	= *(pNode->GetLocalPos());			    
		LocFrom.x /= (dWorldBase/dMapFactor);
		LocFrom.y /= (dWorldBase/dMapFactor);
		LocFrom.z /= (dWorldBase/dMapFactor);
		pObjectMgr->DStoSC(&LocFrom.x);
		pObjectMgr->DStoSC(&LocFrom.y);
		pObjectMgr->DStoSC(&LocFrom.z);
		///////////////////////////////////////////// To
		pWndCtrl = GetDlgItem(IDC_CNODE_TO);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocTo 	= *(pNode->GetLocalPos());			    
		//////////////////////////////// scale etc
		LocTo 	= *(pNode->GetLocalPos());			    
		LocTo.x /= (dWorldBase/dMapFactor);
		LocTo.y /= (dWorldBase/dMapFactor);
		LocTo.z /= (dWorldBase/dMapFactor);
		pObjectMgr->DStoSC(&LocTo.x);
		pObjectMgr->DStoSC(&LocTo.y);
		pObjectMgr->DStoSC(&LocTo.z);
	}
	////////////////////////////////////// Find Components
	WORLD Compo;
	Math3D.Sub3DPts(&LocTo,&LocFrom,&Compo);
	double dLen = Math3D.Len3DPts(&Compo);
	if(fabs(dLen)<DBL_MIN)
	{
		///////////////////
		m_dTanX		= 1;
		m_dTanY 	= 0;
		m_dTanZ 	= 0;
		//////////////////
		return;
	}
	////////////////////////////////// doNOT Normalize
	// because we are interested in Components
	// not just direction cosines of the tangent
//	Math3D.Normalize(&Compo,&Compo);
	///////////////////
	m_dTanX = Compo.x;
	m_dTanY = Compo.y;
	m_dTanZ = Compo.z;
	////////////////
	return;	
}

void CDlg_Tang::OnCancel()
{
	///////////////////////////////
	///////////////////////////////
	CDialog::OnCancel();
}

void CDlg_Tang::OnOK()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	////////////////////////////////
	CDialog::OnOK();
}
///////////////////////// end of Module /////////////////////////////////
