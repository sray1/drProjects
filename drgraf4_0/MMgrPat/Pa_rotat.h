#ifndef	_PA_ROTAT_H_
#define	_PA_ROTAT_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Rotat
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_Rotat : public CObject
{
// Construction
public:  
	CPA_Rotat(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_Rotat)
//////////////////////////////////////

protected: 
public:
// Implementation

			  
	int 	RotateCurve
			(
				BOOL	bClosed_T,
				int		nSegBZ_T,//	# of Quadratic Bezier Segments
				pDOUBLE	pDis,	//	Angle Distribution for each Bez Patch in degrees
								//		(not cumulative)
				WORLD	Axis,	//	unit direction vector of rotation axis
				WORLD	AxisPt, //  a pt. on the rotation vector
				int		nPts,	//	number of input data points
				pWORLD	pPt,	//	input data point array
				pDOUBLE	pWt,	//	input data Weight array
				pWORLD	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);
	int		GetAPtByRotation(pWORLD pb0, WORLD AxisPt, WORLD Normal, 
											double dAng, pWORLD pb2);

	
protected:

	int		Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE pRadius, WORLD Normal,WORLD AxPt);
	int		Compute_b1_w1(pWORLD pCenter,double Rad,pWORLD pb0,pWORLD pb2,double w_b0,
									pWORLD pb1,pDOUBLE pw1);


public:
	virtual ~CPA_Rotat(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_Rotat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

