// drawbox.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

//#include "Def_Lims.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Toler.h"
#include "HitNet.h"
////////////////////
#include "Dlg_HNet.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_HNet dialog

CDlg_HNet::CDlg_HNet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_HNet::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_HNet)
	m_nPixNet		= NET_PIXEL;
	m_dPhysNet		= NET_DOUBLE;
	m_dCoLinear		= 0.0;
	m_dCoPlanar		= 0.0;
	m_dRatio		= 0.0;
	m_NodeMerge_Y = 0.0;
	m_NodeMerge_X = 0.0;
	m_NodeMerge_Z = 0.0;
	//}}AFX_DATA_INIT
}

void CDlg_HNet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_HNet)
	DDX_Text(pDX, IDC_PIXELNET, m_nPixNet);
	DDV_MinMaxInt(pDX, m_nPixNet, 0, 1000);
	DDX_Text(pDX, IDC_PHYSNET, m_dPhysNet);
	DDV_MinMaxDouble(pDX, m_dPhysNet, 0., 9999.);
	DDX_Text(pDX, IDC_COLINEAR, m_dCoLinear);
	DDX_Text(pDX, IDC_COPLANAR, m_dCoPlanar);
	DDX_Text(pDX, IDC_DRATIO, m_dRatio);
	DDX_Text(pDX, IDC_NODEMERGE_Y, m_NodeMerge_Y);
	DDX_Text(pDX, IDC_NODEMERGE_X, m_NodeMerge_X);
	DDX_Text(pDX, IDC_NODEMERGE_Z, m_NodeMerge_Z);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_HNet, CDialog)
	//{{AFX_MSG_MAP(CDlg_HNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_HNet message handlers
/////////////////////////////////////////////////////////////////////////////
void CDlg_HNet::OnHitNet()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
	/////////////////////////////////////////////////
	long lWorldBase			= (long) pPrecision->GetWorldBase();
	double dWorldBase		= (double)lWorldBase;
	double dMapFactor		= pMapFactor->GetMapFactor();
	/////////////////////////////////////		 
	CDlg_HNet	dlg; 
	
	pHitNet->SetSearchNetOld(pHitNet->GetSearchNet()); 	
	dlg.m_nPixNet = pHitNet->GetSearchNet();
	pHitNet->SetSearchDetOld(pHitNet->GetSearchDet()); 	
	double dNet = pHitNet->GetSearchDet();
	//////////////////////////////////////////////////////////////// Strip dTol
	double dTol				= pHitNet->GetSearchDet(); 
	//////////////////////// Precision 
   	dTol /= dWorldBase;
   	//////////////////////// Map Factor
   	dTol *= dMapFactor;
	//////////////////////// Scaled Coord
	pObjectMgr->DStoSC(&dTol);
	//////////////////////////////////////
	dlg.m_dPhysNet = dTol;
	/////////////////////////
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data
		//////////////////////////////////////////////////////////////// Update dTol
		double dTol	= dlg.m_dPhysNet; 
 		//////////////////////// Scaled Coord
		pObjectMgr->SCtoDS(&dTol);
   		//////////////////////// Map Factor
   		dTol /= dMapFactor;
		//////////////////////// Precision 
   		dTol *= dWorldBase;
		//////////////////////////////////////////////////////////////// Save
		pHitNet->SetSearchNet(dlg.m_nPixNet); 	
		pHitNet->SetSearchDet(dTol); 
		pHitNet->SetCoLinear(dlg.m_dCoLinear);
		pHitNet->SetCoPlanar(dlg.m_dCoPlanar);
		pHitNet->SetDblRatio(dlg.m_dRatio);
		pHitNet->SetMergeNode_X(dlg.m_NodeMerge_X);
		pHitNet->SetMergeNode_Y(dlg.m_NodeMerge_Y);
		pHitNet->SetMergeNode_Z(dlg.m_NodeMerge_Z);
		/////////////////////////////////
	}		
	
}

BOOL CDlg_HNet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	GetDlgItem(IDC_PIXELNET)->SetFocus();
//	GotoDlgCtrl(pWndCtrl);
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}
