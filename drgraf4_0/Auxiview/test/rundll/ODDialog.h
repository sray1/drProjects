#if !defined(AFX_ODDIALOG_H__7C3FDD43_5476_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_ODDIALOG_H__7C3FDD43_5476_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ODDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CODDialog dialog

class CODDialog : public CDialog
{
// Construction
public:
	CODDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CODDialog)
	enum { IDD = IDD_ODDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CODDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODDIALOG_H__7C3FDD43_5476_11D2_8A0E_00A0CC30503B__INCLUDED_)
