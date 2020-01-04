// elemobj.h : header file
//
#ifndef _POSTMGR_H
#define _POSTMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


//#include "mouseloc.h"
//#include "SolMouse.h"
//#include "SupMouse.h"
//#include "SLdMouse.h"
//#include "SpLMouse.h"
#include "PatPost.h"
/////////////////////////////////////////////////////////////////////////////
// CPostMgr
/////////////////////////////////////////////////////////////////////////////
class CPostMgr : public CObject
{
// Construction
public:  
	CPostMgr();
	DECLARE_SERIAL(CPostMgr)
protected: 
public:
// Implementation 

public:

	UINT		ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID);
	//////////////////////////
	void		InitDlgIn();
	///////////////////////////////////////////////////// Cursor
	void		SetViewCursor(int nType);
	///////////////////////////////////////////////////// Mouse
//	CDBEdit*	GetDBEdit(){return &m_DBEdit;};
	CPatPost*	GetDLDMouse(){return &m_DLdPost;};
    ///////////////////////////////////////////
	LPOINT3		GetStatusMouseWIC();
	void		SetStatusMouseWIC(LPOINT3 StatWIC);
	////////////////////////////////////////////////////////
	void		SizeRectDlgIn(CRect& BoxRect);



protected:

	HCURSOR			m_hUpArrow;
	HCURSOR			m_hCross;
	HCURSOR			m_hDoubleArrow;
	HCURSOR			m_hHand_12;
	HCURSOR			m_hHand_23;
	HCURSOR			m_hHand_31;
	HCURSOR			m_hHand_ISO;
	HCURSOR			m_hText;
	////////////////////////////////////////////////
	CPatPost		m_DLdPost;	// Dynamic Load
//	CDBEdit			m_DBEdit;	// Drawing others
	///////////////////////////// StatusBar MouseLoc
	LPOINT3			m_StatusMouseWIC; 
	/////////////////////////////////

public:
	virtual ~CPostMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CPostMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
