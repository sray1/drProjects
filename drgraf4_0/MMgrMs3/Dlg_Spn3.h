// Dlg_SpnC.h : header file
//
#ifndef _DLG_SPNS_H
#define _DLG_SPNS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnS dialog

class CDlg_SpnS : public CDialog
{
// Construction
public:
	CDlg_SpnS(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrSolid* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_SpnS)
	enum { IDD = IDD_S_SPAWN };
	CString	m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrSolid*	m_pDrSolid;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0=Symm(Pt+Normal)
							// 2=XForms Based
							// 1=Direct
							// 3=Symm(3Pts)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SpnS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllCurveIDs();



	// Generated message map functions
	//{{AFX_MSG(CDlg_SpnS)
	virtual BOOL OnInitDialog();
	afx_msg void OnSymm();
	afx_msg void OnXform();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////
#endif
