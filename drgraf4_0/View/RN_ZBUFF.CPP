/*****************************************************************************
 *	File:		3dSolidsPgn.c
 *
 *	Purpose:	Renders hierarchical collections of faceted solids using
 *				ZBuffered hidden surface removal techniques.
 *
 *	Version:	Microsoft C / Windows
 *
 *	(C) 1994 Mark M. Owen. All rights reserved.
 *
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <OSINTF.h>
#include <Memory.h>
#include <3dClipng.h>
#include <3dSolidp.h>
#include <3dText.h>
#include <Render.h>
#include <Textures.h>
#include <statcurs.h>
#include <Antia.h>
#include <ZPoly.h>
#include <txudll.h>
#include <didc.h>

typedef struct FacetCell {
	pFPPoint3d		 pN;
	struct FacetCell __huge	*prior;
}
	FacetCell, __huge *pFacetCell;

typedef	pFacetCell __huge *apFacetCell;

#define	SFWASTE	8

typedef	struct TSortFacet {
	hPatch		hP;			// 4	handle to surface patch
	short		ixP;		// 2	index into patch array
	unsigned short ixF;		// 2	facet index hP[ixP] relative
	short		nIx;		// 2	facet geometry (# of indices)
	FPType		dist;		// 4	distance, centroid to viewer
	short		xfIx;		// 2	index of instance matrix
	FPPoint3d	centroid;	// 16	center point of facet
	FPPoint3d	normal;		// 16	perpendicular to the facet
	pFPPoint3d	pAVN;		// 4	array of vertex normals
	pFPPoint3d	pAVR;		// 4	array of raw vertices
	char		huge_waste[SFWASTE];// align to power of 2 boundary
}
	SortFacet, __huge *pSortFacet;


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

#define	FPFix(fx)				((fx)*0.0000152587890625F)
#define	P3dToFP3d(p3d,fp3d)		{(fp3d).x=FPFix((p3d).x);(fp3d).y=FPFix((p3d).y);(fp3d).z=FPFix((p3d).z);}

#define	HMEMCPY(f,t,s)	BlockMove((PMBLK)(f),(PMBLK)(t),(s))
#define	SFCOPY(f,t)		HMEMCPY((f),(t),sizeof(SortFacet)-SFWASTE)


extern HANDLE		ghInst;


static void			__near CacheRawVertices	(short,pVrtx,pFPPoint3d,pMatrix);
static void			__near TransformVertices(pFacet,pVrtx,pMatrix);
static OsErr		__near AddFacetCells	(pFacet,pFPPoint3d,pVrtx,apFacetCell);
static void			__near SetVertexNormals	(pFPPoint3d,short,apFacetCell);
static void			__near DepthSort		(pSortFacet,long);
static pSortFacet	__near allocPSF			(long,pSortFacet,long,long*);
static pMatrix		__near allocXF			(long,pMatrix,long,long*);
static BOOL			__near RenderPolyFacet	(HDC,pMatrix,pSortFacet,pLighting,pZBuffer);

/**********************************************************************************
 *
 *	Function:	CacheRawVertices
 *
 *	Purpose:	Given a set of coordinates for an patch, makes an instanced copy of
 *				the vertices for use in the rendering process, specifically for the
 *				texture mapping functions, which need to know the geometry of the
 *				patch before any viewer / perspective transformations are applied.
 *
 *				Storage for the copy is assumed to have been allocated by the
 *				calling function
 *
 **********************************************************************************
 */
static void	__near CacheRawVertices(
		short			nV,		//	number of vertices present in the arrays below
		pVrtx			pV,		//	array of Vrtx record entries
		pFPPoint3d 		pAVR,	//	array of instanced vertex coordinates (output)
		pMatrix			xf		//	instance transformation matrix
	)
{
	register
		long	i = nV;
	Point3d		p;

	while(i--) {
		p = pV[i].p;
		if( xf ) {	// transform sans translation
			Fixed	aX = p.x, aY = p.y, aZ = p.z;
			p.x	= fixmul( aX, xf->v[0][0] ) + fixmul( aY, xf->v[1][0] ) + fixmul( aZ, xf->v[2][0] );
			p.y	= fixmul( aX, xf->v[0][1] ) + fixmul( aY, xf->v[1][1] ) + fixmul( aZ, xf->v[2][1] );
			p.z	= fixmul( aX, xf->v[0][2] ) + fixmul( aY, xf->v[1][2] ) + fixmul( aZ, xf->v[2][2] );
		}
		P3dToFP3d( p, pAVR[i] );
	}
}

