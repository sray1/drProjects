// Mouse.cpp : implementation file
//


#include "stdafx.h" 


#include "MsMath.h" 
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
#include "DrEdge.h"
/////////////////////
#include "Po_Qu_4.h"
#include "Po_Qu_8.h"
#include "Po_Qu_9.h"
#include "Po_Qu_12.h"
#include "Po_Qu_16.h"
/////////////////////
#include "Po_Tr_3.h"
#include "Po_Tr_6.h"
#include "Po_Tr_9.h"
#include "Po_Tr_10.h"
/////////////////////
#include "MI_GangN.h"
#include "MI_GangC.h"
#include "MI_GangP.h"
#include "MI_Gang0.h" 
/////////////////////
#include "MI_Gang2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Gang2,CMI_Gang1,1)
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////////////////////////////////////////////
CMI_Gang2::CMI_Gang2()
{
}

CMI_Gang2::~CMI_Gang2()
{
}
////////////////////////////////////////////////////////////
int CMI_Gang2::Regen_MESH2D_Elements(CDrObject* pMeshNew,CDrObject* pMeshOld)		
{
	int nResult;
	////////////
	if( !(pMeshOld->GetFE1DList()->IsEmpty()) )
	{
		nResult = Regen_MESH2D_FE1D(pMeshNew,pMeshOld);
		if(nResult<0)
		{
			AfxMessageBox("Internal Error:\nCMI_Gang2::Regen_MESH2D_Elements\nRegen_MESH2D_FE1D");
			return -1;
		}
	}		
	///
	if( !(pMeshOld->GetFE2DList()->IsEmpty()) )
	{
		nResult = Regen_MESH2D_FE2D(pMeshNew,pMeshOld);		
		if(nResult<0)
		{
			AfxMessageBox("Internal Error:\nCMI_Gang2::Regen_MESH2D_Elements\nRegen_MESH2D_FE2D");
			return -1;
		}
	}
	/////////
	return 0;
}

int CMI_Gang2::Regen_MESH2D_FE1D(CDrObject* pMeshNew,CDrObject* pMeshOld)		
{
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CDrMesh2D* pMesh		= (CDrMesh2D*)pMeshNew;
	CDrMesh2D* pMotherMesh	= (CDrMesh2D*)pMeshOld;
	//////////////////////////////////////////////
	CDListMgr* pOldFE0DList_Mesh	= pMotherMesh->GetFE0DList();	// Old Nodes of mother Mesh
	CDListMgr* pOldFE1DList_Mesh	= pMotherMesh->GetFE1DList();	// Old Elems of mother Mesh
	CDListMgr* pNewFE0DList_Mesh	= pMesh->GetFE0DList();			// Newly XFormed
	CDListMgr* pNewFE1DList_Mesh	= pMesh->GetFE1DList();			// Empty
	//////////////////////////////////////////////////// Remove Old Stuff
	pNewFE1DList_Mesh->RemoveAll();
	//////////////////////////////////////////////////// Loop:FE1D
	int nElems = pOldFE1DList_Mesh->GetCount();
	///
	for(int i=0;i<nElems;i++)
	{
		/////////////////////////////////////////// Elem 
		POSITION pos1		= pOldFE1DList_Mesh->FindIndex(i);
		CDrFE1D* pOldObj	= (CDrFE1D*)pOldFE1DList_Mesh->GetAt(pos1);
		////////////////////////////////// Create
		int ElemType		= pOldObj->GetObjectType();
		int nQIndex;
		CDrFE1D* pNewObj	= (CDrFE1D*)(pMsObjMgr->AddToDataBase(nQIndex,ElemType));
		////////////////////////////////// Elem ID
		CString EdgeID;
		SetElemInfoID(EdgeID,ElemType);		
		///
		CloneInfoForRegenElems_FE1D(pNewObj,pOldObj);
		////////////////////////////////// OverRides
		pNewObj->SetObjectID(EdgeID);			
		pNewObj->SetElNumID(EdgeID);			
		/////////////////////////////////////////// FE0D
		CDListMgr* pOldFE0DList_Elem = pOldObj->GetFE0DList();
		int nFE0D = pOldFE0DList_Elem->GetCount();
		///
		pWORLD LocalPos = new WORLD[nFE0D];	// needed later for Edge Centroid Label
		//
		for(int j=0;j<nFE0D;j++)
		{
			POSITION pos0	= pOldFE0DList_Elem->FindIndex(j);
			CDrFE0D* pFE0D	= (CDrFE0D*)pOldFE0DList_Elem->GetAt(pos0);
			/////////////////////////////////////////////// Is it XFormed Already,Should be!
			int index = pOldFE0DList_Mesh->GetObjectIndex(pFE0D);
			if(index<0)
			{
				AfxMessageBox("Internal Error:\nCMI_Gang2::Regen_MESH2D_Elements\nindex<0");
				return -1;
			}
			//////
			pos0	= pNewFE0DList_Mesh->FindIndex(index);
			pFE0D	= (CDrFE0D*)pNewFE0DList_Mesh->GetAt(pos0);
			////////////////////////////////////////////////////// SAVE
			pNewObj->GetFE0DList()->InsertObject(pFE0D);
			LocalPos[j] = *(pFE0D->GetLocalPos());
			////////////////////////////////////////////////////// Reciprocate
			pFE0D->GetFE1DList()->InsertObject(pNewObj);
		}
		////////////////////////////////////////////////////////// Centroid Label Node
		CPo_FE1D Po_FE1D;
		Po_FE1D.SetElTypeNum(ElemType);	
		Po_FE1D.Make_CentroidLabel_EDGE(pNewObj,LocalPos,EdgeID);
		///////////////////
		delete [] LocalPos;
		////////////////////////////////////////////////////// Reciprocate
		pNewObj->GetMs1List()->InsertObject(pMesh);
		pNewFE1DList_Mesh->InsertObject(pNewObj);
		////////////////////////////////////////////////////// Local Bound
		pNewObj->Calc_3DBoundsLocal();											
		////////////////////////////////////////////////////////////////////// Show
		pObjectMgr->SetActiveObjectIndex(nQIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(ElemType);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nQIndex,ElemType);
	}
	/////////
	return 0;
}

