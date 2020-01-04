// Dlg_Uniform.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "MStLMgr.h"
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MSupRsrc.h"
/////////////////////
#include "Dlg_Uniform.h"

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
// CDlg_Uniform dialog


CDlg_Uniform::CDlg_Uniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Uniform::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Uniform)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_Uniform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Uniform)
	DDX_Text(pDX, IDC_MX, m_dMx);
	DDX_Text(pDX, IDC_MY, m_dMy);
	DDX_Text(pDX, IDC_MZ, m_dMz);
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_Text(pDX, IDC_FY, m_dFy);
	DDX_Text(pDX, IDC_FZ, m_dFz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Uniform, CDialog)
	//{{AFX_MSG_MAP(CDlg_Uniform)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Uniform message handlers
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_Uniform message handlers

BOOL CDlg_Uniform::OnInitDialog()
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
			///////////////////////////////////////////// Header
			if(m_GenKind == NODE)
				SetWindowText("Nodal Loading");
			else
				SetWindowText("Uniform Loading");
			break;

		case STL_DISPLACE:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strDisplace[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText(m_strDisplace[1]);
			///////////////////////////////////////////// Header
			if(m_GenKind == NODE)
				SetWindowText("Nodal Displacement");
			else
				SetWindowText("Uniform Displacement");
			break;

		case STL_PRESSURE:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strPressure[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText("");
			///////////////////////////////////////////// Header
			if(m_GenKind == NODE)
				SetWindowText("Nodal Pressure");
			else
				SetWindowText("Uniform Pressure");
			break;

		case STL_THERMAL:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strThermal[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText("");
			///////////////////////////////////////////// Header
			if(m_GenKind == NODE)
				SetWindowText("Nodal Thermal");
			else
				SetWindowText("Uniform Thermal");
			break;

		case STL_LUMPWT:
			GetDlgItem(IDC_TRANHEAD)->SetWindowText(m_strLumpWt[0]);
			GetDlgItem(IDC_ROTHEAD)->SetWindowText("");
			///////////////////////////////////////////// Header
			if(m_GenKind == NODE)
				SetWindowText("Nodal Lump Weight");
			else
				SetWindowText("Uniform Lump Weight");
			break;

		default:
			break;
	}
	///////////////////////////////////////////// Values
	m_dFx		= m_dValu[0];
	m_dFy		= m_dValu[1];
	m_dFz		= m_dValu[2];
	m_dMx		= m_dValu[3];
	m_dMy		= m_dValu[4];
	m_dMz		= m_dValu[5];
	///////////////////////////////////////////// Active?
	for(int i=0;i<6;i++)
	{
		if(!m_bKode[i])
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

void CDlg_Uniform::OnOK()
{
	UpdateData(TRUE);
	///////////////////////////////////////////// Values
	m_dValu[0]	= m_dFx;
	m_dValu[1]	= m_dFy;
	m_dValu[2]	= m_dFz;
	m_dValu[3]	= m_dMx;
	m_dValu[4]	= m_dMy;
	m_dValu[5]	= m_dMz;
	////////////////////
	CDialog::OnOK();
}


void CDlg_Uniform::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
/////////////////////////// end of module //////////////
