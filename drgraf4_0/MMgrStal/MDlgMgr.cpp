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
//#include "Glb_Elem.h"
//#include "Glb_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// Curve
#include "dlg_CClk.h"	// Curve Advance Click In
#include "dlg_CrcT.h"	// Circle Type
///////////////////// Patch
///////////////////// Solid
/////////////////////
#include "MDlgDll.h"
////////////////////
#include "MDlgrsrc.h"
////////////////////
#include "MDlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMDlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMDlgMgr::CMDlgMgr()
{
}

CMDlgMgr::~CMDlgMgr()
{
}

HINSTANCE CMDlgMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMDlgMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}

UINT CMDlgMgr::DoModal_Cur_Advance_In(CDrCurve* pDrCurve,int nOrder)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CClk Dlg;
	UINT nStatus;
	Dlg.m_pDrCurve	= pDrCurve;
	Dlg.m_nOrder	= nOrder;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMDlgMgr::DoModal_CIRCLE_Type(CIRCLETYPE& nType)
{
	HINSTANCE hInstResourceClient =	SetResource();
	/////////////////////////////////////////////////////// Find Input Type
	CDlg_CrcT Dlg;
	UINT nStatus;
	///////////////////////////////////////
	Dlg.m_nType = CIRCLE_BY_NO3;
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	nType	= Dlg.m_nType;
	//////////////////////
/*
	if(nType == 1)
	{
		////////////////////////////////// Now Open Dialog/draw
		CDlg_CIRC Dlg;
		Dlg.m_nHowMany			= nHowMany;		
		///////////////////////////////////////		
		nStatus = Dlg.DoModal();
		/////////////////////////////////////// Update     
		*pID	= Dlg.m_CurveID;
	}
	else
	if(nType == 2)
	{
		////////////////////////////////// Now Open Dialog/draw
		CDlg_CRC2 Dlg;
		Dlg.m_nHowMany			= nHowMany;		
		///////////////////////////////////////		
		nStatus = Dlg.DoModal();
		/////////////////////////////////////// Update     
		*pID	= Dlg.m_CurveID;
	}
*/
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
// CMDlgMgr serialization

void CMDlgMgr::Serialize(CArchive& ar)
{
	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" EDlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" EDlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


