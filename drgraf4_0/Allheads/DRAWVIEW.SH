// Drawview.h : interface of the CDrawView class
//
#ifndef _DRAWVIEW_H_ 
#define _DRAWVIEW_H_ 


// This class implements the behavior of a scrolling view that presents
// multiple Drawing Objects. 
// a Draw view has all of the benefits of a view (as well as scroll view),
// including perhaps most importantly printing and print preview.

#include "ViewInfo.h"
#include "DrObject.h"
#include "DListMgr.h"
//#include "3d.h"
//#include "camera.h"
//#include "3dcolor.h"		// lighting
//#include "CLUTS.H"		// Color palette support
#include "globals.h"        // OpMode 
/////////////////////////////////////////////////////////////////////////////
class CDrawView : public CScrollView
{
protected: // create from serialization only
	CDrawView();
	DECLARE_DYNAMIC(CDrawView)

// Operations
public:


// Attributes
protected:
	int m_nPrevSelectedObjIndex;  // index of the most recently selected Object
//	int m_nPrevRowCount;        // most recent row count, before update
//	int m_nRowsPerPrintedPage;  // how many rows fit on a printed page

// Operations
public:

	virtual void OnInitialUpdate();
	virtual void UpdateObject(int nInvalidObject,int nObjType,	// called by
										int nViewNumber);   	// derived class's 
														   		// OnUpdate		
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	////////////////////////////////////////

// Overridables
public:

	virtual int	 GetActiveObjectIndex() = 0;
	virtual int  GetObjectCount() = 0;
	virtual void OnDrawObject(CDC* pDC, int nRow, int y, BOOL bSelected) = 0;
	virtual void ChangeSelectionNextObjectIndex(BOOL bNext) = 0;
	virtual void ChangeSelectionToObjectIndex(int nObjectIndex) = 0;

// Implementation
public:
	// standard overrides of MFC classes

	virtual void 	OnDraw(CDC* pDC);  // overridden to draw this view
	/////////////////////////////////////////////
	virtual void	GetScalevv3DToLP(double* sU,double* sV)
					{
						*sU = m_dScale_U;
						*sV = m_dScale_U;
					};	
	virtual void	SetScalevv3DToLP()
					{
						m_dScale_U = (double)m_sizeDoc.cx * m_dZoomFac_U;  
						m_dScale_V = (double)m_sizeDoc.cy * m_dZoomFac_V;
					};	  
	virtual void 	Init3DWindow();
	virtual void 	UpdateViewMatrix();
	virtual void 	UpdateCombinedMatrix();
	virtual void 	UpdateWin3DtoViewPort3DMatrix();
//	virtual void 	Corner_3Dto2D(CDrObject* pObject,int nObjectType);
	virtual void 	Transform(WORLD ptIn, pWORLD pptOut);
	virtual void 	Project(WORLD ptIn,pWORLD pptOut);

protected:

//	virtual BOOL 	OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void 	OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void 	OnPrint(CDC* pDC, CPrintInfo* pInfo);

//	virtual void 	UpdateScrollSizes();
	virtual	BOOL 	PreCreateWindow(CREATESTRUCT& cs);
    ////////////////////////////////////////////////// SCENE
	virtual	void 	GetObjectReadyforRender
						(CDC* pDC,CDrObject* pObject,int nObjType);
	virtual	void	GoRender(CDC* pDC,CRect RectClip
								,int nActiveObjIndex);
			///////////////////////////	



public:
	
	virtual ~CDrawView(); 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CViewInfo*	m_pViewInfoDlg;
	/////////////////////////////////////////// ViewNumber
    int 		m_nView;
	CString		m_ClassName;
	int 		m_nMapMode; 
	CSize		m_sizeDoc;
	CSize		m_sizePage;
	CSize		m_sizeLine;
	//////////////////////////////////////////////// Document Size
    CSize		m_sizeView;		// View Size (LOG)
	WORLD		m_CW;			// ViewPort 3D center 
	double		m_Width_U,      // View Width  (LOG/SCALED)
				m_Width_V,      // View Height (LOG/SCALED)
				m_dZoomFac_U,	// zoom factor horizontal
				m_dZoomFac_V;	// zoom factor vertical
	double 		m_dScale_U;		// vv3DToLP:U-direction  
	double 		m_dScale_V;     // vv3DToLP:V-direction
	/////////////////////////////////////////////////// 3D drawing
	LPOINT3		m_penLoc;			// location of the drawing pen

