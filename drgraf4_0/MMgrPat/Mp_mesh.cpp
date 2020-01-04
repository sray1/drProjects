// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "glb_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "EBoxmgr.h" 
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MPatMgr.h"
//#include "Dlg_Node.h"  
///////////////////// elements
#include "Def_IGen.h"
//#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/*
#include "precison.h"
#include "mapfacto.h"
//#include "ScaleFac.h"
#include "DrFont.h"
*/
/////////////////////
//#include "elmouse.h"
#include "MI_Patch.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Patch,CMI_Curve,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Patch::CMI_Patch()
{
	m_pOut = NULL;
	for (int i=0;i<4;i++)
		m_pIn_S[i] = NULL;
	//////////////////////
	m_nCNodeDone   		= 0;
    /////////////////////////////////////////// Mesh/Patch
	m_CurrentPatchID	= "BLANK";
	m_nMaxPatchCNodes_S	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes_T	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
}

CMI_Patch::~CMI_Patch()
{
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	   
}

int CMI_Patch::LBDownInit_PInsert(UINT nType) 
{
//	m_bDirtyPatch		= FALSE;
	return 0;
}

int CMI_Patch::LBUpInit_PInsert(enum CURVETYPE kind) 
{
	m_CurveType	= kind;
	//////////////////////////
	if(!m_nCNodeDone && (kind == CU_BSPLINE))
	{
		m_nMaxPatchCNodes_S++; // for BSpline We need one more(5)
		m_nMaxPatchCNodes_T++; // for BSpline We need one more(5)
		m_nMaxPatchCNodes	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
    } 
	return 0;
}


int CMI_Patch::LBUpExtrudeInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrPatch 		= Extrude_GetInfo();// PGen Dialog
	if(!m_pDrPatch)		// cancel
		return -1;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrPatch->GetCNodeList();	
	/////// 
	Extrude();							// ControlNode Mesh
	/////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString PatchID	= m_pDrPatch->GetObjectID();
	int nPatchIndex = pDListMgr->GetObjectIndex(PATCH,PatchID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nPatchIndex);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nPatchIndex);
	/////////////////////
	return 0;		 
}

void CMI_Patch::FillCNodesLOCAL(CDListMgr* pCurveCNodeList,
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
    	pDrNode = (CDrNode*)(pCurveCNodeList->GetObject(i));
    	//////////////////////////////////////// Save in Patch
    										  // CNodeList
		if(bSave)
		{
			if(bLoft)
				m_CNListLoft.AddTail(pDrNode);// Temporary
			else
			{
				m_pCNodeList->AddTail(pDrNode);
				/////////////////////////////// Reciprocate 
				pDrNode->GetPatchList()->InsertObject(m_pDrPatch);
			}	
		}		
    	//////////////////////////////////////// NPC Pt.
    	LocalPos = *(pDrNode->GetLocalPos());
    	/////////////////////////////////
		pIn[i].x = LocalPos.x;	  
		pIn[i].y = LocalPos.y;  
		pIn[i].z = LocalPos.z;
		/////////////////////
	}	
}

