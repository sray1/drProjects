// unit.cpp : implementation of the CUnit class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "unit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnit

IMPLEMENT_SERIAL(CUnit,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CUnit,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CUnit::CUnit()
{
    SetObjectType((int)UNIT);
    SetElemType((int)SPEC_OBJECT);          //  
	////////////////////////////////////////////////  Set Unit
	CString UnitNames[] = {"Inches","Inches - FRACTIONAL","Feet","Feet - FRACTIONAL",
				  "Miles","Millimeters","Centimeters","Meters","Kilometers",""
        		  };
	UINT	nUnitNameCount  = sizeof(UnitNames)/sizeof(UnitNames[0]);
	///////////////////////////////////
	for (UINT i=0;i<nUnitNameCount;i++)
		m_UnitNames[i] = UnitNames[i];
	m_nUnitNameCount = nUnitNameCount;
} 

void CUnit::ReadDefaultUnit()
{

////////////////////////////// Set Unit
//    m_nUnit;
	m_nUnitIndexDefault = 3;  // FEET-FRACTIONAL

}

void CUnit::InitUnit()
{

	////////////////////////////////////////////////  Set Unit
	CString UnitNames[] = {"Inches","Inches - FRACTIONAL","Feet","Feet - FRACTIONAL",
				  "Miles","Millimeters","Centimeters","Meters","Kilometers",""
        		  };
	UINT	nUnitNameCount  = sizeof(UnitNames)/sizeof(UnitNames[0]);
	///////////////////////////////////
	for (UINT i=0;i<nUnitNameCount;i++)
		m_UnitNames[i] = UnitNames[i];
	m_nUnitNameCount = nUnitNameCount;
	///////////////////////////////////////
	m_nUnitIndex     = m_nUnitIndexDefault;
	m_nUnitIndexOld  = m_nUnitIndexDefault;    
    ///////////////////////////////////////
    
}
	
void CUnit::SetObjectInfo(CDrObject* pObject)
{
	
	CUnit* pUnit = (CUnit*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pUnit->m_nElemType;
	m_nObjectType		= pUnit->m_nObjectType; 
	m_nObjectNo			= pUnit->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nUnitIndex     	= pUnit->m_nUnitIndex;
	m_nUnitIndexOld  	= pUnit->m_nUnitIndexOld;    
	m_nUnitIndexDefault	= pUnit->m_nUnitIndexDefault;    
    /////////////////////////////////////////////////

	return;
}		

void CUnit::GetObjectInfo(CDrObject* pObject)
{
	
	CUnit* pUnit = (CUnit*) pObject;
	//////////////////////////////////////////////////   
	pUnit->m_nObjectType 			= m_nObjectType; 
	pUnit->m_nElemType			= m_nElemType;	
	pUnit->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pUnit->m_nUnitIndex     	= m_nUnitIndex;
	pUnit->m_nUnitIndexOld  	= m_nUnitIndexOld;    
	pUnit->m_nUnitIndexDefault	= m_nUnitIndexDefault;    
	/////////////////////////////////////////
	return;
}		

void CUnit::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CUnit::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == UNIT) 
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

void CUnit::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Unit:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<<	(WORD)m_nUnitNameCount;
		for (UINT i=0;i<m_nUnitNameCount;i++)
			ar	<<	m_UnitNames[i];
		///////////////////////////////////////////////////	
		ar	<<	(WORD)m_nUnitIndex                                       	
			<<	(WORD)m_nUnitIndexOld    
			<<	(WORD)m_nUnitIndexDefault;    

	}
	else
	{
		TRACE(" Unit:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>	w;
		m_nUnitNameCount = (UINT) w; 
		for (UINT i=0;i<m_nUnitNameCount;i++)
			ar	>>	m_UnitNames[i];
		///////////////////////////////////////////////////	Unit
		ar	>>	w;
		m_nUnitIndex    = (UINT) w;
		ar	>>	w;
		m_nUnitIndexOld = (UINT) w;
		ar	>>	w;
		m_nUnitIndexDefault = (UINT) w;

	}        
	///////////////
	
}
////////////////////////////////// end of module //////////////////
