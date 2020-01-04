// dlg_cpro.h : header file
//
#ifndef _DLG_1PRO_H
#define _DLG_1PRO_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MMs1Rsrc.h"
#include "DrProf_C.h"
#include "MatObj.h"
#include "Def_CuPS.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_1Pro dialog

class CDlg_1Pro : public CDialog
{
// Construction
public:
	CDlg_1Pro(CWnd* pParent = NULL);	// standard constructor

	
protected:
	

	/////////////////
	void	SetUpLocalm(pMATRIX pM);
	void	FirstCurve();
	void	NonFirstCurve();
	void	GetTranslations(); 
	void	EmptyListAllString(UINT DlgID);
	void	EmptyComboAllString(UINT DlgID);
	void	FillListAllString_Pool();
	void	FillListAllString_Profile();
	void	FillListAllString_NID(CString& CID, UINT DlgID);
	void	SetInfoForDataBase(CDrProf_1* pDrObject);


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_1Pro)
	enum { IDD = IDD_C_SPLICE };
	CString	m_CPro_ID;
	CString	m_Orient;
	//}}AFX_DATA
	BOOL		m_bCur_Ist;
	/////////////////////////// Transformation
	double		m_RotX;
	double		m_RotY;
	double		m_RotZ;
	double		m_TranX;
	double		m_TranY;
	double		m_TranZ;
	BOOL		m_bLMat;
 	CDListMgr	m_LMList; 
	/////////////////////// These needed for editing later so save in MatObj
	CString		m_End_NID;	// Connectivity
	CString		m_TranPtID;	// Only for the Ist Curve
	CString		m_RotPtID;
	CString		m_FromID;
	CString		m_ToID;
	CMatObj		m_MatObj;
 	int 		m_nHowMany;
	MATRIX		m_LocalM;
	WORLD		m_savRot;
	CURVELATCH	m_CuLat;


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_1Pro)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDefaultLmat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
