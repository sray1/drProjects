// dlg_cpro.cpp : implementation file
//

#include "stdafx.h"

////////////////////
#include "dlg_CTim.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CTim dialog


CDlg_CTim::CDlg_CTim(CWnd* /*pWnd*/)
	: CDialog()                    // Modeless constructor
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CTim)
	//}}AFX_DATA_INIT
}

void CDlg_CTim::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CTim)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CTim, CDialog)
	//{{AFX_MSG_MAP(CDlg_CTim)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CTim message handlers

BOOL CDlg_CTim::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
    ///////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_CTim::Create ()
{
	BOOL bOk;
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(hInstResourceClient); // uses Applic's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	///////////////////////////////////////////////////////////// 
	bOk = CDialog::Create(CDlg_CTim::IDD);
	/////////////////////////////////////// 
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
	//////////////////
	return bOk;
}


void CDlg_CTim::EmptyListAllString(UINT DlgID)
{
			 
	CWnd* pWndCtrl = GetDlgItem(DlgID);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_CTim::OnOK()
{
	// DONE
    ///////////////////	
	CDialog::OnOK();
}

void CDlg_CTim::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}
////////////////////////////////////// end of Module ///////////////////////////
