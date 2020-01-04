 // ELMouse.h : header file
//
#ifndef _REGENNOD_H 
#define _RegenNod_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CRegenNod : public CMouse
{
public:

	CRegenNod();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenNod)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateNode(CDrNode* pNode);	// Supports & Loads

protected:  
// Attributes





//Operations
public:

	~CRegenNod();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenNod)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
