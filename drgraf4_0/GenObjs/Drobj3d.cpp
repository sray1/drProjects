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
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrPatch.h"
/////////////////////
#include "DrObj3D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrObj3D
IMPLEMENT_SERIAL(CDrObj3D, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrObj3D, CDrObject)
	//{{AFX_MSG_MAP(CDrObj3D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrObj3D::CDrObj3D()
{  
    	
    //////////////////////////////	
    SetObjectType((int)OBJ3D);
    SetElemType((int)GENR_OBJECT);          //
    //////////////////////////////  
	m_ObjectID		= " ";
//	m_instanceXf 	= ;
//	m_RInfo		=;
	m_bInstanced	= FALSE;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 
    	
CDrObj3D::~CDrObj3D()
{  
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrObj3D::ReadyToDelete()
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
	CDListMgr* pList;
    ////////////////////////////////////////////////////////// Obj3D
	SetTackled(TRUE);
	pList = GetObj3DList();
	while(!pList->IsEmpty())
	{
		pObject = (CDrObject*)pList->RemoveHead();  //
		/////////////////////////////////////////////
		if(!pObject || ((CDrObj3D*)pObject)->IsTackled())
			continue;
		else
		{
			CDListMgr* pObj3DList = pObject->GetObj3DList();
			int index = pObj3DList->GetObjectIndex(this);
			if(index>=0)
				pObj3DList->RemoveObject(index); //
		/////////////////////////
		}
	//////////
	}	
	SetTackled(FALSE);
    ////////////////////////////////////////////////////////// Solid
	pList = GetSolidList();
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
    ////////////////////////////////////////////////////////// Patch
	pList = GetPatchList();
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
    ////////////////////////////////////////////////////////// Curve
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
	///////////////////////////////////// 
	while(!(GetLabelList()->IsEmpty()))// delete:private
	{
		pObject = (CDrObject*)(GetLabelList()->RemoveHead());
		delete pObject;	//delete:private	
	}	
}
   
int CDrObj3D::DealObjectDialog()
{
/*
	CDrObj3DProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrObj3D::SetObjectInfo(CDrObject* pObject)
{
	
//	CDrPatch::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrObj3D* pAdd = (CDrObj3D*) pObject;
	//////////////////////////////////////////////////////// OBJ3DINFO	
	//////////////////////////////////////////////////////// CopyList
	if(!(pAdd->m_Obj3DList.IsEmpty()) )
		m_Obj3DList.AddTail(&(pAdd->m_Obj3DList) ); 
	if(!(pAdd->m_SolidList.IsEmpty()) )
		m_SolidList.AddTail(&(pAdd->m_SolidList) ); 
	if(!(pAdd->m_PatchList.IsEmpty()) )
		m_PatchList.AddTail(&(pAdd->m_PatchList) ); 
	if(!(pAdd->m_CurveList.IsEmpty()) )
		m_CurveList.AddTail(&(pAdd->m_CurveList) ); 
	if(!(pAdd->m_LabelList.IsEmpty()) )
		m_LabelList.AddTail(&(pAdd->m_LabelList) ); 
    ///////////////////////////
	return;
}		

void CDrObj3D::GetObjectInfo(CDrObject* pObject)
{
	
//	CDrPatch::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrObj3D* pAdd 		= (CDrObj3D*) pObject;
	//////////////////////////////////////////////////////// OBJ3DINFO	
	//////////////////////////////////////////////////////// CopyList
	if(!(m_Obj3DList.IsEmpty()) )
		pAdd->m_Obj3DList.AddTail(&m_Obj3DList ); 
	if(!(m_SolidList.IsEmpty()) )
		pAdd->m_SolidList.AddTail(&m_SolidList ); 
	if(!(m_PatchList.IsEmpty()) )
		pAdd->m_PatchList.AddTail(&m_PatchList ); 
	if(!(m_CurveList.IsEmpty()) )
		pAdd->m_CurveList.AddTail(&m_CurveList ); 
	if(!(m_LabelList.IsEmpty()) )
		pAdd->m_LabelList.AddTail(&m_LabelList ); 
 	////////////////////////////////////////////// 
	return;
}
		
void CDrObj3D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrObj3D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
	name = "OBJ3D";
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
int CDrObj3D::Calc_3DBoundsLocal()
{

	//////////////////////
	CDListMgr*	pList;
	//////////////////////////////////////////////////////
	pList = GetPatchList();     
	///////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrPatch* pPatch 	= (CDrPatch*)pList->GetNextObject(pos);
		///////////////////////
	}
	/////////////
//	m_ptMinMaxL[0] = dMin;
//	m_ptMinMaxL[1] = dMax;
	////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrObj3D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
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
	/////////////////////////////////////////////////////////////// Posted Obj3Ds
	pList = GetObj3DList();     
	///////////////////////////
	SetTackled(TRUE);
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		if(((CDrObj3D*)pObject)->IsTackled())	// stops recursion
			continue;
		pObject->TransformObjectToWorld(pLM,bYes3D);
		///////////////////////
		pObject->GetWorldCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetWorldCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();     
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
	pList = GetPatchList();     
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
	pList = GetCurveList();     
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
	
void CDrObj3D::TransformObjectToView(pMATRIX pViewM)
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
	/////////////////////////////////////////////////////////////// Posted Obj3Ds
	SetTackled(TRUE);
	pList = GetObj3DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		if(((CDrObj3D*)pObject)->IsTackled())
			continue;
		pObject->TransformObjectToView(pViewM);
		///////////////////////
		pObject->GetEyeCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetEyeCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();     
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
	pList = GetPatchList();     
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
	pList = GetCurveList();     
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

BOOL CDrObj3D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	//////////////////////
	BOOL bCulledObject = TRUE,bCulled;
	CDListMgr*	pList;
	POSITION pos;
	/////////////////////////////////////////////////////////////// Posted Solids
	SetTackled(TRUE);
	pList = GetObj3DList();     
	///////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////////
		if(((CDrObj3D*)pObject)->IsTackled())
			continue;
		bCulled = pObject->RemoveHiddenObject(pViewM,VDir,nType);
		///////////////////////
		if(!bCulled)
			bCulledObject = FALSE;
	}	
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();     
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
	pList = GetPatchList();     
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
	pList = GetCurveList();
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
				
void CDrObj3D::ProjectObject
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
	/////////////////////////////////////////////////////////////// Posted Obj3Ds
	SetTackled(TRUE);
	pList = GetObj3DList();
	//////////////////////    
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
		///////////////////////
		if(((CDrObj3D*)pObject)->IsTackled())
			continue;
		pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		pObject->GetScreen3DCorner(&dMinN,0);
		dMin = Calc_NewMin(dMin,dMinN);
		pObject->GetScreen3DCorner(&dMaxN,1);
		dMax = Calc_NewMax(dMax,dMaxN);
		////////////////////////
	}
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();
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
	pList = GetPatchList();
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
	pList = GetCurveList();
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

void CDrObj3D::Calc_ScreenRectFromGenerators()
{

	CDListMgr*	pList;
	POSITION 	pos;
	CRect		BoundRect,theRect(0,0,0,0);	
	/////////////////////////////////////////////////////////////// Posted Obj3Ds
	SetTackled(TRUE);
	pList = GetObj3DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(((CDrObj3D*)pObject)->IsTackled())	// stops recursion
			continue;
		/////////////////////////////////////
		BoundRect = pObject->GetBoundingRect();
		BoundRect.NormalizeRect();
		theRect.UnionRect(&theRect,&BoundRect);
		/////////////////////////////////////
	}
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();
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
	pList = GetPatchList();
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
	pList = GetCurveList();
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

WORLD CDrObj3D::Calc_NewMin(WORLD dMinO, WORLD dMinN)
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

WORLD CDrObj3D::Calc_NewMax(WORLD dMaxO, WORLD dMaxN)
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
void CDrObj3D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrObj3D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
	/////////////////////////////////////// 
	CDListMgr*	pList = GetElemList();
	///////////////////////////////////////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
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
BOOL CDrObj3D::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrObj3D* pDrObj3D = (CDrObj3D*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrObj3D->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	

BOOL CDrObj3D::IsObjectHit(int nNet,POINT point)
{

	CDListMgr*	pList;
	POSITION 	pos;
	BOOL		bHit;	
	/////////////////////////////////////////////////////////////// Posted Obj3Ds
	SetTackled(TRUE);
	pList = GetObj3DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(((CDrObj3D*)pObject)->IsTackled())	// stops recursion
			continue;
		/////////////////////////////////////
		bHit = pObject->IsObjectHit(nNet,point);
		/////////////////////////////////////
		if(bHit)
			return bHit;
		////////////////
	}
	SetTackled(FALSE);
	/////////////////////////////////////////////////////////////// Posted Solids
	pList = GetSolidList();
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
	pList = GetPatchList();
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
	pList = GetCurveList();
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

int CDrObj3D::AppendToObject(
								CDListMgr* pSolidList,
								CDListMgr* pPatchList,
								CDListMgr* pCurveList,
								CDListMgr* pLabelList
							)
{							
	////////////////////
	if(pSolidList && !(pSolidList->IsEmpty()) )
		GetSolidList()->AddTail(pSolidList);
	else
		return -1;	
	if(pPatchList && !(pPatchList->IsEmpty()) )
		GetPatchList()->AddTail(pPatchList);
	else
		return -1;	
	if(pCurveList && !(pCurveList->IsEmpty()) )
		GetCurveList()->AddTail(pCurveList);
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
void CDrObj3D::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{

		TRACE( " Obj3D   :Storing\n");	// TODO: add loading code here

 	}
	else
	{
	
		TRACE( " Obj3D   :Loading\n");	// TODO: add loading code here


	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

