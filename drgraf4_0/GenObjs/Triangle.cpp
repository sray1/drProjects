// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
///////////////////
#include "Triangle.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CTriangle, CObject)
//////////////////// 
CTriangle::CTriangle()
{
	m_bSubDivided = FALSE;			// Subdivided?
} 
int CTriangle::GetLinearIndex(int i, int j, int k, int nDeg)
{
	int Lindex;
	///////////
	return Lindex;
}

void CTriangle::GetIJK(pINT i, pINT j, pINT k, int LIndex, int nDeg)
{
	int nDiv,nLIndex = LIndex;
	//////////////////////////
	*i = 0;
	*j = 0;
	////////
	int nPtOnEachSide = nDeg + 1; // order
	for(;;)
	{
		nDiv = nLIndex/nPtOnEachSide;
		if(0 == nDiv)
		{
			*j = LIndex%nPtOnEachSide;
			break;
		}
		//////////////////////////// reset
		(*i)++;
		nLIndex -= nPtOnEachSide;
	}
	*k = nDeg - (*i) - (*j);
	//////
	return;
}
////////////////////////////////// end of module ///////////////////// 

