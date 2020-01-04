// MouseDll.h : header file
// 
#ifndef _EDITDLL_H 
#define _EDITDLL_H 


#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitEMgrDLL();
/*
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA 
///////////////////////////////////////////////////// 
#include "drawbox.h"
///////////////////////////////////////////////////// 
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
/////////////////////////////////////////////////////
*/
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
