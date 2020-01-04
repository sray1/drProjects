// Mouse.h : header file
//
#ifndef _DB_MOUSE_H 
#define _DB_MOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
/////////////////////////////////////////////////////////////////////////////
// CDBMouse view
//////////////////////////////////////////////////////
class CDBMouse : public CMouse
{
public:

	CDBMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CDBMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public: 

	////////////////////////////////////// Mouse Helpers
	void 	OnDBoxMouseMove(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point);
	void 	OnDBoxLButtonDown(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point);
	void 	OnDBoxRButtonDown(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point);
	void 	OnDBoxLButtonUp(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point);
	void 	OnDBoxRButtonUp(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point);
	////////////////////////////////////////////////////////////////////// FreeHand
	virtual int		GetFHIndexCurrent(){return m_nFHIndexCurrent;};
	virtual void	SetFHIndexCurrent(int nIndex){m_nFHIndexCurrent = nIndex;};
	virtual int		GetFHNumberCurrent(){return m_nFHNumberCurrent;};
	virtual void	SetFHNumberCurrent(int nNum)
						{ m_nFHNumberCurrent = nNum;};
	virtual CString GetCurrentLabelID(){return m_CurrentLabelID;}; 
    virtual void    SetCurrentLabelID(CString CurrentLabelID)
    				{
    					m_CurrentLabelID = CurrentLabelID;
    				}; 
	/////////////////////////////////////////////////////	

protected:

	///////////////////////////////////////////////////////////////////// helpers
	void 	DBoxMMove_FREEHAND(CClientDC* pdc,CPoint point);
	void 	DBoxLBDown_FREEHAND(CPoint point);
	void 	DBoxLBUp_FREEHAND(CPoint point);
    //////////////////////////////////////////
	void 	DBoxMMove_OBJECTMOVE(CClientDC* pdc,CPoint point);
	void    DBoxLBDown_OBJECTMOVE(CClientDC* pdc,CPoint point);
	void 	DBoxLBUp_OBJECTMOVE(CClientDC* pdc,CPoint point,CView* pView);
	
// Attributes
protected:

	///////////////////////////////////////// Label     
	CString		m_CurrentLabelID;
	///////////////////////////////////////// FreeHand     
	int			m_nFHNumberCurrent;
	int			m_nFHIndexCurrent;
	/////////////////////////////////////////// 

//Operations
public:

	~CDBMouse();
	virtual void Serialize(CArchive& ar);

/////////////////////////////////////////////////////////////////////////////
/*
	// Generated message map functions

	//{{AFX_MSG(CDBMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
