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
#include "DrStatic.h"		// DrStatic
////////////////////////// SupportLevel
#include "Def_Supp.h"
#include "DrLinSup.h"		// DrLinSup
////////////////////////// ElementLevel
#include "Def_IGen.h"
#include "Def_Elem.h"	// 
#include "DrFE0D.h"		// DrFE1D
#include "DrFE1D.h"		// DrFE1D
#include "DrFE2D.h"		// DrFE2D
//#include "DrPlate.h"	// for Poly, now; it will be DrPoly
//#include "DrPipe.h"		// for Line, now; it will be DrLine
#include "DrProf_C.h"		// for Profile_C
#include "MatObj.h"		// for Profile_C
////////////////////////// Temporarily: LABEL ShutOff
#include "Def_Draw.h"	//  			@ RenderStray
#include "DrLabel.h"
////////////////////////// Render
#include "Render.h"
#include "RN_Wire0.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CWire_0

IMPLEMENT_DYNAMIC(CWire_0,CRender)
/*
BEGIN_MESSAGE_MAP(CWire_0,CRender)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CWire_0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
///////////////////
CWire_0::CWire_0()
{
	m_bMeshScene = FALSE;
}

CWire_0::CWire_0(
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

int CWire_0::Init	(
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
int	CWire_0::RenderScene_GENERATOR(CClientDC* pDC,CRect& RectClip,int nActiveObjType,
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
			int nElemType = pObject->GetElemType();
			if (nElemType <0) 
				continue;  // not viewable
			//////////////////////////////////////////////// Draw THE Object
			long nObjNo  	= pObject->GetObjectNo();
			int nObjIndex  	= pList->GetObjectIndex(nObjNo);
			int nObjType  	= pObject->GetObjectType();
			BOOL bDirty		= pObject->IsDirty();
			//////////////////////////////////////////////// Meshes
			switch((UINT)nObjType)
			{
				case MESH3D:
				case MESH2D:
				case MESH1D:
				case MESH0D:
				case FE0D:		// Mesh Control Nodes (MCNODE has ObjType as FE0D)
					continue;
			}
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
				continue;
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)NODE) && (m_bNS_Node && m_bNS_CNode))
				continue;
			//////////////////////////////////////////////// Is Selected
			BOOL bSelected = FALSE;
			if(nObjType == nActiveObjType && nObjIndex == nActiveObjIndex)
				bSelected = TRUE;
			//////////////////////////////////////////////////////////////
    		CDrNode* pNode;
			/////////////////////////////////////////////////////////////////
			if (pObjectMgr->IsSceneChanged() || pObjectMgr->IsViewChanged() )
				RenderReadyOBJECT(pDC,pObject,nObjType);
			/////////////////////////////////////////////////////////////////
			switch ((UINT)nObjType)
			{
				case OBJ3D:
					//////////////////////////////////////////////// Obj3D
					if( (bDirty && !m_bNS_D_Object) )
						/////////////
						RenderOBJ3D(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					break;

				case SOLID:
					//////////////////////////////////////////////// Solid
					if( (bDirty && !m_bNS_D_Solid) )
					{
						/////////////
						RenderSOLID(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					}
					break;

				case PATCH:
					//////////////////////////////////////////////// Solid
					if( (bDirty && !m_bNS_D_Patch) )
					{
						/////////////
						RenderPATCH(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					}
					break;

				case C_PROFILE:
					//////////////////////////////////////////////// C_PROFILE
					if( (bDirty && !m_bNS_D_Profile_C) )
					{
						/////////////
						RenderCURVE(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					}
					break;

				case CURVE:
					//////////////////////////////////////////////// CURVE
					if( (bDirty && !m_bNS_D_Curve) )
					{
						/////////////
						RenderCURVE(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					}
					break;

				case NODE:
				case INODE:
				case CNODE:

    				pNode = (CDrNode*)pObject;
					//////////////////////////
    				if(pNode->IsControlNode() && m_bNS_CNode)	break;
					else
		    	 	if(m_bNS_Node)								break;
					/////////////
					RenderNODE(pDC,RectClipLocal,pObject,bSelected);
					///////////////////////
					break;

				default:
					////////////////////////////////////// Individual Elements
					RenderSTRAY(pDC,RectClipLocal,pObject,bSelected,nViewNum);
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

int	CWire_0::RenderOBJ3D
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
	CDListMgr* pListO = pObject->GetObj3DList();
	CDListMgr* pListS = pObject->GetSolidList();
	CDListMgr* pListP = pObject->GetPatchList();
	CDListMgr* pListC = pObject->GetCurveList();
	//////////////////////////////////////////// Obj3Ds									
	if(!pListO->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListO->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListO->GetNextObject(pos);
			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
//			RenderReadyOBJECT(pDC,pObject,nObjType);
			/////////////////////////////////////////////// Clip Against 
			RectBound	= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				return 0;
			/////////////
			RenderOBJ3D(pDC,RectClip,pObject,bSelected);
			///////////////////////
		}
	}
	//////////////////////////////////////////// Solids									
//	if((!(pListS->IsEmpty())) && !m_bNS_P_Solid)								  									
	if(!pListS->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListS->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListS->GetNextObject(pos);
			/////////////
			RenderSOLID(pDC,RectClip,pObject,bSelected);
			///////////////////////
		}
	}
	//////////////////////////////////////////// Patches									
	if(!pListP->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListP->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListP->GetNextObject(pos);
			/////////////
			RenderPATCH(pDC,RectClip,pObject,bSelected);
			///////////////////////
		}
	}
	//////////////////////////////////////////// Posted Curves									
	if(!pListC->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListC->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListC->GetNextObject(pos);
			/////////////
			RenderCURVE(pDC,RectClip,pObject,bSelected);
			///////////////////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderSOLID
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
	int nObjType  	= pObject->GetObjectType();
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	//////////////////////////////////////////// SupportList									
	CDListMgr* pListSupp = pObject->GetSuppList();
	/////////////////////////
	if(!pListSupp->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListSupp->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListSupp->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSUPPORT(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	//////////////////////////////////////////// StaticList									
	CDListMgr* pListStaL = pObject->GetStaLList();
	/////////////////////////
	if(!pListStaL->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListStaL->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListStaL->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSTATIC(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderPATCH
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
	int nObjType  	= pObject->GetObjectType();
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	//////////////////////////////////////////// SupportList									
	CDListMgr* pListSupp = pObject->GetSuppList();
	/////////////////////////
	if(!pListSupp->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListSupp->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListSupp->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSUPPORT(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	//////////////////////////////////////////// StaticList									
	CDListMgr* pListStaL = pObject->GetStaLList();
	/////////////////////////
	if(!pListStaL->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListStaL->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListStaL->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSTATIC(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderCURVE
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{

	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
	int nObjType  	= pObject->GetObjectType();
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	//////////////////////////////////////////// SupportList									
	CDListMgr* pListSupp = pObject->GetSuppList();
	/////////////////////////
	if(!pListSupp->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListSupp->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListSupp->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSUPPORT(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	//////////////////////////////////////////// StaticList									
	CDListMgr* pListStaL = pObject->GetStaLList();
	/////////////////////////
	if(!pListStaL->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListStaL->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListStaL->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSTATIC(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderNODE
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{
	////////////////////////
	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
	int nObjType  	= pObject->GetObjectType();
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
//	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	//////////////////////////////////////////// SupportList									
	CDListMgr* pListSupp = pObject->GetSuppList();
	/////////////////////////
	if(!pListSupp->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListSupp->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListSupp->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSUPPORT(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	//////////////////////////////////////////// StaticList									
	CDListMgr* pListStaL = pObject->GetStaLList();
	/////////////////////////
	if(!pListStaL->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListStaL->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListStaL->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			RenderSTATIC(pDC,RectClip,pObject,TRUE);
			///////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderSTATIC
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{
    int nObjType = pObject->GetObjectType();
	/////////////////////////////////////////////// StaticLoads
   	CDrStatic* pStaL = (CDrStatic*)pObject;
	///////////////////////////////////////
 	if(((pStaL->GetStaLCard())->StaLProc == STL_FORCE) && m_bNS_Force)
    	return 0;
 	if(((pStaL->GetStaLCard())->StaLProc == STL_DISPLACE) && m_bNS_Displace)
    	return 0;
 	if(((pStaL->GetStaLCard())->StaLProc == STL_PRESSURE) && m_bNS_Pressure)
    	return 0;
 	if(((pStaL->GetStaLCard())->StaLProc == STL_THERMAL) && m_bNS_Thermal)
    	return 0;
 	if(((pStaL->GetStaLCard())->StaLProc == STL_LUMPWT) && m_bNS_LumpWt)
    	return 0;
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
//	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	/////////	
	return 0;
}

int	CWire_0::RenderSUPPORT
				(
					CClientDC* pDC,CRect& RectClip,
					CDrObject* pObject,BOOL bSelected
				)
{
    int nObjType = pObject->GetObjectType();
	/////////////////////////////////////////////// LinSupport
   	CDrLinSup* pSupp = (CDrLinSup*)pObject;
	///////////////////////////////////////
 	if(((pSupp->GetSuppCard())->SuppProc == SUP_RIGID) && m_bNS_RIGID)
   		return 0;
 	if(((pSupp->GetSuppCard())->SuppProc == SUP_LINSPR) && m_bNS_Lin_Spring)
 		return 0;
 	if(((pSupp->GetSuppCard())->SuppProc == SUP_LINSNU) && m_bNS_Lin_Snubber)
   		return 0;
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
//	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	if(!(RectInt.IntersectRect(RectClip, RectBound)) )
		return 0;
	////////////////////////////////////////////////
//	pObject->SetControlShapeNeed(!m_bNS_CShape);
	pObject->DoDrawView(pDC, bSelected);
	/////////	
	return 0;
}

int CWire_0::RenderSTRAY
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected,int nViewNum
					)
{ 
	CRect RectInt,RectBound;
	//////////////////////////////////////////////////////////////// Pre-Render	 
    int nObjType = pObject->GetObjectType();
	RenderReadyOBJECT(pDC,pObject,nObjType);
	/////////////////////////////////////////////// Clip Against 
	RectBound	= pObject->GetBoundingRect();// ScreenRect 	
	pDC->LPtoDP(&RectBound);
	RectBound.NormalizeRect();
	//////////////////////////	
	if(!(RectInt.IntersectRect(&RectClip, &RectBound)) )
		return 0;
	////////////////////////////////////////////////////////////////////	
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
 //   if((nObjType == LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
 //   	return 0;
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

int CWire_0::RenderLabelMeshElem(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum)
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

int CWire_0::RenderLabels(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum)
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

void CWire_0::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjectType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	if(!(pObject->IsShow()))
		return;
	////////////////////////	
	pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V);
	//////////////////////////////////////////// SupportList									
	CDListMgr* pListSupp = pObject->GetSuppList();
	/////////////////////////
	if(!pListSupp->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListSupp->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListSupp->GetNextObject(pos);
			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyOBJECT(pDC,pObject,nObjType);
			//////////////////////////////////////////////////////////////		
			CRect rectInvalid = pObject->GetBoundingRect();
		    /////////////////////////
			pDC->LPtoDP(&rectInvalid);
			m_pView->InvalidateRect(&rectInvalid);	  // already in client(Device) coord
			/////////////////////////
		}
	}
	//////////////////////////////////////////// StaticList									
	CDListMgr* pListStaL = pObject->GetStaLList();
	/////////////////////////
	if(!pListStaL->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListStaL->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListStaL->GetNextObject(pos);
			/////////////////////////////////////////////// Clip Against 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyOBJECT(pDC,pObject,nObjType);
			//////////////////////////////////////////////////////////////		
			CRect rectInvalid = pObject->GetBoundingRect();
		    /////////////////////////
			pDC->LPtoDP(&rectInvalid);
			m_pView->InvalidateRect(&rectInvalid);	  // already in client(Device) coord
			/////////////////////////
		}
	}
	/////////	
}

void CWire_0::RenderReadyMESH(CDC* pDC,CDrObject* pObject,int nObjectType)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	if(!(pObject->IsShow()))
		return;
	////////////////////////	
	if(nObjectType == FE2D)
	{
		((CDrFE2D*)pObject)->SetCulled(m_bCulling3D);
		((CDrFE2D*)pObject)->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V,
								m_dShrink);
	}
	else
		pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V);
      	////////////////////////////////////////////////////////////
}

int	CWire_0::RenderScene_MESH(CClientDC* pDC,CRect& RectClip,int nActiveObjType,
							int nActiveObjIndex,int nViewNum)
{   
	m_bMeshScene = TRUE;
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
			int nElemType = pObject->GetElemType();
			if (nElemType <0) 
				continue;  // not viewable
			//////////////////////////////////////////////// Draw THE Object
			long nObjNo  	= pObject->GetObjectNo();
			int nObjIndex  	= pList->GetObjectIndex(nObjNo);
			int nObjType  	= pObject->GetObjectType();
			BOOL bDirty		= pObject->IsDirty();
			//////////////////////////////////////////////// Generators
			switch((UINT)nObjType)
			{
				///////////////
				case SOLID:
				case PATCH:
				case C_PROFILE:
				case CURVE:
				case NODE:
					continue;
			}
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
				continue;
			//////////////////////////////////////////////// Labels take time!
			if((nObjType == (int)NODE) && (m_bNS_Node && m_bNS_CNode))
				continue;
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			RenderReadyMESH(pDC,pObject,nObjType);
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
				case MESH3D:
					//////////////////////////////////////////////// Obj3D
					if( (!bDirty && !m_bNS_P_Solid) )
						/////////////
						RenderMesh3D(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					break;

				case MESH2D:
					//////////////////////////////////////////////// Obj3D
					if(  (!bDirty && !m_bNS_P_Patch) )
						/////////////
						RenderMesh2D(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					break;

				case MESH1D:
					//////////////////////////////////////////////// Obj3D
					if(  (!bDirty && !m_bNS_P_Curve) )
						/////////////
						RenderMesh1D(pDC,RectClipLocal,pObject,bSelected);
						///////////////////////
					break;


				default:
					////////////////////////////////////// Individual Elements
					RenderSTRAY(pDC,RectClipLocal,pObject,bSelected,nViewNum);
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

int	CWire_0::RenderMesh3D
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
	CDListMgr* pListS = pObject->GetFE3DList();
	CDListMgr* pListP = pObject->GetFE2DList();
	CDListMgr* pListC = pObject->GetFE1DList();
	//////////////////////////////////////////// Solids									
//	if((!(pListS->IsEmpty())) && !m_bNS_P_Solid)								  									
	if(!pListS->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListS->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListS->GetNextObject(pos);
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyMESH(pDC,pObject,nObjType);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////// FE3D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
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
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyMESH(pDC,pObject,nObjType);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////// FE2D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
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
/*
			/////////////////////////////////////////////// Clip Against 
			// Curves DONT CLIP by Rect: 
			// Otherwise,
			//	HORIZONTAL & VERTICAL Lines will be Lost
			///////////////////////////////////////////////
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
*/
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyMESH(pDC,pObject,nObjType);
			//////////////////////////////////////// FE1D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderMesh2D
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
	CDListMgr* pListP = pObject->GetFE2DList();
	CDListMgr* pListC = pObject->GetFE1DList();
	//////////////////////////////////////////// Posted Patches									
