// Mouse.cpp : implementation file
//


#include "stdafx.h" 


#include "MsMath.h" 
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "HitNet.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
/////////////////////
#include "MI_GangN.h"
#include "MI_GangC.h"
#include "MI_GangP.h"
#include "MI_Gang0.h" 
/////////////////////
#include "MI_Tang2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  

#define BARY2LIN_PT(i,j,nP)				(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)

#define BARY2LIN_TRI_1_NEW(i,j,nP,nDeg)	( (j)  + ((i)*(2*(nP)-(i)-2))/(nDeg) )/(nDeg)
#define BARY2LIN_TRI_2_NEW(i,j,nP,nDeg)	( (j - nDeg)  + ((i)*(2*(nP)-(i)-2))/(nDeg) - ((nP) - 1) + (i) )/(nDeg)
//////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Tang2,CMI_Gang2,1)
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////////////////////////////////////////////
CMI_Tang2::CMI_Tang2()
{
}

CMI_Tang2::~CMI_Tang2()
{
}
////////////////////////////////////////////////////////////////////////////////////////// Triangle

int CMI_Tang2::Post_PatchCurves_3(CDrPatch* pPatch, pWORLD pOut, pDOUBLE pOutWts, int nOut)		
{
//	todo later
	/////////
	return -1;
}
/////////////////////////////////////////////////////////////
int CMI_Tang2::Post_PatchNodes_IorC_3(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode)		
{
	int nResult = Post_PatchNodes_IorC(pPatch, pOut, nOut, bCNode);
	///////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Qang2::Post_PatchNodes_IorC_3");
		return -1;
	}
	/////////
	return 0;
}

BOOL CMI_Tang2::IsDuplicated(WORLD& CurrentNodPos, CDrObject* pMesh)
{
	CMsMath		MathMs;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr*	pList = pMesh->GetFE0DList();
	WORLD		NodPos;
	//////////////////////////////////////////// Check
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pFE0D 	= (CDrFE0D*)pList->GetNextObject(pos);
		///////////////////////
		NodPos = *(pFE0D->GetLocalPos());
		///////////////////////////////
		if(MathMs.AreSame_WORLD(&NodPos,&CurrentNodPos,pHitNet->GetDblRatio()))
			return TRUE;
	}
	////////////////////////
	return FALSE;
}

int CMI_Tang2::Post_PatchNodes_FE0D_3(CDrObject* pMesh,UINT nGenType, CDrPatch* pDrPatch,pWORLD pOut,
										BOOL bCNode,BOOL bMNode,BOOL bAnyWay)		
{
	int nOut = (int)(pDrPatch->GetLongOutPts());
	/////////////////////////////////////////////////////////////////// LOOP: Output
	int i;
	///////////
	for (i=0;i<nOut;i++)
	{
		////
		WORLD LocalPos = *(pOut+i);
		//////////////////////////////////////////////////////// Post
		Post_FE0D_TRIANGLE(LocalPos,pMesh,nGenType,bCNode,bMNode,bAnyWay);
		//////////////
	}										///////////////////////////// end LIST
	/////////////////////
    return 0;
} 
  	
int  CMI_Tang2::Post_FE0D_TRIANGLE_1(pWORLD pOut,CDrObject* pMesh,UINT nGenType,
									 CDrPatch* pDrPatch,BOOL bCNode,BOOL bMNode,
									 BOOL bAnyWay,int iOutGlo_ST,int jOutGlo_ST)
{ 
	///////////////////////
	int i,j,L1;
	int iOut,jOut;
	WORLD	LocalPos;
	////////////////////////
	int nOut_S		= pDrPatch->GetOut_S();
	int nOutSeg_S	= pDrPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			LocalPos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
			if( IsDuplicated(LocalPos,pMesh) )
				continue;
			//////////////////////////////////////////////////////// Post
			Post_FE0D_TRIANGLE(LocalPos,pMesh,nGenType,bCNode,bMNode,bAnyWay);
			//////////////
		}
	}
	/////////
	return 0;
}

int  CMI_Tang2::Post_FE0D_TRIANGLE_2(pWORLD pOut,CDrObject* pMesh,UINT nGenType,
									 CDrPatch* pDrPatch,BOOL bCNode,BOOL bMNode,
									 BOOL bAnyWay,int iOutGlo_ST,int jOutGlo_ST)
{ 
	///////////////////////
	int i,j,L1;
	int iOut,jOut;
	WORLD	LocalPos;
	////////////////////////
	int nOut_S		= pDrPatch->GetOut_S();
	int nOutSeg_S	= pDrPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			LocalPos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
			if( IsDuplicated(LocalPos,pMesh) )
				continue;
			//////////////////////////////////////////////////////// Post
			Post_FE0D_TRIANGLE(LocalPos,pMesh,nGenType,bCNode,bMNode,bAnyWay);
			//////////////
		}
	}
	/////////
	return 0;
}

