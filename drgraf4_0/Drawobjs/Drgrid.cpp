// Pipe.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "Def_Type.h"
#include "Def_Objs.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// ElObjs
#include "Def_Elem.h"
#include "drNode.h"
////////////////////// DrObjs
#include "Ext_Draw.h"
#include "Def_Draw.h"
//////////////
#include "DrGrid.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrGrid
IMPLEMENT_SERIAL(CDrGrid, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrGrid, CDrObject)
	//{{AFX_MSG_MAP(CDrGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrGrid::CDrGrid()
{  
    	
    //////////////////////////////	
    SetObjectType((int)GRID);
    SetElemType((int)DRAW_OBJECT);          //
    //////////////////////////////  
	m_GrInfo.gridtype  	= 0;
	m_GrInfo.screenful	= 0;
	m_GrInfo.alignment	= 0;
	m_GrInfo.left  		= TRUE;
	m_GrInfo.right  	= FALSE;
	m_GrInfo.top  		= FALSE;
	m_GrInfo.bottom  	= TRUE;
	m_GrInfo.back  		= TRUE;
	m_GrInfo.front  	= FALSE;
	m_GrInfo.connectX 	= FALSE;
	m_GrInfo.connectY   = FALSE; 
	m_GrInfo.connectZ   = FALSE; 
	m_GrInfo.rotation   = FALSE; 
	m_dAngle	= 0;    // screen rotation for snap 
	m_wStep.x	= 10;		
	m_wStep.y	= 10;		
	m_wStep.z	= 10;		
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

CDrGrid::~CDrGrid()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrGrid::ReadyToDelete()
{
	////////////////////////////////////// unload Nodes/No delete
	CDListMgr* pNodeList = GetNodeList();
    //////////////////////////////////////
	CDrObject* pObject,pElem;
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //Node
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pElemList = pObject->GetElemList();
			int index = pElemList->GetObjectIndex(this);
			if(index>=0)
				pElemList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
}

int CDrGrid::DealObjectDialog()
{
/*
	CPipeProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrGrid::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrGrid* pAdd = (CDrGrid*) pObject;
	///////////////////////////////////////////////////// GridINFO
	m_NodeList.AddTail(pAdd->GetNodeList() ); 
	////////////////////////////////////////////////////////   
	m_GrInfo.gridtype  	= (pAdd->GetGrInfo())->gridtype;
	m_GrInfo.screenful	= (pAdd->GetGrInfo())->screenful;
	m_GrInfo.alignment	= (pAdd->GetGrInfo())->alignment;
	m_GrInfo.left  		= (pAdd->GetGrInfo())->left;
	m_GrInfo.right  	= (pAdd->GetGrInfo())->right;
	m_GrInfo.top  		= (pAdd->GetGrInfo())->top;
	m_GrInfo.bottom  	= (pAdd->GetGrInfo())->bottom;
	m_GrInfo.back  		= (pAdd->GetGrInfo())->back;
	m_GrInfo.front  	= (pAdd->GetGrInfo())->front;
	m_GrInfo.connectX 	= (pAdd->GetGrInfo())->connectX;
	m_GrInfo.connectY   = (pAdd->GetGrInfo())->connectY; 
	m_GrInfo.connectZ   = (pAdd->GetGrInfo())->connectZ; 
	m_GrInfo.rotation   = (pAdd->GetGrInfo())->rotation; 
	////////////////////////////////////////////////////	
	m_wStep				= pAdd->m_wStep; 
	m_dAngle			= pAdd->m_dAngle;
	m_wAnchor			= pAdd->m_wAnchor;
	////////////////////
	return;
}		

void CDrGrid::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrGrid* pAdd = (CDrGrid*) pObject;
	///////////////////////////////////////////////////// PIPEINFO
	pAdd->m_NodeList.AddTail(GetNodeList() ); 
	////////////////////////////////////////////////////////   
	(pAdd->GetGrInfo())->gridtype	= m_GrInfo.gridtype;
	(pAdd->GetGrInfo())->screenful	= m_GrInfo.screenful;
	(pAdd->GetGrInfo())->alignment	= m_GrInfo.alignment;
	(pAdd->GetGrInfo())->left		= m_GrInfo.left;
	(pAdd->GetGrInfo())->right		= m_GrInfo.right;
	(pAdd->GetGrInfo())->top		= m_GrInfo.top;
	(pAdd->GetGrInfo())->bottom		= m_GrInfo.bottom;
	(pAdd->GetGrInfo())->back		= m_GrInfo.back;
	(pAdd->GetGrInfo())->front		= m_GrInfo.front;
	(pAdd->GetGrInfo())->connectX	= m_GrInfo.connectX;
	(pAdd->GetGrInfo())->connectY	= m_GrInfo.connectY; 
	(pAdd->GetGrInfo())->connectZ	= m_GrInfo.connectZ; 
	(pAdd->GetGrInfo())->rotation	= m_GrInfo.rotation; 
	////////////////////////////////////////////////////	
	pAdd->m_wStep					= m_wStep; 
	pAdd->m_dAngle					= m_dAngle;
	pAdd->m_wAnchor					= m_wAnchor;
	////////////////////
	return;
}		

void CDrGrid::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrGrid::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_DrawTypes;i++)
   		if(DrTypes[i].num == GRID) 
   		{
   			name = DrTypes[i].ObjName;
   			break;
   		}	
	/////////////////////////
   	CString pad = " "; 
   	////////////////////////
//	m_GrInfo.bValve  = FALSE;  
   	AddStr(pstrCard,&name,5); 
   	AddStr(pstrCard,&pad,5);
	AddInt(pstrCard,m_GrInfo.gridtype);
	//////////// 
	return;

}   
//////////////////////////////////////////////////////////
void CDrGrid::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrGrid::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrGrid::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrGrid::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
	///////////////////////
	// CNodes are same as Nodes
	////////////////////////////			
	Calc_ScreenRectFromCNodes();
	////////////////////////////

}

void CDrGrid::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{

	pMATRIX		pLMP;	
	CDListMgr* pList;
	POSITION pos;
	///////////////////////// 
	if(bYes)
		pLMP 	= pLM;
	//////////////////////////////////////////// Transform
	// Bounding Corners are the Nodes
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_WorldPos(pLMP,bYes);
			//////////////////////////////////
		}
	}	
	///////////////////	
}

void CDrGrid::TransformToEyePos(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// View Transform
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_EyePos(pViewM);
			//////////////////////////////////
		}
	}
	///////////////////	
}

void CDrGrid::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////// Project
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->ProjectToScreenPos3D(pvv3DM);
			//////////////////////////////////
			//	Bounding Corners ARE the Nodes
			// 	So no need to do again
			///////////////////////////////////////
			WORLD ScreenPos = *(pNode->GetScreenPos3D());
			///////////////////////////////////////
			POINT pt;
			//////////////////////////////////////////////////////
			// 	3DScreenPos belongs to [0,-1] because of CVV	//
			//	So before we Change into Integer Logical		//
			//	Coordinates, we Must Use Screen Client Data		//
			//////////////////////////////////////////////////////
			pt.x = (int)(ScreenPos.x * dScale_U);
			pt.y = (int)(ScreenPos.y * dScale_V);
			//////////////////////
			pNode->SetScreenPos2D(pt);
			//////////////////////
		}
	}
	////////////////////////////
}

void CDrGrid::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrGrid::FinishObject()
{ 
	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
	m_rectBounding = CRect(INT_MAX,INT_MIN,INT_MIN,INT_MAX);//L,T,R,B
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			POINT pt = *(pNode->GetScreenPos2D());
			// If the point lies outside of the accumulated bounding
			// rectangle, then inflate the bounding rect to include it.
			m_rectBounding.left     = min(m_rectBounding.left, pt.x);
			m_rectBounding.top      = max(m_rectBounding.top, pt.y);
			m_rectBounding.right    = max(m_rectBounding.right, pt.x);
			m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
		}
	}	
    //////////////////////////////////////////////////////////////////
	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Plat when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth_G, -(int)m_nPenWidth_G));
	///////
	return; 
	
} 
//////////////////////////////////////////////////////////////
void CDrGrid::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{ 
	m_bParallel		= bParallel;
    m_nView			= nView;
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX 
	///////////////////////////////////////////////////////////////// PreProcess
	////////////////////////////////////////////// Coordinates XForm
												// Local->World	  
	MATRIX LM;
	BOOL bXForm = FALSE;
	TransformObjectToWorld(&LM,bXForm);
	///////////////////////////////////////////
	TransformObjectToView(&m_ViewM); 
	ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
	///////////////////////////////////
	FinishObject();//	calc Bounding Rect  
	/////////////
}
						
void CDrGrid::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrGrid::GoDoIt(CDC* PtrDC,BOOL bPenChange)
{ 

	CDListMgr* 	pList;
	POSITION 	pos;
	/////////////////////////////////////// World Nodes
	pList = GetNodeList();
	//////////////////////
	if(pList->GetCount() != MAX_NODES_GRID)
	{
		AfxMessageBox("Internal Problem:Grid::GoDoIt");
		return;
	}	
	//////////////////////////////////////////////////////
	CDrNode* pNode;
	pos = pList->GetFirstObjectPos();
	pNode = (CDrNode*)pList->GetNextObject(pos);
	WORLD minWPos = *(pNode->GetWorldPos());
	pNode = (CDrNode*)pList->GetNextObject(pos);
	WORLD maxWPos = *(pNode->GetWorldPos());
	///////////////////////////////////////////////////////// Draw
	DrawGrid(PtrDC, &maxWPos, &minWPos, &m_wStep, &m_GrInfo);
	//////////////////////////////////////////////////////   	
   	
}   

void CDrGrid::DrawGrid(CDC* pDC,pWORLD max,pWORLD min,pWORLD steps,pGR_INFO pGrInfo)
{
    ////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    //////////////////////////////////////////////////////////////// Grid Pen
   	Pen.CreatePen (m_nPenStyle_G,m_nPenWidth_G,m_crPenColor_G); 
   	PtrOldPen = pDC->SelectObject(&Pen);
   	//////////////////////////////////////
	WORLD		step;
	double		f,x,y,z; 
	int i;
	///////////////////////////////////////////////////////////// Boundary Walls
	step.x = (max->x-min->x)/steps->x;
	step.y = (max->y-min->y)/steps->y;
	step.z = (max->z-min->z)/steps->z;
	
	
	if (pGrInfo->bottom||pGrInfo->back||pGrInfo->top||pGrInfo->front)
		for(i=0,f=min->x;i<=(int)steps->x;f+=step.x,i++) {
		//for(f=min->x;f<=max->x;f+=step.x) {
			if (pGrInfo->bottom)
				DrawLine3D(pDC,f,min->y,min->z,f,min->y,max->z,FALSE); /* y const */
			if (pGrInfo->back)
				DrawLine3D(pDC,f,min->y,max->z,f,max->y,max->z,FALSE); /* z const */
			if (pGrInfo->top)
				DrawLine3D(pDC,f,max->y,min->z,f,max->y,max->z,FALSE); /* y const */
			if (pGrInfo->front)
				DrawLine3D(pDC,f,min->y,min->z,f,max->y,min->z,FALSE); /* z const */
		}
	if (pGrInfo->left||pGrInfo->back||pGrInfo->right||pGrInfo->front)
		for(i=0,f=min->y;i<=(int)steps->y;f+=step.y,i++) {
//		for(f=min->y;f<=max->y;f+=step.y) {
			if (pGrInfo->left)
				DrawLine3D(pDC,min->x,f,min->z,min->x,f,max->z,FALSE); /* x const */
			if (pGrInfo->back)
				DrawLine3D(pDC,min->x,f,max->z,max->x,f,max->z,FALSE); /* z const */
			if (pGrInfo->right)
				DrawLine3D(pDC,max->x,f,min->z,max->x,f,max->z,FALSE); /* x const */
			if (pGrInfo->front)
				DrawLine3D(pDC,min->x,f,min->z,max->x,f,min->z,FALSE); /* z const */
		}
	if (pGrInfo->left||pGrInfo->bottom||pGrInfo->right||pGrInfo->top)
		for(i=0,f=min->z;i<=(int)steps->z;f+=step.z,i++) {
//		for(f=min->z;f<=max->z;f+=step.z) {
			if (pGrInfo->left)
				DrawLine3D(pDC,min->x,min->y,f,min->x,max->y,f,FALSE); /* x const */
			if (pGrInfo->bottom)
				DrawLine3D(pDC,min->x,min->y,f,max->x,min->y,f,FALSE); /* y const */
			if (pGrInfo->right)
				DrawLine3D(pDC,max->x,min->y,f,max->x,max->y,f,FALSE); /* x const */
			if (pGrInfo->top)
				DrawLine3D(pDC,min->x,max->y,f,max->x,max->y,f,FALSE); /* y const */
		}
    //////////////////////////////////////////////////////////////// Connect Pen
   	pDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	Pen.CreatePen (m_nPenStyle_C,m_nPenWidth_C,m_crPenColor_C); 
   	PtrOldPen = pDC->SelectObject(&Pen);
	//////////////////////////////////////////////////////// Cube Internal	
	if(pGrInfo->connectX||pGrInfo->connectZ) {
		for(i=1,y=min->y+step.y;i<(int)steps->y;y+=step.y,i++) {
//		for(y=min->y+step.y;y<max->y;y+=step.y) {
			if(pGrInfo->connectX)
				for(i=1,y=min->z+step.z;i<(int)steps->z;z+=step.z,i++)
//				for(z=min->z+step.z;z<max->z;z+=step.z)
					DrawLine3D(pDC,min->x,y,z,max->x,y,z,FALSE);
			if(pGrInfo->connectZ)
				for(i=1,y=min->x+step.x;i<(int)steps->x;x+=step.x,i++)
//				for(x=min->x+step.x;x<max->x;x+=step.x)
					DrawLine3D(pDC,x,y,min->z,x,y,max->z,FALSE);
		}
	}
	if(pGrInfo->connectY)
		for(i=1,y=min->x+step.x;i<(int)steps->x;x+=step.x,i++)
//		for(x=min->x+step.x;x<max->x;x+=step.x)
			for(i=1,y=min->z+step.z;i<(int)steps->z;z+=step.z,i++)
//			for(z=min->z+step.z;z<max->z;z+=step.z)
				DrawLine3D(pDC,x,min->y,z,x,max->y,z,FALSE);
	////////////////////////////////////////////////////////			
   	pDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
}
BOOL CDrGrid::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{
	////////////////////////////////////		
	if(m_ObjectID == KeyID)
		return TRUE;
	else
		return FALSE;
}
	
