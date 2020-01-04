// Twist.cpp : implementation file
//
#include "stdafx.h"
#include "math.h"

//////////////////// 
#include "3dMath.h" 

//#include "drgraf.h"
/////////////////////
//#include "drgradoc.h"
//#include "ObjMgr.h"
//#include "DListMgr.h"
#include "Def_MouseAct.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
/////////////////////
#include "Twist.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define BUFF_SIZE	1024
//////////////////////////////////////////////////////////
/*
	pWORLD pTwistTan_U_00 = new WORLD[4][4];
	CList<WORLD,WORLD>& TwistTanList_V;
	///////////////////////////////////
	if(TwistMethod == TW_ADINI)
	{
		//////////////////////////////////////// Memory
		pWORLD pTwistTan_U = new WORLD[4][4];
		pWORLD pTwistTan_V = new WORLD[4][4];
		////////////////////////////////////////
		nResult = ExtractTwistInfo_Adini(pCurveList_U,pCurveList_V,
						EndTanList_U,EndTanList_V,TwistTanList_U,TwistTanList_V);
		if(nResult == MA_ERROR)
			return nResult;
	}

int CMP_Tensor::ExtractTwistInfo_Adini(CDListMgr* pNodeList,int n_Nodes_U,int n_Nodes_V,
					CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V)
{
	int nResult = MA_OK;
	//////////////////////////////////////////////////////////////////////
	nResult = CreateCurveEndTanList(pCurveList_U,EndTanList_U);
	if(nResult == MA_ERROR)
		return nResult;
	///
	nResult = CreateCurveEndTanList(pCurveList_V,EndTanList_V);
	//////////////////////////////////////////////////////////////////////
	return nResult;
}

int CMP_Tensor::ExtractFromEndTanList_Adini_U(
				CList<WORLD,WORLD>& EndTanList,CList<WORLD,WORLD>& TwistTanList)
{
	int nResult = MA_OK;
	////////////////////////////////////////////////////////////////////// 
	// Total of:
	//		16 tangents(4Curves x 4Tangents/Curve)
	// Only First 2 Curves & Last 2 Curves need to be considered
	//////////////////////////////////////////////////////////////////////			
	POSITION	pos;
	int			i,nConBZ,index;
	/////////////
	return MA_OK;
}
	//////////////////////////////////////////////////////////////////////
	// Corner Twist saved as:
	//
	//		 ^		Tw10		Tw11
	//	v-dir|		Tw00		Tw01
	//					u-dir --->
	/////////////////////////////////////////////////////////// TwistTanList,if Needed
	pWORLD pTwistTan_U_00 = new WORLD[4][4];
	CList<WORLD,WORLD>& TwistTanList_V;
	///////////////////////////////////
	if(TwistMethod == TW_ADINI)
	{
		//////////////////////////////////////// Memory
		pWORLD pTwistTan_U = new WORLD[4][4];
		pWORLD pTwistTan_V = new WORLD[4][4];
		////////////////////////////////////////
		nResult = ExtractTwistInfo_Adini(pCurveList_U,pCurveList_V,
						EndTanList_U,EndTanList_V,TwistTanList_U,TwistTanList_V);
		if(nResult == MA_ERROR)
			return nResult;
	}


#include "stdafx.h"
#include "math.h"

//////////////////// 
#include "3dMath.h" 

/////////////////////
#include "Twist.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
*/
////////////////////////////////////
IMPLEMENT_DYNAMIC(CTwist,CObject)
/////////////////////////////////////////////////////////////////////////////
CTwist::CTwist()
{
}

CTwist::~CTwist()
{
}

int CTwist::Zero(PWMAT2 CornerTwist)
{
	C3DMath	Math3D;
	WORLD	w0;
	int i,j;
	////////
	Math3D.Set3DPts(&w0,0.,0.,0.);
	////////////////////////////// Copy zero Twist
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			CornerTwist[i][j].x = w0.x;
			CornerTwist[i][j].y = w0.y;
			CornerTwist[i][j].z = w0.z;
		}
	}
	//////////////////////////////
	return MA_OK;
}

