// dlg_loft.h : header file
//
					// ONLY BEZIER BLEND oof Order 2, 3 & 4(ForNow Only)
					/////////////////////////////////////////////////////

#ifndef _DLG_CURVEBLEND_H
#define _DLG_CURVEBLEND_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CMgrRsrc.h"
#include "DrCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CurveBlend dialog

class CDlg_CurveBlend : public CDialog
{
// Construction
public:
	CDlg_CurveBlend(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void SetDataBase_BC_N_BL(CDrCurve* pDrObject);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_CurveBlend)
	enum { IDD = IDD_CURVEBLEND };
	CString	m_strBLEND;
	int		m_ClosingElems;
	double	m_Ratio;
	//}}AFX_DATA
	CDrCurve*	m_pDrCurve;			// Blending Curve
	////////////////////
	int			m_nCur1;
	int			m_nCur2;

protected:

	int			m_nOrder;			// k

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CurveBlend)
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
