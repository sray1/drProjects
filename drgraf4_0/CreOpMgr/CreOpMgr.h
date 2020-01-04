// elemobj.h : header file
//
#ifndef _CREOPMGR_H
#define _CREOPMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "NodCreOp.h"
//#include "CurCreOp.h"
//#include "PatCreOp.h"
//#include "SolCreOp.h"
#include "O3DCreOp.h"
//#include "SupCreOp.h"
//#include "SLdCreOp.h"
//#include "SpLCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CCreOpMgr
/////////////////////////////////////////////////////////////////////////////
class CCreOpMgr : public CObject
{
// Construction
public:  
	CCreOpMgr();
	DECLARE_SERIAL(CCreOpMgr)
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
//	CPatCreOp*	GetPatCreOp(){return &m_PatCreOp;};
	CO3DCreOp*	GetSolCreOp(){return &m_O3DCreOp;};	
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
	CO3DCreOp		m_O3DCreOp;	// Dynamic Load		// for now
//	CSupCreOp		m_SupMouse;	// Support
//	CSLDCreOp		m_SLdMouse;	// Static Load
//	CSpLCreOp		m_SpLMouse;	// Spectral Load
//	CDLDCreOp		m_DLDCreOp;	// Dynamic Load
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CCreOpMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CCreOpMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
