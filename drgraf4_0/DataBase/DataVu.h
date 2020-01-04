#if !defined(AFX_DATAVU_H__FF628E75_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_DATAVU_H__FF628E75_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataVu.h : header file
//


#include "DListMgr.h"
#include "def_sheet.h"
/////////////////////////////////////////////////////////////////////////////
// CDataVu view

class AFX_EXT_CLASS CDataVu : public CView
{
protected:
	CDataVu();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDataVu)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataVu)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	int			Create_SpecificSheet(FORM_SHEET& fsCurrentSheetType,LPCREATESTRUCT lpCreateStruct);
	FORM_SHEET	GetSheetType() {return m_CurrentSheetType; };
	void		SetSheetType(FORM_SHEET fs) { m_CurrentSheetType = fs; };
	CDListMgr*	GetSheetList(){return &m_SheetList;};
	UINT		GetCurrentObjType(){return m_CurrentObjType;};	// stritemType
	void		SetCurrentObjType(UINT u){m_CurrentObjType = u;};	// stritemType
	CString&	GetCurrentstrItem(){return m_CurrentstrItem;};
	void		SetCurrentstrItem(CString& s){m_CurrentstrItem = s;};
	BOOL		IsViewChanged(){return m_bViewChanged;};
	void		SetViewChanged(BOOL b){m_bViewChanged = b;};





protected:
	int			Create_AllSheet(LPCREATESTRUCT lpCreateStruct); 
	int			Create_Sheet(CPropertySheet* pSheet, LPCREATESTRUCT lpCreateStruct); 
	int			ShowCurrentSheet(UINT uCurrentObjType);
	int			HideAllSheet();
	int			UpdateCurrentSheet(CString& strCurrentItem,UINT uCurrentObjType);
//	void	OnSize_CurveSheet(UINT nType, int cx, int cy); 
//	void	OnSize_NodeSheet(UINT nType, int cx, int cy);




protected:
	virtual ~CDataVu();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	

protected:
	FORM_SHEET		m_CurrentSheetType;
	BOOL			m_bSizedBefore;
	CDListMgr		m_SheetList;
	UINT			m_CurrentObjType;	// stritemType
	CString			m_CurrentstrItem;
	BOOL			m_bViewChanged;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataVu)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAVU_H__FF628E75_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
