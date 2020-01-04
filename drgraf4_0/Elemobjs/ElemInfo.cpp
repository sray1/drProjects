// HitNet.cpp : implementation of the CElemInfo class
//

#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "Def_Elem.h"
#include "Def_EInf.h"
#include "Ext_EInf.h"

#include "ElemInfo.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElemInfo

IMPLEMENT_SERIAL(CElemInfo,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CElemInfo,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CElemInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CElemInfo::CElemInfo()
{
    SetObjectType((int)ELEMINFO);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CElemInfo::ReadDefault()
{
}

void CElemInfo::Init()
{
}
	
void CElemInfo::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CElemInfo* pElemInfo = (CElemInfo*) pObject;
	//////////////////////////////////////////////////
	for(int i =0;i<MAX_INFOLIST;i++)
	{
		if(!((pElemInfo->GetInfoList(i))->IsEmpty()) )
		(m_InfoList[i]).AddTail(pElemInfo->GetInfoList(i));
	}
	///////////////////////////////////////////////// 
	return;
}		

void CElemInfo::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CElemInfo* pElemInfo = (CElemInfo*) pObject;
	//////////////////////////////////////////////////
	for(int i =0;i<MAX_INFOLIST;i++)
	{
		if( !GetInfoList(i)->IsEmpty() )
			(pElemInfo->GetInfoList(i))->AddTail(&(m_InfoList[i]));
	}
	///////////////////////////////////////////////// 
	return;
}		

void CElemInfo::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CElemInfo::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_EInfTypes;i++)
   		if(EiTypes[i].num == ELEMINFO) 
   		{
   			name = EiTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   

void CElemInfo::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ElemInfo:    Storing\n");	// TODO: add storing code here
		

	}
	else
	{
		TRACE(" ElemInfo:    Loading\n");	// TODO: add loading code here


	}        
	///////////////
	
}
////////////////////////////////// end of module //////////////////
