// Elem.cpp : implementation file
//
#include "stdafx.h"
#include <math.h>

#include "3DMath.h" 
#include "Def_Type.h" 
#include "DrClip.h"
#include "XForm.h"
///////////////////////////////////////
//#include "drgraf.h"
//#include "drgradoc.h"
/////////////////////
//#include "ObjMgr.h"
//#include "XForm.h"
//////////////////
//#include "3d.h"
/////////////////////
#include "drObject.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrObject    
IMPLEMENT_SERIAL(CDrObject, CObject,1)

/*
BEGIN_MESSAGE_MAP(CDrObject, CGrafObject)
	//{{AFX_MSG_MAP(CDrObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/               
#define MAXSTRINGLENGTH 20 
/////////////////////////////////////////////////////////////////////
CDrObject::CDrObject()
{
 	m_bFormatted	= FALSE;							
   /////////////////////////////////
	m_pMatObj		= NULL;
	m_bInstanced	= FALSE;
	/////////////////////////////////
	m_ParentID		= "";				// if Spawned
	m_SpawnType		= SPN_NONE;
//	m_SubCat		= ;
	m_Category		= CA_ELEMENT;
	m_ElemDimLim	= EDL_THREE;
	//////////////////////////////////////////////////////////
	m_bStepXform	= TRUE;	// if true:	Local->World->View
								// if False:Local->View		
	/////////////////////////////
//	m_RInfo;
	m_bClipped 		= FALSE;
	/////////////////////////////
//	m_Color;
//	m_dShrink;
	//////////////////////
	m_bParallel		= TRUE;
    m_nView			= VIEW12;
//  m_dzMin;
//	m_dScale_U;		// vv3DToLP:U-direction  
//	m_dScale_V;		// vv3DToLP:V-direction
//	m_ViewM;		// viewers transform MATRIX
//	m_ComposedM;	// Local/View Composite MATRIX
//	m_vv3DM;		// Window to 3D Viewport MATRIX
	/////////////////////////////////////////////////////////// 
	m_nLevelType	= LEVEL_EUNUK;
//	m_nObjectType	= ;
//	m_nElemType;	
//	m_nObjectNo;
    /////////////////////////////////
	m_ObjectID		= "";
	/////////////////////////////////
//	m_nLabelNo;
	//////////////////////////////
	m_rectBounding.SetRectEmpty(); // smallest rect that surrounds 
									// Pipe Ends measured in MM_LOENGLISH units
									// (0.01 inches, with Y-axis inverted)
    ////////////////////////////// Normal
	m_nPenWidth		= 0;    // 
	m_crPenColor	= RGB(255,0,0); // Red;
	m_nPenStyle		= PS_SOLID;
    ////////////////////////////// HiLite
	m_nPenWidthHi	= m_nPenWidth+2;    // 
	m_crPenColorHi	= RGB(255,255,0); // Yellow;
	m_nPenStyleHi		= PS_SOLID;
	////////////////////////////// 
	m_nLayer		= 0;
	///////////////////////////////////
	m_nLevel		= LEVEL_EUNUK;				// Hierarchy Level
	///////////////////////////////////
	m_bGenerated	= FALSE;			// generated by Curve or Patch
	m_bMoved		= FALSE;							
	m_bEdited		= FALSE;							
	m_bDeleted		= FALSE;							
	m_bPosted		= FALSE;							
	m_bDirty		= TRUE;							
	m_bShow			= TRUE;
    //////////////////////////////////////////////////////////////////////////////// 
//  WORLD		m_ptMinMaxL[MAX_NODES_CORNER];	// Local Bounding Coords mixed as Min & Max 
//  WORLD		m_ptMinMaxW[MAX_NODES_CORNER];	// World Bounding Coords mixed as Min & Max 
//  WORLD		m_ptMinMaxE[MAX_NODES_CORNER];	// Eye Bounding Coords mixed as Min & Max 
//  WORLD		m_ptMinMaxS[MAX_NODES_CORNER];	// Screen3D Bounding Coords mixed as Min & Max 
// 	POINT 		m_pt[MAX_NODES_CORNER];			// SCREEN Coords.of Corners of 3DBoundVolume
	/////////////////////////////////
	m_LabelList.RemoveAll();       // DrLabel Pointers        "      "    "
	m_Obj3DList.RemoveAll();       // DrObject Pointers        "      "    "
	m_SolidList.RemoveAll();       // DrSolid Pointers        "      "    "
	m_PatchList.RemoveAll();       // DrObject Pointers        "      "    "
	m_CurveList.RemoveAll();       // DrCurve Pointers        "      "    "
	m_CProfList.RemoveAll();       // DrCurve Pointers        "      "    "
	m_NodeList.RemoveAll();        // DrNodes Pointers   "      "    "
	m_INodeList.RemoveAll();       // Input   Nodes Pointers  needed for delete
	m_CNodeList.RemoveAll();       // Control Nodes Pointers  needed for delete: Bezier	  Control Net	
	m_ElemList.RemoveAll();		   // DrElem Pointers        "      "    "
	m_SuppList.RemoveAll();        // DrSupport Pointers   "      "    "
	m_StaLList.RemoveAll();        // DrStatic Loads Pointers   "      "    "
	m_DynLList.RemoveAll();        // DrDynamic Loads Pointers   "      "    "
	m_SpeLList.RemoveAll();        // DrSpectral Loads Pointers   "      "    "
	///////////////////////////////////////////////////////////////////////////
	m_bLinSpr		= FALSE;
	m_bLinSnu		= FALSE;
	m_bSkewed		= FALSE;
	////////////////////////////// 
	m_bToBeEdited	= FALSE;
	m_bToBeDeleted	= FALSE;
	m_bToBeUnDeleted= FALSE;
	m_bToBePosted	= FALSE;
	m_bToBeUnPosted	= FALSE;
	m_bToBeMoved	= FALSE;

}

CDrObject::~CDrObject()
{
	/////////////////////////////
	if(m_pMatObj)
	{
		delete [] m_pMatObj;
		m_pMatObj = NULL;
	}		
}

void CDrObject::GetObjectInfo(CDrObject* pObject)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////////
 	pObject->m_bFormatted		= m_bFormatted;
	///////////////////////////////////////////
	pObject->m_pMatObj 			= m_pMatObj;
	pObject->m_bInstanced 		= m_bInstanced;
//	if( m_bInstanced )
//		Math3D.BlockCopy((HUGEBLK)(&m_instanceXf),(HUGEBLK)(&(pAdd->m_instanceXf)), sizeof(MATRIX) );
	///////////////
	pObject->m_ParentID			= m_ParentID;
	pObject->m_SpawnType		= m_SpawnType;
	pObject->m_SubCat			= m_SubCat;
	pObject->m_Category			= m_Category;
	pObject->m_ElemDimLim		= m_ElemDimLim;
	//////////////////////////////////////////////////////////
	pObject->m_bStepXform		= m_bStepXform;	// if true:	Local->World->View
								// if False:Local->View		
	/////////////////////////////
	Math3D.BlockCopy((HUGEBLK)(&m_RInfo),(HUGEBLK)(&(pObject->m_RInfo)), sizeof(RENDINFO) );
	pObject->m_bClipped			= m_bClipped; 
	/////////////////////////////
	pObject->m_Color			= m_Color;
	pObject->m_dShrink			= m_dShrink;
	/////////////////////////////
	pObject->m_bParallel		= m_bParallel;
    pObject->m_nView			= m_nView;
    pObject->m_dzMin			= m_dzMin;
	pObject->m_dScale_U			= m_dScale_U;		// vv3DToLP:U-direction  
	pObject->m_dScale_V			= m_dScale_V;		// vv3DToLP:V-direction
	Math3D.BlockCopy((HUGEBLK)(&m_ViewM),(HUGEBLK)(&(pObject->m_ViewM)), sizeof(MATRIX) );
	Math3D.BlockCopy((HUGEBLK)(&m_ComposedM),(HUGEBLK)(&(pObject->m_ComposedM)), sizeof(MATRIX) );
	Math3D.BlockCopy((HUGEBLK)(&m_vv3DM),(HUGEBLK)(&(pObject->m_vv3DM)), sizeof(MATRIX) );
	/////////////////////////////////////////////////////////// 
	pObject->m_nLevelType		= m_nLevelType;
	pObject->m_nObjectType		= m_nObjectType;
	pObject->m_nElemType		= m_nElemType;	
	pObject->m_nObjectNo		= m_nObjectNo;
    /////////////////////////////////
	pObject->m_ObjectID			= m_ObjectID;
	/////////////////////////////////
	pObject->m_nLabelNo			= m_nLabelNo;
	//////////////////////////////
	Math3D.BlockCopy((HUGEBLK)(&m_rectBounding),(HUGEBLK)(&(pObject->m_rectBounding)), sizeof(CRect) );
//	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
    //////////////////////////////
	pObject->m_nPenWidth		= m_nPenWidth;    // pen width for Pipe
	pObject->m_crPenColor		= m_crPenColor;
	pObject->m_nPenStyle		= m_nPenStyle;
	////////////////////////////// HiLite 
	pObject->m_nPenWidthHi		= m_nPenWidthHi;    // pen width for Pipe
	pObject->m_crPenColorHi		= m_crPenColorHi;
	pObject->m_nPenStyleHi		= m_nPenStyleHi;
	////////////////////////////// 
	pObject->m_nLayer			= m_nLayer;
	///////////////////////////////////
	pObject->m_nLevel			= m_nLevel;				// Hierarchy Level
	/////////////////////////////////// 
	pObject->m_bGenerated		= m_bGenerated;			// generated by Curve or Patch
	pObject->m_bMoved			= m_bMoved;							
	pObject->m_bEdited			= m_bEdited;							
	pObject->m_bDeleted			= m_bDeleted;							
	pObject->m_bPosted			= m_bPosted;							
	pObject->m_bDirty			= m_bDirty;							
	pObject->m_bShow			= m_bShow;							
	/////////////////////////////////// 
    for(int i = 0; i<MAX_NODES_CORNER; i++)              // 
    {
    	pObject->m_ptMinMaxL[i]	= m_ptMinMaxL[i]; 
    	pObject->m_ptMinMaxW[i]	= m_ptMinMaxW[i]; 
    	pObject->m_ptMinMaxE[i]	= m_ptMinMaxE[i]; 
    	pObject->m_ptMinMaxS[i]	= m_ptMinMaxS[i]; 
    	pObject->m_pt[i]		= m_pt[i];
    }	
	///////////////////////////////////////////////////////////////////////////
	pObject->m_bLinSpr			= m_bLinSpr;
	pObject->m_bLinSnu			= m_bLinSnu;
	///////
	pObject->m_bToBeEdited		= m_bToBeEdited;							
	pObject->m_bToBeDeleted		= m_bToBeDeleted;							
	pObject->m_bToBeUnDeleted	= m_bToBeUnDeleted;							
	pObject->m_bToBePosted		= m_bToBePosted;							
	pObject->m_bToBeUnPosted	= m_bToBeUnPosted;							
	pObject->m_bToBeMoved		= m_bToBeMoved;							
	/////////////////////////////////// 
}

void CDrObject::SetObjectInfo(CDrObject* pObject)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////////
 	m_bFormatted		= pObject->m_bFormatted;
	///////////////////////////////////////////
	m_pMatObj			= pObject->m_pMatObj;
	m_bInstanced 		= pObject->m_bInstanced;
//	if( pAdd->m_bInstanced )
//		Math3D.BlockCopy((HUGEBLK)(&(pAdd->m_instanceXf)),(HUGEBLK)(&m_instanceXf), sizeof(MATRIX) );
	///////////////
	m_ParentID			= pObject->m_ParentID;
	m_SpawnType			= pObject->m_SpawnType;
	m_SubCat			= pObject->m_SubCat;
	m_Category			= pObject->m_Category;
	m_ElemDimLim		= pObject->m_ElemDimLim;
	//////////////////////////////////////////////////////////
	m_bStepXform		= pObject->m_bStepXform;	// if true:	Local->World->View
								// if False:Local->View		
	/////////////////////////////
	Math3D.BlockCopy((HUGEBLK)(&(pObject->m_RInfo)),(HUGEBLK)(&m_RInfo), sizeof(RENDINFO) );
	m_bClipped			= pObject->m_bClipped; 
	/////////////////////////////
	m_Color				= pObject->m_Color;
	m_dShrink			= pObject->m_dShrink;
	/////////////////////////////
	m_bParallel			= pObject->m_bParallel;
    m_nView				= pObject->m_nView;
    m_dzMin				= pObject->m_dzMin;
	m_dScale_U			= pObject->m_dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V			= pObject->m_dScale_V;		// vv3DToLP:V-direction
	Math3D.BlockCopy((HUGEBLK)(&(pObject->m_ViewM)),(HUGEBLK)(&m_ViewM), sizeof(MATRIX) );
	Math3D.BlockCopy((HUGEBLK)(&(pObject->m_ComposedM)),(HUGEBLK)(&m_ComposedM), sizeof(MATRIX) );
	Math3D.BlockCopy((HUGEBLK)(&(pObject->m_vv3DM)),(HUGEBLK)(&m_vv3DM), sizeof(MATRIX) );
	/////////////////////////////////////////////////////////// 
	m_nLevelType		= pObject->m_nLevelType;
	m_nObjectType		= pObject->m_nObjectType;
	m_nElemType			= pObject->m_nElemType;	
	m_nObjectNo			= pObject->m_nObjectNo;
    /////////////////////////////////
	m_ObjectID			= pObject->m_ObjectID;
	/////////////////////////////////
	m_nLabelNo			= pObject->m_nLabelNo;
	//////////////////////////////
	Math3D.BlockCopy((HUGEBLK)(&m_rectBounding),(HUGEBLK)(&(pObject->m_rectBounding)), sizeof(CRect) );
//	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
    //////////////////////////////
	m_nPenWidth			= pObject->m_nPenWidth;    // pen width for Pipe
	m_crPenColor		= pObject->m_crPenColor;
	m_nPenStyle			= pObject->m_nPenStyle;
	////////////////////////////// HiLite 
	m_nPenWidthHi		= pObject->m_nPenWidthHi;    // pen width for Pipe
	m_crPenColorHi		= pObject->m_crPenColorHi;
	m_nPenStyleHi		= pObject->m_nPenStyleHi;
	////////////////////////////// 
	m_nLayer			= pObject->m_nLayer;
	///////////////////////////////////
	m_nLevel			= pObject->m_nLevel;				// Hierarchy Level
	/////////////////////////////////// 
	m_bGenerated		= pObject->m_bGenerated;			// generated by Curve or Patch
	m_bMoved			= pObject->m_bMoved;							
	m_bEdited			= pObject->m_bEdited;							
	m_bDeleted			= pObject->m_bDeleted;							
	m_bPosted			= pObject->m_bPosted;							
	m_bDirty			= pObject->m_bDirty;							
	m_bShow				= pObject->m_bShow;							
	/////////////////////////////////// 
    for(int i = 0; i<MAX_NODES_CORNER; i++)              // 
    {
    	m_ptMinMaxL[i]	= pObject->m_ptMinMaxL[i]; 
    	m_ptMinMaxW[i]	= pObject->m_ptMinMaxW[i]; 
    	m_ptMinMaxE[i]	= pObject->m_ptMinMaxE[i]; 
    	m_ptMinMaxS[i]	= pObject->m_ptMinMaxS[i]; 
    	m_pt[i]			= pObject->m_pt[i];
    }	
	///////////////////////////////////////////////////////////////////////////
	m_bLinSpr			= pObject->m_bLinSpr;
	m_bLinSnu			= pObject->m_bLinSnu;
	///////
	m_bToBeEdited		= pObject->m_bToBeEdited;							
	m_bToBeDeleted		= pObject->m_bToBeDeleted;							
	m_bToBeUnDeleted	= pObject->m_bToBeUnDeleted;							
	m_bToBePosted		= pObject->m_bToBePosted;							
	m_bToBeUnPosted		= pObject->m_bToBeUnPosted;							
	m_bToBeMoved		= pObject->m_bToBeMoved;							
	/////////////////////////////////// 
}

/*****************************************************************************
 *
 *	Function:	SetObjectRenderingAttribs()
 *
 *	Purpose:	Sets the rendering attributes for an Object.
 *
 *
 *****************************************************************************
*/  
void CDrObject::SetRInfo(pRENDINFO pRA)
{

	C3DMath Math3D;
	////////////////////
	Math3D.BlockCopy((HUGEBLK)(pRA),(HUGEBLK)(&m_RInfo), sizeof(RENDINFO) );
	///////////////
	return;
}	

