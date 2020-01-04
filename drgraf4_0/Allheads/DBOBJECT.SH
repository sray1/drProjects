// ObjectBase.h : interface of the CObjectBase class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef OBJECTBASE_H
#define OBJECTBASE_H 
 

#include "stdafx.h" 

#include "DrObject.h"

class CObjectBase : public CObject 
{

protected: // create from serialization only
	CObjectBase();
	DECLARE_DYNCREATE(CObjectBase)

// Attributes
public: 
	///////////////////////////////////////////////////// Object
	POSITION	GetFirstObjectPos();  				
	CDrObject*	GetNextObject( POSITION& pos);
	CDrObject* 	GetObject(int index);
	CDrObject*	NewObject(int nObjectType);
	int 		AddObject(CDrObject* pAddObject,int nObjectType);
	int			EditObject(int index,CDrObject* pEditObject);
	int			DeleteObject(int index);
	int			GetObjectIndex(UINT nObjectNo);
	int			GetObjectFirstIndex(UINT nObjectType);
	int			GetSpecificObjectCount(int nObjectType);
	
protected:                  

    
// Operations
public:
// Implementation
public:
	virtual ~CObjectBase();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CObjectBase)
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
