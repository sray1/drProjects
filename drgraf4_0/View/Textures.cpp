/*****************************************************************************
 *	file:		Textures.cpp
 *
 *	purpose:	ZBuffer rendering, texture mapping functions
 *****************************************************************************
 */
#include "stdafx.h"
#include "time.h"		// for seed
#include "stdlib.h" 	// for rand
#include "limits.h"
#include "math.h"
#include "string.h"

#include "XForm.h"
#include "3DMath.h"

#include "Def_Rend.h"

#include "Textures.h"
/////////////////////////////////////////////////////////////////////////////
// CTextures

IMPLEMENT_SERIAL(CTextures,CObject,1)
/*
BEGIN_MESSAGE_MAP(CTextures,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CTextures)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CTextures::CTextures()
{
}
///////////////////////////////////////////////////////////// 
/////////////////////
/*
//#include <WIN_TRIM.H>
//#include <AntiA.h>
//#include <Textures.h>
//#include <LOADBMPF.h>
*/
/*
//////////////////////////////////
typedef HBITMAP PicHandle;

typedef struct phList {
	char			name[10];
	PicHandle		ph;
	struct phList	__far *prior;
}
	phList, __far *pphList;

//////////////////////////////////
#define	abs(x)	(((x)<0)?-x:x)


extern HANDLE	ghInst;

static HDC			hDCm;
static pPixelQ		PICTpixQ = NULL;
static double		ox,oy;
static PicHandle	ph;
static Rect			rPic;
static Point		dr;
static pphList		pphl = NULL;
*/
////////////////////////////////////////////////////////////////
void CTextures::Init(pRENDINFO pRA, pLTENVIRON LI) 
{
	////////////////////////////////// 
	if( pRA->texture & TX_WOOD )
		WoodLocalMatrix
		(
		 	pRA->tx[TXI_WOOD].txRotations, 
			pRA->tx[TXI_WOOD].txScalars, 
			pRA->tx[TXI_WOOD].txTranslations 
		);
	if( pRA->texture & TX_ROCK )
		RockLocalMatrix
		(
		 	pRA->tx[TXI_ROCK].txRotations, 
			pRA->tx[TXI_ROCK].txScalars, 
			pRA->tx[TXI_ROCK].txTranslations 
		);
/*		
	if( pRA->texture & TX_PICT ) 
	{
		PICTinit( (STR4)(pRA->tx[TXI_PICT].txArgument[0]), &pPE->bounds );
		if(		pRA->tx[TXI_PICT].txScalars.x
			&&	pRA->tx[TXI_PICT].txScalars.y
			&&	pRA->tx[TXI_PICT].txScalars.z
		  )
			PICTLocalMatrix
			(
				pRA->tx[TXI_PICT].txRotations,
				pRA->tx[TXI_PICT].txScalars,
				pRA->tx[TXI_PICT].txTranslations
			);
	}
*/	
	if( pRA->texture & TX_BUMPS )
		BumpsLocalMatrix
		( 	pRA->tx[TXI_BUMPS].txRotations, 
			pRA->tx[TXI_BUMPS].txScalars, 
			pRA->tx[TXI_BUMPS].txTranslations 
		);
	if( !(pRA->texture & TX_USERBIT) ) 
	{
		if( pRA->texture & TX_RGB )
			RGBLocalMatrix
			(	pRA->tx[TXI_RGB].txRotations, 
				pRA->tx[TXI_RGB].txScalars, 
				pRA->tx[TXI_RGB].txTranslations 
			);
		if( pRA->texture & TX_DEPTH )
			DepthLocalMatrix
			(	pRA->tx[TXI_DEPTH].txRotations, 
				pRA->tx[TXI_DEPTH].txScalars, 
				pRA->tx[TXI_DEPTH].txTranslations 
			);
	}
	else 
	{
/*	   													todo
       	LI.pudll = GetUserDll( USERDLLNAME(pRA) );
       	if( LI.pudll != NULL ) 
       	{
       		if( LI.pudll->pTxInit != NULL )
       			LI.pudll->pTxInit( pRA, &pPE->bounds );
       		if( LI.pudll->pTxXfrm != NULL )
       			LI.pudll->pTxXfrm( pRA );
       	}
*/       	
	}
	/////////////////////////////////////// initialize Noise
	m_bNoiseReady = Init_Noise();
	////////////////////////////////
}

void CTextures::Terminate(pRENDINFO pRA, pLTENVIRON LI) 
{
	//////////////////////////////////
	if( pRA->texture & TX_PICT )
		PICTterm();
	///////////////	
/*
   	if( LI.pudll != NULL )
   		if( LI.pudll->pTxTerm != NULL )       todo
   			LI.pudll->pTxTerm();
*/   			
   	////////////////////////////		
}
	
