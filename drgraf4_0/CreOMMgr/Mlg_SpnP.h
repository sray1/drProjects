// Dlg_SpnC.h : header file
//
#ifndef _MLG_SPNP_H
#define _MLG_SPNP_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
#include "DrMesh2D.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnP dialog

class CMlg_SpnP : public CDialog
{
// Construction
public:
	CMlg_SpnP(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMesh2D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CMlg_SpnP)
	enum { IDD = IDD_P_SPAWN };
	CString	m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrMesh2D*	m_pDrPatch;
//	CString		m_CID;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0=Symm(Pt+Normal)
							// 2=XForms Based
							// 1=Direct
							// 3=Symm(3Pts)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_SpnP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllCurveIDs();



	// Generated message map functions
	//{{AFX_MSG(CMlg_SpnP)
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
