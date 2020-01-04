/*****************************************************************************
 *	File:		ColorPal.cpp
 *
 *	Purpose:	Color Look Up Table (CLUT or Palette) Functions.
 *****************************************************************************
 */
 
#include "stdafx.h"

#include "viewrsrc.h"
/////////////////////
#include "Def_Rend.h"

#include "ColorPal.h"
/////////////////////////////////////////////////////////////////////////////
// CColorPal

IMPLEMENT_DYNAMIC(CColorPal,CObject)
/*
BEGIN_MESSAGE_MAP(CColorPal,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CColorPal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CColorPal::CColorPal()
{
}
///////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionView_DLL;
///////////////////////////
#define	NSYSCOLORS		20
#define	NHUES			24
#define	NHUELEVELS		8
#define	NGRAYS			33
////////////////////////////////////////////////////////////////////
#define MIN(_a,_b)        ( ( (long)(_a) < (long)(_b) )? (_a):(_b) )
#define MAX(_a,_b)        ( ( (long)(_a) > (long)(_b) )? (_a):(_b) )
//////////////////////////////////////////////// Stock Palette in RC
typedef struct {
	short		nEntries;
	pRGBCOLOR	pRGB;
//	pRGBCOLOR	prgb;
}	STOCKPAL, *pSTOCKPAL;

typedef HANDLE HSTOCKPAL;
//////////////////////////////////////////////// Accrete
typedef struct tACRPALENTRY {
	struct tACRPALENTRY *prior;
	COLORREF		c;
	long			n;
}	ACRPALENTRY, *pACRPALENTRY;

typedef struct tACRPALENTRYs {
	COLORREF		c;
	long			n;
}	ACRPALENTRYs, *pACRPALENTRYs;


BOOL			accretingPalettes= FALSE;
long			nAPE			= 0;
pACRPALENTRY	pAPE			= NULL;
////////////////////////////////////////////////////// GRAY Palette
#define SetGrayPaletteEntry(ppe,g) {\
			(ppe)->peRed  =\
			(ppe)->peGreen=\
			(ppe)->peBlue = (BYTE)((g)*RGB2CS);\
			(ppe)->peFlags= NULL;\
}

#define SetRGBPaletteEntry(ppe,rr,gg,bb) {\
			(ppe)->peRed  = (BYTE)((rr)*RGB2CS);\
			(ppe)->peGreen= (BYTE)((gg)*RGB2CS);\
			(ppe)->peBlue = (BYTE)((bb)*RGB2CS);\
			(ppe)->peFlags= NULL;\
}
#define SetPaletteEntry(ppe,rgb) {\
			(ppe)->peRed  = (BYTE)((rgb).red*RGB2CS);\
			(ppe)->peGreen= (BYTE)((rgb).green*RGB2CS);\
			(ppe)->peBlue = (BYTE)((rgb).blue *RGB2CS);\
			(ppe)->peFlags= NULL;\
}
////////////////////////////////////////////////////// HSV Palette
#define	SetHSVPaletteEntry(hh,ss,vv,ppe,hsv,rgb) {\
		(hsv).hue = (hh);\
		(hsv).saturation = (ss);\
		(hsv).value = (vv);\
		HSV2RGB(&(hsv),&(rgb));\
		SetPaletteEntry((ppe),(rgb));\
}

void CColorPal::RGB2HSV(pRGBCOLOR rgb,pHSVCOLOR hsv)
{
	double	r,g,b,h,s,mx,mn,delta;

	r = (double)(rgb->red  !=0.)?rgb->red:0.0;
	g = (double)(rgb->green!=0.)?rgb->green:0.0;
	b = (double)(rgb->blue !=0.)?rgb->blue:0.0;
	mx = max(max(r,g),b);			// This is v
	mn = min(min(r,g),b);
	delta = mx-mn;
	s = mx? (delta/mx) : 0.0F;		//saturation 0, if r=g=b = 0
	if( !s )
		h = NOHUE;              
	else { 							//Chromatic case:s<>0, so find hue
		if( r == mx )
			h = (g-b)/delta;		//Resulting color betn. Yellow&Magenta
		else
		if( g == mx )
			h = 2.0F + (b-r)/delta;	//Resulting color betn. Cyan&Yellow
		else
		if( b == mx )
			h = 4.0F + (r-g)/delta;	//Resulting color betn. Magenta&Cyan
		h = h * 60.F;				//Convert to degrees	
		if( h < 0.0F )
			h += 360.F;				//Make sure Hue is NonNegative
	}
	hsv->hue		= h;
	hsv->saturation = s;
	hsv->value		= mx;
}

void CColorPal::HSV2RGB(pHSVCOLOR hsv,pRGBCOLOR rgb)
{
	double	h,s,v,r,g,b,f,p,q,t;
	int i;
    ////////////////////
	h = hsv->hue;
	s = hsv->saturation;
	v = hsv->value;
	if( (hsv->hue==NOHUE) || (!s) ) // s=0:color on Black-white Line
		r = g = b = v;              // h=NOHUE:Achromatic color
	else 
	{ 							// chromatic case
		if (h == 360.)				// 360 deg = 0 deg
			h = 0.0;
		h = h/60.F;					// h in [0,6)	
		i = int(h);					// largest integer <= h
		f = h - (double)i;			// fractional part of h
		p = v * (1.F - s );
		q = v * (1.F - ( s * f ) );
		t = v * (1.F - ( s * (1.F - f ) ) );
		///////////
		switch( i ) 
		{
			case 0:r=v;g=t;b=p;break;
			case 1:r=q;g=v;b=p;break;
			case 2:r=p;g=v;b=t;break;
			case 3:r=p;g=q;b=v;break;
			case 4:r=t;g=p;b=v;break;
			case 5:r=v;g=p;b=q;break;
		}
	}
	rgb->red	= r;
	rgb->green	= g;
	rgb->blue	= b;
}

/*****************************************************************************
 *
 *	Function:	Make256ColorPal
 *
 *	Purpose:	Creates a general purpose color palette consisting of 24 hues
 *				each as a pure color and at seven other levels (pastel and
 *				blackened).  In addition, black, white and 33 gray levels are
 *				included which if appended to the 20 system colors provides
 *				247 total colors. The remaining 9 entries are unused and hence
 *				available for other purposes.  This palette produces reasonable
 *				color values for the sample programs in the 3d Graphic Tools
 *				package.
 *
 *	Returns:	-1 if UnSuccessful
 *				0
 *
 *****************************************************************************
 */
int CColorPal::Make256ColorPal(CColorPal* pColorPal)
{
	///////////////////////////
	LOGPALETTE		pal;
	LPLOGPALETTE	ppal= &pal;
	///////////////////////////
	PALETTEENTRY	pe[227];
	LPPALETTEENTRY	ppe = pe;
	double	h,dh;
	register long	i;
	///////////////////////////
	RGBCOLOR		rgb;
	HSVCOLOR		hsv;
    /////////////////////////////////
	ppal->palVersion	= 0x300;
	ppal->palNumEntries	= 227;
	*(ppal->palPalEntry)= *ppe;
	/////////////////////////////////
	for( dh=360./(double)NHUES, h=0,i=0; i<NHUES; h+=dh,i++ ) {
		SetHSVPaletteEntry( h, 0.25,  0.75,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 0.25,  1.0,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 0.75,  0.25,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 0.75,  0.75, ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 0.75,  1.0,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 1.0,   0.25,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 1.0,   0.75,	ppe, hsv, rgb ); ppe++;
		SetHSVPaletteEntry( h, 1.0,   1.0,	ppe, hsv, rgb ); ppe++;
	}
	////////////////////////////////////////////////////////////// Black
	SetRGBPaletteEntry( ppe, 0,0,0 );	
	////////////////////////////////////////////////////////////// Gray
	ppe++;
	for( h=1;h<=33;h++) {
		SetGrayPaletteEntry( ppe, (double)h*(1./33) );
		ppe++;
	}
	////////////////////////////////////////////////////////////// White
	SetRGBPaletteEntry( ppe, 1,1,1 );
	////////////////////////////////////////////////////////////// Black
	ppe++;
	///////////////////////////////// Create
	if(!pColorPal->CreatePalette(ppal) )
		return -1;
	//////////////	
	return	0;
}

/*****************************************************************************
 *
 *	Function:	MakeNewPal
 *
 *	Purpose:	This function generates a palette containing a variable number
 *				of hues and/or grays.
 *				The function uses the HSV color model
 *				h = [0,360]; 
 *				s = [0,1];
 *				v = [0,1];
 *				where 	h = 0 	is red,
 *						h = 120	is pure green
 *						h = 240 is blue.
 *
 *	Examples:	NewPalette( 0, 24, 9, 32 ) generates a palette containing 24
 *				hues each having four pastels, the pure hue and four blackened
 *				variations of the hue.  32 gray levels are also created.
 *
 *				NewPalette( 0, 0, 0, 192 ) generates a 192 level gray scale.
 *
 *				NewPalette( 43690, 1, 128, 0 ) generates 128 blue levels.
 *
 *	Returns:	-1 if UnSuccessful
 *				0
 *
 *****************************************************************************
 */