/**********************************************************************************
 *
 *	Function:	TransformVertices
 *
 *	Purpose:	Applies a transformation matrix to those elements of an array of
 *				Vrtx structure entries which have not yet been transformed and are
 *				used by a particular facet.  This function is intended to be used
 *				to apply a viewer transformation to the vertices (a process which
 *				occurs on demand, at various times if needed; hence the existance
 *				of the "impure" boolean in the Vrtx structure).
 *
 **********************************************************************************
 */
static void	__near TransformVertices(
		pFacet	pF,			/*	Facet which uses the vertices below				*/
		pVrtx	pV,			/*	array of Vrtx structure entries					*/
		pMatrix	xf			/*	transformation matrix to be applied				*/
	)
{
	register
		long 	i = pF->nIx;
	pVrtx		pv;

	while(i--) {
		pv = pV+(long)(pF->ixVrtx[i]);
		if( !pv->impure ) {
			ApplyTransform( (pPoint3d)&pv->p, (pPoint3d)&pv->p, xf );
			pv->impure = TRUE;
		}
	}
}

/**********************************************************************************
 *
 *	Function:	AddFacetCells
 *
 *	Purpose:	Maintains a list of normal vectors of those facets which share
 *				a given vertex.  In the process the facet's normal vector is
 *				calculated and returned to the caller.
 *
 *	Returns:	noErr if successfull; or MemError() if memory problems occur.
 *
 **********************************************************************************
 */
static OsErr __near AddFacetCells(
		pFacet		pF,		/*	pointer to the source facet						*/
		pFPPoint3d 	pN,		/*	container for the source facet's normal vector	*/
		pVrtx		pV,		/*	Vrtx array of the patch that owns this facet	*/
		apFacetCell	pFC		/*	linked list (stack) of facet normal vectors		*/
	)
{
	register
	unsigned short	i = pF->nIx;
	long			ix;
	pFacetCell		pFCtmp;
	FPPoint3d		a,b,c,p;
	Point3d			p3d;
	FPType			r;

	P3dToFP3d(pF->centroid,c);
	HMEMCPY( &pV[(long)pF->ixVrtx[1]].p, &p3d, sizeof(Point3d) );
	P3dToFP3d(p3d,p);
	a.x = p.x - c.x;
	a.y = p.y - c.y;
	a.z = p.z - c.z;
	HMEMCPY( &pV[(long)pF->ixVrtx[0]].p, &p3d, sizeof(Point3d) );
	P3dToFP3d(p3d,p);
	b.x = p.x - c.x;
	b.y = p.y - c.y;
	b.z = p.z - c.z;
	c.x	= (a.y*b.z)-(a.z*b.y);
	c.y	= (a.z*b.x)-(a.x*b.z);
	c.z	= (a.x*b.y)-(a.y*b.x);

	r = tSqrt( c.x*c.x + c.y*c.y + c.z*c.z );
	if( r!=0.0F ) {
		r = 1.0F/r;
		pN->x=c.x*r;
		pN->y=c.y*r;
		pN->z=c.z*r;
	}
	else
		HMEMCPY( &c, pN, sizeof(FPPoint3d) );

	/*	for each vertex of this facet add this facet's normal
	 *	to the vertex's list of such items
	 */
	while(i--) {
		if( !( pFCtmp = (pFacetCell)NewPtrClr(sizeof(FacetCell)) ) )
			return MemError();
		ix				= pF->ixVrtx[i];	/* select vertex index	*/
		pFCtmp->pN		= pN;				/* record this ->normal	*/
		pFCtmp->prior	= pFC[ix];
		pFC[ix]			= pFCtmp;
	}
	return noErr;
}

/**********************************************************************************
 *
 *	Function:	SetVertexNormals
 *
 *	Purpose:	Derives a normal vector at each vertex based on the average of
 *				the normal vectors of those facets which share the vertex.  The
 *				Vertex normal vectors are returned in a array assumed to have been
 *				allocated by the caller.
 *
 **********************************************************************************
 */
