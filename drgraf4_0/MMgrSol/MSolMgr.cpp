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
///////////////////// Solid
//#include "dlg_SCon.h"
#include "dlg_SXtr.h"
#include "dlg_SRot.h"
#include "dlg_SLof.h"
#include "dlg_SSwi.h"
#include "dlg_SDuc.h"
/*
//	Moved to CreOMgr Dll   01/14/98 
#include "dlg_SpnS.h"	// Solid Spawn
//#include "dlg_SPos.h"
//	Moved to CreOMgr Dll   01/14/98 end 
*/
//////////////////////
#include "dlg_Gordon.h"
#include "dlg_Tensor.h"
#include "dlg_TenBlend.h"
#include "dlg_LoftX.h"
#include "dlg_LoftCC.h"	// Curve Count
#include "dlg_Torq.h"	// Duct/Sweep Twist Factors
#include "dlg_Radius.h"	// Duct/Sweep Radius Factors
#include "dlg_CooT.h"	// Coon Type 			
/////////////////////
#include "MSolDll.h"
////////////////////
#include "MSolRsrc.h"
////////////////////
#include "MSolMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMSolMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMSolMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMSolMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMSolMgr::CMSolMgr()
{
}

CMSolMgr::~CMSolMgr()
{
}

HINSTANCE CMSolMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMSol_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMSolMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT CMSolMgr::DoModal_Solid_Post(CString* pID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SPost PPostDlg;
	nStatus = PPostDlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = PPostDlg.m_PID_Post;
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
*/
UINT CMSolMgr::DoModal_SolidCon(CString* pID,int nHowMany)	// NOT USED ANYMORE(5/20/99)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SCon Dlg_PCon;
	Dlg_PCon.m_nMaxCNodes_S	= nHowMany;		
	Dlg_PCon.m_nMaxCNodes_T	= nHowMany;		
	Dlg_PCon.m_nMaxCNodes_R	= nHowMany;		
	Dlg_PCon.m_nHowMany		= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg_PCon.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_PCon.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
*/
	return nStatus;
	///////////////    
}
 
UINT CMSolMgr::DoModal_Solid_Extrude(CString* pID,PATSUBTYPE TriORQuad)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Xtrd_S Dlg_Xtrd;
	UINT nStatus;
	Dlg_Xtrd.m_SubType		= TriORQuad;		
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
 
UINT CMSolMgr::DoModal_Solid_Rotate(CString* pID,PATSUBTYPE TriORQuad)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_RotP_S Dlg_RotP;
	UINT nStatus;
	Dlg_RotP.m_SubType		= TriORQuad;		
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
 
UINT CMSolMgr::DoModal_Solid_Loft(CString* pID,PATSUBTYPE TriORQuad)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Loft_S Dlg_Loft;
	UINT nStatus;
	Dlg_Loft.m_SubType		= TriORQuad;		
	///////////////////////////////////////		
	nStatus = Dlg_Loft.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg_Loft.m_PatchID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMSolMgr::DoModal_Solid_Swip(CString* pID,PATSUBTYPE TriORQuad)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Swip_S Dlg_Swip;
	UINT nStatus;
	Dlg_Swip.m_SubType		= TriORQuad;		
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
 
UINT CMSolMgr::DoModal_Solid_Duct(CString* pID,PATSUBTYPE TriORQuad)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Duct_S Dlg_Duct;
	UINT nStatus;
	Dlg_Duct.m_SubType		= TriORQuad;		
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
/*
//	Moved to CreOMgr Dll   01/14/98 
 
UINT CMSolMgr::DoModal_Spawn_S(CDrSolid* pNewSolid,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnS Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Item
	Dlg.m_pDrSolid	= pNewSolid;
	Dlg.m_CID		= ParentCid;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_SpawnID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

CDrSolid* CMSolMgr::SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnS	Dlg_SpnS;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrSolid* pAdd 	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
	////////////////////////////////////
	Dlg_SpnS.m_SpawnID		= Cid;
	Dlg_SpnS.m_bInstanced 	= FALSE;
	Dlg_SpnS.m_CID		 	= ParentCid;
	Dlg_SpnS.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnS.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	pAdd->SetSolidProc(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
//	Moved to CreOMgr Dll   01/14/98 end 
*/
///////////////////////////////////////////////////////////////////////////
UINT CMSolMgr::DoModal_Solid_LoftX(CDrCurve* pDrCurve,int nLoftCurves)
{
	UINT nStatus;
/*
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
*/
	return nStatus;
	///////////////    
}
 
UINT CMSolMgr::DoModal_Solid_TensorBlend(CDrCurve* pDrCurve,int nLoftCurves,int nDir)
{
	UINT nStatus;
/*
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
*/
	return nStatus;
	///////////////    
}
 
UINT CMSolMgr::DoModal_Solid_LoftPatchCount(int& nPatches_U)
{
	UINT nStatus;
/*
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
*/
	return nStatus;
	///////////////    
}
 
UINT CMSolMgr::DoModal_Solid_GordonPatchCount(int& nPatches_U,int& nPatches_V,int& nPatches_W)
{
	UINT nStatus;
/*
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
*/
	return nStatus;
	///////////////    
}

UINT CMSolMgr::DoModal_Solid_TensorNodeCount(int& nNodes_U,int& nNodes_V,int& nNodes_W)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Tensor Dlg_Tensor;
	///////////////////////////////////////		
	nStatus = Dlg_Tensor.DoModal();
	///////
	nNodes_U = Dlg_Tensor.m_nNode_U;		
	nNodes_V = Dlg_Tensor.m_nNode_V;		
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
*/
	return nStatus;
	///////////////    
}

UINT CMSolMgr::DoModal_Solid_TwistFactors(pDOUBLE pTwist,int nMaxTwist,double& dScale)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Torq Dlg_Torq;
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
*/
	return nStatus;
	///////////////    
}

UINT CMSolMgr::DoModal_Solid_RadiusFactors(pDOUBLE pRadius,int nMaxRadius,double& dScale)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Radius Dlg_Radius;
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

///////////////////////////////////////////////////////////////////////////
// CMSolMgr serialization

void CMSolMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MSolMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MSolMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


