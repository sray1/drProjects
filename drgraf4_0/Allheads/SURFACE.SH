#ifndef	_SURFACE_H_
#define	_SURFACE_H_


#include "glb_Type.h"
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
typedef WORLD	WMAT2[2][2];
typedef WORLD	(*PWMAT2)[2];
////////////////////////////
//typedef	double	*PDOUBLE;
//typedef struct	tdblP3D { double x, y, z; } dblP3D;
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
class CSurface : public CObject
{
// Construction
public:  
	CSurface();
	DECLARE_DYNAMIC(CSurface)
protected: 
public:
// Implementation

	int 	NumberOfCubicPatches(enum CURVETYPE kind, int nCtlU, int nCtlV,
							int nSegU,int nSegV,BOOL bCloseU,BOOL bCloseV,
						 	int* pnPU, int* pnPV,int* pnOut_U,int* pnOut_V);

	int 	NumberOfLinearPatches(enum CURVETYPE kind, int nCtlU, int nCtlV,
							int nSegU,int nSegV,BOOL bCloseU,BOOL bCloseV,
							int* pnPU, int* pnPV,int* pnOut_U, int* pnOut_V);

	void 	ComputeFDiff_x_Mcoeff
			(
				enum CURVETYPE	kind
			,	double			bias	// beta
			,	double			tension	// beta and hermite
			,	int				nSegU	// number of Intervals in U direction/cubic curve
			,	int				nSegV	// number of Intervals in V direction/cubic curve
			,	PDMAT			EUM
			,	PDMAT			EVM
			) ;
	int		Generate_Cubics
			(
				enum CURVETYPE kind,	//	cubic basis function selection
				int			nCtlU,	//	number of control vertices in U direction
				int			nSegU,	//	number of intervals in U direction
				int			nCtlV,	//	number of control vertices in V direction  	IN CALLING ROUTINE
				int			nSegV,	//	number of intervals in V direction
				pWORLD		ptCtl,	//	array of control vertices
				pWORLD		pOut,	//	array of Output 3D World Points
				int			nPU,	// 	Total Number of Cubic Patches in U direction
				int			nPV,	// 	Total Number of Cubic Patches in V direction
				int			nOutU,	//	expected number of generated curve vertices in U	
				int			nOutV,	//	expected number of generated curve vertices in V	
				int			nOut	//	expected number of generated curve vertices	
			);

	int		Generate_Linears
	(
//		BOOL	 	bCloseU,	//	closed in U direction?
		int			nCU,		//	number of control vertices in U direction
		int			nSegU,		//	number of intervals in U direction
//		BOOL		bCloseV,	//	closed in V direction?
		int			nCV,		//	number of control vertices in V direction  	IN CALLING ROUTINE
		int			nSegV,		//	number of intervals in V direction
		pWORLD		pIn,		//	array of Input control vertices
		pWORLD		pOut,		//	array of Output 3D World Points
		int			nPU,		// 	Total Number of Cubic Patches in U direction
		int			nPV,		// 	Total Number of Cubic Patches in V direction
		int			nOutU,		//	expected number of generated curve vertices in U	
		int			nOutV,		//	expected number of generated curve vertices in V	
		int			nOut		//	expected number of generated curve vertices	
			);

	int 	LoftCurves
			(
				short	segs,	//	subdivision value (interior spaces)
				short	nPts,	//	number of input data points
				pWORLD	p0,		//	input data point array for start curve
				pWORLD	p1,		//	input data point array for end curve
				pWORLD 	pOut	//	Output Pts array
			);
				  
	int 	ExtrudeCurve
			(
				double	depth,	//	distance to the extended surface's end
				pWORLD	v,		//	unit extrusion vector (direction)
				int		segs,	//	subdivision value (interior spaces)
				int		nPts,	//	number of input data points
				pWORLD	pPt,	//	input data point array
				pWORLD	pOut	//	Output Pts array
			);
			  
	int 	RotateCurve
			(
				pWORLD	pAxisPt,//  a pt. on the rotation vector
				double	alpha,	//	initial position angle in degrees
				double	theta,	//	total rotation in degrees
				pWORLD	pAxis,	//	unit direction vector of rotation axis
				int		segs,	//	subdivision value (interior spaces)
				int		nPts,	//	number of input data points
				pWORLD	pPt,	//	input data point array
				pWORLD	pOut	//	Output Pts array
			);
			  
	int 	ExtrudeCurvePath
			(
				int		npSect,	//	number of cross section points
				pWORLD	ppSect,	//	cross section curve points
				int		npPath,	//	number of path points
				pWORLD	ppPath,	//	path curve points
				pWORLD	pOut	//	Output Pts array
			);
			  
	int 	Sweep
			(
				WORLD	wAnchor,	//	cross section Anchor point
				int		npSect,		//	number of cross section points
				pWORLD	ppSect,		//	cross section curve points
				int		npPath,		//	number of path points
				pWORLD	ppPath,		//	path curve points
				pWORLD	ppScale,	//	path scaling factors
				pWORLD	ppRotate,	//	path rotation factors
				pWORLD	pOut		//	Output Pts array
			);	  
			  
	int 	Duct
			(
				WORLD	wAnchor,	//	cross section Anchor point
				int		npSect,		//	number of cross section points
				pWORLD	ppSect,		//	cross section curve points
				int		npPath,		//	number of path points
				pWORLD	ppPath,		//	path curve points
				pWORLD	ppRotate,	//	path rotation factors
				pWORLD	pOut		//	Output Pts array
			);	  



protected:

	void	BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size);
	int 	CtlPtStep(enum CURVETYPE kind);
	PDMAT 	SetBasis(enum CURVETYPE	kind,double bias,double tension);
	PDMAT 	ForwardDifference(int nSegs);
	void 	ComputeEUM_G_XposeEVM(PWMAT DOO,PDMAT EUM, PDMAT EVM, PWMAT G);
	void 	ComputeEUorV_x_M(PDMAT EM, PDMAT FD, PDMAT M);
	int 	GeneratePointsOnCubic(PWMAT D,int nSegU,int nSegV,WORLD P[],
								int nPatchU,
								int uCur,int vCur,int nMaxU, int nMaxV);
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
				int			nPV,	// 	Total Number of Cubic Patches in V direction
				PDMAT		EUM,	// 	EM Matrix in U direction
				PDMAT		EVM		// 	EM Matrix in V direction
			);
	int 	GeneratePointsOnLinear
			(
				PWMAT2 In,int nSegU,int nSegV,
				double rU,double rV,
				Wthis   
  
 A a    2     8J  <J  /  % � t:CDrCurve::SetTension     :this   
  
 A a    .     |J  �J  -  # � x:CDrCurve::GetMemIn   :this     2     �J  �J  -  # $ z:CDrCurve::GetMemInWts    :this     2     K  K  -  # R |:CDrCurve::GetMemInDP     :this     2     TK  XK  -  # � x:CDrCurve::GetMemOut      :this     2     �K  �K  -  # � z:CDrCurve::GetMemOutWts   :this     2     �K  �K  -  # � |:CDrCurve::GetMemOuU direction
				int		nPV		// 	Total Number of Cubic Patches in V direction
			);

	
public:

	
protected:

	int	m_nsubdivisions;


public:
	virtual ~CSurface(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CSurface)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif	// _SURFACE_H_

