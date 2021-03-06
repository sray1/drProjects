/*****************************************************************************
 *	File:		Camera.h
 *
 *	(C) 1989 Mark M. Owen. All rights reserved.
 *****************************************************************************
 */
#ifndef	_CAMERA_H_
#define	_CAMERA_H_

#include <3d.h>

/*	Horizontal angles of view for 35mm Camera Lens equivalence
 *	when used on a 640x480 screen.  A 35mm film frame has an
 *	aspect ratio of 0.666. whereas the 640x480 screen is 0.75.
 *	For example:  using the Lens40mm selection below will cause
 *	46� of a circle centered about the viewer to span the width
 *	of a 640x480 pixel screen.  Lens specifications vary, but
 *	often include horizontal, vertical and diagonal field of
 *	view specifications.  This implementation considers only the
 *	horizontal specification.
 */
#define Lens15mm	Int2Fix( 105 )
#define Lens20mm	Int2Fix(  83 )
#define Lens30mm	Int2Fix(  62 )
#define Lens40mm	Int2Fix(  46 )
#define	Lens50mm	Int2Fix(  40 )
#define Lens60mm	Int2Fix(  33 )
#define Lens70mm	Int2Fix(  29 )
#define Lens80mm	Int2Fix(  26 )
#define Lens90mm	Int2Fix(  23 )
#define Lens100mm	Int2Fix(  20 )
#define Lens150mm	Int2Fix(  15 )
#define Lens200mm	Int2Fix(  10 )
#define Lens500mm	Int2Fix(   4 )
#define Lens1000mm	Int2Fix(   2 )

#define AimCamera3d( fx, fy, fz, tx, ty, tz, vAngle ) {\
		Point3d	from, to;\
		SetPt3d( &from, (fx), (fy), (fz) );\
		SetPt3d( &to, (tx), (ty), (tz) );\
		AimCamera( &from, &to, (vAngle), f_0 );\
	}

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void	API3D AimCamera	(pPoint3d,pPoint3d,Fixed,Fixed);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
