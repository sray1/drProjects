// viewinfo.h : header file
//
#ifndef _VIEWINFO_H
#define _VIEWINFO_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "viewrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CViewInfo dialog

class AFX_EXT_CLASS CViewInfo : public CDialog
{
// Construction
public:
	CViewInfo(CView* pView);	// message filtered to View
    BOOL Create ();
// Dialog Data
	//{{AFX_DATA(CViewInfo)
	enum { IDD = IDD_VIEWINFO };
	double	m_dBack;
	double	m_dFront;
	double	m_PRP_X;
	double	m_PRP_Y;
	double	m_PRP_Z;
	double	m_Umax;
	double	m_Umin;
	double	m_Vmax;
	double	m_Vmin;
	double	m_VPN_X;
	double	m_VPN_Y;
	double	m_VPN_Z;
	double	m_VRP_X;
	double	m_VRP_Y;
	double	m_VRP_Z;
	double	m_VUP_X;
	double	m_VUP_Y;
	double	m_VUP_Z;
	//}}AFX_DATA
    CView*	m_pView;

protected: 

	CBitmapButton buttonOK,buttonCancel;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CViewInfo)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
