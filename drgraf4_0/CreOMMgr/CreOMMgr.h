// elemobj.h : header file
//
#ifndef _CREOMMGR_H
#define _CREOMMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
#include "PatCreOM.h"
//#include "SolCreOp.h"
//#include "M3DCreOM.h"
//#include "SupCreOp.h"
//#include "SLdCreOp.h"
//#include "SpLCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CCreOMMgr
/////////////////////////////////////////////////////////////////////////////
class CCreOMMgr : public CObject
{
// Construction
public:  
	CCreOMMgr();
	DECLARE_SERIAL(CCreOMMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	UINT		CreateorActivateCreIn(UINT wParam, long lParam);
	UINT		UpdateCreIn(UINT wParam, long lParam);
	UINT		CancelCreIn(UINT wParam, long lParam);
	UINT		GoodByeCreIn(UINT wParam, long lParam);
	//////////////////////////
	void		InitDlgIn();
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CNodCreOp*	GetNodCreOp(){return &m_NodCreOp;};
//	CCurCreOp*	GetCurCreOp(){return &m_CurCreOp;};
	CPatCreOM*	GetSolCreOp(){return &m_PatCreOM;};
//	CMs2CreOM*	GetSolCreOp(){return &m_Ms2CreOM;};	
//	CSupCreOp*	GetSupCreOp(){return &m_SupCreOp;};
//	CSLDCreOp*	GetSLDCreOp(){return &m_SLdCreOp;};
//	CSpLCreOp*	GetSPLCreOp(){return &m_SpLCreOp;};
//	CDLDCreOp*	GetDLDCreOp(){return &m_DLdCreOp;};
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
//	CNodCreOp		m_NodCreOp;	// Dynamic Load
//	CCurCreOp		m_CurCreOp;	// Dynamic Load
//	CPatCreOp		m_PatCreOp;	// Dynamic Load
	CPatCreOM		m_PatCreOM;	// Dynamic Load		// for now
//	CSupCreOp		m_SupMouse;	// Support
//	CSLDCreOp		m_SLdMouse;	// Static Load
//	CSpLCreOp		m_SpLMouse;	// Spectral Load
//	CDLDCreOp		m_DLDCreOp;	// Dynamic Load
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CCreOMMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CCreOMMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
