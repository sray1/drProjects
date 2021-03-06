/*****************************************************************************
 *	file:		TXXXXX.c
 *
 *	purpose:	TX_USERDLL texture mapping functions shell
 *
 *	Version:	Microsoft C / Windows
 *
 *	(C) 1994 Mark M. Owen.	All rights reserved.
 *****************************************************************************
*/
#include <WIN_TRIM.H>
#include <OSINTF.h>
#include <3dcolor.h>
#include <apitx.h>

#include <AntiA.h>
#include <LOADBMPF.h>
#include <limits.h>
#include <math.h>
#include <string.h>

typedef	struct {
	FPType	v[4][4];
}
	XFMatrix,__far *pXFMatrix;

static HINSTANCE	ghInst		= NULL;		//	Global instance handle for  DLL

static
	XFMatrix	XF,ID =	{	1,0,0,0
						,	0,1,0,0
						,	0,0,1,0
						,	0,0,0,1
						};

static void	_near xfMul(pXFMatrix a,pXFMatrix b,pXFMatrix c);
static void	_near TextureTransform(pXFMatrix pXF,pPoint3d r,pPoint3d s,pPoint3d t);
static void	_near InverseTextureTransform(pXFMatrix pXF,pPoint3d r,pPoint3d s,pPoint3d t);
static void	_                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                PRGBColor pC,pFPPoint3d pN);
void APITX _export Term(void);
void APITX _export Fini(void);


#ifdef	__TURBOC__
#pragma argsused
#endif // __TURBOC__

#if defined(_MSC_VER)
#	if _MSC_VER >= 700
#		pragma warning(disable:4100) // disable unused argument warnings
#	endif
#endif

int FAR PASCAL _export LibMain(HINSTANCE hInst,WORD wDS,WORD cbHeap,LPSTR lpCmdLine)
{
	ghInst = hInst;
	UnlockData( 0 );
	return TRUE;
}

#ifdef __TURBOC__
#pragma argsused
#endif // __TURBOC__

#pragma alloc_text(FIXEDSEG, WEP)

int CALLBACK _export WEP(int bSystemExit)
{
	return 1;
}

#ifdef __TURBOC__
#pragma argsused
#endif // __TURBOC__

static void	_near xfMul(
		pXFMatrix a,	// source matrix
		pXFMatrix b,	// source matrix
		pXFMatrix c		// destination matrix
	)
{
	XFMatrix 		mt;
	register int	i,j,k;
	FPType			*pC;

	pC = &mt.v[0][0];
	for( i=0; i<=3; i++ )
		for( j=0; j<=3; j++ ) {
			mt.v[i][j] = 0.0F;
			for( k=0; k<=3; k++ )
				*pC += a->v[i][k] * b->v[k][j];
			pC++;
		}
	*c = mt;
}

static void	_near TextureTransform(
		pXFMatrix	pXF,	//	destination matrix
		pPoint3d	r,		//	rotations: pitch, yaw, roll
		pPoint3d	s,		//	scale factors: x,y,z
		pPoint3d	t		//	translations: x,y,z
	)
{
	FPType		rx,ry,rz;
	XFMatrix	xf;

	rx			= r->x * 0.0000002663161089F;	// �/180/65536
	ry 			= r->y * 0.0000002663161089F;
	rz			= r->z * 0.0000002663161089F;

	*pXF = ID;
	pXF->v[0][0]= s->x * 0.0000152587890625F;
	pXF->v[1][1]= s->y * 0.0000152587890625F;
	pXF->v[2][2]= s->z * 0.0000152587890625F;

	xf = ID;
	xf.v[0][0]	= (float)cos(ry);
	xf.v[2][2]	= xf.v[0][0];
	xf.v[2][0]	= (float)sin(ry);
	xf.v[0][2]	= -xf.v[2][0];
	xfMul(pXF,&xf,pXF);

	xf = ID;
	xf.v[2][2]	= xf.v[1][1] = (float)cos(rx);
	xf.v[2][1]	= (float)sin(rx);
	xf.v[1][2]	= -xf.v[2][1];
	xfMul(pXF,&xf,pXF);

	xf = ID;
	xf.v[1][1]	= xf.v[0][0] = (float)cos(rz);
	xf.v[1][0]	= (float)sin(rz);
	xf.v[0][1]	= -xf.v[1][0];
	xfMul(pXF,&xf,pXF);

	pXF->v[3][0]= t->x * 0.0000152587890625F;
	pXF->v[3][1]= t->y * 0.0000152587890625F;
	pXF->v[3][2]= t->z * 0.0000152587890625F;
}

