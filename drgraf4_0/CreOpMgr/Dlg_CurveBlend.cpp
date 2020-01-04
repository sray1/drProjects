// dlg_loft.cpp : implementation file
//
					// ONLY BEZIER BLEND oof Order 2, 3 & 4(ForNow Only)
					/////////////////////////////////////////////////////
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
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MCurRsrc.h"
//////////////////////
#include "dlg_CurveBlend.h"


///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
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
	static CString BLs[] 	=	{	"C0: Linear",	"C1: Quadratic",	"C1: Cubic Blend"};
	static int nBL 			= sizeof(BLs)/sizeof(BLs[0]);
	static int ActualOrd[]	= {2,3,4};	// actual Order
/////////////////////////////////////////////////////////////////////////////
// CDlg_CurveBlend dialog


CDlg_CurveBlend::CDlg_CurveBlend(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CurveBlend::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CurveBlend)
	m_strBLEND		= BLs[0];
	m_ClosingElems	= 1;
	m_Ratio			= 1.0;
	//}}AFX_DATA_INIT
	///////////////////////
	m_nOrder	= 2;	// Linear
}

void CDlg_CurveBlend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CurveBlend)
	DDX_CBString(pDX, IDC_BLENDCONTINUITY, m_strBLEND);
	DDX_Text(pDX, IDC_BLENDELEMS, m_ClosingElems);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CurveBlend, CDialog)
	//{{AFX_MSG_MAP(CDlg_CurveBlend)
	ON_CBN_SELCHANGE(IDC_BLENDCONTINUITY, OnSelchangeBlend)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CurveBlend message handlers
BOOL CDlg_CurveBlend::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////
	CString* pstr;
	char* buf;
	//////////////
	pstr	= new CString;
	buf		= pstr->GetBuffer(BUFF_SIZE);
	sprintf(buf,"Blend Info: Curve_%d & Curve_%d",
				m_nCur1,m_nCur2);
	SetWindowText(*pstr);
	//////////////////
	delete pstr;
   	////////////////////////////////////////////////////// Fill In
 	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_BLENDCONTINUITY);
 	pCombo->EnableWindow(TRUE);	
 	pCombo->ResetContent();// ALL REMOVED 
	for(int i=0;i<nBL;i++)	// 								
	pCombo->AddString(BLs[i]);
 	pCombo->SetCurSel(2);
	////////////////////////////////////	
	OnSelchangeBlend(); // 
// 	GetDlgItem(IDC_BLENDCONTINUITY)->SetFocus();
  	GetDlgItem(IDC_BLENDCONTINUITY)->EnableWindow(FALSE);
  ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CurveBlend::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	SetDataBase_BC_N_BL(m_pDrCurve);
	///////////////
	CDialog::OnOK();
}

void CDlg_CurveBlend::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_CurveBlend::OnSelchangeBlend()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_BLENDCONTINUITY);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
	/////////////////////////////////////////////
	for(int i=0;i<nBL;i++)
	{
		if(BLs[i] == str)
		{
			m_nOrder = ActualOrd[i];
			break;
		}	
	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 

} 

void CDlg_CurveBlend::SetDataBase_BC_N_BL(CDrCurve* pDrObject)	// Blending Curve
{
	//////////////////////////////////
/*
	static CString BLs[] 	=	{	"C0: Linear",	"C1: Quadratic",	"C2: Cubic"};
	static int ActualOrd[]	= {2,3,4};	// actual Order
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
   		CurveType = CP_NURB;
	/////////////////////////////////////// OverRide
	pDrObject->SetCurveType_S(CP_BEZIER);	// ALWAYS
	//////////////////////////////
	pDrObject->SetnDim_S(3);
	////////////////////////////////////////////////// Blend Portion ofElems
	pDrObject->SetClosed_S(FALSE);
	pDrObject->GetElperSegList_S()->AddTail(m_ClosingElems);
	pDrObject->SetRatio_S(m_Ratio);
	///////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////