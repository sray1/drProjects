// dlg_knot.h : header file
//
#ifndef _DLG_KNOT_H
#define _DLG_KNOT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Knot dialog

class CDlg_Knot : public CDialog
{
// Construction
public:

	CDlg_Knot(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Knot)
	enum { IDD = IDD_C_KNOT };
	double	m_dValue;
	CString	m_strMore;
	double	m_dStep;
	//}}AFX_DATA
	int		m_nMaxKnot;
	double*	m_pKVal;	// pointer supplied by calling routine
	int		m_nLast; 	// current
	BOOL	m_bDistinct;// yes= for Interpolation/ no= for Design

// Implementation
protected: 

	CBitmapButton	buttonOK,buttonCancel;
	
protected:
	
	void EmptyListAllString();
	void FillListAllString();
	void FillOthers(int i); 

	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Knot)
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
