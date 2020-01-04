// dlg_loft.h : header file
//

#ifndef _DLG_LOFT2_H
#define _DLG_LOFT2_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft2 dialog

class CDlg_Loft2 : public CDialog
{
// Construction
public:
	CDlg_Loft2(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrPatch* pDrObject);

protected:
	
	void FillListAllCurveIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Loft2)
	enum { IDD = IDD_LOFT2_PATCH };
	CString	m_PatchID;
	int		m_nMesh;
	double	m_Ratio;
	CString	m_CID_1;
	CString	m_CID_2;
	CString	m_Orient_1;
	CString	m_Orient_2;
	//}}AFX_DATA
   	int 		m_nHowMany;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Loft2)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
