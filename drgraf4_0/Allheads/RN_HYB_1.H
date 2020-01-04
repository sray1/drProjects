/******************************************************************************
 *	file:		"ZPoly.h"
 *
 *	(C) 1993 Mark M. Owen.	All rights reserved.
 *****************************************************************************
 */

#ifndef _ZPoly_
#define _ZPoly_
#include <3d.h>
#include <ZBuffers.h>

extern BOOL ZPoly;	// indication that ZPolygon is enabled (DLL internal only)

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif	/* __cplusplus */

OsErr	API3D InitZPoly(LPRECT r);
OsErr	API3D UseZPoly(HWND hWnd);
void	API3D TermZPoly(void);
BOOL	API3D StateZPoly(void);
pZBuffer API3D GetZPolyZB(void);
void	API3D ZPoint(POINT p,Fixed z,COLORREF C);

#ifndef _ZPOLYVARIANT_
OsErr	API3D ZPolygon(short nS,LPPOINT S,pPoint3d P,COLORREF c);
void	API3D ZLine(POINT S0,POINT S1,pPoint3d P0,pPoint3d P1,COLORREF C);
void	API3D ZPolyline(short nS,LPPOINT S,pPoint3d P,COLORREF c);
#else
OsErr API3D ZPolygon(short nS,LPPOINT S,pPoint2d sp,pPoint3d P,COLORREF c,COLORREF ce);
void API3D ZLine(POINT S0,POINT S1,Fixed DX,Fixed DY,pPoint3d P0,pPoint3d P1,COLORREF C);
void	API3D ZPolyline(short nS,LPPOINT S,pPoint2d sp,pPoint3d P,COLORREF c);
#endif	// _ZPOLYVARIANT_

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif	/* __cplusplus */

#endif /* _ZPOLY_ */
