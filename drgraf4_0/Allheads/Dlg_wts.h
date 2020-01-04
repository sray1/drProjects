// dlg_knot.h : header file
//
#ifndef _DLG_WTS_H
#define _DLG_WTS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Wts dialog

class CDlg_Wts : public CDialog
{
// Construction
public:

	CDlg_Wts(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Wts)
	enum { IDD = IDD_C_WEIGHT };
	double	m_dValue;
	CString	m_strMore;
	//}}AFX_DATA
	int		m_nMaxWeight;
	double*	m_pWVal;	// pointer supplied by calling routine
	int		m_nLast; 	// current

// Implementation
protected: 

	CBitmapButton	buttonOK,buttonCancel;
	
protected:
	
	void EmptyListAllString();
	void FillListAllString();
	void FillOthers(int i); 

	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Wts)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
