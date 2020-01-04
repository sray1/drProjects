// DrCurves.cpp : implementation of the CCurve class
//

#include "stdafx.h"
#include <math.h>

#include "3DMath.h"
//////////////////
#include "Curve.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CCurve
////////////////////////////////////
IMPLEMENT_DYNAMIC(CCurve,CObject)
/*
BEGIN_MESSAGE_MAP(CCurve,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CCurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
//////////////////// 
CCurve::CCurve()
{
#ifdef _DEBUG
	int j;
	////////
	for(j=0;j<30;j++)
		m_bMessage[j] = FALSE;
	///////////////////////////////// 		
#endif		
} 
//////////////////////////////////////////// 
int CCurve::CtlPtStep(CURVEPROC kind, int nDegree)
{
	switch( kind ) {
		case CP_BEZIER:			return nDegree;
		case CP_BSPLINE:		return 1;	// B-Spline UNIFORM
		case CP_NUSPLINE:		return 1;	// B-Spline NON-UNIFORM
		case CP_NURB:			return 1;	// B-Spline NON-UNIFORM RATIONAL
		case CP_CATMULLROM:		return 1;	// Catmull-Rom
		case CP_CARDISPLINE:	return 1;	// Cardinal Spline (ALFA Catmull-Rom)
		case CP_HERMITE:		return 2;	// Hermite
		case CP_BETA:			return 1;	// Beta-Spline
		case CP_NURBQUAD:		return 1;	// B-Spline NON-UNIFORM RATIONAL
		case CP_QUADRATIC:		return 2;	// Quadratics:
		case CP_LAGQUAD:		return 2; 	// Lagrange
		case CP_CIRCLE:			return 2;
		case CP_ELLIPSE:		return 2;
		case CP_PARABOLA:		return 2;
		case CP_LINEAR:			return 1;	// Linears
	}
	return 0;
}

int CCurve::NumberOfCurves(CURVEPROC kind,int nC,int* pnp,BOOL bClose, int nOrder)
{

	int dIx;
	if( !(dIx = CtlPtStep( kind, nOrder - 1 )) )
		return -1;
	*pnp 	= bClose ? nC/dIx : (nC - nOrder)/dIx + 1;			// Number of Quad Curves
	////////////////////////
//	*pnOut 	= (*pnp) * nSegs + 1;	// Number of Total Output Points
	//////////////////////// 
	return	0;
}
///////////////////////////////////////////////////////////////////// Helper
int CCurve::DegreeElevate_Seg(pWORLD Cons, pWORLD NewC, int nDegree)
{
	// Elevate Bezier One Degree at a time
    //////////////////////////////////////
    int i,nDeg1 = nDegree + 1;
    //////////////////////////
	NewC[0].x = Cons[0].x;    
	NewC[0].y = Cons[0].y;    
	NewC[0].z = Cons[0].z;    
    //////////////////////
    for(i=1;i<=nDegree;i++)
    	NewC[i].x = (i * Cons[i-1].x + (nDeg1 - i) * Cons[i].x)/nDeg1;
    	NewC[i].y = (i * Cons[i-1].y + (nDeg1 - i) * Cons[i].y)/nDeg1;
    	NewC[i].z = (i * Cons[i-1].z + (nDeg1 - i) * Cons[i].z)/nDeg1;
    //////////////////////
	NewC[nDeg1].x = Cons[nDegree].x;    
	NewC[nDeg1].y = Cons[nDegree].y;    
	NewC[nDeg1].z = Cons[nDegree].z;    
    //////////////////////
    return 0;
    	
}

int CCurve::Rat_DegreeElevate_Seg(	pWORLD Cons, pDOUBLE Wts, 
									pWORLD NewC, pDOUBLE NewW, int nDegree)
{
	// Elevate Rational Bezier One Degree at a time
    //////////////////////////////////////
    int i,nDeg1 = nDegree + 1;
    double alf_i,w1,w2;
    //////////////////////////
	NewW[0]		= Wts[0];    
	    
	NewC[0].x 	= Cons[0].x;    
	NewC[0].y 	= Cons[0].y;    
	NewC[0].z 	= Cons[0].z;    
    //////////////////////
    for(i=1;i<=nDegree;i++)
    {
    	alf_i 	= i/nDeg1;
    	w1		= NewW[i];
    	w2		= NewW[i-1];
    	NewW[i] 	= alf_i * Wts[i-1] + (1 - alf_i) * Wts[i];
    	NewC[i].x 	= (alf_i * w1 * Cons[i-1].x + (1 - alf_i) * w2 * Cons[i].x)/NewW[i];
    	NewC[i].y 	= (alf_i * w1 * Cons[i-1].y + (1 - alf_i) * w2 * Cons[i].y)/NewW[i];
    	NewC[i].z 	= (alf_i * w1 * Cons[i-1].z + (1 - alf_i) * w2 * Cons[i].z)/NewW[i];
    }	
    //////////////////////
	NewW[nDeg1] 	= Wts[nDegree];    
	    
	NewC[nDeg1].x 	= Cons[nDegree].x;    
	NewC[nDeg1].y 	= Cons[nDegree].y;    
	NewC[nDeg1].z 	= Cons[nDegree].z;    
    //////////////////////
    return 0;
    	
}

int CCurve::Tangent_t(pWORLD Cons, double t, int nDegree, WORLD& tangent)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Tangent Vector of Rational Bezier Curve at parameter t
	//	Always:
	//		 Larger Polygon selected for subdivision
	//		 and its beginning Tangent computed
	////////////////////////////////////////////////////////////////////
	pWORLD NewC = new WORLD[nDegree+1];
	///////////////////////////////////
	double sign = 1.0;
	if(t<0.5)		// subdivide Right
		SubDivide_t(Cons, t, NewC, FALSE/*bLeft*/, nDegree);
	else			// subdivide Left
	{		
		SubDivide_t(Cons, t, NewC, TRUE/*bLeft*/, nDegree);
		sign = -1.0;	//negative <- left polygon order reversed in Subdivision
	}	
	///////////////////////////////////////////////////// Tangent
	Tangent_0(NewC, nDegree, tangent);	//022597
	tangent.x = tangent.x * sign;
	tangent.y = tangent.y * sign;
	tangent.z = tangent.z * sign;
	/////////////////
	delete [] NewC;
	////////////////
	return 0; 	
}

