/****************************************************************************
 *	File:		LOADBMPF.h
 *
 *	Copyright:	(C) 1991 Mark M. Owen -- All Rights Reserved.
 ****************************************************************************
 */
#ifndef _LOADBMPFILE_
#define _LOADBMPFILE_

#include <OSINTF.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

HBITMAP	API3D LoadBMPFile	(HDC hDC,LPSTR fileName);
void	API3D WriteBMPFile	(HDC hDC,HBITMAP hBM,LPSTR fileName);
void	API3D WindowShotPal	(HWND hWnd,LPSTR fileName,HPALETTE hPal);
void	API3D ScreenShotPal	(LPSTR fileName,HPALETTE hPal);
void	API3D WindowShot	(HWND hWnd,LPSTR fileName);
void	API3D ScreenShot	(LPSTR fileName);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// _LOADBMPFILE_