	MATRIX		m_IdentityM;	// identity transform MATRIX
	MATRIX		m_LocalM;		// instancing transform MATRIX
	MATRIX		m_ViewM;		// viewers transform MATRIX
	MATRIX		m_ComposedM;	// viewer & instance combined MATRIX 
	MATRIX		m_vv3DM;		// Window to 3D Viewport MATRIX
    //////////////////////////////
	BOOL		m_bParallel;	// if true disables perspective projection
	BOOL		m_bCulling3D;	// if true BackFaceCulling in WorldSpace
	BOOL		m_bCulling2D;	// if true BackFaceCulling in Screen3DSpace
    //////////////////////////////
//	int			m_subdiv;		// MATRIX patch subdivisions
    ////////////////////////////////////////////////////////
	RENDITION	m_Rendition;    // Method of Rendition
/*	
		WIRE_0,
		WIRE_1,
		PAINTER,
		LITFLAT,
		ZBUFFERED
*/
	BOOL		m_bWire_0;		// Use wireframe drawing?
	BOOL		m_bWire_1;		// Use wireframe drawing?
	BOOL		m_bZBuffer;		// Use ZBuffered rendering?
	BOOL		m_bFlatshade;	// Flat or Phong where applicable.
	BOOL   		m_bOffScreen;	// Draw offscreen?
	BOOL   		m_bAntialias;	// Antialias during ZBuffered rendering?
	BOOL    	m_bShadows;		// Cast shadows during ZBuffered rendering?
	/////////////////// View Orientation Parameters /////////////
	WORLD		m_VRP;			// View Reference Point
	WORLD		m_VPN;			// View Plane Normal
	WORLD	  	m_VUP;			// View Up Vector
	WORLD		m_VDir;			// View Direction
	/////////////////// View Mapping Parameters /////////////
	WORLD	  	m_PRP;			// View Reference Point
	double		m_Umin,         // View Plane Window 
	      		m_Umax,
	      		m_Vmin,
	      		m_Vmax;
		  		
	double		m_dFront,		// near clipping plane
				m_dBack,		// far clipping plane 
				m_dzMin;		// near clipping plane for Perspective

	WORLD		m_VPmin,		// 3D ViewPort Min 0<=VPxmin etc <=1
	     		m_VPmax;		// 3D ViewPort Max
	///////////////////////////////////////////////////
//	pLighting	m_pL;			// lighting information
//	HPALETTE	m_hCLUT;		// Color palette handle

	OPMODE		m_OpMode;		// Operation Mode

	LPOINT3		m_Right,
				m_Up,
				m_View,
				m_Current;
	////////////////////////////// NoShow Controls			
	BOOL		m_NS_CNLabel;	
	BOOL		m_NS_CNode;	
	BOOL		m_NS_NLabel;	
	BOOL		m_NS_Node;	
	BOOL		m_NS_CShape;
	/////////////////////////////////////////////////////////////////////////

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void On3dAmbientlight();
	afx_msg void OnUpdate3dAmbientlight(CCmdUI* pCmdUI);
	afx_msg void On3dEyeposition();
	afx_msg void OnUpdate3dEyeposition(CCmdUI* pCmdUI);
	afx_msg void On3dFlatshading();
	afx_msg void OnUpdate3dFlatshading(CCmdUI* pCmdUI);
	afx_msg void On3dLightsource();
	afx_msg void OnUpdate3dLightsource(CCmdUI* pCmdUI);
	afx_msg void On3dProjectionParallel();
	afx_msg void OnUpdate3dProjectionParallel(CCmdUI* pCmdUI);
	afx_msg void On3dProjectionPerspective();
	afx_msg void OnUpdate3dProjectionPerspective(CCmdUI* pCmdUI);
	afx_msg void On3dRendering();
	afx_msg void OnUpdate3dRendering(CCmdUI* pCmdUI);
	afx_msg void On3dWireframed();
	afx_msg void OnUpdate3dWireframed(CCmdUI* pCmdUI);
	afx_msg void On3dZbuffered();
	afx_msg void OnUpdate3dZbuffered(CCmdUI* pCmdUI);
	afx_msg void OnOptionAxison();
	afx_msg void OnUpdateOptionAxison(CCmdUI* pCmdUI);
	afx_msg void OnOptionCursor();
	afx_msg void OnUpdateOptionCursor(CCmdUI* pCmdUI);
	afx_msg void OnOptionPenchange();
	afx_msg void OnUpdateOptionPenchange(CCmdUI* pCmdUI);
	afx_msg void OnOptionRefresh();
	afx_msg void OnUpdateOptionRefresh(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNoShowCNLabel();
	afx_msg void OnUpdateNoShowCNLabel(CCmdUI* pCmdUI);
	afx_msg void OnNoShowCNodes();
	afx_msg void OnUpdateNoShowCNodes(CCmdUI* pCmdUI);
	afx_msg void OnNoShowNLabel();
	afx_msg void OnUpdateNoShowNLabel(CCmdUI* pCmdUI);
	afx_msg void OnNoShowNodes();
	afx_msg void OnUpdateNoShowNodes(CCmdUI* pCmdUI);
	afx_msg void OnNoShowCShape();
	afx_msg void OnUpdateNoShowCShape(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg long OnGoodByeEyePos(UINT wParam, long lParam);
	afx_msg long OnUpdateEyePos(UINT wParam, long lParam);
	DECLARE_MESSAGE_MAP()
};
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
/////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////
/*
#include <3d.h>
#include <camera.h>

class CDemoView : public CView
{
public:
	virtual void SetCamera		(void);
	virtual void SetCamera		(pPoint3d from,pPoint3d to,
								 Fixed Lens=Lens50mm,Fixed Roll=f_0);
	virtual void SetCamera		(Fixed Fx,Fixed Fy,Fixed Fz,
								 Fixed Tx=f_0,Fixed Ty=f_0,Fixed Tz=f_0,
								 Fixed Lens=Lens50mm,Fixed Roll=f_0);
	virtual void ShowPosition(CDC *pDC);
	virtual void DrawBackground	(CDC *pDC);
	virtual void RenderCollection(CDC *pDC);
	virtual void DrawForeground	(CDC *pDC);
*/

