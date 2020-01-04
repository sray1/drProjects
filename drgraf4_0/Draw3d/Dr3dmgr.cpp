// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

/////////////////////
#include "curdef.h"
#include "Dr3DDll.h"
////////////////////
#include "Dr3Drsrc.h"
////////////////////
#include "Dr3DMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionDr3D_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CDr3DMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CDr3DMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDr3DMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
/////////////////////
CDr3DMgr::CDr3DMgr()
{

#ifdef _AFXDLL
	CString strRes;
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDr3D_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif 

	//////////////////////////////////////////////
	m_h000 = AfxGetApp()->LoadCursor( "CURS000" );
	m_h012 = AfxGetApp()->LoadCursor( "CURS012" );
	m_h250 = AfxGetApp()->LoadCursor( "CURS250" );
	m_h037 = AfxGetApp()->LoadCursor( "CURS037" );
	m_h050 = AfxGetApp()->LoadCursor( "CURS050" );
	m_h062 = AfxGetApp()->LoadCursor( "CURS062" );
	m_h075 = AfxGetApp()->LoadCursor( "CURS075" );
	m_h087 = AfxGetApp()->LoadCursor( "CURS087" );
	m_h100 = AfxGetApp()->LoadCursor( "CURS100" );
    //////////////////////////////////////////////

#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

} 

void CDr3DMgr::Init()
{
	///////////////////// 3D Graphics
//	Init3d( NULL );
	/////////////////////
}

/*
UINT CDr3DMgr::DoModal_EyePosition()
{

	////////////////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDr3D_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	UINT nStatus;

	/////////////////////////////////////////////////////////////
//	CNodeProp	NodDr3D;
	/////////////////////////////////////// Now Open Dialog/draw
//	nStatus = NodDr3D.DoModal();
	////////////////////////////////////////////////////////////// 
	
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif 

	///////////////
	return nStatus;
	///////////////
}
*/
 
void CDr3DMgr::SetTimeStatusCursor(float fPercent)
{

	///////////////////////////// Cursor
	if( fPercent<0.125F )
		::SetCursor(m_h000);
	else
	if( fPercent<0.250F )
		::SetCursor(m_h012);
	else
	if( fPercent<0.375F )
		::SetCursor(m_h250);
	else
	if( fPercent<0.500F )
		::SetCursor(m_h037);
	else
	if( fPercent<0.625F )
		::SetCursor(m_h050);
	else
	if( fPercent<0.750F )
		::SetCursor(m_h062);
	else
	if( fPercent<0.875F )
		::SetCursor(m_h075);
	else
	if( fPercent<1.000F )
		::SetCursor(m_h087);
	else
		::SetCursor(m_h100);
    ///////////////////////
    return;
           
}		

CDr3DMgr::~CDr3DMgr()
{

	//////////////////////
	DestroyCursor(m_h000);
	DestroyCursor(m_h012);
	DestroyCursor(m_h250);
	DestroyCursor(m_h037);
	DestroyCursor(m_h050);
	DestroyCursor(m_h062);
	DestroyCursor(m_h075);
	DestroyCursor(m_h087);
	DestroyCursor(m_h100);
    //////////////////////

}

// CDr3DMgr serialization

void CDr3DMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" Dr3DMgr	:Storing\n");	// TODO: add storing code here 

	}
	else
	{
		TRACE(" Dr3DMgr	:Loading\n");	// TODO: add loading code here
	}
	////////////////////////////////////////////// Mouse
	
}
////////////////////// End of Module ////////////////////


