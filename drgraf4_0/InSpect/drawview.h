// Drawview.h : interface of the CDrawView class
//
#ifndef _DRAWVIEW_H_ 
#define _DRAWVIEW_H_ 


// This class implements the behavior of a scrolling view that presents
// multiple Drawing Objects. 
// a Draw view has all of the benefits of a view (as well as scroll view),
// including perhaps most importantly printing and print preview.

#include "AxisDraw.h"
#include "ViewInfo.h"
#include "DrObject.h"
#include "DListMgr.h"
#include "Def_Type.h"         
#include "Def_View.h"        // OpMode 
#include "Def_Mous.h"        // Generation:Forward(Design)/Reverse(Interpolate) 
#include "Def_Rend.h"
/////////////////////         
#include "DVM_Genr.h"
#include "DVM_CreO.h"
#include "DVM_Edit.h"
#include "DVM_Del.h"
#include "DVM_Post.h"
#include "DVM_CreM.h"
#include "DVM_Mdit.h"
#include "Def_NoSoLim.h"	// array bounds for NoShow
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
	int m_nPrevSelectedObjType;  // Type of the most recently selected Object
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
	/////////////////////////////////////////////////////////////////////
	virtual	void 	GetObjectReadyforRender
							(CDC* pDC,CDrObject* pObject,int nObjType);
	virtual void 	UpdateViewMatrix();
	virtual void 	UpdatePerToParMatrix();
	virtual void 	UpdateCombinedMatrix();
	virtual void 	UpdateWin3DtoViewPort3DMatrix();
	virtual void 	UpdatePenultimateMatrix();
	virtual void 	UpdateUltimateMatrix();
//	virtual void 	Corner_3Dto2D(CDrObject* pObject,int nObjectType);
	virtual void 	Transform(pWORLD pptIn,pWORLD pptOut);
	virtual void 	Project(pWORLD pptIn,pWORLD pptOut,BOOL bSize);
	/////////////////////////////////////////////////////////////////////
    virtual int 	GetViewNum(){return m_nView;};
	virtual int 	GetViewMapMode(){return m_nMapMode;};
	///////////////////////////////////////////////// 
	virtual CSize	GetDocSize(){return	m_sizeDoc;};
//	virtual CSize		m_sizePage;
//	virtual CSize		m_sizeLine;
	virtual CSize	GetFOV(){return	m_FOV;};			// Field Of View; 
	virtual void	SetFOV(CSize FOV)
					{
						m_FOV = FOV;
					};			// Field Of View; 
    virtual CSize	GetViewSize(){return m_sizeView;};	// View Size (LOG)
	virtual void	SetViewSize(CSize FOV)
					{
						m_sizeView = FOV;
					};			// Field Of View; 
	virtual WORLD	GetCW(){return m_CW;};			// ViewPort 3D center 
	virtual void	SetCW(WORLD CW)
					{
						m_CW = CW;
					};			// ViewPort 3D center 
	virtual void	GetCWDim(double* pWidth_U,double* pWidth_V)
					{
						*pWidth_U = m_Width_U;
						*pWidth_V = m_Width_V;
					};	
	virtual void	SetCWDim(double Width_U,double Width_V)
					{
						m_Width_U = Width_U;
						m_Width_V = Width_V;
					};	
	virtual void	GetZoomFac(double* pWidth_U,double* pWidth_V)
					{
						*pWidth_U = m_dZoomFac_U;
						*pWidth_V = m_dZoomFac_V;
					};	
	virtual void	SetZoomFac(double Width_U,double Width_V)
					{
						m_dZoomFac_U = Width_U;
						m_dZoomFac_V = Width_V;
					};	
	virtual void	GetViewScale(double* pWidth_U,double* pWidth_V)
					{
						*pWidth_U = m_dScale_U;
						*pWidth_V = m_dScale_V;
					};	
	virtual void	SetViewScale(double Width_U,double Width_V)
					{
						m_dScale_U = Width_U;
						m_dScale_V = Width_V;
					};	
	//////////////////////////////////////////
