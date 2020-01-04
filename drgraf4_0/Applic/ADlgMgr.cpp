// MouseMgr.cpp : implementation file
//
#include "stdafx.h"
////////////////////
#include "drgrafrm.h"
///////////////////// Dlg
#include "Dlg_CTim.h"
/////////////////////
#include "ADlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CAppDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CAppDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CAppDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CAppDlgMgr::CAppDlgMgr()
{
}

CAppDlgMgr::~CAppDlgMgr()
{
}

HINSTANCE CAppDlgMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(hInstResourceClient); // uses Application's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CAppDlgMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

int CAppDlgMgr::DebugList_AddString(CString& strList)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	if(!pWnd->IsDebugCTim())
		return -1;
	/////////////////////////////////////////////////////////
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now GetDlg
	CDlg_CTim* pDlg = pWnd->GetDlg_CTim();
	int bReturn;
	/////////////////////////////////////// Set Item
	CListBox* pList = (CListBox*)(pDlg->GetDlgItem(IDC_LIST));
	bReturn = pList->AddString(strList);
	///////////////    
	return bReturn;
}
// CAppDlgMgr serialization

void CAppDlgMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" AppDlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" AppDlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


