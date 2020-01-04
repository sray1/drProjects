// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"

#include "resource.h"
#include "aboutbox.h"
#include "drgraf.h"

#include "node.h"
#include "drgradoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
void CDrGrafDoc::SetMouseWIC(POINT3 MouseWIC)	
{
    m_MouseWIC.x = MouseWIC.x;
    m_MouseWIC.y = MouseWIC.y;
    m_MouseWIC.z = MouseWIC.z;
}    				
