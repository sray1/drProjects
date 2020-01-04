// CPA_Loft2.cpp : implementation of the CPA_Loft2 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "glb_Type.h"
#include "glb_Objs.h"
#include "glb_CuPS.h"
///////////////////
#include "PA_Loft2.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_Loft2

IMPLEMENT_DYNAMIC(CPA_Loft2,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_Loft2,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_Loft2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPA_Loft2::LoftCurves_2
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
	(
		short	segs,	//	subdivision value (interior spaces)
		double	ratio,	//  Output Last/Ist ratio in T_Direction
		short	nPts,	//	number of input Control points
		pWORLD	p0,		//	input data point array for start curve
		pDOUBLE	pWt0,	//	input data Weight array
		pWORLD	p1,		//	input data point array for end curve
		pDOUBLE	pWt1,	//	input data Weight array
		pWORLD 	pOut,	//	Output Pts array
		pDOUBLE	pOutWts //	Output Wts array
	)	  
{
	pWORLD	pRow;
	pDOUBLE pRowWt;
	double	v = 0.,v1;
	int		nV,nT,i,j,k;
	long	sizeRow,sizeRowWt;
	/////////////////////////////////////////////////////////
	// NOTE:	allows Unequal Lofting
	//		SPACEs between pts. are:
	//			# of Segments = n + 1
	//			x, x+a, x+2a, x+3a, ..., x+na
	//		with
	//			x = (2*depth)/(segs*(ratio+1))		: depth = 1.0
	//			a = (x*(ratio-1))/(segs-1)
	//
	//////////////////////////////////////////////////////////
	double x,a,depth=1.0;
	if( pOut ) 
	{
		C3DMath		Math3D;
		///////////////////
		sizeRow		= nPts*sizeof(WORLD);
		sizeRowWt	= nPts*sizeof(double);
		nT			= segs+1;
		nV			= nPts*nT;
		/////////////////////////////
		x 			= (2 * depth)/(segs * (ratio + 1));
		a 			= (segs == 1)?0.:(x * (ratio-1))/(segs-1);
		/////////////////////////////////////////
		pRow=pOut; 
		Math3D.BlockCopy( (HUGEBLK)p0, (HUGEBLK)pRow, sizeRow );
		pRowWt=pOutWts; 
		Math3D.BlockCopy( (HUGEBLK)pWt0, (HUGEBLK)pRowWt, sizeRowWt );
		pRow += nPts*(nT-1); 
		Math3D.BlockCopy( (HUGEBLK)p1, (HUGEBLK)pRow, sizeRow );
		pRowWt+= nPts*(nT-1); 
		Math3D.BlockCopy( (HUGEBLK)pWt1, (HUGEBLK)pRowWt, sizeRowWt );
		////////////////////////////////
	    for( i = 0; i<nPts; i++ )
		{
			v = 0.0;
			////////
	        for( j = 1; j<nT-1; j++ )
	        {
	        	v	+= (x + (j-1) * a); 
	        	v1 	 = 1. - v;
	        	k = j*nPts + i;
	        	////////////////
	            pOut[k].x = p0[i].x * v1  + p1[i].x * v;
	            pOut[k].y = p0[i].y * v1  + p1[i].y * v;
	            pOut[k].z = p0[i].z * v1  + p1[i].z * v;
				////////////////////////////////////////
	            pOutWts[k] = pWt0[i] * v1  + pWt1[i] * v;
				////////////////////////////////////////
	        }
		}
	}
 	return nV;
}
////////////////////// end of module /////////////////////

