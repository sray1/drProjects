#ifndef	_PA_COONP_H_
#define	_PA_COONP_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_CoonP
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_CoonP : public CObject
{
// Construction
public:  
	CPA_CoonP(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_CoonP)
//////////////////////////////////////

protected: 
public:
// Implementation
	
	int		CoonCurves
			(
				short	nPts_S,	//	number of input Control points in S-dir
				short	nPts_T,	//	number of input Control points in T-dir
				pWORLD	pInC1,	//	input data point for Curve 1
				pDOUBLE	pWts1,	//	input data Weight for Curve 1
				pWORLD	pInC2,	//	input data point for Curve 2
				pDOUBLE	pWts2,	//	input data Weight for Curve 2
				pWORLD	pInC3,	//	input data point for Curve 3
				pDOUBLE	pWts3,	//	input data Weight for Curve 3
				pWORLD	pInC4,	//	input data point for Curve 4
				pDOUBLE	pWts4,	//	input data Weight for Curve 4
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);	  
				  

	
public:

	
protected:


public:
	virtual ~CPA_CoonP(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_CoonP)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
