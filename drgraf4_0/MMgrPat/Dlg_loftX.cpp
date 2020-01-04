// dlg_loft.cpp : implementation file
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
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MPatRsrc.h"
#include "dlg_Tang.h"
//////////////////////
#include "dlg_loftX.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1
///////////////////////////////////////////////////////////////////////////////
//				DO NOT CHANGE FOLLOWING ORDER AND SPELLING
	static CString BLs[] 	=	{
								"LAGRANGIAN_Linear",	"B-SPLINE_Quadratic",
								"CIRCLE",				"PARABOLA"
								"HERMITE",				"B-SPLINE_Cubic",
								"NURB_Cubic"
								};
	static int nBL 			= sizeof(BLs)/sizeof(BLs[0]);
	static int Ord[] 		= {2,3,2,2,4,4,4};	// Conics,like linear needs no end conditions
												// they are faked as having order of linear = 2
	static int ActualOrd[]	= {2,3,3,3,4,4,4};	// actual Order
	static CString BCs[] 	= {	"AUTO","CLAMPED","FREE","BESSEL","QUADRATIC",
								"NOT_A_KNOT","TANGENT"};
	static int nBC 			= sizeof(BCs)/sizeof(BCs[0]);
/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftX dialog


CDlg_LoftX::CDlg_LoftX(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LoftX::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LoftX)
	m_strBLEND 	= "LAGRANGIAN_Linear";
	m_strBCL 	= "AUTO";
	m_strBCR 	= "AUTO";
	m_bRightOn 	= TRUE;
	m_bLeftOn 	= TRUE;
	m_bClosed	= FALSE;
	m_ClosingElems = 1;
	//}}AFX_DATA_INIT
	///////////////////////
	m_nOrder	= 2;	// Linear
}

void CDlg_LoftX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LoftX)
	DDX_CBString(pDX, IDC_BLEND, m_strBLEND);
	DDX_CBString(pDX, IDC_BC_LEFT, m_strBCL);
	DDX_CBString(pDX, IDC_BC_RIGHT, m_strBCR);
	DDX_Check(pDX, IDC_BC_RIGHT_ON, m_bRightOn);
	DDX_Check(pDX, IDC_BC_LEFT_ON, m_bLeftOn);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_ELEMS, m_ClosingElems);
	DDV_MinMaxInt(pDX, m_ClosingElems, 1, 9999);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_LoftX, CDialog)
	//{{AFX_MSG_MAP(CDlg_LoftX)
	ON_CBN_SELCHANGE(IDC_BLEND, OnSelchangeBlend)
	ON_CBN_SELCHANGE(IDC_BC_LEFT, OnSelchangeBcLeft)
	ON_CBN_SELCHANGE(IDC_BC_RIGHT, OnSelchangeBcRight)
	ON_BN_CLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_CLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_DOUBLECLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftX message handlers
BOOL CDlg_LoftX::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////////////////////////// Closing Elems
	if(!m_bClosed)
		GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
   	////////////////////////////////////////////////////// Fill In
 	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_BLEND);
 	pCombo->EnableWindow(TRUE);	
 	pCombo->ResetContent();// ALL REMOVED 
	for(int i=0;i<nBL;i++)	// 								
	pCombo->AddString(BLs[i]);
 	pCombo->SetCurSel(0);
	////////////////////////////////////	
	OnSelchangeBlend(); // this will reset Combos according to ORDER
  	GetDlgItem(IDC_BLEND)->SetFocus();
  ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_LoftX::OnClosed() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
 	CComboBox* pCombo;
	//////////////////
	if(m_bClosed)
	{
		if(m_nLoftCurves<3)
		{
			AfxMessageBox("DATA ERROR:\nNumber of Lofted Curves less than 3\nCAN NOT be CLOSED");
			m_bClosed = FALSE;
			GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
			////////////////////////////////////////////////// Disabled LEFTBoundaryCombo
 			pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
	 		pCombo->EnableWindow(FALSE);	// disabled
			(GetDlgItem(IDC_BC_LEFT_ON))->EnableWindow(FALSE);
			////////////////////////////////////////////////// Disabled RIGHTBoundaryCombo
 			pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT); 
	 		pCombo->EnableWindow(FALSE);	// disabled
			(GetDlgItem(IDC_BC_RIGHT_ON))->EnableWindow(FALSE);
			////////////////////////////////////////////////
		}
	}
	else
		GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    ///////////////////
}

