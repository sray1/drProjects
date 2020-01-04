/*****************************************************************************
 *	File:		AntiAlias.c
 *
 *	Purpose:	Image antialiasing functions.
 *
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <AntiA.h>
#include <Memory.h>
#include <3dColor.h>


#define	sumCpixel(h,v,a,b,c)	GetQueuePixel((h),(v),&rgb);\
								(a)+=rgb.red;\
								(b)+=rgb.green;\
								(c)+=rgb.blue

#define	sumpixel(h,v,a)			GetQueuePixel((h),(v),&rgb);\
								(a)+=rgb.red

pPixelQ		pixQ	= NULL;
pPixelQ		defPixQ	= NULL;

extern HDC	hdcCurrent;
///////////////////////////////////////////////////////////////////
/**********************************************************************************
 *
 *	Function:	AntialiasEdge
 *
 *	Purpose:	Blends the edge pixels into their surroundings.
 *
 **********************************************************************************
 */
void  CRender::AntialiasEdge(
		int			y,	/*	current scan line (vertical coordinate)		*/
		pSCANSPAN	pss	/*	current scanline segment data               */
	)
{
	int			Ix1,Ix2,x,xMx,ox;
	float		r;
	FPWORLD	dP,P;
	RGBCOLOR	rgb,c;
	long		Z;
	long __huge	*pB;

	Ix1 = pss->x[0];
	Ix2 = pss->x[1];
	if( Ix1 == Ix2 )
		return;
	if( Ix1 > (short)pZB->xMx || Ix2 < (short)pZB->xMn )	/* out of window bounds */
		return;

	r	= 1.0F / (pss->x[1] - pss->x[0]);
	P = pss->e[0].P;
	DELTA( dP, P, pss->e[1].P, r );

	x = (int)Max( (int)Ix1, (int)pZB->xMn );	/* forcing -x to zero here */
	ox =  x - Ix1;	// how much offset, if any?
	if( ox )
		OFFSET(P,dP,ox);

	xMx = (int)Min( (int)Ix2, (int)pZB->xMx );
	pB = pZB->zb + ( y - pZB->yMn ) * pZB->xRng + x - pZB->xMn;

	while( x < xMx ) {
		if(		(P.z > 0.0F)
			&&	(		(x == Ix1)
					||	(x >= Ix2-1)
					||	(y == (int)MINV&&(int)MINV!=(int)pZB->yMn)
					||	(y >= (int)MAXV-1&&(int)MAXV!=(int)pZB->yMx)
				)
		  ) {
			Z = (long)(65536.0*distance(P));
			if( Z <= *pB ) {
				*pB = Z;
				GetQueuePixel( x,y, &c );
				ConvolutionColor( x-1, y, W1, W2, W3, &rgb );	/* left */
				SetQueuePixel( x-1, y, &rgb );
				ConvolutionColor( x+1, y, W1, W2, W3, &rgb );	/* right */
				SetQueuePixel( x+1, y, &rgb );
				ConvoluteColorPixel( x, y, W1, W2, W3, &c );		/* this */
			}
		}
		x++;
		pB++;
		INC( P, dP );
	}
}

/*****************************************************************************
 *
 *	Function:	SetPixQ
 *
 *	Purpose:	Sets the current pixel queue to the pixel queue specified.
 *
 *****************************************************************************
 */
void API3D	SetPixQ(pPixelQ thePixQ)
{
	pixQ = thePixQ;
}

/*****************************************************************************
 *
 *	Function:	SetDefPixQ
 *
 *	Purpose:	Sets the current pixel queue to the default queue, allocating
 *				it if needed.
 *
 *****************************************************************************
 */
void API3D	SetDefPixQ(void)
{
	if( !defPixQ )
		defPixQ = NewPixQ();
	pixQ = defPixQ;
}

/*****************************************************************************
 *
 *	Function:	NewPixQ
 *
 *	Purpose:	Allocates a new pixel queue.
 *
 *				A pixel queue is a cache of those pixels most recently used
 *				via GetQueuePixel and SetQueuePixel functions which act as
 *				replacements for the ROM calls SetCPixel and GetCPixel.
 *
 *				Its purpose is to speed things up some (up to 50%) in those
 *				cases like antialiasing, where adjacent pixels are accessed
 *				repeatedly.  The performance improvement is a results of
 *				avoiding the ROM calls and their functions of color mapping
 *				for pixels whose values are known.
 *
 *				We provide a default pixel queue which will be used where
 *				required, when no specific queue has been designated.
 *
 *	Returns:	pointer to a PixelQ.
 *
 *****************************************************************************
 */
