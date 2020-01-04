// ElemDll.h : header file
// 
#ifndef	_STALDLL_H_
#define	_STALDLL_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitStaLDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif	// _ELEMDLL_H_
