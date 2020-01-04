// Patch.h : header file
//
#ifndef _DRPATCH_H_
#define _DRPATCH_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Str_BlendEnd.h"
#include "Triangle.h"
#include "Triangle.h"
#include "DrCurve.h"
#include "DListMgr.h"
#include "Def_Type.h"
#include "Def_CuPS.h"

//#pragma warning( disable : 4200 )
#include "Def_Rend.h"               // Render Attribs.
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
	virtual BOOL		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////////						
	virtual	CATEGORY	GetCategory(){return m_Category;};
	virtual	void		SetCategory(CATEGORY CT){m_Category = CT;};
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
	////////////////////////////////////////////////////////////////////
	BOOL		IsObjectBndryHit(int nNet,POINT point,int& iBndry);
	////////////////////////////////////////////////////////////////////
	CURVEPROC 	GetCurveType_T(){return m_CurveType_T;};
	void		SetCurveType_T(CURVEPROC kind){m_CurveType_T = kind;};
	///////////////////////////////////////////////////////////////////// Used Only for Triangles
//	int			GetSegmentCount_T(){return m_nSegUnif_T;};
//	void		SetSegmentCount_T(int nSegs){m_nSegUnif_T = nSegs;};
	int			GetOutSegUnif_T(){return m_nSegUnif_T;};	// originally	GetSegmentCount_T
	void		SetOutSegUnif_T(int nSegs){m_nSegUnif_T = nSegs;};	//		SetSegmentCount_T
	//////////////////////////////////////////////////////////////////////////////////////////////
	BOOL		IsClosed_T(){return m_bClosed_T;};
	void		SetClosed_T(BOOL bYes){m_bClosed_T = bYes;};
	//////////////////////////////////////////////////////////////////
