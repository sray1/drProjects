// CPo_Tr_3.cpp : implementation of the CPo_Tr_3 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
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
#include "Dr_Tr_3.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Tr_3.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Tr_3

IMPLEMENT_DYNAMIC(CPo_Tr_3,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Tr_3,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Tr_3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Tr_3::CPo_Tr_3()
{  
    	
	m_ElTypeID			= "TR_3";
	m_ElTypeNum			= TR_3;
	///////////////////////////////
	m_ElDegree			= ED_LINEAR;
	m_nEdgeDegree[0]	= 1;
	////////////////////////////
	 
} 
	
int CPo_Tr_3::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Tr_3* pNewObj = new CDr_Tr_3;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Tr_3* pNewObj	= (CDr_Tr_3*)(pMsObjMgr->AddToDataBase(nQIndex,TR_3));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,TR_3);	
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_3((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Tr_3::Post_FE2D\nPost_FE2D_3");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	Fill_Data_MeshObjs((CDrFE2D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Tr_3::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)TR_3);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(3);		
	pNewObj->SetnCorners(3);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(3);			// Bounding Edges
	pNewObj->SetnEdgeNodes(3);		
	pNewObj->SetElDegree(ED_LINEAR);
	pNewObj->SetEdgeDegrees(1,0);
	pNewObj->SetEdgeDegrees(1,1);
	pNewObj->SetEdgeDegrees(1,2);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
