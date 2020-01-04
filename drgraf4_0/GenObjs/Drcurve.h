// DrCurve.h : header file
//
#ifndef _DRCURVE_H_
#define _DRCURVE_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include <afxtempl.h>	// CList

#include "DrObject.h"
#include "DrNode.h"
#include "DListMgr.h"
#include "MatObj.h"
#include "Def_CuPS.h"	// enum CURVETYPE			
#include "Str_Supp.h"	// Support data			
#include "Str_StaL.h"	// Static  data			

//#pragma warning( disable : 4200 )
/////////////////////////////////////////////////////////////////////////////
// CDrCurve    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrCurve: public CDrObject
{
public:
// Construction                 
	CDrCurve();
//////////////////////////////////////
	DECLARE_SERIAL(CDrCurve);
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
	virtual BOOL		IsDirty(){return m_bDirty;};							
	virtual void		SetDirty(BOOL bDirty){m_bDirty = bDirty;};							
	virtual BOOL		IsControlShapeNeeded(){return m_bControlDraw;};							
	virtual void		SetControlShapeNeed(BOOL bCSN){m_bControlDraw = bCSN;};							
	virtual BOOL		IsPosted(){return m_bPosted;};							
	virtual void		SetPosted(BOOL bP){m_bPosted = bP;};							
	//////////////////////////
	virtual void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual void 		TransformObjectToView(pMATRIX pViewM);
	virtual BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual void 		ProjectObject
							(	pMATRIX pvv3DM,
								double dScale_U,double dScale_V
							);
	//////////////////////////						
	virtual	int 		Calc_3DBoundsLocal();
	virtual BOOL		IsObjectHit(int nNet,POINT point); 		// Object Hit
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	/////////////////////////////////////////////////////////////////////////////
    CDListMgr*	GetCN_BSList(){return &m_CN_BSList;};
    CDListMgr*	GetVNodeList(){return &m_VNodeList;};
	//////////////////////////////////////////////////////////////////////						
//	virtual	int			Is2D(){return m_nMeshElemDim;};// 1D or 2D 
//	virtual	void		Set2D(BOOL bDim){m_nMeshElemDim = bDim;};					// 1D or 2D 
	int			GetMeshElemDim(){return m_nMeshElemDim;};// 1D or 2D 
	void		SetMeshElemDim(int nDim){m_nMeshElemDim = nDim;};					// 1D or 2D 
	////////////////////////////////////////////////////////////////////// Iso						
	BOOL		IsIso(){return m_bIso;};
	void		SetIso(BOOL bYes){m_bIso = bYes;};
	CString&	GetIsoToID(){return m_IsoToID;};
	void		SetIsoToID(CString& id){m_IsoToID = id;};
	//////////////////////////////////////////////////////////////////////
	int			GetCompoType(){return m_nCompoType;};
	void		SetCompoType(int CT){m_nCompoType = CT;};
	CString&	GetCompoID(){return m_CompoID;};
	void		SetCompoID(CString& id){m_CompoID = id;};
	 int 		AppendToObject
						(	
							CDListMgr* pSolidList,
							CDListMgr* pObj3DList,
							CDListMgr* pElemList, 
							CDListMgr* pNodeList,
							CDListMgr* pCNodeList,
							CDListMgr* pINodeList,
							CDListMgr* pVNodeList,
							CDListMgr* pCProfList,
							CDListMgr* pPatchList
						);
	////////////////////////////////////////////////////////////////////
	int			GetClass_S(){return m_Class_S;};
	void		SetClass_S(int c){m_Class_S = c;};
	///////////////////////////////////////////////////////////////////// Used Only for Triangles
//	int			GetSegmentCount_S(){return m_nSegUnif_S;};
//	void		SetSegmentCount_S(int nSegs){m_nSegUnif_S = nSegs;};
	int			GetOutSegUnif_S(){return m_nSegUnif_S;};	// originally	GetSegmentCount_T
	void		SetOutSegUnif_S(int nSegs){m_nSegUnif_S = nSegs;};	//		SetSegmentCount_T
	//////////////////////////////////////////////////////////////////////////////////////////////
	BOOL		IsClosed_S(){return m_bClosed_S;};
	void		SetClosed_S(BOOL bYes){m_bClosed_S = bYes;};
	int			GetCurveObjectType(){return m_nCurveObjectType;};
	void		SetCurveObjectType(int nType){m_nCurveObjectType = nType;};
	int			GetMaxINodes_S(){return m_nMaxINodes_S;};
	void		SetMaxINodes_S(int nMax){m_nMaxINodes_S = nMax;};
	int			GetMaxCNodes_S(){return m_nMaxCNodes_S;};
	void		SetMaxCNodes_S(int nMax){m_nMaxCNodes_S = nMax;};
	///////////////////////////////////////////////////////////////////////////
//	int			GetMaxCubicCurves(){return m_nMaxCurves_S;};
//	void		SetMaxCubicCurves(int nMax){m_nMaxCurves_S = nMax;};
	int			GetMaxBezSegments_S(){return m_nMaxCurves_S;};
	void		SetMaxBezSegments_S(int nMax){m_nMaxCurves_S = nMax;};
	///////////////////////////////////////////////////////////////////////////
	int			GetMaxOutPts_S(){return m_nMaxOutPts_S;};
	void		SetMaxOutPts_S(int nMax){m_nMaxOutPts_S = nMax;};
	long		GetLongOutPts(){return m_nOut;};
	void		SetLongOutPts(long nOut){m_nOut = nOut;};
	CURVEPROC 	GetCurveType_S(){return m_CurveType_S;};
	void		SetCurveType_S(CURVEPROC kind){m_CurveType_S = kind;};
    //////////////////////////////////////////////////////////////
	int 		NumberOfCurves(enum CURVEPROC kind,int nMaxCurveCNodes,
										int* pnCurves,BOOL bClosed,int nOrder);
	int 		GenerateCurve(pWORLD pOut, pDOUBLE pOutWts);
			// 
	CURVEOUTPUT		GetOutMethod(){return m_OutMethod_S;};	// Output Method
	double			GetAlfa(){return m_alfa_S;};			// Cardinal Spline (Catmull-Rom Modified)	
	double			GetBias(){return m_bias_S;};			// beta
	double			GetTension(){return m_tension_S;};		// beta and hermite
//	int				GetNumOfKnot(){return m_nKnot_S;};		// number of KNOTs == number of Curves+1		
//	pDOUBLE			GetInKnotPointer(){return m_pInKnot_S;};	// Total input KNOT Value Array
//	pWORLD			GetOutKnotPointer(){return m_pOutKnot_S;};	// Total Output KNOT Points Array (for drawing)
    ///////////////////////////////////////////////////////
	BOOL			IsUniform_S(){return m_bUniform_S;};		// Output Distribution:
	void			SetUniform_S(BOOL a){ m_bUniform_S = a;};		// Output Distribution:
	void			SetOutMethod_S(CURVEOUTPUT a){ m_OutMethod_S = a;};	// Output Method
	int				GetMaxOutSeg_S(){return m_nMaxOutSeg_S;};		// Number of Output Segments on ENTIRE Curve
	void			SetMaxOutSeg_S(int a){m_nMaxOutSeg_S = a;};		// Number of Output Segments on ENTIRE Curve
	pDOUBLE			GetDis_AngPointer_S(){return m_pDis_Ang_S;};	// Distribution of angles 
	void			SetDis_AngPointer_S(pDOUBLE a){m_pDis_Ang_S =a;};	// Distribution of angles 
	pINT			GetNum_tPointer_S(){return m_pNum_t_S;};		// Number of Outputs for each Output Segment
	void			SetNum_tPointer_S(pINT a){m_pNum_t_S =a;};		// Number of Outputs for each Output Segment
	pDOUBLE			GetDis_tPointer_S(){return m_pDis_t_S;};	// Number of Outputs for each Output Segment
	void			SetDis_tPointer_S(pDOUBLE a){m_pDis_t_S =a;};	// Number of Outputs for each Output Segment
	pINT			GetNum_tPointer_Ex_S(){return m_pNum_t_Ex_S;};	// Output t-distribution array:
	void			SetNum_tPointer_Ex_S(pINT a){m_pNum_t_Ex_S = a;};	// Output t-distribution array:
	int				GetnBSeg_Ex_S(){return m_nBSeg_Ex_S;};
	void			SetnBSeg_Ex_S(int b){m_nBSeg_Ex_S  = b;};;
	pINT			GetBSegPointer_Ex_S(){return m_pBSeg_Ex_S;};		// # BezSegment between a pair of DataPts (Conics)
	void			SetBSegPointer_Ex_S(pINT a){m_pBSeg_Ex_S =a;};	// # BezSegment between a pair of DataPts (Conics)
    ///////////////////////////////////////////////////////
	void			SetAlfa(double a){ m_alfa_S = a;};			// Cardinal Spline (Catmull-Rom Modified)	
	void			SetBias(double a){ m_bias_S = a;};			// beta
	void			SetTension(double a){ m_tension_S = a;};	// beta and hermite
	////////////////////////////////////////////////////////////////////////// memory																							
	pWORLD			GetMemIn(){return m_pIn;};
	pDOUBLE			GetMemInWts(){return m_pInWts;};
	POINT*			GetMemInDP(){return m_pInDP;};
	pWORLD			GetMemOut(){return m_pOut;};
	pDOUBLE			GetMemOutWts(){return m_pOutWts;};
	POINT*			GetMemOutDP(){return m_pOutDP;};
	void			SetMemIn(pWORLD pMem){m_pIn = pMem;};
	void			SetMemInWts(pDOUBLE pMem){m_pInWts = pMem;};
	void			SetMemInDP(POINT* pMem){m_pInDP = pMem;};
	void			SetMemOut(pWORLD pMem){m_pOut = pMem;};
	void			SetMemOutWts(pDOUBLE pMem){m_pOutWts = pMem;};
	void			SetMemOutDP(POINT* pMem){m_pOutDP = pMem;};
	/////////////////////////////////////////////////// Memory						
	pDOUBLE			FixMemD(long nOut)
								{
									pDOUBLE pOut;
									return ((pOut = new double[nOut]) == NULL)? (pDOUBLE)NULL:pOut;
								};
	
	void 			FreeMemD(pDOUBLE pOut){delete[] pOut;};
	/////////////////////////
	pWORLD 			FixMem(long nOut)
								{
									pWORLD pOut;
									return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
								};
	
	void 			FreeMem(pWORLD pOut){delete[] pOut;};
	/////////////////////////
	POINT* 			FixMemDP(long nOut)
				{
					POINT* pOut;
					return ((pOut = new POINT[nOut]) == NULL)? (POINT*)NULL:pOut;
				};
	
	void 	FreeMemDP(POINT* pOut){delete[] pOut;};
	//////////////////////////////////////////
	void 	RefillCNLocalPosForPosting();
	void 	RefillCNEyePosForDirtyDraw();
	////////////////////////////////////////////////////////////// interpolation
	int 		GetData_S(){return m_nData_S;};
	void 		SetData_S(int ndat){m_nData_S = ndat;};
	int 		GetOrder_S(){return m_nOrder_S;};
	void 		SetOrder_S(int nOrd){m_nOrder_S = nOrd;};
	KNOT		GetKnotType_S(){return m_KnotType_S;};
	void		SetKnotType_S(KNOT Kn){m_KnotType_S = Kn;};
	WEIGHT		GetWtType_S(){return m_WtType_S;};
	void		SetWtType_S(WEIGHT W){m_WtType_S = W;};
	BOUNDARY	GetBCL_S(){return m_BCL_S;};
	void		SetBCL_S(BOUNDARY bc){m_BCL_S = bc;};
	BOUNDARY	GetBCR_S(){return m_BCR_S;};
	void		SetBCR_S(BOUNDARY bc){m_BCR_S = bc;};
	VECTOR		GetTanL_S(){return m_TanL_S;};
	void		SetTanL_S(VECTOR T){m_TanL_S = T;};
	VECTOR		GetTanR_S(){return m_TanR_S;};
	void		SetTanR_S(VECTOR T){m_TanR_S = T;};
	int			GetnCon_BS_S(){return m_nCon_BS_S;}; 			
	void		SetnCon_BS_S(int bs){m_nCon_BS_S = bs;}; 		
	int			GetnCon_BZ_S(){return m_nMaxCNodes_S;};		// m_nMaxCNodes_S 			
	void		SetnCon_BZ_S(int bs){m_nMaxCNodes_S = bs;}; 		
	int			GetnMKnots_S(){return m_nMKnots_S;}; 			
	void		SetnMKnots_S(int bs){m_nMKnots_S = bs;}; 		
	int			GetnKnots_S(){return m_nKnots_S;}; 			
	void		SetnKnots_S(int bs){m_nKnots_S = bs;}; 		
	int			GetnDim_S(){return m_nDim_S;}; 			
	void		SetnDim_S(int bs){m_nDim_S = bs;}; 		
	////////////////////// Memory for Interpolation
	pDOUBLE		GetpMKnots_S(){return m_pMKnots_S;};			//---|	
	void		SetpMKnots_S(pDOUBLE p){m_pMKnots_S = p;};	//---|	 THESE ACTUALLY
	pDOUBLE		GetpWts_BS_S(){return m_pWts_BS_S;};		//---|-- WE DO NOT NEED, OUR	
	void		SetpWts_BS_S(pDOUBLE p){m_pWts_BS_S = p;};	//---|   INTERNAL REPRESENTATION:
//	pWORLD		GetpCon_BS_S(){return m_pCon_BS_S;};		//---|   ALWAYS - B E Z I E R	
//	void		SetpCon_BS_S(pWORLD p){m_pCon_BS_S = p;};	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		GetpKnots_S(){return m_pKnot_S;};				// User Need	
	void		SetpKnots_S(pDOUBLE p){m_pKnot_S = p;};
	pDOUBLE		GetpWts_DT_S(){return m_pWts_DT_S;};			// User Need	
	void		SetpWts_DT_S(pDOUBLE p){m_pWts_DT_S = p;};
	pDOUBLE		GetpWts_BZ_S(){return m_pWts_BZ_S;};			// Rational Need		
	void		SetpWts_BZ_S(pDOUBLE p){m_pWts_BZ_S = p;};
//	pWORLD		GetpCon_BZ_S(){return m_pCon_BZ_S;};			// stored in CNodeList	
//	void		SetpCon_BZ_S(pWORLD p){m_pCon_BZ_S = p;};
	//////////////////////////////////////////////////////////////////// CONICS
	CDrNode*	GetFromIDNode_S(){return m_pFromIDNode_S;};
	void 		SetFromIDNode_S(CDrNode* dat){m_pFromIDNode_S = dat;};
	CDrNode*	GetToIDNode_S(){return m_pToIDNode_S;};
	void 		SetToIDNode_S(CDrNode* dat){m_pToIDNode_S = dat;};
//	CString		GetFromID_S(){return m_FromID_S;};
//	void		SetFromID_S(CString id){m_FromID_S = id;};
//	CString		GetToID_S(){return m_ToID_S;};
//	void		SetToID_S(CString id){m_ToID_S = id;};
	int 		GetData_Ex_S(){return m_nData_Ex_S;};
	void 		SetData_Ex_S(int ndat){m_nData_Ex_S = ndat;};
	BOOL		IsExpanded_S(){return m_bExpanded_S;};		// Output Distribution:
	void		SetExpanded_S(BOOL a){ m_bExpanded_S = a;};		// Output Distribution:
	int			GetMaxENodes_S(){return m_nMaxENodes_S;};	
	void		SetMaxENodes_S(int nMax){m_nMaxENodes_S = nMax;};
	double 		GetRadius_S(){return m_Radius_S;};
	void 		SetRadius_S(double dat){m_Radius_S = dat;};
	double 		GetTheta_S(){return m_Theta_S;};
	void 		SetTheta_S(double dat){m_Theta_S = dat;};
	WORLD 		GetCenter_S(){return m_Center_S;};
	void 		SetCenter_S(WORLD dat)
						{	m_Center_S.x = dat.x;
							m_Center_S.y = dat.y;
							m_Center_S.z = dat.z;
						};
	WORLD 		GetNormal_S(){return m_Normal_S;};
	void 		SetNormal_S(WORLD dat)
						{	m_Normal_S.x = dat.x;
							m_Normal_S.y = dat.y;
							m_Normal_S.z = dat.z;
						};
	double 		GetSegAngle_S(){return m_SegAngle_S;};
	void 		SetSegAngle_S(double dat){m_SegAngle_S = dat;};
	//////////////////////////////////////////////////////////////////// DrPipe Compatibility
	CDrNode*	GetCNode_CC(){return m_pCNode_CC;};
	void 		SetCNode_CC(CDrNode* dat){m_pCNode_CC = dat;};
	CDrNode*	GetCNode_TI(){return m_pCNode_TI;};
	void 		SetCNode_TI(CDrNode* dat){m_pCNode_TI = dat;};
	CDrNode*	GetCNode_CA(){return m_pCNode_CA;};
	void 		SetCNode_CA(CDrNode* dat){m_pCNode_CA = dat;};
	CDrNode*	GetCNode_CB(){return m_pCNode_CB;};
	void 		SetCNode_CB(CDrNode* dat){m_pCNode_CB = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		IsHole_S(){return m_bHole_S;};
	void		SetHole_S(BOOL bYes){m_bHole_S = bYes;};
	//////////////////////////////////////////////////////////////////// At a Point
	int		GetAPointOnCurrentBezSeg(int nOut_S,pWORLD pOut,pDOUBLE pOutWt);
	int		GetCurrentBezSeg_N_s(int nOut_S,int& nCurBz_S,double& sCur);
	//////////////////////////////////////////////////////////////////// Derivatives
//	void		Get_EndTangent_Vector(VECTOR& tan,BOOL bBegin);
	void		Get_EndTangent_Vector(VECTOR& tan,BOOL bBegin,
											double dSameNessRatio);
//	void		Get_EndTangent(WORLD& tan,BOOL bBegin);
	void		Get_EndTangent(WORLD& tan,BOOL bBegin,double dSameNessRatio);
//	void		Get_TangentAtaNode_Vector(WORLD wNodeCoord,VECTOR& tan);
	void		Get_TangentAtaNode_Vector(WORLD wNodeCoord,VECTOR& tan,
											double dSameNessRatio);
//	int			Get_TangentAtaNode(WORLD wNodeCoord,WORLD& Tangent);
	int			Get_TangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,
											double dSameNessRatio);
	int 		GenerateTangent(pWORLD pOut);
	///	
	pWORLD		GetpTangents_S(){return m_pTangents_S;};
	void		SetpTangents_S(pWORLD t){m_pTangents_S = t;};
	pDOUBLE		GetpCurvatures_S(){return m_pCurvatures_S;};
	void		SetpCurvatures_S(pDOUBLE t){m_pCurvatures_S = t;};
    //////////////////////////////////////////////////////////////////// Output
    double		GetRatio_S(){return m_Ratio_S;};		// for OneSegment Linear Only
    void		SetRatio_S(double r){m_Ratio_S = r;};	// for OneSegment Linear Only
    //////////////////////////////////////////////////////////////////// Input
	BOOL		IsAxisInput(){return m_bAxis;};	// if Axis Input
	void		SetAxisInput(BOOL b){m_bAxis = b;};	// Set if Axis Input
	int			GetAxis(){return m_Axis;};		// 1=X/2=Y/3=Z
	void		SetAxis(int a){m_Axis = a;};		// 1=X/2=Y/3=Z
	BOOL		IsNegative(){return m_bNegative;};
	void		SetNegative(BOOL b){m_bNegative = b;};
	CIRCLETYPE			GetCircleType(){return m_CircleType;};
	void		SetCircleType(CIRCLETYPE c){m_CircleType = c;};
    int			GetInputType(){return m_InputType;};		
    void		SetInputType(int r){m_InputType = r;};	
    BOOL		IsArcType(){return m_bArcType;};		
    void		SetArcType(BOOL r){m_bArcType = r;};	
    CList<int,int>*			GetElperSegList_S(){return &m_ElperSegList_S;};		
	////////////
	BOOL		IsSkewed(){return m_bSkewed;};							
	void		SetSkewed(BOOL bSkewed){m_bSkewed = bSkewed;};
	BOOL		IsLinSpr(){return m_bLinSpr;};							
	void		SetLinSpr(BOOL bLinSpr){m_bLinSpr = bLinSpr;};
	BOOL		IsLinSnu(){return m_bLinSnu;};							
	void		SetLinSnu(BOOL bLinSnu){m_bLinSnu = bLinSnu;};
	///////////////////////////////////////////////////////////////////// Mesh
	BOOL 		CullWorld(WORLD VDir){return FALSE;};
	BOOL 		CullScreen(pMATRIX pViewM){return FALSE;};
    ///
	void 		Calc_CentroidWorld(){};
	void 		Calc_CentroidEye(){};
	void 		Calc_CentroidScreen3D(double dScale_U,double dScale_V){};
	void 		Calc_NormalWorld(){};
	void 		TransformNormalToEye(pMATRIX pView){};
	void 		ProjectNormalToScreen3D
							(pMATRIX pvv3DM,double dScale_U,double dScale_V){};
	///
	pWORLD	 	GetNormalWorld(){return (pWORLD)NULL;};
	void		SetNormalWorld(WORLD Normal){};
	pWORLD	 	GetNormalEye(){return (pWORLD)NULL;};
	void		SetNormalEye(WORLD Normal){};
	pWORLD	 	GetNormalScreen3D(){return (pWORLD)NULL;};
	void		SetNormalScreen3D(WORLD Centroid){};
	POINT*	 	GetNormalScreen2D(){return (POINT*)NULL;};
	void		SetNormalScreen2D(POINT Centroid){};
	//////////////////////////////////////////////////////////////
	CDListMgr*	GetNodTopoList(){return &m_NodTopoList;};
	////////////
	CList<SUPPCARD,SUPPCARD>*	GetSuppCardList(){return	&m_SuppCardList;};
	CList<STALCARD,STALCARD>*	GetStaLCardList(){return	&m_StaLCardList;};
	CList<WORLD,WORLD>*	GetBndryPtList(){return	&m_BndryPtList;};
	//////////////////////////////////////////////////////////		          
	BEZIERTYPE	GetBezierType(){return m_BezierType;};;
	void		SetBezierType(BEZIERTYPE b){m_BezierType = b;};
	///////////////////////////////////////////////////////////




protected:
	

	/////////////////
	void 	GoDoControlNodes(CDC* PtrDC);
	void 	GoDoIt(CDC* PtrDC);
	//////////////////////////////////////////////////////////// Curve
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
	void 	Calc_ScreenRectFromCNodes();
	void 	Rearrange3DCorners(pWORLD pMin, pWORLD pMax);
	void 	Rearrange2DCorners();
	////////////////////////////////////////////////////////////////////////////////////////
	void 	FinishObject();
	void 	TransformToWorldPos(pMATRIX pLM,BOOL bYes);
	void 	TransformToEyePos(pMATRIX pViewM);
	void 	ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	///////////////////////////////////// DirtyDraw				
	void 	Gen_XFormedCurveForDirtyDraw();
	void 	ProjectForDirtyDraw
				(pMATRIX pvv3DM,double dScale_U,double dScale_V);
		          

			
// Helper functions
protected:
// Attributes

	
	BEZIERTYPE	m_BezierType;
	//////////////////////////////////////////////
	CList<WORLD,WORLD>				m_BndryPtList;	
	CList<SUPPCARD,SUPPCARD>		m_SuppCardList;	
	CList<STALCARD,STALCARD>		m_StaLCardList;	
	//////////////////////////
	int			m_Class_S;				// 0=C0,1=C1,2=C2
	CDListMgr	m_NodTopoList;
	//////////////////////////
	int			m_nMeshElemDim;			// Formerly m_b2D  FOR POSTING PURPOSE
										// 0D = Node/1D = Grid or 2D = plate etc 
	int			m_nCompoType;			// NODE, cNODE(0D) : for Node Generation using Curve
										// pipe,beam(Grid 1D) or BoundaryCondition Elem
										// Triangle/Rect(2D) for patch
										// Cube/thk.shell(3D)for solid
	////////////////////////////
	BOOL		m_bIso;					// IsoParametric?
	CString		m_IsoToID;				// IsotoCurveID
	/////////////////////////
	CString		m_CompoID;
	/////////////////////////										
	CURVEPROC	m_CurveType_S;
	/////////////////////////////////
	CDListMgr	m_VNodeList;       // Internally Generated Nodes
	CDListMgr	m_CN_BSList;       // Control Nodes Pointers  needed for delete: B-Spline Control Net
	/////////////////////////
	int			m_nSegUnif_S;		// Used Only for Triangular Patch Later which needs
									// uniform Output for all Bez.segments
	///////////////////////////////////////////////////////////////////////////////////
	BOOL		m_bClosed_S; 
	int			m_nMaxINodes_S;
	int			m_nMaxCNodes_S;			// INTERNALLY: WE ALWAYS STAY WITH  B E Z I E R
	int			m_nMaxCurves_S;			// Formerly: m_nMaxCurves	// No. of Curves
	///////////////////////////////////////////////////////////////////////////////////
	int			m_nCurveObjectType;		// ObjectType to create; -1 = no creation reqd
	BOOL		m_bDirty;				// ObjectType NOT SAVED	
	BOOL		m_bPosted;				// ObjectType NOT SAVED	
    BOOL		m_bControlDraw;
    ////////////////////////////////////// Memory
	pWORLD		m_pIn;		// Control Nodes -WorldCoords
	pDOUBLE		m_pInWts;	// Control Weights -World for Rational
	POINT*		m_pInDP;    // Control Nodes -ScreenCoords
	pWORLD		m_pOut;		// Output  Nodes -World or Eye Pos
	pDOUBLE		m_pOutWts;	// Output  Weights -World or Eye Pos for Rational
	POINT*		m_pOutDP;   // Output  Nodes -ScreenCoords
	long		m_nOut;
	////////////////////////////////////////////////////////////////////////////////
	double		m_alfa_S;			// Cardinal Spline (Catmull-Rom Modified)	
	double		m_bias_S;			// beta
	double		m_tension_S;		// beta and hermite
	//////////////////////////////////////////////////////////////////////////////// Output
	CURVEOUTPUT	m_OutMethod_S;		// Output Method
	BOOL		m_bUniform_S;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	int			m_nMaxOutPts_S;
	int			m_nMaxOutSeg_S;		// Number of Output Segments on ENTIRE Curve
	pINT		m_pNum_t_S;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nCurveSeg																							
	pDOUBLE		m_pDis_t_S;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pINT		m_pNum_t_Ex_S;		// Expanded Number of Outputs for each Output Segment
	pDOUBLE		m_pDis_Ang_S;		// Output theta-distribution array for Circle:
										//	Dis_Ang[i], i = 1,m_nSegUnif_S+1
	/////////////////////////
	int			m_nBSeg_Ex_S;
	pINT		m_pBSeg_Ex_S;		// # BezSegment between a pair of DataPts (Circle)
									// needed for 120 deg construction limit
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	int			m_nOrder_S;				// k
	int			m_nData_S;				// GIVEN: # of Data= nData			= m_nMaxINodes_S  
//	int			m_nSeg_DT_S;			// L = #of CurveSegments= nData - 1	= m_nMaxCurves_S 
//	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// L + k - 1 = nData + k - 2 = n + 1:
										// #of Spline Controls// for drawing ControlNet
	int			m_nMKnots_S;			// n + k + 1 = Total		// Not Need
	int			m_nKnots_S;				// n - k + 3 = distinct		// User Need
//	int			m_nCon_BZ_S;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	int 		m_nDim_S;				// 4 = RATIONAL/	3 = NONrational 
	WEIGHT		m_WtType_S;
	KNOT		m_KnotType_S;
	BOUNDARY	m_BCL_S;
	BOUNDARY	m_BCR_S;
	VECTOR		m_TanL_S;
	VECTOR		m_TanR_S;
	////////////////////// Memory for Interpolation
	pDOUBLE		m_pMKnots_S;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pDOUBLE		m_pWts_BS_S;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	pWORLD		m_pCon_BS_S;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		m_pKnot_S; 		// distinct( for User Need)
	pDOUBLE		m_pWts_DT_S;	// for User Need
	pDOUBLE		m_pWts_BZ_S;
//	pWORLD 		m_pCon_BZ;	// stored in m_CNodeList
	//////////////////////////////////////////////////////////////////// CONICS
	CIRCLETYPE	m_CircleType;
//	CString		m_FromID_S;		// also used:AnchorID for Sweep/Duct
//	CString		m_ToID_S;
	CDrNode*	m_pFromIDNode_S;		// also used:AnchorID for Sweep/Duct
	CDrNode*	m_pToIDNode_S;
	int			m_nData_Ex_S;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	BOOL		m_bExpanded_S;
	int			m_nMaxENodes_S;
	WORLD		m_Center_S;	// Circle
	WORLD		m_Normal_S;	
	double		m_Radius_S;
	double		m_Theta_S;
	double 		m_SegAngle_S;
	///////
	BOOL		m_bAxis;	// if Axis Input
	int			m_Axis;		// 1=X/2=Y/3=Z
	BOOL		m_bNegative;
	//////////////////////////////////////////////// DrPipe Compatibility
	CDrNode*	m_pCNode_CC;		// Center CNode
	CDrNode*	m_pCNode_TI;		// Tangent Intersection CNode
	CDrNode*	m_pCNode_CA;		// CNode_A on Tangent
	CDrNode*	m_pCNode_CB;		// CNode_B on Tangent
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		m_bHole_S;
	//////////////////////////////////////////////////////////////////// Derivatives
	pWORLD		m_pTangents_S;			// Tangents
	pDOUBLE		m_pCurvatures_S;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    double		m_Ratio_S;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Input Type: Normally = 1
	int			m_InputType;		// needed later for editing
	BOOL		m_bArcType;			// needed later for editing
	CList<int,int> m_ElperSegList_S; // for edit purpose etc.
	



public:
	virtual ~CDrCurve();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrCurve)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



