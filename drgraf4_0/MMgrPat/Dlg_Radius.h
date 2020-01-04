// dlg_knot.h : header file
//
#ifndef _DLG_RADIUS_H
#define _DLG_RADIUS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Radius dialog

class AFX_EXT_CLASS CDlg_Radius : public CDialog
{
// Construction
public:

	CDlg_Radius(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Radius)
	enum { IDD = IDD_RADIUS };
	double	m_dValue;
	CString	m_strMore;
	double	m_dStep;
	double	m_dScale;
	//}}AFX_DATA
	int		m_nMaxRadius;
	double*	m_pRadius;	// pointer supplied by calling routine
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
	//{{AFX_MSG(CDlg_Radius)
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
