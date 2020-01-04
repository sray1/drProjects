// NodeProp.h : header file
//
#ifndef _DLGNODE_H
#define _DLGNODE_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "stdafx.h"

#include "glb_Objs.h"
/////////////////////
#include "Mdlgrsrc.h"

#include "DrNode.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Node dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDlg_Node : public CDialog
{
// Construction
public:
	CDlg_Node(CWnd* pParent = NULL);	// standard constructor 
	void	SetInfoForDataBase(CDrNode* pNode,BOOL bGen);
	void	SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel);
	
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
	//{{AFX_DATA(CDlg_Node)
	enum { IDD = IDD_ELP_NODE };
	CString	m_id;
	CString	m_nid_r;
	CString	m_sup_id;
	CString	m_load_id;
	CString	m_FromID;
	CString	m_ToID;
	double	m_dLength;
	double	m_xWorld;
	double	m_yWorld;
	double	m_zWorld;
	double	m_DxWorld;
	double	m_DyWorld;
	double	m_DzWorld;
	//}}AFX_DATA
	BOOL	m_bnid_c;
	int 	m_nActiveViewNumber;
   	LPOINT3 m_MouseWIC;
   	CString m_CurrentNodeID;
   	int 	m_nHowMany;
   	int 	m_nCreated;
 	BOOL	m_bCoord;
  	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_Node)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedAdd();
	afx_msg void OnClickedDel();
	afx_msg void OnClickedEdit();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	afx_msg void OnKillfocusNodeNidR();
	afx_msg void OnKillfocusNodeSupId();
	afx_msg void OnKillfocusNodeId();
	afx_msg void OnCoord();
	afx_msg void OnDirection();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnKillfocusLength();
	afx_msg void OnSelchangeNodeNidR();
	afx_msg void OnKillfocusNodeDx();
	afx_msg void OnKillfocusNodeDy();
	afx_msg void OnKillfocusNodeDz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
