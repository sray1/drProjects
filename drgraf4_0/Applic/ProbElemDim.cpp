// ProbElemDim.cpp : implementation file
//

#include "stdafx.h"
#include "drgraf.h"

#include "ProbElemDim.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProbElemDim dialog
////////////////////////////////////////////////
	static CString ProbDim[]	= {"1D","2D","3D"};
	static int nPDim 			= sizeof(ProbDim)/sizeof(ProbDim[0]);
	static CString ElemDim[]	= {"1D","2D","3D"};
	static int nEDim 			= sizeof(ElemDim)/sizeof(ElemDim[0]);
/////////////////////////////////////////////////////////////////////////////


CProbElemDim::CProbElemDim(CWnd* pParent /*=NULL*/)
	: CDialog(CProbElemDim::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CProbElemDim)
	//}}AFX_DATA_INIT
}


void CProbElemDim::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProbElemDim)
	DDX_CBString(pDX, IDC_COMBOELEMDIM, m_ElemDim);
	DDX_CBString(pDX, IDC_COMBOPROBDIM, m_ProbDim);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProbElemDim, CDialog)
	//{{AFX_MSG_MAP(CProbElemDim)
	ON_CBN_SELCHANGE(IDC_COMBOELEMDIM, OnSelchangeComboElemdim)
	ON_CBN_SELCHANGE(IDC_COMBOPROBDIM, OnSelchangeComboProbdim)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProbElemDim message handlers

void CProbElemDim::OnSelchangeComboElemdim() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_COMBOELEMDIM);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
	/////////////////////////////////////////////
	if(str == "1D")
		m_EDim = EDL_ONE;
	else
	if(str == "2D")
		m_EDim = EDL_TWO;
	else
	if(str == "3D")
		m_EDim = EDL_THREE;
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CProbElemDim::OnSelchangeComboProbdim() 
{
	int nEMax,i;
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_COMBOPROBDIM);
 	CComboBox* pComboE;
 	pComboE = (CComboBox*)GetDlgItem(IDC_COMBOELEMDIM);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
	/////////////////////////////////////////////
	if(str == "1D")
	{
		m_PDim	= PDL_ONE;
		nEMax	= 1; 
	}
	else
	if(str == "2D")
	{
		m_PDim	= PDL_TWO;
		nEMax	= 2; 
	}
	else
	if(str == "3D")
	{
		m_PDim	= PDL_THREE;
		nEMax	= 3; 
	}
	////////////////////////////// Adjust ElemDim Max
	pComboE->ResetContent();
	for(i=0;i<nEMax;i++)	// 								
 			pComboE->AddString(ElemDim[i]);
    pCombo->SetCurSel(0);	//
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

BOOL CProbElemDim::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	if(m_PDim == PDL_ONE)
		((CComboBox*)GetDlgItem(IDC_COMBOPROBDIM))->SetCurSel(0);//1D=0/2D=1/3D=2
	else
	if(m_PDim == PDL_TWO)
		((CComboBox*)GetDlgItem(IDC_COMBOPROBDIM))->SetCurSel(1);//1D=0/2D=1/3D=2
	else
	if(m_PDim == PDL_THREE)
		((CComboBox*)GetDlgItem(IDC_COMBOPROBDIM))->SetCurSel(2);//1D=0/2D=1/3D=2
	///////////////////////////////////////////////////////////////////
	if(m_EDim == PDL_ONE)
		((CComboBox*)GetDlgItem(IDC_COMBOELEMDIM))->SetCurSel(0);//1D=0/2D=1/3D=2
	else
	if(m_EDim == PDL_TWO)
		((CComboBox*)GetDlgItem(IDC_COMBOELEMDIM))->SetCurSel(1);//1D=0/2D=1/3D=2
	else
	if(m_EDim == PDL_THREE)
		((CComboBox*)GetDlgItem(IDC_COMBOELEMDIM))->SetCurSel(2);//1D=0/2D=1/3D=2
   	////////////
	OnSelchangeComboProbdim(); // this will reset Combos according to Type
	OnSelchangeComboElemdim(); // this will reset Combos according to Type
	/////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProbElemDim::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CProbElemDim::OnOK() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE) 
	////////////////////	
	CDialog::OnOK();
}
