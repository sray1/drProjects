/*****************************************************************************
 *	File:		Solids.c
 *
 *	Purpose:	Renders hierarchical collections of faceted solids
 *
 *	Version:	Microsoft C / Windows
 *
 *	(C) 1994 Mark M. Owen. All rights reserved.
 *
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <OSINTF.h>
#include <3dClipng.h>
#include <3dSolids.h>
#include <3dText.h>
#include <statcurs.h>
#include <BackRef.h>
#include <CLUTS.h>				// Accretion Palette
#include <Contours.h>			// Contour line drawing
#include <ZPoly.h>
#include <memory.h>


#define	SFWASTE	15

typedef	struct TSortFacet {
	hPatch		hP;					// 4 handle to surface patch
	int			ixG;				// 2 index into group array
	int			ixP;				// 2 index into patch array
	unsigned int ixF;				// 2 facet index hP[ixP] relative
	char		nIx;				// 1 facet geometry (# of indices)
	Fixed		dist;				// 4 distance, centroid to viewer
	int			xfIx;				// 2 index of instance MATRIX
	char		huge_waste[SFWASTE];// align to power of 2 boundary
}
	SortFacet,	__huge *pSortFacet;

/*
 *	Explanation of the visibility checking macros:
 *	----------- -- --- ---------- -------- -------
 *
 *	given 3 co-planar points a, b and c the two macros below
 *	are derived from the following sequence of operations:
 *
 *	using point a as the origin calculate two vectors in the
 *	plane thereby represented:
 *
 *	Îx = b.x - a.x;
 *	Îy = b.y - a.y;
 *	Îz = b.z - a.z;
 *
 *	ÎX = c.x - a.x;
 *	ÎY = c.y - a.y;
 *	ÎZ = c.z - a.z;
 *
 *	the plane's normal vector N would be:
 *
 *	N.x = Îy*ÎZ - ÎY*Îz;
 *	N.y = ÎX*Îz - Îx*ÎZ;
 *	N.z = Îx*ÎY - ÎX*Îy;
 *
 *	however, since the viewer normal V is [0,0,-1], we
 *	can simplify the above to Îx*Îy - ÎX*ÎY because:
 *
 *		0	 = N.x * V.x
 *		0	 = N.y * V.y
 *		-N.z = N.z * V.z
 *
 *	and the dot product of V˘N is equal to -N, the sum
 *	of the above components.
 *
 *	since our viewer normal V is [0,0,-1] rather than
 *	a line of sight from the facet to the viewer, the
 *	a facet is visible if the dot product Û 0, and is
 *	invisible otherwise.
 */
#define	Visible(a,b,c)\
		(	(	fixmul( ( (b).x-(a).x ) , ( (c).y-(a).y ) )\
			-	fixmul( ( (c).x-(a).x ) , ( (b).y-(a).y ) )\
			)\
			<= f_0\
		)
#define	Invisible(a,b,c) !Visible((a),(b),(c))

#define	MEMCPY(f,t,s)	BlockMove((PMBLK)(f),(PMBLK)(t),(s))
#define	SFCOPY(f,t)		MEMCPY((f),(t),sizeof(SortFacet)-SFWASTE)
#define	Point2d2Point(SRC,DST) (DST)->h = Fix2Int( (SRC)->x ); (DST)->v = Fix2Int( (SRC)->y );
#define	SUBPT3D(a,b,c) {(c).x=(a).x-(b).x;(c).y=(a).y-(b).y;(c).z=(a).z-(b).z;}

extern HANDLE		ghInst;

static void			__near DepthSort		(pSortFacet,long);
static pSortFacet	__near allocPSF			(long,pSortFacet,long,long*);
static pMATRIX		__near allocXF			(long,pMATRIX,long,long*);
#ifdef _ZPOLYVARIANT_
static void			__near MinimizePoly		(pPoint p,pInt nP,pPoint3d p3d,pPoint2d p2d);
#else
static void			__near MinimizePoly		(pPoint p,pInt nP,pPoint3d p3d);
#endif	// _ZPOLYVARIANT_
static void			__near RenderPolyFacet	(HDC,pMATRIX,pSortFacet,pLighting,Boolean);