int CMI_Gang2::Regen_MESH2D_FE2D(CDrObject* pMeshNew,CDrObject* pMeshOld)		
{
	int i,j,k,nResult;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CDrMesh2D* pMesh		= (CDrMesh2D*)pMeshNew;
	CDrMesh2D* pMotherMesh	= (CDrMesh2D*)pMeshOld;
	//////////////////////////////////////////////
	CDListMgr* pOldFE0DList_Mesh	= pMotherMesh->GetFE0DList();	// Old Nodes of mother Mesh
	CDListMgr* pOldFE2DList_Mesh	= pMotherMesh->GetFE2DList();	// Old Elems of mother Mesh
	CDListMgr* pNewFE0DList_Mesh	= pMesh->GetFE0DList();			// Newly XFormed
	CDListMgr* pNewFE2DList_Mesh	= pMesh->GetFE2DList();			// Empty
	//////////////////////////////// FE2D
	pNewFE2DList_Mesh->RemoveAll();
	//////////////////////////////// Edges
	pMesh->GetEdgeList()->RemoveAll();
	//////////////////////////////////////////////////// Loop
	int nElems = pOldFE2DList_Mesh->GetCount();
	///
	for(i=0;i<nElems;i++)
	{
		/////////////////////////////////////////// Elem 
		POSITION pos1		= pOldFE2DList_Mesh->FindIndex(i);
		CDrFE2D* pOldObj	= (CDrFE2D*)pOldFE2DList_Mesh->GetAt(pos1);
		////////////////////////////////// Create
		int ElemType		= pOldObj->GetObjectType();
		int nQIndex;
		CDrFE2D* pNewObj	= (CDrFE2D*)(pMsObjMgr->AddToDataBase(nQIndex,ElemType));
		////////////////////////////////// Elem ID
		CString FaceID;
		SetElemInfoID(FaceID,ElemType);		
		///
		CloneInfoForRegenElems_FE2D(pNewObj,pOldObj);
		////////////////////////////////// OverRides
		pNewObj->SetObjectID(FaceID);			
		pNewObj->SetElNumID(FaceID);			
		////////////////////////////////////////////////////////////////////// Vertices
		CDListMgr* pOldFE0DList_Elem = pOldObj->GetFE0DList();
		int nFE0D = pOldFE0DList_Elem->GetCount();
		//
		for(j=0;j<nFE0D;j++)
		{
			POSITION pos0	= pOldFE0DList_Elem->FindIndex(j);
			CDrFE0D* pFE0D	= (CDrFE0D*)pOldFE0DList_Elem->GetAt(pos0);
			/////////////////////////////////////////////// Is it XFormed Already
			int index = pOldFE0DList_Mesh->GetObjectIndex(pFE0D);
			if(index<0)
			{
				AfxMessageBox("Internal Error:\nCMI_Gang2::Regen_MESH2D_Elements\nindex<0");
				return -1;
			}
			//////
			pos0	= pNewFE0DList_Mesh->FindIndex(index);
			pFE0D	= (CDrFE0D*)pNewFE0DList_Mesh->GetAt(pos0);
			////////////////////////////////////////////////////// SAVE
			pNewObj->GetFE0DList()->InsertObject(pFE0D);
			////////////////////////////////////////////////////// Reciprocate
			pFE0D->GetFE2DList()->InsertObject(pNewObj);
		}
		////////////////////////////////////////////////////////////////////////////
		int nCorners	= pNewObj->GetnCorners();
		CDrFE0D* pVert[4];	// needed later for Edge List
//		pVert	= new CDrFE0D[nCorners];	// needed later for Edge List
		pWORLD LocalPos = new WORLD[nCorners];	// needed later for Edge Centroid Label
		///////////////////////////////////////
		for(k=0;k<nCorners;k++)
		{
			//////
			POSITION pos2	= pNewObj->GetFE0DList()->FindIndex(k);
			CDrFE0D* pFE0D	= (CDrFE0D*)pNewObj->GetFE0DList()->GetAt(pos2);
			//////
			pVert[k]	= pFE0D;
			LocalPos[k] = *(pFE0D->GetLocalPos());
		}
		////////////////////////////////////////////////////////// Edges & Centroid Label
		CPo_FE2D Po_FE2D;
		Po_FE2D.SetElTypeNum(ElemType);
//		UINT nGenType	= pNewObj->GetGenObjType();
		UINT nGenType	= MESH2D;
		///
		if(nCorners == 4)
		{
			Po_FE2D.Make_CentroidLabel_FACE_4(pNewObj,LocalPos,FaceID);
			nResult = Po_FE2D.SetFE2DInfo_Edge(pNewObj,pVert,pMeshNew,nGenType,nCorners);
		}
		else
		if(nCorners == 3)
		{
			Po_FE2D.Make_CentroidLabel_FACE_3(pNewObj,LocalPos,FaceID);
			nResult = Po_FE2D.SetFE2DInfo_Edge(pNewObj,pVert,pMeshNew,nGenType,nCorners);
		}
		///////////////////////////
		delete [] LocalPos;
		////////////////////////////////////////////////////// Reciprocate
		pNewObj->GetMs2List()->InsertObject(pMesh);
		pNewFE2DList_Mesh->InsertObject(pNewObj);
		////////////////////////////////////////////////////// Local Bound
		pNewObj->Calc_3DBoundsLocal();											
		////////////////////////////////////////////////////////////////////// Show
		pObjectMgr->SetActiveObjectIndex(nQIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(ElemType);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nQIndex,ElemType);
	}
	/////////
	return 0;
}

