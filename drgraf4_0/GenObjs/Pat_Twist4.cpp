// CPat_Twist4.cpp : implementation of the CPat_Twist4 class
//
	//					NON-RATIONAL PATCH
	//////////////////////////////////////////////////////////////////////
	//					             m-1 n-1				 m-1	 n-1
	//	Twist(u,v) = d2x/dudv = m*n*(sum sum (del11b(i,j) * B (u) * B (v))
	//					             i=0 j=0				 i       j
	//////////////////////////////////////////////////////////////////////
	// Twist Surface is a Bezier Surface of (m-1)x(n-1) coeffs
	// where coeffs are del11b(i,j) given by
	//
	//		del11b(i,j) = del01b(i+1,j) - del01b(i,j),	i = 1,...,m
	//													j = 1,...,n
	// where
	//		del01b(i+1,j)	=	b(i+1,j+1)	-	b(i+1,j)
	//		del01b(i,j)		=	b(i,j+1)	-	b(i,j)
	//////////////////////////////////////////////////////////////////////
	//					RATIONAL PATCH
	//////////////////////////////////////////////////////////////////////
	// Need To SubDivide at (u,v)

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
#include "Surface4.h"

#include "Pat_Twist4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPat_Twist4

IMPLEMENT_DYNAMIC(CPat_Twist4,CSurface4)
/*
BEGIN_MESSAGE_MAP(CPat_Twist4,CSurface4)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPat_Twist4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////////////////////////////
CPat_Twist4::CPat_Twist4()
{ 
	m_nsubdivisions	= 1;

} 
////////////////////////////////////////////////////////////////////////////
int CPat_Twist4::MakeTwists		// RATIONAL BEZIER Patches
			(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Tangent Array
			)
{
	if(nDim_U == 4 || nDim_V == 4)	// Only NonRational
		return -1;
	//////////////////////////////
	int	CtlStep_U = nDegree_U; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	int	CtlStep_V = nDegree_V; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	//////////////////////////////////////////////////////////////////
	pWORLD	p_U,p_V;
//	pDOUBLE pw_U,pw_V;
	int		i,j,u, v, VnCU,	nOutP = 0, nOut = 0, nMaxU,nMaxV,nMaxUV;
	int		nt_U,nt_V,U[4], V[4], vIx[4][4];	// vertex indices
	BOOL	bLast_U,bLast_V;
	////////////////////////////////////// memory for array of pointers
	PW44 pInC_44 = new pWORLD[4][4];	//	Control Pt. array for the patch: RESERVED for Maximum Cubic
	/////////////////////////////////////////////////////// Totals in U dir
	int nEmitTot_U=0;
	for(u=0;u<nPatches_U;u++)
		nEmitTot_U += *(Num_t_U + u);
	nEmitTot_U++;
	//////////////////////////////////////////////////////////////////////////// V direction:LOOP
	p_V		= pOut_UV; 
//	pw_V	= pOutWts_UV;
	/////////////////////	
	for( V[0] = v = 0; v < nPatches_V; v++, V[0]+=CtlStep_V ) 
	{
		for(i=1;i<=nDegree_V;i++)
			V[i] = (V[0]+i) % nCon_V;
		nt_V = *(Num_t_V + v);
		//////////////////////////////////////////////////////////// U direction:LOOP 
		p_U		= p_V; 
//		pw_U	= pw_V;
		/////////////////////////////	
		for( U[0] = u = 0; u < nPatches_U; u++, U[0]+=CtlStep_U ) 
		{
			/////////////////////////////////////////////////
			bLast_U = (u == (nPatches_U-1))?TRUE:FALSE;
			bLast_V = (v == (nPatches_V-1))?TRUE:FALSE;
			/////////////////////
			nt_U	= *(Num_t_U + u);  
			/////////////////////////////
			nMaxU 	= bLast_U?(nt_U+1):nt_U; // no. of pts to be generated in U
			nMaxV 	= bLast_V?(nt_V+1):nt_V; // no. of pts to be generated in V
			nMaxUV	= nMaxU * nMaxV;
			/////////////////////////////
			for(j=1;j<=nDegree_U;j++)
				U[j] = (U[0]+j) % nCon_U;
			/////////////////////////////	
			for(j=0;j<=nDegree_V;j++)
			{
				VnCU = V[j] * nCon_U;		// if (bClosed_V & bLast_V)-> V[nDegree_V] is
											// automatically zero by Modulo, thus VnCU->0
											// thus vIx[i][nDegree_V] = U[i], i.e.,
											// Ist row of U	 
				/////////////////////
				for(i=0;i<=nDegree_U;i++)
				{
//					vIx[i][j] = (bLast_U && bClosed_U)?U[i]:VnCU + U[i];
					vIx[i][j] = VnCU + U[i];
				}	
			}
			////////////////////////////////////////////////////// fill up CONTROL Info for the patch
			for(i=0;i<=nDegree_U;i++)
			{
				for(j=0;j<=nDegree_V;j++)
				{
					pInC_44[i][j] = pCon_UV + vIx[i][j];
				}	
			}
			/////////////////////////////////////////////////// Go make Tangents for a patch
			nOutP = Make_Twists_A_Patch
						(	pInC_44,
							bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,
							bLast_V,nDegree_V,nDim_V,nt_V,Dis_t_V,
							p_U,nEmitTot_U,nPatches_U,nPatches_V
						);
			///////////////////				
			if(nOutP != nMaxUV)
			{
				//////////////////
				delete [] pInC_44;
				//////////////////
				AfxMessageBox("CPat_Twist4::HO_MakePatches\nnOutP != nMaxUV");
				return -1;
			}	
			else
			{	
				/////////////////
				nOut	+= nOutP;
				///////////////////// Starting Corner for the next Patch in Current column v	
				p_U		+= nt_U; 
//				pw_U	+= nt_U;
				/////////////////////
			}	
		}												///////////////////////////// end LOOP_U
		////////////////////// Starting Corner for Ist Patch in next column v	
		p_V		+= nEmitTot_U * nt_V; 
//		pw_V	+= nEmitTot_U * nt_V;
	}													///////////////////////////// end LOOP_V
	//////////////////
	delete [] pInC_44;
	//////////////////
	return nOut;
	////////////
}

int CPat_Twist4::Make_Twists_A_Patch
			(
					PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
				,	BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
				,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		// 	3= NonRational / 4 = Rational
				,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
				,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
				,	BOOL		bLast_V		// 	Last Patch in V-Dir for Output saving decision		
				,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		// 	3= NonRational / 4 = Rational
				,	int			nt_V		// 	# of subdivision to compute Surface Pts in V-dir
				,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
				,	pWORLD		pOut		// 	Total Output Tangent Array
//				,	pDOUBLE		pOutWts		// 	Total Output Wts Array
				,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
				,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
				,	int			nPatches_V	//  Total Number of Patches in V-dir, needed for t-Dist 
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
		sprintf(buf,"Just in CPat_Twist4::Make_Tangents_A_Patch");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"ppCon_U4V4[%d][%d]: Actually[4][4]\n",nDegree_U+1,nDegree_V+1);
		for(m=0;m<(nDegree_U+1);m++)
		{
			for(k=0;k<(nDegree_V+1);k++)
			{
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f %7.2f %7.2f \n", m, k, 
					ppCon_U4V4[m][k]->x, ppCon_U4V4[m][k]->y, ppCon_U4V4[m][k]->z );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	int		nResult;
	int		i,j,k;
	int		nDegUm1,nDegVm1;
	WORLD	del01bi1j,del01bij,del11bij;	
	//////////////////////////////////////////////////////// compute del11b(i,j)
	nDegUm1 = nDegree_U - 1; 
	nDegVm1 = nDegree_V - 1;
	////////////////////////////////////////////////// Temp memory
	pWORLD pCon_UV	= new WORLD[nDegree_U*nDegree_V];
	pDOUBLE pWts_UV	= new double[nDegree_U*nDegree_V];
	////////////////////
	for(j=0;j<=nDegVm1;j++)		// v dir
	{
		for(i=0;i<=nDegUm1;i++)	// u dir
		{
			k = j*nDegree_U + i;
			////////////////
			del01bi1j.x = (ppCon_U4V4[i+1][j+1])->x	- (ppCon_U4V4[i+1][j])->x;  
			del01bi1j.y = (ppCon_U4V4[i+1][j+1])->y	- (ppCon_U4V4[i+1][j])->y;  
			del01bi1j.z = (ppCon_U4V4[i+1][j+1])->z	- (ppCon_U4V4[i+1][j])->z;  
			////////////////
			del01bij.x	= (ppCon_U4V4[i][j+1])->x	- (ppCon_U4V4[i][j])->x;  
			del01bij.y	= (ppCon_U4V4[i][j+1])->y	- (ppCon_U4V4[i][j])->y;  
			del01bij.z	= (ppCon_U4V4[i][j+1])->z	- (ppCon_U4V4[i][j])->z;  
			/////////////////////////////////////////////////////
			del11bij.x	= del01bi1j.x	- del01bij.x;  
			del11bij.y	= del01bi1j.y	- del01bij.y;  
			del11bij.z	= del01bi1j.z	- del01bij.z;
			///////////////////////////////////////// save
			pCon_UV[k].x	= del11bij.x;
			pCon_UV[k].y	= del11bij.y;
			pCon_UV[k].z	= del11bij.z;
			pWts_UV[k]		= 1.0;
		}
	}
	//////////////////////////////////////////////////////// Generate Twist Patch
	CSurface4 Surface;
	//////////////////////////////////////////////////////////////////
	pWORLD	p;
	pDOUBLE pw;
    //////////////////////
	double		OutWts;
	pDOUBLE		pOutWts = &OutWts; // temporary
	WORLD		Twist;
	pWORLD		pTwist = &Twist;
	double 		NewW;
	pDOUBLE		pNewW = &NewW;
	int			iu,iv,nOut = 0, nOutU=0,nMaxU, nMaxV, nMaxUV;
	//////////////////////////////////////////////////////////////////// LOOP
	nMaxU	= bLast_U?nt_U+1:nt_U;
	nMaxV	= bLast_V?nt_V+1:nt_V;
	nMaxUV	= nMaxU * nMaxV;
	///////////////////////////
	double 	delu	= 1.0/nt_U;
	double	s		= -delu;				
	double 	delv	= 1.0/nt_V;
	double	t		= -delv;				
	/////////////////////////
	p	= pOut;
	pw	= pOutWts;
	/////////////////////////////////////////////////////////////////// V Loop
	for (iv=0;iv<nMaxV;iv++)
	{
		if(nPatches_V == 1 && nDegree_V == 1) // Ratio business/ Single & Linear
			t = Dis_t_V[iv];
		else
			t += delv;
		/////////////////////////////////////////////////////////////////// U Loop
		for (iu=0;iu<nMaxU;iu++)
		{
			if(nPatches_U == 1 && nDegree_U == 1) // Ratio business/ Single & Linear
				s = Dis_t_U[iu];
			else
				s += delu;
			/////////////////////////////////////////////////// Go make a patch
			nResult = Surface.HO_GetAPointOnABezSegPatch
				(
					FALSE/*bClosed_U*/,nDegUm1,nDim_U,nDegree_U/*nCon_U*/,1/*nPatches_U*/,1/*Patch#*/,s,		
					FALSE/*bClosed_V*/,nDegVm1,nDim_V,nDegree_V/*nCon_V*/,1/*nPatches_V*/,1/*Patch#*/,t,		
					pWts_UV,pCon_UV,p,pw
				);
			if(nResult<0)
			{
				delete [] pCon_UV;
				delete [] pWts_UV;
				//////////////////
				AfxMessageBox("CPat_Twist4::HO_Make_A_Patch\nHO_GetAPointOnABezSegPatch error");
				return -1;
			}
			///////////////////
			p++;
			nOutU++;
		}
		/////////////////////////										
		if(nOutU != nMaxU)
		{
			delete [] pCon_UV;
			delete [] pWts_UV;
			//////////////////
			AfxMessageBox("CPat_Twist4::HO_Make_A_Patch\nnOutU != nMaxU");
			return -1;
		}											
		else
		{	
			/////////////////
			nOut	+= nOutU;
			////////////////////////////////// Starting memory for next U-Curve
			p		+= nEmitTot_U;
//			pw		+= nEmitTot_U;
			//////////////////////////////////////////////////// View Matrices
			#ifdef _DEBUG
			///////////////////////////////////////////////
			if(1 != 1 ) // 
			{
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
	 			///////////////////////////////////////////
				sprintf(buf,"Still in CPat_Twist4::HO_Make_A_Patch\n AFTER\nHO_Make_A_Curve_U Return ");
				AfxMessageBox(*str);
				///////////////////
				int j,k;
				///////////////////
				j = sprintf(buf,"pOut[%d]\niv = %2d\n",nOut,iv);
				for(k=0;k<(nOut);k++)
				{
					j += sprintf( buf + j, "k=%2d  %7.2f %7.2f %7.2f \n", k, 
						pOut[k].x, pOut[k].y, pOut[k].z );
				} 
	 			j += sprintf( buf + j, "\n");
				AfxMessageBox(*str);
				///////////////////
				delete str;
			}		
			#endif				
			//////////////////////////////////////////////////////////////////
		}	
	}
	//////////////////
	delete [] pCon_UV;
	delete [] pWts_UV;
	//////////////////
	if(nOut != nMaxUV)
	{
		//////////////////
		AfxMessageBox("CPat_Twist4::HO_Make_A_Patch\nnOut != nMaxUV");
		return -1;
	}
	else	
		return nOut;
	////////////////
}

