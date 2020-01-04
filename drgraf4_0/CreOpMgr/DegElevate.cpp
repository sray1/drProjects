// Loft2.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

//////////////////// 
#include "3dMath.h" 

/////////////////////
#include "DegElevate.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_DYNAMIC(CDegElevate,CObject)
/////////////////////////////////////////////////////////////////////////////
CDegElevate::CDegElevate()
{
}

CDegElevate::~CDegElevate()
{
}

int CDegElevate::Elevate_Curve
				(
					pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
					pWORLD pConNew, pDOUBLE pWtsNew,int nSeg_BZ, int nDim
				)
{
	//////////////////////////////////////// Elevate, if necessary
	int m,nBegOld,nBegNew,nDegNew = nDegOld;
	//////////////////////////////////////// Memory
	pWORLD  pConOtem = new WORLD[4];
	pWORLD  pConNtem = new WORLD[4]; 	// reserved for cubic
	pDOUBLE pWtsOtem = new double[4];
	pDOUBLE pWtsNtem = new double[4]; 	// reserved for cubic
	/////////////////////////////// save Ist One
	int nConNew = 0;
	///////////////
	pConNew[0].x = pConOld[0].x; 	
	pConNew[0].y = pConOld[0].y; 	
	pConNew[0].z = pConOld[0].z; 	
	pWtsNew[0]   = pWtsOld[0]; 
	////////
	nConNew++;
	/////////////////////////////////////////////////// Loop Seg_BZ
	for(int nc=0;nc<nSeg_BZ;nc++)
	{
		nBegOld = nc * nDegOld;
		nBegNew = nc * nDegNew;
		///////////////////////////
		for(m=0;m<=nDegOld;m++)
		{
			pConOtem[m] = pConOld[nBegOld+m];
			pWtsOtem[m] = pWtsOld[nBegOld+m];
		}
		/////////////////////////////////////// Go Elevate	
		nDegNew = Elevate_BezSeg(pConOtem, pWtsOtem, nDegOld, nElev,
							pConNtem, pWtsNtem, nDim);
		/////////////////////////////////////// save
		for(m=1;m<=nDegNew;m++)
		{
			nConNew++;
			///////////////
			pConNew[nBegNew+m].x = pConNtem[m].x; 	
			pConNew[nBegNew+m].y = pConNtem[m].y; 	
			pConNew[nBegNew+m].z = pConNtem[m].z; 	
			pWtsNew[nBegNew+m]   = pWtsNtem[m]; 	
		}
	}										
	//////////////////////////////////////// Free Memory
	delete [] pConOtem;
	delete [] pConNtem; 
	delete [] pWtsOtem;
	delete [] pWtsNtem; 
    ///////////////////
    return nConNew;
     
}
				
int CDegElevate::Elevate_BezSeg
				(
					pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
					pWORLD pConNew, pDOUBLE pWtsNew, int nDim
				)
{
	/////////////////////////////////////////////////////////////////////
	//				 since Maximum Degree = 3 ( Cubic), 
	//		nElev can only be:
	//				 0 = No Elevation
	//				 1 = Lin to Quad or Quad to Cubic
	//				 2 = Lin to Quad to Cubic
	/////////////////////////////////////////////////////////////////////
	int nDegNew = nDegOld;				// for no Elevation
	for(int m=0;m<=nDegOld;m++)  		
	{
		pConNew[m] = pConOld[m];
		pWtsNew[m] = pWtsOld[m];
	}	
	////////////////////////////////////// Once
	if(nElev>0)
	{	  
		DegreeElevate(pConOld, pWtsOld, nDegOld, pConNew, pWtsNew, nDim);
		nDegNew++;
	}	
	////////////////////////////////// Twice
	if(nElev>1)
	{	
		DegreeElevate(pConNew, pWtsNew, nDegNew, pConOld, pWtsOld, nDim);
		nDegNew++;
		//////////////////////////////////////
		for(int m=0;m<=nDegNew;m++)
		{
			pConNew[m].x	= pConOld[m].x;		// put it back
			pConNew[m].y	= pConOld[m].y;		// put it back
			pConNew[m].z	= pConOld[m].z;		// put it back
			pWtsNew[m]		= pWtsOld[m];		// put it back
		}
	}
	///////////////
	return nDegNew;
			
}

int CDegElevate::DegreeElevate(pWORLD Con_BZ, pDOUBLE Wts_BZ, int nDegree, 
							 pWORLD NewCon_BZ, pDOUBLE NewWts_BZ, int nDim)
{

	int	i,nNewDeg = nDegree + 1;
	//////////////////////////////
	NewCon_BZ[0].x 	= Con_BZ[0].x;  							  
	NewCon_BZ[0].y 	= Con_BZ[0].y;  							  
	NewCon_BZ[0].z 	= Con_BZ[0].z;
	//////////////////////////////  							  
	if(4 == nDim)					// Rational
		NewWts_BZ[0]	= Wts_BZ[0];
	else	  							  
		NewWts_BZ[0]	= 1.;  							  
	/////////////////////////////
    for(i=1;i<=nDegree;i++)
    {
		double alfa = ((double)i)/((double)nNewDeg);
		double alf1 = 1. - alfa;
		//////////////////////////////
		if(4 == nDim)					// Rational
		{ 
			NewWts_BZ[i]	= 	Wts_BZ[i-1] * alfa + Wts_BZ[i] * alf1;
			//////////////////////////////////////////////////////////  							  
			NewCon_BZ[i].x 	= (	Wts_BZ[i-1] * Con_BZ[i-1].x * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].x * alf1	)/NewWts_BZ[i];  							  
			NewCon_BZ[i].y 	= (	Wts_BZ[i-1] * Con_BZ[i-1].y * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].y * alf1	)/NewWts_BZ[i];  							  
			NewCon_BZ[i].z 	= (	Wts_BZ[i-1] * Con_BZ[i-1].z * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].z * alf1	)/NewWts_BZ[i];
			/////////////////
		}
		else								// Non-Rational
		{	
			//////////////////////////////////////////////////////////  							  
			NewCon_BZ[i].x 	= (	Con_BZ[i-1].x * alfa + 
								Con_BZ[i  ].x * alf1	);  							  
			NewCon_BZ[i].y 	= (	Con_BZ[i-1].y * alfa + 
								Con_BZ[i  ].y * alf1	);  							  
			NewCon_BZ[i].z 	= (	Con_BZ[i-1].z * alfa + 
								Con_BZ[i  ].z * alf1	);
			NewWts_BZ[i]	= 	1.;
			/////////////////
		}			
	}
	/////////////////////////////
	NewCon_BZ[nNewDeg].x 	= Con_BZ[nDegree].x;  							  
	NewCon_BZ[nNewDeg].y 	= Con_BZ[nDegree].y;  							  
	NewCon_BZ[nNewDeg].z 	= Con_BZ[nDegree].z;
	////////////////////////////////////////////  							  
	if(4 == nDim) 
		NewWts_BZ[nNewDeg]	= Wts_BZ[nDegree];  							  
	else
		NewWts_BZ[nNewDeg]	= 1.;
	/////////////////////////////
	return 0;
}											  							  
/////////////////////////////// end of Module ///////////////////////////				
