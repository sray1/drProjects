// CMDIB.h
// Definition file for CMDIB class.

// This class exists only because there was no DIB class in Microsoft's
// initial version of 32-bit Visual C++. Consequently, this quick and
// dirty DIB class was created. It is mostly based on source code that you
// can find in the DIBLOOK application in your MSVCP\MFC\SAMPLES 
// directory. I didn't bother to pretty it up much because I created 
// the class with the expectation that Microsoft would soon help us all out
// by putting a properly designed DIB class in a new version of the MFC 
// library. If that has happened by the time you read this, great. Use
// the real DIB class, not this one. Meanwhile, the stuff in this class
// works well enough to support my demo programs. For any other purpose,
// use this code at your own risk.
//                                     -- Mark Andrews

#ifndef _INC_CMDIB
#define _INC_CMDIB

// DIB constants
#define PALVERSION   0x300

// DIB Macros
#define IS_WIN30_DIB(lpbi) ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect) ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect) ((lpRect)->bottom - (lpRect)->top)
#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')
#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

// Declare handle to a DIB.
DECLARE_HANDLE(HDIB);

class CMDIB : public CObject
{
public:
	HDIB 		m_hDIB;
private:
	CPalette*	m_pPalette;
	HPALETTE 	m_hPalette;
	HPALETTE 	m_hOldPal;
	HPALETTE 	m_hPal;           // This DIB's palette
	UINT 		m_cScanLines;
	void*		m_lpBits;
//	LPSTR *m_lpBits;
	BITMAPINFO*	m_lpBitsInfo;
//	LPBITMAPINFO *m_lpBitsInfo;
	DWORD 		m_DIBWidth;
	DWORD 		m_DIBHeight;
	
public: 

	CMDIB() {}
	~CMDIB() {}

	// Inline member functions.
	UINT 		GetNrScanLines() { return m_cScanLines; }
	void* 		GetPVBits() { return m_lpBits; }
	BITMAPINFO* GetBitsInfo() { return  m_lpBitsInfo; }
	DWORD 		GetDIBWidth() { return m_DIBWidth; }
	DWORD 		GetDIBHeight() { return m_DIBHeight; }

	// Non-inline member functions.
	BOOL		SetDIBInfo();
	BOOL 		GetDIBInfo(UINT *pScanLines, void *lpBits, 
					BITMAPINFO* lpBitsInfo, DWORD *pWidth,DWORD *pHeight);
	BOOL 		PaintDIB (HDC hDC, LPRECT lpDCRect, HDIB hDIB, LPRECT lpDIBRect,
									 CPalette* pPal,DWORD copyMode);
	BOOL 		CreateDIBPalette(HDIB hDIB, CPalette* cPal);
	LPSTR 		FindDIBBits (LPSTR lpbi);
	DWORD 		DIBWidth (LPSTR lpDIB);
	DWORD 		DIBHeight (LPSTR lpDIB);
	WORD 		PaletteSize (LPSTR lpbi);
	WORD 		DIBNumColors (LPSTR lpbi);
	HDIB 		ReadDIBFile(CFile& file);
};

#endif // _INC_CMDIB
