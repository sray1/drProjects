 // Dynamic Load Mouse.h : header file
//
#ifndef _SPL_EDIT_H 
#define _SPL_EDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SLDEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSpLEdit : public CSLDEdit
{
public:

	CSpLEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CSpLEdit)
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

	~CSpLEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSpLEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