void CDlg_LoftX::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	SetDataBase_BC_N_BL(m_pDrCurve);
	///////////////
	CDialog::OnOK();
}

void CDlg_LoftX::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_LoftX::OnSelchangeBlend()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_BLEND);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
    ///////////////////
	if(str == "CIRCLE" ||str == "PARABOLA")		// Conics
	{		
		if(m_nLoftCurves != 3)
		{
			AfxMessageBox(
			"DATA ERROR:\nNumber of Lofted Curves Not Equal To 3\nCAN NOT be CIRCLE or PARABOLA");
			return;
		}
	}
	/////////////////////////////////////////////
	for(int i=0;i<nBL;i++)
	{
		if(BLs[i] == str)
		{
			m_nOrder = Ord[i];
			break;
		}	
	}
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
 	/////////////////////////////////////////////
    if(m_bClosed || m_nOrder == 2)		// LINEAR & CONICS(set w/ FAKE degree = 2) OR CLOSED
    {
   		pCombo->ResetContent();// ALL REMOVED
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		(GetDlgItem(IDC_BC_LEFT_ON))->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
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
    if(m_bClosed || m_nOrder == 2)		// LINEAR & CONICS(set w/ FAKE degree = 2) OR CLOSED 
    {
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
		//////////////////////////////////////////////// always False to start with
   		pCombo->ResetContent();// ALL REMOVED 
  		pCombo->EnableWindow(FALSE);	
		m_bRightOn = FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
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

void CDlg_LoftX::OnBcLeftOn()
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

void CDlg_LoftX::OnBcRightOn()
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

void CDlg_LoftX::OnSelchangeBcLeft()
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

void CDlg_LoftX::OnSelchangeBcRight()
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
 
void CDlg_LoftX::SetDataBase_BC_N_BL(CDrCurve* pDrObject)	// Blending Curve
{
	pDrObject->SetClosed_S(m_bClosed);
	////////////////////////////// Closing Segment Elems
	if(m_bClosed)
		pDrObject->GetElperSegList_S()->AddTail(m_ClosingElems);
	//////////////////////////////////
/*
	static CString BLs[] 	=	{
								"LAGRANGIAN_Linear",	"B-SPLINE_Quadratic",
								"CIRCLE",				"PARABOLA"
								"HERMITE",				"B-SPLINE_Cubic",
								"NURB_Cubic"
								};
	static int ActualOrd[]	= {2,3,3,3,4,4,4};	// actual Order
*/
	///////////////////////////////////////////// Order
	for(int i=0;i<nBL;i++)
	{
		if(BLs[i] == m_strBLEND)
		{
			m_nOrder = ActualOrd[i];
			break;
		}	
	}
	///////////////////////////////////////
	pDrObject->SetOrder_S(m_nOrder);
	///////////////////////////////////////
   	CURVEPROC CurveType;
	////////////////////////////////////////////////// Blend
   	if(m_strBLEND == BLs[0])	// 
   		CurveType = CP_LINEAR;
   	else	
   	if(m_strBLEND == BLs[1])	// 
   		CurveType = CP_QUADRATIC;
   	else	
   	if(m_strBLEND == BLs[2])	// 
   		CurveType = CP_CIRCLE;
   	else	
   	if(m_strBLEND == BLs[3])	// 
   		CurveType = CP_PARABOLA;
   	else	
   	if(m_strBLEND == BLs[4])	// 
   		CurveType = CP_HERMITE;
   	else	
   	if(m_strBLEND == BLs[5])	// 
   		CurveType = CP_BSPLINE;
   	else	
   	if(m_strBLEND == BLs[6])	// 
   		CurveType = CP_NURB;
	///////////////////////////////////////
	pDrObject->SetCurveType_S(CurveType);
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
		tan.v[2] = m_TanL.x;
		tan.v[3] = 0;
		////////
		pDrObject->SetTanL_S(tan);
	}	
	if(m_BCR == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanR.x;
		tan.v[1] = m_TanR.y;
		tan.v[2] = m_TanR.x;
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
	//////////////////////////////
	int nDim 		= 3;			// NonRational
	if(CurveType == CP_CIRCLE || CurveType == CP_PARABOLA || CurveType == CP_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
	pDrObject->SetnDim_S(nDim);
	///////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
