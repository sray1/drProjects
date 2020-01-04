// Dlg_NodI.h : header file
//
#ifndef _DLGFE2I_H
#define _DLGFE2I_H


#include "EdlgRsrc.h"
//#include "DrPipe.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE2I dialog

class AFX_EXT_CLASS CDlg_FE2I : public CDialog
{
// Construction
public:
	CDlg_FE2I(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

	void FillRefRule();
	void FillListAllRelIDs(int nEndX);
	void FillListAllMatIDs();
	void FillListAllPropIDs();
	void EmptyListAllString();
//	void SetInfoForDataBase(CDrPipe* pPipe);

// Dialog Data
	//{{AFX_DATA(CDlg_FE2I)
	enum { IDD = IDD_FE2_IN };
	CString	m_matID;
	CString	m_propID;
	CString	m_rid_I;
	CString	m_rid_J;
	double	m_RefTemp;
	CString	m_RefRule;
	double	m_dThk;
	CString	m_rid_K;
	CString	m_rid_L;
	//}}AFX_DATA
	///
    CWnd*		m_pWnd;
	UINT		m_ObjType;
	BOOL		m_bQuad;
//	CDrObject*	m_pDrObject;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_FE2I)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_FE2I)
	afx_msg void OnCancel();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
