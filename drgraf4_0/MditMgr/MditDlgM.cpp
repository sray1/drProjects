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
#include "MditDll.h"
////////////////////
#include "MditRsrc.h"
#include "Mlg_ENod.h"
////////////////////
#include "MditDlgM.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionMdit_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMditDlgM,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMditDlgM,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMditDlgM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMditDlgM::CMditDlgM()
{
}

CMditDlgM::~CMditDlgM()
{
}

HINSTANCE CMditDlgM::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMdit_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMditDlgM::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT  CMditDlgM::DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CMlg_ENod Dlg;
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

UINT  CMditDlgM::DoModal_ShowCurveToEdit(CDrMesh1D* pDrCurve, int nViewNumber)
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

UINT  CMditDlgM::DoModal_ShowPatchToEdit(CDrMesh2D* pDrPatch, int nViewNumber)
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

UINT  CMditDlgM::DoModal_ShowSolidToEdit(CDrMesh3D* pDrSolid, int nViewNumber)
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
// CMditDlgM serialization

void CMditDlgM::Serialize(CArchive& ar)
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


