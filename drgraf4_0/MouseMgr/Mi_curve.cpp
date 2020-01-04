// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include "glb_Type.h"
#include "glb_CuPS.h"

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "EDlgMgr.h"  
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// specials
#include "spdefine.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
//#include "elmouse.h" 
#include "MI_Curve.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Curve,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Curve::CMI_Curve()
{

	m_nCNodeDone   		= 0;
    /////////////////////////////////////////// Curve
	m_nMaxCurveCNodes	= MIN_CNODES_CURVE;
	m_bClosed			= FALSE;
	m_nSegs				= 0;
	///////////////////////////////////////////
    
}

CMI_Curve::~CMI_Curve()
{
   
}

int CMI_Curve::Post_Curve(CDrObject* pObject)
{

	//////////////////////////
	return 0;
}		

int CMI_Curve::LBDownInit_CInsert(UINT nType) 
{	
			
//?	m_bDirtyCurve = FALSE;
//?	m_nOut		  = 0;
    /////////
	return 0;

}

int CMI_Curve::LBUpInit_CInsert(enum CURVEPROC kind) 
{
//?	m_CurveType	= kind;
	if(!m_nCNodeDone)
	{
		if(kind == CP_BSPLINE)
			m_nMaxCurveCNodes = 5; // for BSpline We need one more(5)
		else	
		if(kind == CP_BEZIER)
			m_nMaxCurveCNodes = 4;
		else	
		if(kind == CP_LINEAR)
			m_nMaxCurveCNodes = 2;
		else	
		if(kind == CP_QUADRATIC)
			m_nMaxCurveCNodes = 3;
	}		
	/////////
	return 0;
}
	
int CMI_Curve::LBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
    CELMouse* pELMouse		= pDoc->GetMouseMgr()->GetELMouse(nView);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(m_nCNodeDone <= 0) 								// Firsttime 
	{
		m_pDrCurve 		= C_GetInfo(1);                  	// CGen Dialog
		if(!m_pDrCurve)		// cancel
			return -1;
//?		m_pCNodeList	= m_pDrCurve->GetCNodeList();
	}	
	///////////////////////////////////////////////////////////
	if(!pELMouse->ShowNode(pID,TRUE,1))       // Control Nodes
	{
		m_nCNodeDone++;
		SetCurrentCNodeID(*pID);
	}
	else									// cancelled
		return -1;
	///////////		          
	SaveCNode(m_pDrCurve->GetCNodeList(),pID);
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetCurveList()->InsertObject(m_pDrCurve);
	/////////////////////////////////////
	if(m_nCNodeDone < m_nMaxCurveCNodes)
		return 0;
	///////////////////////////////////////////////////////////////////// Go Generate	
	m_nCNodeDone = 0; 	//reset
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrCurve->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	////////////////////////////
	InsertAllInfo(kind);
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}			

int CMI_Curve::InsertAllInfo(enum CURVEPROC kind)
{ 

	///////////////////////////////////// Compute No. of Curves
	int nCurves;
	////////////////////////////////////////////////////////////
	if(kind == CP_HERMITE || kind == CP_BEZIER ||
			kind == CP_BSPLINE)
		/////////////////////////////////////////// Compute Cubics & Fill DrCurve Info
		m_pDrCurve->NumberOfCurves(kind,m_nMaxCurveCNodes,&nCurves,m_bClosed,4);
	else	
	if(kind == CP_QUADRATIC)
		/////////////////////////////////////////// Compute Linears & Fill DrCurve Info
		m_pDrCurve->NumberOfCurves(kind,m_nMaxCurveCNodes,&nCurves,m_bClosed,3);
	else	
	if(kind == CP_LINEAR)
		/////////////////////////////////////////// Compute Linears & Fill DrCurve Info
		m_pDrCurve->NumberOfCurves(kind,m_nMaxCurveCNodes,&nCurves,m_bClosed,2);
	//////////////////////////////////// save in DrCurve
	m_pDrCurve->SetCurveType_S(kind);
	m_pDrCurve->SetMaxCubicCurves(nCurves);
//	m_pDrCurve->SetMaxOutPts_S(nOut);
//	m_pDrCurve->SetLongOutPts();
	m_pDrCurve->SetDirty(TRUE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();											
	////////////////////////////////////// Post NODES & ...
	if(PostNodes_FWD()<0)
		return -1;
	///////////////
	return 0;
	///////////////
	
}			 

int CMI_Curve::RBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrCurve 		= C_GetInfo(2);                  	// CCon Dialog
	if(!m_pDrCurve)		// cancel
		return -1; 
	/////////////////////////////////////////////// Copy ControlNodes (Right Button)
//?	m_pCNodeList = m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////////////////////////////// Go Generate	
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrCurve->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	////////////////////////////
	InsertAllInfo(kind);
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}			

CDrCurve* CMI_Curve::C_GetInfo(int nButton)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CEDlgMgr* pEDlgMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if(nButton ==1)		//Left Button
		if (pEDlgMgr->DoModal_Curve_LB(&Cid,m_CurveType,0) == IDCANCEL)
			return (CDrCurve*)NULL;
	if(nButton ==2)		//Right Button
		if (pEDlgMgr->DoModal_Curve_RB(&Cid,m_CurveType,m_nMaxCurveCNodes) == IDCANCEL)
			return (CDrCurve*)NULL;
    /////////////////////////////////////////////////////// update
//?	m_CurrentCurveID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{						
		CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_nMaxCurveCNodes	= pDrCurve->GetMaxCNodes_S();
		m_nSegs				= pDrCurve->GetSegmentCount_S();
		m_bClosed			= pDrCurve->IsClosed_S();
		///////////////////////////////////////////// for Right Button
/*?
		if(nButton == 2)
		{
			m_nCubicCurves	= pDrCurve->GetMaxCubicCurves();
			m_nOut			= (long)(pDrCurve->GetMaxOutPts());
		}
*/	
		////////////////		
		return pDrCurve;
	}
	else
		return (CDrCurve*)NULL;
}			
			
void CMI_Curve::SaveCNode(CDListMgr* pList,CString* pID)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	////////////////////////////////////////// save in LIST
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	//////////////////////////////////
	pList->InsertObject(pDrNode);
	//////////////////////////////////
}	

int CMI_Curve::RBDown_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{
	return 0; 
}

int CMI_Curve::PostNodes_FWD()
{
/*
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int s,t=0,j,index;
	//////////////////////////////////// Name
	CurveID	= m_pDrCurve->GetObjectID();
	nChLen	= CurveID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	//////////////////////////////	
	for (s = 0; s<m_nOut; s++)
	{
		///////////////////////////////////////// CREATE	
		Nid	= CurveID.Left(nChLen);
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		//////////////////////////////////// Node Index in m_pOut
		index = s;
		LocalPos = *(m_pOut+index);
		////////
		pAddNode = PostNode(Nid,LocalPos,FALSE);
		m_pNodeList->InsertObject(pAddNode);
		//////////////////////////////////////// Reciprocate
		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	} 
*/	
	return 0;

}

void CMI_Curve::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ELMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" ELMouse:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


