// Plat.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
//#include "DrFE1D.h"
//#include "DrFE2D.h"
//////////////
#include "DrFE3D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
//#define COMBO_NIDJ_LOC 	9     // Location of NidJ in element ComboBox
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrFE3D
IMPLEMENT_SERIAL(CDrFE3D, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrFE3D, CDrObject)
	//{{AFX_MSG_MAP(CDrFE3D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrFE3D::CDrFE3D()
{  
    	
    //////////////////////////////	
	SetObjectType((int)FE3D);
    SetElemType((int)EL3D_OBJECT);          // 
	////////////////////////////////////////////////////////////
	m_nCorners			= 4;	// 4 = Tetra/ 5 = Penta/ 6 = Hexa
	m_nEdges			= 6;	// Bounding Edges
	m_nFaces			= 4;	// Bounding Faces
	///
	for(int i=0;i<m_nCorners;i++)
	{
		m_rid[i]		= "";
		m_rel[i]		= 0;
	}
	////////////////////////////////////////////////////////////
	 
} 

CDrFE3D::~CDrFE3D()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrFE3D::ReadyToDelete()
{
	////////////////////////////////////// unload Nodes/No delete
	CDListMgr* pNodeList = GetFE0DList();
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
	/////////////////////////////////////////////////////////////
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		pObject->ReadyToDelete();
	}
	//////////////////////////////////////////////////////////////
}


