/*****************************************************************************
 *	file:		"ZPoly.h"
 *
 *	purpose:	hybrid painters Z buffered polygon renderer
 *
 *	(C) 1993 Mark M. Owen.	All rights reserved.
 *****************************************************************************
 */

#include <WIN_TRIM.H>
#include <OSINTF.h>
#include <ZPoly.h>
#include <limits.h>
#include <math.h>


#define	INVALID_REQUEST		-1
#define	MEMORY_ALLOC_ERROR	-2

#define	PIXELFILL(_x,_y,_c)		SetPixel(hDC,(_x),(_y),(_c))
#define	LINEFILL(_xs,_xe,_y)	MoveTo(hDC,(_xs),(_y));LineTo(hDC,(_xe),(_y))


#ifdef _ZPOLYVARIANT_
typedef struct tScanSeg {
	Fixed		x[2];
	Fixed		z[2];
}
	ScanSeg, __far *pScanSeg;
typedef struct tCouple {
	short	v[2];
	Fixed	z[2];
}
	Couple, __far *pCouple;

static pCouple	pYc;
static pCouple	pXc;

#else // not _ZPOLYVARIANT_

typedef struct tScanSeg {
	short		x[2];
	Fixed		z[2];
}
	ScanSeg, __far *pScanSeg;

#endif	// _ZPOLYVARIANT_

BOOL		ZPoly = FALSE;

static HDC			hDC = NULL;
static short		MINH,MAXH,MINV,MAXV;
static ZBuffer		ZB;
static pZBuffer		pZB = &ZB;
static HANDLE		hSS = NULL;
static pScanSeg		pSS = (pScanSeg)NULL;
static COLORREF		C	= RGB(0,0,0);

#define	Max(a,b)	((a)>(b)?(a):(b))
#define Min(a,b)	((a)<(b)?(a):(b))
#define	SQRT		tSqrt
#define	distance(c)	((Fixed)SQRT((FPType)(c).x*(FPType)(c).x+(FPType)(c).y*(FPType)(c).y+(FPType)(c).z*(FPType)(c).z))
#define	MINMAX	0x80007FFF


#ifdef _ZPOLYVARIANT_
static void	_near AddEdge(POINT p0,Point2d s0,Fixed Az,POINT p1,Point2d s1,Fixed Bz);
#else
static void	_near AddEdge(POINT p0,Fixed Az,POINT p1,Fixed Bz);
#endif	// _ZPOLYVARIANT_

static void	_near RenderSegment(short y,pScanSeg pss);


OsErr API3D InitZPoly(LPRECT r)
{
	register short	i;
	pScanSeg	pss;

	AllocZB( pZB, r->left, r->top, r->right, r->bottom );
	if( !pZB->gh )
		return MEMORY_ALLOC_ERROR;

#ifdef _ZPOLYVARIANT_
	{
		pCouple	pyc;
		pCouple	pxc;
	    MBSIZE	dY,dX;
	    dY = r->bottom-r->top+1;
	    dX = r->right-r->left+1;
		hSS = GlobalAlloc( GMEM_MOVEABLE|GMEM_SHARE,
				(sizeof(ScanSeg)+sizeof(Couple)) * dY
			+	sizeof(Couple) * dX
		);
		if( !hSS ) {
			DeallocZB( pZB );
			return MEMORY_ALLOC_ERROR;
		}
		pSS = (pScanSeg)GlobalLock( hSS );
	    if( !pSS ) {
			DeallocZB( pZB );
			return MEMORY_ALLOC_ERROR;
		}

		pss = pSS;
		pxc = pXc = (pCouple)(pss+dY);
		pyc = pYc = pXc+dY;
		i = (int)dY;
		while( i-- ) {
			pss->x[0] = LONG_MAX;
			pss->x[1] = LONG_MIN;
			pss++;
			*((DWORD*)pxc++) = MINMAX;
		}
		i = (int)dX;
		while( i-- )
			*((DWORD*)pyc++) = MINMAX;
	}
#else	// not _ZPOLYVARIANT_
	hSS = GlobalAlloc( GMEM_MOVEABLE|GMEM_SHARE, sizeof(ScanSeg) * (MBSIZE)(r->bottom-r->top+1) );
	if( !hSS ) {
		DeallocZB( pZB );
		return MEMORY_ALLOC_ERROR;
	}
	pSS = (pScanSeg)GlobalLock( hSS );
    if( !pSS ) {
		DeallocZB( pZB );
		return MEMORY_ALLOC_ERROR;
	}
	pss = pSS;
	i = (r->bottom-r->top+1);
	while( i-- ) {
		*((DWORD*)pss) = MINMAX;
		pss++;
	}
#endif	// _ZPOLYVARIANT_
	hDC = GetCurrentDC();
	ZPoly = TRUE;
	return noErr;
}

