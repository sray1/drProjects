// CDrClip.cpp : implementation of the CClip class
//

#include "stdafx.h"
///////////////////
#include "DrClip.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CDrClip,CObject,1)
/////////////////////////////////////////////////////////////////////////////
// CDrClip

/*
BEGIN_MESSAGE_MAP(CDrClip,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDrClip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
/*****************************************************************************
 *	purpose:	PERSPECTIVE: Canonical View Volume in 3D(Not Homogeneous)	
 *				Implements point and line clipping by a near (hither=zMin),
 *				far (yon = -1) and top, bottom,left and right  planes of
 *				a right pyramid wedge.
 *
 *	        	PARALLEL: Canonical View Volume in 3D(Not Homogeneous)	
 *				Implements point and line clipping by a near (hither=0),
 *				far (yon = -1) and top, bottom,left and right  planes of
 *				a right Cube.
 *
 *****************************************************************************
 */
/////////////////////
#define	ABOVE  0x0001
#define	BELOW  0x0002
#define	RIGHT  0x0004
#define	LEFT   0x0008
#define	BACK   0x0010
#define	FRONT  0x0020

#define	ISABOVE(k)	((k)&ABOVE)
#define	ISBELOW(k)	((k)&BELOW)
#define	ISRIGHT(k)	((k)&RIGHT)
#define	ISLEFT(k)	((k)&LEFT)
#define ISBACK(k)	((k)&BACK)
#define	ISFRONT(k)	((k)&FRONT)
//////////////////////////////////////////////////////////////
CDrClip::CDrClip()
{
}

CDrClip::~CDrClip()
{
}

CDrClip::CDrClip(double dzMin, BOOL bPer, BOOL bCanon)
{
	m_dzMin 	= dzMin;
	m_bPer		= bPer;
	m_bCanon 	= bCanon;
}

void CDrClip::PushUp(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane y=z(bPer=true) or y=-1 (the BOTTOM clipplane).
*				z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dy;
	dy = E->y - S->y;
	if(m_bPer)                     					// Perspective
	{
		t 	= ( S->z - S->y)/( dy - (E->z - S->z) );
		r.y	= S->y + t * dy ;
		r.z	= r.y;
	}	
	else 											// Parallel
	{
		t 	= -( 1. + S->y)/dy;
		r.y = -1.;
		r.z	= S->z + t * ( E->z - S->z ) ;
	}	
	//////////////////////////////////
	r.x	= S->x + t * ( E->x - S->x ) ;
	////////
	*S	= r;
}

void CDrClip::PushDown(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane y=-z(bPer=true) or y=-1 (the TOP clipplane).
*					z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dy;
	dy = E->y - S->y;
	if(m_bPer)                     					// Perspective
	{
		t 	= -( S->z + S->y)/( dy + (E->z - S->z) );
		r.y	= S->y + t * dy ;
		r.z	= -r.y;
	}	
	else 											// Parallel
	{
		t 	= ( 1. - S->y)/dy;
		r.y = 1.;
		r.z	= S->z + t * ( E->z - S->z ) ;
	}	
	//////////////////////////////////
	r.x	= S->x + t * ( E->x - S->x ) ;
	////////
	*S	= r;
}

void CDrClip::PushRight(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane x=z(bPer=true) or x=-1 (the LEFT clipplane).
*					z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dx;
	dx = E->x - S->x;
	if(m_bPer)                     					// Perspective
	{
		t 	= ( S->z - S->x)/( dx - (E->z - S->z) );
		r.x	= S->x + t * dx ;
		r.z	= r.x;
	}	
	else 											// Parallel
	{
		t 	= -( 1. + S->x)/dx;
		r.x = -1.;
		r.z	= S->z + t * ( E->z - S->z ) ;
	}	
	//////////////////////////////////
	r.y	= S->y + t * ( E->y - S->y ) ;
	////////
	*S	= r;
}

void CDrClip::PushLeft(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane x=-z(bPer=true) or x=1 (the RIGHT clipplane).
*					z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dx;
	dx = E->x - S->x;
	if(m_bPer)                     					// Perspective
	{
		t 	= -( S->z + S->x)/( dx + (E->z - S->z) );
		r.x	= S->x + t * dx ;
		r.z	= -r.x;
	}	
	else 											// Parallel
	{
		t 	= ( 1. - S->x)/dx;
		r.x = 1.;
		r.z	= S->z + t * ( E->z - S->z ) ;
	}	
	//////////////////////////////////
	r.y	= S->y + t * ( E->y - S->y ) ;
	////////
	*S	= r;
}

