// databaseDoc.h : interface of the CDatabaseDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEDOC_H__FF628E50_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_DATABASEDOC_H__FF628E50_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////
#include "ObjMap.h"

class CDatabaseDoc : public CDocument
{
protected: // create from serialization only
	CDatabaseDoc();
	DECLARE_DYNCREATE(CDatabaseDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation


	
public:
	CString&		GetCurrentItem() { return m_CurrentItem; };
	void			SetCurrentItem(CString& item) {m_CurrentItem = item;} ;
	CString&		GetCurrentParent() { return m_CurrentParent; };
	void			SetCurrentParent(CString& item) {m_CurrentParent = item;} ;
	int				PopulateMap();
	UINT			GetObjectType_N_Item(CString& strItem);
	
	virtual ~CDatabaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	CString		m_CurrentItem;
	CString		m_CurrentParent;
	DrObjectMap	m_strUintMap;
	

// Generated message map functions
//protected:
	//{{AFX_MSG(CDatabaseDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
#endif 	// !defined(AFX_DATABASEDOC_H__FF628E50_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
