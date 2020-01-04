// dlg_swip.h : header file
//

#ifndef _DLG_SWIP_H
#define _DLG_SWIP_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Swip dialog

class CDlg_Swip : public CDialog
{
// Construction
public:
	CDlg_Swip(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrPatch* pDrObject);


protected:
	
	void FillListAllCurveIDs();
	void FillListAllString();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Swip)
	enum { IDD = IDD_SWEEP_PATCH };
	CString	m_CID_Spine;
	CString	m_CID_Twist;
	CString	m_CID_Xsec;
	CString	m_PatchID;
	CString	m_CNID_Anchor;
	double	m_TwistMult;
	BOOL	m_bIncrement;
	CString	m_CID_Radius;
	BOOL	m_bIncRad;
	double	m_RadiusMult;
	double	m_RadStart;
	double	m_TwistStart;
	CString	m_Orient_4;
	CString	m_Orient_2;
	CString	m_Orient_1;
	CString	m_Orient_3;
	BOOL	m_bCNode;
	//}}AFX_DATA
   	int 	m_nHowMany;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Swip)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnIncrement();
	afx_msg void OnIncRad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