BOOL CDrGrid::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrGrid* pGrid = (CDrGrid*)pObject;
		///////////////////////////////////
		if(pGrid->GetObjectType() == GRID)
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

void CDrGrid::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	WORD	nPenWidth_G,nPenStyle_G,nPenWidth_C,nPenStyle_C;
	DWORD   crPenColor_G,crPenColor_C;
	
	if (ar.IsStoring())
	{
		TRACE( " Grid   :Storing\n");	// TODO: add loading code here

		ar
			<<	/*UINT*/	(WORD)m_nPenWidth_G    // pen width for 
			<<	/*COLORREF*/(DWORD)m_crPenColor_G
			<<	/*UINT*/	(WORD)m_nPenStyle_G 
			<<	/*UINT*/	(WORD)m_nPenWidth_C    // pen width for 
			<<	/*COLORREF*/(DWORD)m_crPenColor_C
			<<	/*UINT*/	(WORD)m_nPenStyle_C; 
		ar.Write(&m_GrInfo, sizeof(GR_INFO) );	
		//////////////////////////////////////////////////////

 	}
	else
	{
	
		TRACE( " Grid   :Loading\n");	// TODO: add loading code here


		ar
		  	>>	/*UINT*/	nPenWidth_G    // pen width 
			>>	/*COLORREF*/crPenColor_G
			>>	/*UINT*/	nPenStyle_G 
		  	>>	/*UINT*/	nPenWidth_C    // pen width 
			>>	/*COLORREF*/crPenColor_C
			>>	/*UINT*/	nPenStyle_C; 
		ar.Read(&m_GrInfo, sizeof(GR_INFO) );	
	    //////////////////////////////////////////////    
		m_nPenWidth_G 		=	(UINT)nPenWidth_G;    // pen width for Pipe
		m_crPenColor_G 		= 	(COLORREF)crPenColor_G;
		m_nPenStyle_G 		= 	(UINT)nPenStyle_G; 
		m_nPenWidth_C 		=	(UINT)nPenWidth_C;    // pen width for Pipe
		m_crPenColor_C 		= 	(COLORREF)crPenColor_C;
		m_nPenStyle_C 		= 	(UINT)nPenStyle_C; 
 	   /////////////////////////////        
	}        
	//////////////////////////////////////////////////////
	m_NodeList.Serialize(ar);
	////////////////////////

}

////////////////////// END OF MODULE ///////////////////////
/*
#define	FACETLINE(a,b,c,t,n,s) {\
		register int	i = (n);\
		ix[0] = ixV++;\
		pV[ix[0]].p.x = (a);\
		pV[ix[0]].p.y = (b);\
		pV[ix[0]].p.z = (c);\
		pV[ix[0]].impure = false;\
		while( i-- ){ \
			ix[1] = ixV++;\
			pV[ix[1]] = pV[ix[0]];\
			pV[ix[1]].p.##t += (s);\
			MakePolyFacet(&pF[ixF++],2,(pUInt)ix,pV);\
			ix[0] = ix[1];\
		}\
	}

#define	FACETLINEX(a,b,c,n,s)	FACETLINE((a),(b),(c),x,(n),(s))
#define	FACETLINEY(a,b,c,n,s)	FACETLINE((a),(b),(c),y,(n),(s))
#define	FACETLINEZ(a,b,c,n,s)	FACETLINE((a),(b),(c),z,(n),(s))
*/


