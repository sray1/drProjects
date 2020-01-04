// dlg_ppos.h : header file
//
#ifndef _DLG_PPOST_H
#define _DLG_PPOST_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PPost dialog

class CDlg_PPost : public CDialog
{
// Construction
public:
	CDlg_PPost(CWnd* pParent = NULL);	// standard constructor
	void 		SetInfoForDataBase(CDrPatch* pDrObject);

protected: 

	CBitmapButton 	buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_PPost)
	enum { IDD = IDD_POST_PATCH };
	CString		m_Dirty;
	CString		m_Elem;
	CString		m_Orient;
	CString		m_SubDiv;
	BOOL		m_bRend;
	CString		m_PID_Post;
	BOOL		m_bIdentity;
	//}}AFX_DATA
   	ORIENT		m_OrientKind;	 
   	SUBDIV		m_SubDivKind;	 
	/////////////////////////// Transformation
	int			m_nType;	// input type
	CMatObj*	m_pMatObj;
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
	/////////////////////////// Rendition
	RENDINFO	m_RI;
	/////////////////
/*	
	double		m_Absorp;
	BOOL		m_bAmb;
	BOOL		m_bCull;
	double		m_Diff_Coef;
	BOOL		m_bDist;
	BOOL		m_bFrame;
	BOOL		m_bHazing;
	BOOL		m_bLight;
	double		m_Refr_Coef;
	BOOL		m_bShadow;
	int			m_SpecIndex;
	double		m_Spec_Coef;
	double		m_Transm_Coef;
	BOOL		m_bTurbul;
	BOOL		m_bWireF;
	COLORREF	m_crColor_Ambi;
	COLORREF	m_crColor_Fram;
	COLORREF	m_crColor_Refl;
*/	
	/////////////////////////// 
	

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
	void		FillPatchListAllString();   // only with DirtyPatch
	void		FillListAllString_Pool();
	void		FillElemListAllString();   // only with 1D or 2D Elems
	void 		EmptyListAllString();

	// Generated message map functions
	//{{AFX_MSG(CDlg_PPost)
	virtual BOOL OnInitDialog();
	afx_msg void OnSymm();
	afx_msg void OnXform();
	afx_msg void OnRendinfo();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeOrient();
	afx_msg void OnSelchangeSubdiv();
	afx_msg void OnSelchangeFems();
	afx_msg void OnDefaultLmat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
