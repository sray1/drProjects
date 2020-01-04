// CSurface4.cpp : implementation of the CSurface4 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "Curve_1.h"
#include "Curve_2.h"
#include "Curve_3.h"

#include "Surface4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSurface4

IMPLEMENT_DYNAMIC(CSurface4,CObject)
/*
BEGIN_MESSAGE_MAP(CSurface4,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CSurface4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////
static DMA22
	CoefLagLin		= {	{ -1,	 1 },
						{  1,	 0 }	}
,					
	CoefBezierLin	= {	{ -1,	 1 },
						{  1,	 0 }	};
static DMA33
	CoefLagQuad		= {	{  2,  -4,	 2 },
						{ -3,	4,	-1 },
						{  1,	0,	 0 } }
,					
	CoefBezierQuad	= {	{  1,  -2,	 1 },         
						{ -2,	2,	 0 },
						{  1,   0,	 0 } };
static DMA44
	CoefBezierCubic = {	{ -1,	 3,	-3,	1 },
						{  3,	-6,	 3,	0 },
						{ -3,	 3,	 0,	0 },
						{  1,	 0,	 0,	0 }	};
/*					
,	CoefBSpline = {
		{ -0.166666666F,  0.5F, 		 -0.5F,  		0.166666666F },
		{  0.5F,			-1,  		  0.5F,  		0 			},
		{ -0.5F,			 0,  		  0.5F,  		0 			},
		{  0.166666666F,  0.66666666F,  0.166666666F,  0 			}	} 
		
,	CoefCatmullRom = {	{ -0.5F,	 1.5F,	-1.5F,	 0.5F },
						{  1,	-2.5F,	 2.0F,	-0.5F },
						{ -0.5F,	 0,	 0.5F,	 0 },
						{  0,	 1,	 0,	 0 }	} 
						
,	CoefHermite = {	{  2, -2,  1,  1 },
					{ -3,  3, -2, -1 },
					{  0,  0,  1,  0 },
					{  1,  0,  0,  0 }	} 
					
,	CoefBeta = {	{ -2,  2, -2,  2 },
					{  6, -3,  3,  0 },
					{ -6,  6,  6,  0 },
					{  2,  1,  2,  0 }	} 
,	CoefAlfa					
; 
*/
static DMAT
	CoefBezier		= {	{ -1,	 3,	-3,	1 },
						{  3,	-6,	 3,	0 },
						{ -3,	 3,	 0,	0 },
						{  1,	 0,	 0,	0 }	}
,	CoefBSpline		= { { -0.166666666F, 	0.5F, 			-0.5F,  		0.166666666F},
						{  0.5F,			-1,  			0.5F,  			0 			},
						{ -0.5F,			0,  			0.5F,  			0 			},
						{  0.166666666F,	0.66666666F,	0.166666666F,	0 			}	}
,	CoefCatmullRom	= {	{ -0.5F,	 1.5F,	-1.5F,	0.5F	},
						{  1,		-2.5F,	 2,		-0.5F	},
						{ -0.5F,	 0,	 	0.5F,	0		},
						{  0,	 	1,	 	0,		0		}	}
,	CoefHermite		= {	{  2, -2,  1,  1 },
						{ -3,  3, -2, -1 },
						{  0,  0,  1,  0 },
						{  1,  0,  0,  0 }	}
,	CoefBeta		= {	{ -2,  2, -2,  2 },
						{  6, -3,  3,  0 },
						{ -6,  6,  6,  0 },
						{  2,  1,  2,  0 }	}
;
//////////////////////////////////////////////////////////////////////
enum { X,Y,Z,W };

#define	SETM(m,n,o,w)		(m)[(n)][X] = (o).x * (w);\
							(m)[(n)][Y] = (o).y * (w);\
							(m)[(n)][Z] = (o).z * (w);\
							(m)[(n)][W] = (w)
#define	SCALEP(a,b)			(a).x = (a).x * (b);\
							(a).y = (a).y * (b);\
							(a).z = (a).z * (b)
#define	SUBP(a,b,c)			(c).x = (a).x - (b).x;\
							(c).y = (a).y - (b).y;\
							(c).z = (a).z - (b).z
#define	P2F3D(_a,_b)	(_b).x = (_a).x; (_b).y = (_a).y; (_b).z = (_a).z

//////////////////////
CSurface4::CSurface4()
{ 
	m_nsubdivisions	= 1;

} 
/////////////////////////////////////////////////////////////////////
int CSurface4::NumberOfPatches(
				CURVEPROC kindU, int nCtlU, BOOL bCloseU, int nOrderU,
				CURVEPROC kindV, int nCtlV, BOOL bCloseV, int nOrderV,
				int* pnPU, int* pnPV)
{ 
	////////////////////////////////////////////////////////////////////////
	// 	Return: 	np 		= No. of Output Pts. to be generated                      
	//	Parameter modified:
	//				pnPU 	= No. of Cubic Patches in U-direction 
	//				pnPV 	= No. of Cubic Patches in V-direction 
	////////////////////////////////////////////////////////////////////////
	CCurve Curve;
	int du,dv;
	if( !(du = Curve.CtlPtStep( kindU, nOrderU-1 )) )	// needed nDegree
		return -1;
	if( !(dv = Curve.CtlPtStep( kindV, nOrderV-1 )) )	// needed nDegree
		return -1;
	////////////////////////////////////
	*pnPU = bCloseU ? nCtlU/du : (nCtlU - nOrderU)/du + 1;
	*pnPV = bCloseV ? nCtlV/dv : (nCtlV - nOrderV)/dv + 1;
/*
	// This was originally there for Uniform #of Output for each Bez. Patch
	*pnOut_U	= nSegU * (*pnPU) + 1;
	*pnOut_V	= nSegV * (*pnPV) + 1;
	int np		= (nSegU*(*pnPU)+1) * (nSegV*(*pnPV)+1);
*/
	///////////////////////////////
	return (*pnPU)*(*pnPV);
	////////

} 