int CDrFE3D::DealObjectDialog()
{
/*
	CPlatProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrFE3D::SetObjectInfo(CDrObject* pObject)
{
	
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE3D* pAdd = (CDrFE3D*) pObject;
	//////////////////////////////////////////////////////// CopyList
	m_nFaces			= pAdd->m_nFaces;	// Bounding Faces
	///
	for(int i=0;i<MAX_CORNERS_3D;i++)
	{
		m_rid[i]		= pAdd->m_rid[i];
		m_rel[i]		= pAdd->m_rel[i];
	}
	////////////////////////////// 
	if(!(pAdd->GetFE0DList()->IsEmpty()))
		m_FE0DList.AddTail(pAdd->GetFE0DList() ); 
	if(!(pAdd->GetFE1DList()->IsEmpty()))
		m_FE1DList.AddTail(pAdd->GetFE1DList() ); 
	if(!(pAdd->GetFE2DList()->IsEmpty()))
		m_FE2DList.AddTail(pAdd->GetFE2DList() ); 
	//
	if(!(pAdd->GetMs0List()->IsEmpty()))
		m_Ms0List.AddTail(pAdd->GetMs0List() ); 
	if(!(pAdd->GetMs1List()->IsEmpty()))
		m_Ms1List.AddTail(pAdd->GetMs1List() ); 
	if(!(pAdd->GetMs2List()->IsEmpty()))
		m_Ms2List.AddTail(pAdd->GetMs2List() ); 
	if(!(pAdd->GetMs3List()->IsEmpty()))
		m_Ms3List.AddTail(pAdd->GetMs3List() ); 
	if(!(pAdd->GetMbj3DList()->IsEmpty()))
		m_Mbj3DList.AddTail(pAdd->GetMbj3DList() ); 
	////////////////////
	return;
}		

void CDrFE3D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE3D* pAdd = (CDrFE3D*) pObject;
	//////////////////////////////////////////////////////// CopyList
	pAdd->m_nFaces			= m_nFaces;	// Bounding Edges
	///
	for(int i=0;i<MAX_CORNERS_3D;i++)
	{
		pAdd->m_rid[i]		= m_rid[i];
		pAdd->m_rel[i]		= m_rel[i];
	}
	///
	if(!(GetFE0DList()->IsEmpty()))
		pAdd->m_FE0DList.AddTail(GetFE0DList() ); 
	if(!(GetFE1DList()->IsEmpty()))
		pAdd->m_FE1DList.AddTail(GetFE1DList() ); 
	if(!(GetFE2DList()->IsEmpty()))
		pAdd->m_FE2DList.AddTail(GetFE2DList() ); 
	///
	if(!(GetMs0List()->IsEmpty()))
		pAdd->m_Ms0List.AddTail(GetMs0List() ); 
	if(!(GetMs1List()->IsEmpty()))
		pAdd->m_Ms1List.AddTail(GetMs1List() ); 
	if(!(GetMs2List()->IsEmpty()))
		pAdd->m_Ms2List.AddTail(GetMs2List() ); 
	if(!(GetMs3List()->IsEmpty()))
		pAdd->m_Ms3List.AddTail(GetMs3List() ); 
	if(!(GetMbj3DList()->IsEmpty()))
		pAdd->m_Mbj3DList.AddTail(GetMbj3DList() ); 
	////////////////////
	return;
}		

void CDrFE3D::Calc_CentroidWorld()
{

	CDListMgr* pList = GetFE0DList();
	//////////////////////////////////////////
	CDrFE0D* 	pNode;
	WORLD		w1,w2,w3,w4,C;
	POSITION pos 	= pList->GetFirstObjectPos();
	///////////////
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w1 = *(pNode->GetWorldPos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w2 = *(pNode->GetWorldPos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w3 = *(pNode->GetWorldPos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w4 = *(pNode->GetWorldPos());
	//////////////////////////
	C3DMath	Math3D;
	Math3D.Avg3DPts(&w1,&w2,&w1);
	Math3D.Avg3DPts(&w3,&w4,&w3);
	Math3D.Avg3DPts(&w1,&w3,&C);
    //////////////////////////
    SetCentroidWorld(C);
    ///////////////

}

void CDrFE3D::Calc_CentroidEye()
{

	CDListMgr* pList = GetFE0DList();
	//////////////////////////////////////////
	CDrFE0D* 	pNode;
	WORLD		w1,w2,w3,w4,C;
	POSITION pos 	= pList->GetFirstObjectPos();
	///////////////
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w1 = *(pNode->GetEyePos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w2 = *(pNode->GetEyePos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w3 = *(pNode->GetEyePos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w4 = *(pNode->GetEyePos());
	//////////////////////////
	C3DMath	Math3D;
	Math3D.Avg3DPts(&w1,&w2,&w1);
	Math3D.Avg3DPts(&w3,&w4,&w3);
	Math3D.Avg3DPts(&w1,&w3,&C);
    //////////////////////////
    SetCentroidEye(C);
    ///////////////
}

void CDrFE3D::Calc_CentroidScreen3D(double dScale_U,double dScale_V)
{

	CDListMgr* pList = GetFE0DList();
	//////////////////////////////////////////
	CDrFE0D* 	pNode;
	WORLD		w1,w2,w3,w4,C;
	POSITION pos 	= pList->GetFirstObjectPos();
	///////////////
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w1 = *(pNode->GetScreenPos3D());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w2 = *(pNode->GetScreenPos3D());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w3 = *(pNode->GetScreenPos3D());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w4 = *(pNode->GetScreenPos3D());
	//////////////////////////
	C3DMath	Math3D;
	Math3D.Avg3DPts(&w1,&w2,&w1);
	Math3D.Avg3DPts(&w3,&w4,&w3);
	Math3D.Avg3DPts(&w1,&w3,&C);
    //////////////////////////
    SetCentroidScreen3D(C);
	//////////////////////////// Centroid Zdepth
	SetCentroidZdepth(C.z);
    //////////////////////////   Screen2D
	POINT pt;
	//////////////////////////////////////////////////////
	// 	3DScreenPos belongs to [0,-1] because of CVV	//
	//	So before we Change into Integer Logical		//
	//	Coordinates, we Must Use Screen Client Data		//
	//////////////////////////////////////////////////////
	pt.x = (int)(C.x * dScale_U);
	pt.y = (int)(C.y * dScale_V);
	//////////////////////
	SetCentroidScreen2D(pt);
	//////////////////////
}

void CDrFE3D::Calc_NormalWorld()
{

	CDListMgr* pList = GetFE0DList();
	//////////////////////////////////////////
	CDrFE0D* 	pNode;
	WORLD		w1,w2,w3,N,vx,vy;
	POSITION pos 	= pList->GetFirstObjectPos();
	///////////////
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w1 		= *(pNode->GetWorldPos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w2 		= *(pNode->GetWorldPos());
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	w3 		= *(pNode->GetWorldPos());
	//////////////////////////
	C3DMath	Math3D;
	Math3D.Sub3DPts(  &w1, &w2,&vx );
	Math3D.Sub3DPts(  &w3, &w2,&vy );
	Math3D.Cross3DPts( &vx,&vy,&N);
	Math3D.Normalize(&N,&N);
    //////////////////////////
    SetNormalWorld(N);
    ////////////////////

}

void CDrFE3D::TransformNormalToEye(pMATRIX pViewM)
{

	/////////////////////////
	WORLD N = *GetNormalWorld();
    ////////////////////////////////// transform
    CXForm XForm;
    XForm.Transform(&N,&N,pViewM);
    //////////////////////////////
    SetNormalEye(N);
    ////////////////
}

void CDrFE3D::ProjectNormalToScreen3D
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	WORLD EyePos,ScreenPos;
	CXForm XForm;
	/////////////
	EyePos = *GetNormalEye();
	/////////////////////////////////////// Multiply by M(Foley:p658)
	//	It will be done beforehand
	//	if(!m_bParallel)
	//		XForm->PerspectiveToParallelCVV
	//			(&EyePos,&ScreenPos,zMin);
	///////////////////////////////////////////////////
	XForm.Project(pvv3DM,&EyePos, &ScreenPos);
	////////////////////////////////////////
	SetNormalScreen3D(ScreenPos);
	//////////////////////////////////
	POINT pt;
		//////////////////////////////////////////////////////
		// 	3DScreenPos belongs to [0,-1] because of CVV	//
		//	So before we Change into Integer Logical		//
		//	Coordinates, we Must Use Screen Client Data		//
		//////////////////////////////////////////////////////
	pt.x = (int)(ScreenPos.x * dScale_U);
	pt.y = (int)(ScreenPos.y * dScale_V);
	//////////////////////
	SetNormalScreen2D(pt);
	//////////////////////
}

BOOL CDrFE3D::CullScreen(pMATRIX pViewM)
{
    ////////////////////////////////////////////////////////// 
    // Back Culling: Use 2D Normal after Projection			//
    // Transformation into Canonical View Parallelopiped	//
	// projected normal points away from viewer, omit it	//
	// 			recall ViewNormal=(0,0,-1)					//
	//	Dot(PolyNormal,ViewNormal) = - PolyNormal.z			//
    //////////////////////////////////////////////////////////
    BOOL 	bVisible = FALSE;
    WORLD 	N;
    //////////////////////////////////  get Eye
    N = *GetNormalEye();
	////////////////////////////////// visible
	if( -N.z  > 0.0)
		bVisible = TRUE;
	////////////////////////////
	SetCulled(bVisible);	
	////////////////////////////
	return bVisible;
				
}

BOOL CDrFE3D::CullWorld(WORLD ViewDir)
{

//////////////////////////////////////////////////////////////
//				Trivial Rejection of Primitives 			//
//			EYE Position:                                   //
//				Parallel Projection - VRP                   //
//				Perspective "		- PRP                   //
//                                                          //
//	So, for Initial Culling without transformation:         //
//		We choose appropriate Eye position and a Point on   //
//		the Polygon to find view direction                  //
//////////////////////////////////////////////////////////////
	C3DMath Math3D;
	CDListMgr* pList = GetFE0DList();
	//////////////////////////////////////////
	BOOL		bCulled = FALSE;
	CDrFE0D* 	pNode;
	WORLD		W,N;
	POSITION pos 	= pList->GetFirstObjectPos();
	///////////////
	pNode 	= (CDrFE0D*)pList->GetNextObject(pos);
	N		= *GetNormalWorld();
	W 		= *(pNode->GetWorldPos());
	////////////////////////////////// View Direction
//	ViewDir.x -= W.x;
//	ViewDir.y -= W.y;
//	ViewDir.z -= W.z;
	/////////////////////////////// visibility
	if((Math3D.Dot3DPts(&ViewDir,&N)) > 0) 	// backface
		bCulled = TRUE;
	////////////////////////////
	SetCulled(bCulled);	
	////////////////////////////
	return bCulled;
	
}	

void CDrFE3D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFE3D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == FE2D) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
   	/////////////////////////                 PACKING is ARBITRARY for now!!!
   	CString pad = " "; 
  	 ////////////////////////
/*
	AddStr(pstrCard,&name,5); 
   
	int nMaxCorner = m_PlatCard.nCorners; 	
    for(i = 0; i<nMaxCorner; i++)              // 
    	AddStr(pstrCard,&m_PlatCard.nid[i],5);
   	AddStr(pstrCard,&m_PlatCard.pid,5);
   	AddStr(pstrCard,&m_PlatCard.mid,5);
  	AddStr(pstrCard,&pad,5);
*/
	//////////// 
	return;

}
/*   
void CDrFE3D::GetRawCoords(long* lCoord, int* pnPrecision, int index)
{

	CDrFE0D* pNode = (CDrFE0D*)m_NodeList.GetObject(index);
	//////////////////////////////////////////
   	lCoord[0] 		= pNode->GetNodeCard()->x;
   	lCoord[1] 		= pNode->GetNodeCard()->y;
   	lCoord[2]		= pNode->GetNodeCard()->z;
   	*pnPrecision 	= pNode->GetPrecision();
   	////////////////////////////////////////// 
   	return;
    
}
*/                            
//////////////////////////////////////////////////////////
void CDrFE3D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	Calc_CentroidWorld();   
	Calc_NormalWorld();
	//////////////////
}
	
