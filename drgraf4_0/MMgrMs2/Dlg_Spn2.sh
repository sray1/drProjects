// Dlg_SpnC.h : header file
//
#ifndef _DLG_SPN2_H
#define _DLG_SPN2_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MMs2Rsrc.h"
#include "DrMesh2D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Spn2 dialog

class CDlg_Spn2 : public CDialog
{
// Construction
public:
	CDlg_Spn2(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMesh2D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CDlg_Spn2)
	enum { IDD = IDD_P_SPAWN };
	CString	m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrMesh2D*	m_pDrMesh2D;
//	CString		m_CID;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0=Symm(Pt+Normal)
							// 2=XForms Based
							// 1=Direct
							// 3=Symm(3Pts)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Spn2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllCurveIDs();



	// Generated message map functions
	//{{AFX_MSG(CDlg_Spn2)
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
