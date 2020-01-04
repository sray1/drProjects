#if !defined(AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeLoadPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNodeLoadPage dialog

class CNodeLoadPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeLoadPage)

// Construction
public:
	CNodeLoadPage();
	~CNodeLoadPage();

// Dialog Data
	//{{AFX_DATA(CNodeLoadPage)
	enum { IDD = IDD_NODE_LOAD };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeLoadPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeLoadPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_)
