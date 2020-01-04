// CardMgr.h : header file
//
#ifndef _CARDMGR
#define _CARDMGR

#include "stdafx.h"     

#include "elglobal.h"
//#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CElemObject
/////////////////////////////////////////////////////////////////////////////
class CCardMgr : public CElemObject
{
// Construction
public:  
	CCardMgr();
	DECLARE_SERIAL(CCardMgr)
protected: 
public:
// Implementation 

public:

/*
	///////////////////////////////////////////////////// Elements
	UINT		GetElementNameCount(){return m_nElementNameCount;};
	CString		GetElementName(UINT nIndex){return m_ElementNames[nIndex];};
	BOOL		GetElementBoxStatus(){return m_bElementBox;};
	void		SetElementBoxStatus(BOOL bStatus){m_bElementBox = bStatus;};
	BOOL		GetElementModeStatus(){return m_bElementMode;};
	int			GetElementType(){return m_nElementType;};
	void		SetElementType(int nElementType)
					{m_nElementType = nElementType;};
	///////////////////////////////////////////////////// NODE
	void 		SerializeNode(CArchive& ar);
	CObList*	GetNodeList(){return &m_NodeList;};
	int			GetNodeCount(){return m_NodeList.GetCount();}; 
	CString     GetCurrentNodeID(){return m_CurrentNodeID;};
    void    	SetCurrentNodeID(CString CurrentNodeID)
    			{
    				m_CurrentNodeID = CurrentNodeID;
    			};    			 
	///////////////////////////////////////////////////// CardList
//	void 		SerializePipe(CArchive& ar);
*/	
protected:

	
/*	
	///////////////////////////////////////// ElementBox
	CString		m_ElementNames[50];
	UINT		m_nElementNameCount;                    
	/////////////////////////////////////////// Node     
	CObList	m_NodeList;
	int		m_MaxNodes;
	/////////////////////////////////////////// Pipe     
	CObList	m_PipeList;
	int		m_MaxPipes;
    /////////////////////////////////////////// Next
protected: 
*/
public:
	virtual ~CCardMgr(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o

	// Generated message map functions
	//{{AFX_MSG(CCardMgr)
	//}}AFX_MSG

};

#endif
