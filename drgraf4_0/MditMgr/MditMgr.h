// elemobj.h : header file
//
#ifndef _MDITMGR_H
#define _MDITMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
#include "SolMdit.h"
//#include "DLdMdit.h"
#include "dbMdit.h"
/////////////////////////////////////////////////////////////////////////////
// CMditMgr
/////////////////////////////////////////////////////////////////////////////
class CMditMgr : public CObject
{
// Construction
public:  
	CMditMgr();
	DECLARE_SERIAL(CMditMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	UINT		ReSetToolID_Mesh(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CDBEdit*	GetDBEdit(){return &m_DBEdit;};
//	CDLDMdit*	GetDLDMouse(){return &m_DLdEdit;};
	CSolMdit*	GetDLDMouse(){return &m_MNodEdit;};
	CSolMdit*	GetMDLDMouse(){return &m_MNodEdit;};
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
	CSolMdit		m_MNodEdit;	// Mesh Node
//	CDLDMdit		m_DLdEdit;	// Dynamic Load
//	CDBEdit			m_DBEdit;	// Drawing others
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CMditMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMditMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
