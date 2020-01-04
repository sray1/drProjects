// CPA_CooP3.cpp : implementation of the CPA_CooP3 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "PA_CooP3.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_CooP3

IMPLEMENT_DYNAMIC(CPA_CooP3,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_CooP3,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_CooP3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)
//////////////////////////////////////////////
int CPA_CooP3::CoonCurves
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
	(
		short	nPts,	//	number of input Control points in Each Curve
		pWORLD	pInC1,	//	input data point for Curve 1
		pDOUBLE	pWts1,	//	input data Weight for Curve 1
		pWORLD	pInC2,	//	input data point for Curve 2
		pDOUBLE	pWts2,	//	input data Weight for Curve 2
		pWORLD	pInC3,	//	input data point for Curve 3
		pDOUBLE	pWts3,	//	input data Weight for Curve 3
		pWORLD 	pOut,	//	Output Pts array
		pDOUBLE	pOutWts //	Output Wts array
	)	  
{
	//////////////////////////////////////////////////////
	//	Output Storage: Example for nPts = 6
	//
	//			P2	0/5								5							
	//				1  4	c3						4 10
	// Input	c1:	2	  3				Output:		3 9  14
	//				3	    2						2 8  13 17	
	//				4		  1						1 7  12 16 19
	//			P3	5/0 1 2 3 4 5/0	P1				0 6  11 15 18 20 --- v=0
	//					c2 Curve					|			    \
	//												|				  \
	//											   u=0				   w=0
	/////////////////////////////////////////////////////////////////////////
	int		i,j,m;
	/////////////////
	if( pOut ) 
	{
		int nV = nPts * (nPts+1)/2;
		/////////////////////////////////////////////////////////// Curve_2 & Curve_3 (vertex P1)
		pWORLD pOut1		= new WORLD[nV];
		pDOUBLE pOutWts1	= new double[nV];
		if(pOut1 && pOutWts1)
		{		
			m = Coon_2_N_3(nPts,pInC2,pWts2,pInC3,pWts3,pOut1,pOutWts1,nV);
			if(m<0)
			{
				AfxMessageBox("Error:\nCPA_CooP3::CoonCurves\nm<0\nCurve_2 & Curve_3");
				if(pOut1)
					delete pOut1;
				if(pOutWts1)
					delete pOutWts1;
				return -1;
			}
		}
		else
		{
			if(pOut1)
				delete pOut1;
			if(pOutWts1)
				delete pOutWts1;
			return -1;
		}
		/////////////////////////////////////////////////////////// Curve_3 & Curve_1 (vertex P2)
		pWORLD pOut2		= new WORLD[nV];
		pDOUBLE pOutWts2	= new double[nV];
		if(pOut2 && pOutWts2)
		{		
			m = Coon_3_N_1(nPts,pInC3,pWts3,pInC1,pWts1,pOut2,pOutWts2,nV);	  
			if(m<0)
			{
				AfxMessageBox("Error:\nCPA_CooP3::CoonCurves\nm<0\nCurve_3 & Curve_1");
				if(pOut2)
					delete pOut2;
				if(pOutWts2)
					delete pOutWts2;
				return -1;
			}
		}
		else
		{
			if(pOut2)
				delete pOut2;
			if(pOutWts2)
				delete pOutWts2;
			return -1;
		}
		/////////////////////////////////////////////////////////// Curve_1 & Curve_2 (vertex P3)
		pWORLD pOut3		= new WORLD[nV];
		pDOUBLE pOutWts3	= new double[nV];
		if(pOut3 && pOutWts3)
		{		
			m = Coon_1_N_2(nPts,pInC1,pWts1,pInC2,pWts2,pOut3,pOutWts3,nV);	  
			if(m<0)
			{
				AfxMessageBox("Error:\nCPA_CooP3::CoonCurves\nm<0\nCurve_1 & Curve_2");
				if(pOut3)
					delete pOut3;
				if(pOutWts3)
					delete pOutWts3;
				return -1;
			}
		}
		else
		{
			if(pOut3)
				delete pOut3;
			if(pOutWts3)
				delete pOutWts3;
			return -1;
		}
		/////////////////////////////////////////////////////////// Convex Combination
		double rPts = 1./(nPts-1);
		double u,v,w;
		int m = -1;
		///////////
	    for( i = 0; i<nPts; i++ )		
		{
			u	= rPts * i;						// u dir
			///////////////
			for( j = 0; j<(nPts-i); j++ )		
			{
        		v	= rPts * j;					// v dir 
        		w 	 = 1. - u - v;				// w dir
				////////////////
        		m++;
        		////
				pOut[m].x = pOut1[m].x * u + pOut2[m].x * v + pOut3[m].x * w;
				pOut[m].y = pOut1[m].y * u + pOut2[m].y * v + pOut3[m].y * w;
				pOut[m].z = pOut1[m].z * u + pOut2[m].z * v + pOut3[m].z * w;
				////////////////////////////////////////
				pOutWts[m]= pOutWts1[m]* u + pOutWts2[m]* v + pOutWts3[m]* w;
				////////////////////////////////////////
			}
		}
		////////////////////////////////// delete memory
		if(pOut1)
			delete pOut1;
		if(pOutWts1)
			delete pOutWts1;
		if(pOut2)
			delete pOut2;
		if(pOutWts2)
			delete pOutWts2;
		if(pOut3)
			delete pOut3;
		if(pOutWts3)
			delete pOutWts3;
		////////////////
		if((m+1) != nV)
		{
			AfxMessageBox("Error:\nCPA_CooP3::CoonCurves\n(m+1) != nV");
			return -1;
		}
		else
			return nV;
		/////////
	}
	////////////
	AfxMessageBox("Error:\nCPA_CooP3::CoonCurves\npOut NULL!");
	return -1;
}

