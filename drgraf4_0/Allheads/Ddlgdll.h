// ElemDll.h : header file
// 
#ifndef _DDLGDLL_H_
#define _DDLGDLL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitDDlgDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