/*****************************************************************************
 *
 *	Function:	DepthSort()
 *
 *	Purpose:	Sorts an array of facets into ascending distance order.
 *
 *	Methods:	Adaptation of Shell-Metzner algorithm
 *
 *	Warnings:	Private Function
 *
 *****************************************************************************
 */
static void	__near DepthSort(pSortFacet pSF,long n)
{
	register long	i,jump = n;
	Boolean			done = false;
	SortFacet		temp;
	pSortFacet		pSFi,pSFj;

	if( ZPoly )
	while( jump ) {
		jump=LLSR(jump,1);
		do	{
			done = true;
			for( i = 0, pSFi = pSF; i < (n-jump); i++, pSFi++ ) {
				pSFj = &pSF[i + jump];
				if(	 pSFi->dist < pSFj->dist ) {
					SFCOPY( pSFi, &temp );
					SFCOPY( pSFj, pSFi );
					SFCOPY( &temp, pSFj );
					done 	= false;
				}
			}
		} while( !done );
	}
    else
	while( jump ) {
		jump=LLSR(jump,1);
		do	{
			done = true;
			for( i = 0, pSFi = pSF; i < (n-jump); i++, pSFi++ ) {
				pSFj = &pSF[i + jump];
				if(	 pSFi->dist > pSFj->dist ) {
					SFCOPY( pSFi, &temp );
					SFCOPY( pSFj, pSFi );
					SFCOPY( &temp, pSFj );
					done 	= false;
				}
			}
		} while( !done );
	}
}

/****************************************************************************
 *
 *	Function:	Distance()
 *
 *	Purpose:	Calculates the magnitude of a vector.
 *
 *	Returns:	Fixed Point magnitude of vector.
 *
 *****************************************************************************
 */
Fixed	API3D Distance(pPoint3d c)
{
	return (Fixed)tSqrt((FPType)c->x*c->x+(FPType)c->y*c->y+(FPType)c->z*c->z);
}

/*****************************************************************************
 *
 *	Function:	allocPSF()
 *
 *	Purpose:	Allocates storage for SortFacet array entries.
 *
 *	Returns:	Pointer to block or nil if unsuccessfull
 *
 *	Warnings:	Private Function
 *				On failure to allocate, any prior allocations are disposed of.
 *
 *****************************************************************************
 */
static pSortFacet	__near allocPSF(
	long		need,
	pSortFacet	pSF,
	long		nInUse,
	long		*nAlloc
	)
{
	long		size,avail;
	pSortFacet	pSFtemp;

	if( pSF ) {	/* accumulation in progress - grow the block if necessary */
		avail = *nAlloc - nInUse;
		need = (avail < need)? need - avail : 0;
		if( need ) {
			*nAlloc += need;
			size = *nAlloc * (long)sizeof(SortFacet);
			pSFtemp = (pSortFacet)NewPtr( size );
			if( pSFtemp ) {
				MEMCPY( pSF, pSFtemp, nInUse*(long)sizeof(SortFacet) );
				DisposPtr( (Ptr)pSF );
			}
		}
		else
			pSFtemp = pSF;
	}
	else {
		pSFtemp = (pSortFacet)NewPtr( (long)sizeof(SortFacet) * need );
		*nAlloc	= need;
	}
	return pSFtemp;
}

/*****************************************************************************
 *
 *	Function:	allocXF()
 *
 *	Purpose:	Allocates storage for a transform MATRIX array.
 *
 *	Returns:	Pointer to block or nil if unsuccessfull
 *
 *	Warnings:	Private Function
 *				On failure to allocate, any prior allocations are disposed of.
 *
 *****************************************************************************
 */