//	if((!(pListP->IsEmpty())) && !m_bNS_P_Patch)								  									
	//////////////////////////////////////////// Patches									
	if(!pListP->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListP->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListP->GetNextObject(pos);
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
//100197			RenderReadyOBJECT(pDC,pObject,nObjType);
			RenderReadyMESH(pDC,pObject,FE2D);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////// FE2D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
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
/*
			/////////////////////////////////////////////// Clip Against 
			// Curves DONT CLIP by Rect: 
			// Otherwise,
			//	HORIZONTAL & VERTICAL Lines will be Lost
			///////////////////////////////////////////////
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
*/
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyMESH(pDC,pObject,nObjType);
			//////////////////////////////////////// FE1D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
		}
	}
	/////////	
	return 0;
}

int	CWire_0::RenderMesh1D
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
	CDListMgr* pListN = pObject->GetFE0DList();
	CDListMgr* pListC = pObject->GetFE1DList();
	//////////////////////////////////////////// Posted Curves									
//	if((!(pListC->IsEmpty())) && !m_bNS_P_Curve)								  									
	//////////////////////////////////////////// Posted Curves									
	if(!pListC->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListC->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListC->GetNextObject(pos);
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyMESH(pDC,pObject,nObjType);
/*
			/////////////////////////////////////////////// Clip Against 
			// Curves DONT CLIP by Rect: 
			// Otherwise,
			//	HORIZONTAL & VERTICAL Lines will be Lost
			///////////////////////////////////////////////
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
*/
			//////////////////////////////////////// FE1D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
		}
	}
/*
	//////////////////////////////////////////// Posted MNode or Vertex									
//	if((!(pListN->IsEmpty())) && !m_bNS_P_Node)								  									
	//////////////////////////////////////////// Posted Curves									
	if(!pListN->IsEmpty())								  									
	{
		///////////////////////////////////////////////////////////////////
		for (POSITION pos = pListN->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pListN->GetNextObject(pos);
  			//////////////////////////////////////////////////////////////// Pre-Render	 
			int nObjType  	= pObject->GetObjectType();
			RenderReadyOBJECT(pDC,pObject,nObjType);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			RectBound.NormalizeRect();
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////// FE1D Draw
			pObject->DoDrawView(pDC, bSelected);
			//////////////////////
		}
	}
*/
	/////////	
	return 0;
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
