// ScaleFactor.cpp : implementation of the CScaleFactor class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "Scalefac.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleFactor

IMPLEMENT_SERIAL(CScaleFactor,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CScaleFactor,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CScaleFactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CScaleFactor::CScaleFactor()
{
    SetObjectType((int)SCALEFACTOR);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CScaleFactor::ReadDefaultScaleFactor()
{

	////////////////////////////// Set ScaleFactor
	m_dScaleFactorDefault = 1.0;

}

void CScaleFactor::InitScaleFactor()
{

	////////////////////////////// Set Scale Factor		
	m_dScaleFactor    = m_dScaleFactorDefault;
	m_dScaleFactorOld = m_dScaleFactorDefault;
	  	
}

void CScaleFactor::SetObjectInfo(CDrObject* pObject)
{
	
	CScaleFactor* pScaleFactor = (CScaleFactor*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pScaleFactor->m_nElemType;
	m_nObjectType		= pScaleFactor->m_nObjectType; 
	m_nObjectNo			= pScaleFactor->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_dScaleFactor    		= pScaleFactor->m_dScaleFactor;
	m_dScaleFactorOld 		= pScaleFactor->m_dScaleFactorOld;
	m_dScaleFactorDefault   = pScaleFactor->m_dScaleFactorDefault;
    /////////////////////////////////////////////////

	return;
}		

void CScaleFactor::GetObjectInfo(CDrObject* pObject)
{
	
	CScaleFactor* pScaleFactor = (CScaleFactor*) pObject;
	//////////////////////////////////////////////////   
	pScaleFactor->m_nObjectType 		= m_nObjectType; 
	pScaleFactor->m_nElemType			= m_nElemType;	
	pScaleFactor->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pScaleFactor->m_dScaleFactor    	= m_dScaleFactor;
	pScaleFactor->m_dScaleFactorOld 	= m_dScaleFactorOld;
	pScaleFactor->m_dScaleFactorDefault = m_dScaleFactorDefault;
	/////////////////////////////////////////
	return;
}		

void CScaleFactor::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CScaleFactor::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == SCALEFACTOR) 
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

void CScaleFactor::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ScaleFactor:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<<	m_dScaleFactor                                       	
			<<	m_dScaleFactorOld    
			<<	m_dScaleFactorDefault;    

	}
	else
	{
		TRACE(" ScaleFactor:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>	m_dScaleFactor
			>>	m_dScaleFactorOld
			>>	m_dScaleFactorDefault;

	}        
	///////////////
	
}

////////////////////////////////// end of module /////////////////////