int  CMI_Tang2::Post_FE0D_TRIANGLE(WORLD& LocalPos,CDrObject* pMesh,UINT nGenType,
									BOOL bCNode,BOOL bMNode,BOOL bAnyWay)
{ 
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh		vertex	list(Entire Pool)
	///////////////////////////////////// Check if NodePos similar to any existing Node of THIS MESH
	BOOL bExist = FALSE;
	CDrFE0D* pAddNode;
	///////////////////
	for (POSITION pos = pListV->GetFirstObjectPos();pos !=NULL;)
	{
		pAddNode = (CDrFE0D*)pListV->GetNextObject(pos);
		if(pAddNode)
		{
			WORLD OldPos = *(pAddNode->GetLocalPos());
			/////////////
			CMsMath MsMath;
			bExist = MsMath.AreSame_WORLD(&OldPos, &LocalPos,pHitNet->GetDblRatio());
			////////
			if(bExist)
				break;
		}
	}
	//////////////////////////////////////////////////////// DoesNOT Exist,so CREATE ANYWAY
	if(!bExist)
	{
		///////////////////////////////////// name
		CString Nid;
		if(bMNode)
			SetElemInfoID(Nid,MNODE);
		else
			SetElemInfoID(Nid,FE0D);
		///////////////////////////////////// MNode or Vertex:Public and Yes reciprocation
		CDrLabel*	pLabel;
		int			nNodeIndex = -12345,nLabelIndex;	// anyway	
		///////////////////////////////////
		CMI_Gang0 Gang0;
		pAddNode = Gang0.CreateFE0D(Nid,pLabel,LocalPos,bCNode,TRUE,bMNode,
								nNodeIndex,nLabelIndex);	// Create 
		///
		if(!pAddNode)	// 
			return -1;
	}
	/////////////////////////////////////////////////////////////////////// save
	pAddNode->SetCategory(CA_ELEMENT);
	///////////////////////////////////////////////////////////////////////
	pMesh->GetFE0DList()->InsertObject(pAddNode);		//MNodeList 
//		pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
	//////////////////////////////////////// Reciprocate
//	pAddNode->SetGenObj(pMesh);
//	pAddNode->SetGenObjType(nGenType);
		int nResult = ReciprocateElemMeshList(pAddNode, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	//////////////////////////////////////// Now Ready
	pAddNode->SetShow(TRUE);
	/////////
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////// EDGEs
int CMI_Tang2::Post_PatchEdges_FE1D_3(CDrMesh2D* pMesh)		
{
	//		THIS ROUTINE IS NOT NECESSARY : 10/04/97
	/////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	//			FILLS:		pMesh->EdgeList()
	//			DEFINES:	Positive Direction of Edges
	////////////////////////////////////////////////////
	CDrPatch* pDrPatch	= pMesh->GetGenObj();
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	CDListMgr* pTriList = pDrPatch->GetTriangleList();
	if(pTriList->IsEmpty() )
		return -1;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So
	////////////////////////
	int nOutSeg_S	= pDrPatch->GetOutSegUnif_S();			
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		if(nType == 1)
			TRIANGLE_1_Edge(pMesh,nOutSeg_S,iOutGlo,jOutGlo);
		else
		if(nType == 2)
			TRIANGLE_2_Edge(pMesh,nOutSeg_S,iOutGlo,jOutGlo);
		else
		{
			//////////////////
			AfxMessageBox("ERROR\nCMI_Tang2::Post_PatchEdges_FE1D_3\nnType !==1 or 2");
			return -1;
		}
	}
	///////////////////////////// end LIST
	return 0;
}

void CMI_Tang2::TRIANGLE_1_Edge(CDrMesh2D* pMesh,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST)
{ 

	//		THIS ROUTINE IS NOT NECESSARY : 10/04/97
	/////////////////////////////////////////////////////
	CDrPatch* pDrPatch	= pMesh->GetGenObj();
	int nOut_S			= pDrPatch->GetOut_S();
	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld;
	int iOut,jOut;
	//////////////////////////////////////////// u-dir
	for (j=0;j<nOutSeg_S;j++)
	{
		iOld = 0;
		//////
		for (m=0;m<nOutSeg_S-j;m++)
		{
			i		= iOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			i++;
			iOut	= iOutGlo_ST + i;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,1);	// 1 = U-dir	
			////
			iOld = i;
		}
	}
	///////////////////////////// v-dir
	for (i=0;i<nOutSeg_S;i++)
	{
		jOld = 0;
		//////
		for (m=0;m<nOutSeg_S-i;m++)
		{
			j		= jOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			j++;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,2);	// 2 = V-dir	
			////
			jOld = j;
		}
	}
	///////////////////////////// w-dir
	for (k=0;k<nOutSeg_S;k++)
	{
		iOld = 0;
		jOld = nOutSeg_S - k;
		//////
		for (m=0;m<nOutSeg_S-k;m++)
		{
			i = iOld;
			j = jOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			i++;
			j--;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,3);	// 3 = W-dir	
			////
			iOld = i;
			jOld = j;
		}
	}
}									

