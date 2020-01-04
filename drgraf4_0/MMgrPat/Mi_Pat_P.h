 // ELMouse.h : header file
//
#ifndef _MI_PAT_P_H 
#define _MI_PAT_P_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
//#include "MI_Cur_P.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Pat_P : public CObject
{
public:

	CMI_Pat_P();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Pat_P)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
//	virtual int	 	Post_Patch(CDrObject* pObject);
    //////////////////////////////////////////////
	virtual int 	LBDownInit_PPost(){return 0;}; 
	virtual int 	LBUpPatchPost();
	////////////////////////////////////////////// 
    				
		
protected:

	/////////////////////////
		          

protected:  
// Attributes

	CDrPatch* 	m_pDrPatch;
	////////////////////////
//Operations
public:

	~CMI_Pat_P();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Pat_P)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
