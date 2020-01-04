#if !defined(AFX_JOINTCOORD_H__CB1D66E1_8508_11D2_8B46_444553540000__INCLUDED_)
#define AFX_JOINTCOORD_H__CB1D66E1_8508_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JointCoord.h : header file
//

#include "Def_Supp.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_JointCoord dialog

class CDlg_JointCoord : public CDialog
{
// Construction
public:
	CDlg_JointCoord(CWnd* pParent = NULL);   // standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_JointCoord)
	enum { IDD = IDD_JOINTCOORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	JOINTCOORD  m_jcType;			//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_JointCoord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_JointCoord)
	afx_msg void OnRadioCurve();
	afx_msg void OnRadioFixedDir();
	afx_msg void OnRadioPatch();
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	afx_msg void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOINTCOORD_H__CB1D66E1_8508_11D2_8B46_444553540000__INCLUDED_)
