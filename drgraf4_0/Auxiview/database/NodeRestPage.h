#if !defined(AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeRestPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage dialog

class CNodeRestPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeRestPage)

// Construction
public:
	CNodeRestPage();
	~CNodeRestPage();

// Dialog Data
	//{{AFX_DATA(CNodeRestPage)
	enum { IDD = IDD_NODE_REST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeRestPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeRestPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_)
