/*****************************************************************************
 *	File:		3dGrid.c
 *
 *	Purpose:	General purpose 3d wireframe gridwork, non hidden.
 *
 *	(C) 1990 Mark M. Owen.	All rights reserved.
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <OSINTF.h>
#include <3dGrid.h>
#include <3dXFDraw.h>

/*****************************************************************************
 *
 *	Function:	xfGrid()
 *
 *	Purpose:	General purpose 3d background gridwork.  Options provide for
 *				size limits, connector lines, line patterns, color, etc.
 *
 *****************************************************************************
 */
#pragma optimize("",off)
void	API3D xfGrid(pPoint3d min,pPoint3d max,pPoint3d steps,pGridOptions options,pMatrix xf)
{
	Point3d		step;
	Fixed		f,x,y,z;

	switch (options->gridPat) {
		case GP_WHITE:
			break;
		case GP_LTGRAY:
			break;
		case GP_GRAY:
			break;
		case GP_DKGRAY:
			break;
		case GP_BLACK:
			break;
		default:
			break;
	}
	step.x = fixdiv(max->x-min->x,steps->x);
	step.y = fixdiv(max->y-min->y,steps->y);
	step.z = fixdiv(max->z-min->z,steps->z);
	if (options->bottom||options->back||options->top||options->front)
		for(f=min->x;f<=max->x;f+=step.x) {
			if (options->bottom)
				xfDraw3dLine(f,min->y,min->z,f,min->y,max->z,xf); /* y const */
			if (options->back)
				xfDraw3dLine(f,min->y,max->z,f,max->y,max->z,xf); /* z const */
			if (options->top)
				xfDraw3dLine(f,max->y,min->z,f,max->y,max->z,xf); /* y const */
			if (options->front)
				xfDraw3dLine(f,min->y,min->z,f,max->y,min->z,xf); /* z const */
		}
	if (options->left||options->back||options->right||options->front)
		for(f=min->y;f<=max->y;f+=step.y) {
			if (options->left)
				xfDraw3dLine(min->x,f,min->z,min->x,f,max->z,xf); /* x const */
			if (options->back)
				xfDraw3dLine(min->x,f,max->z,max->x,f,max->z,xf); /* z const */
			if (options->right)
				xfDraw3dLine(max->x,f,min->z,max->x,f,max->z,xf); /* x const */
			if (options->front)
				xfDraw3dLine(min->x,f,min->z,max->x,f,min->z,xf); /* z const */
		}
	if (options->left||options->bottom||options->right||options->top)
		for(f=min->z;f<=max->z;f+=step.z) {
			if (options->left)
				xfDraw3dLine(min->x,min->y,f,min->x,max->y,f,xf); /* x const */
			if (options->bottom)
				xfDraw3dLine(min->x,min->y,f,max->x,min->y,f,xf); /* y const */
			if (options->right)
				xfDraw3dLine(max->x,min->y,f,max->x,max->y,f,xf); /* x const */
			if (options->top)
				xfDraw3dLine(min->x,max->y,f,max->x,max->y,f,xf); /* y const */
		}
	if(options->connectX||options->connectY||options->connectZ)
		switch (options->connectPat) {
			case GP_WHITE:		break;
			case GP_LTGRAY:		break;
			case GP_GRAY:		break;
			case GP_DKGRAY:		break;
			case GP_BLACK:		break;
		}
	if(options->connectX||options->connectZ) {
		for(y=min->y+step.y;y<max->y;y+=step.y) {
			if(options->connectX)
				for(z=min->z+step.z;z<max->z;z+=step.z)
					xfDraw3dLine(min->x,y,z,max->x,y,z,xf);
			if(options->connectZ)
				for(x=min->x+step.x;x<max->x;x+=step.x)
					xfDraw3dLine(x,y,min->z,x,y,max->z,xf);
		}
	}
	if(options->connectY)
		for(x=min->x+step.x;x<max->x;x+=step.x)
			for(z=min->z+step.z;z<max->z;z+=step.z)
				xfDraw3dLine(x,min->y,z,x,max->y,z,xf);
}

#define	FACETLINE(a,b,c,t,n,s) {\
		register int	i = (n);\
		ix[0] = ixV++;\
		pV[ix[0]].p.x = (a);\
		pV[ix[0]].p.y = (b);\
		pV[ix[0]].p.z = (c);\
		pV[ix[0]].impure = false;\
		while( i-- ){ \
			ix[1] = ixV++;\
			pV[ix[1]] = pV[ix[0]];\
			pV[ix[1]].p.##t += (s);\
			MakePolyFacet(&pF[ixF++],2,(pUInt)ix,pV);\
			ix[0] = ix[1];\
		}\
	}

