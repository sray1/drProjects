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
#include "MNodDll.h"
////////////////////
#include "MNodRsrc.h"
//#include "Dlg_LSyT.h"
//#include "Dlg_SpnN.h"
//#include "Dlg_ENod.h"
////////////////////
#include "MNodMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMNod_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMNodMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMNodMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMNodMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMNodMgr::CMNodMgr()
{
}

CMNodMgr::~CMNodMgr()
{
}

HINSTANCE CMNodMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMNod_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMNodMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
//	Moved to EditMgr Dll   01/14/98 

UINT  CMNodMgr::DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber)
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

//	Moved to CreOMgr Dll   01/14/98 
UINT CMNodMgr::DoModal_SymmetryType(SPAWNTYPE& SpnType)	// in IGen.h
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
 
UINT CMNodMgr::DoModal_Spawn_N(CDrNode* pDrNode,CDrNode* pParentNode,CString* pID,CString* pParentID)
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
//	Moved to CreOMgr Dll   01/14/98 end 
*/ 
// CMNodMgr serialization

void CMNodMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MNodMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MNodMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


