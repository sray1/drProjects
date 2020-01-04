

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Ext_Obj.h"

#include "TreeHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CTreeHandler, CObject )
/////////////////////////////////////////////////////////////////////////////
// CTreeHandler property page


CTreeHandler::CTreeHandler()
{
}


CTreeHandler::~CTreeHandler()
{
}

int CTreeHandler::PopulateTreeCtrl(CTreeCtrl & TCtrl)
{
	CWaitCursor cursor;	// this will automatically display a wait cursor

	// Make sure tree is empty before (re)populating it
	TCtrl.DeleteAllItems();

	TV_INSERTSTRUCT		tvstruct;
	HTREEITEM hItem;
	/////////////////////////////
	tvstruct.hParent = 0;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	/////////////////////////////////////////////////////////////////
	for(int j=0;j<nMax_ObjectTypes;j++)
	{
		///////////////////////////////////////////////// Level 0 (Top Level)
		tvstruct.hInsertAfter = (j==0)?TVI_FIRST:TVI_LAST;
		tvstruct.item.pszText = (LPSTR)(ObjTypes[j].Name);
		hItem = TCtrl.InsertItem(&tvstruct);
		//////////////////////////////////// Level 1 (Children)
		PopulateObject(TCtrl,hItem,ObjTypes[j].ID);
		///////////////////////////////////////
	}

	/***
	TV_ITEM tv_Item;
	CString str = "Hello";
	tv_Item.mask = TVIF_TEXT;
	tv_Item.pszText = (char *)((const char *)str);
	tv_Item.cchTextMax = str.GetLength + 1();
	ASSERT(TCtrl.GetItem(&tv_Item));
	HTREEITEM hRet = tv_Item.hItem;
	CString strSub = tv_Item.pszText;
	***/
	

	return 0;
}

int CTreeHandler::PopulateObject(CTreeCtrl& TCtrl,HTREEITEM hItem,UINT uObjID)
{
// HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage,
//		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////
	int nIndex = pObjectMgr->ObjTypeToListIndex(uObjID);
	if(nIndex<0)
		return -2;		// NoList->No children
	//////////////////////////////////
	CDListMgr*	pList = pObjectMgr->GetObjectListFromIndex(nIndex);
	////////////////////////////////////////////////////
	if(pList->IsEmpty())
		return -2;		// No children
	//////////////////////////////////////////////////// Populate
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		//////////////////////////////////
		TCtrl.InsertItem(pObject->GetObjectID(),0,1,hItem,TVI_LAST);
	}
	/////////
	return 0;
}

int CTreeHandler::InsertOneObject(CTreeCtrl& TCtrl,UINT ObjType,CString& strObjID)
{
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CDbObjMgr* pDbObjMgr 	= pDoc->GetDbObjMgr();
	////////////////////////////////////////////////////////////////////
	LPCTSTR pStrParent = pDbObjMgr->LookUpName(ObjType);	// parent
	if(((CString)pStrParent).GetLength() <=0)
		return -1;
	/////////////////////////////
	HTREEITEM hItemParent;
	TV_ITEM tvItem;
	tvItem.hItem	= hItemParent; 
	tvItem.mask		= TVIF_TEXT; 
	tvItem.pszText = (LPSTR)pStrParent; 
	//
	TCtrl.GetItem(&tvItem);
	//////////////////////////////////
	TCtrl.InsertItem(strObjID,0,1,hItemParent,TVI_LAST);
	/////////
	return 0;
}
