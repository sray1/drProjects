 // mp_Rotat.h : header file
//
#ifndef _MC_SPAWN_H 
#define _MC_SPAWN_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "DrCurve.h"
#include "glb_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Spawn : public CMI_GangC
class CMC_Spawn : public CMI_GangC
{
public:

	CMC_Spawn();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Spawn)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	int		RBUp_CSpawn(CView* pView,UINT nView); 
    				
		
protected:

	////////////////////////////////////////////////////////////
	CDrCurve* 	GetInfo();
	/////////////////////////
		          

protected:  
// Attributes


//Operations
public:

	~CMC_Spawn();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Spawn)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
