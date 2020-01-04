// drawbox.h : header file
//
#ifndef _DLG_LAYR_H
#define _DLG_LAYR_H  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawLayer dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrawLayer : public CDialog
{
// Construction
public:
	CDrawLayer(CWnd* pParent = NULL);	// standard constructor
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
	void OnLayer();
	void FillListAllString();
	void EmptyListAllString();
	void ReFillListAllString(UINT nType);
	void ReFillListString(UINT i,UINT nType);

// Dialog Data
	//{{AFX_DATA(CDrawLayer)
	enum { IDD = IDD_LAYER };
	CString	m_szDrawList;
	//}}AFX_DATA

// Implementation 
public:
//	CString GetLayerInfo(UINT i,BOOL bActive,BOOL bCurrent);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDrawLayer)
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