/////////////////////////////////////////////////////////////////
void CDrObject::Transform(pWORLD pptIn, pWORLD pptOut)
{
	
	CXForm XForm(m_bParallel);
	/////////////////////////////////////
	XForm.Transform(pptIn,pptOut,&m_ViewM);
	/////////////////////////////////////	
    return;
}                            

void CDrObject::Project(pWORLD pptIn, pWORLD pptOut,BOOL bSize)
{

	CXForm XForm(m_bParallel);
	////////////////////////////////
	WORLD pt2;
	/////////////////////////////////////
	XForm.Project(&m_vv3DM,pptIn,&pt2);
	//////////////////////////////////////////////// end transform/Project
	if(bSize)
	{
		pptOut->x = (int)(pt2.x * m_dScale_U);
		pptOut->y = (int)(pt2.y * m_dScale_V);
	}
	else	
	{
		pptOut->x = pt2.x;
		pptOut->y = pt2.y;
		pptOut->z = pt2.z;
	}
    //////////////////////////////////////////////// Restore Old 3d context
//	pXForm->SetZoom(dzoom );
	////////////////////////
    return;
}                            

void CDrObject::DrawPoint3D(CDC* pDC,double x1,double y1,double z1,COLORREF C) 
{
	WORLD	FromPt;
    /////////
	FromPt.x	= x1;
	FromPt.y	= y1;
	FromPt.z	= z1;
	////////////////////////////////////////// Transform/Clip/Project
	WORLD 	Per;
	////////////
	Transform(&FromPt, &FromPt);
	/////////////////////////
	CDrClip DrClip(m_dzMin, !m_bParallel, FALSE); 
	if( DrClip.ClipPt( &FromPt ) == VI_NOT_VISIBLE )
		return;
	/////////////////////////////////////// if Perspective,change Pers->Par
	if(!m_bParallel)
	{
		CXForm XForm(m_bParallel);
		XForm.TransformPerToParCVV(m_dzMin, &FromPt, &Per);
		FromPt = Per; 
	}	 
	Project(&FromPt,&FromPt,TRUE);
	////////////////////////////////////////// Points
	POINT ptF;
	ptF.x = (int)(FromPt.x);
	ptF.y = (int)(FromPt.y);
	///////////////////////////////////////////////////////////////////// Draw 
	pDC->SetPixel( ptF, C );
	/////////////////
}

void CDrObject::DrawPoint3D(CDC* pDC,pWORLD Pt3D,COLORREF C) 
{
	WORLD	FromPt;
    /////////
	FromPt.x	= Pt3D->x;
	FromPt.y	= Pt3D->y;
	FromPt.z	= Pt3D->z;
	////////////////////////////////////////// Transform/Clip/Project
	WORLD 	Per;
	////////////
	Transform(&FromPt, &FromPt);
	/////////////////////////
	CDrClip DrClip(m_dzMin, !m_bParallel, FALSE); 
	if( DrClip.ClipPt( &FromPt ) == VI_NOT_VISIBLE )
		return;
	/////////////////////////////////////// if Perspective,change Pers->Par
	if(!m_bParallel)
	{
		CXForm XForm(m_bParallel);
		XForm.TransformPerToParCVV(m_dzMin, &FromPt, &Per);
		FromPt = Per; 
	}	 
	Project(&FromPt,&FromPt,TRUE);
	////////////////////////////////////////// Points
	POINT ptF;
	ptF.x = (int)(FromPt.x);
	ptF.y = (int)(FromPt.y);
	///////////////////////////////////////////////////////////////////// Draw 
	pDC->SetPixel( ptF, C );
	/////////////////
}

void CDrObject::DrawLine3D
						(
							CDC* pDC,pWORLD A, pWORLD B, BOOL Xformed
						) 
{
	WORLD	FromPt,ToPt;
    /////////
	FromPt.x	= A->x;
	FromPt.y	= A->y;
	FromPt.z	= A->z;
	ToPt.x		= B->x;
	ToPt.y		= B->y;
	ToPt.z		= B->z;
	////////////////////////////////////////// Transform/Clip/Project
	WORLD 	Per;
	////////////
	if(!Xformed)                       // if not already Transformed like in Convex Hull
	{
		Transform(&FromPt, &FromPt);
		Transform(&ToPt, &ToPt);
	}	
	/////////////////////////
	CDrClip DrClip(m_dzMin, !m_bParallel, FALSE); 
	if( DrClip.ClipLine_SC( &FromPt, &ToPt ) == VI_NOT_VISIBLE )
		return;
	/////////////////////////////////////// if Perspective,change Pers->Par
	if(!m_bParallel)
	{
		CXForm XForm(m_bParallel);
		XForm.TransformPerToParCVV(m_dzMin, &FromPt, &Per);
		FromPt = Per; 
		XForm.TransformPerToParCVV(m_dzMin, &ToPt, &Per);
		ToPt = Per; 
	}	 
	Project(&FromPt,&FromPt,TRUE);
	Project(&ToPt,&ToPt,TRUE);
	////////////////////////////////////////// Points
	POINT ptF,ptT;
	ptF.x = (int)(FromPt.x);
	ptF.y = (int)(FromPt.y);
	ptT.x = (int)(ToPt.x);
	ptT.y = (int)(ToPt.y);
	///////////////////////////////////////////////////////////////////// Draw 
	pDC->MoveTo(ptF);
	pDC->LineTo(ptT);
/*
	////////////////////////////////////// put a blob (temporary: green)
	CRect R;
	R.left 	= ptT.x - 2;
	R.right	= ptT.x + 2;
	R.top	= ptT.y - 2;
	R.bottom= ptT.y + 2;
	
	pDC->Rectangle( &R );
	/////////////////////
*/
}

