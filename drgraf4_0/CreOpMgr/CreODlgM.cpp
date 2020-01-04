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
#include "Def_IGen.h"
//#include "Glb_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
/////////////////////
#include "CMgrDll.h"
////////////////////
#include "CMgrRsrc.h"
#include "Dlg_RotT.h"
#include "Dlg_LSyT.h"
#include "Dlg_SpnN.h"
#include "dlg_SpnC.h"	// Curve Spawn
#include "dlg_SpnP.h"	// Patch Spawn
#include "dlg_SpnS.h"	// Solid Spawn
#include "dlg_SpnO.h"	// Obj3D Spawn
//#include "dlg_SPos.h"
//#include "Dlg_ENod.h"
//#include "dlg_PPos.h"
////////////////////
#include "CreODlgM.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionCMgr_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CCreODlgM,CObject,1)
/*
BEGIN_MESSAGE_MAP(CCreODlgM,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCreODlgM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CCreODlgM::CCreODlgM()
{
}

CCreODlgM::~CCreODlgM()
{
}

HINSTANCE CCreODlgM::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionCMgr_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CCreODlgM::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT  CCreODlgM::DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_ENod Dlg;
	UINT nStatus;
	Dlg.m_pDrNode			= pDrNode;
	Dlg.m_nActiveViewNumber	= nViewNumber;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
*/ 
UINT CCreODlgM::DoModal_RotationType(SPAWNTYPE& SpnType)	// in IGen.h
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_ROTT Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_bType_1	= TRUE;		//
	Dlg.m_nType		= 1;		//
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update 
    if(Dlg.m_nType == 1)
		SpnType		 = SPN_ROT_ABT_LINE;
	else
    if(Dlg.m_nType == 2)
		SpnType		 = SPN_ROT_REF_2_TAR;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CCreODlgM::DoModal_SymmetryType(SPAWNTYPE& SpnType)	// in IGen.h
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_LSyT Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_bType_1	= TRUE;		//
	Dlg.m_nType		= 1;		//
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update 
    if(Dlg.m_nType == 1)
		SpnType		 = SPN_SYMM_N;
	else
    if(Dlg.m_nType == 2)
		SpnType		 = SPN_SYMM_3;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CCreODlgM::DoModal_Spawn_N(CDrNode* pDrNode,CDrNode* pParentNode,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnN Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_pDrNode	= pDrNode;
	Dlg.m_pParent 	= pParentNode;	// OldNode
	Dlg.m_CID		= *pParentID;
	Dlg.m_SpawnID	= *pID;			// NewID
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
 
UINT CCreODlgM::DoModal_Spawn_C(CDrCurve* pNewCurve,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnC Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_pDrCurve	= pNewCurve;
	Dlg.m_CID		= *pParentID;
	Dlg.m_SpawnID	= pNewCurve->GetObjectID();			// NewID
	///////////////////////////////////////		
	nStatus		= Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		= Dlg.m_SpawnID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

CDrCurve* CCreODlgM::SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnC	Dlg_SpnC;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrCurve* pAdd 	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	////////////////////////////////////
	Dlg_SpnC.m_SpawnID		= Cid;
	Dlg_SpnC.m_bInstanced 	= FALSE;
	Dlg_SpnC.m_CID		 	= ParentCid;
	Dlg_SpnC.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnC.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	pAdd->SetCurveType_S(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}

UINT CCreODlgM::DoModal_Spawn_P(CDrPatch* pNewPatch,CString* pID,CString& ParentCid)
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

CDrPatch* CCreODlgM::SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp)
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
 
UINT CCreODlgM::DoModal_Spawn_S(CDrSolid* pNewSolid,CString* pID,CString& ParentCid)
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

CDrSolid* CCreODlgM::SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp)
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

UINT CCreODlgM::DoModal_Spawn_O(CDrObj3D* pNewObj3D,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnO Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Item
	Dlg.m_pDrObj3D	= pNewObj3D;
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

CDrObj3D* CCreODlgM::SpawnObj3D(CString& Cid,CString& ParentCid)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnO	Dlg_SpnO;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrObj3D* pAdd 	= (CDrObj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,OBJ3D));
	////////////////////////////////////
	Dlg_SpnO.m_SpawnID		= Cid;
	Dlg_SpnO.m_bInstanced 	= FALSE;
	Dlg_SpnO.m_CID		 	= ParentCid;
	Dlg_SpnO.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnO.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
 
// CCreODlgM serialization

void CCreODlgM::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CreODlgM	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" CreODlgM	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