PDMAT CSurface4::SetBasis(enum CURVEPROC kind,double bias,double tension)
{
	C3DMath	Math3D;
	///////////////
	DMAT	BasisBeta = {	{ -2,  2, -2,  2 },
							{  6, -3,  3,  0 },
							{ -6,  6,  6,  0 },
							{  2,  1,  2,  0 }	};
	PDMAT	C;
	double	r,bias2,bias3;
	int		i,j;

	switch( kind ) {
		case CP_BSPLINE:		return (PDMAT)CoefBSpline;
		case CP_CATMULLROM:		return (PDMAT)CoefCatmullRom;
		case CP_BEZIER:			return (PDMAT)CoefBezier;
		case CP_HERMITE:		return (PDMAT)CoefHermite;
		case CP_BETA:			break;
	}
	C = (PDMAT)CoefBeta;
	Math3D.BlockCopy( (HUGEBLK)BasisBeta, (HUGEBLK)C, sizeof(BasisBeta) );
	bias2 = bias * bias;
	bias3 = bias2 * bias;
	for( i=0;i<3; i++ )
		C[i][0] *= bias3;
	C[0][1] *= tension + bias3 + bias2 + bias;
	C[0][2] *= tension + bias2 + bias + 1;
	C[1][1] *= tension + 2 * bias3 + 2 * bias2;
	C[1][2] *= tension + 2 * bias2;
	C[2][1] *= bias3 - bias;
	C[2][2] *= bias;
	C[3][1] *= tension + 4 * ( bias2 + bias );
	r = 1.0F / (tension + 2*bias3 + 4*bias2 + 4*bias + 2);
	for( i=0; i<4; i++ )
		for( j=0; j<4; j++ )
			C[i][j]*=r;
	return C;
}
///////////////////////////////////////////////////
PDMAT CSurface4::ForwardDifference(int nSegs)
{
	if(nSegs<1) return (PDMAT)NULL;
	///////////////////////////////////
	// Forward Difference Matrix: Foley p 535
	static	DMAT E;
	////////////////////////////
	double delta	= 1.0/nSegs;
	////////////////////////////////////////// E(epsilon): Forward Difference
	E[0][0]=E[0][1]=E[0][2]=E[1][3]=E[2][2]=E[2][3]=E[3][1]=E[3][2]=E[3][3] = 0;
	E[0][3]=1.0;
	E[1][2]=delta;
	E[1][1]=delta * delta;
	E[1][0]=E[1][1] * delta;
	E[2][0]=E[3][0] = E[1][0] * 6.0;
	E[2][1]=E[1][1] * 2.0;
	//////////////////////////////////////////
	return (PDMAT)E; 
}

void CSurface4::ComputeEUM_G_XposeEVM(PWMAT DOO,PDMAT EUM, PDMAT EVM, PWMAT G)
{

	///////////////////////////////////
	// Set up Doo = E(epsilon)_Ci_TransposeE(delta):(i = x,y,z)
	// Forward Difference Method: Foley p 535
	int i,j,k,l;
	double t,tx,ty,tz;
	////////////////////////////////////////// 
	// multiply EUM_G_EVMtranspose, 
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++) 
		{
			tx = 0;ty = 0;tz = 0;
			for(k=0; k<4; k++)
			{
				for(l=0; l<4; l++)
				{   
					t = EUM[i][k] * EVM[j][l]; 
					tx += t * G[k][l].x;
					ty += t * G[k][l].y;
					tz += t * G[k][l].z;
				}
			}		
			DOO[i][j].x = tx;
			DOO[i][j].y = ty;
			DOO[i][j].z = tz;
		}
	}	
}

void CSurface4::ComputeEUorV_x_M(PDMAT EM, PDMAT FD, PDMAT M)
{
	int		i,j,k;
	double	t;

	// multiply FD (ForwardDiff) by M (Coeff.) = EUM or EVM 
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++) 
		{
			t = 0;
			for(k=0; k<4; k++)
				t += FD[i][k]*M[k][j];
			EM[i][j] = t;
		}
	}		
}

int CSurface4::GeneratePointsOnCubic(PWMAT D,int nSegU,int nSegV,WORLD P[],
									int nPatchU,
									int uCur,int vCur,int nMaxU, int nMaxV)
{
	//**************************************************
	// Output Points generate for each CubicPatch:
	// Forward Difference Method: Foley p 535
	// Correspondence:
	// 	s<->U, epsilon; t<->V,delta; 
	// We want to store:
	// 	for V or t = 0		: all USegs , then 
	//	for V ot t = delta	: all USegs , and so on 
	//************************************************** 
	int m,n,i,nOut=0;
	WORLD fo,dfo,d2fo,d3fo;
	long k;
	////////////////////////////////////////////////////////// Compute Points(x,y,z)
	for (m=0; m<nMaxV; m++)
	{
		//////////////////////////////////////////////// for all U
/*
		fo 		= D[0][0];	
		dfo 	= D[1][0];	
		d2fo 	= D[2][0];	
		d3fo 	= D[3][0];
*/		
		fo 		= D[0][0];	
		dfo 	= D[0][1];	
		d2fo 	= D[0][2];	
		d3fo 	= D[0][3];
		//////////////////	
		for (n=0; n<nMaxU; n++)
		{
			nOut++;          // increment points created
			////////////////////////////////////////////
			k = vCur * ((nPatchU*nSegU + 1)*nSegV)	+
				   m * (nPatchU*nSegU + 1)			+
				uCur * nSegU						+
				   n;
			////////////////////////////////////////////		   
//			P->x = fo.x;	
//			P->y = fo.y;	
//			P->z = fo.z;
			P[k].x = fo.x;	
			P[k].y = fo.y;	
			P[k].z = fo.z;
			/////////////// iterate for next U or s or epsilon
			fo.x 		+= dfo.x;
			fo.y 		+= dfo.y;
			fo.z 		+= dfo.z;
			
			dfo.x		+= d2fo.x;
			dfo.y		+= d2fo.y;
			dfo.z		+= d2fo.z;
			
			d2fo.x		+= d3fo.x;
			d2fo.y		+= d3fo.y;
			d2fo.z		+= d3fo.z;
			///////////////
//			P++;
		} 
		/////////////////// iterate for next V or t or delta 
		for (i = 0;i<4;i++)
		{
/*
			D[i][0].x += D[i][1].x;	//Col1=Col1+Col2 
			D[i][0].y += D[i][1].y;	//Col1=Col1+Col2 
			D[i][0].z += D[i][1].z;	//Col1=Col1+Col2 

			D[i][1].x += D[i][2].x;	//Col2=Col2+Col3 
			D[i][1].y += D[i][2].y;	//Col2=Col2+Col3 
			D[i][1].z += D[i][2].z;	//Col2=Col2+Col3 

			D[i][2].x += D[i][3].x;	//Col3=Col3+Col4 
			D[i][2].y += D[i][3].y;	//Col3=Col3+Col4 
			D[i][2].z += D[i][3].z;	//Col3=Col3+Col4
*/			 
			D[0][i].x += D[1][i].x;	//Row1=Row1+Row2 
			D[0][i].y += D[1][i].y;	//Row1=Row1+Row2 
			D[0][i].z += D[1][i].z;	//Row1=Row1+Row2 

			D[1][i].x += D[2][i].x;	//Row2=Row2+Row3 
			D[1][i].y += D[2][i].y;	//Row2=Row2+Row3 
			D[1][i].z += D[2][i].z;	//Row2=Row2+Row3 

			D[2][i].x += D[3][i].x;	//Row3=Row3+Row4 
			D[2][i].y += D[3][i].y;	//Row3=Row3+Row4 
			D[2][i].z += D[3][i].z;	//Row3=Row3+Row4 
		}
	}
	////////////////		
	return nOut;	
}	
	
