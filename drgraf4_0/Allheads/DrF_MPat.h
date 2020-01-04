// Patch.h : header file
//
#ifndef _DRPATCH_H_
#define _DRPATCH_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Triangle.h"
#include "DrCurve.h"
#include "DListMgr.h"
#include "glb_Type.h"
#include "glb_CuPS.h"

//#pragma warning( disable : 4200 )
#include "glb_Rend.h"               // Render Attribs.
// CDrPatch    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrPatch: public CDrCurve
{
public:
// Construction                 
	CDrPatch();
//////////////////////////////////////
	DECLARE_SERIAL(CDrPatch);
//////////////////////////////////////
	
	
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
	///////////////////////////////////////////////////////////////////
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);		 // control Node Hit
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////////						
	virtual BOOL		IsNormalNeeded(){return m_bNormalDraw;};							
	virtual void		SetNormalNeed(BOOL bNN){m_bNormalDraw = bNN;};							
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
	//////////////////////////////////////////////////////////////////////						
	virtual	BOOL		Is2D(){return m_b2D;};// 1D or 2D 
	virtual	void		Set2D(BOOL bDim){m_b2D = bDim;};					// 1D or 2D 
	////////////////////////////////////////////////////////////////////
	virtual CURVEPROC 	GetCurveType_T(){return m_CurveType_T;};
	virtual void		SetCurveType_T(CURVEPROC kind){m_CurveType_T = kind;};
	virtual int			GetSegmentCount_T(){return m_nSegUnif_T;};
	virtual void		SetSegmentCount_T(int nSegs){m_nSegUnif_T = nSegs;};
	virtual BOOL		IsClosed_T(){return m_bClosed_T;};
	virtual void		SetClosed_T(BOOL bYes){m_bClosed_T = bYes;};
	virtual int			GetnMaxCurves_T(){return m_nMaxCurves_T;};
	virtual void		SetnMaxCurves_T(int nMax){m_nMaxCurves_T = nMax;};
	virtual int			GetMaxCNodes_T(){return m_nMaxCNodes_T;};
	virtual void		SetMaxCNodes_T(int nMax){m_nMaxCNodes_T = nMax;};
	virtual int			GetMaxOutPts_T(){return m_nMaxOutPts_T;};
	virtual void		SetMaxOutPts_T(int nMax){m_nMaxOutPts_T = nMax;};
	/////////////////////////////////////////////////////////////
	virtual int 		NumberOfPatches();
	virtual int 		NumberOfElements(UINT nPatchType,int nElemType);
	//////////////////////////////////////// Construction Help
	virtual CString	GetCurveID(int index){return m_CurveID[index];};
	virtual void	SetCurveID(CString id,int index)
						{m_CurveID[index] = id;};
	virtual CURVELATCH	GetCurveLatch(int index){return m_CuLatch[index];};
	virtual void	SetCurveLatch(CURVELATCH id,int index)
						{m_CuLatch[index] = id;};
	virtual CString	GetFromID_T(){return m_FromID_T;};
	virtual void	SetFromID_T(CString id){m_FromID_T = id;};
	virtual CString	GetToID_T(){return m_ToID_T;};
	virtual void	SetToID_T(CString id){m_ToID_T = id;};
	virtual pWORLD	GetFromPtLocal_T(){return &m_FromPtLocal_T;};
	virtual void	SetFromPtLocal_T(WORLD vPt){m_FromPtLocal_T = vPt;};
	virtual pWORLD	GetToPtLocal_T(){return &m_ToPtLocal_T;};
	virtual void	SetToPtLocal_T(WORLD vPt){m_ToPtLocal_T = vPt;};
	virtual pWORLD	GetFromPtWorld_T(){return &m_FromPtWorld_T;};
	virtual void	SetFromPtWorld_T(WORLD vPt){m_FromPtWorld_T = vPt;};
	virtual pWORLD	GetToPtWorld_T(){return &m_ToPtWorld_T;};
	virtual void	SetToPtWorld_T(WORLD vPt){m_ToPtWorld_T = vPt;};
	virtual pWORLD	GetFromPtEye_T(){return &m_FromPtEye_T;};
	virtual void	SetFromPtEye_T(WORLD vPt){m_FromPtEye_T = vPt;};
	virtual pWORLD	GetToPtEye_T(){return &m_ToPtEye_T;};
	virtual void	SetToPtEye_T(WORLD vPt){m_ToPtEye_T = vPt;};
	virtual pWORLD	GetAxis_T(){return &m_vAxis_T;};
	virtual void	SetAxis_T(WORLD vAxis){m_vAxis_T = vAxis;};
	virtual double	GetLength_T(){return m_dLen_T;};
	virtual void	SetLength_T(double dLen){m_dLen_T = dLen;};
	virtual int		GetSegs_T(){return m_nSegs_T;};
	virtual void	SetSegs_T(int nSegs){m_nSegs_T = nSegs;};
	virtual double	GetAng_1_T(){return m_dAng_1_T;};
	virtual void	SetAng_1_T(double dAng){m_dAng_1_T = dAng;};
	virtual double	GetAng_2_T(){return m_dAng_2_T;};
	virtual void	SetAng_2_T(double dAng){m_dAng_2_T = dAng;};
	//////////////////////////////////////////////////////////////////
	virtual PATCHPROC 	GetPatchProc(){return m_PatchProc;};
	virtual void		SetPatchProc(enum PATCHPROC kind)
							{m_PatchProc = kind;};
	virtual PATCHTYPE 	GetPatchType(){return m_PatchType;};
	virtual void		SetPatchType(enum PATCHTYPE kind)
							{m_PatchType = kind;};
	virtual PATSUBTYPE 	GetPatSubType(){return m_PatSubType;};
	virtual void		SetPatSubType(enum PATSUBTYPE kind)
							{m_PatSubType = kind;};
    ///////////////////////////////////////////////////////
	virtual int  	GetOut_S(){return m_nOut_S;};
	virtual void  	SetOut_S(int nOut){m_nOut_S = nOut;};
	virtual int  	GetOut_T(){return m_nOut_T;};
	virtual void  	SetOut_T(int nOut){m_nOut_T = nOut;};
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
	virtual int 	Generate_Patch3(pWORLD pOut, pDOUBLE pOutWts);// Triangular Patches
	virtual int 	Generate_Patch4(pWORLD pOut, pDOUBLE pOutWts);// Quadrilateral Patches
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
	////////////////////////////////////////////////////////////// interpolation
	virtual BOOL	IsUniform_T(){return m_bUniform_T;};		// Output Distribution:
	virtual void	SetUniform_T(BOOL a){ m_bUniform_T = a;};		// Output Distribution:
	virtual int 		GetOrder_T(){return m_nOrder_T;};
	virtual void 		SetOrder_T(int nOrd){m_nOrder_T = nOrd;};
	virtual int			GetnDim_T(){return m_nDim_T;}; 			
	virtual void		SetnDim_T(int bs){m_nDim_T = bs;}; 		
	virtual PATCHOUTPUT	GetOutMethod_T(){return m_OutMethod_T;};	// Output Method
	virtual void		SetOutMethod_T(PATCHOUTPUT a){ m_OutMethod_T = a;};	// Output Method
	virtual int			GetMaxOutSeg_T(){return m_nMaxOutSeg_T;};	// Number of Output Segments on ENTIRE Curve
	virtual void		SetMaxOutSeg_T(int a){m_nMaxOutSeg_T = a;};	// Number of Output Segments on ENTIRE Curve
	virtual pINT		GetNum_tPointer_T(){return m_pNum_t_T;};	// Number of Outputs for each Output Segment
	virtual void		SetNum_tPointer_T(pINT a){m_pNum_t_T =a;};	// Number of Outputs for each Output Segment
	virtual pDOUBLE		GetDis_tPointer_T(){return m_pDis_t_T;};	// Number of Outputs for each Output Segment
	virtual void		SetDis_tPointer_T(pDOUBLE a){m_pDis_t_T =a;};	// Number of Outputs for each Output Segment
	virtual pINT		GetNum_tPointer_Ex_T(){return m_pNum_t_Ex_T;};	// Output t-distribution array:
	virtual void		SetNum_tPointer_Ex_T(pINT a){m_pNum_t_Ex_T = a;};	// Output t-distribution array:
	virtual pDOUBLE		GetDis_AngPointer_T(){return m_pDis_Ang_T;};	// Distribution of angles 
	virtual void		SetDis_AngPointer_T(pDOUBLE a){m_pDis_Ang_T =a;};	// Distribution of angles 
