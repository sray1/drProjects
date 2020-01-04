// MouseMgr.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Dialogs
//#include "dlg_Pipe.h"
//#include "dlg_Plat.h"
//#include "dlg_FE1D.h"
//#include "dlg_FE2D.h"
////////////////////
#include "EDlgRsrc.h"
#include "EDlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionEDlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CEDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CEDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CEDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CEDlgMgr::CEDlgMgr()
{
}

CEDlgMgr::~CEDlgMgr()
{
}

HINSTANCE CEDlgMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CEDlgMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*
UINT CEDlgMgr::DoModal_Pipe(CDrPipe* pPipe)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_Pipe PipeDlg;
	PipeDlg.m_pDrPipe	= pPipe;		
	nStatus = PipeDlg.DoModal();
	//////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

UINT CEDlgMgr::DoModal_Qu_4(CDr_Qu_4* pQu_4)
{
	UINT nStatus;
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CString strPlateType[4] = {"Membrane","Axi-Sym","Pl.Stress","Pl.Strain"};
	CDlg_Plat Dlg_Plat;
	Dlg_Plat.m_nHowMany			= nHowMany;		
	Dlg_Plat.m_PlateType = strPlateType[nPlatTypeIndex];
	///////////////////////////////
	nStatus = Dlg_Plat.DoModal();
	///////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
*/

// CEDlgMgr serialization

void CEDlgMgr::Serialize(CArchive& ar)
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