WORLD CTextures::EffectiveNormal(pRENDINFO pRA, pLTENVIRON LI,
									 WORLD N,WORLD R)
{

	WORLD		n;
    /////////////////////////////////////////////// Texture
	n = N;
	////////////////////////////// Bumps
	if( pRA->texture & TX_BUMPS )
		n = PerturbNormal
			( R.x, R.y, R.z, N, pRA->tx[TXI_BUMPS].txArgument[0], 
								pRA->tx[TXI_BUMPS].txArgument[1], 
								pRA->tx[TXI_BUMPS].txArgument[2], 
								pRA->tx[TXI_BUMPS].txArgument[3] 
			);
/*			
	////////////////////////////// Picture
	if( (pRA->texture & TX_PICT) && pRA->tx[TXI_PICT].txArgument[1]<0 ) 
	{
		double	bumpScale = -pRA->tx[TXI_PICT].txArgument[1];
		if( bumpScale >= 1000 )
			bumpScale -= 1000;
		n = PICTbump
					(
						R.x,R.y,R.z, N,bumpScale,
						pRA->tx[TXI_PICT].txArgument[2],
						pRA->tx[TXI_PICT].txArgument[3] 
					);
	}
	////////////////////////////// UserNormal
	if( pRA->texture & TX_USERNORMAL )
       	if( LI.pudll != NULL )
       		if( LI.pudll->pTxEval != NULL )
       			LI.pudll->pTxEval( pRA, &R, NULL, &n );
    /////////////////////////////
*/
	/////////////
	return n;
	
}
	
RGBCOLOR CTextures::TextureEffect(pRENDINFO pRA, pLTENVIRON LI, WORLD R)
{

	RGBCOLOR	oC;
    /////////////////////////////////////////////// Texture
	////////////////////////////// Wood
	if( pRA->texture & TX_WOOD )
		oC = Wood
				( 
					R.x,R.y,R.z, oC, 
					pRA->tx[TXI_WOOD].txArgument[0], 
					pRA->tx[TXI_WOOD].txArgument[1], 
					pRA->tx[TXI_WOOD].txArgument[2] 
				);
	////////////////////////////// Rock
	if( pRA->texture & TX_ROCK )
		oC = Rock
				( 
					R.x,R.y,R.z, oC, 
					pRA->tx[TXI_ROCK].txArgument[0], 
					pRA->tx[TXI_ROCK].txArgument[1], 
					pRA->tx[TXI_ROCK].txArgument[2], 
					pRA->tx[TXI_ROCK].txArgument[3] 
				);
/*
	////////////////////////////// Picture
	if
	( pRA->texture & TX_PICT
		&& 	( 	pRA->tx[TXI_PICT].txArgument[1]>=0 || 
				pRA->tx[TXI_PICT].txArgument[1]<=-1000 
			)
	)
		oC = PICT
				( 	R.x,R.y,R.z, oC, 
					pRA->tx[TXI_PICT].txArgument[1], 
					pRA->tx[TXI_PICT].txArgument[2], 
					pRA->tx[TXI_PICT].txArgument[3] 
				);
*/					
	////////////////////////////// UserColor
//	if( pRA->texture & TX_USERCOLOR )        todo apitx.h
	if( 1 == 0 ) 
	{ 
/*		
        	if( LI.pudll != NULL )
        		if( LI.pudll->pTxEval != NULL )
        			LI.pudll->pTxEval( pRA, &R, &oC, &n );
*/        			
	}
	
	else 
    {
		////////////////////////////// RGB
		if( pRA->texture & TX_RGB )
			oC = R_G_B
					(	
						R.x,R.y,R.z, oC, 
						pRA->tx[TXI_RGB].txArgument[0] 
					);
		////////////////////////////// Depth
		if( pRA->texture & TX_DEPTH )
			oC = Depth
					( 
						R.x,R.y,R.z, oC,
						pRA->tx[TXI_DEPTH].txArgument[0],
						pRA->tx[TXI_DEPTH].txArgument[1] 
					);
	}
	//////////
	return oC;	

}
	 
/**********************************************************************************
 *
 *	Function:	Noise
 *
 *	Purpose:	Generates a three dimensional lattice of random noise coefficients,
 *				which are translationally and rotationally invariant.
 *
 *	Returns:	A noise coefficient interpolated to a given point in the space
 *				relative to the noise lattice.
 *
 **********************************************************************************
 */
 
#define	NOISE_MULT		10000
#define	R_NOISE_MULT	.0001
////////////////////////////
BOOL CTextures::Init_Noise()
{
	//////////////////////////////////////////////////
	//					WATT:p378 					//
	//////////////////////////////////////////////////
	long	ix,iy,iz;
	long	xx,yy,zz;
	double	drand;
    /////////////////////////////////////////////////// Seed
	//This seeds the random-number generatorwith the time //
	//the numbers will be different every time we run.    //
	srand( (unsigned)time( NULL ) );
    ////////////////////////////////////////////////////////
	//RAND_MAX; = 0x7fff
	/////////////////
	for(ix=0;ix<=MAX_LATTICE;ix++)
		for(iy=0;iy<=MAX_LATTICE;iy++)
			for(iz=0;iz<=MAX_LATTICE;iz++) 
			{
				drand = (double)rand()/(double)RAND_MAX;
				m_NoiseTable[ix][iy][iz] = (long)(drand*NOISE_MULT);
				////////////
				xx = (ix==MAX_LATTICE)?0L:ix;
				yy = (iy==MAX_LATTICE)?0L:iy;
				zz = (iz==MAX_LATTICE)?0L:iz;
				m_NoiseTable[ix][iy][iz] = 
					m_NoiseTable[xx][yy][zz];
			}
	////////////
	return TRUE;		
			
}

