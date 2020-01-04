/*****************************************************************************
 *	File:		Wire2.cpp
 *
 *	Purpose:	WireFrame with Complexity Level = 2
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
 *				CentroidClip			YES		*						
 *				2DCulling				NO
 *			Image-Precision:
 *				DepthSort				YES		*						
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
 *			PolygonalLevel				YES		*
 *		Clipping:
 *			Homogeneous 4D				NO
 *			3D Coordinates				YES		*
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
#include "DrFE1D.h"		// DrFE1D
#include "DrFE2D.h"		// DrFE2D
//#include "DrPlate.h"	// for Poly, now; it will be DrPoly
//#include "DrPipe.h"		// for Line, now; it will be DrLine
#include "DrCurve.h"		// for Curve
#include "DrPatch.h"		// for Patch
#include "DrSolid.h"		// for Solid
#include "DrProf_C.h"		// for Profile_C
#include "MatObj.h"		// for Profile_C
////////////////////////// Temporarily: LABEL ShutOff
#include "Def_Draw.h"	//  			@ RenderStray
#include "DrClip.h"

#include "Render.h"
///////////////////
#include "RN_Wire2.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define EQUAL(a,b)	((a).x == (b).x)&&((a).y == (b).y)&&((a).z == (b).z)
/////////////////////////////////////////////////////////////////////////////
// CWire_2

IMPLEMENT_DYNAMIC(CWire_2,CRender)
/*
BEGIN_MESSAGE_MAP(CWire_2,CRender)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CWire_2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
///////////////////
CWire_2::CWire_2()
{
}

CWire_2::CWire_2(
					CDrawView* pView, RENDITION rend, BOOL bParallel,
					BOOL bNS[],BOOL bNSEL[],BOOL bNSLE[]
				)
{
	/////////////////////////
	m_pView 		= pView;
	m_Rendition		= rend;	//Rendering Method
	m_bParallel		= bParallel;
	/////////////////////////
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
	
}

int CWire_2::Init	(
						int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin, double dScale_U,double dScale_V,
						double dShrink,CDListMgr* pSortList
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
	m_bCullWorld 	= m_bCulling3D;
	m_bShadowOn		= FALSE;
	m_bAntiAliasOn	= FALSE;
	m_bNeedSort		= TRUE;	// for depthsort
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
	m_pPolyList		= pSortList;	// active ones for Shadow
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
int	CWire_2::RenderSCENE(CClientDC* pDC,CRect& RectClip,int nActiveObjType,
							int nActiveObjIndex,int nViewNum)
{   
	//////////////////////////////////////////////////////////////////
    //	RECALL:                                                 	//
    //		1.	We're walking through THE List which contains:		//
    //					POSTED OBJ3D->Solids,Patches & Curves 		//
    //					(Only those containing 1D components, other	//
    //						2D & 3D rendered later thro' SortList)	// 
    //																//
    //					UNPOSTED PATCH (Dirty) // not drawn			//
    //					UNPOSTED CURVE (Dirty) // not drawn			//
    //					ALL Other ElemObjs							//
    //					ALL OTHER DrawObjs							//
    //		2.	Then, we render SortList with 2D Polys              //
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
		/////////////////////////////////////////////////////
		int nObjType = pObjectMgr->ListIndexToObjType(iList);
		if(
			nObjType == OBJ3D	||nObjType == SOLID		||nObjType == PATCH ||  
			nObjType == CURVE	||nObjType == C_PROFILE ||
			nObjType == FE1D    ||nObjType == FE2D		||nObjType == FE3D 
		  )
		  continue;
		///////////////////////////////
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		///////////////////////////////////////////////////////////////////
		int iCount = 0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			/////////
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
			if(!(pObject->IsShow()))
				continue;
			int nLevelType = pObject->GetLevelType();
    		if (nLevelType != LEVEL_GRAPA) 
    			continue;  // not TopLevel 
    		//////////////////////////////////////////////// Draw THE Object
			long nObjNo  	= pObject->GetObjectNo();
			int nObjIndex  	= pList->GetObjectIndex(nObjNo);
			/////////////////////////////////////////////// Clip Against 
			RectBound		= pObject->GetBoundingRect();// ScreenRect 	
			pDC->LPtoDP(&RectBound);
			
			if(!(RectInt.IntersectRect(RectClip, RectBound)) )
				continue;
			//////////////////////////////////////////////// Is Selected
			BOOL bSelected = FALSE;
			if(nObjType == nActiveObjType && nObjIndex == nActiveObjIndex)
				bSelected = TRUE;
			////////////////////////////////////// Individual Elements
			RenderSTRAY(pDC,pObject,bSelected,
							nViewNum);
			//////////////////////				
		}
	}
	///////////////////////////////////////////////////////////////// Render SortList
	RenderSORTLIST(pDC,RectClip,nActiveObjType,nActiveObjIndex);
	///////////////////////				
	return 0;
}

int	CWire_2::RenderSORTLIST(CClientDC* pDC,CRect& RectClip,int nActiveObjType, int nActiveObjIndex)
{

    /////////////////////////////////////////////////////////////////////
	CRect RectInt,RectBound,ClipRect;
	ClipRect = RectClip;
    ////////////////////////////////////////////////////////////
	// Draw each Object in the invalidated region of the window,
	// or on the printed (previewed) page.
	// For each Object, get Bounding Rectangle and intersect with invalidated
	// rectangle. If visible, then draw the Object;
	CDListMgr* pList = m_pPolyList;
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
			///////////////////////////////////////////////////	 
			long nObjNo  	= pObject->GetObjectNo();
			int nObjType  	= pObject->GetObjectType();
			int nObjIndex  	= pList->GetObjectIndex(nObjNo);
			//////////////////////////////////////////////// Is Selected
			BOOL bSelected = FALSE;
			if(nObjType == nActiveObjType && nObjIndex == nActiveObjIndex)
				bSelected = TRUE;
			///////////////////////////////////////////////////	
			WORLD	Node3DPos;
			////////////////////////////////////////////// memory
			pWORLD	NodeEye		= new WORLD[2*MAX_POLY_NODES];
			//////////////////////////////////////////////////
			int		nMaxN;
			////////////////////////////////////////////////// Clip Against
			if((nMaxN = ClipPoly(pObject,NodeEye)) <=0)		// CanonVol
			{
				delete [] NodeEye;
				//////////////////
				continue;
			}
			////////////////////////////////////////////// memory
			POINT*	Node2DPos	= new POINT[2*MAX_POLY_NODES];
			////////////////////////////////////////////////// Project
			for (int i=0;i<nMaxN;i++)
			{
				m_pView->Project(&(NodeEye[i]), &Node3DPos,TRUE); // TRUE = Scaled
				//////////////////////////////////
				Node2DPos[i].x = (int)Node3DPos.x;
				Node2DPos[i].y = (int)Node3DPos.y;
			
			}
			/////////////////////////// Posted Poly
			RenderCLIPPOLY(pDC, Node2DPos,nMaxN,bSelected);
			//////////
			delete [] NodeEye;
			delete [] Node2DPos;
			////////////////////
		}
	}
	/////////					
	return 0;
}

int	CWire_2::RenderCLIPPOLY(CClientDC* pDC,POINT* N2DPos,int nMaxN,BOOL bSelected)
{

	///////////////////////////////////////// Fill Poly w/BackGround Color
	CBrush	Br;
	CBrush*	pBrOld;
	Br.CreateSolidBrush(pDC->GetBkColor());
	pBrOld = pDC->SelectObject(&Br);
//	LOGBRUSH
//	Pen.CreatePen(PS_NULL,0,Br.lbColor);
	pDC->SetPolyFillMode(WINDING);
	///////////////////////////
	pDC->Polygon(N2DPos,nMaxN);
	///////////////////////////
	pDC->SelectObject(pBrOld);
	Br.DeleteObject();
	/////////////
	return 0;
	
}	
	
int	CWire_2::ClipPoly(CDrObject* pObject,pWORLD NodeEye)
{

	pWORLD	N = new WORLD[MAX_POLY_NODES];
	/////////////////////////////////////////////// Clip Against
	WORLD	StartN,EndN;
	int nMaxC = pObject->GetMaxCorners();
	/////////////////////////////////////
	int i=0;
	CDListMgr* pNodeList = pObject->GetNodeList();// CanonViewVol
	////////////////////
	for (POSITION pos = pNodeList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pNodeList->GetNextObject(pos);
		N[i++] = *(pNode->GetEyePos() ); 	
	}	
	if(i != nMaxC)
	{
		delete [] N;
		return -1;
	}
	/////////////////////////////////////////////////// ClipEdges
	CDrClip Clip; 
	int j = 0;
	/////////////
	for(i=1;i<nMaxC;i++)
	{
		StartN 	= N[i-1];
		EndN	= N[i];
		if((Clip.ClipLine_LB(&StartN,&EndN)) == VI_YES_VISIBLE)
		{
			/////////////////////////////////// Store,if Not Duplicate 
			if(i>1)
			{
				if(EQUAL(NodeEye[j-1],StartN) )
					NodeEye[j++] = EndN;
				else
				{	
					NodeEye[j++] = StartN;
					NodeEye[j++] = EndN;
				}	
			}				  
			else				
			{
				NodeEye[j++] = StartN;
				NodeEye[j++] = EndN;
			}	
		}
	}	
	////////////////////////// closing Line
	StartN 	= N[nMaxC-1];
	EndN	= N[0];
	if((Clip.ClipLine_LB(&StartN,&EndN)) == VI_YES_VISIBLE)
	{
		if(!(EQUAL(NodeEye[j-1],StartN) ) )
			NodeEye[j++] 	= StartN; 
		if(!(EQUAL(NodeEye[0],EndN)) )
				NodeEye[j] = EndN;
	}					 
	////////// 
	delete [] N;
	return j;
	
}							

int CWire_2::RenderSTRAY(CClientDC* pDC,CDrObject* pObject,
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
    if((nObjType == LABEL) && (m_bNS_NLabel && m_bNS_CNLabel))
    	return 0;
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
	
void CWire_2::RenderReadySCENE(CDC* pDC)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	for(int iList=0;iList<MAX_LIST_ARRAY;iList++)
	{
		CDListMgr* pList = pObjectMgr->GetObjectListFromIndex(iList);	// 
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		/////////////////////////////////////////////////////
		int nObjType = pObjectMgr->ListIndexToObjType(iList);
		if(
			nObjType == OBJ3D	||nObjType == SOLID		||nObjType == PATCH ||  
			nObjType == CURVE	||nObjType == C_PROFILE 
		  )
		  continue;
		///////////////////////////////////////////////////////////////////
		int iCount = 0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			iCount++;
			/////////////////////////////////////////// Transform/Project
			RenderReadyOBJECT(pDC,pObject,nObjType);
			////////////////////////////////////////
		}
	}
	///////////////////////////////////////////////////////// DepthSort
	CRender Render;
	if(!(m_pPolyList->IsEmpty())  )
		Render.DepthSort(m_pPolyList,TRUE);	// TRUE = Ascending Order in z depth
	/////////////////////////////////	
	
}

void CWire_2::RenderReadyOBJECT(CDC* pDC,CDrObject* pObject,int nObjectType)
{
    /////////////////////////////////////////////////////////////////////
	if(!(pObject->IsShow()))
		return;
	////////////////////////////////////// All Posted Polygons whether
	//										in Patches or Solids
	if(nObjectType == FE2D)
	{
		pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V,
								m_dShrink);
		/////////////////////////////////// sortlist
		CDrFE2D* pPlate = (CDrFE2D*)pObject; 
		WORLD Centroid = *(pPlate->GetCentroidEye() ); // transformed
		///////////
		CDrClip Clip;
		if(Clip.ClipPt(&Centroid) == VI_YES_VISIBLE)
			/////////////////////////////////// Put in the List
			m_pPolyList->InsertObject(pObject); 
			/////////////
	}
	else
		pObject->InitDraw(pDC,m_bParallel,m_nView,&m_ViewM,&m_vv3DM,
								m_dzMin,m_dScale_U,m_dScale_V);
   	///////////////////////////////////

}
/////////////////////////// end of module ///////////////
/*

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
			
			if(pObject->IsCulled()||(pObject->GetObjectType() != FE2D))
				continue;
			//////////////
			CDrFE2D* pPlate = (CDrFE2D*)pObject; 
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