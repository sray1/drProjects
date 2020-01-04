#include "stdafx.h"

#include "mouseloc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CMouseLoc
IMPLEMENT_SERIAL(CMouseLoc,CObject,1)
CMouseLoc::CMouseLoc()
{
}
/////////////////////////////////////////////////////////////// INITIALIZE 
void CMouseLoc::Initialize()
{ 
	/////////////////////////////////////////// Mouse 
	m_MouseWIC     = m_MouseDefaultWIC;
	m_MouseOldWIC  = m_MouseWIC;
}
void CMouseLoc::ReadDefaults()
{
//////////////////////////////////////////////////TEMPORARILY being Set HERE
//                                                Later Read in from DOC FILE
	/////////////////////////////////////////// Mouse 
	m_MouseDefaultWIC.x = 0;
	m_MouseDefaultWIC.y = 0;
	m_MouseDefaultWIC.z = 0;

}

void CMouseLoc::SetMouseWIC(LPOINT3 NewMouseWIC)	
{
    m_MouseWIC.x = NewMouseWIC.x;
    m_MouseWIC.y = NewMouseWIC.y;
    m_MouseWIC.z = NewMouseWIC.z;
}    				
void CMouseLoc::SetMouseOldWIC(LPOINT3 NewMouseOldWIC)	
{
    m_MouseOldWIC.x = NewMouseOldWIC.x;
    m_MouseOldWIC.y = NewMouseOldWIC.y;
    m_MouseOldWIC.z = NewMouseOldWIC.z;
}    				

void CMouseLoc::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MouseLoc:    Storing\n");	
		
			/////////////////////////////////////////////////
    		ar.Write(/*LPOINT*/	&m_LptScrolled,sizeof(LPOINT));
			ar	<</*POINT*/		m_MouseVUC
				<</*POINT*/		m_MouseOldVUC
				<</*POINT*/		m_AnchorVUC;
			ar.Write(/*LPOINT3*/&m_MouseWIC,sizeof(LPOINT3));
			ar.Write(/*LPOINT3*/&m_MouseOldWIC,sizeof(LPOINT3));
			ar.Write(/*LPOINT3*/&m_MouseDefaultWIC,sizeof(LPOINT3));
			ar.Write(/*LPOINT3*/&m_AnchorWIC,sizeof(LPOINT3));
 			//////////////////////////////

	}
	else
	{
		TRACE(" MouseLoc:    Loading\n");	

			/////////////////////////////////////////////////
    		ar.Read(/*LPOINT*/	&m_LptScrolled,sizeof(LPOINT));
			ar	>>/*POINT*/		m_MouseVUC
				>>/*POINT*/		m_MouseOldVUC
				>>/*POINT*/		m_AnchorVUC;
			ar.Read(/*LPOINT3*/	&m_MouseWIC,sizeof(LPOINT3));
			ar.Read(/*LPOINT3*/	&m_MouseOldWIC,sizeof(LPOINT3));
			ar.Read(/*LPOINT3*/	&m_MouseDefaultWIC,sizeof(LPOINT3));
			ar.Read(/*LPOINT3*/	&m_AnchorWIC,sizeof(LPOINT3));
 			//////////////////////////////
	}        
}

