// dlg_cpro.h : header file
//
#ifndef _DLG_1MRG_H
#define _DLG_1MRG_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MMs1Rsrc.h"
#include "DrProf_1.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_1Mrg dialog

class CDlg_1Mrg : public CDialog
{
// Construction
public:
	CDlg_1Mrg(CWnd* pParent = NULL);	// standard constructor

	
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
	//{{AFX_DATA(CDlg_1Mrg)
	enum { IDD = IDD_1_PROFILE_SI };
	CString	m_CPro_ID;
	//}}AFX_DATA
	/////////////////////////// Transformation
 	CDListMgr*	m_pMesh1DList; 


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_1Mrg)
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
