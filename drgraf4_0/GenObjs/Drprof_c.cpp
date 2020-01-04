// DrProf_C.cpp : implementation file
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
#include "Ext_Cur.h"
#include "DrCurve.h"
/////////////////////
#include "MatObj.h"

#include "DrProf_C.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrProf_C
IMPLEMENT_SERIAL(CDrProf_C, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrProf_C, CDrObject)
	//{{AFX_MSG_MAP(CDrProf_C)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrProf_C::CDrProf_C()
{  
    	
    //////////////////////////////	
    SetObjectType((int)C_PROFILE);
    SetElemType((int)GENR_OBJECT);          //
    //////////////////////////////  
	m_ObjectID		= " ";
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
//	m_pMatObj = NULL;	 
} 
    	
CDrProf_C::~CDrProf_C()
{  
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrProf_C::ReadyToDelete()
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
	////////////////////////////////////////////////////////// Local Matrix
	pList = GetLMList();
	while(!pList->IsEmpty())
		delete (CDrObject*)pList->RemoveHead();  //
	///////
	return;

}	
   
int CDrProf_C::DealObjectDialog()
{
/*
	CDrProf_CProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrProf_C::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrProf_C* pAdd = (CDrProf_C*) pObject;
	//////////////////////////////////////////////////////// CopyList
	m_ProfType	= pAdd->m_ProfType;	// Profile Type
	m_pCurve	= pAdd->m_pCurve;		// Profile Assembled Curve
	if(!(pAdd->m_CurveList.IsEmpty()) )
		m_CurveList.AddTail(&(pAdd->m_CurveList) ); 
 //	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
	if(!(pAdd->m_LMList.IsEmpty()) )
		m_LMList.AddTail(&(pAdd->m_LMList) ); 
    ////////////////////////
	return;
}		

void CDrProf_C::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrProf_C* pAdd		= (CDrProf_C*) pObject;
	//////////////////////////////////////////////////////// CopyList
	pAdd->m_ProfType	= m_ProfType;	// Profile Type
    pAdd->m_pCurve 		= m_pCurve;
	if(!(m_CurveList.IsEmpty()) )
		pAdd->m_CurveList.AddTail(&m_CurveList ); 
 //	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
	if(!(m_LMList.IsEmpty()) )
		pAdd->m_LMList.AddTail(&m_LMList ); 
    ////////////////////////
	return;
}
		
//////////////////////////////////////////////////////////////
void CDrProf_C::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
						
void CDrProf_C::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrProf_C::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_CurveTypes;i++)
   		if(CuTypes[i].num == C_PROFILE) 
   		{
   			name = CuTypes[i].ObjName;
   			break;
   		}	
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
int CDrProf_C::Calc_3DBoundsLocal()
{

	//////////////////////
	CDListMgr*	pList;
	//////////////////////////////////////////////////////
	pList = GetCurveList();     
	///////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		///////////////////////
	}
	/////////////
//	m_ptMinMaxL[0] = dMin;
//	m_ptMinMaxL[1] = dMax;
	////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrProf_C::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
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
	MATRIX		LMP;	
	pMATRIX		pLMP = &LMP;	
	/////////////////////////////////////////////////////////////// Curve
	BOOL	bYesOP,bYesP = FALSE;
	C3DMath	Math3D;
	Math3D.GetIdentityMATRIX(pLMP);
	/////////////////////////////////////////////////////////////////////////
	// NOTE:
	//	Generated Nodes are ALREADY TRANSFORMED, if needed, in MI_PROF_c.CPP
	//	to serve as LocalPos
	//	so, We SHOULD NOT TRANSFORM ANY MORE, EVEN IF INSTANCING
	/////////////////////////////////////////////////////////////////////////
/*	
	if(m_pMatObj->IsInstanced())
	{	
		LMP = *(m_pMatObj->GetMatrix());
		bYesP	= TRUE;
	} 
*/	
	bYesOP	= bYes && bYesP;
	///////////////////////// 
	if(bYesOP)
	{	
		//////////////// Composite Transform
		Math3D.MultMATRIX(pLM,pLMP,pLMP);
	}
	else
	if(bYes)
	{
		pLMP 	= pLM;
		bYesOP 	= TRUE;
	}
	else
 	bYesOP = bYesP;
	///////////////////////
	m_pCurve->TransformObjectToWorld(pLMP,bYesOP);   // CentroidWORLD is also created 
	///////////////////////
	m_pCurve->GetWorldCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pCurve->GetWorldCorner(&dMaxN,1);
	dMax = Calc_NewMax(dMax,dMaxN);
	////////////////////////
	SetWorldCorner(&dMin,0);		
	SetWorldCorner(&dMax,1);
	////////////////////////
}
	
