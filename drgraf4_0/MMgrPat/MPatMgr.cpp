// MouseMgr.cpp : implementation file
//
#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
//#include "globals.h"
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Glb_Cur.h"
#include "Glb_Pat.h"
#include "Glb_Sol.h"
#include "glb_Elem.h"
#include "Def_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// Patch
#include "dlg_Gordon.h"
#include "dlg_Tensor.h"
#include "dlg_TenBlend.h"
#include "dlg_LoftX.h"
#include "dlg_LoftCC.h"	// Curve Count
#include "dlg_Torq.h"	// Duct/Sweep Twist Factors
#include "dlg_Radius.h"	// Duct/Sweep Radius Factors
#include "dlg_CooT.h"	// Coon Type 			
/////////////////////
#include "MPatDll.h"
////////////////////
#include "MPatRsrc.h"
////////////////////
#include "MPatMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMPatMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMPatMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMPatMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMPatMgr::CMPatMgr()
{
}

CMPatMgr::~CMPatMgr()
{
}

HINSTANCE CMPatMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMPat_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMPatMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT CMPatMgr::DoModal_Patch_Post(CString* pID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_PPost PPostDlg;
	nStatus = PPostDlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = PPostDlg.m_PID_Post;
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
UINT CMPatMgr::DoModal_PatchCon(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_PCon Dlg_PCon;
	UINT nStatus;
	Dlg_PCon.m_nMaxCNodes_S	= nHowMany;		
	Dlg_PCon.m_nMaxCNodes_T	= nHowMany;		
	Dlg_PCon.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_PCon.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_PCon.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_Extrude(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Xtrd Dlg_Xtrd;
	UINT nStatus;
	Dlg_Xtrd.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_Xtrd.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_Xtrd.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_Rotate(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_RotP Dlg_RotP;
	UINT nStatus;
	Dlg_RotP.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_RotP.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_RotP.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_Coon(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CooP Dlg_CooP;
	UINT nStatus;
	Dlg_CooP.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_CooP.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_CooP.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_CoP3(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CoP3 Dlg_CooP;
	UINT nStatus;
	Dlg_CooP.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_CooP.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_CooP.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_Co34(UINT* pType,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CooT Dlg_CooP;
	UINT nStatus;
	///////////////////////////////////////		
	nStatus = Dlg_CooP.DoModal();
	/////////////////////////////////////// Update 
    if(Dlg_CooP.m_nType == 1)	// Triangular 
		*pType		 = PS_TRIANGLE;
	else
    if(Dlg_CooP.m_nType == 2)	// Quadrilateral
		*pType		 = PS_QUADRILAT;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
*/ 
UINT CMPatMgr::DoModal_Patch_LoftX(CDrCurve* pDrCurve,int nLoftCurves)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_LoftX Dlg_Loft;
	UINT nStatus;
	Dlg_Loft.m_pDrCurve		= pDrCurve;		
	Dlg_Loft.m_nLoftCurves	= nLoftCurves;		
	///////////////////////////////////////		
	nStatus = Dlg_Loft.DoModal();
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_TensorBlend(CDrCurve* pDrCurve,int nLoftCurves,int nDir)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_TensorBlend Dlg;
	UINT nStatus;
	Dlg.m_Dir			= nDir;		
	Dlg.m_pDrCurve		= pDrCurve;		
	Dlg.m_nLoftCurves	= nLoftCurves;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_LoftCurveCount(int& nCurves_U)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_LoftCC Dlg_LoftCC;
	UINT nStatus;
	///////////////////////////////////////		
	nStatus = Dlg_LoftCC.DoModal();
	///////
	nCurves_U = Dlg_LoftCC.m_nCurve_U;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_GordonCurveCount(int& nCurves_U,int& nCurves_V)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Gordon Dlg_Gordon;
	UINT nStatus;
	///////////////////////////////////////		
	nStatus = Dlg_Gordon.DoModal();
	///////
	nCurves_U = Dlg_Gordon.m_nCurve_U;		
	nCurves_V = Dlg_Gordon.m_nCurve_V;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMPatMgr::DoModal_Patch_TensorNodeCount(int& nNodes_U,int& nNodes_V)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Tensor Dlg_Tensor;
	UINT nStatus;
	///////////////////////////////////////		
	nStatus = Dlg_Tensor.DoModal();
	///////
	nNodes_U = Dlg_Tensor.m_nNode_U;		
	nNodes_V = Dlg_Tensor.m_nNode_V;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMPatMgr::DoModal_Patch_TwistFactors(pDOUBLE pTwist,int nMaxTwist,double& dScale)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Torq Dlg_Torq;
	UINT nStatus;
	///////////////////////////////////////
	Dlg_Torq.m_nMaxTwist	= nMaxTwist;
	Dlg_Torq.m_pTwist		= pTwist;	// pointer supplied by calling routine
	///////////////////////////////////////		
	nStatus = Dlg_Torq.DoModal();
	///////
	dScale	= Dlg_Torq.m_dScale;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMPatMgr::DoModal_Patch_RadiusFactors(pDOUBLE pRadius,int nMaxRadius,double& dScale)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Radius Dlg_Radius;
	UINT nStatus;
	///////////////////////////////////////
	Dlg_Radius.m_nMaxRadius	= nMaxRadius;
	Dlg_Radius.m_pRadius	= pRadius;	// pointer supplied by calling routine
	///////////////////////////////////////		
	nStatus = Dlg_Radius.DoModal();
	///////
	dScale	= Dlg_Radius.m_dScale;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMPatMgr::DoModal_Patch_Loft(CString* pID,int nHowMany)	// NOT USED ANYMORE(5/20/99)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Loft2 Dlg_Loft;
	Dlg_Loft.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_Loft.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_Loft.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
*/
	return nStatus;
	///////////////    
}
/* 
UINT CMPatMgr::DoModal_Patch_Swip(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Swip Dlg_Swip;
	UINT nStatus;
	Dlg_Swip.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_Swip.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_Swip.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMPatMgr::DoModal_Patch_Duct(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Duct Dlg_Duct;
	UINT nStatus;
	Dlg_Duct.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_Duct.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_Duct.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
//	Moved to CreOMgr Dll   01/14/98 

UINT CMPatMgr::DoModal_Spawn_P(CDrPatch* pNewPatch,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnP Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Item
	Dlg.m_pDrPatch	= pNewPatch;
	Dlg.m_CID		= ParentCid;
	///////////////////////////////////////		
	nStatus			= Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_SpawnID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

CDrPatch* CMPatMgr::SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnP	Dlg_SpnP;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrPatch* pAdd 	= (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
	////////////////////////////////////
	Dlg_SpnP.m_SpawnID		= Cid;
	Dlg_SpnP.m_bInstanced 	= FALSE;
	Dlg_SpnP.m_CID		 	= ParentCid;
	Dlg_SpnP.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnP.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	pAdd->SetPatchProc(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
//	Moved to CreOMgr Dll   01/14/98 end
*/ 

// CMPatMgr serialization

void CMPatMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MPatMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MPatMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


