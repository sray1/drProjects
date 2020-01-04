// Dlg_NodI.h : header file
//
#ifndef _DLGFE0I_H
#define _DLGFE0I_H


#include "EdlgRsrc.h"
//#include "DrPipe.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE0I dialog

class AFX_EXT_CLASS CDlg_FE0I : public CDialog
{
// Construction
public:
	CDlg_FE0I(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

	void FillListAllMatIDs();
	void FillListAllPropIDs();
	void EmptyListAllString();
//	void SetInfoForDataBase(CDrPipe* pPipe);

// Dialog Data
	//{{AFX_DATA(CDlg_FE0I)
	enum { IDD = IDD_FE0_IN };
	CString	m_matID;
	CString	m_propID;
	double	m_RefTemp;
	//}}AFX_DATA
	///
    CWnd*		m_pWnd;
	UINT		m_ObjType;
//	CDrObject*	m_pDrObject;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_FE0I)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_FE0I)
	afx_msg void OnClickedValve();
	afx_msg void OnCancel();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
