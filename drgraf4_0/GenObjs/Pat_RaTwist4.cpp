// CPat_Tan4.cpp : implementation of the CPat_Tan4 class
//
	//////////////////////////////////////////////////////////////////////
	// For rational surface, the chain rule formula is more 
	// involved,ie, 4D preImage space:
	//
	//	Twist(u,v) = 
	//		[(d2P/dudv - (dx/du)*(dw/dv) - (dx/dv)*(dw/du) - x(d2w/dudv)]/w
	//
	//	where
	//		w = w(u,v) = Wts
	//		x = x(u,v) = (x,y,z);
	//		P = w(u,v)*x(u,v)
	//////////////////////////////////////////////////////////////////////
	// So, WE WILL DO IT BY SUBDIVISION METHOD:
	//	
	//		1. Rational Subdivide patch at (u,v)
	//		2. Use:
	//			Twist(0,0) = (m*n/w00)[
	//							{(w11*b11-w10*b10)-(w01*b01-w00*b00)}
	//						-	{(w10/w00)*(b10-b00)*(w01-w00)}
	//						-	{(w01/w00)*(b01-b00)*(w10-w00)}
	//						-	b00*{(w11-w10)-(w01-w00)}
	//							]
	//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "Curve_1.h"
#include "Curve_2.h"
#include "Curve_3.h"

#include "Pat_Tan4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPat_Tan4

IMPLEMENT_DYNAMIC(CPat_Tan4,CSurface4)
/*
BEGIN_MESSAGE_MAP(CPat_Tan4,CSurface4)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPat_Tan4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////////////////////////////
CPat_Tan4::CPat_Tan4()
{ 
	m_nsubdivisions	= 1;

} 
////////////////////////////////////////////////////////////////////////////
int CPat_Tan4::MakeTwists		// RATIONAL BEZIER Patches
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
	PD44 pInW_44 = new pDOUBLE[4][4]; 
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
					pInW_44[i][j] = pWts_UV + vIx[i][j];
				}	
			}
			/////////////////////////////////////////////////// Go make Tangents for a patch
			nOutP = Make_Tangents_A_Patch
						(	pInC_44,pInW_44,
							bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,
							bLast_V,nDegree_V,nDim_V,nt_V,Dis_t_V,
							p_U,nEmitTot_U,nPatches_U,nPatches_V
						);
			///////////////////				
			if(nOutP != nMaxUV)
			{
				//////////////////
				delete [] pInC_44;
				delete [] pInW_44;
				//////////////////
				AfxMessageBox("CPat_Tan4::HO_MakePatches\nnOutP != nMaxUV");
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
	delete [] pInW_44;
	//////////////////
	return nOut;
	////////////
}

int CPat_Tan4::Make_Tangents_A_Patch
			(
					PW44		ppCon_U4V4	//	pointer to pointer Control Pt. array for the patch
				,	PD44		ppWts_U4V4	//	pointer to pointer Wts. array for the patch	
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
		sprintf(buf,"Just in CPat_Tan4::Make_Tangents_A_Patch");
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
	pWORLD	p;
	pDOUBLE pw;
    //////////////////////
	WORLD		Tang;
	pWORLD		pTang = &Tang;
	double 		NewW;
	pDOUBLE		pNewW = &NewW;
	int			i,j,iv,nOut = 0, nOutU,nMaxU, nMaxV, nMaxUV;
	//////////////////////////////////////////////////////////////////// LOOP
	nMaxU	= bLast_U?nt_U+1:nt_U;
	nMaxV	= bLast_V?nt_V+1:nt_V;
	nMaxUV	= nMaxU * nMaxV;
	///////////////////////////
	double 	delv	= 1.0/nt_V;
	double	t		= -delv;				
	//////////////////////////////// memory
	pWORLD pCon_U4	= new WORLD[4];
	pDOUBLE pWts_U4	= new double[4];
	pWORLD pCon_V4	= new WORLD[4];
	pDOUBLE pWts_V4	= new double[4];
	//////////////////////////////// temp Memory for Wts.
	pDOUBLE pOutWts	= new double[nMaxUV];
	/////////////////////////////////////////////////////////////////// V Loop
	p	= pOut;
	pw	= pOutWts;
	//////////////
	for (iv=0;iv<nMaxV;iv++)
	{
		if(nPatches_V == 1 && nDegree_V == 1) // Ratio business/ Single & Linear
			t = Dis_t_V[iv];
		else
			t += delv;
		//////////
		for(i=0;i<=nDegree_U;i++)			
		{
			///////////////////////// Create Con_U & Wts_U for a specific v
			for(j=0;j<=nDegree_V;j++)
			{
				pCon_V4[j].x = (ppCon_U4V4[i][j])->x;
				pCon_V4[j].y = (ppCon_U4V4[i][j])->y;
				pCon_V4[j].z = (ppCon_U4V4[i][j])->z;
//				if(nDim_V == 4)
					pWts_V4[j] = *(ppWts_U4V4[i][j]);
			}
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Still in CPat_Tan4::Make_Tangents_A_Patch\n BEFORE\nTangent_t Call ");
		AfxMessageBox(*str);
		///////////////////
		int j,k;
	    ///////////////////
		j = sprintf(buf,"pCon_V4[%d]: Actually[4][4]\niv = %2d\n",nDegree_V+1,iv);
		for(k=0;k<(nDegree_V+1);k++)
		{
	   		j += sprintf( buf + j, "k=%2d  %7.2f %7.2f %7.2f \n", k, 
				pCon_V4[k].x, pCon_V4[k].y, pCon_V4[k].z );
		} 
  		j += sprintf( buf + j, "\n");
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
			CCurve Curve;
			///////////////
/*
			if(nDim_V == 3)	// NonRational
			{
				Curve.Tangent_t(pCon_V4, t, nDegree_V, Tang);//022597 
				pWts_U4[i]	= 1.0;
			}
			else	
			if(nDim_V == 4)	// Rational
			{
*/
				Curve.Rat_Tangent_t_for_Patch(pCon_V4, pWts_V4, t, nDegree_V, pNewW
																, Tang);//022597 
				pWts_U4[i]	= *pNewW;
