// Mouse.cpp : implementation file
//


#include "stdafx.h" 


#include "CalcTime.h"
 
#include "MsMath.h" 
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "drgrafrm.h"
/////////////////////
#include "ObjMgr.h"
#include "HitNet.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "DrEdge.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
/////////////////////
#include "Po_Qu_4.h"
#include "Po_Qu_8.h"
#include "Po_Qu_9.h"
#include "Po_Qu_12.h"
#include "Po_Qu_16.h"
/////////////////////
#include "MI_GangN.h"
#include "MI_GangC.h"
#include "MI_GangP.h"
#include "MI_Gang0.h" 
/////////////////////
#include "MI_Qang2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Qang2,CMI_Gang2,1)
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////////////////////////////////////////////
CMI_Qang2::CMI_Qang2()
{
}

CMI_Qang2::~CMI_Qang2()
{
}
//////////////////////////////////////////////////////////////////////////// Poting Helper
int CMI_Qang2::Post_PatchNodes_IorC_4(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode)		
{
	int nResult = Post_PatchNodes_IorC(pPatch, pOut, nOut, bCNode);
	///////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_PatchNodes_IorC_4");
		return -1;
	}
	/////////
	return 0;
}

int CMI_Qang2::Post_PatchCurves_4(CDrPatch* pPatch, pWORLD pOut, pDOUBLE pOutWts, int nOut)		
{
//	todo later
	/////////
	return -1;
}

int CMI_Qang2::Post_PatchNodes_FE0D_4(CDrObject* pMesh,UINT nGenType,pWORLD pOut,int nOut_S,int nOut_T,
							BOOL bCNode,BOOL bMNode,BOOL bAnyWay,BOOL bReverseST)		
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////// Now Post
	char	buf[50];
	int		nLastNum;
	////////////////////////////////
	int		s,t,j,nMax_S,nMax_T;
	WORLD	LocalPos;
	//////////////////////////////////// bReverseST: for Shorter Length First NodeNumbering
	nMax_S = bReverseST ? nOut_T:nOut_S;
	nMax_T = bReverseST ? nOut_S:nOut_T;
	////////////////////////////////////
	for (t = 0; t<nMax_T; t++)
	{
		for (s = 0; s<nMax_S; s++)
		{
			if(bMNode)
			{
				pMsObjMgr->BumpLastMeshNo(MNODE);		// bump it
				nLastNum = pMsObjMgr->GetLastMeshNo(MNODE);		// internal
			}
			else
			{
				pMsObjMgr->BumpLastMeshNo(FE0D);		// bump it
				nLastNum = pMsObjMgr->GetLastMeshNo(FE0D);		// internal
			}
			sprintf(buf,"%d",nLastNum);
			//////////////////////////////////// Name
			CString Nid = "";
			Nid += buf; 
			////////////////////////////////////
			j = bReverseST ? s*nMax_T + t : t*nMax_S + s;
			////////////////////////////		
			LocalPos.x	= (pOut+j)->x;
			LocalPos.y	= (pOut+j)->y;
			LocalPos.z	= (pOut+j)->z;
			///////////////////////////////////// MNode or Vertex:Public and Yes reciprocation
			CDrLabel*	pLabel;
			int			nNodeIndex,nLabelIndex;
			/////////////////////////////////// if bAnyWay
			if(bAnyWay)
				nNodeIndex = -12345;
			///////////////////////////////////
			CMI_Gang0 Gang0;
			CDrFE0D* pAddNode = Gang0.CreateFE0D(Nid,pLabel,LocalPos,bCNode,TRUE,bMNode,
									nNodeIndex,nLabelIndex);	// Create 
//		CDrFE0D* pAddNode = Gang0.PostFE0D(Nid,LocalPos,bCNode,bMNode);	// Create 
			///
			if(!pAddNode)	// 
				return -1;
			//////////////
			pAddNode->SetCategory(CA_ELEMENT);
			///////////////////////////////////////////////////////////////////////
			pMesh->GetFE0DList()->InsertObject(pAddNode);		//MNodeList 
//		pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
			//////////////////////////////////////// Reciprocate
//			pAddNode->SetGenObj(pMesh);
//			pAddNode->SetGenObjType(nGenType);
		int nResult = ReciprocateElemMeshList(pAddNode, pMesh, nGenType);
		if(nResult <0)
			return nResult;
			//////////////////////////////////////// Now Ready
			pAddNode->SetShow(TRUE);
		}
	}
	/////////
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////// EDGEs
int CMI_Qang2::Post_PatchEdges_FE1D_4(CDrMesh2D* pMesh)		
{
	//		THIS ROUTINE IS NOT NECESSARY : 10/04/97
	/////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	//			FILLS:		pMesh->EdgeList()
	//			DEFINES:	Positive Direction of Edges
	////////////////////////////////////////////////////
	BOOL bSwitch		= pMesh->IsReversed_ST();
	CDrPatch* pDrPatch	= pMesh->GetGenObj();
	///
	int nOut_S		= (int)pDrPatch->GetOut_S();
	int nOut_T		= (int)pDrPatch->GetOut_T();
	////////////////////////////////
	int		s,t,nMax_S,nMax_T;
	int		ni,nj;
	///////////////////////////////////////// Shorter Length First NodeNumbering
	nMax_S	= (bSwitch) ? nOut_T:nOut_S;
	nMax_T	= (bSwitch) ? nOut_S:nOut_T;
	//////////////////////////////////////////////////////////////////////////////// SorT-direction
	for (t = 0; t<nMax_T; t++)
	{
		for (s = 0; s<nMax_S-1; s++)
		{
			////////////////////////////////////
			ni = t*nMax_S + s; 
			nj = (bSwitch) ? ni + nMax_S : ni + 1;
			///////////////////////////////////////////////////////////// Fill Edge info
//			Save_EdgeInfo(pMesh,MESH2D,ni,nj,s,1);	// along s-dir	
			/////////////////////////
		}
	}
	//////////////////////////////////////////////////////////////////////////////// TorS-direction
	for (s = 0; s<nMax_S; s++)
	{
		for (t = 0; t<nMax_T-1; t++)
		{
			////////////////////////////////////
			ni = t*nMax_S + s;  
			nj = (bSwitch) ? ni + 1 : ni + nMax_S;
			///////////////////////////////////////////////////////////// Fill Edge info
//			Save_EdgeInfo(pMesh,MESH2D,ni,nj,t,2);	// along t-dir	
			/////////////////////////
		}
	}
	/////////
	return 0;
}

