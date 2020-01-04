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
///////////////////// Mesh1D
//#include "dlg_Spn1.h"	// Mesh1D Spawn
#include "dlg_1Mrg.h"	// Mesh1D Merge
/////////////////////
#include "MMs1Dll.h"
////////////////////
#include "MMs1Rsrc.h"
////////////////////
#include "MMs1Mgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMMs1_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMMs1Mgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMMs1Mgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMMs1Mgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMMs1Mgr::CMMs1Mgr()
{
}

CMMs1Mgr::~CMMs1Mgr()
{
}

HINSTANCE CMMs1Mgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMMs1_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMMs1Mgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CMMs1Mgr::DoModal_ShowMesh1DToEdit(CDrMesh1D* pDrMesh1D)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	UINT nStatus;
	///////////////////////////////////////		
//	nStatus = Dlg.DoModal();
	nStatus = IDCANCEL;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMMs1Mgr::DoModal_Merge_1_ShowInfo(CString* pID,CDListMgr* pMesh1DList)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_1Mrg Dlg;
	UINT nStatus;
	Dlg.m_pMesh1DList	= pMesh1DList;		
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
UINT CMMs1Mgr::DoModal_Spawn_1(CDrMesh1D* pNewMesh1D,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Spn1 Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_pDrMesh1D	= pNewMesh1D;
	Dlg.m_CID		= *pParentID;
	Dlg.m_SpawnID	= pNewMesh1D->GetObjectID();			// NewID
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

CDrMesh1D* CMMs1Mgr::SpawnMesh1D(CString& Cid,CString& ParentCid, CURVEPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_Spn1	Dlg_SpnC;		
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
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
*/
// CMMs1Mgr serialization

void CMMs1Mgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MMs1Mgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MMs1Mgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