/*
			}
*/
			///////////////
			pCon_U4[i].x 	= pTang->x;
			pCon_U4[i].y 	= pTang->y;
			pCon_U4[i].z 	= pTang->z;
		}
		/////////////////////////////// if any side Rational, make it All Rational Calc
		int nDim = nDim_U;
		if(nDim_V>nDim) 
			nDim = nDim_V;
		////////////////////////////////////////////////////////////////////// Curve in U-dir
		nOutU = HO_Make_A_Curve_U(bLast_U,nDegree_U,nDim  ,nt_U,Dis_t_U,pCon_U4,pWts_U4,p,pw,nPatches_U);
//		nOutU = HO_Make_A_Curve_U(bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,pCon_U4,pWts_U4,p,pw,nPatches_U);
		/////////////////////////										
		if(nOutU != nMaxU)
		{
			//////////////////
			delete [] pCon_U4;
			delete [] pWts_U4;
			delete [] pCon_V4;
			delete [] pWts_V4;
			delete [] pOutWts;
			//////////////////
			AfxMessageBox("CPat_Tan4::HO_Make_A_Patch\nnOutU != nMaxU");
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
			sprintf(buf,"Still in CPat_Tan4::HO_Make_A_Patch\n AFTER\nHO_Make_A_Curve_U Return ");
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
	delete [] pCon_U4;
	delete [] pWts_U4;
	delete [] pCon_V4;
	delete [] pWts_V4;
	delete [] pOutWts;
	//////////////////
	if(nOut != nMaxUV)
		return -1;
	else	
		return nOut;
	////////////////
}

