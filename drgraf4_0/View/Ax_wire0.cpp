/*
HCURSOR	API3D SetStatusCursor(HANDLE hInst,float percentage)
{
	HCURSOR	hc;

	if( percentage<0.125F )
		hc = LoadCursor( hInst, "CURS000" );
	else
	if( percentage<0.250F )
		hc = LoadCursor( hInst, "CURS012" );
	else
	if( percentage<0.375F )
		hc = LoadCursor( hInst, "CURS025" );
	else
	if( percentage<0.500F )
		hc = LoadCursor( hInst, "CURS037" );
	else
	if( percentage<0.625F )
		hc = LoadCursor( hInst, "CURS050" );
	else
	if( percentage<0.750F )
		hc = LoadCursor( hInst, "CURS062" );
	else
	if( percentage<0.875F )
		hc = LoadCursor( hInst, "CURS075" );
	else
	if( percentage<1.000F)
		hc = LoadCursor( hInst, "CURS087" );
	else
		hc = LoadCursor( hInst, "CURS100" );

	return SetCursor( hc );
}
*/
/*****************************************************************************
 *	File:		Wire0.cpp
 *
 *	Purpose:	WireFrame with Complexity Level = 0
 *
 *	ComplexityLevel:  0
 *
 *		SmartPainting					YES
 *
 *		Trivial Reject/Accept:		
 *				3DCulling				NO
 *						
 *
 *
 *	ASSUMPTIONS:
 *
 *		Object Measure					Centroid Level ( Not Pixel Level)
 *		Rendering:
 *			PatchLevel					NO
 *			PolygonalLevel				YES
 *		Clipping:
 *			Homogeneous 4D				NO
 *			3D Coordinates				NO
 *			PerspectiveTransformed
 *				to Parallel CVV for
 *				Z-Buffering				NO	
 *
 *****************************************************************************
 */
#include "stdafx.h"

#include "Def_Objs.h"
////////////////////
#include "DrGraf.h"
#include "DrGraDoc.h"
#include "AxObjMgr.h"
#include "DListMgr.h"
////////////////////////// ElementLevel
#include "Def_IGen.h"
////////////////////////// Temporarily: LABEL ShutOff
#include "Def_Draw.h"	//  			@ RenderStray
#include "DrLabel.h"
////////////////////////// Render
#include "Render.h"
#include "AX_Wire0.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAxWire_0

IMPLEMENT_DYNAMIC(CAxWire_0,CRender)
/*
BEGIN_MESSAGE_MAP(CAxWire_0,CRender)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CAxWire_0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
///////////////////
CAxWire_0::CAxWire_0()
{
}

CAxWire_0::CAxWire_0(CView* pView, BOOL bParallel,BOOL bNS[])
{
	/////////////////////////
	m_pView 		= pView;
	m_bParallel		= bParallel;
	////////////////////////////
//	m_pPR_Wire0		= pPR_Wire0;
	////////////////////////////// NoShow Controls			
	/////////////////////////// Objects			
	m_bNS_2DLabel 	= bNS[14];	
	m_bNS_3DLabel 	= bNS[15];	
	m_bNS_CNLabel 	= bNS[16];	
	m_bNS_CNode		= bNS[17];	
	m_bNS_NLabel	= bNS[18];	
	m_bNS_Node		= bNS[19];	
	m_bNS_CShape	= bNS[20];
	///////////////////////////
	m_bNS_Centroid	= bNS[22];
	/////////////////////////// Dirty	
	m_bNS_D_Curve	= bNS[26];
	/////////////////////////// Posted	
	m_bNS_P_Curve	= bNS[30];
	////////////////////////////// MeshNode
	m_bNS_MNLabel		= bNS[42];	
	m_bNS_MNode			= bNS[43];
}

int CAxWire_0::Init	(
						int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin, double dScale_U,double dScale_V,
						double dShrink
					)
{

	m_dShrink		= dShrink;
	//////////////////////////
    m_nView			= nView;   
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_ComposedM		= *pComposedM;	// Composed MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX
	m_VDir			= VDir;			// View Direction 
	//////////////////////////////////
	/////////
	return 0;
	/////////
}
/*****************************************************************************
 *
 *	Function:	RenderScene_Auxilliary()
 *
 *	Purpose:	Controls the process of rendering a Scene of Objects with
 *				groups of surface patches comprised of facets.
 *
 *
 *****************************************************************************
 */
