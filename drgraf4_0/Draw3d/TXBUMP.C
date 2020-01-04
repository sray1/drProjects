/*****************************************************************************
 *	file:		TXBUMP.c
 *
 *	purpose:	TX_USERDLL bump texture mapping functions
 *
 *	Version:	Microsoft C / Windows
 *
 *	(C) 1991 Mark M. Owen.	All rights reserved.
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
static void	_near TransformTexture(pXFMatrix xf,FPType x,FPType y,FPType z,FPType *X,FPType *Y,FPType *Z);

int FAR PASCAL _export LibMain(HINSTANCE hInst,WORD wDS,WORD cbHeap,LPSTR lpCmdLine);
int CALLBACK _export WEP(int bSystemExit);

void APITX _export Init(pRendAttr pRA,pBox bounds);
void APITX _export SetArg(pRendAttr pRA,WORD index,LPVOID pArgV);
void APITX _export GetArg(pRendAttr pRA,WORD index,LPVOID pArgV);
void APITX _export Xfrm(pRendAttr pRA);
void APITX _export Eval(pRendAttr pRA,pFPPoint3d pP,pFPRGBColor pC,pFPPoint3d pN);
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

	rx			= r->x * 0.0000002663161089F;	// ã/180/65536
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

	rx = -r->x * 0.0000002663161089F;	// ã/180/65536
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
		pXFMatrix	pXF,	/* texture mapping transform matrix					*/
		FPType		x,		/* object space X coordinate						*/
		FPType		y,		/* object space Y coordinate						*/
		FPType		z,		/* object space Z coordinate						*/
		FPType		*X,		/* returned texture space X coordinate				*/
		FPType		*Y,		/* returned texture space Y coordinate				*/
		FPType		*Z		/* returned texture space Z coordinate				*/
	)
{
	*X	= x * pXF->v[0][0] + y * pXF->v[1][0] + z * pXF->v[2][0] + pXF->v[3][0];
	*Y	= x * pXF->v[0][1] + y * pXF->v[1][1] + z * pXF->v[2][1] + pXF->v[3][1];
	*Z	= x * pXF->v[0][2] + y * pXF->v[1][2] + z * pXF->v[2][2] + pXF->v[3][2];
}

// custom functions follow

typedef struct phList {
	char		name[10];
	HBITMAP		ph;
	struct phList	__far *prior;
}
	phList, __far *pphList;

static HDC			hDCm;
static pPixelQ		PICTpixQ = NULL;
static FPType		ox,oy;
static HBITMAP	ph;
static Rect			rPic;
static Point		dr;
static pphList		pphl = NULL;

#define	FPFix(fx)		((fx)*0.0000152587890625F)
#define	SET3D(p,a,b,c)	{(p).x=(a);(p).y=(b);(p).z=(c);}
#define ADD(a, b, c)	{(a).x=(b).x+(c).x;(a).y=(b).y+(c).y;(a).z=(b).z+(c).z;}
#define SUB(a, b, c)	{(a).x=(b).x-(c).x;(a).y=(b).y-(c).y;(a).z=(b).z-(c).z;}
#define SCALE(a, k)		{(a).x*=(k);(a).y*=(k);(a).z*=(k);}
#define CROSS(a,b,c)	{(a).x=(b).y*(c).z-(b).z*(c).y; \
						(a).y=(b).z*(c).x-(b).x*(c).z; \
						(a).z=(b).x*(c).y-(b).y*(c).x;}

#define MAG(b)			(FPType)sqrt((b).x*(b).x+(b).y*(b).y+(b).z*(b).z)
#define NORM(a)			{ d=MAG((a)); d = (d!=0.0F)? (1.0F/d):1.0F; (a).x*=d; (a).y*=d; (a).z*=d; }
#define R64K			0.0000152590218966F
#define	NC(a)			(a)*R64K
#define	LUMINANCE(a)	(NC(0.229F*(a).red)+NC(0.587F*(a).green)+NC(0.114F*(a).blue))

static FPRGBColor __near PICT (FPType u,FPType v,FPType w,FPRGBColor c,FPType repeat,FPType lat,FPType lon);
static FPPoint3d __near PICTbump(FPType u,FPType v,FPType w,FPPoint3d N,FPType scalar,FPType lat,FPType lon);


