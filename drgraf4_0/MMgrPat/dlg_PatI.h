// dlg_CooP.h : header file
//

#ifndef _DLG_PATI_H
#define _DLG_PATI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
#include "BasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PatI dialog

class AFX_EXT_CLASS CDlg_PatI : public CBasePage
{
	DECLARE_DYNCREATE(CDlg_PatI)

// Construction
public:
	CDlg_PatI();   // standard constructor
	CDlg_PatI(CWnd* pParentWnd,PATCHPROC PatProc); 
	~CDlg_PatI();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Node();
	void FillListAllString_Curve();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_PatI)
	enum { IDD = IDD_PAT_IN };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_PatI)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnClosed();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	afx_msg void OnIncrement();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
