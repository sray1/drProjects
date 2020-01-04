// dlg_rend.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "dlg_rend.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Rend dialog


CDlg_Rend::CDlg_Rend(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Rend::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Rend)
	m_Absorp 		= 0;
	m_bAmb 			= FALSE;
	m_bCull 		= TRUE;
	m_Diff_Coef 	= 0;
	m_bDist 		= FALSE;
	m_bFrame 		= FALSE;
	m_bHazing 		= FALSE;
	m_bLight 		= FALSE;
	m_Refr_Coef 	= 0;
	m_bShadow 		= FALSE;
	m_SpecIndex 	= 0;
	m_Spec_Coef 	= 0;
	m_Transm_Coef 	= 0;
	m_bTurbul 		= FALSE;
	m_bWireF 		= FALSE;
	//}}AFX_DATA_INIT 
	m_crColor_Ambi 	= RGB(0,255,0);
	m_crColor_Fram 	= RGB(255,0,0);
	m_crColor_Refl 	= RGB(0,0,255);
}

void CDlg_Rend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Rend)
	DDX_Text(pDX, IDC_ABSORPTION, m_Absorp);
	DDV_MinMaxDouble(pDX, m_Absorp, 0., 1.);
	DDX_Check(pDX, IDC_AMBIENT_EFF, m_bAmb);
	DDX_Check(pDX, IDC_CULL, m_bCull);
	DDX_Text(pDX, IDC_DIFFUSION, m_Diff_Coef);
	DDV_MinMaxDouble(pDX, m_Diff_Coef, 0., 1.);
	DDX_Check(pDX, IDC_DISTANCE_EFF, m_bDist);
	DDX_Check(pDX, IDC_FRAMING, m_bFrame);
	DDX_Check(pDX, IDC_HAZING_EFF, m_bHazing);
	DDX_Check(pDX, IDC_LSOURCE, m_bLight);
	DDX_Text(pDX, IDC_REFRACTION, m_Refr_Coef);
	DDV_MinMaxDouble(pDX, m_Refr_Coef, 0., 1.);
	DDX_Check(pDX, IDC_SHADOW_EFF, m_bShadow);
	DDX_Text(pDX, IDC_SPECINDEX, m_SpecIndex);
	DDX_Text(pDX, IDC_SPECULAR, m_Spec_Coef);
	DDV_MinMaxDouble(pDX, m_Spec_Coef, 0., 1.);
	DDX_Text(pDX, IDC_TRANSMISSION, m_Transm_Coef);
	DDV_MinMaxDouble(pDX, m_Transm_Coef, 0., 1.);
	DDX_Check(pDX, IDC_TURBULENCE_EFF, m_bTurbul);
	DDX_Check(pDX, IDC_WIREFRAME, m_bWireF);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Rend, CDialog)
	//{{AFX_MSG_MAP(CDlg_Rend)
	ON_BN_CLICKED(IDC_AMB_COLR, OnAmbColr)
	ON_BN_CLICKED(IDC_FRM_COLR, OnFrmColr)
	ON_BN_CLICKED(IDC_REFL_COLR, OnReflColr)
	ON_BN_CLICKED(IDC_TEXTURE, OnTexture)
	ON_BN_DOUBLECLICKED(IDC_AMB_COLR, OnAmbColr)
	ON_BN_DOUBLECLICKED(IDC_FRM_COLR, OnFrmColr)
	ON_BN_DOUBLECLICKED(IDC_REFL_COLR, OnReflColr)
	ON_BN_DOUBLECLICKED(IDC_TEXTURE, OnTexture)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Rend message handlers

BOOL CDlg_Rend::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////// Paint Static Boxes
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Rend::OnAmbColr()
{

	CColorDialog	ColorDlg;
	
	ColorDlg.m_cc.Flags |= CC_RGBINIT;
	ColorDlg.m_cc.rgbResult = m_crColor_Ambi;

	if(ColorDlg.DoModal() ==IDOK)
		m_crColor_Ambi = ColorDlg.GetColor();
	///////////////////////////////	
	Invalidate();
	UpdateWindow();
	///////////////   
}

void CDlg_Rend::OnFrmColr()
{

	CColorDialog	ColorDlg;
	
	ColorDlg.m_cc.Flags |= CC_RGBINIT;
	ColorDlg.m_cc.rgbResult = m_crColor_Fram;

	if(ColorDlg.DoModal() ==IDOK)
		m_crColor_Fram = ColorDlg.GetColor();
	///////////////////////////////////////////   
	Invalidate();
	UpdateWindow();
	///////////////   
	
}

void CDlg_Rend::OnReflColr()
{

	CColorDialog	ColorDlg;
	
	ColorDlg.m_cc.Flags |= CC_RGBINIT;
	ColorDlg.m_cc.rgbResult = m_crColor_Refl;

	if(ColorDlg.DoModal() ==IDOK)
		m_crColor_Refl = ColorDlg.GetColor();
	///////////////////////////////////////////   
	Invalidate();
	UpdateWindow();
	///////////////   
	
}

void CDlg_Rend::OnTexture()
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_Rend::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_Rend::OnOK()
{
	// TODO: Add extra validation here
	
	/////////////////
	UpdateData(TRUE);
	/////////////////
	CDialog::OnOK();
}

void CDlg_Rend::OnPaint()
{

	CPaintDC dc(this);
	///////////////////
	CStatic* pWndCntrl;
	///////////////////////////////////////////	
	pWndCntrl = (CStatic*)GetDlgItem(IDC_SAMPLE_AMBI);
	pWndCntrl->InvalidateRect(NULL,TRUE);
	pWndCntrl->UpdateWindow();
	//////////
	DrawSample(pWndCntrl,m_crColor_Ambi);
	///////////////////////////////////////////   
	pWndCntrl = (CStatic*)GetDlgItem(IDC_SAMPLE_REFL);
	pWndCntrl->InvalidateRect(NULL,TRUE);
	pWndCntrl->UpdateWindow();
	//////////
	DrawSample(pWndCntrl,m_crColor_Refl);
	///////////////////////////////////////////   
	pWndCntrl = (CStatic*)GetDlgItem(IDC_SAMPLE_FRAM);
	pWndCntrl->InvalidateRect(NULL,TRUE);
	pWndCntrl->UpdateWindow();
	//////////
	DrawSample(pWndCntrl,m_crColor_Fram);
	///////////////////////////////////////////   
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlg_Rend::DrawSample(CStatic* pWndCntrl,COLORREF crColor)
{
    CRect	RectSample;
	pWndCntrl->GetClientRect(&RectSample);
	////////////////////////
	CClientDC dc(pWndCntrl);
	////////////////////////	
   	CBrush  Brush;
   	CBrush* PtrOldBrush;
    /////////////////////////////////////////////////// 
    Brush.CreateSolidBrush(crColor);
    PtrOldBrush= dc.SelectObject(&Brush); 
    ////////////////////////////
//    dc.DPtoLP(&RectSample);
    dc.Rectangle(&RectSample);
    ////////////////////////////
    dc.SelectObject(PtrOldBrush);             
    Brush.DeleteObject(); 
    /////////////////////
    
}

////////////////////////////// end of module //////////////
