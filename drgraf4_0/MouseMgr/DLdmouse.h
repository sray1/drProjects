 // Dynamic Load Mouse.h : header file
//
#ifndef _DLD_MOUSE_H 
#define _DLD_MOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SpLMouse.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CDLDMouse : public CSpLMouse
{
public:

	CDLDMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CDLDMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 


protected:




protected:  
// Attributes





//Operations
public:

	~CDLDMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CDLDMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
