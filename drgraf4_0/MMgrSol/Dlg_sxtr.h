// dlg_xtrd.h : header file
//

#ifndef _DLG_XTRD_S_H
#define _DLG_XTRD_S_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrPatch.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd_S dialog

class CDlg_Xtrd_S : public CDialog
{
// Construction
public:
	CDlg_Xtrd_S(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrSolid* pDrObject);

protected:
	
	void FillListAllSolidIDs();
	void FillListAllNodeIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Xtrd_S)
	enum { IDD = IDD_EXTRUDE_SOLID };
	CString	m_FromID;
	CString	m_ToID;
	double	m_dLen;
	CString	m_CurveID;
	CString	m_PatchID;
	int		m_nMesh;
	double	m_Ratio;
	BOOL	m_bFromCN;
	BOOL	m_bToCN;
	//}}AFX_DATA
   	PATSUBTYPE	m_SubType;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////
	WORLD		m_wLen;
	int			m_nType;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Xtrd_S)
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
