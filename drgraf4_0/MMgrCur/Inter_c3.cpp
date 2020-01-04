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
#include "Inter_C3.h" 

#ifdef _DEBUG
#include <stdio.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
IMPLEMENT_SERIAL(CInter_C3,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2        
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CInter_C3::CInter_C3()
{
	/////////////////// Memory
	m_MemErr	= 0;
	m_pMKnot_S	= NULL;
	m_pKnot_S	= NULL;
	m_pWts_DT_S	= NULL;
	m_pWts_BS_S	= NULL;
	m_pWts_BZ_S	= NULL;
	m_pData		= NULL;
	m_pCon_BS_S	= NULL;
	m_pCon_BZ_S	= NULL;
	m_pAlf		= NULL;
	m_pBet		= NULL;
	m_pGam		= NULL;
	m_pSol		= NULL;
	m_pRHS		= NULL;
}

CInter_C3::~CInter_C3()
{
	/////////////////// Memory
	if(m_MemErr<0)
	{
		if(m_pMKnot_S)
			delete [] m_pMKnot_S; 
		if(m_pKnot_S)
			delete [] m_pKnot_S; 
		if(m_pWts_DT_S)
			delete [] m_pWts_DT_S; 
		if(m_pWts_BS_S)
			delete [] m_pWts_BS_S; 
		if(m_pWts_BZ_S)
			delete [] m_pWts_BZ_S; 
		if(m_pData)
			delete [] m_pData; 
		if(m_pCon_BS_S)
			delete [] m_pCon_BS_S; 
		if(m_pCon_BZ_S)
			delete [] m_pCon_BZ_S;
		if(m_pAlf)
			delete [] m_pAlf;
		if(m_pBet)
			delete [] m_pBet;
		if(m_pGam)
			delete [] m_pGam;
		if(m_pSol)
			delete [] m_pSol;
		if(m_pRHS)
			delete [] m_pRHS;
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
	//		C. SEQUENCES:  ( INTERPOLATIONWITH CUBIC) k = 4						//
	// 
	// 
	//			Rat_BSpline Controls: 
	//					{ d[0],...,d[L+2]},	L = nData-1 
	//
	//			Rat_BeZier	Controls:
	//					{ b[0]=d[0], ..., b[3i -1],b[3i],b[3i+1],...,b[3L]=d[L+2]}	
	//
	//		D. ACTUAL DATA STRUCTURE  ( INTERPOLATIONWITH CUBIC) k = 4			//
	// 
	//			Order:
	//	***			m_nOrder (=k)		= 4						
	//			#of Data Pts:
	//	***				nData:		 	= GIVEN
	//	***		#of Curve Segments		= L 
	//									= nData - 1
	//			#of Control Points:
	//	***			m_nCon_BS(=L+3)		= nData + 2				
	//	//////////////////////////////////////////////////////////////////////	//
	//	***		Data3D[i]:									i = {0,...,L}:
	//	 
	//
	//		E.	KNOT VECTOR:
	//		
	//				Knot[i]:								i = {0,...,L}:
	//				Computed by Various Schemes:
	//					KN_UNIFORM  -------------> Non-Rational B-Spline
	//					KN_USER------------------> Get from User
	//					KN_CHORDLENGTH-------\ 
	//					KN_FOLEY--------------|--> Chord Length parametrization for now
	//					KN_AUTO--------------/
	//					KN_CENTRIPETAL-----------> Centripetal
	//												
	//
	//
	//		F.	SYSTEM:		(L+1) x (L+1) Tridiagonal system
	// 
	//					
	//	0|//////////////////////////////////////////| |	e[0]	|	= |data4[0] |<-- control = leftmost data	 	
	//	 -----------------------------------------------------------------------------------------------------
	//	1|///|	b0	c0<--depend on Left B.C     |///| | e[1]	|	= |  s[0]   |<-- determined by Left B.C
	//	2|///|	a1	b1	c1                      |///| | e[2]	|	= |  s[1]   |-|
	//	 |///|		.                           |///| | 	.   |	= |	   .    | |
	//	 |///|			.                       |///| |		.	|	= |    .    | |-> as under
	//	 |///|				.	                |///| |		.	|	= |    .    | |
	//	L|///|			a[L-1]	b[L-1]	c[L-1]  |///| | e[L]	|	= |  s[L-1] |-|	
	//L+1|///|depend on Rt B.C -->a[L]	b[L]	|///| | e[L+1]	|	= |  s[L]   |<-- determined by Right B.C	
	//	 -----------------------------------------------------------------------------------------------------	
	//	 |///|////////(L+1) x (L+1)//////////////|//| | e[L+1]	|	= |data4[L] |<-- control= rightmost data
	
	//	where:
	//
	//		a[0] = c[L] = 0;
	//		b[0], c[0] <--- Depends on Left  Boundary Condition;
	//		a[L], b[L] <--- Depends on Right Boundary Condition;
	//
	//	and
	//		DEFN.: del[i] = Knot[i+1] - Knot[i], with del[-1] = del[L] = 0
	//		for i = {1,...,L-1}
	//		{   
	//			a[i] = deli**2/sumim1
	//			b[i] = deli*(delim2+delim1)/sumim1 + delim1(deli+delip1)/sumi
	//			c[i] = delim1**2/sumi
	//			where
	//				deli 	= Knot[i+1] - Knot[i]				// del[i]
	//				delip1	= Knot{i+2] - Knot[i+1]				// del[i+1]
	//				delim1	= Knot[i]	- Knot[i-1] 			// del[i-1]
	//				delim2	= Knot[i-1]	- Knot[i-2]             // del[i-2]
	//				sumim1	= delim2 + delim1 + deli
	//				sumi	= delim1 + deli   + delip1			 	
	//      }
	//		3D Rat Data:	data3[i],							i = { 0,...,L}
	//		Data Weights: 		w[i],	 						i = { 0,...,L}
	//		4D Data:		data4[i]
	//							 = (data3[i]*w[i],w[i]),		i = { 0,...,L}
	//
	//		Auxiliary Vector: s[i], 							i = { 0,...,L}			
    //
	//			s[i] = determined by Left Boundary Condition,	i = 0,
	//				 = (delim1 + deli)* data4[i], 				i = {1,...,L-1}  		
	//				 = determined by Right Boundary Condition	i = L;
	//
	//
	//
	//		G.	BOUNDARY CONDITION:
	//
	//								BC_CLAMPED,
	//								BC_FREE,			
	//								BC_BESSEL,			== BC_AUTO
	//								BC_QUADRATIC,
	//								BC_NOT_A_KNOT
	//
	//
	//
	//		H.	SOLUTION:
	//
	//					4D BSpline Control Vector: 
	//							e[i] = (d[i],v[i]),				i = {0,...,L+2}
	//					 where
	//							d[i] = 3D BSpline Control Vector
	//							v[i] = Spline Weights
	// 
	//
	//		I.	CONTROL POINTS & WEIGHTS: BSPLINE 
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
	//		I.	CONTROL POINTS & WEIGHTS: BEZIER ( No Sharing of Control Pts-> No Internal Knot) 
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
int CInter_C3::Interpolate()
{
	//////////////////////////////////////////////////// Setup Knots 
	SetupKnots(m_pData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
	//////////////////////////////////////////
	if(m_nDim_S == 4)
	{
		//////////////////////////////////////////////////// Setup Weights
		SetupWeights(m_WtType_S,m_pWts_DT_S,m_nData_S);
		//////////////////////////////////////////////////// Convert Data to 4D
		SetupData4D(m_pData,m_pWts_DT_S,m_nData_S);
	}	
	//////////////////////////////////////////////////////////////////////// Setup/Solve System
	m_pAlf	= new double[m_nData_S];
	m_pBet	= new double[m_nData_S];
	m_pGam	= new double[m_nData_S];
	m_pSol	= new double[m_nSeg_DT_S+1][4];	// Reserve for Rational
	m_pRHS	= new double[m_nSeg_DT_S+1][4];	// Reserve for Rational
	if(!m_pAlf	|| !m_pBet	|| !m_pGam	||  !m_pSol	||	!m_pRHS	  )	
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}	
	////////////////////////////////////////////////////////////////////////
	if(m_bClosed_S || m_BCL == BC_CLOSED || m_BCR == BC_CLOSED)	// CLOSED
	{
		SetupSystem_Close(m_pAlf,m_pBet,m_pGam,m_pKnot_S,m_nSeg_DT_S);
		//////////////////////////////////////////////////// Setup BoundaryConditions
		SetupBC_Close(m_pData,m_pWts_DT_S,m_pRHS,m_nSeg_DT_S,m_nDim_S);
		//////////////////////////////////////////////////// Solve System
		SolveSystem_Close(m_pAlf,m_pBet,m_pGam,m_pRHS,m_pSol,m_nSeg_DT_S,m_nDim_S); 
	}	
	else														// OPEN
	{	
		SetupSystem_Open(m_pAlf,m_pBet,m_pGam,m_pKnot_S,m_nSeg_DT_S);
		//////////////////////////////////////////////////// Setup BoundaryConditions
		SetupBC_Open(m_pAlf,m_pBet,m_pGam,m_pData,m_pWts_DT_S,m_pKnot_S,
					m_TanL,m_TanR,m_pRHS,m_BCL,m_BCR,m_nSeg_DT_S,m_nDim_S);
		//////////////////////////////////////////////////// Solve System
		SolveSystem_Open(m_pAlf,m_pBet,m_pGam,m_pRHS,m_pSol,m_nSeg_DT_S,m_nDim_S);
	}
	////////////////////// Free Memory
	if(m_pAlf)
	{
		delete [] m_pAlf;
		m_pAlf = NULL;
	}	
	if(m_pBet)
	{
		delete [] m_pBet;
		m_pBet = NULL;
	}	
	if(m_pGam)
	{
		delete [] m_pGam;
		m_pGam = NULL;
	}	
	if(m_pRHS)
	{
		delete [] m_pRHS;
		m_pRHS = NULL;
	}	
	//////////////////////////////////////
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
	//////////////////////////////////////////////////////////////////////// BSpline Cons
	if(!m_bClosed_S)						// OPEN
		FillUpSpline_Open (m_pSol,m_nSeg_DT_S,m_pData,m_pWts_DT_S,
								m_pCon_BS_S,m_pWts_BS_S,m_nDim_S);
	else									//CLOSED
		FillUpSpline_Close(m_pSol,m_nSeg_DT_S,m_pData,m_pWts_DT_S,
								m_pCon_BS_S,m_pWts_BS_S,m_nDim_S);
	//////////////////////////////////////////////////////////////////////// Rat_Bsp to Rat_Bez
	Convert_BS2BZ(m_pSol,m_pData,m_pWts_DT_S,m_pKnot_S,m_pWts_BZ_S,m_pCon_BZ_S,
						m_nSeg_DT_S,m_bClosed_S,m_nDim_S);
	////////////////								
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
			
	if(m_pSol)
	{
		delete [] m_pSol;
		m_pSol = NULL;
	}	
	//////////////////////////////////////////////////////////////////////// Update Knots
	m_pMKnot_S = new double[m_nMKnots_S];
	if(!m_pMKnot_S)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}	
	/////////////////
	UpdateToMultKnots(m_pKnot_S,m_nKnots_S,m_pMKnot_S,m_nMKnots_S,m_nOrder_S);
	////////////////
	return 0;
}		

int CInter_C3::SetupWeights(enum WEIGHT WtType, pDOUBLE Wts,int nWts) 
{

	int i;
	////////////////////////////////////////////////////////////// Uniform or User
	if(WtType == WT_UNIFORM)
	{
		for(i=0;i<nWts;i++)
			Wts[i] = 1;
		return 0;
	}
	else
	if(WtType == WT_USER)
		return 0;			// dont need to do anything
	/////////////////////////////////////////////////////////////////// Auto
	// Depends on Type of Conics
	///////////////////////////////////////////////////////////////////
	if(WtType == WT_AUTO)
	{
		for(i=0;i<nWts;i++)
			Wts[i] = 1;
		return 0;
	}
	/////////
	return 0;
}						

int CInter_C3::SetupData4D(pWORLD Data, pDOUBLE Wts,int nData) 
{

	int i;
	////////////////////// 
	for(i=0;i<nData;i++)
	{
		Data[i].x *=Wts[i];
		Data[i].y *=Wts[i];
		Data[i].z *=Wts[i];
	}	
	/////////
	return 0;
}						

int CInter_C3::SetupKnots(pWORLD Data, enum KNOT KnotType, pDOUBLE Knot,int nKnots) 
{

	//////////////////////////////////////////////////////////////////////
	//	KNOTS Generated are SIMPLE i.e., NO MULTIPLICITY OTHER THAN 1	//
	// 	OPEN:                                                           //
	//			nKnots = nData											//
	// 	CLOSED:                                                         //
	//			nKnots = nData + 1										//
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j,k,nSize;
		//////////
		sprintf(buf,"CInter_C3::SetupKnots");
		AfxMessageBox(*str);
		///////////////////
		nSize = nKnots;
		if(m_bClosed_S)
			nSize--;
		j = sprintf(buf,"Data[%d]\n",nSize);
		for(k=0;k<nSize;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n", k,
		   					Data[k].x, Data[k].y, Data[k].z);
		}
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
    }
#endif				
	int k;
	////////////////////////////////////////////////////////////// Uniform or User
	if(KnotType == KN_UNIFORM)
	{
		for(k=0;k<nKnots;k++)
			*(Knot+k) = k;
		return 0;
	}
	else
	if(KnotType == KN_USER)
		return 0;			// dont need to do anything
	////////////////////////////////////////////////////////////// Non Uniform
	BOOL	bMultKnot = FALSE;
	double	delta;
	/////////////
	Knot[0] = 0.0;		// arbitrary
	////////////////////////////////
	int L = nKnots - 1;
	///////////////////
	for(k=0;k<L;k++)
	{
		if(m_bClosed_S)						
			delta = sqrt( 
							( Data[(k+1)%L].x - Data[k].x ) * ( Data[(k+1)%L].x - Data[k].x) +
							( Data[(k+1)%L].y - Data[k].y ) * ( Data[(k+1)%L].y - Data[k].y) +
							( Data[(k+1)%L].z - Data[k].z ) * ( Data[(k+1)%L].z - Data[k].z)
						);
		else						
			delta = sqrt( 
							( Data[k+1].x - Data[k].x ) * ( Data[k+1].x - Data[k].x) +
							( Data[k+1].y - Data[k].y ) * ( Data[k+1].y - Data[k].y) +
							( Data[k+1].z - Data[k].z ) * ( Data[k+1].z - Data[k].z)
						);
		///////////////////// Multiple Knot
		if(delta == 0.0)
		{
			bMultKnot = TRUE;
			break;
		}
		/////////////////////
		switch(KnotType)
		{
			case KN_FOLEY:              // fall thro' for now
			case KN_AUTO:
			case KN_CHORDLENGTH:
			
				Knot[k+1] = Knot[k] + delta;
				break;
					
			case KN_CENTRIPETAL:
			
				Knot[k+1] = Knot[k] + sqrt(delta);
				break;
			
		}
	}
	////////////////////////////////////////// switch to uniform
	if(bMultKnot)
	{
		for(k=0;k<nKnots;k++)
			*(Knot+k) = k;
		return 0;
	}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j,k;
		///////////////////
		j = sprintf(buf,"Knot[%d]\n",nKnots);
		for(k=0;k<nKnots;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,Knot[k] );
		}
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
    }
