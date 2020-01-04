// NodeProp.cpp : implementation file
//
#include "stdafx.h"

#include <math.h>
#include "3DMath.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_View.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// cards
#include "Def_Card.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
#include "DrFont.h"
////////////////////
#include "CommRsrc.h"
#include "Dlg_Node.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////
// CDlg_Node dialog

CDlg_Node::CDlg_Node(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Node::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Node)
	m_nid_r 	= "";
	m_FromID	= "";
	m_ToID		= "";
	m_bnid_c 	= FALSE;
	m_xWorld	= 0.0;
	m_yWorld	= 0.0;
	m_zWorld	= 0.0;
	m_strLn		= _T("0.0");
	m_strDx		= _T("0.0");
	m_strDy		= _T("0.0");
	m_strDz		= _T("0.0");
	//}}AFX_DATA_INIT
	m_nCreated	= 0;
	m_bCoord	= TRUE;
	m_dLength	= 0.0;
	m_DxWorld	= 0.0;
	m_DyWorld	= 0.0;
	m_DzWorld	= 0.0;
}

void CDlg_Node::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Node)
	DDX_Text(pDX, IDD_NODE_ID, m_id);
	DDX_Text(pDX, IDD_NODE_NID_R, m_nid_r);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_Text(pDX, IDD_LENGTH, m_strLn);
	DDX_Text(pDX, IDD_NODE_X2, m_xWorld);
	DDX_Text(pDX, IDD_NODE_Y2, m_yWorld);
	DDX_Text(pDX, IDD_NODE_Z2, m_zWorld);
	DDX_Text(pDX, IDD_NODE_DX, m_strDx);
	DDX_Text(pDX, IDD_NODE_DY, m_strDy);
	DDX_Text(pDX, IDD_NODE_DZ, m_strDz);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Node, CDialog)
	//{{AFX_MSG_MAP(CDlg_Node)
	ON_BN_CLICKED(IDD_ADD, OnClickedAdd)
	ON_BN_CLICKED(IDD_DEL, OnClickedDel)
	ON_BN_CLICKED(IDD_EDIT, OnClickedEdit)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_EN_KILLFOCUS(IDD_NODE_NID_R, OnKillfocusNodeNidR)
	ON_EN_KILLFOCUS(IDD_NODE_ID, OnKillfocusNodeId)
	ON_BN_CLICKED(IDC_COORD, OnCoord)
	ON_BN_CLICKED(IDC_DIRECTION, OnDirection)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM, OnSelchangeCnodeFrom)
	ON_CBN_SELCHANGE(IDC_CNODE_TO, OnSelchangeCnodeTo)
	ON_CBN_SELCHANGE(IDD_NODE_NID_R, OnSelchangeNodeNidR)
	ON_WM_HELPINFO()
	ON_BN_DOUBLECLICKED(IDD_ADD, OnClickedAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnClickedDel)
	ON_BN_DOUBLECLICKED(IDD_EDIT, OnClickedEdit)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_COORD, OnCoord)
	ON_BN_DOUBLECLICKED(IDC_DIRECTION, OnDirection)
	ON_EN_CHANGE(IDD_NODE_DX, OnChangeNodeDx)
	ON_EN_CHANGE(IDD_NODE_DY, OnChangeNodeDy)
	ON_EN_CHANGE(IDD_NODE_DZ, OnChangeNodeDz)
	ON_EN_CHANGE(IDD_LENGTH, OnChangeLength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Node message handlers

BOOL CDlg_Node::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//structural
//	Setwindowtext
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	////////////////////////////////////// set title: Node or CNode
//	pWndCtrl = GetDlgItem(IDD_ELP_NODE);
	if(m_bnid_c)
		SetWindowText("CNode Properties");
	else
		SetWindowText("Node Properties");
	///////////////////////////////////////////////	
	pWndCtrl = GetDlgItem(IDD_NODE_X);
//	((CEdit*)pWndCtrl)->LimitText(NUM_LEN); 
	pWndCtrl = GetDlgItem(IDD_NODE_Y);
//	((CEdit*)pWndCtrl)->LimitText(NUM_LEN); 
	pWndCtrl = GetDlgItem(IDD_NODE_Z);
//	((CEdit*)pWndCtrl)->LimitText(NUM_LEN);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
	{
		FillListAllString();
		FillListforAllNodeCombos();	// FromID, ToID and NID_R
	}
	//////////////// Coordinate Mode
	m_bCoord = TRUE;
	((CButton*)GetDlgItem(IDC_COORD))->SetCheck(TRUE);// for Coordinate
	((CButton*)GetDlgItem(IDC_DIRECTION))->SetCheck(FALSE);// for Coordinate
	////////////////
	GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);// for Direction only	
	GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);// for Direction only
	GetDlgItem(IDD_LENGTH)->EnableWindow(FALSE);// for Direction only
	//////////////////////////////////////////////////////////////////// Control Node:No Support/Load
	if(m_bnid_c)
	{
		GetDlgItem(IDD_NODE_SUP_ID)->EnableWindow(FALSE);// for Node only	
		GetDlgItem(IDD_NODE_LOAD_ID)->EnableWindow(FALSE);// for Node only	
	}
	///////////////////////////////////////// Show Current MouseLocation, 
										   // if DrawView Mouse-induced		
	/////////////////////////////////////////////////////////////////////
	// m_nHowMany == -9999 -> Dialog-Induced	(AfterThought!)			/
	/////////////////////////////////////////////////////////////////////
	BOOL bDlgInd = FALSE;
	if(m_nHowMany == -9999 || m_nActiveViewNumber == VIEWDAT)
	{
		bDlgInd		= TRUE;
		m_nHowMany	= abs(m_nHowMany);
	}
	///////////////////////////////////////////////////////////////////////////////////////
    if(!bDlgInd)  
    {	
	    /////////////////////////////////////////// 
		CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//		CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
		CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
    
		LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	   	double dWorldBase = (double)lWorldBase; 
	    m_xWorld 		= ((double)(m_MouseWIC.x))/dWorldBase;
	    m_yWorld 		= ((double)(m_MouseWIC.y))/dWorldBase;
	    m_zWorld 		= ((double)(m_MouseWIC.z))/dWorldBase;
	    ///////////////////////////////////////////
		double dMapFactor   = pMapFactor->GetMapFactor();
		///////////////////////////////////////////
		m_xWorld 		*= dMapFactor;
		m_yWorld 		*= dMapFactor;
	    m_zWorld 		*= dMapFactor;
	    //////////////////////// World Coord
		pObjectMgr->DStoSC(&m_xWorld);
		pObjectMgr->DStoSC(&m_yWorld);
		pObjectMgr->DStoSC(&m_zWorld);
		/////////////////
		pWndCtrl = GetDlgItem(IDD_NODE_ID);
		pWndCtrl->SetFocus();
	}
	else                                                     	
	{
		int nActiveObjIndex;
		///////////////////////////////////////// Show Indexed Node, if DataView OR Dialog-induced
		if(m_bnid_c)
			nActiveObjIndex = pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);//notactive = -1
		else
			nActiveObjIndex = pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);//notactive = -1
		////////////////
		if(nActiveObjIndex>=0)
		{
			/////////////////////////////	
			FillOthers(nActiveObjIndex);
			////////////////////
			pWndCtrl = GetDlgItem(IDD_LIST);
			int index = ((CListBox*)pWndCtrl)->FindStringExact(-1,m_id);
			((CListBox*)pWndCtrl)->SetCurSel(index);
		}	
    
	}
	////////////////////////////////////////////////// Disable:Display Coords
	GetDlgItem(IDD_NODE_X2)->EnableWindow(FALSE);
	GetDlgItem(IDD_NODE_Y2)->EnableWindow(FALSE);
	GetDlgItem(IDD_NODE_Z2)->EnableWindow(FALSE);
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Node::OnClickedAdd()
{
//       case IDD_ADD:
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	if(!m_id.GetLength() )   // blank nIDs
	{
		AfxMessageBox("No NodeID!!\nSelect an ID");
   		return;
   	} 
	/////////////////////////////////////////// already exists
	int i;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(m_bnid_c)
   		i= pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);
	else
   		i= pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
	///
   	if(i>=0)
   	{
		AfxMessageBox("NodeID Already Exists !!\nUse Some other ID or OK Button");
   		return;
	}
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrNode* pAddNode;
	if(m_bnid_c)
		pAddNode 	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,CNODE));
	else
		pAddNode 	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,NODE));
	///
	pAddNode->SetCategory(CA_ELEMENT);
	SetInfoForDataBase(pAddNode,FALSE);
    //////////////////////////////////////////////////////////////////////////////// Invalidate
	if(m_bnid_c)
	{
		pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
	}
	else
	{
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	}
	//////////////////////////////////////////////////////////
	m_nCreated++;
 	///////////////////////////////// get new node ptr
	if(m_bnid_c)
   		i= pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);
	else
   		i= pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
	///
   	if(i<0)
   	{
   		AfxMessageBox("DLG_NODE:Add.198 - Internal Problem");
   		return;
   	}	
 	CDListMgr* pDListMgr;
	if(m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///
	CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(i);
    ///////////////////////////////// Add  Label to list
	int nActiveIndexOld = nActiveIndex;													    
    CDrLabel* pAddLabel 	= (CDrLabel*)(pObjectMgr->AddToDataBase(nActiveIndex,LABEL));
    SetInfoForNodeLabel(pNode,pAddLabel);
	////////////////////////////////////////////////////////////////////////////////
	pNode->SetLabelNo(pObjectMgr->GetLastObjectNo(LABEL));		// save in Node
	nActiveIndex = pObjectMgr->GetObjectCount(LABEL) - 1;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(LABEL);					// set Active Type									
    ////////////////////////////////////////////////////////// Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,LABEL);
	nActiveIndex = nActiveIndexOld;													    
	////////////////////////////////////////////////////////// Get out of DialogBox
	if(m_nHowMany)
	{
		if(m_nCreated >= m_nHowMany)
		{
	  		int index = pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
			CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		 	///////////////////////////////////////////////////// Set Mouse At New Position
			m_MouseWIC.x    = (pNode->GetNodeCard())->x;				       
			m_MouseWIC.y    = (pNode->GetNodeCard())->y;				       
			m_MouseWIC.z    = (pNode->GetNodeCard())->z; 
		   	m_CurrentNodeID = (pNode->GetNodeCard())->id;
		    //////////////////////////
		    pObjectMgr->SetActiveObjectIndex(index);
			/////////////////////////////////////////
			CDialog::OnOK();
			return;
		}
	}		
	//////////////////////////////////////////////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	((CListBox*)(pWndCtrl))->AddString(m_id);
	int index;
	index = ((CListBox*)pWndCtrl)->FindStringExact(-1,m_id);
	((CListBox*)pWndCtrl)->SetCurSel(index); 
	////////////////////////////// Update all Node Combos
	FillListforAllNodeCombos();
	////////////////////////////// Update Name
	char	buf[50];
	int		nLastNum;
	///
	if(m_bnid_c)
	{
		pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	    nLastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_id	= "CN_";
		m_id	+= buf;
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    nLastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_id	= "";
		m_id	+= buf;
	}
	/////////////////////////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
	///////////////////
	return;
}

