// DBoxMgr.cpp : implementation file
//

#include "stdafx.h"
#include "DBoxMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CDBoxMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CDBoxMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDBoxMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CDBoxMgr::CDBoxMgr()
{
	////////////////////////////////////////
    m_bDrawBox		= FALSE;    // DrawBox InActive

}
// CDBoxMgr serialization

void CDBoxMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	BYTE b;
	WORD w;
	DWORD dw;
	////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DBoxMgr	:Storing\n");	// TODO: add storing code here
		
    	ar	<</*BOOL*/		(BYTE)m_bDrawBox
			<</*int*/		(WORD)m_nObjectType 
			<</*int*/		(WORD)m_nToolType  
			<</*COLORREF*/	(DWORD)m_crFore 
			<</*COLORREF*/	(DWORD)m_crBack;

	      
	}
	else
	{
		TRACE(" DBoxMgr	:Loading\n");	// TODO: add loading code here

    	ar	>>/*BOOL*/	b;
    	m_bDrawBox 		= (BOOL) b;
		ar	>>/*int*/	w;
		m_nObjectType 	= (int) w; 
		ar	>>/*int*/	w;
		m_nToolType 	= (int) w;
		ar	>>/*COLORREF*/dw;
		m_crFore		= (COLORREF) dw;
		ar	>>/*COLORREF*/dw;
		m_crBack		= (COLORREF) dw;
	      

	}
	
}
////////////////////// End of Module ////////////////////


