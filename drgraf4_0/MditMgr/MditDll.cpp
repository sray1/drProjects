// DBoxDLL.cpp : DLL main program
//

#include "stdafx.h"

#include "MditDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL

#include "afxdllx.h"    // standard MFC Extension DLL routines

extern AFX_EXTENSION_MODULE NEAR extensionMdit_DLL = { NULL, NULL };

// Exported DLL initialization is run in context of running application
extern "C" extern void WINAPI InitMditDLL()
{
	// create a new CDynLinkLibrary for this app
	new CDynLinkLibrary(extensionMdit_DLL);
	// nothing more to do
}
//////////////////////////////////////////////////////////////
extern "C" int APIENTRY
DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   switch (dwReason)
   {
      case DLL_PROCESS_ATTACH:
         /* Code from LibMain inserted here.  Return TRUE to keep the
            DLL loaded or return FALSE to fail loading the DLL.
 
            You may have to modify the code in your original LibMain to
            account for the fact that it may be called more than once.
            You will get one DLL_PROCESS_ATTACH for each process that
            loads the DLL. This is different from LibMain which gets
            called only once when the DLL is loaded. The only time this
            is critical is when you are using shared data sections.
            If you are using shared data sections for statically
            allocated data, you will need to be careful to initialize it
            only once. Check your code carefully.
 
            Certain one-time initializations may now need to be done for
            each process that attaches. You may also not need code from
            your original LibMain because the operating system may now
            be doing it for you.
         */
		// Extension DLL one-time initialization - do not allocate memory here,
		//   use the TRACE or ASSERT macros or call MessageBox
		TRACE0("Mdit.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(extensionMdit_DLL, hInstance))
			return FALSE;
         break;
 
      case DLL_THREAD_ATTACH:
         /* Called each time a thread is created in a process that has
            already loaded (attached to) this DLL. Does not get called
            for each thread that exists in the process before it loaded
            the DLL.
 
            Do thread-specific initialization here.
         */
         break;
 
      case DLL_THREAD_DETACH:
         /* Same as above, but called when a thread in the process
            exits.
 
            Do thread-specific cleanup here.
         */
         break;
 
      case DLL_PROCESS_DETACH:
         /* Code from _WEP inserted here.  This code may (like the
            LibMain) not be necessary.  Check to make certain that the
            operating system is not doing it for you.
         */
		TRACE0("Mdit.DLL Terminating!\n");
         break;
   }
 
   /* The return value is only used for DLL_PROCESS_ATTACH; all other
      conditions are ignored.  */
   return TRUE;   // successful DLL_PROCESS_ATTACH
}
////////////////////////////////////// end of module //////////////////
