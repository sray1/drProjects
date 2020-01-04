// DrCurve.h : header file
//
#ifndef _DRCURVE_H_
#define _DRCURVE_H_       

#include "DrObject.h"
//#include "DrObj3D.h"
#include "DListMgr.h"
#include "glb_CuPS.h"	// enum CURVETYPE			

//#pragma warning( disable : 4200 )
#include "glb_Rend.h" 	// Render Attribs.
/////////////////////////////////////////////////////////////////////////////
// CDrCurve    ///////////////////////////////////////////////////////////////
class CDrCurve: public CDrObject
{
public:
// Construction                 
	CDrCurve();
	DECLARE_SERIAL(CDrCurve);
	
	
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
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect); 		// control Node Hit
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual CDListMgr* 	GetCProfList(){return &m_CProfList;};
	virtual CDListMgr* 	GetObj3DList(){return &m_Obj3DList;};
    virtual	CDListMgr*	GetCNodeList(){return &m_CNodeList;};
    virtual	CDListMgr*	GetCN_BSList(){return &m_CN_BSList;};
    virtual	CDListMgr*	GetINodeList(){return &m_INodeList;};
    virtual	CDListMgr*	GetENodeList(){return &m_ENodeList;};
    virtual	CDListMgr*	GetNodeList(){return &m_NodeList;};
    virtual	CDListMgr*	GetElemList(){return &m_ElemList;};
    virtual	CDListMgr*	GetPatchList(){return &m_PatchList;};
	//////////////////////////////////////////////////////////////////////						
	virtual	int			GetCompoType(){return m_nCompoType;};
	virtual	void		SetCompoType(int CT){m_nCompoType = CT;};
	virtual	CString&	GetCompoID(){return m_CompoID;};
	virtual	void		SetCompoID(CString& id){m_CompoID = id;};
	virtual BOOL		IsInstanced(){return m_bInstanced;};
	virtual void		SetInstanced(BOOL bi){m_bInstanced = bi;};
	virtual int 		AppendToObject
						(	
							CDListMgr* pObj3DList,
							CDListMgr* pElemList, 
							CDListMgr* pNodeList,
							CDListMgr* pCNodeList,
							CDListMgr* pINodeList,
							CDListMgr* pENodeList,
							CDListMgr* pCProfList,
							CDListMgr* pPatchList
						);
	virtual	int 		SetLocalTransform(pMATRIX xF);
	virtual	int 		CatLocalTransform(pMATRIX xF);
	virtual	int 		GetLocalTransform(pMATRIX xF);
	virtual	pRENDINFO	GetRInfo(){return &m_RInfo;};
	virtual	void 		SetRInfo(pRENDINFO pRA);
	////////////////////////////////////////////////////////////////////
	virtual int			GetSegmentCount_S(){return m_nSegUnif_S;};
	virtual void		SetSegmentCount_S(int nSegs){m_nSegUnif_S = nSegs;};
	virtual BOOL		IsClosed_S(){return m_bClosed_S;};
	virtual void		SetClosed_S(BOOL bYes){m_bClosed_S = bYes;};
	virtual int			GetCurveObjectType(){return m_nCurveObjectType;};
	virtual void		SetCurveObjectType(int nType){m_nCurveObjectType = nType;};
	virtual int			GetMaxINodes_S(){return m_nMaxINodes_S;};
	virtual void		SetMaxINodes_S(int nMax){m_nMaxINodes_S = nMax;};
	virtual int			GetMaxCNodes_S(){return m_nMaxCNodes_S;};
	virtual void		SetMaxCNodes_S(int nMax){m_nMaxCNodes_S = nMax;};
	virtual int			GetMaxCubicCurves(){return m_nMaxCurves;};
	virtual void		SetMaxCubicCurves(int nMax){m_nMaxCurves = nMax;};
	virtual int			GetMaxOutPts_S(){return m_nMaxOutPts_S;};
	virtual void		SetMaxOutPts_S(int nMax){m_nMaxOutPts_S = nMax;};
	virtual long		GetLongOutPts(){return m_nOut;};
	virtual void		SetLongOutPts(){m_nOut = (long)m_nMaxOutPts_S;};
	virtual CURVETYPE 	GetCurveType(){return m_CurveType;};
	virtual void		SetCurveType(CURVETYPE kind){m_CurveType = kind;};
    //////////////////////////////////////////////////////////////
	virtual int 		NumberOfLinearCurves(enum CURVETYPE kind,int nMaxCurveCNodes,
										int* pnCurves,BOOL bClosed);
	virtual int 		NumberOfQuadraticCurves(enum CURVETYPE kind,int nMaxCurveCNodes,
										int* pnCurves,BOOL bClosed);
	virtual int 		NumberOfCubicCurves(enum CURVETYPE kind,int nMaxCurveCNodes,
										int* pnCurves,BOOL bClosed);
	virtual int 		GenerateCurve(pWORLD pOut);		// 
