// ObjectBase.h : interface of the CDListMgr class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _DLISTMGR_H_
#define _DLISTMGR_H_ 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


class AFX_EXT_CLASS CDListMgr : public CObList 
{

public: // create from serialization only
	CDListMgr();
#undef AFX_DATA
#define AFX_DATA

	DECLARE_DYNCREATE(CDListMgr)

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA


// Attributes
public: 

	///////////////////////////////////////////////////// Object
	POSITION	GetFirstObjectPos();  				
	CObject*	GetNextObject( POSITION& pos);
	CObject* 	GetObject(int index);
	int 		InsertObject(CObject* pInsertObject);
	int			ReplaceObject(int index,CObject* pReplaceObject);
	int			RemoveObject(int index);
	int			EditObject(int index,CObject* pEditObject);
	int			DeleteObject(int index);
	int			GetObjectIndex(CObject* pObject);
	////////////////////////////////////////////////////////////////////////////////////
	int			GetObjectIndex(long nObjectNo);						// ONLY for DrObject
	int			GetObjectIndex(UINT nObjectType, CString strID);	// ONLY for DrObject
	int			GetObjectFirstIndex(UINT nObjectType);				// ONLY for DrObject
	int			GetSpecificObjectCount(int nObjectType);			// ONLY for DrObject
	////////////////////////////////////////////////////////////////////////////////////
	
protected:                  

    
// Operations
public:
// Implementation
public:
	virtual ~CDListMgr();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
/*
	// Generated message map functions
	//{{AFX_MSG(CDListMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/


};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif
