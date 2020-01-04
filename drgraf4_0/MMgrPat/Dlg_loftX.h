// dlg_loft.h : header file
//

#ifndef _DLG_LOFTX_H
#define _DLG_LOFTX_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftX dialog

class CDlg_LoftX : public CDialog
{
// Construction
public:
	CDlg_LoftX(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void SetDataBase_BC_N_BL(CDrCurve* pDrObject);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_LoftX)
	enum { IDD = IDD_LOFTX_PATCH };
	CString		m_strBLEND;
	CString		m_strBCL;
	CString		m_strBCR;
	BOOL		m_bRightOn;
	BOOL		m_bLeftOn;
	BOOL		m_bClosed;
	int		m_ClosingElems;
	//}}AFX_DATA
	CDrCurve*	m_pDrCurve;			// Blending Curve
	int			m_nLoftCurves;		// # of Lofted Curves
	////////////////////

protected:

	int			m_nOrder;			// k
   	BOUNDARY	m_BCL;
   	BOUNDARY	m_BCR;
	WORLD		m_TanL;
	WORLD		m_TanR;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_LoftX)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBlend();
	afx_msg void OnSelchangeBcLeft();
	afx_msg void OnSelchangeBcRight();
	afx_msg void OnBcLeftOn();
	afx_msg void OnBcRightOn();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClosed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
