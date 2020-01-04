// Dlg_OutR.h : header file
//
#ifndef _DLG_CMSR_H
#define _DLG_CMSR_H



#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsR dialog

class CDlg_CMsR : public CDialog
{
// Construction
public:
	CDlg_CMsR(CWnd* pParent = NULL);   // standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;


public:
// Dialog Data
	//{{AFX_DATA(CDlg_CMsR)
	enum { IDD = IDD_OUT_RATIO };
	double	m_Ratio;
	int		m_nElOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CMsR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_CMsR)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
