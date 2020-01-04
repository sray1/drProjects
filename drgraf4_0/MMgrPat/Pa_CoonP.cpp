// CPA_CoonP.cpp : implementation of the CPA_CoonP class
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
#include "PA_CoonP.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_CoonP

IMPLEMENT_DYNAMIC(CPA_CoonP,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_CoonP,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_CoonP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPA_CoonP::CoonCurves
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
	(
		short	nPts_S,	//	number of input Control points in S-dir
		short	nPts_T,	//	number of input Control points in T-dir
		pWORLD	pInC1,	//	input data point for Curve 1
		pDOUBLE	pWts1,	//	input data Weight for Curve 1
		pWORLD	pInC2,	//	input data point for Curve 2
		pDOUBLE	pWts2,	//	input data Weight for Curve 2
		pWORLD	pInC3,	//	input data point for Curve 3
		pDOUBLE	pWts3,	//	input data Weight for Curve 3
		pWORLD	pInC4,	//	input data point for Curve 4
		pDOUBLE	pWts4,	//	input data Weight for Curve 4
		pWORLD 	pOut,	//	Output Pts array
		pDOUBLE	pOutWts //	Output Wts array
	)	  
{
	int		nV,i,j,k;
	/////////////////
	if( pOut ) 
	{
		nV			= nPts_S*nPts_T;
		////////////////////////////
		double rS = 1./(nPts_S-1);
		double rT = 1./(nPts_T-1);
		double u,v,u1,v1;
		//////////////////////
	    for( j = 0; j<nPts_T; j++ )
		{
	        for( i = 0; i<nPts_S; i++ )
	        {
	        	u	= rS * i; 
	        	v	= rT * j; 
	        	u1 	 = 1. - u;
	        	v1 	 = 1. - v;
				////////////////
	        	k = j*nPts_S + i;
	        	////////////////
	            pOut[k].x = pInC4[nPts_T-j-1].x * u1	+ pInC2[j].x * u			+
							pInC1[i].x * v1				+ pInC3[nPts_S-i-1].x * v	-
							pInC1[0].x * u1 * v1		- pInC4[0].x * u1 * v		-
							pInC2[0].x * u  * v1		- pInC3[0].x * u  * v		;
				/////////
	            pOut[k].y = pInC4[nPts_T-j-1].y * u1	+ pInC2[j].y * u			+
							pInC1[i].y * v1				+ pInC3[nPts_S-i-1].y * v	-
							pInC1[0].y * u1 * v1		- pInC4[0].y * u1 * v		-
							pInC2[0].y * u  * v1		- pInC3[0].y * u  * v		;
				/////////
	            pOut[k].z = pInC4[nPts_T-j-1].z * u1	+ pInC2[j].z * u			+
							pInC1[i].z * v1				+ pInC3[nPts_S-i-1].z * v	-
							pInC1[0].z * u1 * v1		- pInC4[0].z * u1 * v		-
							pInC2[0].z * u  * v1		- pInC3[0].z * u  * v		;
				////////////////////////////////////////
	            pOutWts[k]= pWts4[nPts_T-j-1] * u1		+ pWts2[j] * u				+
							pWts1[i] * v1				+ pWts3[nPts_S-i-1] * v		-
							pWts1[0] * u1 * v1			- pWts4[0] * u1 * v			-
							pWts2[0] * u  * v1			- pWts3[0] * u  * v			;
				////////////////////////////////////////
	        }
		}
	}
 	return nV;
}
////////////////////// end of module /////////////////////

