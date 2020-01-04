#ifndef	_PA_XTRUD_H_
#define	_PA_XTRUD_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPA_Xtrud
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPA_Xtrud : public CObject
{
// Construction
public:  
	CPA_Xtrud(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPA_Xtrud)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
	int 	ExtrudeCurve
			(
				double	depth,	//	distance to the extended surface's end
				WORLD	v,		//	unit extrusion vector (direction)
				int		segs,	//	# of Elements in T-dirction
				double	ratio,	//  Output Last/Ist ratioio in T_Direction
				int		nPts,	//	number of input data points in S_direction
				pWORLD	pPt,	//	input data point array
				pDOUBLE	pWt,	//	input data Weight array
				pWORLD	pOut,	//	Output Pts array
				pDOUBLE	pOutWts //	Output Wts array
			);
	pWORLD 	GetAPtByExtrusion(pWORLD pDOld, WORLD dir, double depth);



	
public:

	
protected:

	int	m_nsubdivisions;


public:
	virtual ~CPA_Xtrud(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPA_Xtrud)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

