// axis.h : header file
//
#ifndef _AXIS
#define _AXIS 

#include "stdafx.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawAxis dialog
/////////////////////////////////////////////////////////////////////////////
class CDrawAxis : public CDialog
{
// Construction
public:
	CDrawAxis(CWnd* pParent = NULL);	// standard constructor
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
// Dialog Data
	//{{AFX_DATA(CDrawAxis)
	enum { IDD = IDD_AXIS };
	CString	m_szDrawVertical;
	CString	m_szDrawPositive;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDrawAxis)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlg_Axis dialog

class CDlg_Axis : public CDialog
{
// Construction
public:
	CDlg_Axis(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Axis)
	enum { IDD = IDD_AXISWND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Axis)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
