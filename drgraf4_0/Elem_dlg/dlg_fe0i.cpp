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
#include "Mat_0D.h"
/////////////////////
#include "CommRsrc.h"
#include "Dlg_FE0I.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_FE0I dialog


CDlg_FE0I::CDlg_FE0I(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_FE0I)
	m_matID			= "";
	m_propID		= "";
	m_RefTemp		= 0.0;
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
}


void CDlg_FE0I::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_FE0I)
	DDX_CBString(pDX, IDD_MID, m_matID);
	DDX_CBString(pDX, IDD_PID, m_propID);
	DDX_Text(pDX, IDC_REFTEMP, m_RefTemp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_FE0I, CDialog)
	//{{AFX_MSG_MAP(CDlg_FE0I)
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
// CDlg_FE0I message handlers

BOOL CDlg_FE0I::OnInitDialog()
{
	CDialog::OnInitDialog();
	//////////////////////////////// Mat IDs
	FillListAllMatIDs();  
	//////////////////////////////// Prop IDs
	FillListAllPropIDs(); 
	////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_FE0I::Create ()
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
	bOk = CDialog::Create(CDlg_FE0I::IDD);
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

void CDlg_FE0I::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_FE0IN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_FE0I::OnUpdate() 
{
	////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_FE0IN,IDC_UPDATE);
}


BOOL CDlg_FE0I::OnHelpInfo(HELPINFO* pHelpInfo) 
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

////////////////////////////////////////////////////////////// HELPERS
void CDlg_FE0I::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 
/*
void CDlg_FE0I::SetInfoForDataBase(CDrPipe* pPipe)
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
void CDlg_FE0I::FillListAllPropIDs()
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

void CDlg_FE0I::FillListAllMatIDs()
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
	CMat_0D* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CMat_0D*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    
/////////////////////////// end of module //////////////
