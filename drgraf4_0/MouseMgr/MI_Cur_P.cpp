// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "glb_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "EBoxmgr.h" 
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Msdefine.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "EDlgMgr.h"
//#include "Dlg_Node.h"  
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// DrawObjs
#include "drdefine.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "spdefine.h"
#include "drpen.h"
#include "Layer.h"
/*
#include "precison.h"
#include "mapfacto.h"
//#include "ScaleFac.h"
#include "DrFont.h"
*/
/////////////////////
#include "MI_Cur_P.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Cur_P,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Cur_P::CMI_Cur_P()
{
	m_pOut = NULL;
	for (int i=0;i<4;i++)
		m_pIn_S[i] = NULL;
	//////////////////////
	m_nCNodeDone   		= 0;
    /////////////////////////////////////////// Mesh/Patch
	m_CurrentPatchID	= "BLANK";
	m_nMaxPatchCNodes_S	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes_T	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
}

CMI_Cur_P::~CMI_Cur_P()
{
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	   
}
//////////////////////////////////////////////////////////// Posting 
int CMI_Cur_P::LBUpCurvePost()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////
	m_pDrPatch 		= Post_GetInfo();// PGen Dialog
	if(!m_pDrPatch)		// cancel
		return -1;
	//////////////////////////////////	
	PostNodes_FWD();							// ControlNode Mesh
	/////////////////
	if(PostMeshInfo_FWD()<0)
		return -1;
	//////////////////////////////////////////////////////////
	CString PatchID	= m_pDrPatch->GetObjectID();
	pDListMgr		= pObjectMgr->GetObjectList(PATCH);
	int nPatchIndex = pDListMgr->GetObjectIndex(PATCH,PatchID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nPatchIndex);
	pObjectMgr->SetActiveObjectType(PATCH);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nPatchIndex,PATCH);
	/////////////////////
	return 0;		 
}
///////////////////////////////////// end of Module //////////////////////		


