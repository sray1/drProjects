// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// elements
#include "Def_Elem.h"
///////////////////// DynLObjs
#include "Def_SpeL.h"
//////////////////////
#include "SpLCreOp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSpLCreOp,CSLDCreOp,1)
/////////////////////////////////////////////////////////////////////////////
CSpLCreOp::CSpLCreOp()
{

}

CSpLCreOp::~CSpLCreOp()
{
}

void CSpLCreOp::Serialize(CArchive& ar)
{

	CSLDEdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SPLEdit:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SPLEdit:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


