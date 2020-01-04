// dlg_CooP.h : header file
//

#ifndef _DLG_CO4I_H
#define _DLG_CO4I_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Co4I dialog

class AFX_EXT_CLASS CDlg_Co4I : public CDialog
{
// Construction
public:
	CDlg_Co4I(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

protected:
	
	void FillListAllCurveIDs();
	void FillListAllPatchIDs();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_Co4I)
	enum { IDD = IDD_COON4_IN };
	CString	m_PatchID;
	CString	m_CID_1;
	CString	m_CID_2;
	CString	m_CID_3;
	CString	m_CID_4;
	int		m_TotEl_1;
	int		m_TotEl_2;
	int		m_TotEl_3;
	int		m_TotEl_4;
	//}}AFX_DATA
	////////////////////
	CString	m_Orient_1;
	CString	m_Orient_2;
	CString	m_Orient_3;
	CString	m_Orient_4;
    CWnd*	m_pWnd;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Co4I)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangeCid1();
	afx_msg void OnSelchangeCid2();
	afx_msg void OnSelchangeCid3();
	afx_msg void OnSelchangeCid4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
