// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgrafrm.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
//#include "globals.h" 
///////////////////// dialogMgr
//#include "MO3DMgr.h"				todo 
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// specials
#include "Def_Spec.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "MI_Obj3D.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Obj3D,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Obj3D::CMI_Obj3D()
{
}

CMI_Obj3D::~CMI_Obj3D()
{
}

int CMI_Obj3D::LBDownInit_OInsert() 
{	
			
    /////////
	return 0;

}

int CMI_Obj3D::LBUpInit_OInsert() 
{
	/////////
	return 0;
}
	
int CMI_Obj3D::LBUp_OInsert(CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrObj3D 		= O_GetInfo();                  	// Obj3D Dialog
	if(!m_pDrObj3D)		// cancel
		return -1;
	////////////////////////////
	InsertAllInfo();
	//////////////////////////////////////////////////////////
	CString Obj3DID	= m_pDrObj3D->GetObjectID();
	int nObj3DIndex = pDListMgr->GetObjectIndex(OBJ3D,Obj3DID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nObj3DIndex);
	pObjectMgr->SetActiveObjectType(OBJ3D);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nObj3DIndex,OBJ3D);
	/////////
	return 0;		 
}			

int CMI_Obj3D::InsertAllInfo()
{ 

	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
//	m_pDrObj3D->Calc_3DBoundsLocal();											
	///////////////////////////////
	return 0;
	///////////////
	
}			 

CDrObj3D* CMI_Obj3D::O_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	//////////////////////////////////////////////////////////////////
//	CMSolMgr* pMSolMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
//	if (pMSolMgr->DoModal_Obj3D(&Cid) == IDCANCEL)
//		return (CDrObj3D*)NULL; 
	///////////////////////////////////////////////////	
	index 				= pObjectMgr->
							GetObjectIndexfromKey(OBJ3D,Cid,1);
	if(index>=0)
	{						
		CDrObj3D* pDrObj3D	= (CDrObj3D*)(pDListMgr->GetObject(index));
		////////////////		
		return pDrObj3D; 
	}
	else
		return (CDrObj3D*)NULL;
		
}			

void CMI_Obj3D::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MI_Obj3D:   Storing\n");	
		//////////////////////////////

	}
	else
	{
		TRACE(" MI_Obj3D: 	Loading\n");	
 		//////////////////////////////
	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


