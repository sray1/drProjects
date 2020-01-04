//  CMDIB.cpp
//	Implementation file for CMDIB class.


#include "stdafx.h"
#include "mdib.h"
#include <io.h>
#include <errno.h>

BOOL CMDIB::SetDIBInfo()
{
	if (m_hDIB == NULL)
		return FALSE;
	LPSTR lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	LPSTR lpDIBBits;           // Pointer to DIB bits

	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	lpDIBBits = FindDIBBits(lpDIBHdr);

	m_cScanLines = (UINT)DIBHeight(lpDIBHdr);  // Nr of scan lines.
	m_lpBits = lpDIBBits;                  // Bit array address.
	m_lpBitsInfo = (LPBITMAPINFO)lpDIBHdr; // BITMAPINFO struct address.
	m_DIBWidth = DIBWidth(lpDIBHdr);
	m_DIBHeight = DIBHeight(lpDIBHdr);

   ::GlobalUnlock((HGLOBAL) m_hDIB);

	return TRUE;
}

BOOL CMDIB::GetDIBInfo(UINT *pScanLines, void *lpBits, 
	BITMAPINFO* lpBitsInfo, DWORD *pWidth, 
	DWORD *pHeight)
{
	pScanLines = &m_cScanLines;  // Nr of scan lines.
	lpBits = m_lpBits;                  
	lpBitsInfo = m_lpBitsInfo;    
	pWidth = &m_DIBWidth;
	pHeight = &m_DIBHeight;

   return TRUE;
}

// DIBWidth member function; works with Windows 3.x DIBs and other
// non-NT DIBs.

DWORD CMDIB::DIBWidth(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	// Get a pointer to the header.
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// Return the DIB width if it is a Win 3.0 DIB.
	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biWidth;
	else  // If we're here, it's an other-style DIB, 
		  // so return its width.
		return (DWORD)lpbmc->bcWidth;
}


// DIBHeight member function; works with Windows 3.x DIBs and other
// non-NT DIBs.

DWORD CMDIB::DIBHeight(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	// Get a pointer to the header.
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// Return the DIB width if it's a Win 3.0 DIB.
	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biHeight;
	else  // If we're here, it's an other-style DIB, 
		  // so return its width.
		return (DWORD)lpbmc->bcHeight;
}

// CreateDIBPalette member function.
BOOL CMDIB::CreateDIBPalette(HDIB hDIB, CPalette* pPal)
{
	LPLOGPALETTE lpPal;      // pointer to a logical palette
	HANDLE hLogPal;          // handle to a logical palette
	HPALETTE hPal = NULL;    // handle to a palette
	int i;                   // loop index
	WORD wNumColors;         // number of colors in color table
	LPSTR lpbi;              // pointer to packed-DIB
	LPBITMAPINFO lpbmi;      // pointer to BITMAPINFO structure (Win3.0)
	LPBITMAPCOREINFO lpbmc;  // pointer to BITMAPCOREINFO structure (old)
	BOOL bWinStyleDIB;       // flag which signifies whether this is a Win3.0 DIB
	BOOL bResult = FALSE;

	// If handle to DIB is invalid, return FALSE.

	if (hDIB == NULL)
	  return FALSE;

   lpbi = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

   // Get a pointer to BITMAPINFO (Win 3.0)
   lpbmi = (LPBITMAPINFO)lpbi;

   // Get a pointer to BITMAPCOREINFO (old 1.x)
   lpbmc = (LPBITMAPCOREINFO)lpbi;

   // Get the number of colors in the DIB.
   wNumColors = DIBNumColors(lpbi);

   if (wNumColors != 0)
   {
		// Allocate a memory block for a logical palette.
		hLogPal = ::GlobalAlloc(GHND, sizeof(LOGPALETTE)
									+ sizeof(PALETTEENTRY)
									* wNumColors);

		// If there isn't enough memory, clean up and return NULL.
		if (hLogPal == 0)
		{
			::GlobalUnlock((HGLOBAL) hDIB);
			return FALSE;
		}

		lpPal = (LPLOGPALETTE) ::GlobalLock((HGLOBAL) hLogPal);

		// Set version number and number of palette entries.
		lpPal->palVersion = PALVERSION;
		lpPal->palNumEntries = (WORD)wNumColors;

		// Win 3.0 DIB?
		bWinStyleDIB = IS_WIN30_DIB(lpbi);
		for (i = 0; i < (int)wNumColors; i++)
		{
			if (bWinStyleDIB)
			{
				lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
				lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
				lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
				lpPal->palPalEntry[i].peFlags = 0;
			}
			else
			{
				lpPal->palPalEntry[i].peRed = lpbmc->bmciColors[i].rgbtRed;
				lpPal->palPalEntry[i].peGreen = lpbmc->bmciColors[i].rgbtGreen;
				lpPal->palPalEntry[i].peBlue = lpbmc->bmciColors[i].rgbtBlue;
				lpPal->palPalEntry[i].peFlags = 0;
			}
		}

		// Create the palette and get handle to it.
		bResult = pPal->CreatePalette(lpPal);
		::GlobalUnlock((HGLOBAL) hLogPal);
		::GlobalFree((HGLOBAL) hLogPal);
	}

	::GlobalUnlock((HGLOBAL) hDIB);

	return bResult;
}

