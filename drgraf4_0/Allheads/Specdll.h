// DBoxDll.h : header file
// 
#ifndef _SPECDLL_H
#define _SPECDLL_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitSpecDLL();
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
