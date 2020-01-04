// CRat_Twist4.cpp : implementation of the CRat_Twist4 class
//
	//					RATIONAL PATCH
	//////////////////////////////////////////////////////////////////////
	//	SUBDIVIDE & FIND TWIST AT (0,0) FOR EACH PATCH
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

#include "Rat_Twist4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CRat_Twist4

IMPLEMENT_DYNAMIC(CRat_Twist4,CObject)
/*
BEGIN_MESSAGE_MAP(CRat_Twist4,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CRat_Twist4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////////////////////////////
CRat_Twist4::CRat_Twist4()
{ 
} 
////////////////////////////////////////////////////////////////////////////
int CRat_Twist4::MakeTwists		// RATIONAL BEZIER Patches
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
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
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
	int		i,j,k,u, v, VnCU,	nOutP = 0, nOut = 0, nMaxU,nMaxV,nMaxUV;
	int		nt_U,nt_V,U[4], V[4], vIx[4][4];	// vertex indices
	BOOL	bLast_U,bLast_V;
	////////////////////////////////////////////////// Temp memory
	pWORLD pCon		= new WORLD[(nDegree_U+1)*(nDegree_V+1)];
	pDOUBLE pWts	= new double[(nDegree_U+1)*(nDegree_V+1)];
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
			for(j=0;j<=nDegree_V;j++)
			{
				for(i=0;i<=nDegree_U;i++)
				{
					k = i + j*(nDegree_U+1);
					////////////////////////
					pCon[k].x	= (pCon_UV + vIx[i][j])->x;
					pCon[k].y	= (pCon_UV + vIx[i][j])->y;
					pCon[k].z	= (pCon_UV + vIx[i][j])->z;
					pWts[k]		= *(pWts_UV + vIx[i][j]);
				}	
			}
			/////////////////////////////////////////////////// Go make Tangents for a patch
			nOutP = Make_Twists_A_Patch
						(	pCon,pWts,
							bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,
							bLast_V,nDegree_V,nDim_V,nt_V,Dis_t_V,
							p_U,nEmitTot_U,nPatches_U,nPatches_V
						);
			///////////////////				
			if(nOutP != nMaxUV)
			{
				//////////////////
				delete [] pCon;
				delete [] pWts;
				//////////////////
				AfxMessageBox("CRat_Twist4::HO_MakePatches\nnOutP != nMaxUV");
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
	delete [] pCon;
	delete [] pWts;
	//////////////////
	return nOut;
	////////////
}

int CRat_Twist4::Make_Twists_A_Patch
			(
					pWORLD		pOldCon		//	Control Pt. array for the patch
				,	pDOUBLE		pOldWts		//	Wts. array for the patch	
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
	CPat_SubDiv4 Pat_SubDiv4;
	//////////////////////////////////////////////////////////////////
	int		nResult;
	int		nOrderU = nDegree_U+1;
	int		nOrderV = nDegree_V+1;
	//////////////////////////////////////////////////////////////////
	pWORLD	p;
	pDOUBLE pw;
    //////////////////////
	double		OutWts;
	pDOUBLE		pOutWts = &OutWts; // temporary
	WORLD		Twist;
	pWORLD		pTwist = &Twist;
	////////////////////////////////////// memory
	pWORLD		pNewCon	= new WORLD[nOrderU*nOrderV];
	pDOUBLE		pNewWts	= new double[nOrderU*nOrderV];
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
			/////////////////////////////////////////////////// Go Subdivide a patch
			nResult = Pat_SubDiv4.Rat_SubDivide_UV(pOldCon,pOldWts,s,t, 
							pNewCon,pNewWts,FALSE/*bLeftU*/,FALSE/*bLeftV*/, 
							nOrderU,nOrderV);
			/////////////
			nResult = GetBezPatCornerTwist_00(Twist,nDegree_U,nDegree_V,pNewCon,pNewWts);
			/////////////
			if(nResult<0)
			{
				delete [] pNewCon;
				delete [] pNewWts;
				//////////////////
				AfxMessageBox("CRat_Twist4::HO_Make_A_Patch\nHO_GetAPointOnABezSegPatch error");
				return -1;
			}
			else
			{
				//////////////////////////////////////// save Twist
				p->x = Twist.x;
				p->y = Twist.y;
				p->z = Twist.z;
				///////////////
				p++;
				nOutU++;
			}
		}
		/////////////////////////										
		if(nOutU != nMaxU)
		{
			delete [] pNewCon;
			delete [] pNewWts;
			//////////////////
			AfxMessageBox("CRat_Twist4::HO_Make_A_Patch\nnOutU != nMaxU");
			return -1;
		}											
		else
		{	
			/////////////////
			nOut	+= nOutU;
			////////////////////////////////// Starting memory for next U-Curve(Row)
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
				sprintf(buf,"Still in CRat_Twist4::HO_Make_A_Patch\n AFTER\nHO_Make_A_Curve_U Return ");
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
	delete [] pNewCon;
	delete [] pNewWts;
	//////////////////
	if(nOut != nMaxUV)
	{
		//////////////////
		AfxMessageBox("CRat_Twist4::HO_Make_A_Patch\nnOut != nMaxUV");
		return -1;
	}
	else	
		return nOut;
	////////////////
}

