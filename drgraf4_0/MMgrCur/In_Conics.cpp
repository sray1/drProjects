// Mouse.cpp : implementation file
//
/////////////////////////////////////////////////////////
//		R A T I O N A L  B E Z I E R  C O N I C S
/////////////////////////////////////////////////////////

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
#include "XForm.h" 
/////////////////////
#include "In_CONICS.h" 

#ifdef _DEBUG
#include <stdio.h>
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
IMPLEMENT_SERIAL(CIn_Conics,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2        
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CIn_Conics::CIn_Conics()
{
	/////////////////// Memory
	m_MemErr		= 0;
	m_pWts_BS_S		= NULL;
	m_pWts_BZ_S		= NULL;
	m_pData			= NULL;
	m_pDat_Ex		= NULL;
	m_pCon_BS_S		= NULL;
	m_pCon_BZ_S		= NULL;
	m_pInCon_BZ_S	= NULL;	// In-between bezier pts
	m_pInWts_BZ_S	= NULL;	// In-between bezier wts
}

CIn_Conics::~CIn_Conics()
{
	/////////////////// Memory
	if(m_MemErr<0)
	{
		if(m_pWts_BS_S)
			delete [] m_pWts_BS_S; 
		if(m_pWts_BZ_S)
			delete [] m_pWts_BZ_S; 
		if(m_pData)
			delete [] m_pData; 
		if(m_pDat_Ex)
			delete [] m_pDat_Ex; 
		if(m_pCon_BS_S)
			delete [] m_pCon_BS_S; 
		if(m_pCon_BZ_S)
			delete [] m_pCon_BZ_S;
	}	
}
///////////////////////////////////////////////////////////////////////////////////// Interpolation
	//////////////////////////////////////////////////////////////////////////////
	//	NOTE:  BackGround:	k = Order; k-1 = Degree of Curve [ k=3 for Conics]	//
	//																			//
///////////////////////////////////////////////////////////////////////////////////////////////	

int CIn_Conics::FillUpBezier(pWORLD Data,pWORLD Con,pDOUBLE Wts,pWORLD InData,pDOUBLE InWts,
																int nCon,int L,BOOL bClosed)
{
	int k;
	//////////////////////////////////////////////// Junctions
	int nJunc = L+1;
	if(bClosed)
		nJunc--;
	//////////////	
	for(k=0;k<nJunc;k++)                        
	{                                                                     
		Con[2*k].x 	= Data[k].x;
		Con[2*k].y 	= Data[k].y; 
		Con[2*k].z 	= Data[k].z;
		Wts[2*k]	= 1.0;			// STANDARD FORM	
	}
	//////////////////////////////////////////////// In-Betweens Cons/Wts (L)
	for(k=0;k<L;k++)
	{
		Con[2*k+1]	= InData[k]; 
		Wts[2*k+1]	= InWts[k];	
	}
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"FillUpBezier\nCIn_Conics::FillUpBezier");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"Cons[%d]\n      X             Y            Z\n",nCon);
		for(k=0;k<nCon;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n", k,
		   							Con[k].x,Con[k].y,Con[k].z );
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
		j = sprintf(buf,"Wts[%d]\n      X             Y            Z\n",nCon);
		for(k=0;k<nCon;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,Wts[k] );
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

