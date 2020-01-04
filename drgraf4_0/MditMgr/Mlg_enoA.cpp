// NodeProp.cpp : implementation file
//
#include "stdafx.h"

#include <stdio.h>			// sscanf:cannot Use in DLL
#include <math.h>
#include "3DMath.h"

#include "Def_Objs.h"
#include "Def_View.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
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
#include "Mlg_ENoA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////
// CMlg_ENoA dialog

CMlg_ENoA::CMlg_ENoA(CWnd* pParent /*=NULL*/)
	: CDialog(CMlg_ENoA::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CMlg_ENoA)
	m_nid_r 	= "";
	m_FromID	= "";
	m_ToID		= "";
	m_xWorld	= 0.0;
	m_yWorld	= 0.0;
	m_zWorld	= 0.0;
	m_bnid_c 	= FALSE;
	m_strLn		= _T("0.0");
	m_strDx		= _T("0.0");
	m_strDy		= _T("0.0");
	m_strDz		= _T("0.0");
	//}}AFX_DATA_INIT
	m_bCoord	= TRUE;
	m_dLength	= 0.0;
	m_DxWorld	= 0.0;
	m_DyWorld	= 0.0;
	m_DzWorld	= 0.0;
}

void CMlg_ENoA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMlg_ENoA)
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

BEGIN_MESSAGE_MAP(CMlg_ENoA, CDialog)
	//{{AFX_MSG_MAP(CMlg_ENoA)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_COORD, OnCoord)
	ON_BN_CLICKED(IDC_DIRECTION, OnDirection)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM, OnSelchangeCnodeFrom)
	ON_CBN_SELCHANGE(IDC_CNODE_TO, OnSelchangeCnodeTo)
	ON_CBN_SELCHANGE(IDD_NODE_NID_R, OnSelchangeNodeNidR)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_STARTOVER, OnStartOver)
	ON_EN_CHANGE(IDD_NODE_DX, OnChangeNodeDx)
	ON_EN_CHANGE(IDD_NODE_DY, OnChangeNodeDy)
	ON_EN_CHANGE(IDD_NODE_DZ, OnChangeNodeDz)
	ON_EN_CHANGE(IDD_LENGTH, OnChangeLength)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_COORD, OnCoord)
	ON_BN_DOUBLECLICKED(IDC_DIRECTION, OnDirection)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_STARTOVER, OnStartOver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlg_ENoA message handlers

BOOL CMlg_ENoA::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////////////////////////// Input Mode
	m_bCoord = m_pDrNode->GetInputMode();
	if(m_bCoord)
		((CButton*)GetDlgItem(IDC_COORD))->SetCheck(TRUE);// for Coord only	
	else
		((CButton*)GetDlgItem(IDC_DIRECTION))->SetCheck(TRUE);// for Direction only	
	//////////////////////////////
	Init_NodeData();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	////////////////////////////////////// set title: Node or CNode
//	pWndCtrl = GetDlgItem(IDD_ELP_NODE);
	if(m_bnid_c)
		SetWindowText("Mesh Control Node Properties");
	else
		SetWindowText("Mesh Node Properties");
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
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(FE0D);
	if(nMaxNodes)
	{
		FillListAllString();
		FillListforAllNodeCombos();	// FromID, ToID and NID_R
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CMlg_ENoA::Init_NodeData()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	CWnd* pWndCtrl;
	///////////////////////////////////////////////
	m_id = m_pDrNode->GetObjectID();
	///////////////////////////////////////////////////////////////////////////////////////
	int nActiveObjIndex = -1;
	if(m_pDrNode->IsControlNode() )
		nActiveObjIndex = pObjectMgr->GetObjectIndexfromKey(MCNODE,m_id,1);//notactive = -1
	else
	if(m_pDrNode->IsMeshNode() )
		nActiveObjIndex = pObjectMgr->GetObjectIndexfromKey(MNODE,m_id,1);//notactive = -1
	else
		nActiveObjIndex = pObjectMgr->GetObjectIndexfromKey(FE0D,m_id,1);//notactive = -1
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
	/////////////////////////////////////////////////////////////////// Mode
	if(m_bCoord)
	{
		////////////////
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);// for Direction only	
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);// for Direction only
		GetDlgItem(IDD_LENGTH)->EnableWindow(FALSE);// for Direction only
		/////////////////////////////////////////////
		GetDlgItem(IDD_NODE_DX)->EnableWindow(TRUE);// Coordinates Input
		GetDlgItem(IDD_NODE_DY)->EnableWindow(TRUE);// Coordinates Input
		GetDlgItem(IDD_NODE_DZ)->EnableWindow(TRUE);// Coordinates Input
	}
	else
	{
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
	}
	////////////////////////////////////////////////// Disable:Display Coords
	GetDlgItem(IDD_NODE_X2)->EnableWindow(FALSE);
	GetDlgItem(IDD_NODE_Y2)->EnableWindow(FALSE);
	GetDlgItem(IDD_NODE_Z2)->EnableWindow(FALSE);
	/////////////////////////////////////////////
}

