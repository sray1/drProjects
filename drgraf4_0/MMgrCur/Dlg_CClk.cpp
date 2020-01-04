// dlg_cirr.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
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
#include "DrCurve.h"
////////////////////
#include "dlg_Knot.h"	
#include "dlg_Wts.h"	
#include "dlg_Tang.h"
/////////////////////		
#include "CommRsrc.h"
#include "MNodRsrc.h"
////////////////////
#include "dlg_CClk.h"	// Curve Interpolate Rational: Rightbutton

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_UNIF	1
///////////////////////////////////////////////////////////////////////////////
//				DO NOT CHANGE FOLLOWING ORDER AND SPELLING
	static CString BCs[] 	= {	"AUTO","CLAMPED","FREE","BESSEL","QUADRATIC",
								"NOT_A_KNOT","TANGENT"};
	static int nBC 			= sizeof(BCs)/sizeof(BCs[0]);
	static CString Deg[] 	= {	"LINEAR","QUADRATIC","CUBIC"};
	static int Ord[] 		= {2,3,4};
	static int nDeg 		= sizeof(Deg)/sizeof(Deg[0]);
/////////////////////////////////////////////////////////////////////////////
// CDlg_CClk dialog


CDlg_CClk::CDlg_CClk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CClk::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CClk)
	m_CurveID	= "";
	m_strDegree = "LINEAR";		// k - 1
	m_bAutoKn 	= TRUE;
	m_bAutoWt 	= FALSE;
	m_strBCL 	= "AUTO";
	m_strBCR 	= "AUTO";
	m_bUnifKN 	= FALSE;
	m_bUnifWT 	= TRUE;
	m_strKN 	= "AUTO";
	m_bRightOn 	= TRUE;
	m_bLeftOn 	= TRUE;
	//}}AFX_DATA_INIT
	//////////////////////////
	m_Typ_KN 		= KN_AUTO;
	m_Typ_WT 		= WT_UNIFORM;
	/////////////////////// Memory
	m_pKVal 		= NULL;
	m_pWVal 		= NULL;
	///////////////////////
}

void CDlg_CClk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CClk)
	DDX_Check(pDX, IDC_AUTO_KN, m_bAutoKn);
	DDX_Check(pDX, IDC_AUTO_WT, m_bAutoWt);
	DDX_CBString(pDX, IDC_BC_LEFT, m_strBCL);
	DDX_CBString(pDX, IDC_BC_RIGHT, m_strBCR);
	DDX_CBString(pDX, IDC_DEGREE, m_strDegree);
	DDX_Check(pDX, IDC_UNIF_KN, m_bUnifKN);
	DDX_Check(pDX, IDC_UNIF_WT, m_bUnifWT);
	DDX_CBString(pDX, IDC_KN_OPTION, m_strKN);
	DDX_Check(pDX, IDC_BC_RIGHT_ON, m_bRightOn);
	DDX_Check(pDX, IDC_BC_LEFT_ON, m_bLeftOn);
	DDX_Text(pDX, IDC_CID, m_CurveID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CClk, CDialog)
	//{{AFX_MSG_MAP(CDlg_CClk)
	ON_BN_CLICKED(IDC_AUTO_KN, OnAutoKn)
	ON_BN_CLICKED(IDC_AUTO_WT, OnAutoWt)
	ON_BN_CLICKED(IDC_NONU_KN, OnNonuKn)
	ON_BN_CLICKED(IDC_NONU_WT, OnNonuWt)
	ON_BN_CLICKED(IDC_UNIF_KN, OnUnifKn)
	ON_BN_CLICKED(IDC_UNIF_WT, OnUnifWt)
	ON_CBN_SELCHANGE(IDC_BC_LEFT, OnSelchangeBcLeft)
	ON_CBN_SELCHANGE(IDC_BC_RIGHT, OnSelchangeBcRight)
	ON_BN_CLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_CLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_AUTO_KN, OnAutoKn)
	ON_BN_DOUBLECLICKED(IDC_AUTO_WT, OnAutoWt)
	ON_BN_DOUBLECLICKED(IDC_NONU_KN, OnNonuKn)
	ON_BN_DOUBLECLICKED(IDC_NONU_WT, OnNonuWt)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_UNIF_KN, OnUnifKn)
	ON_BN_DOUBLECLICKED(IDC_UNIF_WT, OnUnifWt)
	ON_BN_DOUBLECLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_DOUBLECLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CClk message handlers

