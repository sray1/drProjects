// DBoxDll.h : header file
// 
#ifndef _SDLGDLL_H
#define _SDLGDLL_H

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitSDlgDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
