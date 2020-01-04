/*****************************************************************************
 *	File:		Render.c
 *
 *	Purpose:	ZBuffer Rendering Functions.
 *****************************************************************************
 */
#include "stdafx.h"
#include <math.h>                  
#include <limits.h>	//INT_MAX
/////////////////////////////
#include "DrGraf.h"
#include "DrGraDoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
////////////////////////// ElementLevel
#include "Def_Elem.h"	// Patch/Curve
#include "DrNode.h"
#include "DrFE2D.h"
/////////////////////
#include "Textures.h"
//#include "Alias.h"
#include "Light.h"
#include "ZBuffer.h"

//#include "globals.h"
#include "Def_Rend.h"
///////////////////
#include "Render.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// C3DMath

IMPLEMENT_SERIAL(CRender,CObject,1)
/*
BEGIN_MESSAGE_MAP(CRender,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CRender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CRender::CRender()
{
}
///////////////////////////////////////////////////////////// 
/*
//#include <limits.h>
//#include <3dextrn.h>
//#include <statcurs.h>
//#include <txudll.h>
//#include <didc.h>
*/
//////////////////////////////////////////////////////////
//short			nPolys	= 0;
//pPolyList		pPL		= 0L;		//	list of active polygons for shadow
short			MINH,MAXH,MINV,MAXV;
//hPGN			phCurrent;
////////////////////////////////////////////////////////////////////////
#define	MINMAX					0x80007FFF
//////////////////////////////////////////////////////
#define ABS(a)					(((a)<0) ? -(a) : (a))
#define SGN(a)					(((a)<0) ? -1 : 1)
#define	INC(a,b)				{(a).x+=(b).x;(a).y+=(b).y;(a).z+=(b).z;}
#define	DELTADOUBLE(d,a,b,r)	(d)=((b)-(a))*(r);
#define DELTAWORLD(d,a,b,r)		{DELTADOUBLE((d).x,(a).x,(b).x,(r));\
								 DELTADOUBLE((d).y,(a).y,(b).y,(r));\
								 DELTADOUBLE((d).z,(a).z,(b).z,(r));}
#define	OFFSET(a,d,o)			{(a).x+=(d).x*(o);(a).y+=(d).y*(o);(a).z+=(d).z*(o);}
#define	DISTANCE(c)				sqrt((c).x*(c).x+(c).y*(c).y+(c).z*(c).z);
#define DOTPRODUCT(a,b)			(a).x*(b).x+(a).y*(b).y+(a).z*(b).z
#define	CLIPCOLOR(c)			((c)>1.0)?1.0:(((c)<0)?0:(c))
#define	MAX(A,B)				(((A)>(B))?(A):(B))
#define MIN(A,B)				(((A)<(B))?(A):(B))
/////////////////////////////////////////////////////////////////////////
/*
#define	BoxMinMax(c,box,a,b)	if((a).##c<(b).##c){(box).min.c=(a).##c;(box).max.c=(b).##c;}else{(box).min.c=(b).##c;(box).max.c=(a).##c;}
#define	BoxIntersects(a,b)\
			(	MAX((a).min.x,(b).min.x)<=MIN((a).max.x,(b).max.x)\
			&&	MAX((a).min.y,(b).min.y)<=MIN((a).max.y,(b).max.y)\
			&&	MAX((a).min.z,(b).min.z)<=MIN((a).max.z,(b).max.z)\
			)
#define	PointInBox(p,b)\
		(	(p).x>=(b).min.x && (p).y>=(b).min.y && (p).z>=(b).min.z\
		&&	(p).x<=(b).max.x && (p).y<=(b).max.y && (p).z<=(b).max.z\
		)

#define	MEMCPY(f,t,s)	BlockMove((PMBLK)(f),(PMBLK)(t),(s))
*/
//////////////////////////////////////////////////////////////////////
int CRender::Init(CRect* pClientRect, pLTENVIRON pLE)
{

	///////////////////////////////////////////////// ScanLines
	InitScan(pClientRect->Height());
	///////////////////////////////////////////////// Z-Buffer
	m_pZB->InitZB
			(
				pClientRect->left,
				pClientRect->top,
				pClientRect->right,
				pClientRect->bottom
			);
	///////////////////////////////////////////////// Light Environment
	m_pLE 			= pLE;
	///////////////////////////////////////////////// AntiAlias/Shadow
												   // Rendering Attribs	
	m_pRA 			= NULL;
	m_bAntiAliasOn 	= FALSE;
	m_bShadowOn		= FALSE;
    m_bAscending	= FALSE;
	m_dHither		= 0.0;	//Canonical View Volume 
	m_dYon			= -1.0; //Needed for ZBuffer Comparison/Clipping
	/////////
	return 0;
}

int CRender::InitScan(int yMax)
{

	register short	i = yMax;
	///////////////////////////////////////////////// ScanLines
	if(!(m_pScanSpan = new SCANSPAN[i]) )
		return -2;					// Memory Error
   	/////////////////
	while( i-- ) 
	{
		*((DWORD*)m_pScanSpan) = MINMAX;
		m_pScanSpan++;
		/////////////////
	}
	return 0;
}
		
void CRender::TermRender(void)
{
	if(m_pScanSpan)
		delete [] m_pScanSpan;
		
}

/**********************************************************************************
 *
 *	Function:	SetShadows
 *
 *	Purpose:	Sets the shadows global variable to indicate if shadow rendering is
 *				to be performed. Shadow rendering must be selected prior to calling
 *				xfRenderCollectionPgn if shadows are to be generated.
 *
 **********************************************************************************
 */
