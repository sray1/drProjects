// dlg_CooP.h : header file
//

#ifndef _SHEET_PATI_H
#define _SHEET_PATI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxdlgs.h>
////////////////////
#include "MPatRsrc.h"
#include "Dlg_PI_EndCond.h"
#include "Dlg_PI_Tensor.h"
#include "Dlg_PI_Xtrude.h"
#include "Dlg_PI_Revolv.h"
#include "Dlg_PI_Loft.h"
#include "Dlg_PI_Duct.h"
#include "Dlg_PI_Sweep.h"
#include "Dlg_PI_Coons.h"
#include "Dlg_PI_Tensor.h"
#include "Dlg_PI_Gordon.h"
/////////////////////////////////////////////////////////////////////////////
// CSheet_PATI dialog

class AFX_EXT_CLASS CSheet_PATI : public CPropertySheet
{
	DECLARE_DYNCREATE(CSheet_PATI)
// Construction
public:
//	CSheet_PATI(CWnd* pWnd,PATCHPROC PatProc);	// message filtered to View
	CSheet_PATI(UINT nIDCaption, CWnd* pWnd,PATCHPROC PatProc ,UINT iSelectPage = 0);
	CSheet_PATI(LPCTSTR pszCaption, CWnd* pWnd,PATCHPROC PatProc, UINT iSelectPage = 0);
	CSheet_PATI();
	//////////////////////////////
    BOOL			Create ();
	int				SetProcPage(); 
	BOOL			IsEndCondMode(){return m_EndCondMode;};
	void			SetEndCondMode(BOOL b){m_EndCondMode = b;};

protected:
// Implementation
	void			ConstructPages(CWnd* pParentWnd);
	HINSTANCE		SetResource();
	void			RestoreResource(HINSTANCE hInstResourceClient);
	void			SizeRectDlgIn(CRect& BoxRect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheet_PATI)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheet_PATI();
	


public:
	////////////////////
    CWnd*		m_pWnd;
	PATCHPROC	m_PatProc;
	/////////////////////


protected:

	BOOL				m_EndCondMode;
	//////////////////////////////////
	CDlg_PI_Xtrude*		m_pXtrudePage;
	CDlg_PI_Revolv*		m_pRevolvPage;
	CDlg_PI_Loft*		m_pLoftPage;
	CDlg_PI_Duct*		m_pDuctPage;
	CDlg_PI_Sweep*		m_pSweepPage;
	CDlg_PI_Coons*		m_pCoonsPage;
	CDlg_PI_Tensor*		m_pTensorPage;
	CDlg_PI_Gordon*		m_pGordonPage;
	CDlg_PI_EndCond*	m_pEndCondPage;


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSheet_PATI)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
