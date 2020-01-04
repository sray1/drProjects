// DrCurves.cpp : implementation of the CCurve_1 class
//

#include "stdafx.h"
#include <math.h>
                  
#include "3DMath.h"
/////////////////////
#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_CuPS.h"
///////////////////
#include "Curve_1.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CCurve_1
#define	ORDER	2		// Linear
////////////////////////////////////
IMPLEMENT_DYNAMIC(CCurve_1,CCurve)
/*
BEGIN_MESSAGE_MAP(CCurve_1,CCurve)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCurve_1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
#define KNOT_OFFSET	2			// Spline(NonUniform)
/////////////////////
enum { X,Y,Z,W };

static DMA22
	CoefLagLin = {	{ -1,	 1 },
					{  1,	 0 }	}
,					
	CoefBezier = {	{ -1,	 1 },
					{  1,	 0 }	};
/*					
,	CoefBSpline = {                                                           ??
		{ -0.166666666F,  0.5F, 		 -0.5F,  		0.166666666F },
		{  0.5F,			-1,  		  0.5F,  		0 			},
		{ -0.5F,			 0,  		  0.5F,  		0 			},
		{  0.166666666F,  0.66666666F,  0.166666666F,  0 			}	} 
*/		
;

#define	HO_LINEAR(u,v,t)		(u)[(v)+0]*(t) + (u)[(v)+4]
/*
#define	SETM(m,n,o)				(m)[(n)][X] = (o).x;\
								(m)[(n)][Y] = (o).y;\
								(m)[(n)][Z] = (o).z;\
								(m)[(n)][W] = 1 
*/								
#define	SETM(m,n,o,w)			(m)[(n)][X] = (o).x * (w);\
								(m)[(n)][Y] = (o).y * (w);\
								(m)[(n)][Z] = (o).z * (w);\
								(m)[(n)][W] = (w)
//////////////////// 
CCurve_1::CCurve_1()
{
} 
/////////////////////////////////////////////////////////////////////
PDMA22 CCurve_1::SetBasis(enum CURVEPROC kind,double bias,double tension,double alfa)
{
	PDMA22	C;

	switch( kind )
	{
		case CP_LAGQUAD:		return (PDMA22)CoefLagLin;
		case CP_BEZIER:			return (PDMA22)CoefBezier;
	}
	return C;
}
//////////////////////////////////////////////////////////////////	Horner/Quad(HC)
void CCurve_1::GetBlending_NUSpline(int i, double t, pDOUBLE knot, pDOUBLE blend)
{
//    todo : NEEDS TO DO FOR LINEAR
    ///////////////////////////////
    return;

} 
//////////////////////////////////////////////////////////////////	Horner/Cubic(HC)
int CCurve_1::HO_GetAPointOnABezSegCurve 		// 
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
		/////////////////////////////////////////////////////////////
		nOut += HO_GenerateAPointOnASingleBezCurve
					(pInC+Ix[0],nDim,pWts+Ix[0],sCur,pOut,pOutWt);
		/////////////////////////////////////////////////////////////
	}
	return MA_OK;
} 

int CCurve_1::HO_GenerateAPointOnASingleBezCurve 		// 
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
	DMA24		G,MG;
	PDMA24		pMG = (PDMA24)MG;
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
	PDMA22 pMCoef = (PDMA22)CoefBezier;	// Linear
	HO_ComputeMG(pMG, pMCoef, G, nDim);
	///////////////////////////////////
	double t	= sCur;
	////////////////////////////////////////////////////
	nOut += HO_Make_A_Curve_Pt(pMG,nDim,t,pOut,pOutWt);
	////////////////////////////////////////////////////
	return nOut;
} 