double CTextures::Noise
					(
						double x,	/* object space X coordinate								*/
						double y,	/* object space Y coordinate								*/
						double z	/* object space Z coordinate								*/
					)
{
	long	ix,iy,iz, n;
	double	ox,oy,oz,
			n00,n01,n10,n11,n0,n1;
    
	if( !m_bNoiseReady )
		return 0.0;
	//////////////////////////////////////////////////	
	x += SHRT_MAX;					// make them all>0
	y += SHRT_MAX;
	z += SHRT_MAX;
	//////////////
	ix = (long)x % MAX_LATTICE;
	iy = (long)y % MAX_LATTICE;
	iz = (long)z % MAX_LATTICE;
	ox = x - (long)x;
	oy = y - (long)y;
	oz = z - (long)z;
	/////////////////
	n	= m_NoiseTable[ix][iy][iz];
	n00	= n + ox * (m_NoiseTable[ix+1][iy][iz]   - n);
	n	= m_NoiseTable[ix][iy][iz+1];
	n01	= n + ox * (m_NoiseTable[ix+1][iy][iz+1] - n);
	n 	= m_NoiseTable[ix][iy+1][iz];
	n10	= n + ox * (m_NoiseTable[ix+1][iy+1][iz] - n);
	n 	= m_NoiseTable[ix][iy+1][iz+1];
	n11	= n + ox * (m_NoiseTable[ix+1][iy+1][iz+1]-n);
	//////////////////////
	n0 = n00+oy*(n10-n00);
	n1 = n01+oy*(n11-n01);
	////////////////////////////////////////
	return (n0 + oz * (n1-n0))*R_NOISE_MULT;
	////////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	FormLocalMatrix
 *
 *	Purpose:	Generates an instancing transformation matrix for use in mapping
 *				texture fields to points in the object space.
 *
 **********************************************************************************
 */
void CTextures::FormLocalMatrix
				(
				pMATRIX	pXF,//	destination matrix							
				WORLD	r,	//	rotations: pitch, yaw, roll					
				WORLD	s,	//	scale factors: x,y,z						
				WORLD	t	//	translations: x,y,z							
				)
{

	CXForm 	XForm;
	/////////////////////////////////////////
	XForm.Scale(pXF,s.x,s.y,s.z,XF_REPLACE);
	XForm.Rotate_X(pXF,r.x,XF_REPLACE);
	XForm.Rotate_Y(pXF,r.y,XF_REPLACE);
	XForm.Rotate_Z(pXF,r.z,XF_REPLACE);
	XForm.Translate(pXF,t.x,t.y,t.z,XF_REPLACE);
	/////////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	InverseLocalMatrix
 *
 *	Purpose:	Generates an inverse instancing matrix used to map object space to
 *				texture space.
 *
 **********************************************************************************
 */
void CTextures::InverseLocalMatrix
				(
				pMATRIX	pXF,//	destination matrix
				WORLD	r,	//	rotations: pitch, yaw, roll
				WORLD	s,	//	scale factors: x,y,z	
				WORLD	t	//	translations: x,y,z		
				)
{

	/////////////////
	C3DMath	Math3D;
	////////////////////////////
	FormLocalMatrix(pXF,r,s,t);							
	Math3D.TransposeMATRIX(pXF);
	////////////////////////////

}

/**********************************************************************************
 *
 *	Function:	TransformWorldToTexture
 *
 *	Purpose:	Maps a point in object space to a point in texture space through
 *				the application of a specified texture transformation matrix.  The
 *				transformed point coordinates are returned via parameters.
 *
 **********************************************************************************
 */
void CTextures::TransformWorldToTexture
				(
					pMATRIX	pXF,// texture mapping transform matrix					*/
					double	x,	// object space X coordinate						*/
					double	y,	// object space Y coordinate						*/
					double	z,	// object space Z coordinate						*/
					double	*X,	// returned texture space X coordinate				*/
					double	*Y,	// returned texture space Y coordinate				*/
					double	*Z	// returned texture space Z coordinate				*/
				)
{
	*X	= 	x * pXF->v[0][0] + 
			y * pXF->v[0][1] + 
			z * pXF->v[0][2] + 
				pXF->v[0][3];
	*Y	= 	x * pXF->v[1][0] + 
			y * pXF->v[1][1] + 
			z * pXF->v[1][2] + 
				pXF->v[1][3];
	*Z	= 	x * pXF->v[2][0] + 
			y * pXF->v[2][1] + 
			z * pXF->v[2][2] + 
				pXF->v[2][3];
}

/**********************************************************************************
 *
 *	Function:	WoodLocalMatrix
 *
 *	Purpose:	Calls LocalMatrix to generate an instancing matrix for the
 *				wood texture field.
 *
 **********************************************************************************
 */  
void CTextures::WoodLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFwood);
	////////////////////////////////////
	FormLocalMatrix( &m_XFwood, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	RockLocalMatrix
 *
 *	Purpose:	Calls LocalMatrix to generate an instancing matrix for the
 *				rock texture field.
 *
 **********************************************************************************
 */
void CTextures::RockLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFwood);
	////////////////////////////////////
	FormLocalMatrix( &m_XFrock, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	PICTLocalMatrix
 *
 *	Purpose:	Calls InverseLocalMatrix to generate an instancing matrix for
 *				the PICT texture field.
 *
 **********************************************************************************
 */
void CTextures::PICTLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFpict);
	////////////////////////////////////
	InverseLocalMatrix( &m_XFpict, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	RGBLocalMatrix
 *
 *	Purpose:	Calls LocalMatrix to generate an instancing matrix for the
 *				RGB texture field.
 *
 **********************************************************************************
 */
void CTextures::RGBLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFrgb);
	////////////////////////////////////
	FormLocalMatrix( &m_XFrgb, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	DepthLocalMatrix
 *
 *	Purpose:	Calls LocalMatrix to generate an instancing matrix for the
 *				depth texture field.
 *
 **********************************************************************************
 */
void CTextures::DepthLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFdepth);
	////////////////////////////////////
	FormLocalMatrix( &m_XFdepth, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	BumpsLocalMatrix
 *
 *	Purpose:	Calls LocalMatrix to generate an instancing matrix for the
 *				bumps texture field.
 *
 **********************************************************************************
 */
void CTextures::BumpsLocalMatrix
				(
					WORLD	r,	//	rotations: pitch, yaw, roll
					WORLD	s,	//	scale factors: x,y,z
					WORLD	t	//	translations: x,y,z	
				)
{
	///////////////
	C3DMath	Math3D;
	C3DMath* p3DMath;
	p3DMath->GetIdentityMATRIX(&m_XFbumps);
	////////////////////////////////////
	FormLocalMatrix( &m_XFbumps, r,s,t );
	/////////////////////////////////////
}

/**********************************************************************************
 *
 *	Function:	Wood
 *
 *	Purpose:	Given a point in object space coordinates, a base color and some
 *				modifier attributes, calculates and returns a color corresponding
 *				to a point in the current wood texture space.  Optionally, a noise
 *				scaling factor may be supplied which will cause a random variation
 *				in the appearance of the wood grain.  Light and dark coefficients
 *				are specified to control the intensity level of the light (wide)
 *				and dark (narrow) portions of the grain.  It is assumed that an
 *				appropriate wood texture transform has been established prior to
 *				calling this function.
 *
 *				Assuming the wood texture transform is set to identity (0,0,0,
 *				1,1,1,0,0,0) the wood grain field will appear to be a concentric
 *				series of vertically oriented cylinders (symmetric about the Y
 *				axis) whose surfaces have been deformed in a sinusoidal pattern
 *				(think of corrogated sheet metal rolled into a tube, such that the
 *				corrogations are aligned with the length of the tube).  A given
 *				set of object space coordinates may be considered to represent a
 *				block cut out of the wood texture field.
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CTextures::Wood
					(
					double		u,		//	object space X coordinate					
					double		v,		//	object space Y coordinate					
					double		w,		//	object space Z coordinate					
					RGBCOLOR	c,		//	base color (object reflection
										//  	coefficients)	
					double		NoiseFac,//	periodic noise field scaling factor			
					double		light,	//	light grain color scaling factor			
					double		dark	//	dark grain color scaling factor				
					)
{
	double		scale,angle,radius;
	int			grain;
	RGBCOLOR	rgb;
    /////////////////////////////////////////
	TransformWorldToTexture(&m_XFwood,u,v,w,&u,&v,&w);
    ////////////////
    angle	= (w==0)?1.5707963267949:atan2(w,u); 
    radius 	= sqrt(u*u+w*w);
    radius += 2 * sin(20 * angle + v/150) + 0.5;
    grain	= ((int)radius) % 60;
    ////////////// 
	if(grain < 40)
		scale = (NoiseFac!=0)?NoiseFac * Noise(u,v,w) * light:light;
	else
		scale = (NoiseFac!=0)?NoiseFac * Noise(u,v,w) * dark:dark;
	////////////////////	
	rgb = c;
	rgb.red		*=scale;
	rgb.green	*=scale;
	rgb.blue	*=scale;
	///////////
	return rgb;
}

/**********************************************************************************
 *
 *	Function:	Rock
 *
 *	Purpose:	Given a point in object space coordinates, a base color and some
 *				modifier attributes, calculates and returns a color corresponding
 *				to a point in the current rock texture space.  By varying the rock
 *				texture transform, and the bandwidth and grain color scale factors
 *				camoflage, marble, granite and a large number of other turbulent
 *				textures may be generated.
 *
 *				Assuming the rock texture transform is set to identity (0,0,0,
 *				1,1,1,0,0,0) the rock grain field will appear to be a turbulent
 *				series of waves.  A given set of object space coordinates may be
 *				considered to represent a block cut from the rock texture field.
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CTextures::Rock
					(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double		BandWidth,//total width of the four grain bands			
						double		f1,		//	light grain color scaling factor			
						double		f2,		//	intermediate grain color scaling factor		
						double		f3		//	dark grain color scaling factor				
					)
{
	double		d,dd,scale,n;
	RGBCOLOR	rgb;
	int			band[4];
    ///////////////////////////
	band[0] = (int)BandWidth + 1;
	band[1] = (int)BandWidth/4;
	band[2] = 2 * band[1] + 1;
	band[3] = 3 * band[1];
    ////////////////////////////////////////////////// 
	TransformWorldToTexture( &m_XFrock, u,v,w,&u,&v,&w);
	//////////////////////////////////////////////////
	n 	= Noise(u,v,w);
	d 	= u*0.02 + 7*n;
	n	*= 0.2;
	dd 	= (int)d %band[0];
	//////////////////////
	if(dd<band[1])
		scale = f1 + n;
	else
	if(dd<band[2] || dd>=band[3]) {
		d 		-= ((int)(d*0.058823529411765F))*band[0]-10.5F; // .058823529411765=1/17th 
		d 		= fabs(d) * 0.1538462;
		scale 	= f2 + 0.3F*d+n;
	}
	else
		scale	= f3 + n;
	////////////////////	
	rgb = c;
	rgb.red		*=scale;
	rgb.green	*=scale;
	rgb.blue	*=scale;
	///////////
	return rgb;
}

/**********************************************************************************
 *
 *	Function:	PICTinit
 *
 *	Purpose:	Loads into memory a picture (bitmap) to be mapped onto an object.
 *				If a bitmap resource named xxxx or a file named xxxx.bmp is
 *				found it is loaded into an memory device context.	A stack
 *				of active pictures is maintained to allow disposal for memory
 *				management purposes.  A new pixel queue is allocated to expedite
 *				the antialiasing functions used when mapping the picture to object
 *				space.	The PICT texture transform is set to default values which
 *				if not overriden will fit the picture into a specified bounds box.
 *
 **********************************************************************************
 */
void CTextures::PICTinit
				(
					STR4	PICTid,	// resource id of the PICT to load	
					pBox	bounds	// rectangle into which the PICT is to be fitted	
				)
{
/*                                    todo
	pphList		tpphl = pphl;
	Rect		R;
	BITMAP		BM;
	char		name[10];
	HDC 		hDC = GetCurrentDC();

	if( !hDC ) {
		OutputDebugString( "hDC NULL." );
		return;
	}

	memcpy( name, &PICTid, 4 );
	name[4] = 0x00;
	while( tpphl ) {
		if( !strcmp( tpphl->name, name ) ) {
			ph = tpphl->ph;
			break;				// already in the stack
		}
		tpphl = tpphl->prior;
	}
	if( !tpphl ) {				// new stack entry needed
		if( !( ph = LoadBitmap( ghInst, name ) ) ) {
			char	bmpfilename[10];
			bmpfilename[0] = 0x00;
			strcpy( bmpfilename, name );
			strcat( bmpfilename, ".BMP" );
			if( !( ph = LoadBMPFile( hDC, bmpfilename )) ) {
				OutputDebugString( "BMP missing." );
				return; // neither found as resource or as file
			}
		}
		tpphl = (pphList)NewPtr( sizeof(phList) );
		tpphl->ph = ph;
		tpphl->name[0] = 0x00;
		strncpy( tpphl->name, name, 9 );
		tpphl->prior = pphl;
		pphl = tpphl;
	}

	GetObject( (HANDLE)ph, (int)sizeof(BITMAP), (LPSTR)&BM );
	SetRect( &rPic, 0, 0, BM.bmWidth, BM.bmHeight );

	ox = 0.5F*rPic.right;
	oy = 0.5F*rPic.bottom;
	dr.h = rPic.right-rPic.left;
	dr.v = rPic.bottom-rPic.top;

	R.left	= (int)bounds->min.x;
	R.right	= (int)bounds->max.x;
	R.top	= (int)bounds->min.y;
	R.bottom= (int)bounds->max.y;
	OffsetRect( &R, -R.left, -R.top );
	if( rPic.right > R.right || rPic.bottom > R.bottom ) {
		double scale;
		WORLD	nul={f_0,f_0,f_0}, scl;
		scale = (rPic.right>rPic.bottom)? rPic.right  : rPic.bottom;
		scale /= (rPic.right>rPic.bottom)? R.right : R.bottom;
		scl.x = scl.y = scl.z = (long)(scale*65536);
		PICTLocalMatrix( nul, scl, nul );
	}
	hDCm = CreateCompatibleDC( hDC	);
	PICTpixQ = NewPixQ();
*/	
}

/**********************************************************************************
 *
 *	Function:	PICTterm
 *
 *	Purpose:	Unlocks the current PICT and marks it purgeable.  Disposes of the
 *				offscreen PICT image and the pixel queue allocated by PICTinit.
 *
 **********************************************************************************
 */
void CTextures::PICTterm(void)
{
/*
	if( PICTpixQ )
		DisposePixQ( PICTpixQ );
	if( hDCm )
		DeleteDC( hDCm );
	PICTpixQ = 0L;
	SetDefPixQ();
	ph = 0L;
*/	
}

/**********************************************************************************
 *
 *	Function:	PICTcleanup
 *
 *	Purpose:	Releases all PICT handles in the active PICT stack and the stack
 *				itself (a memory cathartic).
 *
 **********************************************************************************
 */
void CTextures::PICTcleanup(void)
{ 
/*
	pphList	tpphl;

	while( pphl ) {
		DeleteObject( pphl->ph );
		tpphl = pphl;
		pphl = pphl->prior;
		DisposPtr( (Ptr)tpphl );
	}
*/	
}

/**********************************************************************************
 *
 *	Function:	PICT
 *
 *	Purpose:	Given a point in object space coordinates and a base color derives
 *				and returns a color corresponding to a point in the current PICT
 *				texture space.  An optional argument allows the PICT texture to be
 *				considered as repeating endlessly throughout the texture space and
 *				or to contain transparent parts.  Setting the repeat parameter to
 *				1 or 3 results in a repeating picture.  Values of 2 or 3 cause all
 *				black pixels to be considered transparent.
 *
 *				Assuming the PICT texture transform is set to identity (0,0,0,
 *				1,1,1,0,0,0) the PICT will appear as though projected onto a flat
 *				plate in the X/Y plane.
 *
 *				In general, small PICT transform scaling factors enlarge the PICT
 *				image relative to the object; larger factors reduce the PICT image
 *				relative to the object.
 *
 *				To project a PICT onto a specific facet of an object, set the PICT
 *				texture transform to the instancing transform of the facet.
 *
 *				Flat, cylindrical and spherical projections of the selected PICT
 *				are available by setting the lat and lon parameters as follows:
 *
 *					Projection	Lat	Lon
 *					-----------	---	---
 *					Flat		  0	  0
 *					Cylindrical	120	  0
 *					Spherical	180	360
 *
 *				Variations in the cylidrical and spherical projections may be used
 *				by using values other than those above.
 *
 *				The color returned for a given object space point is the product of
 *				the base color supplied and an antialiased value of a 3x3 matrix of
 *				sample points centered on the texture space coordinates.  Mappings
 *				which result in many PICT pixels per object pixel product blended
 *				reductions of the PICT image.  Mappings which result in the inverse
 *				result in a chunky enlargement of the PICT image, similar to the
 *				effect of calling DrawPicture with a rectangle larger than the
 *				original Picture bounding box.  In both cases, the result is in the
 *				object space and will be subject to additional transformations when
 *				the object is drawn.
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CTextures::PICT
					(
						double		u,		//	object space X coordinate					  
						double		v,		//	object space Y coordinate					  
						double		w,		//	object space Z coordinate					  
						RGBCOLOR	c,		//	base color (object reflection coefficients)	  
						double		repeat,	//	1|3 repeating pict; 2|3 black=transparent	  
						double		lat,	//	latitude mapping rangeø (sphere ONLY)		  
						double		lon		//	longitude mapping rangeø (sphere/cylinder)	  
					)
{

	RGBCOLOR	rgb;
/*	
	RGBColor	pixColor;
	Point		p;
	HDC 		hDC;
    //////////////////////////////////////////////////
	if( !ph )
		return c;	// no PICT or no offscreen port 
    /////////////////////////////////////////////////
	TransformTexture( &XFpict, u, v, w, &u, &v, &w );
    /////////////////////////////////////////////////
	if( lat != 0.0F )	//	map to sphere	
		v = (float)asin( v / tSqrt(u*u+v*v+w*w) ) * dr.v * 57.295779513082F / lat;
	if( lon != 0.0F )	//	map to cylinder	
		u = (float)atan2( w, u ) * dr.h * 57.295779513082F / lon;
	if( repeat==1.0F || repeat==2.0F ) {
		p.h = (int)( u + ox) % rPic.right;
		p.v = (int)(-v + oy) % rPic.bottom;
		while( p.h < 0 )
			p.h += rPic.right;
		while( p.v < 0 )
			p.v += rPic.bottom;
	}
	else {
		p.h = (int)( u + ox);
		p.v = (int)(-v + oy);
	}

	hDC = GetCurrentDC();
	SetCurrentDC( hDCm );
	SelectObject( hDCm, ph );

	SetPixQ( PICTpixQ );

	GetQueuePixel( p.h, p.v, &pixColor );

	if( (repeat < 2.0F) || pixColor.red || pixColor.green || pixColor.blue ) {
		//	not the transparent part of the PICT (all black)
		ConvolutionColor( p.h, p.v, W1, W2, W3, (pRGBCOLOR)&pixColor );
		rgb			= c;
		rgb.red		*= pixColor.red   * 0.0000152587890625F;
		rgb.green	*= pixColor.green * 0.0000152587890625F;
		rgb.blue	*= pixColor.blue  * 0.0000152587890625F;

	}
	else {
		//	this is the black (transparent) part of a PICT texture
		//	so we return zeros to the caller to indicate such
		rgb.red = rgb.green = rgb.blue = 0;
	}

	SetCurrentDC( hDC );

	SetDefPixQ();
*/
	return rgb;
}
//////////////////////////////////////////////////////////////////////////
#define	SET3D(p,a,b,c)	{(p).x=(a);(p).y=(b);(p).z=(c);}
#define ADD(a, b, c)	{(a).x=(b).x+(c).x;(a).y=(b).y+(c).y;(a).z=(b).z+(c).z;}
#define SUB(a, b, c)	{(a).x=(b).x-(c).x;(a).y=(b).y-(c).y;(a).z=(b).z-(c).z;}
#define SCALE(a, k)		{(a).x*=(k);(a).y*=(k);(a).z*=(k);}
#define CROSS(a,b,c)	{(a).x=(b).y*(c).z-(b).z*(c).y; \
						(a).y=(b).z*(c).x-(b).x*(c).z; \
						(a).z=(b).x*(c).y-(b).y*(c).x;}

