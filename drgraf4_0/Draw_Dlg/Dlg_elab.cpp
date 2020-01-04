// elab_dlg.cpp : implementation file for Editing Label
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Layer.h"
#include "DrFont.h"
////////////////////
#include "dlg_elab.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CEditLabel dialog

CEditLabel::CEditLabel(CWnd* pParent /*=NULL*/)
	: CDialog(CEditLabel::IDD, pParent)
{
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CEditLabel)
	m_EditedLabel = "";
	//}}AFX_DATA_INIT
}

void CEditLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditLabel)
	DDX_Text(pDX, IDC_EDIT_LABEL, m_EditedLabel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditLabel, CDialog)
	//{{AFX_MSG_MAP(CEditLabel)
	ON_BN_CLICKED(IDC_EDIT, OnClickedEdit)
	ON_BN_CLICKED(IDC_DELETE, OnClickedDelete)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_EDIT, OnClickedEdit)
	ON_BN_DOUBLECLICKED(IDC_DELETE, OnClickedDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditLabel message handlers


BOOL CEditLabel::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	buttonCancel.SubclassDlgItem(IDCANCEL,this); 
	buttonCancel.SizeToContent();
    ///////////////////////////////////////
    CWnd* pWndCtrl;
	////////////////////////////////////// set focus
	pWndCtrl = GetDlgItem(IDC_EDIT_LABEL);
	GotoDlgCtrl(pWndCtrl);
	//////////////////
    UpdateData(FALSE);
    //////////////////
	return FALSE;  // return TRUE  unless you set the focus to a control
	
}

void CEditLabel::OnOK()
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CEditLabel::OnClickedEdit()
{
//      case IDD_EDIT:   
	//////////////////////////////////
	UpdateData(TRUE);
	///////////////// 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
	/////////////////////////////////////////////
	int nMaxLabels;                   
	//////////////////////////
	nMaxLabels = pDListMgr->GetSpecificObjectCount(LABEL);  
	if (!nMaxLabels) 
		return;
	///////////////////////////// Edit save
	CDrLabel* pLabel 	= (CDrLabel*)pDListMgr->GetObject(m_nLabelIndex);
	SetInfoForDataBase(pLabel);
	pDListMgr->EditObject(m_nLabelIndex,pLabel);
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
	///////////////////	
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
//	return;
	
}

void CEditLabel::OnClickedDelete()
{
	// TODO: Add your control notification handler code here
//       case IDD_DEL:
	////////////////
	UpdateData(TRUE);
	/////////////////
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////
	CString strDel = "DELETING: " + m_EditedLabel + "\nAre You Sure !!"; 
	if(AfxMessageBox("Are You Sure !!",MB_YESNO) == IDNO)
		return; 
	//////////////////////////////////////////////////////////////// DELETE
	pObjectMgr->DeleteFromDataBase(m_nLabelIndex, LABEL);
	////////////////////
   	m_EditedLabel = "";
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
   	////////////////////
	CDialog::OnOK();
	// TODO: Add your control notification handler code here
//	return;
	
}
////////////////////////////////////////////////////////////// HELPERS
void CEditLabel::SetInfoForDataBase(CDrLabel* pLabel)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////// Color/View Number 
	COLORREF Color	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
	//////////////////////////////////////////////// Update Current Label
	pLabel->SetText(m_EditedLabel); 
	pLabel->SetColor(Color);	
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////////////
} 
///////////////////////////////// End of Module ///////////////


