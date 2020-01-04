// elemdoc.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#ifndef DR_ELEM_DOC
#define DR_ELEM_DOC 

#include "globals.h"
#include "drgradoc.h"
/////////////////////////////////////////////////////////////////////////////
// CElemDoc document

class CEl : public CObject
{
	DECLARE_SERIAL(CElemDoc)
protected:
	CElemDoc();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	///////////////////////////////////////////////////// NODE
	CObList*	GetNodeList(){return &m_NodeList;};
	int			GetNodeCount(){return m_NodeList.GetCount();}; 
	CString     GetCurrentNodeID(){return m_CurrentNodeID;};
    void    	SetCurrentNodeID(CString CurrentNodeID)
    			{
    				m_CurrentNodeID = CurrentNodeID;
    			};
	CString*    GetAnchorNodeID(){return &m_AnchorNodeID;};
    void    	SetAnchorNodeID(CString AnchorNodeID)
    			{
    				m_AnchorNodeID = AnchorNodeID;
    			};
	///////////////////////////////////////////////////// PIPE
	CObList*	GetPipeList(){return &m_PipeList;};
	int			GetPipeCount(){return m_PipeList.GetCount();};
	CString*    GetCurrentPipeID(){return &m_CurrentPipeID;}; 
	
protected:

	CObList	m_NodeList;
	CObList	m_PipeList;
	/////////////////////////////////////////// Node     
	CString m_CurrentNodeID;
	CString m_AnchorNodeID;
	int		m_MaxNodes;
	/////////////////////////////////////////// Pipe     
	CString m_CurrentPipeID;
	int		m_MaxPipes;

// Implementation
protected:
	virtual ~CElemDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
	virtual	BOOL OnNewDocument();

	// Generated message map functions
protected:
	//{{AFX_MSG(CElemDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
////////////////////////////////////
#endif

