// dlg_swip.h : header file
//

#ifndef _DLG_F_MA_H
#define _DLG_F_MA_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MStLRsrc.h"
#include "DrCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_F_MA dialog

class AFX_EXT_CLASS CDlg_F_MA : public CDialog
{
// Construction
public:
	CDlg_F_MA(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void	EnableControls(); 
	void	FillListAllCurveIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_F_MA)
	enum { IDD = IDD_ADVANCE };
	CString	m_CID;
	BOOL	m_bIncrement;
	CString	m_Orient;
	double	m_dScale;
	double	m_dStep;
	double	m_dStart;
	CString	m_NID;
	BOOL	m_bTangent;
	//}}AFX_DATA
	CDrCurve*	m_pDrCurve;
	CATEGORY	m_Category;	//Force/Moment/Disp/Rot/Pres/Therm/LupWt etc
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_F_MA)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnIncrement();
	afx_msg void OnTangent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