void CMI_Gang2::CloneInfoForRegenElems_FE2D(CDrFE2D* pDrObject,CDrFE2D* pOldObj)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	////////////////
	int nObjNo = pDrObject->GetObjectNo();
	if(pOldObj)
		pOldObj->GetObjectInfo(pDrObject);
	/////////////////////////////////////// DisConnect
	if(!(pDrObject->GetLabelList()->IsEmpty()) )
		pDrObject->GetLabelList()->RemoveAll(); 
	if(!(pDrObject->GetFE0DList()->IsEmpty()) )
		pDrObject->GetFE0DList()->RemoveAll();
	if(!(pDrObject->GetFE1DList()->IsEmpty()) )
		pDrObject->GetFE1DList()->RemoveAll();
	if(!(pDrObject->GetFE2DList()->IsEmpty()) )
		pDrObject->GetFE2DList()->RemoveAll();
	if(!(pDrObject->GetFE3DList()->IsEmpty()) )
		pDrObject->GetFE3DList()->RemoveAll();
	if(!(pDrObject->GetMbj3DList()->IsEmpty()) )
		pDrObject->GetMbj3DList()->RemoveAll();
	//////////////////////////////////////////// Override
	pDrObject->SetObjectNo(nObjNo);	
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////////////////////////////////
int CMI_Gang2::Save_EdgeInfo(CDrEdge* pAddEdge,CDrObject* pMesh,UINT nGenType,int ni,int nj)	
{	
	CDListMgr*	pList;
	/////////////////////////////////////////
	if(nGenType == MESH2D)
		pList = ((CDrMesh2D*)pMesh)->GetEdgeList();
//	else																			TODO
//	if(nGenType == MESH3D)
//		pList = ((CDrMesh3D*)pMesh)->GetEdgeList();
	///////////////////////////////////////////////////////////// Fill Edge info
	CString EdgeID;
	SetElemInfoID(EdgeID,GREF_EDGE);
	////////////////////////////////
	pAddEdge->SetObjectID(EdgeID);
	pAddEdge->SetVrtxIndex(ni,0);
	pAddEdge->SetVrtxIndex(nj,1);
//	pAddEdge->SetHist_RCH(nHist_RCH);	
//	pAddEdge->SetHistType(nHist_type);	// T-dir may be switched(Check from pMesh)	
	pAddEdge->SetMesh(pMesh);		
	pAddEdge->SetMeshType(nGenType);	
	///////////////////////////////////////////////////////////// Save
	pList->AddTail(pAddEdge);
	/////////////////////////
	return 0;
}

