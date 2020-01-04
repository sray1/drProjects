/*****************************************************************************
 *	File:		3dSolidsPgn.h
 *
 *	(C) 1991 Mark M. Owen. All rights reserved.
 *****************************************************************************
 */
#ifndef _3dSolidsPgn_
#define	_3dSolidsPgn_

#include <3dSolids.h>
#include <Textures.h>
#include <Render.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

OsErr	API3D xfRenderZBuffer(
		HDC 		hDC,
		hCollection	hC,
		pMatrix		xf,
		pLighting	pL,
		pZBuffer	pZB
	);
OsErr	API3D xfRenderCollectionPgn(
		pRECT		pR,
		hCollection	hC,
		pMatrix		xf,
		pLighting	pL
	);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //	_3dSolidsPgn_
