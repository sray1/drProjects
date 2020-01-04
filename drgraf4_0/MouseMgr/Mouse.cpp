// Mouse.cpp : implementation file
//
#include "stdafx.h"

//#include "Def_Lims.h"
#include "Def_View.h"
////////////////////
#include "drgraf.h"
#include "drawView.h"
#include "drgrafrm.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "MsObjMgr.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// specials
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
/////////////////////
#include "mouse.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define NODERECTMARGIN	7
////////////////////////////////////
IMPLEMENT_SERIAL(CMouse,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMouse::CMouse()
{

	ReadDefaults();
	Initialize();
	
}
CMouse::~CMouse()
{
}

void CMouse::SetViewNumber(UINT nView)
{
	m_nView = nView;
} 

/////////////////////////////////////////////////////////////// INITIALIZE 
void CMouse::Initialize()
{ 
	/////////////////////////////////////////// Mouse 
	m_MouseWIC     = m_MouseDefaultWIC;
	m_MouseOldWIC  = m_MouseWIC;
}
void CMouse::ReadDefaults()
{
//////////////////////////////////////////////////TEMPORARILY being Set HERE
//                                                Later Read in from DOC FILE
	/////////////////////////////////////////// Mouse 
	m_MouseDefaultWIC.x = 0;
	m_MouseDefaultWIC.y = 0;
	m_MouseDefaultWIC.z = 0;

}
void CMouse::SetMouseWIC(LPOINT3 NewMouseWIC)	
{
    m_MouseWIC.x = NewMouseWIC.x;
    m_MouseWIC.y = NewMouseWIC.y;
    m_MouseWIC.z = NewMouseWIC.z;
}    				
void CMouse::SetMouseOldWIC(LPOINT3 NewMouseOldWIC)	
{
    m_MouseOldWIC.x = NewMouseOldWIC.x;
    m_MouseOldWIC.y = NewMouseOldWIC.y;
    m_MouseOldWIC.z = NewMouseOldWIC.z;
}    				

void CMouse::WICtoWOR(long LongC,pDOUBLE pDblC)
{

	///////////////////////////////////////////
   	*pDblC 		= (double)LongC;
   	////////////////////////////// 
   		
}

void CMouse::WICtoWOR(LPOINT3* pWIC,pWORLD pWorld)
{
	///////////////////////////////////////////
   	pWorld->x 		= (double)(pWIC->x);
   	pWorld->y 		= (double)(pWIC->y);
   	pWorld->z 		= (double)(pWIC->z);
	//////////////////////////////////////// 
   		
}
void CMouse::WICtoWOP(long LongC,pDOUBLE pDblC)
{

	long LC = LongC;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
   	*pDblC 		= ((double)(LC))/dWorldBase;
   	////////////////////////////// Map Factor
   	*pDblC 		*= dMapFactor;
 	//////////////////////// World Coord
	pObjectMgr->DStoSC(pDblC);
	//////////////////////////////////////// 
   		
}

void CMouse::WICtoWOP(LPOINT3* pWIC,pWORLD pWorld)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
   	pWorld->x 		= ((double)(pWIC->x))/dWorldBase;
   	pWorld->y 		= ((double)(pWIC->y))/dWorldBase;
   	pWorld->z 		= ((double)(pWIC->z))/dWorldBase;
   	////////////////////////////// Map Factor
   	pWorld->x 		*= dMapFactor;
   	pWorld->y 		*= dMapFactor;
   	pWorld->z 		*= dMapFactor;
 	//////////////////////// World Coord
	pObjectMgr->DStoSC(&pWorld->x);
	pObjectMgr->DStoSC(&pWorld->y);
	pObjectMgr->DStoSC(&pWorld->z);
	//////////////////////////////////////// 
   		
}

void CMouse::WORtoWOP(pDOUBLE pWorld,pDOUBLE pPhysi)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
   	*pPhysi 		= (*pWorld)/dWorldBase;
   	////////////////////////////// Map Factor
   	*pPhysi 		*= dMapFactor;
 	//////////////////////// World Coord
	pObjectMgr->DStoSC(pPhysi);
	//////////////////////////////////////// 
   		
}

