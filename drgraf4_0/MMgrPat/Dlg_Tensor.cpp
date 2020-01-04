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
#include "dlg_Tang.h"
//////////////////////
#include "Dlg_Tensor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Tensor dialog


CDlg_Tensor::CDlg_Tensor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Tensor::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Tensor)
	m_nNode_U	= 2;
	m_nNode_V	= 2;
	m_nNode_Tot = 0;
	//}}AFX_DATA_INIT
}


void CDlg_Tensor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Tensor)
	DDX_Text(pDX, IDC_NODE_U, m_nNode_U);
	DDV_MinMaxInt(pDX, m_nNode_U, 2, 9999);
	DDX_Text(pDX, IDC_NODE_V, m_nNode_V);
	DDV_MinMaxInt(pDX, m_nNode_V, 2, 9999);
	DDX_Text(pDX, IDC_NODE_TOT, m_nNode_Tot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Tensor, CDialog)
	//{{AFX_MSG_MAP(CDlg_Tensor)
	ON_EN_CHANGE(IDC_NODE_V, OnChangeNodeV)
	ON_EN_CHANGE(IDC_NODE_U, OnChangeNodeU)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Tensor message handlers
BOOL CDlg_Tensor::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////////
	m_nNode_Tot = m_nNode_U * m_nNode_V; 
	////////////////////////////////////	
  	GetDlgItem(IDC_NODE_U)->SetFocus();
	////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Tensor::OnOK()
{
    ///////////////////	
	CDialog::OnOK();
}

void CDlg_Tensor::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_Tensor::OnChangeNodeV() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
	m_nNode_Tot = m_nNode_U * m_nNode_V; 
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    ///////////////////
}

void CDlg_Tensor::OnChangeNodeU() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
	m_nNode_Tot = m_nNode_U * m_nNode_V; 
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    ///////////////////
}
/////////////////////////////////////// end of Module /////////////////////////
