 // CMI_GangC : header file
//
#ifndef _MI_GANGC_H 
#define _MI_GANGC_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "MI_GangN.h"
#include "drcurve.h"
#include "drNode.h"
#include "DrLabel.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "Def_CuPS.h"                    
#include "Str_CuPS.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_GangC : public CMI_GangN
{
public:

	CMI_GangC();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_GangC)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	/////////////////////////////////////////////////////////////////// Post
/*
//	Moved to CreOMgr Dll   01/14/98 
	CDrCurve*	PostCurve(CString& Cid,CString& OldID,CURVEPROC CProc);
//	Moved to CreOMgr Dll   01/14/98 end 
*/
	/////////////////////////////////////////// Tan/Twist/Curvature manipulation
	int			WORtoWOP_VECTOR(VECTOR& TanI);
	int			WORtoWOP_WORLD(WORLD& TanI);
	int			WOPtoWOR_VECTOR(VECTOR& TanI);
	int			WOPtoWOR_WORLD(WORLD& TanI);
	///////////////////////////////////////
	int			CreateBezCNsFromTanEnds_Cubic(CDrCurve* pCurve);
	////////////////////////////////////////////////////////////////////////////
	int			CreateCurveAnyType(CDrCurve* pCurve,CURVEDATA& CDat);
	CDrCurve*	CreateCurve(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
					CURVEPROC kind,CList<int,int>* pElperSegList,
					BOOL bAdvanceOn,BOOL bFinal);
	////////////////////////////////////////////////////////////////////////////
	int			GenerateCurveVNodes(CDrCurve* pCurve,CString& CurrentNodeID);
    				
		
public:

	int			SetupKnots(pWORLD Data, enum KNOT KnotType, pDOUBLE Knot,int nKnots);
	///
	BOOL		IsNoDefault(){return m_bNoDefault;};
	void		SetNoDefault(BOOL b){m_bNoDefault = b;};
	///////
	BOOL		IsAxisInput(){return m_bAxis;};	// if Axis Input
	void		SetAxisInput(BOOL b){m_bAxis = b;};	// Set if Axis Input
	int			GetAxis(){return m_nAxis;};		// 1=X/2=Y/3=Z
	void		SetAxis(int a){m_nAxis = a;};		// 1=X/2=Y/3=Z
	BOOL		IsNegative(){return m_bNegative;};
	void		SetNegative(BOOL b){m_bNegative = b;};
	////////////////////////////////////////////////// Posting Helper
	void		SetIsoInfoForCurveBase(CDrCurve* pDrObject);
	void		SetDefaultInfoForCurveBase(CDrCurve* pDrObject);
	void		SetInfoForCurveBase(CDrCurve* pDrObject,CList<int,int>* pElperSegList,
													BOOL bFinal);
	/////////////////
	int 		SetUpINodes(CDListMgr* pList,pWORLD inData,int nData);
	void		SetUpINodes_Wts(CDListMgr* pList,pWORLD pInDat,pDOUBLE pInWts,int nData);
	int			FillMeshNodesCurve(CDrCurve* pDrCurve, pWORLD pOut, pDOUBLE pOutWts, int nOut);
	int			FillMeshTangentsCurve(CDrCurve* pDrCurve, pWORLD pOut, int nOut);
	int 		InsertAllInfo_Curve(BOOL bLoft);
	////////////////////////		          
	BOOL		GetbBack(){return m_bBack;};;
	void		SetbBack(BOOL b){m_bBack = b;};
	//////////////////////////////////////////////////////////		          
	BEZIERTYPE	GetBezierType(){return m_BezierType;};;
	void		SetBezierType(BEZIERTYPE b){m_BezierType = b;};
	int			SetBZ_Knots(CDrCurve* pCurve);
	void		SetInfoForBezierPtsBase(CDrCurve* pDrObject,CList<int,int>* pElperSegList,
													BOOL bFinal);



