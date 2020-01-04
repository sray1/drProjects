 // Dynamic Load Mouse.h : header file
//
#ifndef _SPL_CREOP_H 
#define _SPL_CREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SLDCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSpLCreOp : public CSLDCreOp
{
public:

	CSpLCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CSpLCreOp)
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

	~CSpLCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSpLCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
