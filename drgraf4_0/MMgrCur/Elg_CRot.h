// dlg_rotp.h : header file
//
#ifndef _ELG_CROT_H
#define _ELG_CROT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CElg_CRot dialog

class CElg_CRot : public CDialog
{
// Construction
public:
	CElg_CRot(CWnd* pParent = NULL);	// standard constructor

protected:
	
	int		SetInfoForDataBase(CDrCurve* pDrObject);
	void	FillListAllCurveIDs();
	void	FillListAllNodeIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CElg_CRot)
	enum { IDD = IDD_CIRC_ROTA_ED };
	double	m_dAng;
	CString	m_FromID;
	CString	m_ToID;
	CString	m_NodeID;
	double	m_Ratio;
	int		m_nMesh;
	CString	m_CurveID;
	int		m_SegAngle;
	BOOL	m_bAutoSeg;
	//}}AFX_DATA
//	double	m_SegAngle;
   	int 	m_nHowMany;
	BOOL	m_bUnifOT;
	//////////////////
	pINT	m_pOSeg;
	pDOUBLE	m_pODis;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CElg_CRot)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
