// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////// toolboxes
/*
#include "elembox.h"
#include "drawbox.h"
*/          
///////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	
/*
    CElemBox* 	GetElemBox(){return &m_wndElemBox;};
    CSize		GetSizeElemBox(){return m_szElemBox;};
    void		SetSizeElemBox(CSize szBox){m_szElemBox = szBox;};

    CDrawBox* 	GetDrawBox(){return &m_wndDrawBox;};
    CSize		GetSizeDrawBox(){return m_szDrawBox;};
    void		SetSizeDrawBox(CSize szBox){m_szDrawBox = szBox;};
*/    

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
/*
	CElemBox	m_wndElemBox;
	CSize		m_szElemBox;

	CDrawBox	m_wndDrawBox;
	CSize		m_szDrawBox;
*/

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