#endif				
	/////////////
	return 0;
}						

int CInter_C3::SetupSystem_Close(pDOUBLE a,pDOUBLE b,pDOUBLE c,pDOUBLE Knot,int L) 
{
     
	//////////////////////////////////////////////////////////////////
	//	KNOTS MUST BE SIMPLE i.e., NO MULTIPLICITY OTHER THAN 1		//
	//////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
	//	LAST DATA IS NOT FIRST DATA, i.e., FIRST DATA PT. IS NOT TAGGED ONTO BACK	//
	//					nData = No. of Data WITHOUT REPITITION						//
	//						Knot[i],Wts[i], i={0,...nData-1}						//
	//		However, L = Intervals = #of Curve Segments = nData = Periodicity		//
	//							Knot[L] = Knot[0] etc.								//
	//////////////////////////////////////////////////////////////////////////////////
	double	deli, delim1, delim2, delip1, sumim1, sumi, sum;
	//////////////////////////////////////////////////// Case: One or Two Interval: ERROR 
	if( L < 3)
	{
		AfxMessageBox("Error:SetupSystem_Close\nToo Few Number of Intervals to be Closed!");		
		return -1;	// 
	}	 	
	//////////////////////////////////////////////////// Case: More than Two Intervals
	int i;
	for  (i=0;i<L;i++)		// 2rd to Last-but-1 Rows
	{				
	
		if(i == 0)
		{
			delim1	= Knot[L]	- Knot[L-1]; 			// del[-1] = del{L-1]
			delim2	= Knot[L-1]	- Knot[L-2];			// del[-2] = del[L-2]
		}
		else
		if(i == 1)
		{
			delim1	= Knot[i]		- Knot[i-1]; 		// del[i-1]
			delim2	= Knot[L] 		- Knot[L-1];		// del[-1] = del[L-1]
		}
		else
		{	
			delim1	= Knot[i]		- Knot[i-1]; 		// del[i-1]
			delim2	= Knot[i-1]		- Knot[i-2];		// del[i-2]
		}
		if(i == (L-1) ) 
			delip1	= Knot[1]		- Knot[0];	// del[L] = del[0]
		else
			delip1	= Knot[i+2] 	- Knot[i+1];		// del[i+1]
		//////
		deli 	= Knot[i+1] 		- Knot[i];			// del[i]
		
		sumim1	= delim2 + delim1 + deli;
		sumi	= delim1 + deli   + delip1;
		sum		= delim1 + deli;
		////////////////////////
		a[i] = deli*deli/sumim1;
		b[i] = deli*(delim2+delim1)/sumim1 + delim1*(deli+delip1)/sumi;
		c[i] = delim1*delim1/sumi;
		////////////////////////// Corresponding RHS will be divided by sum in BC routine,so
		a[i] /= sum;
		b[i] /= sum;
		c[i] /= sum;
		///////////////
	}		
	//////////
	return 0;
		
}	
		