void CMlg_ENoA::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMlg_ENoA::OnStartOver() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)
    ////////////////
	Init_NodeData();
	////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CMlg_ENoA::OnCoord() 
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
	OnStartOver();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
	
}

void CMlg_ENoA::OnDirection() 
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
	/////////////////////////// ReSet
	OnStartOver();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CMlg_ENoA::OnChangeNodeDx() 
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

void CMlg_ENoA::OnChangeNodeDy() 
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

void CMlg_ENoA::OnChangeNodeDz() 
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

void CMlg_ENoA::OnSelchangeCnodeFrom() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CMlg_ENoA::OnSelchangeCnodeTo() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////
	ResolveReference_Direction();
	////////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CMlg_ENoA::OnChangeLength() 
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

void CMlg_ENoA::OnSelchangeNodeNidR() 
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

int CMlg_ENoA::ResolveReference_Direction()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
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
	CDrFE0D* 	pDrNode;
	////////////////////////////////////////////////////// RefNode
	if(m_nid_r == "")
	{
		m_xWorld = 0.0;
		m_yWorld = 0.0;
		m_zWorld = 0.0;
	}
	else
	{
		///////////////////////////////////////// Check if ID already Exist
		int nIndex;//notactive = -1
		if(m_pDrNode->IsControlNode() )
			nIndex = pObjectMgr->GetObjectIndexfromKey(MCNODE,m_id,1);//notactive = -1
		else
		if(m_pDrNode->IsMeshNode() )
			nIndex = pObjectMgr->GetObjectIndexfromKey(MNODE,m_id,1);//notactive = -1
		else
			nIndex = pObjectMgr->GetObjectIndexfromKey(FE0D,m_id,1);//notactive = -1
		////////////////
		if(index>=0)
			pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
		else
		{
			AfxMessageBox("Error:\nCMlg_ENoA::OnSelchangeCnodeTo\nm_nid_r");
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
		m_xWorld = xWorld + m_dLength * Axis.x;
		m_yWorld = yWorld + m_dLength * Axis.y;
		m_zWorld = zWorld + m_dLength * Axis.z;
		////////
	}
	/////////
	return 0;
}

int CMlg_ENoA::ResolveReference_Coords()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
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
	CDrFE0D* 	pDrNode;
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
		///////////////////////////////////////// Check if ID already Exist
		int nIndex;//notactive = -1
		if(m_pDrNode->IsControlNode() )
			nIndex = pObjectMgr->GetObjectIndexfromKey(MCNODE,m_nid_r,1);//notactive = -1
		else
		if(m_pDrNode->IsMeshNode() )
			nIndex = pObjectMgr->GetObjectIndexfromKey(MNODE,m_nid_r,1);//notactive = -1
		else
			nIndex = pObjectMgr->GetObjectIndexfromKey(FE0D,m_nid_r,1);//notactive = -1
		////////////////