void CDlg_Node::OnClickedDel()
{
//       case IDD_DEL:
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	UpdateData(TRUE);
	//////////////////
	int nMaxNodes;
	if(m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///
	nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
	///
	if(nMaxNodes <= 0 )   // no Node
	{
		AfxMessageBox("No Node to Delete!!\nUse Cancel Button");
   		return;
   	}
   	//////////////////////////////////////////////////// 
	if(!m_id.GetLength() )   // blank nIDs
	{
		AfxMessageBox("No NodeID!!\nSelect an ID");
   		return;
   	}
   	//////////////////////////////////////////////////// 
//   	CDrNode Node;
	int i;
	if(m_bnid_c)
   		i = pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);
	else
   		i = pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
   	if(i<0)
   	{
   		AfxMessageBox("No Need to Delete !!");
   		return;
   	}		
	//////////////////////////////////////////////////////////
	CString strDel = "DELETING: " + m_id + "\nAre You Sure !!"; 
		if(AfxMessageBox(strDel,MB_YESNO) == IDNO)
		return;
	//////////////////////////////////////////////////////////////// DELETE
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	int index;
 	index = ((CListBox*)pWndCtrl)->FindStringExact(-1,m_id);
	((CListBox*)(pWndCtrl))->DeleteString(index);
	//////////////////////////////////////////////////////////////// DELETE:DataBase
	if(m_bnid_c)
		pObjectMgr->DeleteFromDataBase(i, CNODE);
	else
		pObjectMgr->DeleteFromDataBase(i, NODE);
	/////////////////////////////// Tell all Views of the delete
	pDoc->UpdateAllViews(NULL);
    /////////////////////////////	
	if(m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///
	nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
	///
	if(nMaxNodes>0)
	{
    	////////////////////
    	((CListBox*)pWndCtrl)->SetCurSel(0);
    	OnSelchangeList();
    	
    }
    else
    {

		m_id		= "";	
		m_nid_r		= "";   
		m_DxWorld	= 0.;	
		m_DyWorld	= 0.;	
		m_DzWorld	= 0.;	
		m_xWorld	= 0.;	
		m_yWorld	= 0.;	
		m_zWorld	= 0.;	
		m_bnid_c 	= FALSE;
    	//////////////////////////////////////////////// change ActiveObjIndex
 		pObjectMgr->SetActiveObjectIndex(-1);
   	    ////////////////////////////////////////////////
	}
	////////////////////////////// Update all Node Combos
	FillListforAllNodeCombos();
	////////////////////
	UpdateData(FALSE);          //To Screen
	//////////////////// 
	return;
}

void CDlg_Node::OnClickedEdit()
{
//      case IDD_EDIT:   
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////// 
	UpdateData(TRUE);
	//////////////////
	int i,nMaxNodes;                   
	
	if(m_bnid_c)
		nMaxNodes = pDListMgr->GetSpecificObjectCount(CNODE);
	else
		nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
	///
	if(nMaxNodes <= 0 )   // no Node
	{
		AfxMessageBox("No Node to Edit!!\nUse Add or OK Button");
   		return;
   	}
   	 
	if(!m_id.GetLength() )   // blank nIDs
	{
		AfxMessageBox("No NodeID!!\nSelect an ID");
   		return;
   	} 
    //////////////////////////////////////////////////////
//	CDrNode Node;
	///////////////////////////////////////
 	if(m_bnid_c)
		i= pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);
	else
		i= pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
	///
	if(i <0)
    {
		AfxMessageBox("Node was Not Saved!!\nUse Add or OK Button");
   		return;
   	}
	///////////////////////////////////////////////////////////////// EDIT
 	if(m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///
	CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(i);    
   	SetInfoForDataBase(pNode,FALSE);
	pDListMgr->EditObject(i,pNode);
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	return;

}

void CDlg_Node::OnCoord() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	m_bCoord = TRUE;
	////////////////
	GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);// for Direction only	
	GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);// for Direction only
	GetDlgItem(IDD_LENGTH)->EnableWindow(FALSE);// for Direction only
	/////////////////////////////////////////////
	GetDlgItem(IDD_NODE_DX)->EnableWindow(TRUE);// Coordinates Input
	GetDlgItem(IDD_NODE_DY)->EnableWindow(TRUE);// Coordinates Input
	GetDlgItem(IDD_NODE_DZ)->EnableWindow(TRUE);// Coordinates Input
	/////////////////////////// ReSet
	m_id		= "";	
	m_nid_r		= "";   
	m_DxWorld	= 0.;	
	m_DyWorld	= 0.;	
	m_DzWorld	= 0.;	
	m_xWorld	= 0.;	
	m_yWorld	= 0.;	
	m_zWorld	= 0.;	
	m_bnid_c 	= FALSE;
   	//////////////////////////////////////////////// change ActiveObjIndex
