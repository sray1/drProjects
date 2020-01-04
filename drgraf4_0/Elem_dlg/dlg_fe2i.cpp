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
#include "Def_Mesh.h"
#include "Def_Elem.h"
#include "Def_Einf.h"
#include "Property.h"
#include "Mat_2D.h"
#include "Release.h"
/////////////////////
#include "CommRsrc.h"
#include "Dlg_FE2I.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
	static CString RQs[] 	= {	"AUTO","SHORT DIAG","INTERSECT DIAG","CENTROID",
								"MIDCEN SHORT"};
	static int nRQ 			= sizeof(RQs)/sizeof(RQs[0]);

	static CString RTs[] 	= {	"AUTO","CENTROID",
								"MIDCEN"};
	static int nRT 			= sizeof(RTs)/sizeof(RTs[0]);
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE2I dialog


CDlg_FE2I::CDlg_FE2I(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_FE2I)
	m_matID			= "";
	m_propID		= "";
	m_rid_I			= "";
	m_rid_J			= "";
	m_RefTemp		= 0.0;
	m_RefRule		= "AUTO";
	m_dThk			= 0.0;
	m_rid_K = _T("");
	m_rid_L = _T("");
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
}


void CDlg_FE2I::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_FE2I)
	DDX_CBString(pDX, IDD_MID, m_matID);
	DDX_CBString(pDX, IDD_PID, m_propID);
	DDX_CBString(pDX, IDD_RID_I, m_rid_I);
	DDX_CBString(pDX, IDD_RID_J, m_rid_J);
	DDX_CBString(pDX, IDD_RID_K, m_rid_K);
	DDX_CBString(pDX, IDD_RID_L, m_rid_L);
	DDX_Text(pDX, IDC_REFTEMP, m_RefTemp);
	DDX_CBString(pDX, IDC_REFRULE, m_RefRule);
	DDX_Text(pDX, IDC_THKNESS, m_dThk);
	DDV_MinMaxDouble(pDX, m_dThk, 0., 1.e+022);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_FE2I, CDialog)
	//{{AFX_MSG_MAP(CDlg_FE2I)
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
// CDlg_FE2I message handlers

BOOL CDlg_FE2I::OnInitDialog()
{
	CDialog::OnInitDialog();
	//////////////////////////////// Rel IDs
	FillListAllRelIDs(1);  // end_I
	FillListAllRelIDs(2);  // end_J
	FillListAllRelIDs(3);  // end_K
	FillListAllRelIDs(4);  // end_L
	//////////////////////////////// Mat IDs
	FillListAllMatIDs();  
	//////////////////////////////// Prop IDs
	FillListAllPropIDs(); 
	//////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_FE2I::Create ()
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
	bOk = CDialog::Create(CDlg_FE2I::IDD);
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

//////////////////////////////// RefRule
void CDlg_FE2I::FillRefRule()
{
 	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_REFRULE);;
	///
   	pCombo->EnableWindow(TRUE);	// enabled 
  	pCombo->ResetContent();// ALL REMOVED 
	//////////////////
	int i;
	//////
	if(m_bQuad)
	{
		///////////////////
		for(i=0;i<nRQ;i++)	// 								
 			pCombo->AddString(RQs[i]);
        pCombo->SetCurSel(0);	//
		//////
	}
	else
	{
		///////////////////
		for(i=0;i<nRT;i++)	// 								
 			pCombo->AddString(RTs[i]);
        pCombo->SetCurSel(0);	//
		//////
	}
    //////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_FE2I::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_FE2IN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_FE2I::OnUpdate() 
{
	////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_FE2IN,IDC_UPDATE);
}


BOOL CDlg_FE2I::OnHelpInfo(HELPINFO* pHelpInfo) 
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
void CDlg_FE2I::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 
/*
void CDlg_FE2I::SetInfoForDataBase(CDrPipe* pPipe)
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
void CDlg_FE2I::FillListAllPropIDs()
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

void CDlg_FE2I::FillListAllMatIDs()
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
	CMat_2D* 	pObject;			        
	///
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject		= (CMat_2D*)pDListMgr->GetNextObject( pos);
		CString id = pObject->GetObjectID();
	   	((CComboBox*)(pWndCtrl))->AddString(id);
	} 
    
}    

void CDlg_FE2I::FillListAllRelIDs(int IJKL)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	CElemInfo*	pElemInfo	= (CElemInfo*)pObjectMgr->GetSpecObject(ELEMINFO);
	CDListMgr*	pDListMgr 	= pElemInfo->GetInfoList(2);//	2 = ReleaseList
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	if(IJKL == 1)
		pWndCtrl = GetDlgItem(IDD_RID_I);
	else if(IJKL == 2)
		pWndCtrl = GetDlgItem(IDD_RID_J); 
	else if(IJKL == 3)
		pWndCtrl = GetDlgItem(IDD_RID_K); 
	else if(IJKL == 4)
		pWndCtrl = GetDlgItem(IDD_RID_L); 
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
/////////////////////////// end of module //////////////
