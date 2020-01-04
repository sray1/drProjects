#ifndef	_PAT_TAN4_H_
#define	_PAT_TAN4_H_


#include "Surface4.h"
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CPat_Tan4 : public CObject
class AFX_EXT_CLASS CPat_Tan4 : public CSurface4
{
// Construction
public:  
	CPat_Tan4();
	DECLARE_DYNAMIC(CPat_Tan4)
protected: 
public:
// Implementation

	//////////////////////////////////////////////////////////////////////////////////////// Tangents
	int		MakeTangents		// RATIONAL BEZIER Patches
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
					,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
					,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
					,	pWORLD		pOut_UV		//  Total Output Tangent Array
					);

	int		Make_Tangents_A_Patch
					(
						PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
					,	PD44		ppWts_U4V4	//	pointer to pointer Wts. array for the patch	
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
					,	pWORLD		pOut		// 	Total Output Tangent Array
//					,	pDOUBLE		pOutWts		// 	Total Output Wts Array
					,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
					,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
					,	int			nPatches_V	//  Total Number of Patches in V-dir, needed for t-Dist 
					);
	///////////////////////////////////////////////////////////////////////////////
	int		GetaTangentAtaNode/*Control*/(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
//								pDOUBLE pWts_UV,pWORLD pCon_UV);
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio);
	int		GetTangentsAtaNode/*Control*/(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
//								pDOUBLE pWts_UV,pWORLD pCon_UV);
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio);





protected:

	//////////////////////////////////////////////////////////////////////////// Tensor Product
	int		GetCurrentPatch_N_ControlIndices(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,int& nCurrentPat_U,int& nCurrentPat_V,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
//					pDOUBLE pWts_UV,pWORLD pCon_UV);
					pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio);
	int		GetBezPatEdgeTangent_00(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV);
	int		GetBezPatEdgeTangent_01(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV);
	int		GetBezPatEdgeTangent_10(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV);
	int		GetBezPatEdgeTangent_11(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV);
	int		GetEdgeControls(
				WORLD b[][4],double w[][4],int nCurrentPat_U,int nCurrentPat_V,
				int nDegree_U,int nDegree_V,int nPatches_U,int nPatches_V,
				int	nCon_U,int	nCon_V,pDOUBLE pWts_UV,pWORLD pCon_UV);

	
public:

	
protected:



public:
	virtual ~CPat_Tan4(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPat_Tan4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

