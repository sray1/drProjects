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
#include "Def_Elem.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
/////////////////////
#include "CreMDll.h"
////////////////////
#include "CMgrRsrc.h"
#include "Mlg_RotT.h"
#include "Mlg_LSyT.h"
#include "Mlg_SpnN.h"
#include "Mlg_SpnC.h"	// Curve Spawn
#include "Mlg_SpnP.h"	// Patch Spawn
#include "Mlg_SpnS.h"	// Solid Spawn
#include "Mlg_SpnO.h"	// Obj3D Spawn
//#include "dlg_SPos.h"
//#include "Dlg_ENod.h"
//#include "dlg_PPos.h"
////////////////////
#include "CreMDlgM.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionCreM_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CCreMDlgM,CObject,1)
/*
BEGIN_MESSAGE_MAP(CCreMDlgM,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCreMDlgM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CCreMDlgM::CCreMDlgM()
{
}

CCreMDlgM::~CCreMDlgM()
{
}

HINSTANCE CCreMDlgM::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionCreM_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CCreMDlgM::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT  CCreMDlgM::DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_ENod Dlg;
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
UINT CCreMDlgM::DoModal_RotationType(SPAWNTYPE& SpnType)	// in IGen.h
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_ROTT Dlg;
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
 
UINT CCreMDlgM::DoModal_SymmetryType(SPAWNTYPE& SpnType)	// in IGen.h
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_LSyT Dlg;
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
 
UINT CCreMDlgM::DoModal_Spawn_N(CDrFE0D* pDrNode,CDrFE0D* pParentNode,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_SpnN Dlg;
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
 
UINT CCreMDlgM::DoModal_Spawn_C(CDrMesh1D* pNewCurve,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_SpnC Dlg;
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

CDrMesh1D* CCreMDlgM::SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnC	Dlg_SpnC;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrMesh1D* pAdd 	= (CDrMesh1D*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	////////////////////////////////////
	Dlg_SpnC.m_SpawnID		= Cid;
	Dlg_SpnC.m_bInstanced 	= FALSE;
	Dlg_SpnC.m_CID		 	= ParentCid;
	Dlg_SpnC.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnC.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
//	pAdd->SetCurveType_S(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}

UINT CCreMDlgM::DoModal_Spawn_P(CDrMesh2D* pNewPatch,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_SpnP Dlg;
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

CDrMesh2D* CCreMDlgM::SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnP	Dlg_SpnP;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrMesh2D* pAdd 	= (CDrMesh2D*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
	////////////////////////////////////
	Dlg_SpnP.m_SpawnID		= Cid;
	Dlg_SpnP.m_bInstanced 	= FALSE;
	Dlg_SpnP.m_CID		 	= ParentCid;
	Dlg_SpnP.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnP.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
//	pAdd->SetPatchProc(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
 
UINT CCreMDlgM::DoModal_Spawn_S(CDrMesh3D* pNewSolid,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_SpnS Dlg;
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

CDrMesh3D* CCreMDlgM::SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnS	Dlg_SpnS;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrMesh3D* pAdd 	= (CDrMesh3D*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
	////////////////////////////////////
	Dlg_SpnS.m_SpawnID		= Cid;
	Dlg_SpnS.m_bInstanced 	= FALSE;
	Dlg_SpnS.m_CID		 	= ParentCid;
	Dlg_SpnS.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnS.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
//	pAdd->SetSolidProc(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}

UINT CCreMDlgM::DoModal_Spawn_O(CDrMbj3D* pNewObj3D,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_SpnO Dlg;
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

CDrMbj3D* CCreMDlgM::SpawnObj3D(CString& Cid,CString& ParentCid)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnO	Dlg_SpnO;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrMbj3D* pAdd 	= (CDrMbj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,OBJ3D));
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
 
// CCreMDlgM serialization

void CCreMDlgM::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CreMDlgM	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" CreMDlgM	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


