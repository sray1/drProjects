// MDlgDll.h : header file
// 
#ifndef _MPATDLL_H_
#define _MPATDLL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitMPatDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
