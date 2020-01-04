// DBoxDLL.cpp : DLL main program
//

#include "stdafx.h"

//#include "dbglobal.h"
//#include "dboxrsrc.h"       // symbols unique to this DLL
/*
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
*/
#include "MouseDll.h"
/*
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
*/
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL

#include "afxdllx.h"    // standard MFC Extension DLL routines

extern AFX_EXTENSION_MODULE NEAR extensionMouse_DLL = { NULL, NULL };

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	// Extension DLL one-time initialization - do not allocate memory here,
	//   use the TRACE or ASSERT macros or call MessageBox
	AfxInitExtensionModule(extensionMouse_DLL, hInstance);
	return 1;   // ok
}

// Exported DLL initialization is run in context of running application
extern "C" extern void WINAPI InitMouseDLL()
{
	// create a new CDynLinkLibrary for this app
	new CDynLinkLibrary(extensionMouse_DLL);
	// nothing more to do
}
//////////////////////////////////////////////////////////////