//	LPOINT3		GetPenLoc(){return m_penLoc;};			// location of the drawing pen

	virtual pMATRIX	GetMatrix(MATRICES mType);
	virtual void	SetMatrix(MATRICES mType,pMATRIX pMat);
	//////////////////////////////////////////
	virtual BOOL	IsShrinkOn(){return m_bShrinkOn;};
	virtual void	SetShrinkOn(BOOL d3)
					{
						m_bShrinkOn = d3;
					};	
	virtual double	GetShrink(){return m_dShrink;};
	virtual void	SetShrink(double d){m_dShrink = d;};
	//////////////////////////////////////////
	virtual BOOL	IsParallel(){return m_bParallel;};
	virtual void	SetParallel(BOOL d3)
					{
						m_bParallel = d3;
					};	
	virtual BOOL	IsCulling3D(){return m_bCulling3D;};
	virtual void	SetCulling3D(BOOL d3)
					{
						m_bCulling3D = d3;
					};// if true BackFaceCulling in WorldSpace
	virtual BOOL	IsCulling2D(){return m_bCulling2D;};	// if true BackFaceCulling in WorldSpace
	virtual void	SetCulling2D(BOOL d3)
					{
						m_bCulling2D = d3;
					};// if true BackFaceCulling in Screen3DSpace
	/////////////////// View Orientation Parameters /////////////
	virtual WORLD	GetVRP(){return m_VRP;};	// View Reference Point
	virtual void	SetVRP(WORLD w){m_VRP = w;};
	virtual WORLD	GetVPN(){return m_VPN;};	// View Plane Normal
	virtual void	SetVPN(WORLD w){m_VPN = w;};
	virtual WORLD	GetVUP(){return m_VUP;};	// View Up Vector
	virtual void	SetVUP(WORLD w){m_VUP = w;};
	virtual WORLD	GetVDir(){return m_VDir;};	// View Direction
	virtual void	SetVDir(WORLD w){m_VDir = w;};
	/////////////////// View Mapping Parameters /////////////
	virtual WORLD	GetPRP(){return m_PRP;};	// Proj Reference Point
	virtual void	SetPRP(WORLD w){m_PRP = w;};
	virtual double	GetUmin(){return m_Umin;};	
	virtual void	SetUmin(double w){m_Umin = w;};
	virtual double	GetUmax(){return m_Umax;};	
	virtual void	SetUmax(double w){m_Umax = w;};
	virtual double	GeVmin(){return m_Vmin;};	
	virtual void	SetVmin(double w){m_Vmin = w;};
	virtual double	GetVmax(){return m_Vmax;};	
	virtual void	SetVmax(double w){m_Vmax = w;};

	virtual double	GetFront(){return m_dFront;};	
	virtual void	SetFront(double w){m_dFront = w;};
	virtual double	GetBack(){return m_dBack;};	
	virtual void	SetBack(double w){m_dBack = w;};
	virtual double	GetzMin(){return m_dzMin;};	
	virtual void	SetzMin(double w){m_dzMin = w;};
		  		
	virtual WORLD	GetVPmin(){return m_VPmin;};	// Proj Reference Point
	virtual void	SetVPmin(WORLD w){m_VPmin = w;};
	virtual WORLD	GetVPmax(){return m_VPmax;};	// Proj Reference Point
	virtual void	SetVPmax(WORLD w){m_VPmax = w;};
	//////////////////////////////////////////
	virtual void	GetScalevv3DToLP(double* sU,double* sV)
					{
						*sU = m_dScale_U;
						*sV = m_dScale_U;
					};	
	virtual void	SetScalevv3DToLP();
    //////////////////////////////////////////
	virtual OPMODE	GetOpMode(){return m_OpMode;};			// Operation Mode
	virtual void	SetOpMode(OPMODE om){m_OpMode = om;};	
	virtual RENDITION
					GetRnMode(){return m_Rendition;};			// Rendition Mode
	virtual void	SetRnMode(RENDITION rm){m_Rendition = rm;};	
	virtual BOOL	IsRendChanged(){return m_bRendChanged;};
	virtual void	SetRendChanged(BOOL RC)
					{
						m_bRendChanged = RC;
					};
	virtual void	SetSceneChangedOnNoShow();
	//////////////////////////////////////////////////////////
	virtual GENERATE	GetGenMode(){return m_GenMode;};			// Generation Mode


	
