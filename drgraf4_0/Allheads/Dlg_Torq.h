// dlg_knot.h : header file
//
#ifndef _DLG_TORQ_H
#define _DLG_TORQ_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Torq dialog

class CDlg_Torq : public CDialog
{
// Construction
public:

	CDlg_Torq(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Torq)
	enum { IDD = IDD_TORQ };
	double	m_dValue;
	CString	m_strMore;
	double	m_dStep;
	double	m_dScale;
	//}}AFX_DATA
	int		m_nMaxTwist;
	double*	m_pTwist;	// pointer supplied by calling routine
	int		m_nLast; 	// current
//	BOOL	m_bDistinct;// yes= for Interpolation/ no= for Design

// Implementation
protected: 

	CBitmapButton	buttonOK,buttonCancel;
	
protected:
	
	void EmptyListAllString();
	void FillListAllString();
	void FillOthers(int i); 

	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Torq)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