BOOL CDlg_CClk::OnInitDialog()
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
	/////////////////////////////////////////////////////////// ID
	m_CurveID = m_pDrCurve->GetObjectID(); 
	/////////////////////////////////////////////////////////// NODES
	m_pNodeSelList	= m_pDrCurve->GetINodeList();
	/////////////////////////////////////////////
	// Few Nodes Could Have been Selected Already
	// Include them Ist, If Any
	if(m_pNodeSelList && !m_pNodeSelList->IsEmpty())
		FillListAllString_Select(m_pNodeSelList);   // only with Nodes
	GetDlgItem(IDD_SELECTLIST)->EnableWindow(FALSE);// for view only	
	/////////////////////////////////////////////////////////// DATA
	if(m_nOrder == 2)
		m_strDegree = "LINEAR";		// k - 1
	else	
	if(m_nOrder == 3)
		m_strDegree = "QUADRATIC";	// k - 1
	else	
	if(m_nOrder == 4)
		m_strDegree = "CUBIC";	// k - 1
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_DEGREE))->SetCurSel(4-m_nOrder);//Cubic=0/Quad=1/Lin=2
   	////////////
	OnSelchangeDegree(); // this will reset Combos according to ORDER
	/////////////////
/*
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
	pWndCtrl->EnableWindow(FALSE);
	pWndCtrl = GetDlgItem(IDC_DEGREE);
	pWndCtrl->EnableWindow(FALSE);
*/
    //////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CClk::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE) 
	/////////////////////////////////////////////// BCs & Knots
	SetDataBase_BC_N_KNOTs(m_pDrCurve);
	///////////////
	CDialog::OnOK();
}

void CDlg_CClk::OnCancel()
{
	if(m_pKVal)
	{
		delete [] m_pKVal;
		m_pKVal = NULL;
	}	
	if(m_pWVal)
	{
		delete [] m_pWVal;
		m_pWVal = NULL;
	}	
	////////////////////
	CDialog::OnCancel();
}

void CDlg_CClk::FillListAllString_Select(CDListMgr* pDListMgr)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
	CString Nid;
	
	int nMaxNodes = pDListMgr->GetCount();
    if(nMaxNodes<0)
		return;
	///////////////
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
			Nid   = (pNode->GetNodeCard())->id;
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
} 

