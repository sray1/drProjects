// dlg_mesu.cpp : implementation file
//

#include "stdafx.h"
////////////////////

#include "dlg_CMsU.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsU dialog


CDlg_CMsU::CDlg_CMsU(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CMsU::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CMsU)
	m_nUnif_OT = 0;
	//}}AFX_DATA_INIT
}

void CDlg_CMsU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CMsU)
	DDX_Text(pDX, IDC_ELOUT_UNIF, m_nUnif_OT);
	DDV_MinMaxInt(pDX, m_nUnif_OT, 1, 9999);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CMsU, CDialog)
	//{{AFX_MSG_MAP(CDlg_CMsU)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsU message handlers

BOOL CDlg_CMsU::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////
	GetDlgItem(IDC_ELOUT_UNIF)->SetFocus();
    //////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CMsU::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_CMsU::OnOK()
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
///////////////////////////// end of module //////////////////////////
