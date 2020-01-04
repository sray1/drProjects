// dlg_cout.h : header file
//
#ifndef _DLG_CMSN_H
#define _DLG_CMSN_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "DrCurve.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CMsN dialog

class CDlg_CMsN : public CDialog
{
// Construction
public:
	CDlg_CMsN(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_CMsN)
	enum { IDD = IDD_C_NONUNIFORM };
	int			m_nSegOut;
	CString		m_BegID;
	CString		m_EndID;
	//}}AFX_DATA
	pINT		m_pOSeg;
	CDrCurve*	m_pDrCurve;
	int			m_nSeg_DT;	// L = nData - 1

protected: 

	void 	UpdateList(int index);
	void 	FillOthers(int i);
	void 	FillListAllString();
	void 	EmptyListAllString();
	void 	SetInfoForDataBase();

protected: 

	CBitmapButton buttonOK,buttonCancel;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CMsN)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedEdit();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeCentralAngle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
