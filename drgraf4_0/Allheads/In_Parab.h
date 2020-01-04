 // In_Circle.h : header file
//
#ifndef _IN_PARAB_H 
#define _IN_PARAB_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
#include "In_Conics.h"
#include "Def_Type.h"
#include "Def_CuPS.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CIn_Parab : public CIn_Conics
{
public:

	CIn_Parab();
//////////////////////////////////////
	DECLARE_SERIAL(CIn_Parab)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
			//////////////////////////////////////////////////////////
			int		Prepare();
			int		Interpolate();
			////////////////////////////////////////////////////////// Info
			//////////////////////////////////////////////////////////
							
							
		
protected:

			int		Compute_InBetweens(pWORLD Data,pWORLD Con,pDOUBLE Wts,int L);
		          

protected:
  
// Attributes
protected:


	
			/////////////////////////////////////////////////////////////// Info
    
    
//Operations
public:

	~CIn_Parab();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CIn_Parab)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
