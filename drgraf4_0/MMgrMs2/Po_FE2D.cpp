// CPo_FE2D.cpp : implementation of the CPo_FE2D class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "MsMath.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "HitNet.h"
/////////////////////
#include "Def_Elem.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "MI_Gang2.h"
#include "MI_Qang2.h"
#include "MI_Tang2.h"
#include "Po_FE2D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_FE2D

IMPLEMENT_DYNAMIC(CPo_FE2D,CPo_FE1D)
/*
BEGIN_MESSAGE_MAP(CPo_FE2D,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_FE2D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPo_FE2D::Post_FE2D_4(CDrFE2D* pAddFace,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid)		
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	Make_CentroidLabel_FACE_4(pAddFace,LocalPos,Eid);
	///////////////////////////////////////////////////////////////////////////// Reciprocate/Info
	SetFE2DInfo_4(pAddFace,pVert,pMesh,nGenType);
	/////////
	return 0;
}

int CPo_FE2D::Post_FE2D_3(CDrFE2D* pAddFace,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid)		
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	Make_CentroidLabel_FACE_3(pAddFace,LocalPos,Eid);
	///////////////////////////////////////////////////////////////////////////// Reciprocate/Info
	SetFE2DInfo_3(pAddFace,pVert,pMesh,nGenType);
	/////////
	return 0;
}

int CPo_FE2D::FillData_2D(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////
	pNewObj->SetElNumID(m_ElNumID);	
	pNewObj->SetElTypeID(m_ElTypeID);			// TRUSS,BEAM,PIPE etc
	pNewObj->Setline_id(m_line_id);;
	pNewObj->Setpid(m_pid);  
	pNewObj->Setmid(m_mid);  
	//////////////////////////////////
	pNewObj->SetElNum(m_ElNum);				// Element Number
	pNewObj->SetElTypeNum(m_ElTypeNum);			// id Number: Element Type
	pNewObj->Setline_no(m_line_no);;
	pNewObj->Setprop(m_prop);           //
	pNewObj->Setmat(m_mat);           //
	/////////////////////////
	pNewObj->Setnumseg(m_numseg);
	pNewObj->SetRefTemp(m_refTemp);				//RefrenceTemperature
	////////////////////////////// 
	pNewObj->SetCardNo(m_nCardNo);
	////////////////////////////// Genetics
//	pNewObj->SetGenObjType(nGenType);	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//	pNewObj->SetGenObj(pMesh);
	CMI_Gang0* pMI_Gang0;
		int nResult = pMI_Gang0->ReciprocateElemMeshList(pNewObj, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	//
	///////////////////////////////////////
	pNewObj->Setrid(m_rid[0],0);//
	pNewObj->Setrid(m_rid[1],1);//
	pNewObj->Setrid(m_rid[2],2);//
	pNewObj->Setrid(m_rid[3],3);//
	//////////////////////////////////
	pNewObj->Setrel(m_rel[0],0); 
	pNewObj->Setrel(m_rel[1],1); 
	pNewObj->Setrel(m_rel[2],2); 
	pNewObj->Setrel(m_rel[3],3);
	//////////////////////////////////
	pNewObj->SetThkness(m_Thick);
	///////////////////////////////////////
	switch(m_ElDegree)
	{
		case ED_LINEAR:		m_nEdgeDegree[0] = 1;	break;		
		case ED_QUADRATIC:	m_nEdgeDegree[0] = 2;	break;		
		case ED_CUBIC:		m_nEdgeDegree[0] = 3;	break;		
		case ED_QUARTIC:	m_nEdgeDegree[0] = 4;	break;		
		case ED_QUINTIC:	m_nEdgeDegree[0] = 5;	break;		
		case ED_MIXED:		m_nEdgeDegree[0] = -1;	break;
		default: break;
	}
	pNewObj->SetEdgeDegrees(m_nEdgeDegree[0],0);
	////////////////////////////////////////////////////////////////////////////////	
	pNewObj->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pNewObj->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////// Helpers
int CPo_FE2D::SetFE2DInfo_4(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	int nResult;
	/////////////////////////////////////////////////// 
	nResult = SetFE2DInfo_Vrtx(pFE2D,pVert,pMesh,nGenType,4);
	nResult = SetFE2DInfo_Edge(pFE2D,pVert,pMesh,nGenType,4);
	//////////////////////////////////////////////////////////////////////// Reciprocate
//	pFE2D->SetGenObjType(nGenType);
//	pFE2D->SetGenObj(pMesh);
	CMI_Gang0* pMI_Gang0;
		nResult = pMI_Gang0->ReciprocateElemMeshList(pFE2D, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	//
	/////////
//	if(nGenType == MESH2D)
		((CDrMesh2D*)pMesh)->GetFE2DList()->InsertObject(pFE2D);
//	else
//	if(nGenType == MESH3D)
//		((CDrMesh3D*)pMesh)->GetFE2DList()->InsertObject(pFE2D);
	///////////////////////////////////////////////
	pFE2D->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pFE2D->SetLayer(pLayer->GetCurrentLayer());
	/////////////////////
	return nResult;
}

int CPo_FE2D::SetFE2DInfo_3(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	int nResult;
	/////////////////////////////////////////////////// 
	nResult = SetFE2DInfo_Vrtx(pFE2D,pVert,pMesh,nGenType,3);
	nResult = SetFE2DInfo_Edge(pFE2D,pVert,pMesh,nGenType,3);
	//////////////////////////////////////////////////////////////////////// Reciprocate
//	pFE2D->SetGenObjType(nGenType);
//	pFE2D->SetGenObj(pMesh);
		CMI_Gang0* pMI_Gang0;
		nResult = pMI_Gang0->ReciprocateElemMeshList(pFE2D, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	/////////
//	if(nGenType == MESH2D)
		((CDrMesh2D*)pMesh)->GetFE2DList()->InsertObject(pFE2D);
//	else
//	if(nGenType == MESH3D)
//		((CDrMesh3D*)pMesh)->GetFE2DList()->InsertObject(pFE2D);
	///////////////////////////////////////////////
	pFE2D->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pFE2D->SetLayer(pLayer->GetCurrentLayer());
	/////////////////////
	return nResult;
}

int CPo_FE2D::SetFE2DInfo_Vrtx(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,int nEnds)
{
	//////////////////////////////////////////////////// Update Current Plat
	int			i;
	////////////////////////////////////////////
	CDListMgr*	pList0 = pFE2D->GetFE0DList();	// element	vertex	list
	//////////////////////////////////////////////////////////////////////// Vertices 
    for(i=0;i<nEnds;i++)
    {
		//
		pList0->InsertObject(pVert[i]);
		///////////////////////////////////////////// Reciprocate, if not yet
		CDListMgr* pList2 = pVert[i]->GetFE2DList(); 
		if(pList2->GetObjectIndex(pFE2D)<0)
			pList2->InsertObject(pFE2D);
		//
	
  	}
	///////////////////////
	return 0;
}

int CPo_FE2D::SetFE2DInfo_Edge(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,int nEnds)
{
	CDListMgr*	pListE;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Plat
	int			i;
	/////////////////////////////////////////
//	if(nGenType == MESH2D)
		pListE = ((CDrMesh2D*)pMesh)->GetEdgeList();	// Mesh		edge	list(Entire Pool)
//	else
//	if(nGenType == MESH3D)
//		pListE = ((CDrMesh3D*)pMesh)->GetEdgeList();	// Mesh		edge	list(Entire Pool)
	/////
	CDListMgr*	pList1 = pFE2D->GetFE1DList();	// element	edge	list
	//////////////////////////////////////////////////////////////////////// Edges
	BOOL bPos;
	CDrFE0D* pVi;
	CDrFE0D* pVj;
	////////////////////
    for(i=0;i<nEnds;i++)
    {
		pVi = pVert[i]; 
		pVj = pVert[(i+1)%nEnds];
		//////////////////////
		CDrEdge* pEdge = GetEdge(pMesh,pVi,pVj,bPos);
		//
		if(pEdge)
		{
			pList1->InsertObject(pEdge);
			///////////////////////////////////// Reciprocate
			CFaceInfo* pFaceInfo = new CFaceInfo;
			pFaceInfo->SetDrFace(pFE2D);
			///
			if(nEnds == 3)
				pFaceInfo->SetFaceType(TRIANGLE);
			else
				pFaceInfo->SetFaceType(QUAD);
			///
			pFaceInfo->SetGenObj(pMesh);
			pFaceInfo->SetGenType(nGenType);
			pFaceInfo->SetFaceDim(2); // 2D
			/////////
			pEdge->GetFaceInfoList()->AddTail(pFaceInfo);
		}
		else
		{
			AfxMessageBox("ERROR:\nCPo_FE2D::SetFE2DInfo\npEdge == NULL");
			return -1;
		}
		//////////////////////////
		pFE2D->SetPosiEdge(i,bPos);
		//
	
  	}
	///////////////////////
	return 0;
}

CDrEdge* CPo_FE2D::GetEdge(CDrObject* pMesh,CDrFE0D* pVi,CDrFE0D* pVj,BOOL& bPositive)
{
	//////////////////////////////////////////////////////////////////////
	//	If (Exists)
	//		Check if +ve or -ve
	//	else
	//		Create A +ve Edge & store
	/////////////////////////////////
/*
	if(((CDrMesh2D*)pMesh)->GetEdgeList()->IsEmpty())
	{
		AfxMessageBox("ERROR:\nCPo_FE2D::GetEdge\nMeshEdgeList is Empty");
		return (CDrEdge*)(NULL);
	}
*/
	//////////////////////////
	CDListMgr*	pListV = pMesh->GetFE0DList();					// Mesh		vertex	list(Entire Pool)
	CDListMgr*	pListE = ((CDrMesh2D*)pMesh)->GetEdgeList();	// Mesh		edge	list(Entire Pool)
	int nEdges = pListE->GetCount();
	//////////////////////////////////////////////////////// EdgeList NOT Empty
	if(nEdges>0)
	{
		POSITION pos;
		int ni,nj;
		CDrFE0D* pVi_Cur;
		CDrFE0D* pVj_Cur;
		//////////////////
	    for(int i=0;i<nEdges;i++)
		{
			//////////////////////////// Get Edge
			pos = pListE->FindIndex(i);
			CDrEdge* pEdge = (CDrEdge*)(pListE->GetAt(pos));
			///
			ni = pEdge->GetVrtxIndex(0);
			nj = pEdge->GetVrtxIndex(1);
			//////////////////////////// Get End Vertices
			pos = pListV->FindIndex(ni);
			pVi_Cur = (CDrFE0D*)(pListV->GetAt(pos));
			pos = pListV->FindIndex(nj);
			pVj_Cur = (CDrFE0D*)(pListV->GetAt(pos));
			//////////////////////////// Compare
			if( (pVi_Cur == pVi) && (pVj_Cur == pVj) )
			{
				bPositive = TRUE;
				return pEdge;
			}
			else
			if( (pVi_Cur == pVj) && (pVj_Cur == pVi) )
			{
				bPositive = FALSE;
				return pEdge;
			}
			else
				continue;
		}
  	}
	//////////////////////////////////////////////////////// Edge NOT Found
	int iIndex = pListV->GetObjectIndex(pVi);
	int jIndex = pListV->GetObjectIndex(pVj);
	///
	if(iIndex<0 || jIndex<0)
	{
		////////////////////////////////////
		AfxMessageBox("ERROR:\nCPo_FE2D::GetEdge\niIndex<0 || jIndex<0");
		return (CDrEdge*)(NULL);
	}
	///////////////////////////////////////////////////////////// Create & Fill Edge info
	CDrEdge* pAddEdge = new CDrEdge;
	///
	if(pAddEdge)
	{
		CMI_Gang2 Gang2;
		Gang2.Save_EdgeInfo(pAddEdge,pMesh,MESH2D,iIndex,jIndex);
		/////////////
		bPositive = TRUE;
		return pAddEdge;
	}
	else
	{
		AfxMessageBox("ERROR:\nCPo_FE2D::GetEdge\npAddEdge==NULL");
		return (CDrEdge*)(NULL);
	}
}	

