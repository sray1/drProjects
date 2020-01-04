#ifndef	_PAT_TWIST4_H_
#define	_PAT_TWIST4_H_


#include "Surface4.h"
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CPat_Twist4 : public CObject
class AFX_EXT_CLASS CPat_Twist4 : public CSurface4
{
// Construction
public:  
	CPat_Twist4();
	DECLARE_DYNAMIC(CPat_Twist4)
protected: 
public:
// Implementation

	//////////////////////////////////////////////////////////////////////////////////////// Twists
	int		MakeTwists		// RATIONAL BEZIER Patches
					(
						BOOL		bClosed_U	//  IsClosed_U
					,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
					,	int			nDim_U		//  3= NonRational / 4 = Rational
					,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
					,	int			nPatches_U	//  Total Number of Patches in U-dir 
					,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
					,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
					,	BOOL		bClosed_V	//  IsClosed_V
					,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
					,	int			nDim_V		//  3= NonRational / 4 = Rational
					,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
					,	int			nPatches_V	//  Total Number of Patches in U-dir 
					,	pINT		Num_t_V		//  Number of Segments for each Patch Array 
					,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
					,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
					,	pWORLD		pOut_UV		//  Total Output Twist Array
					);

	int		Make_Twists_A_Patch
					(
						PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
					,	BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
					,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
					,	int			nDim_U		// 	3= NonRational / 4 = Rational
					,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
					,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
					,	BOOL		bLast_V		// 	Last Patch in V-Dir for Output saving decision		
					,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
					,	int			nDim_V		// 	3= NonRational / 4 = Rational
					,	int			nt_V		// 	# of subdivision to compute Surface Pts in V-dir
					,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
					,	pWORLD		pOut		// 	Total Output Twist Array
//					,	pDOUBLE		pOutWts		// 	Total Output Wts Array
					,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
					,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
					,	int			nPatches_V	//  Total Number of Patches in V-dir, needed for t-Dist 
					);
	///////////////////////////////////////////////////////////////////////////////
	int		GetaTwistAtaControlNode(WORLD wNodeCoord,WORLD& Twist,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
								pWORLD pCon_UV,double dSameNessRatio);
	int		GetCurrentPatch_N_Controls(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
					pWORLD pCon_UV,double dSameNessRatio,
					pWORLD B);
	int		GetBezPatCornerTwist_00(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B);
	int		GetBezPatCornerTwist_01(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B);
	int		GetBezPatCornerTwist_10(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B);
	int		GetBezPatCornerTwist_11(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B);
	int		Pat_SubDivide_U(pWORLD Cons, double u, 
					pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV);
	int		Pat_SubDivide_V(pWORLD Cons, double v,  
					pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV);
	int		Pat_SubDivide_UV(pWORLD Cons, double u, double v, 
								pWORLD NewC, BOOL bLeftU, BOOL bLeftV, 
								int nDegreeU, int nDegreeV);



protected:

	//////////////////////////////////////////////////////////////////////////// Tensor Product
	int		CalcCornerTwist(WORLD& Twist,int i00,int i10,int i01,int i11,
								int nDegree_U,int nDegree_V,pWORLD B);






	
public:

	
protected:



public:
	virtual ~CPat_Twist4(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPat_Twist4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

