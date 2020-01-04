// CPat_SubDiv4.cpp : implementation of the CPat_SubDiv4 class
//
	//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_MouseAct.h"
///////////////////
#include "Curve.h"
#include "Pat_SubDiv4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPat_SubDiv4

IMPLEMENT_DYNAMIC(CPat_SubDiv4,CObject)
/*
BEGIN_MESSAGE_MAP(CPat_SubDiv4,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPat_SubDiv4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////////////////////////////
CPat_SubDiv4::CPat_SubDiv4()
{ 
} 
////////////////////////////////////////////////////////////////////////////
int CPat_SubDiv4::SubDivide_U(pWORLD Cons, double u, 
						pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	CCurve Curve;
	int i,j,k;
	/////////////
	// Loop Over Each Row of Controls
	////////////////////////////////////////////////////////////////////
	pWORLD 	OldC_Tem = new WORLD[nOrderU];
	pWORLD 	NewC_Tem = new WORLD[nOrderU];
	///////////////////////////////////
	//Note: left polygon order reversed in Subdivision
	//////////////////////////////////////////////////////////////////// Loop: Rows
	for(j=0;j<nOrderV;j++)	// collect Row
	{
		for(i=0;i<nOrderU;i++)
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
		}
		////////////////////////////////////////////// SubDivide
		nResult = Curve.SubDivide_t(OldC_Tem,u,NewC_Tem,
										bLeft,nOrderU-1);
		////////////////////////////////////////////////// Save
		for(i=0;i<nOrderU;i++)	// collect Row
		{
			k = j*nOrderU + i;
			//////////////////
			NewC[k].x	= NewC_Tem[i].x;
			NewC[k].y	= NewC_Tem[i].y;
			NewC[k].z	= NewC_Tem[i].z;
		}
	}
	///////////////////
	delete [] OldC_Tem;
	delete [] NewC_Tem;
	/////////////////
	return 0; 	
}

int CPat_SubDiv4::SubDivide_V(pWORLD Cons, double v,  
						pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	CCurve Curve;
	int i,j,k;
	/////////////
	// Loop Over Each Col of Controls
	////////////////////////////////////////////////////////////////////
	pWORLD 	OldC_Tem = new WORLD[nOrderU];
	pWORLD 	NewC_Tem = new WORLD[nOrderU];
	///////////////////////////////////
	//Note: left polygon order reversed in Subdivision
	//////////////////////////////////////////////////////////////////// Loop: Cols
	for(i=0;i<nOrderU;i++)
	{
		for(j=0;j<nOrderV;j++)	// collect Col
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
		}
		////////////////////////////////////////////// SubDivide
		nResult = Curve.SubDivide_t(OldC_Tem,v,NewC_Tem,
										bLeft,nOrderV-1);
		////////////////////////////////////////////////// Save
		for(j=0;j<nOrderV;j++)	// collect Col
		{
			NewC[k].x	= NewC_Tem[i].x;
			NewC[k].y	= NewC_Tem[i].y;
			NewC[k].z	= NewC_Tem[i].z;
		}
	}
	///////////////////
	delete [] OldC_Tem;
	delete [] NewC_Tem;
	/////////////////
	return MA_OK; 	
}

int CPat_SubDiv4::SubDivide_UV(pWORLD Cons, double u, double v, 
								pWORLD NewC, BOOL bLeftU, BOOL bLeftV, 
								int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	nResult = SubDivide_U(Cons, u, NewC, bLeftU, nOrderU, nOrderV);
	nResult = SubDivide_V(Cons, v, NewC, bLeftV, nOrderU, nOrderV);
	/////////////////
	return MA_OK; 	
}

int CPat_SubDiv4::Rat_SubDivide_U(pWORLD Cons, pDOUBLE Wts, double u, 
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	CCurve Curve;
	int i,j,k;
	/////////////
	// Loop Over Each Row of Controls
	////////////////////////////////////////////////////////////////////
	pWORLD 	OldC_Tem = new WORLD[nOrderU];
	pDOUBLE OldW_Tem = new double[nOrderU];
	pWORLD 	NewC_Tem = new WORLD[nOrderU];
	pDOUBLE NewW_Tem = new double[nOrderU];
	///////////////////////////////////
	//Note: left polygon order reversed in Subdivision
	//////////////////////////////////////////////////////////////////// Loop: Rows
	for(j=0;j<nOrderV;j++)	// collect Row
	{
		for(i=0;i<nOrderU;i++)
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
			OldW_Tem[i]		= Wts[k];
		}
		////////////////////////////////////////////// SubDivide
		nResult = Curve.Rat_SubDivide_t(OldC_Tem, OldW_Tem, u, 
				NewC_Tem, NewW_Tem, bLeft, nOrderU-1);
		////////////////////////////////////////////////// Save
		for(i=0;i<nOrderU;i++)	// collect Row
		{
			k = j*nOrderU + i;
			//////////////////
			NewC[k].x	= NewC_Tem[i].x;
			NewC[k].y	= NewC_Tem[i].y;
			NewC[k].z	= NewC_Tem[i].z;
			NewW[k]		= NewW_Tem[i];
		}
	}
	///////////////////
	delete [] OldC_Tem;
	delete [] OldW_Tem;
	delete [] NewC_Tem;
	delete [] NewW_Tem;
	/////////////////
	return 0; 	
}

int CPat_SubDiv4::Rat_SubDivide_V(pWORLD Cons, pDOUBLE Wts, double v,  
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	CCurve Curve;
	int i,j,k;
	/////////////
	// Loop Over Each Row of Controls
	////////////////////////////////////////////////////////////////////
	pWORLD 	OldC_Tem = new WORLD[nOrderU];
	pDOUBLE OldW_Tem = new double[nOrderU];
	pWORLD 	NewC_Tem = new WORLD[nOrderU];
	pDOUBLE NewW_Tem = new double[nOrderU];
	///////////////////////////////////
	//Note: left polygon order reversed in Subdivision
	//////////////////////////////////////////////////////////////////// Loop: Cols
	for(i=0;i<nOrderU;i++)
	{
		for(j=0;j<nOrderV;j++)	// collect Col
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
			OldW_Tem[i]		= Wts[k];
		}
		////////////////////////////////////////////// SubDivide
		nResult = Curve.Rat_SubDivide_t(OldC_Tem, OldW_Tem, v, 
				NewC_Tem, NewW_Tem, bLeft, nOrderV-1);
		////////////////////////////////////////////////// Save
		for(j=0;j<nOrderV;j++)	// collect Col
		{
			NewC[k].x	= NewC_Tem[i].x;
			NewC[k].y	= NewC_Tem[i].y;
			NewC[k].z	= NewC_Tem[i].z;
			NewW[k]		= NewW_Tem[i];
		}
	}
	///////////////////
	delete [] OldC_Tem;
	delete [] OldW_Tem;
	delete [] NewC_Tem;
	delete [] NewW_Tem;
	/////////////////
	return MA_OK; 	
}

int CPat_SubDiv4::Rat_SubDivide_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, 
							pWORLD NewC, pDOUBLE NewW, BOOL bLeftU, BOOL bLeftV, 
							int nOrderU, int nOrderV)
{
	int nResult;
	////////////
	nResult = Rat_SubDivide_U(Cons, Wts, u, NewC, NewW, bLeftU, nOrderU, nOrderV);
	nResult = Rat_SubDivide_V(Cons, Wts, v, NewC, NewW, bLeftV, nOrderU, nOrderV);
	/////////////////
	return MA_OK; 	
}
/////////////////////////////////// end of module /////////////////
