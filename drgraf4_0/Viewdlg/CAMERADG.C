/****************************************************************************
 *	Unit:		CameraDG.c
 *
 *	Purpose:	Interactive camera aiming dialog providing viewpoint control.
 *
 *	(C) 1991 Mark M. Owen -- All Rights Reserved.
 *
 *	Version:	Microsoft C / Windows
 *
 *	EXPORTS
 *		DoCameraDialog
 *		PaneXZ
 *		PaneXY
 *		PaneZY
 *		Pane3d
 *
 ****************************************************************************
 */
#include <WIN_TRIM.H>
#include <3dClipng.h>
#include <3dGrid.h>
#include <3dText.h>
#include <Camera.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CAMERADG_
#include <3dDialog.rh>
#include <3DDIALOG.h>


#define PANEXZCLASS		"PaneXZ"
#define PANEXYCLASS		"PaneXY"
#define PANEZYCLASS		"PaneZY"
#define PANE3DCLASS 	"Pane3d"

#define	DeltaRect(r,h,v)	{	(h)=(short)((r).right-(r).left); (v)=(short)((r).bottom-(r).top);	}

// default public camera attribute containers

Point3d		Camera	= {-f_90,f_100,-f_180};	//	camera location
Point3d		Focus	= {f_0,f_0,f_0};		//	camera focus point
Fixed		Lens	= Lens50mm;				//	angle of view / magnification
Fixed		Roll	= f_0;					//	camera roll angle
Fixed		RefSize = f_128;				//	reference grid size

static Point3d		_from, _to;
static pPoint3d		pfrom,pto;
static Fixed		_roll, *proll, _view, *pview;
static short		ch, cv;
static FPType		sh, sv;
static Fixed		refSz, cX,cY;
static Point3d		min, max;
static Point3d		steps	= {f_4,f_4,f_4};
static GridOptions	options;
static RECT			box;
static HPEN			p1x1, p2x2, p3x3;
static HBRUSH		hbRed;


long	FAR	PASCAL	DoCameraDialog	(HWND, UINT, WPARAM, LPARAM);
long	FAR	PASCAL	PaneXZ			(HWND, UINT, WPARAM, LPARAM);
long	FAR	PASCAL	PaneXY			(HWND, UINT, WPARAM, LPARAM);
long	FAR	PASCAL	PaneZY			(HWND, UINT, WPARAM, LPARAM);
long	FAR	PASCAL	Pane3d			(HWND, UINT, WPARAM, LPARAM);


static void		RegisterDialogClasses	(HANDLE hInst);
static void		UnregisterDialogClasses	(HANDLE hInst);
static Fixed	StringToFixed			(char *str);
static void		FixedToString			(Fixed f,char *str);
static void 	StringToPoint3d			(char *str,Point3d *p);
static void 	Point3dToString			(Point3d *p,char *str);
static void		InvalidateItemRect		(HWND hDlg,int which);
static Boolean	Changed3d				(Point3d *p1,Point3d *p2);
static long		Pane2d					(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam,short which);


Boolean	API3D CameraDialog(
		HWND		hWnd,
		HANDLE		hInst,
		Fixed		refSize,
		pPoint3d	from,
		pPoint3d	to,
		pFixed		roll,
		pFixed		view
	)
{
	FARPROC	lpDialogProc;
	BOOL	rslt;

	RegisterDialogClasses( hInst );
	pfrom	= from;
	pto		= to;
	proll	= roll;
	pview	= view;
	refSz	= refSize;
	cX		= GetCenterX();
	cY		= GetCenterY();
	lpDialogProc = MakeProcInstance( (FARPROC)DoCameraDialog, hInst );
	rslt = DialogBox( (HINSTANCE)hInst, "CAMERADIALOG", hWnd, (DLGPROC)lpDialogProc );
	FreeProcInstance( lpDialogProc );
	UnregisterDialogClasses( hInst );
	SetCenter( cX, cY );
	return (Boolean)rslt;
}

