/*****************************************************************************
 *	File:		Camera.cpp
 *
 *	Purpose:	Implements Camera Metaphor & 
 *				PHIG Conversion
 *				.
 *
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <math.h>
#include <3dextrn.h>
#include <Camera.h>

#define	DEG(x)	(x)*57.295779513082F

static FPType	Magnitude		(pPoint3d);
static Fixed	Angle			(pPoint3d,pPoint3d);
static Fixed	ViewAngle		(Fixed);

/*****************************************************************************
 *
 *	Function:	Magnitude()
 *
 *	Purpose:	Calculates length or magnitude of a vector.
 *
 *	Returns:	The vector magnitude in floating point.
 *
 *	Warnings:	Private Function
 *
 *****************************************************************************
 */
static FPType	Magnitude(pPoint3d a)
{
	FPType	x=fix2x(a->x),
			y=fix2x(a->y),
			z=fix2x(a->z);

	return tSqrt(x*x+y*y+z*z);
}

/*****************************************************************************
 *
 *	Function:	Angle()
 *
 *	Purpose:	Calculates the angle between two vectors.
 *
 *	Returns:	The angle between the vectors in degrees rounded to 5 decimal
 *				places.
 *
 *	Warnings:	Private Function
 *
 *****************************************************************************
 */
static Fixed	Angle(pPoint3d E,pPoint3d N)
{
	FPType m,A;

	m = Magnitude(E);
	if( m==0.0F )
		return f_0;
	m *= Magnitude(N);
	A = DotProduct( E, N ) / m;
	if( A<-1 )
		A=-1;
	else
	if( A>1 )
		A=1;
	A = DEG( (FPType)acos( (double)A ) ) + 0.000005F;
	return x2fix(&A);
}

/*****************************************************************************
 *
 *	Function:	ViewAngle()
 *
 *	Purpose:	Calculates the zoom factor needed to produce a specified angle
 *				of view.
 *
 *	Returns:	View zoom factor.
 *
 *	Warnings:	Private Function
 *
 *	History:	Modified 3/7/93 to use 0.5 window width when theta <0
 *
 *****************************************************************************
 */
static Fixed	ViewAngle(Fixed theta)
{
	FPType	y,a,k;

    k = theta<f_0?(centerX*a65536th):320.0F;

	a = a65536th*(theta<f_0?-theta:theta);
	if( a < 0.0039062F )
		a = 0.0039062F;
	else
	if( a >= 180.0F )
		a = 179.9961F;
	y = (float)tan( (180.0F - a ) * 0.0087266462599715F ) * k;
	return (Fixed)(y*65536.0F);
}

/*****************************************************************************
 *
 *	Function:	AimCamera()
 *
 *	Purpose:	Sets the viewer transformation matrix such that the viewer is
 *				looking towards a particular point from a specified location,
 *				using a specified field of view.  The viewer's roll angle is
 *				set to zero, and the scaling factors are set to one.  Pitch
 *				and yaw are set as necessary to cause the focusOn point to be
 *				in the center of the projected image.
 *
 *				Note that the from and focusOn points are in world coordinates
 *				not in viewer coordinates.  The necessary conversions are done
 *				here (changing the signs of the x and z values).
 *
 *****************************************************************************
 */
void	API3D AimCamera(
		pPoint3d	from,		// viewer's location
		pPoint3d	focusOn,	// point to focus on
		Fixed		field,		// field of view angle
		Fixed		roll		// roll angle
	)
{
	Fixed	pitch,yaw;
	Point3d	E,N;

	/* and heres what we do...
	 *	construct vector to eye as
	 *		E = focusOn - from
	 *	Construct two planes at
	 *		H = Ÿ(y) = 0 and
	 *		V = Ÿ(x) = 0
	 *	Construct normals of
	 *		H as n = a x b and
	 *		V as N = A x B
	 *
	 *	pitch	= acos ( (Eùn)/(|E||n|) )
	 *	yaw		= acos ( (EùN)/(|E||N|) )
	 */

	/* convert to viewer coordinates and
	 * construct vector to the viewer's eye
	 */
	E.x = -focusOn->x - -from->x;
	E.y =  focusOn->y -  from->y;
	E.z = -focusOn->z - -from->z;

	/* get pitch angle from eye vector using angle
	 * between vertical vector from horizontal
	 * plane (x,0,z) and eye vector
	 */
	N.x = f_0;
	N.y = -f_2;
	N.z = f_0;
	pitch = -(f_90-Angle(&E,&N));

	/* get yaw angle from eye vector using angle
	 * between horizontal vector from vertical
	 * plane (0,y,z) and eye vector translated to
	 * an elevation of 0 since pitch is no longer
	 * a factor we wish to be considered.
	 */
	E.y = f_0;

	N.x = -f_2;
	N.y = f_0;
	N.z = f_0;
	yaw = f_90-Angle(&E,&N);

	if( E.z > 0 )
		yaw=f_180-yaw;			//	adjust for locations behind the viewer

	SetViewerReferenceFrame(	//	set viewer transform matrix
			pitch,yaw,roll,
			f_1,f_1,f_1,
			-from->x,from->y,-from->z,
			fixdiv( f_1,ViewAngle(field) )
		);
}
