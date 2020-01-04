// NodeProp.h : header file
//
#ifndef _MLG_ENOD_H
#define _MLG_ENOD_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "MditRsrc.h"

#include "DrFE0D.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_ENod dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMlg_ENod : public CDialog
{
// Construction
public:
	CMlg_ENod(CWnd* pParent = NULL);	// standard constructor 
	void	SetInfoForDataBase(CDrFE0D* pNode,BOOL bGen);
	void	SetInfoForNodeLabel(CDrFE0D* pAddNode,CDrLabel* pLabel);
	void	Init_NodeData();
	
protected:
	
	void	FillOthers(int i);
	void	SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView); 

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CMlg_ENod)
	enum { IDD = IDD_NODE_EDIT_SIMPLE };
	CString	m_id;
	double	m_xWorld;
	double	m_yWorld;
	double	m_zWorld;
	CString	m_bla;
	//}}AFX_DATA
	CDrFE0D*	m_pDrNode;	
	BOOL		m_bnid_c;
	int 		m_nActiveViewNumber;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMlg_ENod)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnOK();
	virtual void OnCancel();
	afx_msg void OnStartOver();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