void CDrObject::DrawLine3D
						(
							CDC* pDC,
							double x1,double y1,double z1,
							double x2,double y2,double z2, 
							BOOL Xformed
						) 
{
	WORLD	FromPt,ToPt;
    /////////
	FromPt.x	= x1;
	FromPt.y	= y1;
	FromPt.z	= z1;
	ToPt.x		= x2;
	ToPt.y		= y2;
	ToPt.z		= z2;
	////////////////////////////////////////// Transform/Clip/Project
	WORLD 	Per;
	////////////
	if(!Xformed)                       // if not already Transformed like in Convex Hull
	{
		Transform(&FromPt, &FromPt);
		Transform(&ToPt, &ToPt);
	}	
	/////////////////////////
	CDrClip DrClip(m_dzMin, !m_bParallel, FALSE); 
	if( DrClip.ClipLine_SC( &FromPt, &ToPt ) == VI_NOT_VISIBLE )
		return;
	/////////////////////////////////////// if Perspective,change Pers->Par
	if(!m_bParallel)
	{
		CXForm XForm(m_bParallel);
		XForm.TransformPerToParCVV(m_dzMin, &FromPt, &Per);
		FromPt = Per; 
		XForm.TransformPerToParCVV(m_dzMin, &ToPt, &Per);
		ToPt = Per; 
	}	 
	Project(&FromPt,&FromPt,TRUE);
	Project(&ToPt,&ToPt,TRUE);
	////////////////////////////////////////// Points
	POINT ptF,ptT;
	ptF.x = (int)(FromPt.x);
	ptF.y = (int)(FromPt.y);
	ptT.x = (int)(ToPt.x);
	ptT.y = (int)(ToPt.y);
	///////////////////////////////////////////////////////////////////// Draw 
	pDC->MoveTo(ptF);
	pDC->LineTo(ptT);
	/////////////////
}

