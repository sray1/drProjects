// drawview.cpp : implementation of the CDrawView class         BASE Class
//


#include "stdafx.h"
//#include <stdlib.h>
//#include <math.h>

 
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
//#include "viewrsrc.h"                     		// resource
////////////////////////////////////////////////// toolboxes
//#include "drgrafrm.h"
//#include "dbebextn.h"         
/////////////////////
#include "ObjMgr.h"
//#include "dListMgr.h"
#include "DrObject.h"
///////////////////// DrawOperationObjs
#include "3Ddefine.h"
#include "XForm.h"
#include "DrClip.h"
#include "3DMath.h"
///////////////////// ElemObjs
#include "Eldefine.h"
#include "DrPlate.h"
///////////////////// DrawObjs
#include "drdefine.h"
#include "DrLabel.h"
/*
///////////////////// SpecObjs
#include "Spdefine.h"
#include "SDlgMgr.h"
#include "MapFacto.h"
#include "Precison.h"
//////////////////////
*/
//#include "RNGlobal.h"
//#include "RN_Wire0.h"
//#include "RN_Wire1.h"
////////////////////// 
#include "Render.h"
#include "PR_Wire2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPR_Wire2, CObject)
/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CPR_Wire2::AssertValid() const
{
}

void CPR_Wire2::Dump(CDumpContext& dc) const
{
}

#endif //_DEBUG
///////////////////////////////////////////////////////////////
CPR_Wire2::CPR_Wire2(BOOL bParallel,int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dScale_U,double dScale_V)
{
	m_bParallel		= bParallel;
    m_nView			= nView;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_ComposedM		= *pComposedM;	// Composed MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX
	m_bCulling3D	= bCulling3D;	// if true BackFaceCulling in WorldSpace
	m_VDir			= VDir;			// View Direction
}
						
void CPR_Wire2::Init(CDListMgr* pSortList,double dzMin,BOOL bCanonClip)
{
	m_pSortList = pSortList;
	m_dzMin		= dzMin;
	m_bCanon	= bCanonClip;
}
	
void CPR_Wire2::RenderReadySCENE(CDC* pDC)
{
	// We are not done with LABEL & FREEHAND; so deal differently
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	CDListMgr* pList = pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////////////////////	
		int nElemType	= pObject->GetElemType();
		if(nElemType<0 || (pObject->GetLevelType() != LEVEL_GRAPA) )// Not Viewable
			continue;                                         // Not OBJ3D Level
		/////////////	
		int nObjType  	= pObject->GetObjectType();
		/////////////////////////////////////////// Transform/Project
		RenderReadyOBJECT(pDC,pObject,nObjType);
	}
	///////////////////////////////////////////////////////// DepthSort
	CRender Render;
	if(!(m_pSortList->IsEmpty())  )
		Render.DepthSort(m_pSortList,FALSE);	// FALSE = Descending Order in z depth
	/////////////////////////////////	
	
}

void CPR_Wire2::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
    MATRIX LM;
    BOOL bXForm;
	////////////////////// Label needs to set dc(FONT) temporarily
	if(nObjType == LABEL || nObjType == FREEHAND)
	{
		if(nObjType == LABEL)
		{
			CDrLabel* pLabel = (CDrLabel*) pObject;
			if((pLabel->GetType()) == LABEL_NODE)
		 		if (!(pLabel->IsMoved()) ) 
					/////////////////////////////////////// Xform & Project
					Corner_3Dto2D(pObject,nObjType);
					//////////////////////// 
			pObject->FinishObject((CClientDC*)pDC,m_nView);//	calc Bounding Rect for the view
       	    ///////////////////////////////////////
       	    return;
		}	
		else if(nObjType == FREEHAND)
		{ 
			pObject->FinishObject(m_nView);     	//	calc Bounding Rect for the view 
       	    ///////////////////////////////////
			return;
		}	
	}	
	else 											// 	
	{
		//////////////////////////////////////////////////////////////// ONLY GRAPAs
		if(pObject->GetLevelType() != LEVEL_GRAPA)
			return;
		////////////////////////////////////////////// Coordinates XForm
													// Local->World	
//		if(pObjectMgr->IsSceneChanged())
//		{
			bXForm = FALSE;
			///////////////////////////////////////////////////// OBJ3D
			if((nObjType == OBJ3D) && (pObject->IsInstanced()) )
			{
				bXForm = TRUE;
				((CDrObj3D*)pObject)->GetLocalTransform(&LM);
			}	
			/////////////////////////////////////////// 
			pObject->TransformObjectToWorld(&LM,bXForm);
			///////////////////////////////////////////
//			pObjectMgr->SetSceneChanged(FALSE);
//		}
 		////////////////////////////////////////////// Back-Face Culling
 		if(m_bCulling3D && (nObjType == OBJ3D)  )
 		{
 			//////////////////////////////////////// Posted Solid/Patch/Curve
 			// BACKFACE CULLing Only for SOLIDs & PATCHes
 			// 		with 2D or 3D Components
 			//////////////////////////////////////////////
			BOOL bCulled = 	pObject->RemoveHiddenObject(&m_ViewM,m_VDir,1);
			////////////
			if(bCulled)
				return;
	
		}		
		/////////////////////////////////////////////// Xform & Project
		int doNothing;
		// other LEVEL_GRAPA such as NODE,CNODE etc
 		if(nObjType == OBJ3D )
 			doNothing = 1; // do nothing
		pObject->TransformObjectToView(&m_ViewM);
		pObject->ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
		//////////////////////////////////////// SetUp SortList for Patches&Solids
 		if(nObjType == OBJ3D )
			SortReadyOBJECT(pObject);
		/////////////////////////
	}
	/////////////////////////

}