int CPA_CooP3::Coon_1_N_2
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC1,	//	input data point for Curve 1
				pDOUBLE	pWts1,	//	input data Weight for Curve 1
				pWORLD	pInC2,	//	input data point for Curve 2
				pDOUBLE	pWts2,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			)	  
{
	//	OUTPUT STORAGE ALWAYS SAME
	//////////////////////////////////////////////////////////////////////////
	//	Proj.Map(x(u)) = (1-r) * x(u,0,w)[=Curve_2] + r * x(0,v,w)[=Curve_1]
	//////////////////////////////////////////////////////
	//	No. of Pts on each side:	nPts
	//  Tringle Number				TN = nPts * (nPts + 1) / 2
	//	Example: let nPts = 6
	//	Total Output = TN = 21
	//////////////////////////////////////////////////////
	//	Curve C1 is u=0 Curve
	//	Curve C2 is v=0 Curve
	//	End of Curve C1 is Connected to Start of Curve C2
	//////////////////////////////////////////////////////
	//	Output Storage:
	//
	//				0								5							
	//				1								4 10
	// Input	c1:	2					Output:		3 9  14
	//				3								2 8  13 17	
	//				4								1 7  12 16 19
	//				5/0 1 2 3 4 5					0 6  11 15 18 20
	//					c2 Curve
	////////////////////////////
	double	rPts = 1./(nPts-1);
	double	r,u,v,r1;
	int		i,j,k,m,nCount=0;
	//////////////////////////////////////////////// Curve_1 & Curve_2
    for( k = 0; k<nPts; k++ )		
	{
		///////////////
		for( i = 0; i<nPts-k; i++ )		
        {
 			j	= nPts-i-k-1;
			/////////////////
			u	= rPts * i;			// u dir
        	v	= rPts * j;			// v dir
			r 	= ((v+u) !=0)?v/(v + u):0;
        	r1 	= 1. - r;
			////////////////
        	m	= BARY2LIN_PT(i,j,nPts);
        	////
			nCount++;
			/////////
            pOut[m].x = pInC1[k].x * r	+ pInC2[nPts-k-1].x * r1;
            pOut[m].y = pInC1[k].y * r	+ pInC2[nPts-k-1].y * r1;
            pOut[m].z = pInC1[k].z * r	+ pInC2[nPts-k-1].z * r1;
			////////////////////////////////////////
            pOutWts[m]= pWts1[k]   * r	+ pWts2[nPts-k-1]   * r1;
			////////////////////////////////////////
        }
	}
	////////////////
	if(nCount != nOut)
	{
		AfxMessageBox("Error:\nCPA_CooP3::Coon_1_N_2\nnCount != nOut");
		return -1;
	}
	else
		return nCount;
	/////////
}

