// rundllDoc.h : interface of the CRundllDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNDLLDOC_H__B72ECA3A_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_RUNDLLDOC_H__B72ECA3A_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CRundllDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CRundllDoc)

// Attributes
public:
	CRundllDoc();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRundllDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRundllDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRundllDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNDLLDOC_H__B72ECA3A_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