OsErr API3D UseZPoly(HWND hWnd)
{
	RECT	r;

	GetClientRect( hWnd, &r );
	return InitZPoly( &r );
}

void API3D TermZPoly(void)
{
	if( ZPoly ) {
		if( hSS ) {
			GlobalFree( hSS );
			hSS = NULL;
		}
		DeallocZB( pZB );
		ZPoly = FALSE;
	}
}

BOOL API3D StateZPoly(void)
{
	return ZPoly;
}

pZBuffer API3D GetZPolyZB(void)
{
	return pZB;
}

#ifdef _ZPOLYVARIANT_

OsErr API3D ZPolygon(short nS,LPPOINT S,pPoint2d sp,pPoint3d P,COLORREF c,COLORREF ce)
{
	register short	y,i = nS;
	POINT		*ps = S;
    pPoint3d	pp = P;
    pPoint2d	psp = sp;	//
	pScanSeg	pss;
	Fixed		Az,Bz,Oz;
	HPEN		hpC,hpOld;

	if( !pZB->gh )
		return INVALID_REQUEST;
 	if( !pSS )
		return	MEMORY_ALLOC_ERROR;

    MINH = MAXH = ps->x;
    MINV = MAXV = ps->y;
    i--;
    ps++;

	while( i-- ) {
		if( ps->x<MINH )	MINH = ps->x;
		else
		if( ps->x>MAXH )	MAXH = ps->x;

		if( ps->y<MINV )	MINV = ps->y;
		else
		if( ps->y>MAXV )	MAXV = ps->y;
		ps++;
	}
	// intersect polygon bounds with Zbuffer bounds
	if( MINV<(short)pZB->yMn ) MINV = (short)pZB->yMn;
	if( MAXV>(short)pZB->yMx ) MAXV = (short)pZB->yMx;
	if( MAXV<=MINV )
		return noErr;
	if( MINH<(short)pZB->xMn ) MINH = (short)pZB->xMn;
	if( MAXH>(short)pZB->xMx ) MAXH = (short)pZB->xMx;
	if( MAXH<=MINH )
		return noErr;

	i = nS;
	ps = S;
	Oz = Az = distance( *pp );
	while( --i ) {
		Bz = distance( *(pp+1) );
		AddEdge( *ps, *psp, Az, *(ps+1), *(psp+1), Bz ); //
		Az = Bz;
		ps++;
		psp++;	//
		pp++;
	}
	AddEdge( *ps, *psp, Az, *S, *sp, Oz );

	C = c;
	hpC = CreatePen( PS_SOLID, 1, c );
	hpOld = SelectObject( hDC, hpC );
	pss = pSS;
	for( y = MINV; y <= MAXV; y++, pss++ ) {
		if( pss->x[0] < LONG_MAX ) {
			RenderSegment( y, pss );
			pss->x[0] = LONG_MAX;
			pss->x[1] = LONG_MIN;
		}
	}
    SelectObject( hDC, hpOld );
    DeleteObject( hpC );

    if( c!=ce ) {
		pCouple		pyc = pYc+MINH;
		pCouple		pxc = pXc+MINV;
		for( i=MINH;i<=MAXH; i++, pyc++ ) {
			if( pyc->v[0]<INT_MAX )
				PIXELFILL( i, pyc->v[0], ce );
			if( pyc->v[1]>INT_MIN )
				PIXELFILL( i, pyc->v[1], ce );
			*((DWORD*)pyc) = MINMAX;
		}
		for( y=MINV;y<=MAXV; y++, pxc++ ) {
			if( pxc->v[0]<INT_MAX )
				PIXELFILL( pxc->v[0], y, ce );
			if( pxc->v[1]>INT_MIN )
				PIXELFILL( pxc->v[1], y, ce );
			*((DWORD*)pxc) = MINMAX;
		}
	}
    return noErr;
}

static void	_near AddEdge(POINT p0,Point2d s0,Fixed Az,POINT p1,Point2d s1,Fixed Bz)
{
	register short y,X;
	short		yMn,oy;
	Fixed		x,dx,z,dz,OY;
	pScanSeg	pss;

	if( p0.y == p1.y )
		return;
	if( p0.y > p1.y ) {
		POINT	p = p0;
		Point2d s = s0;
		p0 = p1; p1 = p;
		s0 = s1; s1 = s;
		z = Az; Az = Bz; Bz = z;
	}
	oy	= p1.y-p0.y;
	OY	= s1.y-s0.y;
	dx	= fixdiv( s1.x-s0.x, OY );
	dz	= fixdiv( Bz-Az, OY );
	y	= Max( p0.y, MINV );
	x	= s0.x;
	z	= Az;
	oy	= y-p0.y;
	if( oy ) {
		x	+= dx * oy;
		z	+= dz * oy;
	}
	if( MAXV < p1.y )
		p1.y = MAXV;
	yMn	= MINV;
	pss = pSS + (y-yMn);
	while( y < p1.y ) {
		if( x<pss->x[0] ) {
			pss->x[0] = x;
			pss->z[0] = z;
		}
		if( x>pss->x[1] ) {
			pss->x[1] = x;
			pss->z[1] = z;
		}
		y++;
		pss++;
		x += dx;
		z += dz;
	}
}

static void	_near RenderSegment(short y,pScanSeg pss)
{
	register short x,xMx;
	short		Ix1,Ix2,xs,xe,ox;
	Fixed		z,dz;
	long _huge	*pB;
	BOOL		spanopen = FALSE;
	pCouple		pyc;
	pCouple		pxc;

	Ix1 = (short)LLSR(pss->x[0],16);
	Ix2 = (short)LLSR(pss->x[1],16);
	if( Ix1 == Ix2 )
		return;
	if( Ix1 > (short)pZB->xMx || Ix2 < (short)pZB->xMn )	// out of window bounds
		return;
	z	= pss->z[0];
	x	= Max( Ix1, (short)pZB->xMn );// forcing -x to zero here
	dz	= fixdiv( pss->z[1] - z, pss->x[1]-pss->x[0] );
	ox	= x - Ix1;
	if( ox )
		z	+= dz*ox;
	xMx	= Min( Ix2, (short)pZB->xMx );
	pB	= pZB->zb + ( y - pZB->yMn ) * pZB->xRng + x - pZB->xMn;
	pyc = pYc+x;
	pxc = pXc+y;
	while( x < xMx ) {
		if( z <= *pB ) {
			if( x<pxc->v[0] ) {
				pxc->v[0] = x;
				pxc->z[0] = z;
			}
			if( x>pxc->v[1] ) {
				pxc->v[1] = x;
				pxc->z[1] = z;
			}
			if( y<pyc->v[0] ) {
				pyc->v[0] = y;
				pyc->z[0] = z;
			}
			if( y>pyc->v[1] ) {
				pyc->v[1] = y;
				pyc->z[1] = z;
			}
			*pB = z;
			xe = x;
			if( !spanopen ) {
				spanopen = TRUE;
				xs = x;
			}
		}
		else
		if( spanopen ) {
			spanopen = FALSE;
			if( xe==xs ) {
				PIXELFILL( xs, y, C );
			}
			else {
				LINEFILL(xs,++xe,y);
			}
		}
		x++;
		pyc++;
		pB++;
		z += dz;
	}
	if( spanopen ) {
		spanopen = FALSE;
		if( xe==xs ) {
			PIXELFILL( xs, y, C );
		}
		else {
			LINEFILL(xs,++xe,y);
		}
	}
}

