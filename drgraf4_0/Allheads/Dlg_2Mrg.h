// dlg_cpro.h : header file
//
#ifndef _DLG_2MRG_H
#define _DLG_2MRG_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MMs2Rsrc.h"
#include "DrProf_2.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_2Mrg dialog

class CDlg_2Mrg : public CDialog
{
// Construction
public:
	CDlg_2Mrg(CWnd* pParent = NULL);	// standard constructor

	
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
	//{{AFX_DATA(CDlg_2Mrg)
	enum { IDD = IDD_2_PROFILE_SI };
	CString	m_CPro_ID;
	//}}AFX_DATA
	/////////////////////////// Transformation
 	CDListMgr*	m_pMesh2DList; 


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_2Mrg)
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
