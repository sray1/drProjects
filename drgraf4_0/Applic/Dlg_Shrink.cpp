// Dlg_Shrink.cpp : implementation file
//

#include "stdafx.h"
#include "drgraf.h"
#include "Dlg_Shrink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Shrink dialog


CDlg_Shrink::CDlg_Shrink(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Shrink::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Shrink)
	m_dShrink = 1.0;
	//}}AFX_DATA_INIT
}


void CDlg_Shrink::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Shrink)
	DDX_Text(pDX, IDC_SHRINK, m_dShrink);
	DDV_MinMaxDouble(pDX, m_dShrink, 0.1, 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Shrink, CDialog)
	//{{AFX_MSG_MAP(CDlg_Shrink)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Shrink message handlers

BOOL CDlg_Shrink::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//////////////////// end of module //////////////////

