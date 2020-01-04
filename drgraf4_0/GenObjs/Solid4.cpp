// CSolid4.cpp : implementation of the CSolid4 class
//

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

#include "Solid4.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSolid4

IMPLEMENT_DYNAMIC(CSolid4,CObject)
/*
BEGIN_MESSAGE_MAP(CSolid4,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CSolid4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////
static DMA22
	CoefLagLin		= {	{ -1,	 1 },
						{  1,	 0 }	}
,					
	CoefBezierLin	= {	{ -1,	 1 },
						{  1,	 0 }	};
static DMA33
	CoefLagQuad		= {	{  2,  -4,	 2 },
						{ -3,	4,	-1 },
						{  1,	0,	 0 } }
,					
	CoefBezierQuad	= {	{  1,  -2,	 1 },         
						{ -2,	2,	 0 },
						{  1,   0,	 0 } };
static DMA44
	CoefBezierCubic = {	{ -1,	 3,	-3,	1 },
						{  3,	-6,	 3,	0 },
						{ -3,	 3,	 0,	0 },
						{  1,	 0,	 0,	0 }	};
/*					
,	CoefBSpline = {
		{ -0.166666666F,  0.5F, 		 -0.5F,  		0.166666666F },
		{  0.5F,			-1,  		  0.5F,  		0 			},
		{ -0.5F,			 0,  		  0.5F,  		0 			},
		{  0.166666666F,  0.66666666F,  0.166666666F,  0 			}	} 
		
,	CoefCatmullRom = {	{ -0.5F,	 1.5F,	-1.5F,	 0.5F },
						{  1,	-2.5F,	 2.0F,	-0.5F },
						{ -0.5F,	 0,	 0.5F,	 0 },
						{  0,	 1,	 0,	 0 }	} 
						
,	CoefHermite = {	{  2, -2,  1,  1 },
					{ -3,  3, -2, -1 },
					{  0,  0,  1,  0 },
					{  1,  0,  0,  0 }	} 
					
,	CoefBeta = {	{ -2,  2, -2,  2 },
					{  6, -3,  3,  0 },
					{ -6,  6,  6,  0 },
					{  2,  1,  2,  0 }	} 
,	CoefAlfa					
; 
*/
static DMAT
	CoefBezier		= {	{ -1,	 3,	-3,	1 },
						{  3,	-6,	 3,	0 },
						{ -3,	 3,	 0,	0 },
						{  1,	 0,	 0,	0 }	}
,	CoefBSpline		= { { -0.166666666F, 	0.5F, 			-0.5F,  		0.166666666F},
						{  0.5F,			-1,  			0.5F,  			0 			},
						{ -0.5F,			0,  			0.5F,  			0 			},
						{  0.166666666F,	0.66666666F,	0.166666666F,	0 			}	}
,	CoefCatmullRom	= {	{ -0.5F,	 1.5F,	-1.5F,	0.5F	},
						{  1,		-2.5F,	 2,		-0.5F	},
						{ -0.5F,	 0,	 	0.5F,	0		},
						{  0,	 	1,	 	0,		0		}	}
,	CoefHermite		= {	{  2, -2,  1,  1 },
						{ -3,  3, -2, -1 },
						{  0,  0,  1,  0 },
						{  1,  0,  0,  0 }	}
,	CoefBeta		= {	{ -2,  2, -2,  2 },
						{  6, -3,  3,  0 },
						{ -6,  6,  6,  0 },
						{  2,  1,  2,  0 }	}
;
//////////////////////////////////////////////////////////////////////
enum { X,Y,Z,W };

#define	SETM(m,n,o,w)		(m)[(n)][X] = (o).x * (w);\
							(m)[(n)][Y] = (o).y * (w);\
							(m)[(n)][Z] = (o).z * (w);\
							(m)[(n)][W] = (w)
#define	SCALEP(a,b)			(a).x = (a).x * (b);\
							(a).y = (a).y * (b);\
							(a).z = (a).z * (b)