void CDrObject::GetLocalCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	pPos->x	= m_ptMinMaxL[index].x;
   	pPos->y	= m_ptMinMaxL[index].y;
   	pPos->z	= m_ptMinMaxL[index].z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::SetLocalCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	m_ptMinMaxL[index].x = pPos->x;
   	m_ptMinMaxL[index].y = pPos->y;
   	m_ptMinMaxL[index].z = pPos->z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::GetWorldCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	pPos->x	= m_ptMinMaxW[index].x;
   	pPos->y	= m_ptMinMaxW[index].y;
   	pPos->z	= m_ptMinMaxW[index].z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::SetWorldCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	m_ptMinMaxW[index].x = pPos->x;
   	m_ptMinMaxW[index].y = pPos->y;
   	m_ptMinMaxW[index].z = pPos->z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::GetEyeCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	pPos->x	= m_ptMinMaxE[index].x;
   	pPos->y	= m_ptMinMaxE[index].y;
   	pPos->z	= m_ptMinMaxE[index].z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::SetEyeCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	m_ptMinMaxE[index].x = pPos->x;
   	m_ptMinMaxE[index].y = pPos->y;
   	m_ptMinMaxE[index].z = pPos->z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::GetScreen3DCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	pPos->x	= m_ptMinMaxS[index].x;
   	pPos->y	= m_ptMinMaxS[index].y;
   	pPos->z	= m_ptMinMaxS[index].z;
   	//////////////////////////////////////////
   	return;
}

