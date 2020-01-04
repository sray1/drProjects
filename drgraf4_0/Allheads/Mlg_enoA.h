// NodeProp.h : header file
//
#ifndef _MLG_ENOA_H
#define _MLG_ENOA_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "MditRsrc.h"

#include "DrFE0D.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_ENoA dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMlg_ENoA : public CDialog
{
// Construction
public:
	CMlg_ENoA(CWnd* pParent = NULL);	// standard constructor 
	void	SetInfoForDataBase(CDrFE0D* pNode,BOOL bGen);
	void	SetInfoForNodeLabel(CDrFE0D* pAddNode,CDrLabel* pLabel);
	void	Init_NodeData();
	
protected:
	
	int		ResolveReference_Direction();
	int		ResolveReference_Coords();
	int		UnitAxisFromEndNodes(pWORLD pNormal);
	void	FillListforAllNodeCombos();
	void	EmptyListAllString();
	void	FillListAllString();
	void	FillOthers(int i);
	void	UpdateCurrentNode();
	void	SetCornerInfo(POINT* pCorner,POINT3* pCorner3,int nView); 

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CMlg_ENoA)
	enum { IDD = IDD_NODE_EDIT_ADV };
	CString	m_id;
	CString	m_nid_r;
	CString	m_FromID;
	CString	m_ToID;
	double	m_xWorld;
	double	m_yWorld;
	double	m_zWorld;
	CString	m_strLn;
	CString	m_strDx;
	CString	m_strDy;
	CString	m_strDz;
	//}}AFX_DATA
	double		m_dLength;
	double		m_DxWorld;
	double		m_DyWorld;
	double		m_DzWorld;
	CDrFE0D*	m_pDrNode;	
	BOOL		m_bnid_c;
	int 		m_nActiveViewNumber;
 	BOOL		m_bCoord;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMlg_ENoA)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	afx_msg void OnCoord();
	afx_msg void OnDirection();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnSelchangeNodeNidR();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnOK();
	virtual void OnCancel();
	afx_msg void OnStartOver();
	afx_msg void OnChangeNodeDx();
	afx_msg void OnChangeNodeDy();
	afx_msg void OnChangeNodeDz();
	afx_msg void OnChangeLength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif