// testdllDoc.h : interface of the CTestdllDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDLLDOC_H__A9539D17_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_TESTDLLDOC_H__A9539D17_6284_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestdllDoc : public CDocument
{
protected: // create from serialization only
	CTestdllDoc();
	DECLARE_DYNCREATE(CTestdllDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestdllDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestdllDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestdllDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLDOC_H__A9539D17_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
