// Dlg_SpnC.h : header file
//
#ifndef _MLG_SPNS_H
#define _MLG_SPNS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CREMRsrc.h"
#include "DrMesh3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnS dialog

class CMlg_SpnS : public CDialog
{
// Construction
public:
	CMlg_SpnS(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMesh3D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CMlg_SpnS)
	enum { IDD = IDD_S_SPAWN };
	CString	m_SpawnID;
	CString	m_CID;
	//}}AFX_DATA
	CDrMesh3D*	m_pDrSolid;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0=Symm(Pt+Normal)
							// 2=XForms Based
							// 1=Direct
							// 3=Symm(3Pts)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_SpnS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllCurveIDs();



	// Generated message map functions
	//{{AFX_MSG(CMlg_SpnS)
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