void CMouse::WOPtoWOR(pDOUBLE pPhysi,pDOUBLE pWorld)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
 	//////////////////////// Scaled Coord
	pObjectMgr->SCtoDS(pPhysi);
   	////////////////////////////// Map Factor
   	*pPhysi 		/= dMapFactor;
	//////////////////////////////////////// 
   	*pWorld 		= (*pPhysi)*dWorldBase;
 	///////////////////////////////////////////
  		
}

void CMouse::WORtoWOP(pWORLD pWorld,pWORLD pPhysi)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
   	pPhysi->x 		= ((double)(pWorld->x))/dWorldBase;
   	pPhysi->y 		= ((double)(pWorld->y))/dWorldBase;
   	pPhysi->z 		= ((double)(pWorld->z))/dWorldBase;
   	////////////////////////////// Map Factor
   	pPhysi->x 		*= dMapFactor;
   	pPhysi->y 		*= dMapFactor;
   	pPhysi->z 		*= dMapFactor;
 	//////////////////////// World Coord
	pObjectMgr->DStoSC(&pPhysi->x);
	pObjectMgr->DStoSC(&pPhysi->y);
	pObjectMgr->DStoSC(&pPhysi->z);
	//////////////////////////////////////// 
   		
}

void CMouse::WOPtoWOR(pWORLD pPhysi,pWORLD pWorld)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
 	//////////////////////// Scaled Coord
	pObjectMgr->SCtoDS(&pPhysi->x);
	pObjectMgr->SCtoDS(&pPhysi->y);
	pObjectMgr->SCtoDS(&pPhysi->z);
   	////////////////////////////// Map Factor
   	pPhysi->x 		/= dMapFactor;
   	pPhysi->y 		/= dMapFactor;
   	pPhysi->z 		/= dMapFactor;
	//////////////////////////////////////// 
   	pWorld->x 		= pPhysi->x*dWorldBase;
   	pWorld->y 		= pPhysi->y*dWorldBase;
   	pWorld->z 		= pPhysi->z*dWorldBase;
 	///////////////////////////////////////////
  		
}

void CMouse::WOPtoWIC(long* pLongC,double DblC)
{

	double dblC = DblC;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
 	//////////////////////// Scaled Coord
	pObjectMgr->SCtoDS(&dblC);
   	////////////////////////////// Map Factor
   	dblC 		/= dMapFactor;
	//////////////////////////////////////// 
   	*pLongC 	= (long)((dblC)*dWorldBase);
 	///////////////////////////////////////////
  		
}

void CMouse::WOPtoWIC(LPOINT3* pWIC,pWORLD pWorld)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase; 
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
 	//////////////////////// Scaled Coord
	pObjectMgr->SCtoDS(&pWorld->x);
	pObjectMgr->SCtoDS(&pWorld->y);
	pObjectMgr->SCtoDS(&pWorld->z);
   	////////////////////////////// Map Factor
   	pWorld->x 		/= dMapFactor;
   	pWorld->y 		/= dMapFactor;
   	pWorld->z 		/= dMapFactor;
	//////////////////////////////////////// 
   	pWIC->x 		= (long)(pWorld->x*dWorldBase);
   	pWIC->y 		= (long)(pWorld->y*dWorldBase);
   	pWIC->z 		= (long)(pWorld->z*dWorldBase);
 	///////////////////////////////////////////
  		
}
void CMouse::WORtoWIC(long* pLongC,double DblC)
{

	//////////////////////////////////////// 
   	*pLongC 	= (long)DblC;
 	///////////////////////////////////////////
  		
}

void CMouse::WORtoWIC(LPOINT3* pWIC,pWORLD pWorld)
{

	//////////////////////////////////////// 
   	pWIC->x 		= (long)(pWorld->x);
   	pWIC->y 		= (long)(pWorld->y);
   	pWIC->z 		= (long)(pWorld->z);
 	///////////////////////////////////////////
  		
}