void CSurface4::ComputeFDiff_x_Mcoeff
		(
			enum CURVEPROC	kind
		,	double			bias			// beta
		,	double			tension			// beta and hermite
		,	int				nSegU			// number of Intervals in U direction/cubic curve
		,	int				nSegV			// number of Intervals in V direction/cubic curve
		,	PDMAT			EUM
		,	PDMAT			EVM
		)
{
	C3DMath		Math3D;
	///////////////////
	DMAT		MCoeff,FDiff_U,FDiff_V;
	PDMAT		pMCoeff = (PDMAT)MCoeff,pFDiff_U = (PDMAT)FDiff_U,
										pFDiff_V = (PDMAT)FDiff_V,B,FD;
	//////////////////////////////////////////////////// Coeff Matrix
	B = SetBasis( kind, bias, tension );
	Math3D.BlockCopy( (HUGEBLK)B, (HUGEBLK)pMCoeff, sizeof(double)*16 );
	//////////////////////////////////////////////////// ForwardDifference Matrices
	FD = ForwardDifference(nSegU);
	Math3D.BlockCopy( (HUGEBLK)FD, (HUGEBLK)pFDiff_U, sizeof(double)*16 );
	//////////////////////////////////////////////////// Compute FDiffUxMCoeff 
	ComputeEUorV_x_M(EUM,FDiff_U,MCoeff);  // used to multply matrices
	////////////////////////////////////////////////////
	FD = ForwardDifference(nSegV);
	Math3D.BlockCopy( (HUGEBLK)FD, (HUGEBLK)pFDiff_V, sizeof(double)*16 );
	//////////////////////////////////////////////////// Compute FDiffUxMCoeff 
	ComputeEUorV_x_M(EVM,FDiff_V,MCoeff);  // used to multply matrices
	//////////////////////////////////
	return;
}	

int CSurface4::MakePatchesToFit
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
		PDMAT		EUM,	// EM Matrix
		PDMAT		EVM		// EM Matrix
	)
{
	CCurve	Curve;
	//////////////
	BOOL	bEndU,bEndV;
	WMAT	DOO,G;
	WORLD	d,*P;
	pWORLD	p,pv;
	int		u, v, du, dv, VnCU,	nOut = 0, nMaxU,nMaxV;
	int		U[4], V[4], vIx[4][4];	// vertex indices
	//////////////////////////////////////////////////// Control pt steps
	p	= pOut;
	du 	= Curve.CtlPtStep( kind, 3 );	//degree = 3:Cubic Hardcoded
	dv 	= du;
	//////////////////////////////////////////////////////////////////// LOOP		
	for( V[0] = v = 0; v < nPV; v++, V[0]+=dv ) 
	{
		V[1] = (V[0]+1) % nCtlV;
		V[2] = (V[0]+2) % nCtlV;
		V[3] = (V[0]+3) % nCtlV;
		/////////////////////////////////////////// U direction Cubic Patches
		for( U[0] = u = 0; u < nPU; u++, U[0]+=du ) 
		{
			U[1] = (U[0]+1) % nCtlU;
			U[2] = (U[0]+2) % nCtlU;
			U[3] = (U[0]+3) % nCtlU;
			VnCU = V[0] * nCtlU;
			vIx[0][0] = VnCU + U[0]; vIx[0][1] = VnCU + U[1];
			vIx[0][2] = VnCU + U[2]; vIx[0][3] = VnCU + U[3];			
			VnCU = V[1] * nCtlU;
			vIx[1][0] = VnCU + U[0]; vIx[1][1] = VnCU + U[1];
			vIx[1][2] = VnCU + U[2]; vIx[1][3] = VnCU + U[3];
			VnCU = V[2] * nCtlU;
			vIx[2][0] = VnCU + U[0]; vIx[2][1] = VnCU + U[1];
			vIx[2][2] = VnCU + U[2]; vIx[2][3] = VnCU + U[3];
			VnCU = V[3] * nCtlU;
			vIx[3][0] = VnCU + U[0]; vIx[3][1] = VnCU + U[1];
			vIx[3][2] = VnCU + U[2]; vIx[3][3] = VnCU + U[3];
			///////////////////////////////////////////////// Geometry Matrix 
			// construct geometry matrix for patch
			for(int i=0; i<4; i++ ) 
			{
				if( kind == CP_HERMITE ) 
				{
					// geometry vector [p0 p3 t0 t3]
					double	s = tension;
					P2F3D( ptCntrl[vIx[i][0]], G[i][0] );	// p0
					P2F3D( ptCntrl[vIx[i][3]], G[i][1] );	// p3
					SUBP( ptCntrl[vIx[i][1]], ptCntrl[vIx[i][0]], d );
					SCALEP( d, s ); P2F3D( d, G[i][2] );// t0 = (p1-p0)*s
					SUBP( ptCntrl[vIx[i][3]], ptCntrl[vIx[i][2]], d );
					SCALEP( d, s ); P2F3D( d, G[i][3] );// t3 = (p3-p2)*s
				}
				else
				for(int j=0; j<4; j++ ) 
				{	
					pv = ptCntrl+vIx[i][j];
					P = &G[i][j];
					P2F3D( *pv, *P );
				}
   		 	}
			///////////////////////////////////////////////// Cubic Patch
//			ComputeEUM_G_XposeEVM(DOO,EUM,EVM,G);
			ComputeEUM_G_XposeEVM(DOO,EVM,EUM,G);
			/////////////////////////////////////////////////
			bEndU = FALSE;
			bEndV = FALSE;
			if(u == (nPU-1)) bEndU = TRUE;
			if(v == (nPV-1)) bEndV = TRUE;
			/////////////////////////////
			nMaxU = bEndU?(nSegU+1):nSegU; // no. of pts to be generated in U
			nMaxV = bEndV?(nSegV+1):nSegV; // no. of pts to be generated in V
//			nOut +=GeneratePointsOnCubic(DOO,nSegU,nSegV,p,bEndU,bEndV,nMaxU,nMaxV );
			nOut +=GeneratePointsOnCubic(DOO,nSegU,nSegV,pOut,
											nPU,u,v,nMaxU,nMaxV );
			/////////////////////////////
//			p += nMaxU*nMaxV;
		}
	}
	////////////
	return nOut;
	////////////
}
////////////////////////////////////////////////////////////////////////////////////////////
void CSurface4::SetBasis(CURVEPROC kind, 
				PDMA22 pMCoef_1,PDMA33 pMCoef_2,PDMA44 pMCoef_3,int nDegree)
{
/*						////////// NOT USED /////////////
	///////////////////
	CCurve_1* pCurve_1;
	CCurve_2* pCurve_2;
	CCurve_3* pCurve_3;
	///////////////////
	switch(nDegree)
	{
		case 1:
			pMCoef_1 = pCurve_1->SetBasis(CU_BEZIER,0,0,0);
		    break;

		case 2:
			pMCoef_2 = pCurve_2->SetBasis(CU_BEZIER,0,0,0);
		    break;

		case 3:
			pMCoef_3 = pCurve_3->SetBasis(CU_BEZIER,0,0,0);
		    break;
	}
	////////
	return;
*/	
}

