// dlg_cmes.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_Elem.h"
#include "DrCurve.h"
////////////////////
#include "dlg_CMsN.h"	
#include "dlg_CMsU.h"

#include "dlg_cmes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CMesh dialog


CDlg_CMesh::CDlg_CMesh(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CMesh::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CMesh)
	//}}AFX_DATA_INIT
	///////////////////////////////////////////	
	m_bUnifOT 		= TRUE;			// Uniform Segmentwise
	m_bUnifTOT		= FALSE;		// Uniform on Total Length
	///////////////////////
}

void CDlg_CMesh::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CMesh)
	DDX_Text(pDX, IDC_ELOUT_UNIF, m_nMaxOSeg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CMesh, CDialog)
	//{{AFX_MSG_MAP(CDlg_CMesh)
	ON_BN_CLICKED(IDC_NONU_OT, OnNonuOt)
	ON_EN_KILLFOCUS(IDC_ELOUT_UNIF, OnKillfocusEloutUnif)
	ON_BN_DOUBLECLICKED(IDC_NONU_OT, OnNonuOt)
	ON_BN_CLICKED(IDC_UNIF_OT, OnUnifOt)
	ON_BN_DOUBLECLICKED(IDC_UNIF_OT, OnUnifOt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CMesh message handlers

BOOL CDlg_CMesh::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////
	m_nMaxOSeg 	= m_nDefOSeg;	
    //////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CMesh::OnUnifOt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_CMsU	Dlg;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_nUnifTOT 	= Dlg.m_nUnif_OT;	// for uniform OT only
		m_bUnifTOT	= TRUE;
		m_bUnifOT	= FALSE;
	}
	else
		m_bUnifTOT	= FALSE;
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CMesh::OnNonuOt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_CMsN	Dlg;
	//////////////////////////// Fill Data
	Dlg.m_pDrCurve	= m_pDrCurve; 
	Dlg.m_nSeg_DT	= m_nSeg_DT;	// L = nData - 1
	Dlg.m_nSegOut	= m_nMaxOSeg;
	Dlg.m_pOSeg		= m_pOSeg;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_nMaxOSeg 	= Dlg.m_nSegOut;	// for uniform OT only
		/////////////////////
		m_bUnifOT 	= FALSE;
	}
	else
		m_nMaxOSeg 	= m_nDefOSeg; 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}
 
void CDlg_CMesh::OnKillfocusEloutUnif()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}


void CDlg_CMesh::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}


void CDlg_CMesh::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
	///////////////
	CDialog::OnOK();
}
////////////////////////////// end of Module //////////
