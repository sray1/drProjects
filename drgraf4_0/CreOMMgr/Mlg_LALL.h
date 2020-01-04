// Dlg_LMTR.h : header file
//
#ifndef _MLG_LALL_H
#define _MLG_LALL_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_LALL dialog

class AFX_EXT_CLASS CMlg_LALL : public CDialog
{
// Construction
public:
	CMlg_LALL(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;



public:

// Dialog Data
	//{{AFX_DATA(CMlg_LALL)
	enum { IDD = IDD_XFORM_ALL };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	double	m_TranX;
	double	m_TranY;
	double	m_TranZ;
	CString	m_TranPtID;
	BOOL	m_bAngleIn;
	BOOL	m_bCoordIn;
	double	m_ScaleX;
	double	m_ScaleY;
	double	m_ScaleZ;
	CString	m_strUnit;
	CString	m_RotPtID;
	double	m_ShearX;
	double	m_ShearY;
	double	m_ShearZ;
	CString	m_FromID_R;
	CString	m_FromID_T;
	CString	m_ToID_R;
	CString	m_ToID_T;
	BOOL	m_bOrigin;
	//}}AFX_DATA
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
	BOOL		m_bNoRot;
	BOOL		m_bNoScale;
	BOOL		m_bNoShear;
	BOOL		m_bNoTran;
	//////////////////////
	WORLD		m_wRotPt;
	WORLD		m_wFrom_R;
	WORLD		m_wTo_R;
	WORLD		m_wFrom_T;
	WORLD		m_wTo_T;
	//////////////////////
	UINT		m_IGenType;	// NODE,CURVE,PATCH etc


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_LALL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int		FillListAllString(UINT DlgItemID,CString& IstID);
	void	ShowTranslations(); 
	void	ShowRotations(); 
	void	SetUpLocalm(pMATRIX pM);
	int		CalcRotationFromFromTo(); 
	void	SetCoords_Ref_N_Target(); 



	// Generated message map functions
	//{{AFX_MSG(CMlg_LALL)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTranPt();
	afx_msg void OnAngleInput();
	afx_msg void OnSelchangeCnodeFrom_R();
	afx_msg void OnSelchangeCnodeTo_R();
	afx_msg void OnSelchangeCnodeFrom_T();
	afx_msg void OnSelchangeCnodeTo_T();
	afx_msg void OnCoordInput();
	afx_msg void OnSelchangeRotpt();
	afx_msg void OnOrigin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
