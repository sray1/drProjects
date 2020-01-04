/****************************************************************************
 *	File:		LOADBMPF.c
 *
 *	Purpose:	Load Windows BitMap Files.
 *
 *	Version:	Microsoft C 6/7 / Windows 3.1 / STRICT
 *
 *	Copyright:	(C) 1991 Mark M. Owen -- All Rights Reserved.
 *
 ****************************************************************************
 */
#include <WIN_TRIM.H>
#include <LOADBMPF.h>

#define ANERROR -1L

typedef struct {
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
}
	BMPFILEHEADER;

static WORD	NumberOfDIBColors(LPBITMAPINFOHEADER pbmih);

static WORD	NumberOfDIBColors(LPBITMAPINFOHEADER pbmih)
{
	if( !pbmih->biClrUsed )
		switch( pbmih->biBitCount ) {
			case  1:	return (WORD)2;
			case  4:	return (WORD)16;
			case  8:	return (WORD)256;
			case 16:
			case 24:	return (WORD)pbmih->biClrUsed;
		}
	return (WORD)pbmih->biClrUsed;
}


#define	TEMPALLOC(s,p) {\
	HANDLE h = GlobalAlloc( GMEM_MOVEABLE, (s) );\
	if( h!=NULL )\
		(p) = GlobalLock( h );\
}
#define TEMPFREE(p){\
	HANDLE	h = (HANDLE)LOWORD( GlobalHandle( (UINT)HIWORD((p)) ) );\
	GlobalUnlock( h );\
	GlobalFree( h );\
}

#include <malloc.h>
HBITMAP API3D LoadBMPFile(HDC hDC,LPSTR fileName)
{
	long			size;
	BMPFILEHEADER	bfh;
	LPBITMAPINFO	pbmi;
	HBITMAP			hbm;
	PMBLK			ppix;
	OFSTRUCT		ofsBmpFile;
	HFILE			fh = OpenFile(fileName, &ofsBmpFile, OF_READ);
	int				nc;

	if( ANERROR == fh )
		return NULL;
	if( ANERROR == _hread(fh, (PMBLK)&bfh, sizeof(BMPFILEHEADER) ) ) {
		_lclose( fh );
		return NULL;
	}
    
    nc = NumberOfDIBColors( &bfh.bmih );
	size = nc * sizeof(RGBQUAD);
	pbmi = (LPBITMAPINFO)NewPtr(sizeof(BITMAPINFOHEADER)+size);
	if( pbmi == NULL ) {
		_lclose( fh );
		return NULL;
	}
    BlockMove( (PMBLK)&bfh.bmih, (PMBLK)pbmi, sizeof(BITMAPINFOHEADER) );

	if( ANERROR == _hread(fh, (PMBLK)pbmi->bmiColors, size)
	||	ANERROR == _llseek(fh, bfh.bmfh.bfOffBits, 0)		) {
		DisposPtr( (Ptr)pbmi );
		_lclose( fh );
		return NULL;
	}
	size = bfh.bmfh.bfSize - (size + sizeof(BMPFILEHEADER));
	ppix = (PMBLK)NewPtr( size );
	if( ppix!=NULL )
		_hread( fh, ppix, size );
	_lclose( fh );

	if(	(bfh.bmih.biCompression == BI_RLE8) | (bfh.bmih.biCompression == BI_RLE4) ) {
		DisposPtr( (Ptr)pbmi );
		return NULL;	// decompression is NOT yet supported.
	}
	if( nc == 256 ) {
		HPALETTE		hPal,hOldPal;
		LPLOGPALETTE	ppal = (LPLOGPALETTE)_fmalloc( sizeof(LOGPALETTE) + nc*sizeof(PALETTEENTRY) );
		if( ppal != NULL ) {
			LPPALETTEENTRY	ppe	= ppal->palPalEntry;
			RGBQUAD			*prgb = pbmi->bmiColors+nc;			
			ppal->palVersion	= 0x300;
			ppal->palNumEntries	= nc;
			while( nc-- ) {
				ppe->peRed  = prgb->rgbRed;
				ppe->peGreen= prgb->rgbGreen;
				ppe->peBlue = prgb->rgbBlue;
				ppe->peFlags= NULL;
				prgb--;
				ppe++;
			}
			hPal = CreatePalette( ppal );
			_ffree( ppal );
			if( hPal != NULL ) {
				UnrealizeObject( hPal );
				hOldPal = SelectPalette( hDC, hPal, FALSE );
				RealizePalette( hDC );
			}
		}
		hbm = CreateDIBitmap( hDC, &bfh.bmih, CBM_INIT, ppix, pbmi, DIB_RGB_COLORS );
		if( ppal != NULL ) {
			if( hOldPal ) {
				SelectPalette( hDC, hOldPal, FALSE );
				DeleteObject( hPal );
			}
		}	
    }
    else {
		hbm = CreateDIBitmap( hDC, &bfh.bmih, CBM_INIT, ppix, pbmi, DIB_RGB_COLORS );
    }
	DisposPtr( (Ptr)pbmi );
	return hbm;
}

