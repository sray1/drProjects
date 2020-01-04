#ifndef	_PA_COOP3_H_
#define	_PA_COOP3_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_CooP3
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_CooP3 : public CObject
{
// Construction
public:  
	CPA_CooP3(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_CooP3)
//////////////////////////////////////

public:
// Implementation
	

	int		CoonCurves
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC1,	//	input data point for Curve 1
				pDOUBLE	pWts1,	//	input data Weight for Curve 1
				pWORLD	pInC2,	//	input data point for Curve 2
				pDOUBLE	pWts2,	//	input data Weight for Curve 2
				pWORLD	pInC3,	//	input data point for Curve 3
				pDOUBLE	pWts3,	//	input data Weight for Curve 3
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);
	

protected: 

	int		Coon_1_N_2
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC1,	//	input data point for Curve 1
				pDOUBLE	pWts1,	//	input data Weight for Curve 1
				pWORLD	pInC2,	//	input data point for Curve 2
				pDOUBLE	pWts2,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			);	  
	int		Coon_2_N_3
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC2,	//	input data point for Curve 1
				pDOUBLE	pWts2,	//	input data Weight for Curve 1
				pWORLD	pInC3,	//	input data point for Curve 2
				pDOUBLE	pWts3,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			);	  
	int		Coon_3_N_1
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC3,	//	input data point for Curve 1
				pDOUBLE	pWts3,	//	input data Weight for Curve 1
				pWORLD	pInC1,	//	input data point for Curve 2
				pDOUBLE	pWts1,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			);	  

	
public:

	
protected:


public:
	virtual ~CPA_CooP3(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_CooP3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
