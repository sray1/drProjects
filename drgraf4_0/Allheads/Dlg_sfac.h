// drawbox.h : header file
//
#ifndef _DLG_SFAC_H_
#define _DLG_SFAC_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawScale dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrawScale : public CDialog
{
// Construction
public:
	CDrawScale(CWnd* pParent = NULL);	// standard constructor
	void OnScalefactor();
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
// Dialog Data
	//{{AFX_DATA(CDrawScale)
	enum { IDD = IDD_SCALE_FACTOR };
	double	m_dScaleFactor;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDrawScale)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

