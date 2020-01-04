
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
//debu	int FillTreeCtrl(CTreeCtrl& TCtrl);
	int		PopulateTreeCtrl(CTreeCtrl& TCtrl);
	int		PopulateObject(CTreeCtrl& TCtrl,HTREEITEM hSubI,UINT uObjID);
	int		PopulateMeshObject(CTreeCtrl& TCtrl,HTREEITEM hSubI,UINT uObjID);
	

protected:
};


#endif   // _TREEHANDLER_H

