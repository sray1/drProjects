#if !defined(AFX_SASEPAGE_H__C4D67362_C187_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SASEPAGE_H__C4D67362_C187_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BasePage.h : header file
//

#include <afxtempl.h>	// CList
#include "Def_CuPS.h"
#include "Str_BlendEnd.h"
#include "DListMgr.h"
/////////////////////////////////////////////////////////////////////////////
// CSasePage dialog

class CSasePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSasePage)

// Construction
public:
	CSasePage(CWnd* pMainWnd, SOLIDPROC PatProc, UINT nIDTemplate, UINT nIDCaption = 0);
	CSasePage(CWnd* pMainWnd, SOLIDPROC PatProc, LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
	CSasePage();
	~CSasePage();
//
	virtual void	ResetDlg(){return;};
	virtual void	ResetDlgForTwist(){return;};
	virtual void	ResetDlgForEdit(){return;};



// Dialog Data
	//{{AFX_DATA(CSasePage)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	CString	m_SID;
	CString	m_PID;
	CString	m_CID;
	CString	m_NID;
	int		m_nMesh;
	double	m_Ratio;
	BOOL	m_bClosed;
	double	m_SegAngle;
	BOOL	m_bAutoSeg;
//	CString	m_Orient;
	/////////////////
	CString	m_Orient_C;
	CString	m_Orient_P;
	////////////////////////////////// Duct & Sweep
	BOOL	m_bTwist;	// TRUE:Twist/FALSE:Radius
	pDOUBLE	m_pTwist;
	int		m_nMaxTwist;
	BOOL	m_bIncrement;
	double	m_TwistStart;
	double	m_TwistMult;
	double	m_dCoord;
	//////////////////// Xtrude
	double	m_dLen;
	int		m_nExtruType;
	WORLD	m_wLen;
	//////////////////// Rotation
	BOOL	m_bAxis;
	BOOL	m_bNegative;
	int		m_nTotElems;
	int		m_nElemPerSeg;
	double	m_dAngSpec;
	int		m_nAxis;
	//////////////////// XTrude & Rotate
	BOOL	m_bGenBCurve;
	BOOL	m_bGenBPatch;
	//////////////////// tensor
	double	m_Ratio_V;
	double	m_Ratio_W;
	int		m_nMesh_V;
	int		m_nMesh_W;
	BOOL	m_bAdvanced;
	//////////////////// End Condition
	BOOL		m_bEditMode;		// TRUE:User Checking/FALSE:DataInputting
	BOOL		m_bU;				// TRUE:U_Dir/FALSE:V_Dir
	BOOL		m_bV;				// TRUE:U_Dir/FALSE:V_Dir
	BOOL		m_bW;				// TRUE:U_Dir/FALSE:V_Dir
	int			m_nOrder;			// k
	int			m_nNode_U;			// #DataNodes
	int			m_nNode_V;			// #DataNodes
	int			m_nNode_W;			// #DataNodes
	int			m_indexNode_I;		// Selected BndryNodeIndex in NodeList	
	CDListMgr*	m_pNodeList;		// DataNodeList
	CList<BLENDEND,BLENDEND>*
				m_pEndList_U;
	CList<BLENDEND,BLENDEND>*
				m_pEndList_V;
	CList<BLENDEND,BLENDEND>*
				m_pEndList_W;
	//////////////////////////////////
	BOOL		m_bAllSame;			// Dlg_PI_EndCond
	////////////////////////////////// 
	BOOL		m_bCornerMode;			// needed for Corner Twist
	int			m_nCornerI;
	int			m_nCornerJ;
	PWMAT2		m_pCornerTwist;		// it is full,if TW_USER
	TWIST		m_TwistMethod[2][2];
	/////////////////////////////////////////////////
    CWnd*		m_pWnd;
	SOLIDPROC	m_SolProc;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSasePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSasePage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEPAGE_H__C4D67362_C187_11D2_8B46_444553540000__INCLUDED_)
