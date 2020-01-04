// Mouse.cpp : implementation file
//


#include "stdafx.h" 

/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "Po_Truss.h"
#include "Po_Beam.h"
#include "Po_Pipe.h"
#include "Po_Elbow.h"
/////////////////////
#include "MI_GangN.h"
#include "MI_GangC.h"
/////////////////////
#include "MI_Gang1.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Gang1,CMI_Gang0,1)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////////////////////////////////////////////
CMI_Gang1::CMI_Gang1()
{
}

CMI_Gang1::~CMI_Gang1()
{
}	
//////////////////////////////////////////////////////////////////////////// Poting Helper
int CMI_Gang1::ShowCurveInfo(CDrCurve* pDrCurve)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrCurve->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	CDListMgr*		pNodeList	= pDrCurve->GetINodeList();
    CList<int,int>* pElSegList	= pDrCurve->GetElperSegList_S();
	CURVEPROC 		CurveType	= pDrCurve->GetCurveType_S();
	CIRCLETYPE		CircType	= pDrCurve->GetCircleType();
	CString			FromID		= pDrCurve->GetFromIDNode_S()->GetObjectID();
	CString			ToID		= pDrCurve->GetToIDNode_S()->GetObjectID();
	double			dAng		= pDrCurve->GetTheta_S();
	BOOL			bArc		= pDrCurve->IsArcType();
	BOOL			bClosed		= pDrCurve->IsClosed_S();
	double			dAngSpec	= pDrCurve->GetTheta_S();
	double			dRadius		= pDrCurve->GetRadius_S();
	///////////////////////////
	CString			CCID = "";
	CString			TIID = "";
	CString			CAID = "";
	CString			CBID = "";
	CDrNode*		pCN; 
	/////////////////////////////////////////////////////////////////////// total elems
	int nElems = 0;
	if(!(pElSegList->IsEmpty()))
	{
		for (POSITION posI = pElSegList->GetHeadPosition( );posI !=NULL;)
		{
			////
			nElems += pElSegList->GetNext(posI); 
		}
	}
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Curve_To_Post Hit ****\n");
	//////////////////////////////////////
	switch(CurveType)
	{
		case CP_CIRCLE:

			pCN = pDrCurve->GetCNode_CC(); 
			if(pCN)
				CCID = (pDrCurve->GetCNode_CC())->GetObjectID();
			pCN = pDrCurve->GetCNode_TI(); 
			if(pCN)
				TIID = (pDrCurve->GetCNode_TI())->GetObjectID();
			pCN = pDrCurve->GetCNode_CA(); 
			if(pCN)
				CAID = (pDrCurve->GetCNode_CA())->GetObjectID();
			pCN = pDrCurve->GetCNode_CB(); 
			if(pCN)
				CBID = (pDrCurve->GetCNode_CB())->GetObjectID();
			////////////////
			switch(CircType)
			{
				
				case CIRCLE_BY_ROT:

					j += sprintf(buf+j,"Circle %s contains:\n\t%d InputNode to Rotate\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					j += sprintf(buf+j,"\t%s and %s are Axis Nodes\n",FromID,ToID);
					if(dAng == 360.)
						j += sprintf(buf+j,"\tClosed Circle\n");
					else
						j += sprintf(buf+j,"\t%f is Angle of Rotation\n",dAng);
					break;
				
				case CIRCLE_BY_NO3:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					if(bClosed)
						j += sprintf(buf+j,"\tClosed Circle\n");
					else
					{
						if(bArc)
							j += sprintf(buf+j,"\tArc upto 3rd Node\n");
						else
							j += sprintf(buf+j,"\t%f is Angle of Rotation\n",dAngSpec);
					}
					break;
				
				
				case CIRCLE_BY_2N_TI:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					j += sprintf(buf+j,"2 End Nodes & Tangent Intersection\n");
					j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",TIID);
					break;
				
				
				case CIRCLE_BY_2N_CC:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
						j += sprintf(buf+j,"2 End Nodes & Center\n");
						j += sprintf(buf+j,"\t%s is Center Node\n",CCID);
						break;
						
				case CIRCLE_BY_2CN_TI_R:

					j = sprintf(buf,"Circle %s contains:\n\t%d InPut Nodes\n\t%d Elements\n\tRadius = %f\n",
							*pID,pNodeList->GetCount(),nElems,dRadius);
					j += sprintf(buf+j,"2 Control Nodes on Tangents &\nTangent Intersection\n");
					j += sprintf(buf+j,"\t%s is CNode_CA\n",CAID);
					j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",TIID);
					j += sprintf(buf+j,"\t%s is CNode_CB\n",CBID);
					break;
	
							
				default:
					break;

			}
			break;

		default:

			//////
			j = sprintf(buf,"Curve %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
			*pID,pNodeList->GetCount(),nElems);
	}
	/////////////////////////
	j += sprintf(buf+j,"Nodes:\n");
	//////////////////////////////
	for (POSITION posI = pNodeList->GetHeadPosition( );posI !=NULL;)
	{
		////
		CDrNode* pNode = (CDrNode*)pNodeList->GetNextObject(posI);
		j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
	}
	sprintf( buf + j-2, ";");
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tPost This Curve");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CMI_Gang1::GenPost_CurveNodes(CDrMesh1D* pMesh,CDrCurve* pDrCurve,BOOL bMNode,BOOL bAnyWay)		
{
	int nResult;		
	//////////////////////////////////////////// Output memory
	int nOut		= pDrCurve->GetLongOutPts();
	////////////////
	CMI_GangC GangC;
	////////////////////////////////
	pWORLD	pOut	= GangC.FixMem(nOut);
	pDOUBLE pOutWts = GangC.FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	GangC.SetbBack(FALSE);
	GangC.FillMeshNodesCurve(pDrCurve,pOut,pOutWts,nOut);
	///////////////////////////////////////////////////////// Post MNodes 
	CString LineID = pDrCurve->GetObjectID();
	pMesh->SetObjectID(LineID);
	//////////////////////////
	BOOL bCNode = FALSE;		
	nResult = Post_CurveNodes_FE0D(pMesh,pOut,nOut,bCNode,bMNode,bAnyWay);	//TRUE=MNode/FALSE=VERTEX
	////////////////////////
	GangC.FreeMem(pOut);
	GangC.FreeMemD(pOutWts);
	///////
	if(nResult<0)
		return nResult;
	///////
	return 0;
}

int CMI_Gang1::Post_CurveNodes_FE0D(CDrMesh1D* pMesh, pWORLD pOut,int nOut,
										BOOL bCNode,BOOL bMNode,BOOL bAnyWay)		
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///
	CMI_Gang0 Gang0;
	//////////////////////////////////////////// Now Post
	char	buf[50];
	int		nLastNum;
	////////////////////////////////
	int		s,j;
	WORLD	LocalPos;
	////////
	for (s = 0; s<nOut; s++)
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
		///////////
		j = s;
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
		pAddNode->GetLabelList()->InsertObject(pLabel);
		int nResult = ReciprocateElemMeshList(pAddNode, pMesh, MESH1D);
		if(nResult <0)
			return nResult;
		//////////////////////////////////////// Now Ready
		pAddNode->SetShow(TRUE);
	}
	/////////
	return 0;
}

