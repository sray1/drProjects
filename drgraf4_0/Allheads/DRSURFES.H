#ifndef	_DRSURFACES_
#define	_DRSURFACES_


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
typedef WORLD	WMAT[4][4];
typedef WORLD	(*PWMAT)[4];
////////////////////////////
//typedef	double	*PDOUBLE;
//typedef struct	tdblP3D { double x, y, z; } dblP3D;
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
class CDrSurfes : public CObject
{
// Construction
public:  
	CDrSurfes();
	DECLARE_DYNAMIC(CDrSurfes)
protected: 
public:
// Implementation

	int 	NumberOfCubicPatches(enum CURVETYPE kind, int nCtlU, int nCtlV,
					int nSegU,int nSegV,BOOL bCloseU,BOOL bCloseV,
						 int* pnPU, int* pnPV);
	int		GeneratePointsforPatches
			(
				enum CURVETYPE kind,	//	cubic basis function selection
//				BOOL	 	uClosed,//	closed curve in U direction?  				IN CALLING ROUTINE
				int			nCtlU,	//	number of control vertices in U direction
				int			nSegU,	//	number of intervals in U direction
//				BOOL		vClosed,//	closed curve in V direction?
				int			nCtlV,	//	number of control vertices in V direction  	IN CALLING ROUTINE
				int			nSegV,	//	number of intervals in V direction
				pWORLD		ptCtl,	//	array of control vertices
				pWORLD		pOut,	//	array of Output 3D World Points
				int			nPU,	// 	Total Number of Cubic Patches in U direction
				int			nPV,		// 	Total Number of Cubic Patches in V direction
				int			nOut	//	expected number of generated curve vertices	
//		hGroup		hG,		//	destination group
//		int			ixP,	//	destination patch index
//		pRendAttr 	pRA,	//	rendering attributes for patch
//		pMatrix 	xf		//	instance transform for patch
	);
 

protected:

	void	BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size);
	int 	CtlPtStep(enum CURVETYPE kind);
	PDMAT 	SetBasis(enum CURVETYPE	kind,double bias,double tension);
	void 	ForwardDifference(PDMAT EU, PDMAT EV,int nSegU,int nSegV);
	void 	ComputeC_G_XposeC(PWMAT CGCt, PDMAT C, PWMAT G);
	void 	ComputeEU_CGCT_XposeEV(PWMAT E,PDMAT EU, PDMAT EV, PWMAT CGCT,
						int nSegU,int nSegV);
	int 	GeneratePointsOnCubic(PWMAT D,int nSegU,int nSegV,pWORLD P,
						BOOL bEndU,BOOL bEndV);
	int 	MakePatchesToFit
			(
				enum CURVETYPE kind,	//	cubic basis function selection
				double		bias,	//	beta
				double		tension,//	beta and hermite
				int			nCtlU,	//	number of control vertices in U direction
				int			nSegU,	//	number of intervals in U direction
				int			nCtlV,	//	number of control vertices in V direction  	IN CALLING ROUTINE
				int			nSegV,	//	number of intervals in V direction
				pWORLD		ptCntrl,//	array of control vertices
				pWORLD		pOut,	//	array of Output 3D World Points
				int			nPU,	// 	Total Number of Cubic Patches in U direction
				int			nPV		// 	Total Number of Cubic Patches in V direction
			);

	
public:

	
protected:

	int	m_nsubdivisions;


public:
	virtual ~CDrSurfes(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CDrSurfes)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif	// _DRSURFES_