/*
	virtual int 		GetData_T(){return m_nData_T;};
	virtual void 		SetData_T(int ndat){m_nData_T = ndat;};
	virtual KNOT		GetKnotType_T(){return m_KnotType_T;};
	virtual void		SetKnotType_T(KNOT Kn){m_KnotType_T = Kn;};
	virtual WEIGHT		GetWtType_T(){return m_WtType_T;};
	virtual void		SetWtType_T(WEIGHT W){m_WtType_T = W;};
	virtual BOUNDARY	GetBCL_T(){return m_BCL_T;};
	virtual void		SetBCL_T(BOUNDARY bc){m_BCL_T = bc;};
	virtual BOUNDARY	GetBCR_T(){return m_BCR_T;};
	virtual void		SetBCR_T(BOUNDARY bc){m_BCR_T = bc;};
	virtual VECTOR		GetTanL_T(){return m_TanL_T;};
	virtual void		SetTanL_T(VECTOR T){m_TanL_T = T;};
	virtual VECTOR		GetTanR_T(){return m_TanR_T;};
	virtual void		SetTanR_T(VECTOR T){m_TanR_T = T;};
	virtual int			GetnCon_BS_T(){return m_nCon_BS_T;}; 			
	virtual void		SetnCon_BS_T(int bs){m_nCon_BS_T = bs;}; 		
	virtual int			GetnCon_BZ_T(){return m_nMaxCNodes_T;};		// m_nMaxCNodes_T 			
	virtual void		SetnCon_BZ_T(int bs){m_nMaxCNodes_T = bs;}; 		
	virtual int			GetnMKnots_T(){return m_nMKnots_T;}; 			
	virtual void		SetnMKnots_T(int bs){m_nMKnots_T = bs;}; 		
	virtual int			GetnKnots_T(){return m_nKnots_T;}; 			
	virtual void		SetnKnots_T(int bs){m_nKnots_T = bs;}; 		
	////////////////////// Memory for Interpolation
	virtual pDOUBLE		GetpMKnots_T(){return m_pMKnots_T;};			//---|	
	virtual void		SetpMKnots_T(pDOUBLE p){m_pMKnots_T = p;};	//---|	 THESE ACTUALLY
	virtual pDOUBLE		GetpWts_BS_T(){return m_pWts_BS_T;};		//---|-- WE DO NOT NEED, OUR	
	virtual void		SetpWts_BS_T(pDOUBLE p){m_pWts_BS_T = p;};	//---|   INTERNAL REPRESENTATION:
//	virtual pWORLD		GetpCon_BS_T(){return m_pCon_BS_T;};		//---|   ALWAYS - B E Z I E R	
//	virtual void		SetpCon_BS_T(pWORLD p){m_pCon_BS_T = p;};	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	virtual pDOUBLE		GetpKnots_T(){return m_pKnot_T;};				// User Need	
	virtual void		SetpKnots_T(pDOUBLE p){m_pKnot_T = p;};
	virtual pDOUBLE		GetpWts_DT_T(){return m_pWts_DT_T;};			// User Need	
	virtual void		SetpWts_DT_T(pDOUBLE p){m_pWts_DT_T = p;};
	virtual pDOUBLE		GetpWts_BZ_T(){return m_pWts_BZ_T;};			// Rational Need		
	virtual void		SetpWts_BZ_T(pDOUBLE p){m_pWts_BZ_T = p;};
//	virtual pWORLD		GetpCon_BZ_T(){return m_pCon_BZ_T;};			// stored in CNodeList	
//	virtual void		SetpCon_BZ_T(pWORLD p){m_pCon_BZ_T = p;};
*/
	//////////////////////////////////////////////////////////////////// CONICS
	virtual int 		GetData_Ex_T(){return m_nData_Ex_T;};
	virtual void 		SetData_Ex_T(int ndat){m_nData_Ex_T = ndat;};
	virtual BOOL		IsExpanded_T(){return m_bExpanded_T;};		// Output Distribution:
	virtual void		SetExpanded_T(BOOL a){ m_bExpanded_T = a;};		// Output Distribution:
	virtual int			GetMaxENodes_T(){return m_nMaxENodes_T;};	
	virtual void		SetMaxENodes_T(int nMax){m_nMaxENodes_T = nMax;};
	virtual double 		GetRadius_T(){return m_Radius_T;};
	virtual void 		SetRadius_T(double dat){m_Radius_T = dat;};
	virtual double 		GetTheta_T(){return m_Theta_T;};
	virtual void 		SetTheta_T(double dat){m_Theta_T = dat;};
	virtual WORLD 		GetCenter_T(){return m_Center_T;};
	virtual void 		SetCenter_T(WORLD dat)
						{	m_Center_T.x = dat.x;
							m_Center_T.y = dat.y;
							m_Center_T.z = dat.z;
						};
	virtual WORLD 		GetNormal_T(){return m_Normal_T;};
	virtual void 		SetNormal_T(WORLD dat)
						{	m_Normal_T.x = dat.x;
							m_Normal_T.y = dat.y;
							m_Normal_T.z = dat.z;
						};
	virtual double 		GetSegAngle_T(){return m_SegAngle_T;};
	virtual void 		SetSegAngle_T(double dat){m_SegAngle_T = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	virtual BOOL		IsHole_T(){return m_bHole_T;};
	virtual void		SetHole_T(BOOL bYes){m_bHole_T = bYes;};
	//////////////////////////////////////////////////////////////////// Derivatives
	virtual pWORLD	GetpTangents_T(){return m_pTangents_T;};
	virtual void	SetpTangents_T(pWORLD t){m_pTangents_T = t;};
	virtual pDOUBLE	GetpCurvatures_T(){return m_pCurvatures_T;};
	virtual void	SetpCurvatures_T(pDOUBLE t){m_pCurvatures_T = t;};
    //////////////////////////////////////////////////////////////////// Output
    virtual double	GetRatio_T(){return m_Ratio_T;};		// for OneSegment Linear Only
    virtual void	SetRatio_T(double r){m_Ratio_T = r;};	// for OneSegment Linear Only
	////////////////////////////////////////////////////////////// for Duct/Sweep
	virtual BOOL	IsIncTwist_T(){return m_bIncTwist_T;};
	virtual void	SetIncTwist_T(BOOL dLen){m_bIncTwist_T = dLen;};
	virtual double	GetTwistMult_T(){return m_TwistMult_T;};
	virtual void	SetTwistMult_T(double dLen){m_TwistMult_T = dLen;};
	virtual double	GetTwistStart_T(){return m_TwistStart_T;};
	virtual void	SetTwistStart_T(double dLen){m_TwistStart_T = dLen;};
	virtual BOOL	IsIncScale_T(){return m_bIncScale_T;};
	virtual void	SetIncScale_T(BOOL dLen){m_bIncScale_T = dLen;};
	virtual double	GetScaleMult_T(){return m_ScaleMult_T;};
	virtual void	SetScaleMult_T(double dLen){m_ScaleMult_T = dLen;};
	virtual double	GetScaleStart_T(){return m_ScaleStart_T;};
	virtual void	SetScaleStart_T(double dLen){m_ScaleStart_T = dLen;};
	///////////////////////////////////////////////////////////////////// Triangular Patch
    virtual	CDListMgr*	GetTriangleList(){return &m_TriangleList;};
	virtual int			GetnOutGlo_S(){return m_nOutGlo_S;};	
	virtual void		SetnOutGlo_S(int nMax){m_nOutGlo_S = nMax;};

	

protected:
	
	void 	GoDoControlNodes(CDC* PtrDC);
	void 	GoDoIt(CDC* PtrDC);
	void 	GoDoControlNodes_3(CDC* PtrDC);
	void 	GoDoIt_3(CDC* PtrDC);
	void	TRIANGLE_1(CDC* PtrDC,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST);
	void	TRIANGLE_2(CDC* PtrDC,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST);
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
	PATCHPROC	m_PatchProc;           // How Generated? PP_EXTRUDE etc
	PATCHTYPE	m_PatchType;           	// PA_TENSOR, etc
	PATSUBTYPE 	m_PatSubType;			// Tringle or Quadrilat
	CURVEPROC	m_CurveType_T;         	// PA_BEZIER, etc
	BOOL		m_b2D;					// 1D = Grid or 2D = plate etc 
	/////////////////////////////////
	int			m_nSegUnif_T;		//formerly:m_nSegments_T;
	BOOL		m_bClosed_T; 
	int			m_nMaxINodes_T;
	int			m_nMaxCNodes_T;
	int			m_nMaxCurves_T;			// Formaerly: m_nMaxCubicPatches_T;   // No. of Curves
	int			m_nPatchObjectType;		// ObjectType to create; -1 = no creation reqd
	//////////////////////////////////////// Construction Help
	CString		m_CurveID[4];      	// XSec etc
	CURVELATCH	m_CuLatch[4];      	// Latching
	int			m_nSegs_T;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	WORLD 		m_FromPtLocal_T;		// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtWorld_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtEye_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtLocal_T;			// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtWorld_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtEye_T;		// used also for Sweep/Duct Anchor
	double		m_dLen_T;
	double		m_dLenEye_T;
	WORLD		m_vAxis_T;		// unit Extrusion Axis/XFormed
	WORLD		m_vAxisEye_T;		// unit Extrusion Axis/XFormed
	/////////////////////
	CString		m_FromID_T;		// also used:AnchorID for Sweep/Duct
	CString		m_ToID_T;
	/////////////////////////////////////////// Rotate
	double		m_dAng_1_T;
	double		m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	BOOL		m_bIncTwist_T;	// Incremental?
	BOOL		m_bIncScale_T;	// for Sweep
	double		m_TwistMult_T;
	double		m_ScaleMult_T;	// for Sweep
	double		m_TwistStart_T;
	double		m_ScaleStart_T;	// for Sweep
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
	PATCHOUTPUT	m_OutMethod_T;		// Output Method
	BOOL		m_bUniform_T;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	int			m_nMaxOutPts_T;
	int			m_nMaxOutSeg_T;		// Number of Output Segments on ENTIRE Curve in T
	pINT		m_pNum_t_T;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_t_T;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_Ang_T;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pINT		m_pNum_t_Ex_T;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	int			m_nOrder_T;				// k 
	int 		m_nDim_T;				// 4 = RATIONAL/	3 = NONrational 
/*	
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
*/
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
	//////////////////////////////////////////////////////////////////// Derivatives
	pWORLD		m_pTangents_T;			// Tangents
	pDOUBLE		m_pCurvatures_T;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    double		m_Ratio_T;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	CDListMgr	m_TriangleList;       // Triangles
	//////////////////////////////  Globals:
	int			m_nOutGlo_S;			//  Total Output in each side of entire Base Patch

public:
	virtual ~CDrPatch();
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



