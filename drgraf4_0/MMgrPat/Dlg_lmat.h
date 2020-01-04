// dlg_lmat.h : header file
//
#ifndef _DLG_LMAT_H
#define _DLG_LMAT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LMat dialog

class CDlg_LMat : public CDialog
{
// Construction
public:
	CDlg_LMat(CWnd* pParent = NULL);	// standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;

public:
// Dialog Data
	CString	m_PatchID;	//ID of the Patch to Post
// Dialog Data
	//{{AFX_DATA(CDlg_LMat)
	enum { IDD = IDD_LOCALMATRIX };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	double	m_ScaleX;
	double	m_ScaleY;
	double	m_ScaleZ;
	double	m_TranX;
	double	m_TranY;
	double	m_TranZ;
	CString	m_RotPtID;
	CString	m_TranPtID;
	//}}AFX_DATA

// Implementation

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
			int  FillListAllString(UINT DlgItemID,CString& IstID);

	// Generated message map functions
	//{{AFX_MSG(CDlg_LMat)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTranPt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
