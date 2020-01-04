// drawbox.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Precison.h"
////////////////////
#include "Dlg_Prec.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawPrecision dialog

CDrawPrecision::CDrawPrecision(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawPrecision::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDrawPrecision)
	m_nDrawPrecision = 2;   // 2 decimal places
	//}}AFX_DATA_INIT
}

void CDrawPrecision::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawPrecision)
	DDX_Text(pDX, IDC_PRECISION, m_nDrawPrecision);
	DDV_MinMaxUInt(pDX, m_nDrawPrecision, 0, 4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawPrecision, CDialog)
	//{{AFX_MSG_MAP(CDrawPrecision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawPrecision message handlers
/////////////////////////////////////////////////////////////////////////////
void CDrawPrecision::OnPrecision()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	/////////////////////////////////////		 
	CDrawPrecision	dlg; 
	
	pPrecision->SetPrecisionOld(pPrecision->GetPrecision()); 	
	dlg.m_nDrawPrecision = pPrecision->GetPrecision();
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data
		pPrecision->SetPrecision(dlg.m_nDrawPrecision);                  
		pPrecision->SetWorldBaseOld(pPrecision->GetWorldBase());
		pPrecision->SetWorldBase( (LONG)(pow(10.,(double)dlg.m_nDrawPrecision) ) );
/*		
		// Update Total Scale Factor and MapFactor
		m_dScaleFactor = m_dScaleFactor / (double)m_lWorldBaseOld; 
		m_dScaleFactor = m_dScaleFactor * (double)m_lWorldBase;
		SetMapFactor();
*/		
		/////////////// 
/*		
		CString			m_szDrawPrecision;
		char			buf[50]; 
		sprintf(buf,"No. of Decimal Places = %u",m_nPrecision); 
		m_szDrawPrecision = buf;
		AfxMessageBox(m_szDrawPrecision);
*/
	}		
	
	
}

BOOL CDrawPrecision::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	CWnd* pWndCtrl = GetDlgItem(IDC_PRECISION);
	((CEdit*)(pWndCtrl))->LimitText(1); 
	pWndCtrl = GetDlgItem(IDC_PRECISION);
	GotoDlgCtrl(pWndCtrl);
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}
