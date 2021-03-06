// Element dataBase.cpp : implementation of the CPListMgr class
//

#include "stdafx.h"

#include "drobject.h"
/////////////////////////////
#include "PListMgr.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/*
BEGIN_MESSAGE_MAP(CPListMgr, CObject)
	//{{AFX_MSG_MAP(CPListMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

IMPLEMENT_DYNCREATE(CPListMgr,CObject)

CPListMgr::CPListMgr()
{
}

CPListMgr::~CPListMgr()
{
}

///////////////////////////////////////////////////////////////////////

void CPListMgr::AssertValid() const
{
	CObject::AssertValid();
}

void CPListMgr::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

POSITION CPListMgr::GetFirstObjectPos()
{

	return GetHeadPosition();

}	

CDrObject* CPListMgr::GetNextObject(POSITION& pos)
{ 

	return (CDrObject*)GetNext(pos);

} 

int CPListMgr::InsertObject(CDrObject* pInsertObject)
{

	//////////////////////
	AddTail(pInsertObject);
	///////////////////////
	return 0;
		
}		

int	CPListMgr::ReplaceObject(int index,CDrObject* pReplaceObject)
{                                                   

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;
    ////////////////////////////////////
	POSITION posRemove,posAfter;
	CDrObject* pTemp;
	/////////////////
	if(!(posRemove = (posAfter = FindIndex(index) )) )
		return -1;
	else	
		pTemp 	= (CDrObject*)GetPrev(posAfter); // moves pos to prev
		///////////////
		RemoveAt(posRemove);
		InsertAfter(pReplaceObject,posAfter);
		/////////////////////////////////////
				
}	

int	CPListMgr::RemoveObject(int index)
{ 

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos;
	CDrObject* pTemp;
	/////////////////
	if(!(pos = FindIndex(index)) )
		return -1;
	else	
		pTemp = (CDrObject*)GetAt(pos);
	/////////////////		
	RemoveAt(pos);
	/////////	
	return 0;

}		
	 

int	CPListMgr::DeleteObject(int index)
{ 

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos;
	CDrObject* pTemp;
	/////////////////
	if(!(pos = FindIndex(index)) )
		return -1;
	else	
		pTemp = (CDrObject*)GetAt(pos);
	/////////////////		
	RemoveAt(pos);
	delete pTemp;
	/////////	
	return 0;

}		
	 
CDrObject* CPListMgr::GetObject(int index)
{ 

	int nMaxIndex = GetCount() - 1;

	if ((index>nMaxIndex) || (index<0) )
		return (CDrObject*)NULL;

	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;(pos !=NULL) && (i <= index);i++)
	{
		pObject = GetNextObject( pos);
		
	}
	return pObject;
}
				
int	CPListMgr::GetObjectIndex(long nObjectNo)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = GetNextObject( pos);
		if(pObject->GetObjectNo() == nObjectNo)
		/////////
		return i;
		
	}
	//////////
	return -1;
}	
				
int	CPListMgr::GetObjectIndex(UINT nObjectType, CString strID)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nObjectType)
		{
			if(pObject->GetObjectID() == strID)
			/////////
			return i;
		}	
	}
	///////// r 	6��    �5 	  �5�5  �5      6 	  �5�5  �      �5 t)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = GetNextObject( pos);
		if(pObject == pDrObject)
		/////////
		return i;
		
	}
	//////////
	return -1;
}	
				
int	CPListMgr::GetObjectFirstIndex(UINT nObjectType)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nObjectType)
		/////////
		return i;
		
	}
	//////////
	return -1;
				
}
int	CPListMgr::GetSpecificObjectCount(int nObjectType)
{

    int nCount = 0;
	if(IsEmpty() ) 
		return nCount;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = GetNextObject( pos);
		if(pObject->GetObjectType() == nObjectType)
			nCount++;
	}
	//////////
	return nCount;
				
}
//////////////////////////// End of Module /////////////////////

