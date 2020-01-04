// Dlg_FE1I.cpp : implementation file
//

#include "stdafx.h"

#include "EDlgDll.h"
#include "UserMsg.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
/////////////////////
#include "Def_Elem.h"
#include "Def_Einf.h"
#include "Property.h"
#include "Mat_1D.h"
#include "Release.h"
#include "SIndex.h"
/////////////////////
#include "CommRsrc.h"
#include "Dlg_FE1I.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_FE1I dialog


CDlg_FE1I::CDlg_FE1I(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_FE1I)
	m_bValve		= FALSE;
	m_matID			= "";
	m_propID		= "";
	m_rid_I			= "";
	m_rid_J			= "";
	m_stressID_I	= "";
	m_stressID_J	= "";
	m_RefTemp		= 0.0;
	m_KNodeID = _T("");
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
}


void CDlg_FE1I::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_FE1I)
	DDX_Check(pDX, IDD_VALVE, m_bValve);
	DDX_CBString(pDX, IDD_MID, m_matID);
	DDX_CBString(pDX, IDD_PID, m_propID);
	DDX_CBString(pDX, IDD_RID_I, m_rid_I);
	DDX_CBString(pDX, IDD_RID_J, m_rid_J);
	DDX_CBString(pDX, IDD_PIPE_STRESS_ID_I, m_stressID_I);
	DDX_CBString(pDX, IDD_PIPE_STRESS_ID_J, m_stressID_J);
	DDX_Text(pDX, IDC_REFTEMP, m_RefTemp);
	DDX_CBString(pDX, IDD_BEAM_NID_K, m_KNodeID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_FE1I, CDialog)
	//{{AFX_MSG_MAP(CDlg_FE1I)
	ON_BN_CLICKED(IDD_VALVE, OnClickedValve)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEDlg_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_FE1I message handlers

BOOL CDlg_FE1I::OnInitDialog()
{
	CDialog::OnInitDialog();
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
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_FE1I::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEDlg_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	///////////////////////////////////////////////////////////// 
	bOk = CDialog::Create(CDlg_FE1I::IDD);
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

void CDlg_FE1I::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_FE1IN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_FE1I::OnUpdate() 
{
	////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_FE1IN,IDC_UPDATE);
}


BOOL CDlg_FE1I::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
/*
	BOOL WinHelp(
  

    HWND  hWndMain,	// handle of window requesting Help 
    LPCTSTR  lpszHelp,	// address of directory-path string 
    UINT  uCommand,	// type of Help 
    DWORD  dwData 	// additional data 
   );
*/ 

	AfxGetApp()->WinHelp(pHelpInfo->dwContextId,HELP_CONTEXTPOPUP);
	return TRUE;

//	return CDialog::OnHelpInfo(pHelpInfo);
}


void CDlg_FE1I::OnClickedValve()
{
//      case IDD_Pipe_Valve:
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_bValve = !m_bValve;
	///////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_FE1IN,IDD_VALVE);
}
////////////////////////////////////////////////////////////// HELPERS
void CDlg_FE1I::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 
/*
void CDlg_FE1I::SetInfoForDataBase(CDrPipe* pPipe)
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
*/
void CDlg_FE1I::FillListAllPropIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(0);//	0 = PropertyList
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_PID);
	//////////////////////////
	int nMax 	 = pDListMgr->GetCount();//
	///
	if (nMax<=0)
		return;
	////////////////////////////////////////////////////////////
	CProperty* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject	= (CProperty*)pDListMgr->GetNextObject(pos);
		if(pObject->GetPropType() != m_ObjType)
			continue;
		/////////////
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    

void CDlg_FE1I::FillListAllMatIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(1);//	1 = MaterialList
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_MID);
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

void CDlg_FE1I::FillListAllRelIDs(int IorJ)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(2);//	2 = ReleaseList
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	if(IorJ == 1)
		pWndCtrl = GetDlgItem(IDD_RID_I);
	else if(IorJ == 2)
		pWndCtrl = GetDlgItem(IDD_RID_J); 
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

void CDlg_FE1I::FillListAllSIIDs(int IorJ)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
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
/////////////////////////// end of module //////////////
