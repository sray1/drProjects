 // mp_Rotat.h : header file
//
#ifndef _MC_QUAD_H 
#define _MC_QUAD_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "Inter_C2.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Quad : public CMI_GangC
class AFX_EXT_CLASS CMC_Quad : public CMI_GangC
{
public:

	CMC_Quad();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Quad)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	GoDoIt(); 
 	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
	int 		InterPolate_C2(BOOL bFinal);

    				
		
protected:

	CDrCurve*	GetInfo(int nButton);
	/////////////////////////////////////////////////////////////////// Linear
	int 		C2_SetMemory();
	int 		C2_PrepInterpolation(CInter_C2* pInter_C2);
	int 		C2_PostInterpolation(CInter_C2* pInter_C2,BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes


//Operations
public:

	~CMC_Quad();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Quad)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
