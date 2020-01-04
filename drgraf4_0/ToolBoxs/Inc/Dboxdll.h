// DBoxDll.h : header file
// 
#ifndef _DBOXDLL_H
#define _DBOXDLL_H

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitDBoxDLL();

#undef AFX_DATA
#define AFX_DATA

/////////////////////////////////////////////////////////////////////////////
#endif