#pragma optimize("",off)	// circumvent fatal error C1001: internal compiler error
static pMATRIX  __near allocXF(
	long	need,
	pMATRIX	pMat,
	long	nInUse,
	long	*nAlloc
	)
{
	long	size,avail;
	pMATRIX	pMatTemp;

	if( pMat ) {/* accumulation in progress - grow the block if necessary */
		avail = *nAlloc - nInUse;
		need = (avail < need)? need - avail : 0;
		if( need )	{
			*nAlloc += need;
			size = *nAlloc * (long)sizeof(MATRIX);
			pMatTemp = (pMATRIX)NewPtr( size );
			if( pMatTemp ) {
				MEMCPY( pMat, pMatTemp, nInUse*(long)sizeof(MATRIX) );
				DisposPtr( (Ptr)pMat );
			}
		}
		else
			pMatTemp = pMat;
	}
	else {
		pMatTemp = (pMATRIX)NewPtr( (long)sizeof(MATRIX) * need );
		*nAlloc	= need;
	}
	return pMatTemp;
}
#pragma optimize("",on)

#ifdef _ZPOLYVARIANT_

static void	__near MinimizePoly(pPoint p,pInt nP,pPoint3d p3d,pPoint2d p2d)
{
	Point	P[2*MAXFACETV];
	Point3d	P3D[2*MAXFACETV];
	Point2d	P2D[2*MAXFACETV];
	int		in=1, out=0;

	*P = *p;
	*P3D = *p3d;
	*P2D = *p2d;
	while( in++ < (int)*nP )
		if( *((long*)&p[in]) != *((long*)&P[out]) ) {
			P[++out] = p[in];
			P3D[out] = p3d[in];
			P2D[out] = p2d[in];
		}
	*nP = out;
	MEMCPY( P, p, sizeof(Point) * out );
	MEMCPY( P3D, p3d, sizeof(Point3d) * out );
	MEMCPY( P2D, p2d, sizeof(Point2d) * out );
}

#else // not _ZPOLYVARIANT_

static void	__near MinimizePoly(pPoint p,pInt nP,pPoint3d p3d)
{
	Point	P[2*MAXFACETV];
	Point3d	P3D[2*MAXFACETV];
	int		in=1, out=0;

	*P = *p;
	*P3D = *p3d;
	while( in++ < (int)*nP )
		if( *((long*)&p[in]) != *((long*)&P[out]) ) {
			P[++out] = p[in];
			P3D[out] = p3d[in];
		}
	*nP = out;
	MEMCPY( P, p, sizeof(Point) * out );
	MEMCPY( P3D, p3d, sizeof(Point3d) * out );
}
#endif // _ZPOLYVARIANT_

/*****************************************************************************
 *
 *	Function:	RenderPolyFacet()
 *
 *	Purpose:	Controls the process of rendering a polygonal facet.  Wire
 *				frame only, points and lines are drawn here.  Area filled
 *				facets are drawn by ColorRgn.
 *
 *	Warnings:	Private Function
 *
 *****************************************************************************
 */
