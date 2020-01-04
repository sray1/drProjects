// CPo_FE1D.cpp : implementation of the CPo_FE1D class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// elements
#include "Def_Draw.h"
#include "DrLabel.h"
/////////////////////
#include "Def_Elem.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "MI_Gang0.h"
#include "MI_Gang1.h"
//#include "MI_Gang2.h"

#include "Po_FE1D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPo_FE1D

IMPLEMENT_DYNAMIC(CPo_FE1D,CPo_FE0D)
/*
BEGIN_MESSAGE_MAP(CPo_FE1D,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPo_FE1D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPo_FE1D::Post_FE1D(CDrFE1D* pAddEdge,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid)		
{
	//////////////////////////////////////
	// NEEDED for : Beam/Pipe/Truss/Elbow
	//////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	Make_CentroidLabel_EDGE(pAddEdge,LocalPos,Eid);
	///////////////////////////////////////////////////////////////////////////// Reciprocate/Info
	SetFE1DInfo(pAddEdge,pVert,pMesh,nGenType,2);
	//////////////////////////////////////// Now Ready
	pAddEdge->SetShow(TRUE);
	/////////
	return 0;
}

int CPo_FE1D::FillData_1D(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////
	pNewObj->SetElNumID(m_ElNumID);	
	pNewObj->SetElTypeID(m_ElTypeID);			// TRUSS,BEAM,PIPE etc
	pNewObj->Setline_id(m_line_id);;
	pNewObj->Setrid(m_rid[0],0);//
	pNewObj->Setrid(m_rid[1],1);//
	pNewObj->Setpid(m_pid);  
	pNewObj->Setmid(m_mid);  
	//////////////////////////////////
	pNewObj->SetElNum(m_ElNum);				// Element Number
	pNewObj->SetElTypeNum(m_ElTypeNum);			// id Number: Element Type
	pNewObj->Setline_no(m_line_no);;
	pNewObj->Setrel(m_rel[0],0); 
	pNewObj->Setrel(m_rel[1],1); 
	pNewObj->Setprop(m_prop);           //
	pNewObj->Setmat(m_mat);           //
	/////////////////////////
	pNewObj->Setnumseg(m_numseg);
	pNewObj->SetRefTemp(m_refTemp);				//RefrenceTemperature
	////////////////////////////// 
	pNewObj->SetCardNo(m_nCardNo);
	////////////////////////////// Genetics
//	pNewObj->SetGenObjType(nGenType);	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//	pNewObj->SetGenObj(pMesh);
	CMI_Gang0* pMI_Gang0;
		int nResult = pMI_Gang0->ReciprocateElemMeshList(pNewObj, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	////////////////////////////////////////////////////////////////////////////////	
	pNewObj->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pNewObj->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return 0;
}

int CPo_FE1D::SetFE1DInfo(CDrFE1D* pFE1D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,int nEnds)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Plat
	int			i;
	/////////////////////////////////////////
	CDListMgr*	pListV = pMesh->GetFE0DList();	// Mesh		vertex	list(Entire Pool)
	CDListMgr*	pList0 = pFE1D->GetFE0DList();	// element	vertex	list
	//////////////////////////////////////////////////////////////////////// Vertices 
    for(i=0;i<nEnds;i++)
    {
		//
		pList0->InsertObject(pVert[i]);
		///////////////////////////////////////////// Reciprocate
		pVert[i]->GetFE1DList()->InsertObject(pFE1D);
		//
	
  	}	
	//////////////////////////////////////////////////////////////////////// Edges 
	//////////////////////////////////////////////////////////////////////// Reciprocate
//	pFE1D->SetGenObjType(nGenType);
//	pFE1D->SetGenObj(pMesh);
		CMI_Gang0 MI_Gang0;
		int nResult = MI_Gang0.ReciprocateElemMeshList(pFE1D, pMesh, nGenType);
		if(nResult <0)
			return nResult;
	//
	pMesh->GetFE1DList()->InsertObject(pFE1D);			
	///////////////////////////////////////////////
	pFE1D->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pFE1D->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////
	return 0;
}

int CPo_FE1D::Make_CentroidLabel_EDGE(CDrFE1D* pEdge,pWORLD LocalPos,CString& Eid)
{
	///////////////////////////////////////////////////////////////////////////// Centroid Label Node
	WORLD		Centroid;
	CDrNode*	pCNLabel;	// Edge Label Control Node at Center
	////////////////////////////////////////
//	CMI_Gang1 Gang1;
//	Gang1.CalcCentroid_EDGE(LocalPos,&Centroid);
	//////////////////////////////////////////// coords
	CalcCentroid_EDGE(LocalPos,&Centroid);
	//////////////////////////////////////////// label
	pCNLabel = Make_CentroidLabel(Centroid,Eid);
	if(!pCNLabel)
		return -1;
	//////////////
	pCNLabel->SetCategory(CA_ELEMENT);
	pEdge->GetNodeList()->RemoveAll();	
	pEdge->GetNodeList()->InsertObject(pCNLabel);		// Post Generated Nodes
	//////////
	return 0;
}

CDrNode* CPo_FE1D::Make_CentroidLabel(WORLD& LocalPos,CString& Eid)		
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDrNode*	pCNLabel;	// Label Control Node at Center
	///////////////////////////////////// 
	CDrLabel*	pLabel;
	int nCNLabelIndex,nLabelIndex;
	nCNLabelIndex = -12345;	// Anyway
	///////////////////////////
	CMI_Gang0 Gang0;
	pCNLabel = Gang0.CreateFE0D(Eid,pLabel,LocalPos,TRUE,TRUE,FALSE,
							nCNLabelIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	///////////////////////////////////////////////////
	if(pCNLabel)
	{
		pCNLabel->GetLabelList()->InsertObject(pLabel);
		///////////////////////////////////////////////
		CDListMgr*  pDListMgr	= pObjectMgr->GetObjectList(LABEL);
		pLabel = (CDrLabel*)(pDListMgr->GetObject(nLabelIndex));
		pLabel->SetMeshElemType(m_ElTypeNum);
	}
	//
	return pCNLabel;	// 
	//////////////
}

void CPo_FE1D::CalcCentroid_EDGE(pWORLD Local,pWORLD pC)
{
	CMI_Gang1 Gang;
	/////////////////////////
	Gang.CalcCentroid(pC,Local,2);
	/////
}
////////////////////////////////////////// end of module //////////////////