protected:

			void	ShowScreenGrid(CDC* pDC);
			////////////////////////////////////////////	Mouse:CREATE
			void	MouseMove(UINT nFlags, CPoint point);
			void	LButtonDown(UINT nFlags, CPoint point);
			void	LButtonUp(UINT nFlags, CPoint point);
			void	RButtonDown(UINT nFlags, CPoint point);
			void	RButtonUp(UINT nFlags, CPoint point);
			/////////////////
//	virtual BOOL 	OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void 	OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void 	OnPrint(CDC* pDC, CPrintInfo* pInfo);

//	virtual void 	UpdateScrollSizes();
	virtual	BOOL 	PreCreateWindow(CREATESTRUCT& cs);
    ////////////////////////////////////////////////// SCENE
	virtual	void		GoRender(CDC* pDC,CRect RectClip,int nActiveObjType,
														int nActiveObjIndex);
			void		UpdateAllOtherMatButLocal();
			void		MouseActivateViewMatUpdate();
			///////////////////////////	
			void		ShowCurrentOptions(CDC* pDC);
			void		GoDoAxis(CDC* pDC);
			void		GoDoViewControls(CDC* pDC);
			void		GoDoPoint(CDC* PtrDC,POINT* pt,CString& text);
			void 		GoDoLine(CDC* PtrDC,POINT* pt1,POINT* pt2);
			void 		GoDoHouse(CDC* pDC);
			void 		Pack_NSBools(BOOL bNS[]);
			/////////////////////////////////////
			CDListMgr*	GetList(UINT nType);
			void		ShowCountBox(LPCTSTR string,int nCount);
			void		ShowAxes();



public:
	
	virtual ~CDrawView(); 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	///////////////////////
	CDVM_Genr	m_DVM_Genr;
	CDVM_CreO	m_DVM_CreO;
	CDVM_Edit	m_DVM_Edit;
	CDVM_Del	m_DVM_Del;
	CDVM_Post	m_DVM_Post;
	CDVM_CreM	m_DVM_CreM;
	CDVM_Mdit	m_DVM_Mdit;
	/////////////////////////////////////////// ViewMode
	BOOL		m_bViewGene;
	BOOL		m_bViewMesh;
	/////////////////////////////////////////// Mouse Handler
	BOOL		m_bShrinkOn;
	double		m_dShrink;
	/////////////////////////////////////////// Camera Change
	BOOL		m_bCameraChanged;
	/////////////////////////////////////////// Rendition Change
	BOOL		m_bRendChanged;
	///////////////////////////////////////////
	CAxisDraw	m_wndAxisDraw;
	CViewInfo*	m_pViewInfoDlg;
	/////////////////////////////////////////// ViewNumber
    int 		m_nView;
	CString		m_ClassName;
	int 		m_nMapMode; 
	//////////////////////////////////////////////// Document Size
	CSize		m_sizeDoc;
	CSize		m_sizePage;
	CSize		m_sizeLine;
	CSize		m_FOV;			// Field Of View;
    CSize		m_sizeView;		// View Size (LOG)
	double		m_Width_U,      // View Width  (LOG/SCALED)
				m_Width_V,      // View Height (LOG/SCALED)
				m_dZoomFac_U,	// zoom factor horizontal
				m_dZoomFac_V;	// zoom factor vertical
	double 		m_dScale_U;		// vv3DToLP:U-direction  
	double 		m_dScale_V;     // vv3DToLP:V-direction
	/////////////////////////////////////////////////// 3D drawing
	CDListMgr	m_SortList;		// Polygon Depth Sort List 
	///////////////////////////////////////////////////////////////////////////////////
	LPOINT3		m_penLoc;		// location of the drawing pen

	MATRIX		m_IdentityM;	// identity transform MATRIX
	MATRIX		m_LocalM;		// instancing transform MATRIX
	MATRIX		m_ViewM;		// viewers transform MATRIX
	MATRIX		m_PerToParM;	// Pers to Par MATRIX, if Clipping in 3D
	MATRIX		m_ComposedM;	// viewer & instance combined MATRIX 
	MATRIX		m_vv3DM;		// Window to 3D Viewport MATRIX
	////////////////////
	MATRIX		m_PenultiM;		// instancing to 3DViewport MATRIX
	MATRIX		m_UltimateM;	// instancing to 2DViewport MATRIX(includes Projection)
    ///////////////////////////////////////////////////////////////////////////////////
	BOOL		m_bParallel;	// if true disables perspective projection
	BOOL		m_bCulling3D;	// if true BackFaceCulling in WorldSpace
	BOOL		m_bCulling2D;	// if true BackFaceCulling in Screen3DSpace
    //////////////////////////////