//	pObjectMgr->SetActiveObjectIndex(-1);
    ////////////////////////////////////////////////
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	
}

void CDlg_Node::OnDirection() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	m_bCoord = FALSE;
	/////////////////
	GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);// for Direction only	
	GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);// for Direction only
	GetDlgItem(IDD_LENGTH)->EnableWindow(TRUE);// for Direction only
	/////////////////////////////////////////////
	GetDlgItem(IDD_NODE_DX)->EnableWindow(FALSE);// Coordinates Computed
	GetDlgItem(IDD_NODE_DY)->EnableWindow(FALSE);// Coordinates Computed
	GetDlgItem(IDD_NODE_DZ)->EnableWindow(FALSE);// Coordinates Computed
	/////////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->SetCurSel(0);
 	((CComboBox*)GetDlgItem(IDC_CNODE_TO))->SetCurSel(0);
	/////////////////////////// Reset
	m_id		= "";	
	m_nid_r		= "";   
	m_xWorld	= 0.;	
	m_yWorld	= 0.;	
	m_zWorld	= 0.;	
	m_bnid_c 	= FALSE;
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	


}

void CDlg_Node::OnKillfocusNodeId() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnKillfocusNodeNidR() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////
	if(m_bCoord)
		ResolveReference_Coords();
	else
		ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnChangeNodeDx() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    //////////////////// check if -ve
	m_strDx.TrimLeft();
	/////////
	int nLen = m_strDx.GetLength(); 
	if((nLen == 1) && (m_strDx.Left(1) == "-"))
		return;
	////////////////////////////
	LPTSTR p = m_strDx.GetBuffer(1024);
