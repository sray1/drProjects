// Dlg_LSy3.h : header file
//
#ifndef _MLG_LSY3_H
#define _MLG_LSY3_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_LSy3 dialog

class AFX_EXT_CLASS CMlg_LSy3 : public CDialog
{
// Construction
public:
	CMlg_LSy3(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;




public:

// Dialog Data
	//{{AFX_DATA(CMlg_LSy3)
	enum { IDD = IDD_XFORM_SYM3 };
	//}}AFX_DATA
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_LSy3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void	FillListAllString_Pool();
	void	EmptyListAllString();
	void	GetUnitNormal(pWORLD pNormal); 
	void	SetUpLocalm(pMATRIX pM);



	// Generated message map functions
	//{{AFX_MSG(CMlg_LSy3)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