void CDlg_CClk::OnAutoKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoKn)
	{
		m_Typ_KN 	= KN_AUTO;
		m_bUnifKN	= FALSE;
		/////////////////////////////////////////////// Disable
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
	}
	else
	{
		/////////////////////////////////////////////// Enable
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
	}	
		
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnAutoWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoWt)
	{
		m_Typ_WT 	= WT_AUTO;
		m_bUnifWT	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnUnifKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bUnifKN)
	{
		m_Typ_KN 	= KN_UNIFORM;
		m_bAutoKn	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnUnifWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bUnifWT)
	{
		m_Typ_WT 	= WT_UNIFORM;
		m_bAutoWt	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnNonuKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_Knot	Dlg;
	///////////////////////// set Dialog data
	int nMax;
	BOOL bDistinct;
	///////////////
//											// This is for CIRR.cpp	
	nMax 		= m_pNodeSelList->GetCount();;
	m_pKVal		= new double[nMax];
	bDistinct	= TRUE;
	///////////////////////////////////
	Dlg.m_nMaxKnot	= nMax;
	Dlg.m_pKVal		= m_pKVal;
	Dlg.m_bDistinct = bDistinct;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_bUnifKN 	= FALSE;
		m_bAutoKn 	= FALSE;
		m_Typ_KN 	= KN_USER;
	}
	else		// Cancel
	{
		delete [] m_pKVal;
		m_pKVal = NULL;
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnNonuWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_Wts	Dlg;
	///////////////////////// set Dialog data
	int nMax;
	///////////////
//											// This is for CIRR.cpp	
	nMax 		= m_pNodeSelList->GetCount();
	m_pWVal		= new double[nMax];
/*											// This is for CDRR.cpp	
	else	
	{
		nMax 		= m_nMaxTotal;
		m_pWVal		= new double[nMax];
	}
*/	
	///////////////////////////////////
	Dlg.m_nMaxWeight	= nMax;
	Dlg.m_pWVal			= m_pWVal;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_bUnifWT 	= FALSE;
		m_bAutoWt 	= FALSE;
		m_Typ_WT 	= WT_USER;
	}
	else		// Cancel
	{
		delete [] m_pWVal;
		m_pWVal = NULL;
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnSelchangeDegree()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_DEGREE);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
	/////////////////////////////////////////////
	for(int i=0;i<nDeg;i++)
	{
		if(Deg[i] == str)
		{
			m_nOrder = Ord[i];
			break;
		}	
	}
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
 	/////////////////////////////////////////////
    if(m_nOrder == 2)		// LINEAR
    {
   		pCombo->ResetContent();// ALL REMOVED
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		(GetDlgItem(IDC_BC_LEFT_ON))->EnableWindow(FALSE);
        ///////////////////////////////////////////////
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
     	/////////////////////////////////////////////// Enabled Windows ALL(RATIONAL)
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(TRUE);
		//////////////////////////////////////////////// always left to start with
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn = TRUE;
  		pCombo->EnableWindow(TRUE);	
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox
		////////////////////////////////////	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
       	pCombo->SetCurSel(0);	//
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
     	/////////////////////////////////////////////// Disabled Windows
		OnAutoKn();
		/////////////////////////////////////////////// 
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		////////////////////////////////////////////////
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn 	= TRUE;
		///////////////////
   		pCombo->EnableWindow(TRUE);	// enabled 
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
        pCombo->SetCurSel(0);	//
	}
	////////////////////////////////////////////////// Change RIGHTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
 	//////////////////////////////////////////////
    if(m_nOrder == 2)		// LINEAR
    {
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
		///////////////////////////////////////////////
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
     	/////////////////////////////////////////////// Enabled Windows ALL(RATIONAL)
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(TRUE);
		//////////////////////////////////////////////// always False to start with
   		pCombo->ResetContent();// ALL REMOVED 
  		pCombo->EnableWindow(FALSE);	
		m_bRightOn = FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
     	/////////////////////////////////////////////// Disabled Windows
		OnAutoKn();
		/////////////////////////////////////////////// 
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		////////////////////////////////////////////////
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(TRUE);
		m_bRightOn 	= TRUE;
		///////////////////
   		pCombo->EnableWindow(TRUE);	// enabled 
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
        pCombo->SetCurSel(0);	//
	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 

} 