// FindDIBBits member function.

LPSTR CMDIB::FindDIBBits(LPSTR lpbi)
{
	return (lpbi + *(LPDWORD)lpbi + PaletteSize(lpbi));
}


// PaletteSize member function.
WORD CMDIB::PaletteSize(LPSTR lpbi)
{
   if (IS_WIN30_DIB (lpbi))
	  return (WORD)(DIBNumColors(lpbi) * sizeof(RGBQUAD));
   else
	  return (WORD)(DIBNumColors(lpbi) * sizeof(RGBTRIPLE));
}

// DIBNumColors member function.

WORD CMDIB::DIBNumColors(LPSTR lpbi)
{
	WORD wBitCount;  // DIB bit count

	if (IS_WIN30_DIB(lpbi))
	{
		DWORD dwClrUsed;

		dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;
		if (dwClrUsed != 0)
			return (WORD)dwClrUsed;
	}

	if (IS_WIN30_DIB(lpbi))
		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
	else
		wBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;

	switch (wBitCount)
	{
		case 1:
			return 2;

		case 4:
			return 16;

		case 8:
			return 256;

		default:
			return 0;
	}
}

/*************************************************************************
 *
 * PaintDIB()
 *
 * Parameters:
 *
 * HDC hDC          - DC to do output to
 *
 * LPRECT lpDCRect  - rectangle on DC to do output to
 *
 * HDIB hDIB        - handle to global memory with a DIB spec
 *                    in it followed by the DIB bits
 *
 * LPRECT lpDIBRect - rectangle of DIB to output into lpDCRect
 *
 * CPalette* pPal   - pointer to CPalette containing DIB's palette
 *
 * Return Value:
 *
 * BOOL             - TRUE if DIB was drawn, FALSE otherwise
 *
 * Description:
 *   Painting routine for a DIB.  Calls StretchDIBits() or
 *   SetDIBitsToDevice() to paint the DIB.  The DIB is
 *   output to the specified DC, at the coordinates given
 *   in lpDCRect.  The area of the DIB to be output is
 *   given by lpDIBRect.
 *
 ************************************************************************/

