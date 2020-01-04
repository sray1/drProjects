// MouseMgr.cpp : implementation file
//
#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "globals.h"
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "elglobal.h"
///////////////////// drawObjs
#include "DrDefine.h"
#include "DrLabel.h"
///////////////////// Dialogs
#include "dlg_Axis.h"
#include "dlg_Pipe.h"
/////////////////////
#include "VDlgDll.h"
////////////////////
#include "VDlgrsrc.h"
////////////////////
#include "VDlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionVDlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CVDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CVDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CVDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CVDlgMgr::CVDlgMgr()
{
}

CVDlgMgr::~CVDlgMgr()
{
}

HINSTANCE CVDlgMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionVDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CVDlgMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CVDlgMgr::DoModal_Node(BOOL bnid_C,int nViewNumber,
								LPOINT3* pMouseWIC,CString* pID,int nHowMany)
{

	////////////////////////////////////////////////////////////////////
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	/////////////////////////////////////////////////////////////
	CDlg_Node	NodVDlg;
	////////////////////
	NodVDlg.m_MouseWIC.x 		= pMouseWIC->x;
	NodVDlg.m_MouseWIC.y 		= pMouseWIC->y;
	NodVDlg.m_MouseWIC.z 		= pMouseWIC->z;
	NodVDlg.m_nActiveViewNumber	= nViewNumber;
	NodVDlg.m_bnid_c			= bnid_C;		
	NodVDlg.m_nHowMany			= nHowMany;		
	/////////////////////////////////////// Now Open Dialog/draw
	nStatus = NodVDlg.DoModal();
	/////////////////////////////////////// update	
	pMouseWIC->x = NodVDlg.m_MouseWIC.x;
	pMouseWIC->y = NodVDlg.m_MouseWIC.y;
	pMouseWIC->z = NodVDlg.m_MouseWIC.z;
	//////////////////////////////////
	*pID		 = NodVDlg.m_CurrentNodeID;
	////////////////////////////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////
}


// CVDlgMgr serialization

void CVDlgMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" VDlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" VDlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