//		sscanf( p, "%f", &m_DxWorld );			// cannot Use in DLL
	m_DxWorld = atof( p );
	//////////////////
	ResolveReference_Coords();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnChangeNodeDy() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    //////////////////// check if -ve
	m_strDy.TrimLeft();
	/////////
	int nLen = m_strDy.GetLength(); 
	if((nLen == 1) && (m_strDy.Left(1) == "-"))
		return;
	////////////////////////////
	LPTSTR p = m_strDy.GetBuffer(1024);
//		sscanf( p, "%f", &m_DxWorld );			// cannot Use in DLL
	m_DyWorld = atof( p );
	//////////////////
	ResolveReference_Coords();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnChangeNodeDz() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    //////////////////// check if -ve
	m_strDz.TrimLeft();
	/////////
	int nLen = m_strDz.GetLength(); 
	if((nLen == 1) && (m_strDz.Left(1) == "-"))
		return;
	////////////////////////////
	LPTSTR p = m_strDz.GetBuffer(1024);
//		sscanf( p, "%f", &m_DxWorld );			// cannot Use in DLL
	m_DzWorld = atof( p );
	//////////////////
	ResolveReference_Coords();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnSelchangeCnodeFrom() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnSelchangeCnodeTo() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////
	ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}


void CDlg_Node::OnChangeLength() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    //////////////////// check if -ve
	m_strLn.TrimLeft();
	/////////
	int nLen = m_strLn.GetLength(); 
	if((nLen == 1) && (m_strLn.Left(1) == "-"))
		return;
	////////////////////////////
	LPTSTR p = m_strLn.GetBuffer(1024);
