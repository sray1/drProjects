// elemobj.h : header file
//
#ifndef _MOUSEMGR_H
#define _MOUSEMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
#include "DLdMouse.h"
#include "dbMouse.h"
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


	UINT		GetCurrentProcessType(){return m_uCurrentProcessType;};
	void		SetCurrentProcessType(UINT u){m_uCurrentProcessType = u;};
	BOOL		IsCurrentProcessDone(){return m_bCurrentProcessDone;};
	void		SetCurrentProcessDone(BOOL b){m_bCurrentProcessDone =b;};
	//////////////////////////////////////////////////////////////////////
	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	//////////////////////////
	void		InitDlgIn();
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
	CDBMouse*	GetDBMouse(){return &m_DBMouse;};
//	CSolMouse*	GetSolMouse(){return &m_SolMouse;};
//	CSupMouse*	GetSupMouse(){return &m_SupMouse;};
//	CSLDMouse*	GetSLDMouse(){return &m_SLdMouse;};
	CDLDMouse*	GetDLDMouse(){return &m_DLdMouse;};
//	CSpLMouse*	GetSPLMouse(){return &m_SpLMouse;};
    ///////////////////////////////////////////
	LPOINT3		GetStatusMouseWIC();
	void		SetStatusMouseWIC(LPOINT3 StatWIC);
	////////////////////////////////////////////////////////							



protected:


	UINT			m_uCurrentProcessType;
	BOOL			m_bCurrentProcessDone;
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
//	CSolMouse		m_SolMouse;	// Solid
//	CSupMouse		m_SupMouse;	// Support
//	CSLDMouse		m_SLdMouse;	// Static Load
//	CSpLMouse		m_SpLMouse;	// Spectral Load
	CDLDMouse		m_DLdMouse;	// Dynamic Load
	CDBMouse		m_DBMouse;	// Drawing others
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
