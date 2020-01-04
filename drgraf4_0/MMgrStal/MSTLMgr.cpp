// MouseMgr.cpp : implementation file
//
#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "Def_StaL.h"
///////////////////// StaticLoad Dlgs
#include "dlg_IsoP.h"
#include "dlg_Many.h"
/////////////////////
#include "MSTLDll.h"
////////////////////
#include "MSTLRsrc.h"
////////////////////
#include "MSTLMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMStLMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMStLMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMStLMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////
CMStLMgr::CMStLMgr()
{
}

CMStLMgr::~CMStLMgr()
{
}

HINSTANCE CMStLMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMStL_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMStLMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT CMStLMgr::DoModal_Patch_Post(CString* pID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_PPost PPostDlg;
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
UINT CMStLMgr::DoModal_Value_In(CString& heading,pDOUBLE pValue,int nCompo,STALPROC StaLProc)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_IsoP Dlg;
	////////////////////////
	Dlg.m_nCompo	= nCompo;
	Dlg.m_Heading	= heading;
	Dlg.m_StaLProc	= StaLProc;
	////////////////////////
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pValue		 = Dlg.m_dStart;
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CMStLMgr::DoModal_ManyValue_In(CString& Nid, pDOUBLE dValu,BOOL* bKode,STALPROC StaLProc)
{
	HINSTANCE hInstResourceClient =	SetResource();
	UINT nStatus;
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Many Dlg;
	////////////////////////
	Dlg.Nid			= Nid;
	for(int i=0;i<6;i++)
		Dlg.dValu[i]= dValu[i];
	Dlg.bKode		= bKode;
	Dlg.m_StaLProc	= StaLProc;
	////////////////////////
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update
	if(nStatus == IDOK)
	{
		for(int i=0;i<6;i++)
			dValu[i]= Dlg.dValu[i];
	}
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

// CMStLMgr serialization

void CMStLMgr::Serialize(CArchive& ar)
{
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MStLMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" MStLMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