//	int			GetnMaxCurves_T(){return m_nMaxCurves_T;};
//	void		SetnMaxCurves_T(int nMax){m_nMaxCurves_T = nMax;};
	int			GetMaxBezSegments_T(){return m_nMaxCurves_T;};
	void		SetMaxBezSegments_T(int nMax){m_nMaxCurves_T = nMax;};
	//////////////////////////////////////////////////////////////////
	int			GetMaxCNodes_T(){return m_nMaxCNodes_T;};
	void		SetMaxCNodes_T(int nMax){m_nMaxCNodes_T = nMax;};
	int			GetMaxOutPts_T(){return m_nMaxOutPts_T;};
	void		SetMaxOutPts_T(int nMax){m_nMaxOutPts_T = nMax;};
	/////////////////////////////////////////////////////////////
	int 		NumberOfPatches();
	int 		NumberOfElements(UINT nPatchType,int nElemType);
	//////////////////////////////////////// Construction Help
	int			GetNodes_S(){return m_nNodes_S;};			// for Tensor Product
	void		SetNodes_S(int n){m_nNodes_S = n;};			// for Tensor Product
	int			GetNodes_T(){return m_nNodes_T;};			// for Tensor Product
	void		SetNodes_T(int n){m_nNodes_T = n;};			// for Tensor Product
	int			GetPrimaryDir(){return m_nPrimaryDir;}; // lofting Curve Direction
	void		SetPrimaryDir(int i){m_nPrimaryDir = i;}; // lofting Curve Direction
	CDrCurve*	GetBlendCurve(){return m_pBlendCurve;};	// for lofting
	void		SetBlendCurve(CDrCurve* c){m_pBlendCurve = c;};
	CDrCurve*	GetBlendCurve_U(){return m_pBlendCurve_U;};	// for Tensor Product
	void		SetBlendCurve_U(CDrCurve* c){m_pBlendCurve_U = c;};
	CDrCurve*	GetBlendCurve_V(){return m_pBlendCurve_V;};	// for Tensor Product
	void		SetBlendCurve_V(CDrCurve* c){m_pBlendCurve_V = c;};
	CDrCurve*	GetBlendCurve_W(){return m_pBlendCurve_W;};	// for Tensor Product:TRIANGULAR
															// also Solid
	void		SetBlendCurve_W(CDrCurve* c){m_pBlendCurve_W = c;};
	////
	CDListMgr* 	GetVCurveList(){return	&m_VCurveList;};
	//////////////////////////////////////////////////
    CDListMgr*	GetCurveList_U(){return &m_CurveList_U;};	// for GordonTypeInput
    CDListMgr*	GetCurveList_V(){return &m_CurveList_V;};
    CDListMgr*	GetCurveList_W(){return &m_CurveList_W;};	// TRIANGULAR
    CList<CURVELATCH,CURVELATCH>*	GetCurveLatchList_U(){return &m_CurveLatchList_U;};
    CList<CURVELATCH,CURVELATCH>*	GetCurveLatchList_V(){return &m_CurveLatchList_V;};
    CList<CURVELATCH,CURVELATCH>*	GetCurveLatchList_W(){return &m_CurveLatchList_W;};// TRIANGULAR
																					   // also Solid
	/////////////////////////
	BOOL							IsAdvancedEnd_U(){return m_bAdvancedEnd_U;};
	void							SetAdvancedEnd_U(BOOL b){m_bAdvancedEnd_U = b;};
	PWMAT2							GetCornerTwist_U(){return m_pCornerTwist_U;};// it is full,if TW_USER
	void							SetCornerTwist_U(PWMAT2 p){m_pCornerTwist_U = p;};// it is full,if TW_USER
	TWIST							GetTwistMethod_U(){return m_TwistMethod_U;};
	void							SetTwistMethod_U(TWIST t){m_TwistMethod_U = t;};
	////
	BOOL							IsAdvancedEnd_V(){return m_bAdvancedEnd_V;};
	void							SetAdvancedEnd_V(BOOL b){m_bAdvancedEnd_V = b;};
	PWMAT2							GetCornerTwist_V(){return m_pCornerTwist_V;};// it is full,if TW_USER
	void							SetCornerTwist_V(PWMAT2 p){m_pCornerTwist_V = p;};// it is full,if TW_USER
	TWIST							GetTwistMethod_V(){return m_TwistMethod_V;};
	void							SetTwistMethod_V(TWIST t){m_TwistMethod_V = t;};
	////
    CList<BLENDEND,BLENDEND>*		GetEndList_U(){return &m_EndList_U;};
    CList<BLENDEND,BLENDEND>*		GetEndList_V(){return &m_EndList_V;};
	////////
    CList<int,int>*					GetElperSegList_T(){return &m_ElperSegList_T;};		
	//////////////////////////////////////////////////////////////////////
	// not used anywhere other than MMgr_SOL(To be taken Out Later)
	CString	GetCurveID(int index){return m_CurveID[index];};
	void	SetCurveID(CString id,int index)
						{m_CurveID[index] = id;};
	////////////////////////////////////////////////////////////////////// Bndry Curves
	CDrCurve*	GetBndryCurve(int index){return m_pBndryCurves[index];};
	void		SetCurve(CDrCurve* pC,int index)
						{m_pBndryCurves[index] = pC;};
	//////////////////////////////////////////////////////////////////////
	CURVELATCH	GetCurveLatch(int index){return m_CuLatch[index];};
	void		SetCurveLatch(CURVELATCH id,int index)
						{m_CuLatch[index] = id;};
//////////////////////////////////////////////////
	CDrNode*	GetFromIDNode_T(){return m_pFromIDNode_T;};
	void 		SetFromIDNode_T(CDrNode* dat){m_pFromIDNode_T = dat;};
	CDrNode*	GetToIDNode_T(){return m_pToIDNode_T;};
	void 		SetToIDNode_T(CDrNode* dat){m_pToIDNode_T = dat;};
