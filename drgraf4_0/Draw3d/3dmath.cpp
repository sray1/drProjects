// XForm.cpp : implementation of the C3DMath class
//

#include "stdafx.h"
#include <math.h>                  
/////////////////////
//#include "Def_Lims.h"
//#include "drgraf.h"
//#include "drgradoc.h"
//#include "ObjMgr.h"
///////////////////// SpecObjs
//#include "HitNet.h"
/////////////////////
#include "Def_Type.h"
///////////////////
#include "3dMath.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// C3DMath

IMPLEMENT_SERIAL(C3DMath,CObject,1)
/*
BEGIN_MESSAGE_MAP(C3DMath,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(C3DMath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
C3DMath::C3DMath()
{
//	ObsoleteSystem(FALSE);
}
 
///////////////////////////////////////////////////////////// 
#pragma optimize("",off)
void C3DMath::BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size)
{
					if( p1 && p2 )
					HUGECOPY(p1, p2, size);
}
#pragma optimize("",on) 
/////////////////////////////////////////////////////////////
//BOOL C3DMath::AreSame_DOUBLE(double a, double b)
BOOL C3DMath::AreSame_DOUBLE(double a, double b, double dRatio)
{
//	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
//	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
//	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	if((a == 0.) && (b == 0.))
		return TRUE;
	//////////////////////////
	double den,del,rat;
	del = fabs(a - b);
	////////////////////////// 
	if( del == 0. )
		return TRUE;
	//////////////////////////////////////////////////////////// Check
	double fa = fabs(a);
	double fb = fabs(b);
	//////
	den = (fa>fb)?fa:fb;
	rat = del/den;
	//////////////
//	if(rat<pHitNet->GetDblRatio())
	if(rat<dRatio)
		return TRUE;
	////////////////
	return FALSE;
}

//BOOL C3DMath::AreSame_WORLD(pWORLD pa, pWORLD pb)
BOOL C3DMath::AreSame_WORLD(pWORLD pa, pWORLD pb, double dRatio)
{
//	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
//	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
//	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	double den,del,rat;
	///////////////////
	double aLen = fabs(pa->x*pa->x + pa->y*pa->y + pa->z*pa->z);
	double bLen = fabs(pb->x*pb->x + pb->y*pb->y + pb->z*pb->z);
	////////////////////////////////////////////////////////////
	if	(
			( (aLen == 0.) && (bLen == 0.) )
		)
		return TRUE;
	//////////////////////////////////////////////////////////// Check
	den = (aLen>bLen)?aLen:bLen;
	////////////////////////////////
	del = fabs
			(
				(pa->x - pb->x)*(pa->x - pb->x) + 
				(pa->y - pb->y)*(pa->y - pb->y) + 
				(pa->z - pb->z)*(pa->z - pb->z)
			);
	////////////////////////// 
	if( del == 0. )
		return TRUE;
	////////////////////////// ratio: Lengthwise
	rat = sqrt(del/den);
	//////////////
//	if(rat<pHitNet->GetDblRatio())
	if(rat<dRatio)
		return TRUE;
	////////////////
	return FALSE;
}

void C3DMath::Add3DPts(pLPOINT3 pa, pLPOINT3 pb, pLPOINT3 pc)
{
	/////////////////////////// update
	pc->x	= pa->x + pb->x;
	pc->y	= pa->y + pb->y;
	pc->z	= pa->z + pb->z;
    /////////////////////
	return;
}	

void C3DMath::Add3DPts(pWORLD pa, pWORLD pb, pWORLD pc)
{
	/////////////////////////// update
	pc->x	= pa->x + pb->x;
	pc->y	= pa->y + pb->y;
	pc->z	= pa->z + pb->z;
    /////////////////////
	return;
}	

void C3DMath::Sub3DPts(pLPOINT3 pa, pLPOINT3 pb, pLPOINT3 pc)
{
	/////////////////////////// update
	pc->x	= pa->x - pb->x;
	pc->y	= pa->y - pb->y;
	pc->z	= pa->z - pb->z;
    /////////////////////
	return;
}	

void C3DMath::Sub3DPts(pWORLD pa, pWORLD pb, pWORLD pc)
{
	/////////////////////////// update
	pc->x	= pa->x - pb->x;
	pc->y	= pa->y - pb->y;
	pc->z	= pa->z - pb->z;
    /////////////////////
	return;
}	

void C3DMath::Avg3DPts(pWORLD pda, pWORLD pdb, pWORLD pdc)
{
	/////////////////////////// update
	pdc->x	= (pda->x + pdb->x)*.5;
	pdc->y	= (pda->y + pdb->y)*.5;
	pdc->z	= (pda->z + pdb->z)*.5;
    /////////////////////
	return;
} 

void C3DMath::Scale3DPts(double scale, pWORLD pa)
{
	/////////////////////////// update
	pa->x	= pa->x * scale;
	pa->y	= pa->y * scale;
	pa->z	= pa->z * scale;
    /////////////////////
	return;
}
	
void C3DMath::ScaleVECTOR(double scale,pVECTOR pV)
{
	register int i;

	for(i=0;i<=2;i++)
		pV->v[i] = pV->v[i] * scale;
	//////////////////
}	
	
double C3DMath::Dot3DPts(pWORLD pa,pWORLD pb)
{

	return 		(	pa->x * pb->x +
					pa->y * pb->y +
					pa->z * pb->z
				);
	///////////
	
}	

void C3DMath::Cross3DPts(pWORLD pb,pWORLD pc,pWORLD pa)
{

	//////////////////
	pa->x= pb->y*pc->z - pb->z*pc->y; 
	pa->y= pb->z*pc->x - pb->x*pc->z;
	pa->z= pb->x*pc->y - pb->y*pc->x;
	//////////////////
	return;
	
}	

void C3DMath::AddVECTOR(pVECTOR a,pVECTOR b,pVECTOR c)
{
	register int i;

	for (i=0;i<=2;i++)
		c->v[i] = a->v[i] + b->v[i];
}

double C3DMath::VdotV(VECTOR Va,VECTOR Vb)
{
	//////////////////
	return 	sqrt(	Va.v[0] * Vb.v[0] +
					Va.v[1] * Vb.v[1] +
					Va.v[2] * Vb.v[2] +
					Va.v[3] * Vb.v[3] 
				);
	///////////
	
}	
	
void C3DMath::VcrossV(pVECTOR pVa,pVECTOR pVb,pVECTOR pVc)
{
	//warning: only the first THREE components are used.
	//////////
	VECTOR vt;

	vt.v[0] =  pVa->v[1]*pVb->v[2] - pVb->v[1]*pVa->v[2];
	vt.v[1] =  pVb->v[0]*pVa->v[2] - pVa->v[0]*pVb->v[2];
	vt.v[2] =  pVa->v[0]*pVb->v[1] - pVb->v[0]*pVa->v[1];
	/////////
	*pVc = vt;
	//////////////////
}	

void C3DMath::Normalize(pLPOINT3 plSrc,pWORLD pdDest,int nPrecision)
{
	//////////////////////////////////////////////// 
	double x,y,z,dWorldBase;
	dWorldBase = pow(10.,(double)nPrecision);
	x = ( ((double)plSrc->x) /dWorldBase);         // divide by 10**nPrecision
	y = ( ((double)plSrc->y) /dWorldBase);         // divide by 10**nPrecision
	z = ( ((double)plSrc->z) /dWorldBase);         // divide by 10**nPrecision 
	/////////////////
	double r = 1.0/sqrt(x*x + y*y + z*z);
    /////////////////////////////////////
    pdDest->x = x*r;
    pdDest->y = y*r;
    pdDest->z = z*r;
	/////////////////
}

void C3DMath::Normalize(pWORLD pdSrc,pWORLD pdDest)
{
	//////////////////////////////////////////////// 
	double r = 1.0/sqrt(	pdSrc->x*pdSrc->x + 
							pdSrc->y*pdSrc->y + 
							pdSrc->z*pdSrc->z);
    /////////////////////////////////////
    pdDest->x = pdSrc->x*r;
    pdDest->y = pdSrc->y*r;
    pdDest->z = pdSrc->z*r;
	/////////////////
}
	
void C3DMath::GetIdentityMATRIX(pMATRIX pM)
{
	register int i,j;
	
	for(i=0;i<=3;i++)
		for(j=0;j<=3;j++)
			pM->v[i][j] = (i==j)?1.0:0.;
	
}
	
void C3DMath::SetMATRIX(pMATRIX pM,pWORLD pCol_X,pWORLD pCol_Y,pWORLD pCol_Z,pWORLD pCol_W)
{
	/////////////////////// Ist Col
	pM->v[0][0] = pCol_X->x;
	pM->v[1][0] = pCol_X->y;
	pM->v[2][0] = pCol_X->z;
	/////////////////////// 2nd Col
	pM->v[0][1] = pCol_Y->x;
	pM->v[1][1] = pCol_Y->y;
	pM->v[2][1] = pCol_Y->z;
	/////////////////////// 3rd Col
	pM->v[0][2] = pCol_Z->x;
	pM->v[1][2] = pCol_Z->y;
	pM->v[2][2] = pCol_Z->z;
	/////////////////////// 4th Col
	pM->v[0][3] = pCol_W->x;
	pM->v[1][3] = pCol_W->y;
	pM->v[2][3] = pCol_W->z;
	////////	
}
	
void C3DMath::ScaleMATRIX(double scale,pMATRIX pM)
{
	register int i,j;

	for (i=0;i<=2;i++)
		for (j=0;j<=2;j++)
			pM->v[i][j] = pM->v[i][j] * scale;
	//////////////////////
	
}

void C3DMath::AddMATRIX(pMATRIX pMa,pMATRIX pMb,pMATRIX pMc)
{
	MATRIX mt;
	register int i,j;

	for (i=0;i<=2;i++)
		for (j=0;j<=2;j++)
			mt.v[i][j] = pMa->v[i][j] + pMb->v[i][j];
	//////////		
	*pMc = mt;

	
}
	
void C3DMath::TransposeMATRIX(pMATRIX pM)
{
	register int i,j;
	MATRIX mt;

	for( i=0; i<= 3; i++ )
		for( j=0; j<=3; j++ )
			mt.v[i][j] = pM->v[j][i];
	//////////		
	*pM = mt;
	///////
	
}

void C3DMath::MultMATRIX(pMATRIX pMa,pMATRIX pMb,pMATRIX pMc)
{

	MATRIX 			mt;
	int				i;
	register int	j,k;

	for (i=0;i<=3;i++)
		for (j=0;j<=3;j++) 
		{
			mt.v[i][j] = 0.;
			for (k=0;k<=3;k++)
				mt.v[i][j] += pMa->v[i][k] * pMb->v[k][j];
		}
	//////////		
	*pMc = mt;
	
}

void C3DMath::F_MultMATRIX(pMATRIX a,pMATRIX b,pMATRIX c)
{
/*****************************************************************************
 *	methods:	standard algebraic multiplication of two 4x4 matrices.
 *				differs from MultMATRIX in terms of speed.
 *				F_MultMATRIX is	FASTER, but not very general.
 *****************************************************************************
*/
	MATRIX t;
    /////////
	t.v[0][0]	=		a->v[0][0]*b->v[0][0] + a->v[0][1]*b->v[1][0]
  					+	a->v[0][2]*b->v[2][0] + a->v[0][3]*b->v[3][0];
  	t.v[1][0]	=		a->v[1][0]*b->v[0][0] + a->v[1][1]*b->v[1][0]
  					+	a->v[1][2]*b->v[2][0] + a->v[1][3]*b->v[3][0];
  	t.v[2][0]	=		a->v[2][0]*b->v[0][0] + a->v[2][1]*b->v[1][0]
  					+	a->v[2][2]*b->v[2][0] + a->v[2][3]*b->v[3][0];
  	t.v[3][0]	=		a->v[3][0]*b->v[0][0] + a->v[3][1]*b->v[1][0]
  					+	a->v[3][2]*b->v[2][0] + a->v[3][3]*b->v[3][0];
    ///////////////////////////////////////////////////////////
  	t.v[0][1]	=		a->v[0][0]*b->v[0][1] + a->v[0][1]*b->v[1][1]
  					+	a->v[0][2]*b->v[2][1] + a->v[0][3]*b->v[3][1];
  	t.v[1][1]	=		a->v[1][0]*b->v[0][1] + a->v[1][1]*b->v[1][1]
  					+	a->v[1][2]*b->v[2][1] + a->v[1][3]*b->v[3][1];
  	t.v[2][1]	=   	a->v[2][0]*b->v[0][1] + a->v[2][1]*b->v[1][1]
  					+	a->v[2][2]*b->v[2][1] + a->v[2][3]*b->v[3][1];
  	t.v[3][1]	=   	a->v[3][0]*b->v[0][1] + a->v[3][1]*b->v[1][1]
  					+	a->v[3][2]*b->v[2][1] + a->v[3][3]*b->v[3][1];
    ///////////////////////////////////////////////////////////
  	t.v[0][2]	=		a->v[0][0]*b->v[0][2] + a->v[0][1]*b->v[1][2]
  					+	a->v[0][2]*b->v[2][2] + a->v[0][3]*b->v[3][2];
  	t.v[1][2]	=		a->v[1][0]*b->v[0][2] + a->v[1][1]*b->v[1][2]
  					+	a->v[1][2]*b->v[2][2] + a->v[1][3]*b->v[3][2];
  	t.v[2][2]	=		a->v[2][0]*b->v[0][2] + a->v[2][1]*b->v[1][2]
  					+	a->v[2][2]*b->v[2][2] + a->v[2][3]*b->v[3][2];
  	t.v[3][2]	=		a->v[3][0]*b->v[0][2] + a->v[3][1]*b->v[1][2]
  					+	a->v[3][2]*b->v[2][2] + a->v[3][3]*b->v[3][2];
    ///////////////////////////////////////////////////////////
  	t.v[0][3]	=		a->v[0][0]*b->v[0][3] + a->v[0][1]*b->v[1][3]
  					+	a->v[0][2]*b->v[2][3] + a->v[0][3]*b->v[3][3];
  	t.v[1][3]	=		a->v[1][0]*b->v[0][3] + a->v[1][1]*b->v[1][3]
  					+	a->v[1][2]*b->v[2][3] + a->v[1][3]*b->v[3][3];
  	t.v[2][3]	=		a->v[2][0]*b->v[0][3] + a->v[2][1]*b->v[1][3]
  					+	a->v[2][2]*b->v[2][3] + a->v[2][3]*b->v[3][3];
  	t.v[3][3]	=		a->v[3][0]*b->v[0][3] + a->v[3][1]*b->v[1][3]
  					+	a->v[3][2]*b->v[2][3] + a->v[3][3]*b->v[3][3];
	///////////////////////////////////////////////////////////
	BlockCopy((HUGEBLK)&t,(HUGEBLK)c, (HUGESIZE)sizeof(MATRIX));
	///////////////////////////////////////////////////////////
}

