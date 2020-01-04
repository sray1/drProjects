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
#include "Def_DynL.h"
//////////////////////
#include "DLDEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CDLDEdit,CSpLEdit,1)
/////////////////////////////////////////////////////////////////////////////
CDLDEdit::CDLDEdit()
{

}

CDLDEdit::~CDLDEdit()
{
}

void CDLDEdit::Serialize(CArchive& ar)
{

	CSpLEdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DLDEdit:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" DLDEdit:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


