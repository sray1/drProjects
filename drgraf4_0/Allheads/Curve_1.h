#ifndef	_CURVE_1_H_
#define	_CURVE_1_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include <afxtempl.h>	// CList
#include "Def_Type.h"
#include "Curve.h"
/////////////////////////////////////////////////////////////////////////////
// CCurve_1
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CCurve_1 : public CCurve
class CCurve_1 : public CCurve
{
// Construction
public:  
	CCurve_1();
//////////////////////////////////////
	DECLARE_DYNAMIC(CCurve_1)
//////////////////////////////////////
protected: 
public:
// Implementation

	int		HO_GetAPointOnABezSegCurve 		// 
			(
				int				nC				// number of CONTROL points
			,	pWORLD			pInC            // Total CONTROL Points Array
			,	int				nDim			// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts			// Rational Bezier Weights		
			,	int				nCurBz_S	// Current BezSeg				
			,	double			sCur		// current s param
			,	pWORLD			pOut            // Total Output Points Array
			,	pDOUBLE			pOutWt			// Total Output Wts Array
			,	int				nCurves			// Total Number of Linear Curves 
			);

	int		GenerateCurve
			(

				CURVEOUTPUT		O_kind		// Output Method
			,	BOOL			bClosed		// IsClosed
			,	int				nCon		// number of CONTROL points: ALWAYS BEZIER
			,	pWORLD			pCon        // Total CONTROL Points Array
			,	int				nDim		// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts		// Rational Bezier Weights		
			,	pINT			Num_t		// Number of Outputs for each Output Segment
												//	Num_t[i], i = 1,nMaxOutSeg																							
			,	pDOUBLE			Dis_t			// Output t distribution Pts.				
			,	pWORLD			pOut        // Total Output Points Array
			,	pDOUBLE			pOutWts		// Total Output Wts Array
			,	int				nCurves		// Total Number of Cubic Curves 
			,	int				nOut		// expected number of generated curve vertices
			);
	//////////////////////////////////////////////////
	int 	MakeTangents 		// 
				// Return Actual Number of Tangents Generated
			(
				BOOL			bClosed		// IsClosed
			,	int				nC			// number of CONTROL points
			,	pWORLD			pInC        // Total CONTROL Points Array
			,	int				nDim		// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts		// Rational Bezier Weights		
			,	pINT			Num_t		// number of t-dist for each Curve Segment Output
			,	pDOUBLE			Dis_t			// Output t distribution Pts.				
			,	pWORLD			pOut        // Total Output Points Array
			,	int				nCurves		// Total Number of Cubic Curves 
			);
	//////////////////////////////////////////////////
	int 	MakeCurvatures 		// 
				// Return Actual Number of Curvatures Generated
			(
				BOOL			bClosed			// IsClosed
			,	int				nC			// number of CONTROL points
			,	pWORLD			pInC        // Total CONTROL Points Array
			,	int				nDim		// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts		// Rational Bezier Weights		
			,	pINT			Num_t		// number of t-dist for each Curve Segment Output
			,	pDOUBLE			Dis_t			// Output t distribution Pts.				
			,	pDOUBLE			pOut        // Total Output Points Array
			,	int				nCurves		// Total Number of Cubic Curves 
			);
    /////////////////
	PDMA22 	SetBasis(enum CURVEPROC kind,double bias,double tension,double alfa);
	int		HO_MakeCurves 		// 
				// Return Actual Number of Points Generated
				(
					BOOL			bClosed			// IsClosed
				,	PDMA22			pMCoef			// Basis Matrix
				,	int				CtlStep         // Control Pt. Step
				,	int				nC				// number of CONTROL points
				,	pWORLD			pInC            // Total CONTROL Points Array
				,	int				nDim			// 3= NonRational / 4 = Rational
				,	pDOUBLE			pWts			// Rational Bezier Weights		
				,	pINT			Num_t			// Number of Outpts for each curve
				,	pDOUBLE			Dis_t			// Output t distribution Pts.				
				,	pWORLD			pOut            // Total Output Points Array
				,	pDOUBLE			pOutWts			// Total Output Wts Array
				,	int				nCurves			// Total Number of Cubic Curves 
				);
	int		HO_Make_A_Curve 		// 
				(
					BOOL			bClosed			// IsClosed
				,	pWORLD			pInC_Begin      // Absolute Beginning of CONTROL Points Array
														// for the entire Curve
														// needed for Closed Curve
				,	pDOUBLE			pWts_Begin      // Absolute Beginning of Rational Bezier Weights
														// for the entire Curve
														// needed for Closed Curve
				,	BOOL			bLast			// Last Curve
				,	PDMA22			pMCoef			// Basis Matrix
				,	pWORLD			pInC            // ORDER Number CONTROL Points Array
														// for the Current Curve Segment
				,	int				nDim			// 3= NonRational / 4 = Rational
				,	pDOUBLE			pWts			// Rational Bezier Weights		
				,	int				nt				// Number of Outpts for the curve
				,	pDOUBLE			Dis_t			// Output t distribution Pts.				
				,	pWORLD			pOut            // Total Output Points Array
				,	pDOUBLE			pOutWts			// Total Output Wts Array
				,	int				nCurves			// Total No. of Curves needed for alternate
														// t-distribution
				);
	int 	HO_Make_A_Curve_Pt		// Return Actual Number of Points Generated 	 
				(
					PDMA24			pMG				// Basis*Geometry Matrix
				,	int				nDim			// 3= NonRational / 4 = Rational
				,	double			t				// t Value for the curve
				,	pWORLD			pOut            // Output Point
				,	pDOUBLE			pOutWts			// Total Output Wts Array
				);
	void 	HO_ComputeMG(PDMA24 MG,PDMA22 M,PDMA24 G,int nDim);

	
	
protected:

