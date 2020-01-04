// Dlg_Shrink.h : header file
//
#ifndef _Dlg_SHRINK_H
#define _Dlg_SHRINK_H

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Shrink dialog

class CDlg_Shrink : public CDialog
{
// Construction
public:
	CDlg_Shrink(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Shrink)
	enum { IDD = IDD_SHRINKON };
	double	m_dShrink;
	//}}AFX_DATA


protected: 

	CBitmapButton buttonOK,buttonCancel;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Shrink)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Shrink)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
///////////////////////////////////////////////