int CPat_Twist4::GetaTwistAtaControlNode(WORLD wNodeCoord,WORLD& Twist,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
								pWORLD pCon_UV,double dSameNessRatio)
{
	if(nDim_U == 4 || nDim_V == 4)	// Only NonRational
		return -1;
	//////////////////////////////
	int nResult = 0;
	////////////////
	int i,j;
	/////////////////////////////
	pWORLD	pB	= new WORLD[(nDegree_U+1)*(nDegree_V+1)];	// current Controls
	/////////////////////////////
	nResult = GetCurrentPatch_N_Controls(wNodeCoord,i,j,
						nDegree_U,nPatches_U,nCon_U,
						nDegree_V,nPatches_V,nCon_V,
						pCon_UV,dSameNessRatio,pB);
	/////////////
	if(nResult<0) // NO MATCH
		return nResult;
	////////////////////////////////////////////////////////// Must be Corner Controls
	if(i == 0 && j == 0)
	{
		/////////////
		nResult = GetBezPatCornerTwist_00(Twist,nDegree_U,nDegree_V,pB);
		/////////////
		return nResult;
	}
	else
	if(i == 0 && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatCornerTwist_01(Twist,nDegree_U,nDegree_V,pB);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == 0)
	{
		/////////////
		nResult = GetBezPatCornerTwist_10(Twist,nDegree_U,nDegree_V,pB);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatCornerTwist_11(Twist,nDegree_U,nDegree_V,pB);
		/////////////
		return nResult;
	}
	else
	{
		AfxMessageBox("ERROR:\nCRat_Twist4::GetTwistsAtaNode\nControl i & j problem");
		return -1;
	}
	//////////////
	return nResult;

}


