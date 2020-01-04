// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "ScaleFac.h"
////////////////////
#include "Dlg_SFac.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////
// CDrawScale dialog

CDrawScale::CDrawScale(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawScale::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDrawScale)
	m_dScaleFactor = 0;
	//}}AFX_DATA_INIT
}

void CDrawScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawScale)
	DDX_Text(pDX, IDC_SCALE_FACTOR, m_dScaleFactor);
	DDV_MinMaxDouble(pDX, m_dScaleFactor, 1.e-006, 999999.);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawScale, CDialog)
	//{{AFX_MSG_MAP(CDrawScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawScale message handlers
/////////////////////////////////////////////////////////////////////////////
void CDrawScale::OnScalefactor()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 		= pDoc->GetObjectMgr();
	CScaleFactor* pScaleFactor	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////		 
	CDrawScale		dlg;
	                        
	                        
	pScaleFactor->SetScaleFactorOld(pScaleFactor->GetScaleFactor() ); 
	// show only Scale Factor
//	dlg.m_dScaleFactor = m_dScaleFactor/(double)GetWorldBase();
	dlg.m_dScaleFactor = pScaleFactor->GetScaleFactor();
	                        
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data: Save with precision
//		m_dScaleFactor = dlg.m_dScaleFactor * (double)GetWorldBase(); 
		pScaleFactor->SetScaleFactor(dlg.m_dScaleFactor); 
		//////////////////////////////////// Update MapFactor
//		pMapFactor->SetMapFactor();
		/////////////////////
/*		
		CString			m_szDrawScaleFactor;
		char			buf[50];

		sprintf(buf,"Scale Factor 1: %u ",m_nScaleFactor);
		m_szDrawScaleFactor = buf;  
		AfxMessageBox(m_szDrawScaleFactor);
*/	
	}		
	
}

BOOL CDrawScale::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent(); 
	CWnd* pWndCtrl = GetDlgItem(IDC_SCALE_FACTOR);
	((CEdit*)(pWndCtrl))->LimitText(7); 
	pWndCtrl = GetDlgItem(IDC_SCALE_FACTOR);
	GotoDlgCtrl(pWndCtrl);
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}