int CCurve::Tangent_0(pWORLD Cons, int nDegree, WORLD& tangent)
{
    ///////////////////////////////////////////
	// Computes Tangent of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * delb0
    //	where
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	Math3D.Sub3DPts(&Cons[1], &Cons[0], &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree, &tangent);
	/////////////////
	return 0; 	

}
int CCurve::Tangent_0(WORLD b0, WORLD b1, int nDegree, WORLD& tangent)
{
    ///////////////////////////////////////////
	// Computes Tangent of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * delb0
    //	where
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	Math3D.Sub3DPts(&b1, &b0, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree, &tangent);
	/////////////////
	return 0; 	

}

int CCurve::Tangent_1(WORLD bnm1, WORLD bn, int nDegree, WORLD& tangent)
{
    ///////////////////////////////////////////
	// Computes Tangent of Bezier:
	//	 	at the End Side ( t = 1)
    ///////////////////////////////////////////
    //
    //		tangent at 1 = nDegree * delb_(n-1)
    //	where
    //		delb_(n-1) 	= b_n - b_(n-1)
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	Math3D.Sub3DPts(&bn, &bnm1, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree, &tangent);
	/////////////////
	return 0; 	

}

double CCurve::Curvature_t(pWORLD Cons, double t, int nDegree)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Signed Curvature of Rational Bezier Curve at parameter t
	//	Always:
	//		 Larger Polygon selected for subdivision
	//		 and its beginning Curvature computed
	////////////////////////////////////////////////////////////////////
	pWORLD NewC = new WORLD[nDegree+1];
	///////////////////////////////////
	double sign = 1.0;
	if(t<0.5)		// subdivide Right
		SubDivide_t(Cons, t, NewC, FALSE/*bLeft*/, nDegree);
	else			// subdivide Left
	{		
		SubDivide_t(Cons, t, NewC, TRUE/*bLeft*/, nDegree);
		sign = -1.0;	//negative <- left polygon order reversed in Subdivision
	}	
	///////////////////////////////////////////////////// Curvature
	double curvature;
	curvature = Curvature_0(NewC, nDegree);
	/////////////////
	delete [] NewC;
	/////////////////
	return curvature; 	
}