int CSurface4::HO_MakePatches		// RATIONAL BEZIER Patches
			(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			CtlStep_U	//  Control Pt. Step
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			CtlStep_V   //  Control Pt. Step
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Points Array
				,	pDOUBLE		pOutWts_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
			)
{
//////////////////////////////////////////////////////////////////
	pWORLD	p_U,p_V;
	pDOUBLE pw_U,pw_V;
	int		i,j,u, v, VnCU,	nOutP = 0, nOut = 0, nMaxU,nMaxV,nMaxUV;
	int		nt_U,nt_V,U[4], V[4], vIx[4][4];	// vertex indices
	BOOL	bLast_U,bLast_V;
	////////////////////////////////////// memory for array of pointers
	PW44 pInC_44 = new pWORLD[4][4];	//	Control Pt. array for the patch: RESERVED for Maximum Cubic
	PD44 pInW_44 = new pDOUBLE[4][4]; 
	/////////////////////////////////////////////////////// Totals in U dir
	int nEmitTot_U=0;
	for(u=0;u<nPatches_U;u++)
		nEmitTot_U += *(Num_t_U + u);
	nEmitTot_U++;
	//////////////////////////////////////////////////////////////////////////// V direction:LOOP
	p_V		= pOut_UV; 
	pw_V	= pOutWts_UV;
	/////////////////////	
	for( V[0] = v = 0; v < nPatches_V; v++, V[0]+=CtlStep_V ) 
	{
		for(i=1;i<=nDegree_V;i++)
			V[i] = (V[0]+i) % nCon_V;
		nt_V = *(Num_t_V + v);
		//////////////////////////////////////////////////////////// U direction:LOOP 
		p_U		= p_V; 
		pw_U	= pw_V;
		/////////////////////////////	
		for( U[0] = u = 0; u < nPatches_U; u++, U[0]+=CtlStep_U ) 
		{
			/////////////////////////////////////////////////
			bLast_U = (u == (nPatches_U-1))?TRUE:FALSE;
			bLast_V = (v == (nPatches_V-1))?TRUE:FALSE;
			/////////////////////
			nt_U	= *(Num_t_U + u);  
			/////////////////////////////
			nMaxU 	= bLast_U?(nt_U+1):nt_U; // no. of pts to be generated in U
			nMaxV 	= bLast_V?(nt_V+1):nt_V; // no. of pts to be generated in V
			nMaxUV	= nMaxU * nMaxV;
			/////////////////////////////
			for(j=1;j<=nDegree_U;j++)
				U[j] = (U[0]+j) % nCon_U;
			/////////////////////////////	
			for(j=0;j<=nDegree_V;j++)
			{
				VnCU = V[j] * nCon_U;		// if (bClosed_V & bLast_V)-> V[nDegree_V] is
											// automatically zero by Modulo, thus VnCU->0
											// thus vIx[i][nDegree_V] = U[i], i.e.,
											// Ist row of U	 
				/////////////////////
				for(i=0;i<=nDegree_U;i++)
				{
//					vIx[i][j] = (bLast_U && bClosed_U)?U[i]:VnCU + U[i];
					vIx[i][j] = VnCU + U[i];
				}	
			}
			////////////////////////////////////////////////////// fill up CONTROL Info for the patch
			for(i=0;i<=nDegree_U;i++)
			{
				for(j=0;j<=nDegree_V;j++)
				{
					pInC_44[i][j] = pCon_UV + vIx[i][j];
					pInW_44[i][j] = pWts_UV + vIx[i][j];
				}	
			}
			/////////////////////////////////////////////////// Go make a patch
			nOutP = HO_Make_A_Patch
						(	pInC_44,pInW_44,
							bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,
							bLast_V,nDegree_V,nDim_V,nt_V,Dis_t_V,
							p_U,pw_U,nEmitTot_U,nPatches_U,nPatches_V
						);
			///////////////////				
			if(nOutP != nMaxUV)
			{
				//////////////////
				delete [] pInC_44;
				delete [] pInW_44;
				//////////////////
				AfxMessageBox("CSurface4::HO_MakePatches\nnOutP != nMaxUV");
				return -1;
			}	
			else
			{	
				/////////////////
				nOut	+= nOutP;
				///////////////////// Starting Corner for the next Patch in Current column v	
				p_U		+= nt_U; 
				pw_U	+= nt_U;
				/////////////////////
			}	
		}												///////////////////////////// end LOOP_U
		////////////////////// Starting Corner for Ist Patch in next column v	
		p_V		+= nEmitTot_U * nt_V; 
		pw_V	+= nEmitTot_U * nt_V;
	}													///////////////////////////// end LOOP_V
	//////////////////
	delete [] pInC_44;
	delete [] pInW_44;
	//////////////////
	return nOut;
	////////////
}

