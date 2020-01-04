// drawview.cpp : implementation of the CDrawView class         BASE Class
//


#include "stdafx.h"

 
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
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
//////////////////////
#include "PR_Wire0.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPR_Wire0, CObject)
/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CPR_Wire0::AssertValid() const
{
}

void CPR_Wire0::Dump(CDumpContext& dc) const
{
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
CPR_Wire0::CPR_Wire0(BOOL bParallel,int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin, double dScale_U,double dScale_V)
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
						
void CPR_Wire0::RenderReadySCENE(CDC* pDC)
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
		if(nElemType<0)		// Not Viewable
			continue;
		/////////////////////////////////////////// Transform/Project
		int nObjType	= pObject->GetObjectType();
		RenderReadyOBJECT(pDC,pObject,nObjType);
		///////////////////////
	}
	/////////////
	
}

void CPR_Wire0::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjectType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
    int nElemType = pObject->GetElemType();
    /////////////
    if (nElemType == (int)DRAW_OBJECT)
    {
		pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V);
       	///////////////////////////////////
	}	
	else 												
	{
		////////////////////////////////////////////// Coordinates XForm
													// Local->World	
		MATRIX LM;
		BOOL bXForm = FALSE;
		///////////////////////////////////////////
		pObject->TransformObjectToWorld(&LM,bXForm);
		/////////////////////////////////////////////// Xform/Clip/Project
		pObject->TransformObjectToView(&m_ViewM); 
		
		pObject->ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
		///////////////////////////////////
	}
	/////////////////////////////////////////////END/// Compute Bounding Rect

}
///////////////////////////// end of module //////////////////

