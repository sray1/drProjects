// Mouse.cpp : implementation file
//
/////////////////////////////////////////////////////////
//		R A T I O N A L  B E Z I E R  P A R A B O L A 
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
#include "In_Parab.h" 

#ifdef _DEBUG
#include <stdio.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
IMPLEMENT_SERIAL(CIn_Parab,CIn_Conics,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2        
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CIn_Parab::CIn_Parab()
{
	/////////////////// Memory
	m_MemErr	= 0;
	m_pWts_BS_S	= NULL;
	m_pWts_BZ_S	= NULL;
	m_pData		= NULL;
	m_pDat_Ex	= NULL;
	m_pCon_BS_S	= NULL;
	m_pCon_BZ_S	= NULL;
}

CIn_Parab::~CIn_Parab()
{
	/////////////////// Memory
	if(m_MemErr<0)
	{
		if(m_pWts_BS_S)
			delete [] m_pWts_BS_S; 
		if(m_pWts_BZ_S)
			delete [] m_pWts_BZ_S; 
		if(m_pData)
			delete [] m_pData; 
		if(m_pDat_Ex)
			delete [] m_pDat_Ex; 
		if(m_pCon_BS_S)
			delete [] m_pCon_BS_S; 
		if(m_pCon_BZ_S)
			delete [] m_pCon_BZ_S;
	}	
}
///////////////////////////////////////////////////////////////////////////////////// Interpolation
	//////////////////////////////////////////////////////////////////////////////
	//	NOTE:  BackGround:	k = Order; k-1 = Degree of Curve [ k=3 for Conics]	//
	//																			//
///////////////////////////////////////////////////////////////////////////////////////////////	
int CIn_Parab::Prepare()
{
	m_pInCon_BZ_S	= new WORLD[m_nSeg_DT_S];	// temporary In-between bezier pts
	m_pInWts_BZ_S	= new double[m_nSeg_DT_S];	// temporary In-between bezier wts
	////////////////////////////////////////////// Compute In-between
	Compute_InBetweens(m_pData,m_pInCon_BZ_S,m_pInWts_BZ_S,m_nSeg_DT_S);
	/////////
	return 0;
}

int CIn_Parab::Compute_InBetweens(pWORLD Data,pWORLD Con,pDOUBLE Wts,int L)
{
	// nData = L + 1; // parabola is never closed,for closecircle for example nData = L
	// for parabola L = 2 with (b0,pt(shoulder pt)) & (pt,b2)
	///////////////////////////////////////////////////////// get global b1
	// w1	= ratio(m,pt,b1) = 1 for parabola
	// m	= (b0+b2)/2
	// pt	= shoulder point = c(1/2)
	/////////////////////////////////
	WORLD m,b0,b1,b2,pt,tem;
	double dTem;
	C3DMath Math3D;
	b0 = Data[0];
	pt = Data[1];
	b2 = Data[2];
	/////////////////////////////// b1
	Math3D.Add3DPts(&b0,&b2,&m);
	Math3D.Scale3DPts(.5,&m);
	Math3D.Sub3DPts(&pt,&m,&tem);
	dTem = Math3D.Len3DPts(&tem);
	Math3D.Normalize(&tem,&tem);
	Math3D.Scale3DPts(2*dTem,&tem);
	Math3D.Add3DPts(&m,&tem,&b1);
	///////////////////////////////////////////////////////// bary Coords 
	WORLD BCC;
	FindBaryfor3rdPt(b0,b1,b2,pt,&BCC);
	///////////////////////////////////////////////////////// subdivide
	WORLD b01,b11;
	double w1L,w1R;
	Rat_Subdivide_Conic(b0,b1,b2,pt,BCC,&b01,&w1L,&b11,&w1R);
	///////////////////////////////////////////////////////// save
	Con[0] = b01;
	Con[1] = b11;
	//
	Wts[0] = w1L;
	Wts[1] = w1R;
	/////////////
	return 0;
}

int CIn_Parab::Interpolate()
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
	m_pDat_Ex = m_pData;
	////////////////////
	FillUpBezier(m_pDat_Ex,m_pCon_BZ_S,m_pWts_BZ_S,m_pInCon_BZ_S,m_pInWts_BZ_S,
											m_nCon_BZ_S, m_nSeg_DT_S, FALSE);
	//////////// 							 
 	FillUpSpline(m_pCon_BZ_S, m_pWts_BZ_S,m_nCon_BZ_S,
	 			 m_pCon_BS_S, m_pWts_BS_S,m_nCon_BS_S, m_nSeg_DT_S, FALSE);
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
	 					   	 
void CIn_Parab::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CIn_Parab:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CIn_Parab:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////