int CRat_Twist4::GetaTwistAtaControlNode(WORLD wNodeCoord,WORLD& Twist,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
//								pDOUBLE pWts_UV,pWORLD pCon_UV)
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio)
{
	if(nDim_U == 4 || nDim_V == 4)	// Only NonRational
		return -1;
	//////////////////////////////
	int nResult = 0;
	////////////////
	int i,j;
	/////////////////////////////
	pWORLD	pB	= new WORLD[(nDegree_U+1)*(nDegree_V+1)];	// current Controls
	pDOUBLE	pW	= new double[(nDegree_U+1)*(nDegree_V+1)];
	/////////////////////////////
	nResult = GetCurrentPatch_N_Controls(wNodeCoord,i,j,
						nDegree_U,nPatches_U,nCon_U,
						nDegree_V,nPatches_V,nCon_V,
						pWts_UV,pCon_UV,dSameNessRatio,pB,pW);
	/////////////
	if(nResult<0) // NO MATCH
		return nResult;
	////////////////////////////////////////////////////////// Must be Corner Controls
	if(i == 0 && j == 0)
	{
		/////////////
		nResult = GetBezPatCornerTwist_00(Twist,nDegree_U,nDegree_V,pB,pW);
		/////////////
		return nResult;
	}
	else
	if(i == 0 && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatCornerTwist_01(Twist,nDegree_U,nDegree_V,pB,pW);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == 0)
	{
		/////////////
		nResult = GetBezPatCornerTwist_10(Twist,nDegree_U,nDegree_V,pB,pW);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatCornerTwist_11(Twist,nDegree_U,nDegree_V,pB,pW);
		/////////////
		return nResult;
	}
	else
	{
		AfxMessageBox("ERROR:\nCRat_Twist4::GetTangentsAtaNode\nControl i & j problem");
		return -1;
	}
	//////////////
	return nResult;

}

int CRat_Twist4::GetCurrentPatch_N_Controls(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
//					pDOUBLE pWts_UV,pWORLD pCon_UV)
					pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio,
					pWORLD B, pDOUBLE W)
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
						W[k]	= *(pWts_UV + vIx[i][j]);
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

int CRat_Twist4::GetBezPatCornerTwist_00(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
{
	int i00,i10,i01,i11;
	///
	i00 = 0;
	i10	= i00 + 1;
	i01	= i00 + (nDegree_U+1);
	i11	= i01 + 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B,W);
	/////////
	return 0;
}

int CRat_Twist4::GetBezPatCornerTwist_01(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
{
	int i00,i10,i01,i11;
	///
	i00 = (nDegree_U+1) * nDegree_V;
	i10	= i00 + 1;
	i01	= i00 - (nDegree_U+1);
	i11	= i01 + 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B,W);
	/////////
	return 0;
}

int CRat_Twist4::GetBezPatCornerTwist_10(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
{
	int i00,i10,i01,i11;
	///
	i00 = nDegree_U;
	i10	= i00 - 1;
	i01	= i00 + (nDegree_U+1);
	i11	= i01 - 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B,W);
	/////////
	return 0;
}

