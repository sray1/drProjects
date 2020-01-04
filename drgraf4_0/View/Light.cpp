/*****************************************************************************
 *	File:		Light.cpp
 *
 *	Purpose:	Color rendering of solids.
 *****************************************************************************
 */
 
#include "stdafx.h"
#include "math.h"
/////////////////////
#include "Def_Rend.h"
#include "ColorPal.h"
#include "XForm.h"

#include "Light.h"
/////////////////////////////////////////////////////////////////////////////
// CLight

IMPLEMENT_DYNAMIC(CLight,CObject)
/*
BEGIN_MESSAGE_MAP(CLight,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CLight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CLight::CLight()
{
}
///////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////// resource switch
extern Boolean	ColorPresent;	/* from Init3d() call of SysEnvirons in 3d.c */

#undef max
#define max(a,b) (((a)>(b))?(a):(b))
#undef min
#define min(a,b) (((a)<(b))?(a):(b))
////////////////////////////////////////////////////

/**********************************************************************************
 *
 *	Function:	LightEffect  & LightIntensity
 *
 *	Purpose:	Determines the effect of multiple light sources and the rendering
 *				attributes at a given point.  If shadow rendering is in process,
 *				the active polygon list is processed to determine if the point is
 *				in shadow relative to each light source, and if so the transmission
 *				factor (transparency) of the intersected polygon is used to reduce
 *				the effect of the light source.  The basic light model used here is
 *				the Phong model, extended to include Warn's method of modeling light
 *				sources of variable geometry; colored light sources and colored
 *				specular hilites.
 *
 *	Returns:	Reflected light color at the specified point.
 *
 **********************************************************************************
 */
double CLight::LightIntensity
//////////////////////////////////////////////////////		
//	Warn's Method with Phong Reflection Model:		//
//		SpotLight Intensity Watt:p123		//      //
//		I = (Source Intensity) *					//
//				[Kd(N.L) + Ks(N.H)**n]				//
//	where											//
//		Source Intensity = [Ii(Ln.L)**s]			//
//		L = Light direction vector to Object		//
//		N = Object Surface Normal Vector			//
//		H = Halfway Vector = (L + V)/2				//
//		Ln= Full Intensity direction of Light Source//
//		n = Specular Index							//
//		s = ShapeFactor of LightCone				//
//			Low 	s = FloodLights					//
//			High 	s = SpotLights                  //
//  	Need to do more elaborate: todo later       //
//////////////////////////////////////////////////////
//	N O T E: Everything is Transformed in ViewSpace	//
//				Isometric to World Space			//
////////////////////////////////////////////////////// 
		(
			double		Si,		// specular index
			double		Ks,		// specular reflection coefficient
			double		Kd,		// diffuse reflection coefficient
			pWORLD		pN,		// normal vector
			pWORLD		pC,		// center of reflection
			pLTSOURCE	pLS,		// light source
			double		*pld	// returned light distance
		)
{
	double	a, s, LN, ld, rld, lVx, lVy, lVz;
    ///////////////////////////////////////// light direction(L)
	lVx = pC->x - pLS->location.x;
	lVy = pC->y - pLS->location.y;
	lVz = pC->z - pLS->location.z;
	*pld = ld = sqrt(lVx * lVx + lVy * lVy + lVz * lVz);
	rld = 1.0F / ld;
	lVx *= rld;
	lVy *= rld;
	lVz *= rld;
	////////////////////////////////////////// L dot N 
	LN = pN->x * lVx + pN->y * lVy + pN->z * lVz;
	if(LN > 0)  {
		a = (pLS->shape <= 0.0 )?
				1.0 : pow(	pLS->normal.x * (-lVx) + 
							pLS->normal.y * (-lVy) + 
							pLS->normal.z * (-lVz) , 
							pLS->shape);
		if(a < 0.0)
			a = -a;
		s = (Si == 0.0 )?
			0.0 : (Ks * pow((	pN->x * (pN->x + lVx) + 
								pN->y * (pN->y + lVy) + 
								pN->z * (pN->z + lVz))* 0.5, 
								Si));
		return a * (Kd * LN + s) * pLS->magnitude * rld * rld;
	}
	else
		return 0.0;
}

