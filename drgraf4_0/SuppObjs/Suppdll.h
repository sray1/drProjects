// SuppDll.h : header file
// 
#ifndef	_SUPPDLL_H_
#define	_SUPPDLL_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////
// Initialize the DLL, register the classes etc
extern "C" AFX_EXT_API void WINAPI InitSuppDLL();

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif	// _SUPPDLL_H_