//	int			m_subdiv;		// MATRIX patch subdivisions
    ////////////////////////////////////////////////////////
	RENDITION	m_Rendition;    // Method of Rendition
	BOOL		m_bWF_PURE;		// Use wireframe drawing?
	BOOL		m_bWF_CULL;		// Use wireframe drawing?
	BOOL		m_bWF_HIDDEN;	// Use wireframe drawing?
	BOOL		m_bFS_PAINTER;	// Flat DEPTHSORT where applicable.
	BOOL		m_bFS_ZBUFFER;	// Flat ZBUFFER where applicable.
	BOOL		m_bZB_GOURAUD;	// Use ZBuffered rendering?
	BOOL		m_bZB_PHONG;	// Use ZBuffered rendering?
	BOOL   		m_bOffScreen;	// Draw offscreen?
	BOOL   		m_bAntialias;	// Antialias during ZBuffered rendering?
	BOOL    	m_bShadows;		// Cast shadows during ZBuffered rendering?
	/////////////////// View Orientation Parameters ///////////////////////////////////
	//		VRP,VPN and VUP makes up VIEW ORIENTATION MATRIX
	//			which Xforms WORLD Coord Sys(WRC) -> View Reference Coord(VRC)
	//			i.e., it takes (u,v,n) into (x,y,z)
	//		Umin,Umax,Vmin,Vmax,F and B along with Xmin,Xmax,Ymin,Ymax,Zmin,ZMax
	//			which makes up VIEW MAPPING MATRIX
	//			i.e., XForms points in VRC to points in Normalized Proj. Coord (NPC)
	/////////////////// View Plane ////////////////////////////////////////////////////
	//	VRP, VPN & VUP specified in Right Handed World Coordinate System
	WORLD		m_VRP;			// View Reference Point( Defining View Plane)
								//	Origin of 3DView-Reference-Coord(VRC)(Right Handed)
	WORLD		m_VPN;			// View Plane Normal( Defining View Plane)
								//	One Axis of VRC ( n Axis)
	WORLD	  	m_VUP;			// View Up Vector
								//	2nd Axis of VRC ( v Axis)
	/////////////////// View Window ///////////////////////////////////////////////////
	WORLD		m_CW;			// ViewWindow 3D center 
	double		m_Umin,         // View Plane Window 
	      		m_Umax,
	      		m_Vmin,
	      		m_Vmax;
	WORLD		m_VDir;			// View Direction
	/////////////////// View Projection /////////////
	//	PRP, VPN & VUP specified in VRC System
	WORLD	  	m_PRP;			// View Reference Point
								//	Specified in VRC System		  		
	/////////////////// View Volume /////////////
	double		m_dFront,		// near clipping plane(hither) algebraically > m_dBack
				m_dBack,		// far clipping plane 
				m_dzMin;		// near clipping plane for Perspective

	WORLD		m_VPmin,		// 3D ViewPort Min 0<=VPxmin etc <=1
	     		m_VPmax;		// 3D ViewPort Max
	///////////////////////////////////////////////////
