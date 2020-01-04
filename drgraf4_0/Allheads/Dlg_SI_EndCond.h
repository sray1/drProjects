#if !defined(AFX_DLG_SI_ENDCOND_H__491FCC61_C71F_11D2_8B46_444553540000__INCLUDED_)
#define AFX_DLG_SI_ENDCOND_H__491FCC61_C71F_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_EndTan.h : header file
//

#include "MSolRsrc.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_EndCond dialog

class CDlg_SI_EndCond : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_EndCond)

// Construction
public:
	CDlg_SI_EndCond();   // standard constructor
	CDlg_SI_EndCond(CWnd* pParentWnd,SOLIDPROC SolProc);
	virtual void	ResetDlg();
	virtual void	ResetDlgForTwist();
	virtual void	ResetDlgForEdit();



protected:
	
	void	FillBndryNodeIDCombo(CList<CString,CString>& BndryList);
	void	FillOthers(int index,CList<BLENDEND,BLENDEND>* pEndList);
	void	SetIsoDir();
	void	SetNodeIDs();
	int		GetIndexJ(int indexI, BOOL bU);
	void	SetIendJendBoolText();
	void	SetEndListIndex();
	void	BuildBndryNodeList();
	void	SetIendJendCombos();
	void	UpdateDataBase_BC(int nNodeIndex,CList<BLENDEND,BLENDEND>* pEndList);
	void	UpdateDataBase_Twist();
	

public:

// Dialog Data
	//{{AFX_DATA(CDlg_SI_EndCond)
	enum { IDD = IDD_SOL_IN_ENDCOND };
	CString		m_strBCL;
	CString		m_strBCR;
	BOOL		m_bRightOn;
	BOOL		m_bLeftOn;
	CString		m_strDir;
	CString		m_NodeID;
	CString		m_strTwist;
	BOOL		m_bDefault;
	//}}AFX_DATA
	


protected:


	int			m_indexEnd;			// index for EndList to save Data	
	CString		m_NodeID_I;
	CString		m_NodeID_J;
	/////////////////////////////////////////////////
   	BOUNDARY	m_BCL;
   	BOUNDARY	m_BCR;
	WORLD		m_TanL;
	WORLD		m_TanR;
	TWIST		m_Twist;	// corner Twist	
	///////////////////////////////////////
	CList<CString,CString>
				m_BndryList_U;
	CList<CString,CString>
				m_BndryList_V;
	int			m_CornerIndex[2][2];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SI_EndCond)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_EndCond)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBlend();
	afx_msg void OnSelchangeBcLeft();
	afx_msg void OnSelchangeBcRight();
	afx_msg void OnBcLeftOn();
	afx_msg void OnBcRightOn();
	afx_msg void OnSelchangeComboNode();
	afx_msg void OnSelchangeComboDir();
	afx_msg void OnSelchangeComboTwist();
	afx_msg void OnDefault();
	afx_msg void OnAllSame();
	afx_msg void OnUpdate();
	afx_msg void OnEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ENDCOND_H__491FCC61_C71F_11D2_8B46_444553540000__INCLUDED_)
