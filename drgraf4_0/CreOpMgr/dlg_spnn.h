// Dlg_SpnC.h : header file
//
#ifndef _DLG_SPNN_H
#define _DLG_SPNN_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CMgrRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnN dialog

class AFX_EXT_CLASS CDlg_SpnN : public CDialog
{
// Construction
public:
	CDlg_SpnN(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrNode* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_SpnN)
	enum { IDD = IDD_N_SPAWN };
	CString		m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrNode*	m_pDrNode;
	CDrNode*	m_pParent;	// this must be supplied for CONTROL Nodes
//	CString		m_CID;		// this must be supplied for all Nodes		(defined Above)
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0 = Symmetry
							// 1 = Direct Matrix
							// 2 = Transform Info
							// 3 = Symmetry 3 Pt. Info

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SpnN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllNodeIDs();



	// Generated message map functions
	//{{AFX_MSG(CDlg_SpnN)
	virtual BOOL OnInitDialog();
	afx_msg void OnSymm();
	afx_msg void OnXform();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////
#endif