//	pLighting	m_pL;			// lighting information
//	HPALETTE	m_hCLUT;		// Color palette handle

	OPMODE		m_OpMode;		// Operation Mode
	GENERATE	m_GenMode;		// Generation Mode
	

	WORLD		m_Right,
				m_Up,
				m_View,
				m_Current;
	////////////////////////////// NoShow Controls
	BOOL		m_bNoSoEL[MAX_NOSOEL];
	BOOL		m_bNoSoLabEL[MAX_NOSOLABEL];
	///////////////////////
	BOOL		m_bNS[MAX_NOSOTOTAL];
	////////////////////////////// StaticLoad
	BOOL		m_bNS_Force;		//0	
	BOOL		m_bNS_Displace;		//1
	BOOL		m_bNS_Pressure;		//2
	BOOL		m_bNS_Thermal;		//3
	BOOL		m_bNS_LumpWt;		//4
	BOOL		m_bNS_LabStatic[MAX_NOSOLABSTATIC];
	/////////////////////////// Support
	BOOL		m_bNS_RIGID;		//0
	BOOL		m_bNS_Lin_Spring;	//1 
	BOOL		m_bNS_Lin_Snubber;	//2 
	BOOL		m_bNS_Non_Spring;	//3 
	BOOL		m_bNS_Non_Snubber;	//4 
	BOOL		m_bNS_LabSupp[MAX_NOSOLABSUPPORT];
	/////////////////////////// Dirty	
	BOOL		m_bNS_D_Curve;		//0
	BOOL		m_bNS_D_Profile_C;	//1
	BOOL		m_bNS_D_Patch;		//2	
	BOOL		m_bNS_D_Profile_P;	//3
	BOOL		m_bNS_D_Solid;		//4	
	BOOL		m_bNS_D_Profile_S;	//5
	BOOL		m_bNS_D_Object;		//6			
	BOOL		m_bNS_LabDirty[MAX_NOSOLABDIRTY];
	/////////////////////////// Posted	
	BOOL		m_bNS_P_Curve;		//0
	BOOL		m_bNS_P_Profile_C;	//1
	BOOL		m_bNS_P_Patch;		//2	
	BOOL		m_bNS_P_Profile_P;	//3
	BOOL		m_bNS_P_Solid;		//4	
	BOOL		m_bNS_P_Profile_S;	//5
	BOOL		m_bNS_P_Object;		//6			
	BOOL		m_bNS_LabPosted[MAX_NOSOLABPOSTED];
	/////////////////////////// Misc	
	BOOL		m_bNS_2DLabel;	
	BOOL		m_bNS_3DLabel;	
	BOOL		m_bNS_CNLabel;	
	BOOL		m_bNS_CNode;	
	BOOL		m_bNS_NLabel;	
	BOOL		m_bNS_Node;	
	BOOL		m_bNS_MNLabel;	
	BOOL		m_bNS_MNode;	
	//////
	BOOL		m_bNS_CShape;
	
	BOOL		m_bNS_Normal;
	BOOL		m_bNS_Centroid;
	/////////////////////////// View Controls	
	BOOL		m_bNS_CVV;
	BOOL		m_bNS_VV;
	BOOL		m_bNS_VRP;
	BOOL		m_bNS_PRP;
	BOOL		m_bNS_VUP;
	BOOL		m_bNS_VPN;
	BOOL		m_bNS_CW;
	BOOL		m_bNS_VPlane;
	BOOL		m_bNS_VDIR;
	BOOL		m_bNS_WC;
	BOOL		m_bNS_VRC;
	BOOL		m_bNS_NPC;
	BOOL		m_bNS_Front;
	BOOL		m_bNS_Back;
	/////////////////////////////////////////////////////////////////////////

