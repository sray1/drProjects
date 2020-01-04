// SpecVw.h: interface for the CSpecVw class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SPECVW_H
#define _SPECVW_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DrawVw.h"

class CSpecVw : public CDrawVw  
{
public:
	CSpecVw();
	virtual ~CSpecVw();

	DECLARE_DYNCREATE(CSpecVw)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecVw)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpecVw)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




#endif 
