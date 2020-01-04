// dlg_CooP.h : header file
//

#ifndef _SHEET_SOLI_H
#define _SHEET_SOLI_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxdlgs.h>
////////////////////
#include "MSolRsrc.h"
#include "Dlg_SI_EndCond.h"
#include "Dlg_SI_Tensor.h"
#include "Dlg_SI_Xtrude.h"
#include "Dlg_SI_Revolv.h"
#include "Dlg_SI_Loft.h"
#include "Dlg_SI_Duct.h"
#include "Dlg_SI_Sweep.h"
#include "Dlg_SI_Coons.h"
#include "Dlg_SI_Tensor.h"
#include "Dlg_SI_Gordon.h"
/////////////////////////////////////////////////////////////////////////////
// CSheet_SOLI dialog

class AFX_EXT_CLASS CSheet_SOLI : public CPropertySheet
{
	DECLARE_DYNCREATE(CSheet_SOLI)
// Construction
public:
//	CSheet_SOLI(CWnd* pWnd,SOLIDPROC SolProc);	// message filtered to View
	CSheet_SOLI(UINT nIDCaption, CWnd* pWnd,SOLIDPROC SolProc ,UINT iSelectPage = 0);
	CSheet_SOLI(LPCTSTR pszCaption, CWnd* pWnd,SOLIDPROC SolProc, UINT iSelectPage = 0);
	CSheet_SOLI();
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
	//{{AFX_VIRTUAL(CSheet_SOLI)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheet_SOLI();
	


public:
	////////////////////
    CWnd*		m_pWnd;
	SOLIDPROC	m_SolProc;
	/////////////////////


protected:

	BOOL				m_EndCondMode;
	//////////////////////////////////
	CDlg_SI_Xtrude*		m_pXtrudePage;
	CDlg_SI_Revolv*		m_pRevolvPage;
	CDlg_SI_Loft*		m_pLoftPage;
	CDlg_SI_Duct*		m_pDuctPage;
	CDlg_SI_Sweep*		m_pSweepPage;
	CDlg_SI_Coons*		m_pCoonsPage;
	CDlg_SI_Tensor*		m_pTensorPage;
	CDlg_SI_Gordon*		m_pGordonPage;
	CDlg_SI_EndCond*	m_pEndCondPage;


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSheet_SOLI)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