int	CAxWire_0::RenderScene_AUXILLIARY(CClientDC* pDC,CRect& RectClip,int nActiveObjType,
							int nActiveObjIndex,int nViewNum)
{
	//////////////////////////////////////////////////////////////////
    //	RECALL:                                                 	//
    //		We're walking through THE List which contains:			//
    //					POSTED OBJ3D								//
    //					UNPOSTED PATCH (Dirty)						//
    //					UNPOSTED CURVE (Dirty)						//
    //					ALL Other ElemObjs							//
    //					ALL OTHER DrawObjs							// 
	//////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	///////////////////////////////////////////////
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound,RectClipLocal;
	RectClipLocal = RectClip;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	///////////////////////////////////////////////////////////////////////// Walk Thro' All Lists
	for(int iList=0;iList<MAX_LIST_ARRAY;iList++)
	{
		CDListMgr* pList = pObjectMgr->GetObjectListFromIndex(iList);	// 
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		///////////////////////////////////////////////////////////////////
		int iCount = 0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			iCount++;
			/////////////////////////////////////////////////////////////// ActiveLayer?
			int nObjectLayer	= pObject->GetLayer();
			int nCurrentLayer	= pLayer->GetCurrentLayer();
			////
			if(nObjectLayer != nCurrentLayer)
				continue;
			/////////////////////////////////////////////////////////////// Delete Mark?
			if( pObject->IsDeleted() )
				continue;
			/////////
			if(!(pObject->IsShow())|| (pObject->GetLevelType() == LEVEL_KIDDO) )
				continue;
			///////////////////////////////////////////	
			int nElemType = pObject->GetElemType();
			if (nElemType <0) 
				continue;  // not viewable
			//////////////////////////////////////////////// Draw THE Object
			long nObjNo  	= pObject->GetObjectNo();
			int nObjIndex  	= pList->GetObjectIndex(nObjNo);
			int nObjType  	= pObject->GetObjectType();
			BOOL bDirty		= pObject->IsDirty();
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
				continue;
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)NODE) && (m_bNS_Node && m_bNS_CNode))
				continue;
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			RenderReadyOBJECT(pDC,pObject,nObjType);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			//////////////////////////	
			if(!(RectInt.IntersectRect(&RectClipLocal, &RectBound)) )
				continue;
			//////////////////////////////////////////////// Is Selected
			BOOL bSelected = FALSE;
			if(nObjType == nActiveObjType && nObjIndex == nActiveObjIndex)
				bSelected = TRUE;
			//////////////////////////////////////////////////////////////
			switch ((UINT)nObjType)
			{

				case CURVE:
					//////////////////////////////////////////////// CURVE
					if( (bDirty && !m_bNS_D_Curve) )
					{
						///////////////////////
						pObject->SetControlShapeNeed(!m_bNS_CShape);
						pObject->DoDrawView(pDC, bSelected);
						///////////////////////
					}
					break;

				default:
					////////////////////////////////////// Individual Elements
					RenderSTRAY(pDC,pObject,bSelected,nViewNum);
					//////////////////////
					break;
			}
			////////// end switch
		}
		///////// end List of Specific Objects 
	}
	////////// end List of All Objects
	return 0;
}

int	CAxWire_0::RenderOBJECT
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pListS = pObject->GetSolidList();
	CDListMgr* pListP = pObject->GetPatchList();
	CDListMgr* pListC = pObject->GetCurveList();
	//////////////////////////////////////////// Solids									
//	if((!(pListS->IsEmpty())) && !m_bNS_P_Solid)								  									
	if(!pListS->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListS->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListS->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			pObject->SetControlShapeNeed(!m_bNS_CShape);
			pObject->DoDrawView(pDC, bSelected);
			///////////
		}
	}
	//////////////////////////////////////////// Posted Patches									
//	if((!(pListP->IsEmpty())) && !m_bNS_P_Patch)								  									
	//////////////////////////////////////////// Patches									
	if(!pListP->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListP->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListP->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			pObject->SetControlShapeNeed(!m_bNS_CShape);
			pObject->DoDrawView(pDC, bSelected);
			///////////
		}
	}
	//////////////////////////////////////////// Posted Curves									
//	if((!(pListC->IsEmpty())) && !m_bNS_P_Curve)								  									
	//////////////////////////////////////////// Posted Curves									
	if(!pListC->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListC->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListC->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();	// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			pObject->SetControlShapeNeed(!m_bNS_CShape);
			pObject->DoDrawView(pDC, bSelected);
			///////////
		}
	}
	/////////	
	return 0;
}

