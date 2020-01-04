// edlabdlg.h : header file
//
#ifndef _EDLAB_DLG_H 
#define _EDLAB_DLG_H   

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "ddlgrsrc.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CEditLabel dialog

class CEditLabel : public CDialog
{
// Construction
public:
	CEditLabel(CWnd* pParent = NULL);	// standard constructor

protected: 
	CBitmapButton buttonCancel;
public:	
// Dialog Data
	//{{AFX_DATA(CEditLabel)
	enum { IDD = IDD_LABEL_EDIT };
	CString	m_EditedLabel;
	//}}AFX_DATA
	CString	m_OldLabel;
	int		m_nLabelIndex;
// Implementation
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support 
	
	void FillListAllString();
	void EmptyListAllString();
	void SetInfoForDataBase(CDrLabel* pLabel);

	// Generated message map functions
	//{{AFX_MSG(CEditLabel)
	virtual void OnOK();
	afx_msg void OnClickedEdit();
	afx_msg void OnClickedDelete();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
