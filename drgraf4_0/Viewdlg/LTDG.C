/*****************************************************************************
 *	File:		LtDg.c
 *
 *	Purpose:	Implements setting of lighting information via interactive
 *				dialog boxes.
 *
 *	Version:	Microsoft C / Windows
 *
 *	EXPORTS
 *		DoLightingDialog
 *		DoLightSourceDialog
 *		PanePalette
 *		PaneColor
 *
 *	(C) 1991 Mark M. Owen -- All rights reserved.
 *
 *****************************************************************************
 */
#include <WIN_TRIM.H>
#include <OSINTF.h>

#ifndef __TURBOC__

#ifndef _FAR_
#define	_FAR_ _far
#endif // _FAR_

int _FAR_ _cdecl sprintf(char _FAR_ *, const char _FAR_ *, ...);	// from <stdio.h>
long _FAR_ _cdecl atol(const char _FAR_ *);							// from <stdlib.h>
char _FAR_ * _FAR_ _cdecl itoa(int, char _FAR_ *, int);				// from <stdlib.h>

#else

#include <stdio.h>
#include <stdlib.h>

#endif // __TURBOC__

#include <string.h>
#include <Camera.h>
#include <3dColor.h>

#define _LTDG_
#include <3dDialog.rh>
#include <3DDIALOG.h>

#if defined(_MSC_VER)
#	if _MSC_VER >= 700
#		pragma warning(disable:4100) // disable unreferenced parameter warning
#	endif
#endif


#define PANEPALETTECLASS		"PanePalette"
#define PANECOLORCLASS			"PaneColor"


RendAttr	RA;				// working copy of rendering attributes
pLighting	pL	= NULL;		// lighting information structure
pLtSource	pLS	= NULL; 	// light source array


static pLighting		pLin;
static pLighting		pLout;
static Boolean			pLchanged;
static pLtSource		pLSin;
static HANDLE			ghInst;


