// dlg_PCon.h : header file
//
#ifndef _DLG_SCON_H
#define _DLG_SCON_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SCon dialog

class CDlg_SCon : public CDialog
{
// Construction
public:
	CDlg_SCon(CWnd* pParent = NULL);	// standard constructor
	
protected:
	
	void EmptyListAllString();
	void FillListAllString();
	void SetInfoForDataBase(CDrSolid* pDrObject);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_SCon)
	enum { IDD = IDD_SOLIDCON };
	CString	m_PatchID;
	BOOL	m_bClosed_S;
	BOOL	m_bClosed_T;
	int		m_nSegs_S;
	int		m_nSegs_T;
	int		m_nMaxCNodes_S;
	int		m_nMaxCNodes_T;
	BOOL	m_bClosed_R;
	int		m_nSegs_R;
	int		m_nMaxCNodes_R;
	//}}AFX_DATA
   	int 	m_nHowMany;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SCon)
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
