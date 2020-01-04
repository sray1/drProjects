// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Obj3DMnu.h"
////////////////////
#include "DlgObj3D.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgObj3D dialog

CDlgObj3D::CDlgObj3D(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObj3D::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlgObj3D)
	m_szDrawList = "";
	//}}AFX_DATA_INIT
}

void CDlgObj3D::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgObj3D)
	DDX_LBString(pDX, IDC_DRAW_LIST, m_szDrawList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgObj3D, CDialog)
	//{{AFX_MSG_MAP(CDlgObj3D)
	ON_BN_CLICKED(IDC_DRAW_ALLACTIVE, OnClickedDrawAllactive)
	ON_BN_CLICKED(IDC_TOGGLE_ALL, OnClickedToggleAll)
	ON_BN_CLICKED(IDC_CHANGE, OnClickedChange)
	ON_BN_CLICKED(IDC_CURRENT, OnClickedCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgObj3D message handlers
////////////////////////////////
void CDlgObj3D::OnObj3DMnu()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CObj3DMnu* pObj3DMnu	 		= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	///////////////////////////////////////////////		 
	CDlgObj3D	dlg;
// save  old 
	UINT nObj3DMnu[MAX_OBJ3DMNU][2];
	
	pObj3DMnu->GetObj3DMnuArray(nObj3DMnu);
	pObj3DMnu->SetObj3DMnuOldArray(nObj3DMnu);
	
	pObj3DMnu->SetCurrentObj3DMnuOld(pObj3DMnu->GetCurrentObj3DMnu() );
	///////////////////////////////////////////////////////		
	// call dialogbox
	if(dlg.DoModal() == IDOK)
	{
	 // Do Nothing here. All Done Thro' DlgObj3DMnu  
	}
	else
	{
		// restore data
		pObj3DMnu->GetObj3DMnuOldArray(nObj3DMnu);
		pObj3DMnu->SetObj3DMnuArray(nObj3DMnu);
	
		pObj3DMnu->SetCurrentObj3DMnu(pObj3DMnu->GetCurrentObj3DMnuOld() );
		
	}
	
} 

BOOL CDlgObj3D::OnInitDialog()
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
	CObj3DMnu* pObj3DMnu	 		= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	/////////////////////////////////////		 
	CString	str = pObj3DMnu->GetObj3DMnuID(0);    // set to First One
	pWndCtrl = GetDlgItem(IDC_PATCH_ID);
	((CEdit*)(pWndCtrl))->SetWindowText(str);
	GotoDlgCtrl(pWndCtrl);
		
			 
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlgObj3D::FillListAllString()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CObj3DMnu* pObj3DMnu	 		= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	/////////////////////////////////////		 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	
	for (i=0;i<MAX_OBJ3DMNU;i++)
		((CListBox*)(pWndCtrl))->AddString(pObj3DMnu->GetObj3DMnuInfo(i)); 
    
}

void CDlgObj3D::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	for (i=0;i<MAX_OBJ3DMNU;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
void CDlgObj3D::ReFillListAllString(UINT nType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CObj3DMnu* pObj3DMnu	 		= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	////////////////////////////////////	
    UINT i;
	for (i=0;i<MAX_OBJ3DMNU;i++)
		pObj3DMnu->SetObj3DMnuInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDlgObj3D::ReFillListString(UINT i,UINT nType)
{
	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CObj3DMnu* pObj3DMnu	 		= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	////////////////////////////////////
	pObj3DMnu->SetObj3DMnuInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDlgObj3D::OnClickedDrawAllactive()
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

void CDlgObj3D::OnClickedToggleAll()
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

void CDlgObj3D::OnClickedChange()
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

void CDlgObj3D::OnClickedCurrent()
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