void CRender::SetShadow(BOOL state)
{
	m_bShadowOn 	= state;
	m_bAscending 	|= m_bShadowOn;
}

/**********************************************************************************
 *
 *	Function:	IsShadowOn
 *
 *	Returns:	the state of the shadows global variable.
 *
 **********************************************************************************
 */
BOOL CRender::IsShadowOn(void)
{
	return	m_bShadowOn;
}

/**********************************************************************************
 *
 *	Function:	SetAntiAliasing
 *
 *	Purpose:	Sets the antiAliasing global variable to indicate if edge pixels
 *				should be blended in with the background as they are drawn.
 *
 **********************************************************************************
 */
void CRender::SetAntiAlias(Boolean state)
{
	m_bAntiAliasOn 	= state;
	m_bAscending 	|= m_bAntiAliasOn;
}

/**********************************************************************************
 *
 *	Function:	IsAntiAliasingOn
 *
 *	Returns:	the state of the antiAliasing global variable.
 *
 **********************************************************************************
 */
BOOL CRender::IsAntiAliasingOn(void)
{
	return m_bAntiAliasOn;
}

/**********************************************************************************
 *
 *	Function:	AddToPolyList
 *
 *	Purpose:	Adds a polygon with data extension to the list of active polygons,
 *				provided memory can be allocated.
 *
 **********************************************************************************
 */
void CRender::AddToPolyList(CDrObject* pObject)
{
	m_pPolyList->AddTail(pObject);		
}

/**********************************************************************************
 *
 *	Function:	DisposePolyList
 *
 *	Purpose:	Disposes of all polygon with data extensions in the list of active
 *				polygons.
 *
 **********************************************************************************
 */
void CRender::DisposePolyList(void)
{
/*
	pPolyList ppl = pPL,pplt;

	while( ppl ) {
		KillPolygon( ppl->ph );
		pplt = ppl;
		ppl = ppl->prior;
		DisposPtr( (Ptr)pplt );
	}
	pPL = 0L;
	nPolys = 0;
*/	
}

/**********************************************************************************
 *
 *	Function:	RenderPolyList 
 *
 *	Purpose:	Renders all polygons for SHADOW
 *
 **********************************************************************************
 */
void CRender::RenderPolyList(BOOL bEdgesOnly)
{
/*
	int		n = 0;
	int		nP;
	BOOL	bInterrupted = FALSE;
	/////////////////////////////
    int nPolys = m_pPolyList->GetCount();
    ////////////////////////////////////////////
	if( nPolys > 100 ) 
	{
		SetTimeStatusCursor( 0.0F );
		nP = nPolys / 8;
	}
	///////////////////////////////////////////////////////////////////
	for (POSITION pos = m_pPolyList->GetFirstObjectPos();pos !=NULL;)
	{

		CDrObject* pObject 	= m_pPolyList->GetNextObject(pos);
		/////////////////////////////////////////	
		if( bInterrupted ) 
			return;
		//////////////////////////////////////////////////	
		bInterrupted = RenderPolygon_FULL( pPoly, bEdgesOnly );
		//////////////////////////////////////////////////				
		if( nPolys > 100 ) 
		{
			if( !(n%nPoly) )
				SetTimeStatusCursor( ((float)n)/nPolys );
			n++;
		}
	}
*/	
}


/**********************************************************************************
 *
 *	Function:	RenderPolygon_FULL
 *
 *	Purpose:	Determines if an extended polygon is visible, and if so sets up any
 *				texture mapping parameters and reduces the polygon to an edge list.
 *				The edge list is then processed, rendering the pixels of each scan
 *				line.  Throughout the process, the handle to the extended polygon
 *				remains locked.  It is then unlocked just prior to exit from this
 *				function.
 *
 *	Returns:	NOERR if successful; or MemError() if a memory problem occurs
 *				or TRUE if bInterrupted by an interrupt event.
 *
 **********************************************************************************
 */
int CRender::RenderPolygon_FULL(CClientDC* pDC,CDrObject* pPoly,BOOL bEdgesOnly)
{
	BOOL		bInterrupted = FALSE;
    /////////////////////////////////
	if( !pPoly )
		return 0;
    ////////////////////////////////////////////////////// Z-Buffer Clip
	if(ClippedByZBuffer(pPoly) )
		return 0;
/*
    ////////////////////////////////////////////////////// Back Culling
//   should be done elsewhere beforehand     todo
	if( m_pRA->Culling && !m_bCullWorld )						 
	{ 
		if (m_pView->CullScreenPoly_ONE(pPoly) )
		{
			pPoly->SetCulled(TRUE);
			return 0;
		}	
	}
*/	
    //////////////////////////////////////////////////////
//	phCurrent = ph; = pPoly;         later for shadow todo
    ////////////////////////////////////////////////////// Valid Polygon
	////////////////////////////////////// Build EdgeList.
	BuildEdgeList(pPoly,bEdgesOnly);
	////////////////////////////////////// Antialias the Edges
	if( m_bAntiAliasOn && bEdgesOnly ) 
		////////////////////////////////// 
		bInterrupted = DoAntiAliasing();
		////////////////////////////////
	else 
	{	
		////////////////////////////////// Go Render	
		m_Textures.Init(m_pRA, m_pLE);   
		bInterrupted = RenderScanLines(pDC);
		m_Textures.Terminate(m_pRA, m_pLE);
		//////////////////////////////////   
	}
	//////////////////////////
	return (int)bInterrupted;
}