//	CString	GetFromID_T(){return m_FromID_T;};
//	void	SetFromID_T(CString id){m_FromID_T = id;};
//	CString	GetToID_T(){return m_ToID_T;};
//	void	SetToID_T(CString id){m_ToID_T = id;};
	pWORLD	GetFromPtLocal_T(){return &m_FromPtLocal_T;};
	void	SetFromPtLocal_T(WORLD vPt){m_FromPtLocal_T = vPt;};
	pWORLD	GetToPtLocal_T(){return &m_ToPtLocal_T;};
	void	SetToPtLocal_T(WORLD vPt){m_ToPtLocal_T = vPt;};
	pWORLD	GetFromPtWorld_T(){return &m_FromPtWorld_T;};
	void	SetFromPtWorld_T(WORLD vPt){m_FromPtWorld_T = vPt;};
	pWORLD	GetToPtWorld_T(){return &m_ToPtWorld_T;};
	void	SetToPtWorld_T(WORLD vPt){m_ToPtWorld_T = vPt;};
	pWORLD	GetFromPtEye_T(){return &m_FromPtEye_T;};
	void	SetFromPtEye_T(WORLD vPt){m_FromPtEye_T = vPt;};
	pWORLD	GetToPtEye_T(){return &m_ToPtEye_T;};
	void	SetToPtEye_T(WORLD vPt){m_ToPtEye_T = vPt;};
	pWORLD	GetAxis_T(){return &m_vAxis_T;};
	void	SetAxis_T(WORLD vAxis){m_vAxis_T = vAxis;};
	int		GetExtruType_T(){return m_nExtruType_T;};
	void	SetExtruType_T(int nSegs){m_nExtruType_T = nSegs;};
	double	GetLength_T(){return m_dLen_T;};
	void	SetLength_T(double dLen){m_dLen_T = dLen;};
	////////////////////////////////////////////////////////////////// for Type 2 Input
	WORLD	GetWorldLength_T(){return m_wLen_T;};
	void	SetWorldLength_T(WORLD wLen){m_wLen_T = wLen;};
	//////////////////////////////////////////////////////////////////
	int		GetSegs_T(){return m_nSegs_T;};
	void	SetSegs_T(int nSegs){m_nSegs_T = nSegs;};
	////////////////////////////////////////////////////////////////// Rotation
	BOOL		IsAxisInput_T(){return m_bAxis_T;};	// if Axis Input
	void		SetAxisInput_T(BOOL b){m_bAxis_T = b;};	// Set if Axis Input
	int			GetAxisType_T(){return m_nAxis_T;};		// 1=X/2=Y/3=Z
	void		SetAxisType_T(int a){m_nAxis_T = a;};		// 1=X/2=Y/3=Z
	BOOL		IsNegative_T(){return m_bNegative_T;};
	void		SetNegative_T(BOOL b){m_bNegative_T = b;};
	CIRCLETYPE	GetCircleType_T(){return m_CircleType_T;};
	void		SetCircleType_T(CIRCLETYPE c){m_CircleType_T = c;};
	//////
	double	GetAng_1_T(){return m_dAng_1_T;};
	void	SetAng_1_T(double dAng){m_dAng_1_T = dAng;};
	double	GetAng_2_T(){return m_dAng_2_T;};
	void	SetAng_2_T(double dAng){m_dAng_2_T = dAng;};
	//////////////////////////////////////////////////////////////////
	PATCHPROC 	GetPatchProc(){return m_PatchProc;};
	void		SetPatchProc(enum PATCHPROC kind)
							{m_PatchProc = kind;};
	PATCHTYPE 	GetPatchType(){return m_PatchType;};
	void		SetPatchType(enum PATCHTYPE kind)
							{m_PatchType = kind;};
	PATSUBTYPE 	GetPatSubType(){return m_PatSubType;};
	void		SetPatSubType(enum PATSUBTYPE kind)
							{m_PatSubType = kind;};
    ///////////////////////////////////////////////////////
	int  	GetOut_S(){return m_nOut_S;};
	void  	SetOut_S(int nOut){m_nOut_S = nOut;};
	int  	GetOut_T(){return m_nOut_T;};
	void  	SetOut_T(int nOut){m_nOut_T = nOut;};
	///////////////////////////////////////////////////
	long	GetTotalElems(){return m_nTotElems;};
	void	SetTotalElems(long nMax){m_nTotElems = nMax;};
 	//////////////////////////////////////////////////////////
	virtual void 	Calc_PolyNormalWorld();
	virtual void 	TransformPolyNormalToEye(pMATRIX pViewM);
	virtual void 	ProjectPolyNormalToScreen3D
						(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 	Calc_NodeNormalWorld();
	virtual void 	Calc_NodeNormalEye();
	virtual void 	Calc_NodeNormalScreen3D();
	///////////////////////////////////////////////////////////////////////////////////// Triangle 
	int 	Generate_Patch3(pWORLD pOut, pDOUBLE pOutWts);	// Triangular Patches
	int		Generate_Tangent3(pWORLD pOut,int nDir);	// Triangular Patches
	int		Generate_Tangent3(pWORLD pOut_S,int nDir_1,pWORLD pOut_T,int nDir_2);	// Triangular Patches
	int 	Generate_Normal3(pWORLD pOut);					// Triangular Patch Normals
																	//		Tangents ALREADY Known
	int		Generate_Tangents_N_Normal3(pWORLD pOut);		// Quadrilateral Patch Normals
	int		Get_Tan_N_NorAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
//																	WORLD& Normal);	
													WORLD& Normal,double dSameNessRatio);