void CMI_Tang2::TRIANGLE_2_Edge(CDrMesh2D* pMesh,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST)
{ 

	//		THIS ROUTINE IS NOT NECESSARY : 10/04/97
	/////////////////////////////////////////////////////
	CDrPatch* pDrPatch	= pMesh->GetGenObj();
	int nOut_S			= pDrPatch->GetOut_S();
	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld;
	int iOut,jOut;
	//////////////////////////////////////////// u-dir
	for (j=0;j<nOutSeg_S;j++)
	{
		iOld = 0;
		//////
		for (m=0;m<nOutSeg_S-j;m++)
		{
			i		= iOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			i++;
			iOut	= iOutGlo_ST - i;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,1);	// 1 = U-dir	
			////
			iOld = i;
		}
	}
	///////////////////////////// v-dir
	for (i=0;i<nOutSeg_S;i++)
	{
		jOld = 0;
		//////
		for (m=0;m<nOutSeg_S-i;m++)
		{
			j		= jOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			j++;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,2);	// 2 = V-dir	
			////
			jOld = j;
		}
	}
	///////////////////////////// w-dir
	for (k=0;k<nOutSeg_S;k++)
	{
		iOld = 0;
		jOld = nOutSeg_S - k;
		//////
		for (m=0;m<nOutSeg_S-k;m++)
		{
			i = iOld;
			j = jOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			i++;
			j--;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
//			Save_EdgeInfo(pMesh,MESH2D,L1,L2,m,3);	// 3 = W-dir	
			////
			iOld = i;
			jOld = j;
		}
	}
}									

///////////////////////////////////////////////////////////////////////////////////////////////////////
int CMI_Tang2::Post_Patch_TRIANGLES(CDrObject* pMesh,CDrObject* pDrPatch,UINT nGenType,UINT nElemType)		
{
	////////////////////////////////////////////////////////////////////////////////
	//				nElemType = Tr_3,Tr_6,Tr_9,Tr_10
	//////////////////////////////////////////////////////////////////////////////// Doit
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh Vertex Pool
	if(pListV->IsEmpty())
		return -1;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////// 
	CDListMgr* pTriList = ((CDrPatch*)pDrPatch)->GetTriangleList();
	if(pTriList->IsEmpty() )
		return -1;
	////////////////////////
	int nResult;
	int nTriangle	= pTriList->GetCount();
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	int index = -1;
	///////////
	int nOut_S		= ((CDrPatch*)pDrPatch)->GetOut_S();			
	int nOutPerSeg	= ((CDrPatch*)pDrPatch)->GetOutSegUnif_S();			
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		index++;
		////
		nResult = Post_OneTriangularPatch_LIN((CDrMesh2D*)pMesh,iOutGlo,jOutGlo,nElemType,
																nOutPerSeg,nOut_S,nType);
	}										///////////////////////////// end LIST
	/////////////////////
    return 0;
}

