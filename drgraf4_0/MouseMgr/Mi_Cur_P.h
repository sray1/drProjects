 // ELMouse.h : header file
//
#ifndef _MI_CUR_P_H 
#define _MI_PUR_P_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_Curve.h"
#include "DrNode.h"
#include "DrFE2D.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Cur_P : public CObject
{
public:

	CMI_Cur_P();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Cur_P)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
//	virtual int	 	Post_Patch(CDrObject* pObject);
    //////////////////////////////////////////////
	virtual int 	LBDownInit_CPost(){return 0;}; 
	virtual int 	LBUpCurvePost();
	////////////////////////////////////////////// 
    				
		
protected:

	/////////////////////////
		          

protected:  
// Attributes

	////////////////////////
//Operations
public:

	~CMI_Cur_P();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Cur_P)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