int CTwist::Bessel(CDListMgr* pNodeList,CList<double,double>* pWtList,
				   int nNodes_U,int nNodes_V,PWMAT2 CornerTwist)
{
	// M = nNodes_U / N = nNodes_V 
	/////////////////////////////////////////////////////////////////////
	// Bessel:Bi-linear Surface made up of 4 Patches
	//		Twist_uv = for each Patch 
	//					[-1  1]		[ Q_00		Q_01 ]	{-1
	//								[ Q_10		Q_11 ]	  1 }
	//				 = Q_00 - Q_10 - Q_01 + Q_11
	// NOTE:	EACH PATCH CORNERS HAVE SAME TWIST VECTOR
	//////////////////////////////////////////////////////////// Corner_00
	//		Twist_00 = Q_00 - Q_10 - Q_01 + Q_11 
	//////////////////////////////////////////////////////////// Corner_0N
	//		Twist_0N = Q_0N - Q_1N - Q_0(N-1) + Q_1(N-1) 
	//////////////////////////////////////////////////////////// Corner_10
	//		Twist_M0 = Q_M0 - Q_(M-1)0 - Q_(M-1)1 + Q_M1 
	//////////////////////////////////////////////////////////// Corner_MN
	//		Twist_MN = Q_MN - Q_(M-1)N - Q_M(N-1) + Q_(M-1)(N-1) 
	//////////////////////////////////////////////////////////////////////
	WORLD		wQ1,wQ2,wQ3,wQ4;
	double		Wt1,Wt2,Wt3,Wt4,Wt,rWt;
	int			index;
	POSITION	pos,posW;
	CDrNode*	pNode;
	////////////////////////////
	int M = nNodes_U;
	int N = nNodes_V;
	//////////////////////////////////////////////////////////// Twist_00
	////////////////////////////////////////// wQ1 = Q_00
	index	= 0;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ1		= *(pNode->GetLocalPos());
	//
	posW	= pWtList->FindIndex(index);
	Wt1		= pWtList->GetAt(pos);
	////////////////////////////////////////// wQ2 = Q_01
	index++;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ2		= *(pNode->GetLocalPos());
	//
	posW	= pWtList->FindIndex(index);
	Wt2		= pWtList->GetAt(pos);
	////////////////////////////////////////// wQ3 = Q_10 
	index	= M;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ3		= *(pNode->GetLocalPos());
	//
	posW	= pWtList->FindIndex(index);
	Wt3		= pWtList->GetAt(pos);
	////////////////////////////////////////// wQ4 = Q_11
	index++;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ4		= *(pNode->GetLocalPos());
	//
	posW	= pWtList->FindIndex(index);
	Wt4		= pWtList->GetAt(pos);
	////////////////////////////////////////// Twist
	Wt		= Wt1 - Wt2 - Wt3 + Wt4;
	rWt		= 1.0/Wt;
	/////////////////
	CornerTwist[0][0].x = ((Wt1*wQ1.x) - (Wt2*wQ2.x) - (Wt3*wQ3.x) + (Wt4*wQ4.x))*rWt;
	CornerTwist[0][0].y = ((Wt1*wQ1.y) - (Wt2*wQ2.y) - (Wt3*wQ3.y) + (Wt4*wQ4.y))*rWt;
	CornerTwist[0][0].z = ((Wt1*wQ1.z) - (Wt2*wQ2.z) - (Wt3*wQ3.z) + (Wt4*wQ4.z))*rWt;
	//////////////////////////////////////////////////////////// Twist_M0
	////////////////////////////////////////// wQ1 = Q_00
	index	= M-1;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ1		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ2 = Q_01
	index--;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ2		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ3 = Q_10 
	index	= 2*M - 1;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ3		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ4 = Q_11
	index--;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ4		= *(pNode->GetLocalPos());
	////////////////////////////////////////// Twist
	Wt		= Wt1 - Wt2 - Wt3 + Wt4;
	rWt		= 1.0/Wt;
	/////////////////
	CornerTwist[1][0].x = ((Wt1*wQ1.x) - (Wt2*wQ2.x) - (Wt3*wQ3.x) + (Wt4*wQ4.x))*rWt;
	CornerTwist[1][0].y = ((Wt1*wQ1.y) - (Wt2*wQ2.y) - (Wt3*wQ3.y) + (Wt4*wQ4.y))*rWt;
	CornerTwist[1][0].z = ((Wt1*wQ1.z) - (Wt2*wQ2.z) - (Wt3*wQ3.z) + (Wt4*wQ4.z))*rWt;
	//////////////////////////////////////////////////////////// Twist_0N
	////////////////////////////////////////// wQ1 = Q_00
	index	= (N-1)*M;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ1		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ2 = Q_01
	index++;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ2		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ3 = Q_10 
	index	= (N-2)*M;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ3		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ4 = Q_11
	index++;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ4		= *(pNode->GetLocalPos());
	////////////////////////////////////////// Twist
	Wt		= Wt1 - Wt2 - Wt3 + Wt4;
	rWt		= 1.0/Wt;
	/////////////////
	CornerTwist[0][1].x = ((Wt1*wQ1.x) - (Wt2*wQ2.x) - (Wt3*wQ3.x) + (Wt4*wQ4.x))*rWt;
	CornerTwist[0][1].y = ((Wt1*wQ1.y) - (Wt2*wQ2.y) - (Wt3*wQ3.y) + (Wt4*wQ4.y))*rWt;
	CornerTwist[0][1].z = ((Wt1*wQ1.z) - (Wt2*wQ2.z) - (Wt3*wQ3.z) + (Wt4*wQ4.z))*rWt;
	//////////////////////////////////////////////////////////// Twist_MN
	////////////////////////////////////////// wQ1 = Q_00
	index	= N*M - 1;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ1		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ2 = Q_01
	index--;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ2		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ3 = Q_10 
	index	= (N-1)*M - 1;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ3		= *(pNode->GetLocalPos());
	////////////////////////////////////////// wQ4 = Q_11
	index--;
	pos		= pNodeList->FindIndex(index);
	pNode	= (CDrNode*)pNodeList->GetAt(pos);
	wQ4		= *(pNode->GetLocalPos());
	////////////////////////////////////////// Twist
	Wt		= Wt1 - Wt2 - Wt3 + Wt4;
	rWt		= 1.0/Wt;
	/////////////////
	CornerTwist[1][1].x = ((Wt1*wQ1.x) - (Wt2*wQ2.x) - (Wt3*wQ3.x) + (Wt4*wQ4.x))*rWt;
	CornerTwist[1][1].y = ((Wt1*wQ1.y) - (Wt2*wQ2.y) - (Wt3*wQ3.y) + (Wt4*wQ4.y))*rWt;
	CornerTwist[1][1].z = ((Wt1*wQ1.z) - (Wt2*wQ2.z) - (Wt3*wQ3.z) + (Wt4*wQ4.z))*rWt;
	///////////////////////////
	return MA_OK;
}
int CTwist::Adini
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist,
				CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V
			)
{
	AfxMessageBox("ERROR: Adini TWIST\nNOT IMPLEMENTED YET");
	return MA_ERROR;
}

int CTwist::Spline
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist,
				CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V
			)		
{
	AfxMessageBox("ERROR: Spline TWIST\nNOT  IMPLEMENTED YET");
	return MA_ERROR;
}

int CTwist::Energy
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist
			)		

{
	AfxMessageBox("ERROR: Energy TWIST\nNOTIMPLEMENTED YET");
	return MA_ERROR;
}
/////////////////////////////// end of Module ///////////////////////////				
