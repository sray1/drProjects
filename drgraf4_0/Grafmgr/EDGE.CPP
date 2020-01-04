// Patch.cpp : implementation file
//


#include "stdafx.h"
#include <limits.h>		// MSVC/INC for LONG_MAX,LONG_MIN

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "globals.h"
#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "3Ddefine.h"
#include "XForm.h"
////////////////////// TopLevels
#include "TLextern.h"
#include "TLDefine.h"
////////////////////// elObjs
#include "elextern.h"
#include "eldefine.h"
#include "Node.h"
/////////////////////
#include "3DMath.h"
#include "Patch.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrPatch
IMPLEMENT_SERIAL(CDrPatch, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrPatch, CDrObject)
	//{{AFX_MSG_MAP(CDrPatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrPatch::CDrPatch()
{  
    	
    //////////////////////////////	
    SetObjectType((int)PATCH);
    SetElemType((int)EL3D_OBJECT);          //
    //////////////////////////////  
	m_ObjectID		= " ";
//	m_instanceXf 	= ;
//	m_raOptions		=;
	m_bInstanced	= FALSE;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

int CDrPatch::DealObjectDialog()
{
/*
	CDrPatchProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrPatch::SetObjectInfo(CDrObject* pObject)
{
	
	CDrPatch* pAddPatch = (CDrPatch*) pObject;
	///////////////////////////////////////////////////////////////////
	m_nElemType			= pAddPatch->m_nElemType;
	////////////////////////////////////////////////////////   
	m_rectBounding		= pAddPatch->m_rectBounding; // smallest rect that surrounds 

	m_nObjectType		= pAddPatch->m_nObjectType; 
	m_nObjectNo			= pAddPatch->m_nObjectNo;
	
	SetPenInfo(pAddPatch->m_nPenWidth,pAddPatch->m_crPenColor,pAddPatch->m_nPenStyle);
	
	m_nLayer    		= pAddPatch->m_nLayer;
	////////////////////////////////////////////////////////
	m_ObjectID			= pAddPatch->m_ObjectID;
	//////////////////////////////////////////////////////// CopyList
	m_NodeList.AddTail(pAddPatch->GetNodeList() ); 
	m_PolyList.AddTail(pAddPatch->GetPolyList() );
	////////////////////////////////////////////// 
	BlockCopy((PMBLK)(&(pAddPatch->m_raOptions)),(PMBLK)(&m_raOptions), sizeof(RendAttr) );
	m_bInstanced 		= pAddPatch->m_bInstanced;
	if( pAddPatch->m_bInstanced )
		BlockCopy((PMBLK)(&(pAddPatch->m_instanceXf)),(PMBLK)(&m_instanceXf), sizeof(Matrix) );
	///////////////
    for(int i = 0; i<MAX_NODES_VOLUME; i++)              // 
    {
    	m_pt[i] = pAddPatch->m_pt[i];
	}
	///////////////////////////////////	
	return;
}		

void CDrPatch::GetObjectInfo(CDrObject* pObject)
{
	
	CDrPatch* pAddPatch = (CDrPatch*) pObject;
	///////////////////////////////////////////////////////////////////   
	pAddPatch->m_nElemType				= m_nElemType;	
	////////////////////////////////////////////	
 	pAddPatch->m_rectBounding			= m_rectBounding; // smallest rect that surrounds 

	pAddPatch->m_nObjectType 			= m_nObjectType; 
	pAddPatch->m_nObjectNo				= m_nObjectNo;
	                                    
   	pAddPatch->SetPenInfo(m_nPenWidth,m_crPenColor,m_nPenStyle);
	/////////////////////// 
	pAddPatch->m_nLayer		    		= m_nLayer;
	////////////////////////////////////////////////////////
	pAddPatch->m_ObjectID				= m_ObjectID;
	//////////////////////////////////////////////////////// CopyList
	pAddPatch->GetNodeList()->AddTail(&m_NodeList); 
	pAddPatch->GetPolyList()->AddTail(&m_PolyList); 
	////////////////////////////////////////////// 
	BlockCopy((PMBLK)(&m_raOptions),(PMBLK)(&(pAddPatch->m_raOptions)), sizeof(RendAttr) );
	pAddPatch->m_bInstanced 			= m_bInstanced;
	if( m_bInstanced )
		BlockCopy((PMBLK)(&m_instanceXf),(PMBLK)(&(pAddPatch->m_instanceXf)), sizeof(Matrix) );
	///////////////
    for(int i = 0; i<MAX_NODES_VOLUME; i++)              // 
    {
    	pAddPatch->m_pt[i] = m_pt[i];
	}
	///////////////////////////////////	
	return;
}		

void CDrPatch::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrPatch::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_TLevelTypes;i++)
   		if(TLTypes[i].num == PATCH) 
   		{
   			name = TLTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
//	m_PatchCard.bValve  = FALSE;  
   AddStr(pstrCard,&name,5); 
   AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}   

void CDrPatch::GetRawCoords(long* lCoord, int* pnPrecision, int index)
{
/*  Change to Bounding Volume Coordinates                        todo
	//////////////////////////////////////////
   	lCoord[0] 		= m_pDrNode[index]->GetNodeCard()->x;
   	lCoord[1] 		= m_pDrNode[index]->GetNodeCard()->y;
   	lCoord[2]		= m_pDrNode[index]->GetNodeCard()->z;
   	*pnPrecision 	= m_pDrNode[index]->GetPrecision();
   	//////////////////////////////////////////
   	return;
*/    
}
                            
void CDrPatch::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
/*
    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,m_pt,bPenChange);
   	//////////////////////////////////////////
*/    
}                            

