// PlatProp.h : header file
//
#ifndef _DLG_FE2D_H_
#define _DLG_FE2D_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mdlgrsrc.h"

#include "DrFE2D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_FE2D dialog
/////////////////////////////////////////////////////////////////////////////
class CDlg_FE2D : public CDialog
{
// Construction
public:
	CDlg_FE2D(CWnd* pParent = NULL);	// standard constructor
	void FillListAllNodeIDs(int IorJ);
	void EmptyListAllString();
	void FillListAllString();
	void FillOthers(int i);
	void UpdateCurrentPlat();
	void SetInfoForDataBase(CDrPlat* pPlat);

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_FE2D)
	enum { IDD = IDD_ELP_PLATE };
	CString	m_matID;
	CString	m_nid_I;
	CString	m_nid_J;
	CString	m_nid_K;
	CString	m_nid_L;
	CString	m_propID;
	CString	m_rid_I;
	CString	m_rid_J;
	CString	m_rid_K;
	CString	m_rid_L;
	CString	m_PlateType;
	float	m_RefTemp;
	float	m_Thk;
	BOOL	m_bDispMode;
	CString	m_SPRid;
	CString	m_lid;
	//}}AFX_DATA
   	int 	m_nHowMany;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_FE2D)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedAdd();
	afx_msg void OnClickedDel();
	afx_msg void OnClickedEdit();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	afx_msg void OnDispMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