void CDrObject::SetScreen3DCorner(pWORLD pPos, int index)
{
  	//	Change to Bounding Volume MinMax Coordinates
	//////////////////////////////////////////
   	m_ptMinMaxS[index].x = pPos->x;
   	m_ptMinMaxS[index].y = pPos->y;
   	m_ptMinMaxS[index].z = pPos->z;
   	//////////////////////////////////////////
   	return;
}
///////////////////////////////////////////////////////////////////////////// WRITE
void CDrObject::AddStr(CString* pstrDestin,CString* pstrSource, int nCount)
{
    int nLen;

    nLen = pstrSource->GetLength();
//    strcat(t,e);
    *pstrDestin += *pstrSource;
    while(nLen++<nCount)
//      strcat(t," "); 
		*pstrDestin += " ";
//    strcat(t,",");
	if(!IsFormatted())
		*pstrDestin += ",";    
    return;
}

void CDrObject::sprintn(char* s, long n, long lWorldBase, CString FmtStr)
{

	char sign = ' ';
	
	if(n<0) sign = '-';
	
	sprintf(s,FmtStr.operator const char*(),(UINT)labs(n/lWorldBase),(UINT)labs(n%lWorldBase) );
	while(*s==' ')s++;
	*--s = sign;
	return;
	
}

