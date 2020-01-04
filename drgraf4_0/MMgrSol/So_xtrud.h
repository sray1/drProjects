#ifndef	_SO_XTRUD_H_
#define	_SO_XTRUD_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CSO_Xtrud
/////////////////////////////////////////////////////////////////////////////
class CSO_Xtrud : public CObject
{
// Construction
public:  
	CSO_Xtrud(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CSO_Xtrud)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
	int		ExtrudePatch
			(
				double	depth,	//	distance to the extended solid's end
				WORLD	v,		//	unit extrusion vector (direction)
				int		nPts,	//	number of input data points in ST_direction
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
	virtual ~CSO_Xtrud(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CSO_Xtrud)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

