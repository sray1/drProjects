// CPo_Qu_9.cpp : implementation of the CPo_Qu_9 class
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
#include "Dr_Qu_9.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Qu_9.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Qu_9

IMPLEMENT_DYNAMIC(CPo_Qu_9,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Qu_9,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Qu_9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Qu_9::CPo_Qu_9()
{  
    	
	m_ElTypeID			= "QU_9";
	m_ElTypeNum			= QU_9;
	///////////////////////////////
	m_ElDegree			= ED_QUADRATIC;
	m_nEdgeDegree[0]	= 2;
	////////////////////////////
	 
} 
	
int CPo_Qu_9::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Qu_9* pNewObj = new CDr_Qu_9;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Qu_9* pNewObj	= (CDr_Qu_9*)(pMsObjMgr->AddToDataBase(nQIndex,QU_9));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,QU_9);		
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_4((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Qu_9::Post_FE2D\nGang2.Post_FE2D_4");
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

int CPo_Qu_9::SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType)
{
	CDr_Qu_9* pNewObj		= (CDr_Qu_9*)pFE2D;
	//////////////////////////////////////////////////////////////////////// Create Vertices 
	CMsMath	MsMath;
	WORLD	NewPos,TempPos,Pos5,Pos7;
	///////////////////////////////////////////////////////// Coords: Node 5
	MsMath.Add3DPts(&LocalPos[0],&LocalPos[1],&TempPos);
	////////////////////////////////////// 5
	NewPos = TempPos;
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	Pos5 = NewPos;	// save for 9
	///////////////////////////////////////////////////////// Coords: Node 6
	MsMath.Add3DPts(&LocalPos[1],&LocalPos[2],&TempPos);
	////////////////////////////////////// 6
	NewPos = TempPos;
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 7
	MsMath.Add3DPts(&LocalPos[2],&LocalPos[3],&TempPos);
	////////////////////////////////////// 7
	NewPos = TempPos;
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	Pos7 = NewPos;	// save for 9
	///////////////////////////////////////////////////////// Coords: Node 8
	MsMath.Add3DPts(&LocalPos[3],&LocalPos[0],&TempPos);
	////////////////////////////////////// 8
	NewPos = TempPos;
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////////////////////////////////////// Coords: Node 9
	MsMath.Add3DPts(&Pos5,&Pos7,&TempPos);
	////////////////////////////////////// 9
	NewPos = TempPos;
	MsMath.Scale3DPts(.5,&NewPos);
	EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
	///////////////////////
	return 0;
}

int CPo_Qu_9::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)QU_9);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(9);		
	pNewObj->SetnCorners(4);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(4);			// Bounding Edges
	pNewObj->SetnEdgeNodes(9);		
	pNewObj->SetElDegree(ED_QUADRATIC);
	pNewObj->SetEdgeDegrees(2,0);
	pNewObj->SetEdgeDegrees(2,1);
	pNewObj->SetEdgeDegrees(2,2);
	pNewObj->SetEdgeDegrees(2,3);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
