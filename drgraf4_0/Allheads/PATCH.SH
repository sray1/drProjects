// Patch.h : header file
//
#ifndef _PATCH_H_
#define _PATCH_H_       

#include "DrObject.h"
#include "Obj3D.h"
#include "DListMgr.h"
#include "globals.h"

//#pragma warning( disable : 4200 )
//#include "3d.h"
#include "3dcolor.h"               // Render Attribs.
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_PATCH	2 // Max & Min Corners
// CDrPatch    ///////////////////////////////////////////////////////////////
class CDrPatch: public CDrObject
{
public:
// Construction                 
	CDrPatch();
	DECLARE_SERIAL(CDrPatch);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual int 		GetLevelType(){return m_nLevelType;};
	virtual void		SetLevelType(int nType){ m_nLevelType = nType;};
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	// for smart painting(InvalidateRect) we will find bounding Cnode Coords and store in
	// ConvexHull[MAX_NODES_PATCH] which wil be then supplied thro' GetRawCoords
	/////////////////////////////////////////////////////////////////////////////////////////
	virtual int			GetMaxCorners(){return (int)MAX_NODES_PATCH;}; // Convex Hull(CNodes)
	virtual void 		GetRawCoords(long* lCoord, int* pnPrecision, int index);
	virtual	void 		GetRawCoords(long* lCoord, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt[index] = pt;
						};
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
	virtual void		RearrangeProjectedCoords();// put max/min in right place;					
	////////////////////////////////////////////////////////////////////////////////////////
	virtual	void 		FinishObject();
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);		 // control Node Hit
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual void        GetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	nWidth  =	m_nPenWidth;
					 	 	crColor =	m_crPenColor;
					  		nStyle  =	m_nPenStyle;
				  		};	
	virtual void        SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	m_nPenWidth  = nWidth;
					 		m_crPenColor = crColor;
					 		m_nPenStyle  = nStyle;
						};
	////////////////////////////////////////////////
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
    ////////////////////////////////////////////////////////////////////// helper
    virtual	CDListMgr*	GetCNodeList(){return &m_CNodeList;};
    virtual	CDListMgr*	GetNodeList(){return &m_NodeList;};
    virtual	CDListMgr*	GetPolyList(){return &m_PolyList;};
	//////////////////////////////////////////////////////////////////////						
	virtual	int 		AppendToObject(CDListMgr* pPolyList, CDListMgr* pNodeList);
	virtual	int 		SetObjectTransform(pMATRIX xF);
	virtual	int 		CatObjectTransform(pMATRIX xF);
	virtual	int 		GetObjectTransform(pMATRIX xF);
	virtual	int 		SetObjectRAttribs(pRendAttr pRA);
	virtual	int 		GetObject3DBounds();//ConvexHull of CNodes
	////////////////////////////////////////////////////////////////////
	virtual int			GetSegmentCount_S(){return m_nSegments_S;};
	virtual void		SetSegmentCount_S(int nSegs){m_nSegments_S = nSegs;};
	virtual int			GetSegmentCount_T(){return m_nSegments_T;};
	virtual void		SetSegmentCount_T(int nSegs){m_nSegments_T = nSegs;};
	virtual BOOL		IsClosed_S(){return m_bClosed_S;};
	virtual void		SetClosed_S(BOOL bYes){m_bClosed_S = bYes;};
	virtual BOOL		IsClosed_T(){return m_bClosed_T;};
	virtual void		SetClosed_T(BOOL bYes){m_bClosed_T = bYes;};
	virtual int			GetCurveObjectType(){return m_nCurveObjectType;};
	virtual void		SetCurveObjectType(int nType){m_nCurveObjectType = nType;};
	virtual int			GetMaxCubicPatches_S(){return m_nMaxCubicPatches_S;};
	virtual void		SetMaxCubicPatches_S(int nMax){m_nMaxCubicPatches_S = nMax;};
	virtual int			GetMaxCubicPatches_T(){return m_nMaxCubicPatches_T;};
	virtual void		SetMaxCubicPatches_T(int nMax){m_nMaxCubicPatches_T = nMax;};
	virtual int			GetMaxCNodes_S(){return m_nMaxCNodes_S;};
	virtual void		SetMaxCNodes_S(int nMax){m_nMaxCNodes_S = nMax;};
	virtual int			GetMaxCNodes_T(){return m_nMaxCNodes_T;};
	virtual void		SetMaxCNodes_T(int nMax){m_nMaxCNodes_T = nMax;};
	virtual int			GetMaxOutPts_S(){return m_nMaxOutPts_S;};
	virtual void		SetMaxOutPts_S(int nMax){m_nMaxOutPts_S = nMax;};
	virtual int			GetMaxOutPts_T(){return m_nMaxOutPts_T;};
	virtual void		SetMaxOutPts_T(int nMax){m_nMaxOutPts_T = nMax;};
	virtual BOOL		IsDirty(){return m_bDirty;};
	virtual void		SetDirty(BOOL bDirty){m_bDirty = bDirty;};
	/////////////////////////////////////////////////////////////
	virtual int 		NumberOfCubicPatches();
