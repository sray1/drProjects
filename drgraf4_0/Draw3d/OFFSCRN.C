#include <WIN_TRIM.H>
#include <OffScrn.h>
#include "DIDC.H"

HPALETTE API3D OffscreenBuffer(enum OS_ACTION action,DWORD arg)
{
	static int		is24=FALSE;
	static HDC		hDC	=NULL,
					hDCm=NULL;
	static HBITMAP	hBM	=NULL,hBMold;
	static HBRUSH	hb	=NULL;			// Background brush
	static HPEN		hp	=NULL,hpOld;	// Foreground pen
	static RECT		r;

	switch( action ) {
		case OS_INIT24:
			if( !arg )
				return (HPALETTE)NULL;
			GetClientRect( (HWND)(WORD)arg, &r );
			if( !DIDC_Init( &r, GetCurrentDC() ) )
				return (HPALETTE)NULL;
			is24 = TRUE;
			break;
		case OS_INIT:
			if( !arg )
				return (HPALETTE)NULL;
			GetClientRect( (HWND)(WORD)arg, &r );
			if( !(hDC = GetCurrentDC()) )
				return (HPALETTE)NULL;
			if( hDCm )
				DeleteDC( hDCm );
			if( !(hDCm = CreateCompatibleDC( hDC )) )
				return (HPALETTE)NULL;
			if( hBM )
				DeleteObject( hBM );
			if( !(hBM = CreateCompatibleBitmap( hDC, r.right, r.bottom )) ) {
				DeleteDC( hDCm );
				return (HPALETTE)NULL;
			}
			hBMold = SelectObject( hDCm, hBM );
			is24 = FALSE;
			break;
		case OS_USE:
			if( is24 )
				break;
			if( hDCm )
				SetCurrentDC( hDCm );
			break;
		case OS_ERASE:
			if( is24 )
				DIDC_Erase( arg );
			else {
				if( hb )
					DeleteObject( hb );
				hb	= CreateSolidBrush( arg );
				if( hDCm && hb )
					FillRect( hDCm, &r, hb );	// erase the bitmap
			}
			break;
		case OS_PEN:
			if( hDCm ) {
				if( hp )
					DeleteObject( hp );
				hp	= CreatePen(
						(int)((arg&0xF0000000)>>28),
						(int)((arg&0x0F000000)>>24),
						RGB( GetRValue(arg),GetGValue(arg),GetBValue(arg) )
						);
				if( hp )
					hpOld = SelectObject( hDCm, hp );	// set the offscreen pen
			}
			break;
		case OS_DRAW:
			if( is24 )
				return DIDC_Blt( GetCurrentDC(), (int)arg );
			else
			if( hDC && hDCm )
				StretchBlt( hDC, 0, 0, r.right, r.bottom, hDCm, 0, 0, r.right, r.bottom, arg );
			break;
		case OS_DISPOSE:
			if( is24 )
				DIDC_Dispose();
			if( hDC )
				SetCurrentDC( hDC );
			if( hb )
				DeleteObject( hb );
			if( hp ) {
				SelectObject( hDCm, hpOld );
				DeleteObject( hp );
			}
			if( hBM ) {
				SelectObject( hDCm, hBMold );
				DeleteObject( hBM );
			}
			if( hDCm )
				DeleteDC( hDCm );
			hDC	= NULL;
			hDCm= NULL;
			hBM = NULL;
			hb	= NULL;
			hp	= NULL;
			is24= FALSE;
			break;
	}
	return (HPALETTE)NULL;
}

