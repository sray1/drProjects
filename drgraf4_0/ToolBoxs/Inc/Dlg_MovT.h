// Dlg_CrcT.h : header file
//
#ifndef _DLG_MOVT_H
#define _DLG_MOVT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "CMgrRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_MOVT dialog

class AFX_EXT_CLASS CDlg_MOVT : public CDialog
{
// Construction
public:
	CDlg_MOVT(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_MOVT)
	enum { IDD = IDD_MOV_TYPE };
	//}}AFX_DATA
	BOOL	m_bType_1;		//
	int		m_nType;		//


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_MOVT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_MOVT)
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
