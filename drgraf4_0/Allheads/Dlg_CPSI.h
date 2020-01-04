// dlg_cpro.h : header file
//
#ifndef _DLG_CPSI_H
#define _DLG_CPSI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
#include "DrProf_C.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CPSI dialog

class CDlg_CPSI : public CDialog
{
// Construction
public:
	CDlg_CPSI(CWnd* pParent = NULL);	// standard constructor

	
protected:
	
	/////////////////
	void	EmptyListAllString(UINT DlgID);
	void	EmptyComboAllString(UINT DlgID);
	void	FillListAllString_Pool();
	void	FillListAllString_Profile();


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_CPSI)
	enum { IDD = IDD_C_PROFILE_SI };
	CString	m_CPro_ID;
	//}}AFX_DATA
	/////////////////////////// Transformation
 	CDListMgr*	m_pCurveList; 


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CPSI)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangePoollist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