void CMouse::DevtoScrolledWIC2D(CPoint point,LPOINT* pLptScrolled)
{ 
	/////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr(); 
	CPrecision* pPrecision = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
    //////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
//	CPrecision* pPrecision     = pDoc->GetPrecision();
	/////////////////////////////////// point:DeScaled
    pLptScrolled->x = (long)point.x; 
    pLptScrolled->y = (long)point.y;
	//////////////////////////////////////////// Precision           
	long lWorldBase = (long) pPrecision->GetWorldBase();
	pLptScrolled->x *= lWorldBase;
	pLptScrolled->y *= lWorldBase;
	//////////////////////////////

}
	
void CMouse::WICtoLOG(LPOINT3* pWIC,LPOINT* LpLOG)
{ 
 
	/////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr(); 
	CPrecision* pPrecision = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
    //////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
//	CPrecision* pPrecision     = pDoc->GetPrecision();
	////////////////////// 
	long lWorldBase = (long) pPrecision->GetWorldBase();
	pWIC->x /= lWorldBase;                    // Log
	pWIC->y /= lWorldBase;
	pWIC->z /= lWorldBase;
	//////////////////////////////////////////////// Log/DeScaled 
	if(m_nView == VIEW12)      // hor = x; ver = y;
	{
		LpLOG->x = pWIC->x;
		LpLOG->y = pWIC->y;
	}
	else if(m_nView == VIEW23) // hor = z; ver = y;
	{
		LpLOG->x = pWIC->z;
		LpLOG->y = pWIC->y;
	}
	else if(m_nView == VIEW31) // hor = z; ver = x;
	{
		LpLOG->x = pWIC->z;
		LpLOG->y = pWIC->x;
	}
	else if(m_nView == VIEWISO)      // hor = x; ver = y;  TEMPORARY as 12
	{
		LpLOG->x = pWIC->x;
		LpLOG->y = pWIC->y;
	}
    ///////////////////// 
}
	
void CMouse::LOGtoWIC2(LPOINT3* pWIC,LPOINT* LpLOG,LPOINT3* pOldWIC)
{                                       

	/////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr(); 
	CPrecision* pPrecision = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	/////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
//	CPrecision* pPrecision     = pDoc->GetPrecision();
	long lWorldBase = (long) pPrecision->GetWorldBase();
    //////////////////////								
	if (m_nView == VIEW12)        // hor = x; ver = y;
	{
		pWIC->x = LpLOG->x;
		pWIC->y = LpLOG->y;
		pWIC->z = pOldWIC->z/lWorldBase;
	}
	else if (m_nView == VIEW23)   // hor = z; ver = y;
	{
		pWIC->y = LpLOG->y;
		pWIC->z = LpLOG->x;
		pWIC->x = pOldWIC->x/lWorldBase;
	}
	else if (m_nView == VIEW31)   // hor = z; ver = x;
	{
		pWIC->z = LpLOG->x;	
		pWIC->x = LpLOG->y;
		pWIC->y = pOldWIC->y/lWorldBase;
	}
	else if (m_nView == VIEWISO)        // hor = x; ver = y;   TEMPORARY
	{
		pWIC->x = LpLOG->x;
		pWIC->y = LpLOG->y;
		pWIC->z = pOldWIC->z/lWorldBase;
	}
	
//	/////////////////// temporary (TOBEDONE:Modeless Dlg to input z)
//	pWIC->z = 0;
	////////////////////// 
	pWIC->x *= lWorldBase;
	pWIC->y *= lWorldBase;
	pWIC->z *= lWorldBase;
	////////////////////
}	

