

#include "stdafx.h"
#include "ObjMap.h"

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
// HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage,
//		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

/*
	HTREEITEM	m_rghItem[12];
	TV_INSERTSTRUCT		tvstruct;
	for (iItem = 0; iItem < CELEMS(rgszItems); iItem ++)
	{
		tvstruct.hParent = (iItem % 4 == 0)? NULL : m_rghItem[iItem / 4 * 4];
		tvstruct.hInsertAfter = TVI_SORT;
		tvstruct.item.iImage = iItem / 4 * 2;
		tvstruct.item.iSelectedImage = tvstruct.item.iImage + 1;
		tvstruct.item.pszText = rgszItems[iItem];
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		///
		m_rghItem[iItem] = m_mytreectrl.InsertItem(&tvstruct);
	}


		TCHAR	szItems[][18] = {	_T("Elements"),
										_T("Nodes"),
											_T("Node_1"),
											_T("Node_2"),
										_T("Curves"),
											_T("Curve_1"),
											_T("Curve_2"),
									_T("Static Loads")};
*/
		TV_INSERTSTRUCT		tvstruct;
		HTREEITEM hItem,hSubI;
		/////////////////////////////
		tvstruct.hParent = 0;
		tvstruct.item.iImage = 0;
		tvstruct.item.iSelectedImage = 1;
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		/////////////////////////////////////////////////////////////////	Generator
		tvstruct.hInsertAfter = TVI_FIRST;
		tvstruct.item.pszText = "GENERATOR";
		///
		hItem = TCtrl.InsertItem(&tvstruct);
		///////////////////////////////////////////////////////// Children
		hSubI = TCtrl.InsertItem("INPUT NODE",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,NODE);
		///
		hSubI = TCtrl.InsertItem("CONTROL NODE",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,CNODE);
		///
		hSubI = TCtrl.InsertItem("CURVE",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,CURVE);
		///
		hSubI = TCtrl.InsertItem("PROFILE CURVE",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,PROFILE_C);
		///
		hSubI = TCtrl.InsertItem("PATCH",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,PATCH);
		///
		hSubI = TCtrl.InsertItem("PROFILE PATCH",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,PROFILE_P);
		///
		hSubI = TCtrl.InsertItem("SOLID",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,SOLID);
		///
		hSubI = TCtrl.InsertItem("3D OBJECT",0,1,hItem,TVI_LAST);
		PopulateObject(TCtrl,hSubI,OBJ3D);
		/////////////////////////////////////////////////////////////////	Mesh
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.pszText = "MESH";
		///
		hItem = TCtrl.InsertItem(&tvstruct);
		///////////////////////////////////////////////////////// Children
		hSubI = TCtrl.InsertItem("MESH NODE",0,1,hItem,TVI_LAST);
		PopulateMeshObject(TCtrl,hSubI,MNODE);
		///
		hSubI = TCtrl.InsertItem("MESH CONTROL NODE",0,1,hItem,TVI_LAST);
		PopulateMeshObject(TCtrl,hSubI,MCNODE);
		///
		hSubI = TCtrl.InsertItem("1D MESH",0,1,hItem,TVI_LAST);
		PopulateMeshObject(TCtrl,hSubI,MESH1D);
		///
		hSubI = TCtrl.InsertItem("2D MESH",0,1,hItem,TVI_LAST);
		PopulateMeshObject(TCtrl,hSubI,MESH2D);
		///
		hSubI = TCtrl.InsertItem("3D MESH",0,1,hItem,TVI_SORT);
		PopulateMeshObject(TCtrl,hSubI,MESH3D);
		///
		hSubI = TCtrl.InsertItem("3D MESH OBJECT",0,1,hItem,TVI_LAST);
		PopulateMeshObject(TCtrl,hSubI,MBJ3D);
		/////////////////////////////////////////////////////////////////	Elements
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = 1;
		tvstruct.item.pszText = "ELEMENTS";
		///
		hItem = TCtrl.InsertItem(&tvstruct);
		///////////////////////////////////////////////////////// Children


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

int CTreeHandler::PopulateObject(CTreeCtrl& TCtrl,HTREEITEM hSubI,UINT uObjID)
{
	TCtrl.InsertItem("Node_X",0,1,hSubI,TVI_SORT);
	/////////
	return 0;
}

int CTreeHandler::PopulateMeshObject(CTreeCtrl& TCtrl,HTREEITEM hSubI,UINT uObjID)
{
	TCtrl.InsertItem("Mesh_X",0,1,hSubI,TVI_SORT);
	/////////
	return 0;
}