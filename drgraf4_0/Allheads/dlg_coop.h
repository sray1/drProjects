// dlg_CooP.h : header file
//

#ifndef _DLG_COOP_H
#define _DLG_COOP_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CooP dialog

class CDlg_CooP : public CDialog
{
// Construction
public:
	CDlg_CooP(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void SetInfoForDataBase(CDrPatch* pDrObject);
	void FillListAllCurveIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_CooP)
	enum { IDD = IDD_COONS_PATCH4 };
	CString	m_PatchID;
	CString	m_CID_1;
	CString	m_CID_2;
	CString	m_CID_3;
	CString	m_CID_4;
	int		m_TotEl_1;
	int		m_TotEl_2;
	int		m_TotEl_3;
	int		m_TotEl_4;
	CString	m_Orient_1;
	CString	m_Orient_2;
	CString	m_Orient_3;
	CString	m_Orient_4;
	//}}AFX_DATA
   	int 	m_nHowMany;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CooP)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeCid1();
	afx_msg void OnSelchangeCid2();
	afx_msg void OnSelchangeCid3();
	afx_msg void OnSelchangeCid4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
