// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
#include <math.h>

#include "3Dmath.h"
/////////////////////
#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_CuPS.h"
///////////////////
#include "Curve_3.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CCurve_3
#define	ORDER	4		// Cubic
////////////////////////////////////
IMPLEMENT_DYNAMIC(CCurve_3,CCurve)
/*
BEGIN_MESSAGE_MAP(CCurve_3,CCurve)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCurve_3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
#define KNOT_OFFSET	3			// Spline(NonUniform)
/////////////////////
enum { X,Y,Z,W };

static DMA44
	CoefBezier = {	{ -1,	 3,	-3,	1 },
					{  3,	-6,	 3,	0 },
					{ -3,	 3,	 0,	0 },
					{  1,	 0,	 0,	0 }	}
					
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


#define	HO_CUBIC(u,v,w)			( ( (u)[(v)+0]*(w) + (u)[(v)+4] )*(w) + (u)[(v)+8] )*(w) + (u)[(v)+12]
#define	SETM(m,n,o,w)			(m)[(n)][X] = (o).x * (w);\
								(m)[(n)][Y] = (o).y * (w);\
								(m)[(n)][Z] = (o).z * (w);\
								(m)[(n)][W] = (w)
//////////////////// 
CCurve_3::CCurve_3()
{
    
#ifdef _DEBUG
	/////////////////////////////////////////////// Dump MessageBox
	for(int i=0;i<30;i++)
		m_bMessage[i] = FALSE;
#endif

} 
/////////////////////////////////////////////////////////////////////
PDMA44 CCurve_3::SetBasis(enum CURVEPROC kind,double bias,double tension,double alfa)
{
	C3DMath		Math3D;
	///////////////////
	DMA44	BasisBeta = {
		{ -2,  2, -2,  2 },
		{  6, -3,  3,  0 },
		{ -6,  6,  6,  0 },
		{  2,  1,  2,  0 }
	};
	PDMA44	C;
	double	r,bias2,bias3;
	int		i,j;

	switch( kind ) {
		case CP_BSPLINE:		return (PDMA44)CoefBSpline;
		case CP_CATMULLROM:		return (PDMA44)CoefCatmullRom;
		case CP_BEZIER:			return (PDMA44)CoefBezier;
		case CP_HERMITE:		return (PDMA44)CoefHermite;
		case CP_BETA:
			C = (PDMA44)CoefBeta;
			Math3D.BlockCopy( (HUGEBLK)BasisBeta, (HUGEBLK)C, sizeof(double)*16 );
			bias2 = bias*bias;
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
			for( i=0;i<4;i++ )
				for( j=0;j<4;j++ )
					C[i][j]*=r;
			return C;
		case CP_CARDISPLINE:
			C = (PDMA44)CoefAlfa;
			C[2][1] = C[2][3] = C[3][0] = C[3][2] = C[3][3] = 0;
			C[0][0] = - alfa;
			C[0][1] = 2 - alfa;
			C[0][2] = alfa - 2;
			C[0][3] = alfa;
			C[1][0] = 2 * alfa;
			C[1][1] = alfa - 3;
			C[1][2] = 3 - (2 * alfa);
			C[1][3] = alfa;
			C[2][0] = - alfa;
			C[2][2] = alfa;
			C[3][1] = 1;

			return C;
	}
	return C;
}
//////////////////////////////////////////////////////////////////	Horner/Cubic(HC)
void CCurve_3::GetBlending_NUSpline(int i, double t, pDOUBLE knot, pDOUBLE blend)
{

	/////////////////////////////////////////////////////
	// WILL BE NEEDED FOR, say, FEMs involving QUINTIC B-SPLINES
	/////////////////////////////////////////////////////
	double dt21,dt31,dt41,dt31_1,dt32_1,dt41_1,dt41_2;
	double tti,tti_1,tti_2,tti1,tti2,tti3;
	double b02,b12,b03,b13,b23; 
	///////////////////////////
	dt21 	= knot[i+1] - knot[i];
	if(dt21 == 0.)
		return;	
    ///////////////////////////////////////////////////// constants
	dt31 	= knot[i+2] - knot[i];	
	dt41 	= knot[i+3] - knot[i];	
	dt31_1 	= knot[i+1] - knot[i-1];	
	dt32_1 	= knot[i+2] - knot[i];	
	dt41_1 	= knot[i+2] - knot[i-1];	
	dt41_2 	= knot[i+1] - knot[i-2];
	/////////////////////////////////
	tti		= t - knot[i];
	tti_1	= t - knot[i-1];
	tti_2	= t - knot[i-2];
	tti1	= knot[i+1] - t;
	tti2	= knot[i+2] - t;
	tti3	= knot[i+3] - t;
    ///////////////////////////////////////////////////// 2nd Order
    b02		= tti/dt21;
    b12		= tti1/dt21;
    ///////////////////////////////////////////////////// 3rd Order 
    if(dt31 == 0)
    	b03 = 0;
    else 
	    b03	= (tti/dt31) * b02;
	//////////////////////////////	    
    if(dt31_1 == 0 && dt32_1 == 0)
    	b13 = 0;
    else	
    if(dt31_1 == 0)
    	b13	= (tti2/dt32_1) * b02;
    else	
    if(dt32_1 == 0)
    	b13	= (tti_1/dt31_1) * b12;
	else    
    	b13	= (tti_1/dt31_1) * b12 + (tti2/dt32_1) * b02;
    ///////////////	
    if(dt31_1 == 0)
    	b23	= 0;
    else	
    	b23		= (tti1/dt31_1) * b12;
    ///////////////////////////////////////////////////// deliver
    if(dt41 == 0)
    	blend[0]= 0;
    else	
	    blend[0]= (tti/dt41) * b03; 
	//////////////////////////////	    
    if(dt41_1 == 0 && dt41 == 0)
    	blend[1] = 0;
    else	
    if(dt41_1 == 0)
    	blend[1]= (tti3/dt41) * b03;
    else	
    if(dt41 == 0)
    	blend[1]= (tti_1/dt41_1) * b13;
	else    
    	blend[1]= (tti_1/dt41_1) * b13 + (tti3/dt41) * b03;
    ///////////////	
    if(dt41_2 == 0 && dt41_1 == 0)
    	blend[2] = 0;
    else	
    if(dt41_2 == 0)
    	blend[2]= (tti2/dt41_1) * b13;
    else	
    if(dt41_1 == 0)
    	blend[2]= (tti_2/dt41_2) * b23;
	else    
    	blend[2]= (tti_2/dt41_2) * b23 + (tti2/dt41_1) * b13;
    ///////////////	
    if(dt41_2 == 0)
    	blend[3]= 0;
    else	
    	blend[3]= (tti1/dt41_2) * b23;
    ///////////////////////////////
    return;

} 
//////////////////////////////////////////////////////////////////	Horner/Cubic(HC)
int CCurve_3::HO_GetAPointOnABezSegCurve 		// 
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
		)
{
	////////////////////////////////////////////////////////////////////////
	int	n,nOut=0,Ix[2];
	int nDegree = ORDER-1; 
	/////////////////////////////////////
	for( Ix[0] = n = 0; n < nCurves; n++, Ix[0] += nDegree )
	{
		if(n != nCurBz_S)
			continue;
		//////////////////////////////////////////////////// Geometry Matrix
		Ix[1] = (Ix[0]+1) % nC;	// modulo takes care of last curve
		Ix[2] = (Ix[0]+2) % nC;
		Ix[3] = (Ix[0]+3) % nC;
		/////////////////////////////////////////////////////////////
		nOut += HO_GenerateAPointOnASingleBezCurve
					(pInC+Ix[0],nDim,pWts+Ix[0],sCur,pOut,pOutWt);
		/////////////////////////////////////////////////////////////
	}
	return MA_OK;
} 

int CCurve_3::HO_GenerateAPointOnASingleBezCurve 		// 
		(
			pWORLD			pInC            // ORDER Number CONTROL Points Array
												// for the Current Curve Segment
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	double			sCur	// Current param of Outpt for the curve
		,	pWORLD			pOut            // Total Output Points Array
		,	pDOUBLE			pOutWt			// Total Output Wts Array
		)
{
	////////////////////////////////////////////////////////////////////////
	int			i,nOut=0;
	DMA44		G,MG;
	PDMA44		pMG = (PDMA44)MG;
	double		One;
	double		Wts;
	pWORLD		pv;
	/////////////////
	One = 1.;
	//////////////////////////////////////////////////// Geometry Matrix
	for( i=0; i<ORDER; i++ ) 
	{
		pv	= (pInC+i);
		Wts = *(pWts+i);
		if(nDim == 3)	// NonRational
		{	
			SETM( G, i, *pv, One  );
		}
		else	
		if(nDim == 4)	// Rational
		{
			SETM( G, i, *pv, Wts );
		}	
	}
	////////////////////////////////////////////////////// Cubic Segment	
	PDMA44 pMCoef = (PDMA44)CoefBezier;	// Linear
	HO_ComputeMG(pMG, pMCoef, G, nDim);
	///////////////////////////////////
	double t	= sCur;
	////////////////////////////////////////////////////
	nOut += HO_Make_A_Curve_Pt(pMG,nDim,t,pOut,pOutWt);
	////////////////////////////////////////////////////
	return nOut;
} 

int CCurve_3::HO_MakeCurves 		// 
// Return Actual Number of Points Generated
		(
			BOOL			bClosed			// IsClosed
		,	PDMA44			pMCoef			// Basis Matrix
		,	int				CtlStep         // Control Pt. Step
		,	int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	pINT			Num_t			// Number of Outpts for each curve
		,	pDOUBLE			Dis_t			// Output Pts.				
		,	pWORLD			pOut            // Total Output Points Array
		,	pDOUBLE			pOutWts			// Total Output Wts Array
		,	int				nCurves			// Total Number of Cubic Curves 
		)
{
	////////////////////////////////////////////////////////////////////////
	int			n,nOut=0,Ix[4];
	pWORLD		p;
	pDOUBLE 	pw;
	////////////////////////////////////////
	if( pOut ) 
	{
		p	= pOut;
		pw	= pOutWts;
		/////////////////////////////////////
		for( Ix[0] = n = 0; n < nCurves; n++, Ix[0] += CtlStep )
		{
			Ix[1] = (Ix[0]+1) % nC;
			Ix[2] = (Ix[0]+2) % nC;
			Ix[3] = (Ix[0]+3) % nC;
			/////////////////////////////////////////////////////////////
			nOut += HO_Make_A_Curve(bClosed,pInC,pWts,(n==nCurves-1),pMCoef,pInC+Ix[0],
											nDim,pWts+Ix[0],Num_t[n],Dis_t,p,pw,nCurves);
			/////////////////////////////////////////////////////////////
			p 	+= Num_t[n];
			pw 	+= Num_t[n];

		}
	}
	return nOut;
} 

int CCurve_3::HO_Make_A_Curve 		// 
		(
			BOOL			bClosed			// IsClosed
		,	pWORLD			pInC_Begin      // Absolute Beginning of CONTROL Points Array
												// for the entire Curve
												// needed for Closed Curve
		,	pDOUBLE			pWts_Begin      // Absolute Beginning of Rational Bezier Weights
												// for the entire Curve
												// needed for Closed Curve
		,	BOOL			bLast			// Last Curve
		,	PDMA44			pMCoef			// Basis Matrix
		,	pWORLD			pInC            // ORDER Number CONTROL Points Array
												// for the Current Curve Segment
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	int				nt				// Number of Outpts for the curve
		,	pDOUBLE			Dis_t			// Output Pts.				
		,	pWORLD			pOut            // Total Output Points Array
		,	pDOUBLE			pOutWts			// Total Output Wts Array
		,	int				nCurves			// Total No. of Curves needed for alternate
												// t-distribution
		)
			// Return Actual Number of Points Generated
{
	////////////////////////////////////////////////////////////////////////
	int			i,nOut=0;
	DMA44		G,MG;
	PDMA44		pMG = (PDMA44)MG;
	pWORLD		p,pv;
	double		One;
	double		Wts;
	pDOUBLE 	pw;
	/////////////////
	if( pOut ) 
	{
		p 	= pOut;
		pw 	= pOutWts;
		One = 1.;
		//////////////////////////////////////////////////// Geometry Matrix
		for( i=0; i<ORDER; i++ ) 
		{
//			pv 	= pInC+i;
//			Wts = *(pWts+i);
			pv	= (bClosed && bLast && (i == ORDER-1))?pInC_Begin:(pInC+i);
			Wts = (bClosed && bLast && (i == ORDER-1))?*pWts_Begin:*(pWts+i);
			if(nDim == 3)	// NonRational
			{	
				SETM( G, i, *pv, One  );
			}
			else	
			if(nDim == 4)	// Rational
			{
				SETM( G, i, *pv, Wts );
			}	
		}
		////////////////////////////////////////////////////// Cubic Segment	
		HO_ComputeMG(pMG, pMCoef, G, nDim);
		///////////////////////////////////
		double delt = 1./nt;
		double t	= -delt;
		if(bLast) 	// Last Curve
			nt++;
		/////////////////	
		for(i=0;i<nt;i++)
		{
			if(nCurves == 1)	// single segment
				t = Dis_t[i];
			else
				t += delt;
			////////////////////////////////////////////////////
			nOut += HO_Make_A_Curve_Pt(pMG,nDim,t,p,pw);
			////////////////////////////////////////////////////
			p++;
			pw++;
		}	
		///////////
	}
	return nOut;
} 

int CCurve_3::HO_Make_A_Curve_Pt 		// 
		(
			PDMA44			pMG				// Basis*Geometry Matrix
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	double			t				// t Value for the curve
		,	pWORLD			pOut            // Output Point
		,	pDOUBLE			pOutWts			// Output Wts Point
		)
			// Return Actual Number of Points Generated
{
	////////////////////////////////////////////////////////////////////////
	int			nOut=0;
	pDOUBLE		a=(pDOUBLE)pMG;
	/////////////////
	if( pOut ) 
	{
		//////////////////////////////
		if(nDim == 3)	// NonRational
		{	
			*pOutWts = 1.0; 
			EMIT_POINT( HO_CUBIC(a,0,t), HO_CUBIC(a,1,t), HO_CUBIC(a,2,t), *pOut );
		}
		else
		if(nDim == 4)	// Rational
		{
			*pOutWts = HO_CUBIC(a,3,t); 
			EMIT_POINT_RAT(HO_CUBIC(a,0,t), HO_CUBIC(a,1,t), HO_CUBIC(a,2,t),
															*pOutWts, *pOut );
		}
		///////
		nOut++;
		///////////
	}
	return nOut;
} 

void CCurve_3::HO_ComputeMG(PDMA44 MG,PDMA44 M,PDMA44 G,int nDim)
{
	int		i,j,k;
	double	t;

	// multiply C (coefficients) by G (geometry), CG = CùG
	for(i=0; i<ORDER; i++)
		for(j=0; j<nDim; j++) {
			t = 0;
			for(k=0; k<ORDER; k++)
				t += M[i][k]*G[k][j];
			MG[i][j] = t;
		}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just Leaving\nCCurve_3::HO_ComputeMG");
		AfxMessageBox(*str);
		///////////////////
		int m;
	    ///////////////////
		j = sprintf(buf,"MG[%d][%d]\n",ORDER,nDim);
		for(m=0;m<ORDER;m++)
		{
			for(k=0;k<nDim;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", MG[m][k] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
}
//////////////////////////////////////////////////////////////////	FORWARD DIFFERENCE(FD)
PDMA44 CCurve_3::FD_ForwardDifference(int nSegs)
{
	if(nSegs<1) return (PDMA44)NULL;
	///////////////////////////////////
	// Forward Difference Matrix: Foley p 535
	static	DMA44 E;
	/////////////////////////
	double delta = 1.0/nSegs;
	/////////////////////////
	E[0][0]=E[0][1]=E[0][2]=E[1][3]=E[2][2]=E[2][3]=E[3][1]=E[3][2]=E[3][3] = 0;
	E[0][3]=1.0;
	E[1][2]=delta;
	E[1][1]=delta * delta;
	E[1][0]=E[1][1] * delta;
	E[2][0]=E[3][0] = E[1][0] * 6.0;
	E[2][1]=E[1][1] * 2.0;
	//////////////////////////////////////////
	return (PDMA44)E; 
}	

void CCurve_3::FD_ComputeEA(PDMA44 EA, PDMA44 EM, PDMA44 G)
{
	int		i,j,k;
	double	t;

	// multiply EM (FDxMCcoef) by G (geometry), EA 
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++) 
		{
			t = 0;
			for(k=0; k<4; k++)
				t += EM[i][k]*G[k][j];
			EA[i][j] = t;
		}
	}		
}

int CCurve_3::FD_GeneratePoints_Unif(PDMA44 EA,int nSegs,pWORLD P,BOOL bEndPt)
{
	// Output Points generated for each Cubic:
	// Forward Difference Method: Foley p 535
	int i,j,nOut=0;
	////////////////////////////////////////////////////////// Compute Points(x,y,z)
	for (i=0; i<nSegs;i++)
	{
		nOut++;          // increment points created
		P->x = EA[0][0];	
		P->y = EA[0][1];	
		P->z = EA[0][2]; 
		/////////////////// iterate   col1 = x; col2 = y; col3 = z; 4th column not needed
		for (j = 0;j<3;j++)
		{
			EA[0][j] = EA[0][j] + EA[1][j];	//Row1=Row1+Row2 
			EA[1][j] = EA[1][j] + EA[2][j];	//Row2=Row2+Row3 
			EA[2][j] = EA[2][j] + EA[3][j];	//Row3=Row3+Row4 
		}
		P++;
	}
	//////////////////////////// end Pt
	if(bEndPt)
	{
		nOut++;          // increment points created
		P->x = EA[0][0];	
		P->y = EA[0][1];	
		P->z = EA[0][2];
	}	
	////////////////////
	return nOut;	
}
	
PDMA44 CCurve_3::FD_ComputeFDiff_x_Mcoeff
		(
			enum CURVEPROC	kind
		,	double			alfa			// alfa (Modified Catmull-Rom)
		,	double			bias			// beta
		,	double			tension			// beta and hermite
		,	int				nSeg			// number of Intervals per cubic curve
		)
{
	C3DMath		Math3D;
	///////////////////
	static DMA44		EM;
	DMA44		MCoeff,FDiff;
	PDMA44		pMCoeff = (PDMA44)MCoeff, pFDiff = (PDMA44)FDiff,B,FD;
	//////////////////////////////////////////////////// Coeff Matrix
	B = SetBasis( kind, bias, tension, alfa );
	Math3D.BlockCopy( (HUGEBLK)B, (HUGEBLK)pMCoeff, sizeof(double)*16 );
	//////////////////////////////////////////////////// ForwardDifference Matrix
	FD = FD_ForwardDifference(nSeg);
	Math3D.BlockCopy( (HUGEBLK)FD, (HUGEBLK)pFDiff, sizeof(double)*16 );
	//////////////////////////////////////////////////// Compute FDiffxMCoeff 
	FD_ComputeEA(EM,FDiff,MCoeff);  // used to multply matrices
	////////////////////////////////////////////////////
	return (PDMA44)EM;
}	

int CCurve_3::FD_MakeCurves
// Return Actual Number of Points Generated
		(
			int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	pINT			Num_t			// Number of Outpts for each curve
		,	pWORLD			pOut            // Total Output Points Array
		,	int				nCurves			// Total Number of Cubic Curves 

		)
{
	C3DMath		Math3D;
	///////////////////
	int			i,n,dIx,nOut=0,Ix[4];
	DMA44		EA,G;
	BOOL		bEndPt;
	pWORLD		p,pv;
	double		One;
	double		Wts;
	////////////////////////////////////////////////////// temporarily
	int nSegUniform = 10; //Useful only for ONE CURVE .i.e.,
	//	The way it is right now is USELESS
	//  WE NEED ADAPTIVE FINITE DIFFERENCE 			todo
    ////////////////////////////////////////////////////// generate
    DMA44 EM;
    PDMA44 pEM = (PDMA44)EM,pTemp;
	pTemp = FD_ComputeFDiff_x_Mcoeff( CP_BEZIER, 0.0, 0.0, 0.0,nSegUniform);
	Math3D.BlockCopy( (HUGEBLK)pTemp, (HUGEBLK)pEM, sizeof(double)*16 );
	//////////////////////
	if( pOut ) 
	{
		p = pOut;
		One = 1.;
		//////////////////////////////////////////////////// Control pt step
		dIx = CtlPtStep( CP_BEZIER, ORDER-1 );
		/////////////////////////////////////
		for( Ix[0] = n = 0; n < nCurves; n++, Ix[0] += dIx )
		{
			//////////////////////////////////////////////////// Geometry Matrix
			Ix[1] = (Ix[0]+1) % nC;
			Ix[2] = (Ix[0]+2) % nC;
			////////////////////////
			for( i=0; i<ORDER; i++ ) 
			{
				pv 	= pInC+Ix[i];
				Wts = *(pWts+Ix[i]);
				if(nDim == 3)	// NonRational
				{	
					SETM( G, i, *pv, One  );
				}
				else	
				if(nDim == 4)	// Rational
				{
					SETM( G, i, *pv, Wts );
				}	
			} 
			////////////////////////////////////////////////////// Cubic Curve	
			FD_ComputeEA(EA,EM,G);
			//////////////////
			bEndPt = FALSE;
			if(n == nCurves-1) bEndPt = TRUE;
			//////////////////////////////
			nOut += FD_GeneratePoints_Unif(EA,nSegUniform,p,bEndPt);
			//////////////////////////////
			p += nSegUniform;
			
		}
		/////////////////
	}
	return nOut;
} 

//////////////////////////////////////////////////////////////////////
int	CCurve_3::GenerateCurve
	(

		CURVEOUTPUT		O_kind			// Output Method
	,	BOOL			bClosed			// IsClosed
	,	int				nCon			// number of CONTROL points: ALWAYS BEZIER
	,	pWORLD			pCon            // Total CONTROL Points Array
	,	int				nDim			// 3= NonRational / 4 = Rational
	,	pDOUBLE			pWts			// Rational Bezier Weights		
	,	pINT			Num_t			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	,	pDOUBLE			Dis_t			// Output Pts.				
	,	pWORLD			pOut            // Total Output Points Array
	,	pDOUBLE			pOutWts			// Total Output Wts Array
	,	int				nCurves			// Total Number of Curve Segments 
	,	int				nOut			// expected number of generated curve vertices
	)
{
    ///////////////////////////////////
	if((!nCon)||(!pCon)||(!pOut)||(nCurves<1))
		/*	Lets be reasonable, ok folks? We MUST have these items.
		 */
		return ERROR_MISSING_ARGUMENTS;
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1  ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"nCCurve_3::GenerateCurve");
		AfxMessageBox(*str);
		///////////////////
		int j,k,L;
		L = nCurves; 
		j = sprintf(buf,"Num_t[%d]\n",L);
		for(k=0;k<L;k++)
		{
		   j += sprintf( buf + j, "%d \n",Num_t[k] );
		}
		AfxMessageBox(*str);
    	///////////////////
	    delete str;
	}	    