void CDrPatch::GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange)
{ 
/*
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
    if(!bPenChange)
    {
		// Create normal Pen for Node
	   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor); 
	}
	else		   	
	{
		// Create Green Pen 1 Pixel wide;
		int nPenColor = GREEN;
		int nPenWidth = 2;   
	   	Pen.CreatePen (m_nPenStyle,nPenWidth,nPenColor);
	}	   	
   	PtrOldPen = PtrDC->SelectObject(&Pen);
    //////////////////////////////////// Line
	PtrDC->MoveTo(pt[0]);
	PtrDC->LineTo(pt[1]);
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
*/   	
}   

/////////////////////////////////////////////////////////////////////////////
void CDrPatch::FinishObject()
{ 
/*
	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
	m_rectBounding = CRect(m_pt[0].x, m_pt[0].y, m_pt[0].x, m_pt[0].y);

	for ( int i=1; i < MAX_Patch_DRAW_PT; i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		m_rectBounding.left     = min(m_rectBounding.left, m_pt[i].x);
		m_rectBounding.right    = max(m_rectBounding.right, m_pt[i].x);
		m_rectBounding.top      = max(m_rectBounding.top, m_pt[i].y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, m_pt[i].y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Patch when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	///////
	return; 
*/	
} 

BOOL CDrPatch::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrPatch* pDrPatch = (CDrPatch*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrPatch->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrPatch::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrPatch* pPatch = (CDrPatch*)pObject;
		///////////////////////////////////
		if(pPatch->GetObjectType() == PATCH)
		{
			CSize	Size; 
		/*	
			int nType = pLabel->GetType();
			///////////////////////////////////////// LeftTop Corner
			POINT pointTemp = pLabel->GetCorner(nType,nViewNumber);
	       	///////////////////////////////////////// LOG/Scaled
			pRect->left = pointTemp.x;
	    	pRect->top	= pointTemp.y;
	    	///////////////////////////////////////// get FontSize etc.
			CFont	Font;
			Font.DeleteObject;
			Font.CreateFontIndirect(&(pLabel->m_lf));
			CFont* pOldFont = (CFont*) ptrDC->SelectObject(&Font);
			Size		  = ptrDC->GetTextExtent(pLabel->m_Text,
											(pLabel->m_Text).GetLength());
			ptrDC->SelectObject(pOldFont);
			////////////////////////////////////////////////////////////
	    	pRect->right  = pRect->left + Size.cx; 
	    	pRect->bottom = pRect->top  - Size.cy; // Logical
	    	////////////////////////////// Assumed View12
	    	if((point.x>=pRect->left) && (point.x<=pRect->right) &&
	       		(point.y<=pRect->top ) && (point.y>=pRect->bottom)) 
	    	{
		       	return i; 
	    	}
	    	///////////////////
	    */	
		}
	///////////////
	return FALSE;
}

