// Dlg_CurI.h : header file similar to: Dlg_Circ.h
// CIRCLE_BY_2N_TI_R
//	CString	m_NodeID	= CNode_TI;
//	CString	m_FromID	= Node_I;
//	CString	m_ToID		= Node_J;
/////////////////////
#ifndef _DLG_CR3I_H
#define _DLG_CR3I_H


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Cr3I dialog

class AFX_EXT_CLASS CDlg_Cr3I : public CDialog
{
// Construction
public:
	CDlg_Cr3I(CWnd* pWnd);	// message filtered to View
    BOOL Create ();
	
protected:
	

	/////////////////
	void	FillListAllCurveIDs();
	void	FillListAllNodeIDs();
   /////////////////////////////////////////////



public:
// Dialog Data
	//{{AFX_DATA(CDlg_Cr3I)
	enum { IDD = IDD_CR3_IN };
	CString	m_CurveID;
	int		m_nMesh;
	double	m_Ratio;
	CString	m_FromID;
	CString	m_ToID;
	CString	m_NodeID;
	double	m_SegAngle;
	BOOL	m_bAutoSeg;
	//}}AFX_DATA
    CWnd*	m_pWnd;


protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Cr3I)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Cr3I)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnUpdate();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
