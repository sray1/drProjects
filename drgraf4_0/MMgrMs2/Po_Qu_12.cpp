// CPo_Qu_12.cpp : implementation of the CPo_Qu_12 class
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
#include "DrMesh2D.h"
///////////////////// Elem
#include "Dr_Qu_12.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Qu_12.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Qu_12

IMPLEMENT_DYNAMIC(CPo_Qu_12,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Qu_12,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Qu_12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Qu_12::CPo_Qu_12()
{  
    	
	m_ElTypeID			= "QU_12";
	m_ElTypeNum			= QU_12;
	///////////////////////////////
	m_ElDegree			= ED_CUBIC;
	m_nEdgeDegree[0]	= 3;
	////////////////////////////
	 
} 
	
int CPo_Qu_12::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Qu_12* pNewObj = new CDr_Qu_12;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Qu_12* pNewObj	= (CDr_Qu_12*)(pMsObjMgr->AddToDataBase(nQIndex,QU_12));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,QU_12);		
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_4((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Qu_12::Post_FE2D\nGang2.Post_FE2D_4");
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

int CPo_Qu_12::SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType)
{
	CDr_Qu_12* pNewObj		= (CDr_Qu_12*)pFE2D;
	//////////////////////////////////////////////////////////////////////// Create Vertices 
	CMsMath	MsMath;
	WORLD	NewPos,Tem1Pos,Tem2Pos;
	///////////////////////////////////////////////////////// Coords: Node 5 & 6
	////////////////////////////////////// 5
	Tem1Pos = LocalPos[0]; 
	Tem2Pos = LocalPos[1];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 6
	Tem1Pos = LocalPos[0]; 
	Tem2Pos = LocalPos[1];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 7 & 8
	////////////////////////////////////// 7
	Tem1Pos = LocalPos[1]; 
	Tem2Pos = LocalPos[2];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 8
	Tem1Pos = LocalPos[1]; 
	Tem2Pos = LocalPos[2];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 9 & 10
	////////////////////////////////////// 9
	Tem1Pos = LocalPos[2]; 
	Tem2Pos = LocalPos[3];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 10
	Tem1Pos = LocalPos[2]; 
	Tem2Pos = LocalPos[3];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 11 & 12
	////////////////////////////////////// 11
	Tem1Pos = LocalPos[3]; 
	Tem2Pos = LocalPos[0];
	///
	MsMath.Scale3DPts(2.,&Tem1Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	////////////////////////////////////// 12
	Tem1Pos = LocalPos[3]; 
	Tem2Pos = LocalPos[0];
	///
	MsMath.Scale3DPts(2.,&Tem2Pos);
	MsMath.Add3DPts(&Tem1Pos,&Tem2Pos,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////
	return 0;
}

int CPo_Qu_12::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)QU_12);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(12);		
	pNewObj->SetnCorners(4);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(4);			// Bounding Edges
	pNewObj->SetnEdgeNodes(12);		
	pNewObj->SetElDegree(ED_CUBIC);
	pNewObj->SetEdgeDegrees(3,0);
	pNewObj->SetEdgeDegrees(3,1);
	pNewObj->SetEdgeDegrees(3,2);
	pNewObj->SetEdgeDegrees(3,3);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