pPixelQ API3D NewPixQ(void)
{
	pPixelQ	ppq = (pPixelQ)NewPtr(sizeof(pixelQ));
	ppq->oldest = 0;
	return ppq;
}

/*****************************************************************************
 *
 *	Function:	DisposePixQ
 *
 *	Purpose:	Deallocates a pixel queue.
 *
 *****************************************************************************
 */
void API3D	DisposePixQ(pPixelQ thePixQ)
{
	if( thePixQ )
		DisposPtr( (Ptr)thePixQ );
}

/*****************************************************************************
 *
 *	Function:	DisposeDefPixQ
 *
 *	Purpose:	Deallocates the default pixel queue.
 *
 *****************************************************************************
 */
void API3D	DisposeDefPixQ(void)
{
	if( defPixQ )
		DisposePixQ( defPixQ );
	defPixQ = 0L;
}

/*****************************************************************************
 *
 *	Function:	InPixQ
 *
 *	Returns:	True and the RGBColor of the pixel at coordinates x,y, if it
 *				is in the queue.  Otherwise returns false.
 *
 *****************************************************************************
 */
Boolean API3D InPixQ(int x,int y,pRGBColor rgb)
{
	pPixQitem		ppq = pixQ->pixQ;
	register int	i = 0;

	while( i < MAXPIXQ ) {
		if( ppq->x == x && ppq->y == y) {
			*rgb = ppq->rgb;
			return true;
		}
		i++;
		ppq++;
	}
	return false;
}

/*****************************************************************************
 *
 *	Function:	QueuePixel
 *
 *	Purpose:	Records a pixels x,y coordinates and RGBColor in the current
 *				pixel queue.  If the queue is full, the oldest pixel in the
 *				queue will be overwritten.  The defined item, MAXPIXQ controls
 *				the number of entries in the queue.
 *
 *****************************************************************************
 */
void API3D	QueuePixel(int x,int y,pRGBColor rgb)
{
	pPixQitem	ppq = &pixQ->pixQ[pixQ->oldest];
	if( ++pixQ->oldest >= MAXPIXQ )
		pixQ->oldest = 0;
	ppq->x = x;
	ppq->y = y;
	ppq->rgb = *rgb;
}


/*****************************************************************************
 *
 *	Function:	GetQueuePixel
 *
 *	Purpose:	Returns via the parameter rgb, the color of the pixel at the
 *				coordinates x,y.  If no pixel queue is current the default
 *				queue will be used (and allocated is needed).  If a pixel
 *				queue cannot be allocated this function reverts to a call to
 *				the ROM routine GetCPixel.  Assuming we have a queue, InPixQ
 *				is called to return the pixel's value.  If InPixQ returns
 *				false GetCPixel is called and the RGBColor obtained thereby
 *				is both returned and recorded in the queue (via QueuePixel).
 *
 *****************************************************************************
 */
void API3D	GetQueuePixel(int x,int y,pRGBColor rgb)
{
	if( !pixQ ) 			   {
		if( !defPixQ )
			defPixQ = NewPixQ();
		pixQ = defPixQ;
	}
	if( !pixQ ) {
		GetCPixel( x, y, rgb );
		return;
	}
	if( InPixQ( x, y, rgb ) )
		return;
	GetCPixel( x, y, rgb );
	QueuePixel( x, y, rgb );
}

/*****************************************************************************
 *
 *	Function:	SetQueuePixel
 *
 *	Purpose:	Using the parameter rgb, sets the color of the pixel at the
 *				coordinates x,y.  If no pixel queue is current the default
 *				queue will be used (and allocated is needed).  If a pixel
 *				queue cannot be allocated this function reverts to a call to
 *				the ROM routine SetCPixel.  Assuming we have a queue, a search
 *				is performed to see if the pixel is already queued, in which
 *				case its RGBColor in the queue is updated, appropriately.  If
 *				the pixel is not in the queue it will be recorded via a call
 *				to QueuePixel.
 *
 *****************************************************************************
 */
