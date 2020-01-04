// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Layer.h"
////////////////////
#include "Dlg_Layr.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLayer dialog

CDrawLayer::CDrawLayer(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawLayer::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDrawLayer)
	m_szDrawList = "";
	//}}AFX_DATA_INIT
}

void CDrawLayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawLayer)
	DDX_LBString(pDX, IDC_DRAW_LIST, m_szDrawList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawLayer, CDialog)
	//{{AFX_MSG_MAP(CDrawLayer)
	ON_BN_CLICKED(IDC_DRAW_ALLACTIVE, OnClickedDrawAllactive)
	ON_BN_CLICKED(IDC_TOGGLE_ALL, OnClickedToggleAll)
	ON_BN_CLICKED(IDC_CHANGE, OnClickedChange)
	ON_BN_CLICKED(IDC_CURRENT, OnClickedCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLayer message handlers
////////////////////////////////
void CDrawLayer::OnLayer()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CLayer* pLayer	 		= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	/////////////////////////////////////		 
	CDrawLayer	dlg;
// save  old 
	UINT nLayer[MAX_LAYER][2];
	
	pLayer->GetLayerArray(nLayer);
	pLayer->SetLayerOldArray(nLayer);
	
	pLayer->SetCurrentLayerOld(pLayer->GetCurrentLayer() );
	///////////////////////////////////////////////////////		
	// call dialogbox
	if(dlg.DoModal() == IDOK)
	{
	 // Do Nothing here. All Done Thro' DlgLayer  
	}
	else
	{
		// restore data
		pLayer->GetLayerOldArray(nLayer);
		pLayer->SetLayerArray(nLayer);
	
		pLayer->SetCurrentLayer(pLayer->GetCurrentLayerOld() );
		
	}
	
} 

BOOL CDrawLayer::OnInitDialog()
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
	((CListBox*)(pWndCtrl))->SetCurSel(0);
	GotoDlgCtrl(pWndCtrl);
		
			 
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDrawLayer::FillListAllString()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CLayer* pLayer	 		= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	/////////////////////////////////////		 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	
	for (i=0;i<MAX_LAYER;i++)
		((CListBox*)(pWndCtrl))->AddString(pLayer->GetLayerInfo(i)); 
    
}

void CDrawLayer::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDC_DRAW_LIST);
	
    UINT i;
	for (i=0;i<MAX_LAYER;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
void CDrawLayer::ReFillListAllString(UINT nType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CLayer* pLayer	 		= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	////////////////////////////////////	
    UINT i;
	for (i=0;i<MAX_LAYER;i++)
		pLayer->SetLayerInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDrawLayer::ReFillListString(UINT i,UINT nType)
{
	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CLayer* pLayer	 		= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	////////////////////////////////////
	pLayer->SetLayerInfo(i,nType);
	EmptyListAllString();	
    FillListAllString();
		
}
	
void CDrawLayer::OnClickedDrawAllactive()
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

void CDrawLayer::OnClickedToggleAll()
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

void CDrawLayer::OnClickedChange()
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

void CDrawLayer::OnClickedCurrent()
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


