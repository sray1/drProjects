// dlg_cirr.h : header file
//
#ifndef _DLG_CCLK_H
#define _DLG_CCLK_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "DListMgr.h"
#include "DrCurve.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CClk dialog

class AFX_EXT_CLASS CDlg_CClk : public CDialog
{
// Construction
public:
	CDlg_CClk(CWnd* pParent = NULL);	// standard constructor

	
protected:
	

	/////////////////
	void FillListAllString_Select(CDListMgr* pDListMgr);
	void SetDataBase_BC_N_KNOTs(CDrCurve* pDrObject);


protected: 

	CBitmapButton buttonOK,buttonCancel;


public:
// Dialog Data
	//{{AFX_DATA(CDlg_CClk)
	enum { IDD = IDD_CURV_CLKIN };
	BOOL		m_bAutoKn;
	BOOL		m_bAutoWt;
	CString		m_strBCL;
	CString		m_strBCR;
	CString		m_strDegree;
	BOOL		m_bUnifKN;
	BOOL		m_bUnifWT;
	CString		m_strKN;			// knot Options
	BOOL		m_bRightOn;
	BOOL		m_bLeftOn;
	CString		m_CurveID;
	//}}AFX_DATA
	int			m_nOrder;			// k
   	BOUNDARY	m_BCL;
   	BOUNDARY	m_BCR;
	WORLD		m_TanL;
	WORLD		m_TanR;
	KNOT		m_Typ_KN;
	WEIGHT		m_Typ_WT;
	/////////////////////
	pDOUBLE		m_pKVal;
	pDOUBLE		m_pWVal;
	//////////////////////////// Nodes already Picked All
	CDrCurve*	m_pDrCurve;
	CDListMgr*	m_pNodeSelList;
	//////////////////////////// Part Click & Part Dlg !!!!
	CList<int,int>*	m_pElSegList;


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CClk)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutoKn();
	afx_msg void OnAutoWt();
	afx_msg void OnNonuKn();
	afx_msg void OnNonuWt();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnUnifKn();
	afx_msg void OnUnifWt();
	afx_msg void OnSelchangeBcLeft();
	afx_msg void OnSelchangeBcRight();
	afx_msg void OnSelchangeDegree();
	afx_msg void OnBcLeftOn();
	afx_msg void OnBcRightOn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
