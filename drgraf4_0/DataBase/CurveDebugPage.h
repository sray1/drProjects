#if !defined(AFX_CURVEDEBUGPAGE_H__AA812A70_7244_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CURVEDEBUGPAGE_H__AA812A70_7244_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurveDebugPage.h : header file
//

#include "DbRsrc.h"
#include "DrCurve.h"
#include "Def_CuPs.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveDebugPage dialog

class CCurveDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveDebugPage)

// Construction
public:
	CCurveDebugPage();
	~CCurveDebugPage();

// Dialog Data
	//{{AFX_DATA(CCurveDebugPage)
	enum { IDD = IDD_CURVE_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);
	int		UpdateInfo(CDrCurve* pCurve);


protected:

	int		UpdateInfoCurve(CDrCurve* pCurve);
	int		UpdateInfoCircle(CDrCurve* pCurve);
	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	int		UpdateCombo_Double(pDOUBLE pAng, int nAngs, UINT DlgComboID);
	int		UpdateCombo_Int(pINT pElem, int nEls, UINT DlgComboID);



protected:

	CDrCurve*	m_pCurrentCurve;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDEBUGPAGE_H__AA812A70_7244_11D2_8B46_444553540000__INCLUDED_)
