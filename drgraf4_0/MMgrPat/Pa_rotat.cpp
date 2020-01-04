// CPa_Rotat.cpp : implementation of the CPA_Rotat class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "PA_Rotat.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_Rotat

IMPLEMENT_DYNAMIC(CPA_Rotat,CObject)
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
//////////////////////////////////////////////
int CPA_Rotat::RotateCurve
	(
		BOOL	bClosed_T,
		int		nSegBZ_T,//	# of Quadratic Bezier Segments
		pDOUBLE	pDis,	//	Angle Distribution for each Bez Patch in degrees
						//		(not cumulative)
		WORLD	Axis,	//	unit direction vector of rotation axis
		WORLD	AxisPt, //  a pt. on the rotation vector
		int		nPts,	//	number of input Control points
		pWORLD	pPt,	//	input data point array
		pDOUBLE	pWt,	//	input data Weight array
		pWORLD	pOut,	//	Output Pts array
		pDOUBLE	pOutWts //	Output Wts array
	)	  
//Return:Int	nOut	//	number of points emitted
{
	//////////////////////////////////////////////// Bezier Quadratic
	int Num_BZ_Con = 2 * nSegBZ_T + 1;
	if(bClosed_T)
		Num_BZ_Con--;
	////////////////////////////////////////////////
	pWORLD	pRow,p;
	pDOUBLE pRowWt,pW;
	double	inc = 0;		// initialize
	int		nV,nS,i,j;
	long	sizeRow,sizeRowWt;
	////////////////////////////////
	if(!pOut)
	{
		AfxMessageBox("Internal Problem:\nCPA_Rotat::RotateCurve\npOut = NULL");
		return -1;
	}
	C3DMath		Math3D;
	///////////////////
	sizeRow		= nPts*sizeof(WORLD);
	sizeRowWt	= nPts*sizeof(double);
	nS 			= Num_BZ_Con;		
	nV 			= nPts*nS;
	//////////////////////////////////////////////////////////// Put Curve In-place
	pRow=pOut; 
	Math3D.BlockCopy( (HUGEBLK)pPt, (HUGEBLK)pRow, sizeRow );
	pRowWt=pOutWts; 
	Math3D.BlockCopy( (HUGEBLK)pWt, (HUGEBLK)pRowWt, sizeRowWt );
	///////////////////
	WORLD	Center;
	pWORLD	pb0,pb1,pb2;
	double	Radius;
	pDOUBLE	pb0_W,pb1_W,pb2_W;
//	int loc;
	WORLD	Tem;
	pWORLD	pTem = &Tem;
	double	WTem;
	pDOUBLE	pWTem = &WTem;
	//////////////////////
	p	= pRow;
	pW	= pRowWt;
	/////////
	int nOutC = 0;
	int nPts2 = 2 * nPts;	// for b2
	for( i=0;i<nPts;i++ ) 
	{
		nOutC++;	// for starting b0
		////////////////////////////////////////////// Center & Radisus for the Current Circle	
		Calc_CandR(p,&Center, &Radius, Axis, AxisPt);
		///////////////////
		pb0		= p  - nPts2;
		pb0_W	= pW - nPts2;
		/////////////////////
		for( j=1;j<=nSegBZ_T;j++ )
		{
			///////////////////////////////////////////// Angle
			inc = pDis[j-1];	// not cumulative
			//////////////////////////// Reset Start
			pb0		+= nPts2;
			pb0_W	+= nPts2;
			////////////////////////
			// if Closed: DONOT HAVE Room for Last Control b2
			if(!(bClosed_T && (j == nSegBZ_T) )  )
			{	
				pb2		= pb0	+	nPts2;
				pb2_W	= pb0_W	+	nPts2;
				nOutC++;	// Control Counter
			}
			else
			{	
				pb2		= pTem;
				pb2_W	= pWTem;
			};
			/////////////////////////////////////////// Generate a Pt. by Rotation
			GetAPtByRotation(pb0, Center, Axis, inc, pb2);
			////////////////////////
			*pb2_W = *pb0_W;
			///////////////////////
			pb1		= pb0	+ nPts;
			pb1_W	= pb0_W	+ nPts;
			nOutC++;	// Control Counter
			//////////////////////////// Zero Radius Check
			if(Radius<.000001)
			{
				pb1->x = pb0->x;
				pb1->y = pb0->y;
				pb1->z = pb0->z;
				*pb1_W = *pb0_W;
			}
			else
				/////////////////////////////////////////// Generate Tangent Pts & Wts
				Compute_b1_w1(&Center, Radius, pb0, pb2, *pb0_W, pb1, pb1_W);
				///////////////////////////
		}
		///////////////////////////
		p++;
		pW++;
	}			
//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Leaving CPA_Rotat::RotateCurve");
		AfxMessageBox(*str);
		///////////////////
		int j,k,m,mk;
	    ///////////////////
		j = sprintf(buf,"pOut[%d][%d]: \n",nS,nPts);
		for(k=0;k<nS;k++)
		{
			for(m=0;m<nPts;m++)
			{
				mk = m + k*nPts;
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f %7.2f %7.2f \n", m, k, 
					pOut[mk].x, pOut[mk].y, pOut[mk].z );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"pOutWts[%d][%d]: \n",nPts,nS);
		for(k=0;k<nS;k++)
		{
			for(m=0;m<nPts;m++)
			{
				mk = m + k*nPts;
		   		j += sprintf( buf + j, "m=%2d k=%2d  %7.2f \n", m, k, 
					pOutWts[mk] );
			} 
	  		j += sprintf( buf + j, "\n");
		}
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////// Generate Tangent Pts & Wts
	if(nOutC != nV)
	{
		AfxMessageBox("Internal Problem:\nCPA_Rotat::RotateCurve\nnOutC != nV");
		return -1;
	}
	else
		return nV;
	//////////////
}

