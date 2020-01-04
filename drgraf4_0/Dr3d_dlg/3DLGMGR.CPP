// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "globals.h"
/////////////////////
#include "dlg_EyeP.h"
/////////////////////
#include "3DlgDll.h"
////////////////////
#include "3Dlgrsrc.h"
////////////////////
#include "3DlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extension3Dlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(C3DlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(C3DlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(C3DlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
C3DlgMgr::C3DlgMgr()
{
}

C3DlgMgr::~C3DlgMgr()
{
}

UINT C3DlgMgr::DoModal_EyePosition()
{

	////////////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extension3Dlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	UINT nStatus;
//	CInTextDlg		TextInsertDlg;
//	nStatus = TextInsertDlg.DoModal();
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif 

	///////////////
	return nStatus;
	///////////////
}

 
// C3DlgMgr serialization

void C3DlgMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" 3DlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" 3DlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


