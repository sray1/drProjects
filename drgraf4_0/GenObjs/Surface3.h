#ifndef	_SURFACE3_H_
#define	_SURFACE3_H_


#include "DListMgr.h"
#include "Def_Type.h"
#include "Triangle.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CSurface3 : public CObject
class AFX_EXT_CLASS CSurface3 : public CObject
{
// Construction
public:  
	CSurface3();
	DECLARE_DYNAMIC(CSurface3)
protected: 
public:
// Implementation

	int			Triangles_2D
				(
					PATCHOUTPUT		O_kind		//  Output Method
				,	CDListMgr*		pTriList	//	Patch List
				,	BOOL			bClosed		//  ALL Closed?
				,	int				nDim		//  Overall Dimension 3=NonRational/4=Rational
				,	int				nSeg		//  Number of Output Segments in ALL Dir & ALL patches
				,	int				nCon		//  Number of Control Pts
					//////////////////////////////  Globals:
				,	int				nOutGlo_S		//  Total Output in each side of entire Base Patch
					////////////////////
				,	pWORLD			pCon		//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut		//  Total Output Points Array
				,	pDOUBLE			pOutWts		//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				);

	int			HO_GetAPointOnABezSegPatch		// RATIONAL BEZIER Patches
				(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
					///////////////////
				,	CTriangle*	pTriCur	//	Current Triangle 
				,	double		uCur
				,	double		vCur
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut	//  Output Point
				,	pDOUBLE		pOutWt	//  Output Wt (WE MAY NEED FOR RATIONAL SOLIDS)
				);

protected:


	int			HO_GenerateAPointOnASingleBezPatch
				(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////
				,	double		u		//  output param		
				,	double		v		//  output param		
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	pWORLD		pOut		// 	Total Output Global Points Array
				,	pDOUBLE		pOutWt		// 	Total Output Global Wts Array
				);
	int			EX_MakePatches		// RATIONAL BEZIER Patches					 EXplicit 
				(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Patch Array = 1 (FOR NOW)
					//////////////////////////  Globals:
				,	int			nOutGlo_S	//  Total Output in each side of entire Patch 
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Points Array
				,	pDOUBLE		pOutWts_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
				);

	int			EX_Make_A_Patch
				(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			nOutGloTot_S	//	Total Output in each side of entire Base Patch 
				,	int			iOutGlo			//	Global i Bary Coords for Ist Output of the PentaHed 
				,	int			jOutGlo			//	Global j Bary Coords for Ist Output of the PentaHed 
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_G		// 	Total Output Global Points Array
				,	pDOUBLE		pOutWts_G	// 	Total Output Global Wts Array
				);

	int			Linear(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut);
	int			Quadratic(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut);
	int			Cubic(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut);
	///////////////////////////////////////////////////////////////////////////////////////////


protected:

public:
	virtual ~CSurface3(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CSurface3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