static void RegisterDialogClasses(HANDLE hInst)
{
	WNDCLASS	wc;

	wc.style		= NULL;					// Class style(s).
	wc.cbClsExtra	= 0;					// No per-class extra data.
	wc.cbWndExtra	= 0;					// No per-window extra data.
	wc.hInstance	= hInst;				// Application that owns the class.
	wc.hIcon		= NULL;
	wc.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wc.lpszMenuName	= NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	wc.lpfnWndProc = PaneXZ;			// Message service function
	wc.lpszClassName = PANEXZCLASS;		// Name used in call to CreateWindow.
	RegisterClass( &wc );				// Register window class.

	wc.lpfnWndProc = PaneXY;			// Message service function
	wc.lpszClassName = PANEXYCLASS;		// Name used in call to CreateWindow.
	RegisterClass( &wc );				// Register window class.

	wc.lpfnWndProc = PaneZY;			// Message service function
	wc.lpszClassName = PANEZYCLASS;		// Name used in call to CreateWindow.
	RegisterClass( &wc );				// Register window class.

	wc.lpfnWndProc = Pane3d;			// Message service function
	wc.lpszClassName = PANE3DCLASS;		// Name used in call to CreateWindow.
	RegisterClass( &wc );				// Register window class.
}

#ifdef __TURBOC__
#pragma argsused
#endif // __TURBOC__

#if defined(_MSC_VER)
#	if _MSC_VER >= 700
#		pragma warning(disable:4100) // disable unreferenced parameter warning
#	endif
#endif

void	UnregisterDialogClasses	(HANDLE hInst)
{
/*
	UnregisterClass( PANEXZCLASS, hInst );
	UnregisterClass( PANEXYCLASS, hInst );
	UnregisterClass( PANEZYCLASS, hInst );
	UnregisterClass( PANE3DCLASS, hInst );
 */
}

Fixed	StringToFixed(char *str)
{
	FPType	f;
	f = strlen(str)? (FPType)atof(str) : 0;
	return x2fix(&f);
}

void	FixedToString(Fixed f,char *str)
{
	char	s[256] = "";
	sprintf( s,"%1.2f", fix2x(f) );
	strcpy( str, s );
}

void StringToPoint3d(char *S,Point3d *p)
{
	char	*t, *x, *y, *z, str[257]="";

	strcpy( str, S );
	x	= str;
	t	= x;
	while( *t != ' ' )	t++;
	*t++= 0x00;
	y	= t;
	while( *t != ' ' )	t++;
	*t++= 0x00;
	z	= t;
	p->x = StringToFixed( x );
	p->y = StringToFixed( y );
	p->z = StringToFixed( z );
}

void Point3dToString(Point3d *p,char *str)
{
	char	s[257]="",*ps = str;

	*ps = 0x00;
	sprintf( s, "%1.2f ", fix2x(p->x) );
	strcat( ps, s);
	sprintf( s, "%1.2f ", fix2x(p->y) );
	strcat( ps, s);
	sprintf( s, "%1.2f",  fix2x(p->z) );
	strcat( ps, s);
}

void	InvalidateItemRect(HWND hDlg,int which)
{
	HANDLE	h = GetDlgItem( hDlg, which );

	if( h )
		InvalidateRect( h, NULL, TRUE );
}

Boolean Changed3d(Point3d *p1,Point3d *p2)
{
	if(	( p1->x != p2->x )
	||	( p1->y != p2->y )
	||	( p1->z != p2->z )
	  )
		return TRUE;
	return FALSE;
}

#ifdef __TURBOC__
#pragma argsused
#endif // __TURBOC__

#pragma optimize("",off)
long FAR PASCAL DoCameraDialog(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	Matrix		vxf			= *GetMatrix( MT_VIEWER );
	Matrix		ixf			= *GetMatrix( MT_INSTANCE );
	Matrix		cxf			= *GetMatrix( MT_COMBINED );
	Boolean		bParallel	= GetParallel();
	Fixed		cx			= GetCenterX(),
				cy			= GetCenterY();
	char		nstr[257]="";
	Fixed		fxd;
	Point3d 	p3d;

	switch( message ) {

		case WM_INITDIALOG:
			_from	= *pfrom;
			_to		= *pto;
			_roll	= *proll;
			_view	= *pview;
			SetParallel( false );
			SetMatrix( MT_INSTANCE, GetMatrix( MT_IDENTITY ) );
			min.x = min.y = min.z = -refSz;
			max.x = max.y = max.z =  refSz;
			options.left	= true;
			options.right	= true;
			options.top		= false;
			options.bottom	= true;
			options.front	= false;
			options.back	= true;
			options.gridPat	= GP_BLACK;
			options.connectX = options.connectY = options.connectZ = false;
			options.connectPat	= GP_BLACK;
			GetWindowRect( GetDlgItem( hDlg, ACD_XZ ), &box );
			DeltaRect( box, ch, cv );
			sh = fix2x( fixdiv( refSz, Int2Fix( ch ) ) ) * 16;
			sv = fix2x( fixdiv( refSz, Int2Fix( cv ) ) ) * 16;
			ch/= 2;
			cv/= 2;
			p1x1 = CreatePen( PS_SOLID, 1, RGB(0,0,0) );
			p2x2 = CreatePen( PS_SOLID, 2, RGB(0,255,255) );
			p3x3 = CreatePen( PS_SOLID, 3, RGB(0,0,255) );
			hbRed= CreateSolidBrush( RGB( 127, 0, 0 ) );
			GetWindowRect( GetDlgItem( hDlg, ACD_3D ), &box );
			SetCenter( FixRatio(box.right-box.left,2), FixRatio(box.bottom-box.top,2) );
			Point3dToString(&_from,nstr);
			SetDlgItemText( hDlg, ACD_FROM, nstr );
			Point3dToString(&_to,nstr);
			SetDlgItemText( hDlg, ACD_TO, nstr );
			FixedToString(_view,nstr);
			SetDlgItemText( hDlg, ACD_VIEW, nstr );
			FixedToString(_roll,nstr);
			SetDlgItemText( hDlg, ACD_ROLL, nstr );
			return TRUE;

		case WM_COMMAND:

			switch( wParam ) {

				case IDOK:
					*pfrom	= _from;
					*pto	= _to;
					*proll	= _roll;
					*pview	= _view;
				case IDCANCEL:
					SetParallel( bParallel );
					SetCenter( cx, cy );
					SetMatrix( MT_VIEWER,	&vxf );
					SetMatrix( MT_INSTANCE, &ixf );
					SetMatrix( MT_COMBINED, &cxf );
					DeleteObject( p1x1 );
					DeleteObject( p2x2 );
					DeleteObject( p3x3 );
					DeleteObject( hbRed );
					EndDialog( hDlg, wParam==IDOK );
					return TRUE;

				case ACD_FROM:
					GetDlgItemText( hDlg, ACD_FROM, nstr, 256 );
					StringToPoint3d(nstr,&p3d);
					if( Changed3d( &p3d, &_from ) ) {
						_from = p3d;
						InvalidateItemRect( hDlg, ACD_3D );
						InvalidateItemRect( hDlg, ACD_XZ );
						InvalidateItemRect( hDlg, ACD_XY );
						InvalidateItemRect( hDlg, ACD_ZY );
					}
					return TRUE;

				case ACD_TO:
					GetDlgItemText( hDlg, ACD_TO, nstr, 256 );
					StringToPoint3d(nstr,&p3d);
					if( Changed3d( &p3d, &_to ) ) {
						_to = p3d;
						InvalidateItemRect( hDlg, ACD_3D );
						InvalidateItemRect( hDlg, ACD_XZ );
						InvalidateItemRect( hDlg, ACD_XY );
						InvalidateItemRect( hDlg, ACD_ZY );
					}
					return TRUE;

				case ACD_ROLL:
					GetDlgItemText( hDlg, ACD_ROLL, nstr, 256 );
					fxd = FxMod( StringToFixed( nstr ), f_360 );
					if( fxd != _roll ) {
						_roll = fxd;
						InvalidateItemRect( hDlg, ACD_3D );
					}
					return TRUE;

				case ACD_VIEW:
					GetDlgItemText( hDlg, ACD_VIEW, nstr, 256 );
					fxd = FxMod( StringToFixed( nstr ), f_180 );
					if( fxd != _view ) {
						_view = fxd;
						InvalidateItemRect( hDlg, ACD_3D );
					}
					return TRUE;

			}
			break;
	}
	return FALSE;
}
#pragma optimize("",on)

long FAR PASCAL PaneXZ(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return Pane2d( hWnd, message, wParam, lParam, ACD_XZ );
}

long FAR PASCAL PaneXY(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return Pane2d( hWnd, message, wParam, lParam, ACD_XY );
}

long FAR PASCAL PaneZY(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return Pane2d( hWnd, message, wParam, lParam, ACD_ZY );
}