static void	__near RenderPolyFacet(
	HDC 		hDC,
	pMATRIX		pXF,
	pSortFacet	pSF,
	pLighting	pL,
	Boolean		bWireFrameOnly
	)
{
	pPatch			pP;
	pVrtx			pV,pcV;
	pFacet			pF;
	int				i,j,k, nIx;
	Point3d			p[2*MAXFACETV],
					a,b,N, centroid,rawC,
					Rp[1+MAXFACETV];
	pPoint3d		pp,pRp=Rp;
	Point2d			s[2*MAXFACETV];
	pPoint2d		ps;
	Point			S[2*MAXFACETV];
	pPoint			pS;
	pRendAttr		pRA;
	pMATRIX			pxf = pXF + pSF->xfIx;
	HBRUSH			hbColor;
	HANDLE			hoOld;
	LOGBRUSH		lb;
	HPEN			hp, hpOld;
	HFONT			hfOld;
	BOOL			contours = Contouring();

	pP	= (pPatch)pSF->hP + pSF->ixP;
	pV	= (pVrtx)(pP->hV);
	pF	= (pFacet)(pP->hF) + pSF->ixF;
	pRA	= &pP->raOptions;
    //////////////////////////////////////////////////////////////////
	if( pRA->texture & TX_LABEL ) {
		MATRIX	cxf = xFormCombined;
		SetTextColor( hDC, RGBColor2CS(pRA->frameColor) );
		SetBkMode( hDC, TRANSPARENT );
		switch( TX_ALIGNED(*pRA) ) {
			case leftAlign:		SetTextAlign( hDC, TA_LEFT );	break;
			case rightAlign:	SetTextAlign( hDC, TA_RIGHT );	break;
			case centerAlign:	SetTextAlign( hDC, TA_CENTER );	break;
		}
		MEMCPY( (PMBLK)pxf, (PMBLK)(&xFormCombined), sizeof(MATRIX) );
		if( TX_HFONT(*pRA) )
			hfOld = SelectObject( hDC, TX_HFONT(*pRA) );
		if( pF->refCon ) {	// marker character is in facet's refcon
			pcV = pV + pF->ixVrtx[0];
			DrawString3d( pcV->p.x,pcV->p.y,pcV->p.z, (char*)&pF->refCon );
		}
		else // label string is in the patch record
			DrawString3d( pV->p.x,pV->p.y,pV->p.z, TX_STRING(*pRA) );
		if( TX_HFONT(*pRA) ) {
			SelectObject( hDC, hfOld );
			if( !TX_BSTOCKFONT(*pRA) )
				DeleteObject( TX_HFONT(*pRA) );
		}
		xFormCombined = cxf;
		return;
	}
    //////////////////////////////////////////////////////////////
	nIx = pF->nIx;
	i = j = k = 0;
	pcV = &pV[pF->ixVrtx[0]];
	if( !contours ) 
	{
		if( !pcV->impure ) 
		{
			ApplyTransform( &pcV->p, &pcV->p, pxf );
			pcV->impure = true;
		}
		a = pcV->p;
		while( ++i < nIx ) 
		{
			pcV = pV + pF->ixVrtx[i];
			if( !pcV->impure ) 
			{
				ApplyTransform( &pcV->p, &pcV->p, pxf );
				pcV->impure = true;
			}
			b = pcV->p;
			pp = p+j;
			*pp++ = a;
			*pp = b;
			pp = p+k;
			if( ClipLine( pp, pp+1 ) ) {
				Project( pp, ps=s+k );
				pS = S+k;
				Point2d2Point( ps, pS );
				Project( ++pp, ++ps );
				pS++;
				Point2d2Point( ps, pS );
				k+=2;
				j+=2;
			}
			a = b;
		}
		b = pV[pF->ixVrtx[0]].p;
	}
	else {
		*pRp++ = pcV->p;
		ApplyTransform( &pcV->p, &a, pxf );
		while( ++i < nIx ) {
			pcV = pV + pF->ixVrtx[i];
			*pRp++ = pcV->p;
			ApplyTransform( &pcV->p, &b, pxf );
			pp = p+j;
			*pp++ = a;
			*pp = b;
			pp = p+k;
			if( ClipLine( pp, pp+1 ) ) {
				Project( pp, ps=s+k );
				pS = S+k;
				Point2d2Point( ps, pS );
				Project( ++pp, ++ps );
				pS++;
				Point2d2Point( ps, pS );
				k+=2;
				j+=2;
			}
			a = b;
		}
		pcV = pV + pF->ixVrtx[0];
		*pRp++ = pcV->p;
		ApplyTransform( &pcV->p, &b, pxf );
	}
    // end new transformer loop dealing with separate contour case
	pp = p+j;
	*pp++ = a;
	*pp = b;
	pp = p+k;
	if( ClipLine( pp, pp+1 ) ) {
		Project( pp, ps=s+k );
		pS = S+k;
		Point2d2Point( ps, pS );
		Project( ++pp, ++ps );
		pS++;
		Point2d2Point( ps, pS );
		k+=2;
		j+=2;
	}
    ///////////////////////////////////////////////////////////////
	rawC = pF->centroid;

	//	Final visibility check in 2d space since perspective
	//	projection will eliminate some facets from view.

	if(		( nIx > 2 ) // more complex than point or line
		&&	( pRA->normalVisibility?
				( nIx>3?
					(	Invisible( s[0], s[2], s[4] )
					&&	Invisible( s[2], s[4], s[6] )
					&&	Invisible( s[4], s[6], s[0] )
					)
				:
					Invisible( s[0], s[2], s[4] )
				)
			: false
			)
	  )
		return;
    ////////////////////////////////////////////////////////////////
	if( pRA->transparency > 0 )
		SetROP2( hDC, R2_MERGEPEN );

	if(	nIx < 3 )	{	// point or line only
		if( ZPoly ) {
#ifdef _ZPOLYVARIANT_
			Fixed	dx = (s+1)->x - s->x;
			Fixed	dy = (s+1)->y - s->y;
			ZLine( *(LPPOINT)S, *(LPPOINT)(S+1), dx, dy, p, p+1, RGBColor2CS( pRA->frameColor ) );
#else
			ZLine( *(LPPOINT)S, *(LPPOINT)(S+1), p, p+1, RGBColor2CS( pRA->frameColor ) );
#endif	// _ZPOLYVARIANT_
		}
		else {
			HPEN	hp,hpOld;
			if( pRA->texture & TX_LINES ) {
				hp		= CreatePen( PS_SOLID, TX_PENSIZE(*pRA), RGBColor2CS( pRA->frameColor ) );
				hpOld	= SelectObject( hDC, hp );
				MoveTo( hDC, S[0].h, S[0].v );
				LineTo( hDC, S[1].h, S[1].v );
				SelectObject( hDC, hpOld );
				DeleteObject( hp );
			}
			else {
				if( pRA->refconPen && pF->refCon != NULL )
					hp = (HPEN)(pF->refCon);	// warning C4759 is OK
				else 
					hp = CreatePen( PS_SOLID, 1, RGBColor2CS( pRA->frameColor ) );
				hpOld = SelectObject( hDC, hp );
				MoveTo( hDC, S[0].h, S[0].v );
				LineTo( hDC, S[1].h, S[1].v );
				SelectObject( hDC, hpOld );
				if( !(pRA->refconPen && pF->refCon!=NULL ) )
					DeleteObject( hp );
			}
		}
		if( pRA->transparency > 0 )
			SetROP2( hDC, R2_COPYPEN );
		return;
	}
    ////////////////////////////////////////////////////////////////
#ifdef _ZPOLYVARIANT_
	MinimizePoly( S, &k, p, s );
#else
	MinimizePoly( S, &k, p );
#endif // _ZPOLYVARIANT_
    if( k < 3 ) {
		if( pRA->transparency > 0 )
			SetROP2( hDC, R2_COPYPEN );
		return;
    }

	/*	If light sources are present and WireFrameOnly drawing has
	 *	not been requested we'll do the complete rendering.
	 *	Otherwise, we may just draw the wire frame (see below).
	 */
	if( pL && !bWireFrameOnly ) {
		//	Transform the facet's centroid to viewer space
		ApplyTransform( &pF->centroid, &centroid, pxf );

		//	Compute the facet's normal vector at the centroid
		SUBPT3D( p[1], centroid, a );
		SUBPT3D( p[0], centroid, b );
		N.x	= fixmul(a.y,b.z)-fixmul(b.y,a.z);
		N.y	= fixmul(b.x,a.z)-fixmul(a.x,b.z);
		N.z	= fixmul(a.x,b.y)-fixmul(b.x,a.y);

		//	use ColorRgn to evaluate the lighting effects on the facet.
		hbColor = ColorRgn(
					centroid, N,
					(ZPoly&&pRA->transparency)? f_32000-pSF->dist : pSF->dist,
					pRA, pL
				);
	}
	else //	use background color for hidden surface wireframe fill
		hbColor = CreateSolidBrush( GetBkColor( hDC ) );

	hoOld	= SelectObject( hDC, hbColor );
	GetObject( hbColor, sizeof(LOGBRUSH), (LPSTR)&lb );
	//////////////////////////////////////////////////////////////////////
	AddBackRef( (short)pSF->ixG, (short)pSF->ixP, pSF->ixF, (short)k, (POINT*)S, lb.lbColor );	// BACKREF

	if( pF->refCon && !pRA->refconPen ) {
		pREFCON3D	prc3d =(pREFCON3D)pF->refCon;
		BOOL		rslt;
		prc3d->pP	= pP;			// patch reference
		prc3d->pF	= pF;			// facet reference
		prc3d->c	= lb.lbColor;	// our derived color
		prc3d->nS	= (short)k;		// number of 2d points present
		MEMCPY( S, prc3d->S, k * sizeof(POINT) );
		rslt = prc3d->cb3d( prc3d );
		if( rslt ) {				// callback said we are finished
		    AccretePaletteEntry( prc3d->c );// accrete the callback's color
			SelectObject( hDC, hoOld );
			DeleteObject( hbColor );
			return;
		}
	}

    AccretePaletteEntry( lb.lbColor );
    //////////////////////////////////////////////////////////////////
	if( bWireFrameOnly != -1 && !pRA->wireframed ) {
	    if( ZPoly )
#ifdef _ZPOLYVARIANT_
	    	ZPolygon( (short)k-1, (LPPOINT)S, s, p, lb.lbColor, pRA->framed?RGBColor2CS( pRA->frameColor ):lb.lbColor );
#else
	    	ZPolygon( (short)k-1, (LPPOINT)S, p, lb.lbColor );
#endif	// _ZPOLYVARIANT_
		else {
			hp		= CreatePen( PS_NULL, 0, lb.lbColor );
			hpOld	= SelectObject( hDC, hp );
			SetPolyFillMode( hDC, WINDING );
			Polygon( hDC, (LPPOINT)S, (int)k );
			SelectObject( hDC, hpOld );
			DeleteObject( hp );
	    }
    }

	SelectObject( hDC, hoOld );
	DeleteObject( hbColor );

	if( pRA->framed
	||	bWireFrameOnly==1
	||	pRA->wireframed
	||	(bWireFrameOnly==-1 && !contours)	)
		if( ZPoly ) {
#ifdef _ZPOLYVARIANT_
			if( !pRA->framed || pRA->wireframed || bWireFrameOnly )
				ZPolyline( (short)k, (LPPOINT)S, s, p, RGBColor2CS( pRA->frameColor ) );
#else
			ZPolyline( (short)k, (LPPOINT)S, p, RGBColor2CS( pRA->frameColor ) );
#endif	// _ZPOLYVARIANT_
		}
		else {
			COLORREF	c = RGBColor2CS( pRA->frameColor );
			if( pRA->refconPen && pF->refCon != NULL )
				hp = (HPEN)(pF->refCon);	// warning C4759 is OK
			else 
				hp = CreatePen( PS_SOLID, 1, c );
			hpOld = SelectObject( hDC, hp );
		    AccretePaletteEntry( c );
			Polyline( hDC, (LPPOINT)S, (int)k );
			SelectObject( hDC, hpOld );
			if( !(pRA->refconPen && pF->refCon!=NULL ) )
				DeleteObject( hp );
		}

	if( contours )
		if( nIx == 3 )
			DrawContours( Rp, nIx, pxf );
		else
			TriangulateContours( Rp, nIx, &rawC, pxf );

	if( pRA->transparency > 0 )
		SetROP2( hDC, R2_COPYPEN );
}

