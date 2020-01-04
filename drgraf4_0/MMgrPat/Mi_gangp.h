 // ELMouse.h : header file
//
#ifndef _MI_GANGP_H 
#define _MI_GANGP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "Mi_GangC.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "Def_Cups.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMI_GangP : public CObject
//class CMI_GangP : public CObject
class AFX_EXT_CLASS CMI_GangP : public CMI_GangC
{
public:

	CMI_GangP();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_GangP)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

 	void		SetInfoForCoonBase(CDrPatch* pDrObject, PATSUBTYPE pstCoon);
/*
	/////////////////////////////////////////////////////////////////// Post
//	Moved to CreOMgr Dll   01/14/98 
	CDrPatch*	PostPatch(CString& Cid,CString& OldID,PATCHPROC PProc);
//	Moved to CreOMgr Dll   01/14/98 end 
*/
	/////////////////////////////////////////////////////////////////////////
	int			SetPatchOutputDataFromCurve(CDrCurve* pCurve,int nDir);
	//////////////////////////////////////////////////////// Curve/Patch
	int			DeleteCurves_LockStock(CDListMgr* pCurveList);
	int			ReParametrizeBezWeightsToStdForm(CDrCurve* pCurve);
    void		GetInfo_Curve(CDrCurve* pDrCurve);
	////////////////////////////////////////
	void		UnitAxisFromEndNodes(int nType);
	double		UnitAxis_N_LenFromWorldLength();
	//////////////////////////////////////////////////////////////////////////////
	int 		CurveNodesSaveAsCNodes(CDListMgr* pListTemp,int tIndex);
//	int 		Gen_Curve(CDrCurve* pDrCurve,pWORLD pIn,pWORLD pOut,int nOut);
	void 		FillCNodesLOCAL(CDListMgr* pCurveCNodeList,pDOUBLE pWts_S,
						pWORLD pIn,pDOUBLE pInWts,int nMaxCNodes,
						BOOL bSave);
	int			FillMeshNodesPatch(CDrPatch* pDrPatch, pWORLD pOut, pDOUBLE pOutWts );
	int			FillMeshTangentsInOneDirPatch(CDrPatch* pDrPatch, pWORLD pOut, int nIsoDir );
	int			FillMeshTangentsPatch(CDrPatch* pDrPatch, pWORLD pOut_S, pWORLD pOut_T );
	int			FillMeshNormalsPatch(CDrPatch* pDrPatch, pWORLD pOut );
//	int			FillMeshNodes(CDrCurve* pDrCurve, pWORLD pOut, pDOUBLE pOutWts, int nOut);
	int 		InsertMeshInfo(BOOL bLoft);
//	CDrNode* 	PostNode(CString& Nid,WORLD Pt,BOOL bCNode);
	////////////////////////////////////////////////////////////////////////////// Triangular Patch
	int			InsertMeshInfo_3();
	int			InsertTriangle_Linear();
	int			StoreType_1_Lin(int i, int j, int nP, CDListMgr* pTriList);
	int			StoreType_2_Lin(int i, int j, int nP, CDListMgr* pTriList);
	int			InsertTriangle_Quad();
	int			StoreType_1_Quad(int i, int j, int nP, CDListMgr* pTriList);
	int			StoreType_2_Quad(int i, int j, int nP, CDListMgr* pTriList);
	int			InsertTriangle_Cubic();
	int			StoreType_1_Cubic(int i, int j, int nP, CDListMgr* pTriList);
	int			StoreType_2_Cubic(int i, int j, int nP, CDListMgr* pTriList);


protected:  
// Attributes

	CString		m_PatchID;
	double		m_Ratio_T;
	int			m_nMaxOSeg_S;
	int			m_nMaxOSeg_T;
	BOOL		m_bUnifOT_T;
	pINT		m_pOSeg_S;
	pINT		m_pOSeg_T;
	pDOUBLE		m_pODis_S;
	pDOUBLE		m_pODis_T;
	////////////////////////
	int			m_nNodes_S;	// for Tensor Product
	int			m_nNodes_T;
	BOOL		m_bAdvancedEnd_T;
	PWMAT2		m_pCornerTwist_T;// it is full,if TW_USER
	TWIST		m_TwistMethod_T;
	BOOL		m_bGenBCur;
	PATCHPROC	m_PatchProc;
	PATSUBTYPE	m_PatSubType;
	////////////////////////
//	BOOL		m_bUnifOT;
	pDOUBLE		m_pWts_BZ_T;
	/////////////////////////
	int			m_nMaxCurveCNodes_T;	// in T-dir
	PATCHTYPE	m_PatchType;           	// P_MESH,P_EXTRUDE etc
//	CURVEPROC	m_CurveType_S;         	// CU_BEZIER etc
	CURVEPROC	m_CurveType_T;         	// CU_BEZIER etc
//	int			m_nOrder_S;
	int			m_nOrder_T;
	//////////////////////////////////// ControlNodes Draw
//	int			m_nDim_S;
	int			m_nDim_T;
//	int			m_nSegs_SCon;
	int			m_nSegs_TCon;
//	int			m_nOut_SCon;
	int			m_nOut_TCon;
//	long		m_nOutCon;
	/////////////////////////////////////////// Mesh
	BOOL		m_bDirtyPatch; //True: Indivual Elements NOT SAVED yet    
	CDrPatch* 	m_pDrPatch;
	CString 	m_CurrentPatchID;
	int			m_nMaxPatchCNodes;
	int			m_nMaxPatchCNodes_S;
	int			m_nMaxPatchCNodes_T;
	////////////////////////////////
//	BOOL		m_bClosed_S;
	BOOL		m_bClosed_T;
//	int			m_nSegs_S;
	int			m_nSegs_T;
//	int			m_nOut_S;
	int			m_nOut_T;
	int 		m_nPatches_S;	// formerly: m_nCubicPatches_S;
	int 		m_nPatches_T;	// formerly: m_nCubicPatches_T;
	//////////////////////////////// Memory Curve/Patch
	CDListMgr* 	m_pCNodeList;
//	BOOL		m_bBack;
	pWORLD		m_pIn_S[4];
	pDOUBLE		m_pInWts_S[4];
//	pWORLD		m_pOut;
	pDOUBLE		m_pOutWts;		// wiil be deleted in CDrCurve.h
	pINT		m_pNum_t_S;
	pINT		m_pNum_t_T;
	pDOUBLE		m_pDis_t_S;
	pDOUBLE		m_pDis_t_T;
	pINT		m_pNum_t_Ex_S;
	pINT		m_pNum_t_Ex_T;	// for rotation:Circle
	long		m_nOut;
	/////////////////////////////////////////// Extrude
	double		m_Ratio;
//	CString		m_FromID;
//	CString		m_ToID;
	CString		m_CurveID;
	WORLD		m_vAxis;  
	double		m_dLen;
	WORLD		m_wLen;
	int			m_nExtruType;		// default set to 1
	/////////////////////////////////////////// Rotate
	pDOUBLE		m_pDisAng_T;//	Angle Distribution for 
							//	each Bez Patch in degrees
//	double		m_Ratio;
//	CString		m_FromID;
//	CString		m_ToID;
//	CString		m_CurveID;
//	WORLD		m_vAxis;  
	double		m_dAng_1;
	double		m_dAng_2;
	WORLD 		m_FromPt;	// used also for Sweep/Duct Anchor
	WORLD 		m_ToPt;		// used also for Sweep/Duct Anchor
	/////////////////////////////////////////// Duct
	CString		m_CurveID_S[4];
	CDrCurve*	m_pCurve_S[4];
	CURVELATCH	m_CuLatch[4];
	double		m_TwistStart;
	double		m_TwistMult;
	BOOL		m_bIncTwist;
//	CString		m_FromID;
//	WORLD		m_FromPt;
	/////////////////////////////////////////// Sweep 
//	CString		m_FromID;
//	WORLD		m_FromPt;
	double		m_ScaleStart;	// for Sweep
	double		m_ScaleMult;	// for Sweep
	BOOL		m_bIncScale;
	/////////////////////////////////////////// Loft2
    CDListMgr 	m_CNListLoft;//Temporary for Manipulation
	/////////////////////////////////////////// 
//	double		m_ratio;
//	CString		m_CurveID;
	////////////////////////

//Operations
public:

	~CMI_GangP();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_GangP)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
