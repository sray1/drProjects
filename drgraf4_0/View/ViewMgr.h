// elemobj.h : header file
//
#ifndef _VIEWMGR_H
#define _VIEWMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CViewMgr
/////////////////////////////////////////////////////////////////////////////
class CViewMgr : public CObject
{
// Construction
public:  
	CViewMgr();
	DECLARE_SERIAL(CViewMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT OperID);
	UINT		CreateorActivateDlgIn(UINT wParam, long lParam);
	UINT		UpdateDlgIn(UINT wParam, long lParam);
	UINT		CancelDlgIn(UINT wParam, long lParam);
	UINT		GoodByeDlgIn(UINT wParam, long lParam);
	//////////////////////////
	void		InitDlgIn(UINT OperID);
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
	CVuRotate*	GetVuRotate(){return &m_VuRotate;};	
    ///////////////////////////////////////////
	LPOINT3		GetStatusMouseWIC();
	void		SetStatusMouseWIC(LPOINT3 StatWIC);
	////////////////////////////////////////////////////////							



protected:

	////////////////////////////////
	HCURSOR			m_hUpArrow;
	HCURSOR			m_hCross;
	HCURSOR			m_hDoubleArrow;
	HCURSOR			m_hHand_12;
	HCURSOR			m_hHand_23;
	HCURSOR			m_hHand_31;
	HCURSOR			m_hHand_ISO;
	HCURSOR			m_hText;
	///////////////////////////////////////// mouse
	CVuRotate		m_VuRotate;	// Rotate
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CViewMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CViewMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