int CMI_Tang2::Post_OneTriangularPatch_LIN(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
										int nOutPerSeg,int nOutTot_S,int TriangularPatchType)
{
	/////////////////////////////////////////////////////
	//								FOR:
	//				NON_ISOPARAMETRIC ELEMENT GENERATION
	//								AND
	//						ISOPARAMETRIC_LINEAR
	/////////////////////////////////////////////////////
	int i,j,nP,nB1,nB2,nTri,nTr1,nTr2,nDeg,nCount=0;
	int nP_Glo;
	///////////////////////
	nP		= nOutPerSeg + 1;	// No. of Output Vertices on each side (One Trianglular Patch)	
	nP_Glo	= nOutTot_S;		// No. of Output Vertices on each side (Total for All Patches)	
	////////////////////////////////////////
	nDeg		= 1;
	///////////////////////////
	nB1		= (nP - 1)/nDeg;			// No. of Type1 Triangle Side Controls	
	nB2		= (nP - 1 - nDeg)/nDeg;		// No. of Type2 Triangle Side Controls	
	nTr1	= (nB1+1)*nB1/2;			// No. of Type1 Triangles	
	nTr2	= (nB2+1)*nB2/2;			// No. of Type2 Triangles	
	nTri	= nTr1 + nTr2;				// No. of Triangles	
	///////////////////////////////////////////// Barycentric Coords
	//
	//
	//			v,j
	//			
	//			|
	//			|
	//			o
	//			| \
	//		u=0 |   \ w=0
	//			|     \
	//			|-------o ----  u,i
	//				v=0
	///////////////////////////////////////////// Type 2 Triangles
	//
	//		Triangle K:
	//
	//				   i
	//
	//				   |
	//				   |
	//			N1     P2		
	//			o------o------o N3
	//			 \	K1 |\ K3  |
	//			   \P1 o--oP4 o
	//				 \ |-K--\ |
	//				P0 o---o--o P5 ----- j
	//					\ P3  |
	//					  \K2 |
	//						\ |
	//						  o N2
	///////////////////////////////////////////// Type 1 Triangles
	//
	//		Triangle K:
	//						  i
	//				   N2     
	//				   o      |
	//				   | \    |
	//				   |K2 \  |
	//			       | P3  \
	//			    P5 o--o---o P0 ----- j
	//			       |\--K--| \
	//			       |P4o---oP1 \
	//				   | K3 \-| K1  \
	//				N3 o------o ----- o N1
	//				          P2
	//				        
	//
	/////////////////////////////////////////////////////////// LOOP
	int nResult,nC,nCount1=0,nCount2=0;
	int	ix[3];
	//////////////////////////////////////////////////////////////////////// Type1
	for(i=0;i<nOutPerSeg;i++)
	{
		////////////////////////////////
		for(j=0;j<nOutPerSeg-i;j++)
		{
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Lin(iGlo + i, jGlo + j , nP_Glo, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Lin(iGlo - i, jGlo - j , nP_Glo, ix);
			else
			{
				//////////////////
				AfxMessageBox("CMI_Tang2::Post_OneTriangularPatch_LIN\nnType !==1 or 2");
				return -1;
			}
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCall GetTriangleVertexInfo_1_Lin");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount1++;
		}
	}
	//////////////////////////////////////////////////////////////////////// Type2
	for(i=1;i<nOutPerSeg;i++)
	{
		////////////////////////////////
		for(j=1;j<=nOutPerSeg-i;j++)
		{
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Lin(iGlo + i, jGlo + j , nP_Glo, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Lin(iGlo - i, jGlo - j , nP_Glo, ix);
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCallGetTriangleVertexInfo_2_Lin");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount2++;
			/////////////////
		}
	}
	//////////////////
	if(nCount1 != nTr1)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount1 != nTr1!");
		return - 1;
	}
	if(nCount2 != nTr2)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount2 != nTr2!");
		return - 1;
	}
	///////////////////////////
	nCount = nCount1 + nCount2;
	if(nCount != nTri)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount != nTri!");
		return - 1;
	}
	return 0;
	
}

int CMI_Tang2::GetTriangleVertexInfo_1_Lin(int i, int j, int nP, pINT pIndex)
{
	int nDeg		= 1;
	////////////////////////////////
	int P[3],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  3 for Linear
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_1_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j+1,nP);
	P[2]	= BARY2LIN_PT(i+1	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<3;m++)
		pIndex[m] = P[m];
	/////////
	return 0;

}

int CMI_Tang2::GetTriangleVertexInfo_2_Lin(int i, int j, int nP, pINT pIndex)
{
	int P[3],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  3 for Linear
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_2_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j-1,nP);
	P[2]	= BARY2LIN_PT(i-1	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<3;m++)
		pIndex[m] = P[m];
	/////////
	return 0;
}

