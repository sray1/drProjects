// dlg_ckno.cpp : implementation file
//

#include "stdafx.h"

#include "CommRsrc.h"
////////////////////
#include "dlg_Wts.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Wts dialog


CDlg_Wts::CDlg_Wts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Wts::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Wts)
	m_dValue 	= 0;
	m_strMore 	= "";
	//}}AFX_DATA_INIT
	m_nLast		= 0;
//	m_pWVal = new double[m_nMaxWeight]; will be done in calling routine
	////////////////////////////////	
}

void CDlg_Wts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Wts)
	DDX_Text(pDX, IDC_VALUE, m_dValue);
	DDX_Text(pDX, IDC_NREQ, m_strMore);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Wts, CDialog)
	//{{AFX_MSG_MAP(CDlg_Wts)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_BN_CLICKED(IDD_EDIT, OnEdit)
	ON_BN_DOUBLECLICKED(IDD_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Wts message handlers

BOOL CDlg_Wts::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////// How many Required
	char buf[20];
    sprintf(buf,"%d",(m_nMaxWeight - m_nLast) );
	m_strMore = buf; 
	//////////////////////////////
	FillListAllString(); 
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	((CListBox*)pWndCtrl)->SetCurSel(0);  // at the beginning
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CDlg_Wts::OnDel()
{
	//      case IDD_ADD:   
	///////////////////////////////////////////// 
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////
	char buf[50];
   	if(!m_nLast)
   		return;
   	//////////////		
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	((CListBox*)pWndCtrl)->DeleteString(index);
	////////////////////////////////////////// update
	m_nLast--; 
    sprintf(buf,"%d",(m_nMaxWeight - m_nLast) );
	m_strMore = buf; 
	/////////////////////
	EmptyListAllString();	
	FillListAllString();
	((CListBox*)pWndCtrl)->SetCurSel(0);  // at the beginning
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Wts::OnAdd()
{
	//      case IDD_ADD:   
	///////////////////////////////////////////// 
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////
	char buf[50];
   	if(m_nLast == m_nMaxWeight)
   	{
   		CString str;
    	sprintf(buf,"Got All %d Weights",m_nLast );
    	str = buf;
   		AfxMessageBox(str);
   		return;
   	}
	/////////////////////////////
	*(m_pWVal + m_nLast) = m_dValue;
	////////////////////////////////////////// update
	m_nLast++; 
    sprintf(buf,"%d",(m_nMaxWeight - m_nLast) );
	m_strMore = buf; 
	/////////////////////////////
	EmptyListAllString();	
	FillListAllString();
   	///////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	((CListBox*)pWndCtrl)->SetCurSel(m_nLast-1);  // at the current
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Wts::OnEdit()
{
	//      case IDD_Edit:   
	///////////////////////////////////////////// 
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	int index = ((CListBox*)pWndCtrl)->GetCurSel();  // 
    ////////////////////
	*(m_pWVal + index) = m_dValue;
	////////////////////////////////////////// update
	EmptyListAllString();	
	FillListAllString();
	((CListBox*)pWndCtrl)->SetCurSel(index);  // at the current
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Wts::OnOK()
{ 

//      case IDD_OK:     
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
	//////////////////////////// Adequate Number?
	if(m_nLast < m_nMaxWeight)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(50);
    	sprintf(buf,"Need %d More Weights!",m_strMore );
		AfxMessageBox(*str);
		delete str;
		return;
	}	
 	////////////////
	CDialog::OnOK();

} 

void CDlg_Wts::OnSelchangeList()
{
	//  case IDC_Weight Combo:
   	////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
	//////////////
	FillOthers(index);     
   	////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
   	///////////////////	
	
}

void CDlg_Wts::FillOthers(int i)
{
	m_dValue 	= *(m_pWVal+i);
} 

void CDlg_Wts::FillListAllString()
{
			 
	if(m_nLast<1) return;
	//////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString	strInfo;
	char	buf[20];
    //////////////////////////////////// Pack
    for(int s=0;s<m_nLast;s++)
    {
    	strInfo = "";
	    sprintf(buf,"%2d  %f",s,*(m_pWVal+s));
		strInfo += buf; 
		////////////////
		((CListBox*)(pWndCtrl))->AddString(strInfo); 
	}	
    
} 
   
void CDlg_Wts::EmptyListAllString()
{
			 
	if(m_nLast<1) return;
	//////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 
////////////////////////////////// end of module ///////////////////////////
