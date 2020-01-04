// CPo_Pipe.cpp : implementation of the CPo_Pipe class
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
//#include "DrMesh2D.h"
///////////////////
#include "Po_Pipe.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_Pipe

IMPLEMENT_DYNAMIC(CPo_Pipe,CPo_FE1D)
/*
BEGIN_MESSAGE_MAP(CPo_Pipe,CPo_FE1D)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_Pipe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
CPo_Pipe::CPo_Pipe()
{
	m_ElTypeID			= "PIPE";
	m_ElTypeNum			= PIPE;
}

	
int CPo_Pipe::Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos)
{
	// UINT nGenType = MESH1D or MESH2D or MESH3D
	//////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	////////////////////////////////// Create
	int nQIndex;
	CDrPipe* pNewObj	= (CDrPipe*)(pMsObjMgr->AddToDataBase(nQIndex,PIPE));
	///////////////////////////////////////////////////////////////// NOT Ready
	pNewObj->SetShow(FALSE);// not quite ready
	///////////////////////////////////////////////////////////////// Elem ID
	CString EdgeID;
	SetElemInfoID(EdgeID,PIPE);		
	/////////////////////////// save
	m_ElNumID = EdgeID;
	///////////////////////////////////////////////////////////////// Go Post
	int nResult = Post_FE1D((CDrFE1D*)pNewObj,pMesh,nGenType,pVert,LocalPos,EdgeID);		
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCPo_Pipe::Post_FE1D_Elem\nPost_FE1D");
		return -1;
	}
	///////////////////////////////////////////////////////////////// Element-Specific Info
	Fill_Data_MeshObjs((CDrFE1D*)pNewObj,pMesh,nGenType);		
	///////////////////////////////////////////////////////////////// NOW Ready
	pNewObj->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_Pipe::Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType)		
{
	////////////////////////////////// Object Specific Data
	pNewObj->SetObjectType((int)PIPE);
	pNewObj->SetElemType((int)MESH_OBJECT);              // globals.h
	pNewObj->SetLevelType((int)LEVEL_KIDDO);			// globals
	pNewObj->SetObjectID(m_ElNumID);			
	////////////////////////////////// FE1D Specific
	FillData_1D((CDrFE1D*)pNewObj,pMesh,nGenType);
	////////////////////////////////// Pipe Specific Data
	((CDrPipe*)pNewObj)->SetValve(m_bValve);
	((CDrPipe*)pNewObj)->SetSIid(m_SIid[0],0);
	((CDrPipe*)pNewObj)->SetSIid(m_SIid[1],1);
	///
	return 0;
}
////////////////////////////////////////// end of module //////////////////
