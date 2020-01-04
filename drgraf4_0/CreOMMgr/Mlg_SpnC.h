// Dlg_SpnC.h : header file
//
#ifndef _MLG_SPNC_H
#define _MLG_SPNC_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
#include "DrMesh1D.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_SpnC dialog

class CMlg_SpnC : public CDialog
{
// Construction
public:
	CMlg_SpnC(CWnd* pParent = NULL);   // standard constructor
	void	SetInfoForDataBase(CDrMesh1D* pDrObject);

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:


// Dialog Data
	//{{AFX_DATA(CMlg_SpnC)
	enum { IDD = IDD_C_SPAWN };
	CString		m_SpawnID;
	CString		m_CID;
	//}}AFX_DATA
	CDrMesh1D*	m_pDrCurve;
//	CString		m_CID;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	int			m_nType;	// 0 = Symmetry
							// 1 = Direct Matrix
							// 2 = Transform Info
							// 3 = Symmetry 3 Pt. Info

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_SpnC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	void	FillListAllString_Pool();
	void	FillListAllCurveIDs();



	// Generated message map functions
	//{{AFX_MSG(CMlg_SpnC)
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
