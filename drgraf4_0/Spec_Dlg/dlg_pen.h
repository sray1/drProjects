// pendlg.h : header file
//
#ifndef _DLG_PEN_H_
#define _DLG_PEN_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// Custom Listbox - containing colors

class AFX_EXT_CLASS CColorListBox : public CListBox
{
public:
// Operations
	void AddColorItem(COLORREF color);

// Implementation
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
};
///////////////////////////////////////////////////////////////////
// CPenDlg dialog

class AFX_EXT_CLASS CPenDlg : public CDialog
{
// Construction
public:
	CPenDlg(CWnd* pParent = NULL);	// standard constructor
	void OnPen();
	
// Dialog Data
	//{{AFX_DATA(CPenDlg)
	enum { IDD = IDD_PEN };
	UINT	m_nWidth;
	DWORD	m_PenColor;
	CString	m_StyleName;
	//}}AFX_DATA

protected:
	CBitmapButton 	buttonOK,buttonCancel;
	CColorListBox  	m_colors;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPenDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif
