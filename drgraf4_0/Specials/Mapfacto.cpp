// MapFactor.cpp : implementation of the CMapFactor class
//
#include "stdafx.h" 

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"
//////////////////////
#include "MapFacto.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapFactor

IMPLEMENT_SERIAL(CMapFactor,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CMapFactor,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMapFactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CMapFactor::CMapFactor()
{
    SetObjectType((int)MAPFACTOR);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CMapFactor::ReadDefaultMapFactor()
{

    m_nMapIndexDefault  = MM_LOENGLISH;
	m_dMapFactorDefault = .01;  // LO_ENGLISH

}

void CMapFactor::InitMapFactor()
{

	///////////////////////////////////////////
	m_nMapIndex		  = m_nMapIndexDefault;
	m_nMapIndexOld    = m_nMapIndex;
	m_dMapFactor	  = m_dMapFactorDefault;
	m_dMapFactorOld   = m_dMapFactor;
    
}
	
void CMapFactor::SetObjectInfo(CDrObject* pObject)
{
	
	CMapFactor* pMapFactor = (CMapFactor*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pMapFactor->m_nElemType;
	m_nObjectType		= pMapFactor->m_nObjectType; 
	m_nObjectNo			= pMapFactor->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nMapIndex		  	= pMapFactor->m_nMapIndex;
	m_nMapIndexOld    	= pMapFactor->m_nMapIndexOld;
	m_nMapIndexDefault 	= pMapFactor->m_nMapIndexDefault;
	m_dMapFactor	 	= pMapFactor->m_dMapFactor;
	m_dMapFactorOld   	= pMapFactor->m_dMapFactorOld;
	m_dMapFactor	 	= pMapFactor->m_dMapFactorDefault;
    /////////////////////////////////////////////////

	return;
}		

void CMapFactor::GetObjectInfo(CDrObject* pObject)
{
	
	CMapFactor* pMapFactor = (CMapFactor*) pObject;
	//////////////////////////////////////////////////   
	pMapFactor->m_nObjectType 		= m_nObjectType; 
	pMapFactor->m_nElemType			= m_nElemType;	
	pMapFactor->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pMapFactor->m_nMapIndex		  	= m_nMapIndex;
	pMapFactor->m_nMapIndexOld    	= m_nMapIndexOld;
	pMapFactor->m_nMapIndexDefault 	= m_nMapIndexDefault;
	pMapFactor->m_dMapFactor	  	= m_dMapFactor;
	pMapFactor->m_dMapFactorOld  	= m_dMapFactorOld;
	pMapFactor->m_dMapFactorDefault	= m_dMapFactorDefault;
	/////////////////////////////////////////
	return;
}		

void CMapFactor::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CMapFactor::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == MAPFACTOR) 
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

void CMapFactor::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" MapFactor:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<<	(WORD)m_nMapIndex
			<<	(WORD)m_nMapIndexOld
			<<	(WORD)m_nMapIndexDefault
			<<	m_dMapFactor
			<<	m_dMapFactorOld            					// end chain 
			<<	m_dMapFactorDefault;

	}
	else
	{
		TRACE(" MapFactor:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>	w;
		m_nMapIndex = (UINT) w;
		ar	>>	w;
		m_nMapIndexOld = (UINT) w;
		ar	>>	w;
		m_nMapIndexDefault = (UINT) w;
		ar	>>	m_dMapFactor
			>>	m_dMapFactorOld            					
			>>	m_dMapFactorDefault;            					

	}        
	///////////////
	
} 
////////////////////////////////// end of module //////////////////
