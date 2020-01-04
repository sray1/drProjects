// dlg_cmes.h : header file
//
#ifndef _DLG_CMES_H
#define _DLG_CMES_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_CMesh dialog

class CDlg_CMesh : public CDialog
{
// Construction
public:
	CDlg_CMesh(CWnd* pParent = NULL);	// standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_CMesh)
	enum { IDD = IDD_C_MESH };
	int			m_nMaxOSeg;
	//}}AFX_DATA
	/////////////////////
	BOOL		m_bUnifOT;			// Uniform Segmentwise
	BOOL		m_bUnifTOT;			// Uniform on Total Length
	int			m_nUnifTOT;			// #ofElements on Total Length
	int			m_nDefOSeg;
	CDrCurve*	m_pDrCurve;
	int			m_nSeg_DT;			// L = nData-1
	pINT		m_pOSeg;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_CMesh)
	virtual BOOL OnInitDialog();
	afx_msg void OnNonuOt();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnKillfocusEloutUnif();
	afx_msg void OnUnifOt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