BOOL CMDIB::PaintDIB (HDC hDC, LPRECT lpDCRect, HDIB hDIB, LPRECT lpDIBRect,
									 CPalette* pPal,DWORD copyMode)
{
	///////////////////////////////////////////////////////////////
	LPSTR    lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	LPSTR    lpDIBBits;           // Pointer to DIB bits
	BOOL     bSuccess=FALSE;      // Success/fail flag
	HPALETTE hPal=NULL;           // Our DIB's palette
	HPALETTE hOldPal=NULL;        // Previous palette
    /////////////////////////////////////////////////////////////// For fast Impression
    HDC hdcMem;
    hdcMem = CreateCompatibleDC(hDC);
    HBITMAP hbmpOld,hbmpNew;
    hbmpNew = CreateCompatibleBitmap(hDC,RECTWIDTH(lpDCRect),RECTHEIGHT(lpDCRect));
    hbmpOld = (HBITMAP)SelectObject(hdcMem,hbmpNew);
	HPALETTE hOldPalMem=NULL;        // Previous palette
    ////////////////////////////////////////////////////////////////
	/* Check for valid DIB handle */
	if (hDIB == NULL)
		return FALSE;

	/* Lock down the DIB, and get a pointer to the beginning of the bit
	 *  buffer
	 */
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	lpDIBBits = FindDIBBits (lpDIBHdr);

	// Get the DIB's palette, then select it into DC
	if (pPal != NULL)
	{
		hPal = (HPALETTE) pPal->m_hObject;

		// Select as background since we have
		// already realized in forground if needed
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
		hOldPalMem = ::SelectPalette(hdcMem, hPal, TRUE);
	}
    ////////////////////////////////////////////////////////////////////////////////
	/* Make sure to use the stretching mode best for color pictures */
	::SetStretchBltMode(hDC, COLORONCOLOR);

	/* Determine whether to call StretchDIBits() or SetDIBitsToDevice() */
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) &&
	   (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
		bSuccess = ::SetDIBitsToDevice(hDC,                    // hDC
								   lpDCRect->left,             // DestX
								   lpDCRect->top,              // DestY
								   RECTWIDTH(lpDCRect),        // nDestWidth
								   RECTHEIGHT(lpDCRect),       // nDestHeight
								   lpDIBRect->left,            // SrcX
								   (int)DIBHeight(lpDIBHdr) -
									  lpDIBRect->top -
									  RECTHEIGHT(lpDIBRect),   // SrcY
								   0,                          // nStartScan
								   (WORD)DIBHeight(lpDIBHdr),  // nNumScans
								   lpDIBBits,                  // lpBits
								   (LPBITMAPINFO)lpDIBHdr,     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
   else 
   {
	  bSuccess = ::StretchDIBits(hdcMem,                       // hDC Memory
							   0,                 // DestX
							   0,                  // DestY
							   RECTWIDTH(lpDCRect),            // nDestWidth
							   RECTHEIGHT(lpDCRect),           // nDestHeight
							   lpDIBRect->left,                // SrcX
							   lpDIBRect->top,                 // SrcY
							   RECTWIDTH(lpDIBRect),           // wSrcWidth
							   RECTHEIGHT(lpDIBRect),          // wSrcHeight
							   lpDIBBits,                      // lpBits
							   (LPBITMAPINFO)lpDIBHdr,         // lpBitsInfo
							   DIB_RGB_COLORS,                 // wUsage
							   SRCCOPY);                       // dwROP 
							   
	  bSuccess = ::BitBlt	(  hDC,		                       // hDC 
							   lpDCRect->left,                 // DestX
							   lpDCRect->top,                  // DestY
							   RECTWIDTH(lpDCRect),            // nDestWidth
							   RECTHEIGHT(lpDCRect),           // nDestHeight
							   hdcMem,						   // hdcMem	
							   0,                			   // SrcX
							   0, 			                   // SrcY
							   SRCCOPY);                       // dwROP 
							   
	}
    ::GlobalUnlock((HGLOBAL) hDIB);

	/* Reselect old palette */
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
		::SelectPalette(hdcMem, hOldPalMem, TRUE);
	}

   	SelectObject(hdcMem,hbmpOld);
   	DeleteDC(hdcMem);
   	DeleteObject(hbmpNew);
   return bSuccess;
}

// ReadDIBFile member function.
HDIB CMDIB::ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR pDIB;

	dwBitsSize = file.GetLength();

	if ((file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) !=
		sizeof(bmfHeader)) || (bmfHeader.bfType != DIB_HEADER_MARKER))
	{
		return NULL;
	}

	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	if (file.ReadHuge(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) !=
		dwBitsSize - sizeof(BITMAPFILEHEADER) )
	{
		::GlobalUnlock((HGLOBAL) hDIB);
		::GlobalFree((HGLOBAL) hDIB);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL) hDIB);
	return hDIB;
}

