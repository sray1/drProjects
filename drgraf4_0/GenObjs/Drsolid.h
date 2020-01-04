// Solid.h : header file
//
#ifndef _DRSOLID_H_
#define _DRSOLID_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrPatch.h"
//#include "Obj3D.h"
#include "DListMgr.h"
#include "Def_Type.h"

//#pragma warning( disable : 4200 )
#include "Def_Rend.h"               // Render Attribs.
// CDrSolid    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrSolid: public CDrPatch
{
public:
// Construction                 
	CDrSolid();
//////////////////////////////////////
	DECLARE_SERIAL(CDrSolid);
//////////////////////////////////////
	
	
// Operations
public:

	virtual void 		ReadyToDelete();
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
	virtual BOOL		IsNormalNeeded(){return m_bNormalDraw;};							
	virtual void		SetNormalNeed(BOOL bNN){m_bNormalDraw = bNN;};							
	////////////////////
	virtual int 		AppendToObject
						(	
							CDListMgr* pObj3DList,
							CDListMgr* pPatchList,
							CDListMgr* pElemList, 
							CDListMgr* pNodeList,
							CDListMgr* pCNodeList
						);
	////////////////////////////////////////////////////////////////////
	CURVEPROC 	GetCurveType_R(){return m_CurveType_R;};
	void		SetCurveType_R(CURVEPROC kind){m_CurveType_R = kind;};
	//////////////////////////////////////////////////////////////////
//	int			GetSegmentCount_R(){return m_nSegUnif_R;};
//	void		SetSegmentCount_R(int nSegs){m_nSegUnif_R = nSegs;};
	int			GetOutSegUnif_R(){return m_nSegUnif_R;};
	void		SetOutSegUnif_R(int nSegs){m_nSegUnif_R = nSegs;};
	//////////////////////////////////////////////////////////////////
	BOOL		IsClosed_R(){return m_bClosed_R;};
	void		SetClosed_R(BOOL bYes){m_bClosed_R = bYes;};
	int			GetSolidObjectType(){return m_nSolidObjectType;};
	void		SetSolidObjectType(int nType){m_nSolidObjectType = nType;};
//			int			GetMaxCubicSolides_R(){return m_nMaxCubicSolides_R;};
//Changed	void		SetMaxCubicSolides_R(int nMax){m_nMaxCubicSolides_R = nMax;};
	/////////////////////////////////////////////////////////////////////
//	int			GetMaxCurves_R(){return m_nMaxCurves_R;};
//	void		SetMaxCurves_R(int nMax){m_nMaxCurves_R = nMax;};
	int			GetMaxBezSegments_R(){return m_nMaxCurves_R;};
	void		SetMaxBezSegments_R(int nMax){m_nMaxCurves_R = nMax;};
	///////////////////////////////////////////////////////////////////////

	int			GetMaxCNodes_R(){return m_nMaxCNodes_R;};
	void		SetMaxCNodes_R(int nMax){m_nMaxCNodes_R = nMax;};
	int			GetMaxOutPts_R(){return m_nMaxOutPts_R;};
	void		SetMaxOutPts_R(int nMax){m_nMaxOutPts_R = nMax;};
	/////////////////////////////////////////////////////////////
	int 		NumberOfSolides();
	int			NumberOfBezierPenta();
	int 		NumberOfElements(UINT nSolidType,int nElemType);
	//////////////////////////////////////// Construction Help
	CString	GetPatchID(int index){return m_PatchID[index];};
	void	SetPatchID(CString id,int index)
						{m_PatchID[index] = id;};
	CDrNode*	GetFromIDNode_R(){return m_pFromIDNode_R;};
	void 		SetFromIDNode_R(CDrNode* dat){m_pFromIDNode_R = dat;};
	CDrNode*	GetToIDNode_R(){return m_pToIDNode_R;};
	void 		SetToIDNode_R(CDrNode* dat){m_pToIDNode_R = dat;};
//	CString	GetFromID_R(){return m_FromID_R;};
//	void	SetFromID_R(CString id){m_FromID_R = id;};
//	CString	GetToID_R(){return m_ToID_R;};
//	void	SetToID_R(CString id){m_ToID_R = id;};
	pWORLD	GetFromPtLocal_R(){return &m_FromPtLocal_R;};
	void	SetFromPtLocal_R(WORLD vPt){m_FromPtLocal_R = vPt;};
	pWORLD	GetToPtLocal_R(){return &m_ToPtLocal_R;};
	void	SetToPtLocal_R(WORLD vPt){m_ToPtLocal_R = vPt;};
	pWORLD	GetFromPtWorld_R(){return &m_FromPtWorld_R;};
	void	SetFromPtWorld_R(WORLD vPt){m_FromPtWorld_R = vPt;};
	pWORLD	GetToPtWorld_R(){return &m_ToPtWorld_R;};
	void	SetToPtWorld_R(WORLD vPt){m_ToPtWorld_R = vPt;};
	pWORLD	GetFromPtEye_R(){return &m_FromPtEye_R;};
	void	SetFromPtEye_R(WORLD vPt){m_FromPtEye_R = vPt;};
	pWORLD	GetToPtEye_R(){return &m_ToPtEye_R;};
	void	SetToPtEye_R(WORLD vPt){m_ToPtEye_R = vPt;};
	pWORLD	GetAxis_R(){return &m_vAxis_R;};
	void	SetAxis_R(WORLD vAxis){m_vAxis_R = vAxis;};
	int		GetExtruType_R(){return m_nExtruType_R;};
	void	SetExtruType_R(int nSegs){m_nExtruType_R = nSegs;};
	double	GetLength_R(){return m_dLen_R;};
	void	SetLength_R(double dLen){m_dLen_R = dLen;};
	////////////////////////////////////////////////////////////////// for Type 2 Input
	WORLD	GetWorldLength_R(){return m_wLen_R;};
	void	SetWorldLength_R(WORLD wLen){m_wLen_R = wLen;};
	//////////////////////////////////////////////////////////////////
	int		GetSegs_R(){return m_nSegs_R;};
	void	SetSegs_R(int nSegs){m_nSegs_R = nSegs;};
	//////////////////////////////////////////////////////////////////
	SOLIDPROC 	GetSolidProc(){return m_SolidProc;};
	void		SetSolidProc(enum SOLIDPROC kind)
							{m_SolidProc = kind;};
	SOLIDTYPE 	GetSolidType(){return m_SolidType;};
	void		SetSolidType(enum SOLIDTYPE kind)
							{m_SolidType = kind;};
	SOLSUBTYPE 	GetSolSubType(){return m_SolSubType;};
	void		SetSolSubType(enum SOLSUBTYPE kind)
							{m_SolSubType = kind;};
    ///////////////////////////////////////////////////////
	int  	GetOut_R(){return m_nOut_R;};
	void  	SetOut_R(int nOut){m_nOut_R = nOut;};
	///////////////////////////////////////////// 
	int 	Generate_SolidHex(pWORLD pOut, pDOUBLE pOutWts);
	int 	Generate_SolidPen(pWORLD pOut, pDOUBLE pOutWts);
	int 	Generate_SolidTet(pWORLD pOut, pDOUBLE pOutWts);
	////////////////////////////////////////////////////////////// interpolation
	BOOL	IsUniform_R(){return m_bUniform_R;};		// Output Distribution:
	void	SetUniform_R(BOOL a){ m_bUniform_R = a;};		// Output Distribution:
	int 		GetOrder_R(){return m_nOrder_R;};
	void 		SetOrder_R(int nOrd){m_nOrder_R = nOrd;};
	int			GetnDim_R(){return m_nDim_R;}; 			
	void		SetnDim_R(int bs){m_nDim_R = bs;}; 		
	SOLIDOUTPUT	GetOutMethod_R(){return m_OutMethod_R;};	// Output Method
	void		SetOutMethod_R(SOLIDOUTPUT a){ m_OutMethod_R = a;};	// Output Method
	int			GetMaxOutSeg_R(){return m_nMaxOutSeg_R;};	// Number of Output Segments on ENTIRE Curve
	void		SetMaxOutSeg_R(int a){m_nMaxOutSeg_R = a;};	// Number of Output Segments on ENTIRE Curve
	pINT		GetNum_tPointer_R(){return m_pNum_t_R;};	// Number of Outputs for each Output Segment
	void		SetNum_tPointer_R(pINT a){m_pNum_t_R =a;};	// Number of Outputs for each Output Segment
	pDOUBLE		GetDis_tPointer_R(){return m_pDis_t_R;};	// Number of Outputs for each Output Segment
	void		SetDis_tPointer_R(pDOUBLE a){m_pDis_t_R =a;};	// Number of Outputs for each Output Segment
	pINT		GetNum_tPointer_Ex_R(){return m_pNum_t_Ex_R;};	// Output t-distribution array:
	void		SetNum_tPointer_Ex_R(pINT a){m_pNum_t_Ex_R = a;};	// Output t-distribution array:
	pDOUBLE		GetDis_AngPointer_R(){return m_pDis_Ang_R;};	// Distribution of angles 
	void		SetDis_AngPointer_R(pDOUBLE a){m_pDis_Ang_R =a;};	// Distribution of angles 
	pINT		GetNum_tPointer_ST(){return m_pNum_t_ST;};	// Number of Outputs for each Output Segment
	void		SetNum_tPointer_ST(pINT a){m_pNum_t_ST =a;};	// Number of Outputs for each Output Segment
	pDOUBLE		GetDis_tPointer_ST(){return m_pDis_t_ST;};	// Number of Outputs for each Output Segment
	void		SetDis_tPointer_ST(pDOUBLE a){m_pDis_t_ST =a;};	// Number of Outputs for each Output Segment
	pINT		GetNum_tPointer_Ex_ST(){return m_pNum_t_Ex_ST;};	// Output t-distribution array:
	void		SetNum_tPointer_Ex_ST(pINT a){m_pNum_t_Ex_ST = a;};	// Output t-distribution array:
	pDOUBLE		GetDis_AngPointer_ST(){return m_pDis_Ang_ST;};	// Distribution of angles 
	void		SetDis_AngPointer_ST(pDOUBLE a){m_pDis_Ang_ST =a;};	// Distribution of angles 
	//////////////////////////////////////////////////////////////////// CONICS
	int 		GetData_Ex_R(){return m_nData_Ex_R;};
	void 		SetData_Ex_R(int ndat){m_nData_Ex_R = ndat;};
	BOOL		IsExpanded_R(){return m_bExpanded_R;};		// Output Distribution:
	void		SetExpanded_R(BOOL a){ m_bExpanded_R = a;};		// Output Distribution:
	int			GetMaxENodes_R(){return m_nMaxENodes_R;};	
	void		SetMaxENodes_R(int nMax){m_nMaxENodes_R = nMax;};
	double 		GetRadius_R(){return m_Radius_R;};
	void 		SetRadius_R(double dat){m_Radius_R = dat;};
	double 		GetTheta_R(){return m_Theta_R;};
	void 		SetTheta_R(double dat){m_Theta_R = dat;};
	WORLD 		GetCenter_R(){return m_Center_R;};
	void 		SetCenter_R(WORLD dat)
						{	m_Center_R.x = dat.x;
							m_Center_R.y = dat.y;
							m_Center_R.z = dat.z;
						};
	WORLD 		GetNormal_R(){return m_Normal_R;};
	void 		SetNormal_R(WORLD dat)
						{	m_Normal_R.x = dat.x;
							m_Normal_R.y = dat.y;
							m_Normal_R.z = dat.z;
						};
	double 		GetSegAngle_R(){return m_SegAngle_R;};
	void 		SetSegAngle_R(double dat){m_SegAngle_R = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		IsHole_R(){return m_bHole_R;};
	void		SetHole_R(BOOL bYes){m_bHole_R = bYes;};
	//////////////////////////////////////////////////////////////////// Derivatives
	pWORLD	GetpTangents_R(){return m_pTangents_R;};
	void	SetpTangents_R(pWORLD t){m_pTangents_R = t;};
	pDOUBLE	GetpCurvatures_R(){return m_pCurvatures_R;};
	void	SetpCurvatures_R(pDOUBLE t){m_pCurvatures_R = t;};
    //////////////////////////////////////////////////////////////////// Output
    double	GetRatio_R(){return m_Ratio_R;};		// for OneSegment Linear Only
    void	SetRatio_R(double r){m_Ratio_R = r;};	// for OneSegment Linear Only
	////////////////////////////////////////////////////////////// for Duct/Sweep
	int		GetTwistType_R(){return m_nTwistType_R;};
	void	SetTwistType_R(int nSegs){m_nTwistType_R = nSegs;};
	CList<double,double>* 
			GetTwistList_R(){return &m_TwistList_R;};
	int		GetScaleType_R(){return m_nScaleType_R;};
	void	SetScaleType_R(int nSegs){m_nScaleType_R = nSegs;};
	CList<double,double>* 
			GetScaleList_R(){return &m_ScaleList_R;};
	//////////////////
	BOOL	IsIncTwist_R(){return m_bIncTwist_R;};
	void	SetIncTwist_R(BOOL dLen){m_bIncTwist_R = dLen;};
	double	GetTwistMult_R(){return m_TwistMult_R;};
	void	SetTwistMult_R(double dLen){m_TwistMult_R = dLen;};
	double	GetTwistStart_R(){return m_TwistStart_R;};
	void	SetTwistStart_R(double dLen){m_TwistStart_R = dLen;};
	BOOL	IsIncScale_R(){return m_bIncScale_R;};
	void	SetIncScale_R(BOOL dLen){m_bIncScale_R = dLen;};
	double	GetScaleMult_R(){return m_ScaleMult_R;};
	void	SetScaleMult_R(double dLen){m_ScaleMult_R = dLen;};
	double	GetScaleStart_R(){return m_ScaleStart_R;};
	void	SetScaleStart_R(double dLen){m_ScaleStart_R = dLen;};
	///////////////////////////////////////////////////////////////////// PentaHedrons 
    CDListMgr*	GetPentaList(){return &m_PentaList;};
	int			GetnTriangles_ST(){return m_nTriangles_ST;};	
	void		SetnTriangles_ST(int nMax){m_nTriangles_ST = nMax;};
	/////////////////////////////////////////////////////////////////////	
    CList<int,int>*	GetElperSegList_R(){return &m_ElperSegList_R;};		
	/////////////////////////////////////////////////////////////////////
	BOOL		IsGenBPatch(){return m_bGenBPatch;};		// bndry Patch
	void		SetGenBPatch(BOOL a){ m_bGenBPatch = a;};	// bndry Patch:
	////
	CDListMgr* 	GetVPatchList(){return	&m_VPatchList;};
	//////////////////////////////////////////////////
    CDListMgr*	GetPatchList_U(){return &m_PatchList_U;};	// for GordonTypeInput
    CDListMgr*	GetPatchList_V(){return &m_PatchList_V;};
    CDListMgr*	GetPatchList_W(){return &m_PatchList_W;};	// TRIANGULAR
    CList<PATCHLATCH,PATCHLATCH>*	GetPatchLatchList_U(){return &m_PatchLatchList_U;};
    CList<PATCHLATCH,PATCHLATCH>*	GetPatchLatchList_V(){return &m_PatchLatchList_V;};
    CList<PATCHLATCH,PATCHLATCH>*	GetPatchLatchList_W(){return &m_PatchLatchList_W;};// TRIANGULAR
																					   // also Solid
	////////////////////////////////////////////////////////////////// Rotation
	BOOL		IsAxisInput_R(){return m_bAxis_R;};	// if Axis Input
	void		SetAxisInput_R(BOOL b){m_bAxis_R = b;};	// Set if Axis Input
	int			GetAxisType_R(){return m_nAxis_R;};		// 1=X/2=Y/3=Z
	void		SetAxisType_R(int a){m_nAxis_R = a;};		// 1=X/2=Y/3=Z
	BOOL		IsNegative_R(){return m_bNegative_R;};
	void		SetNegative_R(BOOL b){m_bNegative_R = b;};
	CIRCLETYPE	GetCircleType_R(){return m_CircleType_R;};
	void		SetCircleType_R(CIRCLETYPE c){m_CircleType_R = c;};
	//////
	double	GetAng_1_R(){return m_dAng_1_R;};
	void	SetAng_1_R(double dAng){m_dAng_1_R = dAng;};
	double	GetAng_2_R(){return m_dAng_2_R;};
	void	SetAng_2_R(double dAng){m_dAng_2_R = dAng;};
	//////////////////////////////////////////////////////////////////
 	
 	
 	

protected:
	
	BOOL	IsObjectHit_TETRA(int nNet,POINT point);
	BOOL	IsObjectHit_PENTA(int nNet,POINT point);
	BOOL	ObjectHit_PENTA_1(int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
									int nOutStartIndex,int nNet,POINT point);
	BOOL	ObjectHit_PENTA_2(int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
									int nOutStartIndex,int nNet,POINT point);
	BOOL	IsObjectHit_HEXA(int nNet,POINT point);
	int		ObjectHit_Generate2DPts();
	///
	void 	GoDoControlNodes_HEXA(CDC* PtrDC);
	void 	GoDoIt_HEXA(CDC* PtrDC);
	void 	GoDoControlNodes_PENTA(CDC* PtrDC);
	void 	GoDoIt_PENTA(CDC* PtrDC);
	void	PENTA_1(CDC* PtrDC,int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
							int nOutStartIndex);
	void	PENTA_2(CDC* PtrDC,int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
							int nOutStartIndex);
	void 	GoDoControlNodes_TETRA(CDC* PtrDC);
	void 	GoDoIt_TETRA(CDC* PtrDC);
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
//void 	UnitAxisFromEndNodes();
//	void 	RefillCNEyePosForDirtyDraw();
		          

			
// Helper functions
protected:
// Attributes
 
	CDrCurve*	m_pBndryPatches[6];		// HEX = 6/ PEN = 5 / TET = 4
	//////////////////////////////
	BOOL		m_bGenBPatch;			// bndry Patch
	/////////////////////////////////
	SOLIDPROC	m_SolidProc;           // How Generated? PP_EXTRUDE etc
	SOLIDTYPE	m_SolidType;           	// PA_TENSOR, etc
	SOLSUBTYPE 	m_SolSubType;			// Tringle or Quadrilat
	CURVEPROC	m_CurveType_R;         	// PA_BEZIER, etc
	/////////////////////////
	int			m_nSegUnif_R;		//formerly:m_nSegments_T;
	int			m_nMaxINodes_R;
	int			m_nMaxCurves_R;			// Formaerly: m_nMaxCubicSolides_R;   // No. of Curves
	BOOL		m_bClosed_R; 
	int			m_nMaxCNodes_R;
	int			m_nMaxOutPts_R;
	int			m_nSolidObjectType;		// ObjectType to create; -1 = no creation reqd
	//////////////////////////////////////// Construction Help
	CString		m_PatchID[2];      	// XSec for loft also 
	int			m_nSegs_R;
	int			m_nOut_R;	//	number of generated Solid vertices in V dir	
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	WORLD 		m_FromPtLocal_R;		// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtWorld_R;	// used also for Sweep/Duct Anchor
	WORLD 		m_FromPtEye_R;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtLocal_R;			// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtWorld_R;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPtEye_R;		// used also for Sweep/Duct Anchor
	///////////////////////////
	int			m_nExtruType_R;
	double		m_dLen_R;
	WORLD		m_wLen_R;		// for Type 2 Input
	double		m_dLenEye_R;
	WORLD		m_vAxis_R;		// unit Extrusion Axis/XFormed
	WORLD		m_vAxisEye_R;		// unit Extrusion Axis/XFormed
	/////////////////////
//	CString		m_FromID_R;		// also used:AnchorID for Sweep/Duct
//	CString		m_ToID_R;
	CDrNode*	m_pFromIDNode_R;		// also used:AnchorID for Sweep/Duct
	CDrNode*	m_pToIDNode_R;
//	CString		m_CurveID;      // XSec   Profile for Sweep
	/////////////////////////////////////////// Rotate
	BOOL		m_bAxis_R;	// if Axis Input
	int			m_nAxis_R;		// 1=X/2=Y/3=Z
	BOOL		m_bNegative_R;
	CIRCLETYPE	m_CircleType_R;
	double		m_dAng_1_R;
	double		m_dAng_2_R;
	/////////////////////////////////////////// Duct/Sweep
	int			m_nTwistType_R;	//1 = Distribution
								//2	= Increment; double Type
								//3 = IsoParametric: World Type 
	int			m_nScaleType_R;	//1 = Distribution
								//2	= Increment; double Type
								//3 = IsoParametric: World Type 
	CList<double,double>
				m_TwistList_R;
	CList<double,double>
				m_ScaleList_R;
	///////////////////////////
	BOOL		m_bIncTwist_R;	// Incremental?
	BOOL		m_bIncScale_R;	// for Sweep
	double		m_TwistMult_R;
	double		m_ScaleMult_R;	// for Sweep
	double		m_TwistStart_R;
	double		m_ScaleStart_R;	// for Sweep
	//////////////////////////////////////////////////////////////////////////////// Output
	SOLIDOUTPUT	m_OutMethod_R;		// Output Method
	BOOL		m_bUniform_R;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	int			m_nMaxOutSeg_R;		// Number of Output Segments on ENTIRE Curve in T
	pINT		m_pNum_t_R;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_t_R;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_Ang_R;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pINT		m_pNum_t_Ex_R;		// Expanded Number of Outputs for each Output Segment
	pINT		m_pNum_t_ST;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_t_ST;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pDOUBLE		m_pDis_Ang_ST;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pINT		m_pNum_t_Ex_ST;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	int			m_nOrder_R;				// k 
	int 		m_nDim_R;				// 4 = RATIONAL/	3 = NONrational 
	//////////////////////////////////////////////////////////////////// CONICS
	int			m_nData_Ex_R;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	BOOL		m_bExpanded_R;
	int			m_nMaxENodes_R;
	WORLD		m_Center_R;	// Circle
	WORLD		m_Normal_R;	
	double		m_Radius_R;
	double		m_Theta_R;
	double 		m_SegAngle_R;
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		m_bHole_R;
	//////////////////////////////////////////////////////////////////// Derivatives
	pWORLD		m_pTangents_R;			// Tangents
	pDOUBLE		m_pCurvatures_R;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    double		m_Ratio_R;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// PentaHedrons 
	CDListMgr	m_TetraList;			// Control Penta
	CDListMgr	m_PentaList;			// Control Penta
	CDListMgr	m_HexaList;				// Control Penta
	/////////////////////////
	int			m_nTriangles_ST;			//  Total No of Triangles in Base Patch
	////////////////////////////
	CList<int,int> m_ElperSegList_R; // for edit purpose etc.
	/////////////////////////////
	CDListMgr	m_PatchList_U;       // Patches in u // for GordonType Input
	CDListMgr	m_PatchList_V;       // Patches in v
	CDListMgr	m_PatchList_W;       // Patches in w for Triangle Patches
	CList<PATCHLATCH,PATCHLATCH>	m_PatchLatchList_U;       // Curves in u // for GordonType Input
	CList<PATCHLATCH,PATCHLATCH>	m_PatchLatchList_V;       // Curves in v // for GordonType Input
	CList<PATCHLATCH,PATCHLATCH>	m_PatchLatchList_W;       // Curves in w for Triangle Patches
	////
	CDListMgr	m_VPatchList;       // Virtual Patches: Internally generated
	/////////////////////////////////




public:
	virtual ~CDrSolid();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



