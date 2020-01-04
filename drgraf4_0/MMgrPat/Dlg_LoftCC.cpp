// Dlg_Tensor.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MPatRsrc.h"
//////////////////////
#include "Dlg_LoftCC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftCC dialog


CDlg_LoftCC::CDlg_LoftCC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LoftCC::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LoftCC)
	m_nCurve_U	= 2;
	//}}AFX_DATA_INIT
}


void CDlg_LoftCC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LoftCC)
	DDX_Text(pDX, IDC_NODE_U, m_nCurve_U);
	DDV_MinMaxInt(pDX, m_nCurve_U, 2, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_LoftCC, CDialog)
	//{{AFX_MSG_MAP(CDlg_LoftCC)
	ON_EN_CHANGE(IDC_NODE_U, OnChangeNodeU)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftCC message handlers
BOOL CDlg_LoftCC::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////////	
  	GetDlgItem(IDC_NODE_U)->SetFocus();
	////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_LoftCC::OnOK()
{
    ///////////////////	
	CDialog::OnOK();
}

void CDlg_LoftCC::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_LoftCC::OnChangeNodeU() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    ///////////////////
}
/////////////////////////////////////// end of Module /////////////////////////