double CCurve::Curvature_0(pWORLD Cons, int nDegree)
{
    ///////////////////////////////////////////
	// Computes Curvature of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Eqn.(11.10):
    //
    //		Curvature = 2. * k1 * k2 * k3
    //	where
    //		k1 = (nDegree-1)/nDegree
    //		k2 = w0*w2/(w1**2)
    //		k3 = area/(dist**3)
    //	with
    //		area = area[b0,b1,b2]
    //		dist = dist[b0,b1]
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD r01;
    double dist,area,curvature_0;
	Math3D.Sub3DPts(&Cons[0], &Cons[1], &r01);
	///////////////////////////////////////////
    dist 		= Math3D.Len3DPts(&r01);
	area 		= TriangleArea(Cons[0],Cons[1],Cons[2]);
	curvature_0 = 2.0*(nDegree-1)*area/
					(nDegree*dist*dist*dist);
	/////////////////
	return curvature_0; 	

}

int CCurve::SubDivide_t(pWORLD Cons, double t, pWORLD NewC, BOOL bLeft, int nDegree)
{

	///////////////////////////////////////////
	//	Subdivide  Bezier Curve at parameter t
	//		Left is Reversed Ordered
	///////////////////////////////////////////

	int r,i;
	double tm1 = 1.0 - t;
	///////////////////////////////////////
	if(!bLeft)								// Right Polygon by Casteljau
	{
		for(i=0;i<= nDegree;i++)
		{
			NewC[i].x = Cons[i].x;
			NewC[i].y = Cons[i].y;
			NewC[i].z = Cons[i].z;
		}
		////////////////////////	
		for(r=1;r<= nDegree;r++)
		{
			for(i=0;i<= nDegree-r;i++)
			{
				NewC[i].x = tm1 * NewC[i].x + t * NewC[i+1].x;
				NewC[i].y = tm1 * NewC[i].y + t * NewC[i+1].y;
				NewC[i].z = tm1 * NewC[i].z + t * NewC[i+1].z;
			}
		}
	}
	else									// Left Polygon by Casteljau
	{
		tm1 = t;					// Reverse Ordering to get Leftside
		t 	= 1. - tm1;
		/////////////////////////
		for(i=0;i<= nDegree;i++)
		{
			NewC[nDegree-i].x = Cons[i].x;
			NewC[nDegree-i].y = Cons[i].y;
			NewC[nDegree-i].z = Cons[i].z;
		}
		////////////////////////	
		for(r=1;r<= nDegree;r++)
		{
			for(i=0;i<= nDegree-r;i++)
			{
				NewC[i].x = tm1 * NewC[i].x + t * NewC[i+1].x;
				NewC[i].y = tm1 * NewC[i].y + t * NewC[i+1].y;
				NewC[i].z = tm1 * NewC[i].z + t * NewC[i+1].z;
			}
		}
	}
	//////////
	return 0;					
		
}

int CCurve::Rat_Tangent_t(pWORLD Cons, pDOUBLE Wts, double t, int nDegree, WORLD& tangent)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Tangent Vector of Rational Bezier Curve at parameter t
	//	Always:
	//		 Larger Polygon selected for subdivision
	//		 and its beginning Tangent computed
	////////////////////////////////////////////////////////////////////
	pWORLD 	NewC = new WORLD[nDegree+1];
	pDOUBLE NewW = new double[nDegree+1];
	///////////////////////////////////
	double sign = 1.0;
	if(t<0.5)		// subdivide Right
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, FALSE/*bLeft*/, nDegree);
	else			// subdivide Left
	{		
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, TRUE/*bLeft*/, nDegree);
		sign = -1.0;	//negative <- left polygon order reversed in Subdivision
	}	
	///////////////////////////////////////////////////// Tangent
	Rat_Tangent_0(NewC, NewW, nDegree, tangent);//022597
	tangent.x = tangent.x * sign;	//010997
	tangent.y = tangent.y * sign;	//010997
	tangent.z = tangent.z * sign;	//010997
	/////////////////
	delete [] NewC;
	delete [] NewW;
	/////////////////
	return 0; 	
}

int CCurve::Rat_Tangent_t_for_Patch(pWORLD Cons, pDOUBLE Wts, double t, int nDegree, 
															pDOUBLE NewWt, WORLD& tangent)
{
	//		We Need later NewW[0] at t for Tangent Calculation for
	//					Tensor Product  RationalPatch 
	////////////////////////////////////////////////////////////////////	
	//	Returns Tangent Vector of Rational Bezier Curve at parameter t
	//	Always:
	//		 Larger Polygon selected for subdivision
	//		 and its beginning Tangent computed
	////////////////////////////////////////////////////////////////////
	pWORLD 	NewC = new WORLD[nDegree+1];
	pDOUBLE NewW = new double[nDegree+1];
	///////////////////////////////////
	double sign = 1.0;
	if(t<0.5)		// subdivide Right
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, FALSE/*bLeft*/, nDegree);
	else			// subdivide Left
	{		
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, TRUE/*bLeft*/, nDegree);
		sign = -1.0;	//negative <- left polygon order reversed in Subdivision
	}	
	///////////////////////////////////////////////////// Tangent
	Rat_Tangent_0(NewC, NewW, nDegree, tangent); //022597	
	tangent.x	= tangent.x * sign;	//010997
	tangent.y	= tangent.y * sign;	//010997
	tangent.z	= tangent.z * sign;	//010997
	*NewWt		= NewW[0]; 
	/////////////////
	delete [] NewC;
	delete [] NewW;
	/////////////////
	return 0; 	
}

