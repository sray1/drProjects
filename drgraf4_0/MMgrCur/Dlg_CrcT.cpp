// Dlg_CrcT.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
//#include "drgrafrm.h" 
/////////////////////
#include "MNodRsrc.h"
#include "MCurRsrc.h"
////////////////////
#include "Dlg_CrcT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcT dialog


CDlg_CrcT::CDlg_CrcT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CrcT::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CrcT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_CrcT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CrcT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_CrcT, CDialog)
	//{{AFX_MSG_MAP(CDlg_CrcT)
	ON_BN_CLICKED(IDC_TYPE_1, OnType1)
	ON_BN_CLICKED(IDC_TYPE_2, OnType2)
	ON_BN_DOUBLECLICKED(IDC_TYPE_2, OnType2)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_TYPE_1, OnType1)
	ON_BN_CLICKED(IDC_TYPE_3, OnType3)
	ON_BN_DOUBLECLICKED(IDC_TYPE_3, OnType3)
	ON_BN_CLICKED(IDC_TYPE_4, OnType4)
	ON_BN_DOUBLECLICKED(IDC_TYPE_4, OnType4)
	ON_BN_CLICKED(IDC_TYPE_5, OnType5)
	ON_BN_DOUBLECLICKED(IDC_TYPE_5, OnType5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcT message handlers

BOOL CDlg_CrcT::OnInitDialog()
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
	((CButton*)GetDlgItem(IDC_TYPE_1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_TYPE_2))->SetCheck(FALSE);
	/////////////////////////////////////////////////////////////////// MainFrame Wnd
//	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CWnd* pWnd		= AfxGetMainWnd();
	CenterWindow(pWnd);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CDlg_CrcT::OnType1() 
{
	m_nType = CIRCLE_BY_NO3;		//
}

void CDlg_CrcT::OnType2() 
{
	m_nType = CIRCLE_BY_ROT;		//
}

void CDlg_CrcT::OnType3() 
{
	m_nType = CIRCLE_BY_2N_TI;		//
}

void CDlg_CrcT::OnType4() 
{
	m_nType = CIRCLE_BY_2N_CC;
}

void CDlg_CrcT::OnType5() 
{
	m_nType = CIRCLE_BY_2CN_TI_R;
}

void CDlg_CrcT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_CrcT::OnOK() 
{
    ////////////////////
	UpdateData(TRUE);			//Update Screen(FALSE)    
	//////////////////////////
	CDialog::OnOK();
}
////////////////////////////// end of module ///////////////