#define MAG(b)			sqrt((b).x*(b).x+(b).y*(b).y+(b).z*(b).z)
#define NORM(a)			{ d=MAG((a)); d = (d!=0.0)? (1.0/d):1.0;\
							 (a).x*=d; (a).y*=d; (a).z*=d; }
/*							 
#define R64K			0.0000152590218966F
#define	NC(a)			(a)*R64K
#define	LUMINANCE(a)	(NC(0.229F*(a).red)+NC(0.587F*(a).green)+NC(0.114F*(a).blue))
*/
/////////////////////////////////////////////////////////////////////////////////////
WORLD CTextures::PICTbump
				(
					double		u,		//	object space X coordinate					
					double		v,		//	object space Y coordinate					
					double		w,		//	object space Z coordinate					
					WORLD		N,		//	surface normal vector						
					double		scalar,	//	luminance scaling factor					
					double		lat,	//	latitude mapping rangeø (sphere ONLY)		
					double		lon		//	longitude mapping rangeø (sphere/cylinder)	
				)
{
/*
	double		d, m;
	WORLD	p1, p2, p3, vx, vy, vz, bN, vt;
	RGBColor	c;
	Point		p;
	HDC 		hDC;
	double		k = 57.295779513082F;

	if( !ph )
		return N;	// pict was not usable during init for some reason

	TransformTexture( &XFpict, u, v, w, &u, &v, &w );

	if( lat != 0.0F ) {	//	map to sphere
		double d = tSqrt(u*u+v*v+w*w);
		v = (float)asin( d==0.0F? 0.0F : (v/d) ) * dr.v * k / lat;
    }
	if( lon != 0.0F )	//	map to cylinder
		if( w!=0.0F )
			u = (float)atan2( w, u ) * dr.h * k / lon;
		else
			u = 0.0F;
	p.h = (int)( u + ox) % rPic.right;
	p.v = (int)(-v + oy) % rPic.bottom;
	while( p.h < 0 )
		p.h += rPic.right;
	while( p.v < 0 )
		p.v += rPic.bottom;

	if( p.v<rPic.top+1 || p.v>rPic.bottom-1 || p.h<rPic.left+1 || p.h>rPic.right-1 )
    	return N;

	hDC = GetCurrentDC();
	SetCurrentDC( hDCm );
	SelectObject( hDCm, ph );
	SetPixQ( PICTpixQ );
	GetQueuePixel( p.h, p.v, &c );
	SET3D( p1, 0, scalar * LUMINANCE( c ), 0 );
	GetQueuePixel( p.h-1, p.v+1, &c );
	SET3D( p2, 0, scalar * LUMINANCE( c ), 1 );
	GetQueuePixel( p.h+1, p.v+1, &c );
	SET3D( p3, 1, scalar * LUMINANCE( c ), 1 );
	SetCurrentDC( hDC );
	SetDefPixQ();

	SUB( vx, p1, p2 );
	SUB( vy, p3, p2 );
	CROSS( bN, vy, vx );
	NORM( bN );

	SET3D( vy, N.x, N.y, N.z );
	SET3D( vt, 0.0F, 1.0F, 0.0F );
	CROSS( vx, vy, vt );
	m = MAG( vx );
	if( m < 1.0e-9F ) {
    	m = 1.0F;
		SET3D( vx, 1.0F, 0.0F, 0.0F );
		if( (float)fabs( N.y - 1.0F )<0.001F ) {
			SET3D( vy, 0.0F, 1.0F, 0.0F );
		}
		else {
			SET3D( vy, 0.0F, -1.0F, 0.0F );
		}
	}
    m = 1.0F / m;
	SCALE( vx, m );
	CROSS( vz, vx, vy );
	NORM( vz );
	SCALE( vx, bN.x );
	SCALE( vy, bN.y );
	SCALE( vz, bN.z );
	ADD( vt, vx, vy );
	ADD( N, vt, vz );
	NORM( N ); 
*/	
	return N;
}

