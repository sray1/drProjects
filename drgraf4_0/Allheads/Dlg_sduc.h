// dlg_duct.h : header file
//

#ifndef _DLG_DUCT_S_H
#define _DLG_DUCT_S_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Duct_S dialog

class CDlg_Duct_S : public CDialog
{
// Construction
public:
	CDlg_Duct_S(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrSolid* pDrObject);

protected:
	
	void FillListAllCurveIDs();
	void FillListAllString();
	void FillListAllPatchIDs();
	void FillListAllSolidIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_Duct_S)
	enum { IDD = IDD_DUCT_SOLID };
	CString	m_CID_Spine;
	CString	m_CID_Twist;
	CString	m_CID_Xsec;
	CString	m_PatchID;
	CString	m_CNID_Anchor;
	double	m_TwistMult;
	BOOL	m_bIncrement;
	double	m_TwistStart;
	CString	m_Orient_1;
	CString	m_Orient_2;
	BOOL	m_bCNode;
	//}}AFX_DATA
   	PATSUBTYPE	m_SubType;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Duct_S)
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