int CCurve::Rat_Tangent_0(WORLD b0, WORLD b1, double Wt0, double Wt1, int nDegree,
																	WORLD& tangent)
{
    ///////////////////////////////////////////
	// Computes Tangent of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * k1 * delb0
    //	where
    //		k1 		= w1/w0
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
    double k1;
    k1 	= Wt1/Wt0;
	Math3D.Sub3DPts(&b1, &b0, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree * k1, &tangent);
	///////////////////
	return 0; 	
}

int CCurve::Rat_Tangent_0(pWORLD Cons, pDOUBLE Wts, int nDegree, WORLD& tangent)
{
    ///////////////////////////////////////////
	// Computes Tangent of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * k1 * delb0
    //	where
    //		k1 		= w1/w0
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
    double k1;
    k1 	= Wts[1]/Wts[0];
	Math3D.Sub3DPts(&Cons[1], &Cons[0], &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree * k1, &tangent);
	///////////////////
	return 0; 	
}

int CCurve::Rat_Tangent_1(WORLD bnm1, WORLD bn, double Wtnm1, double Wtn, int nDegree,
																		WORLD& tangent)
{
	// n = Degree
    ///////////////////////////////////////////
	// Computes Tangent of Rational Bezier:
	//	 	at the End Side ( t = 1)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 1 = nDegree * k_(n-1) * delb_(n-1)
    //	where
    //		k_(n-1)		= w_(n-1)/w_n
    //		delb_(n-1) 	= b_n - b_(n-1)
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
    double knp1;
    knp1 	= Wtnm1/Wtn;
	Math3D.Sub3DPts(&bn, &bnm1, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree * knp1, &tangent);
	///////////////////
	return 0; 	

}

double CCurve::Rat_Curvature_t(pWORLD Cons, pDOUBLE Wts, double t, int nDegree)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Signed Curvature of Rational Bezier Curve at parameter t
	//	Always:
	//		 Larger Polygon selected for subdivision
	//		 and its beginning Curvature computed
	////////////////////////////////////////////////////////////////////
	pWORLD 	NewC = new WORLD[nDegree+1];
	pDOUBLE NewW = new double[nDegree+1];
	///////////////////////////////////
	double sign = 1.0;
	if(t<0.5)		// subdivide Right
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, FALSE/*bLeft*/, nDegree);
	else			// subdivide Left
	{		
		Rat_SubDivide_t(Cons, Wts, t, NewC, NewW, TRUE/*bLeft*/, nDegree);
		sign = -1.0;	//negative <- left polygon order reversed in Subdivision
	}	
	///////////////////////////////////////////////////// Curvature
	double curvature;
	curvature = Rat_Curvature_0(NewC, NewW, nDegree);
	/////////////////
	delete [] NewC;
	delete [] NewW;
	/////////////////
	return curvature; 	
}

double CCurve::Rat_Curvature_0(pWORLD Cons, pDOUBLE Wts, int nDegree)
{
    ///////////////////////////////////////////
	// Computes Curvature of Rational Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Eqn.(11.10):
    //
    //		Curvature = 2. * k1 * k2 * k3
    //	where
    //		k1 = (nDegree-1)/nDegree
    //		k2 = w0*w2/(w1**2)
    //		k3 = area/(dist**3)
    //	with
    //		area = area[b0,b1,b2]
    //		dist = dist[b0,b1]
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD r01;
    double dist,area,curvature_0;
	Math3D.Sub3DPts(&Cons[0], &Cons[1], &r01);
	///////////////////////////////////////////
    dist 		= Math3D.Len3DPts(&r01);
	area 		= TriangleArea(Cons[0],Cons[1],Cons[2]);
	curvature_0 = 2.0*(nDegree-1)*Wts[0]*Wts[2]*area/
					(nDegree*Wts[1]*dist*dist*dist);
	/////////////////
	return curvature_0; 	

}
	 
