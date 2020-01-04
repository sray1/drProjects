// Solid.h : header file
//
#ifndef _DRSOLID_H_
#define _DRSOLID_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrPatch.h"
//#include "Obj3D.h"
#include "DListMgr.h"
#include "glb_Type.h"

//#pragma warning( disable : 4200 )
#include "glb_Rend.h"               // Render Attribs.
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
							CDListMgr* pPatchList,
							CDListMgr* pElemList, 
							CDListMgr* pNodeList,
							CDListMgr* pCNodeList
						);
	//////////////////////////////////////////////////////////////////////						
	virtual	int			Is3D(){return m_n3D;};// 1D or 2D or 3D
	virtual	void		Set3D(int nDim){m_n3D = nDim;};					// 1D or 2D 
	////////////////////////////////////////////////////////////////////
	virtual CURVEPROC 	GetCurveType_R(){return m_CurveType_R;};
	virtual void		SetCurveType_R(CURVEPROC kind){m_CurveType_R = kind;};
	virtual int			GetSegmentCount_R(){return m_nSegUnif_R;};
	virtual void		SetSegmentCount_R(int nSegs){m_nSegUnif_R = nSegs;};
	virtual BOOL		IsClosed_R(){return m_bClosed_R;};
	virtual void		SetClosed_R(BOOL bYes){m_bClosed_R = bYes;};
	virtual int			GetSolidObjectType(){return m_nSolidObjectType;};
	virtual void		SetSolidObjectType(int nType){m_nSolidObjectType = nType;};
