#if !defined(AFX_XTRULENS_H__05EA12C1_F889_11D2_8B46_00A0CC212C2F__INCLUDED_)
#define AFX_XTRULENS_H__05EA12C1_F889_11D2_8B46_00A0CC212C2F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// XtruLens.h : header file
//

#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CXtruLens dialog

class AFX_EXT_CLASS CXtruLens : public CDialog
{
// Construction
public:
	CXtruLens(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXtruLens)
	enum { IDD = IDD_EXTRUSION_STEPS };
	double	m_Xtru_X;
	double	m_Xtru_Y;
	double	m_Xtru_Z;
	double	m_DirX;
	double	m_DirY;
	double	m_DirZ;
	double	m_dLen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXtruLens)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		ShowResultants();
	double	UnitAxis_N_LenFromWorldLength(WORLD wLen,WORLD& wAxis);

	// Generated message map functions
	//{{AFX_MSG(CXtruLens)
	afx_msg void OnChangeExtruZ();
	afx_msg void OnChangeExtruX();
	afx_msg void OnChangeExtruY();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTRULENS_H__05EA12C1_F889_11D2_8B46_00A0CC212C2F__INCLUDED_)