int CMI_Gang2::Post_PatchNodes_IorC(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////// 
	CDrNode*	pAddNode;
	CDrLabel*	pAddLabel;
	//////////////////////////////////////////// Now Post
	CString Nid = "";
	char	buf[50];
	int		nLastNum;
	////////////////////////////////
	int		s,j;
	WORLD	LocalPos;
	////////
	for (s = 0; s<nOut; s++)
	{
		if(bCNode)
		{
			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
			nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
			Nid = "CN_";
		}
		else
		{
			pObjectMgr->BumpLastInputNo(INODE);		// bump it
			nLastNum = pObjectMgr->GetLastInputNo(INODE);		// internal
			Nid = "";
		}
		sprintf(buf,"%d",nLastNum);
	    //////////////////////////////////// Name
	    Nid += buf; 
		///////////
		j = s;
		////////////////////////////		
		LocalPos.x	= (pOut+j)->x;
		LocalPos.y	= (pOut+j)->y;
		LocalPos.z	= (pOut+j)->z;
		///////////////////////////////////// INode & CNode:	Public	and NO	reciprocation
		int nNodeIndex,nLabelIndex;
		///////////////////////////
		CMI_GangN GangN;
//092798		pAddNode = GangN.CreateNode(Nid,pAddLabel, LocalPos, bCNode,TRUE,FALSE,
//092798									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
		pAddNode = GangN.CreateNode(Nid,pAddLabel, LocalPos, bCNode,TRUE,
						nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
		if(!pAddNode)	// 
				return -1;
		//////////////
		pAddNode->SetCategory(CA_ELEMENT);
		////////////////////////////////////////////// Reciprocate
		pAddNode->GetPatchList()->InsertObject(pPatch);
		pPatch->GetElemList()->InsertObject(pAddNode);		// Post Generated Nodes
	}
	/////////
	return 0;
}

int CMI_Gang2::ShowPatchInfo(CDrPatch* pDrPatch)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrPatch->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	PATCHPROC 		PatProc		= pDrPatch->GetPatchProc();
	PATSUBTYPE 		PatSubType	= pDrPatch->GetPatSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Patch Hit ****\n");
	//////////////////////////////////////
	switch(PatProc)
	{
		case PP_EXTRUDE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Extrusion\n",*pID);
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Rotation\n",*pID);
			break;

		case PP_LOFT2:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Lofting\n",*pID);
			break;

		case PP_DUCT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Ducting\n",*pID);
			break;

		case PP_SWEEP:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by\nSweeping\n",*pID);
			break;

		case PP_COONS:
			//////////////////////////////////////////////////// Show Patch
			if(PatSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nTriangular Coons Type\n",*pID);
			else
			if(PatSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nQuadrilateral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tEdit This Patch");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Patch with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}
/////////////////////////////////////////////////////////////////////////////////////////// FE2D
CDrFE0D* CMI_Gang2::CreateMNode(CDrObject* pMesh,UINT nGenType,WORLD& LocalPos_In)
{
	///////////////////////////////////////////////////////// create node
	CDrLabel* pLabel;
	int nNodeIndex = -12345,nLabelIndex;
	///////////
	CString Nid;
	SetElemInfoID(Nid,MNODE);
	///////////////////////
	CDrFE0D* pVert_In = CreateFE0D(Nid,pLabel,LocalPos_In,FALSE,TRUE,
											TRUE,nNodeIndex,nLabelIndex);
	//////////////////////////
	if(pVert_In)
	{
		//////////////
		pVert_In->SetCategory(CA_ELEMENT);
		///////////////////////////////////////////////////////////////////////
		pMesh->GetFE0DList()->InsertObject(pVert_In);		//MNodeList 
		//////////////////////////////////////// Reciprocate
//		pVert_In->SetGenObj(pMesh);
//		pVert_In->SetGenObjType(nGenType);
		int nResult = ReciprocateElemMeshList(pVert_In, pMesh, nGenType);
		if(nResult <0)
			return (CDrFE0D*)NULL;
		//////////////////////////////////////// Now Ready
		pVert_In->SetShow(TRUE);
		////////////////
		return pVert_In;
	}
	else
		return (CDrFE0D*)NULL;
	///
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int CMI_Gang2::Post_TR_3(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_LINEAR;
	////////////////////////////////////////////////////////////////////////
	CPo_Tr_3	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= TR_3;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_TR_3\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Gang2::Post_TR_6(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_QUADRATIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Tr_6	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= TR_6;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_TR_6\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}
int CMI_Gang2::Post_TR_9(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_CUBIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Tr_9	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= TR_9;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_TR_9\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Gang2::Post_TR_10(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)		
{
	m_ElDegree = ED_CUBIC;
	////////////////////////////////////////////////////////////////////////
	CPo_Tr_10	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= TR_10;	// needed for Centroid Label
	TransferData_2D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	nResult = Po_Elem.Post_FE2D(pMesh,nGenType,pVert,LocalPos);
	///////////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_Gang2::Post_TR_10\nPo_Elem.Post_FE2D");
		return -1;
	}
	//////////
	return nResult;
}

int CMI_Gang2::TransferData_2D(CPo_FE2D* pFE2D)		
{
	////////////////////////////////////////////////////////////////////// Members
// 	pFE2D->SetElNumID(m_ElNumID);			
// 	pFE2D->SetElTypeID(m_ElTypeID);	
	pFE2D->Setline_id(m_line_id);
 	pFE2D->Setrid(m_rid[0],0);
 	pFE2D->Setrid(m_rid[1],1);
 	pFE2D->Setrid(m_rid[2],2);
 	pFE2D->Setrid(m_rid[3],3);
 	pFE2D->Setpid(m_pid);
 	pFE2D->Setmid(m_mid);
	//////////////////////////////////
//	pFE2D->SetElNum(m_ElNum);			
//	pFE2D->SetElTypeNum(m_ElTypeNum);	
	pFE2D->Setline_no(m_line_no);		
	pFE2D->Setrel(m_rel[0],0);			
	pFE2D->Setrel(m_rel[1],1);			
	pFE2D->Setrel(m_rel[2],2);			
	pFE2D->Setrel(m_rel[3],3);			
	pFE2D->Setprop(m_prop);		
	pFE2D->Setmat(m_mat);
	//////////////////////////////////
	pFE2D->Setnumseg(m_numseg);		
	pFE2D->SetThkness(m_Thick);
	pFE2D->SetRefTemp(m_RefTemp);
	pFE2D->SetOnBndry(TRUE);
	//////////////////////////////////
	pFE2D->SetElDegree(m_ElDegree);
	////////////////////////////////////////////////////////////////////// helper
//	pNewObj->SetCenter(POINT ptCenter);
	/////////
	return 0;
}
////////////////////////////////////////////////////////////
void CMI_Gang2::Serialize(CArchive& ar)
{

	CMI_Gang1::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Gang2:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Gang2:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}
///////////////////////////////////// end of Module //////////////////////		
