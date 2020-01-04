// Dlg_OutR.cpp : implementation file
//

#include "stdafx.h"

////////////////////
#include "Dlg_CMsR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsR dialog


CDlg_CMsR::CDlg_CMsR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CMsR::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CMsR)
	m_Ratio =	1.0;
	m_nElOut =	1;
	//}}AFX_DATA_INIT
}


void CDlg_CMsR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CMsR)
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDV_MinMaxDouble(pDX, m_Ratio, 1.e-002, 999.);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nElOut);
	DDV_MinMaxInt(pDX, m_nElOut, 1, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_CMsR, CDialog)
	//{{AFX_MSG_MAP(CDlg_CMsR)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsR message handlers

BOOL CDlg_CMsR::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////// initialize:
	GetDlgItem(IDC_ELOUT_SEG)->SetFocus();  // 
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CMsR::OnOK()
{ 

//      case IDD_OK:     
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
 	////////////////
	CDialog::OnOK();

} 

void CDlg_CMsR::OnCancel()
{
	m_Ratio =	1.0;
	m_nElOut =	1;
	////////////////////
	CDialog::OnCancel();
}
///////////////////////////// end of module /////////////