int CMI_Patch::InsertMeshInfo(BOOL bLoft)
{
	//////////////////////////////////////////////////////
	// For ALL cases other than Mesh, All ControlNodes	//
	// Must be Put in CNodeList of the Patch. However,	//
	//	1.	some of them already created by generating	//
	//		curve such as								//
	//			DUCT & SWEEP: X-Section Curve CNodes	//
	//			EXTRUDE/ROT.: Generating Curve CNodes	//
	//			LOFT        : Start & End Curves'		// 
	//							CNodes					//
	//	2.	Rest or In-Betweens have to generate		// 
	//					DrNodes							//
	//	3.	Inherent in Loft creation, Start/End Curves	//
	//		Already created CNodes get interweaved		//
	//		Need to sort out because we dont want to	//
	//		create what are already posted				//
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,PatchID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int s,t,j;
	///////////////////////////////////////////// Name
	PatchID	= m_pDrPatch->GetObjectID();
	nChLen	= PatchID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (t = 0; t<m_nMaxPatchCNodes_T; t++)
	{
		for (s = 0; s<m_nMaxPatchCNodes_S; s++)
		{
			if(t == 0)		// first s of them already in List
				continue;   // do nothing
			///////////////////////
			if( bLoft && (t == m_nMaxPatchCNodes_T-1) )
			{
				// get Already created saved in TemporaryList
				pAddNode = (CDrNode*)m_CNListLoft.GetObject(s);
				///////////////////////////////////// in PATCH 	
   				m_pCNodeList->InsertObject(pAddNode); //CNodeList
   				//////////////
   				continue;
   			}
   			///////////////////////////////////////// CREATE	
//			Nid		= PatchID.Left(nChLen);
			Nid		= PatchID;
		    //////////////////////////////////// Name
		    sprintf(buf,"%d%d",s,t);
		    Nid += buf; 
			////////////////////////////////////
			j = t*m_nMaxPatchCNodes_S + s;
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
	////////////////////////////////////////// Save Info inPatch
	m_pDrPatch->SetFromPtLocal(m_FromPt);
	m_pDrPatch->SetToPtLocal(m_ToPt);
	m_pDrPatch->SetAxis(m_vAxis);
	////////////////////////////////////////////////////// All Other
	m_pDrPatch->SetPatchType(m_PatchType);
	m_pDrPatch->SetCurveType(m_CurveType);
	m_pDrPatch->SetMaxCNodes_S(m_nMaxPatchCNodes_S);
	m_pDrPatch->SetMaxCNodes_T(m_nMaxPatchCNodes_T);
	///////////////////////////////////////////////////
	m_pDrPatch->SetSegmentCount_S(m_nSegs_S);	
	m_pDrPatch->SetSegmentCount_T(m_nSegs_T); 
	m_pDrPatch->SetClosed_S(m_bClosed_S);
	m_pDrPatch->SetClosed_T(m_bClosed_T);
	m_pDrPatch->SetDirty(TRUE);
	//////////////////////////////////////////////////
	// call to NumberOfCubicPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	m_pDrPatch->SetLongOutPts(m_nOut);	
	m_pDrPatch->SetOut_S(m_nOut_S);	
	m_pDrPatch->SetOut_T(m_nOut_T);
	///////////////////////////////////	
	if(	(m_PatchType == PA_BEZIER) ||		// computes rest
		(m_PatchType == PA_BSPLINE)	)
		m_pDrPatch->NumberOfCubicPatches();
	else
	if	(m_PatchType == PA_LINEAR)
		m_pDrPatch->NumberOfLinearPatches();
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrPatch->Calc_3DBoundsLocal();											
	////////////////
	return 0;
}			

int CMI_Patch::RBUpMeshInsert(enum CURVETYPE kind,CView* pView) 
{

	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrPatch 		= Mesh_GetInfo(2);                  	// PCon Dialog
	if(!m_pDrPatch)		// cancel
		return -1; 
	/////////////////////////////////////////////// Copy ControlNodes (Right Button)
	m_pCNodeList = m_pDrPatch->GetCNodeList();	
	///////////////////////////////////////////////////////////////////// Go Generate	
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrPatch->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	/////////
	return 0;		 
}			
////////////////// Control Node Generation /////////////////
int CMI_Patch::CurveNodesSaveAsCNodes(CDListMgr* pListTemp,int tIndex)
{
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,PatchID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int s,t,j,index;
	//////////////////////////////////// Name
	PatchID	= m_pDrPatch->GetObjectID();
	nChLen	= PatchID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	//////////////////////////////
	t = tIndex;
	///////////	
	for (s = 0; s<m_nOut_S; s++)
	{
		///////////////////////////////////////// CREATE	
		Nid	= PatchID.Left(nChLen);
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		//////////////////////////////////// Node Index in m_pOut
		index = s;
		LocalPos = *(m_pOut+index);
		////////
		pAddNode = PostNode(Nid,LocalPos,TRUE); 	//CNodes = TRUE
		pListTemp->InsertObject(pAddNode);
	}
	return 0;		
}

int CMI_Patch::Gen_Curve(CDrCurve* pDrCurve,pWORLD pIn,pWORLD pOut,int nOut)
{		

	///////////////////////////////////////////////////////
	int nMaxCNodes		  	= pDrCurve->GetMaxCNodes_S();
	int nSegs				= pDrCurve->GetSegmentCount_S();
	BOOL bClosed			= pDrCurve->IsClosed_S();
	CURVETYPE CurveType		= pDrCurve->GetCurveType();	
/* todo 		
	int nMaxCurves			= pDrCurve->GetMaxCubicCurves();
	int	nMaxOutSeg			=		// Number of Output Segments on ENTIRE Curve
	int				Num_t[]			// Number of Outputs for each Output Segment
	double			Dis_t[]			// Output t-distribution array:
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// generate Curve Pts
	int nOutActual	= pDrCurve->GeneratePointsforCurves
			(
							enum CURVEOUTPUT	O_kind		// Output Method
						,	enum CURVETYPE	kind
						,	int				nC				// number of CONTROL points
						,	pWORLD			pInC            // Total CONTROL Points Array
						,	int 			nMaxOutSeg		// Number of Output Segments on ENTIRE Curve
						,	int				Num_t[]			// Number of Outputs for each Output Segment
						,	double			Dis_t[]			// Output t-distribution array:
						,	pWORLD			pOut            // Total Output Points Array
						,	int				nCurves			// Total Number of Cubic Curves 
						,	int				nOut			// expected number of generated curve vertices
				CO_HORNER,
				CurveType,	//	cubic basis function selection
				nMaxCNodes,	//	number of input control points				
				nMaxCurves,	//	number of Cubic Curves                      
				pIn,		//	array of control vertices
				pOut,		//	Matrix of Output 3D LocalPos Points
				nOut		//	number of generated Patch vertices in V dir	
			); 
			
	////////////////////////////	
	if(nOutActual != nOut)
	{
		AfxMessageBox("Internal Problem:MI_Patch:Gen_Curve");
		return -1;
	}
*/		
	////////////
	return -1; // should be changed to 0   todo
	///////
}	

//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void CMI_Patch::UnitAxisFromEndNodes(int nType)
{
	//////////////////////////////////////////////////////////////
	// nType = 0, do it all the way(Axis):Rotate/Extrude
	//       = 1, just compute LocalPos of m_FromID
	//			  (For Sweep/Duct Anchor Node)
	//////////////////////////////////////////////////////////////

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
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
		AfxMessageBox("Bug:GN_PATCH-UnitAxisFromEndNodes");	
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
int CMI_Patch::LBUpPatchPost()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrPatch 		= Post_GetInfo();// PGen Dialog
	if(!m_pDrPatch)		// cancel
		return -1;
	//////////////////////////////////	
	PostNodes_FWD();							// ControlNode Mesh
	/////////////////
	if(PostMeshInfo_FWD()<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString PatchID	= m_pDrPatch->GetObjectID();
	int nPatchIndex = pDListMgr->GetObjectIndex(PATCH,PatchID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nPatchIndex);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nPatchIndex);
	/////////////////////
	return 0;		 
}

int CMI_Patch::PostNodes_FWD()
{
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,PatchID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int s,t,j,index;
	//////////////////////////////////// Name
	PatchID	= m_pDrPatch->GetObjectID();
	nChLen	= PatchID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	//////////////////////////////	
	for (t = 0; t<m_nOut_T; t++)
	{
		for (s = 0; s<m_nOut_S; s++)
		{
   			///////////////////////////////////////// CREATE	
//			Nid	= PatchID.Left(nChLen);
			Nid	= PatchID;
		    //////////////////////////////////// Name
		    sprintf(buf,"%d%d",s,t);
		    Nid += buf; 
			//////////////////////////////////// Node Index in m_pOut
			index = t*m_nOut_S + s;
			LocalPos = *(m_pOut+index);
			////////
			pAddNode = PostNode(Nid,LocalPos,FALSE);
			m_pNodeList->InsertObject(pAddNode);
			//////////////////////////////////////// Reciprocate
			pAddNode->GetPatchList()->InsertObject(m_pDrPatch);
			////////
		}
	}
	return 0;		
}

int CMI_Patch::PostMeshInfo_FWD()
{
	//////////////////////////////////////////////////////
/*	
		int			wrap,	// 0 don't attach last to first, 1 do				/
		int			orient,	// -1 anti-clockwise, 0 both, 1 clockwise			/
		int			nS,		// Number of Splines								/
		int			nV,		// Total number of Nodes							/
		pWORLD		pPt,	// NodeCoord array pPt[nV]								/
		pRENDINFO	pRA,	// Rendition Info
		pMatrix		pLM		// Local Matrix 
*/		
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		PolyID,PatchID;
	int			nChLen,nMax_T,ix[4];
	char		buf[10];
    CDrNode* 	pAddNode;
    CDrPlat*	pAddPoly;
	int 		s,t,j,index;
	//////////////////////////////////// SubDivision
	ValidateSubDiv();
	//////////////////////////////////// Name
	PatchID	= m_pDrPatch->GetObjectID();
	nChLen	= PatchID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
//	nMax_T = m_nOut_T - 1;
//	if(m_bClosed_T)
//		nMax_T++;
	//////////////////////////////	
//	for (t = 0; t<nMax_T; t++)
	for (t = 0; t<(m_nOut_T-1); t++)
	{
		for (s = 0; s<(m_nOut_S-1); s++)
		{
   			///////////////////////////////////////// CREATE	
			PolyID		= PatchID.Left(nChLen);
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
					///////////////////////////////////////////////
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
					///////////////////////////////////////////////
				}	
				else
					SubDivide_FWD(PolyID,ix[3],ix[2],ix[1],ix[0]);
			}
			//////////////////////////////////////////////
		}				
	}
/////////////////////////////////////////// 
#ifdef _DEBUG
	
	CString Pid;
	CDListMgr* pList = m_pElemList;
	int ntemp = pList->GetCount();
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPlat* pPlat 	= (CDrPlat*)pList->GetNextObject(pos);
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
			CDrPlat* pPlat 	= (CDrPlat*)pElemList->GetNextObject(posE);
			/////////////////////////////////////////// ObjectInfo
			Pid = pPlat->GetObjectID();
			//////////////////////////////////
		}	
	}
