// PipeProp.cpp : implementation file
//
#include "stdafx.h"

/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_Elem.h"
#include "Def_EInf.h"
#include "Pro_PIPE.h"
#include "Mat_1D.h"			        
#include "Release.h"			        
#include "SIndex.h"			        
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "Dlg_Pipe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////
// CDlg_Pipe dialog

CDlg_Pipe::CDlg_Pipe(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Pipe::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Pipe)
	m_bValve		= FALSE;
	m_matID			= "";
	m_propID		= "";
	m_rid_I			= "";
	m_rid_J			= "";
	m_stressID_I	= "";
	m_stressID_J	= "";
	m_RefTemp		= 0.0;
	//}}AFX_DATA_INIT
}

void CDlg_Pipe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Pipe)
	DDX_Check(pDX, IDD_VALVE, m_bValve);
	DDX_CBString(pDX, IDD_PIPE_MID, m_matID);
	DDX_CBString(pDX, IDD_PIPE_PID, m_propID);
	DDX_CBString(pDX, IDD_PIPE_RID_I, m_rid_I);
	DDX_CBString(pDX, IDD_PIPE_RID_J, m_rid_J);
	DDX_CBString(pDX, IDD_PIPE_STRESS_ID_I, m_stressID_I);
	DDX_CBString(pDX, IDD_PIPE_STRESS_ID_J, m_stressID_J);
	DDX_Text(pDX, IDC_REFTEMP, m_RefTemp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Pipe, CDialog)
	//{{AFX_MSG_MAP(CDlg_Pipe)
	ON_BN_CLICKED(IDD_VALVE, OnClickedValve)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Pipe message handlers

BOOL CDlg_Pipe::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//////////////////////////////// Rel IDs
	FillListAllRelIDs(1);  // end_I
	FillListAllRelIDs(2);  // end_J
	//////////////////////////////// Mat IDs
	FillListAllMatIDs();  
	//////////////////////////////// Prop IDs
	FillListAllPropIDs(); 
	//////////////////////////////// SI IDs
	FillListAllSIIDs(1);  // end_I
	FillListAllSIIDs(2);  // end_J
	////////////////////////////////
	//////////////////
	UpdateData(FALSE);
	//////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Pipe::OnOK()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	SetInfoForDataBase(m_pDrPipe);
	////////////////
	CDialog::OnOK();

} 


void CDlg_Pipe::OnClickedValve()
{
//      case IDD_Pipe_Valve:
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_bValve = !m_bValve;
    ////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
    ///////////////////	
	// TODO: Add your control notification handler code here
	
}  
 
////////////////////////////////////////////////////////////// HELPERS
void CDlg_Pipe::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_Pipe::SetInfoForDataBase(CDrPipe* pPipe)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
 	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Pipe
	/////////////////////////////////////////////////
	pPipe->SetObjectType((int)PIPE);
	pPipe->SetElemType((int)ELEM_OBJECT);              // globals.h
    pPipe->SetLevelType((int)LEVEL_GRAPA);          // globals
	/////////////////////////////////////////////////
	pPipe->Setmid(m_matID);
	pPipe->Setpid(m_propID);
	pPipe->Setrid(m_rid_I,0);
	pPipe->Setrid(m_rid_J,1);
	pPipe->SetSIid(m_stressID_I,0);
	pPipe->SetSIid(m_stressID_J,1);
	pPipe->SetValve(m_bValve);
	pPipe->SetRefTemp(m_RefTemp);
	///////////////////////////////////////////////
	pPipe->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pPipe->SetLayer(pLayer->GetCurrentLayer());
	//////////////////////////
	
} 

void CDlg_Pipe::FillListAllPropIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(0);//	0 = PropertyList
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_PIPE_PID);
	//////////////////////////
	int nMax 	 = pDListMgr->GetCount();//
	///
	if (nMax<=0)
		return;
	////////////////////////////////////////////////////////////
	CPro_PIPE* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CPro_PIPE*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    

void CDlg_Pipe::FillListAllMatIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(1);//	1 = MaterialList
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_PIPE_MID);
	//////////////////////////
	int nMax 	 = pDListMgr->GetCount();//
	///
	if (nMax<=0)
		return;
	////////////////////////////////////////////////////////////
	CMat_1D* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CMat_1D*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    

void CDlg_Pipe::FillListAllRelIDs(int IorJ)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(2);//	2 = ReleaseList
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	if(IorJ == 1)
		pWndCtrl = GetDlgItem(IDD_PIPE_RID_I);
	else if(IorJ == 2)
		pWndCtrl = GetDlgItem(IDD_PIPE_RID_J); 
	//////////////////////////
	int nMax 	 = pDListMgr->GetCount();//
	///
	if (nMax<=0)
		return;
	////////////////////////////////////////////////////////////
	CRelease* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CRelease*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    

void CDlg_Pipe::FillListAllSIIDs(int IorJ)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(2);//	2 = ReleaseList
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	if(IorJ == 1)
		pWndCtrl = GetDlgItem(IDD_PIPE_STRESS_ID_I);
	else if(IorJ == 2)
		pWndCtrl = GetDlgItem(IDD_PIPE_STRESS_ID_J); 
	//////////////////////////
	int nMax 	 = pDListMgr->GetCount();//
	///
	if (nMax<=0)
		return;
	////////////////////////////////////////////////////////////
	CSIndex* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CSIndex*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    
///////////////////////////////// End of Module ///////////////*
