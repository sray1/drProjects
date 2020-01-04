#ifndef	_SURFACE4_H_
#define	_SURFACE4_H_


#include "Def_Type.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CSurface4 : public CObject
class AFX_EXT_CLASS CSurface4 : public CObject
{
// Construction
public:  
	CSurface4();
	DECLARE_DYNAMIC(CSurface4)
protected: 
public:
// Implementation

	int		NumberOfPatches(
				CURVEPROC kindU, int nCtlU, BOOL bCloseU, int nOrderU,
				CURVEPROC kindV, int nCtlV, BOOL bCloseV, int nOrderV,
				int* pnPU, int* pnPV);


	void 	ComputeFDiff_x_Mcoeff
			(
				enum CURVEPROC	kind
			,	double			bias	// beta
			,	double			tension	// beta and hermite
			,	int				nSegU	// number of Intervals in U direction/cubic curve
			,	int				nSegV	// number of Intervals in V direction/cubic curve
			,	PDMAT			EUM
			,	PDMAT			EVM
			) ;
    //////////////////////////////////////////////////////////////////////////// Tensor Product
	int		TensorProduct_2D
				(
					PATCHOUTPUT		O_kind		//  Output Method
				,	BOOL			bClosed_S	//  IsClosed_S
				,	int				nDegree_S	//  Degree in S-Dir: 
				,	int				nCon_S		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_S		//  3= NonRational / 4 = Rational
				,	int				nPatches_S	//  Total Number of Patches 
				,	pINT			Num_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	BOOL			bClosed_T	//  IsClosed_S
				,	int				nDegree_T	//  Degree in T-Dir: 
				,	int				nCon_T		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_T		//  3= NonRational / 4 = Rational
				,	int				nPatches_T	//  Total Number of Patches 
				,	pINT			Num_t_T		//  Number of Output Segments Array in T-Dir for each patch
				,	pDOUBLE			Dis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	pWORLD			pCon_ST		//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts_ST		//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut_ST		//  Total Output Points Array
				,	pDOUBLE			pOutWts_ST	//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				);
	void 	HO_ComputeMG
					(
						PW4			ppInC		//	pointer to pointer Control Pt. array
					,	PD4			ppWts		// 	pointer to pointer Wts array	
					,	PDMA24		pMG_1		//  Basis*Geometry Matrix for Linear
					,	PDMA34		pMG_2		//  Basis*Geometry Matrix for Quadratic
					,	PDMA44		pMG_3		//  Basis*Geometry Matrix for Cubic
					,	int			nDegree		// 	Degree : ALWAYS BEZIER
					,	int			nDim		// 	3= NonRational / 4 = Rational
					);
	int 	HO_Make_A_CurvePt_V
					(
						PDMA24		pMG_1		//  Basis*Geometry Matrix for Linear
					,	PDMA34		pMG_2		//  Basis*Geometry Matrix for Quadratic
					,	PDMA44		pMG_3		//  Basis*Geometry Matrix for Cubic
					,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
					,	int			nDim_V		// 	3= NonRational / 4 = Rational
					,	double		t			// 	parameter to compute Surface Pt in V-dir
					,	pWORLD		pv			// 	Output Point
					,	pDOUBLE		w			// 	Output Wt
					);
	int		HO_GetAPointOnABezSegPatch		// RATIONAL BEZIER Patches
					(
						BOOL		bClosed_U	//  IsClosed_U
					,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
					,	int			nDim_U		//  3= NonRational / 4 = Rational
					,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
					,	int			nPatches_U	//  Total Number of Patches in U-dir 
					,	int			nCurBz_S// Output s distribution Pts.				
					,	double		sCur	// Output s distribution Pts.				
					,	BOOL		bClosed_V	//  IsClosed_V
					,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
					,	int			nDim_V		//  3= NonRational / 4 = Rational
					,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
					,	int			nPatches_V	//  Total Number of Patches in U-dir 
					,	int			nCurBz_T// Output s distribution Pts.				
					,	double		tCur	// Output t distribution Pts.				
					,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
					,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
					,	pWORLD		pOut_UV		//  Total Output Points Array
					,	pDOUBLE		pOutWt_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
					);






protected:

	PDMAT 	SetBasis(enum CURVEPROC	kind,double bias,double tension);
	PDMAT 	ForwardDifference(int nSegs);
	void 	ComputeEUM_G_XposeEVM(PWMAT DOO,PDMAT EUM, PDMAT EVM, PWMAT G);
	void 	ComputeEUorV_x_M(PDMAT EM, PDMAT FD, PDMAT M);
	int 	GeneratePointsOnCubic(PWMAT D,int nSegU,int nSegV,WORLD P[],
								int nPatchU,
								int uCur,int vCur,int nMaxU, int nMaxV);
	int 	MakePatchesToFit
			(
				enum CURVEPROC kind,	//	cubic basis function selection
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
	int 	MakePatchesToFit
			(
				int		nCtlU,	//	number of control vertices in U direction
				int		nSegU,	//	number of intervals in U direction
				int		nCtlV,	//	number of control vertices in V direction  	IN CALLING ROUTINE
				int		nSegV,	//	number of intervals in V direction
				pWORLD	ptCntrl,//	array of control vertices
				pWORLD	pOut,	//	array of Output 3D World Points
				int		nPU,	// 	Total Number of Cubic Patches in U direction
				int		nPV		// 	Total Number of Cubic Patches in V direction
			);
	//////////////////////////////////////////////////////////////////////////// Tensor Product
	void 	SetBasis(CURVEPROC kind, 
						PDMA22 pMCoef_1,PDMA33 pMCoef_2,PDMA44 pMCoef_3,int nDegree);
	int 	HO_MakePatches
					(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			CtlStep_U	//  Control Pt. Step
				,	int			nDegree_U	//  Degree in U-direction: 
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		//  Output t distribution Pts. for Ratio Business				
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			CtlStep_V   //  Control Pt. Step
				,	int			nDegree_V	//  Degree in V-direction: 
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_V		//  Output t distribution Pts. for Ratio Business				
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Points Array
				,	pDOUBLE		pOutWts_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
					);
	int 	HO_Make_A_Patch
					(
						PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
					,	PD44		ppWts_U4V4	//	pointer to pointer Wts. array for the patch	
					,	BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
					,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
					,	int			nDim_U		// 	3= NonRational / 4 = Rational
					,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
					,	pDOUBLE		Dis_t_U		//  Output t distribution Pts. for Ratio Business				
					,	BOOL		bLast_V		// 	Last Patch in V-Dir for Output saving decision		
					,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
					,	int			nDim_V		// 	3= NonRational / 4 = Rational
					,	int			nt_V		// 	# of subdivision to compute Surface Pts in V-dir
					,	pDOUBLE		Dis_t_V		//  Output t distribution Pts. for Ratio Business				
					,	pWORLD		pOut		// 	Total Output Points Array
					,	pDOUBLE		pOutWts		// 	Total Output Wts Array
					,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
					,	int			nPatches_U	//  Total Number of Patches in U-dir 
					,	int			nPatches_V	//  Total Number of Patches in V-dir 
					);
	int 	HO_Make_A_Curve_U
					(
						BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
					,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
					,	int			nDim_U		// 	3= NonRational / 4 = Rational
					,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
					,	pDOUBLE		Dis_t_U		//  Output t distribution Pts. for Ratio Business				
					,	pWORLD		pCon_U4		// 	Control Points Array
					,	pDOUBLE		pWts_U4		// 	Wts Array
					,	pWORLD		pOut		// 	Total Output Points Array
					,	pDOUBLE		pOutWts		// 	Total Output Wts Array
					,	int			nPatches_U	//  Total Number of Patches in U-dir 
					);
	int		HO_GenerateAPointOnASingleBezPatch
			(
					PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
				,	PD44		ppWts_U4V4	//	pointer to pointer Wts. array for the patch	
				,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		// 	3= NonRational / 4 = Rational
				,	double		u		// Output u Pt.				
				,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		// 	3= NonRational / 4 = Rational
				,	double		v		// Output v Pt.				
				,	pWORLD		pOut		// 	Total Output Points Array
				,	pDOUBLE		pOutWts		// 	Total Output Wts Array
			);

	
public:

	
protected:

	int	m_nsubdivisions;


public:
	virtual ~CSurface4(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CSurface4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

