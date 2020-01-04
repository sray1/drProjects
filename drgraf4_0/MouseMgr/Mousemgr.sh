// elemobj.h : header file
//
#ifndef _MOUSEMGR_H
#define _MOUSEMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
#include "elmouse.h"
#include "dbmouse.h"
/////////////////////////////////////////////////////////////////////////////
// CMouseMgr
/////////////////////////////////////////////////////////////////////////////
class CMouseMgr : public CObject
{
// Construction
public:  
	CMouseMgr();
	DECLARE_SERIAL(CMouseMgr)
protected: 
public:
// Implementation 

public:

	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// 
	CELMouse*	GetELMouse(int nView);
	CDBMouse*	GetDBMouse(int nView);
	//////////////////////////////////////////////////////////////
	LPOINT3		GetStatusMouseWIC();
	void		SetStatusMouseWIC(LPOINT3 StatWIC);
	////////////////////////////////////////////////////////							
protected:

	///////////////////////////////////////////////////// Mouse
	CELMouse*		GetELMouse12(){return &m_ELMouse12;};
	CDBMouse*		GetDBMouse12(){return &m_DBMouse12;};
	CELMouse*		GetELMouse23(){return &m_ELMouse23;};
	CDBMouse*		GetDBMouse23(){return &m_DBMouse23;};
	CELMouse*		GetELMouse31(){return &m_ELMouse31;};
	CDBMouse*		GetDBMouse31(){return &m_DBMouse31;};
	CELMouse*		GetELMouseIso(){return &m_ELMouseIso;};
	CDBMouse*		GetDBMouseIso(){return &m_DBMouseIso;};
    ///////////////////////////////////////////
protected:

	HCURSOR			m_hUpArrow;
	HCURSOR			m_hCross;
	HCURSOR			m_hDoubleArrow;
	HCURSOR			m_hHand_12;
	HCURSOR			m_hHand_23;
	HCURSOR			m_hHand_31;
	HCURSOR			m_hHand_ISO;
	HCURSOR			m_hText;
	///////////////////////////////////////// mouse
	CELMouse		m_ELMouse12;
	CDBMouse		m_DBMouse12;
	CELMouse		m_ELMouse23;
	CDBMouse		m_DBMouse23;
	CELMouse		m_ELMouse31;
	CDBMouse		m_DBMouse31;
	CELMouse		m_ELMouseIso;
	CDBMouse		m_DBMouseIso;
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CMouseMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMouseMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