void API3D	SetQueuePixel(int x,int y,pRGBColor rgb)
{
	pPixQitem		ppq;
	register int	i;

	if( !pixQ ) {
		if( !defPixQ )
			defPixQ = NewPixQ();
		pixQ = defPixQ;
	}
	if( !pixQ ) {
		SetCPixel( x, y, rgb );
		return;
	}
	ppq = pixQ->pixQ;
	i = 0;
	SetCPixel( x, y, rgb );
	while( i < MAXPIXQ ) {
		if( ppq->x == x && ppq->y == y) {
			ppq->rgb = *rgb;
			return;
		}
		i++;
		ppq++;
	}
	QueuePixel( x, y, rgb );
}


/*****************************************************************************
 *
 *	Function:	ConvoluteColorPixel
 *
 *	Purpose:	Sets a pixel to a color value which is derived from a weighted
 *				average of eight adjacent pixels.  Eight pixels are sampled.
 *				The parameter rgb contains the base color at the pixel x,y.
 *
 *				The parameters w1,w2,w3 are weight factors for the center,
 *				perpendicular and diagonal pixels respectively.  If in doubt
 *				as to values to use, try W1,W2 and W3 defined in Antialias.h.
 *
 *****************************************************************************
 */
void API3D	ConvoluteColorPixel(int x,int y,float w1,float w2,float w3,pRGBColor pRGB)
{
	register int	i=x,j=y;
	float			R,G,B,r,g,b;
    RGBColor		rgb;

	r = pRGB->red	* w1;
	g = pRGB->green	* w1;
	b = pRGB->blue	* w1;
	R=G=B=0.0F;
	sumCpixel(i - 1, j, R,G,B);
	sumCpixel(i + 1, j, R,G,B);
	sumCpixel(i, j + 1, R,G,B);
	sumCpixel(i, j - 1, R,G,B);
	r += R * w2;
	g += G * w2;
	b += B * w2;
	R=G=B=0.0F;
	sumCpixel(i - 1, j - 1, R,G,B);
	sumCpixel(i + 1, j - 1, R,G,B);
	sumCpixel(i - 1, j + 1, R,G,B);
	sumCpixel(i + 1, j + 1, R,G,B);
	r += R * w3;
	g += G * w3;
	b += B * w3;
	rgb.red		= (fract16)((r>65535.0F)?(fract16)0xFFFF:(fract16)r);
	rgb.green	= (fract16)((g>65535.0F)?(fract16)0xFFFF:(fract16)g);
	rgb.blue	= (fract16)((b>65535.0F)?(fract16)0xFFFF:(fract16)b);
	SetQueuePixel(i,j,&rgb);
}

/*****************************************************************************
 *
 *	Function:	ConvolutionColor
 *
 *	Purpose:	Produces a color value which is a weighted average of eight
 *				pixels adjacent to a given pixel.  Nine pixels are sampled.
 *
 *				The parameters w1,w2,w3 are weight factors for the center,
 *				perpendicular and diagonal pixels respectively.  If in doubt
 *				as to values to use, try W1,W2 and W3 defined in Antialias.h.
 *
 *	Returns:	RGBColor.
 *
 *****************************************************************************
 */
void API3D ConvolutionColor(int X,int Y,float w1,float w2,float w3,pRGBColor pRGB)
{
	register int	x=X,y=Y;
	float			R,G,B,r,g,b;
	RGBColor		rgb;

	GetQueuePixel( x,y, &rgb );
	r = rgb.red		* w1;
	g = rgb.green	* w1;
	b = rgb.blue	* w1;
	R=G=B=0.0F;
	sumCpixel(x - 1, y, R,G,B);
	sumCpixel(x + 1, y, R,G,B);
	sumCpixel(x, y + 1, R,G,B);
	sumCpixel(x, y - 1, R,G,B);
	r += R * w2;
	g += G * w2;
	b += B * w2;
	R=G=B=0.0F;
	sumCpixel(x - 1, y - 1, R,G,B);
	sumCpixel(x + 1, y - 1, R,G,B);
	sumCpixel(x - 1, y + 1, R,G,B);
	sumCpixel(x + 1, y + 1, R,G,B);
	r += R * w3;
	g += G * w3;
	b += B * w3;
	rgb.red		= (fract16)((r>65535.0F)?(fract16)0xFFFF:(fract16)r);
	rgb.green	= (fract16)((g>65535.0F)?(fract16)0xFFFF:(fract16)g);
	rgb.blue	= (fract16)((b>65535.0F)?(fract16)0xFFFF:(fract16)b);
	*pRGB = rgb;
}

