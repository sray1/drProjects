// dlg_mesu.h : header file
//
#ifndef _DLG_CMSU_H
#define _DLG_CMSU_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsU dialog

class CDlg_CMsU : public CDialog
{
// Construction
public:
	CDlg_CMsU(CWnd* pParent = NULL);	// standard constructor



protected: 

	CBitmapButton buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_CMsU)
	enum { IDD = IDD_C_MESH_UNIF };
	int		m_nUnif_OT;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CMsU)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
