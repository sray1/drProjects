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
///////////////////// DrLinSup Edit Dlgs
#include "DrLinSup.h"
#include "Dlg_JointCoord.h"
#include "dlg_SupE.h"
/////////////////////
#include "MSupDll.h"
////////////////////
#include "MSupRsrc.h"
////////////////////
#include "MSupMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSup_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMSupMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMSupMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMSupMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMSupMgr::CMSupMgr()
{
}

CMSupMgr::~CMSupMgr()
{
}

HINSTANCE CMSupMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMSup_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMSupMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CMSupMgr::DoModal_Sup_JCType(JOINTCOORD& jcType)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_JointCoord Dlg_JC;
	nStatus = Dlg_JC.DoModal();
	if(nStatus == IDOK)
		jcType = Dlg_JC.m_jcType;
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMSupMgr::DoModal_SupToEdit(CDrLinSup* pSup)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SupE Dlg_SupE(pSup);
	nStatus = Dlg_SupE.DoModal();
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}


// CMSupMgr serialization

void CMSupMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MSupMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MSupMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