int CPat_Twist4::GetCurrentPatch_N_Controls(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
					pWORLD pCon_UV,double dSameNessRatio,
					pWORLD B)
{
	C3DMath Math3D;
	///////////////
	int nOrderU		= nDegree_U+1;
	//////////////////////////////
	int	CtlStep_U	= nDegree_U; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	int	CtlStep_V	= nDegree_V; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	//////////////////////////////////////////////////////////////////
	int		i,j,k,u, v, VnCU;
	int		U[4], V[4], vIx[4][4];	// vertex indices
	//////////////////////////////////////////////////////////////////////////// V direction:LOOP
	for( V[0] = v = 0; v < nPatches_V; v++, V[0]+=CtlStep_V ) 
	{
		/////////////////////////////
		for(i=1;i<=nDegree_V;i++)
			V[i] = (V[0]+i) % nCon_V;
		//////////////////////////////////////////////////////////// U direction:LOOP 
		for( U[0] = u = 0; u < nPatches_U; u++, U[0]+=CtlStep_U ) 
		{
			/////////////////////////////
			for(j=1;j<=nDegree_U;j++)
				U[j] = (U[0]+j) % nCon_U;
			/////////////////////////////	
			for(j=0;j<=nDegree_V;j++)
			{
				VnCU = V[j] * nCon_U;		// if (bClosed_V & bLast_V)-> V[nDegree_V] is
											// automatically zero by Modulo, thus VnCU->0
											// thus vIx[i][nDegree_V] = U[i], i.e.,
											// Ist row of U	 
				/////////////////////
				for(i=0;i<=nDegree_U;i++)
					vIx[i][j] = VnCU + U[i];
			}
			////////////////////////////////////////////////////// fill up Corner CONTROLs for the patch
			for(j=0;j<=nDegree_V;j++)
			{
				for(i=0;i<=nDegree_U;i++)
				{
					if( Math3D.AreSame_WORLD(&wNodeCoord, (pCon_UV + vIx[i][j]),
																dSameNessRatio) )	// MATCH?
					{
						nCtrl_i			= i;
						nCtrl_j			= j;
						////////////////////
						k = j*nOrderU + i;
						//////////////////
						B[k].x	= (pCon_UV + vIx[i][j])->x; 
						B[k].y	= (pCon_UV + vIx[i][j])->y; 
						B[k].z	= (pCon_UV + vIx[i][j])->z; 
						/////////////
						return 0;
					}
				}		
			}
		}	
	}													///////////////////////////// end LOOP_V
	//////////////////
	return -1;		// NO MATCH
}

