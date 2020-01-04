// Dlg_NodI.h : header file
//
#ifndef _DLGFE1I_H
#define _DLGFE1I_H


#include "EdlgRsrc.h"
//#include "DrPipe.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE1I dialog

class AFX_EXT_CLASS CDlg_FE1I : public CDialog
{
// Construction
public:
	CDlg_FE1I(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

	void FillListAllRelIDs(int nEndX);
	void FillListAllMatIDs();
	void FillListAllPropIDs();
	void FillListAllSIIDs(int nEndX);
	void EmptyListAllString();
//	void SetInfoForDataBase(CDrPipe* pPipe);

// Dialog Data
	//{{AFX_DATA(CDlg_FE1I)
	enum { IDD = IDD_FE1_IN };
	BOOL	m_bValve;
	CString	m_matID;
	CString	m_propID;
	CString	m_rid_I;
	CString	m_rid_J;
	CString	m_stressID_I;
	CString	m_stressID_J;
	double	m_RefTemp;
	CString	m_KNodeID;
	//}}AFX_DATA
	///
    CWnd*		m_pWnd;
	UINT		m_ObjType;
//	CDrObject*	m_pDrObject;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_FE1I)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_FE1I)
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
