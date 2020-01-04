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
#include "glb_Elem.h"
//#include "Glb_Pat.h"
//#include "Def_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// Mesh2D
//#include "dlg_Spn2.h"	// Mesh2D Spawn
#include "dlg_2Mrg.h"	// Mesh2D Merge
/////////////////////
#include "MMs2Dll.h"
////////////////////
#include "MMs2Rsrc.h"
////////////////////
#include "MMs2Mgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMMs2_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMMs2Mgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMMs2Mgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMMs2Mgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMMs2Mgr::CMMs2Mgr()
{
}

CMMs2Mgr::~CMMs2Mgr()
{
}

HINSTANCE CMMs2Mgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMMs2_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMMs2Mgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CMMs2Mgr::DoModal_Merge_2_ShowInfo(CString* pID,CDListMgr* pMesh2DList)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_2Mrg Dlg;
	UINT nStatus;
	Dlg.m_pMesh2DList	= pMesh2DList;		
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_CPro_ID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
}
/*
UINT CMMs2Mgr::DoModal_Spawn_2(CDrMesh2D* pNewMesh2D,CString* pID,CString& ParentCid)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Spn2 Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Item
	Dlg.m_pDrMesh2D	= pNewMesh2D;
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

CDrMesh2D* CMMs2Mgr::SpawnMesh2D(CString& Cid,CString& ParentCid)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_Spn2	Dlg_SpnP;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrMesh2D* pAdd 	= (CDrMesh2D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH2D));
	////////////////////////////////////
	Dlg_SpnP.m_SpawnID		= Cid;
	Dlg_SpnP.m_bInstanced 	= FALSE;
	Dlg_SpnP.m_CID		 	= ParentCid;
	Dlg_SpnP.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnP.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
*/
// CMMs2Mgr serialization

void CMMs2Mgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MMs2Mgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MMs2Mgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


