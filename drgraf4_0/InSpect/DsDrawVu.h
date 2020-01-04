// Drawview.h : interface of the CDsDrawVu class
//
#ifndef _DSDRAWVIEW_H_ 
#define _DSDRAWVIEW_H_ 


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
/////////////////////         
#include "DVM_Genr.h"
#include "DVM_Edit.h"
#include "DVM_Del.h"
/////////////////////
#define	MAX_NOSOLABEL	100
#define	MAX_NOSOEL		100
/////////////////////////////////////////////////////////////////////////////
class CDsDrawVu : public CView
{
protected: // create from serialization only
	CDsDrawVu();

	DECLARE_DYNAMIC(CDsDrawVu)


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
	virtual void	GetScalevv3DToLP(double* sU,double* sV)
					{
						*sU = m_dScale_U;
						*sV = m_dScale_U;
					};	
	virtual void	SetScalevv3DToLP();
    //////////////////////////////////////////
	virtual OPMODE	GetOpMode(){return m_OpMode;};			// Operation Mode
	virtual void	SetOpMode(OPMODE om){m_OpMode = om;};	
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
	
	virtual ~CDsDrawVu(); 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	///////////////////////
	CDVM_Genr	m_DVM_Genr;
	CDVM_Edit	m_DVM_Edit;
	CDVM_Del	m_DVM_Del;
	CDVM_Post	m_DVM_Post;
	/////////////////////////////////////////// ViewMode
	BOOL		m_bViewGene;
	BOOL		m_bViewMesh;
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
	BOOL		m_bNS[200];
	/////////////////////////// Dirty	
	BOOL		m_bNS_D_Curve;
	BOOL		m_bNS_P_Curve;
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
	/////////////////////////////////////////////////////////////////////////

// Generated message map functions
public:
	//{{AFX_MSG(CDsDrawVu)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
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
	afx_msg void OnNoshowCentroid();
	afx_msg void OnUpdateNoshowCentroid(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDCurve();
	afx_msg void OnUpdateNoshowDCurve(CCmdUI* pCmdUI);
	afx_msg void OnNoshowDObject();
	afx_msg void OnNoshowPCurve();
	afx_msg void OnUpdateNoshowPCurve(CCmdUI* pCmdUI);
	afx_msg void OnModeDesign();
	afx_msg void OnUpdateModeDesign(CCmdUI* pCmdUI);
	afx_msg void OnModeInterpolate();
	afx_msg void OnUpdateModeInterpolate(CCmdUI* pCmdUI);
	afx_msg void OnSummaryCurveDirty();
	afx_msg void OnSummaryCurvePosted();
	afx_msg void OnSummaryNodeAlltypes();
	afx_msg void OnSummaryNodeControl();
	afx_msg void OnSummaryNodeMesh();
	afx_msg void OnNoshowMnlabel();
	afx_msg void OnUpdateNoshowMnlabel(CCmdUI* pCmdUI);
	afx_msg void OnNoshowMnodes();
	afx_msg void OnUpdateNoshowMnodes(CCmdUI* pCmdUI);
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	afx_msg void OnViewModeGenerator();
	afx_msg void OnUpdateViewModeGenerator(CCmdUI* pCmdUI);
	afx_msg void OnViewModeMesh();
	afx_msg void OnUpdateViewModeMesh(CCmdUI* pCmdUI);
	afx_msg void OnNoshowLabelElements();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

#endif
/////////////////////////////////////////////////////////////////////////////
