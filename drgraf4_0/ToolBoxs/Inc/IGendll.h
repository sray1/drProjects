// IGenDll.h : header file
// 
#ifndef _IGENDLL_H
#define _IGENDLL_H

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitIGenDLL();
/*
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
///////////////////////////////////////////////////// 
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
*/

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif

