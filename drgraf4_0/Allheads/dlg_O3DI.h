// dlg_CooP.h : header file
//

#ifndef _DLG_O3DI_H
#define _DLG_O3DI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MO3DRsrc.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_O3DI dialog

class AFX_EXT_CLASS CDlg_O3DI : public CDialog
{
// Construction
public:
	CDlg_O3DI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();
	void ResetDlg();

protected:
	
	void FillListAllString_Obj3D();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_O3DI)
	enum { IDD = IDD_O3D_IN };
	CString	m_PID;
	//}}AFX_DATA
	////////////////////
    CWnd*		m_pWnd;
	//////////////////// IDC_CID dual Purpose: PatchID or CurveID

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_O3DI)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