static void	__near SetVertexNormals(
		pFPPoint3d	pAVN,	/*	returned array of vertex normal vectors			*/
		short		nVN,	/*	number of elements allocated for the array		*/
		apFacetCell	pFC		/*	linked list (stack) of facet normal vectors		*/
	)
{
	pFacetCell		pFCell;
	FPType			VNx,VNy,VNz,r;
	pFPPoint3d		pN,pavn;
	pFacetCell		pFCprior;

	/*	For each vertex evaluate the list of facet normal's, attached
		and set the vertex normal to be their average.
	 */
	while( nVN-- ) {
		VNx = VNy = VNz = 0.0F;
		pFCell = pFC[(long)nVN];
		if( pFCell ) {
			while( pFCell ) {
				pN = pFCell->pN;
				VNx += pN->x;
				VNy += pN->y;
				VNz += pN->z;
				pFCprior = pFCell;
				pFCell = pFCell->prior;
				DisposPtr( pFCprior );
			}
			pavn = pAVN+(long)nVN;
			r = tSqrt( VNx*VNx + VNy*VNy + VNz*VNz );
			if( r ) {
				r = 1.0F / r;
				pavn->x = VNx*r;
				pavn->y = VNy*r;
				pavn->z = VNz*r;
			}
			else { // bad data
				pavn->x = VNx;
				pavn->y = VNy;
				pavn->z = VNz;
			}
		}
	}
}

/*****************************************************************************
 *
 *	Function:	DepthSort()
 *
 *	Purpose:	Sorts an array of facets into distance order.
 *
 *	Methods:	Adaptation of Shell-Metzner algorithm
 *
 *	Warnings:	Private Function.
 *
 *				Ascending sequence is used except for shadow processing, in
 *				which case, the descending sequence is used to correspond to
 *				the order in which RenderPolyList() processes the polygons.
 *				In the latter case, the effect is the same since the polygons
 *				have been pushed onto a stack, and RenderPolyList() pops them
 *				in reverse order, resulting in their being drawn in ascending
 *				order.  Note also that the ascending drawing sequence is an
 *				optimization related to Z buffer processing in that once the
 *				nearest pixels are drawn, processing of more distant pixels
 *				can be abbreviated.
 *
 *****************************************************************************
 */
