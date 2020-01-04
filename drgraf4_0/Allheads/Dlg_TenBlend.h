// dlg_loft.h : header file
//

#ifndef _DLG_TENSORBLEND_H
#define _DLG_TENSORBLEND_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_TensorBlend dialog

class CDlg_TensorBlend : public CDialog
{
// Construction
public:
	CDlg_TensorBlend(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void SetDataBase_BC_N_BL(CDrCurve* pDrObject);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_TensorBlend)
	enum { IDD = IDD_TENSORBLEND_PATCH };
	CString		m_strBLEND;
	BOOL		m_bClosed;
	int		m_ClosingElems;
	//}}AFX_DATA
	int			m_Dir;
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
	//{{AFX_MSG(CDlg_TensorBlend)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBlend();
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