int CSurface4::HO_Make_A_Patch
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
				,	pWORLD		pOut		// 	Total Output Points Array
				,	pDOUBLE		pOutWts		// 	Total Output Wts Array
				,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
				,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
				,	int			nPatches_V	//  Total Number of Patches in V-dir, needed for t-Dist 
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface4::HO_Make_A_Patch");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"ppCon_U4V4[%d][%d]: Actually[4][4]\n",nDegree_U+1,nDegree_V+1);
		for(m=0;m<(nDegree_U+1);m++)
		{
			for(k=0;k<(nDegree_V+1);k++)
			{
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f %7.2f %7.2f \n", m, k, 
					ppCon_U4V4[m][k]->x, ppCon_U4V4[m][k]->y, ppCon_U4V4[m][k]->z );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	pWORLD	p;
	pDOUBLE pw;
    //////////////////////
	WORLD		temC;
	pWORLD		pC_V = &temC;
	double 		temW;
	pDOUBLE		pW_V = &temW;
	int			i,j,iv,nOut = 0, nOutU,nMaxU, nMaxV, nMaxUV;
	//////////////////////////////////////////////////////////////////// LOOP
	nMaxU	= bLast_U?nt_U+1:nt_U;
	nMaxV	= bLast_V?nt_V+1:nt_V;
	nMaxUV	= nMaxU * nMaxV;
	///////////////////////////
	double 	delv	= 1.0/nt_V;
	double	t		= -delv;				
	//////////////////////////////// memory
	pWORLD pCon_U4	= new WORLD[4];
	pDOUBLE pWts_U4	= new double[4];
	PW4 ppCon_V4	= new pWORLD[4];
	PD4 ppWts_V4	= new pDOUBLE[4];
	/////////////////////////////////////////////////////////////////// V Loop
	p	= pOut;
	pw	= pOutWts;
	//////////////
	for (iv=0;iv<nMaxV;iv++)
	{
		if(nPatches_V == 1 && nDegree_V == 1) // Ratio business/ Single & Linear
			t = Dis_t_V[iv];
		else
			t += delv;
		//////////
		for(i=0;i<=nDegree_U;i++)			
		{
			///////////////////////// Create Con_U & Wts_U for a specific v
			for(j=0;j<=nDegree_V;j++)
			{
				ppCon_V4[j] = ppCon_U4V4[i][j];
//				if(nDim_V == 4)
					ppWts_V4[j] = ppWts_U4V4[i][j];
			}
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Still in CSurface4::HO_Make_A_Patch\n BEFORE\nHO_ComputeMG Call ");
		AfxMessageBox(*str);
		///////////////////
		int j,k;
	    ///////////////////
		j = sprintf(buf,"ppCon_V4[%d]: Actually[4][4]\niv = %2d\n",nDegree_V+1,iv);
		for(k=0;k<(nDegree_V+1);k++)
		{
	   		j += sprintf( buf + j, "k=%2d  %7.2f %7.2f %7.2f \n", k, 
				ppCon_V4[k]->x, ppCon_V4[k]->y, ppCon_V4[k]->z );
		} 
  		j += sprintf( buf + j, "\n");
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////// Memory :Fix
			PDMA24	pMG_1 = (PDMA24) new DMA24;	//  Basis*Geometry Matrix for Linear
			PDMA34	pMG_2 = (PDMA34) new DMA34;	//  Basis*Geometry Matrix for Quadratic
			PDMA44	pMG_3 = (PDMA44) new DMA44;	//  Basis*Geometry Matrix for Cubic
			////////////////////////////////// Make Coef * Geometry Matrix for V-dir
			HO_ComputeMG(ppCon_V4,ppWts_V4,pMG_1,pMG_2,pMG_3,nDegree_V,nDim_V);
			/////////////////////////////////////////////////////////////// Curve Pt. in V-dir
			HO_Make_A_CurvePt_V(pMG_1,pMG_2,pMG_3,nDegree_V,nDim_V,t,pC_V,pW_V);
			///////////////
			pCon_U4[i].x 	= pC_V->x;
			pCon_U4[i].y 	= pC_V->y;
			pCon_U4[i].z 	= pC_V->z;
			pWts_U4[i] 		= *pW_V;
			//////////////////////////////////////////////////////////////////////////// Memory :Free
			delete [] pMG_1;	//  Basis*Geometry Matrix for Linear
			delete [] pMG_2;	//  Basis*Geometry Matrix for Quadratic
			delete [] pMG_3;	//  Basis*Geometry Matrix for Cubic
		}
		////////////////////////////////////////////////////////////////////// Curve in U-dir
		nOutU = HO_Make_A_Curve_U(bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,pCon_U4,pWts_U4,p,pw,nPatches_U);
		/////////////////////////										
		if(nOutU != nMaxU)
		{
			//////////////////
			delete [] pCon_U4;
			delete [] pWts_U4;
			delete [] ppCon_V4;
			delete [] ppWts_V4;
			//////////////////
			AfxMessageBox("CSurface4::HO_Make_A_Patch\nnOutU != nMaxU");
			return -1;
		}											
		else
		{	
			/////////////////
			nOut	+= nOutU;
			////////////////////////////////// Starting memory for next U-Curve
			p		+= nEmitTot_U;
			pw		+= nEmitTot_U;
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
 			///////////////////////////////////////////
			sprintf(buf,"Still in CSurface4::HO_Make_A_Patch\n AFTER\nHO_Make_A_Curve_U Return ");
			AfxMessageBox(*str);
			///////////////////
			int j,k;
			///////////////////
			j = sprintf(buf,"pOut[%d]\niv = %2d\n",nOut,iv);
			for(k=0;k<(nOut);k++)
			{
				j += sprintf( buf + j, "k=%2d  %7.2f %7.2f %7.2f \n", k, 
					pOut[k].x, pOut[k].y, pOut[k].z );
			} 
  			j += sprintf( buf + j, "\n");
			AfxMessageBox(*str);
			///////////////////
			delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
		}	
	}
	//////////////////
	delete [] pCon_U4;
	delete [] pWts_U4;
	delete [] ppCon_V4;
	delete [] ppWts_V4;
	//////////////////
	if(nOut != nMaxUV)
		return -1;
	else	
		return nOut;
	////////////////
}

