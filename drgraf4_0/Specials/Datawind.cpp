// DataWindow.cpp : implementation of the CDataWindow class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "datawind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataWindow

IMPLEMENT_SERIAL(CDataWindow,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDataWindow,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDataWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CDataWindow::CDataWindow()
{
    SetObjectType((int)DATAWINDOW);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CDataWindow::ReadDefaultDataWindow()
{

	///////////////////////////////////////////////////// DataWindow
	m_WinOrgWICDefault.x = 0;
	m_WinOrgWICDefault.y = 0;
	m_WinOrgWICDefault.z = 0;
	m_WinMinWICDefault.x = 0;
	m_WinMinWICDefault.y = 0;
	m_WinMinWICDefault.z = 0;
	
	m_WinMaxWICDefault.x = 0;
	m_WinMaxWICDefault.y = 0;
	m_WinMaxWICDefault.z = 0;

	m_WinExtWICDefault.x = 1;
	m_WinExtWICDefault.y = 1;
	m_WinExtWICDefault.z = 1;

}

void CDataWindow::InitDataWindow()
{

	///////////////////////////////////////
	m_WinOrgWIC.x 	= m_WinOrgWICDefault.x;
	m_WinOrgWIC.y 	= m_WinOrgWICDefault.y;
	m_WinOrgWIC.z 	= m_WinOrgWICDefault.z;

	m_WinMinWIC.x 	= m_WinMinWICDefault.x;
	m_WinMinWIC.y 	= m_WinMinWICDefault.y;
	m_WinMinWIC.z 	= m_WinMinWICDefault.z;

	m_WinMaxWIC.x 	= m_WinMaxWICDefault.x;
	m_WinMaxWIC.y 	= m_WinMaxWICDefault.y;
	m_WinMaxWIC.z 	= m_WinMaxWICDefault.z;

	m_WinExtWIC.x   = m_WinExtWICDefault.x;
	m_WinExtWIC.y   = m_WinExtWICDefault.y;
	m_WinExtWIC.z   = m_WinExtWICDefault.z;

	m_WinMinWICOld.x 	= m_WinMinWIC.x;
	m_WinMinWICOld.y 	= m_WinMinWIC.y;
	m_WinMinWICOld.z 	= m_WinMinWIC.z;

	m_WinMaxWICOld.x 	= m_WinMaxWIC.x;
	m_WinMaxWICOld.y 	= m_WinMaxWIC.y;
	m_WinMaxWICOld.z 	= m_WinMaxWIC.z;

	m_WinExtWICOld.x   = m_WinExtWIC.x;
	m_WinExtWICOld.y   = m_WinExtWIC.y;
	m_WinExtWICOld.z   = m_WinExtWIC.z;
    ///////////////////////////////////////
    
}
	
void CDataWindow::SetObjectInfo(CDrObject* pObject)
{
	
	CDataWindow* pDataWindow = (CDataWindow*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pDataWindow->m_nElemType;
	m_nObjectType		= pDataWindow->m_nObjectType; 
	m_nObjectNo			= pDataWindow->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_WinOrgWIC.x 			= pDataWindow->m_WinOrgWIC.x;
	m_WinOrgWIC.y 			= pDataWindow->m_WinOrgWIC.y;
	m_WinOrgWIC.z 			= pDataWindow->m_WinOrgWIC.z;
	m_WinOrgWICOld.x 		= pDataWindow->m_WinOrgWICOld.x;
	m_WinOrgWICOld.y 		= pDataWindow->m_WinOrgWICOld.y;
	m_WinOrgWICOld.z 		= pDataWindow->m_WinOrgWICOld.z;
	m_WinOrgWICDefault.x 	= pDataWindow->m_WinOrgWICDefault.x;
	m_WinOrgWICDefault.y 	= pDataWindow->m_WinOrgWICDefault.y;
	m_WinOrgWICDefault.z 	= pDataWindow->m_WinOrgWICDefault.z;

	m_WinMinWIC.x 			= pDataWindow->m_WinMinWIC.x;
	m_WinMinWIC.y 			= pDataWindow->m_WinMinWIC.y;
	m_WinMinWIC.z 			= pDataWindow->m_WinMinWIC.z;
	m_WinMinWICOld.x 		= pDataWindow->m_WinMinWICOld.x;
	m_WinMinWICOld.y 		= pDataWindow->m_WinMinWICOld.y;
	m_WinMinWICOld.z 		= pDataWindow->m_WinMinWICOld.z;
	m_WinMinWICDefault.x 	= pDataWindow->m_WinMinWICDefault.x;
	m_WinMinWICDefault.y 	= pDataWindow->m_WinMinWICDefault.y;
	m_WinMinWICDefault.z 	= pDataWindow->m_WinMinWICDefault.z;
                                 
	m_WinMaxWIC.x 			= pDataWindow->m_WinMaxWIC.x;
	m_WinMaxWIC.y 			= pDataWindow->m_WinMaxWIC.y;
	m_WinMaxWIC.z 			= pDataWindow->m_WinMaxWIC.z;
	m_WinMaxWICOld.x 		= pDataWindow->m_WinMaxWICOld.x;
	m_WinMaxWICOld.y 		= pDataWindow->m_WinMaxWICOld.y;
	m_WinMaxWICOld.z 		= pDataWindow->m_WinMaxWICOld.z;
	m_WinMaxWICDefault.x 	= pDataWindow->m_WinMaxWICDefault.x;
	m_WinMaxWICDefault.y 	= pDataWindow->m_WinMaxWICDefault.y;
	m_WinMaxWICDefault.z 	= pDataWindow->m_WinMaxWICDefault.z;

	m_WinExtWIC.x   		= pDataWindow->m_WinExtWIC.x;
	m_WinExtWIC.y   		= pDataWindow->m_WinExtWIC.y;
	m_WinExtWIC.z   		= pDataWindow->m_WinExtWIC.z;
	m_WinExtWICOld.x   		= pDataWindow->m_WinExtWICOld.x;
	m_WinExtWICOld.y   		= pDataWindow->m_WinExtWICOld.y;
	m_WinExtWICOld.z   		= pDataWindow->m_WinExtWICOld.z;
	m_WinExtWICDefault.x   	= pDataWindow->m_WinExtWICDefault.x;
	m_WinExtWICDefault.y   	= pDataWindow->m_WinExtWICDefault.y;
	m_WinExtWICDefault.z   	= pDataWindow->m_WinExtWICDefault.z;
    /////////////////////////////////////////////////
	return;
}		

void CDataWindow::GetObjectInfo(CDrObject* pObject)
{
	
	CDataWindow* pDataWindow = (CDataWindow*) pObject;
	//////////////////////////////////////////////////   
	pDataWindow->m_nObjectType 		= m_nObjectType; 
	pDataWindow->m_nElemType		= m_nElemType;	
	pDataWindow->m_nObjectNo		= m_nObjectNo;
	///////////////////////////////////////////////// 
	pDataWindow->m_WinOrgWIC.x 			= m_WinOrgWIC.x;
	pDataWindow->m_WinOrgWIC.y 			= m_WinOrgWIC.y;
	pDataWindow->m_WinOrgWIC.z 			= m_WinOrgWIC.z;
	pDataWindow->m_WinOrgWICOld.x 		= m_WinOrgWICOld.x;
	pDataWindow->m_WinOrgWICOld.y 		= m_WinOrgWICOld.y;
	pDataWindow->m_WinOrgWICOld.z 		= m_WinOrgWICOld.z;
	pDataWindow->m_WinOrgWICDefault.x 	= m_WinOrgWICDefault.x;
	pDataWindow->m_WinOrgWICDefault.y 	= m_WinOrgWICDefault.y;
	pDataWindow->m_WinOrgWICDefault.z   = m_WinOrgWICDefault.z;

	pDataWindow->m_WinMinWIC.x 			= m_WinMinWIC.x;
	pDataWindow->m_WinMinWIC.y 			= m_WinMinWIC.y;
	pDataWindow->m_WinMinWIC.z 			= m_WinMinWIC.z;
	pDataWindow->m_WinMinWICOld.x 		= m_WinMinWICOld.x;
	pDataWindow->m_WinMinWICOld.y 		= m_WinMinWICOld.y;
	pDataWindow->m_WinMinWICOld.z 		= m_WinMinWICOld.z;
	pDataWindow->m_WinMinWICDefault.x 	= m_WinMinWICDefault.x;
	pDataWindow->m_WinMinWICDefault.y 	= m_WinMinWICDefault.y;
	pDataWindow->m_WinMinWICDefault.z 	= m_WinMinWICDefault.z;
                                 
	pDataWindow->m_WinMaxWIC.x 			= m_WinMaxWIC.x;
	pDataWindow->m_WinMaxWIC.y 			= m_WinMaxWIC.y;
	pDataWindow->m_WinMaxWIC.z 			= m_WinMaxWIC.z;
	pDataWindow->m_WinMaxWICOld.x 		= m_WinMaxWICOld.x;
	pDataWindow->m_WinMaxWICOld.y 		= m_WinMaxWICOld.y;
	pDataWindow->m_WinMaxWICOld.z 		= m_WinMaxWICOld.z;
	pDataWindow->m_WinMaxWICDefault.x 	= m_WinMaxWICDefault.x;
	pDataWindow->m_WinMaxWICDefault.y 	= m_WinMaxWICDefault.y;
	pDataWindow->m_WinMaxWICDefault.z 	= m_WinMaxWICDefault.z;

	pDataWindow->m_WinExtWIC.x   		= m_WinExtWIC.x;
	pDataWindow->m_WinExtWIC.y   		= m_WinExtWIC.y;
	pDataWindow->m_WinExtWIC.z   		= m_WinExtWIC.z;
	pDataWindow->m_WinExtWIC.x   		= m_WinExtWICOld.x;
	pDataWindow->m_WinExtWIC.y   		= m_WinExtWICOld.y;
	pDataWindow->m_WinExtWIC.z   		= m_WinExtWICOld.z;
	pDataWindow->m_WinExtWICDefault.x   = m_WinExtWICDefault.x;
	pDataWindow->m_WinExtWICDefault.y   = m_WinExtWICDefault.y;
	pDataWindow->m_WinExtWICDefault.z   = m_WinExtWICDefault.z;
	///////////////////////////////////////////////////////////
	return;
}		

void CDataWindow::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDataWindow::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == DATAWINDOW) 
   		{
   			name = SpTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   
	 
	

void CDataWindow::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	///////////////////
	if (ar.IsStoring())
	{
		TRACE(" DataWindow:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar.Write(&m_WinOrgWIC, sizeof(LPOINT3) );					 				
		ar.Write(&m_WinMinWIC, sizeof(LPOINT3) );					 				
		ar.Write(&m_WinMaxWIC, sizeof(LPOINT3) );					 				
		ar.Write(&m_WinExtWIC, sizeof(LPOINT3) );					 				

		ar.Write(&m_WinOrgWICOld, sizeof(LPOINT3) );								
		ar.Write(&m_WinMinWICOld, sizeof(LPOINT3) );								
		ar.Write(&m_WinMaxWICOld, sizeof(LPOINT3) );								
		ar.Write(&m_WinExtWICOld, sizeof(LPOINT3) );								

		ar.Write(&m_WinOrgWICDefault, sizeof(LPOINT3) );							
		ar.Write(&m_WinMinWICDefault, sizeof(LPOINT3) );							
		ar.Write(&m_WinMaxWICDefault, sizeof(LPOINT3) );							
		ar.Write(&m_WinExtWICDefault, sizeof(LPOINT3) );
		///////////////////////////////////////////////////							

	}
	else
	{
		TRACE(" DataWindow:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar.Read(&m_WinOrgWIC, sizeof(LPOINT3) );					 				
		ar.Read(&m_WinMinWIC, sizeof(LPOINT3) );					 				
		ar.Read(&m_WinMaxWIC, sizeof(LPOINT3) );					 				
		ar.Read(&m_WinExtWIC, sizeof(LPOINT3) );					 				

		ar.Read(&m_WinOrgWICOld, sizeof(LPOINT3) );								
		ar.Read(&m_WinMinWICOld, sizeof(LPOINT3) );								
		ar.Read(&m_WinMaxWICOld, sizeof(LPOINT3) );								
		ar.Read(&m_WinExtWICOld, sizeof(LPOINT3) );								

		ar.Read(&m_WinOrgWICDefault, sizeof(LPOINT3) );							
		ar.Read(&m_WinMinWICDefault, sizeof(LPOINT3) );							
		ar.Read(&m_WinMaxWICDefault, sizeof(LPOINT3) );							
		ar.Read(&m_WinExtWICDefault, sizeof(LPOINT3) );
		///////////////////////////////////////////////////							

	}        
	///////////////
	
}

void CDataWindow::SetWinMinMaxWIC(LPOINT3 NewWIC)
{ 
	m_WinMinWICOld.x = m_WinMinWIC.x;
	m_WinMinWICOld.y = m_WinMinWIC.y;
	m_WinMinWICOld.z = m_WinMinWIC.z;

	if(m_WinMinWIC.x>NewWIC.x) m_WinMinWIC.x = NewWIC.x;
	if(m_WinMinWIC.y>NewWIC.y) m_WinMinWIC.y = NewWIC.y;
	if(m_WinMinWIC.z>NewWIC.z) m_WinMinWIC.z = NewWIC.z;

	m_WinMaxWICOld.x = m_WinMaxWIC.x;
	m_WinMaxWICOld.y = m_WinMaxWIC.y;
	m_WinMaxWICOld.z = m_WinMaxWIC.z;

	if(m_WinMaxWIC.x<NewWIC.x) m_WinMaxWIC.x = NewWIC.x;
	if(m_WinMaxWIC.y<NewWIC.y) m_WinMaxWIC.y = NewWIC.y;
	if(m_WinMaxWIC.z<NewWIC.z) m_WinMaxWIC.z = NewWIC.z;
	 
}
	
void CDataWindow::SetWinExtWIC()
{
	
	m_WinExtWIC.x = labs(m_WinMaxWIC.x - m_WinMinWIC.x);
	m_WinExtWIC.y = labs(m_WinMaxWIC.y - m_WinMinWIC.y);
	m_WinExtWIC.z = labs(m_WinMaxWIC.z - m_WinMinWIC.z); 

}
////////////////////////////////// end of module //////////////////
