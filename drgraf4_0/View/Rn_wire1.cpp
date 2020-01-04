/*****************************************************************************
 *	File:		Wire1.cpp
 *
 *	Purpose:	WireFrame with Complexity Level = 1
 *
 *	ComplexityLevel:  1
 *
 *		SmartPainting					YES		*
 *
 *		Trivial Reject/Accept:		
 *				3DCulling				YES		*
 *						
 *		HiddenSurfaceRemoval:
 *			Object-Precision:       
 *				CentroidClip			NO						
 *				2DCulling				NO
 *			Image-Precision:
 *				DepthSort				NO						
 *				Z-Buffer				NO
 *
 *		AntiAliasing					NO
 *						
 *		LightEffect
 *			Local:						NO
 *				Reflection:
 *					Gouraud				NO
 *					Phong				NO
 *					TorranceCook		NO					
 *					Ambient				NO
 *					Diffusion			NO
 *					Specular			NO
 *				Transmission:
 *					Transparency		NO
 *				Refraction				NO
 *			Global:
 *				RayTracing				NO				
 *				Radiosity				NO
 *				
 *		DistanceEffect					NO
 *
 *		AtmosphericEffect:				
 *				Hazing					NO
 *				Turbulence				NO
 *
 *		TextureEffect:				
 *				Noise					NO
 *				Bump					NO
 *				3DMap					NO
 *				2DMap: Picture			NO
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
#include "ObjMgr.h"
#include "DListMgr.h"
////////////////////////// StaticLoads
#include "Def_StaL.h"
////////////////////////// SupportLevel
#include "Def_Supp.h"
#include "DrLinSup.h"		// DrLinSup
////////////////////////// ElementLevel
#include "Def_IGen.h"
#include "Def_Elem.h"	// 
#include "DrFE0D.h"		// DrFE0D
#include "DrFE1D.h"		// DrFE1D
#include "DrFE2D.h"		// DrFE2D
#include "DrPatch.h"		// for Patch
#include "DrSolid.h"		// for Solid
#include "DrProf_C.h"		// for Profile_C
#include "MatObj.h"		// for Profile_C
////////////////////////// Temporarily: LABEL ShutOff
#include "Def_Draw.h"	//  			@ RenderStray
#include "DrLabel.h"
////////////////////////// Render
#include "Render.h"
#include "RN_Wire1.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CWire_1

IMPLEMENT_DYNAMIC(CWire_1,CRender)
/*
BEGIN_MESSAGE_MAP(CWire_1,CRender)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CWire_1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
///////////////////
CWire_1::CWire_1()
{
	m_bMeshScene = FALSE;
}

CWire_1::CWire_1(
					CDrawView* pView, RENDITION rend, BOOL bParallel,
					BOOL bNS[],BOOL bNSEL[],BOOL bNSLE[]
				)
{
	/////////////////////////
	m_pView 		= pView;
	m_Rendition		= rend;		//Rendering Method
	m_bParallel		= bParallel;
	////////////////////////////
//	m_pPR_Wire0		= pPR_Wire0;
	////////////////////////////// NoShow Controls			
	int i;
	//////
	for (i=0;i<MAX_NOSOEL;i++)
		m_bNoSoEL[i] = bNSEL[i];
	for (i=0;i<MAX_NOSOLABEL;i++)
		m_bNoSoLabEL[i] = bNSLE[i];
	/////////////////////////// View Controls	
	m_bNS_CVV		= bNS[0];
	m_bNS_VV		= bNS[1];
	m_bNS_VRP		= bNS[2];
	m_bNS_PRP		= bNS[3];
	m_bNS_VUP		= bNS[4];
	m_bNS_VPN		= bNS[5];
	m_bNS_CW		= bNS[6];
	m_bNS_VPlane	= bNS[7];
	m_bNS_VDIR		= bNS[8];
	m_bNS_WC		= bNS[9];
	m_bNS_VRC		= bNS[10];
	m_bNS_NPC		= bNS[11];
	m_bNS_Front		= bNS[12];
	m_bNS_Back		= bNS[13];
	/////////////////////////// Objects			
	m_bNS_2DLabel 	= bNS[14];	
	m_bNS_3DLabel 	= bNS[15];	
	m_bNS_CNLabel 	= bNS[16];	
	m_bNS_CNode		= bNS[17];	
	m_bNS_NLabel	= bNS[18];	
	m_bNS_Node		= bNS[19];	
	m_bNS_CShape	= bNS[20];
	///////////////////////////
	m_bNS_Normal	= bNS[21];
	m_bNS_Centroid	= bNS[22];
	/////////////////////////// Dirty	
	m_bNS_D_Object	= bNS[23];			
	m_bNS_D_Solid	= bNS[24];	
	m_bNS_D_Patch	= bNS[25];	
	m_bNS_D_Curve	= bNS[26];
	/////////////////////////// Posted	
	m_bNS_P_Object	= bNS[27];			
	m_bNS_P_Solid	= bNS[28];	
	m_bNS_P_Patch	= bNS[29];	
	m_bNS_P_Curve	= bNS[30];
	////////////////////////////
	m_bNS_D_Profile_S = bNS[31]; 
	m_bNS_D_Profile_P = bNS[32]; 
	m_bNS_D_Profile_C = bNS[33]; 
    ////////////////////////////
	m_bNS_P_Profile_S = bNS[34]; 
	m_bNS_P_Profile_P = bNS[35]; 
	m_bNS_P_Profile_C = bNS[36]; 
	////////////////////////////
	m_bNS_RIGID			= bNS[37]; 
	m_bNS_Lin_Spring	= bNS[38]; 
	m_bNS_Lin_Snubber	= bNS[39]; 
	m_bNS_Non_Spring	= bNS[40]; 
	m_bNS_Non_Snubber	= bNS[41];
	////////////////////////////// MeshNode
	m_bNS_MNLabel		= bNS[42];	
	m_bNS_MNode			= bNS[43];	
	////////////////////////////// StaticLoad
	m_bNS_Force			= bNS[44];	
	m_bNS_Displace		= bNS[45];
	m_bNS_Pressure		= bNS[46];
	m_bNS_Thermal		= bNS[47];
	m_bNS_LumpWt		= bNS[48];
}

int CWire_1::Init	(
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
	m_bCulling3D	= bCulling3D;	// if true BackFaceCulling in WorldSpace
	m_VDir			= VDir;			// View Direction 
	//////////////////////////////////
	m_bCullWorld	= m_bCulling3D;
	m_bShadowOn		= FALSE;
	m_bAntiAliasOn	= FALSE;
	m_bNeedSort		= FALSE;	// for depthsort
//	m_bAscending;	// for depthsort
//	m_dHither;		//Canonical View Volume
//	m_dYon;
	/////////////////////////
//	m_Textures;

	m_pZB			= NULL;
	m_pScanSpan		= NULL;	// for Full Rendition
	m_pRA			= NULL;
	m_pLE			= NULL;
	/////////////////////////
	m_pPolyList		= NULL;	// active ones for Shadow
	/////////
	return 0;
	/////////
}
/*****************************************************************************
 *
 *	Function:	RenderScene()
 *
 *	Purpose:	Controls the process of rendering a Scene of Objects with
 *				groups of surface patches comprised of facets.
 *
 *
 *****************************************************************************
 */
