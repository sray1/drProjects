// Dlg_NodI.h : header file
//
#ifndef _DLGNODI_H
#define _DLGNODI_H


#include "MNodrsrc.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NodI dialog

class AFX_EXT_CLASS CDlg_NodI : public CDialog
{
// Construction
public:
	CDlg_NodI(CWnd* pWnd,BOOL bDirect,BOOL bCNode,
					 BOOL bAdv,BOOL bCoord);	// message filtered to View	CDlg_NodI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_NodI)
	enum { IDD = IDD_NOD_IN };
CString	m_strLn;
	CString	m_strDx;
	CString	m_strDy;
	CString	m_strDz;
	double	m_xWorld;
	double	m_yWorld;
	double	m_zWorld;
	CString	m_FromID;
	CString	m_ToID;
	CString	m_id;
	CString	m_nid_r;
	//}}AFX_DATA
	CWnd*		m_pWnd;
	BOOL		m_bnid_c;
	int			m_nViewNum;
	LPOINT3		m_MouseWIC;
	BOOL		m_bDirect;
	BOOL		m_bAdvanced;
	BOOL		m_bCoord;
	double		m_dLength;
	double		m_DxWorld;
	double		m_DyWorld;
	double		m_DzWorld;



public:

	void		ResetDlg();
	int			ResolveReference_Direction();
	int			ResolveReference_Coords();
	int			UnitAxisFromEndNodes(pWORLD pNormal);




protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NodI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_NodI)
	afx_msg void OnSelchangeNid();
	afx_msg void OnCancel();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanced();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDirection();
	afx_msg void OnCoordInput();
	afx_msg void OnDirect();
	afx_msg void OnChangeNodeDx();
	afx_msg void OnChangeNodeDy();
	afx_msg void OnChangeNodeDz();
	afx_msg void OnChangeLength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
