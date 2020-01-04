/*****************************************************************************
 *	file:		"Textures.h"
 *
 *	(C) 1994 Mark M. Owen.	All rights reserved.
 *****************************************************************************
 */
#ifndef	_Textures_
#define	_Textures_

#include <Render.h>

#define	MAXNOISE	10

typedef unsigned long	STR4;	// a four byte, unterminated string

typedef struct {
	FPType	noise[MAXNOISE+1][MAXNOISE+1][MAXNOISE+1];
}
	NoiseData,__far *pNoiseData;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void		WoodTextureTransform(Point3d r,Point3d s,Point3d t);
void		RockTextureTransform(Point3d r,Point3d s,Point3d t);
void		PICTTextureTransform(Point3d r,Point3d s,Point3d t);
void		RGBTextureTransform(Point3d r,Point3d s,Point3d t);
void		DepthTextureTransform(Point3d r,Point3d s,Point3d t);
void		BumpsTextureTransform(Point3d r,Point3d s,Point3d t);

FPType		Noise			(FPType u,FPType v,FPType w);
FPRGBColor	Transparency	(pRGBColor bg,pFPRGBColor fg,FPType coef);
FPRGBColor	Opaqueness		(pRGBColor bg,pFPRGBColor fg,FPType coef);
FPRGBColor	Wood			(FPType u,FPType v,FPType w,FPRGBColor c,FPType light,FPType dark,FPType addNoise);
FPRGBColor	Rock			(FPType u,FPType v,FPType w,FPRGBColor c,FPType BandWidth,FPType f1,FPType f2,FPType f3);
void		PICTinit		(STR4 PICTid,pBox bounds);
FPRGBColor	PICT			(FPType u,FPType v,FPType w,FPRGBColor c,FPType repeat,FPType lat,FPType lon);
FPPoint3d	PICTbump		(FPType u,FPType v,FPType w,FPPoint3d N,FPType scalar,FPType lat,FPType lon);
void		PICTterm		(void);
void		PICTcleanup		(void);
FPRGBColor	R_G_B			(FPType u,FPType v,FPType w,FPRGBColor c,FPType addNoise);
FPRGBColor	Depth			(FPType u,FPType v,FPType w,FPRGBColor c,FPType Modulus,FPType addNoise);
FPPoint3d	PerturbNormal	(FPType u,FPType v,FPType w,FPPoint3d N,FPType a,FPType b,FPType c,FPType atten);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //	_Textures_