//		sscanf( p, "%f", &m_DxWorld );			// cannot Use in DLL
	m_dLength = atof( p );
	//////////////////
	if(m_dLength == 0.0)
	{
		AfxMessageBox("For Distinct Node Entry\n Length Must be NonZero",MB_ICONEXCLAMATION);
		GetDlgItem(IDD_LENGTH)->SetFocus();
	}
	else
		ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CDlg_Node::OnSelchangeNodeNidR() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////
	if(m_bCoord)
		ResolveReference_Coords();
	else
		ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

int CDlg_Node::ResolveReference_Direction()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	///////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
	WORLD Axis;
	int nResult = UnitAxisFromEndNodes(&Axis);
	if(nResult<0)
		return -1;
    /////////////////
	int 		index;
	CDrNode* 	pDrNode;
	////////////////////////////////////////////////////// RefNode
	if(m_nid_r == "")
	{
		m_xWorld = 0.0;
		m_yWorld = 0.0;
		m_zWorld = 0.0;
	}
	else
	{
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_nid_r,1);
		if(index>=0)
			pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
		else
		{
			pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
			index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_nid_r,1);
			if(index>=0)
				pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
			else
			{
				AfxMessageBox("Error:\nCDlg_Node::OnSelchangeCnodeTo\nm_nid_r");
				return -1;
			}
		}
		////////////////////////////
		double xWorld,yWorld,zWorld;
	 	///////////////////////////////////////////// get Raw Pt.
    	xWorld 		= ((double)((pDrNode->GetNodeCard())->x))/dWorldBase;
    	yWorld 		= ((double)((pDrNode->GetNodeCard())->y))/dWorldBase;
    	zWorld 		= ((double)((pDrNode->GetNodeCard())->z))/dWorldBase;
    	////////////////////////////// Map Factor
    	xWorld 		*= dMapFactor;
    	yWorld 		*= dMapFactor;
    	zWorld 		*= dMapFactor;
   		//////////////////////// World Coord
		pObjectMgr->DStoSC(&xWorld);
		pObjectMgr->DStoSC(&yWorld);
		pObjectMgr->DStoSC(&zWorld);
		//////////////////////////////////////// Coordinates
		m_xWorld = xWorld + m_dLength * Axis.x;
		m_yWorld = yWorld + m_dLength * Axis.y;
		m_zWorld = zWorld + m_dLength * Axis.z;
		////////
	}
	/////////
	return 0;
}

int CDlg_Node::ResolveReference_Coords()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
 	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	///////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
	int 		index;
	CDrNode* 	pDrNode;
	////////////////////////////////////////////////////// RefNode
	if(m_nid_r == "")
	{
		//////////////////////////////////////// Coordinates
		m_xWorld = m_DxWorld;
		m_yWorld = m_DyWorld;
		m_zWorld = m_DzWorld;
		////////
	}
	else
	{
		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_nid_r,1);
		if(index>=0)
			pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
		else
		{
			AfxMessageBox("Error:\nCDlg_Node::OnSelchangeCnodeTo\nm_nid_r");
			return -1;
		}
		////////////////////////////
		double xWorld,yWorld,zWorld;
	 	///////////////////////////////////////////// get Raw Pt.
    	xWorld 		= ((double)((pDrNode->GetNodeCard())->x))/dWorldBase;
    	yWorld 		= ((double)((pDrNode->GetNodeCard())->y))/dWorldBase;
    	zWorld 		= ((double)((pDrNode->GetNodeCard())->z))/dWorldBase;
    	////////////////////////////// Map Factor
    	xWorld 		*= dMapFactor;
    	yWorld 		*= dMapFactor;
    	zWorld 		*= dMapFactor;
   		//////////////////////// World Coord
		pObjectMgr->DStoSC(&xWorld);
		pObjectMgr->DStoSC(&yWorld);
		pObjectMgr->DStoSC(&zWorld);
		//////////////////////////////////////// Coordinates
		m_xWorld = m_DxWorld + xWorld;
		m_yWorld = m_DyWorld + yWorld;
		m_zWorld = m_DzWorld + zWorld;
		////////
	}		
	/////////
	return 0;
}

