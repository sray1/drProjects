#ifndef	_DRCURVES_
#define	_DRCURVES_


#include "globals.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
//////////////////////////////
typedef	double	DMAT[4][4];
typedef	double	(*PDMAT)[4];
typedef	double	*PDOUBLE;
/////////////////////////////////////////////////////////////////////////////
// CDrCurves
/////////////////////////////////////////////////////////////////////////////
class CDrCurves : public CObject
{
// Construction
public:  
	CDrCurves();
	DECLARE_DYNAMIC(CDrCurves)
protected: 
public:
// Implementation
 
	int 	NumberOfCubicCurves(enum CURVETYPE kind, int nC,BOOL bClose);
	int 	MakeCurvesToFit
			// Return Actual Number of Points Generated
			(
				enum CURVETYPE	kind
			,	double			bias			// beta
			,	double			tension			// beta and hermite
			,	int				nC				// number of control points
			,	int				nSteps			// number of Steps per cubic curve
			,	pWORLD			pIn             // Toal  input  Points Array
			,	pWORLD			pOut            // Total Output Points Array
			,	int				np				// Total Number of Cubic Curves
			);
	int		GeneratePointsforCurves
			(
				enum	CURVETYPE	kind,
				int					nSteps,		/*	number of Steps (t=[0,1]) for each Cubic	*/
				int					nC,			/*	number of input control points				*/
				int					nP,			/*	number of Cubic Curves                      */
				pWORLD				pIn,		/*	array of input control points				*/
				pWORLD 				pOut,		/*	return array of generated curve vertices	*/
				int					nOut		/*	expected number of generated curve vertices	*/
			);
	
protected:

	PDMAT 	ForwardDifference(int nSegs);
	int 	GeneratePointsOnCubic(PDMAT A,PDMAT E, int nSegs,pWORLD P,BOOL bEndPt);
	void	BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size);
	int 	CtlPtStep(enum CURVETYPE kind);
	PDMAT 	SetBasis(enum CURVETYPE kind,double bias,double tension);
	void 	ComputeCG(PDMAT CG, PDMAT C, PDMAT G);
	
public:

	
protected:


public:
	virtual ~CDrCurves(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CDrCurves)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif	// _DRCURVES_