RGBCOLOR CLight::LightEffect
					(
						pLTENVIRON 	pL,
						pRENDINFO	pRA,
						pWORLD		pP,		// current transformed 3d point
						pWORLD		pN,		// current normal vector
						BOOL		b_ShadowOn
					)
{
	int				nS	= pL->nSources;
	pLTSOURCE		pLS	= pL->ppSource;
	WORLD			IC 	= pLS->focus;	// transformed Sun ||rays
										// when pLS->shape<0
	RGBCOLOR		C	= {0.0,0.0,0.0};
	double			I,ld,transmission;

	if( b_ShadowOn )						// todo
	{
	/*                                    
		while( nS-- ) 
		{
			if( !pLS->level ) 
			{
				pLS++;
				continue;
			}
			if( pLS->shape < 0.0 )
			{
				IC = pLS->focus;	// transformed Sun || rays
				I = LightIntensity( pRA->specIndex,
									pRA->specularity,
									pRA->diffusion, 
									pN, &IC, pLS, &ld );
			}									
			else
				I = LightIntensity( pRA->specIndex,
									pRA->specularity,
									pRA->diffusion, 
									pN, pP, pLS, &ld );

			if( I > 0.0 ) 
			{
				if( InShadow( P, ld, pLS, &transmission ) ) 
				{
					if( transmission == 0.0 ) 
					{
						pLS++;
						continue;
					}
					I *= transmission;
				}
				I *= (double)pLS->level;
				/////////////////////////////////
				C.red	+=	pLS->color.red * I;
				C.green	+=	pLS->color.green * I;
				C.blue	+=	pLS->color.blue * I;
			}   /////////////////////////////////
			pLS++;
		}
	*/
	}	
	else
		while( nS-- ) 
		{
			if( !pLS->level ) 
			{
				pLS++;
				continue;
			}
			if( pLS->shape < 0.0 )
				I = LightIntensity( pRA->specIndex,
									pRA->specularity,
									pRA->diffusion, 
									pN, &IC, pLS, &ld );
			else
				I = LightIntensity( pRA->specIndex,
									pRA->specularity,
									pRA->diffusion, 
									pN, pP, pLS, &ld );
			if( I > 0.0 ) 
			{
				I *= pLS->level;
				/////////////////////////////////
				C.red	+=	pLS->color.red 	 * I;
				C.green	+=	pLS->color.green * I;
				C.blue	+=	pLS->color.blue  * I;
				/////////////////////////////////
			}
			pLS++;
		}

	return C;
}

/*****************************************************************************
 *
 *	Function:	NewLighting()
 *
 *	Purpose:	Allocates and sets up a lighting structure containing a number
 *				of light sources and ambient light information.
 *
 *	Returns:	Pointer to the lighting information if successfull
 *				nil if memory allocation fails (call MemError for reason)
 *
 *****************************************************************************
 */
//int CLight::NewLighting
int CLight::NewLightEnvironMent
			(
				pLTENVIRON	pL,		// Light Environ	
				COLORFACTOR R,
				COLORFACTOR G,
				COLORFACTOR B,		// ambient light
				double 		lvl,	// intensity scaling
				int 		nS,		// number of sources
				pLTSOURCE 	ppLS	// pointer to array of sources
	)
{

    /////////////////////
	if( nS<0 )
		nS=0;
//	pL = (pLTENVIRON)NewPtr( sizeof(LTENVIRON) + sizeof(LTSOURCE) * nS );
	if( pL ) {
		pL->color.red	= R;
		pL->color.green	= G;
		pL->color.blue	= B;
		pL->level		= lvl;
		pL->magnitude	= R + G + B;
		pL->Ra			= R * lvl;
		pL->Ga			= G * lvl;
		pL->Ba			= B * lvl;
		pL->nSources	= nS;
//		while( nS-- )
//			pL->source[nS] = pLS[nS];
		pL->ppSource	= ppLS;
	}
	return 0;
}
/*	
int CLight::AugmentLightEnvironment( pRENDINFO pRA,pLTENVIRON pLE)
{
	int ix;
	///////
	//	 		Patch dependent Light Environment			// 	            
	if( pRA->texture )
		for( ix=0; ix<TXLIMIT; ix++ )
			for( y=0; y<TXARGS; y++ )
				pLE->arg[ix][y] = pRA->tx[ix].txArgument[y];
	///////////////////////////////
	return 0;

}
*/
/*****************************************************************************
 *
 *	Function:	FocusLightSource()
 *
 *	Purpose:	Focuses a light source at a specific point by directing the
 *				source's normal vector towards the specified point.
 *
 *****************************************************************************
 */
void CLight::FocusLightSource(pLTSOURCE pLS,double x,double y,double z)
{
	double	r;
    //////////
	pLS->focus.x	= x;
	pLS->focus.y	= y;
	pLS->focus.z	= z;
	////////////////////
	pLS->normal.x	= pLS->focus.x - pLS->location.x;
	pLS->normal.y	= pLS->focus.y - pLS->location.y;
	pLS->normal.z	= pLS->focus.z - pLS->location.z;
	r = 1./sqrt(pLS->normal.x * pLS->normal.x +
				pLS->normal.y * pLS->normal.y +
				pLS->normal.z * pLS->normal.z );
	pLS->normal.x	*= r;
	pLS->normal.y	*= r;
	pLS->normal.z	*= r;
}

