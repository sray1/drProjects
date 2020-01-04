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
#include "dlg_TenBlend.h"


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
								"CIRCLE",				"PARABOLA",
								"HERMITE",				"B-SPLINE_Cubic",
								"NURB_Cubic"
								};
	static int nBL 			= sizeof(BLs)/sizeof(BLs[0]);
	static int Ord[] 		= {2,3,2,2,4,4,4};	// Conics,like linear needs no end conditions
												// they are faked as having order of linear = 2
	static int ActualOrd[]	= {2,3,3,3,4,4,4};	// actual Order
/////////////////////////////////////////////////////////////////////////////
// CDlg_TensorBlend dialog


CDlg_TensorBlend::CDlg_TensorBlend(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_TensorBlend::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_TensorBlend)
	m_strBLEND 	= "LAGRANGIAN_Linear";
	m_bClosed	= FALSE;
	m_ClosingElems = 1;
	//}}AFX_DATA_INIT
	///////////////////////
	m_nOrder	= 2;	// Linear
}

void CDlg_TensorBlend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_TensorBlend)
	DDX_CBString(pDX, IDC_BLEND, m_strBLEND);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_ELEMS, m_ClosingElems);
	DDV_MinMaxInt(pDX, m_ClosingElems, 1, 9999);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_TensorBlend, CDialog)
	//{{AFX_MSG_MAP(CDlg_TensorBlend)
	ON_CBN_SELCHANGE(IDC_BLEND, OnSelchangeBlend)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_TensorBlend message handlers
BOOL CDlg_TensorBlend::OnInitDialog()
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
	////////////////////////////////////////////////////// Heading
	if(m_Dir == 1)
		SetWindowText("U-directional Blending Info.");
	else
	if(m_Dir == 2)
		SetWindowText("V-directional Blending Info.");
   	////////////////////////////////////////////////////// Fill In
 	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_BLEND);
 	pCombo->EnableWindow(TRUE);	
 	pCombo->ResetContent();// ALL REMOVED 
	for(int i=0;i<nBL;i++)	// 								
	pCombo->AddString(BLs[i]);
 	pCombo->SetCurSel(0);
	////////////////////////////////////	
	OnSelchangeBlend(); // 
  	GetDlgItem(IDC_BLEND)->SetFocus();
  ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_TensorBlend::OnClosed() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
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
			////////////////////////////////////////////////
		}
	}
	else
		GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    ///////////////////
}

void CDlg_TensorBlend::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	SetDataBase_BC_N_BL(m_pDrCurve);
	///////////////
	CDialog::OnOK();
}

void CDlg_TensorBlend::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_TensorBlend::OnSelchangeBlend()
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
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 

} 

void CDlg_TensorBlend::SetDataBase_BC_N_BL(CDrCurve* pDrObject)	// Blending Curve
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
	//////////////////////////////
	int nDim 		= 3;			// NonRational
	if(CurveType == CP_CIRCLE || CurveType == CP_PARABOLA || CurveType == CP_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
	pDrObject->SetnDim_S(nDim);
	///////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
