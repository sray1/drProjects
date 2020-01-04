// C3DMath.h : header file
//
#ifndef _3DMATH_H_
#define _3DMATH_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "Def_Type.h"
#include "math.h"
////////////////////////////
typedef	double	(*PDMA3)[4];
/////////////////////////////////////////////////////////////////////////////
// C3DMath
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS C3DMath : public CObject
{
// Construction
public:  
	C3DMath();
//////////////////////////////////////
	DECLARE_SERIAL(C3DMath)
//////////////////////////////////////
protected: 
public:
// Implementation
public:
 
//	BOOL	AreSame_DOUBLE(double a, double b);
	BOOL	AreSame_DOUBLE(double a, double b, double dRatio);
//	BOOL	AreSame_WORLD(pWORLD pa, pWORLD pb);
	BOOL	AreSame_WORLD(pWORLD pa, pWORLD pb, double dRatio);
   ///////////////////////////////////////////////////////////// 
    void	Set3DPts(pLPOINT3 pa, long x, long y, long z)
    					{pa->x =x;pa->y =y; pa->z = z;};
    void	Set3DPts(pWORLD pa, double x, double y, double z)
    					{pa->x =x;pa->y =y; pa->z = z;};
	void 	Add3DPts(pLPOINT3 pa, pLPOINT3 pb, pLPOINT3 pc);
	void 	Add3DPts(pWORLD pa, pWORLD pb, pWORLD pc);
	void 	Sub3DPts(pLPOINT3 pa, pLPOINT3 pb, pLPOINT3 pc);
	void 	Sub3DPts(pWORLD pa, pWORLD pb, pWORLD pc);
	void 	Avg3DPts(pWORLD pda, pWORLD pdb, pWORLD pdc);
	double 	Len3DPts(pWORLD pa)
					{
						return ( sqrt(pa->x*pa->x + pa->y*pa->y + pa->z*pa->z) );
					}	
	void 	Scale3DPts(double scale,pWORLD pa);
	double 	Dot3DPts(pWORLD pa,pWORLD pb);
	void 	Cross3DPts(pWORLD pb,pWORLD pc,pWORLD pa);

	void 	ScaleVECTOR(double scale,pVECTOR pV);
	void 	AddVECTOR(pVECTOR a,pVECTOR b,pVECTOR c);
	double 	VdotV(VECTOR Va,VECTOR Vb);
	void 	VcrossV(pVECTOR pVa,pVECTOR pVb,pVECTOR pVc);
	
	void 	Normalize(pLPOINT3 plSrc,pWORLD pdDest,int nPrecision);
	void 	Normalize(pWORLD pdSrc,pWORLD pdDest);
	
	void 	GetIdentityMATRIX(pMATRIX pM);
	void	SetMATRIX(pMATRIX pM,pWORLD pCol_X,pWORLD pCol_Y,pWORLD pCol_Z,pWORLD pCol_W);
	void 	ScaleMATRIX(double scale,pMATRIX pM);
	void 	TransposeMATRIX(pMATRIX pM);
	void 	AddMATRIX(pMATRIX pMa,pMATRIX pMb,pMATRIX pMc);
	void 	MultMATRIX(pMATRIX pMa,pMATRIX pMb,pMATRIX pMc);
	void 	F_MultMATRIX(pMATRIX a,pMATRIX b,pMATRIX c);
	void 	InvertMATRIX(pMATRIX pMa,pMATRIX pMb);
	double 	GetDeterminant(pMATRIX pM);
	/////////////////////////////////////////////////////////////// Triangular
	void	GetBaryFromUV(pWORLD p1, pWORLD p2, pWORLD p3, pWORLD p, pWORLD pBCC);
	void	GetUVFromBary(pWORLD p1, pWORLD p2, pWORLD p3, pWORLD p, pWORLD pBCC);
	double	GetDeterminant(pWORLD p1, pWORLD p2, pWORLD p3);
	//////////////////////////////////			
	int 	Solve_TriDiag(pDOUBLE a, pDOUBLE b, pDOUBLE c, PDMA3 d, PDMA3 sol,
						 int L, int nDim);
	int 	Solve_TriDiagPeriodic(pDOUBLE a, pDOUBLE b, pDOUBLE c, PDMA3 d, 
											PDMA3 sol, int L, int nDim);
	void 	LUDecompose(pMATRIX a,pINT indx,pDOUBLE d);
	void 	LUBackSubstitute(pMATRIX a, pINT indx, pDOUBLE b);
	/////////////////////////////////////////////////////////////////											
	void	BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size);

	


public:
	~C3DMath(){};
	void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(C3DMath)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