int CRat_Twist4::GetBezPatCornerTwist_11(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
{
	int i00,i10,i01,i11;
	///
	i00 = (nDegree_U+1)*(nDegree_V+1) -1;
	i10	= i00 - 1;
	i01	= i00 - (nDegree_U+1);
	i11	= i01 - 1;
	///
	CalcCornerTwist(Twist,i00,i10,i01,i11,nDegree_U,nDegree_V,B,W);
	/////////
	return 0;
}

int CRat_Twist4::CalcCornerTwist(WORLD& Twist,int i00,int i10,int i01,int i11,
								int nDegree_U,int nDegree_V,pWORLD B,pDOUBLE W)
{
	double wR,wS;
	WORLD d2pdudv,dxdudwdv,dxdvdwdu,xd2wdudv;
	////////////////////////////////////////////////////////// d2pdudv
	d2pdudv.x	=	(W[i11]*B[i11].x - W[i10]*B[i10].x) -
					(W[i01]*B[i01].x - W[i00]*B[i00].x);
	d2pdudv.y	=	(W[i11]*B[i11].y - W[i10]*B[i10].y) -
					(W[i01]*B[i01].y - W[i00]*B[i00].y);
	d2pdudv.z	=	(W[i11]*B[i11].z - W[i10]*B[i10].z) -
					(W[i01]*B[i01].z - W[i00]*B[i00].z);
	////////////////////////////////////////////////////////// dxdudwdv
	wR			=	W[i10]/W[00];
	wS			=	W[i01] - W[i00];
	dxdudwdv.x	=	wR * (B[i10].x - B[i00].x) * wS;
	dxdudwdv.y	=	wR * (B[i10].y - B[i00].y) * wS;
	dxdudwdv.z	=	wR * (B[i10].z - B[i00].z) * wS;
	////////////////////////////////////////////////////////// dxdvdwdu
	wR			=	W[i01]/W[00];
	wS			=	W[i10] - W[i00];
	dxdvdwdu.x	=	wR * (B[i01].x - B[i00].x) * wS;
	dxdvdwdu.y	=	wR * (B[i01].y - B[i00].y) * wS;
	dxdvdwdu.z	=	wR * (B[i01].z - B[i00].z) * wS;
	////////////////////////////////////////////////////////// xd2wdudv
	wR			=	W[i11] - W[i10];
	wS			=	W[i01] - W[i00];
	xd2wdudv.x	=	B[i00].x * (wR - wS);
	xd2wdudv.y	=	B[i00].y * (wR - wS);
	xd2wdudv.z	=	B[i00].z * (wR - wS);
	////////////////////////////////////////////////////////// Twist
	wR			=	nDegree_U*nDegree_V/W[i00];
	Twist.x		=	wR * (d2pdudv.x - dxdudwdv.x - dxdvdwdu.x
							- xd2wdudv.x);
	Twist.y		=	wR * (d2pdudv.y - dxdudwdv.y - dxdvdwdu.y
							- xd2wdudv.y);
	Twist.z		=	wR * (d2pdudv.z - dxdudwdv.z - dxdvdwdu.z
							- xd2wdudv.z);
	/////////
	return 0;
}

int CRat_Twist4::Rat_SubDivide_U(pWORLD Cons, pDOUBLE Wts, double u, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
{
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
	for(i=0;i<nOrderU;i++)
	{
		for(j=0;j<nOrderV;j++)	// collect Row
		{
			k = j*nOrderU + i;
			//////////////////
			OldC_Tem[i].x	= Cons[k].x;
			OldC_Tem[i].y	= Cons[k].y;
			OldC_Tem[i].z	= Cons[k].z;
			OldW_Tem[i]		= Wts[k];
		}
		////////////////////////////////////////////// SubDivide
		Curve.Rat_SubDivide_t(OldC_Tem, OldW_Tem, u, 
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
	return MA_OK; 	
}

int CRat_Twist4::Rat_SubDivide_V(pWORLD Cons, pDOUBLE Wts, double v,  
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
{
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
		Curve.Rat_SubDivide_t(OldC_Tem, OldW_Tem, v, 
				NewC_Tem, NewW_Tem, bLeft, nOrderV-1);
		////////////////////////////////////////////////// Save
		for(i=0;i<nOrderU;i++)	// collect Col
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

int CRat_Twist4::Rat_SubDivide_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeftU, BOOL bLeftV, 
								int nDegreeU, int nDegreeV)
{
	int nResult;
	////////////
	int nOrderU = nDegreeU;
	int nOrderV = nDegreeV;
	////////////
	nResult = Rat_SubDivide_U(Cons, Wts, u, NewC, NewW, bLeftU, nOrderU, nOrderV);
	if(nResult != MA_OK)
		return MA_ERROR;
	////////////
	nResult = Rat_SubDivide_V(Cons, Wts, v, NewC, NewW, bLeftV, nOrderU, nOrderV);
	/////////////////
	return nResult; 	
}
/////////////////////////////////// end of module /////////////////
