// CPA_Loft4.cpp : implementation of the CPA_Loft4 class
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
#include "PA_Loft4.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_Loft4

IMPLEMENT_DYNAMIC(CPA_Loft4,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_Loft4,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_Loft4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPA_Loft4::LoftProfiles
// Input Data Points Should be ALREADY TRANSFORMED in calling Routine
	(
		short	segs,	//	subdivision value (interior spaces)
		double	rat,	//  Output Last/Ist ratio in T_Direction
		short	nPts,	//	number of input data points
		pWORLD	p0,		//	input data point array for start curve
		pWORLD	p2,		//	input data point array for end curve
		pWORLD	p1,		//	input data point array for start curve
		pWORLD	p3,		//	input data point array for end curve
		pWORLD 	pOut	//	Output Pts array
	)	  
//Return:Int	nOut	//	number of points emitted
{
	pWORLD	pRow;
	double	v,v1;
	int		nV,nT,i,j,k;
	long	sizeRow;
	/////////////////////////////////////////////////////////
	// NOTE:	allows Unequal Lofting
	//		SPACEs between pts. are:
	//			x, x+a, x+2a, x+3a, ..., x+na
	//		with
	//			x = (2*depth)/(segs*(rat+1))		: depth = 1.0
	//			a = (x*(rat-1))/(segs-1)
	//
	//////////////////////////////////////////////////////////
	double x,a,depth=1.0;
	if( pOut ) 
	{
		C3DMath		Math3D;
		///////////////////
		sizeRow = nPts*sizeof(WORLD);
		nT = segs+1;
		nV = nPts*nT;
		///////
		pRow=pOut; 
		Math3D.BlockCopy( (HUGEBLK)p0, (HUGEBLK)pRow, sizeRow );
		pRow += nPts*(nT-1); 
		Math3D.BlockCopy( (HUGEBLK)p1, (HUGEBLK)pRow, sizeRow );
		/////////////////////////////
		x 		= (2 * depth)/(segs * (rat + 1));
		a 		= (x * (rat-1))/(segs-1);
		////////////////////////////////
	    for( i = 0; i<nPts; i++ )
	        for( j = 1; j<nT-1; j++ )
	        {
	        	v	+= (x + j * a); 
	        	v1 	 = 1. - v;
	        	k = j*nPts + i;
	        	////////////////
	            pOut[k].x = p0[i].x * v1  + p1[i].x * v;
	            pOut[k].y = p0[i].y * v1  + p1[i].y * v;
	            pOut[k].z = p0[i].z * v1  + p1[i].z * v;
	        }
	}
 	return nV;
}
////////////////////// end of module /////////////////////