void APITX _export Init(pRendAttr pRA,pBox bounds)
{
	STR4		PICTid;		/* resource id of the PICT to load	*/
	pphList		tpphl = pphl;
	Rect		R;
	BITMAP		BM;
	char		name[10];
	HDC 		hDC = GetCurrentDC();

	if( !hDC ) {
		OutputDebugString( "hDC NULL." );
		return;
	}

	USERDLLARGID(pRA,0) = 0;
	USERDLLARGID(pRA,1) = 0;
	USERDLLARGID(pRA,2) = 0;
	USERDLLARGID(pRA,3) = 0;
	USERDLLARGTYPE(pRA,0) = USERDLLARG_STR4;
	USERDLLARGTYPE(pRA,1) = USERDLLARG_FIXED;
	USERDLLARGTYPE(pRA,2) = USERDLLARG_FIXED;
	USERDLLARGTYPE(pRA,3) = USERDLLARG_FIXED;

    GetArg( pRA, 0, (LPVOID)&PICTid );
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
		FPType scale;
		Point3d	nul={f_0,f_0,f_0}, scl;
		scale = (rPic.right>rPic.bottom)? rPic.right  : rPic.bottom;
		scale /= (rPic.right>rPic.bottom)? R.right Œ5 ,?Depth@CTextures@@VEC?EURGBCOLOR@@NNNU2@NN@Z _cos    "›ÝFê›ÜNò›Ý^ê›vÚÄ~J¹ ó¥‹FJ‹VL‹FJ‹VLé  _^fþ]ÊH ¸  U‹ìŽØ¸  š    VW¸Ò‹N‹VÈRQÿvXÿvVÿvTÿvRÿvPÿvNÿvLÿvJÿvHÿvFÿvDÿvBFRŒÒRPFJŒÒRPFBŒÒRPÄ^S&Ä&ÿ_XÿvXÿvVÿvTÿvRÿvPÿvNÿvLÿvJÿvHÿvFÿvDÿvB†òþPÄ^S&Ä&ÿ_L›ÝF"›‰žîþŒ†ðþ‹ðŽÂ›&Ü›ÝžBÿ›ÿvHÿvFÿvDÿvBÿvXÿvVÿvTÿvRÿvPÿvNÿvLÿvJ†òþPÄ^S&Ä&ÿ_L›ÝF"›‰žîþŒ†ðþ‹ðŽÂ›&Ü›Ý^º›ÿvHÿvFÿvDÿvBÿvPÿvNÿvLÿvJÿvXÿvVÿvTÿvR†òþPÄ^S&Ä&ÿ_L›ÝF"›‰žîþŒ†ðþ‹ðŽÂ›&Ü›Ý^‚››Ý ›ÝF›š    ué  ƒì›ÝFR›Ü†Bÿ‹Ü›6Ý›š    ƒÄ,WORD index,LPVOID pArgV)
{
	switch( index ) {
		case 0:
    		_fmemcpy( &((STR4)(pRA->tx[TXI_USERATR].txArgument[index])), pArgV, 4 );
			break;
		case 1:
		case 2:
		case 3:
			pRA->tx[TXI_USERATR].txArgument[index] = *((coefficient*)pArgV);
			break;
	}
}

void APITX _export GetArg(pRendAttr pRA,WORD index,LPVOID pArgV)
{
	switch( index ) {
		case 0:
    		_fmemcpy( pArgV, &((STR4)(pRA->tx[TXI_USERATR].txArgument[index])), 4 );
			break;
		case 1:
		case 2:
		case 3:
			*((coefficient*)pArgV) = pRA->tx[TXI_USERATR].txArgument[index];
			break;
	}
}

void APITX _export Xfrm(pRendAttr pRA)
{
	InverseTextureTransform( &XF, &pRA->tx[TXI_USERATR].txRotations, &pRA->tx[TXI_USERATR].txScalars, &pRA->tx[TXI_USERATR].txTranslations );
}

