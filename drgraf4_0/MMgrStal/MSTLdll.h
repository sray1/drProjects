// MouseDll.h : header file
// 
#ifndef _MSTLDLL_H 
#define _MSTLDLL_H 


#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitMStLDLL();
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
