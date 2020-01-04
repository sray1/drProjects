// elemobj.h : header file
//
#ifndef _DELMGR_H
#define _DELMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
#include "DLdDel.h"
#include "dbDel.h"
/////////////////////////////////////////////////////////////////////////////
// CDelMgr
/////////////////////////////////////////////////////////////////////////////
class CDelMgr : public CObject
{
// Construction
public:  
	CDelMgr();
	DECLARE_SERIAL(CDelMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CDBEdit*	GetDBEdit(){return &m_DBEdit;};
	CDLDDel*	GetDLDMouse(){return &m_DLdDel;};
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
	////////////////////////////////////////////////
	CDLDDel			m_DLdDel;	// Dynamic Load
//	CDBEdit			m_DBEdit;	// Drawing others
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CDelMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDelMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
