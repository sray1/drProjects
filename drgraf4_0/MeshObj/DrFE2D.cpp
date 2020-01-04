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
//#include "DrFE3D.h"
//////////////
#include "DrFE2D.h"


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
// CDrFE2D
IMPLEMENT_SERIAL(CDrFE2D, CDrFE1D,1)
/*
BEGIN_MESSAGE_MAP(CDrFE2D, CDrFE1D)
	//{{AFX_MSG_MAP(CDrFE2D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrFE2D::CDrFE2D()
{  
    	
    //////////////////////////////	
    SetObjectType((int)FE2D);
    SetElemType((int)EL2D_OBJECT);          // 
    //////////////////////////////
    m_bCulled			= FALSE;
	////////////////////////////////////////////////////////////
	m_nCorners			= 4;	// 3 = Triangle/ 4 = Quadrilateral
	m_nEdges			= 4;	// Bounding Edges
	///
	for(int i=0;i<m_nCorners;i++)
	{
		m_rid[i]		= "";
		m_rel[i]		= 0;
	}
	m_Thkness			= 1.0;			// Thickness
	////////////////////////////////////////////////////////////
	m_ElNumID		= "";
	m_ElTypeID		= "";
	m_ElTypeNum		= UNONE;
	m_line_id		= "";
	m_mid			= "";
	m_numseg		= 1 ;
	m_refTemp		= 0.0;
	//////////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

CDrFE2D::~CDrFE2D()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrFE2D::ReadyToDelete()
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

int CDrFE2D::DealObjectDialog()
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
	
void CDrFE2D::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE2D* pAdd = (CDrFE2D*) pObject;
	/////////////////////////////////////////////
	m_bCulled			= pAdd->m_bCulled;	
	m_CentroidWorld		= pAdd->m_CentroidWorld; 
	m_CentroidEye		= pAdd->m_CentroidEye; 
	m_NormalWorld		= pAdd->m_NormalWorld; 
	m_NormalEye			= pAdd->m_NormalEye; 
	m_Zdepth			= pAdd->m_Zdepth; 
	////////////////////////////////////////////////////////////
	m_nCorners			= pAdd->m_nCorners;	// 3 = Triangle/ 4 = Quadrilateral
	m_nEdges			= pAdd->m_nEdges;	// Bounding Edges
	m_nEdgeNodes		= pAdd->m_nEdgeNodes;
	///
	for(int i=0;i<MAX_CORNERS_2D;i++)
	{
		m_rid[i]		= pAdd->m_rid[i];
		m_rel[i]		= pAdd->m_rel[i];
	}
	m_Thkness			= pAdd->m_Thkness;			// Thickness
	////////////////////////////////////////////////////////////
	m_nNodes		= pAdd->m_nNodes;
	m_ElNumID		= pAdd->m_ElNumID;
	m_ElTypeID		= pAdd->m_ElTypeID;
	m_line_id		= pAdd->m_line_id;
	///
	m_pid			= pAdd->m_pid;
	m_mid			= pAdd->m_mid;
	m_numseg		= pAdd->m_numseg;
	m_refTemp		= pAdd->m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	m_ElNum			= pAdd->m_ElNum;              // Element Number
	m_ElTypeNum		= pAdd->m_ElTypeNum;        // id Number: Element Type
	m_line_no		= pAdd->m_line_no;
	m_prop			= pAdd->m_prop;           //
	m_mat			= pAdd->m_mat;           //
	//////////////////////////////////
	m_nCenter		= pAdd->m_nCenter; 
	////////////////////////////// 
	if(!(pAdd->GetNodeList()->IsEmpty()))			// Centroid etc
		m_NodeList.AddTail(pAdd->GetNodeList() ); 
	if(!(pAdd->GetFE0DList()->IsEmpty()))
		m_FE0DList.AddTail(pAdd->GetFE0DList() ); 
	if(!(pAdd->GetFE1DList()->IsEmpty()))
		m_FE1DList.AddTail(pAdd->GetFE1DList() ); 
	if(!(pAdd->GetFE3DList()->IsEmpty()))
		m_FE3DList.AddTail(pAdd->GetFE3DList() ); 
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
	////////
//082898    m_GenObjType		= pAdd->m_GenObjType;
//082898    m_pGenObj			= pAdd->m_pGenObj;
	///////////////////////
	for(i=0;i<MAX_EDGES_2D;i++)
		m_bPosiEdge[i]	= pAdd->m_bPosiEdge[i];	
	////////
	return;
}		

void CDrFE2D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE2D* pAdd = (CDrFE2D*) pObject;
	//////////////////////////////////////////////////////// CopyList
	pAdd->m_bCulled			= m_bCulled;	
	pAdd->m_CentroidWorld	= m_CentroidWorld; 
	pAdd->m_CentroidEye		= m_CentroidEye; 
	pAdd->m_NormalWorld  	= m_NormalWorld;
	pAdd->m_NormalEye	  	= m_NormalEye;
	pAdd->m_Zdepth  		= m_Zdepth;
	////////////////////////////////////////////////////////////
	pAdd->m_nCorners		= m_nCorners;	// 3 = Triangle/ 4 = Quadrilateral
	pAdd->m_nEdges			= m_nEdges;	// Bounding Edges
	pAdd->m_nEdgeNodes		= m_nEdgeNodes;
	///
	for(int i=0;i<MAX_CORNERS_2D;i++)
	{
		pAdd->m_rid[i]		= m_rid[i];
		pAdd->m_rel[i]		= m_rel[i];
	}
	pAdd->m_Thkness			= m_Thkness;			// Thickness
	////////////////////////////////////////////////////////////
	pAdd->m_nNodes		= m_nNodes;
	pAdd->m_ElNumID		= m_ElNumID;
	pAdd->m_ElTypeID	= m_ElTypeID;
	pAdd->m_line_id		= m_line_id;
	pAdd->m_pid			= m_pid;
	pAdd->m_mid			= m_mid;
	pAdd->m_numseg		= m_numseg;
	pAdd->m_refTemp		= m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	pAdd->m_ElNum		= m_ElNum;              // Element Number
	pAdd->m_ElTypeNum	= m_ElTypeNum;        // id Number: Element Type
	pAdd->m_line_no		= m_line_no;
	pAdd->m_prop		= m_prop;           //
	pAdd->m_mat			= m_mat;           //
	//////////////////////////////////
	pAdd->m_nCardNo				= m_nCardNo;
	pAdd->m_nCenter				= m_nCenter; 
	////////////////////////////// 
	if(!(GetNodeList()->IsEmpty()))
		pAdd->m_NodeList.AddTail(GetNodeList() );	// Centroid etc 
	if(!(GetFE0DList()->IsEmpty()))
		pAdd->m_FE0DList.AddTail(GetFE0DList() ); 
	if(!(GetFE1DList()->IsEmpty()))
		pAdd->m_FE1DList.AddTail(GetFE1DList() ); 
	if(!(GetFE3DList()->IsEmpty()))
		pAdd->m_FE3DList.AddTail(GetFE3DList() ); 
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
	/////////////////////// Genetics
//082898    pAdd->m_GenObjType		= m_GenObjType;
//082898    pAdd->m_pGenObj			= m_pGenObj;
	///////////////////////
	for(i=0;i<MAX_EDGES_2D;i++)
		pAdd->m_bPosiEdge[i]	= m_bPosiEdge[i];	
	////////
	return;
}		

void CDrFE2D::Calc_CentroidWorld()
{

	/////////////////////////////////////// Generated Nodes
	CDListMgr* pList;
	pList = GetFE0DList();
	if(pList->IsEmpty())
		return;
	///////////////////////	
	WORLD w={0,0,0},dw,C;
	int nEnds = pList->GetCount();
	/////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
		//////////////////////////////////
		dw = *(pNode->GetWorldPos());
		w.x += dw.x;
		w.y += dw.y;
		w.z += dw.z;
		//////////////////////////////////
	}	
	//////////////////////////
	double r = 1.0/(double)nEnds; 
	C.x = w.x * r;
	C.y = w.y * r;
	C.z = w.z * r;
    //////////////////////////
    SetCentroidWorld(C);
    ///////////////

}

void CDrFE2D::Calc_CentroidEye()
{

	/////////////////////////////////////// Generated Nodes
	CDListMgr* pList;
	pList = GetFE0DList();
	if(pList->IsEmpty())
		return;
	///////////////////////	
	WORLD w={0,0,0},dw,C;
	int nEnds = pList->GetCount();
	/////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
		//////////////////////////////////
		dw = *(pNode->GetEyePos());
		w.x += dw.x;
		w.y += dw.y;
		w.z += dw.z;
		//////////////////////////////////
	}	
	//////////////////////////
	double r = 1.0/(double)nEnds; 
	C.x = w.x * r;
	C.y = w.y * r;
	C.z = w.z * r;
    //////////////////////////
    SetCentroidEye(C);
    ////////////////////////// Set Zdepth for HiddenSurface
	SetCentroidZdepth(C.z);
	///////////////////////
}

void CDrFE2D::Calc_CentroidScreen3D(double dScale_U,double dScale_V)
{
 
	/////////////////////////////////////// Generated Nodes
	CDListMgr* pList;
	pList = GetFE0DList();
	if(pList->IsEmpty())
		return;
	///////////////////////	
	WORLD w={0,0,0},dw,C;
	int nEnds = pList->GetCount();
	/////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
		//////////////////////////////////
		dw = *(pNode->GetScreenPos3D());
		w.x += dw.x;
		w.y += dw.y;
		w.z += dw.z;
		//////////////////////////////////
	}	
	//////////////////////////
	double r = 1.0/(double)nEnds; 
	C.x = w.x * r;
	C.y = w.y * r;
	C.z = w.z * r;
    //////////////////////////
    SetCentroidScreen3D(C);
	//////////////////////////// Centroid Zdepth
//	SetCentroidZdepth(C.z);
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

void CDrFE2D::Calc_NormalWorld()
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

void CDrFE2D::TransformNormalToEye(pMATRIX pViewM)
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

void CDrFE2D::ProjectNormalToScreen3D
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

BOOL CDrFE2D::CullScreen(pMATRIX pViewM)
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

BOOL CDrFE2D::CullWorld(WORLD ViewDir)
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

void CDrFE2D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFE2D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == m_nObjectType) 
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
//////////////////////////////////////////////////////////
void CDrFE2D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	Calc_CentroidWorld();   
	Calc_NormalWorld();
	//////////////////
}
	
void CDrFE2D::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	Calc_CentroidEye();
	TransformNormalToEye(pViewM);

}	

BOOL CDrFE2D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
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
				
void CDrFE2D::ProjectObject
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

void CDrFE2D::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
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

void CDrFE2D::TransformToEyePos(pMATRIX pViewM)
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

void CDrFE2D::ProjectToScreenPos
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

void CDrFE2D::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrFE2D::FinishObject()
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
void CDrFE2D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
						
void CDrFE2D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrFE2D::GoDoIt(CDC* PtrDC,BOOL bPenChange)
{ 

	/////////////////////////
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
	pWORLD pPtEye;
	//////////////////////////////////////////////////////
	if(!pList->IsEmpty())
	{
		/////////////////////////////////////// Memory
		int nMaxCorner = pList->GetCount();
		pPtEye = new WORLD[nMaxCorner+1];
		if(!pPtEye)
		return;
		/////////////////////////////////////// GetNodes
		pWORLD pPt; 	
		for (pos = pList->GetFirstObjectPos(),i = 0;pos !=NULL;i++)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pPt = pPtEye+i;
			*pPt = *(pNode->GetEyePos());
			/////////////////////////////
		}
		*(pPtEye+nMaxCorner) = *pPtEye;	// last = first
		/////////////////////////////////////////////////////////// Shrink
		if(m_dShrink<1.0)
		{
			C3DMath Math3D;
			//////////////////////////////// find center
			WORLD Center = *pPtEye; 
			for(i=1;i<=nMaxCorner;i++)    //
			{
				Math3D.Add3DPts(pPtEye+i, &Center, &Center);
			}
			double r = 1.0/(double)nMaxCorner;
			Center.x *= r;
			Center.y *= r;
			Center.z *= r;
			/////////////////////////////// Adjust Coords
			double dSh1 = 1 - m_dShrink;
 			for(i=0;i<=nMaxCorner;i++)    //
			{
				(pPtEye+i)->x = m_dShrink*(pPtEye+i)->x + dSh1*Center.x;
				(pPtEye+i)->y = m_dShrink*(pPtEye+i)->y + dSh1*Center.y;
				(pPtEye+i)->z = m_dShrink*(pPtEye+i)->z + dSh1*Center.z;
			}
		}
		/////////////////////////////////////////////////////////// Draw
		int iold = 0; 
		for(i=1;i<=nMaxCorner;i++)    //closed
		{
			DrawLine3D(PtrDC,pPtEye+iold,pPtEye + i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
			iold = i; 
		}
		//////////////
		delete [] pPtEye;
	}	
	//////////////////////////////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
   	
}   
/////////////////////////////////////////////////////////////////////////////
BOOL CDrFE2D::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}
	
BOOL CDrFE2D::IsObjectHit(int nNet,POINT point,int startIndex)
{
	if(m_nEdgeNodes<=0)
		return FALSE;
	///////////////////////
	int nOut = m_nEdgeNodes;
	///////////////////////
	CDListMgr* pList;
	pList		= GetFE0DList();
	///
	if(pList->IsEmpty())
		return FALSE;
	/////////////////////////////////////////// Memory
	POINT*	pScrenOutPts	= new POINT[nOut];
	///////////////////////////////////////////
	for (int j = 0;j<nOut;j++)
	{
		POSITION pos = pList->FindIndex(j);
		CDrFE0D* pNode = (CDrFE0D*)pList->GetAt(pos);
		//////////////////////////////////
		*(pScrenOutPts+j) = *(pNode->GetScreenPos2D());
	}		
	///////////////////////////////////// Form PolygonalRgn: LP
	CRgn Quad;
	////////////////////////////////
	BOOL bOk = Quad.CreatePolygonRgn(pScrenOutPts, nOut, ALTERNATE );
   	////////////////////////////////////////////// Check
	if(bOk)
	{
		if(Quad.PtInRegion(point))
		{
			Quad.DeleteObject();
			////////////////////
			delete [] pScrenOutPts;
			////////////////////
   			return TRUE;
		}
	}
	else
	{
		AfxMessageBox(
			"Internal Problem:\nCDrFE2D::IsObjectHit\nCreatePolygonRgn");
		Quad.DeleteObject();
		////////////////////
		delete [] pScrenOutPts;
		////////////////////
		return FALSE;
	}
	////////////////////
	return FALSE;
}

void CDrFE2D::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	BYTE	bCulled;     
	
	if (ar.IsStoring())
	{
		TRACE( " Plat   :Storing\n");	// TODO: add loading code here

		////////////////////////////////////////
		ar	<<	/*BOOL*/	(BYTE)m_bCulled;
		ar.Write(/*WORLD*/	&m_CentroidWorld,sizeof(WORLD) );
		ar.Write(/*WORLD*/	&m_NormalWorld,sizeof(WORLD) );
		ar.Write(/*WORLD*/	&m_CentroidEye,sizeof(WORLD) );
		ar.Write(/*WORLD*/	&m_NormalEye,sizeof(WORLD) );
		ar.Write(/*double*/	&m_Zdepth,sizeof(double) );
	////////////////////////////////////////////////////////////// Plate Card
//		ar.Write(/*PLATCARD*/	&m_PlatCard,sizeof(FEM2D) );
	/////////////////////////////////////////////////////////////


 	}
	else
	{
	
		TRACE( " Plat   :Loading\n");	// TODO: add loading code here


		////////////////////////////////////////
		ar	>>	/*BOOL*/	bCulled;
		ar.Read(/*WORLD*/	&m_CentroidWorld,sizeof(WORLD) );
		ar.Read(/*WORLD*/	&m_NormalWorld,sizeof(WORLD) );
		ar.Write(/*WORLD*/	&m_CentroidEye,sizeof(WORLD) );
		ar.Write(/*WORLD*/	&m_NormalEye,sizeof(WORLD) );
		ar.Read(/*double*/	&m_Zdepth,sizeof(double) );
	////////////////////////////////////////////////////////////// Plate Card
//		ar.Read(/*PLATCARD*/	&m_PlatCard,sizeof(FEM2D) );
	/////////////////////////////////////////////////////////////
    m_bCulled			= 	(BOOL)bCulled;
    /////////////////////////////        


	}        
	//////////////////////////////////////////////////////
//	m_NodeList.Serialize(ar);
	////////////////////////

}

////////////////////// END OF MODULE ///////////////////////