int CMI_Tang2::Post_OneTriangularPatch_QUAD(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
														int nOut_S,int TriangularPatchType)
{
	/////////////////////////////////////////////////////
	//								FOR:
	//				ISOPARAMETRIC ELEMENT GENERATION
	/////////////////////////////////////////////////////
	int i,j,nP,nB1,nB2,nTri,nTr1,nTr2,nDeg,nCount=0;
	///////////////////////
	nP	= nOut_S;		// No. of Vertices on each side	
	////////////////////////////////////////
	nDeg		= 2;
	///////////////////////////
	nB1		= (nP - 1)/nDeg;			// No. of Type1 Triangle Side Controls	
	nB2		= (nP - 1 - nDeg)/nDeg;		// No. of Type2 Triangle Side Controls	
	nTr1	= (nB1+1)*nB1/2;			// No. of Type1 Triangles	
	nTr2	= (nB2+1)*nB2/2;			// No. of Type2 Triangles	
	nTri	= nTr1 + nTr2;				// No. of Triangles	
	///////////////////////////////////////////// Barycentric Coords
	//
	//
	//			v,j
	//			
	//			|
	//			|
	//			o
	//			| \
	//		u=0 |   \ w=0
	//			|     \
	//			|-------o ----  u,i
	//				v=0
	///////////////////////////////////////////// Type 2 Triangles
	//
	//		Triangle K:
	//
	//				   i
	//
	//				   |
	//				   |
	//			N1     P2		
	//			o------o------o N3
	//			 \	K1 |\ K3  |
	//			   \P1 o--oP4 o
	//				 \ |-K--\ |
	//				P0 o---o--o P5 ----- j
	//					\ P3  |
	//					  \K2 |
	//						\ |
	//						  o N2
	///////////////////////////////////////////// Type 1 Triangles
	//
	//		Triangle K:
	//						  i
	//				   N2     
	//				   o      |
	//				   | \    |
	//				   |K2 \  |
	//			       | P3  \
	//			    P5 o--o---o P0 ----- j
	//			       |\--K--| \
	//			       |P4o---oP1 \
	//				   | K3 \-| K1  \
	//				N3 o------o ----- o N1
	//				          P2
	//				        
	//
	/////////////////////////////////////////////////////////// LOOP
	int nResult,nC,nCount1=0,nCount2=0,nPm1 = nP-nDeg-1;
	int	ix[6];
	///////////////////
	for(i=0;i<=nPm1;i += nDeg)
	{
		////////////////////////////////
		for(j=0;j<=nPm1-i;j += nDeg)
		{
			////////////////////////////////////////////// Get:Type 1
			GetTriangleVertexInfo_1_Quad(i, j, nP, ix);
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Quad(iGlo + i, jGlo + j , nP, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Quad(iGlo - i, jGlo - j , nP, ix);
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCall GetTriangleVertexInfo_1_Quad");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount1++;
		}
		///////////////////////////////////////////// Is Type2?
		if(i==nPm1)
			continue;
		/////////////////////
		for(j=nDeg;j<=nPm1-i;j += nDeg)
		{
			////////////////////////////////////////////// Get:Type 2
			GetTriangleVertexInfo_2_Quad(i, j, nP, ix);
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Quad(iGlo + i, jGlo + j , nP, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Quad(iGlo - i, jGlo - j , nP, ix);
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCallGetTriangleVertexInfo_2_Quad");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount2++;
			/////////////////
		}
	}
	//////////////////
	if(nCount1 != nTr1)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount1 != nTr1!");
		return - 1;
	}
	if(nCount2 != nTr2)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount2 != nTr2!");
		return - 1;
	}
	///////////////////////////
	nCount = nCount1 + nCount2;
	if(nCount != nTri)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount != nTri!");
		return - 1;
	}
	return 0;
}

int CMI_Tang2::GetTriangleVertexInfo_1_Quad(int i, int j, int nP, pINT pIndex)
{
	int P[6],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  6 for Quad
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_1_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j+1,nP);
	P[2]	= BARY2LIN_PT(i		,j+2,nP);
	P[3]	= BARY2LIN_PT(i+1	,j	,nP);
	P[4]	= BARY2LIN_PT(i+1	,j+1,nP);
	P[5]	= BARY2LIN_PT(i+2	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<6;m++)
		pIndex[m] = P[m];
	/////////
	return 0;
}

int CMI_Tang2::GetTriangleVertexInfo_2_Quad(int i, int j, int nP, pINT pIndex)
{
	int P[6],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  6 for Quad
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_2_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j-1,nP);
	P[2]	= BARY2LIN_PT(i		,j-2,nP);
	P[3]	= BARY2LIN_PT(i-1	,j	,nP);
	P[4]	= BARY2LIN_PT(i-1	,j-1,nP);
	P[5]	= BARY2LIN_PT(i-2	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<6;m++)
		pIndex[m] = P[m];
	/////////
	return 0;
}

