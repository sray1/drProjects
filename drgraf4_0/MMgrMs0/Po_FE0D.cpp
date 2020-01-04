// CPo_FE0D.cpp : implementation of the CPo_FE0D class
//

#include "stdafx.h"

#include "drgraf.h"
#include "UserMsg.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "MI_Gang0.h"
///////////////////
#include "Po_FE0D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_FE0D

IMPLEMENT_DYNAMIC(CPo_FE0D,CObject)
/*
BEGIN_MESSAGE_MAP(CPo_FE0D,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_FE0D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/


int CPo_FE0D::SetElemInfoID(CString& ElemID,UINT nElemType)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////// 
	char buf[50];
	/////////////////////////////
	pMsObjMgr->BumpLastMeshNo(nElemType);					// bump it
    int nLastNum	= pMsObjMgr->GetLastMeshNo(nElemType);		// internal
	sprintf(buf,"%d",nLastNum);
	ElemID	= "";
	ElemID	+= buf;
	///
	return 0;
}

int CPo_FE0D::FillData_0D(CDrFE0D* pNewObj,CDrObject* pMesh,UINT nGenType)
{

	//////////////////////////////////
	pNewObj->SetElNumID(m_ElNumID);	
	pNewObj->SetElTypeID(m_ElTypeID);			// TRUSS,BEAM,PIPE etc
	pNewObj->Setrid(m_rid_0);//
	pNewObj->Setpid(m_pid);  
	pNewObj->Setmid(m_mid);  
	//////////////////////////////////
	pNewObj->SetElNum(m_ElNum);				// Element Number
	pNewObj->SetElTypeNum(m_ElTypeNum);			// id Number: Element Type
	pNewObj->Setrel(m_rel_0); 
	pNewObj->Setprop(m_prop);           //
	pNewObj->Setmat(m_mat);           //
	/////////////////////////
	pNewObj->SetRefTemp(m_refTemp);				//RefrenceTemperature
	////////////////////////////// 
	pNewObj->SetCardNo(m_nCardNo);
	////////////////////////////// Genetics
//	pNewObj->SetGenObjType(nGenType);	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//	pNewObj->SetGenObj(pMesh);
		CMI_Gang0 MI_Gang0;
		int nResult = MI_Gang0.ReciprocateElemMeshList(pNewObj, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	////////////////////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////
