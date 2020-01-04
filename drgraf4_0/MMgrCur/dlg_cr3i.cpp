// Dlg_CR3I.cpp : implementation file similar to Old: Dlg_Circ.cpp
// CIRCLE_BY_2N_TI_R
//	CString	m_NodeID	= CNode_TI;
//	CString	m_FromID	= Node_I;
//	CString	m_ToID		= Node_J;
/////////////////////
#include "stdafx.h"

#include "glb_Lims.h"
#include "glb_Objs.h"
#include "glb_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_Elem.h"
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
////////////////////
#include "MCurDll.h"
#include "UserMsg.h"

#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "Dlg_Cr3I.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	5
/////////////////////////////////////////////////////////////////////////////
// CDlg_Cr3I dialog


CDlg_Cr3I::CDlg_Cr3I(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_Cr3I)
	m_CurveID 	= "";
	m_nMesh 	= DEFAULT_UNIF;
	m_Ratio 	= 1;
	m_FromID	= _T("");
	m_ToID		= _T("");
	m_NodeID	= _T("");
	m_SegAngle	= 120;
	m_bAutoSeg	= TRUE;
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
}


void CDlg_Cr3I::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Cr3I)
	DDX_CBString(pDX, IDC_CID, m_CurveID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 5, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDV_MinMaxDouble(pDX, m_Ratio, 0.1, 9999.);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_CBString(pDX, IDC_NID, m_NodeID);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Cr3I, CDialog)
	//{{AFX_MSG_MAP(CDlg_Cr3I)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMCur_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_Cr3I message handlers

BOOL CDlg_Cr3I::OnInitDialog()
{
	CDialog::OnInitDialog();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMax = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllCurveIDs();   //  with Curves
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	nMax = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
    ////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_Cr3I::Create()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMCur_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_Cr3I::IDD);
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

void CDlg_Cr3I::OnAutoSeg()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoSeg)
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
	else	
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(TRUE);
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_Cr3I::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}


void CDlg_Cr3I::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//
	if (nMaxCurves<=0)
		return;
    //////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pCurve = (CDrCurve*)pObject;
   			CString CID		 = pCurve->GetObjectID();
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
		}	   		     
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}    

void CDlg_Cr3I::FillListAllNodeIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);//
	if (nMaxNodes<=0)
		return;
	////////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pCurve = (CDrNode*)pObject;
   			CString CID		= pCurve->GetNodeCard()->id;
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_NID);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_TO);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   		    /////////////////////////////////
		}	   		     
   	}
    
}    

void CDlg_Cr3I::OnSelchangeCid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_Cr3I::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_Cr3I::OnUpdate() 
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_CR2IN,IDC_UPDATE);
}
/*
void CDlg_Cr3I::OnCancel() 
{
	CDialog::OnCancel();
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_GOODBYE_CURIN,IDCANCEL);
}

void CDlg_Cr3I::OnOK() 
{
	CDialog::OnOK();
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_GOODBYE_CURIN,IDOK);
}
*/
/////////////////////////// end of module //////////////

