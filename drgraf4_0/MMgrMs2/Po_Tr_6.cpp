// CPo_Tr_6.cpp : implementation of the CPo_Tr_6 class
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
#include "Dr_Tr_6.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Tr_6.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Tr_6

IMPLEMENT_DYNAMIC(CPo_Tr_6,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Tr_6,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Tr_6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Tr_6::CPo_Tr_6()
{  
    	
	m_ElTypeID			= "TR_6";
	m_ElTypeNum			= TR_6;
	///////////////////////////////
	m_ElDegree			= ED_QUADRATIC;
	m_nEdgeDegree[0]	= 2;
	////////////////////////////
	 
} 
	
int CPo_Tr_6::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Tr_6* pNewObj = new CDr_Tr_6;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Tr_6* pNewObj	= (CDr_Tr_6*)(pMsObjMgr->AddToDataBase(nQIndex,TR_6));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,TR_6);	
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_3((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Tr_6::Post_FE2D\nPost_FE2D_3");
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

int CPo_Tr_6::SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType)
{

	CDr_Tr_6* pNewObj		= (CDr_Tr_6*)pFE2D;
	//////////////
	int			i;
	//////////////////////////////////////////////////////////////////////// Create Vertices 
	CMsMath	MsMath;
	WORLD	NewPos;
	CString	Nid;
	/////////////////////
    for(i=0;i<3;i++)
    {
		///////////////////////////////////////////////////////// Coords
		MsMath.Add3DPts(&LocalPos[i],&LocalPos[(i+1)%3],&NewPos);
		MsMath.Scale3DPts(0.5,&NewPos);
		///////////////////////////////
		EachAddlNodeInfo(pFE2D,&NewPos,pMesh,nGenType);
  	}	
	///////////////////////
	return 0;
}

int CPo_Tr_6::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)TR_6);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(6);		
	pNewObj->SetnCorners(3);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(3);			// Bounding Edges
	pNewObj->SetnEdgeNodes(6);		
	pNewObj->SetElDegree(ED_QUADRATIC);
	pNewObj->SetEdgeDegrees(2,0);
	pNewObj->SetEdgeDegrees(2,1);
	pNewObj->SetEdgeDegrees(2,2);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
