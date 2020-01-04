// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
///////////////////
#include "Def_Elem.h"

#include "Pro_Pipe.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CPro_PIPE, CProperty)
//////////////////// 
CPro_PIPE::CPro_PIPE()
{
	m_PropType = PIPE;
} 
////////////////////////////////// end of module ///////////////////// 