double CCurve::TriangleArea(WORLD b0, WORLD b1, WORLD b2)
{
    ////////////////////////////////////////////
	// Computes Area of triangle within p0,p1,p2
	// area = .5 * ||(p1-p2) cross (p3-p1)||
	////////////////////////////////////////////
	WORLD r01,r02,r;
	///////////////////////////
	C3DMath Math3D;
	///////////////
	Math3D.Sub3DPts(&b1, &b0, &r01);
	Math3D.Sub3DPts(&b2, &b0, &r02);
    Math3D.Cross3DPts(&r01,&r02,&r);
    ////////////////////////////////
    double area;
    area = 0.5 * Math3D.Len3DPts(&r);
    /////////////
    return area;
   
}

int CCurve::Rat_SubDivide_t(pWORLD Cons, pDOUBLE Wts, double t, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nDegree)
{

	///////////////////////////////////////////////////
	//	Subdivide  Rational Bezier Curve at parameter t
	//		Left is Reversed Ordered
	///////////////////////////////////////////////////

	int r,i;
	double tm1 = 1.0 - t,w1,w2;
	///////////////////////////////////////
	if(!bLeft)								// Right Polygon by Casteljau
	{
		for(i=0;i<= nDegree;i++)
		{
			NewW[i] 	= Wts[i];
			NewC[i].x	= Cons[i].x;
			NewC[i].y	= Cons[i].y;
			NewC[i].z	= Cons[i].z;
		}	
		for(r=1;r<= nDegree;r++)
		{
			for(i=0;i<= nDegree-r;i++)
			{
				w1			= NewW[i];
				w2			= NewW[i+1];
				////////////////////////
				NewW[i] 	= tm1 * NewW[i] + t * NewW[i+1];
				NewC[i].x 	= (tm1 * w1 * NewC[i].x + t * w2 * NewC[i+1].x)/NewW[i];
				NewC[i].y 	= (tm1 * w1 * NewC[i].y + t * w2 * NewC[i+1].y)/NewW[i];
				NewC[i].z 	= (tm1 * w1 * NewC[i].z + t * w2 * NewC[i+1].z)/NewW[i];
			}
		}
	}
	else									// Left Polygon by Casteljau
	{
		tm1 = t;					// Reverse Ordering to get Leftside
		t 	= 1. - tm1;
		/////////////////////////
		for(i=0;i<= nDegree;i++)
		{
			NewW[nDegree-i] 	= Wts[i];
			NewC[nDegree-i].x	= Cons[i].x;
			NewC[nDegree-i].y	= Cons[i].y;
			NewC[nDegree-i].z	= Cons[i].z;
		}	
		for(r=1;r<= nDegree;r++)
		{
			for(i=0;i<= nDegree-r;i++)
			{
				w1			= NewW[i];
				w2			= NewW[i+1];
				////////////////////////
				NewW[i] 	= tm1 * NewW[i] + t * NewW[i+1];
				NewC[i].x 	= (tm1 * w1 * NewC[i].x + t * w2 * NewC[i+1].x)/NewW[i];
				NewC[i].y 	= (tm1 * w1 * NewC[i].y + t * w2 * NewC[i+1].y)/NewW[i];
				NewC[i].z 	= (tm1 * w1 * NewC[i].z + t * w2 * NewC[i+1].z)/NewW[i];
			}
		}
	}
	//////////
	return 0;					
		
}

//int CCurve::GetTangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,int nDegree,int nCurves,
//					int nCon,int nDim,pDOUBLE pWts,pWORLD pCon)
int CCurve::GetTangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,int nDegree,int nCurves,
					int nCon,int nDim,pDOUBLE pWts,pWORLD pCon,double dSameNessRatio)
{
	int nResult = 0;
	////////////////
	int i,nCurSeg;
	//////////////////
	nResult = GetCurrentBezSeg_N_ControlIndex(wNodeCoord,
					i,nCurSeg,nDegree,nCurves,nCon,pWts,pCon,dSameNessRatio);
	/////////////
	if(nResult<0) // NO MATCH
		return nResult;
	////////////////////////////////////////////////////////// Must be Corner Controls
	if(i == 0)
	{
		nResult = GetBezSegEndTangent_0(nCurSeg,nDegree,pCon,pWts,nCurves,nDim,Tangent);
		/////////////
		return nResult;
	}
	else
	if(i  == nDegree)
	{
		nResult = GetBezSegEndTangent_1(nCurSeg,nDegree,pCon,pWts,nCurves,nDim,Tangent);
		/////////////
		return nResult;
	}
	else
	{
		AfxMessageBox("ERROR:\nCCurve::GetTangentAtaNode\nControl i problem");
		return -1;
	}
	//////////////
	return nResult;


}

