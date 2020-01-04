// zoomdlg.cpp : implementation file
//

#include "zoomdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog

CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CZoomDlg)
	m_Zoom_X = 1.0;
	m_Zoom_Y = 1.0;
	m_Zoom_Z = 1.0;
	//}}AFX_DATA_INIT
}

void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Text(pDX, IDC_ZOOM_X, m_Zoom_X);
	DDV_MinMaxFloat(pDX, m_Zoom_X, 0., 10.);
	DDX_Text(pDX, IDC_ZOOM_Y, m_Zoom_Y);
	DDV_MinMaxFloat(pDX, m_Zoom_Y, 0., 10.);
	DDX_Text(pDX, IDC_ZOOM_Z, m_Zoom_Z);
	DDV_MinMaxFloat(pDX, m_Zoom_Z, 0., 10.);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers

BOOL CZoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	 
	CWnd* pWndCtrl = GetDlgItem(IDC_ZOOM_X);
	((CEdit*)(pWndCtrl))->LimitText(5); 
	pWndCtrl = GetDlgItem(IDC_ZOOM_Y);
	((CEdit*)(pWndCtrl))->LimitText(5); 
	pWndCtrl = GetDlgItem(IDC_ZOOM_Z);
	((CEdit*)(pWndCtrl))->LimitText(5); 
	pWndCtrl = GetDlgItem(IDC_ZOOM_X);
	GotoDlgCtrl(pWndCtrl);
	//////////////////
	UpdateData(FALSE);
	//////////////////
	return FALSE;  // return TRUE  unless you set the focus to a control
}
