// Dlg_SpnC.h : header file
//
#ifndef _MLG_SPNO_H
#define _MLG_SPNO_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
#include "DrMbj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnO dialog

class AFX_EXT_CLASS CMlg_SpnO : public CDialog
{
// Construction
public:
	CMlg_SpnO(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMbj3D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CMlg_SpnO)
	enum { IDD = IDD_O_SPAWN };
	CString		m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrMbj3D*	m_pDrObj3D;
	CDrMbj3D*	m_pParent;	// this must be supplied for CONTROL Nodes
//	CString		m_CID;		// this must be supplied for all Nodes		(defined Above)
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0 = Symmetry
							// 1 = Direct Matrix
							// 2 = Transform Info
							// 3 = Symmetry 3 Pt. Info

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_SpnO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllObj3DIDs();



	// Generated message map functions
	//{{AFX_MSG(CMlg_SpnO)
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
