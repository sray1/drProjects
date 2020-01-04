// MDlgDll.h : header file
// 
#ifndef _MSOLDLL_H_
#define _MSOLDLL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitMSolDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
