// dlg_pobj.h : header file
//
#ifndef _DLG_POBJ_H
#define _DLG_POBJ_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PObj dialog

class CDlg_PObj : public CDialog
{
// Construction
public:
	CDlg_PObj(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_PObj)
	enum { IDD = IDD_POST_OBJ3D };
	CString	m_OID_Post;
	BOOL	m_bLMat;
	//}}AFX_DATA
	/////////////////////////// Transformation
	MATRIX		m_LM;
	/////////////////
	double		m_RotX;
	double		m_RotY;
	double		m_RotZ;
	double		m_ScaleX;
	double		m_ScaleY;
	double		m_ScaleZ;
	double		m_TranX;
	double		m_TranY;
	double		m_TranZ;
	CString		m_RotPtID;


// Implementation
protected:

	CBitmapButton 	buttonOK,buttonCancel;
	void			FillListAllString();   // Posted Objects
	void 			EmptyListAllString();
	void 			SetInfoForDataBase(CDrObj3D* pDrObject);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_PObj)
	afx_msg void OnLocalm();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
