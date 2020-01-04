// CClip.cpp : implementation of the CClip class
//

#include "stdafx.h"

#include "globals.h"
///////////////////
#include "3d.h"
#include "3dclipng.h"
///////////////////
#include "Clip.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CClip

IMPLEMENT_SERIAL(CClip,CObject,1)
/*
BEGIN_MESSAGE_MAP(CClip,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CClip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CClip::CClip()
{
//	ObsoleteSystem(FALSE);
} 

void CClip::SetDrHither(double z)
{

	Fixed fz = X2Fix(&z);
	///////////////////// 
	SetHither(fz);
    /////////////////////
	return;
}	

double CClip::GetDrHither()
{

	///////////////////// 
	Fixed fz = GetHither();
    /////////////////////
	return	(double)Fix2X(fz); 
	
}	

void CClip::SetDrYon(double z)
{

	Fixed fz = X2Fix(&z);
	///////////////////// 
	SetYon(fz);
    /////////////////////
	return;
}	

double CClip::GetDrYon()
{

	///////////////////// 
	Fixed fz = GetYon();
    /////////////////////
	return	(double)Fix2X(fz); 
	
}	

enum visibility CClip::DrClipPt(LPOINT3* pPt, int nPrecision)
{

	pPoint3d pP;
	//////////////////////////////////////////////// 
	double x,y,z,dWorldBase;
	dWorldBase = pow(10.,(double)nPrecision);
	x = ( ((double)pPt->x) /dWorldBase);         // divide by 10**nPrecision
	y = ( ((double)pPt->y) /dWorldBase);         // divide by 10**nPrecision
	z = ( ((double)pPt->z) /dWorldBase);         // divide by 10**nPrecision 
	///////////////// 
	pP->x = X2Fix(&x);
	pP->y = X2Fix(&y);
	pP->z = X2Fix(&z);
	pP->transformed = FALSE;
	////////////////////////
	return ClipPt(pP);
    /////////////////////

}	

enum visibility CClip::DrClipLine(LPOINT3* pStart, LPOINT3* pEnd, int nPrecision)
{

	pPoint3d pS,pE;
	//////////////////////////////////////////////// 
	double x,y,z,dWorldBase;
	dWorldBase = pow(10.,(double)nPrecision);
	x = ( ((double)pStart->x) /dWorldBase);         // divide by 10**nPrecision
	y = ( ((double)pStart->y) /dWorldBase);         // divide by 10**nPrecision
	z = ( ((double)pStart->z) /dWorldBase);         // divide by 10**nPrecision 
	///////////////// 
	pS->x = X2Fix(&x);
	pS->y = X2Fix(&y);
	pS->z = X2Fix(&z);
	pS->transformed = FALSE;
	//////////////////////////////////////////////// 
	x = ( ((double)pEnd->x) /dWorldBase);         // divide by 10**nPrecision
	y = ( ((double)pEnd->y) /dWorldBase);         // divide by 10**nPrecision
	z = ( ((double)pEnd->z) /dWorldBase);         // divide by 10**nPrecision 
	///////////////// 
	pE->x = X2Fix(&x);
	pE->y = X2Fix(&y);
	pE->z = X2Fix(&z);
	pE->transformed = FALSE;
	////////////////////////
	return ClipLine(pS,pE);
    /////////////////////

}	

void CClip::DrSetCanonicalClipOn(BOOL bState)
{

	SetCanonicalClipping(bState);
	
}	
////////////////////////////////// end of module //////////////////