void CDrObject::AddNum(CString* pstrDestin,long lNumber,long lmf,long lBase, CString FmtStr)                                        //drPipe
{

//	lNumber is supposed to have been multiplied already by WorldBase
    char tt[MAXSTRINGLENGTH];
//    long lmf;

//    lmf = (Master_Table[0].fac==0L) ? 1L*FmtBase: Master_Table[0].fac;
//    sprintn(tt,n*FmtBase/lmf);
    sprintn(tt,lNumber/lmf, lBase, FmtStr);
    tt[10]=0;
    CString strSource = tt;                      // maximum 10 characters
    AddStr(pstrDestin,&strSource,10); 
    
    return;
}

void CDrObject::AddInt(CString* pstrDestin,int nNum)
{
    char tt[10];
    sprintf(tt,"% 5d",nNum);
    CString strSource = tt;
    AddStr(pstrDestin,&strSource,5);
}

void CDrObject::AddDouble(CString* pstrDestin,double d)
{
    char tt[10];
    sprintf(tt,"%.10G",d);
    CString strSource = tt;
    AddStr(pstrDestin,&strSource,5);
}
/*
void CDrObject::SetEndPointCoord(long* lSrc,int nPrecision,
													POINT* ptDest, int nEnd)
{

	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CXForm* pXForm = (CXForm*)pObjectMgr->GetSpecObject(XFORM);
	//////////////////////////////////////////////// Transform & Project
	// Matrix must correspond to the Current View
	// set by caller in View
	//////////////////////////////////////////////// 
	long ldest[3];
	////////////////////////////////////////// 
	Matrix m		= *(pXForm->DrGetMatrix(MT_VIEWER));
	pXForm->DrApplyTransform(lSrc,ldest,&m,nPrecision);
	///////////////
	POINT ptdest2;
	pXForm->DrProject(ldest,&ptdest2,nPrecision);
	//////////////////////////////////////////////// end transform/Project
	ptDest[nEnd].x = ptdest2.x;
	ptDest[nEnd].y = ptdest2.y;
	////////////////////////////////

}                            
*/
//////////////////////////////////////////////////////////////////////// Drawing Help