BOOL CRender::RenderScanLines(CClientDC* pDC)
{

	BOOL bInterrupted;
	pSCANSPAN   pss = m_pScanSpan;
	///////////////////////////////////////////// Draw the scan lines
	for( int y = MINV; y <= MAXV && !bInterrupted; y++, pss++ ) 
	{
		if( pss->x[0] < INT_MAX ) 
		{
			/////////////////////
			RenderSpan_FULL(pDC, y, pss );
			/////////////////////
			*((DWORD*)pss) = MINMAX;
		}
//		bInterrupted = InterruptEvent();       todo
	}
	////////////////////
	return bInterrupted;
}

/**********************************************************************************
 *
 *	Function:	RenderSpan_FULL
 *
 *	Purpose:	Draws a series of adjacent pixels on a scan line.  Drawing proceeds
 *				left to right.  Lighting effects and rendering attributes are
 *				evaluated to determine the color of each pixel, through calls to
 *				appropriate subordinate functions.
 *
 **********************************************************************************
 */
void CRender::RenderSpan_FULL
				(
					CClientDC*	pDC,	
					int			y,	//	current scan line (vertical coordinate)
					pSCANSPAN	pss	//	current scanline span data
	)
{
	int				Ix1,Ix2,x,xMx,ox;
	double			r,vd,dvd;
	WORLD			dN,N,dP,P,R,dR;
	pDOUBLE			pB;
    ////////////////////////////////////////////////////
	Ix1 = pss->x[0];
	Ix2 = pss->x[1];
	if( Ix1 == Ix2 )
		return;
	if( Ix1 > m_pZB->GetxMx() || Ix2 < m_pZB->GetxMn() )	// out of window
															// bounds 
		return;
    ////////////////////////////////////////////// Increments 
    // Later change into Integer Arithmatic( p 144:WATT)       todo
    /////////////////////////////////////////////////////
	r	= 1.0 / (pss->x[1] - pss->x[0]);
	N = pss->e[0].N;
	DELTAWORLD( dN, N, pss->e[1].N, r );
	P = pss->e[0].P;
	DELTAWORLD( dP, P, pss->e[1].P, r );
	/////////////////////////////////// Texture
	if( m_pRA->texture) 
	{
		R = pss->e[0].R;
		DELTAWORLD( dR, R, pss->e[1].R, r );
	}
    //////////////////////////////////////////////
	x = (int)MAX( (int)Ix1, (int)m_pZB->GetxMn() );	// forcing -x to zero here
	ox = x - Ix1;			// how much offset, if any?
	if( ox ) 
	{				// adjust items as needed.
		OFFSET(N,dN,ox);
		OFFSET(P,dP,ox);
		/////////////////////////////////// Texture
		if( m_pRA->texture ) 
		{
			OFFSET( R, dR, ox );
		}
	}
	/////////////////////////////////////////////////////
    vd 		= DISTANCE( P ); // MO931120
//    dvd	= ( DISTANCE((pss->e[1].P)) -	DISTANCE((pss->e[0].P)) )
//    		/(pss->x[1]-pss->x[0]); // MO931120
    dvd		= DISTANCE(pss->e[1].P)  -	DISTANCE(pss->e[0].P);
    dvd 	/= (pss->x[1]-pss->x[0]);
	xMx		= (int)MIN( (int)Ix2, (int)m_pZB->GetxMx() );
	//////////////////			
	while( x < xMx ) 
	{
		/////////////////////////////////////////
		BOOL bEdgePixel = 	(x == Ix1) || (x == Ix2)
					||	(y == MINV && MINV != (short)m_pZB->GetyMn())	// don't do edges generated by clipping
					||	(y == MAXV && MAXV != (short)m_pZB->GetyMx());	// to the window boundaries
        ////////////////////////////  in view volume
		if( P.z < 0.0 ) 
		{
			/////////////////////////////////////////////////// Update Z-Buffer
			if( m_pZB->PutZdepth(x,y,vd,m_dHither,m_dYon) ) 
			{
				////////////////////////////////////// Update Frame-Buffer
				RenderPixel_FULL(pDC,x,y,N,P,R,bEdgePixel);
				//////////////////////////////////////
			}	
		}
		x++;
		pB++;
		vd += dvd; 
		//////////////////// Update
		INC( N, dN );
		INC( P, dP );
		if( m_pRA->texture ) 
		{
			INC( R, dR );
		}
		///////////////////
	}
}

void CRender::RenderPixel_FULL(CClientDC* pDC,
								int x,int y,
								WORLD N,
								WORLD P,
								WORLD R,BOOL bEdgePixel)
{

	RGBCOLOR	rgb;
	RGBCOLOR	C;
	////////////////////////////////////
	C = EvaluateColor_FULL(x,y,N,P,R,bEdgePixel);
	///////////////////////////////////////// CLIPCOLOR
	rgb.red		= CLIPCOLOR( C.red );
	rgb.green	= CLIPCOLOR( C.green );
	rgb.blue	= CLIPCOLOR( C.blue );
    ///////////////////////////////////////// Send Color(Class Alias)
	SetCPixel( pDC,x, y, &rgb );
	////////////////////////

}

BOOL CRender::DoAntiAliasing()
{

	BOOL bInterrupted;
/* 											todo
	//////////////////////
	for( y = MINV; y <= MAXV && !bInterrupted; y++, pss++ ) 
	{
		bInterrupted = InterruptEvent();
		if( pss->x[0] < INT_MAX ) 
		{
			////////////////////////
			AntialiasEdge( y, pss );
			////////////////////////
			*((DWORD*)pss) = MINMAX;
		}
	}
*/	
	////////////////////
	return bInterrupted;
}	
	
