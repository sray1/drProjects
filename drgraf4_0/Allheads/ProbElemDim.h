#if !defined(AFX_PROBELEMDIM_H__D1A87243_39CE_11D3_8B46_44455354616F__INCLUDED_)
#define AFX_PROBELEMDIM_H__D1A87243_39CE_11D3_8B46_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProbElemDim.h : header file
//

#include	"Def_Objs.h"	// PROBDIMLIM ELEMDIMLIM
/////////////////////////////////////////////////////////////////////////////
// CProbElemDim dialog

class CProbElemDim : public CDialog
{
// Construction
public:
	CProbElemDim(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProbElemDim)
	enum { IDD = IDD_PROBELEMLIM };
	CString	m_ElemDim;
	CString	m_ProbDim;
	//}}AFX_DATA
	PROBDIMLIM	m_PDim;
	ELEMDIMLIM	m_EDim;


protected: 

	CBitmapButton buttonOK,buttonCancel;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProbElemDim)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProbElemDim)
	afx_msg void OnSelchangeComboElemdim();
	afx_msg void OnSelchangeComboProbdim();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROBELEMDIM_H__D1A87243_39CE_11D3_8B46_44455354616F__INCLUDED_)