void CDlg_CClk::OnBcLeftOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
    // for LINEAR: everything is already Disabled
    /////////////////////////////////////////////
    if(m_nOrder == 4)		// CUBIC:keep BCs On
    {
    	m_bLeftOn = TRUE;
    	return;
    }
	/////////////////////	
 	CComboBox* pCombo;
	if(!m_bLeftOn)
	{
		////////////////////////////////////////////////// DISABLE LEFTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT);
 		//////////////////////////////////////////////
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(FALSE);
		////////////////////////////////////////////////// FILL RIGHTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
  		pCombo->EnableWindow(TRUE);	// Enabled
   		pCombo->ResetContent();// ALL REMOVED 
		for(int i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
		////////////////////////////////////
		int index;	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
        pCombo->SetCurSel(0);	//
        /////////////////////////////////////////////////
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(TRUE);
		m_bRightOn = TRUE;
		//////////////////
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnBcRightOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
    // for LINEAR: everything is already Disabled
    /////////////////////////////////////////////
    if(m_nOrder == 4)		// CUBIC:keep BCs On
    {
    	m_bRightOn = TRUE;
    	return;
    }
	/////////////////////	
 	CComboBox* pCombo;
	if(!m_bRightOn)
	{
		////////////////////////////////////////////////// DISABLE LEFTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
 		//////////////////////////////////////////////
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
		////////////////////////////////////////////////// FILL RIGHTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT);
  		pCombo->EnableWindow(TRUE);	// Enabled
   		pCombo->ResetContent();// ALL REMOVED 
		for(int i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
		////////////////////////////////////
		int index;	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
        pCombo->SetCurSel(0);	//
        /////////////////////////////////////////////////
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn = TRUE;
		//////////////////
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CClk::OnSelchangeBcLeft()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
   	if(m_strBCL.Left(7) == "TANGENT")	// "TANGENT"
   	{
   		CDlg_Tang	Dlg;
   		if(Dlg.DoModal() == IDOK)
   		{
   			m_TanL.x = Dlg.m_dTanX;			
   			m_TanL.y = Dlg.m_dTanY;			
   			m_TanL.z = Dlg.m_dTanZ;			
   		}
   		else
   			m_strBCL = "AUTO";
   		
   	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CDlg_CClk::OnSelchangeBcRight()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
   	if(m_strBCR.Left(7) == "TANGENT")	// "TANGENT"
   	{
   		CDlg_Tang	Dlg;
   		if(Dlg.DoModal() == IDOK)
   		{
   			m_TanR.x = Dlg.m_dTanX;			
   			m_TanR.y = Dlg.m_dTanY;			
   			m_TanR.z = Dlg.m_dTanZ;			
   		}
   		else
   			m_strBCR = "AUTO";
   		
   	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}
 
void CDlg_CClk::SetDataBase_BC_N_KNOTs(CDrCurve* pDrObject)
{
    ////////////////////////////////////////////////// Knots
	pDrObject->SetKnotType_S(m_Typ_KN);
	pDrObject->SetWtType_S(m_Typ_WT);
	////////////////////////////////////////////////// Boundary
   	if(m_strBCL == BCs[0])	// 
   		m_BCL = BC_AUTO;
   	else	
   	if(m_strBCL == BCs[1])	// 
   		m_BCL = BC_CLAMPED;
   	else	
   	if(m_strBCL == BCs[2])	// 
   		m_BCL = BC_FREE;
   	else	
   	if(m_strBCL == BCs[3])	// 
   		m_BCL = BC_BESSEL;
   	else	
   	if(m_strBCL == BCs[4])	// 
   		m_BCL = BC_QUADRATIC;
   	else	
   	if(m_strBCL == BCs[5])	// 
   		m_BCL = BC_NOT_A_KNOT;
   	else	
   	if(m_strBCL.Left(7) == BCs[6])	// "TANGENT" On DialogListBox it is TANGENT...
   		m_BCL = BC_TANGENT;
	//////////////////////////
	pDrObject->SetBCL_S(m_BCL);
	/////////////////////////
   	if(m_strBCR == BCs[0])	// 
   		m_BCR = BC_AUTO;
   	else	
   	if(m_strBCR == BCs[1])	// 
   		m_BCR = BC_CLAMPED;
   	else	
   	if(m_strBCR == BCs[2])	// 
   		m_BCR = BC_FREE;
   	else	
   	if(m_strBCR == BCs[3])	// 
   		m_BCR = BC_BESSEL;
   	else	
   	if(m_strBCR == BCs[4])	// 
   		m_BCR = BC_QUADRATIC;
   	else	
   	if(m_strBCR == BCs[5])	// 
   		m_BCR = BC_NOT_A_KNOT;
   	else	
   	if(m_strBCR.Left(7) == BCs[6])	// "TANGENT" On DialogListBox it is TANGENT...
   		m_BCR = BC_TANGENT;
	/////////////////////////
	pDrObject->SetBCR_S(m_BCR);
	/////////////////////////
	if(m_BCL == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanL.x;
		tan.v[1] = m_TanL.y;
		tan.v[2] = m_TanL.z;
		tan.v[3] = 0;
		////////
		pDrObject->SetTanL_S(tan);
	}	
	if(m_BCR == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanR.x;
		tan.v[1] = m_TanR.y;
		tan.v[2] = m_TanR.z;
		tan.v[3] = 0;
		////////
		pDrObject->SetTanR_S(tan);
	}
	/////////////////////////////////////////////////////// Quadratic
	// Only One BC end is allowable:
	//	 ifLeft	- set tan.v for right 	 -99999.	
	//	 ifRight- set tan.v for left 	= -99999.
	/////////////////////////////////////////////
	if(3 == m_nOrder)
	{
		if(m_bLeftOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			pDrObject->SetTanR_S(tan);
		}	
		if(m_bRightOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			pDrObject->SetTanL_S(tan);
		}
	}		
	///////////////////////////////////////////////////////////////////
	if( m_Typ_WT == WT_USER)
		pDrObject->SetpWts_DT_S(m_pWVal);	// pointer
	else
		pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	/////////////	
	if( m_Typ_KN == KN_USER)
		pDrObject->SetpKnots_S(m_pKVal);	// pointer
	else
		pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	//////////////////////////////
	int nDim 		= 3;			// NonRational
	if(m_Typ_WT != WT_UNIFORM)
		nDim 		= 4;			// Homogeneous(Rational)
	pDrObject->SetnDim_S(nDim);
	//////////////////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
