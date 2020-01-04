// Mouse.cpp : implementation file
//


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
/////////////////////
#include "Inter_C1.h" 

#ifdef _DEBUG
#include <stdio.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
IMPLEMENT_SERIAL(CInter_C1,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2        
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CInter_C1::CInter_C1()
{
	/////////////////// Memory
	m_MemErr	= 0;
	m_pData		= NULL;
	m_pCon_BS_S	= NULL;
	m_pCon_BZ_S	= NULL;
}

CInter_C1::~CInter_C1()
{
	/////////////////// Memory
	if(m_MemErr<0)
	{
		if(m_pData)
			delete [] m_pData; 
		if(m_pCon_BS_S)
			delete [] m_pCon_BS_S; 
		if(m_pCon_BZ_S)
			delete [] m_pCon_BZ_S;
	}	
}
///////////////////////////////////////////////////////////////////////////////////// Interpolation
	//////////////////////////////////////////////////////////////////////////////
	//	NOTE:  BackGround:	k = Order; k-1 = Degree of Curve [ k=4 for Cubic]	//
	//																			//
	//		A. CONTROL PTS. -->KNOTS 
	//                                       	//
	//			Let m_nCon_BS is given for the moment ( which is not)			//
	//			m_nCon_BS = n+1, {0,...,n}                              		//
	//
	//			Curve: 
	//						 n
	//				Q(u) = 	sum	 p[i]*N[i,k](u)
	//						 0													//
	//			each Blending fn. N[i,k] has support: [ti,t(i+k)]				//
	//				Ist one:	[t0,tk] 			blending fn:N[0,k](u)		//
	//				last one:	[tn,t(n+k)]			blending fn:N[n,k](u)		//
	//			So,
	//	***		-->	Total # of Knots = n + k + 1 
	//			Now,
	//				since each curve segment is defined over one Knot Interval	//
	//				and blending fns has a support over k intervals, it follows	//
	//				there exists ATMOST k blending fns. over each interval		//
	//				involving k Control pts to define a segment:
	//					Ist segment:	{po,...,pk}	 
	//					last segment:	[p(n-k+1),...pn}
	//	***		-->	#of Distinct Curve Segments = n - k + 2						//
	//	***		-->	#of Distinct Knots			= n - k + 3						// 
	//	***		--> #of Repitition in Knots		= Total - Distinct
	//											= (n+k+1) - (n-k+3)				//
	//											= 2k - 2
	//			NORMALLY, IST AND LAST KNOTS ARE REPEATED k-1 TIMES FORCING		//
	//			IST AND LAST CONTROL POINTS TO COINCIDE WITH END DATA POINTS	//
	//
	//
	//		B. DATA PTS. -->CONTROL PTS  ( INTERPOLATION)						//
	//
	//			DEFN.: Data Pts = Distinct Knots								//
	//
	//			#of Data Pts	= nData = L + 1	{0,...,L} i.e., L intervals		//
	//			#Control Pts: n + 1
	//						n - k + 3 = L + 1 
	//				-->		n = L + k - 2
	//	***			-->		n+1 	= L + k - 1 
	//								= nData + k - 2								//
	//	***		#of Data Weights 	= nData			                            //
	//	***		#of Curve Segments	= nData - 1									//
	//
	//
	//
	//		C. SEQUENCES:  ( INTERPOLATIONWITH CUBIC) k = 2						//
	// 
	// 
	//			Rat_BSpline Controls: 
	//					{ d[i] = Data[i], i = 0,...,L},	L = nData-1 
	//
	//			Rat_BeZier	Controls:
	//					{ b[i] = Data[i], i = 0,...,L},	L = nData-1 
	//
	//		D. ACTUAL DATA STRUCTURE  ( INTERPOLATIONWITH CUBIC) k = 4			//
	// 
	//			Order:
	//	***			m_nOrder (=k)		= 2						
	//			#of Data Pts:
	//	***				nData:		 	= GIVEN
	//	***		#of Curve Segments		= L 
	//									= nData - 1
	//			#of Control Points:
	//	***			m_nCon_BS(=L)		= nData 				
	//	//////////////////////////////////////////////////////////////////////	//
	//	***		Data3D[i]:									i = {0,...,L}:
	//
	//		I.	CONTROL POINTS : BSPLINE = Data[] 
	//
	//				OPEN: 	We need to store:
	//							[L+ k - 1] Control Pts., because there are L curves
	//							with support over k spans and in ElemObj.Curve_3, we set,for GENERATION: 
	// ***						# of Curves 	= #of Control Pts - k + 1 
	//											= (L+k-1) - k + 1
	//											= L , as it should be,for generation: 
	//						ex.:	the Ist one will have	d[0],...,d[k-1]		Control Pts
	//								the Lth one will have	d[L-1],...,d[L+k-2]	Control Pts 
	
	//				CLOSE: 	We need to store:
	//							[L] Control Pts., because in ElemObj.Curve_3, we set 
	// ***						# of Curves 	= #of Control Pts 
	//											= L , 
	//							with Additional Control Points are determined by
	//							INDICES modulo PERIOD(= L) Operation for generation: 
	//						ex.:	the Ist one will have	d[0],...,d[k-1]				Control Pts
	//								the Lth one will have	d[L-1],d[0],d[1],...,d[k-2]	Control Pts
	//								
	//
	//
	//		I.	CONTROL POINTS : BEZIER = Data[] 
	//
	//				OPEN: 	We need to store:
	//							[(k-1)L	+ 1] Control Pts., because there are L curves
	//							in ElemObj.Curve_3, we set, for GENERATION: 
	// ***						# of Curves 	= (#of Control Pts - k)/(k-1) + 1 
	//											= ((k-1)L + 1 - k))/(k-1) + 1
	//											= ((k-1)(L-1))/(k-1) + 1
	//											=	L - 1 + 1 
	//											= L , as it should be: 
	//						ex.:	the Ist one will have	d[0],...,d[k-1]				Control Pts
	//								the Lth one will have	d[(k-1)(L-1)],...,d[(k-1)L]	Control Pts 
	
	//				CLOSE: 	We need to store:
	//							[(k-1)L] Control Pts., because in ElemObj.Curve_3, 
	//							we set, for GENERATION: 
	// ***						# of Curves 	= (#of Control Pts)/(k-1)
	//											= (k-1)*L/(k-1) 
	//											= L , 
	//							with any Additional Control Points are determined by
	//							INDICES modulo PERIOD(= L) Operation for generation: 
	//						ex.:	the Ist one will have	d[0],...,d[k-1]						Control Pts
	//								the Lth one will have	d[(k-1)(L-1)],...,d[(k-1)L -1],d[0]	Control Pts
	//								
	//
///////////////////////////////////////////////////////////////////////////////////////////////	
int CInter_C1::Interpolate()
{
	//////////////////////////////////////
	m_pCon_BS_S	= new WORLD [m_nCon_BS_S];
	m_pCon_BZ_S	= new WORLD [m_nCon_BZ_S];
	///////////
	if(!m_pCon_BS_S || !m_pCon_BZ_S )
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	//////////////////////////////////////////////////////////////////////// BSpline Cons
	FillUpSpline(m_pCon_BS_S,m_pData,m_nSeg_DT_S,m_bClosed_S);
	//////////////////////////////////////////////////////////////////////// Bezier Cons
	FillUpBezier(m_pCon_BZ_S,m_pData,m_nSeg_DT_S,m_bClosed_S);
	////////////////								
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	////////////////
	return 0;
}		

int CInter_C1::FillUpSpline(pWORLD Con,pWORLD Data,int L,BOOL bClosed) 
{
	//////////////////////////////////////////////////// fill up Controls(Spline)
	int k,Lt3;
	//////////
	Lt3 = L + 1;
	if(bClosed)
		Lt3--;	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j;
		//////////
		sprintf(buf,"FillUpSpline");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"Data[%d]\n     X     Y    Z\n",Lt3);
		for(k=0;k<Lt3;k++)
		{
		   j += sprintf( buf + j, "%7.1f %7.1f %7.1f\n", Data[k].x,Data[k].y,Data[k].z );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
    }
#endif				
	//////////////////////////////////////////////////// fill up Controls (BSpline)
	for(k=0;k<Lt3;k++)                        
	{                                                                     
		Con[k].x 	= Data[k].x;
		Con[k].y 	= Data[k].y; 
		Con[k].z 	= Data[k].z;
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	if(1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		j = sprintf(buf,"B_SplineCon[%d]\n     X     Y    Z\n",Lt3);
		for(k=0;k<Lt3;k++)
		{
	  		j += sprintf( buf + j, "%7.1f %7.1f %7.1f\n", Con[k].x,Con[k].y,Con[k].z );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
	    ///////////////////
	    delete str;
	}	    
#endif				
	/////////////
	return 0;
}
				
int CInter_C1::FillUpBezier(pWORLD Con,pWORLD Data,int L,BOOL bClosed) 
{
	
	//////////////////////////////////////////////////// fill up Controls (Bezier)
	int k,Lt3;
	//////////
	Lt3 = L + 1;
	if(bClosed)
		Lt3--;	
	//////////////////////////////////////////
	for(k=0;k<Lt3;k++)                        
	{                                                                     
		Con[k].x 	= Data[k].x;
		Con[k].y 	= Data[k].y; 
		Con[k].z 	= Data[k].z;
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"In FillUpBezier");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"Bezier Controls[%d]\n      X             Y            Z\n",Lt3);
		for(k=0;k<Lt3;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n", k,Con[k].x,Con[k].y,Con[k].z );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
	/////////////
	return 0;
}

void CInter_C1::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CInter_C1:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CInter_C1:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////
