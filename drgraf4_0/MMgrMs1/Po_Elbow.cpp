// CPo_Elbow.cpp : implementation of the CPo_Elbow class
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
///////////////////
#include "Po_Elbow.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Elbow

IMPLEMENT_DYNAMIC(CPo_Elbow,CPo_FE1D)
/*
BEGIN_MESSAGE_MAP(CPo_Elbow,CPo_FE1D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Elbow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Elbow::CPo_Elbow()
{
	m_ElTypeID			= "ELBOW";
	m_ElTypeNum			= ELBOW;
}
	
int CPo_Elbow::Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	// UINT nGenType = MESH1D or MESH2D or MESH3D
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	////////////////////////////////// Create
	int nQIndex;
	CDrElbow* pNewObj	= (CDrElbow*)(pMsObjMgr->AddToDataBase(nQIndex,ELBOW));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString EdgeID;
	SetElemInfoID(EdgeID,ELBOW);		
	/////////////////////////// save
	m_ElNumID = EdgeID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE1D((CDrFE1D*)pNewObj,pMesh,nGenType,pVert,LocalPos,EdgeID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Elbow::Post_FE1D_Elem\nPost_FE1D");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	Fill_Data_MeshObjs((CDrFE1D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Elbow::Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)ELBOW);
	pNewObj->SetElemType((int)MESH_OBJECT);              // globals.h
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			// globals
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE1D Specific
	FillData_1D((CDrFE1D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Elbow Specific Data
	((CDrElbow*)pNewObj)->SetSIid(m_SIid[0],0);
	((CDrElbow*)pNewObj)->SetSIid(m_SIid[1],1);
	///
	((CDrElbow*)pNewObj)->SetCCID(m_CCID);
	((CDrElbow*)pNewObj)->SetTIID(m_TIID);
	((CDrElbow*)pNewObj)->SetCAID(m_CAID);
	((CDrElbow*)pNewObj)->SetCBID(m_CBID);
	///
	return 0;
}
////////////////////////////////////////// end of module //////////////////
