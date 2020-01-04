// Dlg_CrcT.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
//#include "edlgrsrc.h"
////////////////////
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
#include "Dlg_PatT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PatT dialog


CDlg_PatT::CDlg_PatT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PatT::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_PatT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_PatT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PatT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_PatT, CDialog)
	//{{AFX_MSG_MAP(CDlg_PatT)
	ON_BN_CLICKED(IDC_TYPE_1, OnType1)
	ON_BN_CLICKED(IDC_TYPE_2, OnType2)
	ON_BN_DOUBLECLICKED(IDC_TYPE_2, OnType2)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_PatT message handlers

BOOL CDlg_PatT::OnInitDialog()
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
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CDlg_PatT::OnType1() 
{
	m_bType_1 = TRUE;		//
}

void CDlg_PatT::OnType2() 
{
	m_bType_1 = FALSE;		//
}

void CDlg_PatT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_PatT::OnOK() 
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
