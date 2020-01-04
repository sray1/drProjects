#ifndef	_SOLIDPEN_H_
#define	_SOLIDPEN_H_


#include "DListMgr.h"
#include "Def_Type.h"
#include "Surface3.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CSolidPen : public Surface3
class CSolidPen : public CSurface3
{
// Construction
public:  
	CSolidPen();
	DECLARE_DYNAMIC(CSolidPen)
protected: 
public:
// Implementation

	int			NumberOfBezierPenta
				(
					CURVEPROC kindST, int nCtlS, int nSegS, int nOrderST,
					CURVEPROC kindR, int nCtlR, int nSegR, int nOrderR, BOOL bCloseR, 
					int* pnTr_BZ_ST,int* pnPt_OutST,int* pnSegBZ_R,int* pnPt_OutR,
					int* pnPenBZ
				);

	int			PentaHeds_3D
				(
					SOLIDOUTPUT		O_kind		//  Output Method
				,	BOOL			bClosed		//  Closed?
				,	int				nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_ST		//  3= NonRational / 4 = Rational
				//////////////////
				,	int				nDim_R		//  3= NonRational / 4 = Rational
				,	pDOUBLE			Dis_t_R		//  Output t distribution Pts. for Ratio Business
				,	int				nSolides_R	//  Total Number of Patches in U-dir 
					//////////////////////////////  Globals:
				,	int				nOutGlo_S		//  Total Output in each side of entire Base Patch
					////////////////////
				,	CDListMgr*		pPenList	//	Triangular Patch List
				,	pWORLD			pCon_STR	//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts_STR	//  Total Input Rational Bezier Weights Array		
				,	pWORLD			pOut_STR	//  Total Output Points Array
				,	pDOUBLE			pOutWts_STR	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				);


protected:


	int			EX_MakeSolides		// RATIONAL BEZIER Patches					 EXplicit 
				(
					BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nDim_ST		//  3= NonRational / 4 = Rational
					//////////////////
				,	int			nDim_R		//  3= NonRational / 4 = Rational
				,	pDOUBLE		Dis_t_R		//  Output t distribution Pts. for Ratio Business
				,	int			nSolides_R	//  Total Number of Patches in U-dir 
					//////////////////////////////  Globals:
				,	int			nOutGlo_S		//  Total Output in each side of entire Base Patch
					//////////////////////////
				,	CDListMgr*	pPenList	//	Triangular Patch List
				,	pDOUBLE		pWts_UVW	//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UVW	//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UVW	//  Total Output Points Array
				,	pDOUBLE		pOutWts_UVW	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
				);

	int			EX_Make_A_Solid
				(
					int			nDegree_ST		//  Degree in S-Dir
				,	int			nDim_ST			//  3= NonRational / 4 = Rational
				,	int			nt_S			// 	Output in S-dir
				,	int			nMax_ST			// 	Max Output in ST-plane
				,	int			TriNumCon_ST	//	# of Controls for a Triangle
				/////////////////////////
				,	int			nDegree_R		//  Degree in R-Dir
				,	int			nDim_R			//  3= NonRational / 4 = Rational
				,	int			nt_R			// 	# of subdivision to compute Surface Pts in R-dir
				,	pDOUBLE		Dis_t_R			//  Output t distribution Pts. for Ratio Business
				,	int			nSolides_R		//  Total Number of Patches for Ratio Business 
				,	int			nMax_R			//	Max Output in R-dir
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Base Triangle Type:1=left/2=right
				,	int			nOutStartIndex	//	Global Output Index Start for the Bezier Penta 
				,	int			nOutGloTot_S	//	Total Output in each side of entire Base Patch 
				,	int			iOutGlo			//	Global i Bary Coords for Ist Output of the PentaHed 
				,	int			jOutGlo			//	Global j Bary Coords for Ist Output of the PentaHed 
				//////////////////////////////////
				,	pWORLD		pCon_STR		//	pointer to pointer Control Pt. array for the solid
				,	pDOUBLE		pWts_STR		//	pointer to pointer Wts. array for the solid	
				,	pWORLD		pOut_G			// 	Total Global Output Points Array
				,	pDOUBLE		pOutWT_G		// 	Total Global Output Wts Array
				);



public:
	virtual ~CSolidPen(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CSolidPen)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

