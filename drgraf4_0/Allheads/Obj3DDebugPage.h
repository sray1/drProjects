#if !defined(AFX_OBJ3DDEBUGPAGE_H__F1213086_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_OBJ3DDEBUGPAGE_H__F1213086_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Obj3DDebugPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CObj3DDebugPage dialog

class CObj3DDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CObj3DDebugPage)

// Construction
public:
	CObj3DDebugPage();
	~CObj3DDebugPage();

// Dialog Data
	//{{AFX_DATA(CObj3DDebugPage)
	enum { IDD = IDD_OBJ3D_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
//	int		UpdateCoords(CDrNode* pNode);



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CObj3DDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CObj3DDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJ3DDEBUGPAGE_H__F1213086_72EF_11D2_8B46_444553540000__INCLUDED_)
