// Dlg_CurI.h : header file
//
#ifndef _DLG_STLI_H
#define _DLG_STLI_H


#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "Def_Supp.h"	// for Joint Coords
#include "Def_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_StLI dialog

class AFX_EXT_CLASS CDlg_StLI : public CDialog
{
// Construction
public:
	CDlg_StLI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();
	////
	void	Get_Values_Uniform(); 

// Dialog Data
	//{{AFX_DATA(CDlg_StLI)
	enum { IDD = IDD_STATIC_IN };
	CString	m_LoadID;
	BOOL	m_bTx;
	BOOL	m_bTy;
	BOOL	m_bTz;
	BOOL	m_bRx;
	BOOL	m_bRy;
	BOOL	m_bRz;
	BOOL	m_bUniform;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	STALPROC	m_StaLProc;
	////////////////////////
	BOOL		m_bConOrDis;
	BOOL		m_bIso;
	/////////////////////// NonIso
	BOOL		m_bNonIso;
	CString		m_CID;
	BOOL		m_bIncrement;
	CString		m_Orient;
	double		m_dScale;
	double		m_dStep;
	double		m_dStart;
	///////////////////////
	UINT		m_GenKind;	// Node,Curve,Patch,Solid etc
	CDrNode*	m_pDrNode;	// Base Node for which StaticLoad is needed
	CDrCurve*	m_pDrCurve;	// Base Curve for which StaticLoad is needed
	CDrPatch*	m_pDrPatch;	// Base Patch for which StaticLoad is needed
	CDrPatch*	m_pDrSolid;	// Base Solid for which StaticLoad is needed
	CATEGORY	m_Category;	// Force/Moment/Disp/Rot/Pres/Therm/LupWt etc
	/////////////////////////////////////////////////
	pDOUBLE		m_dUnif;
	/////////////////////////////////////////////////
	JOINTCOORD  m_jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_I_TAN_PATCH,
								//	JC_Z_NOR_PATCH




protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_StLI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_StLI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	virtual void OnCancel();
	afx_msg void OnNonIso();
	afx_msg void OnIsoparConc();
	afx_msg void OnIsoparDistrib();
	afx_msg void OnSelchangeComboJctype();
	afx_msg void OnUniform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