RGBCOLOR CRender::EvaluateColor_FULL(
									int x,int y,
									WORLD 	N,
									WORLD 	P,
									WORLD 	R,
									BOOL 	bEdgePixel
								)
{

	CLight		Light;
	//////////////////
	WORLD		n;
	RGBCOLOR	C,oC,RAC = {m_pRA->R,m_pRA->G,m_pRA->B};
	/////////////////////////////////////////////// Raw Color
	oC = ( m_pRA->framed && bEdgePixel )?	
			m_pRA->frameColor : RAC;
	/////////////////////////////////////////////// Light Effect
	///////////////////////// Adjust Normal:Texture
	n 	= m_Textures.
			EffectiveNormal(m_pRA, m_pLE, N, R);
    ///////////////////////////
	C 	= Light.LightEffect(m_pLE, m_pRA, &P, &n,
							m_bShadowOn );
	/////////////////////////////////////////////// Texture Effect
	if( m_pRA->texture ) 
		oC 	= m_Textures.TextureEffect(m_pRA, m_pLE, R);
	//////////////////
	if(	(m_pRA->texture & TX_PICT)
		&&	
			( 	oC.red	==0.0 && 
				oC.green==0.0 && 
				oC.blue	==0.0 
			)
		&& 	
			(m_pRA->tx[TXI_PICT].txArgument[1]>1)
	  )
	  	//////////////////////////////////////////
		// this is the black (transparent) part // 
		// of a PICT texture so we do nothing	// 
		// except reset the ZBuffer depth value.//	
		//////////////////////////////////////////
		m_pZB->UnSetZdepth( (short)x, (short)y );
	else 
	{
		/////////////////////////////////////////// DistanceEffect &
												 // Reflectivity Factors
    	double vd 	= DISTANCE( P ); // 
		double r 	= ( m_pRA->distanceEffect )?
				 		(vd*vd) : 1.0;
        //////////////////////////////////////
		C.red	= (oC.red   * ( C.red   + m_pLE->Ra ))/r;
		C.green	= (oC.green * ( C.green + m_pLE->Ga ))/r;
		C.blue  = (oC.blue  * ( C.blue  + m_pLE->Ba ))/r;
        /////////////////////////////////////////// AmbientEffect
	 	if( m_pRA->ambientEffect ) 
	 	{	//	Add ambient light reaching the eye directly.
		    if( m_pRA->hazing ) 
		    {
				double b = vd/512;
				if( b > 10 ) b = 10;
				C.red   += m_pLE->Ra*b;
				C.green += m_pLE->Ga*b;
				C.blue  += m_pLE->Ba*b;
		    }
		    else 
		    {
				C.red   += m_pLE->Ra;
				C.green += m_pLE->Ga;
				C.blue  += m_pLE->Ba;
		    }
		}
		/////////////////////////////////////////// Transparency
												 // Effect
		if( m_pRA->transparency > 0 ) 
		{
/*  											todo
			BOOL b = DIDC_CanGetPixel( TRUE );
			GetCPixel( x, y, &rgb );
			DIDC_CanGetPixel( b );
			C = Transparency( &rgb, &C, m_pRA.transparency );
*/			
		}
	}
	//////////
	return C;	

}

RGBCOLOR CRender::EvaluateColor_LF
					(
						WORLD		Centroid,	//	centroid of region
						WORLD		N,			//	normal at centroid
						double		d			//	distance from viewer
					)
{

	CLight		Light;
	//////////////////
	RGBCOLOR	C,oC = {m_pRA->R,m_pRA->G,m_pRA->B};//Raw Color 
    /////////////////////////////////////////////// Light Effect
	C 	= Light.LightEffect(m_pLE, m_pRA, &Centroid, &N, FALSE);
	/////////////////////////////////////////// DistanceEffect
	double r 	= ( m_pRA->distanceEffect )?
			 		(d*d) : 1.0;
	//////////////////////////////////////
	C.red	= (oC.red   * 
				( C.red   + m_pLE->Ra ))/r;
	C.green	= (oC.green * 
				( C.green + m_pLE->Ga ))/r;
	C.blue  = (oC.blue  * 
				( C.blue  + m_pLE->Ba ))/r;
	/////////////////////////////////////////// AmbientEffect
	if( m_pRA->ambientEffect ) 
 	{	//	Add ambient light reaching the eye directly.
	    if( m_pRA->hazing ) 
	    {
			double b = d/512;
			if( b > 10 ) b = 10;
			C.red   += m_pLE->Ra*b;
			C.green += m_pLE->Ga*b;
			C.blue  += m_pLE->Ba*b;
	    }
	    else 
	    {
			C.red   += m_pLE->Ra;
			C.green += m_pLE->Ga;
			C.blue  += m_pLE->Ba;
	    }
	}
	//////////
	return C;	

}

