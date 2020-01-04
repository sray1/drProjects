 // mp_Rotat.h : header file
//
#ifndef _MC_CUBE_H 
#define _MC_CUBE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "Inter_C3.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Cube : public CMI_GangC
class AFX_EXT_CLASS CMC_Cube : public CMI_GangC
{
public:

	CMC_Cube();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Cube)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	GoDoIt(); 
 	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
	int 		InterPolate_C3(BOOL bFinal);

    				
		
protected:

	CDrCurve*	GetInfo(int nButton);
	/////////////////////////////////////////////////////////////////// Linear
	int 		C3_SetMemory();
	int 		C3_PrepInterpolation(CInter_C3* pInter_C3);
	int 		C3_PostInterpolation(CInter_C3* pInter_C3,BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes


//Operations
public:

	~CMC_Cube();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Cube)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
