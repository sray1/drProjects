// JointCoord.cpp : implementation file
//

#include "stdafx.h"
#include "Def_Supp.h"
#include "CommRsrc.h"
#include "MPatRsrc.h"	// IDC_DEFAULT
///////////////////////
#include "Dlg_JointCoord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_JointCoord dialog


CDlg_JointCoord::CDlg_JointCoord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_JointCoord::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_JointCoord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_JointCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_JointCoord)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_JointCoord, CDialog)
	//{{AFX_MSG_MAP(CDlg_JointCoord)
	ON_BN_CLICKED(IDC_RADIOCURVE, OnRadioCurve)
	ON_BN_CLICKED(IDC_RADIOFIXEDDIR, OnRadioFixedDir)
	ON_BN_CLICKED(IDC_RADIOPATCH, OnRadioPatch)
	ON_BN_DOUBLECLICKED(IDC_RADIOCURVE, OnRadioCurve)
	ON_BN_DOUBLECLICKED(IDC_RADIOFIXEDDIR, OnRadioFixedDir)
	ON_BN_DOUBLECLICKED(IDC_RADIOPATCH, OnRadioPatch)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_DOUBLECLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_JointCoord message handlers

BOOL CDlg_JointCoord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////// Values
	m_jcType =	JC_DEFAULT;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH
	////////////////////
	((CButton*)GetDlgItem(IDC_DEFAULT))->SetCheck(TRUE);
	////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_JointCoord::OnDefault() 
{
	m_jcType =	JC_DEFAULT;
}

void CDlg_JointCoord::OnRadioCurve() 
{
	m_jcType =	JC_X_TAN_CURVE;
}

void CDlg_JointCoord::OnRadioFixedDir() 
{
	m_jcType =	JC_X_FIXEDDIR;
}

void CDlg_JointCoord::OnRadioPatch() 
{
	m_jcType =	JC_Z_NOR_PATCH;
}

void CDlg_JointCoord::OnOK()
{
	////////////////////
	CDialog::OnOK();
}


void CDlg_JointCoord::OnCancel() 
{
	m_jcType =	JC_DEFAULT;
	/////////////////////	
	CDialog::OnCancel();
}
