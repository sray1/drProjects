// dlg_rotp.h : header file
//
#ifndef _DLG_ROTP_H
#define _DLG_ROTP_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_RotP dialog

class CDlg_RotP : public CDialog
{
// Construction
public:
	CDlg_RotP(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrPatch* pDrObject);

protected:
	
	void FillListAllCurveIDs();
	void FillListAllNodeIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_RotP)
	enum { IDD = IDD_ROTATE_PATCH };
	double	m_dAng_2;
	CString	m_FromID;
	CString	m_ToID;
	CString	m_CurveID;
	double	m_Ratio;
	int		m_nMesh;
	CString	m_PatchID;
	CString	m_Orient_1;
	BOOL	m_bFromCN;
	BOOL	m_bToCN;
	//}}AFX_DATA
	double	m_dAng_1;
   	int 	m_nHowMany;
	BOOL	m_bUnifOT;
	//////////////////
	pINT	m_pOSeg;
	pDOUBLE	m_pODis;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_RotP)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