void CMouse::LOGtoWIC(LPOINT3* pWIC,LPOINT* LpLOG)
{                                       

	/////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr(); 
	CPrecision* pPrecision = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	/////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc );
//	CPrecision* pPrecision     = pDoc->GetPrecision();
	long lWorldBase = (long) pPrecision->GetWorldBase();
	////////////////////////////// 3rd Coord
	long c3;
	WOPtoWIC(&c3,m_ThirdCoord);
	////////////////////////////
	if (m_nView == VIEW12)           // hor = x; ver = y;
	{
		pWIC->x = LpLOG->x * lWorldBase;
		pWIC->y = LpLOG->y * lWorldBase;
		pWIC->z = c3;
	}
	else if (m_nView == VIEW23)      // hor = z; ver = y;
	{
		pWIC->y = LpLOG->y * lWorldBase;
		pWIC->z = LpLOG->x * lWorldBase;
		pWIC->x = c3;
	}
	else if (m_nView == VIEW31)      // hor = z; ver = x;
	{
		pWIC->z = LpLOG->x * lWorldBase;
		pWIC->x = LpLOG->y * lWorldBase;
		pWIC->y = c3;
	}
	else if (m_nView == VIEWISO)        // hor = x; ver = y;   TEMPORARY
	{
		pWIC->x = LpLOG->x * lWorldBase;
		pWIC->y = LpLOG->y * lWorldBase;
		pWIC->z = c3;
	}
	
	/////////////////////////
}	
/*
CView* CMouse::GetCurrentViewPointer(CRuntimeClass* pViewClass)
{
	/////////////////////////////////////////////////////////
	// also sets m_nView in CMouse and CDrGrafFrame 
	///////////////////////////////////////////////////////// 
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd ); 
	CMDIChildWnd* pMDIActive = pWnd->MDIGetActive();
	ASSERT(pMDIActive != NULL);
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);

	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			////////////////////////////////////// save in the Window
			pWnd->SetActiveViewNumber(m_nView);
			///////////////////////////////////
			return pView;
		}
	}
    return 0;
}
*/
 
void CMouse::SwitchThirdCoordHeading(CStatic* pCtl,UINT VuNum)
{
	switch(VuNum)
	{
		case VIEW12:
			pCtl->SetWindowText("Z");
			break;
		case VIEW23:
			pCtl->SetWindowText("X");
			break;
		case VIEW31:
			pCtl->SetWindowText("Y");
			break;
		case VIEWISO:
		default:
			return;
	}
}

