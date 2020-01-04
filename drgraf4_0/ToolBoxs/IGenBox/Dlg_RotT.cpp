// Dlg_CrcT.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "Def_IGen.h"
////////////////////
#include "Dlg_RotT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_ROTT dialog


CDlg_ROTT::CDlg_ROTT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_ROTT::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_ROTT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Caller = COP_ROTATE;
}


void CDlg_ROTT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_ROTT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_ROTT, CDialog)
	//{{AFX_MSG_MAP(CDlg_ROTT)
	ON_BN_CLICKED(IDC_TYPE_1_ROT, OnType1)
	ON_BN_CLICKED(IDC_TYPE_2_ROT, OnType2)
	ON_BN_DOUBLECLICKED(IDC_TYPE_1_ROT, OnType1)
	ON_BN_DOUBLECLICKED(IDC_TYPE_2_ROT, OnType2)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_ROTT message handlers

BOOL CDlg_ROTT::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////// initialize:
	m_bType_1 = TRUE;		//
	//////////////////////////////// MOVE
	if(m_Caller == GOP_MOVE)
	{
		SetWindowText("MOVE Option");
		GetDlgItem(IDC_TYPE_1_ROT)->SetWindowText("Translational MOVE");
		GetDlgItem(IDC_TYPE_2_ROT)->SetWindowText("Rotational MOVE");
	}
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_TYPE_1_ROT))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_TYPE_2_ROT))->SetCheck(FALSE);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CDlg_ROTT::OnType1() 
{
	m_bType_1 = TRUE;		//
}

void CDlg_ROTT::OnType2() 
{
	m_bType_1 = FALSE;		//
}

void CDlg_ROTT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_ROTT::OnOK() 
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