void CDrClip::PushFront(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane z=-1(bPer=true) or z=-1 (the BACK clipplane).
*					z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dz;
	dz = E->z - S->z;
	///////////////////
	t 	= -( 1. + S->z)/dz;
		r.x	= S->x + t * ( E->x - S->x ) ;
		r.z = -1.;
		r.y	= S->y + t * ( E->y - S->y ) ;
	//////////////////////////////////
	*S	= r;
}

void CDrClip::PushBack(pWORLD S,pWORLD E)
/*****************************************************************************
*	purpose:	moves the start point of a line segment to its intercept
*				with the plane z=zMin(bPer=true) or z=0 (the FRONT clipplane).
*					z is ALWAYS NEGATIVE in TRANSFORMED Space
*****************************************************************************/
{
	WORLD		r;
	//////////////
	double		t,dz;
	dz = E->z - S->z;
	if(m_bPer)                     					// Perspective
	{
		t 	= ( m_dzMin - S->z )/dz;
		r.z	= m_dzMin;
	}	
	else 											// Parallel
	{
		t 	= - S->z/dz;
		r.z	= 0.;
	}	
	//////////////////////////////////
	r.x	= S->x + t * ( E->x - S->x ) ;
	r.y	= S->y + t * ( E->y - S->y ) ;
	/////////
	*S	= r;
}

void CDrClip::Push(WORD cb,pWORLD p1,pWORLD p2)
/*****************************************************************************
*	purpose:	based on the start point's location pushes the point to
*				the appropriate clipping plane.
*****************************************************************************/
{
	if(ISBACK(cb))PushFront(p1,p2);
	else
	if(ISFRONT(cb))PushBack(p1,p2);
	else
	if(ISABOVE(cb))	PushDown(p1,p2);
	else
	if(ISBELOW(cb))	PushUp(p1,p2);
	else
	if(ISRIGHT(cb))	PushLeft(p1,p2);
	else
	if(ISLEFT(cb))	PushRight(p1,p2);
}

WORD CDrClip::ClipEncode(pWORLD p)
/*****************************************************************************
*	purpose:	classifies a point's location relative to the six clipping
*				planes.
*
*	method:		based on Cohen-Sutherland algorithm.
*
*****************************************************************************/
{
	register WORD	cb = 0;

	if(m_bPer)
	{
		if( m_bCanon ) 
		{
			////////////////////////////
			if( p->x < p->z )	cb |= LEFT;
			else
			if( p->x > -p->z )	cb |= RIGHT;
			////////////////////////////
			if( p->y > -p->z )	cb |= ABOVE;
			else
			if( p->y < p->z )	cb |= BELOW;
			////////////////////////////
		}	
		if( p->z < -1.)	cb |= BACK;
		else
		if( p->z > m_dzMin ) cb |= FRONT;
		/////////////////////////////////
	}
	else
	{
		if( m_bCanon ) 
		{
			////////////////////////////
			if( p->x < -1.)	cb |= LEFT;
//			else
			if( p->x > 1.)	cb |= RIGHT;
			////////////////////////////
			if( p->y > 1.)	cb |= ABOVE;
//			else
			if( p->y < -1.)	cb |= BELOW;
			//////////////////////////// 
		}	
		if( p->z < -1.)	cb |= BACK;
//		else
		if( p->z > 0.) cb |= FRONT;
		/////////////////////////////////
	}
	//////////
	return cb;
}

VISIBILITY CDrClip::ClipLine_SC(pWORLD startPt,pWORLD endPt)
/*****************************************************************************
*	purpose:	determines if a line segment intersects the Canonical View Vol,
*				and if so clips it to the view volume, if necessary.
*
*	warning:	it is expected that the start and end points have been
*				transformed prior to calling "ClipLine".
*****************************************************************************/
{
	register WORD	s = ClipEncode( startPt );
	register WORD	e = ClipEncode( endPt );
	short			i = 5;

	if( !(s | e) )
		return VI_YES_VISIBLE;

	if( s & e )
		return VI_NOT_VISIBLE;

	while( i-- )
	{
		if( s ) 
		{
			Push( s, startPt, endPt );
			s = ClipEncode( startPt );
		}
		else
		if( e ) 
		{
			Push( e, endPt, startPt );
			e = ClipEncode( endPt );
		}

		if( !(s | e) )
			return VI_YES_VISIBLE;

		if( s & e )
			return VI_NOT_VISIBLE;
	}
	return VI_NOT_VISIBLE;
}

VISIBILITY CDrClip::ClipPt(pWORLD Pt)
/*****************************************************************************
*	purpose:	determines if a points lies within the Canonical View Volume.
*
*	warning:	it is expected that the point has been transformed prior to
*				calling "ClipPt".
*****************************************************************************/
{
	return (VISIBILITY)(!ClipEncode( Pt ));
}