void	API3D WriteBMPFile(HDC hDC,HBITMAP hBM,LPSTR fileName)
{
	long				size;
	HFILE				fh;
	OFSTRUCT			ofsBmpFile;
	BITMAPFILEHEADER	bmfh = {0,0L,0,0,0L};
	BITMAPINFOHEADER	bmih = {sizeof(BITMAPINFOHEADER),0L,0L,1,0,(DWORD)BI_RGB,0L,0L,0L,0L,0L};
	BITMAP				bm;
	LPBITMAPINFO		pbmi;
	PMBLK				pbits;
	DWORD				adjustment;

	GetObject( hBM, sizeof(BITMAP), (LPSTR)&bm );

	bmih.biWidth	= bm.bmWidth;
	bmih.biHeight	= bm.bmHeight;
	bmih.biBitCount = (WORD)((bm.bmBitsPixel<16)?bm.bmBitsPixel:24);
	adjustment = (bmih.biWidth*bmih.biBitCount) % 32;
	if( adjustment ) // not aligned to 32 bits so...
		adjustment = 32 - adjustment;

	bmih.biSizeImage= ((bmih.biWidth+adjustment)*bmih.biHeight*bmih.biBitCount)/8L;
	bmih.biClrUsed	= NumberOfDIBColors( &bmih );

	size = bmih.biSize + bmih.biClrUsed * sizeof(RGBQUAD);

	bmfh.bfType		= ('B' + ('M' << 8));
	bmfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + size;
	bmfh.bfSize		= bmfh.bfOffBits + bmih.biSizeImage;

	TEMPALLOC( size+sizeof(RGBQUAD)*256, pbmi );
	if( pbmi == NULL )
		return;

	BlockMove( (Ptr)&bmih, (Ptr)pbmi, bmih.biSize );

	TEMPALLOC( bmih.biSizeImage, pbits );
	if( pbits == NULL ) {
		TEMPFREE( pbmi );
		return;
	}

	GetDIBits( hDC, hBM, 0, bm.bmHeight, NULL, pbmi, DIB_RGB_COLORS );
	GetDIBits( hDC, hBM, 0, bm.bmHeight, pbits, pbmi, DIB_RGB_COLORS );

	fh = OpenFile((LPCSTR)fileName, &ofsBmpFile, OF_CREATE|OF_WRITE);
	if( ANERROR != fh ) {
		if( ANERROR != _hwrite( fh, (PMBLK)&bmfh, sizeof(BITMAPFILEHEADER) ) )
			if( ANERROR != _hwrite( fh, (PMBLK)pbmi, size ) )
				_hwrite( fh, (PMBLK)pbits, bmih.biSizeImage );
		_lclose( fh );
    }
	TEMPFREE( pbits );
	TEMPFREE( pbmi );
}

void	API3D WindowShotPal(HWND hWnd,LPSTR fileName,HPALETTE hPal)
{
	HDC			hDC	 = GetDC( hWnd );
	HDC			hDCm = CreateCompatibleDC( hDC );
	RECT		r;
	HBITMAP		hBM,oldBM;
	HPALETTE	hPalOld = NULL;

	GetClientRect( hWnd, &r );
	hBM	 = CreateCompatibleBitmap( hDC, r.right, r.bottom );
	oldBM = SelectObject( hDCm, hBM );
	if( hPal != NULL )
		hPalOld = SelectPalette( hDCm, hPal, FALSE );
	StretchBlt( hDCm, 0, 0, r.right, r.bottom, hDC, 0, 0, r.right, r.bottom, SRCCOPY );
	WriteBMPFile( hDCm, hBM, fileName );
	if( hPalOld != NULL )
		SelectPalette( hDCm, hPalOld, FALSE );
	SelectObject( hDCm, oldBM );
	DeleteObject( hBM );
	ReleaseDC( hWnd, hDC );
	DeleteDC( hDCm );
}

void	API3D ScreenShotPal(LPSTR fileName,HPALETTE hPal)
{
	WindowShotPal( GetDesktopWindow(), fileName, hPal );
}

void	API3D WindowShot(HWND hWnd,LPSTR fileName)
{
	WindowShotPal( hWnd, fileName, NULL );
}

void	API3D ScreenShot(LPSTR fileName)
{
	ScreenShotPal( fileName, NULL );
}

