// Dlg_IsoP.cpp : implementation file
//

#include "stdafx.h"
#include "MSTLMgr.h"
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "Dlg_IsoP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////
static	CString m_strForce[]	= {"Fx","Fy","Fz","Mx","My","Mz"}; 
static	CString m_strDisplace[] = {"Dx","Dy","Dz","Rx","Ry","Rz"}; 
static	CString m_strPressure[] = {"Px","Py","Pz"}; 
static	CString m_strThermal[]	= {"Tx","Ty","Tz"}; 
static	CString m_strLumpWt[]	= {"Wx","Wy","Wz"}; 
/////////////////////////////////////////////////////////////////////////////
// CDlg_IsoP dialog


CDlg_IsoP::CDlg_IsoP(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_IsoP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_IsoP)
	m_dStart = 0.0;
	//}}AFX_DATA_INIT
}


void CDlg_IsoP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_IsoP)
	DDX_Text(pDX, IDC_START, m_dStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_IsoP, CDialog)
	//{{AFX_MSG_MAP(CDlg_IsoP)
	ON_BN_CLICKED(IDD_OK, OnOk)
	ON_BN_DOUBLECLICKED(IDD_OK, OnOk)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_IsoP message handlers

void CDlg_IsoP::OnOk() 
{
	UpdateData(TRUE);
	///////////////
	CDialog::OnOK();
}

void CDlg_IsoP::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlg_IsoP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//////////////////////// Reset Heading etc
	CString heading;
	/////////////////////////////////////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:
			heading = m_strForce[m_nCompo];
			break;
		case STL_DISPLACE:
			heading = m_strDisplace[m_nCompo];
			break;
		case STL_PRESSURE:
			heading = m_strPressure[m_nCompo];
			break;
		case STL_THERMAL:
			heading = m_strThermal[m_nCompo];
			break;
		case STL_LUMPWT:
			heading = m_strLumpWt[m_nCompo];
			break;
// todo Pressure etc.
		default:
			break;
	}
	heading += "@" + m_Heading;
	GetDlgItem(IDC_TRANHEAD)->SetWindowText(heading);
	///////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
///////////////////////////////// end of module //////////////////////