int CDlg_Node::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	//////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
    /////////////////
	int 		index;
	CDrNode* 	pDrNode;
	if(m_FromID == "" || m_ToID == "")
	{
		pNormal->x = 0.0;
		pNormal->y = 0.0;
		pNormal->z = 0.0;
		//////////
		return 0;
	}
	////////////////////////////////////////////////////// Same Node
	if(m_FromID == m_ToID)
	{
		pNormal->x = 0.0;
		pNormal->y = 0.0;
		pNormal->z = 0.0;
		//////////
		return 0;
	}
	////////////////////////////////////////////////////// FromNode
	pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_FromID,1);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
	{
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1);
		if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
		else
		{
			AfxMessageBox("Error:\nCDlg_Node::UnitAxisFromEndNodes\nFromID");
			return -1;
		}
	}
   	///////////////////////////////////////// get Raw Pt.
   	WORLD FromPt = *(pDrNode->GetLocalPos());
	////////////////////////////////////////////////////// ToNode
	pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_ToID,1);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
	{
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1);
		if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
		else
		{
			AfxMessageBox("Error:\nCDlg_Node::UnitAxisFromEndNodes\nToID");
			return -1;
		}
	}
   	//////////////////////////////////////// get Raw Pt.
  	WORLD ToPt = *(pDrNode->GetLocalPos());
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&ToPt, &FromPt, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return 0;
}

void CDlg_Node::OnOK()
{ 

//      case IDD_OK:     
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	if(!m_id.GetLength() )   // blank nIDs
   		return;
	///////////// 
//	CDrNode	Node;
	int			index;
	CDrNode*	pNode;
	CString		id_Current = m_id;
	//////////////////////////////
	if(!m_bnid_c)
	{
		index = pObjectMgr->GetObjectIndexfromKey(NODE,m_id,1);
   		if(index<0)
     	/////////////////////////////////////////////// not in list, so add
 		{
			OnClickedAdd();	// updated m_id
  			index = pObjectMgr->GetObjectIndexfromKey(NODE,id_Current,1);
  		}	
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////
		pObjectMgr->SetActiveObjectIndex(index);
		pObjectMgr->SetActiveObjectType(NODE);
	}
	else
	{
		index = pObjectMgr->GetObjectIndexfromKey(CNODE,m_id,1);
   		if(index<0)
    	/////////////////////////////////////////////// not in list, so add
  		{
			OnClickedAdd();	// updated m_id
  			index = pObjectMgr->GetObjectIndexfromKey(CNODE,id_Current,1);
  		}	
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////
		pObjectMgr->SetActiveObjectIndex(index);
		pObjectMgr->SetActiveObjectType(CNODE);
	}
 	///////////////////////////////////////////////////// Set Mouse At New Position
	m_MouseWIC.x    = (pNode->GetNodeCard())->x;				       
	m_MouseWIC.y    = (pNode->GetNodeCard())->y;				       
	m_MouseWIC.z    = (pNode->GetNodeCard())->z; 
   	m_CurrentNodeID = (pNode->GetNodeCard())->id;
	/////////////////////////////////////////
	CDialog::OnOK();

} 

void CDlg_Node::OnSelchangeList()
{
//      case IDD_LIST:
	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////
	if(!m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	///
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes <= 0) return;
	//////////////////////////
   	////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////	

	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
	    
	CString Nid;  
    ((CListBox*)pWndCtrl)->GetText(index,Nid); 
    
	int i;
//	CDrNode Node;
	///////////////////////////////////////////////
	if(!m_bnid_c)
   		i= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1);
	else
   		i= pObjectMgr->GetObjectIndexfromKey(CNODE,Nid,1);
	///
   	if(i<0)
   	{
    	MessageBeep(0xFFFFFFFF); 
    	return;
	}
	else
	{    	
   		//////////////
   		FillOthers(i);     
   		//////////////
	}    	    
   	////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
   	///////////////////	
	
}
////////////////////////////////////////////////////////////// HELPERS
void CDlg_Node::FillOthers(int i)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	if(!m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	///
	int nMaxNodes     = pDListMgr->GetSpecificObjectCount(NODE);
	CDrNode* pNode 	  = (CDrNode*)(pDListMgr->GetObject(i));       // NODE 
	///////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
    if(nMaxNodes)
    {
	
    	m_xWorld 		= ((double)((pNode->GetNodeCard())->x))/dWorldBase;
    	m_yWorld 		= ((double)((pNode->GetNodeCard())->y))/dWorldBase;
    	m_zWorld 		= ((double)((pNode->GetNodeCard())->z))/dWorldBase;
    	////////////////////////////// Map Factor
    	m_xWorld 		*= dMapFactor;
    	m_yWorld 		*= dMapFactor;
    	m_zWorld 		*= dMapFactor;
   		//////////////////////// World Coord
		pObjectMgr->DStoSC(&m_xWorld);
		pObjectMgr->DStoSC(&m_yWorld);
		pObjectMgr->DStoSC(&m_zWorld);
		//////////////////////////////////////// 
		m_id     		= (pNode->GetNodeCard())->id;
		m_nid_r  		= (pNode->GetNodeCard())->nid_r;
   		m_bnid_c  		= (pNode->GetNodeCard())->bnid_c;
		////////////////////////////////////////////////////// Input Mode
		m_bCoord		= pNode->GetInputMode();
		////////////////////////////////////////
		WORLD temp		= *(pNode->GetDelta());
    	m_DxWorld 		= temp.x;
    	m_DyWorld 		= temp.y;
    	m_DzWorld 		= temp.z;
		//////////
		m_dLength		= pNode->GetLength();
		//////////////////////////////////////////////////////
		CWnd*	pComCtrl;
		int		index;
/*
		/////////////////////////////////////////////
		pComCtrl = GetDlgItem(IDD_NID);
		m_id  = (pNode->GetNodeCard())->id;
   		index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_id);
   		if(index>= 0)
    		((CComboBox*)pComCtrl)->SetCurSel(index);
*/
		/////////////////////////////////////////////
		pComCtrl	= GetDlgItem(IDD_NODE_NID_R);
		m_nid_r		= (pNode->GetNodeCard())->nid_r;
		index		= ((CComboBox*)pComCtrl)->FindStringExact(-1,m_nid_r);
   		if(index>= 0)
    		((CComboBox*)pComCtrl)->SetCurSel(index);
		/////////////////////////////////////////////
		pComCtrl	= GetDlgItem(IDC_CNODE_FROM);
		m_FromID	= pNode->GetFromID();
		index		= ((CComboBox*)pComCtrl)->FindStringExact(-1,m_FromID);
   		if(index>= 0)
    		((CComboBox*)pComCtrl)->SetCurSel(index);
		/////////////////////////////////////////////
		pComCtrl	= GetDlgItem(IDC_CNODE_TO);
		m_ToID		= pNode->GetToID();
		index		= ((CComboBox*)pComCtrl)->FindStringExact(-1,m_ToID);
   		if(index>= 0)
    		((CComboBox*)pComCtrl)->SetCurSel(index);
		/////////////////////////////////////////////
	}   		
}

