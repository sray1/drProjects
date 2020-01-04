// Dlg_Pipe.h : header file
//
#ifndef _DLG_FE1D_H
#define _DLG_FE1D_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "edlgrsrc.h"

#include "DrFE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE1D dialog
/////////////////////////////////////////////////////////////////////////////
class CDlg_FE1D : public CDialog
{
// Construction
public:
	CDlg_FE1D(CWnd* pParent = NULL);	// standard constructor
	void FillListAllNodeIDs(int IorJ);
	void EmptyListAllString();
	void FillListAllString();
	void FillOthers(int i);
	void UpdateCurrentPipe();
	void SetInfoForDataBase(CDrPipe* pPipe);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_FE1D)
	enum { IDD = IDD_ELP_PIPE };
	UINT	m_nseg;
	BOOL	m_bValve;
	CString	m_LineID;
	CString	m_matID;
	CString	m_nid_I;
	CString	m_nid_J;
	CString	m_propID;
	CString	m_rid_I;
	CString	m_rid_J;
	CString	m_stressID_I;
	CString	m_stressID_J;
	//}}AFX_DATA
   	int 	m_nHowMany;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_FE1D)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedAdd();
	afx_msg void OnClickedDel();
	afx_msg void OnClickedEdit();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	afx_msg void OnClickedValve();
	afx_msg void OnKillfocusPipeLineId();
	afx_msg void OnSelchangePipeLineId();
	afx_msg void OnEditupdatePipeLineId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