void C3DMath::InvertMATRIX(pMATRIX pMa,pMATRIX pMb)
{
	int		i,j,indx[4];
	double	d,col[4];
	MATRIX	A;

	BlockCopy( (HUGEBLK)pMa, (HUGEBLK)&A, sizeof(MATRIX) );
	LUDecompose( &A, indx, &d );
	for( j=0; j<4; j++ ) {
		col[0] = col[1] = col[2] = col[3] = 0.;
		col[j] = 1.;
		LUBackSubstitute( &A, indx, col );
		for( i=0; i<4; i++ )
			pMb->v[i][j] = col[i];
	}
	
}	

void C3DMath::GetBaryFromUV(pWORLD p1, pWORLD p2, pWORLD p3, pWORLD p, pWORLD pBCC)
{
	double rdet;
	//////////////////////////
	rdet = 1./GetDeterminant(p1, p2, p3);
	///
	pBCC->x = GetDeterminant(p,	 p2, p3) * rdet; 
	pBCC->y = GetDeterminant(p1, p,  p3) * rdet; 
	pBCC->z = GetDeterminant(p1, p2, p ) * rdet; 
	/////////
	return;
}

void C3DMath::GetUVFromBary(pWORLD p1, pWORLD p2, pWORLD p3, pWORLD p, pWORLD pBCC)
{
	//////////////////////////
	p->x = pBCC->x * p1->x + pBCC->y * p2->x + pBCC->z * p3->x; 
	p->y = pBCC->x * p1->y + pBCC->y * p2->y + pBCC->z * p3->y; 
	/////////
	return;
}

