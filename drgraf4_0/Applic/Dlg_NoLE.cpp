// Dlg_Shrink.cpp : implementation file
//

#include "stdafx.h"
#include "drgraf.h"
#include "Dlg_NoLE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_NoLabELem dialog


CDlg_NoLabELem::CDlg_NoLabELem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_NoLabELem::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_NoLabELem)
	m_bNone		= TRUE;
	m_bAll		= FALSE;
	m_bBallJt	= FALSE;
	m_bBeam		= FALSE;
	m_bElbow	= FALSE;
	m_bHexa		= FALSE;
	m_bPenta	= FALSE;
	m_bPipe		= FALSE;
	m_bQu_12	= FALSE;
	m_bQu_16	= FALSE;
	m_bQu_4		= FALSE;
	m_bQu_8		= FALSE;
	m_bQu_9		= FALSE;
	m_bTetra	= FALSE;
	m_bTr_10	= FALSE;
	m_bTr_3		= FALSE;
	m_bTr_6		= FALSE;
	m_bTr_9		= FALSE;
	m_bTruss	= FALSE;
		//}}AFX_DATA_INIT
}


void CDlg_NoLabELem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_NoLabELem)
	DDX_Check(pDX, IDC_BALLJT, m_bBallJt);
	DDX_Check(pDX, IDC_BEAM, m_bBeam);
	DDX_Check(pDX, IDC_ELBOW, m_bElbow);
	DDX_Check(pDX, IDC_HEXA, m_bHexa);
	DDX_Check(pDX, IDC_NOSHOW_ALL, m_bAll);
	DDX_Check(pDX, IDC_NOSHOW_NONE, m_bNone);
	DDX_Check(pDX, IDC_PENTA, m_bPenta);
	DDX_Check(pDX, IDC_PIPE, m_bPipe);
	DDX_Check(pDX, IDC_QU_12, m_bQu_12);
	DDX_Check(pDX, IDC_QU_16, m_bQu_16);
	DDX_Check(pDX, IDC_QU_4, m_bQu_4);
	DDX_Check(pDX, IDC_QU_8, m_bQu_8);
	DDX_Check(pDX, IDC_QU_9, m_bQu_9);
	DDX_Check(pDX, IDC_TETRA, m_bTetra);
	DDX_Check(pDX, IDC_TR_10, m_bTr_10);
	DDX_Check(pDX, IDC_TR_3, m_bTr_3);
	DDX_Check(pDX, IDC_TR_6, m_bTr_6);
	DDX_Check(pDX, IDC_TR_9, m_bTr_9);
	DDX_Check(pDX, IDC_TRUSS, m_bTruss);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_NoLabELem, CDialog)
	//{{AFX_MSG_MAP(CDlg_NoLabELem)
	ON_BN_CLICKED(IDC_NOSHOW_ALL, OnNoshowAll)
	ON_BN_DOUBLECLICKED(IDC_NOSHOW_ALL, OnNoshowAll)
	ON_BN_CLICKED(IDC_NOSHOW_NONE, OnNoshowNone)
	ON_BN_DOUBLECLICKED(IDC_NOSHOW_NONE, OnNoshowNone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_NoLabELem message handlers

BOOL CDlg_NoLabELem::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_NoLabELem::OnNoshowAll() 
{
	////////////////////
	UpdateData(TRUE);
	////////////////////
	if(m_bAll)
	{
		m_bNone		= FALSE;
		////////////////////
		m_bBallJt	= TRUE;
		m_bBeam		= TRUE;
		m_bElbow	= TRUE;
		m_bHexa		= TRUE;
		m_bPenta	= TRUE;
		m_bPipe		= TRUE;
		m_bQu_12	= TRUE;
		m_bQu_16	= TRUE;
		m_bQu_4		= TRUE;
		m_bQu_8		= TRUE;
		m_bQu_9		= TRUE;
		m_bTetra	= TRUE;
		m_bTr_10	= TRUE;
		m_bTr_3		= TRUE;
		m_bTr_6		= TRUE;
		m_bTr_9		= TRUE;
		m_bTruss	= TRUE;
	}
	////////////////////
	UpdateData(FALSE);
	////////////////////
}

void CDlg_NoLabELem::OnNoshowNone() 
{
	////////////////////
	UpdateData(TRUE);
	////////////////////
	if(m_bNone)
	{
		m_bAll		= FALSE;
		////////////////////
		m_bBallJt	= FALSE;
		m_bBeam		= FALSE;
		m_bElbow	= FALSE;
		m_bHexa		= FALSE;
		m_bPenta	= FALSE;
		m_bPipe		= FALSE;
		m_bQu_12	= FALSE;
		m_bQu_16	= FALSE;
		m_bQu_4		= FALSE;
		m_bQu_8		= FALSE;
		m_bQu_9		= FALSE;
		m_bTetra	= FALSE;
		m_bTr_10	= FALSE;
		m_bTr_3		= FALSE;
		m_bTr_6		= FALSE;
		m_bTr_9		= FALSE;
		m_bTruss	= FALSE;
	}
	////////////////////
	UpdateData(FALSE);
	////////////////////
}
//////////////////// end of module //////////////////

