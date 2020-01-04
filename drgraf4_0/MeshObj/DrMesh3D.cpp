// Obj3D.cpp : implementation file
//


#include "stdafx.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN

#include "Def_Type.h"
#include "Def_Objs.h"

#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "XForm.h"
#include "3DMath.h"
////////////////////// ElemObjs
#include "Def_ELem.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "DrFE3D.h"
/////////////////////
#include "DrMesh3D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrMesh3D
IMPLEMENT_SERIAL(CDrMesh3D, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrMesh3D, CDrObject)
	//{{AFX_MSG_MAP(CDrMesh3D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrMesh3D::CDrMesh3D()
{  
    	
    //////////////////////////////	
    SetObjectType((int)MESH3D);
    SetElemType((int)MESH_OBJECT);          //
    //////////////////////////////  
	m_ObjectID		= " ";
//	m_instanceXf 	= ;
//	m_RInfo		=;
	m_bInstanced	= FALSE;
	m_pGenObj		= NULL;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 
    	
CDrMesh3D::~CDrMesh3D()
{  
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrMesh3D::ReadyToDelete()
{
	//////////////////////////////////////////////////////////////
	//	REASON:                                                 //
	//		                                                    //
	// 		public means it is ALSO in pObjectMgr->ObjList      //
	//			these will be deleted from ObjList              //
	// 		private means ONLY in the current Object            //
	//		hierarchy means current one is a building block		//
	//////////////////////////////////////////////////////////////
	CDrObject* pObject;
	////////////////////////////////////// unload Solids/No delete:public
//	CDListMgr* pList;
/*
    ////////////////////////////////////////////////////////// FE3D
	pList = GetFE3DList();
	while(!pList->IsEmpty())
	{
		pObject = (CDrObject*)pList->RemoveHead();  //
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pMesh3DList = pObject->GetMesh3DList();
			int index = pObj3DList->GetObjectIndex(this);
			if(index>=0)
				pMesh3DList->RemoveObject(index); //
		/////////////////////////
		}
	//////////
	}	
    ////////////////////////////////////////////////////////// FE2D
	pList = GetFE2DList();
	while(!pList->IsEmpty())
	{
		pObject = (CDrObject*)pList->RemoveHead();  //
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pMesh3DList = pObject->GetMesh3DList();
			int index = pObj3DList->GetObjectIndex(this);
			if(index>=0)
				pMesh3DList->RemoveObject(index); //
		/////////////////////////
		}
	//////////
	}	
    ////////////////////////////////////////////////////////// FE1D
	pList = GetCurveList();
	while(!pList->IsEmpty())
	{
		pObject = (CDrObject*)pList->RemoveHead();  //
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pObj3DList = pObject->GetObj3DList();
			int index = pObj3DList->GetObjectIndex(this);
			if(index>=0)
				pObj3DList->RemoveObject(index); //
		/////////////////////////
		}
	//////////
	}
*/
	///////////////////////////////////// 
	while(!(GetLabelList()->IsEmpty()))// delete:private
	{
		pObject = (CDrObject*)(GetLabelList()->RemoveHead());
		delete pObject;	//delete:private	
	}	
}
   
int CDrMesh3D::DealObjectDialog()
{
/*
	CDrMesh3DProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrMesh3D::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrMesh3D* pAdd = (CDrMesh3D*) pObject;
	//////////////////////////////////////////////////////// Mesh3DINFO	
	m_pGenObj	= pAdd->m_pGenObj;
	//////////////////////////////////////////////////////// CopyList
	if(!(pAdd->m_FE3DList.IsEmpty()) )
		m_FE3DList.AddTail(&(pAdd->m_FE3DList) ); 
	if(!(pAdd->m_FE2DList.IsEmpty()) )
		m_FE2DList.AddTail(&(pAdd->m_FE2DList) ); 
	if(!(pAdd->m_FE1DList.IsEmpty()) )
		m_FE1DList.AddTail(&(pAdd->m_FE1DList) ); 
	if(!(pAdd->m_FE0DList.IsEmpty()) )
		m_FE0DList.AddTail(&(pAdd->m_FE0DList) ); 
	if(!(pAdd->m_LabelList.IsEmpty()) )
		m_LabelList.AddTail(&(pAdd->m_LabelList) ); 
    ///////////////////////////
	return;
}		

void CDrMesh3D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrMesh3D* pAdd 		= (CDrMesh3D*) pObject;
	//////////////////////////////////////////////////////// OBJ3DINFO	
	pAdd->m_pGenObj	= m_pGenObj;
	//////////////////////////////////////////////////////// CopyList
	if(!(m_FE3DList.IsEmpty()) )
		pAdd->m_FE3DList.AddTail(&m_FE3DList ); 
	if(!(m_FE2DList.IsEmpty()) )
		pAdd->m_FE2DList.AddTail(&m_FE2DList ); 
	if(!(m_FE1DList.IsEmpty()) )
		pAdd->m_FE1DList.AddTail(&m_FE1DList ); 
	if(!(m_FE0DList.IsEmpty()) )
		pAdd->m_FE0DList.AddTail(&m_FE0DList ); 
	if(!(m_LabelList.IsEmpty()) )
		pAdd->m_LabelList.AddTail(&m_LabelList ); 
 	////////////////////////////////////////////// 
	return;
}
		
void CDrMesh3D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrMesh3D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
	name = "MESH3D";
   	/////////////////////////
/*
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == OBJ3D) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}
*/		
   	/////////////////////////
   	CString pad = " "; 
   	////////////////////////
//	m_Obj3DCard.bValve  = FALSE;  
   	AddStr(pstrCard,&name,5); 
   	AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}   
/////////////////////////////////////////////////////////////////
/*****************************************************************************
 *
 *	Function:	Calc_3DBoundsLocal()
 *
 *	Purpose:	Calculates the 3d bounds(LOCAL) of an Object from
 *				all the patches that form the Object
 *					Called during Mouse Creation
 *
 *****************************************************************************
 */
int CDrMesh3D::Calc_3DBoundsLocal()
{
	//////////////////////
	CDListMgr*	pNodeList;
	//////////////////////	
	WORLD	dMin,dMax,Coords;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MIN; 
	dMax.y = -DBL_MIN; 
	dMax.z = -DBL_MIN;
	///////////////////////////////////////////////////////////////////
	pNodeList = GetFE0DList();     // 
	///////////////////////////
	for (POSITION pos = pNodeList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pNodeList->GetNextObject(pos);
		///////////////////////
		Coords.x = pNode->GetLocalPos()->x; 				
		Coords.y = pNode->GetLocalPos()->y; 				
		Coords.z = pNode->GetLocalPos()->z; 				
		///////////////////////////////////// compare and adjust
		if(Coords.x<dMin.x) dMin.x = Coords.x; 				
		if(Coords.y<dMin.y) dMin.y = Coords.y; 				
		if(Coords.z<dMin.z) dMin.z = Coords.z;
		 				
		if(Coords.x>dMax.x) dMax.x = Coords.x; 				
		if(Coords.y>dMax.y) dMax.y = Coords.y; 				
		if(Coords.z>dMax.z) dMax.z = Coords.z;
		//////////////////////////////////// 				
	}
	////////////////////////
	SetLocalCorner(&dMin,0);
	SetLocalCorner(&dMax,1);
	////////////////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrMesh3D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////////
	WORLD dMin,dMax,dMinN,dMaxN;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MAX; 
	dMax.y = -DBL_MAX; 
	dMax.z = -DBL_MAX; 
	////////////////////
	BOOL bYes3D = FALSE;
	if(IsInstanced() )
	{
		bYes3D = TRUE;
		GetLocalTransform(pLM);
	}	
	////////////////////////////
	CDListMgr*	pList;
	POSITION pos;
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToWorld(pLM,bYes3D);
		///////////////////////
		pObject->GetWorldCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetWorldCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Patches
	pList = GetFE2DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToWorld(pLM,bYes3D);
		///////////////////////
		pObject->GetWorldCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetWorldCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToWorld(pLM,bYes3D);   // CentroidWORLD is also created 
		///////////////////////
		pObject->GetWorldCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetWorldCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	////////////////////////
	SetWorldCorner(&dMin,0);		
	SetWorldCorner(&dMax,1);
	////////////////////////		
}
	
void CDrMesh3D::TransformObjectToView(pMATRIX pViewM)
{
	////////////////////////////
	WORLD dMin,dMax,dMinN,dMaxN;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MAX; 
	dMax.y = -DBL_MAX; 
	dMax.z = -DBL_MAX;
	////////////////////////////
	CDListMgr*	pList;
	POSITION pos;
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToView(pViewM);
		///////////////////////
		pObject->GetEyeCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetEyeCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Patches
	pList = GetFE2DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToView(pViewM);   // CentroidEye is also XFormed 
		///////////////////////
		pObject->GetEyeCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetEyeCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->TransformObjectToView(pViewM);
		///////////////////////
		pObject->GetEyeCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetEyeCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	////////////////////////
	SetEyeCorner(&dMin,0);		
	SetEyeCorner(&dMax,1);
	////////////////////////		
}	

BOOL CDrMesh3D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	//////////////////////
	BOOL bCulledObject = TRUE,bCulled;
	CDListMgr*	pList;
	POSITION pos;
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////////
		bCulled = pObject->RemoveHiddenObject(pViewM,VDir,nType);
		///////////////////////
		if(!bCulled)
			bCulledObject = FALSE;
	}	
	/////////////////////////////////////////////////////////////// Posted Patches
	pList = GetFE2DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////////
		bCulled = pObject->RemoveHiddenObject(pViewM,VDir,nType);
		///////////////////////
		if(!bCulled)
			bCulledObject = FALSE;
	}	
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();
	///////////////////////     
	if((nType == 1) && !(pList->IsEmpty()))	// Cull3D
		return bCulledObject = FALSE;
	/////////////////////////////////////////////////	
	pList = GetCurveList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////////
		bCulled = pObject->RemoveHiddenObject(pViewM,VDir,nType);
		///////////////////////
		if(!bCulled)
			bCulledObject = FALSE;
	}	
	////////////////////
	return bCulledObject;
	
}			 
				
