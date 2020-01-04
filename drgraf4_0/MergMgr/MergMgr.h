// elemobj.h : header file
//
#ifndef _MERGMGR_H
#define _MERGMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
#include "MNodMerg.h"
#include "DLdMerg.h"
#include "dbMerg.h"
/////////////////////////////////////////////////////////////////////////////
// CMergMgr
/////////////////////////////////////////////////////////////////////////////
class CMergMgr : public CObject
{
// Construction
public:  
	CMergMgr();
	DECLARE_SERIAL(CMergMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	UINT		ReSetToolID_Mesh(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CDBMerg*	GetDBMerg(){return &m_DBMerg;};
  	CDLDMerg*	GetDLDMouse(){return &m_DLdMerg;};
  	CMNodMerg*	GetMDLDMouse(){return &m_MNodMerg;};
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
  	CMNodMerg		m_MNodMerg;	// Mesh Node
  	CDLDMerg		m_DLdMerg;	// Dynamic Load
//	CDBMerg			m_DBMerg;	// Drawing others
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CMergMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMergMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
