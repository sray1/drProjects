// IGenDll.h : header file
// 
#ifndef _EBOXDLL_H
#define _EBOXDLL_H

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitEBoxDLL();
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
