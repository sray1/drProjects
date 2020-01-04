// CPo_Qu_8.cpp : implementation of the CPo_Qu_8 class
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
#include "Dr_Qu_8.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Qu_8.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Qu_8

IMPLEMENT_DYNAMIC(CPo_Qu_8,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Qu_8,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Qu_8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Qu_8::CPo_Qu_8()
{  
    	
	m_ElTypeID			= "QU_8";
	m_ElTypeNum			= QU_8;
	///////////////////////////////
	m_ElDegree			= ED_QUADRATIC;
	m_nEdgeDegree[0]	= 2;
	////////////////////////////
	 
} 
	
int CPo_Qu_8::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Qu_8* pNewObj = new CDr_Qu_8;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Qu_8* pNewObj	= (CDr_Qu_8*)(pMsObjMgr->AddToDataBase(nQIndex,QU_8));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,QU_8);		
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_4((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Qu_8::Post_FE2D\nGang2.Post_FE2D_4");
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

int CPo_Qu_8::SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType)
{

	CDr_Qu_8* pNewObj		= (CDr_Qu_8*)pFE2D;
	//////////////
	int			i;
	//////////////////////////////////////////////////////////////////////// Create Vertices 
	CMsMath	MsMath;
	WORLD	NewPos;
	CString	Nid;
	/////////////////////
    for(i=0;i<4;i++)
    {
		///////////////////////////////////////////////////////// Coords
		MsMath.Add3DPts(&LocalPos[i],&LocalPos[(i+1)%4],&NewPos);
		MsMath.Scale3DPts(0.5,&NewPos);
		///////////////////////////////
		EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
  	}	
	///////////////////////
	return 0;
}

int CPo_Qu_8::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)QU_8);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(8);		
	pNewObj->SetnCorners(4);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(4);			// Bounding Edges
	pNewObj->SetnEdgeNodes(8);		
	pNewObj->SetElDegree(ED_QUADRATIC);
	pNewObj->SetEdgeDegrees(2,0);
	pNewObj->SetEdgeDegrees(2,1);
	pNewObj->SetEdgeDegrees(2,2);
	pNewObj->SetEdgeDegrees(2,3);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