/*
int CMI_Qang2::Post_FE1D(CDrFE1D* pAddEdge,CDrObject* pMesh,int* Index,CString& Eid)		
{
	//////////////////////////////////////
	// NEEDED for : Beam/Pipe/Truss/Elbow
	//////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	POSITION	Pos;
	CDrFE0D*	pVert[2];
	///////////////////////////////////////////////////////////////////////////// Vertices
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh Vertex Pool
	if(pListV->IsEmpty())
		return -1;
	///////////////////////////////////////////////
	for(int i=0;i<2;i++)
	{
		Pos			= pListV->FindIndex(Index[i]);
		pVert[i]	= (CDrFE0D*)pListV->GetAt(Pos);
	}
	/////////////////////////////////////////////// 
	WORLD LocalPos[2];
	GetLocalPos_Vertices(LocalPos,pVert,2);
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	Make_CentroidLabel_EDGE(pAddEdge,LocalPos,Eid);
	///////////////////////////////////////////////////////////////////////////// Reciprocate/Info
	SetFE1DInfo(pAddEdge,pVert,pMesh);
	//////////////////////////////////////// Now Ready
	pAddEdge->SetShow(TRUE);
	/////////
	return 0;
}
*/
/////////////////////////////////////////////////////////////////////////////////////////// FE2D
int CMI_Qang2::Post_Patch_QUADRILATS(CDrObject* pMesh,CDrObject* pDrPatch,UINT nGenType,UINT nElemType)		
{
#ifdef _DEBUG
	CCalcTime	CalcTime;
#endif
	////////////////////////////////////////////////////////////////////////////////
	//				nElemType = Qu_4,Qu_8,Qu_9,Qu_10,Qu_12,Qu_16
	//			if NonPlanar:	Tr_3,Tr_6,Tr_9,Tr_10
	//////////////////////////////////////////////////////////////////////////////// Doit
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh Vertex Pool
	if(pListV->IsEmpty())
		return -1;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////// 
	int nResult;
	//////////////////////////////////////////// Mesh Info
	ORIENT		Orient	= ((CDrMesh2D*)pMesh)->GetOrient();
	REF_QUAD	RefQuad	= ((CDrMesh2D*)pMesh)->GetRefQuad();
	//////////////////////////////////////////// Output memory
	int nOut_S		= (int)((CDrPatch*)pDrPatch)->GetOut_S();
	int nOut_T		= (int)((CDrPatch*)pDrPatch)->GetOut_T();
	////////////////////////////////
	int		s,t,nMax_S,nMax_T;
	int		nIndex,ix[4],ntemp;
	///////////////////////////////////////// Shorter Length First NodeNumbering
	BOOL bSwitch;
	bSwitch	= (nOut_T<nOut_S) ? TRUE:FALSE;
	nMax_S	= (bSwitch) ? nOut_T:nOut_S;
	nMax_T	= (bSwitch) ? nOut_S:nOut_T;
	//////////////////////////////////////////////////////////////////////////////// Loop
#ifdef _DEBUG
	//////////////////////////////////////// time it
	CString str;
	sprintf(str.GetBuffer(150),"CMI_Qang2::Post_Patch_QUADRILATS\n");
	CalcTime.OutComment(str);
	str.ReleaseBuffer();
	///
#endif
	for (t = 0; t<nMax_T-1; t++)
	{
		for (s = 0; s<nMax_S-1; s++)
		{
			//////////////////////////////////// FE0D Index in FE0DList
			nIndex = t*nMax_S + s;
			///////////////////////
			//	ANTICLOCK if bSwitch = FALSE; CLOCKWISE if bSwitch = TRUE;
			ix[0] = nIndex;
			ix[1] = ix[0] + 1;
			ix[3] = ix[0] + nMax_S;
			ix[2] = ix[3] + 1;
			//////////////////////////////////// Orient
			if
			( 
				( (Orient == OT_CLOCKWISE) && !bSwitch) ||
				( (Orient == OT_ANTICLOCK) && bSwitch) 
			)
			{
				ntemp	= ix[1];
				ix[1]	= ix[3];
				ix[3]	= ntemp;
			}
/*
#ifdef _DEBUG
	//////////////////////////////////////// time it
	CalcTime.StartClock();
	//////////////////////
#endif
*/
			///////////////////////////////////////////////////////////// Vertex Info
			CDrFE0D*	pVert[4];
			WORLD		LocalPos[4];
			/////////////////////////////////////////
			GetVertexInfo(pListV,ix,pVert,LocalPos,4);
			///////////////////////////////////////// Guard against Cusp,if needed
			RotateFaceNodeIndices(LocalPos,ix);
/*
#ifdef _DEBUG
		/////////////////////
		CalcTime.StopClock();
		CString str;
		sprintf(str.GetBuffer(150),"s = %d  t = %d Vertex Info.",s,t);
		CalcTime.OutDuration(str);
		////////////////////
		str.ReleaseBuffer();
#endif
*/
			///////////////////////////////////////////////////////////// Go Do it
#ifdef _DEBUG
	//////////////////////////////////////// time it
	CalcTime.StartClock();
	////////////////////////
#endif
			switch(RefQuad)
			{
				case RQ_NOREF:			// leave alone						1 Quad 

					nResult = Post_FE2D_4_NOREF((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
					///////
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				case RQ_AUTO:			// RQ_SHORTDIAG iff NonCoPlanar		1 Quad or 2 Tri

					nResult = Post_FE2D_4_AUTO((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
					///////
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				case RQ_SHORTDIAG:		// shorter Diag						2 Tri

					nResult = Post_FE2D_4_SHORTDIAG((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
					///////
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				case RQ_INTERSECT:		// IntersectionDiag					4 Tri

					nResult = Post_FE2D_4_INTERSECT((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
					///////
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				case RQ_CENTROID:		// Centroid							4 Tri

					nResult = Post_FE2D_4_CENTROID((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
					///////
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				case RQ_MIDCENSHORT:	// MidPtCentroidShortDiag			8 Tri

//					nResult = Post_FE2D_4_MIDCENSHORT((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
//					///////
					nResult = -1;	// temporary
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
						return -1;
					}
					break;

				default:
					return -1;
			}
			//////////////////////////////////////////////
#ifdef _DEBUG
		/////////////////////
		CalcTime.StopClock();
		sprintf(str.GetBuffer(150),"s = %d  t = %d Element Info.",s,t);
		CalcTime.OutDuration(str);
		///
		str.ReleaseBuffer();
		///
#endif
		}				
	}
	/////////
	return 0;
}

int CMI_Qang2::Post_FE2D_4_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by Leave Alone QUAD
	////////////////////////////////////////////////////////////////////////
	int	nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		///////////////////////////////////////////////////////// 1D
		case TRUSS:				// fall thro'
		case BEAM:				// 
		case PIPE:				//
		case ELBOW:				// 
		///////////////////////////////////////////////////////// 2D
		case TR_3:	// will be ignored for Coplanar	
		case QU_4:	
			nResult = Post_QU_4(pMesh,nGenType,pVert,LocalPos);
			break;

//		case TR_6:	// will be ignored for Coplanar		
		case QU_8:	
			nResult = Post_QU_8(pMesh,nGenType,pVert,LocalPos);
			break;

		case TR_6:	// will be ignored for Coplanar		
		case QU_9:	
			nResult = Post_QU_9(pMesh,nGenType,pVert,LocalPos);	
			break;

		case TR_9:	// will be ignored for Coplanar		
		case QU_12:	
			nResult = Post_QU_12(pMesh,nGenType,pVert,LocalPos);	
			break;

		case TR_10:	// will be ignored for Coplanar		
		case QU_16:	
			nResult = Post_QU_16(pMesh,nGenType,pVert,LocalPos);	
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

int CMI_Qang2::Post_FE2D_4_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	CMsMath	MsMath;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	int nResult = MsMath.IsCoPlanar(&LocalPos[0],&LocalPos[1],&LocalPos[2],&LocalPos[3],
						  &m_Normal_ABC,&m_D,pHitNet->GetCoLinear());
	if(nResult == -1)
		return -1;	// error
	///////////////////////////////////////////////////////// Coplanar (Leave Alone)
	if(nResult == 1) // TRUE
	{
		nResult = Post_FE2D_4_NOREF((CDrObject*)pMesh,nGenType,pVert,LocalPos,nElemType);
		///////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
			return -1;
		}
		return 0;
	}
	///////////////////////////////////////////////////////// NonCoplanar (Shorter Diag)
	if(nResult == 0) // FALSE
	{
		nResult = Post_FE2D_4_SHORTDIAG((CDrObject*)pMesh,nGenType,pVert,LocalPos,nElemType);
		///////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
			return -1;
		}
		return 0;
	}
	//////////
	return -1;
}

BOOL CMI_Qang2::IsD1ShorterThanD2(pWORLD LocalPos)
{
	//		D1 = (V0,V2) and D2 = (V1,V3) 
	////////////////////////////////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD	wx0,wx1,wx2,wx3,a,b;
	double	d1,d2;
    ///////////////////
	wx0 	= LocalPos[0];
	wx1 	= LocalPos[1];
	wx2 	= LocalPos[2];
	wx3 	= LocalPos[3];
	/////////////////////////////////////////////////////////
	Math3D.Sub3DPts(&wx0,&wx2,&a); 	// diagonal02
	Math3D.Sub3DPts(&wx1,&wx3,&b); 	// diagonal13
	//////
	d1 = a.x*a.x + a.y*a.y + a.z*a.z; //length sq. 02  
	d2 = b.x*b.x + b.y*b.y + b.z*b.z; //length sq. 13
	/////////
	if(d1<=d2)
		return TRUE;
	else
		return FALSE;
	///////
}

int CMI_Qang2::PreProcess_SHORTDIAG
(
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert31[],pWORLD LocalPos31,
					CDrFE0D* pVert32[],pWORLD LocalPos32
)
{
	//		D1 = (V0,V2) and D2 = (V1,V3) 
    ///////////////////
	if(IsD1ShorterThanD2(LocalPos) )
	{
		//////////////////////////////////////////////////////// Set LocalPos & Vertices
		////////////////////////////////// Ist Triangle (0,1,2)
		for(int i = 0;i<3;i++)
		{
			LocalPos31[i]	= LocalPos[i];
			pVert31[i]		= pVert[i];
			/////////////////////////////
		}
		////////////////////////////////// 2nd Triangle (0,2,3)
		LocalPos32[0]	= LocalPos[0];
		pVert32[0]		= pVert[0];
		LocalPos32[1]	= LocalPos[2];
		pVert32[1]		= pVert[2];
		LocalPos32[2]	= LocalPos[3];
		pVert32[2]		= pVert[3];
		//////////
	}
	else
	{
		//////////////////////////////////////////////////////// Set LocalPos & Vertices
		////////////////////////////////// Ist Triangle (1,2,3)
		for(int i = 0;i<3;i++)
		{
			LocalPos31[i]	= LocalPos[i+1];
			pVert31[i]		= pVert[i+1];
			/////////////////////////////
		}
		////////////////////////////////// 2nd Triangle (0,1,3)
		LocalPos32[0]	= LocalPos[0];
		pVert32[0]		= pVert[0];
		LocalPos32[1]	= LocalPos[1];
		pVert32[1]		= pVert[1];
		LocalPos32[2]	= LocalPos[3];
		pVert32[2]		= pVert[3];
		//////////
	}
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE2D_4_SHORTDIAG(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by SHORTEST DIAGONAL
	////////////////////////////////////////////////////////////////////////
	CDrFE0D*	pVert31[3];
	CDrFE0D*	pVert32[3];
	WORLD		LocalPos31[3],LocalPos32[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	PreProcess_SHORTDIAG(pVert,LocalPos,pVert31,LocalPos31,pVert32,LocalPos32);
	//////////////////////////////////////////////////////////////////////
	int			nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TR_3:	
		case QU_4:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_3(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_3(pMesh,nGenType,pVert32,LocalPos32);
			break;

		case TR_6:	
		case QU_8:	// here due to AUTO (NonCoplanar)	
		case QU_9:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_6(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_6(pMesh,nGenType,pVert32,LocalPos32);
			break;

		case TR_9:	
		case QU_12:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_9(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_9(pMesh,nGenType,pVert32,LocalPos32);
			break;

		case TR_10:	
		case QU_16:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

CDrFE0D* CMI_Qang2::CreateIntersectionNode(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,WORLD& LocalPos_In)
{
	CMsMath MathMs;
	///////////////////////////////////////////////////////// Intersection ?
	if(!MathMs.IsIntersect_LINE_LINE(LocalPos,LocalPos_In) )
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::CreateIntersectNode\nNO INTERSECTION");
		return (CDrFE0D*)NULL;
	}
	///////////////////////////////////////////////////////// create node
	return CreateMNode(pMesh,nGenType,LocalPos_In);
	//////
}

int CMI_Qang2::PreProcess_INTERSECT
(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert31[],pWORLD LocalPos31,
					CDrFE0D* pVert32[],pWORLD LocalPos32,
					CDrFE0D* pVert33[],pWORLD LocalPos33,
					CDrFE0D* pVert34[],pWORLD LocalPos34
)
{
	CDrFE0D*	pVert_In;
	WORLD		LocalPos_In;		
	//////////////////////////////////////////////////////// Create LocalPos & Vertices:Intersection
	pVert_In = CreateIntersectionNode(pMesh,nGenType,LocalPos,LocalPos_In);
	if(!pVert_In)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::PreProcess_INTERSECT:\npVert_IN == NULL");
		return -1;
	}
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	////////////////////////////////// Ist Triangle (intersection,0,1)
	LocalPos31[0]	= LocalPos_In;
	pVert31[0]		= pVert_In;
	LocalPos31[1]	= LocalPos[0];
	pVert31[1]		= pVert[0];
	LocalPos31[2]	= LocalPos[1];
	pVert31[2]		= pVert[1];
	////////////////////////////////// 2nd Triangle (intersection,1,2)
	LocalPos32[0]	= LocalPos_In;
	pVert32[0]		= pVert_In;
	LocalPos32[1]	= LocalPos[1];
	pVert32[1]		= pVert[1];
	LocalPos32[2]	= LocalPos[2];
	pVert32[2]		= pVert[2];
	////////////////////////////////// 3rd Triangle (intersection,2,3)
	LocalPos33[0]	= LocalPos_In;
	pVert33[0]		= pVert_In;
	LocalPos33[1]	= LocalPos[2];
	pVert33[1]		= pVert[2];
	LocalPos33[2]	= LocalPos[3];
	pVert33[2]		= pVert[3];
	////////////////////////////////// 4th Triangle (intersection,3,0)
	LocalPos34[0]	= LocalPos_In;
	pVert34[0]		= pVert_In;
	LocalPos34[1]	= LocalPos[3];
	pVert34[1]		= pVert[3];
	LocalPos34[2]	= LocalPos[0];
	pVert34[2]		= pVert[0];
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE2D_4_INTERSECT(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by INTERSECTING DIAGONAL
	////////////////////////////////////////////////////////////////////////
	CDrFE0D*	pVert31[3];
	CDrFE0D*	pVert32[3];
	CDrFE0D*	pVert33[3];
	CDrFE0D*	pVert34[3];
	WORLD		LocalPos31[3],LocalPos32[3],LocalPos33[3],LocalPos34[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	int			nResult;
	////////////////////
	nResult = PreProcess_INTERSECT(pMesh,nGenType,pVert,LocalPos,
						pVert31,LocalPos31,pVert32,LocalPos32,
						pVert33,LocalPos33,pVert34,LocalPos34);
	if(nResult<0)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::Post_FE2D_4_INTERSECT:\nPreProcess_INTERSECT");
		return -1;
	}
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TR_3:	
		case QU_4:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_3(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_3(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_3(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_3(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_6:	
		case QU_8:	// here due to AUTO (NonCoplanar)	
		case QU_9:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_6(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_6(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_6(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_6(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_9:	
			nResult = Post_TR_9(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_9(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_9(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_9(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_10:	
		case QU_12:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_10(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_10(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case QU_16:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_10(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_10(pMesh,nGenType,pVert34,LocalPos34);
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

CDrFE0D* CMI_Qang2::CreateCentroidNode_4(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,WORLD& LocalPos_In)
{
	///////////////////////////////////////////////////////// Centroid
	CalcCentroid_FACE_4(LocalPos,&LocalPos_In);
	///////////////////////////////////////////////////////// create node
	return CreateMNode(pMesh,nGenType,LocalPos_In);
	//////
}

int CMI_Qang2::PreProcess_CENTROID_4
(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert31[],pWORLD LocalPos31,
					CDrFE0D* pVert32[],pWORLD LocalPos32,
					CDrFE0D* pVert33[],pWORLD LocalPos33,
					CDrFE0D* pVert34[],pWORLD LocalPos34
)
{
	CDrFE0D*	pVert_In;
	WORLD		LocalPos_In;		
	//////////////////////////////////////////////////////// Create LocalPos & Vertices:Intersection
	pVert_In = CreateCentroidNode_4(pMesh,nGenType,LocalPos,LocalPos_In);
	if(!pVert_In)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::PreProcess_CENTROID_4:\npVert_IN == NULL");
		return -1;
	}
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	////////////////////////////////// Ist Triangle (intersection,0,1)
	LocalPos31[0]	= LocalPos_In;
	pVert31[0]		= pVert_In;
	LocalPos31[1]	= LocalPos[0];
	pVert31[1]		= pVert[0];
	LocalPos31[2]	= LocalPos[1];
	pVert31[2]		= pVert[1];
	////////////////////////////////// 2nd Triangle (intersection,1,2)
	LocalPos32[0]	= LocalPos_In;
	pVert32[0]		= pVert_In;
	LocalPos32[1]	= LocalPos[1];
	pVert32[1]		= pVert[1];
	LocalPos32[2]	= LocalPos[2];
	pVert32[2]		= pVert[2];
	////////////////////////////////// 3rd Triangle (intersection,2,3)
	LocalPos33[0]	= LocalPos_In;
	pVert33[0]		= pVert_In;
	LocalPos33[1]	= LocalPos[2];
	pVert33[1]		= pVert[2];
	LocalPos33[2]	= LocalPos[3];
	pVert33[2]		= pVert[3];
	////////////////////////////////// 4th Triangle (intersection,3,0)
	LocalPos34[0]	= LocalPos_In;
	pVert34[0]		= pVert_In;
	LocalPos34[1]	= LocalPos[3];
	pVert34[1]		= pVert[3];
	LocalPos34[2]	= LocalPos[0];
	pVert34[2]		= pVert[0];
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE2D_4_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by CENTROID
	////////////////////////////////////////////////////////////////////////
	CDrFE0D*	pVert31[3];
	CDrFE0D*	pVert32[3];
	CDrFE0D*	pVert33[3];
	CDrFE0D*	pVert34[3];
	WORLD		LocalPos31[3],LocalPos32[3],LocalPos33[3],LocalPos34[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	PreProcess_CENTROID_4(pMesh,nGenType,pVert,LocalPos,
						pVert31,LocalPos31,pVert32,LocalPos32,
						pVert33,LocalPos33,pVert34,LocalPos34);
	//////////////////////////////////////////////////////////////////////
	int			nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TR_3:	
		case QU_4:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_3(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_3(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_3(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_3(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_6:	
		case QU_8:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_6(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_6(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_6(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_6(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_9:	
		case QU_9:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_9(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_9(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_9(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_9(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case TR_10:	
		case QU_12:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_10(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_10(pMesh,nGenType,pVert34,LocalPos34);
			break;

		case QU_16:	// here due to AUTO (NonCoplanar)	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_10(pMesh,nGenType,pVert33,LocalPos33);
			nResult = Post_TR_10(pMesh,nGenType,pVert34,LocalPos34);
			break;

		default:	return -1;
	}
	/////////
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
int CMI_Qang2::Post_QU_4(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_LINEAR;
	////////////////////////////////////////////////////////////////////////
	CPo_Qu_4	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= QU_4;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_QU_4\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Qang2::Post_QU_8(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_QUADRATIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Qu_8	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= QU_8;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_QU_8\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Qang2::Post_QU_9(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_QUADRATIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Qu_9	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= QU_9;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_QU_9\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Qang2::Post_QU_12(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_CUBIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Qu_12	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= QU_12;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_QU_12\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Qang2::Post_QU_16(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_CUBIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Qu_16	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= QU_16;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_QU_16\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int CMI_Qang2::Post_FE1D_4_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by Leave Alone QUAD
	////////////////////////////////////////////////////////////////////////
	int	nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TRUSS:				// fall thro'
			nResult = Post_TRUSS(pMesh,nGenType,pVert,LocalPos,4);	// 4 Trusses
			break;
		case BEAM:				// 
			nResult = Post_BEAM(pMesh,nGenType,pVert,LocalPos,4);	// 4 Beams
			break;
		case PIPE:				//
			nResult = Post_PIPE(pMesh,nGenType,pVert,LocalPos,4);	// 4 Pipes
			break;
		case ELBOW:				// 
			nResult = Post_ELBOW(pMesh,nGenType,pVert,LocalPos,4);	// 4 Elbows
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

int CMI_Qang2::Post_FE1D_4_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType)
{
	CMsMath	MsMath;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	int nResult = MsMath.IsCoPlanar(&LocalPos[0],&LocalPos[1],&LocalPos[2],&LocalPos[3],
						  &m_Normal_ABC,&m_D,pHitNet->GetCoLinear());
	if(nResult == -1)
		return -1;	// error
	///////////////////////////////////////////////////////// Coplanar (Leave Alone)
	if(nResult == 1) // TRUE
	{
		nResult = Post_FE1D_4_NOREF(pMesh,nGenType,pVert,LocalPos,nElemType);
		///////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
			return -1;
		}
		return 0;
	}
	///////////////////////////////////////////////////////// NonCoplanar (Shorter Diag)
	if(nResult == 0) // FALSE
	{
		nResult = Post_FE1D_4_SHORTDIAG(pMesh,nGenType,pVert,LocalPos,nElemType);
		///////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_Patch_QUADRILATS\nRQ_NOREF");
			return -1;
		}
		return 0;
	}
	//////////
	return -1;
}

int CMI_Qang2::PreProcess_SHORTDIAG_FE1D
(
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert5[],pWORLD LocalPos5
)
{
	// 5 Vertices Collected for 5 1D Elems
	//////////////////////////////////////
	//		D1 = (V0,V2) and D2 = (V1,V3) 
    //////////////////////////////////////
	if(IsD1ShorterThanD2(LocalPos) )
	{
		//////////////////////////////////////////////////////// Set LocalPos & Vertices
		// Vertex Order:1,2,3,0,2 so that 1D elems can be 
		// created sequentially as (1,2),(2,3),..(0,2)
		////////////////////////////////////////////////////////
		for(int i = 0;i<4;i++)
		{
			LocalPos5[i]	= LocalPos[(i+1)%4];
			pVert5[i]		= pVert[(i+1)%4];
			/////////////////////////////
		}
		LocalPos5[4]	= LocalPos[2];
		pVert5[4]		= pVert[2];
		//////////
	}
	else
	{
		//////////////////////////////////////////////////////// Set LocalPos & Vertices
		// Vertex Order:0,1,2,3,1 so that 1D elems can be 
		// created sequentially as (0,1),(1,2),..(3,1)
		////////////////////////////////////////////////////////
		for(int i = 0;i<4;i++)
		{
			LocalPos5[i]	= LocalPos[i];
			pVert5[i]		= pVert[i];
			/////////////////////////////
		}
		LocalPos5[4]	= LocalPos[1];
		pVert5[4]		= pVert[1];
		//////////
	}
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE1D_4_SHORTDIAG(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by SHORTEST DIAGONAL
	////////////////////////////////////////////////////////////////////////
	CDrFE0D*	pVert5[5];
	WORLD		LocalPos5[5];
	///////////////////////////////////////////////////////////// Split Triangles Info
	PreProcess_SHORTDIAG_FE1D(pVert,LocalPos,pVert5,LocalPos5);
	//////////////////////////////////////////////////////////////////////
	int			nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TRUSS:				// fall thro'
			nResult = Post_TRUSS(pMesh,nGenType,pVert5,LocalPos5,5);	// 5 Trusses
			break;
		case BEAM:				// 
			nResult = Post_BEAM(pMesh,nGenType,pVert5,LocalPos5,5);	// 5 Beams
			break;
		case PIPE:				//
			nResult = Post_PIPE(pMesh,nGenType,pVert5,LocalPos5,5);	// 5 Pipes
			break;
		case ELBOW:				// 
			nResult = Post_ELBOW(pMesh,nGenType,pVert5,LocalPos5,5);	// 5 Elbows
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

int CMI_Qang2::PreProcess_INTERSECT_FE1D
(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert6[],pWORLD LocalPos6,
					CDrFE0D* pVert3[],pWORLD LocalPos3
)
{
	CDrFE0D*	pVert_In;
	WORLD		LocalPos_In;		
	//////////////////////////////////////////////////////// Create LocalPos & Vertices:Intersection
	pVert_In = CreateIntersectionNode(pMesh,nGenType,LocalPos,LocalPos_In);
	if(!pVert_In)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::PreProcess_INTERSECT:\npVert_IN == NULL");
		return -1;
	}
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	// for pVert6:
	//		Vertex Order:0,1,2,3,0,i,2 so that 1D elems can be 
	//		created sequentially as (0,1),(1,2),..(0,i),(i,1)
	// for pVert3:
	//		Vertex Order:3,i,1 so that 1D elems can be 
	//		created sequentially as (3,i),(i,1)
	////////////////////////////////////////////////////////
	////////////////////////////////// pVert6
	for(int i = 0;i<4;i++)
	{
		LocalPos6[i]	= LocalPos[i];
		pVert6[i]		= pVert[i];
		/////////////////////////////
	}
	LocalPos6[4]	= LocalPos[0];
	pVert6[4]		= pVert[0];
	LocalPos6[5]	= LocalPos_In;
	pVert6[5]		= pVert_In;
	LocalPos6[6]	= LocalPos[2];
	pVert6[6]		= pVert[2];
	////////////////////////////////// pVert3
	LocalPos3[0]	= LocalPos[3];
	pVert3[0]		= pVert[3];
	LocalPos3[1]	= LocalPos_In;
	pVert3[1]		= pVert_In;
	LocalPos3[2]	= LocalPos[1];
	pVert3[2]		= pVert[1];
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE1D_4_INTERSECT(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by INTERSECTING DIAGONAL
	////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	// for pVert6:
	//		Vertex Order:0,1,2,3,0,i,2 so that 1D elems can be 
	//		created sequentially as (0,1),(1,2),..(0,i),(i,1)
	// for pVert3:
	//		Vertex Order:3,i,1 so that 1D elems can be 
	//		created sequentially as (3,i),(i,1)
	////////////////////////////////////////////////////////
	CDrFE0D*	pVert6[7];
	CDrFE0D*	pVert2[3];
	WORLD		LocalPos6[6],LocalPos2[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	int			nResult;
	////////////////////
	nResult = PreProcess_INTERSECT_FE1D(pMesh,nGenType,pVert,LocalPos,
						pVert6,LocalPos6,pVert2,LocalPos2);
	if(nResult<0)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::Post_FE1D_4_INTERSECT:\nPreProcess_INTERSECT_FE1D");
		return -1;
	}
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TRUSS:				// fall thro'
			nResult = Post_TRUSS(pMesh,nGenType,pVert6,LocalPos6,7);	// 6 Trusses
			nResult = Post_TRUSS(pMesh,nGenType,pVert2,LocalPos2,3);	// 2 Trusses
			break;
		case BEAM:				// 
			nResult = Post_BEAM(pMesh,nGenType,pVert6,LocalPos6,7);	// 6 Beams
			nResult = Post_BEAM(pMesh,nGenType,pVert2,LocalPos2,3);	// 2 Beams
			break;
		case PIPE:				//
			nResult = Post_PIPE(pMesh,nGenType,pVert6,LocalPos6,7);	// 6 Pipes
			nResult = Post_PIPE(pMesh,nGenType,pVert2,LocalPos2,3);	// 2 Pipes
			break;
		case ELBOW:				// 
			nResult = Post_ELBOW(pMesh,nGenType,pVert6,LocalPos6,7);	// 6 Elbows
			nResult = Post_ELBOW(pMesh,nGenType,pVert2,LocalPos2,3);	// 2 Elbows
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

int CMI_Qang2::PreProcess_CENTROID_4_FE1D
(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert6[],pWORLD LocalPos6,
					CDrFE0D* pVert3[],pWORLD LocalPos3
)
{
	CDrFE0D*	pVert_In;
	WORLD		LocalPos_In;		
	//////////////////////////////////////////////////////// Create LocalPos & Vertices:Intersection
	pVert_In = CreateCentroidNode_4(pMesh,nGenType,LocalPos,LocalPos_In);
	if(!pVert_In)
	{
		AfxMessageBox("ERROR:\nCMI_Qang2::PreProcess_CENTROID_4:\npVert_IN == NULL");
		return -1;
	}
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	// for pVert6:
	//		Vertex Order:0,1,2,3,0,i,2 so that 1D elems can be 
	//		created sequentially as (0,1),(1,2),..(0,i),(i,1)
	// for pVert3:
	//		Vertex Order:3,i,1 so that 1D elems can be 
	//		created sequentially as (3,i),(i,1)
	////////////////////////////////////////////////////////
	////////////////////////////////// pVert6
	for(int i = 0;i<4;i++)
	{
		LocalPos6[i]	= LocalPos[i];
		pVert6[i]		= pVert[i];
		/////////////////////////////
	}
	LocalPos6[4]	= LocalPos[0];
	pVert6[4]		= pVert[0];
	LocalPos6[5]	= LocalPos_In;
	pVert6[5]		= pVert_In;
	LocalPos6[6]	= LocalPos[2];
	pVert6[6]		= pVert[2];
	////////////////////////////////// pVert3
	LocalPos3[0]	= LocalPos[3];
	pVert3[0]		= pVert[3];
	LocalPos3[1]	= LocalPos_In;
	pVert3[1]		= pVert_In;
	LocalPos3[2]	= LocalPos[1];
	pVert3[2]		= pVert[1];
	/////////////
	return 0;
}

int CMI_Qang2::Post_FE1D_4_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by CENTROID
	////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////// Set LocalPos & Vertices
	// for pVert6:
	//		Vertex Order:0,1,2,3,0,i,2 so that 1D elems can be 
	//		created sequentially as (0,1),(1,2),..(0,i),(i,1)
	// for pVert3:
	//		Vertex Order:3,i,1 so that 1D elems can be 
	//		created sequentially as (3,i),(i,1)
	////////////////////////////////////////////////////////
	CDrFE0D*	pVert6[6];
	CDrFE0D*	pVert2[3];
	WORLD		LocalPos6[6],LocalPos2[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	PreProcess_CENTROID_4_FE1D(pMesh,nGenType,pVert,LocalPos,
						pVert6,LocalPos6,pVert2,LocalPos2);
	//////////////////////////////////////////////////////////////////////
	int			nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TRUSS:				// fall thro'
			nResult = Post_TRUSS(pMesh,nGenType,pVert6,LocalPos6,6);	// 6 Trusses
			nResult = Post_TRUSS(pMesh,nGenType,pVert2,LocalPos2,2);	// 2 Trusses
			break;
		case BEAM:				// 
			nResult = Post_BEAM(pMesh,nGenType,pVert6,LocalPos6,6);		// 6 Beams
			nResult = Post_BEAM(pMesh,nGenType,pVert2,LocalPos2,2);		// 2 Beams
			break;
		case PIPE:				//
			nResult = Post_PIPE(pMesh,nGenType,pVert6,LocalPos6,6);		// 6 Pipes
			nResult = Post_PIPE(pMesh,nGenType,pVert2,LocalPos2,2);		// 2 Pipes
			break;
		case ELBOW:				// 
			nResult = Post_ELBOW(pMesh,nGenType,pVert6,LocalPos6,6);	// 6 Elbows
			nResult = Post_ELBOW(pMesh,nGenType,pVert2,LocalPos2,2);	// 2 Elbows
			break;

		default:	return -1;
	}
	/////////
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CMI_Qang2::CalcCentroid_FACE_4(pWORLD Local,pWORLD pC)
{
	/////////////////////////
	CalcCentroid(pC,Local,4);
	/////
}

int CMI_Qang2::RotateFaceNodeIndices(pWORLD LPos, int* ix)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	int	temp;
	/////////////////////////////// guard against CUSP:rotate index
	if( Math3D.AreSame_WORLD( &(LPos[0]),&(LPos[1]),pHitNet->GetDblRatio() ) )
	{
		temp	= ix[0];
		ix[0] 	= ix[1];
		ix[1]	= ix[2];
		ix[2] 	= ix[3];
		ix[3] 	= temp;
	}	
	if( Math3D.AreSame_WORLD( &(LPos[1]),&(LPos[2]),pHitNet->GetDblRatio() ) )
	{
		temp	= ix[0];
		ix[0] 	= ix[2];
		ix[2] 	= temp;
		temp	= ix[1];
		ix[1] 	= ix[3];
		ix[3] 	= temp;
	}				
	/////////
	return 0;
}

////////////////////////////////////////////////////////////
void CMI_Qang2::Serialize(CArchive& ar)
{

	CMI_Gang1::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Qang2:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Qang2:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}
///////////////////////////////////// end of Module //////////////////////		
