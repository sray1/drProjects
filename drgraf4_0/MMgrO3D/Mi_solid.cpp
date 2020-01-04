// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "glb_Objs.h"
///////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "EBoxmgr.h" 
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Msdefine.h" // Mesh Types for Solid
///////////////////// dialogMgr
#include "EDlgMgr.h"
#include "EDl2Mgr.h"
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
///////////////////// DrawObjs
#include "drdefine.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "spdefine.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "PA_Xtrud.h" 
#include "PA_Rotat.h" 
#include "PA_Duct.h" 
#include "PA_Sweep.h" 
#include "PA_Loft2.h"
 
#include "MI_Solid.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_SATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Solid,CMI_Patch,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Solid::CMI_Solid()
{

	m_nCNodeDone   		= 0;
    /////////////////////////////////////////// Mesh/Solid
	m_CurrentSolidID	= "BLANK";
	m_nMaxSolidCNodes_S	= MIN_CNODES_CURVE;
	m_nMaxSolidCNodes_T	= MIN_CNODES_CURVE;
	m_nMaxSolidCNodes_R	= MIN_CNODES_CURVE;
	m_nMaxSolidCNodes	= 	m_nMaxSolidCNodes_S
						 *	m_nMaxSolidCNodes_T
						 *	m_nMaxSolidCNodes_R;
}

CMI_Solid::~CMI_Solid()
{
   
}

int CMI_Solid::LBDownInit_SInsert(UINT nType) 
{
//	m_bDirtySolid		= FALSE;
	return 0;
}

int CMI_Solid::LBUpInit_SInsert(enum PATCHTYPE kind) 
{
	m_PatchType	= kind;
	//////////////////////////
/*
	if(!m_nCNodeDone && (kind == PA_BSPLINE))
	{
		m_nMaxSolidCNodes_R++; // for BSpline We need one more(5)
		m_nMaxSolidCNodes_S++; // for BSpline We need one more(5)
		m_nMaxSolidCNodes_T++; // for BSpline We need one more(5)
		m_nMaxSolidCNodes	= 	m_nMaxSolidCNodes_S
							 * 	m_nMaxSolidCNodes_T
							 * 	m_nMaxSolidCNodes_R;
    } 
*/
	return 0;
}

int CMI_Solid::LBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 	= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
    CELMouse* pELMouse	= pDoc->GetMouseMgr()->GetELMouse(nView);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(m_nCNodeDone <= 0) 								// Firsttime 
	{
		m_pDrSolid 		= S_Mesh_GetInfo(1);   			// SGen Dialog
		if(!m_pDrSolid)		// cancel
			return -1;
	}	
	///////////////////////////////////////////////////////////
	if(!pELMouse->ShowNode(pID,TRUE,1))              	// Control Nodes
	{
		m_nCNodeDone++;
		SetCurrentCNodeID(*pID);
	}
	else									// cancelled
		return -1;
	///////////		          
	SaveCNode(m_pDrSolid->GetCNodeList(),pID);
	/////////////////////////////////////
	if(m_nCNodeDone < m_nMaxSolidCNodes)
		return 0;
	///////////////////////////////////////////////////////////////////// Go Generate	
	m_nCNodeDone = 1; 	//reset
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrSolid->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	//////////////////////////////// Compute Cubics & Fill DrSolid Info
	m_pCNodeList = m_pDrSolid->GetCNodeList();
	//////////////////////////////
/*
	if(kind == PA_BEZIER)	
		m_SolidType = SO_BEZIER;
	else	
	if(kind == PA_BSPLINE)	
		m_SolidType = SO_BSPLINE;
*/
	////////////	
	m_pDrSolid->SetSolidType(m_SolidType);
	m_pDrSolid->SetPatchType(kind);
	//////////////////////////////////////////////////////////
	// 	NumberOfCubicSolides() Computes & Sets in DrSolid:	//
	//					m_nMaxCubicSolides_S            	//
	//					m_nMaxCubicSolides_T            	//
	//					m_nMaxCubicSolides_R            	//
	//					m_nOut_S							//			
	//					m_nOut_T							//							
	//					m_nOut_R							//							
	//					m_nOut      						//
	//////////////////////////////////////////////////////////							
//	m_pDrSolid->NumberOfCubicSolides();
	m_pDrSolid->NumberOfSolides();
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////
	return 0;		 
}			

