// dlg_rotp.h : header file
//
#ifndef _DLG_ROTP_S_H
#define _DLG_ROTP_S_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrPatch.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_RotP_S dialog

class CDlg_RotP_S : public CDialog
{
// Construction
public:
	CDlg_RotP_S(CWnd* pParent = NULL);	// standard constructor
	void SetInfoForDataBase(CDrSolid* pDrObject);

protected:
	
	void FillListAllSolidIDs();
	void FillListAllNodeIDs();
	void FillListAllPatchIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_RotP_S)
	enum { IDD = IDD_ROTATE_SOLID };
	double	m_dAng_2;
	CString	m_FromID;
	CString	m_ToID;
	CString	m_CurveID;
	double	m_Ratio;
	int		m_nMesh;
	CString	m_PatchID;
	BOOL	m_bFromCN;
	BOOL	m_bToCN;
	//}}AFX_DATA
	double		m_dAng_1;
   	PATSUBTYPE	m_SubType;
	BOOL		m_bUnifOT;
	//////////////////
	pINT	m_pOSeg;
	pDOUBLE	m_pODis;
	////////////////////

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_RotP_S)
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