//	int		Get_TangentsAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V);	
	int		Get_TangentsAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,	
																double dSameNessRatio);
//	int		Get_A_Tan_AtaNode_3(WORLD wNodeCoord,WORLD& Tangent,int& DirTan);	
	int		Get_A_Tan_AtaNode_3(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,	
														double dSameNessRatio);
	///////////////////////////////////////////////////////////////////////////////////// Quadrilateral
	int		GetAPointOnCurrentBezSeg_4(int nOut_S,int nOut_T,pWORLD pOut,pDOUBLE pOutWt);
	int		GetCurrentBezSeg_N_st_4(int nOut_S,int nOut_T,int& nCurBz_S,int& nCurBz_T,
									  double& sCur,double& tCur);
	int 	Generate_Patch4(pWORLD pOut, pDOUBLE pOutWts);	
	int		Generate_Tangent4(pWORLD pOut, int nDir);		
	int 	Generate_Normal4(pWORLD pOut);					
	int		Generate_Tangents_N_Normal4(pWORLD pOut);		
	int		Get_Tan_N_NorAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
//																	WORLD& Normal);	
													WORLD& Normal,double dSameNessRatio);
//	int		Get_TangentsAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V);	
	int		Get_TangentsAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,	
																double dSameNessRatio);
//	int		Get_A_Tan_AtaNode_4(WORLD wNodeCoord,WORLD& Tangent,int& DirTan);	
	int		Get_A_Tan_AtaNode_4(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,	
														double dSameNessRatio);
	///////
	pWORLD	GetPtrTangents_S(){return m_pTangents_S;};
	pWORLD	GetPtrTangents_T(){return m_pTangents_T;};
	pWORLD	GetPtrNormals(){return m_pNormals;};
	pWORLD	GetPtrTwists(){return m_pTwists;};
	//////////////////////////////////////////
	virtual pWORLD 	GetMemIn(int index){return m_pIn_S[index];};
	//////////////
	virtual void 	SetMemIn(pWORLD pIn,int index){m_pIn_S[index] = pIn;};
	virtual void 	SetMemIn(pWORLD pIn){m_pIn = pIn;};
	virtual void 	SetMemInDP(POINT* pInDP){m_pInDP = pInDP;};
	virtual void 	SetMemOut(pWORLD pOut){m_pOut = pOut;};
	virtual void 	SetMemOutDP(POINT* pOutDP){m_pOutDP = pOutDP;};
	////////////////////////////////////////////////////////////// interpolation
	BOOL		IsUniform_T(){return m_bUniform_T;};		// Output Distribution:
	void		SetUniform_T(BOOL a){ m_bUniform_T = a;};		// Output Distribution:
	int 		GetClass_T(){return m_Class_T;};
	void 		SetClass_T(int nOrd){m_Class_T = nOrd;};
	int 		GetOrder_T(){return m_nOrder_T;};
	void 		SetOrder_T(int nOrd){m_nOrder_T = nOrd;};
	int			GetnDim_T(){return m_nDim_T;}; 			
	void		SetnDim_T(int bs){m_nDim_T = bs;}; 		
	PATCHOUTPUT	GetOutMethod_T(){return m_OutMethod_T;};	// Output Method
	void		SetOutMethod_T(PATCHOUTPUT a){ m_OutMethod_T = a;};	// Output Method
	int			GetMaxOutSeg_T(){return m_nMaxOutSeg_T;};	// Number of Output Segments on ENTIRE Curve
	void		SetMaxOutSeg_T(int a){m_nMaxOutSeg_T = a;};	// Number of Output Segments on ENTIRE Curve
	pINT		GetNum_tPointer_T(){return m_pNum_t_T;};	// Number of Outputs for each Output Segment
	void		SetNum_tPointer_T(pINT a){m_pNum_t_T =a;};	// Number of Outputs for each Output Segment
	pDOUBLE		GetDis_tPointer_T(){return m_pDis_t_T;};	// Number of Outputs for each Output Segment
	void		SetDis_tPointer_T(pDOUBLE a){m_pDis_t_T =a;};	// Number of Outputs for each Output Segment
	pINT		GetNum_tPointer_Ex_T(){return m_pNum_t_Ex_T;};	// Output t-distribution array:
	void		SetNum_tPointer_Ex_T(pINT a){m_pNum_t_Ex_T = a;};	// Output t-distribution array:
	pDOUBLE		GetDis_AngPointer_T(){return m_pDis_Ang_T;};	// Distribution of angles 
	void		SetDis_AngPointer_T(pDOUBLE a){m_pDis_Ang_T =a;};	// Distribution of angles 
