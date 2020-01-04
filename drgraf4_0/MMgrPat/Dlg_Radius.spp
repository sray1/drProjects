// dlg_ckno.cpp : implementation file
//

#include "stdafx.h"

#include "CommRsrc.h"
#include "MCurRsrc.h"
////////////////////
#include "dlg_Radius.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Radius dialog


CDlg_Radius::CDlg_Radius(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Radius::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Radius)
	m_dValue 	= 0;
	m_strMore 	= "";
	m_dStep		= 0;
	m_dScale	= 1.0;
	//}}AFX_DATA_INIT
	m_nLast		= 0;
//	m_pRadius = new double[m_nMaxRadius]; will be done in calling routine
	////////////////////////////////	
}

void CDlg_Radius::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Radius)
	DDX_Text(pDX, IDC_VALUE, m_dValue);
	DDX_Text(pDX, IDC_NREQ, m_strMore);
	DDX_Text(pDX, IDC_STEP, m_dStep);
	DDX_Text(pDX, IDC_MULTIPLIER, m_dScale);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Radius, CDialog)
	//{{AFX_MSG_MAP(CDlg_Radius)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Radius message handlers

BOOL CDlg_Radius::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////// How many Required
	char buf[20];
    sprintf(buf,"%d",(m_nMaxRadius - m_nLast) );
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


void CDlg_Radius::OnDel()
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
    sprintf(buf,"%d",(m_nMaxRadius - m_nLast) );
	m_strMore = buf; 
	/////////////////////
	EmptyListAllString();	
	FillListAllString();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Radius::OnAdd()
{
	//      case IDD_ADD:   
	///////////////////////////////////////////// 
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////
	char buf[50];
   	if(m_nLast == m_nMaxRadius)
   	{
   		CString str;
    	sprintf(buf,"Got All %d Radius Factors",m_nLast );
    	str = buf;
   		AfxMessageBox(str);
   		return;
   	}
   	double dValue = m_dValue + m_dStep;
	/////////////////////////////
	*(m_pRadius + m_nLast) = dValue;
	////////////////////////////////////////// update
	m_nLast++; 
    sprintf(buf,"%d",(m_nMaxRadius - m_nLast) );
	m_strMore = buf; 
	/////////////////////////////
	EmptyListAllString();	
	FillListAllString();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Radius::OnOK()
{ 

//      case IDD_OK:     
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	/////////////////////////////////////////////// not updated, so edit
	if(m_nLast < m_nMaxRadius)
		OnAdd();
	//////////////////////////// Adequate Number?
	if(m_nLast < m_nMaxRadius)
	{
		CString str;
		char buf[50];
    	sprintf(buf,"Need %d More Twist Factors!",m_strMore );
		str = buf;
		AfxMessageBox(str);
		return;
	}	
 	////////////////
	CDialog::OnOK();

} 

void CDlg_Radius::OnSelchangeList()
{
	//  case IDC_KNOT Combo:
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

void CDlg_Radius::FillOthers(int i)
{
	m_dValue 	= *(m_pRadius+i);
} 

void CDlg_Radius::FillListAllString()
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
	    sprintf(buf,"%f",*(m_pRadius+s));
		strInfo += buf; 
		////////////////
		((CListBox*)(pWndCtrl))->AddString(strInfo); 
	}	
    
} 
   
void CDlg_Radius::EmptyListAllString()
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