int CInter_C3::SetupBC_Close(pWORLD d,pDOUBLE w,PDMA3 s,int L,int nDim) 
{
	// B.C. consists only of RHS setup
	///////////////////////////////////////////////////////////////////////
	// NOTE: CLOSED Boundary Conditions:
	//			L = nData;		// Intervals = No. of Data, because CLOSED
	///////////////////////////////////////////////////////////////////////
	int i;
	/////////////////////
	for(i=0;i<L;i++)
	{
	
			s[i][0] = d[i].x;
			s[i][1] = d[i].y;
			s[i][2] = d[i].z;
			if(nDim == 4)
			s[i][3] = w[i];
	}		
	/////////
	return 0;	
}		
		
int CInter_C3::SetupSystem_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,pDOUBLE Knot,int L) 
{

	//////////////////////////////////////////////////////////////////
	//	KNOTS MUST BE SIMPLE i.e., NO MULTIPLICITY OTHER THAN 1		//
	//////////////////////////////////////////////////////////////////
	//		L 	= nData - 1;	// no. of intervals
	//////////////////////////////////////////////////////////////////////
	// Ist row: 	b[0],c[0] depends on BC -> will be done in BC Routine
	// Last row: 	a[L],b[L] depends on BC -> will be done in BC Routine
	//////////////////////////////////////////////////////////////////////
	double	deli, delim1, delim2, delip1, sumim1, sumi, sum;
	////////////////////////////////////////////////////
	a[0] = 0.0;
	c[L] = 0.0;
	//////////////////////////////////////////////////// Case: One Interval
	if( L == 1)		// b[0],c[0],a[L],b[L] will be done in
		return 0;	// BC routine 	
	//////////////////////////////////////////////////// Case: Two Intervals
	int i;
	//////////
	if( L == 2)		// b[0],c[0],a[L],b[L] will be done in
	{				// BC routine
	
		i = 1;										// 2nd row of Matrix
		//////
		delim2	= 0.0;	             				// del[i-2] = 0.0 for i = 1
		delim1	= Knot[i]	- Knot[i-1]; 			// del[i-1]
		deli 	= Knot[i+1] - Knot[i];				// del[i]
		delip1	= 0.0;								// del[i+1]	= 0.0 for i = 1
		
		sumim1	= delim2 + delim1 + deli;
		sumi	= delim1 + deli   + delip1;
		sum		= delim1 + deli;
		////////////////////////
		a[i] = deli*deli/sumim1;
		b[i] = deli*(delim2+delim1)/sumim1 + delim1*(deli+delip1)/sumi;
		c[i] = delim1*delim1/sumi;
		//////////////////////// Corresponding RHS will be divided by sum in BC routine,so
		a[i] /= sum;
		b[i] /= sum;
		c[i] /= sum;
		///////////////
		return 0;
		
	}	
	//////////////////////////////////////////////////// Case: More than Two Intervals
	for  (i=1;i<L;i++)		// 2rd to Last-but-1 Rows
	{				
	
		if(i == 1)
		{
			delim2	= 0.0;             					// del[i-2] = 0.0
			delip1	= Knot[i+2] - Knot[i+1];			// del[i+1]
		}
		else	
		if(i == L-1)
		{
			delim2	= Knot[i-1]	- Knot[i-2];            // del[i-2]
			delip1	= 0.0;								// del[i+1] = 0.0
		}
		else	
		{
			delim2	= Knot[i-1]	- Knot[i-2];            // del[i-2]
			delip1	= Knot[i+2] - Knot[i+1];			// del[i+1]
		}
		//////
		delim1	= Knot[i]	- Knot[i-1]; 				// del[i-1]
		deli 	= Knot[i+1] - Knot[i];					// del[i] 
		
		sumim1	= delim2 + delim1 + deli;
		sumi	= delim1 + deli   + delip1;
		sum		= delim1 + deli;
		////////////////////////
		a[i] = deli*deli/sumim1;
		b[i] = deli*(delim2+delim1)/sumim1 + delim1*(deli+delip1)/sumi;
		c[i] = delim1*delim1/sumi;
		//////////////////////// Corresponding RHS will be divided by sum in BC routine,so
		a[i] /= sum;
		b[i] /= sum;
		c[i] /= sum;
		///////////////
		
	}	
	//////////
	return 0;
		
}	
		
int CInter_C3::SetupBC_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
						 VECTOR ETan_L,VECTOR ETan_R,PDMA3 s,BOUNDARY BC_L,BOUNDARY BC_R,
						int L,int nDim) 
{
	//////////////////////////////////////////////////////////////////
	//	KNOTS MUST BE SIMPLE i.e., NO MULTIPLICITY OTHER THAN 1		//
	//////////////////////////////////////////////////////////////////
	//		L		= nData - 1;		// Intervals
	////////////////////////////////////////////////////
	// NOTE: 5 different Boundary Conditions:
	////////////////////////////////////////////////////
	b[0] 	= 1.0;
	c[0] 	= 0.0;
	a[L] 	= 0.0;
	b[L] 	= 1.0;
	//////////////////////////////////////////////////// Left End: i = 0
	switch(BC_L)
	{
		case	BC_CLAMPED:										// Clamped: FIXED
																// Slope = HORIZONTAL = 0

			ETan_L.v[0] = 1.0;
			ETan_L.v[1] = 0.0;
			ETan_L.v[2] = 0.0;
			//////////////////
			BC_Tangent(d,w,Knot,ETan_L,ETan_R,s,END_S0,L,nDim); 
//			BC_Auto(d,w,s,END_S0,L,nDim); 
			break;	
		case	BC_TANGENT:										// Specified-Tangent
			BC_Tangent(d,w,Knot,ETan_L,ETan_R,s,END_S0,L,nDim); 
			break;	
		case	BC_FREE:										// Free:Natural: Minimum Energy
			BC_Free(a,b,c,d,w,Knot,s,END_S0,L,nDim); 
			break;	
		case	BC_AUTO:	//fall thro'			
		case	BC_BESSEL:										// Tangent of the Quadratic
			BC_Bessel(d,w,Knot,s,END_S0,L,nDim); 
			break;	
		case	BC_QUADRATIC:									// Constant Curvature:Circular
			BC_Quadratic(a,b,c,d,w,Knot,s,END_S0,L,nDim); 
			break;	
		case	BC_NOT_A_KNOT:									// Not-A-Knot
		{
			AfxMessageBox("Not-a-Knot NOT Implemented!");
			return -1;
		}
		default:
		{
			AfxMessageBox("UNRECOGNIZED B.C.!");
			return -1;
		}
	}			  
	//////////////////////////////////////////////////// Middle: RHS
	int i;
	//////
	for(i=1;i<L;i++)
	{
	
			s[i][0] = d[i].x;
			s[i][1] = d[i].y;
			s[i][2] = d[i].z;
			if(nDim == 4)
			s[i][3] = w[i];
	}			
	//////////////////////////////////////////////////// Right End: i = L
	switch(BC_R)
	{
		case	BC_CLAMPED:										// Clamped: FIXED
																// Slope = HORIZONTAL = 0
			ETan_R.v[0] = 1.0;
			ETan_R.v[1] = 0.0;
			ETan_R.v[2] = 0.0;
			//////////////////
			BC_Tangent(d,w,Knot,ETan_L,ETan_R,s,END_SL,L,nDim); 
//			BC_Auto(d,w,s,END_SL,L,nDim); 
			break;	
		case	BC_TANGENT:										// Specified-Tangent
			BC_Tangent(d,w,Knot,ETan_L,ETan_R,s,END_SL,L,nDim); 
			break;	
		case	BC_FREE:										// Free:Natural: Minimum Energy
			BC_Free(a,b,c,d,w,Knot,s,END_SL,L,nDim); 
			break;	
		case	BC_AUTO:	//fall thro'			
		case	BC_BESSEL:										// Tangent of the Quadratic
			BC_Bessel(d,w,Knot,s,END_SL,L,nDim); 
			break;	
		case	BC_QUADRATIC:									// Constant Curvature:Circular
			BC_Quadratic(a,b,c,d,w,Knot,s,END_SL,L,nDim); 
			break;	
		case	BC_NOT_A_KNOT:									// Not-A-Knot
		{
			AfxMessageBox("Not-a-Knot NOT Implemented!");
			return -1;
		}
		default:
		{
			AfxMessageBox("UNRECOGNIZED B.C.!");
			return -1;
		}
					
	}			  
	/////////
	return 0;	
}		
				
