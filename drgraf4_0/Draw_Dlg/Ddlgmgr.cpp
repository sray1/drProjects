// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "Def_Objs.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Draw.h"
#include "dlg_iLab.h"
#include "dlg_eLab.h"
#include "dlg_Grid.h"
/////////////////////
#include "DDlgDll.h"
////////////////////
#include "DDlgrsrc.h"
////////////////////
#include "DDlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionDDlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CDDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CDDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CDDlgMgr::CDDlgMgr()
{
}

CDDlgMgr::~CDDlgMgr()
{
}

UINT CDDlgMgr::DoModal_Label_Insert(int nView, POINT point)
{

	////////////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	UINT nStatus;
	///////////////////////////////
	CInTextDlg		TextInsertDlg;
	
	TextInsertDlg.m_nActiveViewNumber	= nView;
	TextInsertDlg.m_pt					= point;
	
	nStatus = TextInsertDlg.DoModal();
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif 

	///////////////
	return nStatus;
	///////////////
}

UINT CDDlgMgr::DoModal_Label_Edit(int index)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
	/////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	////////////////////////////////// Now Open Dialog/draw
	CEditLabel 	LabelEditDlg;
	/////////////////////////
   	CDrLabel* pLabel = 
   			(CDrLabel*)pDListMgr->GetObject(index);
   	 
	LabelEditDlg.m_EditedLabel = pLabel->GetText();
	LabelEditDlg.m_nLabelIndex = index;
	LabelEditDlg.m_OldLabel    = LabelEditDlg.m_EditedLabel;
	UINT nStatus;
	nStatus = LabelEditDlg.DoModal();
	//////////////////////////////////
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	///////////////
	return nStatus;
	///////////////    
}

UINT CDDlgMgr::DoModal_Grid_Insert()
{

	////////////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	UINT nStatus;
	///////////////////////////////
	CDlg_Grid		DlgGrid;
	
	nStatus = DlgGrid.DoModal();
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif 

	///////////////
	return nStatus;
	///////////////
}

// CDDlgMgr serialization

void CDDlgMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DDlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" DDlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


