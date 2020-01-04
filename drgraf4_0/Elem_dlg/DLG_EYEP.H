// Dlg_eyeP.h : header file
//
#ifndef _DLG_EYEP_H_
#define _DLG_EYEP_H_  

#include "3dlgrsrc.h"
#include "paredit.h"
#include "spin.h"  
/////////////////////////////////////////////////////////////////////////////
// CEyePosition dialog
/////////////////////////////////////////////////////////////////////////////
class CEyePosition : public CDialog
{
// Construction
public:
	CEyePosition(CWnd* pParent = NULL);	// standard constructor
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
	//{{AFX_MSG(CEyePosition)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
