// intxtdlg.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Layer.h"
#include "DrFont.h"
#include "drpen.h"
////////////////////
#include "dlg_ilab.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CInTextDlg dialog

CInTextDlg::CInTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInTextDlg::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CInTextDlg)
	m_Text = "";
	m_nTextAngle = 0;
	//}}AFX_DATA_INIT
}

void CInTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInTextDlg)
	DDX_Text(pDX, IDD_EDIT_LABEL, m_Text);
	DDX_Text(pDX, IDC_TEXT_ANGLE, m_nTextAngle);
	DDV_MinMaxInt(pDX, m_nTextAngle, -360, 360);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInTextDlg, CDialog)
	//{{AFX_MSG_MAP(CInTextDlg)
	ON_LBN_SELCHANGE(IDD_LIST_LABEL, OnSelchangeListLabel)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_LBN_DBLCLK(IDD_LIST_LABEL, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInTextDlg message handlers

BOOL CInTextDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
	/////////////////////////////////////////////
	int nMaxLabels 	 = pDListMgr->GetSpecificObjectCount(LABEL);
    CWnd* pWndCtrl;
	if(nMaxLabels>0)
	{
		FillListAllString(); 
		pWndCtrl = GetDlgItem(IDD_LIST_LABEL);
		((CListBox*)pWndCtrl)->SetCurSel(0); 
	}
	////////////////////////////////////// set focus
	pWndCtrl = GetDlgItem(IDD_EDIT_LABEL);
	GotoDlgCtrl(pWndCtrl);
	//////////////////
    UpdateData(FALSE);
    //////////////////
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CInTextDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CInTextDlg::OnOK()
{
//      case IDD_OK:     
	//////////////////
	UpdateData(TRUE);
	//////////////////
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 		= pDoc->GetObjectMgr();
	/////////////////////////////////////////////
	int nActiveIndex;
    CDrLabel* pAdd 	= (CDrLabel*)(pObjectMgr->AddToDataBase(nActiveIndex,LABEL));
    SetInfoForDataBase(pAdd);
    //////////////////////////////////////////////////////////////////////////////// Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,LABEL);
	////////////////////////
	CDialog::OnOK();

} 

void CInTextDlg::OnSelchangeListLabel()
{
//      case IDD_LABEL_LIST:
   	////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
	/////////////////////////////////////////////
	int nMaxLabels 	 = pDListMgr->GetSpecificObjectCount(LABEL);
	if (nMaxLabels>0)
	{
		CWnd* pWndCtrl = GetDlgItem(IDD_LIST_LABEL);
    	int index = ((CListBox*)pWndCtrl)->GetCurSel();
    	((CListBox*)pWndCtrl)->GetText(index,m_Text);
		///////////////////// Set selection back
		((CListBox*)(pWndCtrl))->SetCurSel(index);
		GotoDlgCtrl(pWndCtrl);
    	////////////////////
		UpdateData(FALSE);			//TO Screen(FALSE)    
    	///////////////////	
	}
	// TODO: Add your control notification handler code here
	
}
////////////////////////////////////////////////////////////// HELPERS
void CInTextDlg::FillListAllString()
{
			 
//	CDrGrafFrame* pWnd= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
	/////////////////////////////////////////////
	int nMaxLabels 	 = pDListMgr->GetSpecificObjectCount(LABEL);
    if(nMaxLabels>0)
    {
		CString strText;
		int nLabelType;
		int nViewNumber;
//	    int nActiveViewNumber = pWnd->GetActiveViewNumber();   // Current View Number
		CWnd* pWndCtrl = GetDlgItem(IDD_LIST_LABEL);
		/////////////////////// 
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == LABEL)
			{ 
				CDrLabel* pLabel = (CDrLabel*)pObject;
				nLabelType 	= pLabel->GetType();
				nViewNumber = pLabel->GetViewNum();
				////////////////////////////////// if Node Label(-1), SKIP
				////////////////////////////////// Add only Current View Labels
				if((nLabelType != -1) && (nViewNumber == m_nActiveViewNumber))
				{											
					strText 	= pLabel->GetText();
					((CListBox*)(pWndCtrl))->AddString(strText);
				}	
			}	
    	}
	} 
    
}
    
void CInTextDlg::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST_LABEL);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CInTextDlg::SetInfoForDataBase(CDrLabel* pLabel)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
 	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////// Color/View Number 
	COLORREF Color	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
	///////////////////////////////////////  Update Current Label
	/////////////////////////////////////////////////
	pLabel->SetObjectType((int)LABEL);
	pLabel->SetElemType((int)DRAW_OBJECT);              // globals.h
    pLabel->SetLevelType((int)LEVEL_GRAPA);         // globals
	/////////////////////////////////////////////////
	pLabel->SetText(m_Text);
	pLabel->SetType(LABEL_SCREEN);
	pLabel->SetViewNum(m_nActiveViewNumber);
	pLabel->SetCorner(m_pt,m_nActiveViewNumber); // 
	pLabel->SetMoved(TRUE);   // forces coord. to be recognized on 2D basis     
	pLabel->SetColor(Color); 
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	pLabel->SetAngle(m_nTextAngle);
	///////////////////////////////////////////////
	pLabel->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	///////////////////////////////
	return;
} 
///////////////////////////////// End of Module ///////////////*
