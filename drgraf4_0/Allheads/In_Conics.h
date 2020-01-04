 // In_Circle.h : header file
//
#ifndef _IN_CONICS_H 
#define _IN_CONICS_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
//#include "DListMgr.h"
#include "Def_Type.h"
#include "Def_CuPS.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CIn_Conics : public CObject
{
public:

	CIn_Conics();
//////////////////////////////////////
	DECLARE_SERIAL(CIn_Conics)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
    ////////////////////////////////////////////////////////// Info
	virtual void	SetnData_S(int d){m_nData_S = d;};		// GIVEN: # of Data
	virtual void	SetnOrder_S(int d){m_nOrder_S = d;};				// k
	virtual void	SetbClosed_S(BOOL bC){m_bClosed_S = bC;};
	//////////////////////////////////////////////////////////
	virtual void	SetnDim_S(int d){m_nDim_S = d;};
	virtual void	SetnDegree_S(int d){m_nDegree_S = d;};				// k -1
	virtual void	SetnSeg_DT_S(int d){m_nSeg_DT_S = d;};				// L
	
//	virtual void	SetnSeg_BS_S(nSeg_BS);
	virtual void	SetnCon_BS_S(int d){m_nCon_BS_S = d;};
	virtual void	SetnCon_BZ_S(int d){m_nCon_BZ_S = d;};
	////////////////////////////////////////////////////////////// Memory
	virtual pDOUBLE	GetpWts_BS_S(){return m_pWts_BS_S;};
	virtual pDOUBLE	GetpWts_BZ_S(){return m_pWts_BZ_S;};
	virtual pWORLD 	GetpData(){return m_pData;};
	virtual pWORLD 	GetpCon_BS_S(){return m_pCon_BS_S;};
	virtual pWORLD 	GetpCon_BZ_S(){return m_pCon_BZ_S;};
	
	virtual void	SetpWts_BS_S(pDOUBLE m){m_pWts_BS_S = m;};
	virtual void	SetpWts_BZ_S(pDOUBLE m){m_pWts_BZ_S = m;};
	virtual void	SetpData(pWORLD m){m_pData = m;};
	virtual void	SetpCon_BS_S(pWORLD m){m_pCon_BS_S = m;};
	virtual void	SetpCon_BZ_S(pWORLD m){m_pCon_BZ_S = m;};
	//////////////////////////////////////////////////////////
							
							
		
protected:

			int		GetPlanarCoords(WORLD b0,WORLD b1,WORLD b2,WORLD pt,
								pWORLD b02,pWORLD b12,pWORLD b22,pWORLD pt2);
			int		Rat_Subdivide_Conic(WORLD b0,WORLD b1,WORLD b2,WORLD pt,WORLD BCC,
									pWORLD pc1L,pDOUBLE pw1L,pWORLD pc1R,pDOUBLE pw1R);
			int		FindBaryfor3rdPt(WORLD b0,WORLD b1,WORLD b2,WORLD pt,pWORLD pBCC);
			int		Compute_w1(WORLD pBCC,pDOUBLE pw1);
			//////////////////////////////////////////////////////////////// SetUp
			int		FillUpBezier(pWORLD Data,pWORLD Con,pDOUBLE Wts,pWORLD InData,pDOUBLE InWts,
																int nCon,int L,BOOL bClosed);
			int 	FillUpSpline(pWORLD Con_BZ, pDOUBLE Wts_BZ,int nCon_BZ,
							 pWORLD Con_BS, pDOUBLE Wts_BS,int nCon_BS, int L, BOOL bClosed);
			/////////////////////////////////////////////////////////////////
		          

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
	int			m_nCon_BZ_S;			// (k-1) * L + 1 		
	int 		m_nDim_S;
	//////////////////////////////////////////////// Memory 
	int			m_MemErr;
	pDOUBLE		m_pWts_BS_S;
	pDOUBLE		m_pWts_BZ_S;
	pWORLD 		m_pData;
	pWORLD 		m_pDat_Ex;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
	pWORLD 		m_pInCon_BZ_S;	// temporary In-between bezier pts
	pDOUBLE		m_pInWts_BZ_S;	// temporary In-between bezier wts
    
    
//Operations
public:

	~CIn_Conics();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CIn_Conics)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