void APITX _export Eval(pRendAttr pRA,pFPPoint3d pP,pFPRGBColor pC,pFPPoint3d pN)
{
	FPType		a1 = FPFix(pRA->tx[TXI_USERATR].txArgument[1]);
	FPType		a2 = FPFix(pRA->tx[TXI_USERATR].txArgument[2]);
	FPType		a3 = FPFix(pRA->tx[TXI_USERATR].txArgument[3]);
	if( pC == NULL && a1 < 0 ) {
		FPPoint3d	n;
		FPType		bumpScale = -a1;
		if( bumpScale >= 1000 )
			bumpScale -= 1000;
		*pN = PICTbump( pP->x,pP->y,pP->z, *pN, bumpScale, a2, a3 );
	}
	else
	if( a1 >= 0 || a1 <= -1000 )
		*pC = PICT( pP->x,pP->y,pP->z, *pC, a1, a2, a3 );
}

void APITX _export Term(void)
{
	if( PICTpixQ )
		DisposePixQ( PICTpixQ );
	if( hDCm )
		DeleteDC( hDCm );
	PICTpixQ = 0L;
	SetDefPixQ();
	ph = 0L;
}

void APITX _export Fini(void)
{
	pphList	tpphl;

	while( pphl ) {
		DeleteObject( pphl->ph );
		tpphl = pphl;
		pphl = pphl->prior;
		DisposPtr( (Ptr)tpphl );
	}
}

static FPRGBColor __near PICT(
		FPType		u,			/*	object space X coordinate					*/
		FPType		v,			/*	object space Y coordinate					*/
		FPType		w,			/*	object space Z coordinate					*/
		FPRGBColor	c,			/*	base color (object reflection coefficients)	*/
		FPType		repeat,		/*	1|3 repeating pict; 2|3 black=transparent	*/
		FPType		lat,		/*	latitude mapping rangeø (sphere ONLY)		*/
		FPType		lon			/*	longitude mapping rangeø (sphere/cylinder)	*/
	)
{
	FPRGBColor	rgb;
	RGBColor	pixColor;
	Point		p;
	HDC 		hDC;

	if( !ph )
		return c;	/* no PICT or no offscreen port */

	TransformTexture( &XF, u, v, w, &u, &v, &w );

	if( lat != 0.0F )	/*	map to sphere	*/
		v = (float)asin( v / sqrt(u*u+v*v+w*w) ) * dr.v * 57.295779513082F / lat;
	if( lon != 0.0F )	/*	map to cylinder	*/
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
		/*	not the transparent part of the PICT (all black)
		 */
		ConvolutionColor( p.h, p.v, W1, W2, W3, (pRGBColor)&pixColor );
		rgb			= c;
		rgb.red		*= pixColor.red   * 0.0000152587890625F;
		rgb.green	*= pixColor.green * 0.0000152587890625F;
		rgb.blue	*= pixColor.blue  * 0.0000152587890625F;

	}
	else {
		/*	this is the black (transparent) part of a PICT texture
		 *	so we return zeros to the caller to indicate such
		 */
		rgb.red = rgb.green = rgb.blue = 0;
	}

	SetCurrentDC( hDC );

	SetDefPixQ();

	return rgb;
}

static FPPoint3d __near PICTbump(
		FPType		u,			//	object space X coordinate
		FPType		v,			//	object space Y coordinate
		FPType		w,			//	object space Z coordinate
		FPPoint3d	N,			//	surface normal vector
		FPType		scalar,		//	luminance scaling factor
		FPType		lat,		//	latitude mapping rangeø (sphere ONLY)
		FPType		lon			//	longitude mapping rangeø (sphere/cylinder)
	)
{
	FPType		d, m;
	FPPoint3d	p1, p2, p3, vx, vy, vz, bN, vt;
	RGBColor	c;
	Point		p;
	HDC 		hDC;
	FPType		k = 57.295779513082F;

	if( !ph )
		return N;	// pict was not usable during init for some reason

	TransformTexture( &XF, u, v, w, &u, &v, &w );

	if( lat != 0.0F ) {	//	map to sphere
		FPType d = (FPType)sqrt(u*u+v*v+w*w);
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
	return N;
}

