// dlg_cout.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Type.h"
#include "DListMgr.h"
#include "DrNode.h"
////////////////////
#include "CommRsrc.h"
#include "dlg_CMsN.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsN dialog


CDlg_CMsN::CDlg_CMsN(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CMsN::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CMsN)
	m_BegID 	= "";
	m_EndID 	= "";
	//}}AFX_DATA_INIT
	
}

void CDlg_CMsN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CMsN)
	DDX_Text(pDX, IDC_SEG_OT, m_nSegOut);
	DDV_MinMaxInt(pDX, m_nSegOut, 1, 999);
	DDX_Text(pDX, IDC_BEG, m_BegID);
	DDX_Text(pDX, IDC_END, m_EndID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CMsN, CDialog)
	//{{AFX_MSG_MAP(CDlg_CMsN)
	ON_BN_CLICKED(IDD_EDIT, OnClickedEdit)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_WM_DESTROY()
	ON_BN_DOUBLECLICKED(IDD_EDIT, OnClickedEdit)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_EN_CHANGE(IDC_CENTRAL_ANGLE, OnChangeCentralAngle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsN message handlers

BOOL CDlg_CMsN::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////// initialize:
	FillListAllString(); 
	////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	((CListBox*)pWndCtrl)->SetCurSel(0);  // at the beginning
	////////////////////////////////////////// disable
	GetDlgItem(IDC_BEG)->EnableWindow(FALSE);
	GetDlgItem(IDC_END)->EnableWindow(FALSE);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CMsN::OnClickedEdit()
{
//      case IDD_EDIT:   
	///////////////////////////////////////////// 
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////
 	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	int index = ((CListBox*)pWndCtrl)->GetCurSel();// save Current 
	////////////////////
  	UpdateList(index);	
	EmptyListAllString();
	FillListAllString();
	////////////////////
	((CListBox*)pWndCtrl)->SetCurSel(index);  // Set at the Current
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_CMsN::OnChangeCentralAngle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlg_CMsN::OnOK()
{ 

//      case IDD_OK:     
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	/////////////////////////////////////////////// not updated, so Add
	OnClickedEdit();
	/////////////////////////////////////////////// save info
	SetInfoForDataBase();
 	////////////////
	CDialog::OnOK();

} 

void CDlg_CMsN::OnCancel()
{
	//Should be done at Calling Routine
/*
	delete [] m_pOSeg;
	m_pOSeg = NULL;
*/
	////////////////////
	CDialog::OnCancel();
}

void CDlg_CMsN::OnSelchangeList()
{
//      case IDD_LIST:
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

void CDlg_CMsN::UpdateList(int index)
{

   	///////////////////	
	if(index>=0)
		m_pOSeg[index] = m_nSegOut;	
	/////////
	return; 
} 

void CDlg_CMsN::FillOthers(int i)
{
	POSITION pos;
	CDListMgr* pList = m_pDrCurve->GetINodeList();
	int nCount = pList->GetCount();
	/////////////
	if( ( pos = pList->FindIndex( i )) != NULL )
	{
		CDrNode* pNode 	= (CDrNode*) pList->GetAt( pos );
		m_BegID			= (pNode->GetNodeCard())->id;
	}
	if( ( pos = pList->FindIndex( (i+1)%nCount )) != NULL )
	{
		CDrNode* pNode 	= (CDrNode*) pList->GetAt( pos );
		m_EndID			= (pNode->GetNodeCard())->id;
	}
	//////////////////////////
	m_nSegOut	= m_pOSeg[i];	
} 

void CDlg_CMsN::FillListAllString()
{
			 
	CString* pBegID = new CString[m_nSeg_DT];
	CString* pEndID = new CString[m_nSeg_DT];
	////////////////////////////////////////////// Get Curve Input Data List
	CDListMgr* pList = m_pDrCurve->GetINodeList();
	int nCount = pList->GetCount();
	//////////////////////////////////////////////////////////
	if(nCount<=0)
	{
		AfxMessageBox("Please Select Curve Input Data Nodes");
		return;
	}
	//////////////////////////////////////////////////////////	
	BOOL bClosed = m_pDrCurve->IsClosed_S();
	int nSeg_DT = m_nSeg_DT;
	if(bClosed)
		nSeg_DT--;
	/////////////////////////	
	if( (nCount-1) != nSeg_DT)
	{
		AfxMessageBox("Internal Problem:\nCDlg_CMsN::FillListAllString");
		return;
	}	
	//////////////////////////////////////////////
	int i;
	////////
	POSITION pos;
	////////////////////////////////////// for closed, last seg will be done separately
	for(i=0;i<nSeg_DT;i++)
	{
		if( ( pos = pList->FindIndex( i )) != NULL )
		{
			CDrNode* pNode 	= (CDrNode*) pList->GetAt( pos );
			pBegID[i]		= (pNode->GetNodeCard())->id;
			////////////////////////////	
			if(i>0)
				pEndID[i-1]	= pBegID[i];
		}
	}
	if( ( pos = pList->FindIndex( nSeg_DT )) != NULL )
	{
		CDrNode* pNode 	= (CDrNode*) pList->GetAt( pos );
		pEndID[nSeg_DT-1]	= (pNode->GetNodeCard())->id;
	}
	///////////
	if(bClosed)
	{ 
		pBegID[m_nSeg_DT-1]	= pEndID[m_nSeg_DT-2]; 
		pEndID[m_nSeg_DT-1]	= pBegID[0];
	}	 
    //////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString	strInfo;
	char	buf[30];
    //////////////////////////////////// Pack
    for(int s=0;s<m_nSeg_DT;s++)
    {
    	strInfo = pBegID[s] + "         " + pEndID[s]; 
	    sprintf(buf,"         %d",m_pOSeg[s]);
		strInfo += buf; 
		////////////////
		((CListBox*)(pWndCtrl))->AddString(strInfo); 
	}
	/////////////////////////////////////////	
	delete [] pBegID;
	delete [] pEndID;
	/////////////////
    
} 
   
void CDlg_CMsN::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_CMsN::SetInfoForDataBase()
{
}
////////////////////////////////// end of module ///////////////////////////