/*****************************************************************************
 *
 *	Function:	xfRenderGroup()
 *
 *	Purpose:	Controls the process of rendering a group of surface patches
 *				comprised of facets.
 *
 *	Returns:	INVALID_REQUEST		if nil group handle or transform MATRIX
 *				MEMORY_ALLOC_ERROR	if problems allocating memory
 *				noErr				if successful or interrupted by events
 *
 *****************************************************************************
 */
OsErr	API3D xfRenderGroup(
	hGroup		hG,
	pMATRIX		xf,
	pLighting	pL,
	Boolean		bWireFrameOnly
	)
{
	long		nS = 0, nP, nF, currentXF=0, nXF=0;
	HDC 		hDC;
	hPatch		hP;
	pPatch		pP;
	hFacet		hF;
	pFacet		pF;
	long		nAllocSF= 0;
	long		nAllocXF= 0;
	pSortFacet	pSFbase	= NULL;
	pSortFacet	pSF;
	pMATRIX		pXF	= NULL;
	pRendAttr	pRA;
	Boolean		interrupted = FALSE;
 	HCURSOR		saveCurs= SetCursor( LoadCursor( NULL, IDC_WAIT ) );
 	BOOL		needSort = !ZPoly && bWireFrameOnly != -1;

	if( !hG || ! xf )
		return INVALID_REQUEST;

	PurgeBackRefs();

	nP = hG->nP;
	if(!( pXF = allocXF( nP+1, pXF, nXF+1, &nAllocXF ) ) )
		return	MEMORY_ALLOC_ERROR;

	MEMCPY( (PMBLK)xf, (PMBLK)pXF, sizeof(MATRIX) );

	while( nP-- && !interrupted ) {
		hP = hG->hP;
		if( !hP )
			continue;
		pP = (pPatch)hP + nP;
		pRA	= &pP->raOptions;
		nF = pP->nF;
		if( !( pSFbase = allocPSF( nF, pSFbase, nS, &nAllocSF ) ) )
			return	MEMORY_ALLOC_ERROR;
		hF = pP->hF;
		if( !hF || !pP->hV )
			continue;

		currentXF = 0;
		if( pP->instanced ) {
			mMult4x4( &pP->instanceXf, xf, &pXF[++nXF] );
			currentXF = nXF;
		}

		pF = (pFacet)hF + nF;
		interrupted = InterruptEvent();
		while( nF-- && !interrupted ) {
			Point3d		c = (--pF)->centroid;
			ApplyTransform( &c, &c, &pXF[currentXF] );

			if( ClipPt( &c ) == is_visible ) {
				pSF			= &pSFbase[nS++];
				pSF->dist	= Distance( &c );
				pSF->hP 	= hP;
				pSF->ixG	= -1;		// since we don't know
				pSF->ixP	= (int)nP;
				pSF->ixF	= (unsigned int)nF;
				pSF->nIx	= (char)pF->nIx;
				pSF->xfIx	= (int)currentXF;
				if( ZPoly && pRA->transparency ) {
					pSF->dist = f_32000-pSF->dist;
					needSort = TRUE;
				}
			}
		}
	}

	if( !interrupted ) {
		if( needSort )
			DepthSort( pSFbase, nS );
		hDC = GetCurrentDC();
		pSF = pSFbase + nS;
		nF	= nS;
		if( nF > 100 )
			SetStatusCursor( ghInst, 0.0F );
		nP	= nS / 8;
		while( nS--  && !interrupted ) {
			RenderPolyFacet( hDC, pXF, --pSF, pL, bWireFrameOnly );
			if( nF > 100 )
				if( !(nS%nP) )
					SetStatusCursor( ghInst, (nF-nS)/(float)nF );
			interrupted = InterruptEvent();
		}
	}
    SetCursor( saveCurs );
	DisposPtr( (Ptr)pSFbase	);
	DisposPtr( (Ptr)pXF );

	return noErr;
}

