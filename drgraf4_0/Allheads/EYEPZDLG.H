// drawbox.h : header file
//
#ifndef _EYEPOSN
#define _EYEPOSN  

#include "stdafx.h"
#include "axis.h"
#include "prism.h"

#include "xform.h"
#include "resource.h"
#include "paredit.h"
#include "spin.h"  
#include "res\otherids.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawEyePosition dialog
/////////////////////////////////////////////////////////////////////////////
class CDrawEyePosition : public CDialog
{
// Construction
public:
	CDrawEyePosition(CWnd* pParent = NULL);	// standard constructor
protected: 
	CBitmapButton buttonOK,buttonCancel;
	CParsedEdit CPEditTilt;
	CParsedEdit CPEditRotation;
	CParsedEdit CPEditIncrement; 
	
public:

// Dialog Data
	//{{AFX_DATA(CDrawEyePosition)
	enum { IDD = IDD_EYEPOSITION };
	UINT	m_nIncrement;
	UINT	m_nRotation;
	UINT	m_nTilt;
	//}}AFX_DATA
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
			void DrawSampleAxes(CDC* PtrDC);
			POINT GetCenter(RECT* Rect);
			
//	virtual void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CDrawEyePosition)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
