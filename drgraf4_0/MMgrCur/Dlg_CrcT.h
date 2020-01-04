// Dlg_CrcT.h : header file
//
#ifndef _DLG_CRCT_H
#define _DLG_CRCT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "Def_CuPS.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcT dialog

class CDlg_CrcT : public CDialog
{
// Construction
public:
	CDlg_CrcT(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_CrcT)
	enum { IDD = IDD_CIRCLE_TYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	BOOL		m_bType_1;		//
	CIRCLETYPE	m_nType;		//


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CrcT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_CrcT)
	virtual BOOL OnInitDialog();
	afx_msg void OnType1();
	afx_msg void OnType2();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnType3();
	afx_msg void OnType4();
	afx_msg void OnType5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
