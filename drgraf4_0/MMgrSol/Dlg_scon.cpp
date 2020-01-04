// ccon_dlg.cpp : implementation file
//////////////////////////////////////////////////////////////
// 					R-directional variables      			//
// 					NEEDS TOBE DONE              			//
// 			MOST Probably we wont need this Dialog        	//
//////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
///////////////////// Mesh
#include "Def_Ms.h"
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrPatch.h"
#include "DrSolid.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
#include "dlg_Scon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SCon dialog


CDlg_SCon::CDlg_SCon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SCon::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_SCon)
	m_PatchID 		= "";
	m_bClosed_S 	= FALSE;
	m_bClosed_T 	= FALSE;
	m_nSegs_S 		= 10;
	m_nSegs_T 		= 10;
	m_nMaxCNodes_S 	= m_nHowMany;
	m_nMaxCNodes_T 	= m_nHowMany;
	m_bClosed_R = FALSE;
	m_nSegs_R = 0;
	m_nMaxCNodes_R = 0;
	//}}AFX_DATA_INIT
}

void CDlg_SCon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SCon)
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDV_MaxChars(pDX, m_PatchID, 5);
	DDX_Check(pDX, IDC_P_CLOSED_S, m_bClosed_S);
	DDX_Check(pDX, IDC_P_CLOSED_T, m_bClosed_T);
	DDX_Text(pDX, IDC_P_SEGMENT_S, m_nSegs_S);
	DDV_MinMaxInt(pDX, m_nSegs_S, 1, 1000);
	DDX_Text(pDX, IDC_P_SEGMENT_T, m_nSegs_T);
	DDV_MinMaxInt(pDX, m_nSegs_T, 1, 1000);
	DDX_Text(pDX, IDC_P_CNODES_S, m_nMaxCNodes_S);
	DDV_MinMaxInt(pDX, m_nMaxCNodes_S, 4, 1000);
	DDX_Text(pDX, IDC_P_CNODES_T, m_nMaxCNodes_T);
	DDX_Check(pDX, IDC_P_CLOSED_R, m_bClosed_R);
	DDX_Text(pDX, IDC_P_SEGMENT_R, m_nSegs_R);
	DDX_Text(pDX, IDC_P_CNODES_R, m_nMaxCNodes_R);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SCon, CDialog)
	//{{AFX_MSG_MAP(CDlg_SCon)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_SCon message handlers

BOOL CDlg_SCon::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//structural
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString();   // only with CNodes
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_SCon::OnDel()
{
	//delete current selection from SelectList	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
		((CListBox*)(pWndCtrl))->DeleteString(index); 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SCon::OnAdd()
{
	// Add Current selction of POOLLIST to SELECTLIST	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
   	{
		CString CNid;
		((CListBox*)(pWndCtrl))->GetText(index,CNid);
		////////////////////////////////////// 
		pWndCtrl = GetDlgItem(IDD_SELECTLIST);
		if( (((CListBox*)(pWndCtrl))->FindString(-1,CNid) ) >=0)     //already selected
			return;
		((CListBox*)(pWndCtrl))->AddString(CNid);
	}	 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SCon::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	////////////////////////////////// Check first If Adequate Number of Control Nodes
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int nCount = ((CListBox*)pWndCtrl)->GetCount();
   	/////////////////////////////////////////////// Minimum Required
   	int nMinCNode_S = m_nHowMany;
   	int nMinCNode_T = m_nHowMany;
   	if(m_bClosed_S)
   		nMinCNode_S++;
   	if(m_bClosed_T)
   		nMinCNode_T++;
   	///////////////////////////////////////////////////////////////////////// Minimum	
   	if(nCount < (nMinCNode_S*nMinCNode_T) )
   	{
   		CString str;
   		char buf[100];
   		sprintf(buf,"Minimum No. of Control Nodes Required = %d\n        No. of \
   		 			Control Nodes Selected = %d",nMinCNode_S*nMinCNode_T,nCount	);
   		AfxMessageBox(str = buf);
   		return;
   	}
   	///////////////////////////////////////////////////////////////////////// Consistent
   	if(nCount != (m_nMaxCNodes_S * m_nMaxCNodes_T) )
   	{
   		CString str;
   		char buf[200];
   		sprintf(buf,"Total No. of Control Nodes Selected(%d) &\nParametric\
   					directional Control Nodes declared(%d and %d)\n DO NOT MATCH",
   					nCount,m_nMaxCNodes_S,m_nMaxCNodes_T);
   		AfxMessageBox(str = buf);
   		return;
   	}
   	else
   	{
		/////////////////////////////////////////////////////////////////  ADD
		int nActiveIndex;
	    CDrSolid* pAdd 	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
	    SetInfoForDataBase(pAdd);
		/////////////////////////
	} 
	///////////////
	CDialog::OnOK();
}

void CDlg_SCon::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_SCon::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMaxNodes>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == NODE)
			{ 
				CDrNode* pNode = (CDrNode*)pObject;
				if((pNode->GetNodeCard())->bnid_c)             // Only with Control Nodes
				{
	   				Nid   = (pNode->GetNodeCard())->id;
			    	((CListBox*)(pWndCtrl))->AddString(Nid);
			    }	 
			}			    
    	}
	} 
    
}
    
void CDlg_SCon::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
 
void CDlg_SCon::SetInfoForDataBase(CDrSolid* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pCNodeList	= pDrObject->GetCNodeList();
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems,index;  
	CString Nid;
	CDrNode* pDrNode;
    /////////////////
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems )
	{ 
		for (i=0;i<nMaxListItems;i++)
		{
			((CListBox*)(pWndCtrl))->GetText(i,Nid);
			//////////////////////////////////
			index = pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1);
//			index = pObjectList->GetObjectIndex(NODE,Nid);
			if(index>=0)
			{
				CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
				pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
				pCNodeList->InsertObject(pDrNode);
			}
		}
	}			
	////////////////////////////////////
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals 
    pDrObject->SetLevelType((int)LEVEL_DADDY);         // globals
    //////////////////////////////
	pDrObject->SetClosed_S(m_bClosed_S);		
	pDrObject->SetSegmentCount_S(m_nSegs_S);		
	pDrObject->SetClosed_T(m_bClosed_T);		
	pDrObject->SetSegmentCount_T(m_nSegs_T);		
	pDrObject->SetMaxCNodes_S(m_nMaxCNodes_S);		
	pDrObject->SetMaxCNodes_T(m_nMaxCNodes_T);		
	pDrObject->SetObjectID(m_PatchID);
	///////////////////////////////////// Compute No. of Patches in S & T direction
	enum PATCHTYPE kind;
	///////////////////////
	int nMeshType = pObjectMgr->GetMeshType();
	switch(nMeshType)
	{
		case MESH_BSPL:
//			pDrObject->SetSolidType(SO_BSPLINE);
//			kind = PA_BSPLINE;
			break;
						
		case MESH_BEZI:
//			pDrObject->SetSolidType(SO_BEZIER);
//			kind = PA_BEZIER;
			break;
	}			
	//////////////////////////////////
	pDrObject->SetPatchType(kind);
//	pDrObject->NumberOfCubicSolides();
//?	pDrObject->NumberOfElements(S_MESH,1/*int nElemType*/); // temp:1=LINE
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////


