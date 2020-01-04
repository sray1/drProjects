 // Dynamic Load Mouse.h : header file
//
#ifndef _SPL_MOUSE_H 
#define _SPL_MOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SLDMouse.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSpLMouse : public CSLDMouse
{
public:

	CSpLMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CSpLMouse)
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

	~CSpLMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSpLMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