static void	_near InverseTextureTransform(
		pXFMatrix	pXF,	//	destination matrix
		pPoint3d	r,		//	rotations: pitch, yaw, roll
		pPoint3d	s,		//	scale factors: x,y,z
		pPoint3d	t		//	translations: x,y,z
	)
{
	FPType		rx,ry,rz;
	XFMatrix	xf;

	rx = -r->x * 0.0000002663161089F;	// �/180/65536
	ry = -r->y * 0.0000002663161089F;
	rz = -r->z * 0.0000002663161089F;

	*pXF = ID;
	pXF->v[0][0]= s->x * 0.0000152587890625F;
	pXF->v[1][1]= s->y * 0.0000152587890625F;
	pXF->v[2][2]= s->z * 0.0000152587890625F;

	xf = ID;
	xf.v[1][1]	= xf.v[0][0] = (float)cos(rz);
	xf.v[1][0]	= (float)sin(rz);
	xf.v[0][1]	= -xf.v[1][0];
	xfMul(pXF,&xf,pXF);

	xf = ID;
	xf.v[2][2]	= xf.v[1][1] = (float)cos(rx);
	xf.v[2][1]	= (float)sin(rx);
	xf.v[1][2]	= -xf.v[2][1];
	xfMul(pXF,&xf,pXF);

	xf = ID;
	xf.v[0][0]	= (float)cos(ry);
	xf.v[2][2]	= xf.v[0][0];
	xf.v[2][0]	= (float)sin(ry);
	xf.v[0][2]	= -xf.v[2][0];
	xfMul(pXF,&xf,pXF);

	pXF->v[3][0]= t->x * 0.0000152587890625F;
	pXF->v[3][1]= t->y * 0.0000152587890625F;
	pXF->v[3][2]= t->z * 0.0000152587890625F;
}

static void	_near TransformTexture(
		pXFMatrix	pXF,	// texture mapping transform matrix
		FPType		x,		// object space X coordinate
		FPType		y,		// object space Y coordinate
		FPType		z,		// object space Z coordinate
		FPType		*X,		// returned texture space X coordinate
		FPType		*Y,		// returned texture space Y coordinate
		FPType		*Z		// returned texture space Z coordinate
	)
{
	*X	= x * pXF->v[0][0] + y * pXF->v[1][0] + z * pXF->v[2][0] + pXF->v[3][0];
	*Y	= x * pXF->v[0][1] + y * pXF->v[1][1] + z * pXF->v[2][1] + pXF->v[3][1];
	*Z	= x * pXF->v[0][2] + y * pXF->v[1][2] + z * pXF->v[2][2] + pXF->v[3][2];
}

// custom functions follow

void APITX _export Init(pRendAttr pRA,pBox bounds)
{
	USERDLLARGID(pRA,0) = 0;
	USERDLLARGID(pRA,1) = 0;
	USERDLLARGID(pRA,2) = 0;
	USERDLLARGID(pRA,3) = 0;
	USERDLLARGTYPE(pRA,0) = USERDLLARG_FIXED;
	USERDLLARGTYPE(pRA,1) = USERDLLARG_FIXED;
	USERDLLARGTYPE(pRA,2) = USERDLLARG_FIXED;
	USERDLLARGTYPE(pRA,3) = USERDLLARG_FIXED;
}

void APITX _export SetArg(pRendAttr pRA,WORD index,LPVOID pArgV)
{
}

void APITX _export GetArg(pRendAttr pRA,WORD index,LPVOID pArgV)
{
}

void APITX _export Xfrm(pRendAttr pRA)
{
}

void APITX _export Eval(pRendAttr pRA,pFPPoint3d pP,pFPRGBColor pC,pFPPoint3d pN)
{
}

void APITX _export Term(void)
{
}

void APITX _export Fini(void)
{
}