/*****************************************************************************
 *
 *	Function:	AppendToPatch()
 *
 *	Purpose:	Given an array of facets and an array of vertices, expands a
 *				specified patch appending new vertices and facets.
 *
 *	Returns:	INVALID_REQUEST		if patch index is bad or hGroup is nil
 *				MEMORY_ALLOC_ERROR	if any memory error occurs
 *				noErr				if successfull
 *
 *****************************************************************************
 */ 
int CDrPatch::AppendToObject(CDListMgr* pPolyList, CDListMgr* pNodeList)
{							
	////////////////////
	if(pNodeList && !(pNodeList->IsEmpty())  )
		GetNodeList()->AddTail(pNodeList);
	else
		return -1;
	if(pPolyList && !(pPolyList->IsEmpty()) )
		GetPolyList()->AddTail(pPolyList);
	else
		return -1;
	///////////////
	return 0;	
}

/*****************************************************************************
 *
 *	Function:	SetPatchTransform()
 *
 *	Purpose:	Sets the instance transform matrix for a patch.  A nil matrix
 *				address will reset the instanced boolean for the patch, with
 *				the result equivalent to setting the matrix to identity since
 *				no nested instance transform will be applied.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */ 
int CDrPatch::SetObjectTransform(pMatrix pXf)
{

	////////////////////
	m_bInstanced = (Boolean)(pXf != 0);
	if( pXf )
		BlockCopy((PMBLK)(pXf),(PMBLK)(&m_instanceXf), sizeof(Matrix) );
	///////////////
	return 0;
}	

/*****************************************************************************
 *
 *	Function:	CatPatchTransform()
 *
 *	Purpose:	Concatenates (multiplies) an instancing transform matrix with
 *				the existing instance transform matrix of a patch.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */
int CDrPatch::CatObjectTransform(pMatrix pXf)
{

	C3DMath* p3DMath;
	////////////////////
	if(m_bInstanced)
		p3DMath->MultMatrix(&m_instanceXf, pXf, &m_instanceXf);
//		mMult4x4(&m_instanceXf, pXf, &m_instanceXf );
	else
		BlockCopy((PMBLK)(pXf),(PMBLK)(&m_instanceXf), sizeof(Matrix) );
	m_bInstanced = TRUE;	
	///////////////
	return 0;
}	


/*****************************************************************************
 *
 *	Function:	GetPatchTransform()
 *
 *	Purpose:	Retrieves the instance transform matrix for a patch.
 *
 *	Returns:	INVALID_REQUEST		if null in hG, or index is out of bounds
 *									for the group or the target address (xf)
 *									is null.
 *				noErr				otherwise
 *
 *****************************************************************************
 */
int CDrPatch::GetObjectTransform(pMatrix pXfMat)
{

	////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CXForm* pXForm = (CXForm*)pObjectMgr->GetSpecObject(XFORM);
	//////////////////////////////////////////////// Transform
	pMatrix pXf;
	if(m_bInstanced)
		pXf = &m_instanceXf;
	else
//		return -1;
		pXf = pXForm->DrGetMatrix(MT_IDENTITY);
	////////////////////	
	BlockCopy((PMBLK)(pXf),(PMBLK)(pXfMat), sizeof(Matrix) );
	m_bInstanced = TRUE;	
	///////////////
	return 0;
}	

/*****************************************************************************
 *
 *	Function:	SetPatchRenderingAttribs()
 *
 *	Purpose:	Sets the rendering attributes for a patch.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */ 
int CDrPatch::SetObjectRAttribs(pRendAttr pRA)
{

	////////////////////
	BlockCopy((PMBLK)(pRA),(PMBLK)(&m_raOptions), sizeof(RendAttr) );
	///////////////
	return 0;
}	

/*****************************************************************************
 *
 *	Function:	SetPatchRefCon()
 *
 *	Purpose:	Sets the reference constant for a patch and its facets.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
 */ 
/* 
OsErr	API3D SetPatchRefCon(hGroup hG,int ix,pREFCON3D refCon)
{
	hPatch		hP;
	pPatch		pP;
	pFacet		pF;
	int			nF;

	if( ( !hG ) || ( ix<0 ) )
		return	INVALID_REQUEST;
	if( ( !hG->hP ) || ( ix>=hG->nP ) )
		return	INVALID_REQUEST;
	hP = hG->hP;
	pP = (pPatch)hP + (long)ix;
	pP->refCon = (DWORD FAR*)refCon;
	nF = pP->nF;
	pF = (pFacet)pP->hF;
	while( nF-- ) {
		pF->refCon = (DWORD FAR*)refCon;
		pF++;
	}
	return	noErr;
}

/*****************************************************************************
 *
 *	Function:	GetPatchBounds()
 *
 *	Purpose:	Retrieves the 3d bounds of a patch.
 *
 *	Returns:	INVALID_REQUEST		if any parameter is bad
 *				noErr				otherwise
 *
 *****************************************************************************
 */
