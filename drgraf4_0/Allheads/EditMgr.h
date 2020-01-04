// elemobj.h : header file
//
#ifndef _EDITMGR_H
#define _EDITMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
//#include "MNodEdit.h"
#include "DLdEdit.h"
#include "dbEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CEditMgr
/////////////////////////////////////////////////////////////////////////////
class CEditMgr : public CObject
{
// Construction
public:  
	CEditMgr();
	DECLARE_SERIAL(CEditMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
//090298	UINT		ReSetToolID_Mesh(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CDBEdit*	GetDBEdit(){return &m_DBEdit;};
	CDLDEdit*	GetDLDMouse(){return &m_DLdEdit;};
//090298	CMNodEdit*	GetMDLDMouse(){return &m_MNodEdit;};
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
//090298	CMNodEdit		m_MNodEdit;	// Mesh Node
	CDLDEdit		m_DLdEdit;	// Dynamic Load
//	CDBEdit			m_DBEdit;	// Drawing others
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CEditMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CEditMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
