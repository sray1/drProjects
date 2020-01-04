// Pipe.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
//////////////
#include "DrEdge.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDrEdge
IMPLEMENT_SERIAL(CDrEdge, CObject,1)
/*
BEGIN_MESSAGE_MAP(CDrEdge, CObject)
	//{{AFX_MSG_MAP(CDrEdge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrEdge::CDrEdge()
{  
} 

CDrEdge::~CDrEdge()
{
}	
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void CDrEdge::Serialize(CArchive& ar)
{
}

////////////////////// END OF MODULE ///////////////////////