/*
	int 		GetData_T(){return m_nData_T;};
	void 		SetData_T(int ndat){m_nData_T = ndat;};
	KNOT		GetKnotType_T(){return m_KnotType_T;};
	void		SetKnotType_T(KNOT Kn){m_KnotType_T = Kn;};
	WEIGHT		GetWtType_T(){return m_WtType_T;};
	void		SetWtType_T(WEIGHT W){m_WtType_T = W;};
	BOUNDARY	GetBCL_T(){return m_BCL_T;};
	void		SetBCL_T(BOUNDARY bc){m_BCL_T = bc;};
	BOUNDARY	GetBCR_T(){return m_BCR_T;};
	void		SetBCR_T(BOUNDARY bc){m_BCR_T = bc;};
	VECTOR		GetTanL_T(){return m_TanL_T;};
	void		SetTanL_T(VECTOR T){m_TanL_T = T;};
	VECTOR		GetTanR_T(){return m_TanR_T;};
	void		SetTanR_T(VECTOR T){m_TanR_T = T;};
	int			GetnCon_BS_T(){return m_nCon_BS_T;}; 			
	void		SetnCon_BS_T(int bs){m_nCon_BS_T = bs;}; 		
	int			GetnCon_BZ_T(){return m_nMaxCNodes_T;};		// m_nMaxCNodes_T 			
	void		SetnCon_BZ_T(int bs){m_nMaxCNodes_T = bs;}; 		
	int			GetnMKnots_T(){return m_nMKnots_T;}; 			
	void		SetnMKnots_T(int bs){m_nMKnots_T = bs;}; 		
	int			GetnKnots_T(){return m_nKnots_T;}; 			
	void		SetnKnots_T(int bs){m_nKnots_T = bs;}; 		
	////////////////////// Memory for Interpolation
	pDOUBLE		GetpMKnots_T(){return m_pMKnots_T;};			//---|	
	void		SetpMKnots_T(pDOUBLE p){m_pMKnots_T = p;};	//---|	 THESE ACTUALLY
	pDOUBLE		GetpWts_BS_T(){return m_pWts_BS_T;};		//---|-- WE DO NOT NEED, OUR	
	void		SetpWts_BS_T(pDOUBLE p){m_pWts_BS_T = p;};	//---|   INTERNAL REPRESENTATION:
//	pWORLD		GetpCon_BS_T(){return m_pCon_BS_T;};		//---|   ALWAYS - B E Z I E R	
//	void		SetpCon_BS_T(pWORLD p){m_pCon_BS_T = p;};	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		GetpKnots_T(){return m_pKnot_T;};				// User Need	
	void		SetpKnots_T(pDOUBLE p){m_pKnot_T = p;};
	pDOUBLE		GetpWts_DT_T(){return m_pWts_DT_T;};			// User Need	
	void		SetpWts_DT_T(pDOUBLE p){m_pWts_DT_T = p;};
	pDOUBLE		GetpWts_BZ_T(){return m_pWts_BZ_T;};			// Rational Need		
	void		SetpWts_BZ_T(pDOUBLE p){m_pWts_BZ_T = p;};
//	pWORLD		GetpCon_BZ_T(){return m_pCon_BZ_T;};			// stored in CNodeList	
//	void		SetpCon_BZ_T(pWORLD p){m_pCon_BZ_T = p;};
*/
	//////////////////////////////////////////////////////////////////// CONICS
	int 		GetData_Ex_T(){return m_nData_Ex_T;};
	void 		SetData_Ex_T(int ndat){m_nData_Ex_T = ndat;};
	BOOL		IsExpanded_T(){return m_bExpanded_T;};		// Output Distribution:
	void		SetExpanded_T(BOOL a){ m_bExpanded_T = a;};		// Output Distribution:
	int			GetMaxENodes_T(){return m_nMaxENodes_T;};	
	void		SetMaxENodes_T(int nMax){m_nMaxENodes_T = nMax;};
	double 		GetRadius_T(){return m_Radius_T;};
	void 		SetRadius_T(double dat){m_Radius_T = dat;};
	double 		GetTheta_T(){return m_Theta_T;};
	void 		SetTheta_T(double dat){m_Theta_T = dat;};
	WORLD 		GetCenter_T(){return m_Center_T;};
	void 		SetCenter_T(WORLD dat)
						{	m_Center_T.x = dat.x;
							m_Center_T.y = dat.y;
							m_Center_T.z = dat.z;
						};
	WORLD 		GetNormal_T(){return m_Normal_T;};
	void 		SetNormal_T(WORLD dat)
						{	m_Normal_T.x = dat.x;
							m_Normal_T.y = dat.y;
							m_Normal_T.z = dat.z;
						};
	double 		GetSegAngle_T(){return m_SegAngle_T;};
	void 		SetSegAngle_T(double dat){m_SegAngle_T = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		IsHole_T(){return m_bHole_T;};
	void		SetHole_T(BOOL bYes){m_bHole_T = bYes;};
	//////////////////////////////////////////////////////////////////// Derivatives
	pWORLD	GetpTangents_T(){return m_pTangents_T;};
	void	SetpTangents_T(pWORLD t){m_pTangents_T = t;};
	pDOUBLE	GetpCurvatures_T(){return m_pCurvatures_T;};
	void	SetpCurvatures_T(pDOUBLE t){m_pCurvatures_T = t;};
    //////////////////////////////////////////////////////////////////// Output
    double	GetRatio_T(){return m_Ratio_T;};		// for OneSegment Linear Only
    void	SetRatio_T(double r){m_Ratio_T = r;};	// for OneSegment Linear Only
	////////////////////////////////////////////////////////////// for Duct/Sweep
	int		GetTwistType_T(){return m_nTwistType_T;};
	void	SetTwistType_T(int nSegs){m_nTwistType_T = nSegs;};
	CList<double,double>* 
			GetTwistList_T(){return &m_TwistList_T;};
	int		GetScaleType_T(){return m_nScaleType_T;};
	void	SetScaleType_T(int nSegs){m_nScaleType_T = nSegs;};
	CList<double,double>* 
			GetScaleList_T(){return &m_ScaleList_T;};
	//////////////////
	BOOL	IsIncTwist_T(){return m_bIncTwist_T;};
	void	SetIncTwist_T(BOOL dLen){m_bIncTwist_T = dLen;};
	double	GetTwistMult_T(){return m_TwistMult_T;};
	void	SetTwistMult_T(double dLen){m_TwistMult_T = dLen;};
	double	GetTwistStart_T(){return m_TwistStart_T;};
	void	SetTwistStart_T(double dLen){m_TwistStart_T = dLen;};
	BOOL	IsIncScale_T(){return m_bIncScale_T;};
	void	SetIncScale_T(BOOL dLen){m_bIncScale_T = dLen;};
	double	GetScaleMult_T(){return m_ScaleMult_T;};
	void	SetScaleMult_T(double dLen){m_ScaleMult_T = dLen;};
	double	GetScaleStart_T(){return m_ScaleStart_T;};
	void	SetScaleStart_T(double dLen){m_ScaleStart_T = dLen;};
	////////////////////////////////////////////////////////////// for Duct/Sweep:Type2
	WORLD	GetWorldTwistMult_T(){return m_wTwistMult_T;};
	void	SetWorldTwistMult_T(WORLD dLen){m_wTwistMult_T = dLen;};
	WORLD	GetWorldTwistStart_T(){return m_wTwistStart_T;};
	void	SetWorldTwistStart_T(WORLD dLen){m_wTwistStart_T = dLen;};
	WORLD	GetWorldScaleMult_T(){return m_wScaleMult_T;};
	void	SetWorldScaleMult_T(WORLD dLen){m_wScaleMult_T = dLen;};
	WORLD	GetWorldScaleStart_T(){return m_wScaleStart_T;};
	void	SetWorldScaleStart_T(WORLD dLen){m_wScaleStart_T = dLen;};
	///////////////////////////////////////////////////////////////////// Triangular Patch
    virtual	CDListMgr*	GetTriangleList(){return &m_TriangleList;};
	int			GetnOutGlo_S(){return m_nOutGlo_S;};	
	void		SetnOutGlo_S(int nMax){m_nOutGlo_S = nMax;};
	///////////////////////////////////////////////////////////////////// Mesh
	BOOL 		CullWorld(WORLD VDir);
	BOOL 		CullScreen(pMATRIX pViewM);
	/////////////////////////////////////////////////////////////////////
	BOOL		IsGenBCurve(){return m_bGenBCurve;};		// bndry Curve
	void		SetGenBCurve(BOOL a){ m_bGenBCurve = a;};	// bndry Curve:



protected:
	
	BOOL	IsObjectBndryHit_4(int nNet,POINT point,int& iBndry);
	BOOL	IsObjectBndryHit_3(int nNet,POINT point,int& iBndry);
	int		Collect_BoundaryPoints_4(int iBndry,pWORLD pOut,POINT* pOutDP);
	////////////////////
	BOOL	IsObjectHit_Alt_4(int nNet,POINT point);
	BOOL	IsObjectHit_Alt_3(int nNet,POINT point);
	void	IsObjectHit_YScanLineWidth(POINT n1,POINT n2,POINT point,
										  int& nMinX,int& nMaxX);
	int		ObjectHit_Generate2DPts();
	///
	BOOL	IsObjectHit_4(int nNet,POINT point);
	int		Collect_BoundaryPoints_4(int iBndry);
	BOOL	IsObjectHit_3(int nNet,POINT point);
	int		Collect_BoundaryPoints_3(int iOutGlo_ST,int jOutGlo_ST,int nType);
	void	TRIANGLE_1_Bndry(pWORLD pOut,int iOutGlo_ST,int jOutGlo_ST);
	void	TRIANGLE_2_Bndry(pWORLD pOut,int iOutGlo_ST,int jOutGlo_ST);
	/////////////////////////////////////////////
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
	///////////////////////////////////// DirtyDraw				
	void 	UnitAxisFromEndNodes();
//	void 	RefillCNEyePosForDirtyDraw();
//	void 	ProjectForDirtyDraw
//				(pMATRIX pvv3DM,double dScale_U,double dScale_V);
		          

			
// Helper functions
protected:
// Attributes
 
	CDrCurve*	m_pBndryCurves[4];		// Rectangular = 4/ Triangular = 3
	//////////////////////////////
	BOOL		m_bGenBCurve;			// bndry Curve
	int			m_Class_T;				// 0=C0,1=C1,2=C2
	/////////////////////////
//  already in Curve
//	int			m_nCompoType;			// Triangle/Rect(2D) for patch
										// Cube/thk.shell(3D)for solid
	BOOL		m_bNormalDraw;					// Normal draw 
	/////////////////////////////////
	PATCHPROC	m_PatchProc;           // How Generated? PP_EXTRUDE etc
	PATCHTYPE	m_PatchType;           	// PA_TENSOR, etc
	PATSUBTYPE 	m_PatSubType;			// Tringle or Quadrilat
	CURVEPROC	m_CurveType_T;         	// PA_BEZIER, etc
	/////////////////////////////////
	int			m_nSegUnif_T;		//formerly:m_nSegments_T;	// Used Only for Triangles
	BOOL		m_bClosed_T; 
	int			m_nMaxINodes_T;
	int			m_nMaxCNodes_T;
	int			m_nMaxCurves_T;			// Formaerly: m_nMaxCubicPatches_T;   // No. of Curves
	int			m_nPatchObjectType;		// ObjectType to create; -1 = no creation reqd
	//////////////////////////////////////// Construction Help
	int			m_nNodes_S;			// for Tensor Product
	int			m_nNodes_T;
	/////////////////////////////
	int			m_nPrimaryDir;		// lofting Curve Direction
	CDrCurve*	m_pBlendCurve;		// for lofting
	CDrCurve*	m_pBlendCurve_U;		// for Tensor Product
	CDrCurve*	m_pBlendCurve_V;		// for Tensor Product
	CDrCurve*	m_pBlendCurve_W;		// for Tensor Product: TRIANGULAR
	/////////////////////////////
	CDListMgr	m_VCurveList;       // Virtual Curves: Internally generated
	/////////////////////////////////
	CDListMgr	m_CurveList_U;       // Curves in u // for GordonType Input
	CDListMgr	m_CurveList_V;       // Curves in v
	CDListMgr	m_CurveList_W;       // Curves in w for Triangle Patches
	CList<CURVELATCH,CURVELATCH>	m_CurveLatchList_U;       // Curves in u // for GordonType Input
	CList<CURVELATCH,CURVELATCH>	m_CurveLatchList_V;       // Curves in v // for GordonType Input
	CList<CURVELATCH,CURVELATCH>	m_CurveLatchList_W;       // Curves in w for Triangle Patches
	////
	BOOL							m_bAdvancedEnd_V;
	PWMAT2							m_pCornerTwist_V;// it is full,if TW_USER
	TWIST							m_TwistMethod_V;
	////
	BOOL							m_bAdvancedEnd_U;
	PWMAT2							m_pCornerTwist_U;// it is full,if TW_USER
	TWIST							m_TwistMethod_U;
	////
    CList<BLENDEND,BLENDEND>		m_EndList_U;
    CList<BLENDEND,BLENDEND>		m_EndList_V;
	///////////////////////////////////////////////////////////////////////
	CString		m_CurveID[4];      	// XSec etc
	CDrCurve*	m_pCurve[4];
	CURVELATCH	m_CuLatch[4];      	// Latching
	int			m_nSegs_T;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	WORLD 		m_FromPtLocal_T;		// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtWorld_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtEye_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtLocal_T;			// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtWorld_T;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtEye_T;		// used also for Sweep/Duct Anchor
	///////////////////////////
	int			m_nExtruType_T;
	double		m_dLen_T;
	WORLD		m_wLen_T;		// for Type 2 Input

	double		m_dLenEye_T;
	WORLD		m_wLenEye_T;
	WORLD		m_vAxis_T;		// unit Extrusion Axis/XFormed
	WORLD		m_vAxisEye_T;		// unit Extrusion Axis/XFormed
	/////////////////////
//	CString		m_FromID_T;		// also used:AnchorID for Sweep/Duct
//	CString		m_ToID_T;
	CDrNode*	m_pFromIDNode_T;		// also used:AnchorID for Sweep/Duct
	CDrNode*	m_pToIDNode_T;
	/////////////////////////////////////////// Rotate
	BOOL		m_bAxis_T;	// if Axis Input
	int			m_nAxis_T;		// 1=X/2=Y/3=Z
	BOOL		m_bNegative_T;
	CIRCLETYPE	m_CircleType_T;
	double		m_dAng_1_T;
	double		m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	int			m_nTwistType_T;	//1 = Distribution
								//2	= Increment; double Type
								//3 = IsoParametric: World Type 
	int			m_nScaleType_T;	//1 = Distribution
								//2	= Increment; double Type
								//3 = IsoParametric: World Type 
	CList<double,double>
				m_TwistList_T;
	CList<double,double>
				m_ScaleList_T;
	///////////////////////////
	BOOL		m_bIncTwist_T;	// Incremental?
	BOOL		m_bIncScale_T;	// for Sweep
	double		m_TwistMult_T;
	double		m_ScaleMult_T;	// for Sweep
	double		m_TwistStart_T;
	double		m_ScaleStart_T;	// for Sweep
	////////////////////////////////////////
	int			m_nOut_S;	//	number of generated Patch vertices in U dir	
	int			m_nOut_T;	//	number of generated Patch vertices in V dir	
	/////////////////////////////////////////// Duct/Sweep	: For Iso Parametric
	WORLD		m_wTwistMult_T;
	WORLD		m_wScaleMult_T;	// for Sweep
	WORLD		m_wTwistStart_T;
	WORLD		m_wScaleStart_T;	// for Sweep
    ////////////////////////////////////// Memory
	pWORLD		m_pIn_S[4];	// XSec etc Control Pointers
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
	pWORLD		m_pNormals;				// Normals
	pWORLD		m_pTwists;				// Twists
	pDOUBLE		m_pCurvatures_T;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    double		m_Ratio_T;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	CDListMgr	m_TriangleList;       // Triangles
	//////////////////////////////  Globals:
	int			m_nOutGlo_S;			//  Total Output in each side of entire Base Patch
	CList<int,int> m_ElperSegList_T; // for edit purpose etc.

public:
	virtual ~CDrPatch();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



