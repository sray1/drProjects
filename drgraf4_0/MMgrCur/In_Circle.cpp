// Mouse.cpp : implementation file
//
/////////////////////////////////////////////////////////
//		R A T I O N A L  B E Z I E R  C I R C L E 
/////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "math.h"

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
/////////////////////
#include "Def_Type.h"
#include "Def_CuPS.h"
/////////////////////
#include "3DMath.h" 
#include "XForm.h" 
/////////////////////
#include "In_Circle.h" 

#ifdef _DEBUG
#include <stdio.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
IMPLEMENT_SERIAL(CIn_Circle,CIn_Conics,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2        
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CIn_Circle::CIn_Circle()
{
}

CIn_Circle::~CIn_Circle()
{
}
///////////////////////////////////////////////////////////////////////////////////// Interpolation
	//////////////////////////////////////////////////////////////////////////////
	//	NOTE:  BackGround:	k = Order; k-1 = Degree of Curve [ k=3 for Conics]	//
	//																			//
///////////////////////////////////////////////////////////////////////////////////////////////	
int CIn_Circle::Prepare()
{
	m_pInCon_BZ_S	= new WORLD[m_nSeg_DT_S];	// temporary In-between bezier pts
	m_pInWts_BZ_S	= new double[m_nSeg_DT_S];	// temporary In-between bezier wts
	////////////////////////////////////////////// Compute In-between
	Compute_InBetweens(m_pData,m_Center,m_Radius,m_pInCon_BZ_S,m_pInWts_BZ_S,
													m_nSeg_DT_S,m_bClosed_S);
	/////////
	return 0;
}

int CIn_Circle::Compute_InBetweens(pWORLD Data,WORLD Center,double Radius,
								   pWORLD Con,pDOUBLE Wts,int L,BOOL bClosed)
{
	// nData = L + 1; // for close circle nData = L
	/////////////////////////////////
	for(int k=0;k<L-1;k++)
		Compute_b1_w1(Center,Data[k],Data[k+1],Radius,&(Con[k]),&(Wts[k]) );
	///
	Compute_b1_w1(Center,Data[L-1],Data[(bClosed)?0:L],Radius,&(Con[k]),&(Wts[k]) );
	/////////////
	return 0;
}
								 
int CIn_Circle::Compute_b1_w1(WORLD Center,WORLD b0,WORLD b2,double Rad,
									pWORLD pb1,pDOUBLE pw1)
{

	// To find:
	//		b1	= Bezier In-Betwen Pt.
	//			= Intersection of Tangents at b0 and b2
	// and
	//		w1	= Weight at b1 = cos(alfa)
	//////////////////////////////////////////////////////// MidPt of Chord
	double w1;
	WORLD Rm;
	////////////
	Rm.x = .5 * (b0.x + b2.x);
	Rm.y = .5 * (b0.y + b2.y);
	Rm.z = .5 * (b0.z + b2.z);
	//////////////////////////////////////////////////////// normal
	WORLD N;
	//////////
	N.x = Rm.x - Center.x;									
	N.y = Rm.y - Center.y;									
	N.z = Rm.z - Center.z;
	double Base = sqrt(N.x*N.x + N.y*N.y + N.z*N.z );
	//////////////////////////////////////////////////////// Weight = cos(alfa) 
	w1 = Base/Rad;
	//////////////////////////////////////////////////////// Bezier In-Between Pt
	//////////////////////////////// Unit Normal 
	Base = 1./Base;
	N.x *= Base;									
	N.y *= Base;									
	N.z *= Base;
	////////////// Rad/cos(alfa) = length from center to b1
	Base = Rad/w1;
	////////////////////////////////
	pb1->x 	= Center.x + Base * N.x; 
	pb1->y 	= Center.y + Base * N.y; 
	pb1->z 	= Center.z + Base * N.z;
	*pw1	= w1; 
	//////////////////////////////
	return 0;
	
}

int CIn_Circle::Interpolate()
{
	////////////////////////////////////////////////////////////////////////  Cons/Wts
	m_pWts_BS_S	= new double[m_nCon_BS_S];		
	m_pCon_BS_S	= new WORLD [m_nCon_BS_S];
	m_pWts_BZ_S	= new double[m_nCon_BZ_S];
	m_pCon_BZ_S	= new WORLD [m_nCon_BZ_S];
	///////////
	if(!m_pWts_BS_S || !m_pCon_BS_S || !m_pWts_BZ_S || !m_pCon_BZ_S )
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	//////////////////////////////////////////////////////////////// FillUp 
	FillUpBezier(m_pData,m_pCon_BZ_S,m_pWts_BZ_S,m_pInCon_BZ_S,m_pInWts_BZ_S,
											m_nCon_BZ_S, m_nSeg_DT_S, m_bClosed_S);
	//////////// 							 
// 	FillUpSpline(m_pCon_BZ_S, m_pWts_BZ_S,m_nCon_BZ_S,
//	 			 m_pCon_BS_S, m_pWts_BS_S,m_nCon_BS_S, m_nSeg_DT_S, m_bClosed_S);
	////////////////////////////// release memory
	if(m_pInCon_BZ_S)
	{
		delete m_pInCon_BZ_S;	// Temp.tween bezier pts
		m_pInCon_BZ_S = NULL;
	}	
	if(m_pInWts_BZ_S)
	{
		delete m_pInWts_BZ_S;	// Temp.tween bezier wts
		m_pInWts_BZ_S = NULL;
	}
/*
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}
	if(m_pDat_Ex)
	{
		delete [] m_pDat_Ex;
		m_pDat_Ex = NULL;
	}
*/	
	////////////////
	return 0;
}		
	 					   	 
void CIn_Circle::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CIn_Circle:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CIn_Circle:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////
