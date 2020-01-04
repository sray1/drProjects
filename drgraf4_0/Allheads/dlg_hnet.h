// preciDlg.h : header file
//
#ifndef _DLG_HNET_H_
#define _DLG_HNET_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "SdlgRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_HNet dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDlg_HNet : public CDialog
{
// Construction
public:
	CDlg_HNet(CWnd* pParent = NULL);	// standard constructor
	void OnHitNet();
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
// Dialog Data
	//{{AFX_DATA(CDlg_HNet)
	enum { IDD = IDD_HITNET };
	int		m_nPixNet;
	double	m_dPhysNet;
	double	m_dCoLinear;
	double	m_dCoPlanar;
	double	m_dRatio;
	double	m_NodeMerge_Y;
	double	m_NodeMerge_X;
	double	m_NodeMerge_Z;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_HNet)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