/**********************************************************************************
 *
 *	Function:	Opaqueness
 *
 *	Purpose:	Mixes a foreground and a background color based on an transmission
 *				coefficient which specifies a degree of opaquenes.  The values that
 *				are returned are calculated as:
 *					RV = BG * (1.0-c) + FG * c
 *				where:
 *					RV is the returned value,
 *					BG is the background color
 *					FG is the foreground color
 *					c is the transmission coefficient
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CRender::Opaqueness
					(
						pRGBCOLOR	bg,	// background color
						pRGBCOLOR	fg,	// foreground color
						double		coef// transmission coefficient					
					)
{
	RGBCOLOR	c;
	double		f = 1.0F - coef;

	c.red	= bg->red	*f + fg->red	* coef;
	c.green = bg->green	*f + fg->green	* coef;
	c.blue	= bg->blue	*f + fg->blue	* coef;
	//////////
	return c;
}

/**********************************************************************************
 *
 *	Function:	Transparency
 *
 *	Purpose:	Mixes a foreground and a background color based on an transmission
 *				coefficient which specifies a degree of transparency.  The values
 *				returned are calculated as:
 *					RV = BG * c + FG * (1.0-c)
 *				where:
 *					RV is the returned value,
 *					BG is the background color
 *					FG is the foreground color
 *					c is the transmission coefficient
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CRender::Transparency
					(
						pRGBCOLOR	bg,	// background color
						pRGBCOLOR	fg,	// foreground color
						double		coef// transmission coefficient					
					)
{
	RGBCOLOR	c;
	double		f = 1.0F - coef;

	c.red	= bg->red	*coef + fg->red		* f;
	c.green = bg->green	*coef + fg->green	* f;
	c.blue	= bg->blue	*coef + fg->blue	* f;
	//////////
	return c;
}

void CRender::BuildEdgeList(CDrObject* pPoly,BOOL bNeedRaw)
{

	CDrObject* pNodeA;
	CDrObject* pNodeB;
	
	CDListMgr* pList = ((CDrFE2D*)pPoly)->GetNodeList();
	//////////////////////////////////////////////////////// Add all edges.
	int MaxC = pPoly->GetMaxCorners();
	for(int ix =1; ix <MaxC; ix++)
	{
		pNodeA = (CDrObject*)pList->GetObject(ix-1);
		pNodeB = (CDrObject*)pList->GetObject(ix);
		///////////////////////////////
		if(m_Rendition == ZB_GOURAUD || m_Rendition == ZB_PHONG )
			/////////////////////////////
			AddToEdgeList(pPoly,pNodeA,pNodeB,bNeedRaw);
			/////////////////////////////
		else	
		if(m_Rendition == FS_ZBUFFER)  // LitFlat
			///////////////////////////////
			AddToEdgeList_LF(pPoly,pNodeA,pNodeB,bNeedRaw);
			///////////////////////////////
	}
	pNodeA = pNodeB;
	pNodeB = (CDrObject*)pList->GetObject(0);
	///////////////////////////////
	if(m_Rendition == ZB_GOURAUD || m_Rendition == ZB_PHONG )
		/////////////////////////////
		AddToEdgeList(pPoly,pNodeA,pNodeB,bNeedRaw);
		/////////////////////////////
	else	
	if(m_Rendition == FS_ZBUFFER)  // LitFlat
		///////////////////////////////
		AddToEdgeList_LF(pPoly,pNodeA,pNodeB,bNeedRaw);
		///////////////////////////////

}

/**********************************************************************************
 *
 *	Function:	AddToEdgeList [Note: Polygon assumed CONVEX]
 *
 *	Purpose:	Builds a list of edge endpoints for an extended polygon, linked in
 *				a manner which allows it to be processed by scan line (Y). The edge
 *				endpoints are clipped here to the vertical extents of the Z buffer.
 *
 *	Returns:	NOERR if successful;.
 *
 **********************************************************************************
 */
void CRender::AddToEdgeList
				(
					CDrObject*	pPoly,
					CDrObject*	pNodeA,
					CDrObject*	pNodeB,
					BOOL		bNeedRaw
				)
{
	///////////////////////////////////////
	POINT		p0,p1;
	double		r,x,dx;
	int			Iy1,Iy2,y,yMn,oy,X;
	WORLD		A,Na,Ra, B,Nb,Rb,
				N,dN, P,dP, R,dR;
	pSCANSPAN	pss;
	////////////////////////////////////////////// Screen2DPt
	p0	= *(((CDrNode*)pNodeA)->GetScreenPos2D());
	p1	= *(((CDrNode*)pNodeB)->GetScreenPos2D());
    ////////////////////////////////////////////// horizontal edge
    											// reject
	if( p0.y == p1.y )      
		return;
    ////////////////////////////////////////////// higher ScanLine
	if( p0.y > p1.y )				 			// swap 
	{		 
		POINT		p;
		CDrObject*	pNode;
		//////////////////
		p		= p0;		p0	= p1;			p1	= p;
		pNode 	= pNodeA; 	pNodeA = pNodeB; 	pNodeB = pNodeA;
	}
	///////////////////////////////////
	A	= *(((CDrNode*)pNodeA)->GetScreenPos3D());
	Na	= *(((CDrNode*)pNodeA)->GetNormalEye());
	B	= *(((CDrNode*)pNodeB)->GetScreenPos3D());
	Nb	= *(((CDrNode*)pNodeB)->GetNormalEye());
	///////////////////////////////////
	if( m_pRA->specIndex == 0 )	 		// may be able to use ZPoly?
		Na = Nb = *(((CDrFE2D*)pPoly)->GetNormalEye());	// not specular so make it flat
    ///////////////////////////////////
	Iy1	= p0.y;
	Iy2	= p1.y;
    ////////////////////////////////////////////// Increments 
    // Later change into Integer Arithmatic( p 144:WATT)       todo
    /////////////////////////////////////////////////////
	r	= 1.0 / (Iy2 - Iy1);
	N	= Na;
	P	= A;

	DELTAWORLD( dN, N, Nb, r );
	DELTAWORLD( dP, P, B,  r );
	x	= p0.x;
	DELTADOUBLE( dx, x, p1.x, r );
    //////////////////////////////// Texture ?
	if( m_pRA->texture ) 
	{
		Ra	= *(((CDrNode*)pNodeA)->GetWorldPos());
		Rb	= *(((CDrNode*)pNodeB)->GetWorldPos());
		R	= Ra;
		DELTAWORLD( dR, R, Rb, r );
	}
    //////////////////////////////////////////
	y	= (int)MAX( (int)Iy1, (int)MINV );	// forcing -y to zero here 
	oy	= abs( y-Iy1 );						// how much offset, if any?
	if( oy ) 
	{
		x	+= dx * oy;						// adjust items as needed.
		OFFSET(N,dN,oy);
		OFFSET(P,dP,oy);
		if( bNeedRaw )
			OFFSET(R,dR,oy);
	}
	yMn	= (int)MINV;
	x	+= 0.5;
	Iy2 = (int)MIN( (int)Iy2, (int)MAXV );
	//////////////////////////////////////////////// S T O R E
	pss = m_pScanSpan + (y-yMn);
	////////////////////////////upto MaxScanLine - 1
	while( y<Iy2 ) 
	{
        X = (int)x;
        if( X<pss->x[0] ) 
        {
        	pss->x[0] 	= X;
        	pss->e[0].N = N;
        	pss->e[0].P = P;
        	pss->e[0].R = R;
        }
        if( X>pss->x[1] ) 
        {
        	pss->x[1] 	= X;
        	pss->e[1].N = N;
        	pss->e[1].P = P;
        	pss->e[1].R = R;
        }
        ///////////////////////////////////////
		y++;
		pss++;
		x += dx;
		/////////////////
		INC( N, dN );
		INC( P, dP );
		if( m_pRA->texture )
			INC( R, dR );
		/////////////////	
	}
}

