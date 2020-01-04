#ifndef	_SOLIDHEX_H_
#define	_SOLIDHEX_H_


#include "Def_Type.h"
#include "Surface4.h"
////////////////////////////
#define	BSPLINE_TOO_FEW_POINTS			-1
#define	MEMORY_ERROR					-2
#define	HERMITE_OPENCURVE				false
#define	HERMITE_CLOSEDCURVE				true
#define	ERROR_MISSING_ARGUMENTS			0x7FFF
/////////////////////////////////////////////////////////////////////////////
// CDrSolid4
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CSolidHex : public CObject
class CSolidHex : public CSurface4
{
// Construction
public:  
	CSolidHex();
	DECLARE_DYNAMIC(CSolidHex)
protected: 
public:
// Implementation

	int		NumberOfSolides
			(
				CURVEPROC kindU, int nCtlU, int nSegU, BOOL bCloseU, int nOrderU,
				CURVEPROC kindV, int nCtlV, int nSegV, BOOL bCloseV, int nOrderV,
				CURVEPROC kindW, int nCtlW, int nSegW, BOOL bCloseW, int nOrderW,
				int* pnPU,int* pnPV,int* pnPW,int* pnOut_U,int* pnOut_V,int* pnOut_W
			);

    //////////////////////////////////////////////////////////////////////////// Tensor Product
	int		TensorProduct_3D
				(
					SOLIDOUTPUT		O_kind		//  Output Method
				,	BOOL			bClosed_S	//  IsClosed_S
				,	int				nDegree_S	//  Degree in S-Dir
				,	int				nCon_S		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_S		//  3= NonRational / 4 = Rational
				,	int				nSolides_S	//  Total Number of Patches 
				,	pINT			Num_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	BOOL			bClosed_T	//  IsClosed_T
				,	int				nDegree_T	//  Degree in T-Dir
				,	int				nCon_T		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_T		//  3= NonRational / 4 = Rational
				,	int				nSolides_T	//  Total Number of Patches 
				,	pINT			Num_t_T		//  Number of Output Segments Array in T-Dir for each patch
				,	pDOUBLE			Dis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	BOOL			bClosed_R	//  IsClosed_S
				,	int				nDegree_R	//  Degree in S-Dir
				,	int				nCon_R		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_R		//  3= NonRational / 4 = Rational
				,	int				nSolides_R	//  Total Number of Patches 
				,	pINT			Num_t_R		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_R		//  Output t distribution Pts. for Ratio Business				
				,	pWORLD			pCon_STR	//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts_STR	//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut_STR	//  Total Output Points Array
				,	pDOUBLE			pOutWts_STR	//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				);


protected:

	//////////////////////////////////////////////////////////////////////////// Tensor Product
	int 	HO_MakeSolides
				(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			CtlStep_U	//  Control Pt. Step
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			CtlStep_V   //  Control Pt. Step
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array
				,	pDOUBLE		Dis_t_V		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	BOOL		bClosed_W	//  IsClosed_V
				,	int			CtlStep_W   //  Control Pt. Step
				,	int			nDegree_W	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_W		//  3= NonRational / 4 = Rational
				,	int			nCon_W		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_W	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_W		//  Number of Segments for each Patch Array
				,	pDOUBLE		Dis_t_W		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	pDOUBLE		pWts_UVW	//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UVW	//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UVW	//  Total Output Points Array
				,	pDOUBLE		pOutWts_UVW	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
				);
	int 	HO_Make_A_Solid
				(
					PW444		ppCon_S4T4R4	//	pointer to pointer Control Pt. array for the solid
				,	PD444		ppWts_S4T4R4	//	pointer to pointer Wts. array for the solid	
//				,	PDMA22		pMCoef_1		//  Basis*Geometry Matrix for Linear
//				,	PDMA33		pMCoef_2		//  Basis*Geometry Matrix for Quadratic
//				,	PDMA44		pMCoef_3		//  Basis*Geometry Matrix for Cubic
				/////////////////////////
				,	BOOL		bLast_S			//  Last Patch in S-Dir for Output saving decision
				,	int			nDegree_S		//  Degree in S-Dir
				,	int			nDim_S			//  3= NonRational / 4 = Rational
				,	int			nt_S			// 	# of subdivision to compute Surface Pts in S-dir
				,	pDOUBLE		Dis_t_S			//  Output t distribution Pts. for Ratio Business				
				/////////////////////////
				,	BOOL		bLast_T			// 	Last Patch in T-Dir for Output saving decision		
				,	int			nDegree_T		//  Degree in T-Dir
				,	int			nDim_T			//  3= NonRational / 4 = Rational
				,	int			nt_T			// 	# of subdivision to compute Surface Pts in T-dir
				,	pDOUBLE		Dis_t_T			//  Output t distribution Pts. for Ratio Business				
				/////////////////////////
				,	BOOL		bLast_R			//  Last Patch in R-Dir for Output saving decision
				,	int			nDegree_R		//  Degree in R-Dir
				,	int			nDim_R			//  3= NonRational / 4 = Rational
				,	int			nt_R			// 	# of subdivision to compute Surface Pts in R-dir
				,	pDOUBLE		Dis_t_R			//  Output t distribution Pts. for Ratio Business
				/////////////////////////
				,	pWORLD		pOut			// 	Total Output Points Array
				,	pDOUBLE		pOutWts			// 	Total Output Wts Array
				,	int			nEmitTot_S		//  Total Points for All Patches in S-dir
				,	int			nEmitTot_ST		//  Total Points for All Patches in ST-plane(needed for Memory)
				,	int			nSolides_S		//  Total Number of Patches for Ratio Business 
				,	int			nSolides_T		//  Total Number of Patches for Ratio Business 
				,	int			nSolides_R		//  Total Number of Patches for Ratio Business 
				);

	
public:

	
protected:

	int	m_nsubdivisions;


public:
	virtual ~CSolidHex(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CSolidHex)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

