
#ifndef _TREEHANDLER_H
#define _TREEHANDLER_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeHandler.h : header file
//
#include <afxtempl.h>


/////////////////////////////////////////////////////////////////////////////
// CTreeHandler

class CTreeHandler : public CObject
{
	DECLARE_DYNCREATE(CTreeHandler)

// Construction
public:
	CTreeHandler();
	~CTreeHandler();


// Overrides

// Implementation
public:

	int		PopulateTreeCtrl(CTreeCtrl& TCtrl);
	int		PopulateObject(CTreeCtrl& TCtrl,HTREEITEM hItem,UINT uObjID);
	int		InsertOneObject(CTreeCtrl& TCtrl,UINT ObjType,CString& strObjID);
	

protected:
};


#endif   // _TREEHANDLER_H