int	CWire_1::RenderSCENE(CClientDC* pDC,CRect& RectClip,int nActiveObjType,
							int nActiveObjIndex,int nViewNum)
{   
	m_bMeshScene = FALSE;
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
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
			if(!(pObject->IsShow()))
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
			//////////////////////////////////////////////// Obj3D	
			if((UINT)nObjType == OBJ3D)
			{
				if( (bDirty && m_bNS_D_Object) || (!bDirty && m_bNS_P_Object) )
					continue;
				/////////////
				RenderOBJECT(pDC,RectClipLocal,pObject,bSelected);
				///////////////////////
			}					
			else	
			if((UINT)nObjType == SOLID)
			{
				if( (bDirty && m_bNS_D_Solid) || (!bDirty && m_bNS_P_Solid) )
				continue;
				/////////////
				RenderSOLID(pDC,RectClipLocal,pObject,bSelected);
				///////////////////////
			}					
			else	
			if((UINT)nObjType == PATCH)
			{
				if( (bDirty && m_bNS_D_Patch) || (!bDirty && m_bNS_P_Patch) )
				continue;
				/////////////
				RenderPATCH(pDC,RectClipLocal,pObject,bSelected);
				///////////
			}
			else
			if((UINT)nObjType == C_PROFILE)
			{
				if( (bDirty && m_bNS_D_Profile_C) || (!bDirty && m_bNS_P_Profile_C) )
					continue;
				/////////////
				RenderPROFILE_C(pDC,RectClipLocal,pObject,bSelected);
				///////////
			}
			else
			if((UINT)nObjType == CURVE)
			{
				if( (bDirty && m_bNS_D_Curve) || (!bDirty && m_bNS_P_Curve) )
					continue;
				/////////////
				RenderCURVE(pDC,RectClipLocal,pObject,bSelected);
				///////////
			}					
			else
			////////////////////////////////////// Individual Elements
				RenderSTRAY(pDC,pObject,bSelected,nViewNum);
				//////////////////////				
		}
	}
	return 0;
}

int	CWire_1::RenderOBJECT
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	//////////////////////////////////////////// Obj3D
	CDListMgr* pList;
	//////////////////////////////////////////// Posted Solids									
	pList = pObject->GetSolidList();
	////////////////////////////////
	if(!pList->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			RenderSOLID(pDC,RectClip,pObject,bSelected);
			///////////
		}
	}
	//////////////////////////////////////////// Posted Patches									
	pList = pObject->GetPatchList();
	////////////////////////////////
	if(!pList->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			RenderPATCH(pDC,RectClip,pObject,bSelected);
			///////////
		}
	}
	//////////////////////////////////////////// Posted Curves									
	pList = pObject->GetCurveList();
	////////////////////////////////
	if(!pList->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();	// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			RenderCURVE(pDC,RectClip,pObject,bSelected);
		}
	}
	/////////	
	return 0;
}

int	CWire_1::RenderSOLID
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound,ClipRect;
	ClipRect = RectClip;
	////////////////////
	CDrSolid* pSolid = (CDrSolid*)pObject;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pList = pObject->GetElemList();
	///////////////////////                             ***todo** There is PlateLIST inside ElemList
	if(!(pList->IsEmpty()))
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////// BackFace Culling
			if(pObject->IsCulled())
				continue;
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();    // ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			int nObjType = pObject->GetObjectType();
			////////////////////////////////////// Posted Polygons 
			if(nObjType == FE2D)
			{
				/////////////////////////// Posted Poly
				CDrFE2D* pPoly = (CDrFE2D*) pObject;
		    	//////////////////////////////////////////// Pre-Render	 
				RenderReadyOBJECT(pDC,pObject,nObjType);
				//////////////////////////////////////////// Render
				RenderPOLY(pDC, pPoly, bSelected);
				//////////
			}
			else
			if(nObjType == FE1D)
			{
				/////////////////////////// Posted Line
				CDrFE1D* pLine = (CDrFE1D*) pObject;
		    	//////////////////////////////////////////// Pre-Render	 
				RenderReadyOBJECT(pDC,pObject,nObjType);
				//////////////////////////////////////////// Render
				RenderLINE(pDC, pLine, bSelected);
				//////////
			}	
								
		}
	}
	else
	{
		//////////////////////////////////////// Entire Solid DirtyDraw
		pObject->SetControlShapeNeed(!m_bNS_CShape);
		pObject->DoDrawView(pDC, bSelected);
//		pObject->DoDrawView(pDC);
		//////////////////////
	}	
	/////////					
	return 0;
}

int	CWire_1::RenderPATCH
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound,ClipRect;
	ClipRect = RectClip;
	////////////////////
	CDrPatch* pPatch = (CDrPatch*)pObject;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pList = pObject->GetElemList();
	///////////////////////
	if(!(pList->IsEmpty()))
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////// BackFace Culling
			if(pObject->IsCulled())
				continue;
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();    // ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			int nObjType = pObject->GetObjectType();
			////////////////////////////////////// Posted Polygons 
			if(nObjType == FE2D)
			{
				/////////////////////////// Posted Poly
				CDrFE2D* pPoly = (CDrFE2D*) pObject;
		    	//////////////////////////////////////////// Pre-Render	 
				RenderReadyOBJECT(pDC,pObject,nObjType);
				//////////////////////////////////////////// Render
				RenderPOLY(pDC, pPoly, bSelected);
				//////////
			}
			else
			if(nObjType == FE1D)
			{
				/////////////////////////// Posted Line
				CDrFE1D* pLine = (CDrFE1D*) pObject;
		    	//////////////////////////////////////////// Pre-Render	 
				RenderReadyOBJECT(pDC,pObject,nObjType);
				//////////////////////////////////////////// Render
				RenderLINE(pDC, pLine, bSelected);
				//////////
			}	
								
		}
	}
	/////////					
	return 0;
}