int CMI_Tang2::Post_OneTriangularPatch_CUBIC(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
														int nOut_S,int TriangularPatchType)
{
	/////////////////////////////////////////////////////
	//								FOR:
	//				ISOPARAMETRIC ELEMENT GENERATION
	/////////////////////////////////////////////////////
	int i,j,nP,nB1,nB2,nTri,nTr1,nTr2,nDeg,nCount=0;
	///////////////////////
	nP	= nOut_S;		// No. of Vertices on each side	
	////////////////////////////////////////
	nDeg		= 3;
	///////////////////////////
	nB1		= (nP - 1)/nDeg;			// No. of Type1 Triangle Side Controls	
	nB2		= (nP - 1 - nDeg)/nDeg;		// No. of Type2 Triangle Side Controls	
	nTr1	= (nB1+1)*nB1/2;			// No. of Type1 Triangles	
	nTr2	= (nB2+1)*nB2/2;			// No. of Type2 Triangles	
	nTri	= nTr1 + nTr2;				// No. of Triangles	
	///////////////////////////////////////////// Barycentric Coords
	//
	//
	//			v,j
	//			
	//			|
	//			|
	//			o
	//			| \
	//		u=0 |   \ w=0
	//			|     \
	//			|-------o ----  u,i
	//				v=0
	///////////////////////////////////////////// Type 2 Triangles
	//
	//		Triangle K:
	//
	//				   i
	//
	//				   |
	//				   |
	//			N1     P2		
	//			o------o------o N3
	//			 \	K1 |\ K3  |
	//			   \P1 o--oP4 o
	//				 \ |-K--\ |
	//				P0 o---o--o P5 ----- j
	//					\ P3  |
	//					  \K2 |
	//						\ |
	//						  o N2
	///////////////////////////////////////////// Type 1 Triangles
	//
	//		Triangle K:
	//						  i
	//				   N2     
	//				   o      |
	//				   | \    |
	//				   |K2 \  |
	//			       | P3  \
	//			    P5 o--o---o P0 ----- j
	//			       |\--K--| \
	//			       |P4o---oP1 \
	//				   | K3 \-| K1  \
	//				N3 o------o ----- o N1
	//				          P2
	//				        
	//
	/////////////////////////////////////////////////////////// LOOP
	int nResult,nC,nCount1=0,nCount2=0,nPm1 = nP-nDeg-1;
	int	ix[10];
	///////////////////
	for(i=0;i<=nPm1;i += nDeg)
	{
		////////////////////////////////
		for(j=0;j<=nPm1-i;j += nDeg)
		{
			////////////////////////////////////////////// Get:Type 1
			GetTriangleVertexInfo_1_Cubic(i, j, nP, ix);
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Cubic(iGlo + i, jGlo + j , nP, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_1_Cubic(iGlo - i, jGlo - j , nP, ix);
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCall GetTriangleVertexInfo_1_Cubic");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount1++;
		}
		///////////////////////////////////////////// Is Type2?
		if(i==nPm1)
			continue;
		/////////////////////
		for(j=nDeg;j<=nPm1-i;j += nDeg)
		{
			////////////////////////////////////////////// Get:Type 2
			GetTriangleVertexInfo_2_Cubic(i, j, nP, ix);
			///////////////////////////////////////////////////////
			if(TriangularPatchType == 1)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Cubic(iGlo + i, jGlo + j , nP, ix);
			else
			if(TriangularPatchType == 2)	// patch that is getting sub-divided
				nC = GetTriangleVertexInfo_2_Cubic(iGlo - i, jGlo - j , nP, ix);
			////////
			if(nC<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nCallGetTriangleVertexInfo_2_Cubic");
				return - 1;
			}
			/////////////////////////////////////////////////// Post
			nResult = Post_TRIANGLE(pMesh,ix,nElemType);
			if(nResult<0)
			{
				AfxMessageBox("Error:\nCMI_Tang2::\nPost_TRIANGLE");
				return - 1;
			}
			nCount2++;
			/////////////////
		}
	}
	//////////////////
	if(nCount1 != nTr1)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount1 != nTr1!");
		return - 1;
	}
	if(nCount2 != nTr2)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount2 != nTr2!");
		return - 1;
	}
	///////////////////////////
	nCount = nCount1 + nCount2;
	if(nCount != nTri)
	{
		AfxMessageBox("Error:\nCMI_Tang2::InsertTriangle_Linear\nnCount != nTri!");
		return - 1;
	}
	return 0;
}

