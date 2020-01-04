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
#include "dlg_SpnO.h"	// Obj3D Spawn
/////////////////////
#include "MO3DDll.h"
////////////////////
#include "MO3DRsrc.h"
////////////////////
#include "MO3DMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMO3D_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMO3DMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMO3DMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMO3DMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMO3DMgr::CMO3DMgr()
{
}

CMO3DMgr::~CMO3DMgr()
{
}

HINSTANCE CMO3DMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMO3D_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMO3DMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CMO3DMgr::DoModal_Spawn_O(CDrObj3D* pNewObj3D,CString* pID,CString& ParentCid)
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

CDrObj3D* CMO3DMgr::SpawnObj3D(CString& Cid,CString& ParentCid)
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

// CMO3DMgr serialization

void CMO3DMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MO3DMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MO3DMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