/*****************************************************************************
 *
 *	Function:	RenderScene()
 *
 *	Purpose:	Controls the process of rendering a Scene of Objects with
 *				groups of surface patches comprised of facets.
 *
 *	Returns:	INVALID_REQUEST		if nil collection handle or MATRIX
 *				MEMORY_ALLOC_ERROR	if problems allocating memory
 *				noErr				if successful
 *
 *****************************************************************************
 */
int	CPainter::RenderScene
				(
//					pDrObject	pObject,
					pMATRIX		xf,		// View Matrix
					pLighting	pL,
					Boolean		bWireFrameOnly
	)
{
	long		nS = 0, nG, nP, nF;
    HDC 		hDC;
	hGroup		hG;
	hPatch		hP;
	pPatch		pP;
	hFacet		hF;
	pFacet		pF;
	long		nAllocSF	= 0;
	long		nAllocXF	= 0;
	pSortFacet	pSFbase		= NULL;
	pSortFacet	pSF;
	int			currentXF	= 0;
	pMATRIX		pXF			= NULL;
	int			nXF			= 0;
	HCURSOR		saveCurs;
	pRendAttr	pRA;
	Boolean		interrupted = FALSE;
 	BOOL		needSort = !ZPoly && bWireFrameOnly != -1;

	if( !hC || !xf )
		return INVALID_REQUEST;

	PurgeBackRefs();
    ////////////////////////////////////////////////////////////
	saveCurs = SetCursor( LoadCursor( NULL, IDC_WAIT ) );
    ////////////////////////////////////////////////////////////
	nG = hC->nG;
	while( nG--  && !interrupted ) 
	{
		hG = (hC->hG)[nG];
		if( !hG )
			continue;
		nP = hG->nP;
		///////////////////////////////////////
		if(!( pXF = allocXF( nP+1, pXF, nXF+1, &nAllocXF ) ) ) {
			DisposPtr( (Ptr)pSFbase	);
			return	MEMORY_ALLOC_ERROR;
		}
		MEMCPY( (PMBLK)xf, (PMBLK)(pXF), sizeof(MATRIX) );
		/////////////////////////////////////////////////////////// Patch
		while( nP--  && !interrupted ) 
		{
			if( !(hP = hG->hP) )
				continue;
			pP = (pPatch)hP + nP;
			hF = pP->hF;
			if( !hF || !pP->hV )
				continue;
			pRA	= &pP->raOptions;
			nF = pP->nF;
			if( !( pSFbase	= allocPSF( nF, pSFbase, nS, &nAllocSF ) ) )
				return	MEMORY_ALLOC_ERROR;
			currentXF = 0;
			if( pP->instanced ) {
				mMult4x4( &pP->instanceXf, xf, &pXF[++nXF] );
				currentXF = nXF;
			}
			pF = (pFacet)hF + nF;
			interrupted = InterruptEvent();
			////////////////////////////////////////////////////// Facet
			while( nF-- && !interrupted ) {
				Point3d c = (--pF)->centroid;
				ApplyTransform( &c, &c, &pXF[currentXF] );
				if( ClipPt( &c ) == is_visible ) {
					pSF 		= &pSFbase[nS++];
					pSF->dist	= Distance( &c );
					pSF->hP 	= hP;
					pSF->ixG	= (int)nG;
					pSF->ixP	= (int)nP;
					pSF->ixF	= (unsigned int)nF;
					pSF->nIx	= (char)pF->nIx;
					pSF->xfIx	= currentXF;
					if( ZPoly && pRA->transparency ) {
						pSF->dist = f_32000-pSF->dist; // draws last
						needSort = TRUE;
					}
				}
			}
		}
	}
	///////////////////////////////////////////////////////////
	if( !interrupted ) {
		if( needSort )
			DepthSort( pSFbase, nS );
		hDC = GetCurrentDC();
		pSF = pSFbase + nS;
		nF	= nS;
		if( nF > 100 )
			SetStatusCursor( ghInst, 0.0F );
		nP	= nS / 8;
		while( nS--  && !interrupted ) { // draw back to front
			RenderPolyFacet( hDC, pXF, --pSF, pL, bWireFrameOnly );
			if( nF > 100 )
				if( !(nS%nP) )
					SetStatusCursor( ghInst, (nF-nS)/(float)nF );
			interrupted = InterruptEvent();
		}
	}
	///////////////////////////////////////////////////
	SetCursor( saveCurs );
	DisposPtr( (Ptr)pSFbase	);
	DisposPtr( (Ptr)pXF );

	return noErr;
}
