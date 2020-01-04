// dlg_cirC.h : header file
//
#ifndef _ELG_CNO3_H
#define _ELG_CNO3_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CElg_CNO3 dialog

class CElg_CNO3 : public CDialog
{
// Construction
public:
	CElg_CNO3(CDrCurve* pDrCurve, CWnd* pParent = NULL);	// standard constructor

	
protected:
	

	void	Init();
	void	FillListAllString_Select();
	/////////////////
	void 	EmptyListAllString();
	void 	FillListAllString_Pool();
	void 	FillListAllString_Curve();
	int 	SetInfoForDataBase(CDrCurve* pDrObject);
   /////////////////////////////////////////////
	int		SetAdditionalInfo(CDrCurve* pDrCurve, double* pTheta);
	int 	SetUpINodes(CDListMgr* pList,pWORLD inData,int nData);
	int 	Calc_C_R_Normal(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal);
	double 	Calc_CentralAngles(pWORLD Data, WORLD Center, double Radius);
	

protected: 

	CBitmapButton buttonOK,buttonCancel;


public:
// Dialog Data
	//{{AFX_DATA(CElg_CNO3)
	enum { IDD = IDD_CIRC_3NOD_ED };
	CString		m_CurveID;
	double		m_Ratio;
	int			m_nMesh;
	BOOL		m_bClosed;
	double		m_SegAngle;
	BOOL		m_bAutoSeg;
	double		m_dAngSpec;
	//}}AFX_DATA
	BOOL		m_bArc;
	double		m_dAng;
   	int 		m_nHowMany;
	BOOL		m_bUnifOT;
	//////////////////
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////
	CDrCurve*	m_pDrCurve;



// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CElg_CNO3)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClosed();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	afx_msg void OnAngspec();
	afx_msg void OnArc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