int CIn_Conics::FillUpSpline(pWORLD Con_BZ, pDOUBLE Wts_BZ,int nCon_BZ,
							 pWORLD Con_BS, pDOUBLE Wts_BS,int nCon_BS, int L, BOOL bClosed)
{
	int k;
	///////////////////////////////////////////// 
	{
		////////////////////////////////////////// Controls                                                                     
		Con_BS[0].x = Con_BZ[0].x;
		Con_BS[0].y = Con_BZ[0].y;
		Con_BS[0].z = Con_BZ[0].z;
		////////////////////////////////////////// Weights (Not Right)!!!                                                                     
		Wts_BZ[0]	= 1.0;
		////////////////////////		
		for(k=1;k<nCon_BS-1;k++)                        
		{
			////////////////////////////////////// Controls                                                                     
			Con_BS[k].x = Con_BZ[2*k-1].x;
			Con_BS[k].y = Con_BZ[2*k-1].y;
			Con_BS[k].z = Con_BZ[2*k-1].z;
			////////////////////////////////////// Weights                                                                     
			Wts_BS[k]	= 1.0;		
		}
		////////////////////////////////////////// Controls                                                                     
		Con_BS[nCon_BS-1].x = Con_BZ[nCon_BZ-1].x;
		Con_BS[nCon_BS-1].y = Con_BZ[nCon_BZ-1].y;
		Con_BS[nCon_BS-1].z = Con_BZ[nCon_BZ-1].z;
		////////////////////////////////////////// Weights                                                                     
		Wts_BS[nCon_BS-1]	= 1.0;
		////////////////////////		
	}	
	return 0;
}

