// CSurface3.cpp : implementation of the CSurface3 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct
#include <afxtempl.h>	// CList

#include "3DMath.h"
/////////////////////
#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "Triangle.h"

#include "Surface3.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSurface3

IMPLEMENT_DYNAMIC(CSurface3,CObject)
/*
BEGIN_MESSAGE_MAP(CSurface3,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CSurface3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024

#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)
//////////////////////////////////////////////
CSurface3::CSurface3()
{ 

} 
////////////////////////////////////////////////////////////////////////////////////////////
//	Definition:
//					D = degree [ eg. 1 = Linear / 2 = Quadratic / 3 = Cubic ] 
//					N = Order = degree + 1
//					
//					TN= Triangle Number = Number of Total Vertices
//										= (D+1)*(D+2)/2 
//										= (N)*(N+1)/2
//						eg. for:
//								(N=2)Linear		--->	TN = 3  
//								(N=3)Quad		--->	TN = 6  
//								(N=4)Cubic		--->	TN = 10, etc.
//	NOTE:
//					i + j + k = N
//					so, Given i,j,N ---> k is fixed; so is the vertex
///////////////////////////////////////////////////////////////////////  
//	STORAGE MAP:
//
//					(LI)Linear Index of a Vertex at (i,j):
//					
//						LI = BARY2LIN_PT(i,j,N)
//
///////////////////////////////////////////////////////////////////////
//		LINEAR:
//
//						   u=0
//							|						  	
//							|
//				  (P2) Q010	o
//							| \
//							|   \ w=0		
//							|     \
//							|       \
//				  (P3) Q001	o--------o Q100 -----  v=0 --		
//									   (P1)
//						  1	o
//							| \
//							|   \		
//							|     \
//							|       \
//						  0	o--------o 2	
//
///////////////////////////////////////////////////////////////////////
//		QUADRATIC:
//
//						   u=0
//							|						  	
//							|
//				  (P2) Q020	o
//							| \
//							|   \ w=0		
//							|     \
//							|       \
//					   Q010	o---------o Q110
//							| \		  | \
//							|   \     |	  \	w=0		
//							|     \   |	    \
//							|       \ |       \
//				  (P3) Q002	o---------o--------o Q200 -----  v=0 --		
//									Q101		 (P1)
//						  2	o 
//							| \
//							|   \ w=0		
//							|     \
//							|       \
//						  1	o---------o 4
//							| \		  | \
//							|   \     |	  \	w=0		
//							|     \   |	    \
//							|       \ |       \
//							o---------o--------o  -----  v=0 --	
//							0         3        5	
//
///////////////////////////////////////////////////////////////////////	
//		CUBIC:
//
//						   u=0
//							|						  	
//							|
//				  (P2) Q030	o
//							| \
//							|   \ w=0		
//							|     \
//							|       \
//					   Q021	o---------o Q120
//							| \		  | \
//							|   \     |	  \	w=0		
//							|     \   |	    \
//							|       \ |Q111   \
//					   Q012	o---------o---------o Q210
//							| \		  | \       | \
//							|   \     |	  \	    |   \ w=0		
//							|     \   |	    \   |     \
//							|       \ |       \ |       \
//				  (P3) Q003	o---------o---------o-------- o Q300 -----  v=0 --		
//									Q102	  Q201		    (P1)
//						 3	o 
//							| \
//							|   \ w=0		
//							|     \
//							|       \
//					      2	o---------o 6
//							| \		  | \
//							|   \     |	  \	w=0		
//							|     \   |	    \
//							|       \ |5      \
//					      1	o---------o---------o 8
//							| \		  | \       | \
//							|   \     |	  \	    |   \ w=0		
//							|     \   |	    \   |     \
//							|       \ |       \ |       \
//							o---------o---------o-------- o  -----  v=0 --		
//							0		  4	        7		  9
//
///////////////////////////////////////////////////////////////////////	
int CSurface3::HO_GetAPointOnABezSegPatch		// RATIONAL BEZIER Patches
			(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	CTriangle*	pTriCur
				,	double		uCur
				,	double		vCur
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut	//  Output Point
				,	pDOUBLE		pOutWt	//  Output Wt (WE MAY NEED FOR RATIONAL SOLIDS)
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface3::MakePatches");
		AfxMessageBox(*str);
		///////////////////
		int j,m;
	    ///////////////////
		j = sprintf(buf,"pCon_UV[%d] and pWts_UV[%d]:\n",nCon,nCon);
		for(m=0;m<nCon;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f    %7.2f \n", m, 
					pCon_UV[m].x, pCon_UV[m].y, pCon_UV[m].z, pWts_UV[m] );
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif
	int nResult = MA_OK;			
//////////////////////////////////////////////////////////////////
	if(pTriList->IsEmpty() )
		return -1;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		////////////////////
		if(pTri != pTriCur)
			continue;
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int	nDegree		= pTri->GetDegree();			// Overall Degree of Triangle
		/////////////////////////////////////
		int	TriNum		= (nDegree+1)*(nDegree+2)/2;	//  Triangle Number 
		////////////////////////////////////////////
		CList<int,int>* pCNIndexList = pTri->GetCNIndexList();
		int nConTri		= pCNIndexList->GetCount();
		if (nConTri != TriNum)
		{
			AfxMessageBox("ERROR:\nCSurface3::MakePatches\nnCon != TriNum");
			return -1;
		}
		///////////
		pWORLD pCon		= new WORLD[nConTri];
		pDOUBLE pWts	= new double[nConTri];
		/////////////////////////////////////////////////////////////////// Each Triangle
		int i = -1;
		for (POSITION posI = pCNIndexList->GetHeadPosition( );posI !=NULL;)
		{
			int index = pCNIndexList->GetNext(posI); 
    		///////////////////////////////
			i++;
			////
			pCon[i].x	= pCon_UV[index].x;	  
			pCon[i].y	= pCon_UV[index].y;  
			pCon[i].z	= pCon_UV[index].z;
			pWts[i]		= pWts_UV[index];
		}
		//////////////////////////////////// Go Make a Triangular Patch
		nResult = HO_GenerateAPointOnASingleBezPatch(nDegree,nDim,TriNum,
								uCur,vCur,pWts,pCon,pOut,pOutWt);
		//////////////////
		delete [] pCon;
		delete [] pWts;
	}										///////////////////////////// end LIST
	//////////////////
	return nResult;
	////////////
}

int CSurface3::HO_GenerateAPointOnASingleBezPatch
			(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////
				,	double		u		//  output pt		
				,	double		v		//  output pt		
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	pWORLD		pOut		// 	Total Output Global Points Array
				,	pDOUBLE		pOutWt		// 	Total Output Global Wts Array
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface3::EX_Make_A_Patch");
		AfxMessageBox(*str);
		///////////////////
		int j,m;
	    ///////////////////
		j = sprintf(buf,"pCon[%d] and pWts[%d]:\n",TriNum,TriNum);
		for(m=0;m<TriNum;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f    %7.2f \n", m, 
					pCon[m].x, pCon[m].y, pCon[m].z, pWts[m] );
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	if(nDegree == 1)
		Linear(pCon, pWts, u, v, pOut, pOutWt);
	else
	if(nDegree == 2)
		Quadratic(pCon, pWts, u, v, pOut, pOutWt);
	else
	if(nDegree == 3)
		Cubic(pCon, pWts, u, v, pOut, pOutWt);
	//////////////////
	return MA_OK;
}

int CSurface3::EX_MakePatches		// RATIONAL BEZIER Patches
			(
					int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////  Globals:
				,	int			nOutGlo_S	//  Total Output in each side of entire Patch 
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Points Array
				,	pDOUBLE		pOutWts_UV	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface3::MakePatches");
		AfxMessageBox(*str);
		///////////////////
		int j,m;
	    ///////////////////
		j = sprintf(buf,"pCon_UV[%d] and pWts_UV[%d]:\n",nCon,nCon);
		for(m=0;m<nCon;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f    %7.2f \n", m, 
					pCon_UV[m].x, pCon_UV[m].y, pCon_UV[m].z, pWts_UV[m] );
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	if(pTriList->IsEmpty() )
		return -1;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So
	////////////////////////
	int nTot,nEmit,nOutP,nOut=0;				
	nEmit	= (nOutSeg+1)*(nOutSeg+2)/2;	// No. of Output for each Triangle	
	nTot	= nTriangle * nEmit;			// Total No. of Outputs	
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	pWORLD p	= pOut_UV;
	pDOUBLE pW	= pOutWts_UV;
	/////////////////////////
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int	nDegree		= pTri->GetDegree();			// Overall Degree of Triangle
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////
		int	TriNum		= (nDegree+1)*(nDegree+2)/2;	//  Triangle Number 
		////////////////////////////////////////////
		CList<int,int>* pCNIndexList = pTri->GetCNIndexList();
		int nConTri		= pCNIndexList->GetCount();
		if (nConTri != TriNum)
		{
			AfxMessageBox("ERROR:\nCSurface3::MakePatches\nnCon != TriNum");
			return -1;
		}
		///////////
		pWORLD pCon		= new WORLD[nConTri];
		pDOUBLE pWts	= new double[nConTri];
		/////////////////////////////////////////////////////////////////// Each Triangle
		int i = -1;
		for (POSITION posI = pCNIndexList->GetHeadPosition( );posI !=NULL;)
		{
			int index = pCNIndexList->GetNext(posI); 
    		///////////////////////////////
			i++;
			////
			pCon[i].x	= pCon_UV[index].x;	  
			pCon[i].y	= pCon_UV[index].y;  
			pCon[i].z	= pCon_UV[index].z;
			pWts[i]		= pWts_UV[index];
		}
		//////////////////////////////////// Go Make a Triangular Patch
		nOutP = EX_Make_A_Patch(nDegree,nDim,nOutSeg,TriNum,
								nType,nOutGlo_S,iOutGlo,jOutGlo,
								pWts,pCon,pOut_UV,pOutWts_UV);
		///////////////////				
		if (nOutP <0)
		{
			//////////////////
			delete [] pCon;
			delete [] pWts;
			//////////////////
			AfxMessageBox("CSurface3::MakePatches\nnOutP != nEmit");
			return -1;
		}	
		//////////////////
		delete [] pCon;
		delete [] pWts;
	}										///////////////////////////// end LIST
	//////////////////
	return 0;
	////////////
}

int CSurface3::EX_Make_A_Patch
			(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			nOutGloTot_S	//	Total Output in each side of entire Base Patch 
				,	int			iOutGlo			//	Global i Bary Coords for Ist Output of the PentaHed 
				,	int			jOutGlo			//	Global j Bary Coords for Ist Output of the PentaHed 
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_G		// 	Total Output Global Points Array
				,	pDOUBLE		pOutWts_G	// 	Total Output Global Wts Array
			)
{
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSurface3::EX_Make_A_Patch");
		AfxMessageBox(*str);
		///////////////////
		int j,m;
	    ///////////////////
		j = sprintf(buf,"pCon[%d] and pWts[%d]:\n",TriNum,TriNum);
		for(m=0;m<TriNum;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f    %7.2f \n", m, 
					pCon[m].x, pCon[m].y, pCon[m].z, pWts[m] );
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	WORLD	Out;
	double	WtOut;
    //////////////////////
	int		iu,iv,nMax,nOut = 0;
	double	u,v,del;
	//////////////////////////////////////////////////////////////////// LOOP
	del		= 1.0/nSeg;
	nMax	= nSeg + 1;
	////////////////////
	for (iu=0;iu<nMax;iu++)
	{
		/////////
		for (iv=0;iv<nMax-iu;iv++)
		{
			//////////////////////////////////
			u	= iu * del;
			v	= iv * del;
			//////////
			if(nDegree == 1)
				Linear(pCon, pWts, u, v, &Out, &WtOut);
			else
			if(nDegree == 2)
				Quadratic(pCon, pWts, u, v, &Out, &WtOut);
			else
			if(nDegree == 3)
				Cubic(pCon, pWts, u, v, &Out, &WtOut);
			///////////////////////// Save Output in Right Place
			int iOut,jOut,mGlo;
			/////////////////////////
			if(nType == 1)
			{
				iOut	= iOutGlo + iu;
				jOut	= jOutGlo + iv;
			}
			else
			if(nType == 2)
			{
				iOut	= iOutGlo - iu;
				jOut	= jOutGlo - iv;
			}
			else
			{
				//////////////////
				AfxMessageBox("CSurface3::EX_Make_A_Patch\nnType !==1 or 2");
				return -1;
			}
			//////////////////////////////////// Barycentric to Linear: Global
			mGlo = BARY2LIN_PT(iOut,jOut,nOutGloTot_S);
			////////////////////////////////// SAVE
			pOut_G[mGlo].x	= Out.x;
			pOut_G[mGlo].y	= Out.y;
			pOut_G[mGlo].z	= Out.z;
			pOutWts_G[mGlo]	= WtOut;
			//////////////////
			nOut++;
		}
	}
	//////////////////
	return nOut;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int	CSurface3::Linear(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut)
{
	double w = 1.-u-v;
	//////////////////
  	pOut->x = w * Q[0].x * Wt[0] + v * Q[1].x * Wt[1] + u * Q[2].x * Wt[2];
	pOut->y = w * Q[0].y * Wt[0] + v * Q[1].y * Wt[1] + u * Q[2].y * Wt[2];
	pOut->z = w * Q[0].z * Wt[0] + v * Q[1].z * Wt[1] + u * Q[2].z * Wt[2];
	pOut->z = w * Q[0].z * Wt[0] + v * Q[1].z * Wt[1] + u * Q[2].z * Wt[2];
	//////////
	*pWOut	= w *          Wt[0] + v *          Wt[1] + u *          Wt[2];
	//////////
	pOut->x /= *pWOut;
	pOut->y /= *pWOut;
	pOut->z /= *pWOut;
	//////////
	return 0;
}
	
int	CSurface3::Quadratic(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut)
{
	double w,u2,v2,w2,uv2,vw2,uw2;
	///////////////////////////
	w	= 1.-u-v;
	/////////////
	u2	= u * u;
	v2	= v * v;
	w2	= w * w;
	uv2	= 2 * u * v;
	vw2	= 2 * v * w;
	uw2	= 2 * u * w;
	//////////////////
	pOut->x =	w2	* Q[0].x * Wt[0] + uw2 * Q[3].x * Wt[3] + vw2 * Q[1].x * Wt[1] + 
				u2  * Q[5].x * Wt[5] + uv2 * Q[4].x * Wt[4] + v2  * Q[2].x * Wt[2];
	pOut->y =	w2	* Q[0].y * Wt[0] + uw2 * Q[3].y * Wt[3] + vw2 * Q[1].y * Wt[1] + 
				u2  * Q[5].y * Wt[5] + uv2 * Q[4].y * Wt[4] + v2  * Q[2].y * Wt[2];
	pOut->z =	w2	* Q[0].z * Wt[0] + uw2 * Q[3].z * Wt[3] + vw2 * Q[1].z * Wt[1] + 
				u2  * Q[5].z * Wt[5] + uv2 * Q[4].z * Wt[4] + v2  * Q[2].z * Wt[2];
	//////////
	*pWOut	=   w2  *          Wt[0] + uw2 *          Wt[3] + vw2 *          Wt[1] + 
				u2  *          Wt[5] + uv2 *          Wt[4] + v2  *          Wt[2];
	//////////
	pOut->x /= *pWOut;
	pOut->y /= *pWOut;
	pOut->z /= *pWOut;
	//////////
	return 0;
}
	
int	CSurface3::Cubic(pWORLD Q, pDOUBLE Wt, double u, double v, pWORLD pOut, pDOUBLE pWOut)
{
	double w,u3,v3,w3,u2,v2,w2,u2v,u2w,v2u,v2w,w2u,w2v,uvw;
	///////////////////////////
	w	= 1.-u-v;
	/////////////
	u2	= u * u;
	v2	= v * v;
	w2	= w * w;
	u3	= u * u2;
	v3	= v * v2;
	w3	= w * w2;
	u2v	= 3 * u2 * v;
	u2w	= 3 * u2 * w;
	v2u	= 3 * v2 * u;
	v2w	= 3 * v2 * w;
	w2u	= 3 * w2 * u;
	w2v	= 3 * w2 * v;
	uvw = 6 * u  * v * w;
	/////////////////////
	pOut->x =	w3  * Q[0].x * Wt[0] + w2u * Q[4].x * Wt[4] + w2v * Q[1].x * Wt[1] + 
				u2w * Q[7].x * Wt[7] + uvw * Q[5].x * Wt[5] + v2w * Q[2].x * Wt[2] + 
				u3  * Q[9].x * Wt[9] + u2v * Q[8].x * Wt[8] + v2u * Q[6].x * Wt[6] +
				v3  * Q[3].x * Wt[3] ;
	pOut->y =	w3  * Q[0].y * Wt[0] + w2u * Q[4].y * Wt[4] + w2v * Q[1].y * Wt[1] + 
				u2w * Q[7].y * Wt[7] + uvw * Q[5].y * Wt[5] + v2w * Q[2].y * Wt[2] + 
				u3  * Q[9].y * Wt[9] + u2v * Q[8].y * Wt[8] + v2u * Q[6].y * Wt[6] +
				v3  * Q[3].y * Wt[3] ; 
	pOut->z =	w3  * Q[0].z * Wt[0] + w2u * Q[4].z * Wt[4] + w2v * Q[1].z * Wt[1] + 
				u2w * Q[7].z * Wt[7] + uvw * Q[5].z * Wt[5] + v2w * Q[2].z * Wt[2] + 
				u3  * Q[9].z * Wt[9] + u2v * Q[8].z * Wt[8] + v2u * Q[6].z * Wt[6] +
				v3  * Q[3].z * Wt[3] ;
	//////////
	*pWOut	=	w3  *          Wt[0] + w2u *          Wt[4] + w2v *          Wt[1] + 
				u2w *          Wt[7] + uvw *          Wt[5] + v2w *          Wt[2] + 
				u3  *          Wt[9] + u2v *          Wt[8] + v2u *          Wt[6] +	
				v3  *          Wt[3] ;
	//////////
	pOut->x /= *pWOut;
	pOut->y /= *pWOut;
	pOut->z /= *pWOut;
	//////////
	return 0;
}	
//////////////////////////////////////////////////////////////////////
int	CSurface3::Triangles_2D
				(
					PATCHOUTPUT		O_kind		//  Output Method
				,	CDListMgr*		pTriList	//	Patch List
				,	BOOL			bClosed		//  ALL Closed?
				,	int				nDim		//  Overall Dimension 3=NonRational/4=Rational
				,	int				nSeg		//  Number of Output Segments in ALL Dir & ALL patches
				,	int				nCon		//  Number of Control Pts
					//////////////////////////////  Globals:
				,	int				nOutGlo_S		//  Total Output in each side of entire Base Patch
					////////////////////
				,	pWORLD			pCon		//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut		//  Total Output Points Array
				,	pDOUBLE			pOutWts		//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				)
{
    ///////////////////////////////////
	if	(
			(!nCon)||(!pCon)||(!pOut)||(!pOutWts)
		)			   	
		return ERROR_MISSING_ARGUMENTS;
	////////////////////////////////////////////////////// CreatePatchPts
	int nPtActual;
	if (O_kind == PA_MODIFIED)
	{
		AfxMessageBox("ERROR\nCSurface3::Triangles\nPA_MODIFIED Not Implemented Yet");
		return -1;
	}
	///////////////////////
	if (O_kind == PA_DECAS) 	// 
	{
		AfxMessageBox("ERROR\nCSurface3::Triangles\nPA_DECAS Not Implemented Yet");
		return -1;
	}
	/////////////////////////	O_kind == PA_EXPLICIT) 	// 
	nPtActual = EX_MakePatches
				(
					nDim,bClosed,nCon,nSeg,nOutGlo_S,pTriList,pWts,pCon,pOut,pOutWts
				);
	////////////////////
	if(nPtActual<0)
	{
		//////////////////
		AfxMessageBox("CSurface3::Triangles_2D\nnPtActual<0");
		return -1;
	}		
    else
		return nPtActual;
}
/////////////////////////////////// end of module /////////////////