int CPA_CooP3::Coon_2_N_3
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC2,	//	input data point for Curve 1
				pDOUBLE	pWts2,	//	input data Weight for Curve 1
				pWORLD	pInC3,	//	input data point for Curve 2
				pDOUBLE	pWts3,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			)	  
{
	//	OUTPUT STORAGE ALWAYS SAME
	//////////////////////////////////////////////////////////////////////////
	//	Proj.Map(x(u)) = (1-r) * x(u,0,w)[=Curve_2] + r * x(u,v,0)[=Curve_3]
	//////////////////////////////////////////////////////
	//	No. of Pts on each side:	nPts
	//  Tringle Number				TN = nPts * (nPts + 1) / 2
	//	Example: let nPts = 6
	//	Total Output = TN = 21
	//////////////////////////////////////////////////////
	//	Curve C2 is v=0 Curve
	//	Curve C3 is w=0 Curve
	//	End of Curve C2 is Connected to Start of Curve C3
	//////////////////////////////////////////////////////
	//	Output Storage:
	//
	//				5								5							
	//				  4	  							4 10
	// Input	c3:	    3				Output:		3 9  14
	//				 	  2	 						2 8  13 17	
	//				 		1						1 7  12 16 19
	//				0 1 2 3 4 5/0					0 6  11 15 18 20
	//					c2 Curve
	////////////////////////////
	double	rPts = 1./(nPts-1);
	double	r,v,w,r1;
	int		i,j,k,m,nCount=0;
	//////////////////////////////////////////////// Curve_2 & Curve_3
    for( i = 0; i<nPts; i++ )		
	{
		///////////////
		for( j = 0; j<nPts-i; j++ )		
        {
 			k	= nPts-i-j-1;
			/////////////////
			v	= rPts * j;			// v dir
        	w	= rPts * k;			// w dir 
			r	= ((v+w) !=0)?v/(v + w):0;
        	r1	= 1. - r;
			////////////////
        	m	= BARY2LIN_PT(i,j,nPts);
        	////
			nCount++;
			/////////
            pOut[m].x = pInC2[i].x * r1	+ pInC3[nPts-i-1].x * r;
            pOut[m].y = pInC2[i].y * r1	+ pInC3[nPts-i-1].y * r;
            pOut[m].z = pInC2[i].z * r1	+ pInC3[nPts-i-1].z * r;
			////////////////////////////////////////
            pOutWts[m]= pWts2[i]   * r1	+ pWts3[nPts-i-1]   * r;
			////////////////////////////////////////
        }
	}
	////////////////
	if(nCount != nOut)
	{
		AfxMessageBox("Error:\nCPA_CooP3::Coon_2_N_3\nnCount != nOut");
		return -1;
	}
	else
		return nCount;
	/////////
}

int CPA_CooP3::Coon_3_N_1
			(
				short	nPts,	//	number of input Control points in Each Curve
				pWORLD	pInC3,	//	input data point for Curve 1
				pDOUBLE	pWts3,	//	input data Weight for Curve 1
				pWORLD	pInC1,	//	input data point for Curve 2
				pDOUBLE	pWts1,	//	input data Weight for Curve 2
				pWORLD 	pOut,	//	Output Pts array
				pDOUBLE	pOutWts,//	Output Wts array
				int		nOut	//	Expected Output Pts = nPts*(nPts+1)/2
			)	  
{
	//	OUTPUT STORAGE ALWAYS SAME
	//////////////////////////////////////////////////////////////////////////
	//	Proj.Map(x(u)) = (1-r) * x(u,v,0)[=Curve_3] + r * x(0,v,w)[=Curve_1]
	//////////////////////////////////////////////////////
	//	No. of Pts on each side:	nPts
	//  Tringle Number				TN = nPts * (nPts + 1) / 2
	//	Example: let nPts = 6
	//	Total Output = TN = 21
	//////////////////////////////////////////////////////
	//	Curve C3 is w=0 Curve
	//	Curve C1 is u=0 Curve
	//	End of Curve C3 is Connected to Start of Curve C1
	//////////////////////////////////////////////////////
	//	Output Storage:
	//
	//				0/5								5							
	//				1  4   c3 Curve					4 10
	// Input	c1:	2   3				Output:		3 9  14
	//				3 	  2	 						2 8  13 17	
	//				4 		1						1 7  12 16 19
	//				5        0  					0 6  11 15 18 20
	//					
	////////////////////////////
	double	rPts = 1./(nPts-1);
	double	r,w,u,r1;
	int		i,j,k,m,nCount=0;
	//////////////////////////////////////////////// Curve_3 & Curve_1
    for( j = 0; j<nPts; j++ )		
	{
		///////////////
		for( k = 0; k<(nPts-j); k++ )		
        {
 			i	= nPts-j-k-1;
			/////////////////
       		u	= rPts * i;		// u dir 
  			w	= rPts * k;		// w dir
 			r	= ((w+u) !=0)?w/(w + u):0;
        	r1 	 = 1. - r;
			////////////////
        	m	= BARY2LIN_PT(i,j,nPts);
        	////
			nCount++;
			/////////
            pOut[m].x = pInC3[j].x * r1	+ pInC1[nPts-j-1].x * r;
            pOut[m].y = pInC3[j].y * r1	+ pInC1[nPts-j-1].y * r;
            pOut[m].z = pInC3[j].z * r1	+ pInC1[nPts-j-1].z * r;
			////////////////////////////////////////
            pOutWts[m]= pWts3[j]   * r1	+ pWts1[nPts-j-1]   * r;
			////////////////////////////////////////
        }
	}
	////////////////
	if(nCount != nOut)
	{
		AfxMessageBox("Error:\nCPA_CooP3::Coon_3_N_1\nnCount != nOut");
		return -1;
	}
	else
		return nCount;
	/////////
}
////////////////////// end of module /////////////////////

