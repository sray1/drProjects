// dlg_CooP.h : header file
//

#ifndef _DLG_SOLI_H
#define _DLG_SOLI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SolI dialog

class AFX_EXT_CLASS CDlg_SolI : public CDialog
{
// Construction
public:
	CDlg_SolI(CWnd* pWnd,SOLIDPROC SolProc);	// message filtered to View
    BOOL Create ();
	void ResetDlg();

protected:
	
	void FillListAllString_Node();
	void FillListAllString_Curve();
	void FillListAllString_Patch();
	void FillListAllString_Solid();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SolI)
	enum { IDD = IDD_SOLID_IN };
	CString	m_PID;
	CString	m_CID;
	CString	m_NID;
	int		m_nMesh;
	double	m_Ratio;
	BOOL	m_bClosed;
	double	m_SegAngle;
	BOOL	m_bAutoSeg;
	CString	m_Orient;
	BOOL	m_bIncrement;
	double	m_TwistStart;
	double	m_TwistMult;
	double	m_dLen;
	double	m_dCoord;
	//}}AFX_DATA
	////////////////////
    CWnd*		m_pWnd;
	SOLIDPROC	m_SolProc;
	BOOL		m_bTwist;
	//////////////////// IDC_CID dual Purpose: PatchID or CurveID
	BOOL		m_bCurve;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SolI)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnClosed();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	afx_msg void OnIncrement();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