long WINAPI	DoLightingDialog		(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
long WINAPI	DoLightSourceDialog		(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
long WINAPI	PanePalette				(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
long WINAPI	PaneColor				(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

static void		RegisterDialogClasses	(HANDLE hInst);
static void		UnRegisterDialogClasses	(HANDLE hInst);
static long		StringToNum				(char *str);
static void		NumToString				(long n,char *str);
static Fixed	StringToFixed			(char *str);
static void		FixedToString			(Fixed f,char *str);
static void		InvalidateItemRect		(HWND hDlg,int which);
static void		set_FIXED				(HWND hDlg,WPARAM wParam,Fixed value);
static void		set_ULONG				(HWND hDlg,WPARAM wParam,unsigned long value);
static void		get_FIXED				(HWND hDlg,WPARAM wParam,Fixed *data);
static void 	get_ULONG				(HWND hDlg,WPARAM wParam,unsigned long *data);
static void		get_PALETTE				(HWND hDlg,unsigned long* red,unsigned long* green,unsigned long* blue);


/*****************************************************************************
 *
 *	Function:	LightingDialog
 *
 *	Purpose:	Displays a dialog box which allows the user to set the ambient
 *				light color and intensity level; and to specify the number of
 *				point light sources which are to be used.
 *
 *				The caller supplies a pointer to an initialized Lighting
 *				structure which is updated when changes are made to the level
 *				and color of the ambient light and the OK button is pressed,
 *				provided the number of point light sources is not changed.  If
 *				the number of point light sources is changed (since they are a
 *				variable length array at the end of the Lighting structure) a
 *				new Lighting structure is allocated and initialized using the
 *				existing information.  If the number of point light sources has
 *				increased, the new sources will be at the end of the "source"
 *				array, set to a color of black, level zero and located at the
 *				origin (X=Y=Z=0).  If the number of point light sources has
 *				decreased extra sources at the top of the array are discarded.
 *
 *	Returns:	NULL if the number of point light sources does not change or if
 *				the number did change but memory for the new lights could not
 *				be allocated;
 *
 *				pLighting if the number of point light sources changes.
 *
 *****************************************************************************
 */
pLighting	API3D LightingDialog(
		HWND		hWnd,
		HANDLE		hInst,
		pLighting	pL
	)
{
	FARPROC	lpDialogProc;

	if( !pL )
		return NULL;

	ghInst = hInst;
	RegisterDialogClasses( hInst );
	pLchanged = false;
	pLin = pL;
	pLout = NewLighting(pLin->color.red,pLin->color.green,pLin->color.blue,pLin->level,pLin->nSources,pLin->source);
	lpDialogProc = MakeProcInstance( (FARPROC)DoLightingDialog, hInst );
	DialogBox( (HINSTANCE)hInst, "LIGHTINGDIALOG", hWnd, (DLGPROC)lpDialogProc );
	FreeProcInstance( lpDialogProc );
	UnRegisterDialogClasses( hInst );
	if( !pLchanged ) {
		DisposPtr( (Ptr)pLout );
		return pLin;
	}
	DisposPtr( (Ptr)pLin );
	return pLout;
}

/*****************************************************************************
 *
 *	Function:	LightSourceDialog
 *
 *	Purpose:	Displays a dialog box which allows the user to set the color,
 *				intensity level, location, focus and shape of an individual
 *				point light source.
 *
 *				The caller supplies a pointer to an initialized LtSource
 *				structure which will be modified if the OK button is pressed.
 *
 *				Note that a TransformLighting must be called after a light
 *				source has been modified with this function, to transform the
 *				lights coordinates relative to the point of view.  This need
 *				not be done on an individual basis, rather it could be done
 *				after all light source changes are made.  Either way will work
 *				equally well, the latter being a slighty more expensive but
 *				more flexible if you don't know or are not controlling what
 *				the user is doing.
 *
 *****************************************************************************
 */
void API3D LightSourceDialog(
		HWND		hWnd,
		HANDLE		hInst,
		pLtSource	pLS
	)
{
	FARPROC	lpDialogProc;

	if( !pLS )
		return;

	ghInst = hInst;
	RegisterDialogClasses( hInst );
	pLSin = pLS;
	lpDialogProc = MakeProcInstance( (FARPROC)DoLightSourceDialog, hInst );
	DialogBox( (HINSTANCE)hInst, "LIGHTSOURCEDIALOG", hWnd, (DLGPROC)lpDialogProc );
	FreeProcInstance( lpDialogProc );
	UnRegisterDialogClasses( hInst );
}

static void RegisterDialogClasses(HANDLE hInst)
{
	WNDCLASS	wc;

	wc.style		= NULL;					// Class style(s).
	wc.cbClsExtra	= 0;					// No per-class extra data.
	wc.cbWndExtra	= 0;					// No per-window extra data.
	wc.hInstance	= hInst;				// Application that owns the class.
	wc.hIcon		= NULL;
	wc.lpszMenuName	= NULL;
	wc.hbrBackground= (HBRUSH)(COLOR_WINDOW+1);

	wc.lpfnWndProc	= PaneColor;			// Message service function
	wc.lpszClassName= PANECOLORCLASS;		// Name used in call to CreateWindow.
	wc.hCursor		= LoadCursor( (HINSTANCE)NULL, IDC_ARROW );
	RegisterClass( &wc );					// Register window class.

	wc.lpfnWndProc	= PanePalette;			// Message service function
	wc.lpszClassName= PANEPALETTECLASS;		// Name used in call to CreateWindow.
	wc.hCursor		= LoadCursor( (HINSTANCE)hInst, "Dropper" );
	RegisterClass( &wc );					// Register window class.
}

#ifdef __TURBOC__
#pragma argsused
#endif
#if defined(_MSC_VER)
#	if _MSC_VER >= 700
#		pragma warning(disable:4100) // disable unused argument warnings
#	endif
#endif
static void UnRegisterDialogClasses(HANDLE hInst)
{
/*	UnregisterClass( (LPSTR)PANECOLORCLASS, hInst );
	UnregisterClass( (LPSTR)PANEPALETTECLASS, hInst );
*/
}

static long	StringToNum(char *str)
{
	return strlen(str)? atol( str ) : 0;
}

static void	NumToString(long n,char *str)
{
	char	s[256] = "";
	sprintf( s,"%ld", n );
	strcpy( str, s );
}

static Fixed	StringToFixed(char *str)
{
	FPType	f;
	f = strlen(str)? (FPType)atof(str) : 0;
	return x2fix(&f);
}

static void	FixedToString(Fixed f,char *str)
{
	char	s[256] = "";
	sprintf( s,"%1.3f", fix2x(f) );
	strcpy( str, s );
}

static void	InvalidateItemRect(HWND hDlg,int which)
{
	HANDLE		h = GetDlgItem( hDlg, which );
	if( h )
		InvalidateRect( h, NULL, TRUE );
}

static void set_FIXED(HWND hDlg,WPARAM wParam,Fixed value)
{
	char	nstr[257]="";
	FixedToString( value, nstr );
	SetDlgItemText( hDlg, wParam, nstr );
}

static void set_ULONG(HWND hDlg,WPARAM wParam,unsigned long value)
{
	char	nstr[257]="";
	NumToString( value, nstr );
	SetDlgItemText( hDlg, wParam, nstr );
}

static void	get_FIXED(HWND hDlg,WPARAM wParam,Fixed *data)
{
	char	nstr[257]="";

	GetDlgItemText( hDlg, wParam, nstr, 256 );
	*data = StringToFixed( nstr );
}

static void get_ULONG(HWND hDlg,WPARAM wParam,unsigned long *data)
{
	char	nstr[257]="";
	GetDlgItemText( hDlg, wParam, nstr, 256 );
	*data = StringToNum( nstr );
}

static void	get_PALETTE(HWND hDlg,unsigned long* red,unsigned long* green,unsigned long* blue)
{
	get_ULONG( hDlg, ID_RED, red );
	get_ULONG( hDlg, ID_GREEN, green );
	get_ULONG( hDlg, ID_BLUE, blue );
	UpdateWindow( GetDlgItem( hDlg, ID_COLOR ) );
}

#ifdef __TURBOC__
#pragma argsused
#endif

#pragma optimize("",off)
long WINAPI DoLightingDialog(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	char		nstr[257]="";
	long		n;
	int 		i;
	pLtSource	pLSt;

	static HMENU			hmBar;
	static BOOL 			mInit = FALSE;
	static unsigned long	red,green,blue;
	static Fixed			level;
	static long				nSources;

	switch( message ) {

		case WM_INITMENUPOPUP:
			if( mInit )
				break;
			mInit = TRUE;
			hmBar = (HMENU)wParam;
			nSources= pLin->nSources;
			i = 1;
			while( (long)i <= nSources ) {
				itoa( i, nstr, 10 );
				AppendMenu( hmBar, MF_STRING, i+ID_LIGHTSRCBASE, nstr );
				i++;
			}
			break;

		case WM_INITDIALOG:
			level	= pLin->level;
			red		= pLin->color.red;
			green	= pLin->color.green;
			blue	= pLin->color.blue;
			nSources= pLin->nSources;
			set_FIXED( hDlg, ID_LEVEL, level );
			set_ULONG( hDlg, ID_RED, red );
			set_ULONG( hDlg, ID_GREEN, green );
			set_ULONG( hDlg, ID_BLUE, blue );
			set_ULONG( hDlg, ID_SOURCES, nSources );
			return TRUE;

		case WM_COMMAND:
			switch( wParam ) {
				case IDOK: {
					pLighting pL = pLchanged? pLout : pLin;
					pL->color.red	= (colorFactor)red;
					pL->color.green	= (colorFactor)green;
					pL->color.blue	= (colorFactor)blue;
					pL->level		= level;
					pL->magnitude	= (FPType)(red + green + blue);
					pL->nSources	= (short)nSources;
					// intentional drop through to IDCANCEL case...
					}
				case IDCANCEL:
					mInit = FALSE;
					EndDialog( hDlg, FALSE );
					return TRUE;

				case ID_RED:	get_ULONG( hDlg, ID_RED, &red );
								return TRUE;
				case ID_GREEN:	get_ULONG( hDlg, ID_GREEN, &green );
								return TRUE;
				case ID_BLUE:	get_ULONG( hDlg, ID_BLUE, &blue );
								return TRUE;
				case ID_LEVEL:	get_FIXED( hDlg, ID_LEVEL, &level );
								return TRUE;
				case ID_PALETTE:get_PALETTE( hDlg, &red, &green, &blue );
								return TRUE;

				case ID_SOURCES:
					GetDlgItemText( hDlg, wParam, nstr, 256 );
					if( (n = StringToNum( nstr )) < 0 ) {
						InvalidateItemRect( hDlg, ID_SOURCES );
						SetDlgItemText( hDlg, ID_SOURCES, nstr );
						break;
					}
					if( n != nSources ) {
						pLSt = (pLtSource)NewPtr( sizeof(LtSource)*n );
						BlockMove((Ptr)pLout->source,(Ptr)pLSt,sizeof(LtSource)*(n<nSources?n:nSources));
						DisposPtr( (Ptr)pLout );
						pLout = NewLighting((colorFactor)red,(colorFactor)green,(colorFactor)blue,(Fixed)level,(short)n,pLSt);
						DisposPtr( (Ptr)pLSt );
						if( pLout ) {
							for( i=(int)nSources; (long)i<n; i++ )
								Set3dLtSource( &pLout->source[i],0,0,0,f_0,f_0,f_0,f_0);
							pLchanged = true;
						}
						else {
							pLchanged = false;
							MessageBox( hDlg, "Allocate new lighting area failed",NULL,
								MB_ICONEXCLAMATION|MB_TASKMODAL|MB_OK
							);
						}
						while( nSources < n ) {
							itoa( (int)(++nSources), nstr, 10 );
							AppendMenu(hmBar,MF_STRING,(WORD)(nSources+ID_LIGHTSRCBASE),nstr);
						}
						while( nSources > n ) {
							DeleteMenu( hmBar, (WORD)(nSources+ID_LIGHTSRCBASE), MF_BYCOMMAND );
							nSources--;
						}
						DrawMenuBar( hDlg );
					}
					return TRUE;

				default:
					if( wParam > ID_LIGHTSRCBASE ) {
						LightSourceDialog( hDlg, ghInst, &pLout->source[wParam-ID_LIGHTSRCBASE-1] );
						pLchanged = true;
						return TRUE;
					}
					break;
			}
			break;
	}
	return FALSE;
}
#pragma optimize("",on)

#ifdef __TURBOC__
#pragma argsused
#endif

long WINAPI DoLightSourceDialog(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static unsigned long	red,green,blue;
	static Fixed			level;
	static Point3d			location,focus;
	static Fixed			shape;

	switch( message ) {

		case WM_INITDIALOG:
			level	= pLSin->level;
			red		= pLSin->color.red;
			green	= pLSin->color.green;
			blue	= pLSin->color.blue;
			location= pLSin->location;
			focus	= pLSin->focus;
			shape	= x2fix( &pLSin->shape );

			set_FIXED(hDlg,ID_LEVEL,level);
			set_ULONG( hDlg, ID_RED, red );
			set_ULONG( hDlg, ID_GREEN, green );
			set_ULONG( hDlg, ID_BLUE, blue );
			set_FIXED( hDlg, ID_LX, location.x );
			set_FIXED( hDlg, ID_LY, location.y );
			set_FIXED( hDlg, ID_LZ, location.z );
			set_FIXED( hDlg, ID_AIMX, focus.x );
			set_FIXED( hDlg, ID_AIMY, focus.y );
			set_FIXED( hDlg, ID_AIMZ, focus.z );
			set_FIXED( hDlg, ID_FOCUS, shape );
			return TRUE;

		case WM_COMMAND:

			switch( wParam ) {

				case IDOK:
					pLSin->color.red	= (fract16)red;
					pLSin->color.green	= (fract16)green;
					pLSin->color.blue	= (fract16)blue;
					pLSin->level		= level;
					pLSin->magnitude	= (FPType)(red + green + blue);
					Set3dLtSource(
						pLSin, (colorFactor)red, (colorFactor)green, (colorFactor)blue,
						(Fixed)level, location.x, location.y, location.z
					);
					AimLightSource( pLSin, focus.x, focus.y, focus.z );
					pLSin->shape = fix2x( shape );
					/*	a transform lighting call should occur after changes, but
						we won't do it here because more changes may be made...
						the caller must do it when ready.
					*/
					EndDialog( hDlg, TRUE );
					return TRUE;

				case IDCANCEL:
					EndDialog( hDlg, FALSE );
					return TRUE;

				case ID_RED:	get_ULONG( hDlg, ID_RED, &red );
								return TRUE;
				case ID_GREEN:	get_ULONG( hDlg, ID_GREEN, &green );
								return TRUE;
				case ID_BLUE:	get_ULONG( hDlg, ID_BLUE, &blue );
								return TRUE;
				case ID_LEVEL:	get_FIXED( hDlg, ID_LEVEL, &level );
								return TRUE;
				case ID_LX:		get_FIXED( hDlg, ID_LX, &location.x );
								return TRUE;
				case ID_LY:		get_FIXED( hDlg, ID_LY, &location.y );
								return TRUE;
				case ID_LZ:		get_FIXED( hDlg, ID_LZ, &location.z );
								return TRUE;
				case ID_AIMX:	get_FIXED( hDlg, ID_AIMX, &focus.x );
								return TRUE;
				case ID_AIMY:	get_FIXED( hDlg, ID_AIMY, &focus.y );
								return TRUE;
				case ID_AIMZ:	get_FIXED( hDlg, ID_AIMZ, &focus.z );
								return TRUE;
				case ID_FOCUS:	get_FIXED( hDlg, ID_FOCUS, &shape );
								return TRUE;
				case ID_PALETTE:get_PALETTE( hDlg, &red, &green, &blue );
								return TRUE;
			}
			break;
	}
	return FALSE;
}

/*****************************************************************************
 *
 *	Function:	PanePalette
 *
 *	Purpose:	Services mouse messages in an ID_PALETTE custom control of a
 *				dialog box providing a method of selecting a color from those
 *				displayed within the box (an underlying ICON for example).
 *
 *				For mouse messages the following occurs:
 *
 *					when the mouse button is down:
 *						the color of the pixel at the mouse point is obtained
 *						and the ID_RED,ID_GREEN and ID_BLUE edit wParams are set
 *						to the corresponding color components.
 *
 *				Note that is is permissible to click inside the ID_PALETTE
 *				then drag outside the pane to obtain different values. The
 *				mouse location is tracked as long as the button is down.
 *
 *****************************************************************************
 */
long WINAPI	PanePalette(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC 		hDC,hDCm;
	HANDLE		hBM;
	RECT		r;
	BITMAP		BM;
	RGBColor	rgb;
	COLORREF	CS;
	POINT		m;
	char		str[257]="";
	HWND		hDlg = GetParent( hWnd );
	HWND		hw;
	static BOOL	active = FALSE;

	switch( message ) {

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			active = TRUE;

		case WM_MOUSEMOVE:
			if( active ) {
				hDC			= GetDC( hWnd );
				m			= MAKEPOINT( lParam );
				CS			= GetPixel( hDC, m.x, m.y );
				rgb.red		= (fract16)(GetRValue( CS ) * 257);
				rgb.green	= (fract16)(GetGValue( CS ) * 257);
				rgb.blue	= (fract16)(GetBValue( CS ) * 257);
				NumToString( rgb.red, str );
				SetDlgItemText( hDlg, ID_RED, str );
				NumToString( rgb.green, str );
				SetDlgItemText( hDlg, ID_GREEN, str );
				NumToString( rgb.blue, str );
				SetDlgItemText( hDlg, ID_BLUE, str );
				ReleaseDC( hWnd, hDC );
				hw = GetDlgItem( hDlg, ID_COLOR );
				InvalidateRect( hw, NULL, false );
				UpdateWindow( hw );
			}
			break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			active = FALSE;
			break;

		case WM_PAINT:
			hDC = GetDC( hWnd );
			GetClientRect( hWnd, &r );
			hDCm= CreateCompatibleDC( hDC );
			hBM = LoadBitmap( ghInst, "ColorWheel" );
			GetObject( (HANDLE)hBM, (int)sizeof(BITMAP), (LPSTR)&BM );
			SelectObject( hDCm, hBM );
			ReleaseDC( hWnd, hDC );
			hDC = BeginPaint( hWnd, &ps );
			StretchBlt(
				hDC,  0, 0, r.right, r.bottom,
				hDCm, 0, 0, BM.bmWidth, BM.bmHeight,
				SRCCOPY
			);
			EndPaint( hWnd, &ps );
			DeleteDC( hDCm );
			DeleteObject( hBM );
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
    }
	return NULL;
}

long WINAPI	PaneColor(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC 		hDC;
	RECT		r;
	HBRUSH		hb;
	RGBColor	rgb;
	char		str[257]="";
	HWND		hDlg = GetParent( hWnd );

	switch( message ) {
		case WM_PAINT:
			GetClientRect( hWnd, &r );
			GetDlgItemText( hDlg, ID_RED, str, 256 );
			rgb.red		= (fract16)StringToNum( str );
			GetDlgItemText( hDlg, ID_GREEN, str, 256 );
			rgb.green	= (fract16)StringToNum( str );
			GetDlgItemText( hDlg, ID_BLUE, str, 256 );
			rgb.blue	= (fract16)StringToNum( str );
			hDC = BeginPaint( hWnd, &ps );
			hb = CreateSolidBrush( RGB(rgb.red,rgb.green,rgb.blue) );
			FillRect( hDC, &r, hb );
			DeleteObject( hb );
			EndPaint( hWnd, &ps );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
    }
	return NULL;
}

/*****************************************************************************
 *
 *	Function:	SetDefaultRendAttrs
 *
 *	Purpose:	Provides default values for a set of rendering attributes.
 *
 *	Returns:	Not Applicable.
 *
 *****************************************************************************
 */
void	API3D SetDefaultRendAttrs(pRendAttr pRA,colorFactor r,colorFactor g,colorFactor b)
{
	short i;

	pRA->R					=	r;
	pRA->G					=	g;
	pRA->B					=	b;
	pRA->frameColor.red		=	32767;
	pRA->frameColor.green	=	32767;
	pRA->frameColor.blue	=	32767;
	pRA->lightSoue	˜œššš+,šœœ’šœœše;
	pRA->ambientEffect		=	true;
	pRA->normalVisibility	=	true;
	pRA->framed				=	true;
	pRA->wireframed			=	falsšœœœœ’’œœš˜œœœššš’ššš˜˜šš˜ššš˜˜šœœ˜–˜œššššœ˜ œœ˜œš˜š  šœ˜œœ,œœšœœš˜œœœ˜˜š–˜’˜ššššœ’˜œ˜š , ˜šœ š˜,˜ ,œœœ–šššœ+œœ˜œšš˜š  œœœœšœœœœœ˜œššœ,+œšš˜,––˜š˜š˜,šššœ˜˜˜šš,œœšetPt3d( &RA.tx[i].txScalars, f_1,f_1,f_1 );
		SetPt3d( &RA.tx[i].txTranslations, f_0,f_0,f_0 );
	}
	RA.tx[TXI_WOOD].txArgument[0] = 0;		// add noise?
	RA.tx[TXI_WOOD].txArgument[1] = f_0p6;	// light grain %
	RA.tx[TXI_WOOD].txArgument[2] = f_0p5;	// dark grain %
	RA.tx[TXI_WOOD].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_ROCK].txArgument[0] = f_16;	// width of band
	RA.tx[TXI_ROCK].txArgument[1] = f_0p6;	// light grain %
	RA.tx[TXI_ROCK].txArgument[2] = f_0p5;	// med grain %
	RA.tx[TXI_ROCK].txArgument[3] = f_0p25; // dark grain %
	RA.tx[TXI_RGB].txArgument[0] = 0;		// add noise?
	RA.tx[TXI_RGB].txArgument[1] = 0;		// N.A.
	RA.tx[TXI_RGB].txArgument[2] = 0;		// N.A.
	RA.tx[TXI_RGB].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_DEPTH].txArgument[0] = 0; 	// add noise?
	RA.tx[TXI_DEPTH].txArgument[1] = f_32;	// modulus
	RA.tx[TXI_DEPTH].txArgument[2] = 0; 	// N.A.
	RA.tx[TXI_DEPTH].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_BUMPS].txArgument[0] = 0; 	// field scalar
	RA.tx[TXI_BUMPS].txArgument[1] = f_0p6;˜š”œ–+˜šœš˜œ ššœœœœœš˜œ˜š˜’œ šš˜œšš˜  +˜šœ˜  šœ˜œœœ˜œ˜šš˜œœœœœ”œššš˜š ššœœœ,šœ šœœœœœœœ”œœšš,   šššš šš˜˜œ +œœ’œ šœ šœœœœš”  ššœ ’+˜š– š šœœš,œœœ˜š