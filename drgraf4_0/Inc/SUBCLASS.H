// subclass.h : header file
//
#ifndef _SUBCLASS
#define _SUBCLASS
/////////////////////////////////////////////////////////////////////////////
// CSubclassDlg dialog

class CSubclassDlg : public CDialog
{
// Construction
public:
	CSubclassDlg(UINT id);   //  constructor with any dialog id
protected: 
	CBitmapButton buttonOK,buttonCancel;
    
// Dialog Data
	//{{AFX_DATA(CSubclassDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    
	// Generated message map functions
	//{{AFX_MSG(CSubclassDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif  