#define	FACETLINEX(a,b,c,n,s)	FACETLINE((a),(b),(c),x,(n),(s))
#define	FACETLINEY(a,b,c,n,s)	FACETLINE((a),(b),(c),y,(n),(s))
#define	FACETLINEZ(a,b,c,n,s)	FACETLINE((a),(b),(c),z,(n),(s))

/*****************************************************************************
 *
 *	Function:	xfGrid2Patch()
 *
 *	Purpose:	General purpose 3d background gridwork.  Options provide for
 *				size limits, connector lines, line patterns, color, etc.
 *
 *****************************************************************************
 */
#pragma optimize("",off)
OsErr	API3D xfGrid2Patch(
	hGroup			hG,
	int				ixP,
	pPoint3d		min,
	pPoint3d		max,
	pPoint3d		steps,
	pGridOptions	options,
	pRendAttr		pRA,
	pMatrix			xf
	)
{
	Point3d		step;
	Fixed		f,x,y,z;
	pVrtx		pV;					/* Vertex working area				*/
	pFacet		pF;					/* Facet Working Array				*/
	int			nF=0,nV=0,			/* Number of facets and vertices	*/
				ixF=0,ixV=0;		/* Current facet and vertex indices	*/
	int			ix[2];				/* Index array for MakePolyFacet	*/
	int			nSX,nSY,nSZ;		/* steps per axis integer			*/
	int			nX,nY,nZ;
	OsErr		err;

	pRA->normalVisibility	= false; 		/* not practical for lines	*/
	if( pRA->R || pRA->G || pRA->B ) {
		pRA->frameColor.red	= pRA->R;	/* inherit frame color from	*/
		pRA->frameColor.green	= pRA->G;	/* whatever was specified	*/
		pRA->frameColor.blue	= pRA->B;	/* as the primary color		*/
	}
	nX = nSX = Fix2Int( steps->x );
	nY = nSY = Fix2Int( steps->y );
	nZ = nSZ = Fix2Int( steps->z );
	steps->x	= Int2Fix( nSX );
	steps->y	= Int2Fix( nSY );
	steps->z	= Int2Fix( nSZ );
	nX++;
	nY++;
	nZ++;
	if( options->top )
		nF += nX*nSZ + nSX*nZ;
	if( options->bottom )
		nF += nX*nSZ + nSX*nZ;
	if( options->left )
		nF += nY*nSZ + nSY*nZ;
	if( options->right )
		nF += nY*nSZ + nSY*nZ;
	if( options->front )
		nF += nX*nSY + nSX*nY;
	if( options->back )
		nF += nX*nSY + nSX*nY;
	nX-=2;
	nY-=2;
	nZ-=2;
	if( options->connectX )
		nF += nSX*nY*nZ;
	if( options->connectY )
		nF += nX*nSY*nZ;
	if( options->connectZ )
		nF += nX*nY*nSZ;
	nV = nF*2;
	pF = (pFacet)NewPtr( (long)sizeof(Facet) * nF);
	if( !pF )
		return MEMORY_ALLOC_ERROR;
	pV = (pVrtx)NewPtr( (long)sizeof(Vrtx) * nV );
	if( !pV ) {
		DisposPtr( (Ptr)pF );
		return MEMORY_ALLOC_ERROR;
	}
	step.x = fixdiv( max->x-min->x, steps->x );
	step.y = fixdiv( max->y-min->y, steps->y );
	step.z = fixdiv( max->z-min->z, steps->z );
	if( options->bottom || options->back || options->top || options->front )
		for( f=min->x;f<=max->x;f+=step.x ) {
			if( options->bottom )
				FACETLINEZ( f, min->y, min->z, nSZ, step.z );
			if( options->top )
				FACETLINEZ( f, max->y, min->z, nSZ, step.z );
			if( options->back )
				FACETLINEY( f, min->y, max->z, nSY, step.y );
			if( options->front )
				FACETLINEY( f, min->y, min->z, nSY, step.y );
		}
	if( options->left || options->back || options->right || options->front )
		for( f=min->y;f<=max->y;f+=step.y ) {
			if( options->left )
				FACETLINEZ( min->x, f, min->z, nSZ, step.z );
			if( options->right )
				FACETLINEZ( max->x, f, min->z, nSZ, step.z );
			if( options->back )
				FACETLINEX( min->x, f, max->z, nSX, step.x );
			if( options->front )
				FACETLINEX( min->x, f, min->z, nSX, step.x );
		}
	if( options->left || options->bottom || options->right || options->top )
		for( f=min->z;f<=max->z;f+=step.z ) {
			if( options->left )
				FACETLINEY( min->x, min->y, f, nSY, step.y );
			if( options->right )
				FACETLINEY( max->x, min->y, f, nSY, step.y );
			if( options->bottom )
				FACETLINEX( min->x, min->y, f, nSX, step.x );
			if( options->top )
				FACETLINEX( min->x, max->y, f, nSX, step.x );
		}
	if( options->connectX || options->connectZ ) {
		for( y = min->y + step.y; y < max->y; y += step.y ) {
			if( options->connectX )
				for( z = min->z + step.z; z < max->z; z += step.z )
					FACETLINEX( min->x, y, z, nSX, step.x );
			if( options->connectZ )
				for( x = min->x + step.x; x < max->x; x += step.x )
					FACETLINEZ( x, y, min->z, nSZ, step.z );
		}
	}
	if( options->connectY )
		for( x = min->x + step.x; x < max->x; x += step.x )
			for( z = min->z + step.z; z< max->z; z += step.z )
				FACETLINEY( x, min->y, z, nSY, step.y );

	err = NewPatch( hG, ixP, ixV, pV, ixF, pF, pRA, xf );
	DisposPtr( (Ptr)pF );
	DisposPtr( (Ptr)pV );
	return err;
}
#pragma optimize("",on)

