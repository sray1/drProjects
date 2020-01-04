#ifndef	_PA_LOFT2_H_
#define	_PA_LOFT2_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Loft2
/////////////////////////////////////////////////////////////////////////////
class CPA_Loft2 : public CObject
{
// Construction
public:  
	CPA_Loft2(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_Loft2)
//////////////////////////////////////

protected: 
public:
// Implementation
	
	int		LoftCurves_2
			(
				short	segs,	//	subdivision value (interior spaces)
				double	ratio,	//  Output Last/Ist ratio in T_Direction
				short	nPts,	//	number of input Control points
				pWORLD	p0,		//	input data point array for start curve
				pDOUBLE	pWt0,	//	input data Weight array
				pWORLD	p1,		//	input data point array for end curve
				pDOUBLE	pWt1,	//	input data Weight array
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);	  
				  

	
public:

	
protected:


public:
	virtual ~CPA_Loft2(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_Loft2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
