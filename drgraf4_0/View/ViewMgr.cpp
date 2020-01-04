// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "drgraf.h"

#include "ViewDll.h"

#include "drgrafrm.h"
////////////////////
#include "curdef.h"
#include "ViewRsrc.h"
////////////////////
#include "ViewMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionView_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CViewMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CViewMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CViewMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CViewMgr::CViewMgr()
{
#ifdef _AFXDLL
	CString strRes;
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionView_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	m_hCross   		= AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_hUpArrow 		= AfxGetApp()->LoadStandardCursor(IDC_UPARROW);
	m_hDoubleArrow 	= AfxGetApp()->LoadStandardCursor(IDC_SIZE);
	m_hHand_12 		= AfxGetApp()->LoadCursor(IDC_CUR12);
	m_hHand_23 		= AfxGetApp()->LoadCursor(IDC_CUR23);
	m_hHand_31 		= AfxGetApp()->LoadCursor(IDC_CUR31);
	m_hHand_ISO		= AfxGetApp()->LoadCursor(IDC_CURISO);
	m_hText    		= AfxGetApp()->LoadCursor(IDC_CURTEXT);
	//////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

}

CViewMgr::~CViewMgr()
{
	DestroyCursor(m_hCross);
	DestroyCursor(m_hUpArrow);
	DestroyCursor(m_hDoubleArrow);
	DestroyCursor(m_hHand_12);
	DestroyCursor(m_hHand_23);
	DestroyCursor(m_hHand_31);
	DestroyCursor(m_hHand_ISO);
	DestroyCursor(m_hText);

}

void CViewMgr::InitDlgIn(UINT OperID)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	GetVuRotate()->SetProbLim(pWnd->GetProbDimLim());
	GetVuRotate()->SetElemLim(pWnd->GetElemDimLim());
	///////////////////////////////
	switch(OperID)
	{
		case VO_ROTATE:
			GetVuRotate()->InitDlgIn();
		default:
			break;
	}
	///////////////////////////////
}

UINT CViewMgr::ReSetToolID(UINT OperID)
{
	switch(OperID)
	{
		case VO_ROTATE:	
			return GetVuRotate()->ReSetToolID(OperID);

		default:
			return UNONE;
	}
}

UINT CViewMgr::CreateorActivateDlgIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case VO_ROTATE:	
			return GetVuRotate()->CreateorActivateDlgIn(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

UINT CViewMgr::UpdateDlgIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case VO_ROTATE:	
			return GetVuRotate()->UpdateDlgIn(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

UINT CViewMgr::CancelDlgIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case VO_ROTATE:	
			return GetVuRotate()->CancelDlgIn(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

UINT CViewMgr::GoodByeDlgIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case VO_ROTATE:	
			return GetVuRotate()->GoodByeDlgIn(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

LPOINT3 CViewMgr::GetStatusMouseWIC()
{
	return m_StatusMouseWIC;
}

void CViewMgr::SetStatusMouseWIC(LPOINT3 StatWIC)
{
	m_StatusMouseWIC.x = StatWIC.x;
	m_StatusMouseWIC.y = StatWIC.y;
	m_StatusMouseWIC.z = StatWIC.z;
}

void CViewMgr::SetViewCursor(int nType)
{
	///////////////////////////////////////////// If helpMode, no-op
	if(AfxGetApp()->m_bHelpMode)
		return;
	///////////////////////////////////////////// Cursor
	UINT uType = (UINT)nType;
	/////////////////////////
	switch(uType)
	{
	
		case CROSS :
			::SetCursor(m_hCross);
			return;
			
		case DOUBLEARROW :
			::SetCursor(m_hDoubleArrow);
			return;
			
		case UPARROW :
			::SetCursor(m_hUpArrow);
			return;
			
		case HAND_12 :
			::SetCursor(m_hHand_12);
			return;
			
		case HAND_23 :
			::SetCursor(m_hHand_23);
			return;
			
		case HAND_31 :
			::SetCursor(m_hHand_31);
			return;
			
		case HAND_ISO:
			::SetCursor(m_hHand_ISO);
			return;
			
		case HAND_TEXT :
			::SetCursor(m_hText);
			return;
			
		default :
			break;
			
	}
    ////////////////////////////////////       
    return;
           
}		
 
// CViewMgr serialization

void CViewMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ViewMgr	:Storing\n");	// TODO: add storing code here 
		ar.Write(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));

	}
	else
	{
		TRACE(" ViewMgr	:Loading\n");	// TODO: add loading code here
		ar.Read(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));
	}
	////////////////////////////////////////////// Mouse
//	GetSolCreOp()->Serialize(ar);
	/////////////
	
}
////////////////////// End of Module ////////////////////


