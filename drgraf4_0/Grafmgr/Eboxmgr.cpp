// EBoxMgr.cpp : implementation file
//

#include "stdafx.h"

#include "glb_Mous.h"

#include "Eldefine.h" // initialize PIPE
#include "EBoxMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CEBoxMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CEBoxMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CEBoxMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CEBoxMgr::CEBoxMgr()
{
	////////////////////////////////////////
    m_bElemBox		= TRUE;    // ElemBox Active
    m_nObjectType	= NODE;
	m_nToolType		= INSERT;      // Insert Mode

}

//////////////////////////////////////////////////////////////////
// CEBoxMgr serialization

void CEBoxMgr::Serialize(CArchive& ar)
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
		
    	ar	<</*BOOL*/	(BYTE)m_bElemBox
			<</*int*/	(WORD)m_nObjectType 
			<</*int*/	(WORD)m_nToolType; 
	      
	}
	else
	{
		TRACE(" EBoxMgr	:Loading\n");	// TODO: add loading code here

    	ar	>>/*BOOL*/	b;
    	m_bElemBox 		= (BOOL) b;
		ar	>>/*int*/	w;
		m_nObjectType 	= (int) w; 
		ar	>>/*int*/	w;
		m_nToolType 	= (int) w; 
	      

	}
	
}
////////////////////// End of Module ////////////////////


