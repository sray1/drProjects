// drawbox.h : header file
//
#ifndef _DLG_OBJ3D_H_
#define _DLG_OBJ3D_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgObj3D dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDlgObj3D : public CDialog
{
// Construction
public:
	CDlgObj3D(CWnd* pParent = NULL);	// standard constructor
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
	void OnObj3DMnu();
	void FillListAllString();
	void EmptyListAllString();
	void ReFillListAllString(UINT nType);
	void ReFillListString(UINT i,UINT nType);

// Dialog Data
	//{{AFX_DATA(CDlgObj3D)
	enum { IDD = IDD_OBJ3D };
	CString	m_szDrawList;
	//}}AFX_DATA

// Implementation 
public:
//	CString GetLayerInfo(UINT i,BOOL bActive,BOOL bCurrent);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlgObj3D)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedDrawAllactive();
	afx_msg void OnClickedToggleAll();
	afx_msg void OnClickedChange();
	afx_msg void OnClickedCurrent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