#else	// not _ZPOLYVARIANT_

OsErr API3D ZPolygon(short nS,LPPOINT S,pPoint3d P,COLORREF c)
{
	register short	y,i = nS;
	POINT		*ps = S;
    pPoint3d	pp = P;
	pScanSeg	pss;
	Fixed		Az,Bz,Oz;
	HPEN		hpC,hpOld;

	if( !pZB->gh )
		return INVALID_REQUEST;
 	if( !pSS )
		return	MEMORY_ALLOC_ERROR;

    MINH = MAXH = ps->x;
    MINV = MAXV = ps->y;
    i--;
    ps++;

	while( i-- ) {
		if( ps->x<MINH )	MINH = ps->x;
		else
		if( ps->x>MAXH )	MAXH = ps->x;

		if( ps->y<MINV )	MINV = ps->y;
		else
		if( ps->y>MAXV )	MAXV = ps->y;
		ps++;
	}
	// intersect polygon bounds with Zbuffer bounds
	if( MINV<(short)pZB->yMn ) MINV = (short)pZB->yMn;
	if( MAXV>(short)pZB->yMx ) MAXV = (short)pZB->yMx;
	if( MAXV<=MINV )
		return noErr;
	if( MINH<(short)pZB->xMn ) MINH = (short)pZB->xMn;
	if( MAXH>(short)pZB->xMx ) MAXH = (short)pZB->xMx;
	if( MAXH<=MINH )
		return noErr;

	i = nS;
	ps = S;
	Oz = Az = distance( *pp );
	while( --i ) {
		Bz = distance( *(pp+1) );
		AddEdge( *ps, Az, *(ps+1), Bz );
		Az = Bz;
		ps++;
		pp++;
	}
	AddEdge( *ps, Az, *S, Oz );

	C = c;
	hpC = CreatePen( PS_SOLID, 1, c );
	hpOld = SelectObject( hDC, hpC );
	pss = pSS;
	for( y = MINV; y <= MAXV; y++, pss++ ) {
		if( pss->x[0] < INT_MAX ) {
			RenderSegment( y, pss );
			*((DWORD*)pss) = MINMAX;
		}
	}
    SelectObject( hDC, hpOld );
    DeleteObject( hpC );
    return noErr;
}

static void	_near AddEdge(POINT p0,Fixed Az,POINT p1,Fixed Bz)
{
	register short y,X;
	short		yMn,oy;
	Fixed		x,dx,z,dz;
	pScanSeg	pss;

	if( p0.y == p1.y )
		return;
	if( p0.y > p1.y ) {
		POINT	p = p0; p0 = p1; p1 = p;
		z = Az; Az = Bz; Bz = z;
	}
	oy	= p1.y-p0.y;
	dx	= fixdiv( (p1.x-p0.x), (Fixed)oy );
	dz	= fixdiv( Bz-Az, LLSL( (Fixed)oy, 16 ) );
	y	= Max( p0.y, MINV );
	x	= LLSL((Fixed)p0.x,16);
	z	= Az;
	oy	= y-p0.y;
	if( oy ) {
		x	+= dx * oy;
		z	+= dz * oy;
	}
	if( MAXV < p1.y )
		p1.y = MAXV;
	yMn	= MINV;
	x	+= f_0p5;
	pss = pSS + (y-yMn);
	while( y < p1.y ) {
		X 	= (short)LLSR(x,16);
		if( X<pss->x[0] ) {
			pss->x[0] = X;
			pss->z[0] = z;
		}
		if( X>pss->x[1] ) {
			pss->x[1] = X;
			pss->z[1] = z;
		}
		y++;
		pss++;
		x += dx;
		z += dz;
	}
}

