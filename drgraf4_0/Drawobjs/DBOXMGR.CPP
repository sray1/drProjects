// DrawBoxMgr.cpp : implementation file
//

#include "stdafx.h"

#include "dboxmgr.h"

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

CDBoxMgr::CDBoxMgr()
{
	/////////////////////////////////////////// DrawBox
	CString DrawNames[]= {"Text Edit","FreeHand","Text Move","Reserved1",
						  "Dimension","Font","Text Insert","Grid On",
						  "Zoom Select","Rectangle","Round Rect.","Ellipse/Circle"
    					 };
	UINT	nDrawNameCount  = sizeof(DrawNames)/sizeof(DrawNames[0]);
      
    for ( int i=0;i<(int)nDrawNameCount;i++) 
    	m_DrawNames[i] = DrawNames[i]; 
    	
	m_nDrawNameCount 	= nDrawNameCount;
	m_bDrawBox 	   		= FALSE;
	//////////////////////////// Label     
	m_CurrentLabelID    = "";
	//////////////////////////// FreeHand     
	m_nFHNumberCurrent	= 0;
	//////////////////////////// Next  
}

// CDBoxMgr serialization

void CDBoxMgr::Serialize(CArchive& ar)
{

    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	BYTE b;
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" DrawBox	:Storing\n");	
		
		ar	<</*CString*/	m_CurrentLabelID
			<</*BOOL*/		(BYTE)m_bDrawBox
			<</*int*/		(WORD)m_nDrawType
			<</*int*/		(WORD)m_nFHNumberCurrent
			<</*int*/		(WORD)m_nFHIndexCurrent;
	}
	else
	{
		TRACE(" DrawBox	:Loading\n");
		
		ar	>>/*CString*/	m_CurrentLabelID
			>>/*BOOL*/		b
			>>/*int*/		w;
		m_bDrawBox			= (BOOL)b;				
		m_nDrawType			= (int)w;
		ar	>>/*int*/		(WORD)w;
		m_nFHNumberCurrent	= (int)w;
		ar	>>/*int*/		(WORD)w;
		m_nFHIndexCurrent	= (int)w;
	}
	///////////////////////////////////// other items
	m_Font.Serialize(ar);
	/////////////////////
	
}

////////////////////// End of Module ////////////////////


