// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

//#include "globals.h"
/////////////////////
#include "Def_Spec.h"
#include "dlg_HNet.h"
#include "dlg_Layr.h"
#include "dlg_Pen.h"
#include "dlg_Sfac.h"
#include "dlg_Prec.h"
#include "dlg_Unit.h"
#include "dlgObj3D.h"
#include "dlgPatch.h"
/////////////////////
#include "SDlgDll.h"
////////////////////
#include "SDlgrsrc.h"
////////////////////
#include "SDlgMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionSDlg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CSDlgMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CSDlgMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CSDlgMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CSDlgMgr::CSDlgMgr()
{
}

CSDlgMgr::~CSDlgMgr()
{
}

UINT CSDlgMgr::DoModal_SpecObjs(UINT nObjType)
{

	////////////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionSDlg_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	UINT nStatus;
	CDlg_HNet* 		pHitNet;
	CDrawLayer* 	pLayer;
	CPenDlg* 		pPen;
	CDrawScale* 	pScale;
	CDrawUnit* 		pUnit;
	CDrawPrecision* pPrec;
	CDlgObj3D* 		pDlgObj3D;
	CDlgPatch* 		pDlgPatch;
	//////////////////
	switch(nObjType)
	{
	
		case HITNET:
			pHitNet->OnHitNet();
			break;
	
		case LAYER:
			pLayer->OnLayer();
			break;
	
		case DRPEN:
			pPen->OnPen();
			break;
	
		case SCALEFACTOR:
			pScale->OnScalefactor();
			break;
	
		case UNIT:
			pUnit->OnUnit();
			break;
	
		case PRECISION:
			pPrec->OnPrecision();
			break;
	
		case PATCHMNU:
			pDlgPatch->OnPatchMnu();
			break;
	
		case OBJ3DMNU:
			pDlgObj3D->OnObj3DMnu();
			break;
	
		default:
			break;
	}	
			
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	///////////////
	return nStatus;
	///////////////    
}
 
// CSDlgMgr serialization

void CSDlgMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SDlgMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" SDlgMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


