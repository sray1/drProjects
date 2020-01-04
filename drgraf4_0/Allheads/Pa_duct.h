#ifndef	_PA_DUCT_H_
#define	_PA_DUCT_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Duct
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_Duct : public CObject
{
// Construction
public:  
	CPA_Duct(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_Duct)
//////////////////////////////////////

protected: 
public:
// Implementation

			  
	int 	Duct
			(
				WORLD	Anchor,		//	cross section Anchor point	
				int		nXSec,		//	number of cross section points
				pWORLD	pXSec,		//	cross section curve points
				pDOUBLE	pXSecWt,	//	cross section curve points
				int		nPath,		//	number of path points
				pWORLD	pPath,		//	path curve points
				pWORLD	pPathTan,	//	path curve Tangents
				pDOUBLE	pTwist,		//	path Twist factors:
				pWORLD	pOut,		//	Output Pts array
				pDOUBLE	pOutWt		//	Output Wts array
			);	  

	
public:

	
protected:


public:
	virtual ~CPA_Duct(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPA_Duct)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

