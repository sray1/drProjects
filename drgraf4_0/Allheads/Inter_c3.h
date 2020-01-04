 // Inter_C3.h : header file
//
#ifndef _INTER_C3_H 
#define _INTER_C3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
//#include "DListMgr.h"
#include "Def_Type.h"
#include "Def_CuPS.h" 
////////////////////////////                   
//typedef	double (*PDMA3)[4]; in glb_type.h
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CInter_C3 : public CObject
{
public:

	CInter_C3();
//////////////////////////////////////
	DECLARE_SERIAL(CInter_C3)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	//////////////////////////////////////////////////////////
	virtual int		Interpolate();
    ////////////////////////////////////////////////////////// Info
	virtual void	SetnData_S(int d){m_nData_S = d;};		// GIVEN: # of Data
	virtual void	SetnOrder_S(int d){m_nOrder_S = d;};				// k
	virtual void	SetbClosed_S(BOOL bC){m_bClosed_S = bC;};
//	virtual void	SetCurveType(CTyp);
	virtual void	SetKnotType_S(KNOT Kn){m_KnotType_S = Kn;};
	virtual void	SetWtType_S(WEIGHT Wt){m_WtType_S = Wt;};
	virtual void	SetBCL(BOUNDARY b){m_BCL = b;};
	virtual void	SetBCR(BOUNDARY b){m_BCR = b;};
	virtual void	SetTanL(VECTOR d){m_TanL = d;};
	virtual void	SetTanR(VECTOR d){m_TanR = d;};
	//////////////////////////////////////////////////////////
	virtual void	SetnDim_S(int d){m_nDim_S = d;};
	virtual void	SetnDegree_S(int d){m_nDegree_S = d;};				// k -1
	virtual void	SetnSeg_DT_S(int d){m_nSeg_DT_S = d;};				// L
	
//	virtual void	SetnSeg_DT_S(nSeg_DT);
//	virtual void	SetnSeg_BS_S(nSeg_BS);
	virtual void	SetnCon_BS_S(int d){m_nCon_BS_S = d;};
	virtual void	SetnKnots_S(int d){m_nKnots_S = d;};
	virtual void	SetnMKnots_S(int d){m_nMKnots_S = d;}; 
	virtual void	SetnCon_BZ_S(int d){m_nCon_BZ_S = d;};
	////////////////////////////////////////////////////////////// Memory
	virtual pDOUBLE	GetpMKnot_S(){return m_pMKnot_S;};
	virtual pDOUBLE	GetpKnot_S(){return m_pKnot_S;};
	virtual pDOUBLE	GetpWts_DT_S(){return m_pWts_DT_S;};
	virtual pDOUBLE	GetpWts_BS_S(){return m_pWts_BS_S;};
	virtual pDOUBLE	GetpWts_BZ_S(){return m_pWts_BZ_S;};
	virtual pWORLD 	GetpData(){return m_pData;};
	virtual pWORLD 	GetpCon_BS_S(){return m_pCon_BS_S;};
	virtual pWORLD 	GetpCon_BZ_S(){return m_pCon_BZ_S;};
	
	virtual void	SetpMKnot_S(pDOUBLE m){m_pMKnot_S = m;};
	virtual void	SetpKnot_S(pDOUBLE m){m_pKnot_S = m;};
	virtual void	SetpWts_DT_S(pDOUBLE m){m_pWts_DT_S = m;};
	virtual void	SetpWts_BS_S(pDOUBLE m){m_pWts_BS_S = m;};
	virtual void	SetpWts_BZ_S(pDOUBLE m){m_pWts_BZ_S = m;};
	virtual void	SetpData(pWORLD m){m_pData = m;};
	virtual void	SetpCon_BS_S(pWORLD m){m_pCon_BS_S = m;};
	virtual void	SetpCon_BZ_S(pWORLD m){m_pCon_BZ_S = m;};
	//////////////////////////////////////////////////////////
		
protected:


	//////////////////////////////////////////////////////////////////////////////////////////// SetUp
	int 	SetupWeights(enum WEIGHT WtType, pDOUBLE Wts,int nWts); 
	int 	SetupData4D(pWORLD Data, pDOUBLE Wts,int nData); 
	
	int 	SetupKnots(pWORLD Data, enum KNOT KnotType, pDOUBLE Knot,int nKnots); 
	 
	int 	SetupSystem_Close(pDOUBLE a,pDOUBLE b,pDOUBLE c,pDOUBLE Knot,int L); 
	int 	SetupSystem_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,pDOUBLE Knot,int L);
	//////////////////////////////////////////////////////////////////////////////////////////// BC 
	int 	SetupBC_Close(pWORLD d,pDOUBLE w,PDMA3 s,int L,int nDim); 
	int 	SetupBC_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
						 VECTOR ETan_L,VECTOR ETan_R,PDMA3 s,BOUNDARY BC_L,BOUNDARY BC_R,
						int L,int nDim); 
	int 	BC_Auto(pWORLD d,pDOUBLE w,PDMA3 s,ENDS BC_End,int L,int nDim); 
	int 	BC_Tangent(pWORLD d,pDOUBLE w,pDOUBLE Knot,VECTOR ETan_L,VECTOR ETan_R,
							PDMA3 s,ENDS BC_End,int L,int nDim); 
	int 	BC_Free(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim); 
	int 	BC_Bessel(pWORLD d,pDOUBLE w,pDOUBLE Knot,PDMA3 s,ENDS BC_End,
								int L,int nDim); 
	int 	BC_Quadratic(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim); 
	int 	BC_Not_A_Knot(pDOUBLE a,pDOUBLE b[],pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim);
	//////////////////////////////////////////////////////////////////////////////////////////// Solve							 
	int 	SolveSystem_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,PDMA3 RHS,PDMA3 Sol,
						int L,int nDim); 
	int 	SolveSystem_Close(pDOUBLE a,pDOUBLE b,pDOUBLE c,PDMA3 RHS,PDMA3 Sol,
						int L,int nDim); 
	//////////////////////////////////////////////////////////////////////////////////////////// Spline							 
	int 	FillUpSpline_Open(PDMA3 Sol,int L,pWORLD Data,pDOUBLE Wts_DT,
						pWORLD Con,pDOUBLE Wts,int nDim); 
	int 	FillUpSpline_Close(PDMA3 Sol,int L,pWORLD Data,pDOUBLE Wts_DT,
						pWORLD Con,pDOUBLE Wts,int nDim); 
	//////////////////////////////////////////////////////////////////////////////////////////// Bezier							 
	int 	Convert_BS2BZ(PDMA3 BS,pDOUBLE Knot,PDMA3 BZ,
						int L,BOOL bClosed,int nDim); 
	int 	Convert_BS2BZ(PDMA3 Sol,pWORLD Data,pDOUBLE w_DT,pDOUBLE Knot,
						pDOUBLE w_BZ,pWORLD Bez,int L,BOOL bClosed,int nDim); 
	int 	Set4DPreImage_BS(PDMA3 Sol,pWORLD Data,pDOUBLE w_DT,PDMA3 BS,
						int L,BOOL bClosed,int nDim);
	int 	FillUpBezier(PDMA3 BZ4,pWORLD Con,pDOUBLE Wts,int L,BOOL bClosed,int nDim); 
	///////////////////////////////////////////////////////////////////////////////
	int 	UpdateToMultKnots(pDOUBLE Knots,int nKnots,pDOUBLE MKnots,
									int nMKnots, int nOrder);
	////////////////////////////////////////////////////////////////////////////////
		          

protected:
  
// Attributes
protected:


	
	/////////////////////////////////////////// Curve
	BOOL		m_bClosed_S;
	int			m_nOrder_S;				// k
	int			m_nDegree_S;			// k -1
	int			m_nData_S;				// GIVEN: # of Data 
	int			m_nSeg_DT_S;			// L
	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// n + 1: #of Spline Controls
	int			m_nMKnots_S;			// n + k + 1 = Total
	int			m_nKnots_S;				// n - k + 3 = distinct
	int			m_nCon_BZ_S;			// (k-1) * L + 1 		
	int			m_nSegs;
	int 		m_nDim_S;
	WEIGHT		m_WtType_S;
	KNOT		m_KnotType_S;
	BOUNDARY	m_BCL;
	BOUNDARY	m_BCR;
	VECTOR		m_TanL;
	VECTOR		m_TanR;
	//////////////////////////////////////////////// Memory 
	int			m_MemErr;
	pDOUBLE		m_pMKnot_S;
	pDOUBLE		m_pKnot_S;
	pDOUBLE		m_pWts_DT_S;
	pDOUBLE		m_pWts_BS_S;
	pDOUBLE		m_pWts_BZ_S;
	pWORLD 		m_pData;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
	pDOUBLE		m_pAlf;
	pDOUBLE		m_pBet;
	pDOUBLE		m_pGam;
	PDMA3		m_pSol;
	PDMA3		m_pRHS;
    
    
//Operations
public:

	~CInter_C3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CInter_C3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