/*	
						(
							enum CURVEOUTPUT	O_kind		// Output Method
						,	enum CURVETYPE	kind
						,	int				nC				// number of CONTROL points
						,	pWORLD			pInC            // Total CONTROL Points Array
						,	int 			nMaxOutSeg		// Number of Output Segments on ENTIRE Curve
						,	int				Num_t[]			// Number of Outputs for each Output Segment
						,	double			Dis_t[]			// Output t-distribution array:
						,	pWORLD			pOut            // Total Output Points Array
						,	int				nCurves			// Total Number of Cubic Curves 
						,	int				nOut			// expected number of generated curve vertices
						);
*/						
	virtual 	CURVEOUTPUT		GetOutMethod(){return m_OutMethod;};	// Output Method
	virtual 	double			GetAlfa(){return m_alfa_S;};			// Cardinal Spline (Catmull-Rom Modified)	
	virtual 	double			GetBias(){return m_bias_S;};			// beta
	virtual 	double			GetTension(){return m_tension_S;};		// beta and hermite
//	virtual 	int				GetNumOfKnot(){return m_nKnot_S;};		// number of KNOTs == number of Curves+1		
//	virtual 	pDOUBLE			GetInKnotPointer(){return m_pInKnot_S;};	// Total input KNOT Value Array
//	virtual 	pWORLD			GetOutKnotPointer(){return m_pOutKnot_S;};	// Total Output KNOT Points Array (for drawing)
    ///////////////////////////////////////////////////////
	virtual 	BOOL			IsUniform(){return m_bUniform_S;};		// Output Distribution:
	virtual 	void			SetUniform(BOOL a){ m_bUniform_S = a;};		// Output Distribution:
	virtual 	void			SetOutMethod(CURVEOUTPUT a){ m_OutMethod = a;};	// Output Method
	virtual 	int				GetMaxOutSeg(){return m_nMaxOutSeg;};		// Number of Output Segments on ENTIRE Curve
	virtual 	void			SetMaxOutSeg(int a){m_nMaxOutSeg = a;};		// Number of Output Segments on ENTIRE Curve
	virtual 	pINT			GetNum_tPointer(){return m_pNum_t_S;};			// Number of Outputs for each Output Segment
	virtual 	void			SetNum_tPointer(pINT a){m_pNum_t_S =a;};			// Number of Outputs for each Output Segment
	virtual 	pDOUBLE			GetDis_tPointer(){return m_pDis_t_S;};	// Output t-distribution array:
	virtual 	void			SetDis_tPointer(pDOUBLE a){m_pDis_t_S = a;};	// Output t-distribution array:
    ///////////////////////////////////////////////////////
	virtual 	void			SetAlfa(double a){ m_alfa_S = a;};			// Cardinal Spline (Catmull-Rom Modified)	
	virtual 	void			SetBias(double a){ m_bias_S = a;};			// beta
	virtual 	void			SetTension(double a){ m_tension_S = a;};	// beta and hermite
	///////////////////////////////////////////////////																							
	virtual 	pWORLD			GetMemIn(){return m_pIn;};
	virtual 	POINT*			GetMemInDP(){return m_pInDP;};
	virtual 	pWORLD			GetMemOut(){return m_pOut;};
	virtual 	POINT*			GetMemOutDP(){return m_pOutDP;};
	/////////////////////////////////////////////////// Memory						
	virtual 	pWORLD 			FixMem(long nOut)
								{
									pWORLD pOut;
									return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
								};
	
	virtual 	void 			FreeMem(pWORLD pOut){delete[] pOut;};
	/////////////////////////
	virtual 	POINT* 			FixMemDP(long nOut)
				{
					POINT* pOut;
					return ((pOut = new POINT[nOut]) == NULL)? (POINT*)NULL:pOut;
				};
	
	virtual void 	FreeMemDP(POINT* pOut){delete[] pOut;};
	//////////////////////////////////////////
	virtual void 	RefillCNLocalPosForPosting();
	virtual void 	RefillCNEyePosForDirtyDraw();
	////////////////////////////////////////////////////////////// interpolation
	virtual int 		GetData_S(){return m_nData_S;};
	virtual void 		SetData_S(int ndat){m_nData_S = ndat;};
	virtual int 		GetOrder_S(){return m_nOrder_S;};
	virtual void 		SetOrder_S(int nOrd){m_nOrder_S = nOrd;};
	virtual KNOT		GetKnotType_S(){return m_KnotType_S;};
	virtual void		SetKnotType_S(KNOT Kn){m_KnotType_S = Kn;};
	virtual WEIGHT		GetWtType_S(){return m_WtType_S;};
	virtual void		SetWtType_S(WEIGHT W){m_WtType_S = W;};
	virtual BOUNDARY	GetBCL(){return m_BCL;};
	virtual void		SetBCL(BOUNDARY bc){m_BCL = bc;};
	virtual BOUNDARY	GetBCR(){return m_BCR;};
	virtual void		SetBCR(BOUNDARY bc){m_BCR = bc;};
	virtual VECTOR		GetTanL(){return m_TanL;};
	virtual void		SetTanL(VECTOR T){m_TanL = T;};
	virtual VECTOR		GetTanR(){return m_TanR;};
	virtual void		SetTanR(VECTOR T){m_TanR = T;};
	virtual int			GetnCon_BS_S(){return m_nCon_BS_S;}; 			
	virtual void		SetnCon_BS_S(int bs){m_nCon_BS_S = bs;}; 		
	virtual int			GetnCon_BZ_S(){return m_nMaxCNodes_S;};		// m_nMaxCNodes_S 			
	virtual void		SetnCon_BZ_S(int bs){m_nMaxCNodes_S = bs;}; 		
	virtual int			GetnMKnots_S(){return m_nMKnots_S;}; 			
	virtual void		SetnMKnots_S(int bs){m_nMKnots_S = bs;}; 		
	virtual int			GetnKnots_S(){return m_nKnots_S;}; 			
	virtual void		SetnKnots_S(int bs){m_nKnots_S = bs;}; 		
	virtual int			GetnDim_S(){return m_nDim_S;}; 			
	virtual void		SetnDim_S(int bs){m_nDim_S = bs;}; 		
	////////////////////// Memory for Interpolation
	virtual pDOUBLE		GetpMKnots_S(){return m_pMKnots_S;};			//---|	
	virtual void		SetpMKnots_S(pDOUBLE p){m_pMKnots_S = p;};	//---|	 THESE ACTUALLY
	virtual pDOUBLE		GetpWts_BS_S(){return m_pWts_BS_S;};		//---|-- WE DO NOT NEED, OUR	
	virtual void		SetpWts_BS_S(pDOUBLE p){m_pWts_BS_S = p;};	//---|   INTERNAL REPRESENTATION:
//	virtual pWORLD		GetpCon_BS_S(){return m_pCon_BS_S;};		//---|   ALWAYS - B E Z I E R	
//	virtual void		SetpCon_BS_S(pWORLD p){m_pCon_BS_S = p;};	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	virtual pDOUBLE		GetpKnots_S(){return m_pKnot_S;};				// User Need	
	virtual void		SetpKnots_S(pDOUBLE p){m_pKnot_S = p;};
	virtual pDOUBLE		GetpWts_DT_S(){return m_pWts_DT_S;};			// User Need	
	virtual void		SetpWts_DT_S(pDOUBLE p){m_pWts_DT_S = p;};
	virtual pDOUBLE		GetpWts_BZ_S(){return m_pWts_BZ_S;};			// Rational Need		
	virtual void		SetpWts_BZ_S(pDOUBLE p){m_pWts_BZ_S = p;};
//	virtual pWORLD		GetpCon_BZ_S(){return m_pCon_BZ_S;};			// stored in CNodeList	
//	virtual void		SetpCon_BZ_S(pWORLD p){m_pCon_BZ_S = p;};
	//////////////////////////////////////////////////////////////////// CONICS
	virtual int			GetMaxENodes_S(){return m_nMaxENodes_S;};	
	virtual void		SetMaxENodes_S(int nMax){m_nMaxENodes_S = nMax;};
	virtual double 		GetRadius_S(){return m_Radius_S;};
	virtual void 		SetRadius_S(double dat){m_Radius_S = dat;};
	virtual double 		GetTheta_S(){return m_Theta_S;};
	virtual void 		SetTheta_S(double dat){m_Theta_S = dat;};
	virtual WORLD 		GetCenter_S(){return m_Center_S;};
	virtual void 		SetCenter_S(WORLD dat)
						{	m_Center_S.x = dat.x;
							m_Center_S.y = dat.y;
							m_Center_S.z = dat.z;
						};
	virtual double 		GetSegAngle_S(){return m_SegAngle_S;};
	virtual void 		SetSegAngle_S(double dat){m_SegAngle_S = dat;};
	//////////////////////////////////////////////////////////////////// Hole?
	virtual BOOL		IsHole_S(){return m_bHole_S;};
	virtual void		SetHole_S(BOOL bYes){m_bHole_S = bYes;};

protected:
	
	

#ifdef _DEBUG	
	void 	DrMessageBox(CString& str);
#endif	
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
 
	int			m_nCompoType;			// pipe,beam(Grid 1D) or BoundaryCondition Elem
										// Triangle/Rect(2D) for patch
										// Cube/thk.shell(3D)for solid
	CString		m_CompoID;										
	/////////////////////////////////
	CDListMgr	m_ENodeList;       // Expanded   Nodes Pointers  needed for CONICS
	CDListMgr	m_INodeList;       // Input   Nodes Pointers  needed for delete
	CDListMgr	m_CNodeList;       // Control Nodes Pointers  needed for delete: Bezier	  Control Net	
	CDListMgr	m_CN_BSList;       // Control Nodes Pointers  needed for delete: B-Spline Control Net
	CDListMgr	m_NodeList;        // Mesh    Nodes Pointers   "      "    "
	CDListMgr	m_ElemList;        // DrObject Pointers        "      "    "
	CDListMgr	m_PatchList;       // DrObject Pointers        "      "    "
	CDListMgr	m_Obj3DList;       // DrObject Pointers        "      "    "
	CDListMgr	m_CProfList;       // Curve Profile List needed for later deleting
    /////////////////////////////////
	MATRIX		m_instanceXf;
	RENDINFO	m_RInfo;
	BOOL		m_bInstanced;
	int			m_nSegUnif_S;
	BOOL		m_bClosed_S; 
	int			m_nMaxINodes_S;
	int			m_nMaxCNodes_S;			// INTERNALLY: WE ALWAYS STAY WITH  B E Z I E R
	CURVETYPE	m_CurveType;
	int			m_nMaxCurves;      		// No. of Cubic Curves
	int			m_nCurveObjectType;		// ObjectType to create; -1 = no creation reqd
	BOOL		m_bDirty;				// ObjectType NOT SAVED	
	BOOL		m_bPosted;				// ObjectType NOT SAVED	
    BOOL		m_bControlDraw;
    ////////////////////////////////////// Memory
	pWORLD		m_pIn;		// Control Nodes -WorldCoords
	POINT*		m_pInDP;    // Control Nodes -ScreenCoords
	pWORLD		m_pOut;		// Output  Nodes -World or Eye Pos
	POINT*		m_pOutDP;   // Output  Nodes -ScreenCoords
	long		m_nOut;
	////////////////////////////////////////////////////////////////////////////////
	double		m_alfa_S;			// Cardinal Spline (Catmull-Rom Modified)	
	double		m_bias_S;			// beta
	double		m_tension_S;		// beta and hermite
	///////////////////////////////////////////////////////////////////////////////onstruct Æ?ClipLine_SCòñ È?ClipPtóòñ É?ClipLine_LBòñ Ë?SetzMinòñ Í?GetzMinòñ Ï?SetPerspectiveóòñ Ñ?GetPerspectiveóòñ Ò?SetCanonicalñ Ó?GetCanonicalñ Õ?PushDownñ Õ?PushUpóòñ Õ?PushLeftñ Õ?	PushRight Õ?	PushFront Õ?PushBackñ Ø?Pushñ Ú?
ClipEncodeóòñ Ý?	ClipPt_LBA   m_dzMinr   m_bPerñr   m_bCanonóòñ Þ?~CDrClipñ™   ß?   ©  CDrClip*    NOT_VISIBLEòñ  YES_VISIBLEòñG   r á?  
VISIBILITYñ<
  Ó=„  W		
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	int			m_nOrder_S;				// k
	int			m_nData_S;				// GIVEN: # of Data 		= m_nMaxINodes_S  
//	int			m_nSeg_DT_S;			// L = #of CurveSegments 	= m_nMaxCurves 
//	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// n + 1: #of Spline Controls// for drawing ControlNet
	int			m_nMKnots_S;			// n + k + 1 = Total		// Not Need
	int			m_nKnots_S;				// n - k + 3 = distinct		// User Need
//	int			m_nCon_BZ_S;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	int 		m_nDim_S;				// 4 = RATIONAL/	3 = NONrational 
	WEIGHT		m_WtType_S;
	KNOT		m_KnotType_S;
	BOUNDARY	m_BCL;
	BOUNDARY	m_BCR;
	VECTOR		m_TanL;
	VECTOR		m_TanR;
	////////////////////// Memory for Interpolation
	pDOUBLE		m_pMKnots_S;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pDOUBLE		m_pWts_BS_S;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	pWORLD		m_pCon_BS_S;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		m_pKnot_S; 	// distinct( for User Need)
	pDOUBLE		m_pWts_DT_S;	// for User Need
	pDOUBLE		m_pWts_BZ_S;
//	pWORLD 		m_pCon_BZ;	// stored in m_CNodeList
	//////////////////////////////////////////////////////////////////// CONICS
	int			m_nMaxENodes_S;
	WORLD		m_Center_S;	// Circle
	double		m_Radius_S;
	double		m_Theta_S;
	double 		m_SegAngle_S;
	//////////////////////////////////////////////////////////////////// Hole?
	BOOL		m_bHole_S;
	


    
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
/////////////////////////////////////////////
#endif                                       