int CMI_Tang2::GetTriangleVertexInfo_1_Cubic(int i, int j, int nP, pINT pIndex)
{
	int P[10],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  10 for Cubic
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_1_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j+1,nP);
	P[2]	= BARY2LIN_PT(i		,j+2,nP);
	P[3]	= BARY2LIN_PT(i		,j+3,nP);
	P[4]	= BARY2LIN_PT(i+1	,j	,nP);
	P[5]	= BARY2LIN_PT(i+1	,j+1,nP);
	P[6]	= BARY2LIN_PT(i+1	,j+2,nP);
	P[7]	= BARY2LIN_PT(i+2	,j	,nP);
	P[8]	= BARY2LIN_PT(i+2	,j+1,nP);
	P[9]	= BARY2LIN_PT(i+3	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<10;m++)
		pIndex[m] = P[m];
	/////////
	return 0;
}

int CMI_Tang2::GetTriangleVertexInfo_2_Cubic(int i, int j, int nP, pINT pIndex)
{
	int P[10],m;
//	int K;
	//////////////////////////////// Number of Vertices
	// Triangle # =  10 for Cubic
	//////////////////////////////////////////////// Current Triangle & Vertices
//	K		= BARY2LIN_TRI_2_NEW(i,j,nP,nDeg);
	P[0]	= BARY2LIN_PT(i		,j	,nP);
	P[1]	= BARY2LIN_PT(i		,j-1,nP);
	P[2]	= BARY2LIN_PT(i		,j-2,nP);
	P[3]	= BARY2LIN_PT(i		,j-3,nP);
	P[4]	= BARY2LIN_PT(i-1	,j	,nP);
	P[5]	= BARY2LIN_PT(i-1	,j-1,nP);
	P[6]	= BARY2LIN_PT(i-1	,j-2,nP);
	P[7]	= BARY2LIN_PT(i-2	,j	,nP);
	P[8]	= BARY2LIN_PT(i-2	,j-1,nP);
	P[9]	= BARY2LIN_PT(i-3	,j	,nP);
	////////////////////////////////////// SAVE
	for (m = 0;m<10;m++)
		pIndex[m] = P[m];
	/////////
	return 0;
}

