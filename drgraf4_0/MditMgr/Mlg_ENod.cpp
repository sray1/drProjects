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
#include "CommRsrc.h"		// IDC_ADVANCED
#include "Mlg_ENoA.h"
#include "Mlg_ENod.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////
// CMlg_ENod dialog

CMlg_ENod::CMlg_ENod(CWnd* pParent /*=NULL*/)
	: CDialog(CMlg_ENod::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CMlg_ENod)
	m_xWorld	= 0.0;
	m_yWorld	= 0.0;
	m_zWorld	= 0.0;
	m_bnid_c 	= FALSE;
	m_id		= _T("");
	//}}AFX_DATA_INIT
}

void CMlg_ENod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMlg_ENod)
	DDX_Text(pDX, IDC_COORD_X, m_xWorld);
	DDX_Text(pDX, IDC_COORD_Y, m_yWorld);
	DDX_Text(pDX, IDC_COORD_Z, m_zWorld);
	DDX_Text(pDX, IDC_NID, m_id);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMlg_ENod, CDialog)
	//{{AFX_MSG_MAP(CMlg_ENod)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_STARTOVER2, OnStartOver)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_DOUBLECLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlg_ENod message handlers

BOOL CMlg_ENod::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	////////////////////////////////////////////////////// Input Mode
	Init_NodeData();
	///////////////////////////////////////////////////////////////////
	GetDlgItem(IDC_NID)->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CMlg_ENod::Init_NodeData()
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
	}	
}

void CMlg_ENod::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMlg_ENod::OnStartOver() 
{
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)
    ////////////////
	Init_NodeData();
	////////////////
	UpdateData(FALSE);			//TO  Screen(FALSE)    
 	///////////////////	
}

void CMlg_ENod::OnOK()
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
	if(m_id != OldID)
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
		if(nIndex>=0)
		{
			AfxMessageBox("NodeID Already Exists!\nPlease Select a New ID");
   			return;
		}
	}
	/////////////////////////////////////////
    SetInfoForDataBase(m_pDrNode,FALSE);
	/////////////////////////////////////
	int index = m_pDrNode->GetLabelList()->GetObjectIndex(LABEL, OldID);
	if(index<0)
	{
		AfxMessageBox("Internal ERROR:\nCMlg_ENod::OnOK()\nLabelIndex<0");
   		return;
   	} 
    CDrLabel* pLabel = (CDrLabel*)m_pDrNode->GetLabelList()->GetObject(index);
    SetInfoForNodeLabel(m_pDrNode,pLabel);
	/////////////////////////////////////////
	CDialog::OnOK();

} 
////////////////////////////////////////////////////////////// HELPERS
void CMlg_ENod::FillOthers(int i)
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
   		m_bnid_c  		= (pNode->GetNodeCard())->bnid_c;
	}   		
}

void CMlg_ENod::OnAdvanced() 
{
	////////////////////
	CMlg_ENoA	Nodedlg;
	////////////////////
	Nodedlg.m_pDrNode			= m_pDrNode;
	Nodedlg.m_id				= m_id;
	Nodedlg.m_nActiveViewNumber	= m_nActiveViewNumber;
	/////////////////////////////////////// Now Open Dialog/draw
	UINT nStatus = Nodedlg.DoModal(); 
	if(nStatus == IDOK)
		CDialog::OnOK();
	else
		CDialog::OnCancel();
	////////////////////////
}

void CMlg_ENod::SetInfoForDataBase(CDrFE0D* pNode,BOOL bGen)
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
	pNode->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	(pNode->GetNodeCard())->id 		= m_id;	
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

void CMlg_ENod::SetInfoForNodeLabel(CDrFE0D* pAddNode,CDrLabel* pLabel)
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
	pLabel->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	pLabel->SetText(m_id);
	pLabel->SetType(LABEL_NODE);       
	pLabel->SetViewNum(m_nActiveViewNumber);
	pLabel->SetMoved(FALSE);   // forces coord. to be recognized on 3D basis
	/////////////////////////////     
	pLabel->SetColor(Color); 
	pLabel->SetAngle(0);       // Horizontal Label
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	////////////
	return;
}


BOOL CMlg_ENod::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnHelpInfo(pHelpInfo);
}
 
/*
void CMlg_ENod::SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView)
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
