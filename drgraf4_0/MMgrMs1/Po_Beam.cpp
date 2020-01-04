// CPo_Beam.cpp : implementation of the CPo_Beam class
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
#include "Po_Beam.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Beam

IMPLEMENT_DYNAMIC(CPo_Beam,CPo_FE1D)
/*
BEGIN_MESSAGE_MAP(CPo_Beam,CPo_FE1D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Beam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Beam::CPo_Beam()
{
	m_ElTypeID			= "BEAM";
	m_ElTypeNum			= BEAM;
}
	
int CPo_Beam::Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	// UINT nGenType = MESH1D or MESH2D or MESH3D
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	////////////////////////////////// Create
	int nQIndex;
	CDrBeam* pNewObj	= (CDrBeam*)(pMsObjMgr->AddToDataBase(nQIndex,BEAM));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString EdgeID;
	SetElemInfoID(EdgeID,BEAM);		
	/////////////////////////// save
	m_ElNumID = EdgeID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE1D((CDrFE1D*)pNewObj,pMesh,nGenType,pVert,LocalPos,EdgeID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Beam::Post_FE1D_Elem\nPost_FE1D");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	Fill_Data_MeshObjs((CDrFE1D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Beam::Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)BEAM);
	pNewObj->SetElemType((int)MESH_OBJECT);              // globals.h
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			// globals
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE1D Specific
	FillData_1D((CDrFE1D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Beam Specific Data
	((CDrBeam*)pNewObj)->SetKNodeID(m_KNodeID);
	///
	return 0;
}
////////////////////////////////////////// end of module //////////////////
