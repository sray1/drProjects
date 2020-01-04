// GrafObj.cpp : implementation file
//

#include "stdafx.h"     
#include <Limits.h>	// UINT_MAX   

/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
/////////////////////
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Obj.h"
//#include "dListMgr.h"
//#include "drobject.h"
/////////////////////
#include "DbObjMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CBaseRowHint, CObject)
////////////////////////////////////////////// CDataRowHint class
CBaseRowHint::CBaseRowHint()
{
}
/////////////////////////////////////////////////////////////////////////////
// CGrafObj
IMPLEMENT_SERIAL(CDbObjMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CDbObjMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDbObjMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
CDbObjMgr::CDbObjMgr()
{
	m_CurrentItem	= "";
	m_CurrentParent	= "";
}

CDbObjMgr::~CDbObjMgr()
{
}
/////////////////////////////
void CDbObjMgr::Init()
{
	///////  		
	return;
}
///////////////////////////////////////////////////////// helpers 
UINT CDbObjMgr::GetObjectName_N_ID(CString& strItem)
{
	UINT uValue =  UINT_MAX;
	////////////
	strItem = GetCurrentItem();
	if(strItem == "")
		return uValue;
	//////////////////
	CString strPar = GetCurrentParent();
	if(strPar == "")	// Top Level
	{
		uValue = LookUpID(strItem);
		strItem = "";
	}
	else				// child
		uValue = LookUpID(strPar);
	/////////
	return uValue;
}

UINT CDbObjMgr::LookUpID(CString& strItem)
{
	int i;
	extern OBJTYPES FAR ObjTypes[];
	for(i=0;i<nMax_ObjectTypes;i++)
	{
		if(ObjTypes[i].Name == strItem)
			return ObjTypes[i].ID;
	}
	return (UINT)NULL;
}

LPCTSTR CDbObjMgr::LookUpName(UINT ID)
{
	int i;
	extern OBJTYPES FAR ObjTypes[];
	for(i=0;i<nMax_ObjectTypes;i++)
	{
		if(ObjTypes[i].ID == ID)
			return ObjTypes[i].Name;
	}
	return (LPCTSTR)NULL;
}

int CDbObjMgr::ShowActiveObject_On_Off(CString& strItem,CString& strPar,BOOL bOn)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	int nResult = 0;
	////////////////
	if(strPar == "")	// Top Level, so no item hit
		return nResult;
	////////////////////////////////// child
	UINT GenObj = LookUpID(strPar);;
	CDListMgr* pList = pObjectMgr->GetObjectList(GenObj);
	if(!pList)
		return nResult;
	/////////////////////////
	int nActiveIndex	= pList->GetObjectIndex(GenObj, strItem);
	CDrObject* pObject	= (CDrObject*)pList->GetObject(nActiveIndex);
	//////////////////////////////////////////////////////// HighLight
	pObjectMgr->ShowObject_On_Off(pObject,GenObj,bOn);
	///////////////
	return nResult;
}
/////////////////////////////////////////////////////////////////////////////////////////		
// CDbObjMgr serialization

void CDbObjMgr::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DataBaseMgr		:Storing\n");	// TODO: add storing code here 
	    /////////////////////////////////////////

	}
	else
	{
		TRACE(" DataBaseMgr		:Loading\n");	// TODO: add loading code here
	    /////////////////////////////////////////
		
	} 

}
/////////////////////////// End of Module /////////////////