#define	SUBP(a,b,c)			(c).x = (a).x - (b).x;\
							(c).y = (a).y - (b).y;\
							(c).z = (a).z - (b).z
#define	P2F3D(_a,_b)	(_b).x = (_a).x; (_b).y = (_a).y; (_b).z = (_a).z

//////////////////////
CSolid4::CSolid4()
{ 
	m_nsubdivisions	= 1;

} 
/////////////////////////////////////////////////////////////////////
int CSolid4::NumberOfSolides
			(
				CURVEPROC kindU, int nCtlU, int nSegU, BOOL bCloseU, int nOrderU,
				CURVEPROC kindV, int nCtlV, int nSegV, BOOL bCloseV, int nOrderV,
				CURVEPROC kindW, int nCtlW, int nSegW, BOOL bCloseW, int nOrderW,
				int* pnPU,int* pnPV,int* pnPW,int* pnOut_U,int* pnOut_V,int* pnOut_W
			)
{ 
	////////////////////////////////////////////////////////////////////////
	// 	Return: 	np 		= No. of Output Pts. to be generated                      
	//	Parameter modified:
	//				pnPU 	= No. of Cubic Patches in U-direction 
	//				pnPV 	= No. of Cubic Patches in V-direction 
	////////////////////////////////////////////////////////////////////////
	CCurve Curve;
	int du,dv,dw;
	if( !(du = Curve.CtlPtStep( kindU, nOrderU-1 )) )	// needed nDegree
		return -1;
	if( !(dv = Curve.CtlPtStep( kindV, nOrderV-1 )) )	// needed nDegree
		return -1;
	if( !(dw = Curve.CtlPtStep( kindV, nOrderW-1 )) )	// needed nDegree
		return -1;
	////////////////////////////////////
	*pnPU = bCloseU ? nCtlU/du : (nCtlU - nOrderU)/du + 1;
	*pnPV = bCloseV ? nCtlV/dv : (nCtlV - nOrderV)/dv + 1;
	*pnPW = bCloseW ? nCtlW/dw : (nCtlW - nOrderW)/dw + 1;

	*pnOut_U	= nSegU * (*pnPU) + 1;
	*pnOut_V	= nSegV * (*pnPV) + 1;
	int np		= (nSegU*(*pnPU)+1) * (nSegV*(*pnPV)+1);
	///////////////////////////////
	return np;
	////////

} 
////////////////////////////////////////////////////////////////////////////////////////////
int CSolid4::HO_MakeSolides		// RATIONAL BEZIER Solides
			(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			CtlStep_U	//  Control Pt. Step
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			CtlStep_V   //  Control Pt. Step
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array
				,	pDOUBLE		Dis_t_V		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	BOOL		bClosed_W	//  IsClosed_V
				,	int			CtlStep_W   //  Control Pt. Step
				,	int			nDegree_W	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_W		//  3= NonRational / 4 = Rational
				,	int			nCon_W		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nSolides_W	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_W		//  Number of Segments for each Patch Array
				,	pDOUBLE		Dis_t_W		//  Output t distribution Pts. for Ratio Business				
					//////////////////////////
				,	pDOUBLE		pWts_UVW	//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UVW	//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UVW	//  Total Output Points Array
				,	pDOUBLE		pOutWts_UVW	//  Total Output Wts Array (WE MAY NEED FOR RATIONAL SOLIDS)
			)
{
	pWORLD	p_U,p_V,p_W;
	pDOUBLE pw_U,pw_V,pw_W;
	int		nEmitTot_CurUCurVCurW,nEmitTot_UCurVCurW,nEmitTot_UVCurW;
	int		i,j,k,u, v, w, WnCUV, VnCU,	nOut_S, nOut_ST, nOut_STR, nOut, nMaxW;
	int		nt_U,nt_V,nt_W, U[4], V[4], W[4], vIx[4][4][4];	// vertex indices
	BOOL	bLast_U,bLast_V,bLast_W;
	int		nMaxU,nMaxV;
	////////////////////////////////////// memory for array of pointers
	PW444 pInC_444 = new pWORLD[4][4][4];	//	Control Pt. array for the Solid: RESERVED for Maximum Cubic
	PD444 pInW_444 = new pDOUBLE[4][4][4]; 
	/////////////////////////////////////////////////////// Totals in UV dir
	int nEmitTot_U=0;
	for(u=0;u<nSolides_U;u++)
		nEmitTot_U += *(Num_t_U + u);
	nEmitTot_U++;
	/////////////
	int nEmitTot_V=0;
	for(v=0;v<nSolides_V;v++)
		nEmitTot_V += *(Num_t_V + v);
	nEmitTot_V++;
	/////////////
	int nEmitTot_W=0;
	for(w=0;w<nSolides_W;w++)
		nEmitTot_W += *(Num_t_W + w);
	nEmitTot_W++;
	///////////////
	int nEmitTot_UV		= nEmitTot_U * nEmitTot_V;				// Max on a ST plane
	int nEmitTot_STR	= nEmitTot_U * nEmitTot_V * nEmitTot_W;	// absolute Max
	int	nCon_UV			= nCon_U * nCon_V;
	//////////////////////////////////////////////////////////////////////////// W direction:LOOP
	p_W				= pOut_UVW; 
	pw_W			= pOutWts_UVW;
	nOut_STR		= 0;
	/////////////////////	
	for( W[0] = w = 0; w < nSolides_W; w++, W[0]+=CtlStep_W ) 
	{
		for(i=1;i<=nDegree_W;i++)
			W[i] = (W[0]+i) % nCon_W;
		/////////////////////////
		nt_W			= *(Num_t_W + w);
		bLast_W			= (w == (nSolides_W-1))?TRUE:FALSE;
		nMaxW 			= bLast_W?(nt_W+1):nt_W; // no. of pts to be generated in W
		nEmitTot_UVCurW	= nEmitTot_UV * nMaxW;	
		///////////////////////////////////////
		int nEmitTot_UVW = nEmitTot_UV * nMaxW;
		//////////////////////////////////////////////////////////////////// V direction:LOOP
		p_V		= p_W;
		pw_V	= pw_W;
		nOut_ST	= 0;
		////////////////
		for( V[0] = v = 0; v < nSolides_V; v++, V[0]+=CtlStep_V ) 
		{
			for(i=1;i<=nDegree_V;i++)
				V[i] = (V[0]+i) % nCon_V;
			/////////////////////////
			nt_V				= *(Num_t_V + v);
			bLast_V				= (v == (nSolides_V-1))?TRUE:FALSE;
			nMaxV 				= bLast_V?(nt_V+1):nt_V; // no. of pts to be generated in V
			nEmitTot_UCurVCurW	= nEmitTot_U * nMaxV * nMaxW;	
			//////////////////////////////////////////////////////////// U direction:LOOP 
			p_U		= p_V;
			pw_U	= pw_V;
			nOut_S	= 0;
			////////////////
			for( U[0] = u = 0; u < nSolides_U; u++, U[0]+=CtlStep_U ) 
			{
				/////////////////////////
				nt_U	= *(Num_t_U + u);  
				bLast_U	= (u == (nSolides_U-1))?TRUE:FALSE;
				nMaxU	= bLast_U?(nt_U+1):nt_U; // no. of pts to be generated in U
				/////////////////////////////
				for(j=1;j<=nDegree_U;j++)
					U[j] = (U[0]+j) % nCon_U;
				/////////////////////////////
				for(k=0;k<=nDegree_W;k++)
				{
					WnCUV = W[k] * nCon_UV;		// if (bClosed_W & bLast_W)-> W[nDegree_W] is
												// automatically zero by Modulo, thus VnCU->0
												// thus vIx[i][nDegree_V] = U[i], i.e.,
												// Ist row of U	 
					for(j=0;j<=nDegree_V;j++)
					{
						VnCU = V[j] * nCon_U;		// if (bClosed_V & bLast_V)-> V[nDegree_V] is
													// automatically zero by Modulo, thus VnCU->0
													// thus vIx[i][nDegree_V] = U[i], i.e.,
													// Ist row of U	 
						/////////////////////
						for(i=0;i<=nDegree_U;i++)
						{
							vIx[i][j][k] = WnCUV + VnCU + U[i];
						}	
					}
				}
				////////////////////////// fill up CONTROL Info for the solid
				for(i=0;i<=nDegree_U;i++)
				{
					for(j=0;j<=nDegree_V;j++)
					{
						for(k=0;k<=nDegree_W;k++)
						{
							pInC_444[i][j][k] = pCon_UVW + vIx[i][j][k];
							pInW_444[i][j][k] = pWts_UVW + vIx[i][j][k];
						}	
					}
				}
				/////////////////////////////////////////////////// Go make a solid
				nEmitTot_CurUCurVCurW	= nMaxU * nMaxV * nMaxW;
				/////////////////////////
				nOut	= HO_Make_A_Solid
								(	pInC_444,pInW_444,
									bLast_U,nDegree_U,nDim_U,nt_U,Dis_t_U,
									bLast_V,nDegree_V,nDim_V,nt_V,Dis_t_V,
									bLast_W,nDegree_W,nDim_W,nt_W,Dis_t_W,
									p_U,pw_U,nEmitTot_U,nEmitTot_UV,
									nSolides_U,nSolides_V,nSolides_W
								);
				///////////////////				
				if(nOut != nEmitTot_CurUCurVCurW)
				{
					//////////////////
					delete [] pInC_444;
					delete [] pInW_444;
					//////////////////
					AfxMessageBox("CSolid4::HO_MakeSolides\nnOutS != nMaxUVW");
					return -1;
				}	
				else
				{	
					/////////////////
					nOut_S	+= nOut;
					///////////////////// U-Corner
					p_U		+= nt_U; 
					pw_U	+= nt_U;
				}
			} /////////////////////////////////////////////////////////////////////// end LOOP_U	
			if(nOut_S != nEmitTot_UCurVCurW)
			{
				//////////////////
				delete [] pInC_444;
				delete [] pInW_444;
				//////////////////
				AfxMessageBox("CSolid4::HO_MakeSolides\nnOut != nEmitTot_UVW");
				return -1;
			}	
			else
			{	
				/////////////////
				nOut_ST	+= nOut_S;
				//////////////////////// Starting Corner for Ist Solid in next column w	
				p_V		+= nt_V * nEmitTot_U; 
				pw_V	+= nt_V * nEmitTot_U;
			}
		} /////////////////////////////////////////////////////////////////////////// end LOOP_V
		////////////////////////				
		if(nOut_ST != nEmitTot_UVCurW)
		{
			//////////////////
			delete [] pInC_444;
			delete [] pInW_444;
			//////////////////
			AfxMessageBox("CSolid4::HO_MakeSolides\nnOut != nEmitTot_UVW");
			return -1;
		}	
		else
		{	
			/////////////////
			nOut_STR	+= nOut_ST;
			//////////////////////// Starting Corner for Ist Solid in next column w	
			p_W		+= nt_W * nEmitTot_UV; 
			pw_W	+= nt_W * nEmitTot_UV;
		}
	} /////////////////////////////////////////////////////////////////////////////// end LOOP_W
	//////////////////
	delete [] pInC_444;
	delete [] pInW_444;
	////////////////////////				
	if(nOut_STR != nEmitTot_STR)
	{
		//////////////////
		AfxMessageBox("CSolid4::HO_MakeSolides\nnOutSTR != nEmitTot_STR");
		return -1;
	}	
	else
		return nOut_STR;
	////////////
}