int CMI_Solid::LBUp_SDuctInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID,CurveID;
	CString*	pID = &ID, pCurveID;
	//////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Duct_GetInfo();       // PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	///////                    				// ControlNode Mesh
	S_Duct();
	/////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Solid::LBUp_SSweepInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID,CurveID;
	CString*	pID = &ID, pCurveID;
	////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Sweep_GetInfo();  // PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	/////// 
	S_Sweep();							// ControlNode Mesh
	/////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Solid::LBUp_SLoftInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID,CurveID;
	CString*	pID = &ID, pCurveID;
	////////////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Loft_GetInfo();   // PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	//////////////////////////////////////////////////////////////// clear
	if(!(m_CNListLoft.IsEmpty() ) )
		m_CNListLoft.RemoveAll();
	///////////////////////////////	
	S_Loft();							// ControlNode Mesh
	/////////////////
	if(InsertMeshInfo(TRUE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Solid::LBUp_SRotateInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Rotate_GetInfo(); // PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	/////// 
	S_Rotate();							// ControlNode Mesh
	/////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Solid::LBUp_SExtrudeInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Extrude_GetInfo();// PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	/////// 
	S_Extrude();							// ControlNode Mesh
	/////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}

void CMI_Solid::FillCNodesLOCAL(CDListMgr* pPatchCNodeList,
							pWORLD pIn,int nMaxCNodes,
							BOOL bSave,BOOL bLoft)
{
	/////////////////////////////////////////
	int i;
	CDrNode* pDrNode;
    /////////////////
	WORLD 	LocalPos;
	//////////////////////////////////////////// Get point 
    for(i = 0; i<nMaxCNodes; i++)              
    {
    	pDrNode = (CDrNode*)(pPatchCNodeList->GetObject(i));
    	//////////////////////////////////////// Save in Solid
    										  // CNodeList
		if(bSave)
		{
			if(bLoft)
				m_CNListLoft.AddTail(pDrNode);// Temporary
			else
				m_pCNodeList->AddTail(pDrNode); 
		}		
    	//////////////////////////////////////// Pt.
    	LocalPos = *(pDrNode->GetLocalPos());
    	/////////////////////////////////
		pIn[i].x = LocalPos.x;	  
		pIn[i].y = LocalPos.y;  
		pIn[i].z = LocalPos.z;
		/////////////////////
	}	
}

int CMI_Solid::InsertMeshInfo(BOOL bLoft)
{
	//////////////////////////////////////////////////////
	// For ALL cases other than Mesh, All ControlNodes	//
	// Must be Put in CNodeList of the Solid. However,	//
	//	1.	some of them already created by generating	//
	//		patch such as								//
	//			DUCT & SWEEP: X-Section Patch CNodes	//
	//			EXTRUDE/ROT.: Generating Patch CNodes	//
	//			LOFT        : Start & End Patches'		// 
	//							CNodes					//
	//	2.	Rest or In-Betweens have to generate		// 
	//					DrNodes							//
	//	3.	Inherent in Loft creation, Start/End Patches//
	//		Already created CNodes get interweaved		//
	//		Need to sort out because we dont want to	//
	//		create what are already posted				//
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,SolidID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int st,r,j;
	///////////////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (r = 0; r<m_nMaxSolidCNodes_R; r++)
	{
		for (st = 0; st<m_nMaxSolidCNodes_ST; st++)
		{
			if(r == 0)		// first st of them already in List
				continue;   // do nothing
			///////////////////////
			if( bLoft && (r == m_nMaxSolidCNodes_ST-1) )
			{
				// get Already created saved in TemporaryList
				pAddNode = (CDrNode*)m_CNListLoft.GetObject(st);
				///////////////////////////////////// in SOLID 	
   				m_pCNodeList->InsertObject(pAddNode); //CNodeList
   				//////////////
   				continue;
   			}
   			///////////////////////////////////////// CREATE	
//			Nid		= SolidID.Left(nChLen);
			Nid		= SolidID;
		    //////////////////////////////////// Name
		    sprintf(buf,"%d%d%d",	st/m_nMaxSolidCNodes_S,
		    						st%m_nMaxSolidCNodes_S,r);
		    Nid += buf; 
			////////////////////////////////////
			j = r*m_nMaxSolidCNodes_ST + st;
			////////////////////////////		
			LocalPos.x	= (m_pOut+j)->x;
			LocalPos.y	= (m_pOut+j)->y;
			LocalPos.z	= (m_pOut+j)->z;
			///////////////////////////////////// in THE List 
			if(!(pAddNode = PostNode(Nid,LocalPos,TRUE)))	// Create DrCNode
				return -1;
			///////////////////////////////////// in PATCH 	
   			m_pCNodeList->InsertObject(pAddNode); //CNodeList 
			//////////////////////////////////////////////
		}				
	}
	/////////////////////////////////////////// temporarily here
	WORLD Local;
	int ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	}
	////////////////////////////////////////// Save Info inSolid
	m_pDrSolid->SetFromPtLocal_R(m_FromPt);
	m_pDrSolid->SetToPtLocal_R(m_ToPt);
	m_pDrSolid->SetAxis_R(m_vAxis);
	////////////////////////////////////////////////////// All Other
	m_pDrSolid->SetSolidType(m_SolidType);
	m_pDrSolid->SetPatchType(m_PatchType);
	m_pDrSolid->SetMaxCNodes_S(m_nMaxSolidCNodes_S);
	m_pDrSolid->SetMaxCNodes_T(m_nMaxSolidCNodes_T);
	m_pDrSolid->SetMaxCNodes_R(m_nMaxSolidCNodes_R);
	///////////////////////////////////////////////////
	m_pDrSolid->SetSegmentCount_S(m_nSegs_S);	
	m_pDrSolid->SetSegmentCount_T(m_nSegs_T); 
	m_pDrSolid->SetSegmentCount_R(m_nSegs_R); 
	m_pDrSolid->SetClosed_S(m_bClosed_S);
	m_pDrSolid->SetClosed_T(m_bClosed_T);
	m_pDrSolid->SetClosed_R(m_bClosed_R);
	m_pDrSolid->SetDirty(TRUE);
	//////////////////////////////////////////////////
	// call to NumberOfCubicSolides() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	m_pDrSolid->SetLongOutPts(m_nOut);	
	m_pDrSolid->SetOut_S(m_nOut_S);	
	m_pDrSolid->SetOut_T(m_nOut_T);
	m_pDrSolid->SetOut_R(m_nOut_R);
	///////////////////////////////////	
/*
	if(	(m_SolidType == SO_BEZIER) ||		// computes rest
		(m_SolidType == SO_BSPLINE)	)
		m_pDrSolid->NumberOfCubicSolides();
	else
	if	(m_SolidType == SO_LINEAR)
		m_pDrSolid->NumberOfLinearSolides();
*/
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	////////////////
	return 0;
}			

int CMI_Solid::RBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView) 
{

	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Mesh_GetInfo(2);                  	// PCon Dialog
	if(!m_pDrSolid)		// cancel
		return -1; 
	/////////////////////////////////////////////// Copy ControlNodes (Right Button)
	m_pCNodeList = m_pDrSolid->GetCNodeList();	
	///////////////////////////////////////////////////////////////////// Go Generate	
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrSolid->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	/////////
	return 0;		 
}			

CDrSolid* CMI_Solid::S_Mesh_GetInfo(int nButton)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* pEDlgMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if(nButton ==1)		//Left Button
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
			return (CDrSolid*)NULL;
	if(nButton ==2)		//Right Button
		if (pEDlgMgr->DoModal_SolidCon(&Cid,4) == IDCANCEL)
			return (CDrSolid*)NULL;
    /////////////////////////////////////////////////////// update
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
		m_nMaxSolidCNodes_S	= pDrSolid->GetMaxCNodes_S();
		m_nMaxSolidCNodes_T	= pDrSolid->GetMaxCNodes_T();
		m_nMaxSolidCNodes_R	= pDrSolid->GetMaxCNodes_R();
		///////////////////////////////////////////////////
		m_nMaxSolidCNodes_ST = m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
		m_nMaxSolidCNodes	 = m_nMaxSolidCNodes_ST * m_nMaxSolidCNodes_R;
		///////////////////////////////////////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			

CDrSolid* CMI_Solid::S_Extrude_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pEDlgMgr->DoModal_Solid_Extrude(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL;
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_FromID 		= pDrSolid->GetFromID_R();
		m_ToID			= pDrSolid->GetToID_R();
		m_CurveID_S[0]	= pDrSolid->GetCurveID(0);// Ist one is Patch
		m_dLen			= pDrSolid->GetLength_R();
		m_nSegs_RCon	= pDrSolid->GetSegs_R();	//segs in Extrusion dirn
		////////////////
		return pDrSolid;
	}
	else 
		return (CDrSolid*)NULL;
}			

CDrSolid* CMI_Solid::S_Rotate_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pEDlgMgr->DoModal_Solid_Rotate(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL; 
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_FromID 		= pDrSolid->GetFromID_R();
		m_ToID			= pDrSolid->GetToID_R();
		m_CurveID_S[0]	= pDrSolid->GetCurveID(0); // Ist One is Patch
		m_dAng_1		= pDrSolid->GetAng_1_R();
		m_dAng_2		= pDrSolid->GetAng_2_R();
		m_nSegs_RCon	= pDrSolid->GetSegs_R();
		////////////////
		return pDrSolid;
	}
	else 
		return (CDrSolid*)NULL;
}			

