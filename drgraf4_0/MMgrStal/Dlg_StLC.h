// dlg_swip.h : header file
//

#ifndef _DLG_STLC_H
#define _DLG_STLC_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MStLRsrc.h"
#include "DrCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_StLC dialog

class AFX_EXT_CLASS CDlg_StLC : public CDialog
{
// Construction
public:
	CDlg_StLC(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void	EnableControls(); 
	void	FillListAllCurveIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_StLC)
	enum { IDD = IDD_CURVILINEAR };
	CString	m_CID;
	BOOL	m_bIncrement;
	CString	m_Orient;
	double	m_dScale;
	double	m_dStep;
	double	m_dStart;
	//}}AFX_DATA
	CDrCurve*	m_pDrCurve;	// Base Curve for which StaticLoad is needed
	CATEGORY	m_Category;	// Force/Moment/Disp/Rot/Pres/Therm/LupWt etc
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_StLC)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnIncrement();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
