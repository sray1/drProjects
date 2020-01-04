// Dlg_CrcT.h : header file
//
#ifndef _MLG_ROTT_H
#define _MLG_ROTT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "CreMRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_ROTT dialog

class AFX_EXT_CLASS CMlg_ROTT : public CDialog
{
// Construction
public:
	CMlg_ROTT(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CMlg_ROTT)
	enum { IDD = IDD_ROT_TYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	BOOL	m_bType_1;		//
	int		m_nType;		//


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_ROTT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMlg_ROTT)
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