//int CCurve::GetCurrentBezSeg_N_ControlIndex(WORLD wNodeCoord,int& nCtrl,int& nCurrentBezSeg,
//					int nDegree,int nCurves,int nC,pDOUBLE pWts,pWORLD pInC)
int CCurve::GetCurrentBezSeg_N_ControlIndex(WORLD wNodeCoord,int& nCtrl,int& nCurrentBezSeg,
				int nDegree,int nCurves,int nC,pDOUBLE pWts,pWORLD pInC,double dSameNessRatio)
{
	C3DMath Math3D;
	///////////////
	int			i,n,dIx,nOut=0,Ix;
	//////////////////////////////////////////////////// Control pt step
	dIx = CtlPtStep( CP_BEZIER, nDegree );
	/////////////////////////////////////
	for( Ix = n = 0; n < nCurves; n++, Ix += dIx )
	{
		////////////////////////////////////////////////////// fill up CONTROL for the Curve
		for(i=0;i<=nDegree;i++)
		{
			if( Math3D.AreSame_WORLD(&wNodeCoord, pInC+Ix+i,dSameNessRatio ) )	// MATCH?
			{
				nCtrl			= i;	// 0 or nDegree
				nCurrentBezSeg	= n;
				/////////////
				return 0;
			}
	
		}
	}													
	//////////////////
	return -1;		// NO MATCH
} 

int CCurve::GetBezSegEndTangent_0(int nCurrentBezSeg,int nDegree,pWORLD pCon,pDOUBLE pWts,
									int nMaxBezSegs,int nDim,WORLD& Tangent)
{
	if(nCurrentBezSeg<0 || nCurrentBezSeg>nMaxBezSegs)	// Zero-Based index
		return -1;
	//////////////////////////////////////////////////
	int	CtlStep		= CtlPtStep( CP_BEZIER, nDegree );		// Control Pt. Step
	int nStartCtl	= nCurrentBezSeg * CtlStep;
	/////////////////////////////
	WORLD b0 = pCon[nStartCtl]; 
	WORLD b1 = pCon[nStartCtl+1];
	////////////////////////////////////////////////// get Tangent
	if(nDim == 3)	// NonRational
		//////////////////////////////
		Tangent_0(b0, b1, nDegree, Tangent);
		//////////////////////////////
	else	
	if(nDim == 4)	// Rational
	{
		double Wt0 = pWts[nStartCtl]; 
		double Wt1 = pWts[nStartCtl+1];
		//////////////////////////////
		Rat_Tangent_0(b0, b1, Wt0, Wt1, nDegree, Tangent); 
		//////////////////////////////
	}
	////////
	return 0;
}

int CCurve::GetBezSegEndTangent_1(int nCurrentBezSeg,int nDegree,pWORLD pCon,pDOUBLE pWts,
									int nMaxBezSegs,int nDim,WORLD& Tangent)
{
	if(nCurrentBezSeg<0 || nCurrentBezSeg>nMaxBezSegs)	// Zero-Based index
		return -1;
	//////////////////////////////////////////////////
	int	CtlStep	= CtlPtStep( CP_BEZIER, nDegree );		// Control Pt. Step
	int nEndCtl	= nCurrentBezSeg * CtlStep + nDegree;
	/////////////////////////////
	WORLD bn	= pCon[nEndCtl]; 
	WORLD bnm1	= pCon[nEndCtl-1];
	////////////////////////////////////////////////// get Tangent
	if(nDim == 3)	// NonRational
		//////////////////////////////
		Tangent_0(bnm1, bn, nDegree, Tangent);//010997 
		//////////////////////////////
	else	
	if(nDim == 4)	// Rational
	{
		double Wtn		= pWts[nEndCtl]; 
		double Wtnm1	= pWts[nEndCtl-1];
		//////////////////////////////
		Rat_Tangent_0(bnm1, bn, Wtnm1, Wtn, nDegree, Tangent); 
		//////////////////////////////
	}
	////////
	return 0;
}
//////////////////////////////////////////////////// 
/*
int	CCurve::Gen_OutputReDistribution
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

