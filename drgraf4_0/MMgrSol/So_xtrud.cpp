// CSO_Xtrud.cpp : implementation of the CSO_Xtrud class
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
#include "SO_Xtrud.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSO_Xtrud

IMPLEMENT_DYNAMIC(CSO_Xtrud,CObject)
//////////////////////////////////////////////
int CSO_Xtrud::ExtrudePatch
	(
		double	depth,	//	distance to the extended solid's end
		WORLD	v,		//	unit extrusion vector (direction)
		int		nPts,	//	number of input data points in ST_direction
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
	//////////////////////////////////////////////////////////
	if( pOut ) 
	{
		C3DMath		Math3D;
		///////////////////
		sizeRow		= nPts*sizeof(WORLD);
		sizeRowWt	= nPts*sizeof(double);
		nS 			= 2;
		nV 			= nPts*nS;
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
			for( p=pRow,j=0;j<nPts;j++,p++ )
			{
				///////////////////////////////// 
				GetAPtByExtrusion(p, v, depth);
				/////////////////////////////////
			}
		}
	}
 	return nV;
}

pWORLD CSO_Xtrud::GetAPtByExtrusion(pWORLD pDOld, WORLD dir, double depth)
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