// Generated message map functions
public:
	//{{AFX_MSG(CDrawView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void On3dAmbientlight();
	afx_msg void OnUpdate3dAmbientlight(CCmdUI* pCmdUI);
	afx_msg void On3dEyeposition();
	afx_msg void OnUpdate3dEyeposition(CCmdUI* pCmdUI);
	afx_msg void On3dLightsource();
	afx_msg void OnUpdate3dLightsource(CCmdUI* pCmdUI);
	afx_msg void On3dProjectionParallel();
	afx_msg void OnUpdate3dProjectionParallel(CCmdUI* pCmdUI);
	afx_msg void On3dProjectionPerspective();
	afx_msg void OnUpdate3dProjectionPerspective(CCmdUI* pCmdUI);
	afx_msg void On3dRendering();
	afx_msg void OnUpdate3dRendering(CCmdUI* pCmdUI);
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
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void On3dFsPainter();
	afx_msg void OnUpdate3dFsPainter(CCmdUI* pCmdUI);
	afx_msg void On3dFsZbuffer();
	afx_msg void OnUpdate3dFsZbuffer(CCmdUI* pCmdUI);
	afx_msg void On3dWfHidden();
	afx_msg void OnUpdate3dWfHidden(CCmdUI* pCmdUI);
	afx_msg void On3dWfPure();
	afx_msg void OnUpdate3dWfPure(CCmdUI* pCmdUI);
	afx_msg void On3dZbGouraud();
	afx_msg void OnUpdate3dZbGouraud(CCmdUI* pCmdUI);
	afx_msg void On3dZbPhong();
	afx_msg void OnUpdate3dZbPhong(CCmdUI* pCmdUI);
	afx_msg void OnNoshowCentroid();
	afx_msg void OnUpdateNoshowCentroid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDCurve();
	afx_msg void OnUpdateNoshowDCurve(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDObject();
	afx_msg void OnUpdateNoshowDObject(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDPatch();
	afx_msg void OnUpdateNoshowDPatch(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDSolid();
	afx_msg void OnUpdateNoshowDSolid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDProfile_C();
	afx_msg void OnUpdateNoshowDProfile_C(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDProfile_P();
	afx_msg void OnUpdateNoshowDProfile_P(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDProfile_S();
	afx_msg void OnUpdateNoshowDProfile_S(CCmdUI* pCmdUI);
	afx_msg void OnNoshowNormals();
	afx_msg void OnUpdateNoshowNormals(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPCurve();
	afx_msg void OnUpdateNoshowPCurve(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPObject();
	afx_msg void OnUpdateNoshowPObject(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPPatch();
	afx_msg void OnUpdateNoshowPPatch(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPSolid();
	afx_msg void OnUpdateNoshowPSolid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPProfile_C();
	afx_msg void OnUpdateNoshowPProfile_C(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPProfile_P();
	afx_msg void OnUpdateNoshowPProfile_P(CCmdUI* pCmdUI);
	afx_msg void OnNoshowPProfile_S();
	afx_msg void OnUpdateNoshowPProfile_S(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcBcp();
	afx_msg void OnUpdateNoshowVcBcp(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcCvv();
	afx_msg void OnUpdateNoshowVcCvv(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcFcp();
	afx_msg void OnUpdateNoshowVcFcp(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcPlane();
	afx_msg void OnUpdateNoshowVcPlane(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcPrp();
	afx_msg void OnUpdateNoshowVcPrp(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVcs();
	afx_msg void OnUpdateNoshowVcVcs(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVdir();
	afx_msg void OnUpdateNoshowVcVdir(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVpn();
	afx_msg void OnUpdateNoshowVcVpn(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVrp();
	afx_msg void OnUpdateNoshowVcVrp(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVup();
	afx_msg void OnUpdateNoshowVcVup(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcVv();
	afx_msg void OnUpdateNoshowVcVv(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcWc();
	afx_msg void OnUpdateNoshowVcWc(CCmdUI* pCmdUI);
	afx_msg void OnNoshowVcWcs();
	afx_msg void OnUpdateNoshowVcWcs(CCmdUI* pCmdUI);
	afx_msg void OnModeDesign();
	afx_msg void OnUpdateModeDesign(CCmdUI* pCmdUI);
	afx_msg void OnModeInterpolate();
	afx_msg void OnUpdateModeInterpolate(CCmdUI* pCmdUI);
	afx_msg void OnSummaryCurveDirty();
	afx_msg void OnSummaryCurvePosted();
	afx_msg void OnSummaryElements();
	afx_msg void OnSummaryNodeAlltypes();
	afx_msg void OnSummaryNodeControl();
	afx_msg void OnSummaryNodeMesh();
	afx_msg void OnSummaryObject();
	afx_msg void OnSummaryPatchDirty();
	afx_msg void OnSummaryPatchPosted();
	afx_msg void OnSummarySolidDirty();
	afx_msg void OnSummarySolidPosted();
	afx_msg void On3dShrinkOn();
	afx_msg void OnUpdate3dShrinkOn(CCmdUI* pCmdUI);
	afx_msg void On3dCulling3D();
	afx_msg void OnUpdate3dCulling3D(CCmdUI* pCmdUI);
	afx_msg void OnNoshowLinearsupportRigid();
	afx_msg void OnUpdateNoshowLinearsupportRigid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowLinearsupportSnubber();
	afx_msg void OnUpdateNoshowLinearsupportSnubber(CCmdUI* pCmdUI);
	afx_msg void OnNoshowLinearsupportSpring();
	afx_msg void OnUpdateNoshowLinearsupportSpring(CCmdUI* pCmdUI);
	afx_msg void OnSummaryLinearsupportRigid();
	afx_msg void OnSummaryLinearsupportSnubber();
	afx_msg void OnSummaryLinearsupportSpring();
	afx_msg void OnNoshowMnlabel();
	afx_msg void OnUpdateNoshowMnlabel(CCmdUI* pCmdUI);
	afx_msg void OnNoshowMnodes();
	afx_msg void OnUpdateNoshowMnodes(CCmdUI* pCmdUI);
	afx_msg void OnNoshowStaticForce();
	afx_msg void OnUpdateNoshowStaticForce(CCmdUI* pCmdUI);
	afx_msg void OnNoshowStaticDisplace();
	afx_msg void OnUpdateNoshowStaticDisplace(CCmdUI* pCmdUI);
	afx_msg void OnNoshowStaticPressure();
	afx_msg void OnUpdateNoshowStaticPressure(CCmdUI* pCmdUI);
	afx_msg void OnNoshowStaticThermal();
	afx_msg void OnUpdateNoshowStaticThermal(CCmdUI* pCmdUI);
	afx_msg void OnNoshowStaticLumpWt();
	afx_msg void OnUpdateNoshowStaticLumpWt(CCmdUI* pCmdUI);
	afx_msg void OnSummaryStaticForce();
	afx_msg void OnSummaryStaticDisplace();
	afx_msg void OnSummaryStaticPressure();
	afx_msg void OnSummaryStaticThermal();
	afx_msg void OnSummaryStaticLumpWt();
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	afx_msg void OnViewModeGenerator();
	afx_msg void OnUpdateViewModeGenerator(CCmdUI* pCmdUI);
	afx_msg void OnViewModeMesh();
	afx_msg void OnUpdateViewModeMesh(CCmdUI* pCmdUI);
	afx_msg void OnNoshowElements();
	afx_msg void OnUpdateNoshowElements(CCmdUI* pCmdUI);
	afx_msg void OnNoshowLabelElements();
	afx_msg void OnNoshowlabelsDCurve();
	afx_msg void OnUpdateNoshowlabelsDCurve(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsDObject();
	afx_msg void OnUpdateNoshowlabelsDObject(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsDPatch();
	afx_msg void OnUpdateNoshowlabelsDPatch(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsDProfileS();
	afx_msg void OnUpdateNoshowlabelsDProfileS(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsDSolid();
	afx_msg void OnUpdateNoshowlabelsDSolid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsLinearsupportRigid();
	afx_msg void OnUpdateNoshowlabelsLinearsupportRigid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsLinearsupportSpring();
	afx_msg void OnUpdateNoshowlabelsLinearsupportSpring(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsPCurve();
	afx_msg void OnUpdateNoshowlabelsPCurve(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsPObject();
	afx_msg void OnUpdateNoshowlabelsPObject(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsPPatch();
	afx_msg void OnUpdateNoshowlabelsPPatch(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsPSolid();
	afx_msg void OnUpdateNoshowlabelsPSolid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsStaticDisplace();
	afx_msg void OnUpdateNoshowlabelsStaticDisplace(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsStaticForce();
	afx_msg void OnUpdateNoshowlabelsStaticForce(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsStaticGravity();
	afx_msg void OnUpdateNoshowlabelsStaticGravity(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsStaticLumpwt();
	afx_msg void OnUpdateNoshowlabelsStaticLumpwt(CCmdUI* pCmdUI);
	afx_msg void OnNoshowlabelsStaticThermal();
	afx_msg void OnUpdateNoshowlabelsStaticThermal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg long OnGoodByeEyePos(UINT wParam, long lParam);
	afx_msg long OnUpdateEyePos(UINT wParam, long lParam);
	DECLARE_MESSAGE_MAP()
};
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

#endif
/////////////////////////////////////////////////////////////////////////////
