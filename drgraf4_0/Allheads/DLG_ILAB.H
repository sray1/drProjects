// intxtdlg.h : header file
//
#ifndef _INTXTDLG_H 
#define _INTXTDLG_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    

#include "ddlgrsrc.h"
#include "DrLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CInTextDlg dialog

class CInTextDlg : public CDialog
{
// Construction
public:
	CInTextDlg(CWnd* pParent = NULL);	// standard constructor

protected: 
	CBitmapButton buttonOK,buttonCancel;
public:	
// Dialog Data
	//{{AFX_DATA(CInTextDlg)
	enum { IDD = IDD_TEXT_INSERT };
	CString	m_Text;
	int		m_nTextAngle;
	//}}AFX_DATA
	POINT 	m_pt;   // current location
	int		m_nActiveViewNumber; // current View
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support 
	
	void FillListAllString();
	void EmptyListAllString();
	void SetInfoForDataBase(CDrLabel* pLabel);

	// Generated message map functions
	//{{AFX_MSG(CInTextDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeListLabel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
