// HistVw.h: interface for the CHistVw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTVW_H__B72ECA67_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_HISTVW_H__B72ECA67_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DrawVw.h"

class CHistVw : public CDrawVw  
{
public:
	CHistVw();
	virtual ~CHistVw();

	DECLARE_DYNCREATE(CHistVw)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistVw)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistVw)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif // !defined(AFX_HISTVW_H__B72ECA67_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
