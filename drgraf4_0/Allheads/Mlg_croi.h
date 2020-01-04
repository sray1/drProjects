// Dlg_NodI.h : header file
//
#ifndef _MLGCROI_H
#define _MLGCROI_H


#include "CreMRsrc.h"
#include "Def_IGen.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_CrOI dialog

class AFX_EXT_CLASS CMlg_CrOI : public CDialog
{
// Construction
public:
	CMlg_CrOI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CMlg_CrOI)
	enum { IDD = IDD_CRO_IN };
	CString	m_ObjID;
	double	m_X;
	double	m_Y;
	double	m_Z;
	CString	m_NID;
	BOOL	m_bDirect;
	BOOL	m_bDirCos;
	BOOL	m_bDominant;
	BOOL	m_bAngleIn;
	BOOL	m_bNegative;
	BOOL	m_bAxis;
	//}}AFX_DATA
	///
    CWnd*		m_pWnd;
	UINT		m_CreOp;
	int			m_nAxis;		

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_CrOI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMlg_CrOI)
	afx_msg void OnCancel();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCoordInput();
	afx_msg void OnChangeObjID();
	afx_msg void OnAngleInput();
	afx_msg void OnDirCos();
	afx_msg void OnDominant();
	afx_msg void OnNegative();
	afx_msg void OnAxisX();
	afx_msg void OnAxisY();
	afx_msg void OnAxisZ();
	afx_msg void OnAxis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
