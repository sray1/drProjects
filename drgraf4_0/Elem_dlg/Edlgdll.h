// ElemDll.h : header file
// 
#ifndef _EDLGDLL_H_
#define _EDLGDLL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitEDlgDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
