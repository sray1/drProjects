 // Inter_C1.h : header file
//
#ifndef _INTER_C1_H 
#define _INTER_C1_H 
                    
#include "drcurve.h"
//#include "DListMgr.h"
#include "glb_Type.h"
#include "glb_CuPS.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CInter_C1 : public CObject
{
public:

	CInter_C1();
	DECLARE_SERIAL(CInter_C1)


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
	//////////////////////////////////////////////////////////
	virtual void	SetnDegree_S(int d){m_nDegree_S = d;};				// k -1
	virtual void	SetnSeg_DT_S(int d){m_nSeg_DT_S = d;};				// L
	
	virtual void	SetnCon_BS_S(int d){m_nCon_BS_S = d;};
	virtual void	SetnCon_BZ_S(int d){m_nCon_BZ_S = d;};
	////////////////////////////////////////////////////////////// Memory
	virtual pWORLD 	GetpData(){return m_pData;};
	virtual pWORLD 	GetpCon_BS_S(){return m_pCon_BS_S;};
	virtual pWORLD 	GetpCon_BZ_S(){return m_pCon_BZ_S;};
	
	virtual void	SetpData(pWORLD m){m_pData = m;};
	virtual void	SetpCon_BS_S(pWORLD m){m_pCon_BS_S = m;};
	virtual void	SetpCon_BZ_S(pWORLD m){m_pCon_BZ_S = m;};
	//////////////////////////////////////////////////////////
		
protected:

			//////////////////////////////////////////////////////////////// SetUp
			int 	FillUpSpline(pWORLD Con,pWORLD Data,int L,BOOL bClosed); 
			int 	FillUpBezier(pWORLD Con,pWORLD Data,int L,BOOL bClosed); 
			/////////////////////////////////////////////////////////////////
		          

protected:
  
// Attributes
protected:


	
	/////////////////////////////////////////// Curve
//	CDrCurve* 	m_pDrCurve;
//	CDListMgr*	m_pINodeList;
//	CURVETYPE	m_CurveType;
	BOOL		m_bClosed_S;
	int			m_nOrder_S;				// k
	int			m_nDegree_S;			// k -1
	int			m_nData_S;				// GIVEN: # of Data 
	int			m_nSeg_DT_S;			// L
	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// n + 1: #of Spline Controls
	int			m_nCon_BZ_S;			// (k-1) * L + 1 		
	int			m_nSegs;
	//////////////////////////////////////////////// Memory 
	int			m_MemErr;
	pWORLD 		m_pData;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
    
    
//Operations
public:

	~CInter_C1();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CInter_C1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

/////////////////////////////////////////////////////////////////////////////
#endif
