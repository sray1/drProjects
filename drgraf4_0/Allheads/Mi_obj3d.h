 // ELMouse.h : header file
//
#ifndef _MI_OBJ3D_H 
#define _MI_OBJ3D_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                   
#include "drObj3D.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Obj3D : public CObject
{
public:

	CMI_Obj3D();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Obj3D)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
    /////////////////////////////////////////////
    virtual int 	LBDownInit_OEdit(){return 0;}; 
    virtual int 	LBUpObj3DEdit(){return 0;}; 
    virtual int 	LBDownInit_OMove(){return 0;}; 
    virtual int 	LBUpObj3DMove(){return 0;}; 
	///////////////////////////////////////////// 
    virtual int 	LBDownInit_OInsert(); 
    virtual int 	LBUpInit_OInsert(); 
    virtual int 	LBUp_OInsert(CView* pView,UINT nView); 
    				

		
protected:

	//////////////////////////////////////////////////////////// Obj3D
	int 		InsertAllInfo();
	CDrObj3D* 	O_GetInfo();

		          

protected:  
// Attributes
protected:


	/////////////////////////////////////////// Curve
	CDrObj3D* 	m_pDrObj3D;
    /////////////////////////////////////////// Next

//Operations
public:

	~CMI_Obj3D();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Obj3D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
