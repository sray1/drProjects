 // In_Circle.h : header file
//
#ifndef _IN_CRCLE_H 
#define _IN_CRCLE_H 
                    
#include "drcurve.h"
//#include "DListMgr.h"
#include "glb_Type.h"
#include "glb_CuPS.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CIn_Circle : public CObject
{
public:

	CIn_Circle();
	DECLARE_SERIAL(CIn_Circle)


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
	virtual void	SetnDim_S(int d){m_nDim_S = d;};
	virtual void	SetnDegree_S(int d){m_nDegree_S = d;};				// k -1
	virtual void	SetnSeg_DT_S(int d){m_nSeg_DT_S = d;};				// L
	
//	virtual void	SetnSeg_BS_S(nSeg_BS);
	virtual void	SetnCon_BS_S(int d){m_nCon_BS_S = d;};
	virtual void	SetnCon_BZ_S(int d){m_nCon_BZ_S = d;};
	//////////////////////////////////////////////////////////// Circle
	virtual double	GetTheta(){return m_theta;};
	virtual int		GetDatNew(){return m_nDatNew;};	// Adjusted# of Data for Conics(Circle) 
	virtual WORLD	GetCenter(){return m_Center;};
	virtual double	GetRadius(){return m_Radius;};
	virtual void	SetTheta(double t){ m_theta = t;};
	virtual void	SetDatNew(int t){m_nDatNew = t;};	// Adjusted# of Data for Conics(Circle) 
	virtual void	SetCenter(WORLD t)
					{
						m_Center.x = t.x;
						m_Center.y = t.y;
						m_Center.z = t.z;
					};
	virtual void	SetRadius(double t){m_Radius = t;};
	////////////////////////////////////////////////////////////// Memory
	virtual pDOUBLE	GetpWts_BS_S(){return m_pWts_BS_S;};
	virtual pDOUBLE	GetpWts_BZ_S(){return m_pWts_BZ_S;};
	virtual pWORLD 	GetpData(){return m_pData;};
	virtual pWORLD 	GetpCon_BS_S(){return m_pCon_BS_S;};
	virtual pWORLD 	GetpCon_BZ_S(){return m_pCon_BZ_S;};
	virtual pWORLD 	GetpDatNew(){return m_pDatNew;};
	
	virtual void	SetpWts_BS_S(pDOUBLE m){m_pWts_BS_S = m;};
	virtual void	SetpWts_BZ_S(pDOUBLE m){m_pWts_BZ_S = m;};
	virtual void	SetpData(pWORLD m){m_pData = m;};
	virtual void	SetpCon_BS_S(pWORLD m){m_pCon_BS_S = m;};
	virtual void	SetpCon_BZ_S(pWORLD m){m_pCon_BZ_S = m;};
	virtual void	SetpDatNew(pWORLD m){m_pDatNew = m;};
	//////////////////////////////////////////////////////////
		
protected:

			int		Compute_CandR(pWORLD Data, pWORLD Center, pDOUBLE Radius);
			int 	GetNewPtsOnCircle(pWORLD DOld, double theta, WORLD Center, 
															pWORLD DNew, int nNew); 
			int 	Compute_b1_w1(WORLD Center,WORLD b0,WORLD b2,double Rad,
														pWORLD pb1,pDOUBLE pw1);
			//////////////////////////////////////////////////////////////// SetUp
			int 	FillUpBezier(pWORLD Data, double theta, WORLD Center, double Radius, 
							 pWORLD Con, pDOUBLE Wts,int nCon, int L, BOOL bClosed);
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
	int			m_nSegs;
	int 		m_nDim_S;
	//////////////////////////////////////////////////////////// Circle
	double		m_theta;
	int			m_nDatNew;			// Adjusted# of Data for Conics(Circle) 
	WORLD		m_Center;
	double  	m_Radius;
	WORLD		m_Normal;
	//////////////////////////////////////////////// Memory 
	int			m_MemErr;
	pDOUBLE		m_pWts_BS_S;
	pDOUBLE		m_pWts_BZ_S;
	pWORLD 		m_pData;
	pWORLD 		m_pDatNew;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
    
    
//Operations
public:

	~CIn_Circle();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CIn_Circle)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

/////////////////////////////////////////////////////////////////////////////
#endif
