// CNodeCard.h : header file
//
#ifndef _NODECARDOBJECT
#define _NODECARDOBJECT

#include "stdafx.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeCard
/////////////////////////////////////////////////////////////////////////////
class CNodeCard : public CCardMgr
{
// Construction
public:  
	CNodeCard();
	DECLARE_SERIAL(CNodeCard)
protected: 
public:
// Implementation
public:
	
	int			GetSearchNet(){return m_nSearchNet;};
	void		SetSearchNet(int nNet){ m_nSearchNet = nNet;};
	int			GetSearchNetOld(){return m_nSearchNetOld;};
	void		SetSearchNetOld(int nNet){ m_nSearchNetOld = nNet;};
	int			GetSearchNetDefault(){return m_nSearchNetDefault;};
	void		SetSearchNetDefault(int nNet){ m_nSearchNetDefault = nNet;};
	
protected: 

	///////////////////////////////////////////////////// Unit 
	void 	ReadDefaultNodeCard();
	void	InitializeNodeCard();
	
protected:

	int			m_nSearchNet;
	int 		m_nSearchNetOld;
	int			m_nSearchNetDefault;

protected: 

public:
	virtual ~CNodeCard(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CNodeCard)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif
