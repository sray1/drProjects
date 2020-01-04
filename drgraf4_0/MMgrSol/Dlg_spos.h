// dlg_ppos.h : header file
//
#ifndef _DLG_SPOST_H
#define _DLG_SPOST_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SPost dialog

class CDlg_SPost : public CDialog
{
// Construction
public:
	CDlg_SPost(CWnd* pParent = NULL);	// standard constructor

protected: 

	CBitmapButton 	buttonOK,buttonCancel;
	void			FillPatchListAllString();   // only with DirtyPatch
	void			FillElemListAllString();   // only with 1D or 2D Elems
	void 			EmptyListAllString();
	void 			SetInfoForDataBase(CDrSolid* pDrObject);

public:

// Dialog Data
	//{{AFX_DATA(CDlg_SPost)
	enum { IDD = IDD_POST_SOLID };
	CString		m_Dirty;
	CString		m_Elem;
	CString		m_Orient;
	CString		m_SubDiv;
	BOOL		m_bLMat;
	BOOL		m_bRend;
	CString		m_PID_Post;
	//}}AFX_DATA
   	ORIENT		m_OrientKind;	 
   	SUBDIV		m_SubDivKind;	 
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

	// Generated message map functions
	//{{AFX_MSG(CDlg_SPost)
	virtual BOOL OnInitDialog();
	afx_msg void OnLocalm();
	afx_msg void OnRendinfo();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeOrient();
	afx_msg void OnSelchangeSubdiv();
	afx_msg void OnSelchangeFems();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
