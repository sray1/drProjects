// Precision.cpp : implementation of the CPrecision class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "Precison.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrecision

IMPLEMENT_SERIAL(CPrecision,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CPrecision,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPrecision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CPrecision::CPrecision()
{
    SetObjectType((int)PRECISION);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CPrecision::ReadDefaultPrecision()
{

////////////////////////////// Set Precision
//    m_nPrecision;
	m_nPrecisionDefault = 2;  // 2 decimal places
    m_lWorldBaseDefault = 100;

}

void CPrecision::InitPrecision()
{

	///////////////////////////////////////
	m_nPrecision     = m_nPrecisionDefault;
	m_nPrecisionOld  = m_nPrecisionDefault;    
	///////////////////////////////////////  Set WorldBase
    m_lWorldBase         =  m_lWorldBaseDefault;
    m_lWorldBaseOld      =  m_lWorldBaseDefault;
    ///////////////////////////////////////////
    
}	

void CPrecision::SetObjectInfo(CDrObject* pObject)
{
	
	CPrecision* pPrecision = (CPrecision*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pPrecision->m_nElemType;
	m_nObjectType		= pPrecision->m_nObjectType; 
	m_nObjectNo			= pPrecision->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nPrecision     	= pPrecision->m_nPrecision;
	m_nPrecisionOld  	= pPrecision->m_nPrecisionOld;    
	m_nPrecisionDefault	= pPrecision->m_nPrecisionDefault;
	///////////////////////////////////////  Set WorldBase
    m_lWorldBase        = pPrecision->m_lWorldBase;
    m_lWorldBaseOld     = pPrecision->m_lWorldBaseOld;
    m_lWorldBase        = pPrecision->m_lWorldBaseDefault;
    /////////////////////////////////////////////////

	return;
}		

void CPrecision::GetObjectInfo(CDrObject* pObject)
{
	
	CPrecision* pPrecision = (CPrecision*) pObject;
	//////////////////////////////////////////////////   
	pPrecision->m_nObjectType 			= m_nObjectType; 
	pPrecision->m_nElemType			= m_nElemType;	
	pPrecision->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pPrecision->m_nPrecision     	= m_nPrecision;
	pPrecision->m_nPrecisionOld  	= m_nPrecisionOld;    
	pPrecision->m_nPrecisionDefault	= m_nPrecisionDefault;
	///////////////////////////////////////  Set WorldBase
    pPrecision->m_lWorldBase        = m_lWorldBase;
    pPrecision->m_lWorldBaseOld     = m_lWorldBaseOld;
    pPrecision->m_lWorldBase        = m_lWorldBaseDefault;
	/////////////////////////////////////////
	return;
}		

void CPrecision::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CPrecision::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == PRECISION) 
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

void CPrecision::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Precision:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<<	(WORD)m_nPrecision                                       	
			<<	(WORD)m_nPrecisionOld    
			<<	(WORD)m_nPrecisionDefault    
			<<	m_lWorldBase    
			<<	m_lWorldBaseOld    
			<<	m_lWorldBaseDefault;    

	}
	else
	{
		TRACE(" Precision:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>	w;
		m_nPrecision    	= (UINT) w;
		ar	>>	w;
		m_nPrecisionOld 	= (UINT) w;
		ar	>>	w;
		m_nPrecisionDefault = (UINT) w;
		ar	<<	m_lWorldBase    
			<<	m_lWorldBaseOld    
			<<	m_lWorldBaseDefault;    

	}        
	///////////////
	
}
////////////////////////////////// end of module /////////////////////