int CCurve_1::HO_MakeCurves 		// 
// Return Actual Number of Points Generated
		(
			BOOL			bClosed			// IsClosed
		,	PDMA22			pMCoef			// Basis Matrix
		,	int				CtlStep         // Control Pt. Step
		,	int				nC				// number of CONTROL points
		,	pWORLD			pInC            // Total CONTROL Points Array
		,	int				nDim			// 3= NonRational / 4 = Rational
		,	pDOUBLE			pWts			// Rational Bezier Weights		
		,	pINT			Num_t			// Number of Outpts for each curve
		,	pDOUBLE			Dis_t			// Output Pts.				
		,	pWORLD			pOut            // Total Output Points Array
		,	pDOUBLE			pOutWts			// Total Output Wts Array
		,	int				nCurves			// Total Number of Linear Curves 
		)
{
	////////////////////////////////////////////////////////////////////////
	int			n,nOut=0,Ix[2];
	pWORLD		p;
	pDOUBLE 	pw;
	////////////////////////////////////////
	if( pOut ) 
	{
		p 	= pOut;
		pw 	= pOutWts;
		/////////////////////////////////////
		for( Ix[0] = n = 0; n < nCurves; n++, Ix[0] += CtlStep )
		{
			//////////////////////////////////////////////////// Geometry Matrix
			Ix[1] = (Ix[0]+1) % nC;
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

int CCurve_1::HO_Make_A_Curve 		// 
		(
			BOOL			bClosed			// IsClosed
		,	pWORLD			pInC_Begin      // Absolute Beginning of CONTROL Points Array
												// for the entire Curve
												// needed for Closed Curve
		,	pDOUBLE			pWts_Begin      // Absolute Beginning of Rational Bezier Weights
												// for the entire Curve
												// needed for Closed Curve
		,	BOOL			bLast			// Last Curve
		,	PDMA22			pMCoef			// Basis Matrix
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
	DMA24		G,MG;
	PDMA24		pMG = (PDMA24)MG;
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

int CCurve_1::HO_Make_A_Curve_Pt 		// 
		(
			PDMA24			pMG				// Basis*Geometry Matrix
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
			EMIT_POINT( HO_LINEAR(a,0,t), HO_LINEAR(a,1,t), HO_LINEAR(a,2,t), *pOut );
		}
		else
		if(nDim == 4)	// Rational
		{
			*pOutWts = HO_LINEAR(a,3,t); 
			EMIT_POINT_RAT(HO_LINEAR(a,0,t), HO_LINEAR(a,1,t), HO_LINEAR(a,2,t),
															*pOutWts, *pOut );
		}
		///////
		nOut++;
		///////////
	}
	return nOut;
} 

void CCurve_1::HO_ComputeMG(PDMA24 MG,PDMA22 M,PDMA24 G,int nDim)
{
	int		i,j,k;
	double	t;

	// multiply C (coefficients) by G (geometry), CG = C�G
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
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just Leaving\nCCurve_1::HO_ComputeMG");
		AfxMessageBox(*str);
		///////////////////
		int m;
	    ///////////////////
		j = sprintf(buf,"MG[%d][%d]\n",ORDER,4);
		for(m=0;m<ORDER;m++)
		{
			for(k=0;k<4;k++)
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
PDMA22 CCurve_1::FD_ForwardDifference(int nSegs)
{
	if(1 == 1) return (PDMA22)NULL;
	///////////////////////////////////
	// Forward Difference Matrix: Foley p 535
	static	DMA22 E;
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
	return (PDMA22)E; 
}	

void CCurve_1::FD_ComputeEA(PDMA24 EA, PDMA22 EM, PDMA24 G)
{
	int		i,j,k;
	double	t;

	// multiply EM (FDxMCcoef) by G (geometry), EA 
	for(i=0; i<ORDER; i++)
	{
		for(j=0; j<4; j++) 
		{
			t = 0;
			for(k=0; k<ORDER; k++)
				t += EM[i][k]*G[k][j];
			EA[i][j] = t;
		}
	}		
}

void CCurve_1::FD_MultMat(PDMA22 A, PDMA22 B, PDMA22 C)
{
	int		i,j,k;
	double	t;

	// multiply EM (FDxMCcoef) by G (geometry), EA 
	for(i=0; i<ORDER; i++)
	{
		for(j=0; j<ORDER; j++) 
		{
			t = 0;
			for(k=0; k<ORDER; k++)
				t += B[i][k]*C[k][j];
			A[i][j] = t;
		}
	}		
}

int CCurve_1::FD_GeneratePoints_Unif(PDMA24 EA,int nSegs,pWORLD P,BOOL bEndPt)
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
	
PDMA22 CCurve_1::FD_ComputeFDiff_x_Mcoeff
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
	static DMA22		EM;
	DMA22		MCoeff,FDiff;
	PDMA22		pMCoeff = (PDMA22)MCoeff, pFDiff = (PDMA22)FDiff,B,FD;
	//////////////////////////////////////////////////// Coeff Matrix
	B = SetBasis( kind, bias, tension, alfa );
	Math3D.BlockCopy( (HUGEBLK)B, (HUGEBLK)pMCoeff, sizeof(double)*9 );
	//////////////////////////////////////////////////// ForwardDifference Matrix
	FD = FD_ForwardDifference(nSeg);
	Math3D.BlockCopy( (HUGEBLK)FD, (HUGEBLK)pFDiff, sizeof(double)*9 );
	//////////////////////////////////////////////////// Compute FDiffxMCoeff 
	FD_MultMat(EM,FDiff,MCoeff);  // used to multply matrices
	////////////////////////////////////////////////////
	return (PDMA22)EM;
}	

int CCurve_1::FD_MakeCurves
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
	DMA24		EA,G;
	BOOL		bEndPt;
	pWORLD		p,pv;
	double		One;
	double		Wts;
	////////////////////////////////////////////////////// temporarily
	int nSegUniform = 10; //Useful only for ONE CURVE .i.e.,
	//	The way it is right now is USELESS
	//  WE NEED ADAPTIVE FINITE DIFFERENCE 			todo
    ////////////////////////////////////////////////////// generate
    DMA22 EM;
    PDMA22 pEM = (PDMA22)EM,pTemp;
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
int	CCurve_1::GenerateCurve
	(

		enum CURVEOUTPUT	O_kind		// Output Method
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
	,	int				nCurves			// Total Number of Cubic Curves 
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
	if(1 != 1 ) 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"nCCurve_1::GenerateCurve");
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
		////////////////////
	    delete str;
	}	    
#endif
	////////////////////////////////////////////////////// ControlSteps & Basis
	PDMA22 pMCoef 	= SetBasis( CP_BEZIER, 0.0, 0.0, 0.0 );	// Basis Matrix
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
		//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
		///////////////////////////////////////
		if(1 != 1 ) 
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
	    	///////////////////////////////////////////
			sprintf(buf,"pOut:Output\nCCurve_1::GenerateCurve");
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
	}
	//////////////////////////////////////
	if(nPtActual != nOut)
		return -1;	
   	else
		return nPtActual;
}