static void	_near RenderSegment(short y,pScanSeg pss)
{
	register short x,xMx;
	short		Ix1,Ix2,xs,xe,ox;
	Fixed		z,dz;
	long _huge	*pB;
	BOOL		spanopen = FALSE;

	Ix1 = pss->x[0];
	Ix2 = pss->x[1];
	if( Ix1 == Ix2 )
		return;
	if( Ix1 > (short)pZB->xMx || Ix2 < (short)pZB->xMn )	// out of window bounds
		return;
	z	= pss->z[0];
	x	= Max( Ix1, (short)pZB->xMn );// forcing -x to zero here
	dz	= fixdiv( pss->z[1] - z, LLSL( (Fixed)(Ix2-Ix1),16 ) );
	ox = x - Ix1;
	if( ox )
		z	+= dz*ox;
	xMx	= Min( Ix2, (short)pZB->xMx );
	pB	= pZB->zb + ( y - pZB->yMn ) * pZB->xRng + x - pZB->xMn;
	while( x < xMx ) {
		if( z <= *pB ) {
			*pB = z;
			xe = x;
			if( !spanopen ) {
				spanopen = TRUE;
				xs = x;
			}
		}
		else
		if( spanopen ) {
			spanopen = FALSE;
			if( xe==xs ) {
				PIXELFILL( xs, y, C );
			}
			else {
				LINEFILL(xs,++xe,y);
			}
		}
		x++;
		pB++;
		z += dz;
	}
	if( spanopen ) {
		spanopen = FALSE;
		if( xe==xs ) {
			PIXELFILL( xs, y, C );
		}
		else {
			LINEFILL(xs,++xe,y);
		}
	}
}
#endif	// _ZPOLYVARIANT_

void API3D ZPoint(POINT p,Fixed z,COLORREF C)
{
	if( !pZB->gh )
		return;
	if( SetZB( pZB, p.x, p.y, z ) ) {
		PIXELFILL( p.x, p.y, C );
	}
}

#ifdef _ZPOLYVARIANT_

void API3D ZLine(POINT S0,POINT S1,Fixed DX,Fixed DY,pPoint3d P0,pPoint3d P1,COLORREF C)
{
	Fixed		z,dz;
	long _huge	*pB;
	long _huge	*zb;
	int			d,dx,dy,ax,ay,sx,sy,x,y;
	int			xMn,xMx,yMn,yMx;
	long		xRng;

#define ABS(a)		(((a)<0) ? -(a) : (a))
#define SGN(a)		(((a)<0) ? -1 : 1)

	if( !pZB->gh )
		return;

	if( S0.y > S1.y ) {
		POINT 		S = S0;
		pPoint3d	P = P0;
		S0 = S1; S1 = S;
		P0 = P1; P1 = P;
		DX = -DX;
		DY = -DY;
	}

    dx = S1.x-S0.x;
    dy = S1.y-S0.y;
	if( !dx && !dy ) {
		ZPoint( S0, distance(*P0), C );
		return;
	}
    ax = ABS(dx)<<1;
    ay = ABS(dy)<<1;
    sx = SGN(dx);
    sy = SGN(dy);

    x = S0.x;
    y = S0.y;
	z = distance(*P0);
    xMn = (int)pZB->xMn;
    xMx = (int)pZB->xMx;
    yMn = (int)pZB->yMn;
    yMx = (int)pZB->yMx;
    xRng= pZB->xRng;
    zb = pZB->zb;
    dz = distance(*P1) - z;

    if( ax > ay ) {	// x dominant
		d = ay-(ax>>1);
		dz = fixdiv( dz, DX );
		if( sx<0 ) dz = -dz;
		for(;;) {
			if(	(x >= xMn) && (x <= xMx)
			&&	(y >= yMn) && (y <= yMx) ) {
				pB	= zb + (y - yMn) * xRng + (x - xMn);
			    if( z <= *pB ) {
			    	*pB = z;
					PIXELFILL( x, y, C );
				}
			}
		    if (x==S1.x) return;
		    if (d>=0) {
				y += sy;
				d -= ax;
		    }
		    x += sx;
		    d += ay;
		    z += dz;
		}
    }
    else {			// y dominant
		d = ax-(ay>>1);
		dz = fixdiv( dz, DY );
		for(;; ) {
			if(	(x >= xMn) && (x <= xMx)
			&&	(y >= yMn) && (y <= yMx) ) {
				pB	= zb + (y - yMn) * xRng + (x - xMn);
			    if( z <= *pB ) {
			    	*pB = z;
					PIXELFILL( x, y, C );
				}
			}
		    if (y==S1.y) return;
		    if (d>=0) {
				x += sx;
				d -= ay;
		    }
		    y += sy;
		    d += ax;
		    z += dz;
		}
    }
}