int CPA_Rotat::GetAPtByRotation(pWORLD pb0 , WORLD AxisPt, WORLD Normal, 
								double dAng, pWORLD pb2)
{

/*************************************************************
//	FOLLOWING FORMULA IS NOT BEING USED
//	r = (r dot n)n + [r - (r dot n)n] cos(theta)
//				   + [n cross (r - (r dot n)n)] sin(theta)
//	r = (r dot n)n (1 - cos(theta)) + r cos(theta)
//				   + [n cross r] sin(theta)
//	indicial:
//	r[i] = (r dot n)n[i] (1 - cos(theta)) + r[i] cos(theta)
//				   + (e[i][j][k].n[j].r[k]) sin(theta)
***************************************************************/
	WORLD b2Local;
	pWORLD pb2Local = &b2Local;
	///////////////////////////	
	pb2Local->x	= pb0->x;
	pb2Local->y	= pb0->y;
	pb2Local->z	= pb0->z;
	////////////////////////////////////////////////////////////////// 
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////// Translate AxisPt & DOld to Origin
	XForm.Translate(pRot, -AxisPt.x, -AxisPt.y, -AxisPt.z, XF_REPLACE);	
	//////////////////////////////////////// 	
	XForm.Transform(pb2Local, pb2Local, pRot);	  
	//////////////////////////////////////////////////////////// Generatioe by rotation
	WORLD Origin = {0.0,0.0,0.0};
	double rAng = atan(1.0) * dAng/45.; // radian 
	////////////
	Math3D.GetIdentityMATRIX(pRot);
	XForm.RotateAboutLineMATRIX(pRot, &Origin, &Normal,rAng,XF_REPLACE);
	XForm.Transform(pb2Local, pb2Local, pRot);
	//////////////////////////////////////////////////////////// Translate Data Back: New Pt
	Math3D.GetIdentityMATRIX(pRot);
	XForm.Translate(pRot, AxisPt.x, AxisPt.y, AxisPt.z, XF_REPLACE);
	XForm.Transform(pb2Local, pb2Local, pRot);
	/////////////////////	
	pb2->x	= pb2Local->x;
	pb2->y	= pb2Local->y;
	pb2->z	= pb2Local->z;
	///////////////////
	return 0;
}	

int CPA_Rotat::Compute_b1_w1(pWORLD pCenter,double Rad,pWORLD pb0,pWORLD pb2,double w_b0,
									pWORLD pb1,pDOUBLE pw1)
{

	// To find:
	//		b1	= Bezier In-Betwen Pt.
	//			= Intersection of Tangents at b0 and b2
	// and
	//		w1	= Weight at b1 = cos(alfa) * w_b0
	//////////////////////////////////////////////////////// MidPt of Chord
	WORLD Rm;
	////////////
	Rm.x = .5 * (pb0->x + pb2->x);
	Rm.y = .5 * (pb0->y + pb2->y);
	Rm.z = .5 * (pb0->z + pb2->z);
	//////////////////////////////////////////////////////// normal
	WORLD N;
	//////////
	N.x = Rm.x - pCenter->x;									
	N.y = Rm.y - pCenter->y;									
	N.z = Rm.z - pCenter->z;
	double Base = sqrt(N.x*N.x + N.y*N.y + N.z*N.z );
	//////////////////////////////////////////////////////// Weight = cos(alfa)*w_b0 
	double w1;
	w1 = Base/Rad;
	//////////////////////////////////////////////////////// Bezier In-Between Pt
	//////////////////////////////// Unit Normal 
	Base = 1./Base;
	N.x *= Base;									
	N.y *= Base;									
	N.z *= Base;
	////////////// Rad/cos(alfa) = length from center to b1
	Base = Rad/w1;
	////////////////////////////////
	pb1->x 	= pCenter->x + Base * N.x; 
	pb1->y 	= pCenter->y + Base * N.y; 
	pb1->z 	= pCenter->z + Base * N.z;
	//////////////////////////////// Must be scale with b0 & b2 Weights
	*pw1	= w1 * w_b0; 
	//////////////////////////////
	return 0;
	
}

int CPA_Rotat::Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE pRadius, WORLD Normal,WORLD AxPt)
{
	//////////////////////////////
	// Content of Data:	//
	//		1. NID_I	NODE	//
	///////////////////////////////////////////////////////
	// given:
	//		Data	= a Pt. on the Current Circle
	//		Normal	= to the Plane of the circle (unit Normal)
	//		AxPt	= a Pt on the Normal
	// Now
	//		Center	= rAxPt + ((rData-rAxPt) dot N) N;
	//		Radius	= ||rCenter - rData||
	////////////////////////////////////////////////////////
	C3DMath	Math3D;
	WORLD	temp;
	//////////////////////////////////////////////////////// Center
	Math3D.Sub3DPts(pData,&AxPt,pCenter);
    Math3D.Set3DPts(&temp, Normal.x, Normal.y, Normal.z);
	Math3D.Scale3DPts(Math3D.Dot3DPts(pCenter,&Normal),&temp);
    Math3D.Set3DPts(pCenter, AxPt.x, AxPt.y, AxPt.z);
	Math3D.Add3DPts(pCenter, &temp, pCenter);			// Center
	//////////////////////////////////////////////////////// Radius
	Math3D.Sub3DPts(pCenter,pData,&temp);
	*pRadius = Math3D.Len3DPts(&temp);
	/////////
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////