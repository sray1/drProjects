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
//#include "dlg_SPos.h"
/////////////////////
#include "MMs3Dll.h"
////////////////////
#include "MMs3Rsrc.h"
////////////////////
#include "MMs3Mgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMMs3_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMMs3Mgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMMs3Mgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMMs3Mgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMMs3Mgr::CMMs3Mgr()
{
}

CMMs3Mgr::~CMMs3Mgr()
{
}

HINSTANCE CMMs3Mgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMMs3_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMMs3Mgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT CMMs3Mgr::DoModal_Solid_Post(CString* pID)
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

// CMMs3Mgr serialization

void CMMs3Mgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MMs3Mgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MMs3Mgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


