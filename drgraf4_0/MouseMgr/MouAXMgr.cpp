// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "MMgrDll.h"

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
#include "MMgrRsrc.h"
////////////////////
#include "MouAXMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMMgr_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CMouAXMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMouAXMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMouAXMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CMouAXMgr::CMouAXMgr()
{
#ifdef _AFXDLL
	CString strRes;
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMMgr_DLL.hModule); // uses client's instance handle 
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

CMouAXMgr::~CMouAXMgr()
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

void CMouAXMgr::InitDlgIn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	GetDLDMouse()->InitDlgIn_NOD();
	GetDLDMouse()->InitDlgIn_CUR();
/*
	GetDLDMouse()->InitDlgIn_PAT();
	GetDLDMouse()->InitDlgIn_SOL();
	GetDLDMouse()->InitDlgIn_O3D();
	///////////////////////////////
//	GetDBMouse()->InitDlgIn();
	///////////////////////////////
	GetDLDMouse()->InitDlgIn_SUP();
	GetDLDMouse()->InitDlgIn_SLD();
*/
	GetDLDMouse()->SetProbLim(pWnd->GetProbDimLim());
	GetDLDMouse()->SetElemLim(pWnd->GetElemDimLim());
	///////////////////////////////
//	GetDLDMouse()->InitDlgIn();
//	GetSPLMouse()->InitDlgIn();
	///////////////////////////////
}

UINT CMouAXMgr::ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID)
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
				case NODE:	
				case INODE:	
				case CNODE:	
				case MCNODE:	
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
//					return GetDLDMouse()->ReSetToolID_PAT(CntlID,IGenID,OperID);

				case SOLID:
				case S_EXTRUDE:
				case S_ROTATE: 
				case S_LOFT: 
				case S_DUCT: 
				case S_SWEEP: 
				case S_COONS:
//					return GetDLDMouse()->ReSetToolID_SOL(CntlID,IGenID,OperID);

				case OBJ3D:
//					return GetDLDMouse()->ReSetToolID_O3D(CntlID,IGenID,OperID);
					;
			}
		}
			return (UINT)NONE;
		//////////////////////////////////////// Support
		case SUPPORT:
		case SUPPORT_RIGID:
		case SUPPORT_LINSPRING:
		case SUPPORT_LINSNUBBER:
		case SUPPORT_NLSPRING:
		case SUPPORT_NLSNUBBER:

//			return GetDLDMouse()->ReSetToolID_SUP(CntlID,IGenID,OperID);
		//////////////////////////////////////// StaticLoad
		case STATICLOAD:
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
			
//			return GetDLDMouse()->ReSetToolID_SLD(CntlID,IGenID,OperID);


		default:

			return (UINT)NONE;

		//	GetDLDMouse()->InitDlgIn();
		//	GetSPLMouse()->InitDlgIn();
	}
}

LPOINT3 CMouAXMgr::GetStatusMouseWIC()
{
	return m_StatusMouseWIC;
}

void CMouAXMgr::SetStatusMouseWIC(LPOINT3 StatWIC)
{
	m_StatusMouseWIC.x = StatWIC.x;
	m_StatusMouseWIC.y = StatWIC.y;
	m_StatusMouseWIC.z = StatWIC.z;
}

void CMouAXMgr::SetViewCursor(int nType)
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
 
// CMouAXMgr serialization

void CMouAXMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MouAXMgr	:Storing\n");	// TODO: add storing code here 
		ar.Write(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));

	}
	else
	{
		TRACE(" MouAXMgr	:Loading\n");	// TODO: add loading code here
		ar.Read(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));
	}
	////////////////////////////////////////////// Mouse
//	GetSolMouse()->Serialize(ar);
//	GetSupMouse()->Serialize(ar);
//	GetSLDMouse()->Serialize(ar);
//	GetSPLMouse()->Serialize(ar);
	GetDLDMouse()->Serialize(ar);
	/////////////
	GetDBMouse()->Serialize(ar);
	
}
////////////////////// End of Module ////////////////////


