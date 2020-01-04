// drawbox.h : header file
//
#ifndef _DLG_PATCH_H_
#define _DLG_PATCH_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPatch dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDlgPatch : public CDialog
{
// Construction
public:
	CDlgPatch(CWnd* pParent = NULL);	// standard constructor
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
	void OnPatchMnu();
	void FillListAllString();
	void EmptyListAllString();
	void ReFillListAllString(UINT nType);
	void ReFillListString(UINT i,UINT nType);

// Dialog Data
	//{{AFX_DATA(CDlgPatch)
	enum { IDD = IDD_PATCH };
	CString	m_szDrawList;
	//}}AFX_DATA

// Implementation 
public:
//	CString GetLayerInfo(UINT i,BOOL bActive,BOOL bCurrent);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlgPatch)
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