/**********************************************************************************
 *
 *	Function:	R_G_B
 *
 *	Purpose:	Given a point in object space coordinates and a base color returns
 *				a color corresponding to a point in the current RGB texture space.
 *				An optional noise coefficient may be supplied to roughen and deform
 *				the appearance of the RGB texture field.
 *
 *				Assuming the RGB texture transform is set to identity (0,0,0,
 *				1,1,1,0,0,0) the RGB field is oriented with its red, green and
 *				blue axes aligned with the X, Y and Z object space axes.  Black is
 *				located at the origin and white at coordinates 65535,65535,65535.
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CTextures::R_G_B
					(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double 		NoiseFac//	periodic noise field scaling factor			
					)
{
	RGBCOLOR	rgb;
	double		d;
    ////////////////////////////////////////////////
	TransformWorldToTexture( &m_XFrgb, u, v, w, &u, &v, &w );
	////////////////////////////////////////////////
	d = sqrt( u*u+v*v+w*w ) * 
			((NoiseFac!=0.0F)?NoiseFac*Noise(u,v,w):1.0);
	/////////////			
	if( d==0.0 )
		return c;
	/////////////	
	d = 1.0 / d;
	/////////
	rgb = c;
	
	rgb.red		*=u*d;
	rgb.green	*=v*d;
	rgb.blue	*=w*d;
	///////////
	return rgb;
}

/**********************************************************************************
 *
 *	Function:	Depth
 *
 *	Purpose:	Given a point in object space coordinates, a base color and a depth
 *				modulus, calculates and returns an intensity corresponding to the
 *				relative depth of the object space point in the depth field.  The
 *				depth modulus establishes the range of values corresponding to the
 *				maximum and minimum intensities.  Maximum intensity is at zero and
 *				minimum at the modulus.
 *
 *				Assuming the depth texture transform is set to identity (0,0,0,
 *				1,1,1,0,0,0) the depth field appears as a series of gray levels
 *				where white is near zero and black is near the modulus value.
 *
 *	Returns:	RGB color coefficients.
 *
 **********************************************************************************
 */