int	CWire_1::RenderPROFILE_C
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{
/*
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pListC 	= pObject->GetCurveList();
	CDListMgr* pListLM	= ((CDrProf_C*)pObject)->GetLMList();
	/////////////////////////////////////////////////////////// C_Profile
	int index;
	//////////////////////////////////////////// Posted Curves									
	if(!(pListC->IsEmpty()) )								  									
	{
		POSITION pos = pListC->GetFirstObjectPos();
		///////////////////////////////////////////////////////////////////
		for (index=0;pos !=NULL;index++)
		{
			CDrObject* pObject = (CDrObject*)pListC->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();	// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////////////// Change Instancing
			CMatObj* pMatObj 	= (CMatObj*)pListLM->GetObject(index);
			pMATRIX  pLM 		= pMatObj->GetMatrix();
			BOOL	 bInstance	= pObject->IsInstanced();
			pObject->SetInstanced(TRUE);
			((CDrCurve*)pObject)->SetLocalTransform(pLM);
			/////////////////////////////////////////////
			RenderCURVE(pDC,RectClip,pObject,bSelected);
			///////////////////////////////////////////// reset back
			pObject->SetInstanced(bInstance);
		}
	}
*/

	CDrCurve* pCurve = ((CDrProf_C*)pObject)->GetCurve();
	////////////////////////////////////	 
	pCurve->SetControlShapeNeed(!m_bNS_CShape);
	pCurve->DoDrawView(pDC, bSelected);
	////////////////////////////////////				
	/////////	
	return 0;
}

int	CWire_1::RenderCURVE
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pList = pObject->GetElemList();
	///////////////////////
	if(!(pList->IsEmpty()))
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();    // ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			////////////////////////////////////////////////
			int nObjType = pObject->GetObjectType();
			////////////////////////// Posted Line
			CDrFE1D* pLine = (CDrFE1D*) pObject;
	    	//////////////////////////////////////////// Pre-Render	 
			RenderReadyOBJECT(pDC,pObject,nObjType);
			//////////////////////////////////////////// Render
			RenderLINE(pDC, pLine, bSelected);
			//////////
								
		}
	}
	else
	{
		//////////////////////////////////////// Entire Curve DirtyDraw
		pObject->SetControlShapeNeed(!m_bNS_CShape);
		pObject->DoDrawView(pDC, bSelected);
		//////////////////////
	}	
	/////////					
	return 0;
}

int	CWire_1::RenderPOLY(CClientDC* pDC,CDrObject* pObject,
										BOOL bSelected )
{

	////////////////////////////////////	 
	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	////////////////////////////////////				
	return 0;
}

int	CWire_1::RenderLINE(CClientDC* pDC,CDrObject* pObject,
										BOOL bSelected )
{

	////////////////////////////////////	 
	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	////////////////////////////////////				
	return 0;
}

