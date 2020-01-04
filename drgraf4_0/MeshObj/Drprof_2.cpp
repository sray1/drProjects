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
#include "Def_Elem.h"
//#include "Ext_Cur.h"
#include "DrMesh2D.h"
/////////////////////
#include "MatObj.h"

#include "DrProf_2.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrProf_2
IMPLEMENT_SERIAL(CDrProf_2, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrProf_2, CDrObject)
	//{{AFX_MSG_MAP(CDrProf_2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrProf_2::CDrProf_2()
{  
    	
    //////////////////////////////	
    SetObjectType((int)M1_PROFILE);
    SetElemType((int)GENR_OBJECT);          //
    //////////////////////////////  
	m_ObjectID		= " ";
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
//	m_pMatObj = NULL;	 
} 
    	
CDrProf_2::~CDrProf_2()
{  
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrProf_2::ReadyToDelete()
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
    ////////////////////////////////////////////////////////// Mesh1D
	pList = GetMesh2DList();
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
   
int CDrProf_2::DealObjectDialog()
{
/*
	CDrProf_2Prop	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrProf_2::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrProf_2* pAdd = (CDrProf_2*) pObject;
	//////////////////////////////////////////////////////// CopyList
	pAdd->m_pMesh2D	= m_pMesh2D;		// Profile Assembled Mesh1D
	if(!(pAdd->m_Mesh2DList.IsEmpty()) )
		m_Mesh2DList.AddTail(&(pAdd->m_Mesh2DList) ); 
 //	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
	if(!(pAdd->m_LMList.IsEmpty()) )
		m_LMList.AddTail(&(pAdd->m_LMList) ); 
    ////////////////////////
	return;
}		

void CDrProf_2::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrProf_2* pAdd		= (CDrProf_2*) pObject;
	//////////////////////////////////////////////////////// CopyList
    pAdd->m_pMesh2D 		= m_pMesh2D;
	if(!(m_Mesh2DList.IsEmpty()) )
		pAdd->m_Mesh2DList.AddTail(&m_Mesh2DList ); 
 //	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
	if(!(m_LMList.IsEmpty()) )
		pAdd->m_LMList.AddTail(&m_LMList ); 
    ////////////////////////
	return;
}
		
//////////////////////////////////////////////////////////////
void CDrProf_2::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
						
void CDrProf_2::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrProf_2::Pack_drPipe(CString* pstrCard)
{
/*
   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_Mesh1DTypes;i++)
   		if(CuTypes[i].num == M1_PROFILE) 
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
*/
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
int CDrProf_2::Calc_3DBoundsLocal()
{
	m_pMesh2D->Calc_3DBoundsLocal();
	////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrProf_2::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
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
	/////////////////////////////////////////////////////////////// Mesh1D
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
	m_pMesh2D->TransformObjectToWorld(pLMP,bYesOP);   // CentroidWORLD is also created 
	///////////////////////
	m_pMesh2D->GetWorldCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pMesh2D->GetWorldCorner(&dMaxN,1);
	dMax = Calc_NewMax(dMax,dMaxN);
	////////////////////////
	SetWorldCorner(&dMin,0);		
	SetWorldCorner(&dMax,1);
	////////////////////////
}
	
void CDrProf_2::TransformObjectToView(pMATRIX pViewM)
{
	////////////////////////////
	WORLD dMin,dMax,dMinN,dMaxN;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MAX; 
	dMax.y = -DBL_MAX; 
	dMax.z = -DBL_MAX;
	/////////////////////////////////////////////////////////////// Mesh1D
	m_pMesh2D->TransformObjectToView(pViewM);
	///////////////////////
	m_pMesh2D->GetEyeCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pMesh2D->GetEyeCorner(&dMaxN,1);
	dMax = Calc_NewMax(dMax,dMaxN);
	////////////////////////
	SetEyeCorner(&dMin,0);		
	SetEyeCorner(&dMax,1);
	////////////////////////		
}	

BOOL CDrProf_2::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	//////////////////////
	BOOL bCulledObject = TRUE,bCulled;
	/////////////////////////////////////////////////////////////// Mesh1D
	if(nType == 1)	// Cull3D
		return bCulledObject = FALSE;
	/////////////////////////////////////////////////	
	bCulled = m_pMesh2D->RemoveHiddenObject(pViewM,VDir,nType);
	///////////////////////
	if(!bCulled)
		bCulledObject = FALSE;
	////////////////////
	return bCulledObject;
	
}			 
				
void CDrProf_2::ProjectObject
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
	/////////////////////////////////////////////////////////////// Posted Mesh1Ds
	m_pMesh2D->ProjectObject(pvv3DM,dScale_U,dScale_V);
	///////////////////////
	m_pMesh2D->GetScreen3DCorner(&dMinN,0);
	dMin = Calc_NewMin(dMin,dMinN);
	m_pMesh2D->GetScreen3DCorner(&dMaxN,1);
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

void CDrProf_2::Calc_ScreenRectFromGenerators()
{

	CRect		BoundRect,theRect(0,0,0,0);	
	/////////////////////////////////////////////////////////////// Mesh1D
	BoundRect = m_pMesh2D->GetBoundingRect();
	BoundRect.NormalizeRect();
	theRect.UnionRect(&theRect,&BoundRect);
	/////////////////////////// set
	m_rectBounding = theRect;
	///////////////////////////
}				

WORLD CDrProf_2::Calc_NewMin(WORLD dMinO, WORLD dMinN)
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

WORLD CDrProf_2::Calc_NewMax(WORLD dMaxO, WORLD dMaxN)
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
void CDrProf_2::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
 	///////////////////////////////////////////// Draw 
	m_pMesh2D->DoDrawView(PtrDC,bPenChange);
	//////////////////////////////////////////

}                            
/////////////////////////////////////////////////////////////////////////////
BOOL CDrProf_2::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrProf_2* pDrObj3D = (CDrProf_2*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrObj3D->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrProf_2::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrProf_2* pObj3D = (CDrProf_2*)pObject;
		///////////////////////////////////
		if(pObj3D->GetObjectType() == MBJ3D)
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

int CDrProf_2::AppendToObject(
								CDListMgr* pMesh2DList
							)
{							
	////////////////////
	if(pMesh2DList && !(pMesh2DList->IsEmpty()) )
		GetMesh2DList()->AddTail(pMesh2DList);
	else
		return -1;	
	///////////////
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////
void CDrProf_2::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{

		TRACE( " DrProf_2   :Storing\n");	// TODO: add loading code here

 	}
	else
	{
	
		TRACE( " DrProf_2   :Loading\n");	// TODO: add loading code here


	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

