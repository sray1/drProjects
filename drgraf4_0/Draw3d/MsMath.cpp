// XForm.cpp : implementation of the CMsMath class
//
//Spec_d32.Lib Elem_D32.lib OMgr_D32.lib 
#include "stdafx.h"
/////////////////////
//#include "Def_MLims.h"
//#include "drgraf.h"
//#include "drgradoc.h"
//#include "ObjMgr.h"
///////////////////// SpecObjs
//#include "HitNet.h"
/////////////////////
#include "Def_Type.h"
///////////////////
#include "MsMath.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMsMath

IMPLEMENT_SERIAL(CMsMath,C3DMath,1)
/*
BEGIN_MESSAGE_MAP(CMsMath,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMsMath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CMsMath::CMsMath()
{
//	ObsoleteSystem(FALSE);
}
 
/////////////////////////////////////////////////////////////
//int CMsMath::IsCoLinear(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2)
int CMsMath::IsCoLinear(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2,double dCoLin)
{
//	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
//	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
//	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	WORLD	a,b;
	double	d,La,Lb;
	/////////////////////////////////////
	Sub3DPts(pwx0,pwx1,&a); 	// 01
	Sub3DPts(pwx0,pwx2,&b); 	// 02
	La = Len3DPts(&a);
	Lb = Len3DPts(&b);
	if(La == 0.0 || Lb == 0.0)
		return 1;	// TRUE
	//////////////////////////
	d = Dot3DPts(&a,&b);
	//////
//	if(fabs(d) > (pHitNet->GetCoLinear()) * La * Lb)
	if(fabs(d) > dCoLin * La * Lb)
		return 1;	// TRUE
	else
		return 0;	// FALSE
}

int CMsMath::IsCoPlanar(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2,pWORLD pwx3,
						  pWORLD pNormal_ABC,pDOUBLE pD,double dCoLin)
{
	//////////////////	ALSO COMPUTES PLANE EQUATION	////////////////
	//////////////////				A,B,C,D				////////////////
	////////////////////////////////////////////////////////////////////
//	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
//	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
//	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD	a,b,v0;
	pWORLD	pvx0,pvx1,pvx2,pvx3;
	double	d;
	/////////////////////////////
	pvx0 = pwx0;
	pvx1 = pwx1;
	pvx2 = pwx2;
	pvx3 = pwx3;
	///////////////////////////////
	if(IsCoLinear(pvx0,pvx1,pvx2,dCoLin) )
	{
		pvx2 = pwx3;		// switch
		pvx3 = pwx2;
	}
	if(IsCoLinear(pvx0,pvx1,pvx2,dCoLin) )
		return -1;												//error
	///////////////////////////////
	Sub3DPts(pwx0,pwx1,&a);
	Sub3DPts(pwx2,pwx1,&b);
	Cross3DPts(&a,&b,&v0);	// Normal
	///////
	d = sqrt(v0.x*v0.x + v0.y*v0.y + v0.z*v0.z); //length  
	d = 1./d;
	////////////////////////////////// Unit Normal
	pNormal_ABC->x = v0.x * d;
	pNormal_ABC->y = v0.y * d;
	pNormal_ABC->z = v0.z * d;
	////////////////////////////////// D
	*pD	=		pNormal_ABC->x * pvx0->x; 
			+	pNormal_ABC->y * pvx0->y; 
			+	pNormal_ABC->z * pvx0->z;
	*pD = -(*pD);		  		
	///////////////////////////////////// Distance of 4th point
	d	=		pNormal_ABC->x * pvx3->x; 
			+	pNormal_ABC->y * pvx3->y; 
			+	pNormal_ABC->z * pvx3->z;
			+	*pD;
	/////////////////
//	if( fabs(d)< pHitNet->GetCoLinear() )			// within ??% of co-planar 
	if( fabs(d)< dCoLin )			// within ??% of co-planar 
		return 1;	// TRUE
	else
		return 0;	// FALSE
}


BOOL CMsMath::IsIntersect_LINE_LINE(pWORLD LocalPos,WORLD& LocalPos_In)
{
	////////////////////////////////////////////////////////////////////////
	//	intersect =	(LP_1 - LP_0)/[(LP_2 - LP_0) - (LP_3 - LP_1)], x,y,z 
	////////////////////////////////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	WORLD	wx0,wx1,wx2,wx3,d1,d2,e;
	double	t = -1.0,t1,deno;
    ///////////////////
	wx0 	= LocalPos[0];
	wx1 	= LocalPos[1];
	wx2 	= LocalPos[2];
	wx3 	= LocalPos[3];
	///////////////////////////////////////////////////////// get parameter
	Sub3DPts(&wx2,&wx0,&d1); 	// diagonal02 
	Sub3DPts(&wx3,&wx1,&d2); 	// diagonal13
	Sub3DPts(&wx1,&wx0,&e); 		// auxiliary
	//////
	deno = d1.x*d2.y - d2.x*d1.y; //denominator
	if(deno	!= 0.0)
		t = (e.x*d1.y - d1.x*e.y)/deno; // parameter
	else
	{
		deno = d1.x*d2.z - d2.x*d1.z; //denominator
		if(deno	!= 0.0)
			t = (e.x*d1.z - d1.x*e.z)/deno; // parameter
		else
		{
			deno = d1.y*d2.z - d2.y*d1.z; //denominator
			if(deno	!= 0.0)
				t = (e.y*d1.z - d1.y*e.z)/deno; // parameter
		}
	}
	///////////////////////////////////////////////////////// t  ( No Intersection )
	if(t < 0.0 || t > 1.0)
	{
		AfxMessageBox("ERROR:\nCMI_Gang2::IsIntersect_LINE_LINE\nt < 0.0 || t > 1.0");
		return FALSE;
	}
	///////////////////////////////////////////////////////// get Coords
	t1 = 1.0 - t;
	LocalPos_In.x = LocalPos[1].x * t1 + LocalPos[3].x * t;
	LocalPos_In.y = LocalPos[1].y * t1 + LocalPos[3].y * t;
	LocalPos_In.z = LocalPos[1].z * t1 + LocalPos[3].z * t;
	/////////
	return TRUE;
	///
}

void CMsMath::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" CMsMath:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" CMsMath:    Loading\n");	// TODO: add loading code here
	}
		
}
////////////////////////////////// end of module //////////////////