//			virtual int			GetMaxCubicSolides_R(){return m_nMaxCubicSolides_R;};
//Changed	virtual void		SetMaxCubicSolides_R(int nMax){m_nMaxCubicSolides_R = nMax;};
	virtual int			GetMaxCurves_R(){return m_nMaxCurves_R;};
	virtual void		SetMaxCurves_R(int nMax){m_nMaxCurves_R = nMax;};
	virtual int			GetMaxCNodes_R(){return m_nMaxCNodes_R;};
	virtual void		SetMaxCNodes_R(int nMax){m_nMaxCNodes_R = nMax;};
	virtual int			GetMaxOutPts_R(){return m_nMaxOutPts_R;};
	virtual void		SetMaxOutPts_R(int nMax){m_nMaxOutPts_R = nMax;};
	/////////////////////////////////////////////////////////////
	virtual int 		NumberOfSolides();
	virtual int			NumberOfBezierPenta();
	virtual int 		NumberOfElements(UINT nSolidType,int nElemType);
	//////////////////////////////////////// Construction Help
	virtual CString	GetPatchID(int index){return m_PatchID[index];};
	virtual void	SetPatchID(CString id,int index)
						{m_PatchID[index] = id;};
	virtual CString	GetFromID_R(){return m_FromID_R;};
	virtual void	SetFromID_R(CString id){m_FromID_R = id;};
	virtual CString	GetToID_R(){return m_ToID_R;};
	virtual void	SetToID_R(CString id){m_ToID_R = id;};
	virtual pWORLD	GetFromPtLocal_R(){return &m_FromPtLocal_R;};
	virtual void	SetFromPtLocal_R(WORLD vPt){m_FromPtLocal_R = vPt;};
	virtual pWORLD	GetToPtLocal_R(){return &m_ToPtLocal_R;};
	virtual void	SetToPtLocal_R(WORLD vPt){m_ToPtLocal_R = vPt;};
	virtual pWORLD	GetFromPtWorld_R(){return &m_FromPtWorld_R;};
	virtual void	SetFromPtWorld_R(WORLD vPt){m_FromPtWorld_R = vPt;};
	virtual pWORLD	GetToPtWorld_R(){return &m_ToPtWorld_R;};
	virtual void	SetToPtWorld_R(WORLD vPt){m_ToPtWorld_R = vPt;};
	virtual pWORLD	GetFromPtEye_R(){return &m_FromPtEye_R;};
	virtual void	SetFromPtEye_R(WORLD vPt){m_FromPtEye_R = vPt;};
	virtual pWORLD	GetToPtEye_R(){return &m_ToPtEye_R;};
	virtual void	SetToPtEye_R(WORLD vPt){m_ToPtEye_R = vPt;};
	virtual pWORLD	GetAxis_R(){return &m_vAxis_R;};
	virtual void	SetAxis_R(WORLD vAxis){m_vAxis_R = vAxis;};
	virtual double	GetLength_R(){return m_dLen_R;};
	virtual void	SetLength_R(double dLen){m_dLen_R = dLen;};
	virtual int		GetSegs_R(){return m_nSegs_R;};
	virtual void	SetSegs_R(int nSegs){m_nSegs_R = nSegs;};
	virtual double	GetAng_1_R(){return m_dAng_1_R;};
	virtual void	SetAng_1_R(double dAng){m_dAng_1_R = dAng;};
	virtual double	GetAng_2_R(){return m_dAng_2_R;};
	virtual void	SetAng_2_R(double dAng){m_dAng_2_R = dAng;};
	//////////////////////////////////////////////////////////////////
	virtual SOLIDPROC 	GetSolidProc(){return m_SolidProc;};
	virtual void		SetSolidProc(enum SOLIDPROC kind)
							{m_SolidProc = kind;};
	virtual SOLIDTYPE 	GetSolidType(){return m_SolidType;};
	virtual void		SetSolidType(enum SOLIDTYPE kind)
							{m_SolidType = kind;};
	virtual SOLSUBTYPE 	GetSolSubType(){return m_SolSubType;};
	virtual void		SetSolSubType(enum SOLSUBTYPE kind)
							{m_SolSubType = kind;};
    ///////////////////////////////////////////////////////
	virtual int  	GetOut_R(){return m_nOut_R;};
	virtual void  	SetOut_R(int nOut){m_nOut_R = nOut;};
 	//////////////////////////////////////////////////////////
	virtual void 	Calc_PolyNormalWorld();
	virtual void 	TransformPolyNormalToEye(pMATRIX pViewM);
	virtual void 	ProjectPolyNormalToScreen3D
						(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 	Calc_NodeNormalWorld();
	virtual void 	Calc_NodeNormalEye();
	virtual void 	Calc_NodeNormalScreen3D();
	///////////////////////////////////////////// 
	virtual int 	Generate_SolidHex(pWORLD pOut, pDOUBLE pOutWts);
	virtual int 	Generate_SolidPen(pWORLD pOut, pDOUBLE pOutWts);
	virtual int 	Generate_SolidTet(pWORLD pOut, pDOUBLE pOutWts);
	////////////////////////////////////////////////////////////// interpolation
	virtual BOOL	IsUniform_R(){return m_bUniform_R;};		// Output Distribution:
	virtual void	SetUniform_R(BOOL a){ m_bUniform_R = a;};		// Output Distribution:
	virtual int 		GetOrder_R(){return m_nOrder_R;};
	virtual void 		SetOrder_R(int nOrd){m_nOrder_R = nOrd;};
	virtual int			GetnDim_R(){return m_nDim_R;}; 			
	virtual void		SetnDim_R(int bs){m_nDim_R = bs;}; 		
	virtual SOLIDOUTPUT	GetOutMethod_R(){return m_OutMethod_R;};	// Output Method
	virtual void		SetOutMethod_R(SOLIDOUTPUT a){ m_OutMethod_R = a;};	// Output Method
	virtual int			GetMaxOutSeg_R(){return m_nMaxOutSeg_R;};	// Number of Output Segments on ENTIRE Curve
	virtual void		SetMaxOutSeg_R(int a){m_nMaxOutSeg_R = a;};	// Number of Output Segments on ENTIRE Curve
	virtual pINT		GetNum_tPointer_R(){return m_pNum_t_R;};	// Number of Outputs for each Output Segment
	virtual void		SetNum_tPointer_R(pINT a){m_pNum_t_R =a;};	// Number of Outputs for each Output Segment
	virtual pDOUBLE		GetDis_tPointer_R(){return m_pDis_t_R;};	// Number of Outputs for each Output Segment
	virtual void		SetDis_tPointer_R(pDOUBLE a){m_pDis_t_R =a;};	// Number of Outputs for each Output Segment
	virtual pINT		GetNum_tPointer_Ex_R(){return m_pNum_t_Ex_R;};	// Output t-distribution array:
	virtual void		SetNum_tPointer_Ex_R(pINT a){m_pNum_t_Ex_R = a;};	// Output t-distribution array:
	virtual pDOUBLE		GetDis_AngPointer_R(){return m_pDis_Ang_R;};	// Distribution of angles 
	virtual void		SetDis_AngPointer_R(pDOUBLE a){m_pDis_Ang_R =a;};	// Distribution of angles 
	virtual pINT		GetNum_tPointer_ST(){return m_pNum_t_ST;};	// Number of Outputs for each Output Segment
	virtual void		SetNum_tPointer_ST(pINT a){m_pNum_t_ST =a;};	// Number of Outputs for each Output Segment
	virtual pDOUBLE		GetDis_tPointer_ST(){return m_pDis_t_ST;};	// Number of Outputs for each Output Segment
	virtual void		SetDis_tPointer_ST(pDOUBLE a){m_pDis_t_ST =a;};	// Number of Outputs for each Output Segment
	virtual pINT		GetNum_tPointer_Ex_ST(){return m_pNum_t_Ex_ST;};	// Output t-distribution array:
	virtual void		SetNum_tPointer_Ex_ST(pINT a){m_pNum_t_Ex_ST = a;};	// Output t-distribution array:
	virtual pDOUBLE		GetDis_AngPointer_ST(){return m_pDis_Ang_ST;};	// Distribution of angles 
	virtual void		SetDis_AngPointer_ST(pDOUBLE a){m_pDis_Ang_ST =a;};	// Distribution of angles 
	//////////////////////////////////////////////////////////////////// CONICS
	virtual int 		GetData_Ex_R(){return m_nData_Ex_R;};
	virtual void 		SetData_Ex_R(int ndat){m_nData_Ex_R = ndat;};
	virtual BOOL		IsExpanded_R(){return m_bExpanded_R;};		// Output Distribution:
	virtual void		SetExpanded_R(BOOL a){ m_bExpanded_R = a;};		// Output Distribution:
	virtual int			GetMaxENodes_R(){return m_nMaxENodes_R;};	
	virtual void		SetMaxENodes_R(int nMax){m_nMaxENodes_R = nMax;};
	virtual double 		GetRadius_R(){return m_Radius_R;};
	virtual void 		SetRadius_R(double dat){m_Radius_R = dat;};
	virtual double 		GetTheta_R(){return m_Theta_R;};
	virtual void 		SetTheta_R(double dat){m_Theta_R = dat;};
	virtual WORLD 		GetCenter_R(){return m_Center_R;};
	virtual void 		SetCenter_R(WORLD dat)
						{	m_Center_R.x = dat.x;
							m_Center_R.y = dat.y;
							m_Center_R.z = dat.z;
						};
	virtual WORLD 		GetNormal_R(){return m_Normal_R;};
	virtual void 		SetNormal_R(WORLD dat)
						{	m_Normal_R.x = dat.x;
							m_Normal_R.y = dat.y;
							m_Normal_R.z = dat.z;
						};
	virtual double 		GetSegAngle_R(){return m_SegAngle_R;};
	virtual void 		SetSegAngle_R(double dat){m_SegAngle_R = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	virtual BOOL		IsHole_R(){return m_bHole_R;};
	virtual void		SetHole_R(BOOL bYes){m_bHole_R = bYes;};
	//////////////////////////////////////////////////////////////////// Derivatives
	virtual pWORLD	GetpTangents_R(){return m_pTangents_R;};
	virtual void	SetpTangents_R(pWORLD t){m_pTangents_R = t;};
	virtual pDOUBLE	GetpCurvatures_R(){return m_pCurvatures_R;};
	virtual void	SetpCurvatures_R(pDOUBLE t){m_pCurvatures_R = t;};
    //////////////////////////////////////////////////////////////////// Output
    virtual double	GetRatio_R(){return m_Ratio_R;};		// for OneSegment Linear Only
    virtual void	SetRatio_R(double r){m_Ratio_R = r;};	// for OneSegment Linear Only
	////////////////////////////////////////////////////////////// for Duct/Sweep
	virtual BOOL	IsIncTwist_R(){return m_bIncTwist_R;};
	virtual void	SetIncTwist_R(BOOL dLen){m_bIncTwist_R = dLen;};
	virtual double	GetTwistMult_R(){return m_TwistMult_R;};
	virtual void	SetTwistMult_R(double dLen){m_TwistMult_R = dLen;};
	virtual double	GetTwistStart_R(){return m_TwistStart_R;};
	virtual void	SetTwistStart_R(double dLen){m_TwistStart_R = dLen;};
	virtual BOOL	IsIncScale_R(){return m_bIncScale_R;};
	virtual void	SetIncScale_R(BOOL dLen){m_bIncScale_R = dLen;};
	virtual double	GetScaleMult_R(){return m_ScaleMult_R;};
	virtual void	SetScaleMult_R(double dLen){m_ScaleMult_R = dLen;};
	virtual double	GetScaleStart_R(){return m_ScaleStart_R;};
	virtual void	SetScaleStart_R(double dLen){m_ScaleStart_R = dLen;};
	///////////////////////////////////////////////////////////////////// PentaHedrons 
    virtual	CDListMgr*	GetPentaList(){return &m_PentaList;};
	virtual int			GetnTriangles_ST(){return m_nTriangles_ST;};	
	virtual void		SetnTriangles_ST(int nMax){m_nTriangles_ST = nMax;};
	
 	
 	
 	

protected:
	
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
	BOOL 	CullWorld(WORLD VDir);
	BOOL 	CullScreen(pMATRIX pViewM);
	///////////////////////////////////// DirtyDraw				
//void 	UnitAxisFromEndNodes();
//	void 	RefillCNEyePosForDirtyDraw();
		          

			
// Helper functions
protected:
// Attributes
 
	/////////////////////////////////
	SOLIDPROC	m_SolidProc;           // How Generated? PP_EXTRUDE etc
	SOLIDTYPE	m_SolidType;           	// PA_TENSOR, etc
	SOLSUBTYPE 	m_SolSubType;			// Tringle or Quadrilat
	CURVEPROC	m_CurveType_R;         	// PA_BEZIER, etc
	int			m_n3D;					// 1D or 2D or 3D
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
	double		m_dLen_R;
	double		m_dLenEye_R;
	WORLD		m_vAxis_R;		// unit Extrusion Axis/XFormed
	WORLD		m_vAxisEye_R;		// unit Extrusion Axis/XFormed
	/////////////////////
	CString		m_FromID_R;		// also used:AnchorID for Sweep/Duct
	CString		m_ToID_R;
//	CString		m_CurveID;      // XSec   Profile for Sweep
	/////////////////////////////////////////// Rotate
	double		m_dAng_1_R;
	double		m_dAng_2_R;
	/////////////////////////////////////////// Duct/Sweep
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
	CDListMgr	m_PentaList;			// Control Penta
	/////////////////////////
	int			m_nTriangles_ST;			//  Total No of Triangles in Base Patch




public:
	virtual ~CDrSolid();
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