int CPo_FE2D::Make_CentroidLabel_FACE_4(CDrFE2D* pFace,pWORLD LocalPos,CString& Eid)
{
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	WORLD		Centroid;
	CDrNode*	pCNLabel;	// Edge Label Control Node at Center
	////////////////////////////////////////
	CMI_Qang2 Gang2;
	Gang2.CalcCentroid_FACE_4(LocalPos,&Centroid);
	///
	pCNLabel = Make_CentroidLabel(Centroid,Eid);
	////////////////////////////////////////
	if(!pCNLabel)
		return -1;
	//////////////
	pCNLabel->SetCategory(CA_ELEMENT);
	pFace->GetNodeList()->RemoveAll();
	pFace->GetNodeList()->InsertObject(pCNLabel);		// Post Generated Nodes
	/////////
	return 0;
}

int CPo_FE2D::Make_CentroidLabel_FACE_3(CDrFE2D* pFace,pWORLD LocalPos,CString& Eid)
{
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	WORLD		Centroid;
	CDrNode*	pCNLabel;	// Edge Label Control Node at Center
	////////////////////////////////////////
	CMI_Tang2 Gang2;
	Gang2.CalcCentroid_FACE_3(LocalPos,&Centroid);
	///
	pCNLabel = Make_CentroidLabel(Centroid,Eid);
	////////////////////////////////////////
	if(!pCNLabel)
		return -1;
	//////////////
	pCNLabel->SetCategory(CA_ELEMENT);
	pFace->GetNodeList()->RemoveAll();
	pFace->GetNodeList()->InsertObject(pCNLabel);		// Post Generated Nodes
	/////////
	return 0;
}

