// CAxWire_0.h : header file
//
#ifndef _AX_WIRE0_H_
#define _AX_WIRE0_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CAxWire_0
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CAxWire_0 : public CObject
{
// Construction
public:  
	CAxWire_0();
	CAxWire_0(CView* pView, BOOL bParallel, BOOL bNS[]);
	DECLARE_DYNAMIC(CAxWire_0)
protected: 
public:
// Implementation
public:

	virtual int 	Init
					(
						int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin, double dScale_U,double dScale_V,
						double dShrink
					);
	virtual int		RenderScene_AUXILLIARY
					(
						CClientDC* pDC,CRect& RectClip,int nActiveObjType,
						int nActiveObjIndex,int nViewNum
					);
					
					
	virtual void 	RenderReadyOBJECT
					(	
						CDC* pDC,CDrObject* pObject,int nObjectType
					);

protected:
					
	virtual int		RenderOBJECT
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	virtual int		RenderSTRAY
					(
						CClientDC* pDC,
						CDrObject* pObject,
						BOOL bSelected,
						int nViewNum 
					);
	virtual int		RenderLabels(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum);
					

protected:


	CView*		m_pView;
	/////////////////////////
	BOOL		m_bParallel;
	double		m_dShrink;
	/////////////////////////////////////////// ViewNumber
    int 		m_nView;
	/////////////////////////////////////////// Document Size
	double 		m_dzMin;
	double 		m_dScale_U;		// vv3DToLP:U-direction  
	double 		m_dScale_V;     // vv3DToLP:V-direction
	/////////////////////////////////////////// 3D drawing
	MATRIX		m_ViewM;		// viewers transform MATRIX
	MATRIX		m_ComposedM;
	MATRIX		m_vv3DM;		// Window to 3D Viewport MATRIX
    //////////////////////////////
//	BOOL		m_bParallel;	// if true disables perspective projection      In Render.h
	BOOL		m_bCulling3D;	// if true BackFaceCulling in WorldSpace   todo m_bCullWorld = m_bCulling3D
	/////////////////// View Orientation Parameters /////////////
	WORLD		m_VDir;			// View Direction
	///////////////////////////////////////////
	/////////////////////////// Dirty	
	BOOL		m_bNS_D_Curve;
	/////////////////////////// Posted	
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


public:
	virtual ~CAxWire_0(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CAxWire_0)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