	int		HO_GenerateAPointOnASingleBezCurve 		// 
			(
				pWORLD			pInC            // ORDER Number CONTROL Points Array
												// for the Current Curve Segment
			,	int				nDim			// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts			// Rational Bezier Weights		
			,	double			sCur	// Current param of Outpt for the curve
			,	pWORLD			pOut            // Total Output Points Array
			,	pDOUBLE			pOutWt			// Total Output Wts Array
			);
	//////////////////////////////////////////////////////////////////////////////
	void 	GetBlending_NUSpline(int i, double t, pDOUBLE knot, pDOUBLE blend);
	//////////////////////////////////////////////////////////////////////////////
	PDMA22 	FD_ForwardDifference(int nSegs);
	void 	FD_MultMat(PDMA22 A, PDMA22 B, PDMA22 C);
	void 	FD_ComputeEA(PDMA24 EA, PDMA22 EM, PDMA24 G);
	int 	FD_GeneratePoints_Unif(PDMA24 EA,int nSegs,pWORLD P,BOOL bEndPt);
	PDMA22 	FD_ComputeFDiff_x_Mcoeff
			(
				enum CURVEPROC	kind
			,	double			alfa			// alfa (Modified Catmull-Rom)
			,	double			bias			// beta
			,	double			tension			// beta and hermite
			,	int				nSeg			// number of Intervals per cubic curve
			);
	int 	FD_MakeCurves
				// Return Actual Number of Points Generated
			(

				int				nC				// number of CONTROL points
			,	pWORLD			pInC            // Total CONTROL Points Array
			,	int				nDim			// 3= NonRational / 4 = Rational
			,	pDOUBLE			pWts			// Rational Bezier Weights		
			,	pINT			Num_t			// Number of Outpts for each curve
			,	pWORLD			pOut            // Total Output Points Array
			,	int				nCurves			// Total Number of Cubic Curves 
			);
/*		
	//////////////////////////////////////////////////
	int		Gen_OutputReDistribution
			(

				BOOL			bClosed			// IsClosed
			,	int				nCon			// number of CONTROL points
			,	pWORLD			Con         	// Total CONTROL Points Array
			,	int				nMaxOutSeg		// Number of Outpts segments
			,	pINT			OSeg_t 			// Number of intervals/Output segments
			,	pDOUBLE			OVal_t			// Output Segment Boundaries
			,	pINT			CSeg_t			// Number of Pts./Curve				
			,	pDOUBLE			CVal_t			// Output Pts.				
			,	int				nCurves			// Total Number of Cubic Curves 
			,	int				nOut			// expected number of generated curve vertices
		);
*/
public:
	virtual ~CCurve_1(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _CURVE_1_H_
