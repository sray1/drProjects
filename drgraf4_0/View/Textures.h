// CTextures.h : header file
//
#ifndef _TEXTURES_H_
#define _TEXTURES_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Rend.h"
#include "Def_Type.h"
///////////////////////
#define	MAX_LATTICE		10
typedef unsigned long	STR4;// a four byte, unterminated string
/////////////////////////////////////////////////////////////////////////////
// CTextures
/////////////////////////////////////////////////////////////////////////////
class CTextures : public CObject
{
// Construction
public:  
	CTextures();
	DECLARE_SERIAL(CTextures)
protected: 
public:
// Implementation
public:

	virtual void 		Init(pRENDINFO pRA, pLTENVIRON LI);
	virtual void 		Terminate(pRENDINFO pRA, pLTENVIRON LI);
	virtual RGBCOLOR 	TextureEffect(pRENDINFO pRA, pLTENVIRON LI, WORLD R);
	virtual WORLD 		EffectiveNormal(pRENDINFO pRA, pLTENVIRON LI,
									 WORLD N,WORLD R);
	virtual BOOL 		Init_Noise();
	virtual RGBCOLOR 	Wood
						(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection
											//  coefficients)	
						double		NoiseFac,//	periodic noise field scaling factor			
						double		light,	//	light grain color scaling factor			
						double		dark	//	dark grain color scaling factor				
						);
	virtual RGBCOLOR 	Rock
						(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double		BandWidth,//total width of the four grain bands			
						double		f1,		//	light grain color scaling factor			
						double		f2,		//	intermediate grain color scaling factor		
						double		f3		//	dark grain color scaling factor				
						);
	virtual void 		PICTinit
						(
						STR4	PICTid,	// resource id of the PICT to load	
						pBox	bounds	// rectangle into which the PICT is to be fitted	
						);
	virtual void 		PICTterm(void);
	virtual void 		PICTcleanup(void);
	virtual RGBCOLOR 	PICT
						(
						double		u,		//	object space X coordinate					  
						double		v,		//	object space Y coordinate					  
						double		w,		//	object space Z coordinate					  
						RGBCOLOR	c,		//	base color (object reflection coefficients)	  
						double		repeat,	//	1|3 repeating pict; 2|3 black=transparent	  
						double		lat,	//	latitude mapping rangeø (sphere ONLY)		  
						double		lon		//	longitude mapping rangeø (sphere/cylinder)	  
						);
	virtual WORLD 		PICTbump
						(
						double	u,		//	object space X coordinate					
						double	v,		//	object space Y coordinate					
						double	w,		//	object space Z coordinate					
						WORLD	N,		//	surface normal vector						
						double	scalar,	//	luminance scaling factor					
						double	lat,	//	latitude mapping rangeø (sphere ONLY)		
						double	lon		//	longitude mapping rangeø (sphere/cylinder)	
						);
	virtual RGBCOLOR 	R_G_B
						(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double 		NoiseFac//	periodic noise field scaling factor			
						);
	virtual RGBCOLOR	Depth
						(
						double		u,		//	object space X coordinate					
						double		v,		//	object space Y coordinate					
						double		w,		//	object space Z coordinate					
						RGBCOLOR	c,		//	base color (object reflection coefficients)	
						double 		NoiseFac,//	periodic noise field scaling factor			
						double 		Modulus  
						);

protected:

	virtual double 		Noise
						(
							double x,	/* object space X coordinate								*/
							double y,	/* object space Y coordinate								*/
							double z	/* object space Z coordinate								*/
						);
						
	virtual void 		FormLocalMatrix
						(
							pMATRIX	pXF,//	destination matrix							
							WORLD	r,	//	rotations: pitch, yaw, roll					
							WORLD	s,	//	scale factors: x,y,z						
							WORLD	t	//	translations: x,y,z							
						);
						
	virtual void 		InverseLocalMatrix
						(
							pMATRIX	pXF,//	destination matrix
							WORLD	r,	//	rotations: pitch, yaw, roll
							WORLD	s,	//	scale factors: x,y,z	
							WORLD	t	//	translations: x,y,z		
						);
						
	virtual void 		TransformWorldToTexture
						(
							pMATRIX	pXF,// texture mapping transform matrix					*/
							double	x,	// object space X coordinate						*/
							double	y,	// object space Y coordinate						*/
							double	z,	// object space Z coordinate						*/
							double	*X,	// returned texture space X coordinate				*/
							double	*Y,	// returned texture space Y coordinate				*/
							double	*Z	// returned texture space Z coordinate				*/
						);
						
	virtual void 		WoodLocalMatrix
						(
							WORLD	r,	//	rotations: pitch, yaw, roll
							WORLD	s,	//	scale factors: x,y,z
							WORLD	t	//	translations: x,y,z	
						);
						
	virtual void 		RockLocalMatrix
						(
							WORLD	r,	//	rotations: pitch, yaw, roll
							WORLD	s,	//	scale factors: x,y,z
							WORLD	t	//	translations: x,y,z	
						);
						
	virtual void 		PICTLocalMatrix
						(
							WORLD	r,	//	rotations: pitch, yaw, roll
							WORLD	s,	//	scale factors: x,y,z
							WORLD	t	//	translations: x,y,z	
						);
						
	virtual void 		RGBLocalMatrix
						(
						WORLD	r,	//	rotations: pitch, yaw, roll
						WORLD	s,	//	scale factors: x,y,z
						WORLD	t	//	translations: x,y,z	
						);
						
	virtual void 		DepthLocalMatrix
						(
						WORLD	r,	//	rotations: pitch, yaw, roll
						WORLD	s,	//	scale factors: x,y,z
						WORLD	t	//	translations: x,y,z	
						);
						
	virtual void 		BumpsLocalMatrix
						(
						WORLD	r,	//	rotations: pitch, yaw, roll
						WORLD	s,	//	scale factors: x,y,z
						WORLD	t	//	translations: x,y,z	
						);
						
	virtual WORLD 		PerturbNormal
						(
						double u,
						double v,
						double w,	//	object space coordinates	
						WORLD  N,	//	input normal vector			
						double a,	//	noise scalar				
						double b,	//	cos scalar					
						double c,	//	sin scalar					
						double atten//  attenuation factor			
						);


protected:


	BOOL	m_bNoiseReady;	// if true NoiseTable Initiated
	long	m_NoiseTable[MAX_LATTICE+1][MAX_LATTICE+1][MAX_LATTICE+1];
    /////////////////////
	MATRIX	m_XFwood,		// Instance Matrices
			m_XFrock,
			m_XFbumps,
			m_XFrgb,
			m_XFdepth,
			m_XFpict;

protected: 

public:
	virtual ~CTextures(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CTextures)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