/*****************************************************************************
 *
 *	Function:	xfLines2Patch()
 *
 *	Purpose:	General purpose 3d Line storage at patch/facet level.
 *
 *	Returns:	INVALID_REQUEST		if odd number of points and disjoint.
 *				MEMORY_ALLOC_ERROR	if any trouble allocating memory occurs.
 *
 *****************************************************************************
 */
OsErr	API3D xfLines2Patch(
	hGroup		hG,
	int			ixP,
	Boolean		disjoint,
	int			nPts,
	pPoint3d	pPt,
	pRendAttr	pRA,
	pMatrix		xf
	)
{
	pVrtx		pV;					/* Vertex working area				*/
	pFacet		pF;					/* Facet Working Array				*/
	int			nF=0,nV=0,			/* Number of facets and vertices	*/
				ixF=0,ixV=0;		/* Current facet and vertex indices	*/
	int			ix[2];				/* Index array for MakePolyFacet	*/
	OsErr		err;

	if( (nPts % 2) && disjoint )
		return	INVALID_REQUEST;

	pRA->normalVisibility	= false; 		/* not practical for lines	*/
	if( pRA->R || pRA->G || pRA->B ) {
		pRA->frameColor.red	= pRA->R;	/* inherit frame color from	*/
		pRA->frameColor.green	= pRA->G;	/* whatever was specified	*/
		pRA->frameColor.blue	= pRA->B;	/* as the primary color		*/
	}

	nF = (disjoint)? nPts/2 : nPts;

	nV = nPts;
	pF = (pFacet)NewPtr( (long)sizeof(Facet) * nF);
	if( !pF )
		return MEMORY_ALLOC_ERROR;
	pV = (pVrtx)NewPtr( (long)sizeof(Vrtx) * nV );
	if( !pV ) {
		DisposPtr( (Ptr)pF );
		return MEMORY_ALLOC_ERROR;
	}
	ixV = 0;
	while(ixV<nPts) {
		pV[ixV].p = pPt[ixV];
		pV[ixV].impure = false;
		ixV++;
	}

	if(disjoint) {
		ixV = 0;
		while(ixV<nPts) {
			ix[0] = ixV++;
			ix[1] = ixV++;
			MakePolyFacet(&pF[ixF++],2,(pUInt)ix,pV);
		}
	}
	else {
		ixV = 0;
		ix[0] = ixV++;
		while(ixV<nPts) {
			ix[1] = ixV++;
			MakePolyFacet(&pF[ixF++],2,(pUInt)ix,pV);
			ix[0] = ix[1];
		}
		ix[1] = 0;
		MakePolyFacet(&pF[ixF++],2,(pUInt)ix,pV);
	}

	err = NewPatch( hG, ixP, ixV, pV, ixF, pF, pRA, xf );
	DisposPtr( (Ptr)pF );
	DisposPtr( (Ptr)pV );
	return err;
}