#pragma optimize("",off)
long Pane2d(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam,short which)
{
	PAINTSTRUCT ps;
	HDC 		hDC;
	POINT		m;
	Point		F,T;
	long		fx,fy,fz;
	long		tx,ty,tz;
	char		nstr[257]="";
	HPEN		hpOld;
	short		i = (short)(which-ACD_XZ);
	HWND		hDlg;
	RECT		r;
	Point3d 	*pP3d,p3d;
	static BOOL	active[3] = {FALSE,FALSE,FALSE};

	switch( message ) {

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			active[i] = TRUE;
			break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			active[i] = FALSE;
			break;

		case WM_MOUSEMOVE:
			if( active[i] ) {
				m = MAKEPOINT(lParam);
				if( ! ( wParam & MK_CONTROL ) )
					pP3d = &_from;
				else
					pP3d = &_to;
				p3d = *pP3d;
				switch( which ) {
					case ACD_XZ:	p3d.x = Int2Fix( (m.x-ch)*sh);
									p3d.z = Int2Fix(-(m.y-cv)*sv);
									break;
					case ACD_XY:	p3d.x = Int2Fix( (m.x-ch)*sh);
									p3d.y = Int2Fix(-(m.y-cv)*sv);
									break;
					case ACD_ZY:	p3d.y = Int2Fix(-(m.y-cv)*sv);
									p3d.z = Int2Fix( (m.x-ch)*sh);
									break;
				}
				if( Changed3d( &p3d, pP3d ) ) {
					*pP3d = p3d;
					hDlg = GetParent( hWnd );
					InvalidateItemRect( hDlg, ACD_3D );
					InvalidateItemRect( hDlg, ACD_XZ );
					InvalidateItemRect( hDlg, ACD_XY );
					InvalidateItemRect( hDlg, ACD_ZY );
				}
			}
			break;

		case WM_PAINT:
			hDC = BeginPaint( hWnd, &ps );
			GetClientRect( hWnd, &r );
			FrameRect( hDC, &r, hbRed );
			SetCurrentDC( hDC );
			fx = Fix2Int(_from.x);	fy = Fix2Int(_from.y);	fz = Fix2Int(_from.z);
			tx = Fix2Int(_to.x);	ty = Fix2Int(_to.y);	tz = Fix2Int(_to.z);
			switch( which ) {
				case ACD_XZ:	F.h = (int)fx;	F.v = (int)-fz;
								T.h = (int)tx;	T.v = (int)-tz;
								break;
				case ACD_XY:	F.h = (int)fx;	F.v = (int)-fy;
								T.h = (int)tx;	T.v = (int)-ty;
								break;
				case ACD_ZY:	F.h = (int)fz;	F.v = (int)-fy;
								T.h = (int)tz;	T.v = (int)-ty;
								break;
			}
			F.h=(int)(F.h/sh);	F.v=(int)(F.v/sv);
			T.h=(int)(T.h/sh);	T.v=(int)(T.v/sv);
			F.h+=ch;	F.v+=+cv;
			T.h+=ch;	T.v+=+cv;
			hpOld = SelectObject( hDC, p3x3 );
			MoveTo( hDC, F.h, F.v );
			LineTo( hDC, F.h, F.v );
			SelectObject( hDC, p1x1 );
			LineTo( hDC, T.h, T.v );
			SelectObject( hDC, p2x2 );
			LineTo( hDC, T.h, T.v );
			SelectObject( hDC, hpOld );
			EndPaint( hWnd, &ps );

			hDlg = GetParent( hWnd );
			Point3dToString( &_from, nstr );
			SetDlgItemText( hDlg, ACD_FROM, nstr );
			Point3dToString( &_to, nstr );
			SetDlgItemText( hDlg, ACD_TO, nstr );

			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
    }
	return NULL;
}
#pragma optimize("",on)

long FAR PASCAL Pane3d(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC 		hDC;
	RECT		r;
	int 		oldBM;
	DWORD		oldTC;
	WORD		oldTA;

	switch( message ) {

		case WM_PAINT:
			hDC = BeginPaint( hWnd, &ps );
			GetClientRect( hWnd, &r );
			FrameRect( hDC, &r, hbRed );
			SetCurrentDC( hDC );
			AimCamera(&_from,&_to,_view,_roll);
			CombineReferenceFrames();
			xfGrid( &min, &max, &steps, &options, GetMatrix(MT_VIEWER) );
			oldTC = SetTextColor( hDC, RGB(127,127,255) );
			oldBM = SetBkMode( hDC, TRANSPARENT );
			oldTA = (WORD)SetTextAlign( hDC, TA_CENTER );
			DrawString3d( max.x, f_0, f_0, "+X" );
			DrawString3d( f_0, maªªªªªªª888ÿ                                           ÿÿ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ªªªªªªªªªªªªªªªªªªÿÿ                                             ÿÿ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ªªªªªªªªªªªªªªªªªªÿÿ    