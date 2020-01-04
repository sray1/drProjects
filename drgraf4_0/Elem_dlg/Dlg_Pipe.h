// Dlg_Pipe.h : header file
//
#ifndef _DLG_PIPE_H
#define _DLG_PIPE_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "EdlgRsrc.h"

#include "DrPipe.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Pipe dialog
/////////////////////////////////////////////////////////////////////////////
class CDlg_Pipe : public CDialog
{
// Construction
public:
	CDlg_Pipe(CWnd* pParent = NULL);	// standard constructor
	void FillListAllRelIDs(int nEndX);
	void FillListAllMatIDs();
	void FillListAllPropIDs();
	void FillListAllSIIDs(int nEndX);
	void EmptyListAllString();
	void SetInfoForDataBase(CDrPipe* pPipe);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Pipe)
	enum { IDD = IDD_ELP_PIPE };
	BOOL	m_bValve;
	CString	m_matID;
	CString	m_propID;
	CString	m_rid_I;
	CString	m_rid_J;
	CString	m_stressID_I;
	CString	m_stressID_J;
	double	m_RefTemp;
	//}}AFX_DATA

	CDrPipe*	m_pDrPipe;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Pipe)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickedValve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