int CInter_C3::BC_Auto(pWORLD d,pDOUBLE w,PDMA3 s,ENDS BC_End,int L,int nDim) 
{
	//////////////////////////////////////////////////////
	//	NOT BEING USED BECAUSE WRONG FORMULAE FOR CLAMPED
	//////////////////////////////////////////////////////
	AfxMessageBox("CInter_C3::BC_Auto: SHOULD NOT BE CALLED",MB_ICONSTOP);
		return -1;
	//////////////////////////////////////////////////////////////////////
	switch(BC_End)
	{
		case	END_S0:			// Left End: i = 0 

			s[0][0] = d[0].x;
			s[0][1] = d[0].y;
			s[0][2] = d[0].z;
			if(nDim == 4)
				s[0][3] = w[0];
			/////////	
			return 0;	
			  
		
			
		case	END_SL:			// Right End: i = L  

			s[L][0] = d[L].x;
			s[L][1] = d[L].y;
			s[L][2] = d[L].z;
			if(nDim == 4)
				s[L][3] = w[L];
			/////////	
			return 0;	
		
	}	
	/////////	
	return 0;	

}
				
int CInter_C3::BC_Tangent(pWORLD d,pDOUBLE w,pDOUBLE Knot,VECTOR ETan_L,VECTOR ETan_R,
							PDMA3 s,ENDS BC_End,int L,int nDim) 
{ 
 
	//							Specified-Tangent
	//////////////////////////////////////////////////////////////////////		
	double del0,delLm1;
	////////////////////////////////////////// 				
	switch(BC_End)
	{
		case	END_S0:			// Left End: i = 0 

			del0 	= Knot[1]	- Knot[0];
			////////////////////////////////////////
			s[0][0] = d[0].x + del0 * ETan_L.v[0]/3;
			s[0][1] = d[0].y + del0 * ETan_L.v[1]/3;
			s[0][2] = d[0].z + del0 * ETan_L.v[2]/3;
			if(nDim == 4)
				s[0][3] = w[0] + del0 * ETan_L.v[3]/3;  // estimated Tan0[0].v[3] = 0
			/////////	
			return 0;	
			  
		
			
		case	END_SL:			// Right End: i = L  

			delLm1	= Knot[L] 	- Knot[L-1];
			////////////////////////////////////////
			s[L][0] = d[L].x - delLm1 * ETan_R.v[0]/3;
			s[L][1] = d[L].y - delLm1 * ETan_R.v[1]/3;
			s[L][2] = d[L].z - delLm1 * ETan_R.v[2]/3;
			if(nDim == 4)
				s[L][3] = w[L] - delLm1 * ETan_R.v[3]/3;  // estimated Tan0[1].v[3] = 0
			/////////	
			return 0;	
	}	
	/////////	
	return 0;	

}
				
int CInter_C3::BC_Free(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim) 
{ 

	//							FREE:Natural: Minimum Energy		
	///////////////////////////////////////////////////////////////// One Curve Segment
	if(L == 1)												
	{
		// Turn out to be Linear
		//////////////////////////////////
		s[0][0] = (2 * d[0].x + d[1].x)/3;
		s[0][1] = (2 * d[0].y + d[1].y)/3;
		s[0][2] = (2 * d[0].z + d[1].z)/3;
		if(nDim == 4)
			s[0][3] = (2 * w[0] + w[1])/3;
		//////////////////////////////////
		s[1][0] = (2 * d[1].x + d[0].x)/3;
		s[1][1] = (2 * d[1].y + d[0].y)/3;
		s[1][2] = (2 * d[1].z + d[0].z)/3;
		if(nDim == 4)
			s[1][3] = (2 * w[1] + w[0])/3;
		/////////	
		return 0;
	}		
	///////////////////////////////////////////////////////////////// General: L>1 Curve Segments
	double del0,del1,sum,delLm1,delLm2;
	////////////////////////////////////////// 				
	switch(BC_End)
	{
		case	END_S0:			// Left End: i = 0 

			del0 	= Knot[1]	- Knot[0];
			del1 	= Knot[2]	- Knot[1];
			sum		= del0 + del1;
			
			b[0]	= 2. - del1/sum;
			c[0]	= 	 - del0/sum;
			//////////////////////////////////
			s[0][0] = d[0].x;
			s[0][1] = d[0].y;
			s[0][2] = d[0].z;
			if(nDim == 4)
				s[0][3] = w[0];
			/////////	
			return 0;	
			  
			
		case	END_SL:			// Right End: i = L 

			delLm1	= Knot[L] 	- Knot[L-1];
			delLm2	= Knot[L-1] - Knot[L-2];
	       	sum		= delLm1 + delLm2;
			/////
			a[L]	= 	 - delLm1/sum;
			b[L]	= 2. - delLm2/sum;
			//////////////////////////////////
			s[L][0] = d[L].x;
			s[L][1] = d[L].y;
			s[L][2] = d[L].z;
			if(nDim == 4)
				s[L][3] = w[L];
			/////////	
			return 0;	
	}	
	/////////	
	return 0;	

}
			
int CInter_C3::BC_Bessel(pWORLD d,pDOUBLE w,pDOUBLE Knot,PDMA3 s,ENDS BC_End,
								int L,int nDim) 
{ 

	//							BESSEL: Tangent of the End Quadratic		
	///////////////////////////////////////////////////////////////// One(L=1) Curve Segment
	if(L == 1)												
	{
		// Turn out to be Linear
		//////////////////////////////////
		s[0][0] = (2 * d[0].x + d[1].x)/3;
		s[0][1] = (2 * d[0].y + d[1].y)/3;
		s[0][2] = (2 * d[0].z + d[1].z)/3;
		if(nDim == 4)
			s[0][3] = (2 * w[0] + w[1])/3;
		//////////////////////////////////
		s[1][0] = (2 * d[1].x + d[0].x)/3;
		s[1][1] = (2 * d[1].y + d[0].y)/3;
		s[1][2] = (2 * d[1].z + d[0].z)/3;
		if(nDim == 4)
			s[1][3] = (2 * w[1] + w[0])/3;
		/////////	
		return 0;
	}		
	///////////////////////////////////////////////////////////////// General: L>2 Curve Segments
	double del0,del1,sum,alf,bet,delLm1,delLm2;
	////////////////////////////////////////// 				
	switch(BC_End)
	{
		case	END_S0:			// Left End: i = 0
			
			del0 	= Knot[1]	- Knot[0];
			del1 	= Knot[2]	- Knot[1];
			sum		= del0 + del1;
			alf		= del1/sum;
			bet		= 1. - alf;		// del0/sum
			////////////////////////////////////////// 				
			s[0][0] = ((alf+1)*d[0].x + d[1].x/alf - (bet*bet/alf)*d[2].x)/3;
			s[0][1] = ((alf+1)*d[0].y + d[1].y/alf - (bet*bet/alf)*d[2].y)/3;
			s[0][2] = ((alf+1)*d[0].z + d[1].z/alf - (bet*bet/alf)*d[2].z)/3;
			if(nDim == 4)
			s[0][3] = ((alf+1)*w[0] + w[1]/alf - (bet*bet/alf)*w[2])/3;
			/////////	
			return 0;	
			  
		
		
		case	END_SL:			// Right End: i = L
			
			delLm1	= Knot[L] 	- Knot[L-1];
			delLm2	= Knot[L-1] - Knot[L-2];
	       	sum		= delLm1 + delLm2;
	       	alf		= delLm2/sum;
			bet		= 1. - alf;		// delLm1/sum
			////////////////////////////////////////// 				
			s[L][0] = ((alf+1)*d[L].x + d[L-1].x/alf - (bet*bet/alf)*d[L-2].x)/3;
			s[L][1] = ((alf+1)*d[L].y + d[L-1].y/alf - (bet*bet/alf)*d[L-2].y)/3;
			s[L][2] = ((alf+1)*d[L].z + d[L-1].z/alf - (bet*bet/alf)*d[L-2].z)/3;
			if(nDim == 4)
			s[L][3] = ((alf+1)*w[L] + w[L-1]/alf - (bet*bet/alf)*w[L-2])/3;
			/////////	
			return 0;	
	}				
	/////////	
	return 0;	

}
				