int CPat_Tan4::GetaTangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
//								pDOUBLE pWts_UV,pWORLD pCon_UV)
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio)
{
	int nResult = 0;
	////////////////
	int i,j,nP_U,nP_V;
	//////////////////
	nResult = GetCurrentPatch_N_ControlIndices(wNodeCoord,i,j,nP_U,nP_V,
						nDegree_U,nPatches_U,nCon_U,
						nDegree_V,nPatches_V,nCon_V,
						pWts_UV,pCon_UV,dSameNessRatio);
	/////////////
	if(nResult<0) // NO MATCH
		return nResult;
	////////////////////////////////////////////////////////// Must be Corner Controls
	if(i == 0 && j == 0)
	{
		/////////////
		nResult = GetBezPatEdgeTangent_00(DirTan,Tangent,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == 0 && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatEdgeTangent_01(DirTan,Tangent,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == 0)
	{
		/////////////
		nResult = GetBezPatEdgeTangent_10(DirTan,Tangent,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == nDegree_V)
	{
		/////////////
		nResult = GetBezPatEdgeTangent_11(DirTan,Tangent,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	{
		AfxMessageBox("ERROR:\nCPat_Tan4::GetTangentsAtaNode\nControl i & j problem");
		return -1;
	}
	//////////////
	return nResult;

}

int CPat_Tan4::GetTangentsAtaNode(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio)
//								pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	int nResult = 0;
	////////////////
	int i,j,nP_U,nP_V;
	//////////////////
	nResult = GetCurrentPatch_N_ControlIndices(wNodeCoord,i,j,nP_U,nP_V,
						nDegree_U,nPatches_U,nCon_U,
						nDegree_V,nPatches_V,nCon_V,
//						pWts_UV,pCon_UV);
						pWts_UV,pCon_UV,dSameNessRatio);
	/////////////
	if(nResult<0) // NO MATCH
		return nResult;
	////////////////////////////////////////////////////////// Must be Corner Controls
	if(i == 0 && j == 0)
	{
		nResult = GetBezPatEdgeTangent_00(1,Tangent_U,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		if(nResult<0) // 
			return nResult;
		/////////////
		nResult = GetBezPatEdgeTangent_00(2,Tangent_V,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == 0 && j == nDegree_V)
	{
		nResult = GetBezPatEdgeTangent_01(1,Tangent_U,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		if(nResult<0) // 
			return nResult;
		/////////////
		nResult = GetBezPatEdgeTangent_01(2,Tangent_V,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == 0)
	{
		nResult = GetBezPatEdgeTangent_10(1,Tangent_U,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		if(nResult<0) // 
			return nResult;
		/////////////
		nResult = GetBezPatEdgeTangent_10(2,Tangent_V,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	if(i == nDegree_U && j == nDegree_V)
	{
		nResult = GetBezPatEdgeTangent_11(1,Tangent_U,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		if(nResult<0) // 
			return nResult;
		/////////////
		nResult = GetBezPatEdgeTangent_11(2,Tangent_V,
					nDegree_U,nP_U,nCon_U,nDim_U,nPatches_U,
					nDegree_V,nP_V,nCon_V,nDim_V,nPatches_V,
					pWts_UV,pCon_UV);
		/////////////
		return nResult;
	}
	else
	{
		AfxMessageBox("ERROR:\nCPat_Tan4::GetTangentsAtaNode\nControl i & j problem");
		return -1;
	}
	//////////////
	return nResult;

}

int CPat_Tan4::GetCurrentPatch_N_ControlIndices(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,int& nCurrentPat_U,int& nCurrentPat_V,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
//					pDOUBLE pWts_UV,pWORLD pCon_UV)
					pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio)
{
	C3DMath Math3D;
	///////////////
	int	CtlStep_U = nDegree_U; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	int	CtlStep_V = nDegree_V; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	//////////////////////////////////////////////////////////////////
	int		i,j,u, v, VnCU;
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
			for(i=0;i<=nDegree_U;i++)
			{
				for(j=0;j<=nDegree_V;j++)
				{
					if( Math3D.AreSame_WORLD(&wNodeCoord, (pCon_UV + vIx[i][j]),
																dSameNessRatio) )	// MATCH?
					{
						nCtrl_i			= i;
						nCtrl_j			= j;
						nCurrentPat_U	= u;
						nCurrentPat_V	= v;
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

int CPat_Tan4::GetBezPatEdgeTangent_00(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	if(nDirection != 1 && nDirection != 2)
	{
		AfxMessageBox(
			"ERROR\nCPat_Tan4::GetBezPatEdgeNormal_00\nnDirection != 1 && nDirection != 2");
		return -1;
	}
	/////////////////////////////
	WORLD	b[4][4];
	double	w[4][4];
	/////////////////////////////
	GetEdgeControls(b,w,nCurrentPat_U,nCurrentPat_V,nDegree_U,nDegree_V,
					nPatches_U,nPatches_V,nCon_U,nCon_V,pWts_UV,pCon_UV);
	/////////////////////////////// if any side Rational, make it All Rational Calc
	int nDim = nDim_U;
	if(nDim_V>nDim) 
		nDim = nDim_V;
	/////////////////////////////////////////// tangent
	C3DMath Math3D;
	///////////////
	if(nDirection == 1) // wrt U
	{
		Math3D.Sub3DPts(&(b[1][0]), &(b[0][0]), &Tangent);
		Math3D.Scale3DPts(nDegree_U, &Tangent);
	}
	else
	if(nDirection == 2) // wrt V
	{
		Math3D.Sub3DPts(&(b[0][1]), &(b[0][0]), &Tangent);
		Math3D.Scale3DPts(nDegree_V, &Tangent);
	}
	/////////////////////////////////////////// Rational?
	if(nDim == 4)	// Rational
	{
		double k1;
		//
		if(nDirection == 1) // wrt U
			k1 	= w[1][0]/w[0][0];
		else
		if(nDirection == 2) // wrt V
			k1 	= w[0][1]/w[0][0];
		///////////////////////////////////////////
		Math3D.Scale3DPts(k1, &Tangent);
		///////////////////
	}
	/////////
	return 0;
}


int CPat_Tan4::GetBezPatEdgeTangent_01(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	if(nDirection != 1 && nDirection != 2)
	{
		AfxMessageBox(
			"ERROR\nCPat_Tan4::GetBezPatEdgeNormal_00\nnDirection != 1 && nDirection != 2");
		return -1;
	}
	/////////////////////////////
	WORLD	b[4][4];	// reserved max for Cubic
	double	w[4][4];	// reserved max for Cubic
	/////////////////////////////
	GetEdgeControls(b,w,nCurrentPat_U,nCurrentPat_V,nDegree_U,nDegree_V,
					nPatches_U,nPatches_V,nCon_U,nCon_V,pWts_UV,pCon_UV);
	/////////////////////////////// if any side Rational, make it All Rational Calc
	int nDim = nDim_U;
	if(nDim_V>nDim) 
		nDim = nDim_V;
	/////////////////////////////////////////// tangent
	C3DMath Math3D;
	///////////////
	if(nDirection == 1) // wrt U
	{
		Math3D.Sub3DPts(&(b[1][nDegree_V]), &(b[0][nDegree_V]), &Tangent);
		Math3D.Scale3DPts(nDegree_U, &Tangent);
	}
	else
	if(nDirection == 2) // wrt V
	{
		Math3D.Sub3DPts(&(b[0][nDegree_V]), &(b[0][nDegree_V-1]), &Tangent);
		Math3D.Scale3DPts(nDegree_V, &Tangent);
	}
	/////////////////////////////////////////// Rational?
	if(nDim == 4)	// Rational
	{
		double k1;
		//
		if(nDirection == 1) // wrt U
			k1 	= w[1][nDegree_V]/w[0][nDegree_V];
		else
		if(nDirection == 2) // wrt V
			k1 	= w[0][nDegree_V-1]/w[0][nDegree_V];
		///////////////////////////////////////////
		Math3D.Scale3DPts(k1, &Tangent);
		///////////////////
	}
	/////////
	return 0;
}


int CPat_Tan4::GetBezPatEdgeTangent_10(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	if(nDirection != 1 && nDirection != 2)
	{
		AfxMessageBox(
			"ERROR\nCPat_Tan4::GetBezPatEdgeNormal_00\nnDirection != 1 && nDirection != 2");
		return -1;
	}
	/////////////////////////////
	WORLD	b[4][4];
	double	w[4][4];
	/////////////////////////////
	GetEdgeControls(b,w,nCurrentPat_U,nCurrentPat_V,nDegree_U,nDegree_V,
					nPatches_U,nPatches_V,nCon_U,nCon_V,pWts_UV,pCon_UV);
	/////////////////////////////// if any side Rational, make it All Rational Calc
	int nDim = nDim_U;
	if(nDim_V>nDim) 
		nDim = nDim_V;
	/////////////////////////////////////////// tangent
	C3DMath Math3D;
	///////////////
	if(nDirection == 1) // wrt U
	{
		Math3D.Sub3DPts(&(b[nDegree_U][0]), &(b[nDegree_U-1][0]), &Tangent);
		Math3D.Scale3DPts(nDegree_U, &Tangent);
	}
	else
	if(nDirection == 2) // wrt V
	{
		Math3D.Sub3DPts(&(b[nDegree_U][1]), &(b[nDegree_U][0]), &Tangent);
		Math3D.Scale3DPts(nDegree_V, &Tangent);
	}
	/////////////////////////////////////////// Rational?
	if(nDim == 4)	// Rational
	{
		double k1;
		//
		if(nDirection == 1) // wrt U
			k1 	= w[nDegree_U-1][0]/w[nDegree_U][0];
		else
		if(nDirection == 2) // wrt V
			k1 	= w[nDegree_U][1]/w[nDegree_U][0];
		///////////////////////////////////////////
		Math3D.Scale3DPts(k1, &Tangent);
		///////////////////
	}
	/////////
	return 0;
}


int CPat_Tan4::GetBezPatEdgeTangent_11(int nDirection,WORLD& Tangent,
					int nDegree_U,int nCurrentPat_U,int nCon_U,int nDim_U,int nPatches_U,
					int nDegree_V,int nCurrentPat_V,int nCon_V,int nDim_V,int nPatches_V,
					pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	if(nDirection != 1 && nDirection != 2)
	{
		AfxMessageBox(
			"ERROR\nCPat_Tan4::GetBezPatEdgeNormal_00\nnDirection != 1 && nDirection != 2");
		return -1;
	}
	/////////////////////////////
	WORLD	b[4][4];
	double	w[4][4];
	/////////////////////////////
	GetEdgeControls(b,w,nCurrentPat_U,nCurrentPat_V,nDegree_U,nDegree_V,
					nPatches_U,nPatches_V,nCon_U,nCon_V,pWts_UV,pCon_UV);
	/////////////////////////////// if any side Rational, make it All Rational Calc
	int nDim = nDim_U;
	if(nDim_V>nDim) 
		nDim = nDim_V;
	/////////////////////////////////////////// tangent
	C3DMath Math3D;
	///////////////
	if(nDirection == 1) // wrt U
	{
		Math3D.Sub3DPts(&(b[nDegree_U][nDegree_V]), &(b[nDegree_U-1][nDegree_V]), &Tangent);
		Math3D.Scale3DPts(nDegree_U, &Tangent);
	}
	else
	if(nDirection == 2) // wrt V
	{
		Math3D.Sub3DPts(&(b[nDegree_U][nDegree_V]), &(b[nDegree_U][nDegree_V-1]), &Tangent);
		Math3D.Scale3DPts(nDegree_V, &Tangent);
	}
	/////////////////////////////////////////// Rational?
	if(nDim == 4)	// Rational
	{
		double k1;
		//
		if(nDirection == 1) // wrt U
			k1 	= w[nDegree_U-1][nDegree_V]/w[nDegree_U][nDegree_V];
		else
		if(nDirection == 2) // wrt V
			k1 	= w[nDegree_U][nDegree_V-1]/w[nDegree_U][nDegree_V];
		///////////////////////////////////////////
		Math3D.Scale3DPts(k1, &Tangent);
		///////////////////
	}
	/////////
	return 0;
}

int CPat_Tan4::GetEdgeControls(	
					WORLD b[][4],double w[][4],int nCurrentPat_U,int nCurrentPat_V,
					int nDegree_U,int nDegree_V,int nPatches_U,int nPatches_V,
					int	nCon_U,int	nCon_V,pDOUBLE pWts_UV,pWORLD pCon_UV)
{
	int	CtlStep_U = nDegree_U; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	int	CtlStep_V = nDegree_V; 	//  Control Pt. Step ASSUMED ALWAYS BEZIER
	//////////////////////////////////////////////////////////////////
	int		i,j,u, v, VnCU;
	int		U[4], V[4], vIx[4][4];	// vertex indices
	//////////////////////////////////////////////////////////////////////////// V direction:LOOP
	for( V[0] = v = 0; v < nPatches_V; v++, V[0]+=CtlStep_V ) 
	{
		if(v != nCurrentPat_V)
			continue;
		/////////////////////////////
		for(i=1;i<=nDegree_V;i++)
			V[i] = (V[0]+i) % nCon_V;
		//////////////////////////////////////////////////////////// U direction:LOOP 
		for( U[0] = u = 0; u < nPatches_U; u++, U[0]+=CtlStep_U ) 
		{
			if(u != nCurrentPat_U)
				continue;
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
			////////////////////////////////////////////////////// fill up CONTROL Info for the patch
			for(i=0;i<=nDegree_U;i++)
			{
				for(j=0;j<=nDegree_V;j++)
				{
					b[i][j].x	= (pCon_UV + vIx[i][j])->x; 
					b[i][j].y	= (pCon_UV + vIx[i][j])->y; 
					b[i][j].z	= (pCon_UV + vIx[i][j])->z; 
					w[i][j]		= *(pWts_UV + vIx[i][j]);
				}		
			}
		}	
	}													///////////////////////////// end LOOP_V
	//////////////////
	return 0;
}
/////////////////////////////////// end of module /////////////////
