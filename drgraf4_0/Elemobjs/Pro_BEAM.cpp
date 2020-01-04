// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
///////////////////
#include "Def_Elem.h"

#include "Pro_Beam.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CPro_BEAM, CProperty)
//////////////////// 
CPro_BEAM::CPro_BEAM()
{
	m_PropType = BEAM;
} 
////////////////////////////////// end of module ///////////////////// 

