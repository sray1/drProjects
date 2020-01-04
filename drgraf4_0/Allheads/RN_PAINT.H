/*****************************************************************************
 *	File:		3dSolids.h
 *
 *	(C) 1989 Mark M. Owen. All rights reserved.
 *****************************************************************************
 */

#ifndef _3dSolids_
#define	_3dSolids_

#include <math.h>
#include <3dHrchy.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

Fixed		API3D Distance				(pPoint3d);
OsErr		API3D xfRenderGroup			(hGroup,pMatrix,pLighting,Boolean);
OsErr		API3D xfRenderCollection	(hCollection,pMatrix,pLighting,Boolean);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