/*****************************************************************************
 *
 *	Function:	SetLightSource()
 *
 *	Purpose:	Stores color and location information about a light source in
 *				a caller supplied area.
 *	
 *	N o t e:	R,G,Bs in [0,1]
 *
 *****************************************************************************
 */
void CLight::SetLightSource(	
								pLTSOURCE pLS,
								COLORFACTOR R,COLORFACTOR G,COLORFACTOR B,
								double lvl,
								double x,double y,double z
							)
{
	CColorPal	ColorPal;
	/////////////////////
	pLS->color.red	= R;
	pLS->color.green= G;
	pLS->color.blue	= B;
	////////////////////
	ColorPal.RGB2HSV( &(pLS->color), &(pLS->hsvColor) );
	////////////////////
	pLS->level		= lvl;
	pLS->magnitude	= R + G + B;
	pLS->location.x = x;
	pLS->location.y = y;
	pLS->location.z = z;
	pLS->focus.x	= x;
	pLS->focus.y	= y-1.;
	pLS->focus.z	= z;
	pLS->normal.x	= 0.;
	pLS->normal.y	=-1.;	// along y axis to origin
	pLS->normal.z	= 0.;
	pLS->shape		= 0.;
	pLS->limitAngle	= 360.0*0.017453292519943;  // radian
}

/*****************************************************************************
 *
 *	Function:	TransformLighting()
 *
 *	Purpose:	Transforms the locations of a lighting set's light sources
 *				using a supplied transform matrix and converts the results to
 *				double precision.
 *
 *****************************************************************************
 */
void CLight::TransformLightEnviron(pLTENVIRON pL,pMATRIX pXFM)
{
	register int	i;
	pLTSOURCE		pLS;
	double			r;
	WORLD			Loc,Foc;
	////////////////////////
	CColorPal		ColorPal;
	CXForm			XForm;
    ////////////////////////
	for (i=0;i<pL->nSources;i++)
	{
		pLS = pL->ppSource + i;
	    /////////////////////////////////////////////
		XForm.Transform( &(pLS->location), &Loc, pXFM );
		XForm.Transform( &(pLS->focus),    &Foc, pXFM );
		/////////////////////////////////////////////
		pLS->normal.x	= Foc.x - Loc.x;
		pLS->normal.y	= Foc.y - Loc.y;
		pLS->normal.z	= Foc.z - Loc.z;
		r = 1./sqrt(pLS->normal.x * pLS->normal.x +
					pLS->normal.y * pLS->normal.y +
					pLS->normal.z * pLS->normal.z );
		pLS->normal.x	*= r;
		pLS->normal.y	*= r;
		pLS->normal.z	*= r;
		/////////////////////////////////////
		ColorPal.RGB2HSV( &(pLS->color), &(pLS->hsvColor) );
		/////////////////////////////////////
	}
}
/*
double CLight::LightIntensity (	double Si,double Ks,double Kd,
								double Nx,double Ny,double Nz, // Normal
								double Cx,double Cy,double Cz, // 
								pLTSOURCE pLS
							)
{
	double	a, s, LN, d, rd, Vx, Vy, Vz;
	////////////////////////////////////////////// distance
	Vx 	= Cx - pLS->location.x;					
	Vy 	= Cy - pLS->location.y;
	Vz 	= Cz - pLS->location.z;
	d 	= sqrt(Vx * Vx + Vy * Vy + Vz * Vz);
	rd = 1.0 / d;
	Vx *= rd;
	Vy *= rd;
	Vz *= rd;
	LN = Nx * Vx + Ny * Vy + Nz * Vz;
	////////////////////////////////////
	if(LN > 0)  {
		a = (pLS->shape <= 0.0 )?
			1.0 : pow(	pLS->normal.x * (-Vx) +
						pLS->normal.y * (-Vy) + 
						pLS->normal.z * (-Vz) , pLS->shape);
		if(a < 0.0)
			a = -a;
		s = (Si == 0.0 )?
			0.0 : (Ks * pow((Nx * (Nx + Vx) + Ny * (Ny + Vy) + Nz * (Nz + Vz)) * 0.5, Si));
		return a * (Kd * LN + s) * pLS->magnitude * rd * rd;
	}
	else
		return 0;
}
*/
////////////////////////////// end of module //////////////