int CCurve_1::MakeTangents 		// 
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

int CCurve_1::MakeCurvatures 		// 
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
/*
int	CCurve_1::Gen_OutputReDistribution
	(

		BOOL			bClosed			// IsClosed
	,	int				nCon			// number of Input Data points
	,	pWORLD			Con         	// Total Input Data Points Array
	,	int				nMaxOutSeg		// Number of Outpts segments
	,	pINT			OSeg_t			// Number of intervals/Output segments
	,	pDOUBLE			OVal_t			// Output Segment Boundaries
	,	pINT			CSeg_t			// Number of Pts./Curve				
	,	pDOUBLE			CVal_t			// Output Pts.				
	,	int				nCurves			// Total Number of Cubic Curves 
	,	int				nOut			// expected number of generated curve vertices
	)
{
    int i,j;
    double 	LenTot = 0.;
	pDOUBLE pLen = new double[nCurves];	// Data Pt. Lengths
    ////////////////////////////////////////////////
	for (i=0;i<nCurves;i++)
	{
		double sum = 0.0;
		if(bClosed)
			sum 	+= (	(Con[(i+1)%nCurves].x - Con[i].x)*(Con[(i+1)%nCurves].x - Con[i].x)
						+	(Con[(i+1)%nCurves].y - Con[i].y)*(Con[(i+1)%nCurves].y - Con[i].y)
						+	(Con[(i+1)%nCurves].z - Con[i].z)*(Con[(i+1)%nCurves].z - Con[i].z)
						);
		else
			sum 	+= (	(Con[i+1].x - Con[i].x)*(Con[i+1].x - Con[i].x)
						+	(Con[i+1].y - Con[i].y)*(Con[i+1].y - Con[i].y)
						+	(Con[i+1].z - Con[i].z)*(Con[i+1].z - Con[i].z)
						);
		//////////////////////							
		*(pLen+i) = sqrt(sum);
		//////////////////////
		LenTot	+= *(pLen+i);
	}
	///////////////////////////////////////////////// endPts of Curves
	for (i=1;i<nCurves;i++)
		*(pLen+i) += *(pLen+i-1);
	///////////////////////////////////////////////////////// 
	double dBeg,dEnd,del;
	int nSeg,nCum=0;
	///////////////////////////////////////////////
	CVal_t[0] = 0.0;		// First one ALWAYS 0.0
	for (i=0;i<nMaxOutSeg;i++)
	{
		dBeg	= OVal_t[i];
		dEnd 	= OVal_t[i+1];
		nSeg 	= OSeg_t[i];
		del		= (dEnd-dBeg)/nSeg;			
		///////////////////////////
		for(j=1;j<=nSeg;j++)
			CVal_t[nCum+j] = CVal_t[nCum+j-1] + del*LenTot; // scale by total length
		//////////////////////
		nCum	+= nSeg;
	}
	CVal_t[nCum] = LenTot;		// 
	/////////////////////////////////////////////////////////// ReDistribute
	int LastNum = 0;
	double r;
	////////////////
	dBeg = 0.0;
	for (i=0;i<nCurves;i++)
	{
		dEnd 	= *(pLen+i);
		r = 1./(dEnd-dBeg);			// stretch factor, because each segment is [0,1]
		int num	= 0;
		for(j=LastNum;j<nOut;j++)
		{
			if(CVal_t[j]<= dEnd)
			{
				num++;
				CVal_t[j] -= dBeg;	// shift by beginning of Curve Segment
				CVal_t[j] *= r;
				if(CVal_t[j]>1.0)
					CVal_t[j] = 1.0;	 
			}	
			else
			{
				dBeg = dEnd;		// save beginning of the next Curve Segment
				break;
			}	
		}
		CSeg_t[i] 	= num;
		LastNum 	+= num;
	}
	/////////////////////////// Recover last point = 1.0
	CVal_t[nOut-1] = 1.0;	 			
	///////////////////////////	
	delete [] pLen;	// Control Lengths
	/////////
	return 0;
		
}
*/		
////////////////////////////////// end of module ///////////////////// 
