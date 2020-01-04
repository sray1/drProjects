// VDlgDLL.cpp : DLL main program
//

#include "stdafx.h"

#include "VDlgDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL

#include "afxdllx.h"    // standard MFC Extension DLL routines

extern AFX_EXTENSION_MODULE NEAR extensionVDlg_DLL = { NULL, NULL };

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	// Extension DLL one-time initialization - do not allocate memory here,
	//   use the TRACE or ASSERT macros or call MessageBox
	AfxInitExtensionModule(extensionVDlg_DLL, hInstance);
	return 1;   // ok
}

// Exported DLL initialization is run in context of running application
extern "C" extern void WINAPI InitVDlgDLL()
{
	// create a new CDynLinkLibrary for this app
	new CDynLinkLibrary(extensionVDlg_DLL);
	// nothing more to do
}
//////////////////////////////////////////////////////////////