void CDrMesh3D::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{
	////////////////////////////
	WORLD dMin,dMax,dMinN,dMaxN;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MAX; 
	dMax.y = -DBL_MAX; 
	dMax.z = -DBL_MAX;
	////////////////////////////
	CDListMgr*	pList;
	POSITION pos;
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();
	//////////////////////    
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		pObject->GetScreen3DCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetScreen3DCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Patchs
	pList = GetFE2DList();
	//////////////////////    
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		pObject->GetScreen3DCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetScreen3DCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();
	//////////////////////    
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		pObject->GetScreen3DCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetScreen3DCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	////////////////////////
	SetScreen3DCorner(&dMin,0);		
	SetScreen3DCorner(&dMax,1);
	////////////////////////		
/*	
	///////////////// To draw all Bound Rect ////////// Later 
	Rearrange3DCorners(m_ptMinMaxL[0], m_ptMinMaxL[1]);		
	Rearrange3DCorners(m_ptMinMaxW[0], m_ptMinMaxW[1]);		
	Rearrange3DCorners(m_ptMinMaxS[0], m_ptMinMaxS[1]);
	/////////////////////////////////////////////////////////
*/
	///////////////////////
	Calc_ScreenRectFromGenerators();
	////////////////////////////

}

void CDrMesh3D::Calc_ScreenRectFromGenerators()
{

	CDListMgr*	pList;
	POSITION 	pos;
	CRect		BoundRect,theRect(0,0,0,0);	
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		BoundRect = pObject->GetBoundingRect();
		BoundRect.NormalizeRect();
		theRect.UnionRect(&theRect,&BoundRect);
		/////////////////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Patchs
	pList = GetFE2DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		BoundRect = pObject->GetBoundingRect();
		BoundRect.NormalizeRect();
		theRect.UnionRect(&theRect,&BoundRect);
		/////////////////////////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		BoundRect = pObject->GetBoundingRect();
		BoundRect.NormalizeRect();
		theRect.UnionRect(&theRect,&BoundRect);
		/////////////////////////////////////
	}
	/////////////////////////// set
	m_rectBounding = theRect;
	///////////////////////////
}				

