// Dlg_CrcI.h : header file similar to Old:Dlg_Crc2.h
//	Circle by 3 Nodes
#ifndef _DLG_CRCI_H
#define _DLG_CRCI_H


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcI dialog

class AFX_EXT_CLASS CDlg_CrcI : public CDialog
{
// Construction
public:
	CDlg_CrcI(CWnd* pWnd,CIRCLETYPE	CircType);	// message filtered to View
    BOOL Create ();
	
protected:

	/////////////////
	void 	EmptyListAllString();
	void 	FillListAllString_Node();
	void 	FillListAllString_Curve();
   /////////////////////////////////////////////


public:

	// Dialog Data
	//{{AFX_DATA(CDlg_CrcI)
	enum { IDD = IDD_CRC_IN };
	CString	m_CurveID;
	CString	m_NID;
	double	m_Ratio;
	double	m_SegAngle;
	BOOL	m_bAutoSeg;
	double	m_dCoord;
	BOOL	m_bAxis;
	BOOL	m_bNegative;
	BOOL	m_bUniform;
	int		m_nTotElems;
	int		m_nElemPerSeg;
	double	m_dRadius;
	double	m_dAngSpec;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	BOOL		m_bArc;
	BOOL		m_bClosed;
	CIRCLETYPE	m_CircType;
	int			m_nAxis;


protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CrcI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_CrcI)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	afx_msg void OnUpdate();
	afx_msg void OnClosed();
	afx_msg void OnAngspec();
	afx_msg void OnArc();
	afx_msg void OnCancel();
	afx_msg void OnKillfocusCoord();
	afx_msg void OnAxisZ();
	afx_msg void OnAxisX();
	afx_msg void OnAxisY();
	afx_msg void OnAxis();
	afx_msg void OnNegative();
	afx_msg void OnUniform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
