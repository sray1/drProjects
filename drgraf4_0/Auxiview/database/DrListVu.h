// DrListVu.h: interface for the CDrListVu class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _DRLISTVU_H
#define _DRLISTVU_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <afxcview.h>



class CDrListVu : public CListView  
{
public:
	CDrListVu();
	virtual ~CDrListVu();

	DECLARE_DYNCREATE(CDrListVu)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrListVu)
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
	//{{AFX_MSG(CDrListVu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif 

