// CRender.h : header file
//
#ifndef _RENDER_H_
#define _RENDER_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "ZBuffer.h"
#include "Textures.h"
#include "Light.h"

#include "DListMgr.h"

#include "DrObject.h"
#include "Def_Rend.h"
#include "Def_Type.h"
#include "DrawView.h"
///////////////////////////////////////////////////////// ScanInfo
typedef	struct edgeinfo {
	WORLD		N,	// normal vector
				P,	// viewer transformed point
				R;	// raw (instanced only) point
}
	EDGEINFO, *pEDGEINFO;

typedef struct scanspan				// Polygon assumed CONVEX
{									// : 1 span/scanline
	short		x[2];				// horizontal screen coordinates
	double		z[2];				// depth screen3D coordinates
	EDGEINFO	e[2];
}
	SCANSPAN, *pSCANSPAN;
///////////////////////////////
typedef struct box 
{
	WORLD	min,max;
}
	BOX, *pBOX;
/////////////////////////////////////////////////////////////////////////////
// CRender
/////////////////////////////////////////////////////////////////////////////
class CRender : public CObject
{
// Construction
public:  
	CRender();
	DECLARE_SERIAL(CRender)
protected: 
public:
// Implementation
public:

	virtual CDListMgr*	GetPolyList(){return m_pPolyList;};
	///////////////////////////////////////////////////////
	virtual RGBCOLOR 	Opaqueness
						(
						pRGBCOLOR	bg,	// background color
						pRGBCOLOR	fg,	// foreground color
						double		coef// transmission coefficient					
						);
	virtual RGBCOLOR 	Transparency
						(
						pRGBCOLOR	bg,	// background color
						pRGBCOLOR	fg,	// foreground color
						double		coef// transmission coefficient					
						);
	///////////////////////////////////////////////////					
	virtual int 		Init(CRect* pClientRect, pLTENVIRON pLE);
	virtual int 		InitScan(int yMax);
	virtual void 		TermRender(void);
	virtual void 		SetShadow(BOOL state);
	virtual BOOL 		IsShadowOn(void);
	virtual void 		SetAntiAlias(Boolean state);
	virtual BOOL 		IsAntiAliasingOn(void);
	virtual void 		AddToPolyList(CDrObject* pObject);
	virtual void 		DisposePolyList(void);
	virtual void 		RenderPolyList(BOOL bEdgesOnly);
	virtual int 		RenderPolygon_FULL(CClientDC* pDC,CDrObject* pPoly,BOOL bEdgesOnly);
	virtual BOOL 		RenderScanLines(CClientDC* pDC);
	virtual void 		RenderSpan_FULL
							(
								CClientDC*	pDC,	
								int			y,	//	current scan line (vertical coordinate)
								pSCANSPAN	pss	//	current scanline span data
							);
	virtual void 		RenderPixel_FULL
							(
								CClientDC* pDC,
								int x,int y,
								WORLD N,
								WORLD P,
								WORLD R,BOOL bEdgePixel
							);
	virtual BOOL 		DoAntiAliasing();
	virtual RGBCOLOR 	EvaluateColor_FULL
							(
								int x,int y,
								WORLD N,
								WORLD P,
								WORLD R,BOOL bEdgePixel
							);
	virtual RGBCOLOR 	EvaluateColor_LF
							(
								WORLD		Centroid,	//	centroid of region
								WORLD		N,			//	normal at centroid
								double		d			//	distance from viewer
							);
	virtual void 		BuildEdgeList
							(CDrObject* pPoly,BOOL bNeedRaw);
	virtual void 		AddToEdgeList
							(
								CDrObject*	pPoly,
								CDrObject*	pNodeA,
								CDrObject*	pNodeB,
								BOOL		bNeedRaw
							);
	virtual Boolean		AdjacentPoly
							(CDrObject* pPolyA, CDrObject* pPolyB);
	virtual void 		AddToEdgeList_LF
							(
								CDrObject*	pPoly,
								CDrObject*	pNodeA,
								CDrObject*	pNodeB,
								BOOL		bNeedRaw
							);
	virtual Boolean 	InShadow
							(
								pWORLD		P,
								double		ld,
								pLTSOURCE	pLS,
								double		*transmission
							);
	virtual void 		DepthSort
							(
								CDListMgr* pSortList, 
								BOOL bAscending
							);
	virtual void 		RenderPolyline_Z
							(
								CClientDC* pDC,	
								short nS,LPPOINT S,
								pWORLD P,COLORREF C   
							);
	virtual void 		RenderLine_Z
							(
								CClientDC* pDC,	
								POINT S0,POINT S1,
								pWORLD P0,pWORLD P1,
								COLORREF C
							);
	virtual void 		RenderPixel_Z
							(
								CClientDC* pDC, 
								int x, int y, double z,
								COLORREF C
							);
	virtual void 		LightUpScanSpan
							(
								CClientDC* pDC, 
								int xs, int xe, int y
							);
	virtual COLORREF	LightUpPixel
							(
								CClientDC* pDC, 
								int x, int y, COLORREF c
							);
	virtual void 		GetCPixel
							( 
								CClientDC* pDC, 
								int x, int y, pRGBCOLOR pRGB
							);
	virtual void 		SetCPixel
							( 
								CClientDC* pDC, 
								int x, int y, pRGBCOLOR pRGB
							);
    /////////////////////////////////////////////////////
	virtual BOOL 		ClippedByZBuffer
							(/*CClientDC* pDC,*/CDrObject* pPoly);


protected:


	CDrawView*  m_pView;
	/////////////////////////
	RENDITION	m_Rendition;	//Rendering Method
	BOOL		m_bParallel;
	BOOL		m_bCullWorld;
	BOOL		m_bShadowOn;
	BOOL		m_bAntiAliasOn;
    BOOL		m_bNeedSort;	// for depthsort
    BOOL		m_bAscending;	// for depthsort
	double		m_dHither;		//Canonical View Volume
	double		m_dYon;
	/////////////////////////
	CTextures	m_Textures;

    CZBuffer*	m_pZB;
    pSCANSPAN	m_pScanSpan;	// for Full Rendition
	pRENDINFO	m_pRA;
	pLTENVIRON	m_pLE;
	/////////////////////////
	CDListMgr*	m_pPolyList;	// active ones for Shadow


protected: 

public:
	virtual ~CRender(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CRender)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
