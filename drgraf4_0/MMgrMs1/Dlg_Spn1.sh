// Dlg_SpnC.h : header file
//
#ifndef _DLG_SPN1_H
#define _DLG_SPN1_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrMesh1D.h"
#include "MMs1Rsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Spn1 dialog

class CDlg_Spn1 : public CDialog
{
// Construction
public:
	CDlg_Spn1(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMesh1D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_Spn1)
	enum { IDD = IDD_C_SPAWN };
	CString		m_SpawnID;
	CString		m_CID;
	//}}AFX_DATA
	CDrMesh1D*	m_pDrMesh1D;
//	CString		m_CID;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0 = Symmetry
							// 1 = Direct Matrix
							// 2 = Transform Info
							// 3 = Symmetry 3 Pt. Info

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Spn1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllMesh1DIDs();



	// Generated message map functions
	//{{AFX_MSG(CDlg_Spn1)
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