protected:  
// Attributes


	BEZIERTYPE	m_BezierType;
	BOOL		m_bNoDefault;
	//////////////////////////////////// Needed for Circle/Ellipse
	int			m_nBSeg_Ex_S;
	pINT		m_pBSeg_Ex_S;
	////////////////////////////////////
	BOOL		m_bFinal;
	////////////////////////////////////
	BOOL		m_bUnifOT;
	BOOL		m_bBack;
	//////////////////////////////////// ControlNodes Draw
	int			m_nDim_S;
	int			m_nSegs_SCon;
	int			m_nOut_SCon;
	long		m_nOutCon;
	////////////////////////////////
	BOOL		m_bClosed_S;
	int			m_nSegs_S;
	int			m_nOut_S;
	//////////////////////////////// Memory Curve
	CDListMgr*	m_pINodeList;
	CDListMgr* 	m_pCNodeList;
	pINT		m_pNum_t_S;
	pINT		m_pNum_t_Ex_S;
	long		m_nOut;
	/////////////////////////////////////////// Circle/Extrude
	CIRCLETYPE	m_nType;	// 
	double		m_SegAngle;
	double		m_dAngSpec;
	double		m_dAng;
	BOOL		m_bArc;
	int			m_nMesh;
	double		m_Ratio_S;
	CDrNode*	m_pFromIDNode;
	CDrNode*	m_pToIDNode;
	WORLD		m_vAxis_S;  
	BOOL		m_bUnifOT_S;
	/////////////////////////////////////////// Rotate
	WORLD		m_Center_S;
	double		m_Radius_S;
	double		m_dAng1_S;
	double		m_dAng2_S;
	WORLD 		m_FromPt_S;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPt_S;		// used also for Sweep/Duct Anchor
	///////
	BOOL		m_bAxis;	// if Axis Input
	int			m_nAxis;		// 1=X/2=Y/3=Z
	BOOL		m_bNegative;
	/////////////////////////////////////////// Curve
	int			m_nMaxCurveCNodes_S;
	int			m_nMaxCurveINodes_S;
	//////////////////////////////
	CDrCurve* 	m_pDrCurve;
	int			m_nSegsOut_S;				// for Uniform Output
	////////////////////////
	int			m_nInputType;
	CURVEPROC	m_CurveType_S;
	int			m_nOrder_S;				// k
	int			m_nDegree_S;			// k -1
	int			m_nData_S;				// GIVEN: # of Data 
	int			m_nSeg_DT_S;			// L
	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// n + 1: #of Spline Controls
	int			m_nMKnots_S;			// n + k + 1 = Total
	int			m_nKnots_S;				// n - k + 3 = distinct
	int			m_nCon_BZ_S;			// (k-1) * L + 1  = m_nMaxCurveCNodes 		
//	int 		m_nDim_S;
	WEIGHT		m_WtType_S;
	KNOT		m_KnotType_S;
	BOUNDARY	m_BCL;
	BOUNDARY	m_BCR;
	VECTOR		m_TanL;
	VECTOR		m_TanR;
	//////////////////////////////////////////////////////////// Circle
	double		m_theta;
	//////////////////////////////////////////////////////////// Memory
	int			m_MemErr;
	pDOUBLE		m_pMKnot_S;
	pDOUBLE		m_pKnot_S;
	pDOUBLE		m_pWts_BS_S;
	pDOUBLE		m_pWts_BZ_S;
	pDOUBLE		m_pWts_DT_S;
	pWORLD 		m_pData;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
	pDOUBLE		m_pDisAng_S;
    /////////////////////////////////////////// Next
//	pDOUBLE		m_pOutWts;		// wiil be deleted in CDrCurve.h
    pWORLD		m_pOut;			// = m_pCon_BZ_S: Bezier
///////////////////////////////////////////////////////////////////////// CDlg_CIRR)
	int			m_nControls;		// L + k - 1 = nData + k - 2 = n + 1 (B-Spline)
	int			m_nCurveSeg;		// L 	= nData - 1	, Open
	CString		m_CurveID;
	int			m_nMaxOSeg;
	int			m_nMaxDistinct;		// n - k + 3 = nData				Knots, Weights
	int			m_nMaxTotal;		// n + k + 1 = nData + (2k - 2)		Knots, Weights
	KNOT		m_Typ_KN;
	WEIGHT		m_Typ_WT;
	/////////////////////
	pDOUBLE		m_pKVal;
	pDOUBLE		m_pWVal;
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	///////////////////////////////////////////////////////




//Operations
public:

	~CMI_GangC();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_GangC)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