int CMI_Gang1::Post_CurveNodes_IorC(CDrCurve* pCurve,pWORLD pOut, int nOut, BOOL bCNode)		
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
		pAddNode->GetCurveList()->InsertObject(pCurve);
		pCurve->GetElemList()->InsertObject(pAddNode);
	}
	/////////
	return 0;
}

int CMI_Gang1::Post_Curve_Elements(CDrObject* pMesh,CDrObject* pDrCurve,UINT nGenType,UINT nElemType)		
{
	////////////////////////////////////////////////////////////////////////////////
	//				nElemType = TRUSS,BEAM,PIPE,ELBOW
	//////////////////////////////////////////////////////////////////////////////// Doit
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh Vertex Pool
	if(pListV->IsEmpty())
		return -1;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////// 
	int nResult;
	//////////////////////////////////////////// Output memory
	int nOut_S		= (int)((CDrCurve*)pDrCurve)->GetLongOutPts();
	////////////////////////////////
	int		s;
	int		nVert = 2,ix[2];
	//////////////////////////////////////////////////////////////////////////////// Loop
	for (s = 0; s<nOut_S-1; s++)
	{
		//////////////////////////////////// FE0D Index in FE0DList
		ix[0] = s;
		ix[1] = ix[0] + 1;
		///////////////////////////////////////////////////////////// Vertex Info
		CDrFE0D*	pVert[2];
		WORLD		LocalPos[2];
		/////////////////////////////////////////
		GetVertexInfo(pListV,ix,pVert,LocalPos,2);
		///////////////////////////////////////////////////////////// Go Do it
		switch(nElemType)
		{
			case TRUSS:		
				
				nResult = Post_TRUSS(pMesh,nGenType,pVert,LocalPos,nVert);
				///////
				if(nResult<0)
				{
					AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_Curve_Elements\nPost_TRUSS");
					return -1;
				}
				break;


			case BEAM:		
				
				nResult = Post_BEAM(pMesh,nGenType,pVert,LocalPos,nVert);
				///////
				if(nResult<0)
				{
					AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_Curve_Elements\nPost_BEAM");
					return -1;
				}
				break;


			case PIPE:		
				
				nResult = Post_PIPE(pMesh,nGenType,pVert,LocalPos,nVert);
				///////
				if(nResult<0)
				{
					AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_Curve_Elements\nPost_PIPE");
					return -1;
				}
				break;


			case ELBOW:		
				
				nResult = Post_ELBOW(pMesh,nGenType,pVert,LocalPos,nVert);
				///////
				if(nResult<0)
				{
					AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_Curve_Elements\nPost_ELBOW");
					return -1;
				}
				break;


				default:
					return -1;
		//////////////////////////////////////////////
		}				
	}
	/////////
	return 0;
}

