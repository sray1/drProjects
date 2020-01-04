 // ELMouse.h : header file
//
#ifndef _REGENPROF_C_H 
#define _REGENPROF_C_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CRegenProf_C : public CMouse
{
public:

	CRegenProf_C();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenProf_C)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
	////////////////////////////////////////////////////////////////// Curve
	int				ReGen_EditedProf_C_Controls(CDrProf_C* pEditedProfile);


protected:

protected:  
// Attributes





//Operations
public:

	~CRegenProf_C();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenProf_C)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