int CIn_Conics::GetPlanarCoords(WORLD b0,WORLD b1,WORLD b2,WORLD pt,
								pWORLD b02,pWORLD b12,pWORLD b22,pWORLD pt2)
{
//	////////////////////////////////////////////////////
//	Rotate so that the Normal to the plane of the Conic
//					points to z-Axis
//				SO THE CONIC IS IN XY PLANE
	//////////////////////////////////////////////////// 
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////////////////////////// Translate b0 to Origin
	XForm.Translate(pRot, -b0.x, -b0.y, -b0.z, XF_REPLACE);	
	//////////////////////////////////////// 	
	WORLD a,b,c,d;
	//////////////
	XForm.Transform(&b0, &a, pRot);	  
	XForm.Transform(&b1, &b, pRot);	  
	XForm.Transform(&b2, &c, pRot);	  
	XForm.Transform(&pt, &d, pRot);	  
	//////////////////////////////////////// Normal to plane of Conic
	WORLD wN;
	WORLD rab,rac;
	Math3D.Sub3DPts(&b, &a, &rab);
	Math3D.Sub3DPts(&c, &a, &rac);
	Math3D.Cross3DPts(&rab,&rac,&wN);
	//////////////////////// Normalize
	Math3D.Normalize(&wN,&wN);
	//////////////////////////////////////// Rotation Mat: wN->Z-axis/rab->Y-Axis
	Math3D.GetIdentityMATRIX(pRot);
	XForm.VRCtoWORLDRotationMATRIX(pRot,&wN,&rab);	
	//////////////////////////////////////// Change Effectively to 2D
	XForm.Transform(&a, b02, pRot);
	XForm.Transform(&b, b12, pRot);
	XForm.Transform(&c, b22, pRot);
	XForm.Transform(&d, pt2, pRot);
	/////////
	return 0;
}

								 
int CIn_Conics::Rat_Subdivide_Conic(WORLD b0,WORLD b1,WORLD b2,WORLD pt,WORLD BCC,
									pWORLD pc1L,pDOUBLE pw1L,pWORLD pc1R,pDOUBLE pw1R)
{

	/////////////////////////////////////////////////////////////
	//			CONIC in STANDARD FORM, i.e., w0=w2=1
	//	/////////////////////////////////////////////////////////
	// Given:
	//		b0,b1,b2	= Bezier  Pts.
	//		w0 & w2 are = 1.0 in standard form
	//		pt			= third pt. on the conic
	//		BCC			= 
	//		t0,t1,t2	= barycentric coords of pt wrt
	//						b0,b1,b2
	//
	// Find:
	//		c0L,c1L,c2L = Left Bezier polygon
	//		w0L,w1L,w2L = Left Bezier polygon
	//		c0R,c1R,c2R = Right Bezier polygon
	//		w0R,w1R,w2R = Right Bezier polygon
	//
	//	NOTE:
	//		1.
	//			c1L_c1R is tangent at pt with
	//			c1L on b0b1
	//			c1R on b1b2
	//		2.
	//			trivial:
	//				c0L = b0; c2R = b2; c2L = c0R = pt
	//				w0L = w2L = w0R = w2R = 1.0 for standard Form
	//			So,
	//				To find only:
	//					c1L( let, = b01) & c1R( let, = b11) &
	//					w1L and w1R
	//					/////////////////////////////////
	//
	// Method:
	//		//////////////////////////////////////////////////////////
	//		to = w0*((1-t)**2)/D
	//		t1 = 2*w1*(t*(1-t))/D
	//		t2 = w2*(t**2)/D
	//	where
	//		c(t) = Numerator/D
	//
	//	so,
	//		(1-t)/t = sqrt(t0/t2);
	//
	//	Now also,
	//		(1-t)/t = cross(b(r,i),q(r,1),b(r+1,1),b(r,i+1) )  for all r,i
	//				= ratio(b0,q0,b1)/ratio(b0,b01,b1)
	//				= (1-t)/t
	//	so,			= sqrt(t0/t2) as above
	//
	//  but, with auxilliary pt:q0,q1 with q0q1 parallel to b0b2	
	//		ratio(b0,q0,b1) = w1
	//  Let,
	//		r0 = ratio(b0,b01,b1) 
	//	then,
	//		w1/r0 = sqrt(t0/t2)  ====>				r0 = w1*sqrt(t2/t0)
	//												===================
	//	Also,
	//		ratio(b1,q1,b2) = 1/w1
	//  Let,
	//		r1 = ratio(b1,b11,b2) 
	//	then,
	//		1/(w1*r0) = sqrt(t0/t2)  ====>			r1 = sqrt(t2/t0)/w1
	//												===================
	/////////////////////////////////////////////////////////////////////////////
	//	Knowing r0,r1, we can locate b01,b11:
	//
	//		c1L = b01 = (b0 + (r0 * b1))/(1 + r0) 
	//		c1R = b11 = (b1 + (r1 * b2))/(1 + r1)
	//	Weights:
	//		w1L = (w0 + (r0 * w1))/(1 + r0)
	//			= (1 + (r0 * w1))/(1 + r0)		// in std. form w0 = 1
	//		w1R = (w1 + (r1 * w2)) /(1+r1)
	//			= (w1 + r1)/(1 + r1)			// in std. form w2 = 1
	/////////////////////////////////////////////////////////////////////////////
	C3DMath Math3D;
	double t0,t1,t2,r0,r1,w1;
	t0 = BCC.x;
	t1 = BCC.y;
	t2 = BCC.z;
	w1 = t1/(2.*sqrt(t0*t2));
	/////////////////////////
	double sqrt20 = sqrt(t2/t0); 
	r0 = w1*sqrt20;
	r1 = sqrt20/w1;
	///////////////////////////
	double rr0 = 1./(1.+r0);
	double rr1 = 1./(1.+r1);
	/////////////////////////////// c1L,w1L
	*pc1L = b1; 
	Math3D.Scale3DPts(r0,pc1L);
	Math3D.Add3DPts(&b0,pc1L,pc1L);
	Math3D.Scale3DPts(rr0,pc1L);
	///
	*pw1L = (1.+r0*w1)*rr0;
	/////////////////////////////// c1R,w1R
	*pc1R = b2; 
	Math3D.Scale3DPts(r1,pc1R);
	Math3D.Add3DPts(&b1,pc1R,pc1R);
	Math3D.Scale3DPts(rr1,pc1R);
	///
	*pw1R = (w1+r1)*rr1;
	///////////////////
	return 0;
}