int CMI_Gang1::Regen_MESH1D_Elements(CDrObject* pMeshNew,CDrObject* pMeshOld)		
{
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CDrMesh1D* pMesh		= (CDrMesh1D*)pMeshNew;
	CDrMesh1D* pMotherMesh	= (CDrMesh1D*)pMeshOld;
	//////////////////////////////////////////////
	CDListMgr* pOldFE0DList_Mesh	= pMotherMesh->GetFE0DList();	// Old Nodes of mother Mesh
	CDListMgr* pOldFE1DList_Mesh	= pMotherMesh->GetFE1DList();	// Old Elems of mother Mesh
	CDListMgr* pNewFE0DList_Mesh	= pMesh->GetFE0DList();			// Newly XFormed
	CDListMgr* pNewFE1DList_Mesh	= pMesh->GetFE1DList();			// Empty
	///
	pNewFE1DList_Mesh->RemoveAll();
	//////////////////////////////////////////////////// Loop
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
			/////////////////////////////////////////////// Is it XFormed Already
			int index = pOldFE0DList_Mesh->GetObjectIndex(pFE0D);
			if(index<0)
			{
				AfxMessageBox("Internal Error:\nCMI_Gang1::Regen_MESH1D_Elements\nindex<0");
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

void CMI_Gang1::CloneInfoForRegenElems_FE1D(CDrFE1D* pDrObject,CDrFE1D* pOldObj)
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

int CMI_Gang1::Post_TRUSS(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert)		
{
	////////////////////////////////////////////////////////////////////////
	CPo_Truss	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= TRUSS;	// needed for Centroid Label
	TransferData_1D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	CDrFE0D*	pVertCurrent[2];;
	WORLD		LPosCurrent[2];
	///////////////////////
	for(int i=0; i<nVert-1;i++)
	{
		pVertCurrent[0] = pVert[i]; 
		pVertCurrent[1] = pVert[i+1]; 
		LPosCurrent[0] = LocalPos[i]; 
		LPosCurrent[1] = LocalPos[i+1]; 
		///////////////////////////////
		nResult = Po_Elem.Post_FE1D_Elem(pMesh,nGenType,pVertCurrent,LocalPos);
		///////////////////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_Truss\nPo_Elem.Post_FE1D");
			return -1;
		}
	}
	//////////
	return 0;
}

int CMI_Gang1::Post_BEAM(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert)		
{
	////////////////////////////////////////////////////////////////////////
	CPo_Beam	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= BEAM;	// needed for Centroid Label
	TransferData_1D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	CDrFE0D*	pVertCurrent[2];;
	WORLD		LPosCurrent[2];
	///////////////////////
	for(int i=0; i<nVert-1;i++)
	{
		pVertCurrent[0] = pVert[i]; 
		pVertCurrent[1] = pVert[i+1]; 
		LPosCurrent[0] = LocalPos[i]; 
		LPosCurrent[1] = LocalPos[i+1]; 
		///////////////////////////////
		nResult = Po_Elem.Post_FE1D_Elem(pMesh,nGenType,pVertCurrent,LocalPos);
		///////////////////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_BEAM\nPo_Elem.Post_FE1D");
			return -1;
		}
	}
	//////////
	return 0;
}

int CMI_Gang1::Post_PIPE(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert)		
{
	////////////////////////////////////////////////////////////////////////
	CPo_Pipe	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= PIPE;	// needed for Centroid Label
	TransferData_1D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	CDrFE0D*	pVertCurrent[2];;
	WORLD		LPosCurrent[2];
	///////////////////////
	for(int i=0; i<nVert-1;i++)
	{
		pVertCurrent[0] = pVert[i]; 
		pVertCurrent[1] = pVert[i+1]; 
		LPosCurrent[0] = LocalPos[i]; 
		LPosCurrent[1] = LocalPos[i+1]; 
		///////////////////////////////
		nResult = Po_Elem.Post_FE1D_Elem(pMesh,nGenType,pVertCurrent,LocalPos);
		///////////////////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_PIPE\nPo_Elem.Post_FE1D");
			return -1;
		}
	}
	//////////
	return 0;
}