#endif	
	////////////////
	return 0;
}			

void CMI_Patch::CalcCentroid(pWORLD pC,UINT ix0,UINT ix1,UINT ix2,UINT ix3)
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

int CMI_Patch::SubDivide_FWD(CString& PolyID,UINT ix0,UINT ix1,UINT ix2,UINT ix3)
{ 
	C3DMath Math3D;
	///////////////
	CDrNode* pNode;
	CDrPlat* pAddElem;
	char	buf[10];
	UINT	cIx;
	WORLD	wx0,wx1,wx2,wx3,a,b,v0,v1;
	double	d,d1,d2;
	int		nCount;
    ///////////////////
	switch( m_nSubDiv ) 
	{
	
		case SU_ONCE:								// Triangulation by SHORTEST DIAGONAL
		    
		    //////////////////////////////////////
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix0);
			wx0 	= *(pNode->GetLocalPos());
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix1);
			wx1 	= *(pNode->GetLocalPos());
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix2);
			wx2 	= *(pNode->GetLocalPos());
			pNode 	= (CDrNode*)m_pNodeList->GetObject(ix3);
			wx3 	= *(pNode->GetLocalPos());
			///////////////////////////////////////////////////
			Math3D.Sub3DPts(&wx0,&wx2,&a); 	// diagonal02
			Math3D.Sub3DPts(&wx1,&wx3,&b); 	// diagonal13
			d1 = a.x*a.x + a.y*a.y + a.z*a.z; //length sq. 02  
			d2 = b.x*b.x + b.y*b.y + b.z*b.z; //length sq. 13
			if(d1<d2)
			{ 
				pAddElem = MakePoly_3(PolyID,ix0,ix1,ix2);
				m_pElemList->InsertObject(pAddElem); //ElemList	012
				pAddElem = MakePoly_3(PolyID,ix0,ix2,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList	023
			}
			else	
			{ 
				pAddElem = MakePoly_3(PolyID,ix0,ix1,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList	013		
				pAddElem = MakePoly_3(PolyID,ix1,ix2,ix3);
				m_pElemList->InsertObject(pAddElem); //ElemList	123
			}
			////////////////////////
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

void CMI_Patch::ValidateSubDiv(void)
{
	switch( m_nSubDiv ) 
	{
		case SU_NOSUB:
		case SU_ONCE:
		case SU_TWICE:
		case SU_AUTO:
			break;
		default:
			m_nSubDiv = SU_NOSUB;          // Quad
	}
}

CDrNode* CMI_Patch::PostNode(CString& Nid,WORLD Pt,BOOL bCNode)
{

	CMPatMgr 	MPatMgr;
	CMPatMgr* 	pMPatMgr = &MPatMgr;
	CDrNode*	pNode;
	/////////////////////////////////////////////
	pNode = pMPatMgr->CreateNode(Nid,Pt,bCNode);
	//////////////////////////////////////////////
	return pNode;
}			

CDrPlat* CMI_Patch::MakePoly_3(CString& PolyID,int ix0,int ix1,int ix2)
{
    CNewObjs*	pNewObjs;
    /////////////////////
	int ix[3];
	////////////
	ix[0] = ix0;
	ix[1] = ix1;
	ix[2] = ix2;
//	ix[3] = ix2;
	//////////////////////////////////////////////////// Create
	CDrPlat* pPoly = (CDrPlat*)pNewObjs->NewObject(PLATE);
	pPoly->SetObjectID(PolyID);
	/////////////////////////////////////////////////
	PostPoly(pPoly,ix,3);
	///////////////////////
	return pPoly;
}
	
CDrPlat* CMI_Patch::MakePoly_4(CString& PolyID,int ix0,int ix1,int ix2,int ix3)
{
	CNewObjs*	pNewObjs;
	/////////////////////
	int ix[4];
	////////////
	ix[0] = ix0;
	ix[1] = ix1;
	ix[2] = ix2;
	ix[3] = ix3;
	int			i,temp;
	//////////////////////////////////// guard against CUSP:rotate index
	WORLD LPos[4];
    for(i=0;i<4;i++)
    {
		CDrNode* pNode = (CDrNode*)m_pNodeList->GetObject(ix[i]);
		LPos[i] = *(pNode->GetLocalPos());
	}
	////////////////////
	if( wEQL(LPos[0],LPos[1]) )
	{
		temp	= ix[0];
		ix[0] 	= ix[1];
		ix[1]	= ix[2];
		ix[2] 	= ix[3];
		ix[3] 	= temp;
	}	
	if( wEQL(LPos[1],LPos[2]) )
	{
		temp	= ix[0];
		ix[0] 	= ix[2];
		ix[2] 	= temp;
		temp	= ix[1];
		ix[1] 	= ix[3];
		ix[3] 	= temp;
	}				
	//////////////////////////////////////////////////// Create
	CDrPlat* pPoly = (CDrPlat*)pNewObjs->NewObject(PLATE);
	pPoly->SetObjectID(PolyID);
	/////////////////////
	PostPoly(pPoly,ix,4);
	/////////////////////
	return pPoly;
}
	
CDrNode* CMI_Patch::PostPoly(CDrPlat* pPoly,int* index,int nEnds)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Plat
	CMPatMgr* 	pMPatMgr;
	CDrNode*	pNode;
	int			i,temp;
/*	
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
*/
	/////////////////////////////////////////////////////  
    for(i=0;i<nEnds;i++)
    {
		CDrNode* pDrNode = (CDrNode*)m_pNodeList->GetObject(index[i]);
		pPoly->GetNodeList()->InsertObject(pDrNode);
		//////////////////////////////// save Current Plate Pointer in Nodes
		pDrNode->GetElemList()->InsertObject(pPoly);
	
  	}	
	//////////////////////////////////////////////
	pPoly->SetObjectType((int)PLATE);
	pPoly->SetElemType((int)EL3D_OBJECT);  			// globals.h
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
//	m_PlateType = "AxiSym";
	(pPoly->GetPlatCard())->nSAPNum		= 4;   // temporarily//3=Membrane; 4=2D FEM
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

CDrPatch* CMI_Patch::Post_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CMPatMgr* 	pMPatMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
//todo		if (pMPatMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
	if (pMPatMgr->DoModal_Patch_Post(&Cid) == IDCANCEL)
			return (CDrPatch*)NULL;
/*
    /////////////////////////////////////////////////////// update
	m_CurrentPatchID 	= Cid;
*/	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{						
		CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
   		//////////////////////////////
   		m_nSubDiv	= pDrPatch->GetSubDiv();
		m_bClosed_T	= pDrPatch->IsClosed_T();	// 0 don't attach last to first, 1 do				/
		m_nOrient	= pDrPatch->GetOrient();	// -1 anti-clockwise, 0 both, 1 clockwise			/
		m_nOut_T	= pDrPatch->GetOut_T();		// Number of Splines= Nodes in T								/
		m_nOut_S	= pDrPatch->GetOut_S();		// Total number of Nodes in S							/
		m_nOut		= pDrPatch->GetLongOutPts();// Total number of Nodes
		/////////////////////////////////////////////////////////////////
		////////////////////////////////////////// Need to generate Patch
												// using Local CNodes
		pDrPatch->RefillCNLocalPosForPosting();	// for Posting
		pDrPatch->Generate_Patch();
		//////////////////////////////////////////		
		m_pOut		= pDrPatch->GetMemOut();	// NodeCoord array 				todo -  Use local FixMem
//		m_pRA		= pDrPatch->GetRInfo(),		// Rendition Info
//		m_pLM		= pDrPatch->GetLocalTransform(pMATRIX xF)// Local Matrix
		m_pNodeList	= pDrPatch->GetNodeList(); 
		m_pElemList	= pDrPatch->GetElemList(); 
		////////////////
		return pDrPatch;
	}
	else
		return (CDrPatch*)NULL;
}			
////////////////////////////////////////////////////////////
void CMI_Patch::Serialize(CArchive& ar)
{

	CMI_Curve::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MI_PATCH:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" MI_PATCH:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