int CIn_Conics::FindBaryfor3rdPt(WORLD b0,WORLD b1,WORLD b2,WORLD pt,pWORLD pBCC)
{

	/////////////////////////////////////////////////////////////
	//			CONIC in STANDARD FORM, i.e., w0=w2=1
	//	/////////////////////////////////////////////////////////
	// Given:
	//		b0,b1,b2	= Bezier  Pts.
	//		w0 & w2 are = 1.0 in standard form
	//		pt			= third pt. on the conic
	//
	// Find:
	//		t0,t1,t2 =	are barycentric coords of pt wrt
	//					b0,b1,b2
	//					related to w1 (with w0 = w2 = 1) by
	//
	// Method:
	//		1.		to,t1,t2 are obtained by solution of
	//
	//				pBCC-> = t0 =
	//
	//					| cx	b1x		b2x |
	//					| cy	b1y		b2y |	/ delta
	//					| 1		 1		 1	|
	//
	//				pBCC-> = t1 =
	//
	//					| b0x	cx		b2x | 
	//					| b0y	cy		b2y |	/ delta
	//					| 1		 1		 1	|
	//
	//				pBCC-> = t2 =
	//
	//					| b0x	b1x		cx | 
	//					| b0y	b1y		cy |	/ delta
	//					| 1		 1		1  |
	//			with
	//
	//				delta =
	//
	//					| b0x	b1x		b2x | 
	//					| b0y	b1y		b2y |	
	//					| 1		 1		1   |
	//
	//
	//			N O T E:
	//				t0 + t1 + t2 should be 1.0
	//
	///////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// set for the plane of the Conic
	WORLD b02,b12,b22,pt2;
	GetPlanarCoords(b0,b1,b2,pt,&b02,&b12,&b22,&pt2);
	///////////////////////////////////////////////////////////////////////
	double delta,t0,t1,t2,sum;
  	delta	= b02.x*(b12.y-b22.y)+b12.x*(b22.y-b02.y)+b22.x*(b02.y-b12.y);
  	delta	= 1.0/delta;
  	t0		= (pt2.x*(b12.y-b22.y)+b12.x*(b22.y-pt2.y)+b22.x*(pt2.y-b12.y))*delta;
  	t1		= (b02.x*(pt2.y-b22.y)+pt2.x*(b22.y-b02.y)+b22.x*(b02.y-pt2.y))*delta;
  	t2		= (b02.x*(b12.y-pt2.y)+b12.x*(pt2.y-b02.y)+pt2.x*(b02.y-b12.y))*delta;
	//
  	sum		= t0 + t1 + t2;
	////////////////////////////
// 	*pw1	= t1/2* sqrt(t0*t2);
	pBCC->x = t0;
	pBCC->y = t1;
	pBCC->z = t2;
	////////////////////////////
	return 0;
	
}

int CIn_Conics::Compute_w1(WORLD BCC,pDOUBLE pw1)
{

	//	/////////////////////////////////////////////////////////
	// Given:
	//		pBCC		= Barycentric Coords. of 3rd Pt.
	//						wrt bo,b1,b2
	//		w0 & w2 are = 1.0 in standard form
	//
	// Find:
	//		w1			= Weight at b1, the bezier In-beteen point
	// Method:
	//		1.		to find:
	//					//////////////////////
	//					w1 = t1/2* sqrt(t0*t2)
	//					//////////////////////
	//
	//				If	w1<1 --> conic is Ellipse
	//				If	w1=1 --> conic is Parabola
	//				If	w1>1 --> conic is Hyperbola
	//
	//			NOTE:
	//			
	//				General Invariance Condition:
	//
	//					t1**2/(t0*t2) = 4* w1**2/(w0*w2)
	////////////////////////////////////////////////////////////////////////
	double dCheckSum;
	dCheckSum	= BCC.x + BCC.y + BCC.z;
	*pw1	= BCC.y/(2* sqrt(BCC.x*BCC.z)); 
	////////////////////////////
	return 0;
	
}
	 					   	 
void CIn_Conics::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CIn_Conics:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CIn_Conics:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////
