// NodeProp.h : header file
//
#ifndef _DLG_ENOD_H
#define _DLG_ENOD_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "MMs0Rsrc.h"

#include "DrNode.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_ENod dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDlg_ENod : public CDialog
{
// Construction
public:
	CDlg_ENod(CWnd* pParent = NULL);	// standard constructor 
	void	SetInfoForDataBase(CDrNode* pNode,BOOL bGen);
	void	SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel);
	void	Init_NodeData();
	
protected:
	
	void	FillOthers(int i);
	void	SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView); 

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_ENod)
	enum { IDD = IDD_NODE_EDIT_SIMPLE };
	CString	m_id;
	double	m_xWorld;
	double	m_yWorld;
	double	m_zWorld;
	CString	m_bla;
	//}}AFX_DATA
	CDrNode*	m_pDrNode;	
	BOOL		m_bnid_c;
	int 		m_nActiveViewNumber;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_ENod)
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