void CPR_Wire2::Corner_3Dto2D(CDrObject* pObject,int nObjectType)
{ 
    
    int		nMax, nPrecision, index;
	long 	lCoord[3];
	POINT 	pt;
	////////////////////////////////
	nMax = pObject->GetMaxCorners();
	////////////////////////////////////////////// Get point 
	WORLD ptIn,ptOut;
	/////////////////
    for( int i = 0; i<nMax; i++)              // fill up m_pt[]
    {
   		///////////////////////////////////////////// get Raw Pt.
   		pObject->GetRawCoords(lCoord, &nPrecision, i);
		///////////////////////////////////////////// 
		ptIn.x = (double)lCoord[0];
		ptIn.y = (double)lCoord[1];
		ptIn.z = (double)lCoord[2];
		//////////////////////////////////////// Transform
		CXForm XForm(m_bParallel);

		XForm.Transform(&ptIn,&ptOut,&m_ComposedM);
		//////////////////////////////////////// Project
		XForm.Project(&m_vv3DM,&ptOut,&ptIn);
		//////////////////////////////////////// Logical
		pt.x = (int)(ptIn.x * m_dScale_U);
		pt.y = (int)(ptIn.y * m_dScale_V);
		///////////////////////////////////////////// Set 2D pt. back
		index = i;
		//////////
		if(nObjectType == LABEL)// find index based on viewnumber
		{                       // because of NodeLabel Complexity
			if(m_nView == VIEW12)
				index = 0;
			else	
			if(m_nView == VIEW23)
				index = 1;
			else	
			if(m_nView == VIEW31)
				index = 2;
			else	
			if(m_nView == VIEWISO)
				index = 3;
		}
		//////////////////////////////////////	save
		pObject->SetProjectedCoords(pt,index);
		////////////////////////////////////// 
	}	
	///////
	return; 
	
} 

int	CPR_Wire2::SortReadyOBJECT(CDrObject* pObj3D)
{

	//////////////////////////////////////////// Obj3D
	CDListMgr* pList;
	//////////////////////////////////////////// Posted Patches									
	pList = pObj3D->GetPatchList();
	////////////////////////////////
	if(!(pList->IsEmpty()))								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			//////////////////////
			if(pObject->IsCulled())
				continue;
			////////////////////////
			SortReadyPATCH(pObject);
			///////////
		}
	}
	//////////////////////////////////////////// Posted Solids									
	pList = pObj3D->GetSolidList();
	////////////////////////////////
	if(!(pList->IsEmpty()))								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			//////////////////////
			if(pObject->IsCulled())
				continue;
			////////////////////////
			SortReadySOLID(pObject);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CPR_Wire2::SortReadySOLID(CDrObject* pSolid)
{

	//////////////////////////////////////////// Obj3D
	CDListMgr* pList;
	//////////////////////////////////////////// Posted Elems									
	pList = pSolid->GetElemList();
	////////////////////////////////
	if(!(pList->IsEmpty()))								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			//////////////////////
			if(pObject->IsCulled())
				continue;
			//////////////////////// LOOP over polys **** todo*****
//			SortReadyPoly(pObject);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CPR_Wire2::SortReadyPATCH(CDrObject* pPatch)
{

	CDrClip Clip(m_dzMin,!m_bParallel,m_bCanon);
	//////////////////////////////////////////// Patch
	CDListMgr* pList;
	//////////////////////////////////////////// Posted Elems									
	pList = pPatch->GetElemList();
	////////////////////////////////
	if(!(pList->IsEmpty()))								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			//////////////////////
			
			if(pObject->IsCulled()||(pObject->GetObjectType() != PLATE))
				continue;
			//////////////
			CDrPlat* pPlate = (CDrPlat*)pObject; 
			WORLD Centroid = *(pPlate->GetCentroidEye() ); // transformed
			///////////                                   
			if(Clip.ClipPt(&Centroid) == NOT_VISIBLE)
				continue;
			/////////////////////////////////// Put in the List
			m_pSortList->InsertObject(pObject); 
			/////////////	
		}
	}
	/////////	
	return 0;
}


///////////////////////////// end of module //////////////////

