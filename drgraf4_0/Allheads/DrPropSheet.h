#if !defined(AFX_CDrPropSheet_H__3AE81D02_73B9_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CDrPropSheet_H__3AE81D02_73B9_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDrPropSheet.h : header file
//

#include "Def_Sheet.h"
/////////////////////////////////////////////////////////////////////////////
// CDrPropSheet

class CDrPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDrPropSheet)

// Construction
public:
	CDrPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDrPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDrPropSheet();
// Attributes
public:
	virtual int	UpdateSheet(CString& /*strItem*/){return (int)NULL;};

// Operations
public:
	FORM_SHEET&	GetSheetType(){return m_fsSheetType;}; 
	void		SetSheetType(FORM_SHEET& fs){m_fsSheetType = fs;}; 
	UINT&		GetObjType(){return m_uObjType;}; 
	void		SetObjType(UINT& u){m_uObjType = u;}; 
	CString&	GetstrItem(){return m_strItem;};
	void		SetstrItem(CString& s){m_strItem = s;};
	////////////////////////
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrPropSheet)
	//}}AFX_VIRTUAL


protected:

	CString			m_strItem;
	FORM_SHEET		m_fsSheetType;
	UINT			m_uObjType;
	CPropertyPage*	m_pActivePage;


// Implementation
public:
	virtual ~CDrPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDrPropSheet_H__3AE81D02_73B9_11D2_8B46_444553540000__INCLUDED_)