VISIBILITY CDrClip::ClipLine_LB(pWORLD pS,pWORLD pE)
//////////////////////////////////////////////////////////////////////
//		FOR NOW ONLY DONE FOR PERSPECTIVE CANONICAL VIEW VOLUME     //
//		todo: FOR PARALLEL CANONICAL VIEW VOLUME                    //
/*****************************************************************************
*	purpose:	determines if a line segment intersects the Canonical View Vol,
*				and if so clips it to the view volume, if necessary.
*
*	warning:	it is expected that the start and end points have been
*				transformed prior to calling "ClipLine".
*	
*	method:		Liang-Barsky Parametric Clipping Algorithm
*****************************************************************************/
{
	double tmin,tmax,dx,dy,dz;
	/////////////////////////////
	tmin 	= 0.;
	tmax 	= 0.;
	dx		= pE->x - pS->x;
	dz		= pE->z - pS->z; 
	////////////////////////
	if( ClipPt_LB(-dx-dz,pS->x+pS->z,&tmin,&tmax) )					//Right side
	/////////////////////////////////////////////
	{
		if( ClipPt_LB(-dx-dz,pS->x+pS->z,&tmin,&tmax) )				//Left side
		/////////////////////////////////////////////
		{	//If get this far, part of line is in -z<=x<=z
			dy = pE->y - pS->y;
		    ///////////////////
			if( ClipPt_LB(-dy-dz,-pS->y+pS->z,&tmin,&tmax) )			//Bottom
			/////////////////////////////////////////////
			{
				if( ClipPt_LB(-dy-dz,-pS->y+pS->z,&tmin,&tmax) )		//Top
				/////////////////////////////////////////////
				{//If get this far, part of line is in -z<=x<=z,-z<=y<=z
					if( ClipPt_LB(-dz,pS->z-m_dzMin,&tmin,&tmax) )	//Front
					/////////////////////////////////////////////
					{
					/////////////////////////////////////////////
						if( ClipPt_LB(dz,-pS->z-1,&tmin,&tmax) )		//Back
						/////////////////////////////////////////////
						{//If get this far, part of line is visiblein
						 //  -z<=x<=z,-z<=y<=z,-1<=z<=zMin
			             	if(tmax<1.)
			             	{//end pt (t=1) is not in the region,
			             	 //compute intersection
			             	 	pE->x = pS->x + tmax*dx;
			             	 	pE->y = pS->y + tmax*dy;
			             	 	pE->z = pS->z + tmax*dz;
								//////////////////////		
								return VI_YES_VISIBLE;
							}	
			             	if(tmin>0.)
			             	{//start pt (t=0) is not in the region,
			             	 //compute intersection
			             	 	pS->x = pS->x + tmin*dx;
			             	 	pS->y = pS->y + tmin*dy;
			             	 	pS->z = pS->z + tmin*dz;
								//////////////////////		
								return VI_YES_VISIBLE;
							}	
		                }
					}
				}
			}
		}
	}
	////////////////////					
	return VI_NOT_VISIBLE;
}

BOOL CDrClip::ClipPt_LB(double denom,double num,double* pdtE,double* pdtL)
/*****************************************************************************
*	purpose:	determines if a points lies within the Canonical View Volume.
*
*	warning:	it is expected that the point has been transformed prior to
*				calling "ClipPt".
*	
*	method:		Liang-Barsky Parametric Clipping Algorithm
*****************************************************************************/
{

	double t;
	BOOL bAccept = TRUE;
	////////////////////	
	if(denom>0.)					//PE intersection
	{                                
		t = num/denom;              //t at intersection
		//////////////
		if(t>(*pdtL))					//tE and tL crossover
			return bAccept = FALSE;	//prepare to reject line
		else
		if(t>(*pdtE))					//a new tE has been found
			*pdtE = t;
	}
	else
	if(denom<0.)					//PL intersection
	{                                
		t = num/denom;              //t at intersection
		//////////////
		if(t<(*pdtE))					//tE and tL crossover
			return bAccept = FALSE;	//prepare to reject line
		else
		if(t<(*pdtL))					//a new tL has been found
			*pdtL = t;
	}
	else
	if(num>0.)						//Line on outside of edge
		return bAccept = FALSE;		//prepare to reject line
	///////////////////////////
	return bAccept;			 	 

}

void CDrClip::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" CDrClip:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" CDrClip:    Loading\n");	// TODO: add loading code here
	}
		
}
//////////////////////////// end of module ///////////////////
