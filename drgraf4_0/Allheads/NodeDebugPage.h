#if !defined(AFX_CNodeDebugPage_H__DD65B042_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeDebugPage_H__DD65B042_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeDebugPage.h : header file
//

#include "DrNode.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeDebugPage dialog

class CNodeDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeDebugPage)

// Construction
public:
	CNodeDebugPage();
	~CNodeDebugPage();

// Dialog Data
	//{{AFX_DATA(CNodeDebugPage)
	enum { IDD = IDD_NODE_DEBUG };
	double	m_LocalPos_X;
	double	m_LocalPos_Y;
	double	m_LocalPos_Z;
	int		m_Pt_X;
	int		m_Pt_Y;
	int		m_Normal2D_X;
	int		m_Normal2D_Y;
	double	m_NormalWorld_X;
	double	m_NormalWorld_Y;
	double	m_NormalWorld_Z;
	double	m_EyePosX;
	double	m_EyePosY;
	double	m_EyePosZ;
	double	m_ScreenPos3DX;
	double	m_ScreenPos3DY;
	double	m_ScreenPos3DZ;
	double	m_WorldPosX;
	double	m_WorldPosY;
	double	m_WorldPosZ;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
	int		UpdateInfo(CDrNode* pNode);



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;




// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeDebugPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeDebugPage_H__DD65B042_7096_11D2_8B46_444553540000__INCLUDED_)
