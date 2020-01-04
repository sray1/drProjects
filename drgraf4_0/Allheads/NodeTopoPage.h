#if !defined(AFX_NODETOPOPAGE_H__F36D6F61_754E_11D2_8B46_444553540000__INCLUDED_)
#define AFX_NODETOPOPAGE_H__F36D6F61_754E_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NodeTopoPage.h : header file
//

#include "DrNode.h"
#include "DrFE0D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeTopoPage dialog

class CNodeTopoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeTopoPage)

// Construction
public:
	CNodeTopoPage();
	~CNodeTopoPage();

// Dialog Data
	//{{AFX_DATA(CNodeTopoPage)
	enum { IDD = IDD_NODE_TOPO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeTopoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeTopoPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODETOPOPAGE_H__F36D6F61_754E_11D2_8B46_444553540000__INCLUDED_)
