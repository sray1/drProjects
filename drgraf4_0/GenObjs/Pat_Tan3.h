#ifndef	_PAT_TAN3_H_
#define	_PAT_TAN3_H_


#include "Surface3.h"
/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CPat_Tan3 : public CObject
class AFX_EXT_CLASS CPat_Tan3 : public CSurface3
{
// Construction
public:  
	CPat_Tan3();
	DECLARE_DYNAMIC(CPat_Tan3)
protected: 
public:
// Implementation


	int			MakeTangents
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
				,	pWORLD			pOut_S		//  Total Output Points Array
				,	int				nDir1		//	direction 1=S/2=T/3=R
				,	pWORLD			pOut_T		//  Total Output Points Array
				,	int				nDir2		//	direction 1=S/2=T/3=R
				,	int				nOut		//	expected number of generated Patch vertices	
				);

	int			MakeTangentsInOneDir
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
				,	int				nDir		//	direction 1=S/2=T/3=R
				,	int				nOut		//	expected number of generated Patch vertices	
				);

		int			DC_GetTangentsForNormalAtaNode		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
				(
					WORLD		wNodeCoord
				,	WORLD&		OutTan_U	//  Total Output Points Array
				,	WORLD&		OutTan_V	//  Total Output Points Array
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	double		dSameNessRatio
				);

	int			DC_GetaTangentAtaNode		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
				(
					WORLD		wNodeCoord
				,	WORLD&		OutTan		//  Total Output Points Array
				,	int			DirTan		//  Total Output Points Array
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	double		dSameNessRatio
				);

protected:


	BOOL		IsDesiredControlIndices(WORLD wNodeCoord,
//					int& LIndex,pWORLD pCon,int nConTri);
					int& LIndex,pWORLD pCon,int nConTri,double dSameNessRatio);
	int			DC_GetTangentsForNormalAtaLIndex
				(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			LIndex			//	Linear Index where tangents needed
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	WORLD&		OutTanU		// 	tangent along u
				,	WORLD&		OutTanV		// 	tangent along v
				);
	///////////////////////////////////////////////////////////////////////////////////////////
	int			DC_GetaTangentAtaLIndex
				(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			LIndex			//	Linear Index where tangents needed
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	WORLD&		OutTan		// 	tangent
				,	int&		DirTan		// 	dir for tangent
				);
	///////////////////////////////////////////////////////////////////////////////////////////
	int			DC_MakeTangentsInOneDir		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
				(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////  Globals:
				,	int			nOutGlo_S	//  Total Output in each side of entire Patch 
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOutTan		//  Total Output Points Array
				,	int			nDir		//  direction of Tangent
				);

	int			DC_Make_TangentsInOneDir_A_Patch
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
				,	pWORLD		pOutTan_G	// 	Total Output Global Points Array
				,	int			nDir		// 	Total Output Global Points Array
				);
	int			DC_MakeTangents		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
				(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////  Globals:
				,	int			nOutGlo_S	//  Total Output in each side of entire Patch 
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOutTan_U	//  Total Output Points Array
				,	pWORLD		pOutTan_V	//  Total Output Points Array
				);

	int			DC_Make_Tangents_A_Patch
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
				,	pWORLD		pOutTanU_G	// 	Total Output Global Points Array
				,	pWORLD		pOutTanV_G	// 	Total Output Global Points Array
				);
	int			Tangent_UV(pWORLD Cons, double u, double v, int nDegree, int nDir,WORLD& tangent);
	int			Tangent_00(pWORLD Cons, int nDegree, int nDir,WORLD& tangent);
	int			SubDivide(pWORLD Cons, double u, double v, pWORLD NewC, int nDegree,
																			int nSide);
	int			Pick_SubDivCons_U(pWORLD NewC, pWORLD OldC, int r, int nDegree);
	int			Pick_SubDivCons_V(pWORLD NewC, pWORLD OldC, int r, int nDegree);
	int			Pick_SubDivCons_W(pWORLD NewC, pWORLD OldC, int r, int nDegree);
	///////////////////////////
	int			Rat_Tangent_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, int nDegree, int nDir,
																					WORLD& tangent);
	int			Rat_Tangent_00(pWORLD Cons, pDOUBLE Wts, int nDegree, int nDir,WORLD& tangent);
	int			Rat_SubDivide(pWORLD Cons, pDOUBLE Wts, double u, double v,
									pWORLD NewC, pDOUBLE NewW, int nDegree,int nSide);
	int			Rat_Pick_SubDivCons_U(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree);
	int			Rat_Pick_SubDivCons_V(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree);
	int			Rat_Pick_SubDivCons_W(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree);


protected:

	int			m_nDir1;
	int			m_nDir2;
public:
	virtual ~CPat_Tan3(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPat_Tan3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