int CDrPatch::GetObject3DBounds(LPOINT3* pMin, LPOINT3* pMax)
{

	////////////////////
	if(!pMin || !pMax)
		return -1;
	////////////////////	
	LPOINT3	min,max,Coords;
	min.x = LONG_MAX; 
	min.y = LONG_MAX; 
	min.z = LONG_MAX;
	 
	max.x = LONG_MIN; 
	max.y = LONG_MIN; 
	max.z = LONG_MIN;
	/////////////////////////////////////// 
	CDListMgr*	pNodeList = GetNodeList();
	///////////////////////////////////////////////////////////////////
	for (POSITION pos = pNodeList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pNodeList->GetNextObject(pos);
		if(!pNode)
			continue;
		///////////////////////
		Coords.x = (pNode->GetNodeCard())->x; 				
		Coords.y = (pNode->GetNodeCard())->y; 				
		Coords.z = (pNode->GetNodeCard())->z;
		///////////////////////////////////// compare and adjust
		if(Coords.x<min.x) min.x = Coords.x; 				
		if(Coords.y<min.y) min.y = Coords.y; 				
		if(Coords.z<min.z) min.z = Coords.z;
		 				
		if(Coords.x>max.x) max.x = Coords.x; 				
		if(Coords.y>max.y) max.y = Coords.y; 				
		if(Coords.z>max.z) max.z = Coords.z;
		//////////////////////////////////// 				
	}
	/////////////
	*pMin = min;
	*pMax = max;
	////////////
	return	0;
}

void CDrPatch::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	int nCount;     
	WORD	nElementType,nObjectNo,nObjectType,nPenWidth,nPenStyle,nLayer;
	DWORD   crPenColor;
	WORD	wCount;
	
	if (ar.IsStoring())
	{
		TRACE( " Patch   :Storing\n");	// TODO: add loading code here

		ar	<<	/*int*/		(WORD)m_nElemType	// Type = Patch = 2 in ElGlobal.h
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			///////////////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Patch Ends measured in MM_LOENGLISH units
			
			<<	/*UINT*/	(WORD)m_nPenWidth    // pen width for Pipe
			<<	/*COLORREF*/(DWORD)m_crPenColor
			<<	/*UINT*/	(WORD)m_nPenStyle 
			
			<<	/*UINT*/	(WORD)m_nLayer;
		/////////////////////////////////////////////// Lists
		UINT nCount = m_NodeList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_NodeList.Serialize(ar);	
		nCount = m_PolyList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_PolyList.Serialize(ar);
		////////////////////////////////////////////////		
		for(int i=0; i<MAX_NODES_VOLUME;i++)	
			ar	<<	/*POINT*/	m_pt[i];



 	}
	else
	{
	
		TRACE( " Patch   :Loading\n");	// TODO: add loading code here


		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo 
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Patch Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
		  	>>	/*UINT*/	nPenWidth    // pen width for Pipe
			>>	/*COLORREF*/crPenColor
			>>	/*UINT*/	nPenStyle 
			>>	/*UINT*/	nLayer;
		/////////////////////////////////////////////// Lists
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_NodeList.Serialize(ar);	
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_PolyList.Serialize(ar);
		////////////////////////////////////////////////		
		for(int i=0; i<MAX_NODES_VOLUME;i++)	
			ar	>>	/*POINT*/	m_pt[i];

    //////////////////////////////////////////////    
	m_nElemType		  	= 	(int)nElementType;		// Type = Patch = 2 in ElGlobal.h

    m_nObjectType		= 	(int)nObjectType;
    m_nObjectNo			= 	(UINT)nObjectNo;
	m_nPenWidth 		=	(UINT)nPenWidth;    // pen width for Pipe
	m_crPenColor 		= 	(COLORREF)crPenColor;
	m_nPenStyle 		= 	(UINT)nPenStyle; 
	m_nLayer			=	(UINT)nLayer;
    //////////////////////////////////////////////        

	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

