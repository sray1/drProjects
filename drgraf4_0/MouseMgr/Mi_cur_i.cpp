// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h> 

#include "Def_Type.h"
#include "Def_CuPS.h"

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "MCurMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// specials
#include "Def_Spec.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "MC_Circle.h" 
#include "MC_Lin.h"
#include "MC_Quad.h"
#include "MC_Cube.h"
 

#include "MI_Cur_I.h" 
/////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Cur_I,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
/////////////////////////////////////////////////////////////////////////////
CMI_Cur_I::CMI_Cur_I()
{

//	m_nINodeDone   		= 0;
    /////////////////////////////////////////// Curve
}

CMI_Cur_I::~CMI_Cur_I()
{
}	
/*	
int CMI_Cur_I::LBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
    CELMouse* pELMouse		= pDoc->GetMouseMgr()->GetELMouse(nView);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(m_nINodeDone <= 0) 								// Firsttime 
	{
		m_pDrCurve 		= C_GetInfo(kind,1);                  	// CGen Dialog
		if(!m_pDrCurve)		// cancel
			return -1;
//?		m_pINodeList	= m_pDrCurve->GetINodeList();
	}	
	///////////////////////////////////////////////////////////
	if(!pELMouse->ShowNode(pID,FALSE,1))       // Interpolation Nodes
	{
		m_nINodeDone++;
		SetCurrentINodeID(*pID);
	}
	else									// cancelled
		return -1;
	///////////		          
	SaveINode(m_pDrCurve->GetINodeList(),pID);
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr				= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetCurveList()->InsertObject(m_pDrCurve);
	/////////////////////////////////////
	if(m_nINodeDone < m_nMaxCurveINodes)
		return 0;
	///////////////////////////////////////////////////////////////////// Go Generate	
	m_nINodeDone = 0; 	//reset
	CString* str = new CString;
	char* buf = str->GetBuffer(80);
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrCurve->GetINodeList()->GetCount());
	AfxMessageBox(*str);
	str->ReleaseBuffer();
	delete str;
	////////////////////////////
	InsertAllInfo(m_nOrder_S);
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}			
*/
int CMI_Cur_I::RBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(kind == CP_CIRCLE)
	{
//		CMC_Circle	MC_Circle;
//		m_pDrCurve 	= MC_Circle.GoDoIt();
		if(!m_pDrCurve)
			return -1;
	}
	else
	if(kind == CP_LINEAR)
	{
		CMC_Lin		MC_Lin;
		m_pDrCurve 	= MC_Lin.GoDoIt();
		if(!m_pDrCurve)
			return -1;
	}
	else
	if(kind == CP_QUADRATIC)
	{
		CMC_Quad	MC_Quad;
		m_pDrCurve 	= MC_Quad.GoDoIt();
		if(!m_pDrCurve)
			return -1;
	}
	else
	if(kind == CP_BSPLINE||kind == CP_BEZIER||kind == CP_NURB)
	{
		CMC_Cube	MC_Cube;
		m_pDrCurve 	= MC_Cube.GoDoIt();
		if(!m_pDrCurve)
			return -1;
	}
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}
/*			
void CMI_Cur_I::SaveINode(CDListMgr* pList,CString* pID)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	////////////////////////////////////////// save in LIST
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr 				= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	//////////////////////////////////
	pList->InsertObject(pDrNode);
	//////////////////////////////////
}	
*/
int CMI_Cur_I::RBDown_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{
	return 0; 
}

int CMI_Cur_I::Post_Curve(CDrObject* pObject)
{

	//////////////////////////
	return 0;
}		
void CMI_Cur_I::Serialize(CArchive& ar)
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