int CInter_C3::BC_Quadratic(pDOUBLE a,pDOUBLE b,pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim) 
{ 

	//						Constant Curvature:Circular								
	///////////////////////////////////////////////////////////////// One(L=1) Curve Segment
	if(L == 1)												
	{
		// Turn out to be Linear
		//////////////////////////////////
		s[0][0] = (2 * d[0].x + d[1].x)/3;
		s[0][1] = (2 * d[0].y + d[1].y)/3;
		s[0][2] = (2 * d[0].z + d[1].z)/3;
		if(nDim == 4)
			s[0][3] = (2 * w[0] + w[1])/3;
		//////////////////////////////////
		s[1][0] = (2 * d[1].x + d[0].x)/3;
		s[1][1] = (2 * d[1].y + d[0].y)/3;
		s[1][2] = (2 * d[1].z + d[0].z)/3;
		if(nDim == 4)
			s[1][3] = (2 * w[1] + w[0])/3;
		/////////	
		return 0;
	}		
	///////////////////////////////////////////////////////////////// General: L>2 Curve Segments
	double del0,del1,sum,delLm1,delLm2;
	////////////////////////////////////////// 				
	switch(BC_End)
	{
		case	END_S0:			// Left End: i = 0

			del0 	= Knot[1]	- Knot[0];
			del1 	= Knot[2]	- Knot[1];
			sum		= del0 + del1;
			//////////////////////
			b[0]	= del0/sum;
			c[0]	= b[0];
			//////////////////////////////
			s[0][0] = (d[0].x - d[1].x)/3;
			s[0][1] = (d[0].y - d[1].y)/3;
			s[0][2] = (d[0].z - d[1].z)/3;
			if(nDim == 4)
			s[0][3] = (w[0] - w[1])/3;
			/////////
			return 0;	


		case	END_SL:			// Right End: i = L 

			delLm1	= Knot[L] 	- Knot[L-1];
			delLm2	= Knot[L-1] - Knot[L-2];
	       	sum		= delLm1 + delLm2;
			////////////////////////////////
			a[L]	= delLm1/sum;
			b[L]	= a[L];
			//////////////////////////////////
			s[L][0] = (d[L].x - d[L-1].x)/3;
			s[L][1] = (d[L].y - d[L-1].y)/3;
			s[L][2] = (d[L].z - d[L-1].z)/3;
			if(nDim == 4)
			s[L][3] = (w[L] - w[L-1])/3;
			/////////
			return 0;	
	}	
	/////////	
	return 0;	

}
				
int CInter_C3::BC_Not_A_Knot(pDOUBLE a,pDOUBLE b[],pDOUBLE c,pWORLD d,pDOUBLE w,pDOUBLE Knot,
								PDMA3 s,ENDS BC_End,int L,int nDim)
{ 

		
	//						Not-A-Knot Condition								
	///////////////////////////////////////////////////////////////////////////////
	double del0,del1,sum,alf,bet,delLm1,delLm2;
	////////////////////////////////////////// 				
	switch(BC_End)
	{
		case	END_S0:			// Tangent of the Quadratic
		//////////////////////////////////////////////////// Left End: i = 0
			del0 	= Knot[1]	- Knot[0];
			del1 	= Knot[2]	- Knot[1];
			sum		= del0 + del1;
			alf		= del1/sum;
			bet		= del0/sum;		// 1 - alf
			/////////	
			return 0;	
			
		case	END_SL:			// Tangent of the Quadratic 
		//////////////////////////////////////////////////// Right End: i = L
			delLm1	= Knot[L] 	- Knot[L-1];
			delLm2	= Knot[L-1] - Knot[L-2];
	       	sum		= delLm1 + delLm2;
	       	alf		= delLm2/sum;
	       	bet		= delLm1/sum;		// 1 - alf
			/////////	
			return 0;	
			/////
	}	
	/////////	
	return 0;	

}

