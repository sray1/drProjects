// MouseDll.h : header file
// 
#ifndef _DECKDLL_H 
#define _DECKDLL_H 


#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitDeckDLL();
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
