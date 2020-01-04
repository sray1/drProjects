// dlg_grid.h : header file
//
#ifndef _DLG_GRID_H 
#define _DLG_GRID_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    

#include "ddlgrsrc.h"
#include "DrGrid.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Grid dialog

class CDlg_Grid : public CDialog
{
// Construction
public:
	CDlg_Grid(CWnd* pParent = NULL);	// standard constructor

protected: 
	CBitmapButton buttonOK,buttonCancel;

public:	

// Dialog Data
	//{{AFX_DATA(CDlg_Grid)
	enum { IDD = IDD_GRID };
	CString	m_AlignNid;
	BOOL	m_bBack;
	BOOL	m_bAlign;
	BOOL	m_bBottom;
	CString	m_FromNid;
	CString	m_MaxNid;
	CString	m_MinNid;
	CString	m_ToNid;
	BOOL	m_bFront;
	BOOL	m_bFull;
	CString	m_GridID;
	BOOL	m_bLeft;
	BOOL	m_bRight;
	BOOL	m_bRotate;
	UINT	m_nStepX;
	UINT	m_nStepY;
	UINT	m_nStepZ;
	BOOL	m_bTop;
	BOOL	m_bConX;
	BOOL	m_bConY;
	BOOL	m_bConZ;
	//}}AFX_DATA
	BOOL	m_bGrType;	// 0(FALSE) = draw/ 1(TRUE)= data 
	BOOL	m_bDraw;	// 0(FALSE) = BackGround / 1(TRUE)= ForeGround

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	void FillListAllNodeIDs();
	void SetInfoForDataBase(CDrGrid* pDrObject);


	// Generated message map functions
	//{{AFX_MSG(CDlg_Grid)
	virtual BOOL OnInitDialog();
	afx_msg void OnAlign();
	afx_msg void OnBack();
	afx_msg void OnBackground();
	afx_msg void OnBottom();
	afx_msg void OnForeground();
	afx_msg void OnFront();
	afx_msg void OnFull();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnRotate();
	afx_msg void OnTop();
	afx_msg void OnXcon();
	afx_msg void OnYcon();
	afx_msg void OnZcon();
	virtual void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
