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
#include "DrFE0D.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
/////////////////////
#include "MMs0Dll.h"
////////////////////
#include "MMs0Rsrc.h"
//#include "Dlg_LSyT.h"
//#include "Dlg_Spn0.h"
#include "Dlg_ENod.h"
////////////////////
#include "MMs0Mgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMMs0_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMMs0Mgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMMs0Mgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMMs0Mgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMMs0Mgr::CMMs0Mgr()
{
}

CMMs0Mgr::~CMMs0Mgr()
{
}

HINSTANCE CMMs0Mgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMMs0_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMMs0Mgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT  CMMs0Mgr::DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber)
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
/* 
UINT CMMs0Mgr::DoModal_SymmetryType(SPAWNTYPE& SpnType)	// in IGen.h
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
 
UINT CMMs0Mgr::DoModal_Spawn_N(CDrFE0D* pDrNode,CDrFE0D* pParentNode,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Spn0 Dlg;
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
*/ 
// CMMs0Mgr serialization

void CMMs0Mgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MMs0Mgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MMs0Mgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