/*****************************************************************************
 *
 *	Function:	SetLocalTransform()
 *
 *	Purpose:	Sets the instance transform MATRIX for a Curve.  A nil MATRIX
 *				address will reset the instanced boolean for the Curve, with
 *				the result equivalent to setting the MATRIX to identity since
 *				no nested instance transform will be applied.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */ 
int CDrObject::SetLocalTransform(pMATRIX pXf)
{
/*
	C3DMath Math3D;
	////////////////////
	m_bInstanced = (BOOL)(pXf != 0);
	if( pXf )
		Math3D.BlockCopy((HUGEBLK)(pXf),(HUGEBLK)(&m_instanceXf), sizeof(MATRIX) );
*/
	///////////////
	return -1;
}	

/*****************************************************************************
 *
 *	Function:	CatLocalTransform()
 *
 *	Purpose:	Concatenates (multiplies) an instancing transform MATRIX with
 *				the existing instance transform MATRIX of a Curve.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */
int CDrObject::CatLocalTransform(pMATRIX pXf)
{

	/*
	C3DMath* p3DMath;
	////////////////////
	if(m_bInstanced)
		p3DMath->MultMATRIX(&m_instanceXf, pXf, &m_instanceXf);
//		mMult4x4(&m_instanceXf, pXf, &m_instanceXf );
	else
		p3DMath->BlockCopy((HUGEBLK)(pXf),(HUGEBLK)(&m_instanceXf), sizeof(MATRIX) );
	m_bInstanced = TRUE;
*/	
	///////////////
	return -1;
}	


/*****************************************************************************
 *
 *	Function:	GetLocalTransform()
 *
 *	Purpose:	Retrieves the instance transform MATRIX for a Curve.
 *
 *	Returns:	INVALID_REQUEST		if null in hG, or index is out of bounds
 *									for the group or the target address (xf)
 *									is null.
 *				noErr				otherwise
 *
 *****************************************************************************
 */
int CDrObject::GetLocalTransform(pMATRIX pXfMat)
{
/*
	C3DMath Math3D;
	//////////////////////////////////////////////// Transform
	pMATRIX pXf;
	if(m_bInstanced)
		pXf = &m_instanceXf;
	else
	{
		C3DMath* p3DMath;
		p3DMath->GetIdentityMATRIX(pXf);
	}	
	////////////////////	
	Math3D.BlockCopy((HUGEBLK)(pXf),(HUGEBLK)(pXfMat), sizeof(MATRIX) );
*/
	///////////////
	return -1;
}	


void CDrObject::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	if (ar.IsStoring())
	{
		TRACE( " DrObject	:Storing\n");	// TODO: add storing code here

 	}
	else
	{
		TRACE(" DrObject	:Loading\n");	// TODO: add loading code here

	}        
	////////////////////////

}
	

//////////////////////////////// end of module ///////////////////////////// 
