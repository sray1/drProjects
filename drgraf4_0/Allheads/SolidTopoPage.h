#if !defined(AFX_SOLID_TOPO_H__F1213069_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SOLID_TOPO_H__F1213069_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Solid_Topo.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidTopoPage dialog

class CSolidTopoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSolidTopoPage)

// Construction
public:
	CSolidTopoPage();
	~CSolidTopoPage();

// Dialog Data
	//{{AFX_DATA(CSolidTopoPage)
	enum { IDD = IDD_SOLID_TOPO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);



protected:

	CDrPatch*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSolidTopoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSolidTopoPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLID_TOPO_H__F1213069_72EF_11D2_8B46_444553540000__INCLUDED_)