int CColorPal::MakeNewPal
		(
			CColorPal* 		pColorPal,
			double			baseHue,	// if nHues == 1 indicates hue to use
			int				nHues,		// number of color wheel subdivisions
			int				nHueLevels,	// number of variations per hue
			int				nGrays		// number of gray levels to emit
		)
{
	register long	i,j;
	///////////////////////////
	LOGPALETTE		pal;
	LPLOGPALETTE	ppal= &pal;
	///////////////////////////
	PALETTEENTRY	pe[MAX_COLOR];
	LPPALETTEENTRY	ppe = pe;
	///////////////////////////
	RGBCOLOR		rgb;
	HSVCOLOR		hsv;
	double			dh,h,dl,l;
    //////////////////////////////////////////
	if( nHues * nHueLevels < 1 && nGrays < 1 )
		return -1;
	//////////////////////////// No. of Colors		
	i = nGrays+nHues*nHueLevels;
	////////////////////////////
	ppal->palVersion	= 0x300;
	ppal->palNumEntries	= (WORD)i;
	*(ppal->palPalEntry)= *ppe;
    ////////////////////////////////////////////////////// Gray
	if( nGrays ) 
	{
		for( dl=1.F/(double)nGrays, l=0., i=1; i<=nGrays; i++, l+=dl ) 
			{
				SetGrayPaletteEntry( ppe, l );
			}
	}
    ////////////////////////////////////////////////////// Hues
	if( nHues && nHueLevels ) {
		for( dh=360.F/(double)nHues, h=((nHues>1)?0:baseHue), i=0; i<nHues; i++, h+=dh ) {
			if( nHueLevels == 1) 
			{											// pure hues only
				SetHSVPaletteEntry( h, 1.0F, 1.0F, ppe, hsv, rgb );
				continue;
			}
			for( dl=1.0F/(nHueLevels-(nHueLevels%2)), l=-dl*nHueLevels*0.5F, j=0; j<nHueLevels; j++, l+=dl ) {
				if( l<0.0F ) 
				{
					SetHSVPaletteEntry( h, l+1.0F, 1.0F, ppe, hsv, rgb );
				}
				else
				if( l==0.0F ) 
				{
					SetHSVPaletteEntry( h, 1.0F, 1.0F, ppe, hsv, rgb );
				}
				else 
				{
					SetHSVPaletteEntry( h, 1.0F, l-1.0F, ppe, hsv, rgb );
				}
			}
		}
	}
	///////////////////////////////// Create
	if(!pColorPal->CreatePalette(ppal) )
		return -1;
	//////////////	
	return	0;
}

/*****************************************************************************
 *
 *	Function:	LoadStockPal
 *
 *	Purpose:	Loads a palette from a named CLUT resource (several CLUTs are
 *				included in the CLUTS.RC resource script.
 *
 *	Example:	LoadStockPal( "EarthTones" ) loads the STOCKPAL resource
 *				whose name is "EarthTones" and returns a handle to it.
 *
 *	Returns:	-1 if UnSuccessful
 *				0
 *
 *****************************************************************************
 */
 
int CColorPal::LoadStockPal(CColorPal* pColorPal,LPSTR lpszName)
{
//	lpszName should be an integer ID like with # like "#ID"
	///////////////////////////////////////////////////////////
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);				
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionView_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);              
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
    ///////////////////////////////////////////////////////////
	register int	i;
	HSTOCKPAL		h;
	pSTOCKPAL		p;
	pRGBCOLOR		pc;
	///////////////////////////
	LOGPALETTE		pal;
	LPLOGPALETTE	ppal= &pal;
	///////////////////////////
	PALETTEENTRY	pe[MAX_COLOR];
	LPPALETTEENTRY	ppe = pe;
	///////////////////////////
//	HPALETTE		hpal;

	if( !(h = (HSTOCKPAL)LoadResource( hInstResourceClient,
			 FindResource( hInstResourceClient, lpszName, "STOCKPAL" ) )) )
		return NULL;
	/////////////////////////////////////	
	p = (pSTOCKPAL)LockResource( (HANDLE)h );
	i = p->nEntries;
    //////////////////////////////
	ppal->palVersion	= 0x300;
	ppal->palNumEntries	= (WORD)i;
	*(ppal->palPalEntry)= *ppe;
	pc	= p->pRGB;
	while( i-- ) {
		SetRGBPaletteEntry(ppe,pc->red,pc->green,pc->blue);
		pc++;
	}
	UnlockResource( (HANDLE)h );
	FreeResource( (HANDLE)h );
	/////////////////////////////
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);              
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	///////////////////////////////// Create
	if(!pColorPal->CreatePalette(ppal) )
		return -1;
	//////////////	
	return	0;

}

