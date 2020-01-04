#ifndef	_PA_SWEEP_H_
#define	_PA_SWEEP_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Sweep
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_Sweep : public CObject
{
// Construction
public:  
	CPA_Sweep(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_Sweep)
//////////////////////////////////////

protected: 
public:
// Implementation

			  
	int 	Sweep
			(
				WORLD	Anchor,		//	cross section Anchor point	
				int		nXSec,		//	number of cross section points
				pWORLD	pXSec,		//	cross section curve points
				pDOUBLE	pXSecWt,	//	cross section curve points
				int		nPath,		//	number of path points
				pWORLD	pPath,		//	path curve points
				pWORLD	pPathTan,	//	path curve Tangents
				pDOUBLE	pTwist,		//	path Twist factors:
				pDOUBLE	pScale,		//	path Scale factors: ONLY Y-COMPONENT is USEFUL
				pWORLD	pOut,		//	Output Pts array
				pDOUBLE	pOutWt		//	Output Wts array
			);	  
			  
public:

	
protected:


public:
	virtual ~CPA_Sweep(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_Sweep)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