//		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_nid_r,1);
		if(index>=0)
			pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
		else
		{
			AfxMessageBox("Error:\nCMlg_ENoA::OnSelchangeCnodeTo\nm_nid_r");
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

int CMlg_ENoA::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	//////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
    /////////////////
	int 		index;
	CDrFE0D* 	pDrNode;
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
	pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	index	= pObjectMgr->GetObjectIndexfromKey(MCNODE,m_FromID,1);
	if(index>=0)
		pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
	else
	{
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
		index	= pObjectMgr->GetObjectIndexfromKey(FE0D,m_FromID,1);
		if(index>=0)
		pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
		else
		{
			pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
			index	= pObjectMgr->GetObjectIndexfromKey(FE0D,m_FromID,1);
			if(index>=0)
			pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
			else
			{
				AfxMessageBox("Error:\nCMlg_ENoA::UnitAxisFromEndNodes\nFromID");
				return -1;
			}
		}
	}
   	///////////////////////////////////////// get Raw Pt.
   	WORLD FromPt = *(pDrNode->GetLocalPos());
	////////////////////////////////////////////////////// ToNode
	pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	index	= pObjectMgr->GetObjectIndexfromKey(MCNODE,m_ToID,1);
	if(index>=0)
		pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
	else
	{
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
		index	= pObjectMgr->GetObjectIndexfromKey(FE0D,m_ToID,1);
		if(index>=0)
		pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
		else
		{
			pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
			index	= pObjectMgr->GetObjectIndexfromKey(FE0D,m_ToID,1);
			if(index>=0)
			pDrNode	= (CDrFE0D*)(pDListMgr->GetObject(index));
			else
			{
				AfxMessageBox("Error:\nCMlg_ENoA::UnitAxisFromEndNodes\nFromID");
				return -1;
			}
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

void CMlg_ENoA::OnOK()
{ 

//      case IDD_OK:     
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	if(!m_id.GetLength() )   // blank nIDs
	{
		AfxMessageBox("No NodeID!!\nPlease Select an ID");
   		return;
   	} 
	///////////////////////////////////////// save Old Before Change 
	CString OldID = m_pDrNode->GetObjectID();
	/////////////////////////////////////////
	m_pDrNode->SetCategory(CA_ELEMENT);
    SetInfoForDataBase(m_pDrNode,FALSE);
	/////////////////////////////////////
	int index = m_pDrNode->GetLabelList()->GetObjectIndex(LABEL, OldID);
	if(index<0)
	{
		AfxMessageBox("Internal ERROR:\nCMlg_ENoA::OnOK()\nLabelIndex<0");
   		return;
   	} 
    CDrLabel* pLabel = (CDrLabel*)m_pDrNode->GetLabelList()->GetObject(index);
    SetInfoForNodeLabel(m_pDrNode,pLabel);
	/////////////////////////////////////////
	CDialog::OnOK();

} 

void CMlg_ENoA::OnSelchangeList()
{
//      case IDD_LIST:
	/////////////////////////////////////// do nothing Op
	if(1==1)
		return;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
	//////////////////////////////////////////////////////
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(FE0D);
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
//	CDrFE0D Node;
	///////////////////////////////////////////////
   	if((i= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
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
void CMlg_ENoA::FillOthers(int i)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	int nMaxNodes     = pDListMgr->GetCount();
	CDrFE0D* pNode 	  = (CDrFE0D*)(pDListMgr->GetObject(i));       // NODE 
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
//		m_bCoord		= pNode->GetInputMode();
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

void CMlg_ENoA::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Nid;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(FE0D);
    if(nMaxNodes>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == FE0D)
			{ 
				CDrFE0D* pNode = (CDrFE0D*)pObject;
	   			Nid   = (pNode->GetNodeCard())->id;
//	   			if((pNode->GetNodeCard())->bnid_c == m_bnid_c)		// node for node/cnode for cnode
			    ((CListBox*)(pWndCtrl))->AddString(Nid); // Show ALL 
			}			    
    	}
	} 
    
}    

void CMlg_ENoA::FillListforAllNodeCombos()
{

   	((CComboBox*)(GetDlgItem(IDC_CNODE_FROM)))->ResetContent();	// Remove ALL  
   	((CComboBox*)(GetDlgItem(IDC_CNODE_TO)))->ResetContent();	// Remove ALL  
   	((CComboBox*)(GetDlgItem(IDD_NODE_NID_R)))->ResetContent();	// Remove ALL   
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////
	CDListMgr* pDListMgr = NULL;
	if(m_pDrNode->IsControlNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_pDrNode->IsMeshNode() )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	///////////////////////////////////////////////
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
	CString Nid;
	
	int nMax = pDListMgr->GetSpecificObjectCount(FE0D);
    if(nMax<0)
		return;
	//////////////////////////////////
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == FE0D)
		{ 
			CDrFE0D* pNode = (CDrFE0D*)pObject;
   			Nid   = (pNode->GetNodeCard())->id;
//   			if((pNode->GetNodeCard())->bnid_c == m_bnid_c)		// node for node/cnode for cnode
//			{
		    	((CComboBox*)(GetDlgItem(IDC_CNODE_FROM)))->AddString(Nid);		// Show ALL  
		    	((CComboBox*)(GetDlgItem(IDC_CNODE_TO)))->AddString(Nid);		// Show ALL  
		    	((CComboBox*)(GetDlgItem(IDD_NODE_NID_R)))->AddString(Nid);		// Show ALL   

//			}
		}			    
   	}
   
}    

void CMlg_ENoA::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CMlg_ENoA::SetInfoForDataBase(CDrFE0D* pNode,BOOL bGen)
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
	pNode->SetObjectType((int)FE0D);
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

void CMlg_ENoA::SetInfoForNodeLabel(CDrFE0D* pAddNode,CDrLabel* pLabel)
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


BOOL CMlg_ENoA::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnHelpInfo(pHelpInfo);
}
 
/*
void CMlg_ENoA::SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView)
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
		CDrFE0D* pNode 	 	= pEBoxMgr->GetNode(index);       // Reference NODE 
	
    	LONG ref_xLong 		= (pNode->GetNodeCard())->x;
    	LONG ref_yLong 		= (pNode->GetNodeCard())->y;
    	LONG ref_zLong 		= (pNode->GetNodeCard())->z;
*/
///////////////////////////////////////////////////////////////
///////////////////////////////// End of Module ///////////////*