#endif
	////////////////////////////////////////////////////// ControlSteps & Basis
	PDMA44 pMCoef 	= SetBasis( CP_BEZIER, 0.0, 0.0, 0.0 );	// Basis Matrix
	int	CtlStep		= CtlPtStep( CP_BEZIER, ORDER-1 );		// Control Pt. Step
	////////////////////////////////////////////////////// CreateCurvePts
	int nPtActual;
	if (O_kind == CO_FINITEDIF)
		///////////////////////////
		nPtActual = FD_MakeCurves(nCon,pCon,nDim,pWts,Num_t,pOut,nCurves); 
		///////////////////////////
	else						
	if (O_kind == CO_HORNER)
	{
		///////////////////////////
		nPtActual = HO_MakeCurves(bClosed,pMCoef,CtlStep,nCon,pCon,nDim,pWts,
											Num_t,Dis_t,pOut,pOutWts,nCurves); 
	///////////////////////////
	}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1  ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
    	///////////////////////////////////////////
		sprintf(buf,"pOut-FIRST TIME\n:Output\nCCurve_3::GenerateCurve");
		AfxMessageBox(*str);
		///////////////////
		int j,k,L;
		L = nOut; 
		j = sprintf(buf,"pOut[%d]\n     X        Y        Z\n",L);
		for(k=0;k<L;k++)
		{
	   		j += sprintf( buf + j, "%7.1f %7.1f %7.1f\n", 
	   				pOut[k].x,pOut[k].y,pOut[k].z );
		}
		AfxMessageBox(*str);
	    ///////////////////
	    delete str;
	}	    
