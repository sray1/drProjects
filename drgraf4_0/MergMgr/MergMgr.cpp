// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "MergDll.h"

#include "drgrafrm.h"
////////////////////
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_Supp.h"
#include "Def_StaL.h"
#include "Def_SpeL.h"
#include "Def_DynL.h"
////////////////////
#include "curdef.h"
#include "MergRsrc.h"
////////////////////
#include "MergMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMerg_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMergMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMergMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMergMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMergMgr::CMergMgr()
{
#ifdef _AFXDLL
	CString strRes;
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMerg_DLL.hModule); // uses client's instance handle 
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

CMergMgr::~CMergMgr()
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

UINT CMergMgr::ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////
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
				case NODE:	
				case INODE:	
				case CNODE:	
				case MNODE:	
					return GetDLDMouse()->ReSetToolID_NOD(CntlID,IGenID,OperID);

				case CURVE:
				case C_CIRCLE:
				case C_ELLIPSE:
				case C_PARABOLA:
				case C_LINEAR:
				case C_QUADRATIC:
				case C_BSPLINE:
				case C_BEZIER:
				case C_NURB:
					return GetDLDMouse()->ReSetToolID_CUR(CntlID,IGenID,OperID);

				case PATCH:
				case P_EXTRUDE:
				case P_ROTATE: 
				case P_LOFT: 
				case P_DUCT: 
				case P_SWEEP:
				case P_COONS:	
					return GetDLDMouse()->ReSetToolID_PAT(CntlID,IGenID,OperID);

				case SOLID:
				case S_EXTRUDE:
				case S_ROTATE: 
				case S_LOFT: 
				case S_DUCT: 
				case S_SWEEP: 
				case S_COONS:
					return GetDLDMouse()->ReSetToolID_SOL(CntlID,IGenID,OperID);
			}
		}
		//////////////////////////////////////// Support
		case SUPPORT:
		case SUPPORT_RIGID:
		case SUPPORT_LINSPRING:
		case SUPPORT_LINSNUBBER:
		case SUPPORT_NLSPRING:
		case SUPPORT_NLSNUBBER:

			return GetDLDMouse()->ReSetToolID_SUP(CntlID,IGenID,OperID);
		//////////////////////////////////////// StaticLoad
		case STATICLOAD:
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
			
			return GetDLDMouse()->ReSetToolID_SLD(CntlID,IGenID,OperID);


		default:

			return (UINT)NONE;

		//	GetDLDMouse()->InitDlgIn();
		//	GetSPLMouse()->InitDlgIn();
	}
}


UINT CMergMgr::ReSetToolID_Mesh(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////
	switch(CntlID)
	{
		//////////////////////////////////////// IGEN
		case ELEMENT:

		{
			switch(IGenID)
			{
				case EDIM_0:
					return GetMDLDMouse()->ReSetToolID_NOD(CntlID,IGenID,OperID);

				case EDIM_1:
//					return GetMDLDMouse()->ReSetToolID_CUR(CntlID,IGenID,OperID);

				case EDIM_2:
//					return GetMDLDMouse()->ReSetToolID_PAT(CntlID,IGenID,OperID);

				case EDIM_3:
//					return GetMDLDMouse()->ReSetToolID_SOL(CntlID,IGenID,OperID);
				default:
					return (UINT)NONE;
			}
		}
		//////////////////////////////////////// Support
		case SUPPORT:
		case SUPPORT_RIGID:
		case SUPPORT_LINSPRING:
		case SUPPORT_LINSNUBBER:
		case SUPPORT_NLSPRING:
		case SUPPORT_NLSNUBBER:

//			return GetMDLDMouse()->ReSetToolID_SUP(CntlID,IGenID,OperID);
		//////////////////////////////////////// StaticLoad
		case STATICLOAD:
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
			
//			return GetMDLDMouse()->ReSetToolID_SLD(CntlID,IGenID,OperID);


		default:

			return (UINT)NONE;

		//	GetDLDMouse()->InitDlgIn();
		//	GetSPLMouse()->InitDlgIn();
	}
}

LPOINT3 CMergMgr::GetStatusMouseWIC()
{
	return m_StatusMouseWIC;
}

void CMergMgr::SetStatusMouseWIC(LPOINT3 StatWIC)
{
	m_StatusMouseWIC.x = StatWIC.x;
	m_StatusMouseWIC.y = StatWIC.y;
	m_StatusMouseWIC.z = StatWIC.z;
}

void CMergMgr::SetViewCursor(int nType)
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
 
// CMergMgr serialization

void CMergMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MergMgr	:Storing\n");	// TODO: add storing code here 
		ar.Write(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));

	}
	else
	{
		TRACE(" MergMgr	:Loading\n");	// TODO: add loading code here
		ar.Read(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));
	}
	////////////////////////////////////////////// Mouse
	GetDLDMouse()->Serialize(ar);
	/////////////
//	GetDBEdit()->Serialize(ar);
	
}
////////////////////// End of Module ////////////////////

