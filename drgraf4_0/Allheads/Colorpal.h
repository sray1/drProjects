// CColorPal.h : header file
//
#ifndef _COLORPAL_H_
#define _COLORPAL_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CColorPal
/////////////////////////////////////////////////////////////////////////////
class CColorPal : public CPalette
{
// Construction
public:  
	CColorPal();
	DECLARE_DYNAMIC(CColorPal)
protected: 
public:
// Implementation
public:
 
    ///////////////////////////////////////////////////// 
	virtual void 		RGB2HSV(pRGBCOLOR rgb,pHSVCOLOR hsv);
	virtual void 		HSV2RGB(pHSVCOLOR hsv,pRGBCOLOR rgb);
	virtual int 		Make256ColorPal(CColorPal* pColorPal);
	virtual int 		MakeNewPal
						(
							CColorPal* pColorPal,
							double	baseHue,	// if nHues == 1 indicates hue to use
							int		nHues,		// number of color wheel subdivisions
							int		nHueLevels,	// number of variations per hue
							int		nGrays		// number of gray levels to emit
						);
	virtual int 		LoadStockPal(CColorPal* pColorPal,LPSTR lpszName);
	virtual CColorPal*	SelectPal(CClientDC* pDC, CColorPal* pPal);
	virtual void 		DisposePal(CColorPal* pPal);
/////////////////////////////////////////////////// todo
//typedef BYTE __far *LPMPINST;
//typedef BYTE __huge *HPPIX24;
//typedef COLORREF __huge *HPPIX32;
//BOOL		AccretePalette(void);
//BOOL 		AccretingPalette(void);
//BOOL 		SetAccretePalette(BOOL state);
//void 		_cdecl AccretePaletteEntry(COLORREF c);
//HPALETTE	GetAccretedPalette(void);
////////////////////////////////////////////////////

protected:

//	void	FrequencySort(pACRPALENTRYs pAPEs,long n);



protected:

	 

public:
	virtual ~CColorPal(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CColorPal)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