WORLD CDrMesh3D::Calc_NewMin(WORLD dMinO, WORLD dMinN)
{

	//////////////////////	
	WORLD	dMin;
	dMin = dMinO;
	///////////////////////////////////// compare and adjust
	if(dMinN.x<dMin.x) dMin.x = dMinN.x; 				
	if(dMinN.y<dMin.y) dMin.y = dMinN.y; 				
	if(dMinN.z<dMin.z) dMin.z = dMinN.z; 				
	////////////
	return	dMin;
}

WORLD CDrMesh3D::Calc_NewMax(WORLD dMaxO, WORLD dMaxN)
{

	//////////////////////	
	WORLD	dMax;
	dMax = dMaxO;
	///////////////////////////////////// compare and adjust
	if(dMaxN.x>dMax.x) dMax.x = dMaxN.x; 				
	if(dMaxN.y>dMax.y) dMax.y = dMaxN.y; 				
	if(dMaxN.z>dMax.z) dMax.z = dMaxN.z; 				
	////////////
	return	dMax;
}
//////////////////////////////////////////////////////////////
void CDrMesh3D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
//	FinishObject();//	calc Bounding Rect      DONE in ProjectObject 
	/////////////
}
						
////////////////////////////////////////////////////////////
void CDrMesh3D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
	CDListMgr*	pList;
	POSITION	pos;
	///////////////////////////////////////////////////////////////// FE3D 
	pList = GetFE3DList();
	///////////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pDrObject = (CDrObject*)pList->GetNextObject(pos);
		if(!pDrObject)
			continue;
   	 	///////////////////////////////////////////// Draw 
		pDrObject->DoDrawView(PtrDC,bPenChange);
   		//////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////////// FE2D 
	pList = GetFE2DList();
	///////////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pDrObject = (CDrObject*)pList->GetNextObject(pos);
		if(!pDrObject)
			continue;
   	 	///////////////////////////////////////////// Draw 
		pDrObject->DoDrawView(PtrDC,bPenChange);
   		//////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////////// FE1D 
	pList = GetFE1DList();
	///////////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pDrObject = (CDrObject*)pList->GetNextObject(pos);
		if(!pDrObject)
			continue;
   	 	///////////////////////////////////////////// Draw 
		pDrObject->DoDrawView(PtrDC,bPenChange);
   		//////////////////////////////////////////
	}
}                            
/////////////////////////////////////////////////////////////////////////////
BOOL CDrMesh3D::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrMesh3D* pDrObj3D = (CDrMesh3D*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrObj3D->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	

BOOL CDrMesh3D::IsObjectHit(int nNet,POINT point)
{

	CDListMgr*	pList;
	POSITION 	pos;
	BOOL		bHit;	
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetFE3DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		bHit = pObject->IsObjectHit(nNet,point);
		/////////////////////////////////////
		if(bHit)
			return bHit;
		////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Patchs
	pList = GetFE2DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		bHit = pObject->IsObjectHit(nNet,point);
		/////////////////////////////////////
		if(bHit)
			return bHit;
		////////////////
	}
	/////////////////////////////////////////////////////////////// Posted Curves
	pList = GetFE1DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
		bHit = pObject->IsObjectHit(nNet,point);
		/////////////////////////////////////
		if(bHit)
			return bHit;
		////////////////
	}
	/////////////////////////////////////
	return FALSE;
	
}