int CMI_Tang2::Post_TRIANGLE(CDrMesh2D* pMesh,pINT ix,UINT nElemType)
{
	int ntemp,nResult;
	//////////////////////////////////////////////////////////////////////////////// Doit
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh Vertex Pool
	if(pListV->IsEmpty())
		return -1;
	//////////////////////////////////////////// Mesh Info
	ORIENT		Orient	= ((CDrMesh2D*)pMesh)->GetOrient();
	REF_TRI		Ref_Tri	= ((CDrMesh2D*)pMesh)->GetRefTri();
	//////////////////////////////////// Orient
	if(Orient == OT_CLOCKWISE)
	{
		ntemp	= ix[1];
		ix[1]	= ix[2];
		ix[2]	= ntemp;
	}
	///////////////////////////////////////////////////////////// Vertex Info
	CDrFE0D*	pVert[3];
	WORLD		LocalPos[3];
	////////////////////////////////////////
	GetVertexInfo(pListV,ix,pVert,LocalPos,3);
	///////////////////////////////////////////////////////////// Go Do it
	switch(Ref_Tri)
	{
		case RT_NOREF:			// leave alone						1 Quad 

			nResult = Post_FE2D_3_NOREF((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
			///////
			if(nResult<0)
			{
				AfxMessageBox("Internal ERROR:\nCMI_Tang2::Post_Patch_TRIANGLES\nRT_NOREF");
				return -1;
			}
			break;

		case RT_AUTO:			//				1 Tri

			nResult = Post_FE2D_3_AUTO((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
			///////
			if(nResult<0)
			{
				AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_Patch_TRIANGLES\nRT_AUTO");
				return -1;
			}
			break;

		case RT_CENTROID:		// Centroid							4 Tri

			nResult = Post_FE2D_3_CENTROID((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
			///////
			if(nResult<0)
			{
				AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_Patch_TRIANGLES\nRT_CENTROID");
				return -1;
			}
			break;

		case RT_MIDCEN:	// MidPtCentroidShortDiag			8 Tri

//			nResult = Post_FE2D_3_MIDCEN((CDrObject*)pMesh,MESH2D,pVert,LocalPos,nElemType);
//			///////
			nResult = -1;	// temporary
			if(nResult<0)
			{
				AfxMessageBox("Internal ERROR:\nCMI_Tang2::Post_Patch_TRIANGLES\nRT_MIDCEN");
				return -1;
			}
			break;

		default:
					return -1;
	}
	/////////
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////// Helpers
int CMI_Tang2::Post_FE2D_3_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by Leave Alone TRI
	////////////////////////////////////////////////////////////////////////
	int	nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TR_3:	
			nResult = Post_TR_3(pMesh,nGenType,pVert,LocalPos);
			break;

		case TR_6:	
			nResult = Post_TR_6(pMesh,nGenType,pVert,LocalPos);
			break;

		case TR_9:	
			nResult = Post_TR_9(pMesh,nGenType,pVert,LocalPos);	
			break;

		case TR_10:	
			nResult = Post_TR_10(pMesh,nGenType,pVert,LocalPos);	
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

int CMI_Tang2::Post_FE2D_3_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	int nResult = Post_FE2D_3_NOREF(pMesh,nGenType,pVert,LocalPos,nElemType);
	///////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Tang2::Post_FE2D_3_AUTO");
		return -1;
	}
	return 0;
}

CDrFE0D* CMI_Tang2::CreateCentroidNode_3(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,
																	WORLD& LocalPos_In)
{
	///////////////////////////////////////////////////////// Centroid
	CalcCentroid_FACE_3(LocalPos,&LocalPos_In);
	///////////////////////////////////////////////////////// create node
	return CreateMNode(pMesh,nGenType,LocalPos_In);
	//////
}

int CMI_Tang2::PreProcess_CENTROID_3
(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert31[],pWORLD LocalPos31,
					CDrFE0D* pVert32[],pWORLD LocalPos32,
					CDrFE0D* pVert33[],pWORLD LocalPos33
)
{
	CDrFE0D*	pVert_In;
	WORLD		LocalPos_In;		
	//////////////////////////////////////////////////////// Create LocalPos & Vertices:Intersection
	pVert_In = CreateCentroidNode_3(pMesh,nGenType,LocalPos,LocalPos_In);
	if(!pVert_In)
	{
		AfxMessageBox("ERROR:\nCMI_Tang2::PreProcess_CENTROID_3:\npVert_IN == NULL");
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
	////////////////////////////////// 3rd Triangle (intersection,2,0)
	LocalPos33[0]	= LocalPos_In;
	pVert33[0]		= pVert_In;
	LocalPos33[1]	= LocalPos[2];
	pVert33[1]		= pVert[2];
	LocalPos33[2]	= LocalPos[0];
	pVert33[2]		= pVert[0];
	/////////////
	return 0;
}

int CMI_Tang2::Post_FE2D_3_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType)
{
	////////////////////////////////////////////////////////////////////////	
	//						Posting by CENTROID
	////////////////////////////////////////////////////////////////////////
	CDrFE0D*	pVert31[3];
	CDrFE0D*	pVert32[3];
	CDrFE0D*	pVert33[3];
	WORLD		LocalPos31[3],LocalPos32[3],LocalPos33[3];
	///////////////////////////////////////////////////////////// Split Triangles Info
	PreProcess_CENTROID_3(pMesh,nGenType,pVert,LocalPos,
						pVert31,LocalPos31,pVert32,LocalPos32,
						pVert33,LocalPos33);
	//////////////////////////////////////////////////////////////////////
	int			nResult;
	///////////////////////////////////////////////////////////// Go Do it
	switch(nElemType)
	{
		case TR_3:	
			nResult = Post_TR_3(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_3(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_3(pMesh,nGenType,pVert33,LocalPos33);
			break;

		case TR_6:	
			nResult = Post_TR_6(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_6(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_6(pMesh,nGenType,pVert33,LocalPos33);
			break;

		case TR_9:	
			nResult = Post_TR_9(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_9(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_9(pMesh,nGenType,pVert33,LocalPos33);
			break;

		case TR_10:	
			nResult = Post_TR_10(pMesh,nGenType,pVert31,LocalPos31);
			nResult = Post_TR_10(pMesh,nGenType,pVert32,LocalPos32);
			nResult = Post_TR_10(pMesh,nGenType,pVert33,LocalPos33);
			break;

		default:	return -1;
	}
	/////////
	return 0;
}

void CMI_Tang2::CalcCentroid_FACE_3(pWORLD Local,pWORLD pC)
{
	/////////////////////////
	CalcCentroid(pC,Local,3);
	/////
}
////////////////////////////////////////////////////////////
void CMI_Tang2::Serialize(CArchive& ar)
{

	CMI_Gang1::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Tang2:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Tang2:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}
///////////////////////////////////// end of Module //////////////////////		
