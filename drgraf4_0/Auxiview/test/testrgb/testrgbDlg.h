// testrgbDlg.h : header file
//

#if !defined(AFX_TESTRGBDLG_H__2F591C49_5394_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_TESTRGBDLG_H__2F591C49_5394_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestrgbDlg dialog

class CTestrgbDlg : public CDialog
{
// Construction
public:
	CTestrgbDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestrgbDlg)
	enum { IDD = IDD_TESTRGB_DIALOG };
	UINT	m_Blue;
	UINT	m_Green;
	UINT	m_Red;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestrgbDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CRect m_ColorRect;    

	// Generated message map functions
	//{{AFX_MSG(CTestrgbDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDone();
	afx_msg void OnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRGBDLG_H__2F591C49_5394_11D2_8A0E_00A0CC30503B__INCLUDED_)
