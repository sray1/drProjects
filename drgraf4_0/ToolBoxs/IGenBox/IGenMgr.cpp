// EBoxMgr.cpp : implementation file
//

#include "stdafx.h"
#include "Def_Elem.h" // initialize Element
#include "IGenMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CIGenMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CIGenMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CIGenMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CIGenMgr::CIGenMgr()
{
	////////////////////////////////////////
    m_bIGenBox		= TRUE;    // ElemBox Active
    m_nObjectType	= ELEMENT;
	m_nToolType		= -1;      // Insert Mode

}
// CIGenMgr serialization

void CIGenMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	BYTE b;
	WORD w;
	////////////////////
	if (ar.IsStoring())
	{
		TRACE(" EBoxMgr	:Storing\n");	// TODO: add storing code here
		
    	ar	<</*BOOL*/	(BYTE)m_bIGenBox
			<</*int*/	(WORD)m_nObjectType 
			<</*int*/	(WORD)m_nToolType; 
	      
	}
	else
	{
		TRACE(" EBoxMgr	:Loading\n");	// TODO: add loading code here

    	ar	>>/*BOOL*/	b;
    	m_bIGenBox 		= (BOOL) b;
		ar	>>/*int*/	w;
		m_nObjectType 	= (int) w; 
		ar	>>/*int*/	w;
		m_nToolType 	= (int) w; 
	      

	}
	
}
////////////////////// End of Module ////////////////////


