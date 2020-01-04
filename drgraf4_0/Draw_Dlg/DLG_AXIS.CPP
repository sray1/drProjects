// drawAxis.cpp : implementation file
//

#include "axisDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////
// CDrawAxis dialog

CDrawAxis::CDrawAxis(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawAxis::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDrawAxis)
	m_szDrawVertical = "Y-Axis";
	m_szDrawPositive = "Upward";
	//}}AFX_DATA_INIT
}

void CDrawAxis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawAxis)
	DDX_CBString(pDX, IDC_COMBO_VERTICAL, m_szDrawVertical);
	DDX_CBString(pDX, IDC_COMBO_POSITIVE, m_szDrawPositive);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawAxis, CDialog)
	//{{AFX_MSG_MAP(CDrawAxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawAxis message handlers

BOOL CDrawAxis::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CDlg_Axis dialog


CDlg_Axis::CDlg_Axis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Axis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Axis)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlg_Axis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Axis)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Axis, CDialog)
	//{{AFX_MSG_MAP(CDlg_Axis)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Axis message handlers
BOOL CDlg_Axis::Create ()
{
	/////////////////////////////////////////////////////////////
	return CDialog::Create(CCDlg_Axis::IDD);
	///////////////////////////////////////
}	

void CDlg_Axis::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