/**********************************************************************************
 *
 *	Function:	AdjacentPoly
 *
 *	Purpose:	Determines if two polygons have a vertex in common.
 *
 *	Returns:	true if there is a vertex in common; false otherwise.
 *
 **********************************************************************************
 */
BOOL CRender::AdjacentPoly(CDrObject* pPolyA, CDrObject* pPolyB)
{
/*
todo
	CString NodeId_A, NodeId_B;
	///////////////////////////
	int	MaxA = pPolyA->GetMaxNodes(),
	 	MaxB = pPolyB->GetMaxNodes(), i,j;
    //////////////////////////////////////
	for(i=0;i<MaxA;i++) 
	{
		pNodeA 		= pPolyA->GetNodePtr(i);
		NodeId_A	= pNodeA->GetObjectID();  	
		for(j=0;j<MaxB;j++)
		{ 
			pNodeB 		= pPolyB->GetNodePtr(j);
			NodeId_B	= pNodeB->GetObjectID();  	
			if( NodeId_A  == NodeId_B )
				return TRUE;
		}		
	}
*/	
	return FALSE;
}

void CRender::AddToEdgeList_LF
				(
					CDrObject*	pPoly,
					CDrObject*	pNodeA,
					CDrObject*	pNodeB,
					BOOL		bNeedRaw
				)
{
	POINT		p0,p1;
	double		x,dx,z,dz,Az,Bz;
	int			y,yMn,oy,X;
	WORLD		A, B;
	pSCANSPAN	pss;
	////////////////////////////////////////////// Screen2DPt
	p0	= *(((CDrNode*)pNodeA)->GetScreenPos2D());              // Projected
	p1	= *(((CDrNode*)pNodeB)->GetScreenPos2D());
    ////////////////////////////////////////////// horizontal edge
    											// reject
	if( p0.y == p1.y )      
		return;
    ////////////////////////////////////////////// higher ScanLine
	if( p0.y > p1.y )				 			// swap 
	{		 
		POINT		p;
		CDrObject*	pNode;
		p		= p0;		p0	= p1;			p1	= p;
		pNode 	= pNodeA; 	pNodeA = pNodeB; 	pNodeB = pNodeA;
	}
	///////////////////////////////////
	A	= *(((CDrNode*)pNodeA)->GetScreenPos3D());   // Transformed
	B	= *(((CDrNode*)pNodeB)->GetScreenPos3D());
	Az 	= DISTANCE( A );
	Bz 	= DISTANCE( B );
    ////////////////////////////////////////////// Increments 
    // Later change into Integer Arithmatic( p 144:WATT)       todo
    /////////////////////////////////////////////////////
	oy	= p1.y-p0.y;
	dx	= (p1.x-p0.x)/oy;
	dz	= (Bz-Az)/oy;
	y	= MAX( p0.y, MINV );
	x	= p0.x;
	z	= Az;
	oy	= y-p0.y;
	if( oy ) 
	{
		x	+= dx * oy;
		z	+= dz * oy;
	}
	if( MAXV < p1.y )
		p1.y = MAXV;
	yMn	= MINV;
	x	+= 0.5;
	//////////////////////////////////////////////// S T O R E
	pss = m_pScanSpan + (y-yMn);
	////////////////////////////
	while( y < p1.y ) 
	{
		X 	= (int)x;
		if( X<pss->x[0] ) 
		{
			pss->x[0] = X;
			pss->z[0] = z;
		}
		if( X>pss->x[1] ) 
		{
			pss->x[1] = X;
			pss->z[1] = z;
		}
		y++;
		pss++;
		x += dx;
		z += dz;
	}

}

/**********************************************************************************
 *
 *	Function:	InShadow
 *
 *	Purpose:	Intersects a ray from a point to a light source with each polygon
 *				in a polygon list to determine if any obscuration occurs.
 *
 *	Returns:	true if any polygon obscures the light ray; otherwise false.
 *
 **********************************************************************************
 */
