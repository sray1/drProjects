// Mouse.cpp : implementation file
//


#include "stdafx.h"

#include "glb_Objs.h"
#include "glb_type.h"
//////////////////// 
#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// Element Defn
#include "Def_IGen.h"
/////////////////////
#include "MP_Post.h" 

#include "MI_Pat_P.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Pat_P,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Pat_P::CMI_Pat_P()
{
}

CMI_Pat_P::~CMI_Pat_P()
{
}
//////////////////////////////////////////////////////////// Posting 
int CMI_Pat_P::LBUpPatchPost()
{


	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CMP_Post	MP_Post;
	m_pDrPatch = MP_Post.GoDoIt();
	if(!m_pDrPatch)
		return -1;
	//////////////////////////////////////////////////////////
	CString PatchID	= m_pDrPatch->GetObjectID();
	pDListMgr 		= pObjectMgr->GetObjectList(PATCH);
	int nPatchIndex = pDListMgr->GetObjectIndex(PATCH,PatchID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nPatchIndex);
	pObjectMgr->SetActiveObjectType(PATCH);
 	///////////////////////////////////////////////////////// show Patch
	m_pDrPatch->SetDirty(FALSE);
	m_pDrPatch->SetPosted(TRUE);
	m_pDrPatch->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nPatchIndex,PATCH);
	/////////////////////
	return 0;		 
}
////////////////////////////////////////////////////////////
void CMI_Pat_P::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MI_PAT_P:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" MI_PAT_P:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		