int CPat_Twist4::GetBezPatCornerTwist_00(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B)
{
	int i00,i10,i01,i11;
	///
	i00 = 0;
	i10	= i00 + 1;
	i01	= i00 + (nDegree_U+1);
	i11	= i01 + 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B);
	/////////
	return 0;
}

int CPat_Twist4::GetBezPatCornerTwist_01(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B)
{
	int i00,i10,i01,i11;
	///
	i00 = (nDegree_U+1) * nDegree_V;
	i10	= i00 + 1;
	i01	= i00 - (nDegree_U+1);
	i11	= i01 + 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B);
	/////////
	return 0;
}

int CPat_Twist4::GetBezPatCornerTwist_10(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B)
{
	int i00,i10,i01,i11;
	///
	i00 = nDegree_U;
	i10	= i00 - 1;
	i01	= i00 + (nDegree_U+1);
	i11	= i01 - 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B);
	/////////
	return 0;
}

int CPat_Twist4::GetBezPatCornerTwist_11(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B)
{
	int i00,i10,i01,i11;
	///
	i00 = (nDegree_U+1)*(nDegree_V+1) -1;
	i10	= i00 - 1;
	i01	= i00 - (nDegree_U+1);
	i11	= i01 - 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B);
	/////////
	return 0;
}