void API3D ZPolyline(short nS,LPPOINT S,pPoint2d sp,pPoint3d P,COLORREF c)
{
	register short	i = nS;
	LPPOINT		s = S;
	pPoint2d	psp = sp;
	pPoint3d	p = P;

	while( --i ) {
		Fixed	dx = (psp+1)->x - psp->x;
		Fixed	dy = (psp+1)->y - psp->y;
		ZLine( *s, *(s+1), dx, dy, p, p+1, c );
		s++;
		psp++;
		p++;
	}
}

#else // not_ZPOLYVARIANT_

void API3D ZLine(POINT S0,POINT S1,pPoint3d P0,pPoint3d P1,COLORREF C)
{
	Fixed		z,dz;
	long _huge	*pB;
	long _huge	*zb;
	int			d,dx,dy,ax,ay,sx,sy,x,y;
	int			xMn,xMx,yMn,yMx;
	long		xRng;

#define ABS(a)		(((a)<0) ? -(a) : (a))
#define SGN(a)		(((a)<0) ? -1 : 1)

	if( !pZB->gh )
		return;

	if( S0.y > S1.y ) {
		POINT 		S = S0;
		pPoint3d	P = P0;
		S0 = S1; S1 = S;
		P0 = P1; P1 = P;
	}

    dx = S1.x-S0.x;
    dy = S1.y-S0.y;
	if( !dx && !dy ) {
		ZPoint( S0, distance(*P0), C );
		return;
	}
    ax = ABS(dx)<<1;
    ay = ABS(dy)<<1;
    sx = SGN(dx);
    sy = SGN(dy);

    x = S0.x;
    y = S0.y;
	z = distance(*P0);
    xMn = (int)pZB->xMn;
    xMx = (int)pZB->xMx;
    yMn = (int)pZB->yMn;
    yMx = (int)pZB->yMx;
    xRng= pZB->xRng;
    zb = pZB->zb;
    dz = distance(*P1) - z;

    if( ax > ay ) {	// x dominant
		d = ay-(ax>>1);
		dz = fixdiv( dz, LLSL( dx, 16 ) );
		if( sx<0 ) dz = -dz;
		for(;;) {
			if(	(x >= xMn) && (x <= xMx)
			&&	(y >= yMn) && (y <= yMx) ) {
				pB	= zb + (y - yMn) * xRng + (x - xMn);
			    if( z <= *pB ) {
			    	*pB = z;
					PIXELFILL( x, y, C );
				}
			}
		    if (x==S1.x) return;
		    if (d>=0) {
				y += sy;
				d -= ax;
		    }
		    x += sx;
		    d += ay;
		    z += dz;
		}
    }
    else {			// y dominant
		d = ax-(ay>>1);
		dz = fixdiv( dz, LLSL( dy, 16 ) );
		for(;; ) {
			if(	(x >= xMn) && (x <= xMx)
			&&	(y >= yMn) && (y <= yMx) ) {
				pB	= zb + (y - yMn) * xRng + (x - xMn);
			    if( z <= *pB ) {
			    	*pB = z;
					PIXELFILL( x, y, C );
				}
			}
		    if (y==S1.y) return;
		    if (d>=0) {
				x += sx;
				d -= ay;
		    }
		    y += sy;
		    d += ax;
		    z += dz;
		}
    }
}

void API3D ZPolyline(short nS,LPPOINT S,pPoint3d P,COLORREF c)
{
	register short	i = nS;
	LPPOINT		s = S;
	pPoint3d	p = P;

	while( --i ) {
		ZLine( *s, *(s+1), p, p+1, c );
		s++;
		p++;
	}
}
#endif // _ZPOLYVARIANT_