int	CMouse::IsObjectHit(int nObjectType,pWORLD point, int startIndex)
{
	// 3D Problem
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////
	//			Return		>=0 ->index (Yes Hit)		//
	//						<0 -> No Hit				//
	//////////////////////////////////////////////////////
	pDListMgr = pObjectMgr->GetObjectList(nObjectType);
	////////////////////////////////////////////////
	if(pDListMgr->GetSpecificObjectCount(nObjectType) <= 0)
		return -1;
	///////////////////////////////////////////////////
	CHitNet* pHitNet = (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double dNet = pHitNet->GetSearchDet();
	////////////////////////////////
	BOOL bYes;			
	int i=-1;
	int nCount = pDListMgr->GetCount();
	///////////////////////////////////
	for (POSITION pos = pDListMgr->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		////////////////
		i++;
		////
		if(i<startIndex)
			continue;
		/////////////////////
		if(pObject->IsDeleted())
			continue;
		/////////////////////
		bYes = pObject->IsObjectHit(dNet,*point);	// all else
		if(bYes)
			return i;				
	}	
	return -1;
}

int	CMouse::IsObjectHit(int nObjectType,POINT point, int startIndex)
{
	// 2D Problem
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	////////////////// Return >=0 ->index (Yes Hit)
	//////////////////         <0 -> No Hit
	if(nObjectType == LABEL)
		return -1;
	////////////////////////////////////////////////////////
	pDListMgr = pObjectMgr->GetObjectList(nObjectType);
	////////////////////////////////////////////////
	if(pDListMgr->GetSpecificObjectCount(nObjectType) <= 0)
		return -1;
/*090498
	/////////////////////////////////////////////////// 
	CHitNet* pHitNet = (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	int nNet = pHitNet->GetSearchNet();
	////////////////////////////////
*/
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	//////////////////////////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		drad		= pHitNet->GetSearchDet();
	///
	drad 	= ((double)(drad))/dWorldBase;
	pObjectMgr->DStoSC(&drad);
	///
	int			nNet = (int)drad;	// in Pixels now 
	/////////////////////////////////
	BOOL bYes;			
	int i=-1;
	int nCount = pDListMgr->GetCount();
	///////////////////////////////////
	for (POSITION pos = pDListMgr->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		////////////////
		i++;
		////
		if(i<startIndex)
			continue;
		/////////////////////
		if(pObject->IsDeleted())
			continue;
		//////////////////////////////////////// Transform & Project
		((CDrawView*)m_pView)->GetObjectReadyforRender(m_pdc,pObject,nObjectType);
		/////////////////////
		bYes = pObject->IsObjectHit(nNet,point);	// all else
		if(bYes)
			return i;				
	}	
	return -1;
}

int	CMouse::IsObjectHit(int nObjectType,POINT point,CRect* pRect)
{
	// LABEL Hit (2D)
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	////////////////// Return >=0 ->index (Yes Hit)
	//////////////////         <0 -> No Hit
	if(nObjectType != LABEL)
		return -1;
	////////////////////////////////////////////////////////
	pDListMgr = pObjectMgr->GetObjectList(nObjectType);
	////////////////////////////////////////////////
	if(pDListMgr->GetSpecificObjectCount(nObjectType) <= 0)
		return -1;
	///////////////////////////////////////////////////
	CHitNet* pHitNet = (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	int nNet = pHitNet->GetSearchNet();
	////////////////////////////////
	BOOL bYes;			
	int i=0;
	for (POSITION pos = pDListMgr->GetFirstObjectPos();pos !=NULL;i++)
	{
	
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == nObjectType);
		{
			if(nObjectType == LABEL)
			{
				//////////////////////////////////////// Transform & Project
				((CDrawView*)m_pView)->GetObjectReadyforRender(m_pdc,pObject,nObjectType);
				/////////////////////
				bYes = pObject->IsObjectHit(m_pdc,nNet,point,pRect,m_nView);	// viewdependent
			}
			if(bYes)
				return i;				
        }
	}	
	return -1;
}

int CMouse::LabelHit_SetBMSize(CString& NodeID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(LABEL);
	///////////////////////////////////////////////////////////
	
	int nIndex = pList->GetObjectIndex(LABEL, NodeID);
	if(nIndex>=0)
	{
		CDrLabel* pLabel = (CDrLabel*)pList->GetObject(nIndex);
		/////////////////////////////////////////////////////////
		CSize	Size;
   		///////////////////////////////////////// get FontSize etc.
		m_Font.DeleteObject();
		m_lf = pLabel->GetLogFont();
		////////////////////////////// double it
		m_lf.lfHeight *=2;
		m_lf.lfWidth  *=2;
		//////////////////
		m_Font.CreateFontIndirect(&m_lf);
		CFont* pOldFont = (CFont*) m_pdc->SelectObject(&m_Font);
		Size		  = m_pdc->GetTextExtent(NodeID,NodeID.GetLength()); //log
		m_pdc->SelectObject(pOldFont);
		m_Font.Detach();
		/////////////////////////////////////////////////// increase by NODERECTMARGIN pix each side
		m_BMWidth = Size.cx + 2*NODERECTMARGIN;		// logical
		m_BMHeight= Size.cy + 2*NODERECTMARGIN;
		////////////
		return 0;
	}
	else
		return -1;
}


void CMouse::LabelHit_InitBM(CPoint Point,CString& NodeID)
{

	/////////////////////////////////////////////////////////// BMSize
	if(LabelHit_SetBMSize(NodeID)<0)
	{
		AfxMessageBox
			("Error:CMouse::LabelHit_InitBM\nLabelHit_SetBMSize");
		return;
	}
	/////////////////////////////////////////////////////////// Rectangle: dev 
															 // because neede in pixel
	CRect ObjectRect;
	ObjectRect.left		= Point.x;		//log
	ObjectRect.top		= Point.y;		//log
	ObjectRect.right	= Point.x + m_BMWidth;	//log
	ObjectRect.bottom	= Point.x + m_BMHeight;	//log
	///////////////////////	                          
	m_pdc->LPtoDP(&ObjectRect);		
	///////////////////////////////////////////////////////////  
    m_BitmapSave.CreateCompatibleBitmap
    	(&m_MemDC,ObjectRect.Width(), 	 				//width=pixel
    	            ObjectRect.Height());  				//height=pixel
	m_BitmapSource.CreateCompatibleBitmap
    	(&m_MemDC,ObjectRect.Width(), 	 				//width=pixel
    	            ObjectRect.Height());  				//height=pixel
 	/////////////////////////////////////////////////////////// because neede in logical	                          
	m_pdc->DPtoLP(&ObjectRect);		
	////////////////////////	
 	return;
}

void CMouse::LabelHit_ShowBM(CPoint point, CString& NodeID, BOOL bFirstTime)
{
	CDrGrafDoc* pDoc 	   = ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	CMapFactor* pMapFactor = (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
   	CPen    Pen;
	CPen*   pOldPen;
	CBrush Brush;
	CBrush* pOldBrush;
	///////////////////////////////////////////////// Restore Old Screen pix
	if(bFirstTime)
	{
		/////////////////////////////////////////////////////////
		m_MemDC.CreateCompatibleDC (m_pdc);
		/////////////////////////////////////////////////////////// MapMode
		m_MemDC.SetMapMode(pMapFactor->GetMapModeIndex());
	}
	else
	{
   		m_MemDC.SelectObject (&m_BitmapSave);
 		//////////////////////////////// Set InvalidRect 
		m_ObjectRectOld = m_ObjectRect;		//log
		////////////////////
		m_pdc->BitBlt
			(m_ObjectRectOld.left,
			m_ObjectRectOld.top,
   			m_ObjectRectOld.Width(),
			m_ObjectRectOld.Height(),
			&m_MemDC,
			0,
			0,
			SRCCOPY);
		///////////////////////////////////////////////// Delete Old Ones
   		m_BitmapSave.DeleteObject ();
   		m_BitmapSource.DeleteObject();
		//////////////////////////////
	}
	///////////////////////////////////////////////// Init New BM
	LabelHit_InitBM(point,NodeID);
	/////////////////////////////////////////////////////////// Rectangle:Logical 
	m_ObjectRect.left		= point.x;		//log
	m_ObjectRect.top		= point.y;		//log
	m_ObjectRect.right		= point.x + m_BMWidth;	//log
	m_ObjectRect.bottom		= point.x + m_BMHeight;	//log
	///////////////////////////////////////////////// Save New Screen pix
   	m_MemDC.SelectObject (&m_BitmapSave);
	///////////////////////////////////
	m_MemDC.BitBlt
    	(0,
         0,
   	     m_ObjectRect.Width(),
       	 m_ObjectRect.Height(),
         m_pdc,
         m_ObjectRect.left,
         m_ObjectRect.top,
   	     SRCCOPY);
	///////////////////////////////////////////////// draw New BM
   	m_MemDC.SelectObject (&m_BitmapSource);
	/////////////////////////////////// Yellow Pen
	// Create Yellow Pen 2 Pixel wide;
	int two = 2;
	COLORREF crColor = RGB(255,255,0);  
	Pen.CreatePen ((int)PS_SOLID,two,crColor);
	pOldPen = m_pdc->SelectObject(&Pen);
	/////////////////////////////////////////// Red Brush
	Brush.CreateSolidBrush(RGB(255,0,0));
	pOldBrush = m_pdc->SelectObject(&Brush);
	m_MemDC.Rectangle(&m_ObjectRect);
	m_MemDC.SelectObject(pOldBrush);
	m_MemDC.SelectObject(pOldPen);
	/////////////////////////////////////////// Text			todo: increase the font Size
	CFont* pOldFont = (CFont*) m_pdc->SelectObject(&m_Font);
	m_MemDC.SetTextColor(RGB(255,255,0));	// Yellow Text
	int x = m_ObjectRect.left + NODERECTMARGIN; 
	int y = m_ObjectRect.top  - NODERECTMARGIN;	//logical
	////////
	m_MemDC.TextOut(x, y, (LPCTSTR)&NodeID, NodeID.GetLength());
	m_MemDC.SelectObject(pOldFont);
	/////////////////////////// Copy ID
    m_pdc->BitBlt
        (m_ObjectRect.left,
   	     m_ObjectRect.top,
       	 m_ObjectRect.Width(),
         m_ObjectRect.Height(),
         &m_MemDC,
         0,
         0,
   	     SRCCOPY);
	/////////////////////////////////////// invalidate
	CRect tempRect,oldRect,newRect;
	newRect = m_ObjectRect;		//log 
	m_pdc->LPtoDP(&newRect);	//dev
	//////////////////////
	if(bFirstTime)
		m_InvalidMoveRect = newRect;	//dev
	else
	{
		oldRect = m_ObjectRectOld; 
		m_pdc->LPtoDP(&oldRect);
		tempRect.UnionRect(oldRect,newRect);
		m_InvalidMoveRect = tempRect;	//dev
	}
	////////////////////////////////////
    CRect clientRect;
	m_pView->GetClientRect(&clientRect);
	tempRect = m_InvalidMoveRect;
	m_InvalidMoveRect.IntersectRect(tempRect,clientRect);
    m_pView->InvalidateRect(&m_InvalidMoveRect);
	//////////////
    return;
}

void CMouse::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDragOn,bDragging,bRefreshOn; 
	WORD nView;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" Mouse:    Storing\n");	
		/////////////////////////////////////////////////
		ar	<</*UINT*/	(WORD)m_nView 
			<</*BOOL*/	(BYTE)m_bDragOn 
			<</*BOOL*/	(BYTE)m_bDragging 
			<</*BOOL*/	(BYTE)m_bRefreshOn 
			<</*POINT*/	m_MouseLOG
			<</*POINT*/	m_MouseOldLOG
			<</*POINT*/	m_AnchorNodeLOG 
			<</*POINT*/	m_PointOld;
		///////////////////////////////////////////MouseLoc
   		ar.Write(/*LPOINT*/	&m_LptScrolled,sizeof(LPOINT));
		ar	<</*POINT*/		m_MouseVUC
			<</*POINT*/		m_MouseOldVUC
			<</*POINT*/		m_AnchorVUC;
		ar.Write(/*LPOINT3*/&m_MouseWIC,sizeof(LPOINT3));
		ar.Write(/*LPOINT3*/&m_MouseOldWIC,sizeof(LPOINT3));
		ar.Write(/*LPOINT3*/&m_MouseDefaultWIC,sizeof(LPOINT3));
		ar.Write(/*LPOINT3*/&m_AnchorWIC,sizeof(LPOINT3));
		//////////////////////////////

	}        

	else
	{
		TRACE(" Mouse:    Loading\n");	
		/////////////////////////////////////////////////
		ar	>>/*UINT*/	nView 
			>>/*BOOL*/	bDragOn 
			>>/*BOOL*/	bDragging 
			>>/*BOOL*/	bRefreshOn 
			>>/*POINT*/	m_MouseLOG
			>>/*POINT*/	m_MouseOldLOG
			>>/*POINT*/	m_AnchorNodeLOG 
			>>/*POINT*/	m_PointOld;
 		//////////////////////////////
		m_nView			= (int)nView;
		m_bDragOn		= (BOOL)bDragOn;
		m_bDragging		= (BOOL)bDragging;
		m_bRefreshOn	= (BOOL)bRefreshOn;
	    /////////////////////////////////// MouseLoc
   		ar.Read(/*LPOINT*/	&m_LptScrolled,sizeof(LPOINT));
		ar	>>/*POINT*/		m_MouseVUC
			>>/*POINT*/		m_MouseOldVUC
			>>/*POINT*/		m_AnchorVUC;
		ar.Read(/*LPOINT3*/	&m_MouseWIC,sizeof(LPOINT3));
		ar.Read(/*LPOINT3*/	&m_MouseOldWIC,sizeof(LPOINT3));
		ar.Read(/*LPOINT3*/	&m_MouseDefaultWIC,sizeof(LPOINT3));
		ar.Read(/*LPOINT3*/	&m_AnchorWIC,sizeof(LPOINT3));
		//////////////////////////////
	    
	}
}

///////////////////////////////////// end of Module //////////////////////		