double C3DMath::GetDeterminant(pWORLD p1, pWORLD p2, pWORLD p3)
{

	return
		p1->x * ((p2->y * p3->z) - (p3->y * p2->z))
	   -p2->x * ((p1->y * p3->z) - (p1->z * p3->y))
	   +p3->x * ((p1->y * p2->z) - (p2->y * p1->z));
	//////////////////////

}

double C3DMath::GetDeterminant(pMATRIX pM)
{

	double	d;
	int		indx[4];
	MATRIX	A;

	BlockCopy( (HUGEBLK)pM, (HUGEBLK)&A, sizeof(MATRIX) );
	LUDecompose( &A, indx, &d );
	//////////////////////
	return d*A.v[0][0]*A.v[1][1]*A.v[2][2]*A.v[3][3];

}

void C3DMath::LUDecompose(pMATRIX a,pINT indx,pDOUBLE d)
{
/*****************************************************************************
 *
 *	Function:	LUDecompose
 *
 *	purpose:	Lower/Upper decomposition of a MATRIX.
 *
 *****************************************************************************
 */
	int		i,imax,j,k;
	double	big,dum,sum,temp;
	double	v[4];

	// WARNING!!! MATRIX a is overwritten by this process.

	*d=1.;
	for( i=0; i<4; i++ ) 
	{
		big = 0.;
		for( j=0; j<4; j++ )
			if( (temp = fabs(a->v[i][j])) > big )
				big = temp;
//		if( !big )
//			Debugger();// singular
		v[i] = 1./big;
	}
	for( j=0; j<4; j++ ) 
	{
		for( i=0; i<j; i++ ) 
		{
			sum = a->v[i][j];
			for( k=0; k<i; k++ )
				sum -= a->v[i][k] * a->v[k][j];
			a->v[i][j] = sum;
		}
		big = 0.;
		for( i=j; i<4; i++ ) 
		{
			sum = a->v[i][j];
			for( k=0; k<j; k++ )
				sum -= a->v[i][k] * a->v[k][j];
			a->v[i][j] = sum;
			if( (dum = v[i] * fabs(sum) ) >= big ) 
			{
				big = dum;
				imax = i;
			}
		}
		if( j != imax ) 
		{
			for( k=0; k<4; k++ ) 
			{
				dum = a->v[imax][k];
				a->v[imax][k] = a->v[j][k];
				a->v[j][k] = dum;
			}
			*d = -(*d);
			v[imax]=v[j];
		}
		indx[j] = imax;
//?		if( !a->v[j][j] )
//			a->v[j][j] = 1L;	// smallest representable value
		if( j != 3 ) 
		{
			dum = 1./ a->v[j][j];
			for( i=j+1; i<4; i++ )
				a->v[i][j] = a->v[i][j] * dum;
		}
	}
}