void CDrFE3D::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	Calc_CentroidEye();
	TransformNormalToEye(pViewM);

}	

BOOL CDrFE3D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	if(nType == 1)
		return CullWorld(VDir);
	else
	if(nType == 2)
		return CullScreen(pViewM);
	else
		return FALSE;	// do nothing
}			 
				
void CDrFE3D::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
	Calc_CentroidScreen3D(dScale_U,dScale_V);
	ProjectNormalToScreen3D(pvv3DM,dScale_U,dScale_V);
	///////////////////////
	// CNodes are same as Nodes
	////////////////////////////			
	Calc_ScreenRectFromCNodes();
	////////////////////////////

}

void CDrFE3D::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
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
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_WorldPos(pLMP,bYes);
			//////////////////////////////////
		}
	}	
	///////////////////	
}

void CDrFE3D::TransformToEyePos(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// View Transform
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_EyePos(pViewM);
			//////////////////////////////////
		}
	}
	///////////////////	
}

void CDrFE3D::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////// Project
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
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
}

void CDrFE3D::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrFE3D::FinishObject()
{ 
	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
	m_rectBounding = CRect(INT_MAX,INT_MIN,INT_MIN,INT_MAX);//L,T,R,B
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			POINT pt = *(pNode->GetScreenPos2D());
			// If the point lies outside of the accumulated bounding
			// rectangle, then inflate the bounding rect to include it.
			m_rectBounding.left     = min(m_rectBounding.left, pt.x);
			m_rectBounding.right    = max(m_rectBounding.right, pt.x);
			m_rectBounding.top      = max(m_rectBounding.top, pt.y);
			m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
		}
	}	
    //////////////////////////////////////////////////////////////////
	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Plat when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	///////
	return; 
	
} 
//////////////////////////////////////////////////////////////
void CDrFE3D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V,double dShrink)
{ 
	m_dShrink		= dShrink;
	////////////////////////////
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
//	FinishObject();//	calc Bounding Rect  
	/////////////
}
						