int CPo_FE2D::EachAddlNodeInfo(CDrFE2D* pFE2D,pWORLD NewPos,CDrObject* pMesh,UINT nGenType)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh		vertex	list(Entire Pool)
	CDListMgr*	pList0 = pFE2D->GetFE0DList();	// element	vertex	list
	///////////////////////////////////// Check if NodePos similar to any existing Node of THIS MESH
	BOOL bExist = FALSE;
	CDrFE0D* pAddNode;
	///////////////////
	for (POSITION pos = pListV->GetFirstObjectPos();pos !=NULL;)
	{
		pAddNode = (CDrFE0D*)pListV->GetNextObject(pos);
		if(pAddNode)
		{
			WORLD LocPos = *(pAddNode->GetLocalPos());
			/////////////
			CMsMath MsMath;
			bExist = MsMath.AreSame_WORLD(&LocPos, NewPos,pHitNet->GetDblRatio());
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
		SetElemInfoID(Nid,MNODE);
		///////////////////////////////////// MNode or Vertex:Public and Yes reciprocation
		CDrLabel*	pLabel;
		int			nNodeIndex = -12345,nLabelIndex;	// anyway	
		///////////////////////////////////
		CMI_Gang0 Gang0;
		pAddNode = Gang0.CreateFE0D(Nid,pLabel,*NewPos,FALSE,TRUE,TRUE,
								nNodeIndex,nLabelIndex);	// Create 
		///
		if(!pAddNode)	// 
			return -1;
		///////////////////////////////////// 
		pAddNode->SetCategory(CA_ELEMENT);
		///////////////////////////////////////////
		pListV->InsertObject(pAddNode);		//MNodeList 
//		pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
		//////////////////////////////////////// Reciprocate
		int nResult = Gang0.ReciprocateElemMeshList(pAddNode, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	//
//		pAddNode->SetGenObj(pMesh);
//		pAddNode->SetGenObjType(nGenType);
		//////////////////////////////////////////// Common Reciprocate
		pList0->InsertObject(pAddNode);		//MNodeList of Elem 
		pAddNode->GetFE2DList()->InsertObject(pFE2D);
	}
	else
	{
		//////////////////////////////////////////// Common Reciprocate
		pList0->InsertObject(pAddNode);		//MNodeList of Elem 
		pAddNode->GetFE2DList()->InsertObject(pFE2D);
	}
	//////////////////////////////////////// Now Ready
	pAddNode->SetShow(TRUE);
	/////////
	return 0;
}

////////////////////////////////////////// end of module //////////////////