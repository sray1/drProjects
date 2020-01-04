// Dlg_CrcT.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
//#include "edlgrsrc.h"
////////////////////
#include "Mlg_LSyT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMlg_LSyT dialog


CMlg_LSyT::CMlg_LSyT(CWnd* pParent /*=NULL*/)
	: CDialog(CMlg_LSyT::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CMlg_LSyT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMlg_LSyT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMlg_LSyT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMlg_LSyT, CDialog)
	//{{AFX_MSG_MAP(CMlg_LSyT)
	ON_BN_CLICKED(IDC_TYPE_1_SYM, OnType1)
	ON_BN_CLICKED(IDC_TYPE_2_SYM, OnType2)
	ON_BN_DOUBLECLICKED(IDC_TYPE_1_SYM, OnType1)
	ON_BN_DOUBLECLICKED(IDC_TYPE_2_SYM, OnType2)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlg_LSyT message handlers

BOOL CMlg_LSyT::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////// initialize:
	m_bType_1 = TRUE;		//
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_TYPE_1_SYM))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_TYPE_2_SYM))->SetCheck(FALSE);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CMlg_LSyT::OnType1() 
{
	m_bType_1 = TRUE;		//
}

void CMlg_LSyT::OnType2() 
{
	m_bType_1 = FALSE;		//
}

void CMlg_LSyT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMlg_LSyT::OnOK() 
{
    ////////////////////
	UpdateData(TRUE);			//Update Screen(FALSE)    
    ///////////////////	
	if(m_bType_1)
		m_nType = 1;		//
	else
		m_nType = 2;		//
	//////////////////////////
	CDialog::OnOK();
}
////////////////////////////// end of module ///////////////
