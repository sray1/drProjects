// Dlg_SpnC.h : header file
//
#ifndef _DLG_SPNO_H
#define _DLG_SPNO_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MO3DRsrc.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SpnO dialog

class AFX_EXT_CLASS CDlg_SpnO : public CDialog
{
// Construction
public:
	CDlg_SpnO(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrObj3D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_SpnO)
	enum { IDD = IDD_O_SPAWN };
	CString		m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrObj3D*	m_pDrObj3D;
	CDrObj3D*	m_pParent;	// this must be supplied for CONTROL Nodes
//	CString		m_CID;		// this must be supplied for all Nodes		(defined Above)
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0 = Symmetry
							// 1 = Direct Matrix
							// 2 = Transform Info
							// 3 = Symmetry 3 Pt. Info

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SpnO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllObj3DIDs();



	// Generated message map functions
	//{{AFX_MSG(CDlg_SpnO)
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
