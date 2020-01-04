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
#include "3DMath.h"
///////////////////// ElemObjs
#include "Eldefine.h"
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
#include "PR_Wire1.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPR_Wire1, CObject)
/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CPR_Wire1::AssertValid() const
{
}

void CPR_Wire1::Dump(CDumpContext& dc) const
{
}

#endif //_DEBUG
///////////////////////////////////////////////////////////////
CPR_Wire1::CPR_Wire1(BOOL bParallel,int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{
	m_bParallel		= bParallel;
    m_nView			= nView;
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_ComposedM		= *pComposedM;	// Composed MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX
	m_bCulling3D	= bCulling3D;	// if true BackFaceCulling in WorldSpace
	m_VDir			= VDir;			// View Direction
}
						
void CPR_Wire1::Init(CDListMgr* pSortList)
{
	m_pSortList = pSortList;
}
	
void CPR_Wire1::RenderReadySCENE(CDC* pDC)
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
		///////////////////////
	}
	/////////////
	
}

void CPR_Wire1::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
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
//		if(pObject->GetObjectType() != OBJ3D)
//			return;
		////////////////////////////////////////////// Coordinates XForm
													// Local->World	
    	MATRIX LM;
    	BOOL bXForm = FALSE;
		/////////////////////////////////////////// 
		pObject->TransformObjectToWorld(&LM,bXForm);
		////////////////////////////////////////////// Back-Face Culling
 		if( m_bCulling3D && (pObject->GetObjectType() == OBJ3D)  )
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
		pObject->TransformObjectToView(&m_ViewM);
		pObject->ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
		///////////////////////////////////
	}
	/////////////////////////

}

void CPR_Wire1::Corner_3Dto2D(CDrObject* pObject,int nObjectType)
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

///////////////////////////// end of module //////////////////

