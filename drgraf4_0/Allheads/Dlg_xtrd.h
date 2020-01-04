// dlg_xtrd.h : header file
//

#ifndef _DLG_XTRD_H
#define _DLG_XTRD_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd dialog

class CDlg_Xtrd : public CDialog
{
// Construction
public:
	CDlg_Xtrd(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrPatch* pDrObject);

protected:
	
	void FillListAllCurveIDs();
	void FillListAllNodeIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Xtrd)
	enum { IDD = IDD_EXTRUDE_PATCH };
	CString	m_FromID;
	CString	m_ToID;
	double	m_dLen;
	WORLD	m_wLen;
	CString	m_CurveID;
	CString	m_PatchID;
	int		m_nMesh;
	double	m_Ratio;
	CString	m_Orient_1;
	BOOL	m_bFromCN;
	BOOL	m_bToCN;
	//}}AFX_DATA
   	int 		m_nHowMany;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////
	int			m_nType;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Xtrd)
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
