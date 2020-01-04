// Dlg_NodI.h : header file
//
#ifndef _DLGNODI_H
#define _DLGNODI_H


#include "MNodRsrc.h"
#include "Def_IGen.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NodI dialog

class AFX_EXT_CLASS CDlg_NodI : public CDialog
{
// Construction
public:
	CDlg_NodI(CWnd* pWnd,BOOL bAdv);	// message filtered to View
	BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_NodI)
	enum { IDD = IDD_NOD_IN };
	CString	m_ObjID;
	double	m_X;
	double	m_Y;
	double	m_Z;
	CString	m_NID;
	BOOL	m_bAdvanced;
	BOOL	m_bDirect;
	BOOL	m_bDirection;	
	BOOL	m_bDominant;
	BOOL	m_bIncrement;		
	BOOL	m_bMultiple;		
	//}}AFX_DATA
	///
    CWnd*		m_pWnd;
	double		m_dCoord;	// Third Coord for NONAdvance
	int			m_nViewNum;
	BOOL		m_bnid_C;
	LPOINT3		m_MouseWIC;



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
	afx_msg void OnCancel();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnChangeObjID();
	afx_msg void OnIncrement();
	afx_msg void OnDirection();
	afx_msg void OnDirect();
	afx_msg void OnDominant();
	afx_msg void OnAdvanced();
	afx_msg void OnMultiple();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
