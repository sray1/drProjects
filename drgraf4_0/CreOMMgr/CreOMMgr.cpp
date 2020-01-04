// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "CreMDll.h"

#include "drgrafrm.h"
////////////////////
#include "Def_Elem.h"
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_Supp.h"
#include "Def_StaL.h"
#include "Def_SpeL.h"
#include "Def_DynL.h"
////////////////////
#include "curdef.h"
#include "MMgrRsrc.h"	// for Cursors
////////////////////
#include "CreOMMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionCreM_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CCreOMMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CCreOMMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCreOMMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CCreOMMgr::CCreOMMgr()
{
#ifdef _AFXDLL
	CString strRes;
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionCreM_DLL.hModule); // uses client's instance handle 
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

CCreOMMgr::~CCreOMMgr()
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

void CCreOMMgr::InitDlgIn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	GetSolCreOp()->SetProbLim(pWnd->GetProbDimLim());
	GetSolCreOp()->SetElemLim(pWnd->GetElemDimLim());
	///////////////////////////////
	GetSolCreOp()->InitDlgIn();
	///////////////////////////////
}

UINT CCreOMMgr::ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID)
{
	switch(CntlID)
	{
		//////////////////////////////////////// IGEN
		case ELEMENT:
		case EDIM_0:
		case EDIM_1:
		case EDIM_2:
		case EDIM_3:

		{
			switch(IGenID)
			{
				case MESH0D:	
				case FE0D:	
				case MCNODE:	
				case MNODE:	
					return GetSolCreOp()->ReSetToolID_NOD(CntlID,IGenID,OperID);

				case MESH1D:
					return GetSolCreOp()->ReSetToolID_CUR(CntlID,IGenID,OperID);

				case MESH2D:
					return GetSolCreOp()->ReSetToolID_PAT(CntlID,IGenID,OperID);

				case MESH3D:
//					return GetSolCreOp()->ReSetToolID_SOL(CntlID,IGenID,OperID);

				case MBJ3D:
//					return GetSolCreOp()->ReSetToolID_O3D(CntlID,IGenID,OperID);
				default:
					return UNONE;
			}
		}
		//////////////////////////////////////// Support
		case SUPPORT:
		case SUPPORT_RIGID:
		case SUPPORT_LINSPRING:
		case SUPPORT_LINSNUBBER:
		case SUPPORT_NLSPRING:
		case SUPPORT_NLSNUBBER:

//			return GetSupCreOp()->ReSetToolID_SUP(CntlID,IGenID,OperID);
		//////////////////////////////////////// StaticLoad
		case STATICLOAD:
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
			
//			return GetSLDCreOp()->ReSetToolID_SLD(CntlID,IGenID,OperID);


		default:

			return (UINT)NONE;

		//	GetDLDCreOp()->InitDlgIn();
		//	GetSPLMouse()->InitDlgIn();
	}
}

UINT CCreOMMgr::CreateorActivateCreIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case MESH0D:	
		case FE0D:	
		case MCNODE:	
		case MNODE:	
			return GetSolCreOp()->CreateorActivateCreOp_NOD(wParam, lParam);
		case MESH1D:
			return GetSolCreOp()->CreateorActivateCreOp_CUR(wParam, lParam);
		case MESH2D:
			return GetSolCreOp()->CreateorActivateCreOp_PAT(wParam, lParam);
		case MESH3D:
//			return GetSolCreOp()->CreateorActivateCreOp_SOL(wParam, lParam);
		case MBJ3D:
//			return GetSolCreOp()->CreateorActivateCreOp_O3D(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

UINT CCreOMMgr::UpdateCreIn(UINT wParam, long lParam)
{
	return GetSolCreOp()->UpdateCreOp(wParam, lParam);
}

UINT CCreOMMgr::CancelCreIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case MESH0D:	
		case FE0D:	
		case MCNODE:	
		case MNODE:	
			return GetSolCreOp()->CancelCreOp_NOD(wParam, lParam);
		case MESH1D:
			return GetSolCreOp()->CancelCreOp_CUR(wParam, lParam);
		case MESH2D:
			return GetSolCreOp()->CancelCreOp_PAT(wParam, lParam);
		case MESH3D:
//			return GetSolCreOp()->CancelCreOp_SOL(wParam, lParam);
		case MBJ3D:
//			return GetSolCreOp()->CancelCreOp_O3D(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

UINT CCreOMMgr::GoodByeCreIn(UINT wParam, long lParam)
{
	switch(wParam)
	{
		case MESH0D:	
		case FE0D:	
		case MCNODE:	
		case MNODE:	
			return GetSolCreOp()->GoodByeCreOp_NOD(wParam, lParam);
		case MESH1D:
			return GetSolCreOp()->GoodByeCreOp_CUR(wParam, lParam);
		case MESH2D:
			return GetSolCreOp()->GoodByeCreOp_PAT(wParam, lParam);
		case MESH3D:
//			return GetSolCreOp()->GoodByeCreOp_SOL(wParam, lParam);
		case MBJ3D:
//			return GetSolCreOp()->GoodByeCreOp_O3D(wParam, lParam);
		//////////////////////
		default:
			return 0L;
	}
}

LPOINT3 CCreOMMgr::GetStatusMouseWIC()
{
	return m_StatusMouseWIC;
}

void CCreOMMgr::SetStatusMouseWIC(LPOINT3 StatWIC)
{
	m_StatusMouseWIC.x = StatWIC.x;
	m_StatusMouseWIC.y = StatWIC.y;
	m_StatusMouseWIC.z = StatWIC.z;
}

void CCreOMMgr::SetViewCursor(int nType)
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
 
// CCreOMMgr serialization

void CCreOMMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CreOMMgr	:Storing\n");	// TODO: add storing code here 
		ar.Write(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));

	}
	else
	{
		TRACE(" CreOMMgr	:Loading\n");	// TODO: add loading code here
		ar.Read(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));
	}
	////////////////////////////////////////////// Mouse
	GetSolCreOp()->Serialize(ar);
//	GetCurCreOp()->Serialize(ar);
//	GetPatCreOp()->Serialize(ar);
//	GetSolCreOp()->Serialize(ar);
//	GetSupCreOp()->Serialize(ar);
//	GetSLDCreOp()->Serialize(ar);
//	GetSPLCreOp()->Serialize(ar);
//	GetDLDCreOp()->Serialize(ar);
	/////////////
	
}
////////////////////// End of Module ////////////////////


