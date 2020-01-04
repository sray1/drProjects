// dlg_PCon.h : header file
//
#ifndef _DLG_PCON_H
#define _DLG_PCON_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PCon dialog

class CDlg_PCon : public CDialog
{
// Construction
public:
	CDlg_PCon(CWnd* pParent = NULL);	// standard constructor
	
protected:
	
	void EmptyListAllString();
	void FillListAllString();
	void SetInfoForDataBase(CDrPatch* pDrObject);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_PCon)
	enum { IDD = IDD_PATCHCON };
	CString	m_PatchID;
	BOOL	m_bClosed_S;
	BOOL	m_bClosed_T;
	int		m_nSegs_S;
	int		m_nSegs_T;
	int		m_nMaxCNodes_S;
	int		m_nMaxCNodes_T;
	//}}AFX_DATA
   	int 	m_nHowMany;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_PCon)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
