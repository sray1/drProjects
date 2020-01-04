// preciDlg.h : header file
//
#ifndef _DLG_PREC_H_
#define _DLG_PREC_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawPrecision dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrawPrecision : public CDialog
{
// Construction
public:
	CDrawPrecision(CWnd* pParent = NULL);	// standard constructor
	void OnPrecision();
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
// Dialog Data
	//{{AFX_DATA(CDrawPrecision)
	enum { IDD = IDD_PRECISION };
	UINT	m_nDrawPrecision;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDrawPrecision)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

