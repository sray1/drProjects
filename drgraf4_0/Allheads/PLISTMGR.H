// PListMgr.h : interface of the CPListMgr class : PolyList
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _PLISTMGR_H_
#define _PLISTMGR_H_ 
 

#include "stdafx.h" 

#include "DrObject.h"

class CPListMgr : public CObList 
{

public: // create from serialization only
	CPListMgr();
	DECLARE_DYNCREATE(CPListMgr)

// Attributes
public: 
	///////////////////////////////////////////////////// Object
	POSITION	GetFirstObjectPos();  				
	CDrObject*	GetNextObject( POSITION& pos);
	CDrObject* 	GetObject(int index);
	int 		InsertObject(CDrObject* pInsertObject);
	int			ReplaceObject(int index,CDrObject* pReplaceObject);
	int			RemoveObject(int index);
	int			EditObject(int index,CDrObject* pEditObject);
	int			DeleteObject(int index);
	int			GetObjectIndex(long nObjectNo);
	int			GetObjectIndex(UINT nObjectType, CString strID);
	int			GetObjectIndex(CDrObject* pDrObject);
	int			GetObjectFirstIndex(UINT nObjectType);
	int			GetSpecificObjectCount(int nObjectType);
	
protected:                  

    
// Operations
public:
// Implementation
public:
	virtual ~CPListMgr();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CPListMgr)
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
