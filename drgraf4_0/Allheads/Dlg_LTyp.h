// Dlg_CrcT.h : header file
//
#ifndef _DLG_LTYP_H
#define _DLG_LTYP_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LTyp dialog

class CDlg_LTyp : public CDialog
{
// Construction
public:
	CDlg_LTyp(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_LTyp)
	enum { IDD = IDD_LMAT_TYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	BOOL	m_bType_1;		//
	int		m_nType;		//


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LTyp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_LTyp)
	virtual BOOL OnInitDialog();
	afx_msg void OnType1();
	afx_msg void OnType2();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