void CDlg_Node::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Nid;
	
	if(!m_bnid_c)
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	///
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
	   			Nid   = (pNode->GetNodeCard())->id;
//	   			if((pNode->GetNodeCard())->bnid_c == m_bnid_c)		// node for node/cnode for cnode
			    ((CListBox*)(pWndCtrl))->AddString(Nid); // Show ALL 
			}			    
    	}
	} 
    
}    

void CDlg_Node::FillListforAllNodeCombos()
{

   	((CComboBox*)(GetDlgItem(IDC_CNODE_FROM)))->ResetContent();	// Remove ALL  
   	((CComboBox*)(GetDlgItem(IDC_CNODE_TO)))->ResetContent();	// Remove ALL  
   	((CComboBox*)(GetDlgItem(IDD_NODE_NID_R)))->ResetContent();	// Remove ALL   
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
	CString Nid;
	//////////////////////////////////
	CDrObject* pObject;			       
	POSITION pos;
	///	
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
   			Nid   = (pNode->GetNodeCard())->id;
	    	((CComboBox*)(GetDlgItem(IDC_CNODE_FROM)))->AddString(Nid);		// Show ALL  
	    	((CComboBox*)(GetDlgItem(IDC_CNODE_TO)))->AddString(Nid);		// Show ALL  
	    	((CComboBox*)(GetDlgItem(IDD_NODE_NID_R)))->AddString(Nid);		// Show ALL   
		}			    
   	}
	///	
	pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
   			Nid   = (pNode->GetNodeCard())->id;
	    	((CComboBox*)(GetDlgItem(IDC_CNODE_FROM)))->AddString(Nid);		// Show ALL  
	    	((CComboBox*)(GetDlgItem(IDC_CNODE_TO)))->AddString(Nid);		// Show ALL  
	    	((CComboBox*)(GetDlgItem(IDD_NODE_NID_R)))->AddString(Nid);		// Show ALL   
		}			    
   	}
   
}    

