// CPo_Tr_10.cpp : implementation of the CPo_Tr_10 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "MsMath.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Elem.h"
#include "DrPatch.h"
/////////////////////
#include "Def_Mesh.h"
///////////////////// Elem
#include "Dr_Tr_10.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Tr_10.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Tr_10

IMPLEMENT_DYNAMIC(CPo_Tr_10,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Tr_10,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Tr_10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Tr_10::CPo_Tr_10()
{  
    	
	m_ElTypeID			= "TR_10";
	m_ElTypeNum			= TR_10;
	///////////////////////////////
	m_ElDegree			= ED_CUBIC;
	m_nEdgeDegree[0]	= 3;
	////////////////////////////
	 
} 
	
int CPo_Tr_10::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Tr_10* pNewObj = new CDr_Tr_10;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Tr_10* pNewObj	= (CDr_Tr_10*)(pMsObjMgr->AddToDataBase(nQIndex,TR_10));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,TR_10);	
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_3((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Tr_10::Post_FE2D\nPost_FE2D_3");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	SetAddlNodeInfo((CDrFE2D*)pNewObj,LocalPos,pMesh,nGenType);
	Fill_Data_MeshObjs((CDrFE2D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Tr_10::SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType)
{
	CDr_Tr_10* pNewObj		= (CDr_Tr_10*)pFE2D;
	//////////////////////////////////////////////////////////////////////// Create Vertices 
	CMsMath	MsMath;
	WORLD	NewPos,Tem1Pos,Tem2Pos;
	WORLD	Pos6,Pos9;
	///////////////////////////////////////////////////////// Coords: Node 4 & 5
	////////////////////////////////////// 4
	Tem1Pos = LocalPos[0]; 
	Tem2Pos = LocalPos[1];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 5
	Tem1Pos = LocalPos[0]; 
	Tem2Pos = LocalPos[1];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 6 & 7
	////////////////////////////////////// 6
	Tem1Pos = LocalPos[1]; 
	Tem2Pos = LocalPos[2];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	Pos6 = NewPos;	// for Node 10
	////////////////////////////////////// 7
	Tem1Pos = LocalPos[1]; 
	Tem2Pos = LocalPos[2];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 8 & 9
	////////////////////////////////////// 8
	Tem1Pos = LocalPos[2]; 
	Tem2Pos = LocalPos[0];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 9
	Tem1Pos = LocalPos[2]; 
	Tem2Pos = LocalPos[0];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	Pos9 = NewPos;	// for Node 10
	///////////////////////////////////////////////////////// Coords: Node 10
	////////////////////////////////////// 10
	Tem1Pos = Pos6; 
	Tem2Pos = Pos9;
	///
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////
	return 0;
}

int CPo_Tr_10::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)TR_10);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(10);		
	pNewObj->SetnCorners(3);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(3);			// Bounding Edges
	pNewObj->SetnEdgeNodes(9);		
	pNewObj->SetElDegree(ED_QUADRATIC);
	pNewObj->SetEdgeDegrees(2,0);
	pNewObj->SetEdgeDegrees(2,1);
	pNewObj->SetEdgeDegrees(2,2);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
