// dlg_cirr.h : header file
//
#ifndef _ELG_LQC_H
#define _ELG_LQC_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CElg_LQC dialog

class AFX_EXT_CLASS CElg_LQC : public CDialog
{
// Construction
public:
	CElg_LQC(CWnd* pParent = NULL);	// standard constructor

	
protected:
	

	/////////////////
	void EmptyListAllString();
	void FillListAllString_Pool();
	void FillListAllString_Curve();
	void SetInfoForDataBase(CDrCurve* pDrObject);


protected: 

	CBitmapButton buttonOK,buttonCancel;


public:
// Dialog Data
	//{{AFX_DATA(CElg_LQC)
	enum { IDD = IDD_LQC_ED };
	BOOL		m_bAutoKn;
	BOOL		m_bAutoWt;
	CString		m_strBCL;
	CString		m_strBCR;
	int			m_nControls;		// L + k - 1 = nData + k - 2 = n + 1 (B-Spline)
	int			m_nCurveSeg;		// L 	= nData - 1	, Open
	CString		m_strDegree;
	BOOL		m_bUnifKN;
	BOOL		m_bUnifWT;
	CString		m_strKN;			// knot Options
	BOOL		m_bClosed;
	BOOL		m_bRightOn;
	BOOL		m_bLeftOn;
	CString		m_CurveID;
	//}}AFX_DATA
	double		m_Ratio;
	int			m_nMaxOSeg;
   	int 		m_nHowMany;
	int			m_nOrder;			// k
   	BOUNDARY	m_BCL;
   	BOUNDARY	m_BCR;
	WORLD		m_TanL;
	WORLD		m_TanR;
	BOOL		m_bUnifOT;
	int			m_nMaxDistinct;		// n - k + 3 = nData				Knots, Weights
	int			m_nMaxTotal;		// n + k + 1 = nData + (2k - 2)		Knots, Weights
	KNOT		m_Typ_KN;
	WEIGHT		m_Typ_WT;
	/////////////////////
	pDOUBLE		m_pKVal;
	pDOUBLE		m_pWVal;
	pINT		m_pOSeg;
	pDOUBLE		m_pODis;
	////////////////////
	CURVEPROC	m_CurveType;



// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CElg_LQC)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutoKn();
	afx_msg void OnAutoWt();
	afx_msg void OnNonuKn();
	afx_msg void OnNonuWt();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnUnifKn();
	afx_msg void OnUnifWt();
	afx_msg void OnSelchangeBcLeft();
	afx_msg void OnSelchangeBcRight();
	afx_msg void OnSelchangeDegree();
	afx_msg void OnClosed();
	afx_msg void OnBcLeftOn();
	afx_msg void OnBcRightOn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
