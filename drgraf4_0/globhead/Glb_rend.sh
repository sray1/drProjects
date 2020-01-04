#ifndef _GLOBREND_H_
#define _GLOBREND_H_
                                               
#include "glb_Type.h"
#include "Windows.h"
///////////////////////////////////////////////
#define noErr			0
#define	Boolean			BOOL

typedef unsigned char	Byte;

//typedef struct { int h; int v; } Point, __far *pPoint;
///////////////////////////////////////////////// ColorMap
#define	MAX_COLOR  		 256
#define	NOHUE			-1.0
///////////////////////////////////////////////////
//#define RGB2CS			MAX_COLOR - 1
//#define CS2RGB			1./RGB2CS 
#define RGB2CS			255
#define CS2RGB			.0039216 

#define	CS2RGBCOLOR(cs,rgb) \
	(rgb).red   = GetRValue((cs))*CS2RGB;\
	(rgb).green = GetGValue((cs))*CS2RGB;\
	(rgb).blue  = GetBValue((cs))*CS2RGB;

#define	RGBCOLOR2CS(rgb) \
	PALETTERGB(	(BYTE)((rgb).red  *RGB2CS), \
				(BYTE)((rgb).green*RGB2CS), \
				(BYTE)((rgb).blue *RGB2CS) )

///////////////////////////////////////////////////				
typedef	double			COLORFACTOR;	// 	
typedef	unsigned short	COLORINDEX;
typedef double			COEFFICIENT;
typedef struct
	 	{
	  		double red;			// [0,1]
	  		double green;       // [0,1]
	  		double blue;        // [0,1]
	 	}	RGBCOLOR, __far *pRGBCOLOR;
	 	
typedef struct 
		{ 
			double hue;			// [0,360 Deg] or UnDefined=-1
			double saturation;  // [0,1]
			double value;       // [0,1]
		}	HSVCOLOR, __far *pHSVCOLOR;

enum ALIGNMENT
{
	LEFTALIGN, 
	RIGHTALIGN, 
	CENTERALIGN
//	aligmentSize16 = 32767
};

///////////////////////////////////////////////// TextureMap
#define	TXARGS	4
#define	TXLIMIT	6
/////////////////
enum TEXTUREINDICES {
	TXI_WOOD,
	TXI_ROCK,
	TXI_PICT,
	TXI_BUMPS,
	TXI_RGB,
	TXI_DEPTH
	};

#define TXI_MIN TXI_WOOD
#define TXI_MAX TXI_DEPTH

enum TEXTURES		
	{
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

typedef struct {
	pWORLD	min,max;
}
	Box,__far *pBox;

typedef struct
{
	WORLD			txRotations;		// texture field rotations in degrees		
	WORLD			txScalars;			// texture field scaling factors			
	WORLD			txTranslations;		// texture field displacements				
	COEFFICIENT		txArgument[TXARGS];	// texture type dependent arguments			
}	TXINFO,  __far *pTXINFO;
///////////////////////////////////////////////// RenderAttrib
typedef	struct
{
	COLORFACTOR		R,G,B;				// (I)RGB reflected color coefficients			
	COEFFICIENT		diffusion;			// (Kd)diffuse reflection coefficient			
	COLORINDEX		specIndex;			// (Is)specular reflection index				
	RGBCOLOR		frameColor;			// frame RGB reflected color coefficients	
	RGBCOLOR		ambientColor;		// frame RGB ambient color coefficients	
	unsigned short	lightSource:1,		// emits light?								
					distanceEffect:1,	// apply light source distance?				
					ambientEffect:1,	// apply ambient light effects?				
					culling:1,			// visibility based on facet normals?		
					framed:1,			// frame the facets?						
					turbulence:1,		// turbulence effect?				
					shadow:1,			// use shadow?
					wireframed:1,		// wireframe override                       
					hazing:1,			// atmospheric hazing effects?				
					refconPen:1,		// refcon context: TRUE - pen, FALSE - proc
					extraBits:6;		// unused... reserved for expansion			
	COEFFICIENT		specularity;		// (Ks)specular reflection coefficient			
	COEFFICIENT		ambience;			// not used. retained for compatibility		
	COEFFICIENT		absorption;			// reserved for expansion					
	COEFFICIENT		transmission;		// reserved for expansion					
	COEFFICIENT		translucence;		// reserved for expansion					
	COEFFICIENT		refraction;			// reserved for expansion					
	COEFFICIENT		transparency;		// transparency coefficient	( 0 = opaque )	
	TEXTURES		texture;			// texture type code						
	TXINFO			tx[TXLIMIT];
}
	RENDINFO, __far *pRENDINFO;

typedef struct {	// do not exceed sizeof(TXINFO)*TXLIMIT bytes in length
	enum alignment	aligned;
	char			label[256];
	BOOL			bStockFont;
	HFONT			hFont;
}	TxLabel, __far *pTxLabel;

#define	TX_STRING(ra)		((pTxLabel)(&(ra).tx)[0])->label
#define	TX_ALIGNED(ra)		((pTxLabel)(&(ra).tx)[0])->aligned
#define	TX_BSTOCKFONT(ra)	((pTxLabel)(&(ra).tx)[0])->bStockFont
#define	TX_HFONT(ra)		((pTxLabel)(&(ra).tx)[0])->hFont

typedef struct 
{
	WORD	penPat[8];	// used to create a 4x4 monochrome bitmap
	short	penSize;
}
	TXLINES, __far *pTXLINES;

#define	TX_PATTERN(ra)	(LPSTR)((pTXLINES)(&(ra).tx)[0])->penPat
#define	TX_PENSIZE(ra)	(int)((pTXLINES)(&(ra).tx)[0])->penSize
///////////////////////////////////////////////// Light Environment
typedef struct
{
	RGBCOLOR	color;		//	light color (RGB) emitted by the source[0,1] 
	HSVCOLOR	hsvColor;	//	light color (HSV):h[0,360],s,v:[0,1]						
	double		level;		//	intensity scaling factor for the source 
	WORLD		location;	//	location of the light source in space	
	WORLD		focus;		//	focal point for directional lights
							//	doubled for holding Sun || direction
							//	i.e. for shape <0 case below 		
	WORLD		normal;		//	direction the source points towards		
	double		shape;		//	shape exponent index(  =0 = Isotropic 
							//						   >0 = Directional
							//						   <0 =	Parallel ray)
	double		limitAngle;	//	cutoff angle							
	double		magnitude;	//	effective magnitude of source äRGB=max	
}
	LTSOURCE, __far *pLTSOURCE;

typedef	struct
{
	RGBCOLOR	color;		//	raw ambience:light color (RGB)
							//	emitted by the source[0,1] 
	double		level;		//	intensity scaling factor for the source[0,1] 
	double		magnitude;	//	effective magnitude of source äRGB=max	
	double		Ra,Ga,Ba;	//	ambience levels color*level					
	int			nSources;	//	number of point light sources (0=none)	
//	LTSOURCE	source[];	//	array of point light sources			
	pLTSOURCE	ppSource;	//	pointer to array of point light sources			
	double		arg[TXLIMIT][TXARGS];//texture mapping parameters
//todo    pUserDll	pudll;		// reference to user dll info
}
	LTENVIRON, __far *pLTENVIRON;
/////////////////////////////////////////////
#endif

