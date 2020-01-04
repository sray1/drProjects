#ifndef	_CURVE_H_
#define	_CURVE_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "Def_CuPS.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
//////////////////////////////
#define	EMIT_POINT(a,b,c,d)			(d).x= (a); 	(d).y= (b); 	(d).z= (c)
#define	EMIT_POINT_RAT(a,b,c,w,d)	(d).x= (a)/(w); (d).y= (b)/(w); (d).z= (c)/(w)
#define	EMIT_TANGENT(t,p)		(p).x= (t)->x ; (p).y= (t)->y ; (p).z= (t)->z
#define	SCALEP(a,b)				(a).x = (a).x * (b);\
								(a).y = (a).y * (b);\
								(a).z = (a).z * (b)
#define	SUBP(a,b,c)				(c).x = (a).x - (b).x;\
								(c).y = (a).y - (b).y;\
								(c).z = (a).z - (b).z
/////////////////////////////////////////////////////////////////////////////
// CCurve
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CCurve : public CObject
class AFX_EXT_CLASS CCurve : public CObject
{
// Construction
public:  
	CCurve();
//////////////////////////////////////
	DECLARE_DYNAMIC(CCurve)
//////////////////////////////////////
protected: 
public:
// Implementation
	int 	NumberOfCurves(CURVEPROC kind,int nC,int* pnp,BOOL bClose, int nOrder);
			/////////////////
	int		CtlPtStep(CURVEPROC kind, int nDegree);
	/////////////////////////////////////////////////////////////////////////////////////
	int 	DegreeElevate_Seg(pWORLD Cons, pWORLD NewC, int nDegree);
	int 	Tangent_t(pWORLD Cons, double t, int nDegree, WORLD& tangent);
	int 	Tangent_0(pWORLD Cons, int nDegree, WORLD& tangent);
	int		Tangent_0(WORLD b0, WORLD b1, int nDegree, WORLD& tangent);
	int		Tangent_1(WORLD bnm1, WORLD bn, int nDegree, WORLD& tangent);
	double 	Curvature_t(pWORLD Cons, double t, int nDegree);
	double 	Curvature_0(pWORLD Cons, int nDegree);
	int 	SubDivide_t(pWORLD Cons, double t, pWORLD NewC, BOOL bLeft, int nDegree);
    ///////////////////////////////////////////////////////////////////////////////////// Rational
	int 	Rat_DegreeElevate_Seg(	pWORLD Cons, pDOUBLE Wts, 
									pWORLD NewC, pDOUBLE NewW, int nDegree);
	int 	Rat_Tangent_t(pWORLD Cons, pDOUBLE Wts, double t, int nDegree, WORLD& tangent);
	int 	Rat_Tangent_0(pWORLD Cons, pDOUBLE Wts, int nDegree, WORLD& tangent);
	int		Rat_Tangent_0(WORLD b0, WORLD b1, double Wt0, double Wt1, int nDegree,
																		WORLD& tangent);
	int		Rat_Tangent_1(WORLD bnm1, WORLD bn, double Wtnm1, double Wtn, int nDegree,
																		WORLD& tangent);
	double 	Rat_Curvature_t(pWORLD Cons, pDOUBLE Wts, double t, int nDegree);
	double 	Rat_Curvature_0(pWORLD Cons, pDOUBLE Wts, int nDegree);
	int 	Rat_SubDivide_t(pWORLD Cons, pDOUBLE Wts, double t, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nDegree);
	int		Rat_Tangent_t_for_Patch(pWORLD Cons, pDOUBLE Wts, double t, int nDegree,
															pDOUBLE NewWt, WORLD& tangent);
	////////////////
	int		GetTangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,int nDegree,int nCurves,
//						int nCon,int nDim,pDOUBLE pWts,pWORLD pCon);
						int nCon,int nDim,pDOUBLE pWts,pWORLD pCon,double dSameNessRatio);
	int		GetCurrentBezSeg_N_ControlIndex(WORLD wNodeCoord,int& nCtrl,int& nCurrentBezSeg,
//				int nDegree,int nCurves,int nC,pDOUBLE pWts_UV,pWORLD pInC);
				int nDegree,int nCurves,int nC,pDOUBLE pWts_UV,pWORLD pInC,double dSameNessRatio);
	int		GetBezSegEndTangent_0(int nCurrentBezSeg,int nDegree,pWORLD pCon,pDOUBLE pWts,
									int nMaxBezSegs,int nDim,WORLD& Tangent);
	int		GetBezSegEndTangent_1(int nCurrentBezSeg,int nDegree,pWORLD pCon,pDOUBLE pWts,
									int nMaxBezSegs,int nDim,WORLD& Tangent);
	///////////////////////////////////////////////////////////////////////////////////// Helper
	double 	TriangleArea(WORLD b0, WORLD b1, WORLD b2);
	///////////////////////////////////////////////////
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



protected:
    
#ifdef _DEBUG
	/////////////////////////////////////////////// Dump MessageBox
	BOOL		m_bMessage[30];
#endif

public:
	virtual ~CCurve(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _CURVE_H_
