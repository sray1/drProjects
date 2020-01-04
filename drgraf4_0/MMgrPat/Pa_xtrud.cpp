// CPa_Xtrud.cpp : implementation of the CPA_Xtrud class
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
#include "PA_Xtrud.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_Xtrud

IMPLEMENT_DYNAMIC(CPA_Xtrud,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_Xtrud,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_Xtrud)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPA_Xtrud::ExtrudeCurve
	(
		double	depth,	//	distance to the extended surface's end
		WORLD	v,		//	unit extrusion vector (direction)
		int		segs,	//	# of Elements in T-dirction
		double	ratio,	//  Output Last/Ist ratioio in T_Direction
		int		nPts,	//	number of input data points in S_direction
		pWORLD	pPt,	//	input data point array
		pDOUBLE	pWt,	//	input data Weight array
		pWORLD	pOut,	//	Output Pts array
		pDOUBLE	pOutWts //	Output Wts array
	)	  
{
	pWORLD	pRow,p;
	pDOUBLE pRowWt;
	double	inc = 0;		// initialize
	int		nV,nS,i,j;
	long	sizeRow,sizeRowWt;
	////////////////////////////////////
	// NOTE:	allows Unequal Extrusion
	//		# of segments = n + 1;
	//		SPACEs between pts. are:
	//			x, x+a, x+2a, x+3a, ..., x+na
	//		with
	//			x = (2*depth)/(segs*(rat+1))
	//			a = (x*(rat-1))/(segs-1)
	//
	//////////////////////////////////////////////////////////
	double x,a;
	if( pOut ) 
	{
		C3DMath		Math3D;
		///////////////////
		sizeRow		= nPts*sizeof(WORLD);
		sizeRowWt	= nPts*sizeof(double);
		nS 			= segs+1;
		nV 			= nPts*nS;
		////////////////
		x 			= (2 * depth)/(segs * (ratio + 1));
		a 			= (segs == 1)?0.:(x * (ratio-1))/(segs-1);
		/////////////////////////////////////////
		pRow=pOut; 
		Math3D.BlockCopy( (HUGEBLK)pPt, (HUGEBLK)pRow, sizeRow );
		pRowWt=pOutWts; 
		Math3D.BlockCopy( (HUGEBLK)pWt, (HUGEBLK)pRowWt, sizeRowWt );
		////////////////
		for( pRow+=nPts,pRowWt+=nPts,i=1;i<nS;i++,pRow+=nPts,pRowWt+=nPts ) 
		{
			Math3D.BlockCopy( (HUGEBLK)pPt, (HUGEBLK)pRow, sizeRow );
			Math3D.BlockCopy( (HUGEBLK)pWt, (HUGEBLK)pRowWt, sizeRowWt );
			////////////////
			inc += (x + (i-1) * a);
			////////////////
			for( p=pRow,j=0;j<nPts;j++,p++ )
			{
				///////////////////////////////// 
				GetAPtByExtrusion(p, v, inc);
				/////////////////////////////////
			}
		}
	}
 	return nV;
}

pWORLD CPA_Xtrud::GetAPtByExtrusion(pWORLD pDOld, WORLD dir, double depth)
{

	WORLD DNew;
	pWORLD pDNew = &DNew;
    /////////////////////
	pDNew->x = pDOld->x + depth * (dir.x);
	pDNew->y = pDOld->y + depth * (dir.y);
	pDNew->z = pDOld->z + depth * (dir.z);
    /////////////////////
	pDOld->x = pDNew->x;
	pDOld->y = pDNew->y;
	pDOld->z = pDNew->z;
    /////
	return pDNew;
}	
////////////////////////////////////////// end of module //////////////////
