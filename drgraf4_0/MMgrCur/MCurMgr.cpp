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
#include "Def_CuPS.h"
///////////////////// drawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// Curve
#include "dlg_CClk.h"	// Curve Advance Click In
#include "dlg_CrcT.h"	// Circle Type
/////////////////////
//#include "dlg_Cirr.h"	// Curve general
//#include "dlg_CIRC.h"	// Circle Interpolate 	NURB   Rightbutton
//#include "dlg_CRC2.h"	// Circle Interpolate 	NURB   Rightbutton
//#include "dlg_CrcT.h"	// Circle Type 			NURB   Rightbutton
#include "dlg_cpro.h"	// Curve Profile
#include "Dlg_CPSI.h"	// Curve Profile Show Info
//#include "dlg_SpnC.h"	// Curve Spawn
/////////////////////
#include "MCurDll.h"
////////////////////
#include "MCurRsrc.h"
////////////////////
#include "MCurMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMCur_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMCurMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMCurMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMCurMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMCurMgr::CMCurMgr()
{
}

CMCurMgr::~CMCurMgr()
{
}

HINSTANCE CMCurMgr::SetResource()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMCur_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	return hInstResourceClient;  
#endif
 
}

void CMCurMgr::RestoreResource(HINSTANCE hInstResourceClient)
{
 	
#ifdef _AFXDLL
	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
 
}
/*

//	Moved to EditMgr Dll   01/14/98 

UINT CMCurMgr::DoModal_ShowCurveToEdit(CDrCurve* pDrCurve)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	UINT nStatus;
	///////////////////////////////////////		
//	nStatus = Dlg.DoModal();
	nStatus = IDCANCEL;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
//	Moved to EditMgr Dll   01/14/98 end 
*/

UINT CMCurMgr::DoModal_Cur_Advance_In(CDrCurve* pDrCurve,int nOrder)
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
 
UINT CMCurMgr::DoModal_CIRCLE_Type(CIRCLETYPE& nType)
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

UINT CMCurMgr::DoModal_Cur_I_LB(CString* pID,int nHowMany)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CIRR Dlg;
	Dlg.m_nHowMany			= nHowMany;
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_CurveID;
	////////////////////////////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
*/	
	return nStatus;
	/////////////// 
}
 
UINT CMCurMgr::DoModal_Cur_I_RB(CString* pID,int nHowMany)
{
	UINT nStatus;
/*
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CIRR Dlg;
	Dlg.m_nOrder			= nHowMany;	// THIS IS ACTUALLY USED AS m_nOrder		
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_CurveID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
*/	
	return nStatus;
	///////////////
}
 
UINT CMCurMgr::DoModal_Cur_I_CIRCLE(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	/////////////////////////////////////////////////////// Find Input Type
	CDlg_CrcT Dlg;
	UINT nStatus;
	///////////////////////////////////////
	Dlg.m_nType = CIRCLE_BY_NO3;
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	int nType	= Dlg.m_nType;
/*
	//////////////////////
	if(nType == CIRCLE_BY_NO3)
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
	if(nType == CIRCLE_BY_ROT)
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
 
UINT CMCurMgr::DoModal_Profile_C(CString* pID,int nHowMany)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CPro Dlg;
	UINT nStatus;
	Dlg.m_nHowMany			= nHowMany;		
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_CPro_ID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}
 
UINT CMCurMgr::DoModal_Profile_C_ShowInfo(CString* pID,CDListMgr* pCurveList)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_CPSI Dlg;
	UINT nStatus;
	Dlg.m_pCurveList	= pCurveList;		
	///////////////////////////////////////		
	nStatus = Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		 = Dlg.m_CPro_ID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

/*
//	Moved to CreOMgr Dll   01/14/98 
 
UINT CMCurMgr::DoModal_Spawn_C(CDrCurve* pNewCurve,CString* pID,CString* pParentID)
{
	HINSTANCE hInstResourceClient =	SetResource();
	////////////////////////////////// Now Open Dialog/draw
	CDlg_SpnC Dlg;
	UINT nStatus;
	/////////////////////////////////////// Set Data
	Dlg.m_pDrCurve	= pNewCurve;
	Dlg.m_CID		= *pParentID;
	Dlg.m_SpawnID	= pNewCurve->GetObjectID();			// NewID
	///////////////////////////////////////		
	nStatus		= Dlg.DoModal();
	/////////////////////////////////////// Update     
	*pID		= Dlg.m_SpawnID;
	/////////////////////////////////////// 
	RestoreResource(hInstResourceClient);
	///////////////
	return nStatus;
	///////////////    
}

CDrCurve* CMCurMgr::SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp)
{

	HINSTANCE hInstResourceClient =	SetResource();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnC	Dlg_SpnC;		
	/////////////////////////////////////////////////////////////////////////// Add
	int nActiveIndex;
    CDrCurve* pAdd 	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	////////////////////////////////////
	Dlg_SpnC.m_SpawnID		= Cid;
	Dlg_SpnC.m_bInstanced 	= FALSE;
	Dlg_SpnC.m_CID		 	= ParentCid;
	Dlg_SpnC.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnC.SetInfoForDataBase(pAdd);
	/////////////////////////////////////// Override
	pAdd->SetCurveType_S(cp);
	CString bla = "";
	pAdd->SetParentID(bla);	
	//////////////////////////////////////////////
	RestoreResource(hInstResourceClient);
	///////////////
    return pAdd;
}
//	Moved to CreOMgr Dll   01/14/98 end 
*/
// CMCurMgr serialization

void CMCurMgr::Serialize(CArchive& ar)
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


