// dlg_rend.h : header file
//
#ifndef _DLG_REND_H
#define _DLG_REND_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Rend dialog

class CDlg_Rend : public CDialog
{
// Construction
public:
	CDlg_Rend(CWnd* pParent = NULL);	// standard constructor

protected: 

	CBitmapButton 	buttonOK,buttonCancel;
	void 			DrawSample(CStatic* pWndCntrl,COLORREF crColor);

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Rend)
	enum { IDD = IDD_RENDINFO };
	double	m_Absorp;
	BOOL	m_bAmb;
	BOOL	m_bCull;
	double	m_Diff_Coef;
	BOOL	m_bDist;
	BOOL	m_bFrame;
	BOOL	m_bHazing;
	BOOL	m_bLight;
	double	m_Refr_Coef;
	BOOL	m_bShadow;
	int		m_SpecIndex;
	double	m_Spec_Coef;
	double	m_Transm_Coef;
	BOOL	m_bTurbul;
	BOOL	m_bWireF;
	//}}AFX_DATA
	COLORREF	m_crColor_Ambi;
	COLORREF	m_crColor_Fram;
	COLORREF	m_crColor_Refl;
	////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CDlg_Rend)
	virtual BOOL OnInitDialog();
	afx_msg void OnAmbColr();
	afx_msg void OnFrmColr();
	afx_msg void OnReflColr();
	afx_msg void OnTexture();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
