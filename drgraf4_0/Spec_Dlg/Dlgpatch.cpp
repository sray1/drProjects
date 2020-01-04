// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "PatchMnu.h"
////////////////////
#include "DlgPatch.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPatch dialog

CDlgPatch::CDlgPatch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPatch::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlgPatch)
	m_szDrawList = "";
	//}}AFX_DATA_INIT
}

void CDlgPatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPatch)
	DDX_LBString(pDX, IDC_DRAW_LIST, m_szDrawList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgPatch, CDialog)
	//{{AFX_MSG_MAP(CDlgPatch)
	ON_BN_CLICKED(IDC_DRAW_ALLACTIVE, OnClickedDrawAllactive)
	ON_BN_CLICKED(IDC_TOGGLE_ALL, OnClickedToggleAll)
	ON_BN_CLICKED(IDC_CHANGE, OnClickedChange)
	ON_BN_CLICKED(IDC_CURRENT, OnClickedCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPatch message handlers
////////////////////////////////
void CDlgPatch::OnPatchMnu()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPatchMnu* pPatchMnu	 		= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	///////////////////////////////////////////////		 
	CDlgPatch	dlg;
// save  old 
	UINT nPatchMnu[MAX_PATCHMNU][2];
	
	pPatchMnu->GetPatchMnuArray(nPatchMnu);
	pPatchMnu->SetPatchMnuOldArray(nPatchMnu);
	
	pPatchMnu->SetCurrentPatchMnuOld(pPatchMnu->GetCurrentPatchMnu() );
	///////////////////////////////////////////////////////		
	// call dialogbox
	if(dlg.DoModal() == IDOK)
	{
	 // Do Nothing here. All Done Thro' DlgPatchMnu  
	}
	else
	{
		// restore data
		pPatchMnu->GetPatchMnuOldArray(nPatchMnu);
		pPatchMnu->SetPatchMnuArray(nPatchMnu);
	
		pPatchMnu->SetCurrentPatchMnu(pPatchMnu->GetCurrentPatchMnuOld() );
		
	}
	
} 

BOOL CDlgPatch::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent(); 
	
	/////////////////////////////////////////////
	FillListAllString();
	///////////////////// Set selection to 0
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	((CListBox*)(pWndCtrl))->SetCurSel(0);        // set to First One
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPatchMnu* pPatchMnu	 		= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	/////////////////////////////////////		 
	CString	str = pPatchMnu->GetPatchMnuID(0);    // set to First One
	pWndCtrl = GetDlgItem(IDC_PATCH_ID);
	((CEdit*)(pWndCtrl))->SetWindowText(str);
	GotoDlgCtrl(pWndCtrl);
		
			 
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlgPatch::FillListAllString()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPatchMnu* pPatchMnu	 		= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	/////////////////////////////////////		 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	
	for (i=0;i<MAX_PATCHMNU;i++)
		((CListBox*)(pWndCtrl))->AddString(pPatchMnu->GetPatchMnuInfo(i)); 
    
}

void CDlgPatch::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	for (i=0;i<MAX_PATCHMNU;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
void CDlgPatch::ReFillListAllString(UINT nType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPatchMnu* pPatchMnu	 		= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	////////////////////////////////////	
    UINT i;
	for (i=0;i<MAX_PATCHMNU;i++)
		pPatchMnu->SetPatchMnuInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDlgPatch::ReFillListString(UINT i,UINT nType)
{
	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPatchMnu* pPatchMnu	 		= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	////////////////////////////////////
	pPatchMnu->SetPatchMnuInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDlgPatch::OnClickedDrawAllactive()
{
	// TODO: Add your control notification handler code here
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	UINT i = ((CListBox*)(pWndCtrl))->GetCurSel();
	///////////////////////
	ReFillListAllString(1);	
	////////////////////// Set selection back
	((CListBox*)(pWndCtrl))->SetCurSel(i);
	GotoDlgCtrl(pWndCtrl);
}

void CDlgPatch::OnClickedToggleAll()
{
	// TODO: Add your control notification handler code here
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	UINT i = ((CListBox*)(pWndCtrl))->GetCurSel(); 
	//////////////////////
	ReFillListAllString(5);
	///////////////////// Set selection back
	((CListBox*)(pWndCtrl))->SetCurSel(i);
	GotoDlgCtrl(pWndCtrl);
}

void CDlgPatch::OnClickedChange()
{
	// TODO: Add your control notification handler code here
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	UINT i = ((CListBox*)(pWndCtrl))->GetCurSel();
	////////////////////////
	ReFillListString( i ,5);
	////////////////////////set selection back	
	((CListBox*)(pWndCtrl))->SetCurSel(i);
	GotoDlgCtrl(pWndCtrl);
	
}

void CDlgPatch::OnClickedCurrent()
{
	// TODO: Add your control notification handler code here
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	UINT i = ((CListBox*)(pWndCtrl))->GetCurSel();
	////////////////////////
	ReFillListString( i ,3);
	////////////////////////		
	((CListBox*)(pWndCtrl))->SetCurSel(i);
	GotoDlgCtrl(pWndCtrl);
	
}
/////////////////////////////////// end of Module /////////////////////////
