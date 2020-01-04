// CPo_Qu_4.cpp : implementation of the CPo_Qu_4 class
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
#include "Dr_Qu_4.h"
///////////////////
#include "MI_Gang2.h"
#include "Po_Qu_4.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Qu_4

IMPLEMENT_DYNAMIC(CPo_Qu_4,CPo_FE2D)
/*
BEGIN_MESSAGE_MAP(CPo_Qu_4,CPo_FE2D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Qu_4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Qu_4::CPo_Qu_4()
{  
    	
	m_ElTypeID			= "QU_4";
	m_ElTypeNum			= QU_4;
	///////////////////////////////
	m_ElDegree			= ED_LINEAR;
	m_nEdgeDegree[0]	= 1;
	////////////////////////////
	 
} 
	
int CPo_Qu_4::Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////////////// Create
//	CDr_Qu_4* pNewObj = new CDr_Qu_4;
	////////////////////////////////// Create
	int nQIndex;
	CDr_Qu_4* pNewObj	= (CDr_Qu_4*)(pMsObjMgr->AddToDataBase(nQIndex,QU_4));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString FaceID;
	SetElemInfoID(FaceID,QU_4);		
	/////////////////////////// save
	m_ElNumID = FaceID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE2D_4((CDrFE2D*)pNewObj,pMesh,nGenType,pVert,LocalPos,FaceID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Qu_4::Post_FE2D\nGang2.Post_FE2D_4");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	Fill_Data_MeshObjs((CDrFE2D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Qu_4::Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)QU_4);
	pNewObj->SetElemType((int)EL2D_OBJECT);              
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE2D Specific
	FillData_2D((CDrFE2D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elem Specific
	pNewObj->SetObjectID(m_ElNumID);			
	pNewObj->SetnNodes(4);		
	pNewObj->SetnCorners(4);		// 3 = Triangle/ 4 = Quadrilateral
	pNewObj->SetnEdges(4);			// Bounding Edges
	pNewObj->SetnEdgeNodes(4);		
	pNewObj->SetElDegree(ED_LINEAR);
	pNewObj->SetEdgeDegrees(1,0);
	pNewObj->SetEdgeDegrees(1,1);
	pNewObj->SetEdgeDegrees(1,2);
	pNewObj->SetEdgeDegrees(1,3);
	/////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