/*****************************************************************************
 *
 *	Function:	ConvoluteColor
 *
 *	Purpose:	Applies a 3x3 convolution matrix to the area beneath a given
 *				rectangle, thereby smoothing edges within the image.  A side
 *				effect is a general defocusing or softening of the image.
 *
 *****************************************************************************
 */
void	API3D ConvoluteColor(pRect r)
{
	register int	x,y;
	RGBColor		color;
    pRGBColor		pColor = (pRGBColor)&color;

	for( y = r->top + 1; y P_SQL_ROW_UPDATE_NOT_SUPPORTED 0xF291 MAFX_IDP_SQL_ODBC_V2_REQUIRED 0xF292 NAFX_IDP_SQL_NO_POSITIONED_UPDATES 0xF293 OAFX_IDP_SQL_LOCK_MODE_NOT_SUPPORTED 0xF294 PAFX_IDP_SQL_DATA_TRUNCATED 0xF295 QAFX_IDC_LISTBOX 100 WAFX_IDC_CHANGE 101 XAFX_IDC_PRINT_DOCNAME 201 [AFX_IDC_PRINT_PRINTERNAME 202 \AFX_IDC_PRINT_PORTNAME 203 ]AFX_IDC_PRINT_PAGENUM 204 ^AFX_IDI_STD_MDIFRAME 1 dAFX_IDI_STD_FRAME 2 eAFX_IDD_NEWTYPEDLG 30721 uAFX_IDD_PRINTDLG 30722 vAFX_IDD_PREVIEW_TOOLBAR 30723 wAFXf the image's red components.  It is
 *				intended for use with grayscaled images (where red=green=blue)
 *				hence the reliance on the red component.
 *
 *	Returns:	gray level in the range 0..65535.
 *
 *****************************************************************************
 */
unsigned short API3D Convolution(int X,int Y)
{
	register int	x=X,y=Y;
	float			R,r;
	RGBColor		rgb;

	GetQueuePixel( x,y, &rgb );
	r = rgb.red	* W1;
	R=0.0F;
	sumpixel(x - 1, y, R);
	sumpixel(x + 1, y, R);
	sumpixel(x, y + 1, R);
	sumpixel(x, y - 1, R);
	r += R * W2;
	R=0.0F;
	sumpixel(x - 1, y - 1, R);
	sumpixel(x + 1, y - 1, R);
	sumpixel(x - 1, y + 1, R);
	sumpixel(x + 1, y + 1, R);
	r += R * W3;
	return (unsigned short)((r>65535.0F)?(unsigned short)0xFFFF:(unsigned short)r);
}

/*****************************************************************************
 *
 *	Function:	Convolute
 *
 *	Purpose:	Applies a 3x3 convolution matrix to the area beneath a given
 *				rectangle, thereby smoothing edges within the image.  A side
 *				effect is a general defocusing or softening of the image.
 *
 *				This function is faster than ConvoluteColor, since it deals
 *				only with the intensity of the image's red components.  It is
 *				intended for use with grayscaled images (where red=green=blue)
 *				hence the reliance on the red component.
 *
 *	Warning:	Another difference between this and ConvoluteColor is that it
 *				does not use an offscreen port, resulting in a displacement
 *				of the image. Since this function may called with the current
 *				port potentially "on screen" it is possible to blend the cursor
 *				into the image.  To avoid this unsightly abberation: either
 *				call HideCursor() while using this function and ShowCursor()
 *				when done; --or-- switch to an off screen port before calling
 *				this function.
 *
 *****************************************************************************
 */
void	API3D Convolute(pRect r)
{
	register int	x,y;
	RGBColor		color;

	for( y = r->top + 1; y < r->bottom; y++ )
		for( x = r->left + 1; x < r->right; x++ ) {
			color.red	=
			color.green	=
			color.blue	= Convolution(x,y);
			SetQueuePixel(x,y,&color);
		}
}