Boolean CRender::InShadow(
		pWORLD		P,
		double		ld,
		pLTSOURCE	pLS,
		double		*transmission
	)
{
/*
	int			i;
	float		t,ldx,ldy,ldz;
	pPolyList	ppl = pPL;
	pVN			pvn;
	WORLD		iP,LS,V;
	Box			RayBox;
	pPGN		pCpgn,ppgn;
	pPolyExt	pPE,pPEcurrent;

	LS.x = pLS->x;
	LS.y = pLS->y;
	LS.z = pLS->z;
	pCpgn = (pPGN)phCurrent;
	pPE	= (pPolyExt)( (Ptr)pCpgn + pCpgn->p.polySize);

	pPEcurrent = pPE;

	BoxMinMax(x,RayBox,*P,LS);
	BoxMinMax(y,RayBox,*P,LS);
	BoxMinMax(z,RayBox,*P,LS);

	ldx = LS.x-P->x;
	ldy = LS.y-P->y;
	ldz = LS.z-P->z;

	while( ppl ) 
	{
		if( ppl->ph!=phCurrent ) 
		{
			ppgn= (pPGN)ppl->ph;
			pPE	= (pPolyExt)(((Ptr)ppgn) + ppgn->p.polySize);

			if( BoxIntersects( pPE->bounds, RayBox ) ) 
			{
				if( !Adjacent( pPEcurrent, pPE ) ) 
				{
					t = -
					(   pPE->n.x*(P->x-pPE->c.x)+pPE->n.y*(P->y-pPE->c.y)+pPE->n.z*(P->z-pPE->c.z)	)
					/ /-------------------------------------------------------------------------/
					(					pPE->n.x*ldx+pPE->n.y*ldy+pPE->n.z*ldz					);
					iP.x= P->x+ldx*t;
					iP.y= P->y+ldy*t;
					iP.z= P->z+ldz*t;

					if( PointInBox( iP, pPE->bounds ) ) 
					{
						V.x = LS.x - iP.x;
						V.y = LS.y - iP.y;
						V.z = LS.z - iP.z;
						if( DISTANCE( V ) < ld ) 
						{
							pvn = pPE->vn;
							i = pPE->np;
							while( --i ) 
							{
								V.x = iP.x - pvn->v.x;
								V.y = iP.y - pvn->v.y;
								V.z = iP.z - pvn->v.z;
								if( DOTPRODUCT( pvn->d, V ) < 0 )
									break;
								pvn++;
							}
							if( !i ) 
							{
								*transmission = FPFix( pPE->RA.transparency );
								return true;
							}
						}
					}
				}
			}
		}
		ppl = ppl->prior;
	}
*/	
	return FALSE;
}

/*****************************************************************************
 *
 *	Function:	DepthSort()
 *
 *	Purpose:	Sorts an array of facets into distance order.
 *
 *	Methods:	Adaptation of Shell-Metzner algorithm
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
void CRender::DepthSort(CDListMgr* pSortList, BOOL bAscending)
{
	register long	i,jump,n;
	BOOL			done = FALSE;
	CDrObject*		pPolyI;
	CDrObject*		pPolyJ;
	CDrObject*		pPolyTemp;
	////////////////////////////////////////
    n = pSortList->GetCount();
    //////////////////////////
    jump = n;
    /////////
	if( bAscending  )
		while( jump ) 
		{
			jump>>= 1;
			do 
			{
				done = TRUE;
				for( i = 0; i < (n-jump); i++ ) 
				{
					pPolyI = (CDrObject*)pSortList->GetObject((int)i);
					pPolyJ = (CDrObject*)pSortList->GetObject((int)(i + jump));
					/////////////////////////////////
					double zI = ((CDrFE2D*)pPolyI)->GetCentroidZdepth();
					double zJ = ((CDrFE2D*)pPolyJ)->GetCentroidZdepth(); 
					if( zI > zJ) 
					{
/*
						pPolyTemp 	= pPolyI;
						pPolyI 		= pPolyJ;
						pPolyJ		= pPolyTemp;
*/
						pSortList->ReplaceObject((int)i,pPolyJ);				// switch
						pSortList->ReplaceObject((int)(i + jump),pPolyI);		// switch
						////////////////////////////////////////////////
						done 		= FALSE;
					}
				}
			} while( !done );
		}
	else
		while( jump ) 
		{
			jump>>= 1;
			do 
			{
				done = TRUE;
				for( i = 0; i < (n-jump); i++ ) 
				{
					pPolyI = (CDrObject*)pSortList->GetObject((int)i);
					pPolyJ = (CDrObject*)pSortList->GetObject((int)(i + jump));
					/////////////////////////////////
					double zI = ((CDrFE2D*)pPolyI)->GetCentroidZdepth();
					double zJ = ((CDrFE2D*)pPolyJ)->GetCentroidZdepth(); 
					if( zI < zJ) 
					{
/*
						pPolyTemp 	= pPolyI;
						pPolyI 		= pPolyJ;
						pPolyJ		= pPolyTemp;
*/
						pSortList->ReplaceObject((int)i,pPolyJ);				// switch
						pSortList->ReplaceObject((int)(i + jump),pPolyI);		// switch
						////////////////////////////////////////////////
						done 		= FALSE;
					}
				}
			} while( !done );
		}
}

void CRender::RenderPolyline_Z
				(
					CClientDC* pDC,	short nS,LPPOINT S,
									pWORLD P,COLORREF C
				)
{
	register short	i = nS;
	LPPOINT		s = S;
	pWORLD	p = P;

	while( --i ) 
	{
		RenderLine_Z(pDC, *s, *(s+1), p, p+1, C );
		s++;
		p++;
	}
}