void CSurface4::HO_ComputeMG
			(
				PW4			ppInC		//	pointer to pointer Control Pt. array
			,	PD4			ppWts		// 	pointer to pointer Wts array	
			,	PDMA24		pMG_1		//  Basis*Geometry Matrix for Linear
			,	PDMA34		pMG_2		//  Basis*Geometry Matrix for Quadratic
			,	PDMA44		pMG_3		//  Basis*Geometry Matrix for Cubic
			,	int			nDegree		// 	Degree : ALWAYS BEZIER
			,	int			nDim		// 	3= NonRational / 4 = Rational
			)
{
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface4::HO_ComputeMG");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"ppWts[%d]\n",nDegree+1);
		for(m=0;m<(nDegree+1);m++)
		{
	   		j += sprintf( buf + j, "%2d %7.2f\n",m,
						*ppWts[m] );
		}
		AfxMessageBox(*str);
	    ///////////////////
		j = sprintf(buf,"ppInC[%d]\n",nDegree+1);
		for(m=0;m<(nDegree+1);m++)
		{
	   		j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n",m,
				ppInC[m]->x,ppInC[m]->y,ppInC[m]->z );
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	///////////////////
	pWORLD		pv;
	double		One = 1.0;
	double		Wts;
	int			i,nOrder = nDegree + 1;
	///////////////////
	if(1 == nDegree)
	{
		DMA24		G_1;		//  Geometry Matrix for Linear
		//////////////////////////////////////////////////// Geometry Matrix
		for( i=0; i<nOrder; i++ ) 
		{
//				pv 	= pInC+i;
//				Wts = *(pWts+i);
			pv 	= ppInC[i];
			Wts = *(ppWts[i]);
			//////////////////
			if(nDim == 3)	// NonRational
			{	
				SETM( G_1, i, *pv, One  );
			}
			else	
			if(nDim == 4)	// Rational
			{
				SETM( G_1, i, *pv, Wts );
			}	
		}
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface4::HO_ComputeMG");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"G_1[%d][%d]\n",nOrder,4);
		for(m=0;m<nOrder;m++)
		{
			for(k=0;k<4;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", G_1[m][k] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////	
		////////////////////////////////////////////////////// Basis
		PDMA22 pMCoef_1 = (PDMA22)CoefBezierLin;	// Linear
		////////////////////////////////////////////////////// Basis * Geometry	
		CCurve_1 Curve;
		Curve.HO_ComputeMG(pMG_1,pMCoef_1,G_1,nDim);
		//////////////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just Leaving\nCSurface4::HO_ComputeMG");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"MG_1[%d][%d]\n",nOrder,4);
		for(m=0;m<nOrder;m++)
		{
			for(k=0;k<4;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", pMG_1[m][k] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
	}
	else
	if(2 == nDegree)
	{
		DMA34		G_2;		//  Geometry Matrix for Quadratic
		//////////////////////////////////////////////////// Geometry Matrix
		for( i=0; i<nOrder; i++ ) 
		{
//				pv 	= pInC+i;
//				Wts = *(pWts+i);
			pv 	= ppInC[i];
			Wts = *(ppWts[i]);
			//////////////////
			if(nDim == 3)	// NonRational
			{	
				SETM( G_2, i, *pv, One  );
			}
			else	
			if(nDim == 4)	// Rational
			{
				SETM( G_2, i, *pv, Wts );
			}	
		}
		////////////////////////////////////////////////////// Basis
		PDMA33 pMCoef_2 = (PDMA33)CoefBezierQuad;	// Quadratic
		////////////////////////////////////////////////////// Basis * Geometry	
		CCurve_2 Curve;
		Curve.HO_ComputeMG(pMG_2,pMCoef_2,G_2,nDim);
		//////////////////////
	}
	else
	if(3 == nDegree)
	{
		DMA44		G_3;		//  Geometry Matrix for Cubic
		//////////////////////////////////////////////////// Geometry Matrix
		for( i=0; i<nOrder; i++ ) 
		{
//				pv 	= pInC+i;
//				Wts = *(pWts+i);
			pv 	= ppInC[i];
			Wts = *(ppWts[i]);
			//////////////////
			if(nDim == 3)	// NonRational
			{	
				SETM( G_3, i, *pv, One  );
			}
			else	
			if(nDim == 4)	// Rational
			{
				SETM( G_3, i, *pv, Wts );
			}	
		}
		////////////////////////////////////////////////////// Basis
		PDMA44 pMCoef_3 = (PDMA44)CoefBezierCubic;	// Cubic
		////////////////////////////////////////////////////// Basis * Geometry	
		CCurve_3 Curve;
		Curve.HO_ComputeMG(pMG_3,pMCoef_3,G_3,nDim);
		//////////////////////
	}
	////////
	return;	
}

int CSurface4::HO_Make_A_CurvePt_V
			(
				PDMA24		pMG_1		//  Basis*Geometry Matrix for Linear
			,	PDMA34		pMG_2		//  Basis*Geometry Matrix for Quadratic
			,	PDMA44		pMG_3		//  Basis*Geometry Matrix for Cubic
			,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
			,	int			nDim_V		// 	3= NonRational / 4 = Rational
			,	double		t			// 	parameter to compute Surface Pt in V-dir
			,	pWORLD		pv			// 	Output Point
			,	pDOUBLE		pw			// 	Output Wt
			)
{
	///////////////////
	CCurve_1* pCurve_1;
	CCurve_2* pCurve_2;
	CCurve_3* pCurve_3;
    ///////////////////
	int		nOut = 0;
	//////////////////////////////////////////////////// Controls at V = t
	switch(nDegree_V)
	{
		case 1:
			nOut += pCurve_1->HO_Make_A_Curve_Pt(pMG_1,nDim_V,t,pv,pw);
		    break;

		case 2:
			nOut += pCurve_2->HO_Make_A_Curve_Pt(pMG_2,nDim_V,t,pv,pw);
		    break;

		case 3:
			nOut += pCurve_3->HO_Make_A_Curve_Pt(pMG_3,nDim_V,t,pv,pw);
		    break;
	}
	////////////
	return nOut;
	////////////
}

int CSurface4::HO_Make_A_Curve_U
			(
				BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
			,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
			,	int			nDim_U		// 	3= NonRational / 4 = Rational
			,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
			,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
			,	pWORLD		pCon_U4		// 	Control Points Array
			,	pDOUBLE		pWts_U4		// 	Wts Array
			,	pWORLD		pOut		// 	Total Output Points Array
			,	pDOUBLE		pOutWts		// 	Total Output Wts Array
			,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
	)
{
	/////////////////////////////////////////////////////////////////////////////////////
	//	If Patch is Closed in any direction, it was already taken care of by modulo and
	//	manipulation of vIx[i][j] in HO_MakePatches();
	//	So, here we will fake the patch to be always NOT CLOSED for curve generation
	/////////////////////////////////////////////////////////////////////////////////////
	BOOL	bClosed_U = FALSE;	// IsClosed
	pWORLD	pConBegin_U = NULL; // Absolute Beginning of CONTROL Points Array
											// for the entire Curve
											// needed for Closed Curve
	pDOUBLE	pWtsBegin_U = NULL; // Absolute Beginning of Rational Bezier Weights
											// for the entire Curve
											// needed for Closed Curve
	///////////////////////////////////////////////////////////////////////////////////////
	int		nOut = 0, nMaxU;
	/////
	nMaxU	= bLast_U?nt_U+1:nt_U;
	////////////////////////////////////////////////////////////////////// Curve in U-dir
	if (1 == nDegree_U)
	{
		CCurve_1* pCurve;
		PDMA22 pMCoef = (PDMA22)CoefBezierLin;	// Linear
		/////////////////////////////////////////////////////////////
		nOut += pCurve->HO_Make_A_Curve(bClosed_U,pConBegin_U,pWtsBegin_U,
							bLast_U,pMCoef,pCon_U4,nDim_U,pWts_U4,nt_U,Dis_t_U,pOut,pOutWts,nPatches_U);
			/////////////////////////////////////////////////////////////
	}
	else
	if (2 == nDegree_U)
	{
		CCurve_2* pCurve;
		PDMA33 pMCoef = (PDMA33)CoefBezierQuad;	// Quadratic
		/////////////////////////////////////////////////////////////
		nOut += pCurve->HO_Make_A_Curve(bClosed_U,pConBegin_U,pWtsBegin_U,
							bLast_U,pMCoef,pCon_U4,nDim_U,pWts_U4,nt_U,Dis_t_U,pOut,pOutWts,nPatches_U);
		/////////////////////////////////////////////////////////////
	}
	else
	if (3 == nDegree_U)
	{
		CCurve_3* pCurve;
		PDMA44 pMCoef = (PDMA44)CoefBezierCubic;	// Quadratic
		/////////////////////////////////////////////////////////////
		nOut += pCurve->HO_Make_A_Curve(bClosed_U,pConBegin_U,pWtsBegin_U,
							bLast_U,pMCoef,pCon_U4,nDim_U,pWts_U4,nt_U,Dis_t_U,pOut,pOutWts,nPatches_U);
		/////////////////////////////////////////////////////////////
	}
	//////////////////
	if(nOut != nMaxU)
	{
		//////////////////
		AfxMessageBox("CSurface4::HO_Make_A_Curve_U\nnOut != nMaxU");
		return -1;
	}	
	else	
		return nOut;
	////////////////
}
//////////////////////////////////////////////////////////////////////
int	CSurface4::TensorProduct_2D
				(
					PATCHOUTPUT		O_kind		//  Output Method
				,	BOOL			bClosed_S	//  IsClosed_S
				,	int				nDegree_S	//  Degree in S-Dir
				,	int				nCon_S		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_S		//  3= NonRational / 4 = Rational
				,	int				nPatches_S	//  Total Number of Patches 
				,	pINT			Num_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_S		//  Output t distribution Pts.				
				,	BOOL			bClosed_T	//  IsClosed_T
				,	int				nDegree_T	//  Degree in T-Dir
				,	int				nCon_T		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_T		//  3= NonRational / 4 = Rational
				,	int				nPatches_T	//  Total Number of Patches 
				,	pINT			Num_t_T		//  Number of Output Segments Array in T-Dir for each patch
				,	pDOUBLE			Dis_t_T		//  Output t distribution Pts.				
				,	pWORLD			pCon_ST		//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts_ST		//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut_ST		//  Total Output Points Array
				,	pDOUBLE			pOutWts_ST	//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				)
{
    ///////////////////////////////////
	if	(
			(!nCon_S)||(nPatches_S<1)||
		   	(!nCon_T)||(nPatches_T<1)||(!pCon_ST)||(!pOut_ST)||(!pOutWts_ST)
		)			   	
		return ERROR_MISSING_ARGUMENTS;
/*		
    ////////////////////////////////////////////////////// generate
    													// FDiffxMCoeff	
    DMAT EUM,EVM;
	ComputeFDiff_x_Mcoeff( kind, bias, tension,nSegU,nSegV,EUM,EVM);
*/	
	/////////////////		ASUMMED ALWAYS BEZIER !!!			////////////////////
	int	CtlStep_S = nDegree_S;		// Control Pt. Step
	int	CtlStep_T = nDegree_T;		// Control Pt. Step
	////////////////////////////////////////////////////// CreatePatchPts
	int nPtActual;
	if (O_kind == PA_FINITEDIF)
		;	// nothing for Now
		///////////////////////////
//		nPtActual = FD_MakePatches(nCon,pCon,nDim,pWts,Num_t,pOut,nCurves); 
		///////////////////////////
	else						
	if (O_kind == PA_HORNER) 	// for now same method in S & T
	{
		///////////////////////////
		nPtActual = HO_MakePatches
					(
						bClosed_S,CtlStep_S,nDegree_S,nDim_S,nCon_S,nPatches_S,Num_t_S,Dis_t_S, 
						bClosed_T,CtlStep_T,nDegree_T,nDim_T,nCon_T,nPatches_T,Num_t_T,Dis_t_T, 
						pWts_ST,pCon_ST,pOut_ST,pOutWts_ST
					);
		///////////////////////////
	}
	////////////////////
	if(nPtActual != nOut)
	{
		//////////////////
		AfxMessageBox("CSurface4::TensorProduct_Surfaces\nnPtActual != nOut");
		return -1;
	}		
    else
		return nPtActual;
}
/////////////////////////////////////////////////////////////////// Compute at specific (s,t)
int CSurface4::HO_GetAPointOnABezSegPatch		// RATIONAL BEZIER Patches
			(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_U	//  Total Number of Patches in U-dir 
				,	int			nCurBz_S	//	Output s distribution Pts.				
				,	double		sCur		//	Output s distribution Pts.				
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_V	//  Total Number of Patches in U-dir 
				,	int			nCurBz_T	//	Output s distribution Pts.				
				,	double		tCur		//	Output t distribution Pts.				
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Points Array
				,	pDOUBLE		pOutWt_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
			)
{
	int nResult = MA_OK;
//////////////////////////////////////////////////////////////////
	int		i,j,u, v, VnCU;
	int		U[4], V[4], vIx[4][4];	// vertex indices
	////////////////////////////////////// memory for array of pointers
	PW44 pInC_44 = new pWORLD[4][4];	//	Control Pt. array for the patch: RESERVED for Maximum Cubic
	PD44 pInW_44 = new pDOUBLE[4][4]; 
	//////////////////////////////////////////////////////////////////////////// V direction:LOOP
	for( V[0] = v = 0; v < nPatches_V; v++, V[0]+=nDegree_V ) 
	{
		if(v != nCurBz_T)
			continue;
		/////////////////////////////
		for(i=1;i<=nDegree_V;i++)
			V[i] = (V[0]+i) % nCon_V;
		//////////////////////////////////////////////////////////// U direction:LOOP 
		for( U[0] = u = 0; u < nPatches_U; u++, U[0]+=nDegree_U ) 
		{
			if(u != nCurBz_S)
				continue;
			/////////////////////////////
			for(j=1;j<=nDegree_U;j++)
				U[j] = (U[0]+j) % nCon_U;
			/////////////////////////////	
			for(j=0;j<=nDegree_V;j++)
			{
				VnCU = V[j] * nCon_U;		// if (bClosed_V & bLast_V)-> V[nDegree_V] is
											// automatically zero by Modulo, thus VnCU->0
											// thus vIx[i][nDegree_V] = U[i], i.e.,
											// Ist row of U	 
				/////////////////////
				for(i=0;i<=nDegree_U;i++)
				{
//					vIx[i][j] = (bLast_U && bClosed_U)?U[i]:VnCU + U[i];
					vIx[i][j] = VnCU + U[i];
				}	
			}
			////////////////////////////////////////////////////// fill up CONTROL Info for the patch
			for(i=0;i<=nDegree_U;i++)
			{
				for(j=0;j<=nDegree_V;j++)
				{
					pInC_44[i][j] = pCon_UV + vIx[i][j];
					pInW_44[i][j] = pWts_UV + vIx[i][j];
				}	
			}
			/////////////////////////////////////////////////// Go make a patch
			nResult = HO_GenerateAPointOnASingleBezPatch
						(	pInC_44,pInW_44,
							nDegree_U,nDim_U,sCur,
							nDegree_V,nDim_V,tCur,pOut_UV,pOutWt_UV
						);
		}												///////////////////////////// end LOOP_U
		////////////////////// Starting Corner for Ist Patch in next column v	
	}													///////////////////////////// end LOOP_V
	//////////////////
	delete [] pInC_44;
	delete [] pInW_44;
	//////////////////
	return nResult;
	////////////
}

int CSurface4::HO_GenerateAPointOnASingleBezPatch
			(
					PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
				,	PD44		ppWts_U4V4	//	pointer to pointer Wts. array for the patch	
				,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		// 	3= NonRational / 4 = Rational
				,	double		u			//	Output u Pt.				
				,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		// 	3= NonRational / 4 = Rational
				,	double		v			//	Output v Pt.				
				,	pWORLD		pOut		// 	Total Output Points Array
				,	pDOUBLE		pOutWts		// 	Total Output Wts Array
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface4::HO_Make_A_Patch");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"ppCon_U4V4[%d][%d]: Actually[4][4]\n",nDegree_U+1,nDegree_V+1);
		for(m=0;m<(nDegree_U+1);m++)
		{
			for(k=0;k<(nDegree_V+1);k++)
			{
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f %7.2f %7.2f \n", m, k, 
					ppCon_U4V4[m][k]->x, ppCon_U4V4[m][k]->y, ppCon_U4V4[m][k]->z );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	WORLD		temC;
	pWORLD		pC_V = &temC;
	double 		temW;
	pDOUBLE		pW_V = &temW;
	int			i,j;
	//////////////////////////////// memory
	PW4 ppCon_U4	= new pWORLD[4];
	PD4 ppWts_U4	= new pDOUBLE[4];
	PW4 ppCon_V4	= new pWORLD[4];
	PD4 ppWts_V4	= new pDOUBLE[4];
	//////////////////////////////////////////////////////////////////////////// Memory :Fix
	PDMA24	pMG_1 = (PDMA24) new DMA24;	//  Basis*Geometry Matrix for Linear
	PDMA34	pMG_2 = (PDMA34) new DMA34;	//  Basis*Geometry Matrix for Quadratic
	PDMA44	pMG_3 = (PDMA44) new DMA44;	//  Basis*Geometry Matrix for Cubic
	//////////
	for(i=0;i<=nDegree_U;i++)			
	{
		///////////////////////// Create Con_U & Wts_U for a specific v
		for(j=0;j<=nDegree_V;j++)
		{
			ppCon_V4[j] = ppCon_U4V4[i][j];
//				if(nDim_V == 4)
			ppWts_V4[j] = ppWts_U4V4[i][j];
		}
		////////////////////////////////// Make Coef * Geometry Matrix for V-dir
		HO_ComputeMG(ppCon_V4,ppWts_V4,pMG_1,pMG_2,pMG_3,nDegree_V,nDim_V);
		/////////////////////////////////////////////////////////////// Curve Pt. in V-dir
		HO_Make_A_CurvePt_V(pMG_1,pMG_2,pMG_3,nDegree_V,nDim_V,v,pC_V,pW_V);
		///////////////
		ppCon_U4[i] 	= pC_V;
		ppWts_U4[i] 	= pW_V;
	}
	////////////////////////////////// Make Coef * Geometry Matrix for U-dir
	HO_ComputeMG(ppCon_U4,ppWts_U4,pMG_1,pMG_2,pMG_3,nDegree_U,nDim_U);
	/////////////////////////////////////////////////////////////// Curve Pt. in U-dir
	HO_Make_A_CurvePt_V(pMG_1,pMG_2,pMG_3,nDegree_U,nDim_U,u,pOut,pOutWts);
	//////////////////////////////////////////////////////////////////////////// Memory :Free
	delete [] pMG_1;	//  Basis*Geometry Matrix for Linear
	delete [] pMG_2;	//  Basis*Geometry Matrix for Quadratic
	delete [] pMG_3;	//  Basis*Geometry Matrix for Cubic
	//////////////////
	delete [] ppCon_U4;
	delete [] ppWts_U4;
	delete [] ppCon_V4;
	delete [] ppWts_V4;
	////////////////
	return MA_OK;
}
/////////////////////////////////// end of module /////////////////
/*
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface4::HO_MakePatches");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"pMCoef_1[%d][%d]\n",2,2);
		for(m=0;m<2;m++)
		{
			for(k=0;k<2;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", pMCoef_1[m][k] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
*/