/*	
						(
							enum CURVETYPE kind,
							int nMaxPatchCNodes_S,int nMaxPatchCNodes_T,
							int nSegs_S,int nSegs_T,BOOL bClosed_S,BOOL bClosed_T,
							int* pnPatches_S,int* pnPatches_T,int* pnOut_S,int* pnOut_T
						);
*/						
	virtual int 		NumberOfElements(UINT nPatchType,int nElemType);
	virtual int 		GeneratePointsforPatches
						(
							enum CURVETYPE kind,	//	cubic basis function selection
							int			nCtlU,	//	number of control vertices in U direction
							int			nSegU,	//	number of intervals in U direction
							int			nCtlV,	//	number of control vertices in V direction  	IN CALLING ROUTINE
							int			nSegV,	//	number of intervals in V direction
							pWORLD		ptCtl,	//	array of control vertices
							pWORLD		pOut,	//	array of Output 3D World Points
							int			nPU,	// 	Total Number of Cubic Patches in U direction
							int			nPV,	// 	Total Number of Cubic Patches in V direction
							int			nOutU,	//	expected number of generated curve vertices in U	
							int			nOutV,	//	expected number of generated curve vertices in V	
							int			nOut	//	expected number of generated curve vertices	
						);
	virtual int ExtrudeCurve
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
						(
							double	depth,	//	distance to the extended surface's end
							pWORLD	v,		//	unit extrusion vector (direction)
							int		segs,	//	subdivision value (interior spaces)
							int		nPts,	//	number of input data points
							pWORLD	pPt,	//	input data point array
							pWORLD	pOut,	//	Output Pts array
							int		nOut	//	expected number of generated curve vertices	
						);	  
	virtual int RotateCurve
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
						(
							pWORLD	pAxisPt,//  a pt. on the rotation vector
							double	alpha,	//	initial position angle in degrees
							double	theta,	//	total rotation in degrees
							pWORLD	pAxis,	//	unit direction vector of rotation axis
							int		segs,	//	subdivision value (interior spaces)
							int		nPts,	//	number of input data points
							pWORLD	pPt,	//	input data point array
							pWORLD	pOut,	//	Output Pts array
							int		nOut	//	expected number of generated curve vertices	
						);	  
	virtual int LoftCurves
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
						(
							short	segs,	//	subdivision value (interior spaces)
							short	nPts,	//	number of input data points
							pWORLD	p0,		//	input data point array for start curve
							pWORLD	p1,		//	input data point array for end curve
							pWORLD 	pOut,	//	Output Pts array
							int		nOut	//	expected number of generated curve vertices	
						);	  
	virtual int SweepCurve
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
						(
							WORLD	wAnchor,//	cross section Anchor point
							int		npXSec,	//	number of cross section points
							pWORLD	ppXSec,	//	cross section curve points
							int		npSpine,//	number of path points
							pWORLD	ppSpine,//	path curve points
							pWORLD	ppProf,//	path scaling factors
							pWORLD	ppTwist,//	path rotation factors
							pWORLD	pOut,	//	Output Pts array
							int		nOut	//	expected number of generated curve vertices	
						);	  
	virtual int DuctCurve
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
						(
							WORLD	wAnchor,//	cross section Anchor point
							int		npXSec,	//	number of cross section points
							pWORLD	ppXSec,	//	cross section curve points
							int		npSpine,//	number of path points
							pWORLD	ppSpine,//	path curve points
							pWORLD	ppTwist,//	path rotation factors
							pWORLD	pOut,	//	Output Pts array
							int		nOut	//	expected number of generated curve vertices	
						);	  
	//////////////////////////////////////// Construction Help
	virtual CString	GetFromID(){return m_FromID;};
	virtual void	SetFromID(CString id){m_FromID = id;};
	virtual CString	GetToID(){return m_ToID;};
	virtual void	SetToID(CString id){m_ToID = id;};
	virtual CString	GetCurveID(int index){return m_CurveID[index];};
	virtual void	SetCurveID(CString id,int index)
						{m_CurveID[index] = id;};
