// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "glb_Objs.h"
///////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "EBoxmgr.h" 
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "EDl2Mgr.h"
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
/////////////////////
#include "MS_Xtrud.h" 
#include "MS_Xtru3.h" 
#include "MS_Rotat.h" 
#include "MS_Rota3.h" 
#include "MS_Lof42.h"
#include "MS_Lof32.h"
#include "MS_Duct.h" 
#include "MS_Duc3.h" 
#include "MS_Sweep.h" 
///////////////////// 
#include "MI_Sol_I.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_SATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Sol_I,CMI_Patch,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Sol_I::CMI_Sol_I()
{
	m_pOut = NULL;
}

CMI_Sol_I::~CMI_Sol_I()
{
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	   
}

int CMI_Sol_I::LBDownInit_SInsert(UINT nType) 
{
//	m_bDirtySolid		= FALSE;
	return 0;
}

int CMI_Sol_I::LBUpInit_SInsert(enum PATCHTYPE kind) 
{
	return 0;
}
/*
int CMI_Sol_I::LBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 	= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
    CELMouse* pELMouse	= pDoc->GetMouseMgr()->GetELMouse(nView);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(m_nCNodeDone <= 0) 								// Firsttime 
	{
		m_pDrSolid 		= S_Mesh_GetInfo(1);   			// SGen Dialog
		if(!m_pDrSolid)		// cancel
			return -1;
	}	
	///////////////////////////////////////////////////////////
	if(!pELMouse->ShowNode(pID,TRUE,1))              	// Control Nodes
	{
		m_nCNodeDone++;
		SetCurrentCNodeID(*pID);
	}
	else									// cancelled
		return -1;
	///////////		          
	SaveCNode(m_pDrSolid->GetCNodeList(),pID);
	/////////////////////////////////////
	if(m_nCNodeDone < m_nMaxSolidCNodes)
		return 0;
	///////////////////////////////////////////////////////////////////// Go Generate	
	m_nCNodeDone = 1; 	//reset
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrSolid->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	//////////////////////////////// Compute Cubics & Fill DrSolid Info
	m_pCNodeList = m_pDrSolid->GetCNodeList();
	//////////////////////////////
	////////////	
	m_pDrSolid->SetSolidType(m_SolidType);
	m_pDrSolid->SetPatchType(kind);
	//////////////////////////////////////////////////////////
	// 	NumberOfCubicSolides() Computes & Sets in DrSolid:	//
	//					m_nMaxCubicSolides_S            	//
	//					m_nMaxCubicSolides_T            	//
	//					m_nMaxCubicSolides_R            	//
	//					m_nOut_S							//			
	//					m_nOut_T							//							
	//					m_nOut_R							//							
	//					m_nOut      						//
	//////////////////////////////////////////////////////////							
	m_pDrSolid->NumberOfCubicSolides();
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex);
	/////////
	return 0;		 
}			
*/
int CMI_Sol_I::RBUp_SDuctInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	UINT		nOption;
	if (pEDlgMgr->DoModal_Patch_Co34(&nOption,1) == IDCANCEL)
		return -1;
	////////////////////////// from Triangular Patch
	if(nOption == PS_TRIANGLE)
	{
		CMS_Duc3	MS_Duct;
		/////////
		m_pDrSolid = MS_Duct.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	else
	////////////////////////// from Quadrilateral Patch
	if(nOption == PS_QUADRILAT)
	{	
		CMS_Duct	MS_Duct;
		/////////
		m_pDrSolid = MS_Duct.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(SOLID);
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Sol_I::RBUp_SSweepInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CMS_Sweep	MS_Sweep;
	m_pDrSolid = MS_Sweep.GoDoIt();
	if(!m_pDrSolid)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(SOLID);
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Sol_I::RBUp_SLoft2Insert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	UINT		nOption;
	if (pEDlgMgr->DoModal_Patch_Co34(&nOption,1) == IDCANCEL)
		return -1;
	////////////////////////// from Triangular Patch
	if(nOption == PS_TRIANGLE)
	{
		CMS_Lof32	MS_Loft2;
		/////////
		m_pDrSolid = MS_Loft2.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	else
	////////////////////////// from Quadrilateral Patch
	if(nOption == PS_QUADRILAT)
	{	
		CMS_Lof42	MS_Loft2;
		/////////
		m_pDrSolid = MS_Loft2.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(SOLID);
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Sol_I::RBUp_SCoonInsert(CView* pView) 
{
/*
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////
	CMS_Loft2	MS_Loft2;
	m_pDrSolid = MS_Loft2.GoDoIt();
	if(!m_pDrSolid)
		return -1;
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex);
	/////////////////////
*/
	return 0;		 
}			

int CMI_Sol_I::RBUp_SRotateInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	UINT		nOption;
	if (pEDlgMgr->DoModal_Patch_Co34(&nOption,1) == IDCANCEL)
		return -1;
	////////////////////////// from Triangular Patch
	if(nOption == PS_TRIANGLE)
	{
		CMS_Rota3	MS_Rotat;
		/////////
		m_pDrSolid = MS_Rotat.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	else
	////////////////////////// from Quadrilateral Patch
	if(nOption == PS_QUADRILAT)
	{	
		CMS_Rotat	MS_Rotat;
		/////////
		m_pDrSolid = MS_Rotat.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(SOLID);
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}			

int CMI_Sol_I::RBUp_SExtrudeInsert(CView* pView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////
	CEDl2Mgr* 	pEDlgMgr;
	UINT		nOption;
	if (pEDlgMgr->DoModal_Patch_Co34(&nOption,1) == IDCANCEL)
		return -1;
	////////////////////////// from Triangular Patch
	if(nOption == PS_TRIANGLE)
	{
		CMS_Xtru3	MS_XtruT;
		/////////
		m_pDrSolid = MS_XtruT.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	else
	////////////////////////// from Quadrilateral Patch
	if(nOption == PS_QUADRILAT)
	{	
		CMS_Xtrud	MS_Xtrud;
		/////////
		m_pDrSolid = MS_Xtrud.GoDoIt();
		if(!m_pDrSolid)
			return -1;
	}
	//////////////////////////////////////////////////////////
	CString SolidID	= m_pDrSolid->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(SOLID);
	int nSolidIndex = pDListMgr->GetObjectIndex(SOLID,SolidID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nSolidIndex);
	pObjectMgr->SetActiveObjectType(SOLID);
    ////////////////////////////////////////////////////////// done/Invalidate
	m_pDrSolid->SetDirty(TRUE);
	m_pDrSolid->SetShow(TRUE);	// make it visible
   ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nSolidIndex,SOLID);
	/////////////////////
	return 0;		 
}
/*
int CMI_Sol_I::RBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView) 
{

	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrSolid 		= S_Mesh_GetInfo(2);                  	// PCon Dialog
	if(!m_pDrSolid)		// cancel
		return -1; 
	/////////////////////////////////////////////// Copy ControlNodes (Right Button)
	m_pCNodeList = m_pDrSolid->GetCNodeList();	
	///////////////////////////////////////////////////////////////////// Go Generate	
	char buf[80];
	CString str;
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrSolid->GetCNodeList()->GetCount());
	AfxMessageBox(str = buf);
	/////////
	return 0;		 
}			

CDrSolid* CMI_Sol_I::S_Mesh_GetInfo(int nButton)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CEDl2Mgr* pEDlgMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if(nButton ==1)		//Left Button
//todo		if (pEDlgMgr->DoModal_MeshGen(&Cid,0) == IDCANCEL)
			return (CDrSolid*)NULL;
	if(nButton ==2)		//Right Button
		if (pEDlgMgr->DoModal_SolidCon(&Cid,4) == IDCANCEL)
			return (CDrSolid*)NULL;
    /////////////////////////////////////////////////////// update
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
		m_nMaxSolidCNodes_S	= pDrSolid->GetMaxCNodes_S();
		m_nMaxSolidCNodes_T	= pDrSolid->GetMaxCNodes_T();
		m_nMaxSolidCNodes_R	= pDrSolid->GetMaxCNodes_R();
		///////////////////////////////////////////////////
		m_nMaxSolidCNodes_ST = m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
		m_nMaxSolidCNodes	 = m_nMaxSolidCNodes_ST * m_nMaxSolidCNodes_R;
		///////////////////////////////////////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			
*/
////////////////////////////////////////////////////////////
void CMI_Sol_I::Serialize(CArchive& ar)
{

	CMI_Pat_I::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MI_SOL_I:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" MI_SOL_I:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