int CWire_1::RenderSTRAY(CClientDC* pDC,CDrObject* pObject,
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
	/////////////////////////////////////////////// LinSupport
    if(nObjType == LIN_SUPPORT)
    {
      	CDrLinSup* pSupp = (CDrLinSup*)pObject;
		///////////////////////////////////////
 	 	if
		(
			((pSupp->GetSuppCard())->SuppProc == SUP_RIGID) && m_bNS_RIGID
		)
    		return 0;
		////////////
 	 	if
		(
			((pSupp->GetSuppCard())->SuppProc == SUP_LINSPR) && m_bNS_Lin_Spring
		)
    		return 0;
 		////////////
 	 	if
		(
			((pSupp->GetSuppCard())->SuppProc == SUP_LINSNU) && m_bNS_Lin_Snubber
		)
    		return 0;
 		////////////
   }			
	/////////////////////////////////////////////// StaticLoads
    if(nObjType == FORCE && m_bNS_Force)
    	return 0;
    if(nObjType == DISPLACE && m_bNS_Displace)
    	return 0;
    if(nObjType == PRESSURE && m_bNS_Pressure)
    	return 0;
    if(nObjType == THERMAL && m_bNS_Thermal)
    	return 0;
    if(nObjType == LUMPWT && m_bNS_LumpWt)
    	return 0;
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

int CWire_1::RenderLabelMeshElem(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum)
{
  	CDrLabel* pLabel = (CDrLabel*)pObject;
	//////////////////////////////////////
	if(pLabel->GetMeshElemType() == NONE)
		return 0;
	////////////////////////////////////// 
  	if(pLabel->GetType() != LABEL_NODE)
		return 0;
	//////////////////////////////////////////////////////////////// Elements
	if(m_bNoSoLabEL[ 0]) //////////////////////////////////// All
		return 0;
	if(m_bNoSoLabEL[ 1]) //////////////////////////////////// None
	{
		pObject->DoDrawView(pDC,bSelected,nViewNum);
		return 0;

	}
	///////////////////////////////////////////////////////// Some
	switch(pLabel->GetMeshElemType())
	{
		case BALLJOINT:
			if(m_bNoSoLabEL[11])
				return 0;
			break;
		///////////
		case TRUSS:
			if(m_bNoSoLabEL[20])
				return 0;
			break;
		case BEAM:
			if(m_bNoSoLabEL[21])
				return 0;
			break;
		case PIPE:
			if(m_bNoSoLabEL[22])
				return 0;
			break;
		case ELBOW:
			if(m_bNoSoLabEL[23])
				return 0;
			break;
		///////////
		case TR_3:
			if(m_bNoSoLabEL[30])
				return 0;
			break;
		case TR_6:
			if(m_bNoSoLabEL[31])
				return 0;
			break;
		case TR_9:
			if(m_bNoSoLabEL[32])
				return 0;
			break;
		case TR_10:
			if(m_bNoSoLabEL[33])
				return 0;
			break;
		case QU_4:
			if(m_bNoSoLabEL[34])
			break;
		case QU_8:
			if(m_bNoSoLabEL[35])
				return 0;
			break;
		case QU_9:
			if(m_bNoSoLabEL[36])
				return 0;
			break;
		case QU_12:
			if(m_bNoSoLabEL[37])
				return 0;
		case QU_16:
			if(m_bNoSoLabEL[38])
				return 0;
			break;
		case TETRAHED:
			///////////
			if(m_bNoSoLabEL[60])
				return 0;
			break;
		case PENTAHED:
			if(m_bNoSoLabEL[70])
				return 0;
			break;
		case HEXAHED:
			if(m_bNoSoLabEL[80])
				return 0;
			break;
		default:
			return 0;
	}
	////////////////////////////////////////////
	pObject->DoDrawView(pDC,bSelected,nViewNum);
	/////////
	return 0;
	
}

int CWire_1::RenderLabels(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum)
{
  	CDrLabel* pLabel = (CDrLabel*)pObject;
	//////////////////////////////////////////////////////////////// Elements
	if(pLabel->GetMeshElemType() != NONE)
	{
		RenderLabelMeshElem(pDC,pObject,bSelected,nViewNum);
		return 0;
	}
	//////////////////////////////////////////////////////////////// Nodes
  	if(pLabel->GetType() == LABEL_NODE)
	{
    	CDrNode* pNode = (CDrNode*)pLabel->GetNodePtr();
		////////////////////////////////////////////////
    	if(pNode->IsControlNode())
    	{
			if(m_bNS_CNLabel)
				return 0;
			/////////////////
			if( (pNode->GetObjectType() == FE0D) && !m_bMeshScene)
				return 0;
			else
	  	 		if( (pNode->GetObjectType() != FE0D) &&	m_bMeshScene)
    			return 0;
		}    			
		else
    	if(pNode->IsMeshNode())
		{   			
    		if(m_bNS_MNLabel ||	!m_bMeshScene )
    			return 0;
    	}
		else 
		{   			
    		if(m_bNS_NLabel ||	m_bMeshScene)
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

void CWire_1::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjectType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
		int nObjType = pObject->GetObjectType();
		////////////////////////////////////// Posted Polygons 
		if(nObjType == FE2D ||nObjType == FE3D)
		{
			pObject->SetCulled(m_bCulling3D);
			pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
									m_dzMin,m_dScale_U,m_dScale_V,
									m_dShrink);
		}
		else
			pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
									m_dzMin,m_dScale_U,m_dScale_V);
       	///////////////////////////////////
 		if( m_bCulling3D && (pObject->GetObjectType() == PATCH)  )
 		{
 			//////////////////////////////////////// Posted Solid/Patch
 			// BACKFACE CULLing Only for SOLIDs & PATCHes
 			// 		with 2D or 3D Components
 			//////////////////////////////////////////////
			BOOL bCulled = 	pObject->RemoveHiddenObject(&m_ViewM,m_VDir,1);
			////////////
			if(bCulled)
				return;
		}		
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
/////////////////////////// end of module ///////////////
/*

void CPR_Wire1::RenderReadySOLID(CDrObject* pObject,int nObjType)
{
	//////////////////////////////////////// PolyList SetUp
	CDListMgr* pList = pObject->GetElemList();
	//////////////////////////////////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////////////////////
		if(pObject->IsCulled())
			continue;	
		/////////////////////// put in the list if 2D or 3D
		// 		Needs more Elaborate Logic						**** todo ****
		m_pSortList->InsertObject(pObject);
		/////////////
	}
	/////////////

}

void CPR_Wire1::RenderReadyPATCH(CDrObject* pObject,int nObjType)
{
	//////////////////////////////////////// PolyList SetUp
	CDListMgr* pList = pObject->GetElemList();
	//////////////////////////////////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////////////////////
		if(pObject->IsCulled())
			continue;	
		/////////////////////// put in the list if 2D Component
		if(pObject->Is2D())
			m_pSortList->InsertObject(pObject);
		/////////////
	}
	/////////////

}
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