CDrSolid* CMI_Solid::S_Sweep_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
	if (pEDlgMgr->DoModal_Solid_Swip(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL; 
/*			
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
*/	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
	   	//////////////////////////////
		m_FromID 		= pDrSolid->GetFromID_R(); // AnchorID
		m_CurveID_S[0]	= pDrSolid->GetCurveID(0); // Ist One is Patch
		m_CurveID_S[1]	= pDrSolid->GetCurveID(1);
		m_CurveID_S[2]	= pDrSolid->GetCurveID(2);
		m_CurveID_S[3]	= pDrSolid->GetCurveID(3);
		m_nSegs_R		= pDrSolid->GetSegs_R();
		////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			

CDrSolid* CMI_Solid::S_Duct_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
	if (pEDlgMgr->DoModal_Solid_Duct(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL;
/*
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
*/	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_FromID 		= pDrSolid->GetFromID_R(); // AnchorID
		m_CurveID_S[0]	= pDrSolid->GetCurveID(0); // Ist One is Patch
		m_CurveID_S[1]	= pDrSolid->GetCurveID(1);
		m_CurveID_S[2]	= pDrSolid->GetCurveID(2);
		m_nSegs_R		= pDrSolid->GetSegs_R();
		////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			

CDrSolid* CMI_Solid::S_Loft_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
	if (pEDlgMgr->DoModal_Solid_Loft(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL;
/*
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
*/	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_CurveID_S[0]	= pDrSolid->GetCurveID(0); // Ist One is Patch
		m_CurveID_S[1]	= pDrSolid->GetCurveID(1); // 2nd One is Patch
		m_nSegs_R		= pDrSolid->GetSegs_R();
		////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			

////////////////// Control Node Generation /////////////////
int CMI_Solid::S_Duct() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		CurveID,PatchID;
	BOOL		bPutinCNodeList = FALSE;
	long 	sizeOut,nPts;
	pWORLD 	pOut,pIn;
	/////////////////////////////////////////////////////// Generate CNodes
	//////////////////////////////////////// get Patch Info	
	PatchID = m_CurveID_S[0];
	/////////////////////////
	int index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
		return -1;
	///////////	
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
	m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
	/////////////////////////////////////////// Memory ControlPts 
	if( !(m_pIn_S[0] = FixMem((long)m_nMaxSolidCNodes_ST)) )
	{
		AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	///////////////////////////////////////// Store LOCAL Pos
	bPutinCNodeList = TRUE;// XSection CNodes
	FillCNodesLOCAL(pDrPatch->GetCNodeList(),
		m_pIn_S[0],m_nMaxSolidCNodes_ST,bPutinCNodeList,FALSE);
	//////////////////////
	m_nOut_S	= (int)pDrPatch->GetOut_S();
	m_nOut_T	= (int)pDrPatch->GetOut_T();
	m_nOut_ST	= pDrPatch->GetLongOutPts();
	m_nSegs_S	= pDrPatch->GetSegmentCount_S();
	m_nSegs_T	= pDrPatch->GetSegmentCount_S();
	///////////////////////////////////////////////
	m_PatchType	= pDrPatch->GetPatchType();
	//////////////////////////////
/*
	if(m_PatchType == PA_BEZIER)
		m_SolidType = SO_BEZIER;
	else	
	if(m_PatchType == PA_BSPLINE)
		m_SolidType = SO_BSPLINE;
	else
	if(m_PatchType == PA_DUCT)
		m_SolidType = SO_LINEAR;
*/
	/////////////////////////////////////////////
	m_nOut_SCon			= (int)m_nMaxPatchCNodes_S;
	m_nOut_TCon			= (int)m_nMaxPatchCNodes_T;
	m_nOut_STCon		= (int)m_nMaxSolidCNodes_ST;
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	m_bClosed_S			= pDrPatch->IsClosed_S();	// X-Section
	m_bClosed_T			= pDrPatch->IsClosed_T();	// X-Section
	/////////////////////////////////////////////////////////////////
    for(int i=1;i<3;i++)		// other curves
    {
		//////////////////////////////////////// get Curve Info	
   		CurveID = m_CurveID_S[i];
   		/////////////////////////
		int index	= pObjectMgr->
						GetObjectIndexfromKey(CURVE,CurveID,1);
		if(index>=0)
		{
			////////////////////////	
			pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
			CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
			if(!pDrCurve)
				return -1;
			/////////////////	
			m_nMaxCurveCNodes = pDrCurve->GetMaxCNodes_S();
			/////////////////////////////////////////// Memory ControlPts 
			if( !(m_pIn_S[i] = FixMem((long)m_nMaxCurveCNodes)) )
			{
				AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
				return -1;
			}
			/////////////////////////// Store LOCAL Pos
			FillCNodesLOCAL(pDrCurve->GetCNodeList(),
				m_pIn_S[i],m_nMaxCurveCNodes,FALSE,FALSE);
			if(i == 1)		// Spine Curve 
			{
				/////////////////////////////		
				m_nOut_R			= (int)pDrCurve->GetLongOutPts();
				m_nSegs_R			= m_nOut_R - 1;
				m_nOut_RCon			= (int)m_nMaxCurveCNodes;
				m_nMaxSolidCNodes_R = m_nOut_RCon;
				m_bClosed_R			= pDrCurve->IsClosed_S();	// 
				//////////////////////////////////
			}	
 	  	}
	} 
	////////////////////////////////// Save SolidInfo
	m_nOut				= 	(	
								((long)m_nOut_ST)*
								((long)m_nOut_R) 
							);				
	m_nOutCon			= 	(
								((long)m_nOut_STCon)*
								((long)m_nOut_RCon) 
							);				
	m_nMaxSolidCNodes	= m_nOutCon;
    ///////////////////////////////////////// Anchor Node Coords.
    UnitAxisFromEndNodes(1);
	/////////////////////////////////////////// Memory OutPts 
	if( !(m_pOut = m_pDrSolid->FixMem(m_nOutCon)) )
	{
		AfxMessageBox("CMI_Solid::Duct\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Duct
	int nResult = S_Duct_GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMI_Solid::S_Sweep() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		CurveID,PatchID;
	BOOL		bPutinCNodeList = FALSE;
	long 	sizeOut,nPts;
	pWORLD 	pOut,pIn;
	/////////////////////////////////////////////////////// Generate CNodes
	//////////////////////////////////////// get Patch Info:XSection	
	PatchID = m_CurveID_S[0];
	/////////////////////////
	int index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
		return -1;
	///////////	
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
	m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
	/////////////////////////////////////////// Memory ControlPts 
	if( !(m_pIn_S[0] = FixMem((long)m_nMaxSolidCNodes_ST)) )
	{
		AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	///////////////////////////////////////// Store LOCAL Pos
	bPutinCNodeList = TRUE;// XSection CNodes
	FillCNodesLOCAL(pDrPatch->GetCNodeList(),
		m_pIn_S[0],m_nMaxSolidCNodes_ST,bPutinCNodeList,FALSE);
	//////////////////////
	m_nOut_S	= (int)pDrPatch->GetOut_S();
	m_nOut_T	= (int)pDrPatch->GetOut_T();
	m_nOut_ST	= pDrPatch->GetLongOutPts();
	m_nSegs_S	= pDrPatch->GetSegmentCount_S();
	m_nSegs_T	= pDrPatch->GetSegmentCount_S();
	///////////////////////////////////////////////
	m_PatchType	= pDrPatch->GetPatchType();
	//////////////////////////////
	if(1 == 1)
	{
		AfxMessageBox("Still Need to fix next few lines");
/*	
	if(m_PatchType == PA_BEZIER)
		m_SolidType = SO_BEZIER;
	else	
	if(m_PatchType == PA_BSPLINE)
		m_SolidType = SO_BSPLINE;
	else
	if(m_PatchType == PA_LINEAR)
		m_SolidType = SO_LINEAR;
*/		
	}	
	/////////////////////////////////////////////
	m_nOut_SCon			= (int)m_nMaxPatchCNodes_S;
	m_nOut_TCon			= (int)m_nMaxPatchCNodes_T;
	m_nOut_STCon		= (int)m_nMaxSolidCNodes_ST;
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	m_bClosed_S			= pDrPatch->IsClosed_S();	// X-Section
	m_bClosed_T			= pDrPatch->IsClosed_T();	// X-Section
	/////////////////////////////////////////////////////////////////
    for(int i=1;i<4;i++)		// other curves
    {
		//////////////////////////////////////// get Curve Info	
   		CurveID = m_CurveID_S[i];
   		/////////////////////////
		int index	= pObjectMgr->
						GetObjectIndexfromKey(CURVE,CurveID,1);
		if(index>=0)
		{
			////////////////////////	
			pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
			CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
			if(!pDrCurve)
				return -1;
			/////////////////	
			m_nMaxCurveCNodes = pDrCurve->GetMaxCNodes_S();
			/////////////////////////////////////////// Memory ControlPts 
			if( !(m_pIn_S[i] = FixMem((long)m_nMaxCurveCNodes)) )
			{
				AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
				return -1;
			}
			/////////////////////////// Store LOCAL Pos
			FillCNodesLOCAL(pDrCurve->GetCNodeList(),
				m_pIn_S[i],m_nMaxCurveCNodes,FALSE,FALSE);
			if(i == 1)		// Spine Curve 
			{
				/////////////////////////////		
				m_nOut_R			= (int)pDrCurve->GetLongOutPts();
				m_nSegs_R			= m_nOut_R - 1;
				m_nOut_RCon			= (int)m_nMaxCurveCNodes;
				m_nMaxSolidCNodes_R = m_nOut_RCon;
				m_bClosed_R			= pDrCurve->IsClosed_S();	// 
				//////////////////////////////////
			}	
 	  	}
	} 
	////////////////////////////////// Save SolidInfo
	m_nOut				= 	(	
								((long)m_nOut_ST)*
								((long)m_nOut_R) 
							);				
	m_nOutCon			= 	(
								((long)m_nOut_STCon)*
								((long)m_nOut_RCon) 
							);				
	m_nMaxSolidCNodes	= m_nOutCon;
    ///////////////////////////////////////// Anchor Node Coords.
    UnitAxisFromEndNodes(1);
	/////////////////////////////////////////// Memory OutPts 
	if( !(m_pOut = m_pDrSolid->FixMem(m_nOutCon)) )
	{
		AfxMessageBox("CMI_Solid::Duct\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Sweep
	int nResult = S_Sweep_GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMI_Solid::S_Loft() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////
	CString	PatchID;
	BOOL	bPutinCNodeList = TRUE,bLoft = FALSE;
	int 	nMaxCNodes0,nMaxCNodes1;
	///////////////////////////////////////// Generate CurvePts
    for(int i=0;i<2;i++)
    {
    	PatchID = m_CurveID_S[i];// both Patches
		//////////////////////////////////////// get Curve Info	
		int index	= pObjectMgr->
						GetObjectIndexfromKey(PATCH,PatchID,1);
		if(index>=0)
		{						
			pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
			CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
			if(!pDrPatch)
				return -1;
			/////////////////	
			m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
			m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
			m_nMaxSolidCNodes_ST 	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
			/////////////////////////////////////////// Memory ControlPts 
			if( !(m_pIn_S[i] = FixMem((long)m_nMaxPatchCNodes)) )
			{
				AfxMessageBox("CMI_Solid::Patch\nFixMemforCNodes Failure!");
				return -1;
			}
			/////////////////////////// Store LOCAL Pos	
   			if(i == 1) 
   				bLoft = TRUE; // 2nd set of CNodes in a different list
			FillCNodesLOCAL(pDrPatch->GetCNodeList(),
				m_pIn_S[i],m_nMaxSolidCNodes_ST,bPutinCNodeList,
				bLoft);
			////////////////////////////////////
			if(i<=0)		// Start Patch
			{
				/////////////////////////////////////// Save Patch
				m_nOut_S	= (int)pDrPatch->GetOut_S();
				m_nOut_T	= (int)pDrPatch->GetOut_T();
				m_nOut_ST	= pDrPatch->GetLongOutPts();
				m_nSegs_S	= pDrPatch->GetSegmentCount_S();
				m_nSegs_T	= pDrPatch->GetSegmentCount_S();
				m_nOut_R	= m_nSegs_R + 1;
				///////////////////////////////////////////////
				m_PatchType	= pDrPatch->GetPatchType();
				//////////////////////////////
	if(1 == 1)
	{
		AfxMessageBox("Still Need to fix next few lines");
/*				
				if(m_PatchType == PA_BEZIER)
					m_SolidType = SO_BEZIER;
				else	
				if(m_PatchType == PA_BSPLINE)
					m_SolidType = SO_BSPLINE;
				else
				if(m_PatchType == PA_LINEAR)
					m_SolidType = SO_LINEAR;
*/					
	}
				//////////////////////////////	
//				if(m_SolidType == SO_LINEAR)
					m_nOut_R		= 2;
				/////////////////////////////////////////////
				m_bClosed_S			= pDrPatch->IsClosed_S();// X-Section
				m_bClosed_T			= pDrPatch->IsClosed_T();// X-Section
				//////////////////////////////////////// save to compare	
			    nMaxCNodes0			= m_nMaxPatchCNodes_S;
			    nMaxCNodes1			= m_nMaxPatchCNodes_T;
			    ///////////////////
				m_nOut_RCon			= 2;
				m_nMaxSolidCNodes_R = m_nOut_RCon;
			}	
			if(i == 1)		// End Curve 
			{
				if
				(
					nMaxCNodes0 != m_nMaxPatchCNodes_S ||
					nMaxCNodes1 != m_nMaxPatchCNodes_T 
				)
				{
					AfxMessageBox("Both Patches must have\nSame Number of Control Nodes!");
					return -1;
				}
				m_nOut_SCon			= (int)m_nMaxPatchCNodes_S;
				m_nOut_TCon			= (int)m_nMaxPatchCNodes_T;
				m_nOut_STCon		= (int)m_nMaxSolidCNodes_ST;
				m_nMaxSolidCNodes_S = m_nOut_SCon;
				m_nMaxSolidCNodes_T = m_nOut_TCon;
				m_nSegs_SCon		= m_nOut_SCon - 1;
				m_nSegs_TCon		= m_nOut_TCon - 1;
				m_nSegs_RCon		= m_nOut_RCon - 1;
			}	
 	   }
	} 
	////////////////////////////////// Save SolidInfo
	m_nOut				= 	(	
								((long)m_nOut_ST)*
								((long)m_nOut_R) 
							);				
	m_nOutCon			= 	(
								((long)m_nOut_STCon)*
								((long)m_nOut_RCon) 
							);				
	m_nMaxSolidCNodes	= m_nOutCon;
	/////////////////////////////////////////// Memory OutPts 
	if( !(m_pOut = FixMem(m_nOutCon)) )
	{
		AfxMessageBox("CMI_Solid::Loft\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Loft 
	int nResult = S_Loft_GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	///////////////////////////////////////// Save Ist Row of CNodes
	int ntemp = m_pCNodeList->GetCount();
	/////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,SolidID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int st,r=0,j;
	///////////////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (st = 0; st<m_nMaxSolidCNodes_ST; st++)
	{
		///////////////////////////////////////// CREATE	
//		Nid		= SolidID.Left(nChLen);
		Nid		= SolidID;
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d%d",	st/m_nMaxSolidCNodes_S,
	    						st%m_nMaxSolidCNodes_S,r);
	    Nid += buf; 
		////////////////////////////////////
		LocalPos.x	= (m_pOut+st)->x;
		LocalPos.y	= (m_pOut+st)->y;
		LocalPos.z	= (m_pOut+st)->z;
		///////////////////////////////////// in THE List 
		if(!(pAddNode = PostNode(Nid,LocalPos,TRUE)))	// Create DrCNode
			return -1;
		///////////////////////////////////// in SOLID 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList 
		//////////////////////////////////////////////
	}				
	/////////////////////////////////////////// temporarily here
	WORLD Local;
	ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	}
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMI_Solid::S_Rotate() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////////
	CString		PatchID;
	BOOL		bPutinCNodeList = TRUE;
	int i;
	//////////////////////////////////////// get Patch Info:XSection	
	PatchID = m_CurveID_S[0];
	/////////////////////////
	int index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
		return -1;
	///////////	
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
	m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
	/////////////////////////////////////////// Memory ControlPts 
	if( !(m_pIn_S[0] = FixMem((long)m_nMaxSolidCNodes_ST)) )
	{
		AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	///////////////////////////////////////// Store LOCAL Pos
	bPutinCNodeList = TRUE;// XSection CNodes
	FillCNodesLOCAL(pDrPatch->GetCNodeList(),
		m_pIn_S[0],m_nMaxSolidCNodes_ST,bPutinCNodeList,FALSE);
	//////////////////////
	m_nOut_S	= (int)pDrPatch->GetOut_S();
	m_nOut_T	= (int)pDrPatch->GetOut_T();
	m_nOut_ST	= pDrPatch->GetLongOutPts();
	m_nSegs_S	= pDrPatch->GetSegmentCount_S();
	m_nSegs_T	= pDrPatch->GetSegmentCount_T();
	///////////////////////////////////////////////
	m_PatchType	= pDrPatch->GetPatchType();
	//////////////////////////////
	if(1 == 1)
	{
		AfxMessageBox("Still Need to fix next few lines");
/*
	if(m_PatchType == PA_BEZIER)
		m_SolidType = SO_BEZIER;
	else	
	if(m_PatchType == PA_BSPLINE)
		m_SolidType = SO_BSPLINE;
	else
	if(m_PatchType == PA_LINEAR)
		m_SolidType = SO_LINEAR; 
*/
	}		
	/////////////////////////////////////////////
	m_nOut_SCon			= (int)m_nMaxPatchCNodes_S;
	m_nOut_TCon			= (int)m_nMaxPatchCNodes_T;
	m_nOut_STCon		= (int)m_nMaxSolidCNodes_ST;
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	m_bClosed_S			= pDrPatch->IsClosed_S();	// X-Section
	m_bClosed_T			= pDrPatch->IsClosed_T();	// X-Section
	/////////////////////////////////////////////
	m_nOut_RCon			= m_nSegs_RCon + 1;
	if((m_dAng_1 == 0.) && (m_dAng_2 == 360.))
		m_bClosed_R			= TRUE;
	else	
		m_bClosed_R			= FALSE;				
	//////////////////////////////////////////////////////////
	m_nOut_R			= m_nOut_RCon;
	m_nSegs_R			= 1;
	//////// 
	m_nSegs_SCon		= m_nOut_SCon - 1;
	m_nSegs_TCon		= m_nOut_TCon - 1;
	m_nSegs_RCon		= m_nOut_RCon - 1;
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	m_nMaxSolidCNodes_R = m_nOut_RCon;
	////////////////////////////////// Save SolidInfo
	m_nOut				= 	(	
								((long)m_nOut_ST)*
								((long)m_nOut_R) 
							);				
	m_nOutCon			= 	(
								((long)m_nOut_STCon)*
								((long)m_nOut_RCon) 
							);				
	m_nMaxSolidCNodes	= m_nOutCon;
    ///////////////////////////////////////// AxisVector from
    									   // end nodes	
    UnitAxisFromEndNodes(0);
	/////////////////////////////////////////// Memory OutPts 
	if( !(m_pOut = FixMem(m_nOutCon)) )
	{
		AfxMessageBox("CMI_Solid::Rotate\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Rotate 
	int nResult = S_Rotate_GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMI_Solid::S_Extrude() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;

	///////////////////////////////////////////////////
	CString		PatchID;
	BOOL		bPutinCNodeList = TRUE;
	int i;
	//////////////////////////////////////// get Patch Info:XSection	
	PatchID = m_CurveID_S[0];
	/////////////////////////
	int index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
		return -1;
	///////////	
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
	m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
	/////////////////////////////////////////// Memory ControlPts 
	if( !(m_pIn_S[0] = FixMem((long)m_nMaxSolidCNodes_ST)) )
	{
		AfxMessageBox("CMI_Solid::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	///////////////////////////////////////// Store LOCAL Pos
	bPutinCNodeList = TRUE;// XSection CNodes
	FillCNodesLOCAL(pDrPatch->GetCNodeList(),
		m_pIn_S[0],m_nMaxSolidCNodes_ST,bPutinCNodeList,FALSE);
	///////////////////////////////////////////////
	m_PatchType	= pDrPatch->GetPatchType();
	//////////////////////////////
	if(1 == 1)
	{
		AfxMessageBox("Still Need to fix next few lines");

/*	if(m_PatchType == PA_BEZIER)
		m_SolidType = SO_BEZIER;
	else	
	if(m_PatchType == PA_BSPLINE)
		m_SolidType = SO_BSPLINE;
	else
	if(m_PatchType == PA_LINEAR)
		m_SolidType = SO_LINEAR;
*/		
	}		
	/////////////////////////////////////////////
	m_nOut_S	= (int)pDrPatch->GetOut_S();
	m_nOut_T	= (int)pDrPatch->GetOut_T();
	m_nOut_ST	= pDrPatch->GetLongOutPts();
	m_nSegs_S	= pDrPatch->GetSegmentCount_S();
	m_nSegs_T	= pDrPatch->GetSegmentCount_T();
	//////////////////////////////////////////////////////////
	//	because Extrusion is StraightLine, we actually need	//
	//	Only 2 for m_nOut_T, but for Bezier Solid we need	//
	//			Atleast:                                    //
	//			 4 in each direction for BEZIER				//
	//			 5 in each direction for BSPLINE			//
	//////////////////////////////////////////////////////////
	m_nOut_SCon			= (int)m_nMaxPatchCNodes_S;
	m_nOut_TCon			= (int)m_nMaxPatchCNodes_T;
	m_nOut_STCon		= (int)m_nMaxSolidCNodes_ST;
	////////////////////////
/*	
	m_nOut_RCon			= 4;
	if(m_SolidType == SO_BSPLINE)
		m_nOut_RCon		= 5;
	else		
	if(m_SolidType == SO_LINEAR)
		m_nOut_RCon		= 2;
*/			
    ///////////////////////////////////
	m_nOut_RCon			= m_nSegs_RCon + 1;// for bezier/bspline needs
										// HullSplitting later
	m_nSegs_R			= 1;
	//////// 
	m_bClosed_S			= pDrPatch->IsClosed_S();	// X-Section
	m_bClosed_T			= pDrPatch->IsClosed_T();	// X-Section
	m_bClosed_R			= FALSE;
	
	m_nSegs_SCon		= m_nOut_SCon - 1;
	m_nSegs_TCon		= m_nOut_TCon - 1;
	m_nSegs_RCon		= m_nOut_RCon - 1;
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	m_nMaxSolidCNodes_R = m_nOut_RCon;
	////////////////////////////////// Save SolidInfo
	m_nOut				= 	(	
								((long)m_nOut_ST)*
								((long)m_nOut_R) 
							);				
	m_nOutCon			= 	(
								((long)m_nOut_STCon)*
								((long)m_nOut_RCon) 
							);				
	m_nMaxSolidCNodes	= m_nOutCon;
    ///////////////////////////////////////// AxisVector from
    									   // end nodes	
    UnitAxisFromEndNodes(0);
	/////////////////////////////////////////// Memory OutPts 
	if( !(m_pOut = FixMem(m_nOutCon)) )
	{
		AfxMessageBox("CMI_Solid::Extrude\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Extrude 
	int nResult = S_Extrude_GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			
//////////////////////////////////////////////////////////
int CMI_Solid::S_Duct_GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Duct	PA_Duct;
/*todo	
	int nOutActual	= PA_Duct.Duct
			(
				m_FromPt,		//	Anchor 3D Pt. for Xsec scale,twist etc
		    	m_nOut_SCon,	//	number of cross section points
		      	m_pIn_S[0],		//	cross section curve ControlPts
		   		m_nOut_TCon,	//	number of path points
		      	m_pIn_S[1],		//	path curve ControlPts
		      	m_pIn_S[2],		//	path rotation curve ControlPts
//		      	m_pIn_S[3],		//	path rotation factors
		      	m_pOut			//	Output ControlPts array
			);
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else 
*/			

		return 0;
												
}

int CMI_Solid::S_Sweep_GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Sweep	PA_Sweep;
/*	
	int nOutActual	= PA_Sweep.Sweep
			(
				m_FromPt,		//	Anchor 3D Pt. for Xsec scale,twist etc
		    	m_nOut_SCon,	//	number of cross section points
		      	m_pIn_S[0],		//	cross section curve ControlPts
		   		m_nOut_TCon,	//	number of path points
		      	m_pIn_S[1], 	//	path curve ControlPts
		      	m_pIn_S[2], 	//	path scaling curve ControlPts
		      	m_pIn_S[3], 	//	path rotation curve ControlPts
		      	m_pOut			//	Output ControlPts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else 
*/
		return 0;
												
}

int CMI_Solid::S_Loft_GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Loft2	PA_Loft2;
/*	
	int nOutActual	= PA_Loft2.LoftCurves_2
			(
				(short)m_nSegs_TCon,//	subdivision value (interior spaces)
				m_Ratio,			//  Output Last/Ist ratio in T_Direction
				(short)m_nOut_SCon,	//	number of input data points
				m_pIn_S[0],			//	input Start curve ControlPts
				m_pIn_S[1],			//	input End curve ControlPts
				m_pOut				//	Output ControlPts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
*/
		return 0;
												
}

int CMI_Solid::S_Extrude_GenerateCNodes()
{
	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Xtrud	PA_Xtrud;
/*	
	int nOutActual	= PA_Xtrud.ExtrudeCurve
			(
				m_dLen,			//	distance to the extended surface's end
				m_vAxis,		//	unit extrusion vector (direction)
				m_nSegs_TCon,	//	subdivision value (interior spaces)
				m_Ratio,		//  Output Last/Ist ratio in T_Direction
				m_nOut_SCon,	//	number of input data points
				m_pIn_S[0],		//	input XSec curve dataPts
				m_pOut			//	Output ControlPts
			);
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
*/			
		return 0;
												
}

int CMI_Solid::S_Rotate_GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Rotat	PA_Rotat;
/*	
	int nOutActual	= PA_Rotat.RotateCurve
			(
				m_dAng_2,		//	total rotation in degrees
				m_vAxis,		//	unit rotation vector (direction)
				m_FromPt,		//	a pt. on the rotation vector
				m_nSegs_TCon,	//	subdivision value (interior spaces)
				m_Ratio,		//  Output Last/Ist ratio in T_Direction
				m_nOut_SCon,	//	number of input data points
				m_pIn_S[0],		//	input XSec curve ControlPts
				m_pOut			//	Output Pts array
			);
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
*/	
		return 0;
												
}
////////////////////////////////////////////////////////////
void CMI_Solid::UnitAxisFromEndNodes(int nType)
{
	//////////////////////////////////////////////////////////////
	// nType = 0, do it all the way(Axis):Rotate/Extrude
	//       = 1, just compute LocalPos of m_FromID
	//			  (For Sweep/Duct Anchor Node)
	//////////////////////////////////////////////////////////////

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
    /////////////////
	int 		index;
	CDrNode* 	pDrNode;
//    int			nPrecision;
//	long 		lCoord_1[3],lCoord_2[3];
//	WORLD		ptDest_1,ptDest_2;
	////////////////////////////////////////////////////// FromNode
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
		AfxMessageBox("Bug:GN_SATCH-UnitAxisFromEndNodes");	
   	///////////////////////////////////////////// get Raw Pt.
   	m_FromPt = *(pDrNode->GetLocalPos());
	//////////////////////////////// For Sweep/duct
	if(nType == 1)
		return; 
	////////////////////////////////////////////////////// ToNode
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1);
	pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
   	///////////////////////////////////////////// get Raw Pt.
  	m_ToPt = *(pDrNode->GetLocalPos());
	///////////////////////////////////////////// Vector
	m_vAxis.x = m_ToPt.x - m_FromPt.x;  
	m_vAxis.y = m_ToPt.y - m_FromPt.y;  
	m_vAxis.z = m_ToPt.z - m_FromPt.z;  
	///////////////////////// Unit
	double NewD =	m_vAxis.x*m_vAxis.x +  
    				m_vAxis.y*m_vAxis.y +
    				m_vAxis.z*m_vAxis.z;
	double r = 1.0/sqrt(NewD);
	///////////////////////////// Unit vector
	m_vAxis.x *= r;  
	m_vAxis.y *= r;  
	m_vAxis.z *= r;
	///////////////
}
//////////////////////////////////////////////////////////// Posting 
int CMI_Solid::LBUpSolidPost()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrSolid 		= Post_GetInfo();// PGen Dialog
	if(!m_pDrSolid)		// cancel
		return -1;
	//////////////////////////////////	
	PostNodes_FWD();							// ControlNode Mesh
	/////////////////
	if(PostMeshInfo_FWD()<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}

int CMI_Solid::PostNodes_FWD()
{
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,SolidID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	long st,r,j;
	long index;
	//////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	//////////////////////////////	
	for (r = 0; r<m_nOut_R; r++)
	{
		for (st = 0; st<m_nOut_ST; st++)
		{
   			///////////////////////////////////////// CREATE	
//			Nid	= SolidID.Left(nChLen);
			Nid	= SolidID;
		    //////////////////////////////////// Name
	    	sprintf(buf,"%d%d%d",	st/m_nMaxSolidCNodes_S,
	    						st%m_nMaxSolidCNodes_S,r);
	    	Nid += buf; 
			//////////////////////////////////// Node Index in m_pOut
			index = r*m_nOut_ST + st;
			LocalPos = *(m_pOut+index);
			////////
			pAddNode = PostNode(Nid,LocalPos,FALSE);
			m_pNodeList->InsertObject(pAddNode);
			////////
		}
	}
	return 0;		
}

int CMI_Solid::PostMeshInfo_FWD()
{
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		PolyID,SolidID;
	int			nChLen,nMax_T,ix[4];
	char		buf[10];
    CDrNode* 	pAddNode;
    CDrFE2D*	pAddPoly;
	int 		s,t,j,index;
	//////////////////////////////////// SubDivision
	ValidateSubDiv();
	//////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (t = 0; t<(m_nOut_T-1); t++)
	{
		for (s = 0; s<(m_nOut_S-1); s++)
		{
   			///////////////////////////////////////// CREATE	
			PolyID		= SolidID.Left(nChLen);
		    //////////////////////////////////// Name
		    sprintf(buf,"%d%d",s,t);
		    PolyID += buf; 
			//////////////////////////////////// Node Index in NodeList
			index = t*m_nOut_S + s;
			/////////////////////// assumed AntiClock
			ix[0] = index;
			ix[1] = ix[0] + 1;
			ix[3] = ix[0] + m_nOut_S;
			ix[2] = ix[3] + 1;
			/////////////////////// last spline & closed(wrapped)
/*
			if(t == m_nOut_T-1)
			{
				ix[3] = s;
				ix[2] = s + 1;
			}
*/			
			/////////////////////////////////////		
			if( m_nOrient == OT_ANTICLOCK ||m_nOrient == OT_DUALSIDED ) 
			{
				if( m_nSubDiv == SU_NOSUB )
				{
					pAddPoly = MakePoly_4(PolyID,ix[0],ix[1],ix[2],ix[3]);
					m_pElemList->InsertObject(pAddPoly); //ElemList
				}	
				else
					SubDivide_FWD(PolyID,ix[0],ix[1],ix[2],ix[3]);
			}
			if( m_nOrient ==  OT_CLOCKWISE || m_nOrient == OT_DUALSIDED ) 
			{
				if( m_nSubDiv == SU_NOSUB )
				{
					pAddPoly = MakePoly_4(PolyID,ix[3],ix[2],ix[1],ix[0]);
					m_pElemList->InsertObject(pAddPoly); //ElemList
				}	
				else
					SubDivide_FWD(PolyID,ix[3],ix[2],ix[1],ix[0]);
			}
			//////////////////////////////////////////////
		}				
	}
	/////////////////////////////////////////// temporarily here
	CString Pid;
	CDListMgr* pList = m_pElemList;
	int ntemp = pList->GetCount();
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE2D* pPlat 	= (CDrFE2D*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Pid = pPlat->GetObjectID();
		//////////////////////////////////
		CDListMgr* pNodeList = pPlat->GetNodeList();
		ntemp = pNodeList->GetCount();
		////////////////////////////////
		for (POSITION posN = pNodeList->GetFirstObjectPos();posN !=NULL;)
		{
			CDrNode* pNode 	= (CDrNode*)pNodeList->GetNextObject(posN);
			/////////////////////////////////////////// ObjectInfo
			Pid = pNode->GetObjectID();
			//////////////////////////////////
		}	
	}
	////////////////////////////////
	pList = m_pNodeList;
	ntemp = pList->GetCount();
	////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Pid = pNode->GetObjectID();
		//////////////////////////////////
		CDListMgr* pElemList = pNode->GetElemList();
		int ntemp = pElemList->GetCount();
		////////////////////////////////
		for (POSITION posE = pElemList->GetFirstObjectPos();posE !=NULL;)
		{
			CDrFE2D* pPlat 	= (CDrFE2D*)pElemList->GetNextObject(posE);
			/////////////////////////////////////////// ObjectInfo
			Pid = pPlat->GetObjectID();
			//////////////////////////////////
		}	
	}
	////////////////
	return 0;
}			

void CMI_Solid::CalcCentroid(pWORLD pC,UINT ix0,UINT ix1,UINT ix2,UINT ix3)
{
	CDrNode* pNode;
	/////////////////////////
	pNode = (CDrNode*)m_pNodeList->GetObject(ix0);
	pWORLD p0 = pNode->GetLocalPos();
	pNode = (CDrNode*)m_pNodeList->GetObject(ix1);
	pWORLD p1 = pNode->GetLocalPos();
	pNode = (CDrNode*)m_pNodeList->GetObject(ix2);
	pWORLD p2 = pNode->GetLocalPos();
	pNode = (CDrNode*)m_pNodeList->GetObject(ix3);
	pWORLD p3 = pNode->GetLocalPos();
    ///////////////////
	pC->x	= (p0->x + p1->x + p2->x + p3->x) * .25;
	pC->y	= (p0->y + p1->y + p2->y + p3->y) * .25;
	pC->z	= (p0->z + p1->z + p2->z + p3->z) * .25;
	/////
}

int CMI_Solid::SubDivide_FWD(CString& PolyID,UINT ix0,UINT ix1,UINT ix2,UINT ix3)
{ 
	C3DMath Math3D;
	///////////////
	CDrNode* pNode;
	CDrFE2D* pAddElem;
	char	buf[10];
	UINT	cIx;
	WORLD	wx0,wx1,wx2,wx3,a,b,v0,v1;
	double	d;
	int		nCount;
    ///////////////////
	switch( m_nSubDiv ) 
	{
	
		case SU_ONCE:
		
			pAddElem = MakePoly_3(PolyID,ix0,ix1,ix3);
			m_pElemList->InsertObject(pAddElem); //ElemList
			pAddElem = MakePoly_3(PolyID,ix1,ix2,ix3);
			m_pElemList->InsertObject(pAddElem); //ElemList
			break;
			
			
		case SU_AUTO:
		
		    //////////////////////////////////////
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix0);
			wx0 	= *(pNode->GetLocalPos());
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix1);
			wx1 	= *(pNode->GetLocalPos());
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix2);
			wx2 	= *(pNode->GetLocalPos());
			///////
			Math3D.Sub3DPts(&wx0,&wx1,&a);
			Math3D.Sub3DPts(&wx2,&wx1,&b);
//			vCrossProduct((Vector*)&a,(Vector*)&b,(Vector*)&v0);
			Math3D.Cross3DPts(&a,&b,&v0);
			///////
			d = sqrt(v0.x*v0.x + v0.y*v0.y + v0.z*v0.z); //length  
			if( d <= 1 ) 
			{ // long thin sliver
				pAddElem = MakePoly_4(PolyID,ix0,ix1,ix2,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList
				break;
			}
			d = 1./d;
			v0.x *= d;
			v0.y *= d;
			v0.z *= d;
			/////////////////////////////////////
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix3);
			wx3 	= *(pNode->GetLocalPos());
			//////
			Math3D.Sub3DPts(&wx1,&wx2,&a);
			Math3D.Sub3DPts(&wx3,&wx2,&b);
			Math3D.Cross3DPts(&a,&b,&v1);
			//////
			d = sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z); //length  
			if( d <= 1 )
			{ // long thin sliver
				pAddElem = MakePoly_4(PolyID,ix0,ix1,ix2,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList
				break;
			}
			//////////
			d = 1/d;
			v1.x *= d;
			v1.y *= d;
			v1.z *= d;
			//////////
			d = Math3D.Dot3DPts(&v0,&v1);
			d = fabs( d );
			//////////////
			if( d>.99 )			// within 1% of co-planar 
			{	
				pAddElem = MakePoly_4(PolyID,ix0,ix1,ix2,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList
				break;
			}										// Fall through
			
		case SU_TWICE:
			/////////////////////////////////////// Generate Centroid
			nCount = m_pNodeList->GetCount();
			//////
			cIx = nCount+1;
			WORLD wcIx;
			CalcCentroid(&wcIx,ix0,ix1,ix2,ix3);
		    //////////////////////////////////// Name
		    sprintf(buf,"%c",'c');
		    PolyID += buf; 
			pNode = PostNode(PolyID,wcIx,FALSE);
			m_pNodeList->InsertObject(pNode);
			/////////////////////
		    sprintf(buf,"%c",'0');
		    PolyID += buf; 
			pAddElem = MakePoly_3(PolyID,cIx,ix0,ix1);
			m_pElemList->InsertObject(pAddElem); //ElemList
		    sprintf(buf,"%c",'1');
		    PolyID += buf; 
			pAddElem = MakePoly_3(PolyID,cIx,ix1,ix2);
			m_pElemList->InsertObject(pAddElem); //ElemList
		    sprintf(buf,"%c",'2');
		    PolyID += buf; 
			pAddElem = MakePoly_3(PolyID,cIx,ix2,ix3);
			m_pElemList->InsertObject(pAddElem); //ElemList
		    sprintf(buf,"%c",'3');
		    PolyID += buf; 
			pAddElem = MakePoly_3(PolyID,cIx,ix3,ix0);
			m_pElemList->InsertObject(pAddElem); //ElemList
			return 1;
	}
	return 0;
}

void CMI_Solid::ValidateSubDiv(void)
{
	switch( m_nSubDiv ) 
	{
		case SU_NOSUB:
		case SU_ONCE:
		case SU_TWICE:
		case SU_AUTO:
			break;
		default:
			m_nSubDiv = SU_NOSUB;
	}
}

CDrNode* CMI_Solid::PostNode(CString& Nid,WORLD Pt,BOOL bCNode)
{

	CEDlgMgr* 	pEDlgMgr;
	CDrNode*	pNode;
	/////////////////////////////////////////////
	pNode = pEDlgMgr->CreateNode(Nid,Pt,bCNode);
	//////////////////////////////////////////////
	return pNode;
}			

CDrFE2D* CMI_Solid::MakePoly_3(CString& PolyID,int ix0,int ix1,int ix2)
{
    CNewObjs*	pNewObjs;
    /////////////////////
	int ix[4];
	////////////
	ix[0] = ix0;
	ix[1] = ix1;
	ix[2] = ix2;
	ix[3] = ix2;
	//////////////////////////////////////////////////// Create
	CDrFE2D* pPoly = (CDrFE2D*)pNewObjs->NewObject(FE2D);
	pPoly->SetObjectID(PolyID);
	/////////////////////////////////////////////////
	PostPoly(pPoly,ix,4);
	///////////////////////
	return pPoly;
}
	
CDrFE2D* CMI_Solid::MakePoly_4(CString& PolyID,int ix0,int ix1,int ix2,int ix3)
{
	CNewObjs*	pNewObjs;
	/////////////////////
	int ix[4];
	////////////
	ix[0] = ix0;
	ix[1] = ix1;
	ix[2] = ix2;
	ix[3] = ix3;
	//////////////////////////////////////////////////// Create
	CDrFE2D* pPoly = (CDrFE2D*)pNewObjs->NewObject(FE2D);
	pPoly->SetObjectID(PolyID);
	/////////////////////
	PostPoly(pPoly,ix,4);
	/////////////////////
	return pPoly;
}
	
CDrNode* CMI_Solid::PostPoly(CDrFE2D* pPoly,int* index,int nEnds)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Plat
	CEDlgMgr* 	pEDlgMgr;
	CDrNode*	pNode;
	int			i,temp;
	//////////////////////////////////// guard against CUSP:rotate index
	WORLD LPos[4];
    for(i=0;i<nEnds;i++)
    {
		CDrNode* pNode = (CDrNode*)m_pNodeList->GetObject(index[i]);
		LPos[i] = *(pNode->GetLocalPos());
	}
	////////////////////
	if( wEQL(LPos[0],LPos[1]) )
	{
		temp		= index[0];
		index[0] 	= index[1];
		index[1]	= index[2];
		index[2] 	= index[3];
		index[3] 	= temp;
	}	
	if( wEQL(LPos[1],LPos[2]) )
	{
		temp		= index[0];
		index[0] 	= index[2];
		index[2] 	= temp;
		temp		= index[1];
		index[1] 	= index[3];
		index[3] 	= temp;
	}				
	/////////////////////////////////////////////////////  
    for(i=0;i<nEnds;i++)
    {
		CDrNode* pDrNode = (CDrNode*)m_pNodeList->GetObject(index[i]);
		pPoly->GetNodeList()->InsertObject(pDrNode);
		//////////////////////////////// save Current Plate Pointer in Nodes
		pDrNode->GetElemList()->InsertObject(pPoly);
	
  	}	
	//////////////////////////////////////////////
	pPoly->SetObjectType((int)FE2D);
	pPoly->SetElemType((int)EL3D_OBJECT);              // globals.h
    pPoly->SetLevelType((int)LEVEL_KIDDO);          // globals
	/////////////////////////////////////////////////
/*
	/////////////////////////////////////////////////
	(pPoly->GetPlatCard())->nid[0]		= m_nid_I;
	(pPoly->GetPlatCard())->nid[1]		= m_nid_J;
	(pPoly->GetPlatCard())->nid[2]		= m_nid_K;
	(pPoly->GetPlatCard())->nid[3]		= m_nid_L;
	(pPoly->GetPlatCard())->Thkness		= m_Thk;
	(pPoly->GetPlatCard())->pid			= m_propID;
	(pPoly->GetPlatCard())->mid			= m_matID;
	(pPoly->GetPlatCard())->rid[0]		= m_rid_I;
	(pPoly->GetPlatCard())->rid[1]		= m_rid_J;
	(pPoly->GetPlatCard())->rid[2]		= m_rid_K;
	(pPoly->GetPlatCard())->rid[3]		= m_rid_L;
	(pPoly->GetPlatCard())->refTemp		= m_RefTemp;
*/	 
    ////////////////////////////////////////////////////////////////// TEMPORARY
//	m_SlateType = "AxiSym";
	(pPoly->GetPlatCard())->IDNum		= 4;   // temporarily//3=Membrane; 4=2D FEM
    (pPoly->GetPlatCard())->nCorners	= nEnds;   //3=triangular; 4=quadrilateral
    (pPoly->GetPlatCard())->nPlateType	= 1;   //1=AxiSym;2=Pl.Strain;3=Pl.Stress(2D FEM)
/*
    for(int i=0;i<MAX_LOADS;i++)
    	(pPoly->GetPlatCard())->lid[i]	= m_lid;   //Loadcase A,B,C,D
    (pPoly->GetPlatCard())->sprid		= m_SPRid;   //stress print CodeID
    //////////////////////////////////////////////////////////////////////////////
*/
	///////////////////////////////////////////////
	pPoly->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pPoly->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////
	return 0;
}			

CDrSolid* CMI_Solid::Post_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
	if (pEDlgMgr->DoModal_Solid_Post(&Cid) == IDCANCEL)
			return (CDrSolid*)NULL;
/*
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
*/	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
   		m_nSubDiv	= pDrSolid->GetSubDiv();
		m_bClosed_T	= pDrSolid->IsClosed_T();	// 0 don't attach last to first, 1 do				/
		m_nOrient	= pDrSolid->GetOrient();	// -1 anti-clockwise, 0 both, 1 clockwise			/
		m_nOut_T	= pDrSolid->GetOut_T();		// Number of Splines= Nodes in T								/
		m_nOut_S	= pDrSolid->GetOut_S();		// Total number of Nodes in S							/
		m_nOut		= pDrSolid->GetLongOutPts();// Total number of Nodes
		/////////////////////////////////////////////////////////////////
		////////////////////////////////////////// Need to generate Solid
												// using Local CNodes
		pDrSolid->RefillCNLocalPosForPosting();	// for Posting
//		pDrSolid->Generate_Solid();
		//////////////////////////////////////////		
		m_pOut		= pDrSolid->GetMemOut();	// NodeCoord array 								/
//		m_pRA		= pDrSolid->GetRInfo(),		// Rendition Info
//		m_pLM		= pDrSolid->GetLocalTransform(pMATRIX xF)// Local Matrix
		m_pNodeList	= pDrSolid->GetNodeList(); 
		m_pElemList	= pDrSolid->GetElemList(); 
		////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			
////////////////////////////////////////////////////////////
void CMI_Solid::Serialize(CArchive& ar)
{

	CMI_Curve::Serialize( ar);              // must call base class Serializer
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
}

///////////////////////////////////// end of Module //////////////////////		