CColorPal* CColorPal::SelectPal(CClientDC* pDC, CColorPal* pPal)
{
	if( pPal ) 
	{
		CColorPal* pPalOld;
		if(!(pPalOld = (CColorPal*)(pDC->SelectPalette( pPal,FALSE)) ) )
			return (CColorPal*) NULL;
		/////////////////////////////	
		pDC->RealizePalette();
		return (CColorPal*)pPalOld;
	}
	return (CColorPal*) NULL;
}

void CColorPal::DisposePal(CColorPal* pPal)
{
	if( pPal )
		DeleteObject();
}
/*
BOOL CColorPal::AccretePalette(void)
{
	return accretingPalettes;
}

BOOL CColorPal::AccretingPalette(void)
{
	return accretingPalettes;
}

BOOL CColorPal::SetAccretePalette(BOOL state)
{
	BOOL	bPrev;
	Get3dContext();
	bPrev = accretingPalettes;
	accretingPalettes = state;
	return bPrev;
}

void _cdecl AccretePaletteEntry(COLORREF c)
{
	pACRPALENTRY	tpAPE;

	if( !accretingPalettes )
		return;

	tpAPE = pAPE;
	while( tpAPE ) {
		if( tpAPE->c == c ) {
			tpAPE->n++;
			return;
		}
		tpAPE = tpAPE->prior;
	}
	nAPE++;
	tpAPE = (pACRPALENTRY)NewPtr( sizeof(ACRPALENTRY) );
	tpAPE->c = c;
	tpAPE->n = 1;
	tpAPE->prior = pAPE;
	pAPE = tpAPE;
}

void	FrequencySort(pACRPALENTRYs pAPEs,long n)
{
	register long	i,jump;
	Boolean			done;
	ACRPALENTRYs			temp;
	pACRPALENTRYs			pAPEsi,pAPEsj;

	jump = n;
	done = false;
	while( jump ) {
		jump=LLSR(jump,1);
		do	{
			done = true;
			for( i = 0, pAPEsi = pAPEs; i < (n-jump); i++, pAPEsi++ ) {
				pAPEsj = &pAPEs[i + jump];
				if(	 pAPEsi->n > pAPEsj->n ) {
					temp	= *pAPEsi;
					*pAPEsi	= *pAPEsj;
					*pAPEsj	= temp;
					done 	= false;
				}
			}
		} while( !done );
	}
}


HPALETTE CColorPal::GetAccretedPalette(void)
{
	int				n;
	LPLOGPALETTE	ppal;
	LPPALETTEENTRY	ppe;
	HPALETTE		hpal;
	pACRPALENTRYs	pAPEs,tpAPEs;

	if( !pAPE )
		return NULL;

	pAPEs	= (pACRPALENTRYs)NewPtr( sizeof(ACRPALENTRYs) * nAPE );
	tpAPEs	= pAPEs;
	while( pAPE ) {
		pACRPALENTRY	tpAPE = pAPE;
		tpAPEs->c = tpAPE->c;
		tpAPEs->n = tpAPE->n;
		tpAPEs++;
		pAPE = tpAPE->prior;
		DisposPtr( (Ptr)tpAPE );
	}
	FrequencySort( pAPEs, nAPE );
	n = nAPE>236? 236 : (int)nAPE;
	nAPE = 0;
	ppal = (LPLOGPALETTE)NewPtr( sizeof(LOGPALETTE)+n*sizeof(PALETTEENTRY) );
	if( !ppal )
		return NULL;
	ppal->palVersion	= 0x300;
	ppal->palNumEntries	= (WORD)n;
	ppe	= ppal->palPalEntry;
	tpAPEs = pAPEs;
	while( n-- ) {
		ppe->peRed  = GetRValue(tpAPEs->c);
		ppe->peGreen= GetGValue(tpAPEs->c);
		ppe->peBlue = GetBValue(tpAPEs->c);
		ppe->peFlags= NULL;
		ppe++;
		tpAPEs++;
	}
	hpal = CreatePalette( ppal );
	DisposPtr( (Ptr)pAPEs );
	DisposPtr( (Ptr)ppal );
	return	hpal;
}
*/
////////////////////////////// end of module //////////////