void CRender::RenderLine_Z
				(
					CClientDC* pDC,
					POINT S0,POINT S1,
					pWORLD P0,pWORLD P1,COLORREF C
				)
{
	//////////////////////////////////////////////////////////
	// 			MidPt. Scan Conversion for Line             //
	//			Modified by ZBuffer depth Info				//
	//			Points with Nearer Zdepth Colored			//
	//////////////////////////////////////////////////////////
	double	z,dz;
	int		d,dx,dy,ax,ay,sx,sy,x,y;

//////////////////////////////////////////////////////////////////
	if( !m_pZB )
		return;
    ////////////////////////////////////////// Swap Order
    										// increasing ScanLine
	if( S0.y > S1.y ) 
	{
		POINT	S = S0;
		pWORLD	P = P0;
		S0 = S1; S1 = S;
		P0 = P1; P1 = P;
	}
    ////////////////////////////////////////// just a Point!
    dx 	= S1.x-S0.x;
    dy 	= S1.y-S0.y;
    z	= DISTANCE((*P0));
	if( !dx && !dy ) 
	{
		RenderPixel_Z(pDC, S0.x,S0.y, z, C );
		return;
	}
	////////////////////////////////////////// Scan Convert
    ax = ABS(dx)<<1;
    ay = ABS(dy)<<1;
    sx = SGN(dx);
    sy = SGN(dy);
    /////////////
    x = S0.x;
    y = S0.y;
	z = DISTANCE(*P0);
    ///////////////////////
    dz = DISTANCE(*P1) - z;
    ////////////////////////////////////////// Slope <45 deg
    if( ax > ay ) {							// x dominant
		d = ay-(ax>>1);
		////////////////////////////////// z increment
		dz = dz/dx;
		if( sx<0 ) dz = -dz;
		////////////////////
		for(;;) 
		{
			///////////////////////////////
			RenderPixel_Z( pDC, x, y, z, C );
			///////////////////////////////	
		    if (x==S1.x) 
		    	return;
		    /////////////	
		    if (d>=0) 
		    {
				y += sy;
				d -= ax;
		    }
		    x += sx;
		    d += ay;
		    z += dz;
		}
    }
    ////////////////////////////////////////// Slope >45 deg
    else {									// y dominant
		d = ax-(ay>>1);
		////////////////////////////////// z increment
		dz = dz/dy;
		////////////////////
		for(;; ) 
		{
			///////////////////////////////
			RenderPixel_Z( pDC, x, y, z, C );
			///////////////////////////////	
		    if (y==S1.y) return;
		    if (d>=0) 
		    {
				x += sx;
				d -= ay;
		    }
		    y += sy;
		    d += ax;
		    z += dz;
		}
    }
}

void CRender::RenderPixel_Z
				(
					CClientDC* pDC, 
					int x, int y, double z,COLORREF C
				)
{
	//////////////////////////////////////////////////////////
	// 					SetPixel in GDI		         	    //
	//			Modified by ZBuffer depth Info				//
	//			Points with Nearer Zdepth Colored			//
	//////////////////////////////////////////////////////////
	if( !m_pZB )
		return;
	////////////	
	if( m_pZB->PutZdepth(x,y,z,m_dHither,m_dYon) ) 
	{
		LightUpPixel( pDC, x, y, C );
	}
	
}

void CRender::LightUpScanSpan(CClientDC* pDC, int xs, int xe, int y)
{

	pDC->MoveTo(xs,y);
	pDC->LineTo(xe,y);
	
}

COLORREF CRender::LightUpPixel(CClientDC* pDC, int x, int y, COLORREF c)
{
	return pDC->SetPixel(x,y,c);
}
///////////////////////////////////////////////////////////////////
void CRender::GetCPixel( CClientDC* pDC, int x, int y, pRGBCOLOR pRGB)
{
	COLORREF	CS = pDC->GetPixel( x, y );
	CS2RGBCOLOR( CS, *pRGB );
}

void CRender::SetCPixel( CClientDC* pDC, int x, int y, pRGBCOLOR pRGB)
{
	pDC->SetPixel( x, y, RGBCOLOR2CS(*pRGB) );
}
////////////////////////////////////////////////////////////// CLIPS
BOOL CRender::ClippedByZBuffer(/*CClientDC* pDC,*/CDrObject* pPoly)
{
    //////////////////////////////////////////////////////
	//Intersect Z buffer and polygon bounding boxes
	////////////////////////////////////////////////////// view needed
	CRect polyBBox = pPoly->GetBoundingRect();
//	pDC->LPtoDP(&polyBBox);
	/////////////////////////////////////////
	MINV= MAX( polyBBox.top, 	(short)m_pZB->GetyMn() );
	MAXV= MIN( polyBBox.bottom, (short)m_pZB->GetyMx() );
	if( MAXV<=MINV ) // clipped out of existance, omit it.
		return TRUE;
	////////////////////////	
	MINH= MAX( polyBBox.left, 	(short)m_pZB->GetxMn() );
	MAXH= MIN( polyBBox.right, 	(short)m_pZB->GetxMx() );
	if( MAXH<=MINH ) // clipped out of existance, omit it.
		return TRUE;
	////////////////////////	
	return FALSE;
}	
//////////////////////////////////////////// Painter's Clip
///////////////////////////////////////////////////////////
void CRender::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Render:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" Render:    Loading\n");	// TODO: add loading code here
	}
		
}
/////////////////////////// end of module ///////////////////
