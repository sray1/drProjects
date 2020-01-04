// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"

#include "MStLMgr.h"
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MSupRsrc.h"

#include "dlg_Many.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////
static	CString m_strForce[] = {"Force","Moment"}; 
static	CString m_strDisplace[] = {"Displace","Rotation"}; 
static	CString m_strPressure[] = {"Pressure"}; 
static	CString m_strThermal[] = {"Temperature"}; 
static	CString m_strLumpWt[] = {"Weight"}; 
/////////////////////////////////////////////////////////////////////////////
// CDlg_Many dialog


CDlg_Many::CDlg_Many(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Many::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Many)
	//}}AFX_DATA_INIT

}


void CDlg_Many::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Many)
	DDX_Text(pDX, IDC_MX, m_dMx);
	DDX_Text(pDX, IDC_MY, m_dMy);
	DDX_Text(pDX, IDC_MZ, m_dMz);
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_Text(pDX, IDC_FY, m_dFy);
	DDX_Text(pDX, IDC_FZ, m_dFz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Many, CDialog)
	//{{AFX_MSG_MAP(CDlg_Many)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_Many message handlers

BOOL CDlg_Many::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////// Reset Heading etc
	switch(m_StaLProc)
	{
		case STL_FORCE:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strForce[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText(m_strForce[1]);
			break;
		case STL_DISPLACE:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strDisplace[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText(m_strDisplace[1]);
			break;
// todo Pressure etc.
		default:
			break;
	}
	///////////////////////////////////////////// Header
	CString header("Static Info. @ Node ");
	header += Nid;
	SetWindowText(header);
	///////////////////////////////////////////// Values
	m_dFx		= dValu[0];
	m_dFy		= dValu[1];
	m_dFz		= dValu[2];
	m_dMx		= dValu[3];
	m_dMy		= dValu[4];
	m_dMz		= dValu[5];
	///////////////////////////////////////////// Active?
	for(int i=0;i<6;i++)
	{
		if(!bKode[i])
		{
			switch (i)
			{
				case 0:	GetDlgItem(IDC_FX)->EnableWindow(FALSE);break;
				case 1:	GetDlgItem(IDC_FY)->EnableWindow(FALSE);break;
				case 2: GetDlgItem(IDC_FZ)->EnableWindow(FALSE);break;
				case 3: GetDlgItem(IDC_MX)->EnableWindow(FALSE);break;
				case 4: GetDlgItem(IDC_MY)->EnableWindow(FALSE);break;
				case 5: GetDlgItem(IDC_MZ)->EnableWindow(FALSE);break;
				default:break;
			}
		}
	}		
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Many::OnOK()
{
	UpdateData(TRUE);
	///////////////////////////////////////////// Values
	dValu[0]	= m_dFx;
	dValu[1]	= m_dFy;
	dValu[2]	= m_dFz;
	dValu[3]	= m_dMx;
	dValu[4]	= m_dMy;
	dValu[5]	= m_dMz;
	////////////////////
	CDialog::OnOK();
}


void CDlg_Many::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
/////////////////////////// end of module //////////////