int CPat_Twist4::CalcCornerTwist(WORLD& Twist,int i00,int i10,int i01,int i11,
								int nDegree_U,int nDegree_V,pWORLD B)
{
	double wR;
	WORLD d2pdudv;
	////////////////////////////////////////////////////////// d2pdudv
	d2pdudv.x	=	(B[i11].x - B[i10].x) - (B[i01].x - B[i00].x);
	d2pdudv.y	=	(B[i11].y - B[i10].y) -	(B[i01].y - B[i00].y);
	d2pdudv.z	=	(B[i11].z - B[i10].z) - (B[i01].z - B[i00].z);
	////////////////////////////////////////////////////////// Twist
	wR			=	nDegree_U*nDegree_V;
	Twist.x		=	wR * d2pdudv.x;
	Twist.y		=	wR * d2pdudv.y;
	Twist.z		=	wR * d2pdudv.z;
	/////////
	return 0;
}

int CPat_Twist4::Pat_SubDivide_U(pWORLD Cons, double u, 
								pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV)
{
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
	for(i=0;i<nOrderU;i++)
	{
		for(j=0;j<nOrderV;j++)	// collect Row
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
		}
		////////////////////////////////////////////// SubDivide
		Curve.SubDivide_t(OldC_Tem, u, 
				NewC_Tem, bLeft, nOrderU-1);
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
	return MA_OK; 	
}

int CPat_Twist4::Pat_SubDivide_V(pWORLD Cons, double v,  
					pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV)
{
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
		Curve.SubDivide_t(OldC_Tem, v, 
				NewC_Tem, bLeft, nOrderV-1);
		////////////////////////////////////////////////// Save
		for(i=0;i<nOrderU;i++)	// collect Col
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

int CPat_Twist4::Pat_SubDivide_UV(pWORLD Cons, double u, double v, 
								pWORLD NewC, BOOL bLeftU, BOOL bLeftV, 
								int nDegreeU, int nDegreeV)
{
	int nResult;
	////////////
	int nOrderU = nDegreeU;
	int nOrderV = nDegreeV;
	////////////
	nResult = Pat_SubDivide_U(Cons, u, NewC, bLeftU, nOrderU, nOrderV);
	if(nResult != MA_OK)
		return MA_ERROR;
	////////////
	nResult = Pat_SubDivide_V(Cons, v, NewC, bLeftV, nOrderU, nOrderV);
	/////////////////
	return nResult; 	
}
/////////////////////////////////// end of module /////////////////
