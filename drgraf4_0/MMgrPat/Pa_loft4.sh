#ifndef	_PA_LOFT4_H_
#define	_PA_LOFT4_H_


#include "glb_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Loft4
/////////////////////////////////////////////////////////////////////////////
class CPA_Loft4 : public CObject
{
// Construction
public:  
	CPA_Loft4();
	DECLARE_DYNAMIC(CPA_Loft4)
protected: 
public:
// Implementation

	int 	LoftProfiles
			(
				short	segs,	//	subdivision value (interior spaces)
				double	rat,	//  Output Last/Ist ratio in T_Direction
				short	nPts,	//	number of input data points
				pWORLD	p0,		//	input data point array for start curve
				pWORLD	p1,		//	input data point array for end curve
				pWORLD 	pOut	//	Output Pts array
			);
				  

	
public:

	
protected:


public:
	virtual ~CPA_Loft4(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_Loft4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif	// _PA_LOFT4_H_