int CInter_C3::SolveSystem_Open(pDOUBLE a,pDOUBLE b,pDOUBLE c,PDMA3 RHS,PDMA3 Sol,
						int L,int nDim) 
{

	int nSize = L;
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Just Before Calling\nSolve_TriDiagonal");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
		j = sprintf(buf,"alfa[%d]     beta[%d]     gama[%d]\n",
							nSize+1, nSize+1, nSize+1);
		for(k=0;k<=L;k++)
		{
		   j += sprintf( buf + j, "%7.2f %7.2f %7.2f\n", a[k],b[k],c[k] );
		}
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
	    ///////////////////
		j = sprintf(buf,"RHS[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=L;m++)
		{
			for(k=0;k<nDim;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", RHS[m][k] );
			} 
	   		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}
#endif				
	//////////////////////////////////////////////////// solve Tridiagonal
	C3DMath Math3D;
	if( (Math3D.Solve_TriDiag(a, b, c, RHS, Sol, nSize, nDim) )<0)
	{
		AfxMessageBox("SolveSystem_Open:Error\nSolveTriDiag!");
		return -1;
	}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k,m;
		j = sprintf(buf,"Sol[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=L;m++)
		{
			for(k=0;k<nDim;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", Sol[m][k] );
			} 
   			j += sprintf( buf + j, "\n");
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
	/////////				
	return 0;
}
				
int CInter_C3::SolveSystem_Close(pDOUBLE a,pDOUBLE b,pDOUBLE c,PDMA3 RHS,PDMA3 Sol,
						int L,int nDim) 
{

	int nSize = L - 1;
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k,m;
		//////////
		sprintf(buf,"Just Before Calling\nSolve_TriDiagonalPeriodic");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"alfa[%d]     beta[%d]     gama[%d]\n",
							nSize+1, nSize+1, nSize+1);
		for(k=0;k<=nSize;k++)
		{
	   		j += sprintf( buf + j, "%7.1f %7.1f %7.1f\n", a[k],b[k],c[k] );
		}
		AfxMessageBox(*str);
    	///////////////////
		j = sprintf(buf,"RHS[%d][%d]\n",L,nDim);
		for(m=0;m<=nSize;m++)
		{
			for(k=0;k<nDim;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", RHS[m][k] );
			} 
   			j += sprintf( buf + j, "\n");
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
	//////////////////////////////////////////////////// solve Tridiagonal
	C3DMath Math3D;
	if( (Math3D.Solve_TriDiagPeriodic(a, b, c, RHS, Sol, nSize, nDim) )<0)
	{
		AfxMessageBox("SolveSystem_Close:Error\nSolveTriDiagPeriodic!");
		return -1;
	}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"Sol[%d][%d]\n",L,nDim);
		for(m=0;m<=nSize;m++)
		{
			for(k=0;k<nDim;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", Sol[m][k] );
			} 
   			j += sprintf( buf + j, "\n");
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
	/////////				
	return 0;
}
				
int CInter_C3::FillUpSpline_Open(PDMA3 Sol,int L,pWORLD Data,pDOUBLE Wts_DT,
						pWORLD Con,pDOUBLE Wts,int nDim) 
{
	//////////////////////////////////////////////////// fill up Controls and Wts (Spline)
	int k;
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,m;
		//////////
		sprintf(buf,"FillUpSpline_Open:NONRATIONAL");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"Data[%d]\n     X     Y    Z\n",L+1);
		for(k=0;k<=L;k++)
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
		j = sprintf(buf,"Sol[%d][%d]\n",L+1,3);
		for(m=0;m<L+1;m++)
		{
			for(k=0;k<3;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", Sol[m][k] );
			} 
	   		j += sprintf( buf + j, "\n");
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
	if(3 == nDim)
	{
		////////////////////////////////////////// First: 1 of them --------------|
		Con[0].x 	= Data[0].x;                                	// 	          |
		Con[0].y 	= Data[0].y;                                 	//            |
		Con[0].z 	= Data[0].z;                                  	//  	 	  |
		////////////////////////////////////////// In-between: (L + 1) of them ---| 
		for(k=0;k<=L;k++)                                           //            |
		{                                                                     //  |---- (L+3) of them
			Con[k+1].x 	= Sol[k][0]; 	                            //            |
			Con[k+1].y 	= Sol[k][1];	                            //            |
			Con[k+1].z 	= Sol[k][2]; 	 	                        //           /
		}                            	                            //         /
		////////////////////////////////////////// Last: 1 of them ----------/ 
		Con[L+2].x 	= Data[L].x;	 
		Con[L+2].y 	= Data[L].y; 
		Con[L+2].z 	= Data[L].z;
		////////////////////////
	}	
	else	
	if(4 == nDim)
	{
		double r;
		////////////////////////////////////////// First: 1 of them -----------------|
		r			= 1/Wts_DT[0];										//	             |
		Con[0].x 	= Data[0].x * r;          						// 	      		 |
		Con[0].y 	= Data[0].y * r;                               	// 	  	    	 |
		Con[0].z 	= Data[0].z * r;                               	// 	   		     |
		Wts[0]		= Wts_DT[0];                                         //       	     |	
		////////////////////////////////////////// In-between: (L + 1) of them ------| 
		for(k=0;k<=L;k++)                                           //               |
		{                                                                     //     |---- (L+3) of them
			r = 1./Sol[k][3];                                       //   		     |
			Con[k+1].x 	= Sol[k][0] * r;                            //               |
			Con[k+1].y 	= Sol[k][1] * r;                            //             /
			Con[k+1].z 	= Sol[k][2] * r;                            //           /
			Wts[k+1]	= Sol[k][3];                                //         /
		}                                                           //       /
		////////////////////////////////////////// Last: 1 of them --------/ 
		r			= 1/Wts_DT[L];										
		Con[L+2].x 	= Data[L].x * r;	 
		Con[L+2].y 	= Data[L].y * r; 
		Con[L+2].z 	= Data[L].z * r;
		Wts[L+2]	= Wts_DT[L];
		/////////////
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		j = sprintf(buf,"B_SplineCon[%d]\n     X     Y    Z\n",L+3);
		for(k=0;k<=(L+2);k++)
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
		if(4==nDim)
		{
			j = sprintf(buf,"B_SplineWts[%d]\n",L+3);
			for(k=0;k<=(L+2);k++)
			{
		  		j += sprintf( buf + j, "%7.1f\n", Wts[k] );
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
		}
	    ///////////////////
	    delete str;
	}	    
#endif				
	/////////////
	return 0;
}
				
int CInter_C3::FillUpSpline_Close(PDMA3 Sol,int L,pWORLD Data,pDOUBLE Wts_DT,
						pWORLD Con,pDOUBLE Wts,int nDim) 
{
	//			int L = nData;
	//////////////////////////////////////////////////// fill up Controls and Wts (Spline)
	int k;
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,m;
		//////////
		sprintf(buf,"FillUpSpline_CLOSE:NONRATIONAL");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"Data[%d]\n     X     Y    Z\n",L);
		for(k=0;k<L;k++)
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
		j = sprintf(buf,"Sol[%d][%d]\n",L,3);
		for(m=0;m<L;m++)
		{
			for(k=0;k<3;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", Sol[m][k] );
			} 
	   		j += sprintf( buf + j, "\n");
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
	if(3 == nDim)
	{
		////////////////////////////////////////// First: 1 of them --------------|
		Con[0].x 	= Sol[L-1][0];	// d[-1] = d[L-1]              	// 	          |
		Con[0].y 	= Sol[L-1][1];                                 	//            |
		Con[0].z 	= Sol[L-1][2];                                  	//  	  |
		////////////////////////////////////////// In-between: L of them ---------| 
		for(k=0;k<L;k++)                                           //             |
		{                                                                     //  |---- (L+2) of them
			Con[k+1].x 	= Sol[k][0]; 	                            //            |---- L = nData
			Con[k+1].y 	= Sol[k][1];	                            //            |
			Con[k+1].z 	= Sol[k][2]; 	 	                        //           /
		}                            	                            //         /
		////////////////////////////////////////// Last: 1 of them ----------/ 
		Con[L+1].x 	= Sol[0][0];	// d[L] = d[0]	 
		Con[L+1].y 	= Sol[0][1]; 
		Con[L+1].z 	= Sol[0][2];
		////////////////////////
	}	
	else	
	if(4 == nDim)
	{
		double r;
		////////////////////////////////////////// First: 1 of them --------------|
		r 			= 1./Sol[L-1][3];
		Con[0].x 	= Sol[L-1][0] * r;	// d[-1] = d[L-1]          	// 	          |
		Con[0].y 	= Sol[L-1][1] * r;                             	//            |
		Con[0].z 	= Sol[L-1][2] * r;                               	//  	  |
		Wts[0]		= Sol[L-1][3];
		////////////////////////////////////////// In-between: L of them ---------| 
		for(k=0;k<L;k++)                                           //             |
		{                                                                     //  |---- (L+2) of them
			r 			= 1./Sol[k][3];
			Con[k+1].x 	= Sol[k][0] * r;                            //            |---- L = nData
			Con[k+1].y 	= Sol[k][1] * r;                            //            |
			Con[k+1].z 	= Sol[k][2] * r; 	                        //           /
			Wts[k+1]	= Sol[k][3];
		}                            	                            //         /
		////////////////////////////////////////// Last: 1 of them ----------/ 
		r 			= 1./Sol[0][3];
		Con[L+1].x 	= Sol[0][0] * r;	// d[L] = d[0]	 
		Con[L+1].y 	= Sol[0][1] * r; 
		Con[L+1].z 	= Sol[0][2] * r;
		Wts[L+1] 	= Sol[0][3];
		////////////////////////
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		j = sprintf(buf,"B_SplineCon[%d]\n     X     Y    Z\n",L+2);
		for(k=0;k<(L+2);k++)
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
		if(4==nDim)
		{
			j = sprintf(buf,"B_SplineWts[%d]\n",L+2);
			for(k=0;k<(L+2);k++)
			{
		  		j += sprintf( buf + j, "%7.1f\n", Wts[k] );
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
		}
	    ///////////////////
	    delete str;
	}	    
#endif				
	/////////////
	return 0;
}

int CInter_C3::Convert_BS2BZ(PDMA3 BS,pDOUBLE Knot,PDMA3 BZ,
						int L,BOOL bClosed,int nDim) 
{
	//							NON-RATIONAL COUNTERPART
	////////////////////////////////////////////////////////////////
	//		Converts Cubic B-Spline to Bezier --> still C2 class
	//		1. Spline can be Rational(nDim = 4) or NonRational(nDim = 3)
	//		2. Spline can be Open or Closed.
	//						KNOTS ARE SIMPLE
	////////////////////////////////////////////////////////////////
	// OPEN: L = nData - 1 = intervals
	//		Spline Dimension :  L+3: (0,...,L+2) 
	//		Bezier Dimension : 3L+1: (0,...,3L)  
	//
	// CLOSE: L = nData = intervals: Periodic( Period = L)
	//		Spline Dimension :  L: (0,...,L-1) 
	//		Bezier Dimension : 3L: (0,...,3L - 1)  
	////////////////////////////////////////////////////////////////
	//	
	//		del.i = Knot[i+1] - Knot[i] = Forward Difference
	//
	//		BZ[0] = BS[0]; BZ[1] = BS[1];
	//		BZ[2] = (del.1*BS[0]+del.0*BS[1])/del.0+del.1
	//		
	//		BZ[3i-1] = (del.i*BS[i]+(del.i-2+del.i-1)*BS[i+1])/(del.i-2+del.i-1+del.i)
	//		BZ[3i+1] = (del.i*BS[i]+(del.i-1+del.i  )*BS[i+1])/(del.i-2+del.i-1+del.i)
	//		BZ[3i  ] = del.i*BZ[3i-1]/(del.i-1+del.i)+del.i-1*BZ[3i+1]/(del.i-1+del.i)
	//
	//		OPEN:
	//				BZ[3L-2] = (del.L-1*BS[L]+del.L-2*BS[L+1])/(del.L-2+del.L-1)
	//				BZ[3L-1] = BS[L+1]
	//				BZ[3L  ] = BS[L+2]		
	//
	//		CLOSED: L MUST BE >= 3
	//				BZ[3L-2] = (del.L-1*BS[L%Period]+del.L-2*BS[(L+1)%Period])/(del.L-2+del.L-1)
	//				BZ[3L-1] = BS[(L+1)%Period]
	//				BZ[3L  ] = modulo Operation Done in Generation Time in ElemObj.Curve3		
	//
	///////////////////////////////////////////////////////////////////////////////////////////				
	int k,j,Lt3; 
	/////////////////////////////////////////////////////////////////// First Points
	if(!bClosed)												// OPEN
	{
		for(j=0;j<nDim;j++)
		{
			BZ[0][j]	= BS[0][j];
			BZ[1][j]	= BS[1][j];
		}	
		////////////////
		double deli,delip1,sum,sum0,sum1;//,delim1,sum2,sum3,sum4;
		if(L>1)
		{
			delip1 = Knot[2] - Knot[1]; 
			deli   = Knot[1] - Knot[0];
			sum0   = Knot[2] - Knot[0];
			///////////////////////////	
			for(j=0;j<nDim;j++)
			{
				BZ[2][j] = (delip1 * BS[1][j] + deli   * BS[2][j] ) / sum0;
			}			    	  	
		}	 
		////////////////
		if(L>2)
		{
			sum1   = Knot[3] - Knot[1];
			sum    = Knot[3] - Knot[0];
			///////////////////////////
			for(j=0;j<nDim;j++)
			{
				BZ[4][j] = (sum1   * BS[2][j] + deli   * BS[3][j] ) / sum;
				BZ[3][j] = (delip1 * BZ[2][j] + deli   * BZ[4][j] ) / sum0;
			}			    	  	
		}
	}
	else												// CLOSED (ALWAYS L>2)
	{
		////////////////
		double deli,delim1,delim2,delip1,sum0,sum1,sum2,sum3,sum4;
		////////////
		delim2 = Knot[L-1] 		- Knot[L-2];	// del[-2] = del[L-2] 
		delim1 = Knot[L] 		- Knot[L-1];	// del[-1] = del[L-1] 
		delip1 = Knot[2] 		- Knot[1]; 
		deli   = Knot[1] 		- Knot[0];		// i = 0
		sum0   = delim2 + delim1;
		sum1   = sum0 + deli;
		sum2   = deli + delip1;
		sum3   = delim1 + sum2;
		sum4   = delim1 + deli;	
		///////////////////////////
		for(j=0;j<nDim;j++)
		{
			BZ[3*L-1][j]	= (deli * BS[0    ][j] + sum0   * BS[1][j])/sum1; // BZ[-1] = BZ[3L-1]
			BZ[1]    [j]	= (sum2 * BS[1    ][j] + delim1 * BS[2][j])/sum3;
			BZ[0]    [j]	= (deli * BZ[3*L-1][j] + delim1 * BZ[1][j])/sum4;
		}
			
		delim2 = Knot[L] 		- Knot[L-1];	// del[-1] = del[L-1] 
		delim1 = Knot[1] 		- Knot[0];
		delip1 = Knot[3] 		- Knot[2]; 
		deli   = Knot[2] 		- Knot[1];		// i = 1
		sum0   = delim2 + delim1;
		sum1   = sum0 + deli;
		sum2   = deli + delip1;
		sum3   = delim1 + sum2;
		sum4   = delim1 + deli;	
		///////////////////////////
		for(j=0;j<nDim;j++)
		{
			BZ[2][j] = (deli * BS[1][j] + sum0   * BS[2][j] ) / sum1;
			BZ[4][j] = (sum2 * BS[2][j] + delim1 * BS[3][j] ) / sum3;
			BZ[3][j] = (deli * BZ[2][j] + delim1 * BZ[4][j] ) / sum4;
		}			    	  	
	}
	/////////////////////////////////////////////////////////////////// In-Between Points
	for (k=2;k<L-1;k++)
	{
		Lt3 = 3 * k;
		////////////////
		double deli,delim1,delip1,sum0,sum1,sum2,sum3,sum4;
		////////////
		delim1 = Knot[k] 		- Knot[k-1]; 
		delip1 = Knot[2] 		- Knot[1]; 
		deli   = Knot[k+1] 		- Knot[k];
		sum0   = Knot[k+2]	 	- Knot[k];
		sum1   = Knot[k] 		- Knot[k-2];
		sum2   = Knot[k+1] 		- Knot[k-2];
		sum3   = Knot[k+2]		- Knot[k-1];
		sum4   = Knot[k+1] 		- Knot[k-1];	
		///////////////////////////
		for(j=0;j<nDim;j++)
		{
			BZ[Lt3-1][j] = ( deli * BS[k    ][j]	+  sum1   * BS[k+1    ][j]   ) / sum2;	
			BZ[Lt3+1][j] = ( sum0 * BS[k+1  ][j]	+  delim1 * BS[k+2    ][j]   ) / sum3;	
			BZ[Lt3  ][j] = ( deli * BZ[Lt3-1][j]	+  delim1 * BZ[Lt3+1  ][j]   ) / sum4;	
		}
	}			
	/////////////////////////////////////////////////////////////////// Last Points
	Lt3	= 3 * L;
	////////////
	if(!bClosed)												// OPEN
	{
		////////////////
		double deli,delim1,sum0,sum1,sum2;
		////////////
		if(L>2)
		{
			delim1 = Knot[L] 	- Knot[L-1]; 
			sum0   = Knot[L-1] 	- Knot[L-3];
			sum1   = Knot[L] 	- Knot[L-3];
			///////////////////////////	
			for(j=0;j<nDim;j++)
				BZ[Lt3-4][j] = ( delim1 * BS[L-1][j] + sum0 * BS[L][j]  ) / sum1;		
		}	 
		////////////////
		if(L>1)
		{
			delim1 = Knot[L] 	- Knot[L-1]; 
			deli   = Knot[L-1]	- Knot[L-2];	
			sum1   = Knot[L] 	- Knot[L-3];
			sum2   = Knot[L]	- Knot[L-2];	
			///////////////////////////	
			for(j=0;j<nDim;j++)
			{
				BZ[Lt3-2][j] = ( delim1 * BS[L    ][j] + deli * BS[L+1  ][j]   ) / sum2;		
				BZ[Lt3-3][j] = ( delim1 * BZ[Lt3-4][j] + deli * BZ[Lt3-2][j]   ) / sum2;
			}		
		}
		////////////////
		for(j=0;j<nDim;j++)
		{
			BZ[Lt3-1][j] = BS[L+1][j];
			////////////////////////// Open
			BZ[Lt3  ][j] = BS[L+2][j];
			/////////////
		}	
	}	
	else														// CLOSED (ALWAYS L>2)
	{

		////////////////
		double deli,delim1,delim2,delip1,sum0,sum1,sum2,sum3,sum4;
		////////////
		delim2	= Knot[L-2]	- Knot[L-3]; 
		delim1	= Knot[L-1]	- Knot[L-2]; 
		deli	= Knot[L] 	- Knot[L-1]; 
		delip1	= Knot[1] 	- Knot[0];	// del[L] = del[0]; 
		sum0   	= delim2 + delim1;
		sum1   	= sum0   + deli;
		sum2   	= deli   + delip1;
		sum3	= sum2   + delim1;
		sum4	= deli	 + delim1;
		///////////////////////////	
		for(j=0;j<nDim;j++)
		{
			BZ[Lt3-4][j] = ( deli   * BS[L-1  ][j]  + sum0   * BS[L    ][j]) / sum1;		
			BZ[Lt3-2][j] = ( sum2   * BS[L    ][j] 	+ delim1 * BS[L+1  ][j]) / sum3;
			BZ[Lt3-3][j] = ( deli   * BZ[Lt3-4][j] 	+ delim1 * BZ[Lt3-2][j]) / sum4;
		}
			////////////////
//			BZ[Lt3-1][j]  already done before	
			/////////////
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k,m,nSize;
		//////////
		sprintf(buf,"ConvertBStoBZ");
		AfxMessageBox(*str);
		///////////////////
		nSize = L+2;
		if(bClosed)
			nSize = L+1;
		j = sprintf(buf,"BS[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=nSize;m++)
		{
   			j += sprintf( buf + j, "%2d ",m  );
			for(k=0;k<nDim;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", BS[m][k] );
			} 
   			j += sprintf( buf + j, "\n");
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
    	nSize = Lt3;
    	if(bClosed)
    		nSize = Lt3-1;
		j = sprintf(buf,"BZ[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=nSize;m++)
		{
   			j += sprintf( buf + j, "%2d ",m  );
			for(k=0;k<nDim;k++)
			{
	   			j += sprintf( buf + j, "%7.2f ", BZ[m][k] );
			} 
   			j += sprintf( buf + j, "\n");
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
				
int CInter_C3::Convert_BS2BZ(PDMA3 Sol,pWORLD Data,pDOUBLE w_DT,pDOUBLE Knot,
						pDOUBLE w_BZ,pWORLD Bez,int L,BOOL bClosed,int nDim) 
{
	//							RATIONAL B-Spline
	////////////////////////////////////////////////////////////////
	//		Converts Cubic B-Spline to Bezier --> still C2 class
	//						KNOTS ARE SIMPLE
	////////////////////////////////////////////////////////////////
	// OPEN: L = nData - 1 = intervals
	//		Spline Dimension :  L+3: (0,...,L+2) 
	//		Bezier Dimension : 3L+1: (0,...,3L)  
	//
	// CLOSE: L = nData = intervals: Periodic( Period = L)
	//		Spline Dimension :  L: (0,...,L-1) 
	//		Bezier Dimension : 3L: (0,...,3L - 1)  
	////////////////////////////////////////////////////////////////
	//
	PDMA3 pBS,pBZ;
	pBS	= new double[L+2+1][4];	// reserve for Rational
	pBZ = new double[3*L+1][4];	// reserve for Rational
	//////////////////////////////////////////////////////////////// Spline: 4D PreImage
	Set4DPreImage_BS(Sol,Data,w_DT,pBS,L,bClosed,nDim);
	//////////////////////////////////////////////////////////////// 4D_BS --> 4D_BZ
	Convert_BS2BZ(pBS,Knot,pBZ,L,bClosed,nDim); 
	//////////////////////////////////////////////////////////////// Bezier: 3D Image & Weights
	FillUpBezier(pBZ,Bez,w_BZ,L,bClosed,nDim); 
	///////////////////////////////////////////
	delete [] pBS;
	delete [] pBZ;
	//////////////
	return 0;
				
} 

int CInter_C3::Set4DPreImage_BS(PDMA3 Sol,pWORLD Data,pDOUBLE w_DT,PDMA3 BS,
						int L,BOOL bClosed,int nDim)
{																	
	//////////////////////////////////////////////////// Augment 
	int k;
	////////////
	if(!bClosed)														// OPEN
	{
		////////////////////////////////////////// First: 1 of them 
		BS[0][0] 	= Data[0].x;                                	
		BS[0][1] 	= Data[0].y;                                 	
		BS[0][2] 	= Data[0].z;
		if(nDim>3)                                  	//  	 	
			BS[0][3] 	= w_DT[0];
		////////////////////////////////////////// In-between: L  of them  
		for(k=0;k<=L;k++)                                           
		{                                                           
			BS[k+1][0] 	= Sol[k][0]; 	                            
			BS[k+1][1] 	= Sol[k][1];	                            
			BS[k+1][2] 	= Sol[k][2]; 	 	                        
			if(nDim>3)                                  			
				BS[k+1][3] 	= Sol[k][3];
		}                            	                            //         /
		////////////////////////////////////////// Last: 1 of them ----------/ 
		BS[L+2][0] 	= Data[L].x;	 
		BS[L+2][1]	= Data[L].y; 
		BS[L+2][2] 	= Data[L].z;
		if(nDim>3)   // 012099 added                               	//  	 	
			BS[L+2][3] 	= w_DT[L]; // 012099 added
		///////////// 
	}
	else																// CLOSED
	{
		////////////////////////////////////////// First: 1 of them --------------|
		BS[0][0] 	= Sol[L-1][0];	// d[-1] = d[L-1]              	// 	          |
		BS[0][1] 	= Sol[L-1][1];                                 	//            |
		BS[0][2] 	= Sol[L-1][2];                                  	//  	  |
		if(nDim>3)   // 012099 added                               	//  	 	
			BS[0][3] 	= Sol[L-1][3]; // 012099 added
		////////////////////////////////////////// In-between: L of them ---------| 
		for(k=0;k<L;k++)                                           //             |
		{                                                                     //  |---- (L+2) of them
			BS[k+1][0] 	= Sol[k][0]; 	                            //            |---- L = nData
			BS[k+1][1] 	= Sol[k][1];	                            //            |
			BS[k+1][2] 	= Sol[k][2]; 	 	                        //           /
			if(nDim>3)   // 012099 added                               	//  	 	
				BS[k+1][3] 	= Sol[k][3]; // 012099 added
		}                            	                            //         /
		////////////////////////////////////////// Last: 1 of them ----------/ 
		BS[L+1][0] 	= Sol[0][0];	// d[L] = d[0]	 
		BS[L+1][1] 	= Sol[0][1]; 
		BS[L+1][2] 	= Sol[0][2];
        ////////////////////////
		if(nDim>3)   // 012099 added                               	//  	 	
			BS[L+1][3] 	= Sol[0][3]; // 012099 added
	} 
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k,m,nSize;
		//////////
		sprintf(buf,"Set4DPreImage");
		AfxMessageBox(*str);
	    ///////////////////
	    nSize = L;
	    if(bClosed)
	    	nSize--;
		j = sprintf(buf,"Sol[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=nSize;m++)
		{
 	  		j += sprintf( buf + j, "%2d ",m  );
			for(k=0;k<nDim;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", Sol[m][k] );
			} 
 	  		j += sprintf( buf + j, "\n");
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
	    nSize = L+2;
	    if(bClosed)
	    	nSize = L+1;
		j = sprintf(buf,"BS[%d][%d]\n",nSize+1,nDim);
		for(m=0;m<=nSize;m++)
		{
 	  		j += sprintf( buf + j, "%2d ",m  );
			for(k=0;k<nDim;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", BS[m][k] );
			} 
 	  		j += sprintf( buf + j, "\n");
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
	//////////
	return 0;			
}

int CInter_C3::FillUpBezier(PDMA3 BZ4,pWORLD Con,pDOUBLE Wts,int L,BOOL bClosed,int nDim) 
{
	
	//////////////////////////////////////////////////// fill up Controls and Wts (Bezier)
	int k,Lt3;
	//////////
	Lt3 = 3 * L + 1;
	if(bClosed)
		Lt3--;	
	//////////////////////////////////////////
	if(nDim>3)									// RATIONAL
	{
		for(k=0;k<Lt3;k++)                        
		{                                                                     
			double r = 1./BZ4[k][3];
			Con[k].x 	= BZ4[k][0] * r;
			Con[k].y 	= BZ4[k][1] * r; 
			Con[k].z 	= BZ4[k][2] * r;
			Wts[k]	= BZ4[k][3];
		}	
	}
	else										// NonRATIONAL
	{	 
		for(k=0;k<Lt3;k++)                        
		{                                                                     
			Con[k].x 	= BZ4[k][0]; 	                           
			Con[k].y 	= BZ4[k][1];	                            
			Con[k].z 	= BZ4[k][2]; 	 	                        
		}
	}	                            	                            
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(  1 != 1 ) // iDLL = 12 , Module = 0
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

int CInter_C3::UpdateToMultKnots(pDOUBLE Knots,int nKnots,pDOUBLE MKnots,
									int nMKnots, int nOrder)
{
	//////////
	return 0;
}

void CInter_C3::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CInter_C3:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CInter_C3:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////
