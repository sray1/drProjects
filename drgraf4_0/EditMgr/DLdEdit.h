 // Dynamic Load Mouse.h : header file
//
#ifndef _DLD_EDIT_H 
#define _DLD_EDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SpLEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CDLDEdit : public CSpLEdit
{
public:

	CDLDEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CDLDEdit)
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

	~CDLDEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CDLDEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