#endif
	//////////////////////////////////////
	if(nPtActual != nOut)
		return -1;	
   	else
		return nPtActual;
} 

int CCurve_3::MakeTangents 		// 
// Return Actual Number of Tangents Generated
		(
			BOOL			bClosed			// IsClosed
		,	int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	pINT			Num_t			// Number of Outpts for each curve
		,	pDOUBLE			Dis_t			// Output Pts.				
		,	pWORLD			pOut            // Total Output TANGENTs Array
		,	int				nCurves			// Total Number of Cubic Curves 
		)
{
	////////////////////////////////////////////////////////////////////////
	int			i,n,dIx,nOut=0,Ix;
	pWORLD		p;
	WORLD		tangent;
	////////////////////////////////////////
	if( pOut ) 
	{
		p = pOut;
		//////////////////////////////////////////////////// Control pt step
		dIx = CtlPtStep( CP_BEZIER, ORDER-1 );
		/////////////////////////////////////
		for( Ix = n = 0; n < nCurves; n++, Ix += dIx )
		{
			//////////////////////////////
			int nt 		= Num_t[n];
			double delt = 1./nt;
			double t=-delt;
			if(n == (nCurves-1) && !bClosed ) 	// Last Curve and not Closed
				nt++;
			/////////////////	
			for(i=0;i<nt;i++)
			{
				t += delt;
				/////////////////////////
				if(nDim == 3)	// NonRational
					Tangent_t(pInC+Ix, t, ORDER-1,tangent);//010997 
				else	
				if(nDim == 4)	// Rational
					Rat_Tangent_t(pInC+Ix, pWts, t, ORDER-1,tangent);//010997 
				//////////////////////////
				EMIT_TANGENT(&tangent,*p);
				/////////
				nOut++;
				p++;
			}	
			///////////
		}
	}
	return nOut;
} 

