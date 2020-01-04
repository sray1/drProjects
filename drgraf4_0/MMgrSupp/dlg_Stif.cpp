// SupStif.cpp : implementation file
//

#include "stdafx.h"
#include "Def_Supp.h"
#include "CommRsrc.h"
/////////////////////
#include "Dlg_Stif.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Stif dialog


CDlg_Stif::CDlg_Stif(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Stif::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Stif)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_Stif::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Stif)
	DDX_Text(pDX, IDC_MX, m_dMx);
	DDX_Text(pDX, IDC_MY, m_dMy);
	DDX_Text(pDX, IDC_MZ, m_dMz);
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_Text(pDX, IDC_FY, m_dFy);
	DDX_Text(pDX, IDC_FZ, m_dFz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Stif, CDialog)
	//{{AFX_MSG_MAP(CDlg_Stif)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSup_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_Stif message handlers

BOOL CDlg_Stif::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////// Values
	m_dFx		= dValu[0];
	m_dFy		= dValu[1];
	m_dFz		= dValu[2];
	m_dMx		= dValu[3];
	m_dMy		= dValu[4];
	m_dMz		= dValu[5];
	///////////////////////////////////////////// Rigid?
	if(m_SuppProc == SUP_RIGID)
	{
		////////////////////
		UpdateData(FALSE);			//Update Screen(FALSE)    
		///////////////////	
		return TRUE;
	}
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

void CDlg_Stif::OnOK()
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


void CDlg_Stif::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
/////////////////////////// end of module //////////////