int CDrMesh3D::AppendToObject(
								CDListMgr* pFE3DList,
								CDListMgr* pFE2DList,
								CDListMgr* pFE1DList,
								CDListMgr* pFE0DList,
								CDListMgr* pLabelList
							)
{							
	////////////////////
	if(pFE3DList && !(pFE3DList->IsEmpty()) )
		GetFE3DList()->AddTail(pFE3DList);
	else
		return -1;	
	if(pFE2DList && !(pFE2DList->IsEmpty()) )
		GetFE2DList()->AddTail(pFE2DList);
	else
		return -1;	
	if(pFE1DList && !(pFE1DList->IsEmpty()) )
		GetFE1DList()->AddTail(pFE1DList);
	else
		return -1;	
	if(pFE0DList && !(pFE0DList->IsEmpty()) )
		GetFE0DList()->AddTail(pFE0DList);
	else
		return -1;	
	if(pLabelList && !(pLabelList->IsEmpty()) )
		GetLabelList()->AddTail(pLabelList);
	else
		return -1;	
	///////////////
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////
void CDrMesh3D::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{

		TRACE( " Mesh3D   :Storing\n");	// TODO: add loading code here

 	}
	else
	{
	
		TRACE( " Mesh3D   :Loading\n");	// TODO: add loading code here


	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