int CCurve_3::MakeCurvatures 		// 
// Return Actual Number of Tangents Generated
		(
			BOOL			bClosed			// IsClosed
		,	int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	pINT			Num_t			// Number of Outpts for each curve
		,	pDOUBLE			Dis_t			// Output Pts.				
		,	pDOUBLE			pOut            // Total Output CURVATUREs Array
		,	int				nCurves			// Total Number of Cubic Curves 
		)
{
	////////////////////////////////////////////////////////////////////////
	int			i,n,dIx,nOut=0,Ix;
	pDOUBLE		p;
	////////////////////////////////////////
	if( pOut ) 
	{
		p = pOut;
		//////////////////////////////////////////////////// Control pt step
		dIx = CtlPtStep( CP_BEZIER, ORDER-1 );
		/////////////////////////////////////
		for( Ix = n = 0; n < nCurves; n++, Ix += dIx )
		{
			//////////////////////////////
			int nt 		= Num_t[n];
			double delt = 1./nt;
			double t=-delt;
			if(n == (nCurves-1) && !bClosed ) 	// Last Curve and not Closed
				nt++;
			/////////////////	
			for(i=0;i<nt;i++)
			{
				t += delt;
				/////////////////////////
				if(nDim == 3)	// NonRational
					*p = Curvature_t(pInC+Ix, t, ORDER-1);//010997 
				else	
				if(nDim == 4)	// Rational
					*p = Rat_Curvature_t(pInC+Ix, pWts, t, ORDER-1);//010997
				/////////
				nOut++;
				p++;
			}	
			///////////
		}
	}
	return nOut;
} 
////////////////////////////////// end of module ///////////////////// 
/*
int CCurve_3::HO_Generate_OnePtOnBezSeg 		// 
		(
			CList<PDMA44,PDMA44>& MGList
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	double			t				// t Value for the curve
		,	int				indexCurSeg		// Current segment index
		,	pWORLD			pOut            // Output Point
		,	pDOUBLE			pOutWts			// Output Wts Point
		
		)
{

	POSITION pos;
	pos = MGList.FindIndex(indexCurSeg);
	////////////////////////////////////////////////////////////////////////
	PDMA44 pMG = (PDMA44)MGList.GetAt(pos);			// Basis*Geometry Matrix
	////////////////////////////////////////////////////// Segment	
	HO_Make_A_Curve_Pt(pMG,nDim,t,pOut,pOutWts);
	///////////////////////////////////
	return MA_OK;
} 

int CCurve_3::Generate_N_Save_MGs_ForAllBezSegs 		// 
// Return Actual Number of Points Generated
		(
			BOOL			bClosed			// IsClosed
		,	PDMA44			pMCoef			// Basis Matrix
		,	int				CtlStep         // Control Pt. Step
		,	int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	int				nCurves			// Total Number of Linear Curves 
		,	CList<PDMA44,PDMA44>& MGList
		)
{
	////////////////////////////////////////////////////////////////////////
	int			n,nOut=0,Ix[2];
	/////////////////////////////////////
	for( Ix[0] = n = 0; n < nCurves; n++, Ix[0] += CtlStep )
	{
		//////////////////////////////////////////////////// Geometry Matrix
		Ix[1] = (Ix[0]+1) % nC;
		/////////////////////////////////////////////////////////////
		PDMA44 pMG = new DMA44;
		///////////////////////
		Generate_MG_forABezSeg(bClosed,pInC,pWts,(n==nCurves-1),pMCoef,pInC+Ix[0],
										nDim,pWts+Ix[0],pMG);
		///////////////////////////////////////////////////////////// save in the List
		MGList.AddTail(pMG);
		//////////////////////
	}

	return MA_OK;
} 

int CCurve_3::Generate_MG_forABezSeg 		// 
		(
			BOOL			bClosed			// IsClosed
		,	pWORLD			pInC_Begin      // Absolute Beginning of CONTROL Points Array
												// for the entire Curve
												// needed for Closed Curve
		,	pDOUBLE			pWts_Begin      // Absolute Beginning of Rational Bezier Weights
												// for the entire Curve
												// needed for Closed Curve
		,	BOOL			bLast			// Last Curve
		,	PDMA44			pMCoef			// Basis Matrix
		,	pWORLD			pInC            // ORDER Number CONTROL Points Array
												// for the Current Curve Segment
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	PDMA44			pMG				// Output Matrix
		)
			// Return Actual Number of Points Generated
{
	////////////////////////////////////////////////////////////////////////
	int			i,nOut=0;
	DMA44		G;
	pWORLD		p,pv;
	double		One;
	double		Wts;
	pDOUBLE 	pw;
	/////////////////
	One = 1.;
	//////////////////////////////////////////////////// Geometry Matrix
	for( i=0; i<ORDER; i++ ) 
	{
		pv	= (bClosed && bLast && (i == ORDER-1))?pInC_Begin:(pInC+i);
		Wts = (bClosed && bLast && (i == ORDER-1))?*pWts_Begin:*(pWts+i);
		if(nDim == 3)	// NonRational
		{	
			SETM( G, i, *pv, One  );
		}
		else	
		if(nDim == 4)	// Rational
		{
			SETM( G, i, *pv, Wts );
		}	
	}
	////////////////////////////////////////////////////// Segment	
	HO_ComputeMG(pMG, pMCoef, G, nDim);
	///////////////////////////////////
	return MA_OK;
} 
*/