void C3DMath::LUBackSubstitute(pMATRIX a, pINT indx, pDOUBLE b)
{
/*****************************************************************************
 *
 *	Function:	LUBackSubstitute
 *
 *	purpose:	Lower/Upper back substitution of a MATRIX.
 *
 *****************************************************************************
 */
	int		i,ii=-1,ip,j;
	double	sum;

	for( i=0; i<4; i++ ) 
	{
		ip = indx[i];
		sum = b[ip];
		b[ip] = b[i];
		if( ii>=0 )
			for( j=ii; j<i; j++ )
				sum = sum - a->v[i][j] * b[j];
		else
		if( sum )
			ii = i;
		b[i] = sum;
	}
	for( i=3;i>=0;i-- ) {
		for( sum = b[i], j=i+1; j<4; j++ )
			sum = sum - a->v[i][j] * b[j];
		b[i] = sum / a->v[i][i];
	}
}

int C3DMath::Solve_TriDiag(pDOUBLE a, pDOUBLE b, pDOUBLE c, PDMA3 d, PDMA3 sol,
						 int L, int nDim)
{
/*****************************************************************************
 *					nDim MUST BE LESS THAN OR EQUAL TO 4 
 *    			///////////////////////////////////////////
 *
 *	Function:	Solve Tridiagonal Matrix Eqn of order [L+1]
 *				for nDim many cases
 *
 *	Method:		Use Gauss Elimination: Factorization/Back-substitution.
 *				The Thory of Splines and their Aplication
 *				Ahlberg et al
 *				DOES NOT DESTROY a,b,c,d
 *
 *	Input:		a,b,c:				lower, main and upper diagonals of matrix[L+1] each
 *				d:					RHS[L+1][nDim] 
 *				L:					matrix size [0->L]x[0->L] i.e., [L+1] x [L+1] size
 *	Output:		sol:				solution[L+1][nDim]
 *
 *	Return:		0:					successful
 *				-1:					Error
 *
 *****************************************************************************
 */
	int m;
	//////
	int k;
	pDOUBLE p,q;
	PDMA3 u;
	//////////////////////
	if(!(p	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(q	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(u	= new double[L+1][4]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
    //////////////////////////// Factorize
    p[0] = b[0];
    q[0] = -c[0]/p[0];
    for(m=0;m<nDim;m++)
    	u[0][m] = d[0][m]/p[0];
    //////////////////
    for(k=1;k<=L;k++)
    {
    	p[k] = a[k] * q[k-1] + b[k];
    	q[k] = -c[k]/p[k];
    	for(m=0;m<nDim;m++)
    		u[k][m] = (d[k][m] - a[k] * u[k-1][m])/p[k];
    }
    //////////////////////////// Back-substitute
    for(m=0;m<nDim;m++)
    	sol[L][m] = u[L][m];
    for(k=L-1;k>=0;k--)
    {
    	for(m=0;m<nDim;m++)
           	sol[k][m] = u[k][m] + q[k] * sol[k+1][m];
	}           	
	////////////
	delete [] p;
	delete [] q;
	delete [] u;
	/////////
	return 0;
	
}	    	

int C3DMath::Solve_TriDiagPeriodic(pDOUBLE a, pDOUBLE b, pDOUBLE c, PDMA3 d, 
											PDMA3 sol, int L, int nDim)
{
/*****************************************************************************
 *					nDim MUST BE LESS THAN OR EQUAL TO 4 
 *    			///////////////////////////////////////////
 *
 *	Function:	Solve Tridiagonal Matrix Eqn of order [L+1]
 *				for PERIODIC (Closed) Splines for which the matrix is
 *				of the form:
 *					b0	c0	0	0	0...	0	a0 <- 
 *					a1	b1	c1 	0	0...	0	0
 *					0	a2	b2	c2	0...	0	0
 *							.
 *								.
 *				->	cL	0	0	0	0...	aL	bL	
 *
 *	Method:		solve for sol(0),sol(1),...,sol(L-1) in terms of sol(L) in Ist L eqns.
 *				and then determine sol(L+1);
 *				The Thory of Splines and their Aplication
 *				Ahlberg et al p15
 *				DOES NOT DESTROY a,b,c,d
 *
 *	Input:		a,b,c:				lower, main and upper diagonals of matrix[L+1] each
 *				d:					RHS[L+1][nDim] 
 *				L:					matrix size [0->L]x[0->L] i.e., [L+1] x [L+1] size
 *	Output:		sol:				solution[L+1][nDim]
 *
 *	Return:		0:					successful
 *				-1:					Error
 *
 *****************************************************************************
 */

	int m;
	//////
	int k;
	pDOUBLE p,q,s,t;
	PDMA3 u,v;
	//////////////////////
	if(!(p	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(q	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(u	= new double[L+1][4]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	//////////////////////////
	if(!(s	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(t	= new double[L+1]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
	if(!(v	= new double[L+1][4]) )
	{
		AfxMessageBox("TriDiagonal:\nMemory Too Low ?");
		return -1;
	}	
    //////////////////////////// Factorize
    p[0] =  b[0];
    q[0] = -c[0]/p[0];
    for(m=0;m<nDim;m++)
    	u[0][m] =  d[0][m]/p[0];
    
    s[0] = -a[0]/p[0];
    //////////////////
    for(k=1;k<=L;k++)
    {
    	p[k] =  a[k] * q[k-1] + b[k];
    	q[k] = -c[k]/p[k];
   	    for(m=0;m<nDim;m++)
	    	u[k][m] = (d[k][m] - a[k] * u[k-1][m])/p[k];
     	s[k] = -a[k] * s[k-1]/p[k]; 
    }
    //////////////////////////// Back-substitute
    t[L] = 1;
    for(m=0;m<nDim;m++)
    	v[L][m] = 0;
    for(k=L-1;k>=0;k--)
    {
    	t[k] = s[k] + q[k] * t[k+1];
    	for(m=0;m<nDim;m++)
    	   	v[k][m] = u[k][m] + q[k] * v[k+1][m];
	}   	
    /////////////////////////////
    double tmp1,tmp2[4];
    tmp1 = c[L] * t[0] + a[L] * t[L-1] + b[L];
    for(m=0;m<nDim;m++)
	    tmp2[m] = d[L][m] - c[L] * v[0][m] - a[L] * v[L-1][m];
    
    for(m=0;m<nDim;m++)
    	sol[L][m] = tmp2[m]/tmp1;
	for(k=L-1;k>=0;k--)
	{
    	for(m=0;m<nDim;m++)
    		sol[k][m] = v[k][m] + t[k] * sol[L][m];
	}    		
	////////////
	delete [] p;
	delete [] q;
	delete [] u;

	delete [] s;
	delete [] t;
	delete [] v;
	/////////
	return 0;
	
}	    	

void C3DMath::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" C3DMath:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" C3DMath:    Loading\n");	// TODO: add loading code here
	}
		
}
////////////////////////////////// end of module //////////////////
