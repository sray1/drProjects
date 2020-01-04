#ifndef	_CU_CIRCL_H_
#define	_CU_CIRCL_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CCU_Circl
/////////////////////////////////////////////////////////////////////////////
class CCU_Circl : public CObject
{
// Construction
public:  
	CCU_Circl(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CCU_Circl)
//////////////////////////////////////

protected: 
public:
// Implementation

			  
	int 	RotatePoint
			(
				WORLD	Center,
				double	Radius,
				BOOL	bClosed,
				int		nSegBZ, //	# of Quadratic Bezier Segments
				pDOUBLE	pDis,	//	Angle Distribution for each Bez Patch in degrees
				WORLD	Axis,	//	unit direction vector of rotation axis
//				WORLD	AxisPt, //  a pt. on the rotation vector
				int		segs,	//	# of Elements in T-dirction
				int		nPts,	//	number of input data points
				pWORLD	pPt,	//	input data point array
				pDOUBLE	pWt,	//	input data Weight array
				pWORLD	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);
	int		GetAPtByRotation(pWORLD pb0, WORLD AxisPt, WORLD Normal, 
											double dAng, pWORLD pb2);

	
protected:

	int		Compute_b1_w1(pWORLD pCenter,double Rad,pWORLD pb0,pWORLD pb2,double w_b0,
									pWORLD pb1,pDOUBLE pw1);


public:
	virtual ~CCU_Circl(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CCU_Circl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

