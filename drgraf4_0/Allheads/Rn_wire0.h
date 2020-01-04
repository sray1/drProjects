// CWire_0.h : header file
//
#ifndef _RN_WIRE0_H_
#define _RN_WIRE0_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Render.h"
/////////////////////////////////////////////////////////////////////////////
// CWire_0
/////////////////////////////////////////////////////////////////////////////
#define	MAX_NOSOLABEL	100
#define	MAX_NOSOEL		100
/////////////////////
class AFX_EXT_CLASS CWire_0 : public CRender
{
// Construction
public:  
	CWire_0();
	CWire_0 (
				CDrawView* pView, RENDITION rend, BOOL bParallel,
				BOOL bNS[],BOOL bNSEL[],BOOL bNSLE[]
			);
	DECLARE_DYNAMIC(CWire_0)
protected: 
public:
// Implementation
public:

	int 	Init
					(
						int nView,BOOL bCulling3D,WORLD VDir,
					 	pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
						double dzMin, double dScale_U,double dScale_V,
						double dShrink
					);
	int		RenderScene_GENERATOR
					(
						CClientDC* pDC,CRect& RectClip,int nActiveObjType,
						int nActiveObjIndex,int nViewNum
					);
					
	void 	RenderReadyOBJECT
					(	
						CDC* pDC,CDrObject* pObject,int nObjectType
					);

	int		RenderScene_MESH
					(
						CClientDC* pDC,CRect& RectClip,int nActiveObjType,
						int nActiveObjIndex,int nViewNum
					);
					
	void 	RenderReadyMESH
					(	
						CDC* pDC,CDrObject* pObject,int nObjectType
					);

protected:
					
	int		RenderOBJ3D
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderSOLID
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderPATCH
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderCURVE
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderNODE
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderSUPPORT
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderSTATIC
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	//////////////////////////////////////////////////////
	int		RenderMesh3D
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderMesh2D
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderMesh1D
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected
					);
	int		RenderSTRAY
					(
						CClientDC* pDC,CRect& RectClip,
						CDrObject* pObject,BOOL bSelected,int nViewNum
					);
	int		RenderLabelMeshElem(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum);
	int		RenderLabels(CDC* pDC,CDrObject* pObject,BOOL bSelected,int nViewNum);
					

protected:


	BOOL		m_bMeshScene;
	/////////////////////////
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
	////////////////////////////// NoShow Controls
	BOOL		m_bNoSoEL[MAX_NOSOEL];
	BOOL		m_bNoSoLabEL[MAX_NOSOLABEL];
	////////////////////////////// StaticLoad
	BOOL		m_bNS_Force;	
	BOOL		m_bNS_Displace;
	BOOL		m_bNS_Pressure;
	BOOL		m_bNS_Thermal;
	BOOL		m_bNS_LumpWt;
	////////////////////////////// Supports
	BOOL		m_bNS_RIGID; 
	BOOL		m_bNS_Lin_Spring; 
	BOOL		m_bNS_Lin_Snubber; 
	BOOL		m_bNS_Non_Spring; 
	BOOL		m_bNS_Non_Snubber; 
	/////////////////////////// Dirty	
	BOOL		m_bNS_D_Object;			
	BOOL		m_bNS_D_Profile_S;
	BOOL		m_bNS_D_Solid;	
	BOOL		m_bNS_D_Profile_P;
	BOOL		m_bNS_D_Patch;	
	BOOL		m_bNS_D_Profile_C;
	BOOL		m_bNS_D_Curve;
	/////////////////////////// Posted	
	BOOL		m_bNS_P_Object;			
	BOOL		m_bNS_P_Profile_S;
	BOOL		m_bNS_P_Solid;	
	BOOL		m_bNS_P_Profile_P;
	BOOL		m_bNS_P_Patch;	
	BOOL		m_bNS_P_Profile_C;
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
	virtual ~CWire_0(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CWire_0)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