RGBCOLOR CTextures::Depth
					(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double 		NoiseFac,//	periodic noise field scaling factor			
						double 		Modulus  
					)
{

	RGBCOLOR		rgb;
	double			d;
    /////////////////////
	if( Modulus == 0.0 )
		return c;
    /////////////////////////////////////////////////////////
	TransformWorldToTexture( &m_XFdepth, u, v, w, &u, &v, &w );
    /////////////////////////////////////////////////////////
	d = 1.0 - ((int)sqrt( u*u+v*v+w*w ) % 
				(int)Modulus) / Modulus * 
				((NoiseFac!=0.0F)?NoiseFac*Noise(u,v,w):1.0);
	/////////				
	rgb = c;
	
	rgb.red		*=d;
	rgb.green	*=d;
	rgb.blue	*=d;
	///////////
	return rgb;
}

/**********************************************************************************
 *
 *	Function:	PerturbNormal
 *
 *	Purpose:	Given a point in object space coordinates, a normal vector and some
 *				modifier attributes, calculates and returns a normal vector altered
 *				by the current bump texture space.  The effect is a disturbance of
 *				the normal vector supplied, which results in a pebbly texture.
 *
 *	Returns:	modified normal vector.
 *
 **********************************************************************************
 */
WORLD CTextures::PerturbNormal
					(
						double u,
						double v,
						double w,	//	object space coordinates	
						WORLD N,	//	input normal vector			
						double a,	//	noise scalar				
						double b,	//	cos scalar					
						double c,	//	sin scalar					
						double atten//  attenuation factor			
					)
{

	double	d, m;
	WORLD	p1, p2, p3, vx, vy, vz, bN, vt,n;
    double	n0,n1,n2;
    //////////////////////////////////////////////////
	TransformWorldToTexture( &m_XFbumps, u, v, w, &u, &v, &w );
    //////////////////////////////////////////////////
	n0 = a * Noise(u,v,w);
	n1 = a * Noise(w,u,v);
	n2 = a * Noise(w,v,u);
	if( b != 0.0 ) 
	{
		n0 *= b*cos(u+n0);
		n1 *= b*cos(v+n1);
		n2 *= b*cos(w+n2);
	}
	if( c != 0.0 ) 
	{
		n0 *= c*sin(v+n0);
		n1 *= c*sin(w+n1);
		n2 *= c*sin(u+n2);
	}
	////////////////////////////
	SET3D( p1, 0, atten*n0, 0 );
	SET3D( p2, 0, atten*n1, 1 );
	SET3D( p3, 1, atten*n2, 1 );
    //////////////////
	SUB( vx, p1, p2 );
	SUB( vy, p3, p2 );
	CROSS( bN, vy, vx );
	NORM( bN );
    //////////////////////////////
	SET3D( vy, N.x, N.y, N.z );
	SET3D( vt, 0.0, 1.0, 0.0 );
	
	CROSS( vx, vy, vt );
	m = MAG( vx );
	////////////////
	if( m < 1.0e-9 ) 
	{
    	m = 1.0;
		SET3D( vx, 1.0, 0.0, 0.0 );
		if( fabs( N.y - 1.0 ) < 0.001 ) 
		{
			SET3D( vy, 0.0, 1.0, 0.0 );
		}
		else 
		{
			SET3D( vy, 0.0, -1.0, 0.0 );
		}
	}
	
    m = 1.0 / m;
    
	SCALE( vx, m );
	CROSS( vz, vx, vy );
	NORM( vz );
	SCALE( vx, bN.x );
	SCALE( vy, bN.y );
	SCALE( vz, bN.z );
	ADD( vt, vx, vy );
	ADD( n, vt, vz );
	NORM( n );
	///////////////////////////////////
	if( (n.x*N.x+n.y*N.y+n.z*N.z) < 0 )
		return N;
	/////////	
	return n;
	
}

void CTextures::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Textures:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" Textures:    Loading\n");	// TODO: add loading code here
	}
		
}
/////////////////////////////////// end of module //////////////