void CDlg_Node::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_Node::SetInfoForDataBase(CDrNode* pNode,BOOL bGen)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Node
	LONG  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////
	pNode->SetObjectType((int)NODE);
	pNode->SetElemType((int)ELEM_OBJECT);              // globals.h
    pNode->SetLevelType((int)LEVEL_GRAPA);         // globals
	pNode->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	(pNode->GetNodeCard())->id 		= m_id;	
	(pNode->GetNodeCard())->nid_r 	= m_nid_r;
	//////////////////////
   	WORLD LocalPos;
	if(!bGen) // Not Internally generated
	{
		/////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_xWorld);
		pObjectMgr->SCtoDS(&m_yWorld);
		pObjectMgr->SCtoDS(&m_zWorld);
    	//////////////////////////////
    	LocalPos.x = m_xWorld*dWorldBase/dMapFactor; 
    	LocalPos.y = m_yWorld*dWorldBase/dMapFactor; 
    	LocalPos.z = m_zWorld*dWorldBase/dMapFactor;
	}
	else	// Internally Generated
	{    
    	//////////////////////////////
    	LocalPos.x = m_xWorld; 
    	LocalPos.y = m_yWorld; 
    	LocalPos.z = m_zWorld;
    }	
    //////////////////////////////////////// Save as Local Pos
    pNode->SetLocalPos(LocalPos);
    /////////////////////////////
	(pNode->GetNodeCard())->x = (long)LocalPos.x;	
	(pNode->GetNodeCard())->y = (long)LocalPos.y;	
	(pNode->GetNodeCard())->z = (long)LocalPos.z;
	/////////////////////////////////////////////
	pNode->SetInputMode(m_bCoord);
	//////////////////////////////
	WORLD Delta;
	Delta.x = m_DxWorld;
	Delta.y = m_DyWorld;
	Delta.z = m_DzWorld;
	///////////////////////
    pNode->SetDelta(Delta);
	///////////////////////
    pNode->SetLength(m_dLength);
    pNode->SetFromID(m_FromID);
    pNode->SetToID(m_ToID);
	//////////////////////////////////////////	
	(pNode->GetNodeCard())->bnid_c 	= m_bnid_c; 
	////////////////////////////////////////// 
	pNode->SetFormat(pObjectMgr->GetFormat());
	pNode->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pNode->SetLayer(pLayer->GetCurrentLayer());
	pNode->SetPrecision(pPrecision->GetPrecision());
	pNode->SetMapFactor(pMapFactor->GetMapFactor());
	pNode->SetScaleFactor(pScaleFactor->GetScaleFactor());
	pNode->SetMasterMultFac(1); // temporary: should come from MASTER CARD  todo
	//////////////////
	return;
	
} 

void CDlg_Node::SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	///////////////////////////////////////////////////////// Color/View Number 
	COLORREF Color 	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
	///////////////////////////////////////////////////////// Update Current Label
	pLabel->SetObjectType((int)LABEL);
	pLabel->SetElemType((int)DRAW_OBJECT);              // globals.h
    pLabel->SetLevelType((int)LEVEL_GRAPA);         // globals
	pLabel->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	pLabel->SetText(m_id);
	pLabel->SetType(LABEL_NODE);       
	pLabel->SetViewNum(m_nActiveViewNumber);
	/////////////////////////////
	pLabel->SetContextObj(CO_NODE);
	pLabel->SetNodePtr(pAddNode);
	///////////////////////////// Reciprocate
	pAddNode->GetLabelList()->AddTail(pLabel);
	pLabel->SetMoved(FALSE);   // forces coord. to be recognized on 3D basis
	/////////////////////////////     
	pLabel->SetColor(Color); 
	pLabel->SetAngle(0);       // Horizontal Label
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	////////////
	return;
}


BOOL CDlg_Node::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnHelpInfo(pHelpInfo);
}
 
/*
void CDlg_Node::SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(((CDrGrafApp*)AfxGetApp())->m_pDoc ); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////
	if (nView == VIEW12)        // hor = x; ver = y;
	{
		pCorner->x = pCorner3->x;
		pCorner->y = pCorner3->y;
	}
	else if (nView == VIEW23)   // hor = z; ver = y;
	{
		pCorner->x = pCorner3->z;
		pCorner->y = pCorner3->y;
	}
	else if (nView == VIEW31)   // hor = x; ver = z;
	{
		pCorner->x = pCorner3->x;
		pCorner->y = pCorner3->z;
	}
	///////
	return;
	
}

/////////////SAve following/needed for Drg ///////////////////////////////

/////////////////////////////
//  REFERENCE NODE RESOLUTION
/////////////////////////////
	LONG  lWorldBase  = pDoc->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
	int nLength = m_nid_r.GetLength();
	if (!nLength)
	{
		(pNode->GetNodeCard())->x 		= (LONG) (m_xWorld*dWorldBase );	
		(pNode->GetNodeCard())->y 		= (LONG) (m_yWorld*dWorldBase );	
		(pNode->GetNodeCard())->z 		= (LONG) (m_zWorld*dWorldBase );	
	}
	else                                                  // Add Reference Node X,Y & Z
	{
	int nMaxNodes     = pEBoxMgr->GetNodeCount();
    if(nMaxNodes)
    {
		int index;
    	if((index = pEBoxMgr->GetNodeIndex(m_nid_r,1))<0)
    	{
	    	MessageBeep(0);
	    	return;
		}	    	
		CDrNode* pNode 	 	= pEBoxMgr->GetNode(index);       // Reference NODE 
	
    	LONG ref_xLong 		= (pNode->GetNodeCard())->x;
    	LONG ref_yLong 		= (pNode->GetNodeCard())->y;
    	LONG ref_zLong 		= (pNode->GetNodeCard())->z;
*/
///////////////////////////////////////////////////////////////
///////////////////////////////// End of Module ///////////////*