int CSolid4::HO_Make_A_Solid
			(
					PW444		ppCon_S4T4R4	//	pointer to pointer Control Pt. array for the solid
				,	PD444		ppWts_S4T4R4	//	pointer to pointer Wts. array for the solid	
				/////////////////////////
				,	BOOL		bLast_S			//  Last Patch in S-Dir for Output saving decision
				,	int			nDegree_S		//  Degree in S-Dir
				,	int			nDim_S			//  3= NonRational / 4 = Rational
				,	int			nt_S			// 	# of subdivision to compute Surface Pts in S-dir
				,	pDOUBLE		Dis_t_S			//  Output t distribution Pts. for Ratio Business				
				/////////////////////////
				,	BOOL		bLast_T			// 	Last Patch in T-Dir for Output saving decision		
				,	int			nDegree_T		//  Degree in T-Dir
				,	int			nDim_T			//  3= NonRational / 4 = Rational
				,	int			nt_T			// 	# of subdivision to compute Surface Pts in T-dir
				,	pDOUBLE		Dis_t_T			//  Output t distribution Pts. for Ratio Business				
				/////////////////////////
				,	BOOL		bLast_R			//  Last Patch in R-Dir for Output saving decision
				,	int			nDegree_R		//  Degree in R-Dir
				,	int			nDim_R			//  3= NonRational / 4 = Rational
				,	int			nt_R			// 	# of subdivision to compute Surface Pts in R-dir
				,	pDOUBLE		Dis_t_R			//  Output t distribution Pts. for Ratio Business
				/////////////////////////
				,	pWORLD		pOut			// 	Total Output Points Array
				,	pDOUBLE		pOutWts			// 	Total Output Wts Array
				,	int			nEmitTot_S		//  Total Points for All Patches in S-dir
				,	int			nEmitTot_ST		//  Total Points for All Patches in ST-plane(needed for Memory)
				,	int			nSolides_S		//  Total Number of Patches for Ratio Business 
				,	int			nSolides_T		//  Total Number of Patches for Ratio Business 
				,	int			nSolides_R		//  Total Number of Patches for Ratio Business 
			)
{
    /////////////////////////////////
	WORLD		C_R[4][4];
	pWORLD		p_R;
	double 		W_R[4][4];
	pDOUBLE		pw_R;
	int			i,j,k,ir,nOut = 0, nOutST,nMaxR, nMaxSTR, nMaxS, nMaxT, nMax_ST;
	//////////////////////////////////////////////////////////////////// LOOP
	nMaxS 	= bLast_S?(nt_S+1):nt_S; // no. of pts to be generated in U
	nMaxT 	= bLast_T?(nt_T+1):nt_T; // no. of pts to be generated in V
	nMax_ST	= nMaxS * nMaxT;
	/////////////////////////////
	nMaxR	= bLast_R?nt_R+1:nt_R;
	nMaxSTR	= nMax_ST * nMaxR;
	//////////////////////////////
	double 	delr	= 1.0/nt_R;
	double	t		= -delr;				
	//////////////////////////////// memory
	PW44 pCon_S4T4	= new pWORLD[4][4];	//	Control Pt. array for the patch: RESERVED for Maximum Cubic
	PD44 pWts_S4T4	= new pDOUBLE[4][4]; 
	PW4 ppCon_R4	= new pWORLD[4];
	PD4 ppWts_R4	= new pDOUBLE[4];
	/////////////////////////////////////////////////////////////////// R Loop
	p_R		= pOut;
	pw_R	= pOutWts;
	//////////////
	for (ir=0;ir<nMaxR;ir++)
	{
		if(nSolides_R == 1 && nDegree_R == 1) // Ratio business/ Single & Linear
			t = Dis_t_R[ir];
		else
			t += delr;
		///////////////////////// Create Con_ST & Wts_ST for a specific R
		for(i=0;i<=nDegree_S;i++)			
		{
			for(j=0;j<=nDegree_T;j++)
			{
				for(k=0;k<=nDegree_R;k++)
				{
					ppCon_R4[k] = ppCon_S4T4R4[i][j][k];
					ppWts_R4[k] = ppWts_S4T4R4[i][j][k];
				}
				//////////////////////////////////////////////////////////////////////////// Memory :Fix
				PDMA24	pMG_1 = (PDMA24) new DMA24;	//  Basis*Geometry Matrix for Linear
				PDMA34	pMG_2 = (PDMA34) new DMA34;	//  Basis*Geometry Matrix for Quadratic
				PDMA44	pMG_3 = (PDMA44) new DMA44;	//  Basis*Geometry Matrix for Cubic
				////////////////////////////////// Make Coef * Geometry Matrix for V-dir
				HO_ComputeMG(ppCon_R4,ppWts_R4,pMG_1,pMG_2,pMG_3,nDegree_R,nDim_R);
				/////////////////////////////////////////////////////////////// Curve Pt. in W-dir
				HO_Make_A_CurvePt_V(pMG_1,pMG_2,pMG_3,nDegree_R,nDim_R,t,&C_R[i][j],&W_R[i][j]);
				///////////////
				pCon_S4T4[i][j] 	= &C_R[i][j];
				pWts_S4T4[i][j]		= &W_R[i][j];
				//////////////////////////////////////////////////////////////////////////// Memory :Free

				delete [] pMG_1;	//  Basis*Geometry Matrix for Linear
				delete [] pMG_2;	//  Basis*Geometry Matrix for Quadratic
				delete [] pMG_3;	//  Basis*Geometry Matrix for Cubic
			}
		}
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"CSolid4::HO_Make_A_Solid-Just before Calling HO_Make_A_Solid\nir = %d",ir);
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"pCon_S4T4[%d][%d]: Actually[4][4]\n",nDegree_S+1,nDegree_T+1);
		for(m=0;m<(nDegree_S+1);m++)
		{
			for(k=0;k<(nDegree_T+1);k++)
			{
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f %7.2f %7.2f \n", m, k, 
					pCon_S4T4[m][k]->x, pCon_S4T4[m][k]->y, pCon_S4T4[m][k]->z );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////// Go make a patch in ST-dir
		nOutST = HO_Make_A_Patch
							(
								pCon_S4T4,pWts_S4T4,
								bLast_S,nDegree_S,nDim_S,nt_S,Dis_t_S,
								bLast_T,nDegree_T,nDim_T,nt_T,Dis_t_T,
								p_R,pw_R,nEmitTot_S,nSolides_S,nSolides_T
						
							);
		///////////////////////////
		if(nOutST != nMax_ST)
		{
			//////////////////
			delete [] pCon_S4T4;
			delete [] pWts_S4T4;
			delete [] ppCon_R4;
			delete [] ppWts_R4;
			//////////////////
			AfxMessageBox("CSolid4::HO_Make_A_Solid\nnOutST != nMaxST");
			return -1;
		}											
		else
		{	
			/////////////////
			nOut	+= nOutST;
			////////////////////////////////// Starting memory of Corner for next R-Level
			p_R		+= nEmitTot_ST;
			pw_R	+= nEmitTot_ST;
		}	
	}
	//////////////////
	delete [] pCon_S4T4;
	delete [] pWts_S4T4;
	delete [] ppCon_R4;
	delete [] ppWts_R4;
	//////////////////
	if(nOut != nMaxSTR)
		return -1;
	else	
		return nOut;
	////////////////
}
//////////////////////////////////////////////////////////////////////
int	CSolid4::TensorProduct_3D
				(
					SOLIDOUTPUT		O_kind		//  Output Method
				,	BOOL			bClosed_S	//  IsClosed_S
				,	int				nDegree_S	//  Degree in S-Dir
				,	int				nCon_S		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_S		//  3= NonRational / 4 = Rational
				,	int				nSolides_S	//  Total Number of Patches 
				,	pINT			Num_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	BOOL			bClosed_T	//  IsClosed_T
				,	int				nDegree_T	//  Degree in T-Dir
				,	int				nCon_T		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_T		//  3= NonRational / 4 = Rational
				,	int				nSolides_T	//  Total Number of Patches 
				,	pINT			Num_t_T		//  Number of Output Segments Array in T-Dir for each patch
				,	pDOUBLE			Dis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	BOOL			bClosed_R	//  IsClosed_S
				,	int				nDegree_R	//  Degree in S-Dir
				,	int				nCon_R		//  number of CONTROL points: ALWAYS BEZIER
				,	int				nDim_R		//  3= NonRational / 4 = Rational
				,	int				nSolides_R	//  Total Number of Patches 
				,	pINT			Num_t_R		//  Number of Output Segments Array in S-Dir for each patch
				,	pDOUBLE			Dis_t_R		//  Output t distribution Pts. for Ratio Business				
				,	pWORLD			pCon_STR	//  Total Input CONTROL Points Array
				,	pDOUBLE			pWts_STR	//  Rational Bezier Weights Array at input Control Pts		
				,	pWORLD			pOut_STR	//  Total Output Points Array
				,	pDOUBLE			pOutWts_STR	//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	int				nOut		//	expected number of generated Patch vertices	
				)
{
    ///////////////////////////////////
	if	(
			(!nCon_S)||(nSolides_S<1)||
		   	(!nCon_T)||(nSolides_T<1)||
		   	(!nCon_R)||(nSolides_R<1)||
			(!pCon_STR)||(!pOut_STR)||(!pOutWts_STR)
		)			   	
		return ERROR_MISSING_ARGUMENTS;
/*		
    ////////////////////////////////////////////////////// generate
    													// FDiffxMCoeff	
    DMAT EUM,EVM;
	ComputeFDiff_x_Mcoeff( kind, bias, tension,nSegU,nSegV,EUM,EVM);
*/	
	////////////////////////////////////////////////////// ControlSteps & Basis
//	PDMA22 pMCoef_1 = (PDMA22)CoefBezierLin;	// Linear
//	PDMA33 pMCoef_2 = (PDMA33)CoefBezierQuad;	// Quadratic
//	PDMA44 pMCoef_3 = (PDMA44)CoefBezierCubic;	// Cubic
	/////////////////		ASUMMED ALWAYS BEZIER !!!			////////////////////
	int	CtlStep_S = nDegree_S;		// Control Pt. Step
	int	CtlStep_T = nDegree_T;		// Control Pt. Step
	int	CtlStep_R = nDegree_R;		// Control Pt. Step
	////////////////////////////////////////////////////// CreatePatchPts
	int nPtActual;
	if (O_kind == PA_FINITEDIF)
		;	// nothing for Now
		///////////////////////////
//		nPtActual = FD_MakePatches(nCon,pCon,nDim,pWts,Num_t,pOut,nCurves); 
		///////////////////////////
	else						
	if (O_kind == PA_HORNER) 	// for now same method in S & T
	{
		///////////////////////////
		nPtActual = HO_MakeSolides
					(
						bClosed_S,CtlStep_S,nDegree_S,nDim_S,nCon_S,nSolides_S,Num_t_S,Dis_t_S, 
						bClosed_T,CtlStep_T,nDegree_T,nDim_T,nCon_T,nSolides_T,Num_t_T,Dis_t_T, 
						bClosed_R,CtlStep_R,nDegree_R,nDim_R,nCon_R,nSolides_R,Num_t_R,Dis_t_R, 
						pWts_STR,pCon_STR,pOut_STR,pOutWts_STR
					);
		///////////////////////////
	}
	////////////////////
	if(nPtActual != nOut)
	{
		//////////////////
		AfxMessageBox("CSolid4::TensorProduct_Surfaces\nnPtActual != nOut");
		return -1;
	}		
    else
		return nPtActual;
}
/////////////////////////////////// end of module /////////////////
/*
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Just in CSolid4::TensorProduct");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m;
	    ///////////////////
		j = sprintf(buf,"pMCoef_1[%d][%d]\n",2,2);
		for(m=0;m<2;m++)
		{
			for(k=0;k<2;k++)
			{
		   		j += sprintf( buf + j, "%7.2f ", pMCoef_1[m][k] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
*/



