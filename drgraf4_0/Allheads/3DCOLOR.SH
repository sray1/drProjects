/*****************************************************************************
 *	File:	3dColor.h
 *
 *	Version:	Microsoft C / Windows
 *
 *	(C) 1994 Mark M. Owen.	All rights reserved.
 *****************************************************************************
 */
#ifndef _3dColor_
#define _3dColor_  

#include "globals.h"
//#include <3d.h>
enum alignment	{
	leftAlign, rightAlign, centerAlign,
	aligmentSize16 = 32767
};


#define	TXARGS	4
#define	TXLIMIT	6

enum textureIndices {
	TXI_WOOD,
	TXI_ROCK,
	TXI_PICT,
	TXI_BUMPS,
	TXI_RGB,
	TXI_DEPTH
	};

#define TXI_MIN TXI_WOOD
#define TXI_MAX TXI_DEPTH

enum textures		{
	TX_NONE		=   0,
	TX_WOOD		=   1,
	TX_ROCK		=   2,
	TX_PICT		=   4,
	TX_BUMPS	=   8,
	TX_RGB		=  16,
	TX_DEPTH	=  32,
	TX_USERBIT	=  64,	// use with RGB or DEPTH (see apitx.h)
	TX_LABEL	= 128,	//	exclusive
	TX_LINES	= 512	//	exclusive
	};

#define fract16			unsigned short
typedef struct { fract16 red; fract16 green; fract16 blue; }		RGBColor, __far *pRGBColor;
typedef struct { fract16 hue; fract16 saturation; fract16 value; }	HSVColor, __far *pHSVColor;
typedef	unsigned short	colorFactor;	// 65536= 1 (SmallFract)	
typedef	unsigned short	colorIndex;
//typedef Fixed			coefficient;
typedef double			coefficient;

typedef struct
{
	WORLD			txRotations;		// texture field rotations in degrees		
	WORLD			txScalars;			// texture field scaling factors			
	WORLD			txTranslations;		// texture field displacements				
	coefficient		txArgument[TXARGS];	// texture type dependent arguments			
}	txInfo,  __far *ptxInfo;

typedef	struct
{
	colorFactor		R,G,B;				// RGB reflected color coefficients			
	coefficient		diffusion;			// diffuse reflection coefficient			
	colorIndex		specIndex;			// specular reflection index				
	RGBColor		frameColor;			// frame RGB reflected color coefficients	
	unsigned short	lightSource:1,		// emits light?								
					distanceEffect:1,	// apply light source distance?				
					ambientEffect:1,	// apply ambient light effects?				
					normalVisibility:1,	// visibility based on facet normals?		
					framed:1,			// frame the facets?						
					patterned:1,		// use pix patterns? or solids - Mac only!				
					grayScaled:1,		// use gray scale patterns? - Mac only!
					wireframed:1,		// wireframe override                       
					hazing:1,			// atmospheric hazing effects?				
					refconPen:1,		// refcon context: TRUE - pen, FALSE - proc
					extraBits:6;		// unused... reserved for expansion			

	coefficient		specularity;		// specular reflection coefficient			
	coefficient		ambience;			// not used. retained for compatibility		
	coefficient		absorption;			// reserved for expansion					
	coefficient		translucence;		// reserved for expansion					
	coefficient		refraction;			// reserved for expansion					
	coefficient		transparency;		// transparency coefficient	( 0 = opaque )	
	enum textures	texture;			// texture type code						
	txInfo			tx[TXLIMIT];
}
	RendAttr, __far *pRendAttr;
/*
typedef struct {	// do not exceed sizeof(txInfo)*TXLIMIT bytes in length
	enum alignment	aligned;
	char			label[256];
	BOOL			bStockFont;
	HFONT			hFont;
}	TxLabel, __far *pTxLabel;

#define	TX_STRING(ra)		((pTxLabel)(&(ra).tx)[0])->label
#define	TX_ALIGNED(ra)		((pTxLabel)(&(ra).tx)[0])->aligned
#define	TX_BSTOCKFONT(ra)	((pTxLabel)(&(ra).tx)[0])->bStockFont
#define	TX_HFONT(ra)		((pTxLabel)(&(ra).tx)[0])->hFont

typedef struct {
	WORD	penPat[8];	// used to create a 4x4 monochrome bitmap
	short	penSize;
}
	TxLines, __far *pTxLines;

#define	TX_PATTERN(ra)	(LPSTR)((pTxLines)(&(ra).tx)[0])->penPat
#define	TX_PENSIZE(ra)	(int)((pTxLines)(&(ra).tx)[0])->penSize


typedef struct
{
	RGBColor	color;				//	light color (RGB) emitted by the source 
	HSVColor	hsvColor;			//	light color (HSV)						
	Fixed		level;				//	intensity scaling factor for the source 
	WORLD		location;			//	location of the light source in space	
	WORLD		focus;				//	focal point for directional lights		
	WORLD		normal;				//	direction the source points towards		
	FPType		x,y,z;				//	location in floating point notation		
	FPType		fx,fy,fz;			//	focal point in floating point notation	
	FPType		nx,ny,nz;			//	direction in floating point notation	
	FPType		shape;				//	shape exponent index					
	FPType		limitAngle;			//	cutoff angle							
	FPType		magnitude;			//	effective magnitude of source ‰RGB=max	
}
	LtSource, __far *pLtSource;

typedef	struct
{
	RGBColor	color;				//	light color (RGB) emitted by the source 
	Fixed		level;				//	intensity scaling factor for the source 
	FPType		magnitude;			//	effective magnitude of source ‰RGB=max	
	FPType		Ra,Ga,Ba;			//	ambience levels c*lvl					
	int			nSources;			//	number of point light sources (0=none)	
	LtSource	source[];			//	array of point light sources			
}
	Lighting, __far *pLighting;


#define HUEUNDEFINED	-1

#define cs2rgb			257
#define rgb2cs			0.0038910505836576F

#define	CS2RGBColor(cs,rgb) \
	(rgb).red   = (fract16)(GetRValue((cs))*cs2rgb);\
	(rgb).green = (fract16)(GetGValue((cs))*cs2rgb);\
	(rgb).blue  = (fract16)(GetBValue((cs))*cs2rgb);

#define	RGBColor2CS(rgb) \
	PALETTERGB(	(BYTE)((rgb).red  *rgb2cs), \
				(BYTE)((rgb).green*rgb2cs), \
				(BYTE)((rgb).blue *rgb2cs) )

#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++ 
#endif	// __cplusplus 

void		API3D RGB2HSV(pRGBColor rgb,pHSVColor hsv);
void		API3D HSV2RGB(pHSVColor hsv,pRGBColor rgb);

pLighting	API3D NewLighting		(colorFactor R,colorFactor G,colorFactor B,Fixed lvl,int nS,pLtSource pLS);
void		API3D Set3dLtSource		(pLtSource pLS,colorFactor R,colorFactor G,colorFactor B,Fixed lvl,Fixed x,Fixed y,Fixed z);
void		API3D AimLightSource	(pLtSource pLS,Fixed x,Fixed y,Fixed z);
void		API3D TransformLighting	(pLighting pL,pMatrix xf);

HBRUSH		API3D ColorRgn			(WORLD C,WORLD N,Fixed d,pRendAttr pRA,pLighting pL);

#ifdef __cplusplus
}                       // End of extern "C" { 
#endif	// __cplusplus   
*/
////////////////////////////////////////////////
#endif
