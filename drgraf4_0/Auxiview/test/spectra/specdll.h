#ifndef _SPECDLL_H_
#define _SPECDLL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
// SpecDll.h : header file
// 
/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitSpecDLL();
// <body of your header file>
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
