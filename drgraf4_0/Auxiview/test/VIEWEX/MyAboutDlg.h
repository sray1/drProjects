#if !defined(AFX_MYABOUTDLG_H__951174C3_516D_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_MYABOUTDLG_H__951174C3_516D_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyAboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg dialog

class CMyAboutDlg : public CDialog
{
// Construction
public:
	CMyAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyAboutDlg)
	enum { IDD = IDD_MYABOUT };
	BOOL	m_bCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyAboutDlg)
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYABOUTDLG_H__951174C3_516D_11D2_8A0E_00A0CC30503B__INCLUDED_)