void CDrProf_C::TransformObjectToView(pMATRIX pViewM)
{
	////////////////////////////
	WORLD dMin,dMax,dMinN,dMaxN;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MAX; 
	dMax.y = -DBL_MAX; 
	dMax.z = -DBL_MAX;
	/////////////////////////////////////////////////////////////// Curve
	m_pCurve->TransformObjectToView(pViewM);
	///////////////////////
	m_pCurve->GetEyeCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pCurve->GetEyeCorner(&dMaxN,1);
	dMax = Calc_NewMax(dMax,dMaxN);
	////////////////////////
	SetEyeCorner(&dMin,0);		
	SetEyeCorner(&dMax,1);
	////////////////////////		
}	

BOOL CDrProf_C::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	//////////////////////
	BOOL bCulledObject = TRUE,bCulled;
	/////////////////////////////////////////////////////////////// Curve
	if(nType == 1)	// Cull3D
		return bCulledObject = FALSE;
	/////////////////////////////////////////////////	
	bCulled = m_pCurve->RemoveHiddenObject(pViewM,VDir,nType);
	///////////////////////
	if(!bCulled)
		bCulledObject = FALSE;
	////////////////////
	return bCulledObject;
	
}			 
				
void CDrProf_C::ProjectObject
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
	/////////////////////////////////////////////////////////////// Posted Curves
	m_pCurve->ProjectObject(pvv3DM,dScale_U,dScale_V);
	///////////////////////
	m_pCurve->GetScreen3DCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pCurve->GetScreen3DCorner(&dMaxN,1);
	dMax = Calc_NewMax(dMax,dMaxN);
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

void CDrProf_C::Calc_ScreenRectFromGenerators()
{

	CRect		BoundRect,theRect(0,0,0,0);	
	/////////////////////////////////////////////////////////////// Curve
	BoundRect = m_pCurve->GetBoundingRect();
	BoundRect.NormalizeRect();
	theRect.UnionRect(&theRect,&BoundRect);
	/////////////////////////// set
	m_rectBounding = theRect;
	///////////////////////////
}				

WORLD CDrProf_C::Calc_NewMin(WORLD dMinO, WORLD dMinN)
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

WORLD CDrProf_C::Calc_NewMax(WORLD dMaxO, WORLD dMaxN)
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
////////////////////////////////////////////////////////////
void CDrProf_C::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
 	///////////////////////////////////////////// Draw 
	m_pCurve->DoDrawView(PtrDC,bPenChange);
	//////////////////////////////////////////

}                            
/////////////////////////////////////////////////////////////////////////////
BOOL CDrProf_C::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrProf_C* pDrObj3D = (CDrProf_C*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrObj3D->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrProf_C::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrProf_C* pObj3D = (CDrProf_C*)pObject;
		///////////////////////////////////
		if(pObj3D->GetObjectType() == OBJ3D)
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

int CDrProf_C::AppendToObject(
								CDListMgr* pCurveList
							)
{							
	////////////////////
	if(pCurveList && !(pCurveList->IsEmpty()) )
		GetCurveList()->AddTail(pCurveList);
	else
		return -1;	
	///////////////
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////
void CDrProf_C::Serialize(CArchive& ar)
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

