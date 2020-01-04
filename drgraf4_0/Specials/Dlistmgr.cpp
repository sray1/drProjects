// Element dataBase.cpp : implementation of the CDListMgr class
//

#include "stdafx.h"

#include "drobject.h"
/////////////////////////////
#include "DListMgr.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/*
BEGIN_MESSAGE_MAP(CDListMgr, CObList)
	//{{AFX_MSG_MAP(CDListMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

IMPLEMENT_DYNCREATE(CDListMgr,CObList)

CDListMgr::CDListMgr()
{
}

CDListMgr::~CDListMgr()
{
}

///////////////////////////////////////////////////////////////////////

void CDListMgr::AssertValid() const
{
	CObject::AssertValid();
}

void CDListMgr::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

POSITION CDListMgr::GetFirstObjectPos()
{

	return GetHeadPosition();

}	

CObject* CDListMgr::GetNextObject(POSITION& pos)
{ 

	return GetNext(pos);

} 

int CDListMgr::InsertObject(CObject* pInsertObject)
{

	//////////////////////
	AddTail(pInsertObject);
	///////////////////////
	return 0;
		
}		

int	CDListMgr::EditObject(int index,CObject* pEditObject)
{                                                   

	CObject* pObject = GetObject(index);
//	pObject->SetObjectInfo(pEditObject);
//	pObjectMgr->SetActiveObjectIndex(index);		    	// set Index									
    ////////////////////////////////////////////////////////// Invalidate
//	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,index);
	///////////////////////////////////////////////////										
	return 0;		
}	

int	CDListMgr::ReplaceObject(int index,CObject* pReplaceObject)
{                                                   

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;
    ////////////////////////////////////
	POSITION posRemove,posAfter;
	CObject* pTemp;
	/////////////////
	if(!(posRemove = (posAfter = FindIndex(index) )) )
		return -1;
	else	
		pTemp 	= GetPrev(posAfter); // moves pos to prev
	///////////////
	RemoveAt(posRemove);
	InsertAfter(posAfter,pReplaceObject);
	/////////////////////////////////////
	return 0;
				
}	

int	CDListMgr::RemoveObject(int index)
{ 

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos;
	CObject* pTemp;
	/////////////////
	if(!(pos = FindIndex(index)) )
		return -1;
	else	
		pTemp = GetAt(pos);
	/////////////////		
	RemoveAt(pos);
	/////////	
	return 0;

}		

int	CDListMgr::DeleteObject(int index)
{ 

	int nMaxIndex = GetCount() - 1; 
 
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos;
	CObject* pTemp;
	/////////////////
	if(!(pos = FindIndex(index)) )
		return -1;
	else	
		pTemp = GetAt(pos);
	/////////////////		
	RemoveAt(pos);
	delete pTemp;
	/////////	
	return 0;

}		
	 
CObject* CDListMgr::GetObject(int index)
{ 

	int nMaxIndex = GetCount() - 1;

	if ((index>nMaxIndex) || (index<0) )
		return (CObject*)NULL;

	POSITION pos = GetFirstObjectPos();
	CObject* pObject;
	for (int i=0;(pos !=NULL) && (i <= index);i++)
	{
		pObject = GetNextObject( pos);
		
	}
	return pObject;
}
				
int	CDListMgr::GetObjectIndex(long nObjectNo)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = (CDrObject*)GetNextObject( pos);
		if(pObject->GetObjectNo() == nObjectNo)
		/////////
		return i;
		
	}
	//////////
	return -1;
}	
				
int	CDListMgr::GetObjectIndex(UINT nObjectType, CString strID)
{

	if(IsEmpty() ) 
		return -1;
	///////////////////////////////////////////////// ObjType
	//		Special for Node,CNode,MNode,INode
	//		///////////////////////////////////
	//	Since it is the correct List(hopefully) and
	//	CDrNode Class ObjectType is always NODE
	//	We Need to convert variations to NODE
	/////////////////////////////////////////////////
	UINT nType = nObjectType;
	///
	if	( nType == NODE	|| nType == INODE || nType == CNODE	)
		nType = NODE;
	if	( nType == FE0D	|| nType == MNODE || nType == MCNODE )
		nType = FE0D;
    /////////////////////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = (CDrObject*)GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nType)
		{
			if(pObject->GetObjectID() == strID)
			/////////
			return i;
		}	
	}
	//////////
	return -1;
}	
				
int	CDListMgr::GetObjectIndex(CObject* pDrObject)
{

	if(IsEmpty() ) 
		return -1;
    /////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CObject* pObject;
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
				
int	CDListMgr::GetObjectFirstIndex(UINT nObjectType)
{

	if(IsEmpty() ) 
		return -1;
	///////////////////////////////////////////////// ObjType
	//		Special for Node,CNode,MNode,INode
	//		///////////////////////////////////
	//	Since it is the correct List(hopefully) and
	//	CDrNode Class ObjectType is always NODE
	//	We Need to convert variations to NODE
	/////////////////////////////////////////////////
	UINT nType = nObjectType;
	///
	if	(
			nType == NODE	|| nType == INODE ||
			nType == CNODE	|| nType == MNODE 
	)
		nType = NODE;
    /////////////////////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = (CDrObject*)GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nType)
		/////////
		return i;
		
	}
	//////////
	return -1;
				
}
int	CDListMgr::GetSpecificObjectCount(int nObjectType)
{

    int nCount = 0;
	///////////////
	if(IsEmpty() ) 
		return nCount;
	///////////////////////////////////////////////// ObjType
	//		Special for Node,CNode,MNode,INode
	//		///////////////////////////////////
	//	Since it is the correct List(hopefully) and
	//	CDrNode Class ObjectType is 
	//		NODE for NODE,INODE & CNODE
	//		FE0D for FE0D,MNODE & MCNODE
	//	We Need to convert variations to NODE
	/////////////////////////////////////////////////
	UINT nType = (UINT)nObjectType;
	///
	if	( nType == NODE	|| nType == INODE	|| nType == CNODE )
		nType = NODE;
	else
	if	( nType == MNODE	|| nType == FE0D )
		nType = FE0D;
    /////////////////////////////////////////////////
	POSITION pos = GetFirstObjectPos();
	CDrObject* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = (CDrObject*)GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nType)
			nCount++;
	}
	//////////
	return nCount;
				
}
//////////////////////////// End of Module /////////////////////
/*		
// SAVE FOLLOWING STATEMENTS
////////////////////////////////////////////// 
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////////////// 
//		nLastObjectNo = pObjectMgr->GetLastObjectNo();
//		pObject->SetObjectNo(nLastObjectNo);					// for ObjectList
//		pAddObject->SetObjectNo(nLastObjectNo);					// for ObjectList
		////////////////////////////////////////////////////////// ObjectList Update
															 	// search for
															 	// edit/delete	 
//		pObjectMgr->UpdateLastObjectNo();                    	// ++ for next
	    //////////////////////////////////////////////
	    int nElemType = pObject->GetElemType();   				// Mark document
	    if( nElemType>0)                              			// as modified for 
			pDoc->SetModifiedFlag();                   			// VIEWABLE Objects ONLY		 
		////////////////////////////////////////////////////////////////////////////////													    
		int nActiveIndex = pObjectMgr->GetObjectCount() - 1;
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Index									
        ////////////////////////////////////////////////////////// Invalidate
        														// IF VIEWABLE 
		if(nElemType >0)        															
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex);
    //////////////////////////////////////////////
*/