static void	__near DepthSort(pSortFacet pSF,long n)
{
	register long	i,jump = n;
	Boolean			done = FALSE;
	SortFacet		temp;
	pSortFacet		pSFi,pSFj;
	Boolean			ascending = GetShadows() || GetAntiAliasing();

	if( ascending  )
		while( jump ) {
			jump=LLSR(jump,1);
			do {
				done = TRUE;
				for( i = 0, pSFi = pSF; i < (n-jump); i++, pSFi++ ) {
					pSFj = pSFi + jump;
					if(	 pSFi->dist > pSFj->dist ) {
						SFCOPY( pSFi, &temp );
						SFCOPY( pSFj, pSFi );
						SFCOPY( &temp, pSFj );
						done 	= FALSE;
					}
				}
			} while( !done );
		}
	else
		while( jump ) {
			jump=LLSR(jump,1);
			do {
				done = TRUE;
				for( i = 0, pSFi = pSF; i < (n-jump); i++, pSFi++ ) {
					pSFj = pSFi + jump;
					if(	 pSFi->dist < pSFj->dist ) {
						SFCOPY( pSFi, &temp );
						SFCOPY( pSFj, pSFi );
						SFCOPY( &temp, pSFj );
						done 	= FALSE;
					}
				}
			} while( !done );
		}
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
static pSortFacet __near allocPSF(
	long		need,
	pSortFacet	pSF,
	long		nInUse,
	long		*nAlloc
	)
{
	long		size,avail;
	pSortFacet	pSFtemp;

	if( pSF ) {	// accumulation in progress - grow the block if necessary
		avail = *nAlloc - nInUse;
		need = (avail < need)? need - avail : 0;
		if( need ) {
			*nAlloc += need;
			size = *nAlloc * (long)sizeof(SortFacet);
 			pSFtemp = (pSortFacet)NewPtr( size );
			if( pSFtemp ) {
				HMEMCPY( pSF, pSFtemp, nInUse*(long)sizeof(SortFacet) );
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
 *	Purpose:	Allocates storage for a transform matrix array.
 *
 *	Returns:	Pointer to block or nil if unsuccessfull
 *
 *	Warnings:	Private Function
 *				On failure to allocate, any prior allocations are disposed of.
 *
 *****************************************************************************
 */
#pragma optimize("",off)	// circumvent fatal error C1001: internal compiler error
static pMatrix	__near allocXF(
		long		need,	// quantity required
		pMatrix		pMat,	// current storage area
		long		nInUse,	// number of current area elements in use
		long		*nAlloc
	)
{
	long		size,avail;
	pMatrix		pMatTemp;

	if( pMat ) {	// accumulation in progress - grow the block if necessary
		avail = *nAlloc - nInUse;
		need = (avail < need)? need - avail : 0;
		if( need ) {
			*nAlloc += need;
			size = *nAlloc * (long)sizeof(Matrix);
			pMatTemp = (pMatrix)NewPtr( size );
			if( pMatTemp ) {
				HMEMCPY( pMat, pMatTemp, nInUse*(long)sizeof(Matrix) );
				DisposPtr( pMat );
			}
		}
		else
			pMatTemp = pMat;
	}
	else {
		pMatTemp = (pMatrix)NewPtr( (long)sizeof(Matrix) * need );
		*nAlloc	= need;
	}
	return pMatTemp;
}
#pragma optimize("",on)

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
static BOOL	__near RenderPolyFacet(
		HDC 		hDC,
		pMatrix		pXF,			/* viewer transformation matrix			*/
		pSortFacet	pSF,			/* sorted facet information				*/
		pLighting	pL,				/* ambient and point source light info	*/
		pZBuffer	pZB				/* target Z Buffer						*/
	)
{
	pPatch		pP;
	hVrtx		hV;
	pVrtx		pV,pv;
	hFacet		hF;
	pFacet		pF;
	long		i=0,ix,nIx;
	FPPoint3d	A[MAXFACETV], N[MAXFACETV], R[MAXFACETV];
	pFPPoint3d	pA=A, pN=N, pR=R;
	Point3d		p[MAXFACETV];
	pPoint3d	pp=p;
	Point2d		s[MAXFACETV];
	pPoint2d	ps=s;
	Point		S[MAXFACETV];
	pPoint		pS=S;
	hPGN		phFacet;
	Boolean		incomplete = FALSE;
	pRendAttr	RA;
	BOOL		interrupted = FALSE;

	/*	dereference the various handles for simplicity
	 */
	pP	= (pPatch)pSF->hP + (long)pSF->ixP;
	hV	= pP->hV;
	hF	= pP->hF;
	pV = (pVrtx)hV;
	pF = (pFacet)hF;
	RA = &pP->raOptions;

	//	this block is not really very useful for a zbuffered image since the
	//	characters rendered posess no actual depth information per se.
	//
 	if( RA->texture & TX_LABEL ) {
 		HFONT		hfOld;
		Matrix		cxf = xFormCombined;
		SetTextColor( hDC, RGBColor2CS(RA->frameColor) );
		SetBkMode( hDC, TRANSPARENT );
		switch( TX_ALIGNED(*RA) ) {
			case leftAlign:		SetTextAlign( hDC, TA_LEFT );	break;
			case rightAlign:	SetTextAlign( hDC, TA_RIGHT );	break;
			case centerAlign:	SetTextAlign( hDC, TA_CENTER );	break;
		}
		HMEMCPY( &pXF[pSF->xfIx], &xFormCombined, sizeof(Matrix) );
		if( TX_HFONT(*RA) )
			hfOld = SelectObject( hDC, TX_HFONT(*RA) );
		if( pF->refCon ) {	// marker character is in facet's refcon
			pv = pV + pF[pSF->ixF].ixVrtx[i];
			DrawString3d( pv->p.x,pv->p.y,pv->p.z, (char*)&pF->refCon );
		}
		else // label string is in the patch record
			DrawString3d( pV->p.x,pV->p.y,pV->p.z, TX_STRING(*RA) );
		if( TX_HFONT(*RA) ) {
			SelectObject( hDC, hfOld );
			if( !TX_BSTOCKFONT(*RA) )
				DeleteObject( TX_HFONT(*RA) );
		}
		xFormCombined = cxf;
		return InterruptEvent();
	}

	i	= nIx = pF[pSF->ixF].nIx;

	pp	+= i;
	pA	+= i;
	pN	+= i;
	pR	+= i;
	ps	+= i;
	pS	+= i;
	while( i-- ) {
		pp--;
		pA--;
		pN--;
		pR--;
		ps--;
		pS--;
		/*	Isolate the vertex index from the SortFacet entry
		 */
		ix = pF[pSF->ixF].ixVrtx[i];

		pv = &pV[ix];
		if( !pv->impure ) {
			/*	This vertex has not yet been transformed, do it now.
			 */
			ApplyTransform( &pv->p, &pv->p, &pXF[pSF->xfIx] );
			pv->impure = TRUE;
		}

		/*	Isolate the vertex
		 */
		HMEMCPY( &pv->p, pp, sizeof(Point3d) );
		P3dToFP3d(*pp,*pA);
		HMEMCPY( &pSF->pAVN[ix], pN, sizeof(FPPoint3d) );
		HMEMCPY( &pSF->pAVR[ix], pR, sizeof(FPPoint3d) );

		/*	On other than the last vertex in the polygon, check for
		 *	clipped visibility and terminate if not visible.
		 */
		if(i < nIx-1)	// not last
			incomplete = (Boolean)( ClipLine( pp, pp+1 ) == isnt_visible );
			if( incomplete )
				break;
		/*	Project to 2d space and convert to screen coordinates
		 */
		Project( pp, ps );
		pS->h = Fix2Int( ps->x );
		pS->v = Fix2Int( ps->y );
	}

	/*	Final visibility check in 2d space since perspective
	 *	projection will eliminate some facets from view.
	 */
	if( 	incomplete
		||	(	( nIx > 2 ) /* more complex than point or line */
			&&	( RA->normalVisibility?
					( nIx > 3 ?
						(	Invisible( s[0], s[1], s[2] )
						&&	Invisible( s[1], s[2], s[3] )
						&&	Invisible( s[2], s[3], s[0] )
						)
					:
						Invisible( s[0], s[1], s[2] )
					)
				:	FALSE
				)
			&& !GetShadows()	/* not cacheing for shadow usage */
			)
	  )
		return InterruptEvent();

	if( nIx < 3 && !GetShadows() ) {	/* point or line only and not shadowing */
		ZLine( *(POINT*)S, *(POINT*)(S+1), p, p+1, RGBColor2CS( RA->frameColor ) );
		return InterruptEvent();
	}

	/*	Create a polygon from the projected and clipped facet's
	 *	line segments, if possible.
	 */
	phFacet = NewPolygon(
				(int)nIx, S, pL, RA,
				pSF->dist, &pSF->centroid, &pSF->normal,
				A, N, R, pZB
			);

	if( phFacet ) {
		pPGN ppgn = (pPGN)phFacet;
		if( ppgn->p.polySize > sizeof(polygon) ) { /* data accumulated */
			if( GetShadows() || GetAntiAliasing() )	/* defer drawing */
				AddToPolyList( phFacet );
			else
			if( pL )							/* have lights mode... draw now	*/
				interrupted = RenderPolygon( phFacet, FALSE );
			else {	/* no lights... erase & frame only	*/
			//	ErasePoly( (PolyHandle)phFacet );
			//	FramePoly( (PolyHandle)phFacet );
				interrupted = InterruptEvent();
			}
		}
		if( !GetShadows() && !GetAntiAliasing() )
			KillPolygon( phFacet );
	}
	return interrupted;
}

/*****************************************************************************
 *
 *	Function:	xfRenderZBuffer
 *
 *	Purpose:	Controls the process of rendering a collection of groups of
 *				surface patches comprised of facets. Employs ZBuffer hidden
 *				surface removal techniques
 *
 *	Returns:	INVALID_REQUEST		if nil collection handle or matrix
 *				MEMORY_ALLOC_ERROR	if problems allocating memory
 *				noErr				if successful
 *				TRUE				if interrupted by interupt event
 *
 *****************************************************************************
 */
OsErr	API3D xfRenderZBuffer(
		HDC 		hDC,
		hCollection	hC,		/*	collection to be rendered			*/
		pMatrix		xf,		/*	viewer transformation matrix		*/
		pLighting	pL,		/*	ambient and point light sources		*/
		pZBuffer	pZB		/*	target Z buffer, caller supplied	*/
	)
{
	hGroup		hG;
	hPatch		hP;
	pPatch		pP,pPnP;
	hFacet		hF;
	pFacet		pF,pFnF;
	pVrtx		pV;
	DWORD		nS=0,nG,nP,nF,nV;
	long		nAllocSF= 0;
	long		nAllocXF= 0;
	SortFacet	SF;
	pSortFacet	pSF = NULL,psf;
	pRendAttr	RA;
	short		currentXF=0,nXF=0;
	pMatrix		pCXF,pXF	=NULL;
	apFacetCell	pFC;
	pFPPoint3d	pAVN,		/*	array of vertex normals	*/
				pAFN,		/*	array of facet normals	*/
				pAVR;		/*	array of raw vertices	*/
	long		ixpTD=0L;
	Handle		hapTD;
	Ptr			_huge *apTD;
	BOOL		interrupted = FALSE;
	BOOL		needSort = FALSE;

	if( !hC || !xf )
		return INVALID_REQUEST;

	nG = hC->nG;
	while( nG-- )
		if( (hC->hG)[nG] )
			ixpTD += ((pGroup)(hC->hG)[nG])->nP;
	hapTD = NewHandleClr( ixpTD * 3L * sizeof( Ptr _huge * ) );
	apTD = (Ptr _huge *)hapTD;
	ixpTD = 0;
	nG = hC->nG;
	while( nG-- && !interrupted ) {
		hG = (hC->hG)[nG];
		if( !hG )
			continue;
		if( !(hP = ((pGroup)hG)->hP) )
			continue;
		pP = (pPatch)hP;
		nP = ((pGroup)hG)->nP;
		if(!( pXF = allocXF( nP+1, pXF, nXF+1, &nAllocXF ) ) ) {
			DisposPtr( pSF );
			return MEMORY_ALLOC_ERROR;
		}

		HMEMCPY( xf, pXF, sizeof(Matrix) );

		while( nP-- && !interrupted ) {
			pPnP = pP+nP;
			hF = pPnP->hF;
			nV = pPnP->nV;
			if( !pPnP || !hF || !pPnP->hV || !nV )
				continue;
			RA	= &pPnP->raOptions;
			if( RA->transparency == 65535 ) // completely transparent
				continue;
			nF = pPnP->nF;
			if( !nF )
				continue;
			if( !( pSF = allocPSF( nF, pSF, nS, &nAllocSF ) ) )
				return MEMORY_ALLOC_ERROR;
			currentXF = 0;
			if( pPnP->instanced ) {
				mMult4x4( &pPnP->instanceXf, xf, &pXF[++nXF] );
				currentXF = nXF;
			}
			pCXF= &pXF[currentXF];

			pF = (pFacet)hF;
			pV = (pVrtx)pPnP->hV;

			pFC = (apFacetCell)NewPtrClr( (long)nV*sizeof(pFacetCell));
			pAVN= (pFPPoint3d) NewPtrClr( (long)nV*sizeof(FPPoint3d) );
			pAVR= (pFPPoint3d) NewPtrClr( (long)nV*sizeof(FPPoint3d) );
			pAFN= (pFPPoint3d) NewPtrClr( (long)nF*sizeof(FPPoint3d) );
			if( !pAVN || !pFC || !pAFN || !pAVR ) {
				DisposPtr( pAVR );
				DisposPtr( pAVN );
				DisposPtr( pFC );
				DisposPtr( pAFN );
				DisposPtr( pSF );
				DisposPtr( pXF );
				return MEMORY_ALLOC_ERROR;
			}

			CacheRawVertices( (short)nV, pV, pAVR, pPnP->instanced?&pPnP->instanceXf:0L );

			while( nF-- && !interrupted ) {
				pFnF = pF+nF;
				ApplyTransform( &pFnF->centroid, &pFnF->centroid, pCXF );
				TransformVertices( pFnF, pV, pCXF );
				AddFacetCells( pFnF, pAFN+nF, pV, pFC );
				P3dToFP3d( pFnF->centroid, SF.centroid );
				SF.dist	= tSqrt(SF.centroid.x*SF.centroid.x+SF.centroid.y*SF.centroid.y+SF.centroid.z*SF.centroid.z );
				SF.hP 	= hP;
				SF.ixP	= (short)nP;
				SF.ixF	= (unsigned short)nF;
				SF.nIx	= pFnF->nIx;
				SF.xfIx	= currentXF;
				SF.normal	= pAFN[nF];
				SF.pAVN	= pAVN;
				SF.pAVR	= pAVR;

				if( RA->transparency > 0 ) // draw transparent objects last
					SF.dist = 1000000-SF.dist;
				needSort |= ((RA->transparency > 0) || (RA->texture != TX_NONE));
				SFCOPY( &SF, pSF+nS );
				nS++;
			}
			SetVertexNormals( pAVN, (short)nV, pFC );
			DisposPtr( pFC );
			apTD[ixpTD++] = (Ptr)pAFN;
			apTD[ixpTD++] = (Ptr)pAVN;
			apTD[ixpTD++] = (Ptr)pAVR;
			interrupted = InterruptEvent();
		}
	}
	if( needSort )
		DepthSort( pSF, nS );
	psf = pSF + nS;
	nF	= nS;
	if( nF > 100 )
		SetStatusCursor( ghInst, 0.0F );
	nP	= nS / 8;
	while( nS-- && !interrupted ) {
		interrupted = RenderPolyFacet( hDC, pXF, --psf, pL, pZB );
		if( nF > 100 )
			if( !(nS%nP) )
				SetStatusCursor( ghInst, (nF-nS)/(float)nF );
	}
	DisposPtr( pSF );
	DisposPtr( pXF );
	while( ixpTD-- )
		DisposPtr( apTD[ixpTD] );
	DisposHandle( hapTD );
	PICTcleanup();
	UnloadUserDlls();
	return (OsErr)interrupted;
}

/*****************************************************************************
 *
 *	Function:	xfRenderCollectionPgn()
 *
 *	Purpose:	Controls the process of rendering a collection of groups of
 *				surface patches comprised of facets. Employs ZBuffer hidden
 *				surface removal techniques.
 *
 *	Returns:	INVALID_REQUEST		if nil collection handle or matrix
 *				MEMORY_ALLOC_ERROR	if problems allocating memory
 *				noErr				if successful
 *				TRUE				if interrupted by interupt event
 *
 *****************************************************************************
 */
OsErr	API3D xfRenderCollectionPgn(
		pRECT		pR,			//	active bitmap rectangle
		hCollection	hC,			//	collection to be rendered
		pMatrix		xf,			//	viewer transformation matrix
		pLighting	pL			//	ambient and point light source info
	)
{
	pZBuffer	pZB;
	OsErr		err;
	HDC 		hDC = GetCurrentDC();
	HCURSOR		saveCurs = SetCursor( LoadCursor( NULL, IDC_WAIT ) );
	BOOL		ZPolySet = StateZPoly();

	if( !ZPolySet )
	    if( InitZPoly( pR ) )
	    	return MEMORY_ALLOC_ERROR;

   	pZB = GetZPolyZB();

	if( InitRender(pR) != noErr ) {
		if( StateZPoly() && !ZPolySet )
			TermZPoly();	// if it was externally set we don't dispose of it
		return MEMORY_ALLOC_ERROR;
	}

	err = xfRenderZBuffer( hDC, hC, xf, pL, pZB );

	if( GetShadows() && !GetAntiAliasing() )
		RenderPolyList( FALSE );

	if( GetAntiAliasing() ) {
		RenderPolyList( FALSE );
		DIDC_CanGetPixel( TRUE );
		RenderPolyList( TRUE );
		DIDC_CanGetPixel( FALSE );
	}

	if( GetShadows() || GetAntiAliasing() )
		DisposePolyList();

	TermRender();	// new polygon fill implementation

	if( StateZPoly() && !ZPolySet )
		TermZPoly();	// if it was externally set we don't dispose of it

	SetCursor( saveCurs );

	return err;
}