void CDrFE3D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrFE3D::GoDoIt(CDC* PtrDC,BOOL bPenChange)
{ 

	CDListMgr* 	pList;
	POSITION 	pos;
    ////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	int i;
	POINT* pPtMem;
	//////////////////////////////////////////////////////
	if(!pList->IsEmpty())
	{
		/////////////////////////////////////// Memory
		int nMaxCorner = pList->GetCount();
		pPtMem = new POINT[nMaxCorner+1];
		if(!pPtMem)
		return;
		/////////////////////////////////////// GetNodes
		POINT* pPt; 	
		for (pos = pList->GetFirstObjectPos(),i = 0;pos !=NULL;i++)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pPt = pPtMem+i;
			*pPt = *(pNode->GetScreenPos2D());
			/////////////////////////////
		}
		*(pPtMem+nMaxCorner) = *pPtMem;	// last = first
    	//////////////////////////////////// Line
		PtrDC->Polyline(pPtMem,nMaxCorner+1);
		//////////////
		delete [] pPtMem;
	}	
	//////////////////////////////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
   	
}   
/////////////////////////////////////////////////////////////////////////////
BOOL CDrFE3D::IsKeyMatch(CString KeyID,UINT KeyNo)
{

	return FALSE;
}
	
BOOL CDrFE3D::IsObjectHit(int nNet, POINT point)
{
	///////////////
	return FALSE;
}

void CDrFE3D::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{
		TRACE( " FE3D   :Storing\n");	// TODO: add loading code here
 	}
	else
	{
		TRACE( " Plat   :Loading\n");	// TODO: add loading code here
	}        

}

////////////////////// END OF MODULE ///////////////////////

