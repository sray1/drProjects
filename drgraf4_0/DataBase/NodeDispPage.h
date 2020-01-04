#if !defined(AFX_CNodeDispPage_H__DD65B043_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeDispPage_H__DD65B043_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeDispPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeDispPage dialog

class CNodeDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeDispPage)

// Construction
public:
	CNodeDispPage();
	~CNodeDispPage();

// Dialog Data
	//{{AFX_DATA(CNodeDispPage)
	enum { IDD = IDD_NODE_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
	int		UpdateCoords(CDrNode* pNode);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeDispPage_H__DD65B043_7096_11D2_8B46_444553540000__INCLUDED_)
