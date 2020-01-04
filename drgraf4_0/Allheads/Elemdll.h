// ElemDll.h : header file
// 
#ifndef	_ELEMDLL_H_
#define	_ELEMDLL_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitElemDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif	// _ELEMDLL_H_
