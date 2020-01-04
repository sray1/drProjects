// dlg_loft.h : header file
//

#ifndef _DLG_LOFT_S_H
#define _DLG_LOFT_S_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrPatch.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft_S dialog

class CDlg_Loft_S : public CDialog
{
// Construction
public:
	CDlg_Loft_S(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrSolid* pDrObject);

protected:
	
	void FillListAllSolidIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Loft_S)
	enum { IDD = IDD_LOFT_SOLID };
	CString	m_PatchID;
	int		m_nMesh;
	double	m_Ratio;
	CString	m_CID_1;
	CString	m_CID_2;
	int		m_TotEl_1;
	int		m_TotEl_2;
	//}}AFX_DATA
   	PATSUBTYPE	m_SubType;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Loft_S)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCid1();
	afx_msg void OnSelchangeCid2();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