/*
	virtual CString	GetCurveID_2(){return m_CurveID_2;};
	virtual void	SetCurveID_2(CString id){m_CurveID_2 = id;};
	virtual CString	GetCurveID_3(){return m_CurveID_3;};
	virtual void	SetCurveID_3(CString id){m_CurveID_3 = id;};
	virtual CString	GetCurveID_4(){return m_CurveID_4;};
	virtual void	SetCurveID_4(CString id){m_CurveID_4 = id;};
*/	
	virtual double	GetLength(){return m_dLen;};
	virtual void	SetLength(double dLen){m_dLen = dLen;};
	virtual int		GetSegs(){return m_nSegs;};
	virtual void	SetSegs(int nSegs){m_nSegs = nSegs;};
	virtual double	GetAng_1(){return m_dAng_1;};
	virtual void	SetAng_1(double dAng){m_dAng_1 = dAng;};
	virtual double	GetAng_2(){return m_dAng_2;};
	virtual void	SetAng_2(double dAng){m_dAng_2 = dAng;};
	//////////////////////////////////////////////////////////////////
	virtual UINT 	GetPatchType(){return m_nPatchType;};
	virtual void	SetPatchType(UINT kinat{minkÛÚÒ ¥+
CancelLinkÛÚÒ µ+IOleUILinkContainerÚÒ ª+	operator=  °+ 	 û+¢+  Ì      û+  §+ 	 " û+¢+         §+
  ß+    	 " û+¢+  ˚    
  ©+    	 û+¢+  ;    
  ´+    	 û+¢+  /#    
  ≠+    	 û+¢+  õ+    
  Ø+    	 û+¢+  ú+    
  ±+     	 û+¢+  ˚    
  ≥+/////////////////////
	virtual void  	SetMemIn(pWORLD pIn,int index)
					{ m_pIn[index] = pIn;};
	virtual void  	SetMemInDP(POINT* pInDP,int index)
					{ m_pInDP[index] = pInDP;};
	virtual void  	SetMemOut(pWORLD pOut)
					{ m_pOut = pOut;};
	virtual void  	SetMemOutDP(POINT* pOutDP)
					{ m_pOutDP = pOutDP;};
	////////////////////////////////////////////////					
	virtual long		GetTotalElems(){return m_nTotElems;};
	virtual void		SetTotalElems(long nMax){m_nTotElems = nMax;};
    ////////////////////////////////////////////////

protected:
	
	void 		GoDoControlNodes(CDC* PtrDC,BOOL bPenChange,int index);
	void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
	//////////////////////////////////////////////////

			
// Helper functions
protected:
// Attributes
 
	int			m_nLevelType;
	int			m_nObjectType;
	int			m_nElemType;	
	long		m_nObjectNo;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	CURVETYPE	m_CurveType;			// for P_MESH
	////// ’+
  ⁄+ ﬁ+ 	  ¬+∆+  €+      ‹+  ! ›+   ¬+ 	  ¬+∆+         ‡+ 	 ·+¬+∆+  €+      ! ¬+   „+ WGV COleLinksDialogö ê!    classCOleLinksDialogÒ ‰+GetRuntimeClassÚÒ¿+ & m_elÛÚÒ Ë+COleLinksDialogÚÒ Î+DoModalÚÒ Ì+~COleLinksDialogÒ Ô+DumpÒ Ò+AssertValidÚÒ% H m_pDocumentﬁ% J m_pSelectedItem L m_posÚÒr  N m_bUpdateLinksÒr  P m_bUpdateEmbeddings	¬+XOleUILinkContainer¬+ R m_xOleUILinkContainerÚÒ7 _interfaceEntlyList;        // DrObject
	MATRIX		m_instanceXf;
	RendAttr	m_raOptions;
	BOOL		m_bInstanced;
	int			m_nSegments_S;
	int			m_nSegments_T;
	BOOL		m_bClosed_S; 
	BOOL		m_bClosed_T; 
	int			m_nMaxCNodes_S;
	int			m_nMaxCNodes_T;
	int			m_nMaxOutPts_S;
	int			m_nMaxOutPts_T;
	int			m_nMaxCubicPatches_S;   // No. of Cubic Curves
	int			m_nMaxCubicPatches_T;   // No. of Cubic Curves
	int			m_nCurveObjectType;		// ObjectType to create; -1 = no creation reqd
	BOOL		m_bDirty;				// TRUE=NOT POSTED/FALSE=POSTED	
	UINT		m_nPatchType;           // P_MESH,P_EXTRUDE etc
    //////////////////////////////////////////////////////////////////////////////// 
    LPOINT3		m_ptMinMax[2];			// Raw Bounding Coords mixed as Min & Max 
	POINT 		m_pt[MAX_NODES_PATCH];	// SCREEN Coords.of Corners of 3DBoundVolume
	//////////////////////////////////////// Construction Help
	CString		m_CurveID[4];      // XSec etc
	int			m_nSegs;
	/////////////////////////////////////////// Extrude
	CString		m_FromID;		// also used:AnchorID for Sweep/Duct
	CString		m_ToID;
//	CString		m_CurveID;      // XSec   Profile for Sweep
	double		m_dLen;
	WORLD		m_vAxis;		// unit Extrusion Axis/XFormed
	/////////////////////////////////////////// Rotate
	double		m_dAng_1;
	double		m_dAng_2;
	WORLD 		m_FromPt; // used also for Sweep/Duct Anchor
	/////////////////////////////////////////// Duct
	int			m_nOut_S;	//	number of generated Patch vertices in U dir	
	int			m_nOut_T;	//	number of generated Patch vertices in V dir	
    ////////////////////////////////////// Memory
	pWORLD		m_pIn[4];	// Control Nodes -WorldCoords
	POINT*		m_pInDP[4]; // Control Nodes -ScreenCoords
	pWORLD		m_pOut;		// Output  Nodes -WorldCoords
	POINT*		m_pOutDP;   // Output  Nodes -ScreenCoords
	long		m_nOut;
	////////////////////////////////////// NoOfElems
	long		m_nTotElems;


public:
	virtual ~CDrPatch(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrPatch)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



