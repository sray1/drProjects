// intxtdlg.cpp : implementation file
//

#include "stdafx.h"   

#include "drgraf.h"
//#include "drgrafrm.h"
#include "drgradoc.h"

#include "globals.h"

#include "drfont.h"
#include "dboxmgr.h"
 
#include "dbObject.h"
#include "intxtdlg.h"


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
	//}}AFX_DATA_INIT
}

void CInTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInTextDlg)
	DDX_Text(pDX, IDD_EDIT_LABEL, m_Text);
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
	///////////////////////
	CObjectBase*	pObjectBase;		
	int nMaxLabels 	 = pObjectBase->GetSpecificObjectCount(LABEL);
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
	CObjectBase* pObjectBase;
    CDrLabel		AddLabel;
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc); 
	///////////////////////////////////////////////
    SetInfoForDataBase(&AddLabel);
   	pObjectBase->AddObject(&AddLabel);
	////////////////////////
	CDialog::OnOK();

} 

void CInTextDlg::OnSelchangeListLabel()
{
//      case IDD_LABEL_LIST:
   	////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////	
	///////////////////////
	CObjectBase*	pObjectBase;		
	int nMaxLabels 	 = pObjectBase->GetSpecificObjectCount(LABEL);
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
	////////////////////////////////////////////////
	CObjectBase*	pObjectBase;		
	int nMaxLabels 	 = pObjectBase->GetSpecificObjectCount(LABEL);
    if(nMaxLabels>0)
    {
		CString strText;
		int nLabelType;
		int nViewNumber;
//	    int nActiveViewNumber = pWnd->GetActiveViewNumber();   // Current View Number
		CWnd* pWndCtrl = GetDlgItem(IDD_LIST_LABEL);
		/////////////////////// 
		CDrObject* pObject;			       
	
		POSITION pos = pObjectBase->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = pObjectBase->GetNextObject( pos);
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

	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	CDrFont* pDrFont   		= pDBoxMgr->GetDrFont();
	CLayer* pLayer			= pDoc->GetLayer(); 
	//////////////////////////////////////// Color/View Number 
	COLORREF Color	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
	int nType 		= 0;           // Label Type
	///////////////////////////////////////  Update Current Label
	pLabel->SetText(m_Text);
	pLabel->SetType(nType);
	pLabel->SetViewNum(m_nActiveViewNumber);
	pLabel->SetCorner(nType,m_pt,m_nActiveViewNumber); // nType = 0
	pLabel->SetColor(Color); 
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////////////
	return;
} 
///////////////////////////////// End of Module ///////////////*