int CAxWire_0::RenderSTRAY(CClientDC* pDC,CDrObject* pObject,
							BOOL bSelected,int nViewNum)
{ 

	if(!(pObject->IsShow())|| (pObject->GetLevelType() == LEVEL_KIDDO) )
		return 0;
	///////////
	int nElemType = pObject->GetElemType();
    //////////////////////////////////// Zoom 
//    POINT ptZoom;
//    ptZoom.x = 1;
//    ptZoom.y = 1;
//    if (nViewNumber == VIEWISO)
//    		ScalebyZoomFactor(ptZoom,1,nViewNumber);
    //////////////////////////////////////////////// Draw THE Object
    if (nElemType <0) return -1;  // not viewable 
    //////////////////////////////////////////////// 
    int nObjType = pObject->GetObjectType();
 //   if((nObjType == LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
 //   	return 0;
    if(nObjType == NODE)
    {
    	CDrNode* pNode = (CDrNode*)pObject;
    	if(pNode->IsControlNode())
    	{
    	 	if(m_bNS_CNode)
    			return 0;
		}    			
		else 
		{   			
    	 	if(m_bNS_Node)
    			return 0;
    	}
    }
	/////////////////////////////////////////////// FE0D & MNode
/*
    if(nObjType == FE0D)
    {
    	CDrNode* pFE0D = (CDrFE0D*)pObject;
    	if(pFE0D->IsMeshNode())
    	{
    	 	if(m_bNS_MNode)
    			return 0;
		}    			
		else 
    	if(pFE0D->IsControlNode())
    	{
    	 	if(m_bNS_CNode)
    			return 0;
		}    			
		else 
		{   			
    	 	if(m_bNS_Node)
    			return 0;
    	}
    }
*/
    ////////////////////////////////////////////////	
    if (nElemType == (int)DRAW_OBJECT)
    {
		pObject->SetControlShapeNeed(!m_bNS_CShape);
		if(nObjType == GRID)
			pObject->DoDrawView(pDC,bSelected); 
		else
		if(nObjType == LABEL)
			RenderLabels(pDC,pObject,bSelected,nViewNum);
		else
			pObject->DoDrawView(pDC,bSelected,nViewNum); 
	}	
    else
//    if (nElemType == (int)ELEM_OBJECT)
	{
		pObject->SetControlShapeNeed(!m_bNS_CShape);
		pObject->DoDrawView(pDC,bSelected);
	}	
	////////////////////////////////////////////////
	return 0;   	
                               
}

int CAxWire_0::RenderLabels(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum)
{
  	CDrLabel* pLabel = (CDrLabel*)pObject;
	//////////////////////////////////////////////////////////////// Nodes
  	if(pLabel->GetType() == LABEL_NODE)
	{
    	CDrNode* pNode = (CDrNode*)pLabel->GetNodePtr();
		////////////////////////////////////////////////
    	if(pNode->IsControlNode())
    	{
			if(m_bNS_CNLabel)
				return 0;
		}    			
		else
    	if(pNode->IsMeshNode())
		{   			
    		if(m_bNS_MNLabel )
    			return 0;
    	}
		else 
		{   			
    		if(m_bNS_NLabel)
    			return 0;
    	}
		//////////////////////////////////////////// Draw
		pObject->DoDrawView(pDC,bSelected,nViewNum); 
	}
	else
    if(pLabel->GetType() == LABEL_SCREEN)
	{
		//////////////////////////////////////////// Draw
		pObject->DoDrawView(pDC,bSelected,nViewNum);
	}
	//////////////////////////////////////////////////////////////////
	return 0;
}

void CAxWire_0::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjectType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
    /////////////////////////////////////////////////////////////////////
/*    
    int nElemType = pObject->GetElemType();
    /////////////
    if (nElemType == (int)DRAW_OBJECT)
    {
*/ 
		if(!(pObject->IsShow()))
			return;
		////////////////////////	
//100197		int nObjType = pObject->GetObjectType();
		////////////////////////////////////// Posted Polygons 
//100197		if(nObjType == FE2D ||nObjType == FE3D)
		pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
									m_dzMin,m_dScale_U,m_dScale_V);
       	///////////////////////////////////
/*
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
*/	
	/////////////////////////////////////////////END/// Compute Bounding Rect

}
/////////////////////////// end of module ///////////////
/*
	if( !interrupted ) {
		if( needSort )
			DepthSort( pSFbase, nS );
		hDC = GetCurrentDC();
		pSF = pSFbase + nS;
		nF	= nS;
		if( nF > 100 )
			SetStatusCursor( ghInst, 0.0F );
		nP	= nS / 8;
		while( nS--  && !interrupted ) { // draw back to front
			RenderPolyFacet( hDC, pXF, --pSF, pL, bWireFrameOnly );
			if( nF > 100 )
				if( !(nS%nP) )
					SetStatusCursor( ghInst, (nF-nS)/(float)nF );
			interrupted = InterruptEvent();
		}
	}

*/
