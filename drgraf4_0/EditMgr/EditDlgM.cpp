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
#include "Def_IGen.h"
//#include "Glb_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
/////////////////////
#include "EMgrDll.h"
////////////////////
#include "EMgrRsrc.h"
#include "Dlg_ENod.h"
////////////////////
#include "EditDlgM.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionEMgr_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CEditDlgM,CObject,1)
/*
BEGIN_MESSAGE_MAP(CEditDlgM,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CEditDlgM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CEditDlgM::CEditDlgM()
{
}

CEditDlgM::~CEditDlgM()
{
}

HINSTANCE CEditDlgM::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEMgr_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CEditDlgM::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT  CEditDlgM::DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_ENod Dlg;
	Dlg.m_pDrNode			= pDrNode;
	Dlg.m_nActiveViewNumber	= nViewNumber;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT  CEditDlgM::DoModal_ShowCurveToEdit(CDrCurve* pDrCurve, int nViewNumber)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
/*todo
	////////////////////////////////// Now Open Dialog/draw
	CDlg_ECur Dlg;
	Dlg.m_pDrCurve			= pDrCurve;
	Dlg.m_nActiveViewNumber	= nViewNumber;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
*/
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT  CEditDlgM::DoModal_ShowPatchToEdit(CDrPatch* pDrPatch, int nViewNumber)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
/*todo
	////////////////////////////////// Now Open Dialog/draw
	CDlg_EPat Dlg;
	Dlg.m_pDrPatch			= pDrPatch;
	Dlg.m_nActiveViewNumber	= nViewNumber;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
*/
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT  CEditDlgM::DoModal_ShowSolidToEdit(CDrSolid* pDrSolid, int nViewNumber)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
/*todo
	CDlg_ESol Dlg;
	Dlg.m_pDrSolid			= pDrSolid;
	Dlg.m_nActiveViewNumber	= nViewNumber;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
*/
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
// CEditDlgM serialization

void CEditDlgM::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" EditDlgM	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" EditDlgM	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