int CMI_Gang1::Post_ELBOW(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert)		
{
	////////////////////////////////////////////////////////////////////////
	CPo_Elbow	Po_Elem;
	int			nResult;
	///////////////////////////////////////////////////////////////// Transfer Data
	m_ElTypeNum	= ELBOW;	// needed for Centroid Label
	TransferData_1D(&Po_Elem);
	///////////////////////////////////////////////////////////////// Do Post
	CDrFE0D*	pVertCurrent[2];;
	WORLD		LPosCurrent[2];
	///////////////////////
	for(int i=0; i<nVert-1;i++)
	{
		pVertCurrent[0] = pVert[i]; 
		pVertCurrent[1] = pVert[i+1]; 
		LPosCurrent[0] = LocalPos[i]; 
		LPosCurrent[1] = LocalPos[i+1]; 
		///////////////////////////////
		nResult = Po_Elem.Post_FE1D_Elem(pMesh,nGenType,pVertCurrent,LocalPos);
		///////////////////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_Gang1::Post_ELBOW\nPo_Elem.Post_FE1D");
			return -1;
		}
	}
	//////////
	return 0;
}

int CMI_Gang1::TransferData_1D(CPo_FE1D* pFE1D)		
{
	////////////////////////////////////////////////////////////////////// Members
// 	pFE1D->SetElNumID(m_ElNumID);			
//	pFE1D->SetElTypeID(m_ElTypeID);	
	pFE1D->Setline_id(m_line_id);
 	pFE1D->Setrid(m_rid[0],0);
 	pFE1D->Setrid(m_rid[1],1);
 	pFE1D->Setpid(m_pid);
 	pFE1D->Setmid(m_mid);
	//////////////////////////////////
//	pFE1D->SetElNum(m_ElNum);			
//	pFE1D->SetElTypeNum(m_ElTypeNum);	
	pFE1D->Setline_no(m_line_no);		
	pFE1D->Setrel(m_rel[0],0);			
	pFE1D->Setrel(m_rel[1],1);			
	pFE1D->Setprop(m_prop);		
	pFE1D->Setmat(m_mat);
	//////////////////////////////////
	pFE1D->Setnumseg(m_numseg);		
	pFE1D->SetRefTemp(m_RefTemp);
	pFE1D->SetOnBndry(TRUE);
	////////////////////////////////////////////////////////////////////// helper
//	pNewObj->SetCenter(POINT ptCenter);
	/////////
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////// Helpers
int CMI_Gang1::GetVertexInfo(CDListMgr* pListV,int* Index,CDrFE0D* pVert[],
												pWORLD LocalPos, int nIndex)
{												
	////////////////////////////////////
	POSITION	Pos;
	/////////////////////////////////////////////// Vertices
	for(int i=0;i<nIndex;i++)
	{
		Pos			= pListV->FindIndex(Index[i]);
		pVert[i]	= (CDrFE0D*)pListV->GetAt(Pos);
	}
	/////////////////////////////////////////////// LocalPos
	GetLocalPos_Vertices(LocalPos,pVert,nIndex);
	//////////
	return 0;
}

void CMI_Gang1::GetLocalPos_Vertices(pWORLD Local,CDrFE0D* pVert[],int nVert)
{
	/////////////////////////
	for(int i=0;i<nVert;i++)
		Local[i] = *(pVert[i]->GetLocalPos());
	/////
}

void CMI_Gang1::CalcCentroid(pWORLD pCentroid,pWORLD Local,int nVert)
{
	if(nVert<=0)
		return;
	//
	pCentroid->x = Local[0].x;
	pCentroid->y = Local[0].y;
	pCentroid->z = Local[0].z;
	/////////////////////////
	for(int i=1;i<nVert;i++)
	{
		pCentroid->x += Local[i].x;
		pCentroid->y += Local[i].y;
		pCentroid->z += Local[i].z;
	}
	///////////////////
	double r = 1./nVert;
    ///////////////////
	pCentroid->x	*= r;
	pCentroid->y	*= r;
	pCentroid->z	*= r;
	/////
}
/////////////////////////////////////////////////////////////////////////////
void CMI_Gang1::Serialize(CArchive& ar)
{

	CMI_Gang0::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Gang1:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Gang1:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


