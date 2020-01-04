// Patch.h : header file
//
#ifndef _DRPATCH_H_
#define _DRPATCH_H_       

#include "DrCurve.h"
#include "DListMgr.h"
#include "glb_Type.h"
#include "glb_CuPS.h"

//#pragma warning( disable : 4200 )
#include "glb_Rend.h"               // Render Attribs.
// CDrPatch    ///////////////////////////////////////////////////////////////
class CDrPatch: public CDrCurve
{
public:
// Construction                 
	CDrPatch();
	DECLARE_SERIAL(CDrPatch);
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	///////////////////////////////////////////////////////////////////////
	virtual void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual void 		TransformObjectToView(pMATRIX pViewM);
	virtual BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual void 		ProjectObject
							(	pMATRIX pvv3DM,
								double dScale_U,double dScale_V
							);
//	virtual	int 		Calc_3DBoundsLocal();
	///////////////////////////////////////////////////////////////////
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);		 // control Node Hit
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
    virtual	CDListMgr*	GetCurveList(){return &m_CurveList;};
    virtual	CDListMgr*	GetSolidList(){return &m_SolidList;};
	//////////////////////////////////////////////////////////////////////						
	virtual BOOL	IsNormalNeeded(){return m_bNormalDraw;};							
	virtual void	SetNormalNeed(BOOL bNN){m_bNormalDraw = bNN;};							
	virtual	BOOL		Is2D(){return m_b2D;};// 1D or 2D 
	virtual	void		Set2D(BOOL bDim){m_b2D = bDim;};					// 1D or 2D 
	////////////////////
	virtual int 		AppendToObject
						(	
							CDListMgr* pObj3DList,
							CDListMgr* pSolidList, 
							CDListMgr* pCurveList, 
							CDListMgr* pElemList, 
							CDListMgr* pNodeList,
							CDListMgr* pCNodeList
						);
	////////////////////////////////////////////////////////////////////
	virtual int			GetSegmentCount_T(){return m_nSegments_T;};
	virtual void		SetSegmentCount_T(int nSegs){m_nSegments_T = nSegs;};
	virtual BOOL		IsClosed_T(){return m_bClosed_T;};
	virtual void		SetClosed_T(BOOL bYes){m_bClosed_T = bYes;};
	virtual int			GetMaxCubicPatches_S(){return m_nMaxCubicPatches_S;};
	virtual void		SetMaxCubicPatches_S(int nMax){m_nMaxCubicPatches_S = nMax;};
	virtual int			GetMaxCubicPatches_T(){return m_nMaxCubicPatches_T;};
	virtual void		SetMaxCubicPatches_T(int nMax){m_nMaxCubicPatches_T = nMax;};
	virtual int			GetMaxCNodes_T(){return m_nMaxCNodes_T;};
	virtual void		SetMaxCNodes_T(int nMax){m_nMaxCNodes_T = nMax;};
	virtual int			GetMaxOutPts_T(){return m_nMaxOutPts_T;};
	virtual void		SetMaxOutPts_T(int nMax){m_nMaxOutPts_T = nMax;};
	/////////////////////////////////////////////////////////////
	virtual int 		NumberOfCubicPatches();
	virtual int 		NumberOfLinearPatches();
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

	virtual pWORLD	GetFromPtLocal(){return &m_FromPtLocal;};
	virtual void	SetFromPtLocal(WORLD vPt){m_FromPtLocal = vPt;};
	virtual pWORLD	GetToPtLocal(){return &m_ToPtLocal;};
	virtual void	SetToPtLocal(WORLD vPt){m_ToPtLocal = vPt;};
	virtual pWORLD	GetFromPtWorld(){return &m_FromPtWorld;};
	virtual void	SetFromPtWorld(WORLD vPt){m_FromPtWorld = vPt;};
	virtual pWORLD	GetToPtWorld(){return &m_ToPtWorld;};
	virtual void	SetToPtWorld(WORLD vPt){m_ToPtWorld = vPt;};
	virtual pWORLD	GetFromPtEye(){return &m_FromPtEye;};
	virtual void	SetFromPtEye(WORLD vPt){m_FromPtEye = vPt;};
	virtual pWORLD	GetToPtEye(){return &m_ToPtEye;};
	virtual void	SetToPtEye(WORLD vPt){m_ToPtEye = vPt;};
	virtual pWORLD	GetAxis(){return &m_vAxis;};
	virtual void	SetAxis(WORLD vAxis){m_vAxis = vAxis;};
	virtual double	GetLength(){return m_dLen;};
	virtual void	SetLength(double dLen){m_dLen = dLen;};
	virtual int		GetSegs(){return m_nSegs;};
	virtual void	SetSegs(int nSegs){m_nSegs = nSegs;};
	virtual double	GetAng_1(){return m_dAng_1;};
	virtual void	SetAng_1(double dAng){m_dAng_1 = dAng;};
	virtual double	GetAng_2(){return m_dAng_2;};
	virtual void	SetAng_2(double dAng){m_dAng_2 = dAng;};
	//////////////////////////////////////////////////////////////////
	virtual PATCHTYPE 	GetPatchType(){return m_PatchType;};
	virtual void		SetPatchType(enum PATCHTYPE kind)
							{m_PatchType = kind;};
    ///////////////////////////////////////////////////////
	virtual int  	GetOut_S(){return m_nOut_S;};
	virtual void  	SetOut_S(int nOut){m_nOut_S = nOut;};
	virtual int  	GetOut_T(){return m_nOut_T;};
	virtual void  	SetOut_T(int nOut){m_nOut_T = nOut;};
	virtual long  	GetLongOutPts(){return m_nOut;};
	virtual void  	SetLongOutPts(long nOut){m_nOut = nOut;};
	///////////////////////////////////////////////////
	virtual long	GetTotalElems(){return m_nTotElems;};
	virtual void	SetTotalElems(long nMax){m_nTotElems = nMax;};
 	//////////////////////////////////////////////////////////
	virtual void 	Calc_PolyNormalWorld();
	virtual void 	TransformPolyNormalToEye(pMATRIX pViewM);
	virtual void 	ProjectPolyNormalToScreen3D
						(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 	Calc_NodeNormalWorld();
	virtual void 	Calc_NodeNormalEye();
	virtual void 	Calc_NodeNormalScreen3D();
	///////////////////////////////////////////// 
//	virtual void 	RefillCNLocalPosForPosting();
	virtual void 	Generate_Patch();
	virtual SUBDIV	GetSubDiv(){return m_nSubDiv;};
	virtual void	SetSubDiv(SUBDIV sd){m_nSubDiv = sd;};
	virtual ORIENT 	GetOrient(){return m_nOrient;};
	virtual void 	SetOrient(ORIENT ot){m_nOrient = ot;};
	//////////////////////////////////////////
	virtual pWORLD 	GetMemIn(int index){return m_pIn_S[index];};
	//////////////
	virtual void 	SetMemIn(pWORLD pIn,int index){m_pIn_S[index] = pIn;};
	virtual void 	SetMemIn(pWORLD pIn){m_pIn = pIn;};
	virtual void 	SetMemInDP(POINT* pInDP){m_pInDP = pInDP;};
	virtual void 	SetMemOut(pWORLD pOut){m_pOut = pOut;};
	virtual void 	SetMemOutDP(POINT* pOutDP){m_pOutDP = pOutDP;};
	//////////////////////////////////////////////////

 	
 	

protected:
	
	void 	GoDoControlNodes(CDC* PtrDC);
	void 	GoDoIt(CDC* PtrDC);
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
//	void 	Calc_ScreenRectFromCNodes();
	void 	Calc_ScreenRectFromPoly();
//	void 	Rearrange3DCorners(pWORLD pMin, pWORLD pMax);
//	void 	Rearrange2DCorners();
	////////////////////////////////////////////////////////////////////////////////////////
//	void 	FinishObject();
	void 	TransformToWorldPos(pMATRIX pLM,BOOL bYes);
	void 	TransformToEyePos(pMATRIX pViewM);
	void 	ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	BOOL 	CullWorld(WORLD VDir);
	BOOL 	CullScreen(pMATRIX pViewM);
	///////////////////////////////////// DirtyDraw				
	void 	UnitAxisFromEndNodes();
//	void 	RefillCNEyePosForDirtyDraw();
//	void 	ProjectForDirtyDraw
//				(pMATRIX pvv3DM,double dScale_U,double dScale_V);
		          

			
// Helper functions
protected:
// Attributes
 
	BOOL		m_bNormalDraw;					// Normal draw 
	/////////////////////////////////
	PATCHTYPE	m_PatchType;           	// PA_BEZIER, etc
	BOOL		m_b2D;					// 1D = Grid or 2D = plate etc 
	/////////////////////////////////
	CDListMgr	m_CurveList;       // Control Curves
	CDListMgr	m_SolidList;       // DrObject Pointers        "      "    "
	/////////////////////////////////
	int			m_nSegUnif_T;		//formerly:m_nSegments_T;
	BOOL		m_bClosed_T; 
	int			m_nMaxINodes_T;
	int			m_nMaxCNodes_T;
	int			m_nMaxOutPts_T;
//	int			m_nMaxCubicPatches_S;   // No. of Curves = m_nMaxCurves_S in DrCurve.h
	int			m_nMaxCurves_T;			// Formaerly: m_nMaxCubicPatches_T;   // No. of Curves
	//////////////////////////////////////// Construction Help
	CString		m_CurveID[4];      	// XSec etc
	int			m_nSegs;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	WORLD 		m_FromPtLocal;		// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtWorld;	// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtEye;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtLocal;			// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtWorld;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtEye;		// used also for Sweep/Duct Anchor
	double		m_dLen;
	double		m_dLenEye;
	WORLD		m_vAxis;		// unit Extrusion Axis/XFormed
	WORLD		m_vAxisEye;		// unit Extrusion Axis/XFormed
	/////////////////////
	CString		m_FromID;		// also used:AnchorID for Sweep/Duct
	CString		m_ToID;
//	CString		m_CurveID;      // XSec   Profile for Sweep
	/////////////////////////////////////////// Rotate
	double		m_dAng_1;
	double		m_dAng_2;
	/////////////////////////////////////////// Duct
	int			m_nOut_S;	//	number of generated Patch vertices in U dir	
	int			m_nOut_T;	//	number of generated Patch vertices in V dir	
    ////////////////////////////////////// Memory
	pWORLD		m_pIn_S[4];	// XSec etc Control Pointers
	//////////////////////
	SUBDIV		m_nSubDiv;
	ORIENT 		m_nOrient;
	////////////////////////////////////// NoOfElems
	long		m_nTotElems;
	//////////////////////////////////////////////////////////////////////////////// Output
	PATCHOUTPUT	m_OutMethod;		// Output Method
	BOOL		m_bUniform_T;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	int			m_nMaxOutSeg;		// Number of Output Segments on ENTIRE Curve
	pINT		m_pNum_t_T;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_t_T;			// Output t-distribution array:
											//	Dis_t[i], i = 1,nMaxOutSeg+1																							
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	int			m_nOrder_T;				// k
	int			m_nData_T;				// GIVEN: # of Data 		= m_nMaxINodes_S  
//	int			m_nSeg_DT_T;			// L = #of CurveSegments 	= m_nMaxCurves 
//	int			m_nSeg_BS_T;			// n
	int			m_nCon_BS_T; 			// n + 1: #of Spline Controls// for drawing ControlNet
	int			m_nMKnots_T;			// n + k + 1 = Total		// Not Need
	int			m_nKnots_T;				// n - k + 3 = distinct		// User Need
//	int			m_nCon_BZ_T;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	int 		m_nDim_T;				// 4 = RATIONAL/	3 = NONrational 
	WEIGHT		m_WtType_T;
	KNOT		m_KnotType_T;
	BOUNDARY	m_BCL_T;
	BOUNDARY	m_BCR_T;
	VECTOR		m_TanL_T;
	VECTOR		m_TanR_T;
	////////////////////// Memory for Interpolation
	pDOUBLE		m_pMKnots_T;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pDOUBLE		m_pWts_BS_T;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	pWORLD		m_pCon_BS_T;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		m_pKnot_T; 	// distinct( for User Need)
	pDOUBLE		m_pWts_DT_T;	// for User Need
	pDOUBLE		m_pWts_BZ_T;
//	pWORLD 		m_pCon_BZ;	// stored in m_CNodeList
	//////////////////////////////////////////////////////////////////// CONICS
	int			m_nData_Ex_T;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	BOOL		m_bExpanded_T;
	int			m_nMaxENodes_T;
	WORLD		m_Center_T;	// Circle
	WORLD		m_Normal_T;	
	double		m_Radius_T;
	double		m_Theta_T;
	double 		m_SegAngle_T;
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		m_bHole_T;


public:
	virtual ~CDrPatch();
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



