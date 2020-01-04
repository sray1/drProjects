// CPat_Tan3.cpp : implementation of the CPat_Tan3 class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct
#include <afxtempl.h>	// CList

#include "3DMath.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "Triangle.h"

#include "Pat_Tan3.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPat_Tan3

IMPLEMENT_DYNAMIC(CPat_Tan3,CSurface3)
/*
BEGIN_MESSAGE_MAP(CPat_Tan3,CSurface3)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPat_Tan3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024

#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)

#define BARY2LIN_TRI_1_NEW(i,j,nP,nDeg)	( (j)  + ((i)*(2*(nP)-(i)-2))/(nDeg) )/(nDeg)
#define BARY2LIN_TRI_2_NEW(i,j,nP,nDeg)	( (j - nDeg)  + ((i)*(2*(nP)-(i)-2))/(nDeg) - ((nP) - 1) + (i) )/(nDeg)
//////////////////////////////////////////////
CPat_Tan3::CPat_Tan3()
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
int CPat_Tan3::DC_GetTangentsForNormalAtaNode		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
			(
					WORLD		wNodeCoord
				,	WORLD&		OutTan_U	//  Total Output Points Array
				,	WORLD&		OutTan_V	//  Total Output Points Array
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	double		dSameNessRatio
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
		sprintf(buf,"Just in CPat_Tan3::DC_GetTangentsAtaNode");
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
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
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
			AfxMessageBox("ERROR:\nCPat_Tan3::DC_GetTangentsAtaNode\nnConTri != TriNum");
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
		/////////////////////////////// Compare
		int LIndex;
		///////////
		if( IsDesiredControlIndices(wNodeCoord,LIndex,pCon,nConTri,
													dSameNessRatio) )	// MATCH?
		{
			/////////////
			DC_GetTangentsForNormalAtaLIndex(nDegree,nDim,nOutSeg,TriNum,nType,LIndex,
												pWts,pCon,OutTan_U,OutTan_V);
			///////////////
			delete [] pCon;
			delete [] pWts;
			/////////
			return 0;
		}
		///////////////
		delete [] pCon;
		delete [] pWts;
		/////////
	}
	//////////////////
	return -1;
	////////////
}

//BOOL CPat_Tan3::IsDesiredControlIndices(WORLD wNodeCoord,
//					int& LIndex,pWORLD pCon,int nConTri)
BOOL CPat_Tan3::IsDesiredControlIndices(WORLD wNodeCoord,
			int& LIndex,pWORLD pCon,int nConTri,double dSameNessRatio)
{
	C3DMath Math3D;
	///////////////
	for(int i=0;i<nConTri;i++)
	{
		/////////////////////////////// Compare
		if( Math3D.AreSame_WORLD(&wNodeCoord, &(pCon[i]),dSameNessRatio )	)	// MATCH?
		{
			LIndex = i;
			///////////
			return TRUE;
		}
	}
	/////////////
	return FALSE;
}

int CPat_Tan3::DC_GetTangentsForNormalAtaLIndex
			(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			LIndex			//	Linear Index where tangents needed
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	WORLD&		OutTanU		// 	tangent along u
				,	WORLD&		OutTanV		// 	tangent along v
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
		sprintf(buf,"Just in CPat_Tan3::DC_MakeTangents_A_Patch");
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
////////////////////////////////////////////////////////////////// u,v index from Linear Index
	int iu,iv,iw; ///	indices where tangents needed
	CTriangle Triangle;
	Triangle.GetIJK(&iu,&iv,&iw,LIndex,nDegree);
	////////////////////////////////////////////
	double	u,v,del;
	del		= 1.0/nSeg;
	u	= iu * del;
	v	= iv * del;
	///////////////
	if(nDim == 3)
	{
		Tangent_UV(pCon, u, v, nDegree, 1,OutTanU);
		Tangent_UV(pCon, u, v, nDegree, 2,OutTanV);
	}
	else
	if(nDim == 4)
	{
		Rat_Tangent_UV(pCon, pWts, u, v, nDegree, 1,OutTanU);
		Rat_Tangent_UV(pCon, pWts, u, v, nDegree, 2,OutTanV);
	}
	///////////////////////// Correct x Axis for Type 2 Triangle
	if(nType == 2)
	{
		C3DMath Math3D;
		///////////////
		Math3D.Scale3DPts(-1.0,&OutTanU);
		Math3D.Scale3DPts(-1.0,&OutTanV);
	}
	//////////////////
	return 0;
}

int CPat_Tan3::DC_GetaTangentAtaNode		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
			(
					WORLD		wNodeCoord
				,	WORLD&		OutTan		//  Total Output Points Array
				,	int			DirTan		//  Total Output Points Array
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	BOOL		bClosed		//  Closed?
				,	int			nCon		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nOutSeg		//  Number of Segments for each Bezier Triangular Patch
					//////////////////////////
				,	CDListMgr*	pTriList	//	Triangular Patch List
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	double		dSameNessRatio
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
		sprintf(buf,"Just in CPat_Tan3::DC_GetTangentsAtaNode");
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
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
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
			AfxMessageBox("ERROR:\nCPat_Tan3::DC_GetTangentsAtaNode\nnConTri != TriNum");
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
		/////////////////////////////// Compare
		int LIndex;
		///////////
		if( IsDesiredControlIndices(wNodeCoord,LIndex,pCon,nConTri,
													dSameNessRatio) )	// MATCH?
		{
			/////////////
			DC_GetaTangentAtaLIndex(nDegree,nDim,nOutSeg,TriNum,nType,LIndex,
												pWts,pCon,OutTan,DirTan);
			///////////////
			delete [] pCon;
			delete [] pWts;
			/////////
			return 0;
		}
		///////////////
		delete [] pCon;
		delete [] pWts;
		/////////
	}
	//////////////////
	return -1;
	////////////
}

int CPat_Tan3::DC_GetaTangentAtaLIndex
			(
					int			nDegree		//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim		//  3= NonRational / 4 = Rational
				,	int			nSeg		//  Number of Segments for each Patch Array 
				,	int			TriNum		//  Number of Controls
				//////////////////////////////////  Globals for Output Storage:
				,	int			nType			//	Triangle Type:1=left/2=right
				,	int			LIndex			//	Linear Index where tangents needed
				//////////////////////////////////
				,	pDOUBLE		pWts		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon		//  Total Input CONTROL Points Array
				,	WORLD&		OutTan		// 	tangent
				,	int&		DirTan		// 	dir for tangent
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
		sprintf(buf,"Just in CPat_Tan3::DC_MakeTangents_A_Patch");
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
////////////////////////////////////////////////////////////////// u,v index from Linear Index
	int iu,iv,iw; ///	indices where tangents needed
	CTriangle Triangle;
	Triangle.GetIJK(&iu,&iv,&iw,LIndex,nDegree);
	////////////////////////////////////////////
	double	u,v,del;
	del		= 1.0/nSeg;
	u	= iu * del;
	v	= iv * del;
	///////////////
	if(nDim == 3)
		Tangent_UV(pCon, u, v, nDegree, DirTan,OutTan);
	else
	if(nDim == 4)
		Rat_Tangent_UV(pCon, pWts, u, v, nDegree, DirTan,OutTan);
	///////////////////////// Correct x Axis for Type 2 Triangle
	if(nType == 2)
	{
		C3DMath Math3D;
		///////////////
		Math3D.Scale3DPts(-1.0,&OutTan);
	}
	/////////
	return 0;
}

int CPat_Tan3::DC_MakeTangentsInOneDir		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
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
				,	pWORLD		pOutTan		//  Total Output Points Array
				,	int			nDir		//  Total Output Points Array
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
		sprintf(buf,"Just in CPat_Tan3::MakePatches");
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
			AfxMessageBox("ERROR:\nCPat_Tan3::MakePatches\nnConTri != TriNum");
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
		nOutP = DC_Make_TangentsInOneDir_A_Patch(nDegree,nDim,nOutSeg,TriNum,
								nType,nOutGlo_S,iOutGlo,jOutGlo,
								pWts,pCon,pOutTan,nDir);
		///////////////////				
		if (nOutP <0)
		{
			//////////////////
			delete [] pCon;
			delete [] pWts;
			//////////////////
			AfxMessageBox("CPat_Tan3::MakePatchesInOneDir\nnOutP != nEmit");
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

int CPat_Tan3::DC_Make_TangentsInOneDir_A_Patch
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
				,	pWORLD		pOutTan_G	// 	Total Output Global Points Array
				,	int			nDir		// 	direction of tangent
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
		sprintf(buf,"Just in CPat_Tan3::DC_MakeTangents_A_Patch");
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
	WORLD	OutTan;
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
			if(nDim == 3)
				Tangent_UV(pCon, u, v, nDegree, nDir,OutTan);
			else
			if(nDim == 4)
				Rat_Tangent_UV(pCon, pWts, u, v, nDegree, nDir,OutTan);
			///////////////////////// Correct x Axis for Type 2 Triangle
			if(nType == 2)
			{
				C3DMath Math3D;
				///////////////
				Math3D.Scale3DPts(-1.0,&OutTan);
			}
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
				AfxMessageBox("CPat_Tan3::EX_MakeTangents_A_Patch\nnType !==1 or 2");
				return -1;
			}
			//////////////////////////////////// Barycentric to Linear: Global
			mGlo = BARY2LIN_PT(iOut,jOut,nOutGloTot_S);
			////////////////////////////////// SAVE
			pOutTan_G[mGlo].x	= OutTan.x;
			pOutTan_G[mGlo].y	= OutTan.y;
			pOutTan_G[mGlo].z	= OutTan.z;
			//////////////////
			nOut++;
		}
	}
	//////////////////
	return nOut;
}

int CPat_Tan3::DC_MakeTangents		// RATIONAL BEZIER Patch Tangents By deCasteljau SubDiv
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
				,	pWORLD		pOutTan_U	//  Total Output Points Array
				,	pWORLD		pOutTan_V	//  Total Output Points Array
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
		sprintf(buf,"Just in CPat_Tan3::MakePatches");
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
			AfxMessageBox("ERROR:\nCPat_Tan3::MakePatches\nnConTri != TriNum");
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
		nOutP = DC_Make_Tangents_A_Patch(nDegree,nDim,nOutSeg,TriNum,
								nType,nOutGlo_S,iOutGlo,jOutGlo,
								pWts,pCon,pOutTan_U,pOutTan_V);
		///////////////////				
		if (nOutP <0)
		{
			//////////////////
			delete [] pCon;
			delete [] pWts;
			//////////////////
			AfxMessageBox("CPat_Tan3::MakePatches\nnOutP != nEmit");
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

int CPat_Tan3::DC_Make_Tangents_A_Patch
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
				,	pWORLD		pOutTanU_G	// 	Total Output Global Points Array
				,	pWORLD		pOutTanV_G	// 	Total Output Global Points Array
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
		sprintf(buf,"Just in CPat_Tan3::DC_MakeTangents_A_Patch");
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
	WORLD	OutTanU,OutTanV;
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
			if(nDim == 3)
			{
				Tangent_UV(pCon, u, v, nDegree, m_nDir1,OutTanU);
				Tangent_UV(pCon, u, v, nDegree, m_nDir2,OutTanV);
			}
			else
			if(nDim == 4)
			{
				Rat_Tangent_UV(pCon, pWts, u, v, nDegree, m_nDir1,OutTanU);
				Rat_Tangent_UV(pCon, pWts, u, v, nDegree, m_nDir2,OutTanV);
			}
			///////////////////////// Correct x Axis for Type 2 Triangle
			if(nType == 2)
			{
				C3DMath Math3D;
				///////////////
				Math3D.Scale3DPts(-1.0,&OutTanU);
				Math3D.Scale3DPts(-1.0,&OutTanV);
			}
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
				AfxMessageBox("CPat_Tan3::EX_MakeTangents_A_Patch\nnType !==1 or 2");
				return -1;
			}
			//////////////////////////////////// Barycentric to Linear: Global
			mGlo = BARY2LIN_PT(iOut,jOut,nOutGloTot_S);
			////////////////////////////////// SAVE
			pOutTanU_G[mGlo].x	= OutTanU.x;
			pOutTanU_G[mGlo].y	= OutTanU.y;
			pOutTanU_G[mGlo].z	= OutTanU.z;
			////////
			pOutTanV_G[mGlo].x	= OutTanV.x;
			pOutTanV_G[mGlo].y	= OutTanV.y;
			pOutTanV_G[mGlo].z	= OutTanV.z;
			//////////////////
			nOut++;
		}
	}
	//////////////////
	return nOut;
}

int CPat_Tan3::Tangent_UV(pWORLD Cons, double u, double v, int nDegree, int nDir,
																		WORLD& tangent)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Tangent Vector of Bezier Triangular Patch at parameter uv
	////////////////////////////////////////////////////////////////////
	int		nTriNum = (nDegree+1)*(nDegree+2)/2;
	pWORLD	NewC	= new WORLD[nTriNum];
	////////////////////////////////////////////
	int nSide = 1; // 1 ---> u=0 Side SubDivision
	//////////
	if(u<.5)
	{
		if(v<.5)
			nSide = 3; // 3 ---> w=0 Side SubDivision
		else
			nSide = 2; // 2 ---> v=0 Side SubDivision
	}
	//////
	SubDivide(Cons, u, v, NewC, nDegree,nSide); //
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CPat_Tan3::Tangent_UV");
		AfxMessageBox(*str);
		///////////////////
		int j,m;
	    ///////////////////
		j = sprintf(buf,"u = %7.4f v = %7.4f nSide = %d\n\n",u,v,nSide);
		j += sprintf(buf + j,"Cons[%d]:\n",nTriNum);
		for(m=0;m<nTriNum;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f\n", m, 
					Cons[m].x, Cons[m].y, Cons[m].z );
	  		j += sprintf( buf + j, "\n");
		}
		////////////////////////////////////////////
		j += sprintf(buf + j,"\n\nNewC[%d]:\n",nTriNum);
		for(m=0;m<nTriNum;m++)
		{
	   		j += sprintf( buf + j, "m=%2d  %7.2f %7.2f %7.2f\n", m, 
					NewC[m].x, NewC[m].y, NewC[m].z );
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////// Tangent
	Tangent_00(NewC, nDegree, nDir,tangent);	
	/////////////////
	delete [] NewC;
	////////////////
	return 0; 	
}

int CPat_Tan3::Tangent_00(pWORLD Cons, int nDegree, int nDir,WORLD& tangent)
{
	// nDir	= 1 : u-dir
	//		= 2 : v-dir
	//		= 3 : w-dir
    ///////////////////////////////////////////
	// Computes Tangents of Bezier:
	//	 	at the Beginning Side ( t = 0)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * delb0
    //	where
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD  Con0,Con1;
	pWORLD pCon0 = &Con0, pCon1 = &Con1;
	int LIndex;
	///////////////////
	switch(nDir)
	{
		case 1:		// u-Dir
			pCon0 = &Cons[0];
			LIndex = BARY2LIN_PT(1,0,nDegree+1);
			pCon1 = &Cons[LIndex];
		break;
		case 2:		// v-Dir
			pCon0 = &Cons[0];
			LIndex = BARY2LIN_PT(0,1,nDegree+1);
			pCon1 = &Cons[LIndex];
		break;
		case 3:		// w-Dir
			LIndex = BARY2LIN_PT(1,0,nDegree+1);
			pCon0 = &Cons[LIndex];
			LIndex = BARY2LIN_PT(0,1,nDegree+1);
			pCon1 = &Cons[LIndex];
		break;
		default:
		break;
	}
	Math3D.Sub3DPts(pCon1, pCon0, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree, &tangent);
	/////////////////
	return 0; 	

}

int CPat_Tan3::SubDivide(pWORLD Cons, double u, double v, pWORLD NewC, int nDegree,
																			int nSide)
{

	//	SubDivide with
	//		nSide = 1 u = 0 Side
	//		nSide = 2 v = 0 Side
	//		nSide = 3 w = 0 Side
	////////////////////////////////////////////////////////////////////////////
	int r,i,j,i0,j0,k0,ij,rDegree;
	int nTriNum,nOrder,rOrder,rOrderOld;
	double w = 1. - u - v;
	/////////////////////////////////////// save
	switch(nSide)
	{
		case 1:			// u=0 side
			Pick_SubDivCons_U(NewC, Cons, 0, nDegree);
			break;
		case 2:			// v=0 side
			Pick_SubDivCons_V(NewC, Cons, 0, nDegree);
			break;
		case 3:			// w=0 side
			Pick_SubDivCons_W(NewC, Cons, 0, nDegree);
			break;
		default:
			{
				AfxMessageBox("Internal ERROR\nCPat_Tan3::SubDivide\nILLEGAL nSide");
				return -1;
			}
	}
	//////////////// Linear: nothing else to do but pick up values not done by Pick_... subroutines
	if(nDegree == 1)
	{
		*(NewC+(3-nSide) ) = *(Cons+(3-nSide) );
		/////////////	
		return 0;
	}
	/////////////////////////////////////// Triangle Number
	nTriNum = (nDegree+1)*(nDegree+2)/2;
	/////////////////////////////////////// Memory
	pWORLD AuxC = new WORLD[nTriNum];
	///////////////////////////////// init
	for(i=0;i<nTriNum;i++)
		*(AuxC+i) = *(Cons+i);
	/////////////////////////////////////// deCasteljau
	nOrder	= nDegree+1;
	rOrder	= nOrder;
	////////////////////////
	for(r=1;r<= nDegree;r++)
	{
		rDegree = nDegree- r;
		/////////////////////////////////////// Triangle Number
		rOrderOld	= rOrder;
		rOrder		= rDegree+1;
		//////////////////////////////////
		for(i=0;i<= rDegree;i++)
		{
			for(j=0;j<= rDegree-i;j++)
			{
				ij = BARY2LIN_PT(i,j,rOrder);
				//////////////////////////////
				i0 = BARY2LIN_PT(i+1,j	,rOrderOld);
				j0 = BARY2LIN_PT(i	,j+1,rOrderOld);
				k0 = BARY2LIN_PT(i	,j	,rOrderOld);
				///////////////////////////////
				AuxC[ij].x = u * AuxC[i0].x + v * AuxC[j0].x + w * AuxC[k0].x;
				AuxC[ij].y = u * AuxC[i0].y + v * AuxC[j0].y + w * AuxC[k0].y;
				AuxC[ij].z = u * AuxC[i0].z + v * AuxC[j0].z + w * AuxC[k0].z;
			}
		}
		////////////////////////////// Pick up Triangle Controls
		switch(nSide)
		{
			case 1:			// u=0 side
				Pick_SubDivCons_U(NewC, AuxC, r, nDegree);
				break;
			case 2:			// v=0 side
				Pick_SubDivCons_V(NewC, AuxC, r, nDegree);
				break;
			case 3:			// w=0 side
				Pick_SubDivCons_W(NewC, AuxC, r, nDegree);
				break;
			default:
				{
					AfxMessageBox("Internal ERROR\nCPat_Tan3::SubDivide\nILLEGAL nSide");
					return -1;
				}
		}
	}
	///////////////////////// Delete Mem
	delete [] AuxC;
	///////////////
	return 0;					
		
}

int CPat_Tan3::Pick_SubDivCons_U(pWORLD NewC, pWORLD OldC, int r, int nDegree)
{
	//	SubDivide with u = 0 [Jo = ( 0,j,k) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Bezier Triangular Patch Control Nodes & parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(r,j,k) = b (V);	r = 0,...nDeg; j + k = nDeg - r;  Jo = (0,j,k);
	//			     Jo
	////////////////////////////////////////////////////////////////////////////
	int rDegree,k;
	rDegree = nDegree - r;
	/////////////////////////
	int j,rjk,ujk;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(k=0;k<= rDegree;k++)
	{
		j = rDegree - k;
		////////////////
		rjk = BARY2LIN_PT(r,j,nOrder);
		ujk = BARY2LIN_PT(0,j,rOrder);
		//////////////////////////////
		*(NewC+rjk) = *(OldC+ujk);
	}
	///////////////
	return 0;					
}

int CPat_Tan3::Pick_SubDivCons_V(pWORLD NewC, pWORLD OldC, int r, int nDegree)
{
	//	SubDivide with v = 0 [Jo = ( i,0,k) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Bezier Triangular Patch Control Nodes & parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(i,r,k) = b (V);	r = 0,...nDeg; i + k = nDeg - r;  Jo = (i,0,k);
	//			     Jo
	////////////////////////////////////////////////////////////////////////////
	int rDegree,k;
	rDegree = nDegree - r;
	/////////////////////////
	int i,irk,ivk;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(k=0;k<= rDegree;k++)
	{
		i = rDegree - k;
		////////////////
		irk = BARY2LIN_PT(i,r,nOrder);	
		ivk = BARY2LIN_PT(i,0,rOrder);	
		//////////////////////////////
		*(NewC+irk) = *(OldC+ivk);
	}
	///////////////
	return 0;					
}

int CPat_Tan3::Pick_SubDivCons_W(pWORLD NewC, pWORLD OldC, int r, int nDegree)
{
	//	SubDivide with w = 0 [Jo = ( i,j,0) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Bezier Triangular Patch Control Nodes & parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(i,j,r) = b (V);	r = 0,...nDeg; i + j = nDeg - r;  Jo = (i,j,0);
	//			     Jo
	////////////////////////////////////////////////////////////////////////////
	int rDegree;
	rDegree = nDegree - r;
	/////////////////////////
	int i,j,ijr,ijw;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(i=0;i<= rDegree;i++)
	{
		j = rDegree - i;
		////////////////
		ijr = BARY2LIN_PT(i,j,nOrder);	
		ijw = BARY2LIN_PT(i,j,rOrder);	
		//////////////////////////////
		*(NewC+ijr) = *(OldC+ijw);
	}
	///////////////
	return 0;					
}

int CPat_Tan3::Rat_Tangent_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, int nDegree, int nDir,
																					WORLD& tangent)
{
	////////////////////////////////////////////////////////////////////
	//	Returns Tangent Vector of Rational Bezier Triangular Patch at parameter uv
	////////////////////////////////////////////////////////////////////
	int		nTriNum = (nDegree+1)*(nDegree+2)/2;
	pWORLD	NewC	= new WORLD[nTriNum];
	pDOUBLE	NewW	= new double[nTriNum];
	////////////////////////////////////////////
	if(u<.5)
	{
		if(v<.5)
			Rat_SubDivide(Cons, Wts, u, v, NewC, NewW, nDegree,3); // 3 ---> w=0 Side SubDivision
		else
			Rat_SubDivide(Cons, Wts, u, v, NewC, NewW, nDegree,2); // 2 ---> v=0 Side SubDivision
	}
	else
		Rat_SubDivide(Cons, Wts, u, v, NewC, NewW, nDegree,1); // 1 ---> u=0 Side SubDivision
	///////////////////////////////////////////////////// Tangent
	Rat_Tangent_00(NewC, NewW, nDegree, nDir,tangent);	
	/////////////////
	delete [] NewC;
	delete [] NewW;
	////////////////
	return 0; 	
}

int CPat_Tan3::Rat_Tangent_00(pWORLD Cons, pDOUBLE Wts, int nDegree, int nDir,WORLD& tangent)
{
	// nDir	= 1 : u-dir
	//		= 2 : v-dir
	//		= 3 : w-dir
    ///////////////////////////////////////////
	// Computes Tangents of Rational Bezier Triangle:
	//	 	at the Beginning Side ( uv = 00n)
    ///////////////////////////////////////////
    // Farin: Chapter 15: pg 236:
    //
    //		tangent at 0 = nDegree * k1 * delb0
    //	where
    //		k1 		= w1/w0
    //		delb0 	= b1-b0
    ////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD  Con0,Con1;
	pWORLD pCon0 = &Con0, pCon1 = &Con1;
	int LIndex,LIndex1;
    double k1;
	///////////////////
	switch(nDir)
	{
		case 1:		// u-Dir
			pCon0 = &Cons[0];
			LIndex = BARY2LIN_PT(1,0,nDegree+1);
			pCon1 = &Cons[LIndex];
			k1 		= Wts[LIndex]/Wts[0];
		break;
		case 2:		// v-Dir
			pCon0 = &Cons[0];
			LIndex = BARY2LIN_PT(0,1,nDegree+1);
			pCon1 = &Cons[LIndex];
			k1 		= Wts[LIndex]/Wts[0];
		break;
		case 3:		// w-Dir
			LIndex = BARY2LIN_PT(1,0,nDegree+1);
			pCon0 = &Cons[LIndex];
			LIndex1 = BARY2LIN_PT(0,1,nDegree+1);
			pCon1 = &Cons[LIndex1];
			k1 		= Wts[LIndex1]/Wts[LIndex];
		break;
		default:
		break;
	}
	Math3D.Sub3DPts(pCon1, pCon0, &tangent);
	///////////////////////////////////////////
	Math3D.Scale3DPts(nDegree * k1, &tangent);
	/////////////////
	return 0; 	

}

int CPat_Tan3::Rat_SubDivide(pWORLD Cons, pDOUBLE Wts, double u, double v,
									pWORLD NewC, pDOUBLE NewW, int nDegree, int nSide)
{

	//	SubDivide with u = 0 [Jo = ( 0,j,k) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Rational Bezier Triangular Patch Control Nodes, Weights & 
	//			parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(r,j,k) = b (V);	r = 0,...nDeg; j + k = nDeg - r;  Jo = (0,j,k);
	//			     Jo
	//	where b^ is 4 dimensional with (b^,w)
	////////////////////////////////////////////////////////////////////////////
	int r,i,j,i0,j0,k0,ij,rDegree;
	int nTriNum,rTriNum,rTriNumOld;
	double w = 1. - u - v;
	/////////////////////////////////////// Triangle Number
	nTriNum = (nDegree+1)*(nDegree+2)/2;
	rTriNum = nTriNum;
	/////////////////////////////////////// save
	switch(nSide)
	{
		case 1:			// u=0 side
			Rat_Pick_SubDivCons_U(NewC, Cons, NewW, Wts, 0, nDegree);
			break;
		case 2:			// v=0 side
			Rat_Pick_SubDivCons_V(NewC, Cons, NewW, Wts, 0, nDegree);
			break;
		case 3:			// w=0 side
			Rat_Pick_SubDivCons_W(NewC, Cons, NewW, Wts, 0, nDegree);
			break;
		default:
			{
				AfxMessageBox("Internal ERROR\nCPat_Tan3::Rat_SubDivide\nILLEGAL nSide");
				return -1;
			}
	}
	////////////////////////// Linear: nothing else to do but pick up(u=0,v=0) value
	if(nDegree == 1)
	{
		*(NewC+(3-nSide) ) = *(Cons+(3-nSide) );
		*(NewW+(3-nSide) ) = *(Wts+(3-nSide) );
		/////////////	
		return 0;
	}
	/////////////////////////////////////// Memory
	pWORLD AuxC = new WORLD[nTriNum];
	pDOUBLE AuxW = new double[nTriNum];
	//////////////////////////
	for(i=0;i<= nTriNum;i++)
	{
		AuxC[i].x	= Cons[i].x;
		AuxC[i].y	= Cons[i].y;
		AuxC[i].z	= Cons[i].z;
		AuxW[i]		= Wts[i];
	}
	/////////////////////////////////////// deCasteljau
	for(r=1;r<= nDegree;r++)
	{
		rDegree = nDegree- r;
		/////////////////////////////////////// Triangle Number
		rTriNumOld	= rTriNum;
		rTriNum		= (rDegree+1)*(rDegree+2)/2;
		//////////////////////////////////
		for(i=0;i<= rDegree;i++)
		{
			for(j=0;j<= rDegree-i;j++)
			{
				ij = BARY2LIN_PT(i,j,rDegree+1);
				//////////////////////////////
				i0 = BARY2LIN_PT(i+1,j	,rDegree);
				j0 = BARY2LIN_PT(i	,j+1,rDegree);
				k0 = BARY2LIN_PT(i	,j	,rDegree);
				///////////////////////////////
				double w1,w2,w3;
				w1			= AuxW[i0]; 
				w2			= AuxW[j0]; 
				w3			= AuxW[k0];
				///////////////////////
				AuxW[ij]	=  u * w1 + v * w2 + w * w3;
				////////
				AuxC[ij].x	= (u * w1 * AuxC[i0].x + 
							   v * w2 * AuxC[j0].x + 
							   w * w3 * AuxC[k0].x)/AuxW[ij];
				AuxC[ij].y	= (u * w1 * AuxC[i0].y + 
							   v * w2 * AuxC[j0].y + 
							   w * w3 * AuxC[k0].y)/AuxW[ij];
				AuxC[ij].z	= (u * w1 * AuxC[i0].z + 
							   v * w2 * AuxC[j0].z + 
							   w * w3 * AuxC[k0].z)/AuxW[ij];
				/////////
			}
		}
		////////////////////////////// Pick up Triangle Controls
		switch(nSide)
		{
			case 1:			// u=0 side
				Rat_Pick_SubDivCons_U(NewC, AuxC, NewW, AuxW, r, nDegree);
				break;
			case 2:			// v=0 side
				Rat_Pick_SubDivCons_V(NewC, AuxC, NewW, AuxW, r, nDegree);
				break;
			case 3:			// w=0 side
				Rat_Pick_SubDivCons_W(NewC, AuxC, NewW, AuxW, r, nDegree);
				break;
			default:
				{
					AfxMessageBox("Internal ERROR\nCPat_Tan3::Rat_SubDivide\nILLEGAL nSide");
					return -1;
				}
	}
	}
	///////////////////////// Delete Mem
	delete [] AuxC;
	delete [] AuxW;
	///////////////
	return 0;					
		
}

int CPat_Tan3::Rat_Pick_SubDivCons_U(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree)
{
	//	SubDivide with u = 0 [Jo = ( 0,j,k) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Rational Bezier Triangular Patch Control Nodes, Weights & 
	//			parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(r,j,k) = b (V);	r = 0,...nDeg; j + k = nDeg - r;  Jo = (0,j,k);
	//			     Jo
	//	where b^ is 4 dimensional with (b^,w)
	////////////////////////////////////////////////////////////////////////////
	int rDegree,k;
	rDegree = nDegree - r;
	/////////////////////////
	int j,rjk,ujk;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(k=0;k<= rDegree;k++)
	{
		j = rDegree - k;
		////////////////
		rjk = BARY2LIN_PT(r,j,nOrder);
		ujk = BARY2LIN_PT(0,j,rOrder);
		//////////////////////////////
		*(NewC+rjk) = *(OldC+ujk);
		*(NewW+rjk) = *(OldW+ujk);
	}
	///////////////
	return 0;					
}

int CPat_Tan3::Rat_Pick_SubDivCons_V(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree)
{
	//	SubDivide with v = 0 [Jo = ( i,0,k) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Rational Bezier Triangular Patch Control Nodes, Weights &
	//			parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(i,r,k) = b (V);	r = 0,...nDeg; i + k = nDeg - r;  Jo = (i,0,k);
	//			     Jo
	//	where b^ is 4 dimensional with (b^,w)
	////////////////////////////////////////////////////////////////////////////
	int rDegree,k;
	rDegree = nDegree - r;
	/////////////////////////
	int i,irk,ivk;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(k=0;k<= rDegree;k++)
	{
		i = rDegree - k;
		////////////////
		irk = BARY2LIN_PT(i,r,nOrder);	
		ivk = BARY2LIN_PT(i,0,rOrder);	
		//////////////////////////////
		*(NewC+irk) = *(OldC+ivk);
		*(NewW+irk) = *(OldW+ivk);
	}
	///////////////
	return 0;					
}

int CPat_Tan3::Rat_Pick_SubDivCons_W(pWORLD NewC, pWORLD OldC, pDOUBLE NewW, pDOUBLE OldW, 
																	int r, int nDegree)
{
	//	SubDivide with w = 0 [Jo = ( i,j,0) side & given Pt. V=(u,v)
	////////////////////////////////////////////////////////////////////////////
	//	Given Rational Bezier Triangular Patch Control Nodes Weights & 
	//			parameter V = (u,v,1-u-v)
	////////////////////////////////////////////////////////////////////////////
	//				 r
	//	b^(i,j,r) = b (V);	r = 0,...nDeg; i + j = nDeg - r;  Jo = (i,j,0);
	//			     Jo
	//	where b^ is 4 dimensional with (b^,w)
	////////////////////////////////////////////////////////////////////////////
	int rDegree;
	rDegree = nDegree - r;
	/////////////////////////
	int i,j,ijr,ijw;
	//////////////////////////////////////// Pick up Triangle Controls
	int nOrder = nDegree+1;
	int rOrder = rDegree+1;
	/////////////////////////
	for(i=0;i<= rDegree;i++)
	{
		j = rDegree - i;
		////////////////
		ijr = BARY2LIN_PT(i,j,nOrder);	
		ijw = BARY2LIN_PT(i,j,rOrder);	
		//////////////////////////////
		*(NewC+ijr) = *(OldC+ijw);
		*(NewW+ijr) = *(OldW+ijw);
	}
	///////////////
	return 0;					
}
/////////////////////////////////////////////////////////////////////////////////////////////
int	CPat_Tan3::MakeTangents
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
				,	pWORLD			pOut_S		//  Total Output Points Array
				,	int				nDir1		//	direction 1=S/2=T/3=R
				,	pWORLD			pOut_T		//  Total Output Points Array
				,	int				nDir2		//	direction 1=S/2=T/3=R
				,	int				nOut		//	expected number of generated Patch vertices	
				)
{
	//////////////// Directions for Tangents
	m_nDir1 = nDir1;
	m_nDir2 = nDir2;
    ///////////////////////////////////
	if	(
			(!nCon)||(!pCon)||(!pOut_S)||(!pOut_T)
		)			   	
		return ERROR_MISSING_ARGUMENTS;
	////////////////////////////////////////////////////// CreatePatchPts
	int nPtActual;
	if (O_kind == PA_MODIFIED)
	{
		AfxMessageBox("ERROR\nCPat_Tan3::Triangles\nPA_MODIFIED Not Implemented Yet");
		return -1;
	}
	///////////////////////
	if (O_kind == PA_DECAS) 	// 
	{
		nPtActual = DC_MakeTangents
				(
					nDim,bClosed,nCon,nSeg,nOutGlo_S,pTriList,pWts,pCon,pOut_S,pOut_T
				);
	}
	/////////////////////////	O_kind == PA_EXPLICIT) 	// 
	if (O_kind == PA_EXPLICIT)
	{
		AfxMessageBox("ERROR\nCPat_Tan3::Triangles\nPA_Explicit Not Implemented Yet");
		return -1;
	}
	////////////////////
	if(nPtActual<0)
	{
		//////////////////
		AfxMessageBox("CPat_Tan3::MakeTangents\nnPtActual<0");
		return -1;
	}		
    else
		return nPtActual;
}

int	CPat_Tan3::MakeTangentsInOneDir
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
				,	int				nDir		//	direction 1=S/2=T/3=R
				,	int				nOut		//	expected number of generated Patch vertices	
				)
{
    ///////////////////////////////////
	if	(
			(!nCon)||(!pCon)||(!pOut)
		)			   	
		return ERROR_MISSING_ARGUMENTS;
	////////////////////////////////////////////////////// CreatePatchPts
	int nPtActual;
	if (O_kind == PA_MODIFIED)
	{
		AfxMessageBox("ERROR\nCPat_Tan3::Triangles\nPA_MODIFIED Not Implemented Yet");
		return -1;
	}
	///////////////////////
	if (O_kind == PA_DECAS) 	// 
	{
		nPtActual = DC_MakeTangentsInOneDir
				(
					nDim,bClosed,nCon,nSeg,nOutGlo_S,pTriList,pWts,pCon,pOut,nDir
				);
	}
	/////////////////////////	O_kind == PA_EXPLICIT) 	// 
	if (O_kind == PA_EXPLICIT)
	{
		AfxMessageBox("ERROR\nCPat_Tan3::Triangles\nPA_Explicit Not Implemented Yet");
		return -1;
	}
	////////////////////
	if(nPtActual<0)
	{
		//////////////////
		AfxMessageBox("CPat_Tan3::MakeTangents\nnPtActual<0");
		return -1;
	}		
    else
		return nPtActual;
}
/////////////////////////////////// end of module /////////////////




