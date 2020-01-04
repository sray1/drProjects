// Dlg_Shrink.h : header file
//
#ifndef _DLG_NOLABELEM_H
#define _DLG_NOLABELEM_H

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NoLabELem dialog

class CDlg_NoLabELem : public CDialog
{
// Construction
public:
	CDlg_NoLabELem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_NoLabELem)
	enum { IDD = IDD_NOSHOW_LABEL_ELEM };
	BOOL	m_bBallJt;
	BOOL	m_bBeam;
	BOOL	m_bElbow;
	BOOL	m_bHexa;
	BOOL	m_bAll;
	BOOL	m_bNone;
	BOOL	m_bPenta;
	BOOL	m_bPipe;
	BOOL	m_bQu_12;
	BOOL	m_bQu_16;
	BOOL	m_bQu_4;
	BOOL	m_bQu_8;
	BOOL	m_bQu_9;
	BOOL	m_bTetra;
	BOOL	m_bTr_10;
	BOOL	m_bTr_3;
	BOOL	m_bTr_6;
	BOOL	m_bTr_9;
	BOOL	m_bTruss;
	//}}AFX_DATA
	

protected: 

	CBitmapButton buttonOK,buttonCancel;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NoLabELem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_NoLabELem)
	virtual BOOL OnInitDialog();
	afx_msg void OnNoshowAll();
	afx_msg void OnNoshowNone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
///////////////////////////////////////////////
