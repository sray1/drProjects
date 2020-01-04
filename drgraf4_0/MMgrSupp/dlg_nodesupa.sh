#if !defined(AFX_DLG_NODESUPA_H__E65E2741_843C_11D2_8B46_444553540000__INCLUDED_)
#define AFX_DLG_NODESUPA_H__E65E2741_843C_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// dlg_NodeSupA.h : header file
//

#include "Def_Supp.h"
#include "DrNode.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NodeSupA dialog

class AFX_EXT_CLASS CDlg_NodeSupA : public CDialog
{
// Construction
public:
	CDlg_NodeSupA(CWnd* pParent = NULL);   // standard constructor

protected:
	
	void	EnableControls(); 
	void	FillListAllNodeIDs_A();
	void	FillListAllNodeIDs_B();
	void	FillListAllCurveIDs();
	void	FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_NodeSupA)
	enum { IDD = IDD_ADV_LSUP_NODE };
	BOOL	m_bRxG;
	BOOL	m_bRyG;
	BOOL	m_bRzG;
	BOOL	m_bTxG;
	BOOL	m_bTyG;
	BOOL	m_bTzG;
	CString	m_NID;
	CString	m_NID_B;
	BOOL	m_bCN_a;
	BOOL	m_bCN_b;
	CString	m_CurveID;
	CString	m_PatchID;
	//}}AFX_DATA
    CWnd*		m_pWnd;
    CDrNode*	m_pNode;
	BOOL		m_bRx;
	BOOL		m_bRy;
	BOOL		m_bRz;
	BOOL		m_bTx;
	BOOL		m_bTy;
	BOOL		m_bTz;
	UINT&		m_nType;	// 0 = Fixed Dir/1 = NODE/2 = CURVE/3 = PATCH


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NodeSupA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_NodeSupA)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNid();
	afx_msg void OnCnA();
	afx_msg void OnCnB();
	afx_msg void OnSelchangeNidb();
	afx_msg void OnSelchangeCurvecombo();
	afx_msg void OnSelchangePatchcombo();
	afx_msg void OnNormal();
	afx_msg void OnTangent();
	afx_msg void OnRadioPatch();
	afx_msg void OnRadioNode();
	afx_msg void OnRadioCurve();
	afx_msg void OnRadioFixedDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_NODESUPA_H__E65E2741_843C_11D2_8B46_444553540000__INCLUDED_)
